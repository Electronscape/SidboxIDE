#include "gametilemap.h"
#include "ppbcodec.h"

#include <QAbstractScrollArea>
#include <QComboBox>
#include <QCheckBox>
#include <QSettings>
#include <QPalette>
#include <QPen>
#include <QDialogButtonBox>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QJsonValue>
#include <QJsonArray>
#include <QTimer>
#include <QRegion>
#include <QLabel>
#include <QMessageBox>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QPainter>
#include <QSaveFile>
#include <QPushButton>
#include <QPaintEvent>
#include <QResizeEvent>
#include <utility>
#include <QScrollBar>
#include <QScrollArea>
#include <QPixmap>
#include <QEvent>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QtGlobal>

void SidboxTilemap::resizeMap(int w, int h)
{
    w = qBound(30, w, 256);
    h = qBound(20, h, 256);
    QByteArray nextG(w * h, char(0)), nextC(w * h, char(0));
    for (int y = 0; y < qMin(h, height); ++y)
        for (int x = 0; x < qMin(w, width); ++x) {
            const int from = y * width + x, to = y * w + x;
            if (from < graphics.size()) nextG[to] = graphics.at(from);
            if (from < collisions.size()) nextC[to] = collisions.at(from);
        }
    width = w; height = h;
    graphics = nextG; collisions = nextC;
}

QJsonObject SidboxTilemap::toJson() const
{
    QJsonObject result;
    result.insert(QStringLiteral("width"), width);
    result.insert(QStringLiteral("height"), height);
    result.insert(QStringLiteral("tileSize"), tileSize);
    result.insert(QStringLiteral("atlasPath"), atlasPath);
    result.insert(QStringLiteral("graphicsZ"), QString::fromLatin1(qCompress(graphics, 9).toBase64()));
    result.insert(QStringLiteral("collisionsZ"), QString::fromLatin1(qCompress(collisions, 9).toBase64()));
    QJsonArray animated;
    for (const SidboxTileAnimation &a : animations) {
        QJsonObject item;
        item.insert(QStringLiteral("graphicId"), a.graphicId);
        item.insert(QStringLiteral("frames"), a.frames);
        item.insert(QStringLiteral("frameTicks"), a.frameTicks);
        item.insert(QStringLiteral("loop"), a.loop);
        item.insert(QStringLiteral("bounce"), a.bounce);
        animated.append(item);
    }
    result.insert(QStringLiteral("animations"), animated);
    return result;
}

bool SidboxTilemap::fromJson(const QJsonObject &object)
{
    const int w = object.value(QStringLiteral("width")).toInt(100);
    const int h = object.value(QStringLiteral("height")).toInt(100);
    const int tile = object.value(QStringLiteral("tileSize")).toInt(16);
    if (w < 30 || w > 256 || h < 20 || h > 256 ||
        (tile != 8 && tile != 16 && tile != 32)) return false;
    const QString encodedG = object.value(QStringLiteral("graphicsZ")).toString();
    const QString encodedC = object.value(QStringLiteral("collisionsZ")).toString();
    if (encodedG.size() > 131072 || encodedC.size() > 131072) return false;
    const QByteArray compressedG = QByteArray::fromBase64(encodedG.toLatin1());
    const QByteArray compressedC = QByteArray::fromBase64(encodedC.toLatin1());
    // qUncompress uses a 4-byte big-endian uncompressed-length prefix.
    // Reject excessive/corrupt lengths before requesting decompression.
    auto expectedLength = [](const QByteArray &data) -> quint32 {
        if (data.size() < 4) return 0;
        const auto *p = reinterpret_cast<const unsigned char *>(data.constData());
        return (quint32(p[0]) << 24) | (quint32(p[1]) << 16) | (quint32(p[2]) << 8) | p[3];
    };
    if (expectedLength(compressedG) != quint32(w * h) ||
        expectedLength(compressedC) != quint32(w * h)) return false;
    const QByteArray g = qUncompress(compressedG);
    const QByteArray c = qUncompress(compressedC);
    if (g.size() != w * h || c.size() != w * h) return false;
    QVector<SidboxTileAnimation> decoded;
    const QJsonValue animationValue = object.value(QStringLiteral("animations"));
    if (!animationValue.isUndefined() && !animationValue.isArray()) return false;
    const QJsonArray list = animationValue.toArray();
    if (list.size() > 255) return false;
    bool seen[256] = {};
    for (const QJsonValue &value : list) {
        if (!value.isObject()) return false;
        const QJsonObject entry = value.toObject();
        SidboxTileAnimation a;
        a.graphicId = entry.value(QStringLiteral("graphicId")).toInt(0);
        a.frames = entry.value(QStringLiteral("frames")).toInt(0);
        a.frameTicks = entry.value(QStringLiteral("frameTicks")).toInt(0);
        a.loop = entry.value(QStringLiteral("loop")).toBool(true);
        a.bounce = entry.value(QStringLiteral("bounce")).toBool(false);
        if (a.graphicId < 1 || a.graphicId > 255 || a.frames < 1 ||
            a.frames > 16 || a.graphicId + a.frames - 1 > 255 ||
            a.frameTicks < 1 || a.frameTicks > 255 || seen[a.graphicId]) return false;
        seen[a.graphicId] = true;
        decoded.append(a);
    }
    width = w; height = h; tileSize = tile;
    atlasPath = object.value(QStringLiteral("atlasPath")).toString();
    graphics = g; collisions = c;
    animations = decoded;
    return true;
}

// Same playback maths as the V1 helper (50 VBlanks per second).
static int tileAnimationFrame(const SidboxTileAnimation &a, qint64 ticks)
{
    if (a.frames < 2 || a.frameTicks < 1) return 0;
    const qint64 step = ticks / a.frameTicks;
    if (a.bounce) {
        const qint64 last = a.frames - 1;
        const qint64 cycle = last * 2;
        const qint64 pos = a.loop ? step % cycle : qMin(step, cycle);
        return int(pos <= last ? pos : cycle - pos);
    }
    return int(a.loop ? step % a.frames : qMin(step, qint64(a.frames - 1)));
}

static const SidboxTileAnimation *findTileAnimation(const SidboxTilemap &map, int id)
{
    for (const SidboxTileAnimation &a : map.animations)
        if (a.graphicId == id) return &a;
    return nullptr;
}

// Same flat, visible-chevron treatment as the main Game Designer controls.
// The colours are inherited from the active CoderGirl theme.
class TilemapComboBox final : public QComboBox
{
public:
    using QComboBox::QComboBox;
protected:
    void paintEvent(QPaintEvent *event) override
    {
        QComboBox::paintEvent(event);
        QPainter painter(this);
        QPen pen(palette().color(isEnabled() ? QPalette::Active : QPalette::Disabled,
                                 QPalette::Text));
        pen.setWidth(2);
        painter.setPen(pen);
        const int cx = width() - 12;
        const int cy = height() / 2;
        painter.drawLine(cx - 4, cy - 2, cx, cy + 2);
        painter.drawLine(cx, cy + 2, cx + 4, cy - 2);
    }
};

class SidboxTilemapEditor::Canvas final : public QAbstractScrollArea
{
public:
    SidboxTilemap *map = nullptr;
    QImage *atlas = nullptr;
    int zoom = 2;
    bool showCollisions = true;
    // -1 = preserve existing value, 0 = erase, 1 = selected atlas tile.
    int graphicMode = 1;
    int graphicBrush = 1;
    int collisionBrush = -1;
    bool painting = false;
    bool panning = false;
    QPoint lastPan;
    int wheelRemainderX = 0;
    int wheelRemainderY = 0;
    qint64 animationTicks = 0;
    void refreshAnimated(qint64 ticks)
    {
        if (!map || map->animations.isEmpty()) return;
        if (ticks == animationTicks) return;
        animationTicks = ticks;
        const int px = map->tileSize * zoom;
        const int scrollX = horizontalScrollBar()->value();
        const int scrollY = verticalScrollBar()->value();
        const int x0 = qMax(0, scrollX / px);
        const int y0 = qMax(0, scrollY / px);
        const int x1 = qMin(map->width, (scrollX + viewport()->width()) / px + 1);
        const int y1 = qMin(map->height, (scrollY + viewport()->height()) / px + 1);
        QRegion dirty;
        for (int y = y0; y < y1; ++y)
            for (int x = x0; x < x1; ++x) {
                const int id = quint8(map->graphics.at(y*map->width+x));
                if (findTileAnimation(*map, id))
                    dirty += QRect(x*px-scrollX, y*px-scrollY, px, px);
            }
        if (!dirty.isEmpty()) viewport()->update(dirty);
    }

    explicit Canvas(QWidget *parent = nullptr) : QAbstractScrollArea(parent)
    {
        setFocusPolicy(Qt::StrongFocus);
        setMouseTracking(true);
        viewport()->setCursor(Qt::CrossCursor);
    }
    void adjust()
    {
        if (!map) return;
        const int px = map->tileSize * zoom;
        horizontalScrollBar()->setRange(0, qMax(0, map->width * px - viewport()->width()));
        verticalScrollBar()->setRange(0, qMax(0, map->height * px - viewport()->height()));
        horizontalScrollBar()->setPageStep(viewport()->width());
        verticalScrollBar()->setPageStep(viewport()->height());
        viewport()->update();
    }
    void paintAt(const QPoint &at, bool erase)
    {
        if (!map) return;
        const int px = map->tileSize * zoom;
        const int tx = (at.x() + horizontalScrollBar()->value()) / px;
        const int ty = (at.y() + verticalScrollBar()->value()) / px;
        if (tx < 0 || ty < 0 || tx >= map->width || ty >= map->height) return;
        const int index = ty * map->width + tx;
        bool changed = false;
        // One stroke can change graphics and collision together, or either one.
        if (graphicMode >= 0) {
            const char value = char(erase ? 0 : (graphicMode == 0 ? 0 : graphicBrush));
            if (map->graphics.at(index) != value) {
                map->graphics[index] = value;
                changed = true;
            }
        }
        if (collisionBrush >= 0) {
            const char value = char(erase ? 0 : collisionBrush);
            if (map->collisions.at(index) != value) {
                map->collisions[index] = value;
                changed = true;
            }
        }
        if (changed) {
            viewport()->update(QRect(tx * px - horizontalScrollBar()->value(),
                                     ty * px - verticalScrollBar()->value(), px+1, px+1));
        }
    }
protected:
    void resizeEvent(QResizeEvent *event) override { QAbstractScrollArea::resizeEvent(event); adjust(); }
    void paintEvent(QPaintEvent *event) override
    {
        QPainter painter(viewport());
        const QRect dirty = event->rect();
        painter.fillRect(dirty, QColor(28, 37, 49));
        if (!map) return;
        const int px = map->tileSize * zoom;
        const int scrollX = horizontalScrollBar()->value();
        const int scrollY = verticalScrollBar()->value();
        const int x0 = qMax(0, (scrollX + dirty.left()) / px);
        const int y0 = qMax(0, (scrollY + dirty.top()) / px);
        const int x1 = qMin(map->width, (scrollX + dirty.right()) / px + 2);
        const int y1 = qMin(map->height, (scrollY + dirty.bottom()) / px + 2);
        const int cols = atlas && !atlas->isNull() ? atlas->width() / map->tileSize : 0;
        const int rows = atlas && !atlas->isNull() ? atlas->height() / map->tileSize : 0;
        painter.setRenderHint(QPainter::SmoothPixmapTransform, false);
        for (int y = y0; y < y1; ++y) for (int x = x0; x < x1; ++x) {
            const QRect dest(x * px - scrollX, y * px - scrollY, px, px);
            const int i = y * map->width + x;
            const int tile = quint8(map->graphics.at(i));
            int frameTile = tile;
            if (const SidboxTileAnimation *anim = findTileAnimation(*map, tile))
                if (tile + anim->frames - 1 <= cols*rows)
                    frameTile += tileAnimationFrame(*anim, animationTicks);
            if (frameTile && cols > 0 && frameTile <= cols * rows) {
                const int n = frameTile - 1;
                painter.drawImage(dest, *atlas, QRect((n % cols) * map->tileSize,
                    (n / cols) * map->tileSize, map->tileSize, map->tileSize));
            } else if (tile) {
                painter.fillRect(dest, QColor(84, 90, 105));
                painter.setPen(Qt::white);
                painter.drawText(dest, Qt::AlignCenter, QString::number(tile));
            }
            if (showCollisions) {
                const unsigned type = quint8(map->collisions.at(i));
                if (type) {
                    const QColor colour = type == 1 ? QColor(50, 233, 179, 110)
                        : type == 2 ? QColor(255, 216, 70, 125)
                        : type == 5 ? QColor(240, 78, 75, 135)
                        : type == 6 ? QColor(153, 103, 246, 140)
                        : QColor(84, 174, 244, 135);
                    painter.fillRect(dest, colour);
                    painter.setPen(Qt::white);
                    painter.drawText(dest, Qt::AlignCenter, QString::number(type));
                }
            }
            painter.setPen(QColor(128, 157, 175, 68));
            painter.drawRect(dest.adjusted(0, 0, -1, -1));
        }
    }
    void mousePressEvent(QMouseEvent *e) override
    {
        if (e->button() == Qt::MiddleButton ||
            (e->button() == Qt::LeftButton && e->modifiers() & Qt::AltModifier)) {
            panning = true; lastPan = e->position().toPoint();
            viewport()->setCursor(Qt::ClosedHandCursor); return;
        }
        if (e->button() == Qt::LeftButton || e->button() == Qt::RightButton) {
            painting = true; paintAt(e->position().toPoint(), e->button() == Qt::RightButton);
        }
    }
    void mouseMoveEvent(QMouseEvent *e) override
    {
        if (panning) {
            const QPoint at = e->position().toPoint();
            horizontalScrollBar()->setValue(horizontalScrollBar()->value() + lastPan.x() - at.x());
            verticalScrollBar()->setValue(verticalScrollBar()->value() + lastPan.y() - at.y());
            lastPan = at;
        } else if (painting && e->buttons() & (Qt::LeftButton | Qt::RightButton)) {
            paintAt(e->position().toPoint(), bool(e->buttons() & Qt::RightButton));
        }
    }
    void mouseReleaseEvent(QMouseEvent *e) override
    {
        if (e->button() == Qt::MiddleButton || e->button() == Qt::LeftButton) {
            panning = false;
            viewport()->setCursor(Qt::CrossCursor);
        }
        if (e->button() == Qt::RightButton || e->button() == Qt::LeftButton) painting = false;
    }
    void wheelEvent(QWheelEvent *e) override
    {
        // Move exactly one map tile per mouse-wheel notch, at the current zoom.
        // Keep middle-button dragging pixel-accurate and unchanged.
        const QPoint angle = e->angleDelta();
        if (angle.isNull()) {
            // Touchpads may send pixel-based scrolling instead of wheel notches.
            QAbstractScrollArea::wheelEvent(e);
            return;
        }

        int deltaX = angle.x();
        int deltaY = angle.y();
        if ((e->modifiers() & Qt::ShiftModifier) && deltaX == 0) {
            deltaX = deltaY;
            deltaY = 0;
        }

        // Some wheels send fractions of a notch: collect them until 120 units.
        wheelRemainderX += deltaX;
        wheelRemainderY += deltaY;
        const int notchesX = wheelRemainderX / 120;
        const int notchesY = wheelRemainderY / 120;
        wheelRemainderX -= notchesX * 120;
        wheelRemainderY -= notchesY * 120;

        const int tilePixels = map ? map->tileSize * zoom : 16 * zoom;
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - notchesX * tilePixels);
        verticalScrollBar()->setValue(verticalScrollBar()->value() - notchesY * tilePixels);
        e->accept();
    }
};

SidboxTilemapEditor::SidboxTilemapEditor(SidboxTilemap map,
    const QVector<QPair<QString, QString>> &atlases,
    const QString &designDirectory, QWidget *parent)
    : QDialog(parent), m_map(std::move(map)), m_designDirectory(designDirectory)
{
    setWindowTitle(tr("Visual Tilemap Editor — Graphics + Collisions"));
    resize(960, 700);
    // Restore the last window state. First-time opening defaults to maximised.
    QSettings windowSettings(QStringLiteral("Sidbox"), QStringLiteral("SidboxIDE"));
    const QByteArray geometry = windowSettings.value(
        QStringLiteral("GameTilemapEditor/geometry")).toByteArray();
    if (geometry.isEmpty() || !restoreGeometry(geometry))
        setWindowState(windowState() | Qt::WindowMaximized);

    // Match the square-edged, theme-coloured Game Designer dropdowns.
    // TilemapComboBox draws the arrow itself, avoiding Qt style-specific arrows.
    setStyleSheet(QStringLiteral(
        "QComboBox { border:1px solid palette(mid); border-radius:0px; "
        "background:palette(base); color:palette(text); padding:3px 24px 3px 5px; } "
        "QComboBox::drop-down { width:20px; border-left:1px solid palette(mid); "
        "border-radius:0px; } "
        "QComboBox::down-arrow { image:none; width:0px; height:0px; } "
        "QComboBox QAbstractItemView { border:1px solid palette(mid); "
        "border-radius:0px; background:palette(base); color:palette(text); "
        "selection-background-color:palette(highlight); "
        "selection-color:palette(highlighted-text); }"));
    auto *layout = new QVBoxLayout(this);
    auto *form = new QHBoxLayout;
    auto *sizeX = new QSpinBox(this), *sizeY = new QSpinBox(this);
    sizeX->setRange(30, 256); sizeY->setRange(20, 256);
    sizeX->setValue(m_map.width); sizeY->setValue(m_map.height);
    auto *tileSize = new TilemapComboBox(this);
    for (int s : {8, 16, 32}) tileSize->addItem(QString::number(s) + QStringLiteral(" px"), s);
    tileSize->setCurrentIndex(qMax(0, tileSize->findData(m_map.tileSize)));
    auto *atlasChoice = new TilemapComboBox(this);
    atlasChoice->setMinimumWidth(130);
    atlasChoice->addItem(tr("No artwork (IDs only)"), QString());
    for (const auto &a : atlases) atlasChoice->addItem(a.first, a.second);
    const QString existing = QDir(m_designDirectory).absoluteFilePath(m_map.atlasPath);
    const int selected = atlasChoice->findData(existing);
    if (selected >= 0) atlasChoice->setCurrentIndex(selected);
    else if (!m_map.atlasPath.isEmpty()) {
        atlasChoice->addItem(tr("Missing: %1").arg(m_map.atlasPath), existing);
        atlasChoice->setCurrentIndex(atlasChoice->count()-1);
    }
    // Both layers are painted with one drag. Either dropdown can opt out.
    auto *brushC = new TilemapComboBox(this);
    for (const QPair<QString, int> &type : QVector<QPair<QString,int>>{
         {tr("Don't change collision"), -1},
         {tr("0 — Empty (no collision)"), 0}, {tr("1 — Solid"), 1},
         {tr("2 — One-way"), 2}, {tr("3 — Slope rising right"), 3},
         {tr("4 — Slope falling right"), 4}, {tr("5 — Hazard"), 5},
         {tr("6 — Door"), 6}})
        brushC->addItem(type.first, type.second);
    auto *brushG = new TilemapComboBox(this);
    brushG->addItem(tr("Don't change graphic"), -1);
    brushG->addItem(tr("0 — Empty graphic"), 0);
    brushG->addItem(tr("Selected atlas tile (ID 1)"), 1);
    brushG->setCurrentIndex(2);
    m_graphicMode = brushG;
    brushG->setToolTip(tr("Click a tile in the atlas below to select it. "
        "Choose Don't change graphic to paint collisions only."));
    brushC->setToolTip(tr("Choose Don't change collision to paint graphics only. "
        "Otherwise both layers are painted with one stroke."));
    form->addWidget(new QLabel(tr("Tiles X"))); form->addWidget(sizeX);
    form->addWidget(new QLabel(tr("Y"))); form->addWidget(sizeY);
    form->addWidget(new QLabel(tr("Tile"))); form->addWidget(tileSize);
    form->addWidget(new QLabel(tr("Artwork"))); form->addWidget(atlasChoice, 1);
    layout->addLayout(form);
    auto *paintRow = new QHBoxLayout;
    paintRow->addWidget(new QLabel(tr("Paint collision type:")));
    paintRow->addWidget(brushC);
    paintRow->addSpacing(8);
    paintRow->addWidget(new QLabel(tr("Paint graphic:")));
    paintRow->addWidget(brushG);
    auto *collisionOverlay = new QCheckBox(tr("Show collisions"), this);
    collisionOverlay->setChecked(true);
    collisionOverlay->setToolTip(tr("Show or hide the collision overlay while editing either layer."));
    paintRow->addStretch();
    layout->addLayout(paintRow);
    auto *viewRow = new QHBoxLayout;
    viewRow->addWidget(collisionOverlay);
    auto *zoom = new TilemapComboBox(this);
    for (int z : {1, 2, 3, 4}) zoom->addItem(QStringLiteral("%1×").arg(z), z);
    zoom->setCurrentIndex(1);
    viewRow->addStretch();
    viewRow->addWidget(new QLabel(tr("Zoom")));
    viewRow->addWidget(zoom);
    layout->addLayout(viewRow);
    // Click the atlas image to select an actual tile, without typing an ID.
    auto *tilePickerArea = new QScrollArea(this);
    tilePickerArea->setWidgetResizable(false);
    tilePickerArea->setFixedHeight(100);
    m_atlasPicker = new QLabel(tilePickerArea);
    m_atlasPicker->setText(tr("Choose a PPB tile sheet above, then click a tile here."));
    m_atlasPicker->setToolTip(tr("Click a tile to select it for graphic painting. "
        "The yellow outline shows the selected tile."));
    m_atlasPicker->installEventFilter(this);
    tilePickerArea->setWidget(m_atlasPicker);
    layout->addWidget(tilePickerArea);

    // Animation definitions are separate from both tile maps. Selecting an
    // atlas tile edits ONE shared animation, never the pixels or collision.
    auto *animationRow = new QHBoxLayout;
    m_animationPreview = new QLabel(this);
    m_animationPreview->setFixedSize(72, 72);
    m_animationPreview->setAlignment(Qt::AlignCenter);
    m_animationPreview->setToolTip(tr("Live preview of the selected tile, at 50 game frames/sec."));
    animationRow->addWidget(m_animationPreview);
    auto *animationFields = new QVBoxLayout;
    auto *animationValues = new QHBoxLayout;
    m_animFrames = new QSpinBox(this);
    m_animFrames->setRange(1, 16);
    m_animFrames->setValue(4);
    m_animFrames->setToolTip(tr("Number of consecutive atlas cells to play, starting from the selected tile."));
    m_animDelay = new QSpinBox(this);
    m_animDelay->setRange(1, 255);
    m_animDelay->setValue(5);
    m_animDelay->setToolTip(tr("How many VBlanks to hold each frame (50 VBlanks is about one second at 50 FPS)."));
    animationValues->addWidget(new QLabel(tr("Frames:"), this));
    animationValues->addWidget(m_animFrames);
    animationValues->addWidget(new QLabel(tr("VBlanks per frame:"), this));
    animationValues->addWidget(m_animDelay);
    m_animLoop = new QCheckBox(tr("Loop"), this);
    m_animLoop->setChecked(true);
    m_animBounce = new QCheckBox(tr("Ping-pong"), this);
    animationValues->addWidget(m_animLoop);
    animationValues->addWidget(m_animBounce);
    auto *setAnimation = new QPushButton(tr("Set Animation"), this);
    m_removeAnimation = new QPushButton(tr("Remove Animation"), this);
    setAnimation->setToolTip(tr("Save animation properties for the selected atlas tile."));
    m_removeAnimation->setToolTip(tr("Turn the selected tile back into an ordinary static graphic."));
    animationFields->addLayout(animationValues);
    auto *buttonRow = new QHBoxLayout;
    buttonRow->addWidget(setAnimation);
    buttonRow->addWidget(m_removeAnimation);
    buttonRow->addStretch();
    animationFields->addLayout(buttonRow);
    m_animationStatus = new QLabel(this);
    m_animationStatus->setWordWrap(true);
    animationFields->addWidget(m_animationStatus);
    animationRow->addLayout(animationFields, 1);
    layout->addLayout(animationRow);

    m_canvas = new Canvas(this);
    m_canvas->map = &m_map;
    m_canvas->atlas = &m_atlas;
    layout->addWidget(m_canvas, 1);
    auto *help = new QLabel(tr("LEFT-DRAG paints both enabled layers  |  RIGHT-DRAG erases enabled layers  |  "
        "MIDDLE-DRAG or ALT+LEFT-DRAG pans.\n"
        "Pick a graphic by clicking the atlas above. Choose 'Don't change' in either dropdown "
        "to leave that layer untouched."), this);
    help->setWordWrap(true); layout->addWidget(help);
    auto *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttons->button(QDialogButtonBox::Ok)->setText(tr("Apply to Design"));
    layout->addWidget(buttons);
    connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(sizeX, qOverload<int>(&QSpinBox::valueChanged), this, [this](int v) {
        m_map.resizeMap(v, m_map.height); m_canvas->adjust();
    });
    connect(sizeY, qOverload<int>(&QSpinBox::valueChanged), this, [this](int v) {
        m_map.resizeMap(m_map.width, v); m_canvas->adjust();
    });
    connect(tileSize, qOverload<int>(&QComboBox::currentIndexChanged), this,
        [this, tileSize](int) {
            m_map.tileSize = tileSize->currentData().toInt();
            m_canvas->adjust(); updateAtlasPicker(); updateAnimationControls();
        });
    connect(atlasChoice, qOverload<int>(&QComboBox::currentIndexChanged), this,
        [this, atlasChoice](int) { setAtlas(atlasChoice->currentData().toString()); });
    connect(brushG, qOverload<int>(&QComboBox::currentIndexChanged), this,
        [this, brushG](int) { m_canvas->graphicMode = brushG->currentData().toInt(); });
    connect(brushC, qOverload<int>(&QComboBox::currentIndexChanged), this,
        [this, brushC](int) { m_canvas->collisionBrush = brushC->currentData().toInt(); });
    connect(collisionOverlay, &QCheckBox::toggled, this,
        [this](bool enabled) {
            m_canvas->showCollisions = enabled;
            m_canvas->viewport()->update();
        });
    connect(zoom, qOverload<int>(&QComboBox::currentIndexChanged), this,
        [this, zoom](int) { m_canvas->zoom = zoom->currentData().toInt(); m_canvas->adjust(); });
    connect(setAnimation, &QPushButton::clicked, this,
        [this]() { saveSelectedAnimation(); });
    connect(m_removeAnimation, &QPushButton::clicked, this,
        [this]() { removeSelectedAnimation(); });
    connect(m_animFrames, qOverload<int>(&QSpinBox::valueChanged), this,
        [this](int) { updateAnimationPreview(); });
    connect(m_animDelay, qOverload<int>(&QSpinBox::valueChanged), this,
        [this](int) { updateAnimationPreview(); });
    connect(m_animLoop, &QCheckBox::toggled, this,
        [this](bool) { updateAnimationPreview(); });
    connect(m_animBounce, &QCheckBox::toggled, this,
        [this](bool) { updateAnimationPreview(); });
    setAtlas(atlasChoice->currentData().toString());
    m_canvas->adjust();
    m_animationClock.start();
    m_animationTimer = new QTimer(this);
    m_animationTimer->setInterval(40); // sample at 25fps, timing remains 50Hz
    connect(m_animationTimer, &QTimer::timeout, this, [this]() {
        if (!isVisible()) return;
        m_canvas->refreshAnimated(m_animationClock.elapsed() / 20);
        updateAnimationPreview();
    });
    m_animationTimer->start();
}

void SidboxTilemapEditor::setAtlas(const QString &absolutePath)
{
    m_map.atlasPath = absolutePath.isEmpty() ? QString()
        : QDir(m_designDirectory).relativeFilePath(absolutePath);
    m_atlas = QImage();
    if (!absolutePath.isEmpty()) {
        SidboxPpb::Picture picture;
        QString error;
        if (SidboxPpb::read(absolutePath, &picture, &error)) m_atlas = picture.indexed;
        else QMessageBox::warning(this, tr("Tile Artwork"), error);
    }
    if (m_canvas) m_canvas->graphicBrush = 1;
    updateAtlasPicker();
    updateAnimationControls();
    if (m_canvas) m_canvas->viewport()->update();
}

void SidboxTilemapEditor::updateAtlasPicker()
{
    if (!m_atlasPicker || !m_canvas) return;
    if (m_atlas.isNull()) {
        m_atlasPicker->setPixmap(QPixmap());
        m_atlasPicker->setText(tr("No PPB tile sheet selected (IDs only)."));
        m_atlasPicker->adjustSize();
    } else {
        // A two-times enlargement keeps nearest-neighbour pixel art crisp.
        QPixmap display = QPixmap::fromImage(m_atlas).scaled(
            m_atlas.width() * 2, m_atlas.height() * 2,
            Qt::IgnoreAspectRatio, Qt::FastTransformation);
        const int cols = m_atlas.width() / m_map.tileSize;
        const int rows = m_atlas.height() / m_map.tileSize;
        const int selected = m_canvas->graphicBrush - 1;
        if (cols > 0 && rows > 0 && selected >= 0 && selected < cols * rows) {
            QPainter painter(&display);
            QPen outline(QColor(255, 217, 65));
            outline.setWidth(2);
            painter.setPen(outline);
            const int px = m_map.tileSize * 2;
            painter.drawRect(QRect((selected % cols) * px, (selected / cols) * px,
                                   px, px).adjusted(1, 1, -2, -2));
        }
        m_atlasPicker->setPixmap(display);
        m_atlasPicker->adjustSize();
    }
    if (m_graphicMode) {
        m_graphicMode->setItemText(2,
            tr("Selected atlas tile (ID %1)").arg(m_canvas->graphicBrush));
    }
}

void SidboxTilemapEditor::updateAnimationControls()
{
    if (!m_animFrames || !m_canvas) return;
    const int id = m_canvas->graphicBrush;
    const int cols = m_atlas.isNull() ? 0 : m_atlas.width()/m_map.tileSize;
    const int rows = m_atlas.isNull() ? 0 : m_atlas.height()/m_map.tileSize;
    const int count = qMin(255, cols*rows);
    const bool valid = id > 0 && id <= count;
    const SidboxTileAnimation *anim = findTileAnimation(m_map, id);
    m_animFrames->setMaximum(qMax(1, qMin(16, count - id + 1)));
    m_animFrames->setValue(anim ? anim->frames : qMin(4, m_animFrames->maximum()));
    m_animDelay->setValue(anim ? anim->frameTicks : 5);
    m_animLoop->setChecked(anim ? anim->loop : true);
    m_animBounce->setChecked(anim ? anim->bounce : false);
    m_removeAnimation->setEnabled(anim != nullptr);
    if (m_animationStatus) {
        m_animationStatus->setText(!valid ?
            tr("Choose a tile from the atlas to define its animation.") :
            anim ? tr("Tile %1: animated (%2 frames). Changes apply to every cell painted with ID %1.")
                  .arg(id).arg(anim->frames) :
            tr("Tile %1: static. Choose settings and press Set Animation. Frames must be consecutive in the atlas.").arg(id));
    }
    updateAnimationPreview();
}

void SidboxTilemapEditor::updateAnimationPreview()
{
    if (!m_animationPreview || !m_canvas || m_atlas.isNull()) return;
    const int id = m_canvas->graphicBrush;
    const int cols = m_atlas.width()/m_map.tileSize;
    const int rows = m_atlas.height()/m_map.tileSize;
    if (!cols || id < 1 || id > qMin(255, cols*rows)) {
        m_animationPreview->clear();
        return;
    }
    SidboxTileAnimation current;
    if (const SidboxTileAnimation *saved = findTileAnimation(m_map, id)) current = *saved;
    else {
        current.graphicId = id;
        current.frames = 1;
    }
    // Show the SAVED animation, not unsaved edits in the property widgets.
    const int frameId = id + tileAnimationFrame(current,
        m_animationClock.isValid() ? m_animationClock.elapsed()/20 : 0);
    const QRect source(((frameId-1)%cols)*m_map.tileSize,
                       ((frameId-1)/cols)*m_map.tileSize,
                       m_map.tileSize, m_map.tileSize);
    m_animationPreview->setPixmap(QPixmap::fromImage(m_atlas.copy(source)).scaled(
        64, 64, Qt::KeepAspectRatio, Qt::FastTransformation));
}

void SidboxTilemapEditor::saveSelectedAnimation()
{
    if (!m_canvas || m_atlas.isNull()) return;
    const int id = m_canvas->graphicBrush;
    const int cols = m_atlas.width()/m_map.tileSize;
    const int rows = m_atlas.height()/m_map.tileSize;
    if (!cols || id < 1 || id > qMin(255, cols*rows)) {
        QMessageBox::warning(this, tr("Tile Animation"), tr("Select a valid atlas tile first."));
        return;
    }
    SidboxTileAnimation a;
    a.graphicId = id;
    a.frames = m_animFrames->value();
    a.frameTicks = m_animDelay->value();
    a.loop = m_animLoop->isChecked();
    a.bounce = m_animBounce->isChecked();
    if (a.graphicId+a.frames-1 > qMin(255, cols*rows)) {
        QMessageBox::warning(this, tr("Tile Animation"),
            tr("The selected frame range goes past the end of the atlas."));
        return;
    }
    bool updated = false;
    for (SidboxTileAnimation &entry : m_map.animations)
        if (entry.graphicId == id) { entry = a; updated = true; break; }
    if (!updated) m_map.animations.append(a);
    updateAnimationControls();
    m_canvas->viewport()->update();
}

void SidboxTilemapEditor::removeSelectedAnimation()
{
    if (!m_canvas) return;
    const int id = m_canvas->graphicBrush;
    for (int i = 0; i < m_map.animations.size(); ++i)
        if (m_map.animations.at(i).graphicId == id) {
            m_map.animations.removeAt(i);
            break;
        }
    updateAnimationControls();
    m_canvas->viewport()->update();
}

void SidboxTilemapEditor::done(int result)
{
    // Save for Apply and Cancel alike: window state is a user preference,
    // not a tilemap edit. saveGeometry includes the maximised state.
    QSettings settings(QStringLiteral("Sidbox"), QStringLiteral("SidboxIDE"));
    settings.setValue(QStringLiteral("GameTilemapEditor/geometry"), saveGeometry());
    QDialog::done(result);
}

bool SidboxTilemapEditor::eventFilter(QObject *target, QEvent *event)
{
    if (target == m_atlasPicker && event->type() == QEvent::MouseButtonPress &&
        !m_atlas.isNull() && m_graphicMode) {
        const auto *mouse = static_cast<QMouseEvent *>(event);
        if (mouse->button() == Qt::LeftButton) {
            const int cols = m_atlas.width() / m_map.tileSize;
            const int rows = m_atlas.height() / m_map.tileSize;
            const int tx = int(mouse->position().x()) / (2*m_map.tileSize);
            const int ty = int(mouse->position().y()) / (2*m_map.tileSize);
            if (cols && tx >= 0 && tx < cols && ty >= 0 && ty < rows) {
                const int id = ty*cols+tx+1;
                if (id <= 255) {
                    m_canvas->graphicBrush = id;
                    m_graphicMode->setCurrentIndex(2);
                    updateAtlasPicker();
                    updateAnimationControls();
                }
            }
            return true;
        }
    }
    return QDialog::eventFilter(target, event);
}

bool sidboxExportTilemap(const SidboxTilemap &map, const QString &designDirectory,
                         QString *error)
{
    if (map.width < 30 || map.width > 256 || map.height < 20 || map.height > 256 ||
        (map.tileSize != 8 && map.tileSize != 16 && map.tileSize != 32) ||
        map.graphics.size() != map.width * map.height ||
        map.collisions.size() != map.width * map.height) {
        if (error) *error = QStringLiteral("Invalid tilemap dimensions or data.");
        return false;
    }
    // Optional tile atlas is a normal indexed PPB sprite sheet, with each
    // graphic ID 1..255 referring to successive tile-sized cells.
    QByteArray packedTiles;
    unsigned tileCount = 0;
    if (!map.atlasPath.isEmpty()) {
        SidboxPpb::Picture picture;
        if (!SidboxPpb::read(QDir(designDirectory).absoluteFilePath(map.atlasPath), &picture, error))
            return false;
        const QImage &image = picture.indexed;
        if (image.width() % map.tileSize || image.height() % map.tileSize) {
            if (error) *error = QStringLiteral("Tile artwork dimensions must be multiples of %1 pixels.").arg(map.tileSize);
            return false;
        }
        const int cols = image.width() / map.tileSize, rows = image.height() / map.tileSize;
        tileCount = qMin(cols * rows, 255);
        packedTiles.reserve(int(tileCount) * map.tileSize * map.tileSize);
        for (unsigned t = 0; t < tileCount; ++t) {
            const int ox = (int(t) % cols) * map.tileSize;
            const int oy = (int(t) / cols) * map.tileSize;
            for (int y = 0; y < map.tileSize; ++y)
                packedTiles.append(reinterpret_cast<const char *>(image.constScanLine(oy+y) + ox), map.tileSize);
        }
    }
    bool seenAnimated[256] = {};
    for (const SidboxTileAnimation &a : map.animations) {
        if (a.graphicId < 1 || a.graphicId > 255 || a.frames < 1 || a.frames > 16 ||
            a.frameTicks < 1 || a.frameTicks > 255 || seenAnimated[a.graphicId] ||
            a.graphicId + a.frames - 1 > int(tileCount)) {
            if (error) *error = QStringLiteral(
                "Animated tile %1 uses frames outside the available atlas (or has invalid settings).")
                .arg(a.graphicId);
            return false;
        }
        seenAnimated[a.graphicId] = true;
    }
    const QString folder = QDir(designDirectory).filePath(QStringLiteral("gamelevels"));
    if (!QDir().mkpath(folder)) {
        if (error) *error = QStringLiteral("Cannot create gamelevels directory.");
        return false;
    }
    QByteArray header =
        "#ifndef SIDBOX_GAME_LEVEL1_H\n#define SIDBOX_GAME_LEVEL1_H\n"
        "#include <stdint.h>\n#include \"../gamehelpers/gametilemap.h\"\n\n"
        "extern const uint8_t game_level1_graphics[];\n"
        "extern const uint8_t game_level1_collisions[];\n"
        "extern const uint8_t game_level1_atlas[];\n"
        "extern const game_tile_animation_t game_level1_animations[];\n"
        "extern const game_tilemap_t game_level1;\n"
        "#endif\n";
    QByteArray source = "#include \"level1.h\"\n\n";
    auto writeBytes = [&source](const QByteArray &data, const QByteArray &name) {
        source += "const uint8_t " + name + "[] __attribute__((aligned(32))) = {\n";
        for (int i = 0; i < data.size(); ++i) {
            if (i % 20 == 0) source += "    ";
            source += QByteArray::number(quint8(data.at(i)));
            if (i != data.size() - 1) source += ",";
            if (i % 20 == 19 || i == data.size() - 1) source += "\n";
            else source += " ";
        }
        source += "};\n\n";
    };
    writeBytes(map.graphics, "game_level1_graphics");
    writeBytes(map.collisions, "game_level1_collisions");
    writeBytes(packedTiles.isEmpty() ? QByteArray(1, char(0)) : packedTiles, "game_level1_atlas");
    source += "const game_tile_animation_t game_level1_animations[] = {\n";
    if (map.animations.isEmpty()) source += "    {0, 0, 0, 0} // No animations yet\n";
    else {
        for (const SidboxTileAnimation &a : map.animations) {
            const int flags = (a.loop ? 1 : 0) | (a.bounce ? 2 : 0);
            source += QByteArray("    {") + QByteArray::number(a.graphicId) + ", " +
                QByteArray::number(a.frames) + ", " + QByteArray::number(a.frameTicks) +
                ", " + QByteArray::number(flags) + "},\n";
        }
    }
    source += "};\n\n";
    source += "const game_tilemap_t game_level1 = {\n";
    source += "    game_level1_graphics, game_level1_collisions, game_level1_atlas,\n";
    source += QByteArray("    ") + QByteArray::number(map.width) + ", " + QByteArray::number(map.height)
        + ", " + QByteArray::number(map.tileSize) + ", " + QByteArray::number(tileCount) + ",\n"
        + (map.animations.isEmpty() ? QByteArray("    0, 0") :
            QByteArray("    game_level1_animations, ") + QByteArray::number(map.animations.size()))
        + "\n};\n\n";
    source +=
        "/*\n"
        " * ANIMATED TILES — BEGINNER INSTRUCTIONS\n"
        " *\n"
        " * Tile IDs still use one byte per cell. If tile 40 has four\n"
        " * frames, it displays atlas tiles 40, 41, 42, 43 in sequence.\n"
        " * Every tile painted with ID 40 shares the same animation.\n"
        " * Collision types never change when the tile animates.\n"
        " *\n"
        " * After setting up your game, call once: \n"
        " *   game_tilemap_animation_reset();\n"
        " * Once per VBlank, BEFORE drawing either front buffer: \n"
        " *   game_tilemap_animation_tick(1);\n"
        " * Then call game_tilemap_blit_view() as you already do.\n"
        " * Call animation_tick only ONCE per frame, not once per buffer.\n"
        " * Existing projects require the UPDATED gametilemap.c and .h\n"
        " * from the IDE codehelpers template for animation support.\n"
        " */\n\n";
    source +=
        "/*\n"
        " * BEGINNER EXAMPLE — DRAWING THE LEVEL (480x320 foreground)\n"
        " *\n"
        " * After your gfx_mode() / gameassets_init() setup:\n"
        " *   gameassets_show_background(); // Static backdrop\n"
        " *   game_tilemap_animation_reset();\n"
        " *   game_tile_player_start(&physics, &game_level1, &player);\n"
        " *\n"
        " * In your VBlank-synchronised game loop, ONCE per frame:\n"
        " *   game_tilemap_animation_tick(1);\n"
        " *   game_tile_player_run(&physics, getjoyport(), 1);\n"
        " *\n"
        " * For whichever foreground page is currently the drawing page:\n"
        " *   gfx_usebuffer(front[draw_index]);\n"
        " *   game_tilemap_blit_view(&game_level1, camera_x, camera_y, 480, 320);\n"
        " *   game_tile_player_screen(&physics, camera_x, camera_y);\n"
        " *   gfx_drawbob(&player);\n"
        " *   // Flip your foreground pages with your existing working code.\n"
        " *\n"
        " * Tick the animation once per VBlank, NOT once for each buffer!\n"
        " * An animation applies to all cells painted with that graphic ID.\n"
        " * The collision map and player physics remain unchanged.\n"
        " * FOREGROUND palette colour 0 must be transparent, so empty\n"
        " * map cells show the separate BACKGROUND image beneath them.\n"
        " */\n";
    const auto atomic = [error](const QString &path, const QByteArray &bytes) {
        QSaveFile f(path);
        if (!f.open(QIODevice::WriteOnly) || f.write(bytes) != bytes.size() || !f.commit()) {
            if (error) *error = QStringLiteral("Cannot write %1: %2").arg(path, f.errorString());
            return false;
        }
        return true;
    };
    return atomic(QDir(folder).filePath(QStringLiteral("level1.h")), header)
        && atomic(QDir(folder).filePath(QStringLiteral("level1.c")), source);
}
