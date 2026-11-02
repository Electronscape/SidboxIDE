#include "gameanimationeditor.h"
#include "gamehelpertemplates.h"
#include "gameplayerprofile.h"
#include "gameeditoricons.h"
#include "ppbcodec.h"

#include <QCoreApplication>
#include <QAbstractItemView>
#include <QButtonGroup>
#include <QDrag>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QMimeData>
#include <QRadioButton>
#include <QStyledItemDelegate>
#include <QStyleOptionViewItem>
#include <QCheckBox>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QDropEvent>
#include <QPen>
#include <QPair>
#include <QVector>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QColorDialog>
#include <QSettings>
#include <QStyle>
#include <QFileInfo>
#include <QFormLayout>
#include <QGridLayout>
#include <QIcon>
#include <QFont>
#include <QSizePolicy>
#include <QHBoxLayout>
#include <QImageReader>
#include <QInputDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QListWidget>
#include <QMessageBox>
#include <QPainter>
#include <QPushButton>
#include <QSaveFile>
#include <QRegularExpression>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QAbstractItemModel>
#include <QLineEdit>
#include <QPixmap>
#include <QScrollArea>
#include <QScrollBar>
#include <QWheelEvent>
#include <QtMath>
#include <QSignalBlocker>
#include <QSpinBox>
#include <QSplitter>
#include <QTimer>
#include <QVBoxLayout>
#include <QStyle>
#include <algorithm>

namespace {
QStringList directionsFor(int count)
{
    if (count == 8) return {"Up", "UpRight", "Right", "DownRight", "Down", "DownLeft", "Left", "UpLeft"};
    if (count == 4) return {"Up", "Right", "Down", "Left"};
    return {"Right", "Left"};
}

// The requested compact state glyphs are drawn locally — no extra PNGs,
// resources or runtime asset dependencies.
QIcon animationStateIcon(const QString &state, const IDETheme &theme)
{
    const QIcon custom = gameEditorExternalIcon(
        QStringLiteral("animation_state_%1.png").arg(state.toLower()));
    if (!custom.isNull()) return custom;
    QPixmap pix(20, 20);
    pix.fill(Qt::transparent);
    QPainter p(&pix);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setPen(QPen(theme.text, 2, Qt::SolidLine, Qt::RoundCap));
    p.setBrush(theme.text);
    p.drawEllipse(QRect(8, 2, 4, 4));
    const bool running = state.compare(QStringLiteral("Run"), Qt::CaseInsensitive) == 0;
    const bool jumping = state.compare(QStringLiteral("Jump"), Qt::CaseInsensitive) == 0;
    const bool walking = running || state.compare(QStringLiteral("Walk"), Qt::CaseInsensitive) == 0;
    const int lean = running ? 3 : walking ? 1 : 0;
    p.drawLine(10, 7, 10 + lean, 12);
    if (jumping) {
        p.drawLine(10, 8, 5, 4); p.drawLine(10, 8, 15, 4);
        p.drawLine(10 + lean, 12, 5, 16); p.drawLine(10 + lean, 12, 16, 15);
    } else if (walking) {
        p.drawLine(10, 8, 5, 11); p.drawLine(10, 8, 16, 9);
        p.drawLine(10 + lean, 12, 5, 17); p.drawLine(10 + lean, 12, 16, 15);
    } else {
        p.drawLine(10, 8, 6, 11); p.drawLine(10, 8, 14, 11);
        p.drawLine(10, 12, 7, 18); p.drawLine(10, 12, 13, 18);
    }
    return QIcon(pix);
}

// A real timeline drag: transfer the source/destination positions, not QListWidget's
// visual icon coordinates. The editor then updates frames AND frameMs together.
class AnimationTimelineList final : public QListWidget {
public:
    explicit AnimationTimelineList(QWidget *parent = nullptr) : QListWidget(parent) {}
    std::function<void(int, int)> reordered;
    QColor accent;

protected:
    int insertionAt(const QPoint &at) const
    {
        if (count() == 0) return 0;
        QListWidgetItem *target = itemAt(at);
        if (target) {
            const int r = row(target);
            return r + (at.x() > visualItemRect(target).center().x() ? 1 : 0);
        }
        // Empty margins before the first card and after the last card.
        return at.x() < visualItemRect(item(0)).left() ? 0 : count();
    }

    void paintEvent(QPaintEvent *event) override
    {
        QListWidget::paintEvent(event);
        if (m_dropInsertion < 0 || count() == 0) return;
        const QRect edge = m_dropInsertion >= count()
            ? visualItemRect(item(count() - 1))
            : visualItemRect(item(m_dropInsertion));
        const int x = m_dropInsertion >= count() ? edge.right() + 2 : edge.left() - 2;
        QPainter painter(viewport());
        painter.setPen(QPen(accent, 3));
        painter.drawLine(x, 8, x, viewport()->height() - 10);
    }

    void startDrag(Qt::DropActions) override
    {
        const int source = currentRow();
        if (source < 0 || source >= count()) return;
        auto *drag = new QDrag(this);
        auto *mime = new QMimeData;
        mime->setData("application/x-sidbox-animation-frame", QByteArray::number(source));
        drag->setMimeData(mime);
        const QPixmap pix = item(source)->icon().pixmap(QSize(64, 64));
        if (!pix.isNull()) {
            drag->setPixmap(pix);
            drag->setHotSpot(QPoint(pix.width() / 2, pix.height() / 2));
        }
        drag->exec(Qt::MoveAction);
        drag->deleteLater();
        m_dropInsertion = -1;
        viewport()->update();
    }

    void dragEnterEvent(QDragEnterEvent *event) override
    {
        if (event->source() == this &&
            event->mimeData()->hasFormat("application/x-sidbox-animation-frame")) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->ignore();
        }
    }

    void dragMoveEvent(QDragMoveEvent *event) override
    {
        if (event->source() == this &&
            event->mimeData()->hasFormat("application/x-sidbox-animation-frame")) {
            const int next = insertionAt(event->position().toPoint());
            if (m_dropInsertion != next) {
                m_dropInsertion = next;
                viewport()->update();
            }
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->ignore();
        }
    }

    void dragLeaveEvent(QDragLeaveEvent *event) override
    {
        m_dropInsertion = -1;
        viewport()->update();
        QListWidget::dragLeaveEvent(event);
    }

    void dropEvent(QDropEvent *event) override
    {
        if (event->source() != this ||
            !event->mimeData()->hasFormat("application/x-sidbox-animation-frame")) {
            event->ignore();
            return;
        }
        bool valid = false;
        const int source = event->mimeData()
                               ->data("application/x-sidbox-animation-frame")
                               .toInt(&valid);
        if (!valid || source < 0 || source >= count()) {
            event->ignore();
            return;
        }
        // Drop before/after a hovered card; dropping into free space appends.
        const int insertion = insertionAt(event->position().toPoint());
        m_dropInsertion = -1;
        viewport()->update();
        const int destination = qBound(0, insertion - (insertion > source ? 1 : 0), count() - 1);
        event->setDropAction(Qt::MoveAction);
        event->accept();
        if (source == destination || !reordered) return;

        // Do not replace the list while Qt is still processing the drop event.
        QTimer::singleShot(0, this, [this, source, destination] {
            if (reordered) reordered(source, destination);
        });
    }

private:
    int m_dropInsertion = -1;
};

// One square-cornered frame card: atlas index / sprite / per-frame duration.
// The data remains on ordinary QListWidgetItems for saving and drag handling.
class AnimationFrameCardDelegate final : public QStyledItemDelegate {
public:
    explicit AnimationFrameCardDelegate(const IDETheme &theme, QObject *parent = nullptr)
        : QStyledItemDelegate(parent), m_theme(theme) {}

    QSize sizeHint(const QStyleOptionViewItem &, const QModelIndex &) const override
    {
        return QSize(90, 136);
    }

    void paint(QPainter *p, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override
    {
        p->save();
        const QRect card = option.rect.adjusted(4, 4, -4, -4);
        const bool selected = option.state & QStyle::State_Selected;
        const bool hovered = option.state & QStyle::State_MouseOver;
        const QColor border = selected ? m_theme.accent
                                        : hovered ? m_theme.scrollHandleHover
                                                  : m_theme.border;
        p->fillRect(card, m_theme.panelBackground);
        p->fillRect(QRect(card.left() + 1, card.top() + 1,
                          card.width() - 2, 21), m_theme.alternateBackground);
        p->fillRect(QRect(card.left() + 1, card.bottom() - 22,
                          card.width() - 2, 21), m_theme.alternateBackground);
        p->setPen(QPen(border, selected ? 2 : 1));
        p->drawRect(card.adjusted(0, 0, -1, -1));
        p->setPen(m_theme.border);
        p->drawLine(card.left() + 1, card.top() + 23,
                    card.right() - 1, card.top() + 23);
        p->drawLine(card.left() + 1, card.bottom() - 23,
                    card.right() - 1, card.bottom() - 23);

        const int cell = index.data(Qt::UserRole).toInt();
        const int durationMs = qMax(1, index.data(Qt::UserRole + 1).toInt());
        const QIcon icon = qvariant_cast<QIcon>(index.data(Qt::DecorationRole));
        QFont font = option.font;
        font.setPixelSize(12);
        font.setBold(selected);
        p->setFont(font);
        p->setPen(m_theme.text);
        p->drawText(QRect(card.left() + 2, card.top() + 2,
                          card.width() - 4, 18), Qt::AlignCenter, QString::number(cell));
        const QRect imageArea(card.left() + 4, card.top() + 26,
                              card.width() - 8, card.height() - 52);
        const QPixmap pix = icon.pixmap(QSize(64, 64));
        if (!pix.isNull()) {
            const QPoint centre = imageArea.center();
            p->drawPixmap(centre.x() - pix.width() / 2,
                          centre.y() - pix.height() / 2, pix);
        }
        font.setBold(false);
        font.setPixelSize(11);
        p->setFont(font);
        p->setPen(m_theme.mutedText);
        p->drawText(QRect(card.left() + 2, card.bottom() - 22,
                          card.width() - 4, 21), Qt::AlignCenter,
                    QStringLiteral("%1ms").arg(durationMs));
        p->restore();
    }
private:
    IDETheme m_theme;
};

// Small diagram icons for 2/4/8-direction controls (no resource files needed).
QPixmap directionModeGlyph(int count, const IDETheme &theme)
{
    QPixmap result(20, 20);
    result.fill(Qt::transparent);
    QPainter p(&result);
    p.setPen(Qt::NoPen);
    const QColor active = theme.accent, inactive = theme.mutedText;
    const int n = count == 8 ? 3 : 2;
    const int cell = n == 3 ? 4 : 6, space = n == 3 ? 2 : 3;
    const int origin = (20 - (n * cell + (n - 1) * space)) / 2;
    for (int y = 0; y < n; ++y) {
        for (int x = 0; x < n; ++x) {
            bool on = count == 2 ? (x == y)
                       : count == 4 ? true
                       : !(x == 1 && y == 1);
            p.fillRect(origin + x * (cell + space), origin + y * (cell + space),
                       cell, cell, on ? active : inactive);
        }
    }
    return result;
}

// A lightweight clickable sheet with one native-zoomed 32x32 (or custom)
// grid. No pixmap interpolation or alpha blending is done by this widget.
class AnimationAtlasView final : public QWidget {
public:
    QImage image;
    QColor accent;
    QColor background;
    QColor atlasGrid;
    QColor cellNumberBackground;
    QColor cellNumberText;
    int cellW = 32, cellH = 32, zoom = 3, selected = -1;
    std::function<void(int, bool)> doubleClicked;
    explicit AnimationAtlasView(QWidget *parent = nullptr) : QWidget(parent) {
        setMouseTracking(true);
        setCursor(Qt::CrossCursor);
    }
    void resizeSheet() {
        if (image.isNull() || !cellW || !cellH) { setFixedSize(1, 1); update(); return; }
        setFixedSize((image.width() / cellW) * cellW * zoom,
                     (image.height() / cellH) * cellH * zoom);
        update();
    }
protected:
    void paintEvent(QPaintEvent *) override {
        QPainter p(this);
        p.fillRect(rect(), background);
        if (image.isNull() || cellW < 1 || cellH < 1) return;
        p.setRenderHint(QPainter::SmoothPixmapTransform, false);
        p.drawImage(QRect(0, 0, image.width() * zoom, image.height() * zoom), image);
        const int cols = image.width() / cellW;
        const int rows = image.height() / cellH;
        p.setPen(atlasGrid);
        for (int x = 0; x <= cols; ++x) p.drawLine(x * cellW * zoom, 0, x * cellW * zoom, rows * cellH * zoom);
        for (int y = 0; y <= rows; ++y) p.drawLine(0, y * cellH * zoom, cols * cellW * zoom, y * cellH * zoom);
        // Atlas indexes are visible at all zoom levels (row-major, zero based).
        QFont numberFont = p.font(); numberFont.setBold(true);
        numberFont.setPixelSize(qBound(9, 4 * zoom, 13));
        p.setFont(numberFont);
        for (int n = 0; n < cols * rows; ++n) {
            const QPoint topLeft((n % cols) * cellW * zoom, (n / cols) * cellH * zoom);
            const QString number = QString::number(n);
            const int width = p.fontMetrics().horizontalAdvance(number) + 8;
            const int height = p.fontMetrics().height() + 3;
            p.fillRect(QRect(topLeft.x() + 2, topLeft.y() + 2, width, height), cellNumberBackground);
            p.setPen(cellNumberText);
            p.drawText(topLeft + QPoint(6, 2 + p.fontMetrics().ascent()), number);
        }
        if (selected >= 0 && selected < cols * rows) {
            p.setPen(QPen(accent, 2));
            p.setBrush(Qt::NoBrush);
            p.drawRect(QRect((selected % cols) * cellW * zoom,
                             (selected / cols) * cellH * zoom,
                             cellW * zoom, cellH * zoom).adjusted(1, 1, -2, -2));
        }
    }
    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() != Qt::LeftButton || image.isNull()) return;
        const int col = int(event->position().x()) / (cellW * zoom);
        const int row = int(event->position().y()) / (cellH * zoom);
        const int cols = image.width() / cellW, rows = image.height() / cellH;
        if (col < 0 || col >= cols || row < 0 || row >= rows) return;
        const int frame = row * cols + col;
        selected = frame; update();
    }
    void mouseDoubleClickEvent(QMouseEvent *event) override {
        if (event->button() != Qt::LeftButton || image.isNull()) return;
        const int col = int(event->position().x()) / (cellW * zoom);
        const int row = int(event->position().y()) / (cellH * zoom);
        const int cols = image.width() / cellW, rows = image.height() / cellH;
        if (col < 0 || col >= cols || row < 0 || row >= rows) return;
        const int frame = row * cols + col;
        if (doubleClicked) doubleClicked(frame, event->modifiers() & Qt::ShiftModifier);
        selected = frame; update();
    }
};


// The atlas keeps its existing cell click/double-click behaviour, while a
// middle-button grab pans the scroll area and the wheel zooms around the
// pointer without jumping to the upper-left of the sheet.
class AnimationAtlasScrollArea final : public QScrollArea {
public:
    explicit AnimationAtlasScrollArea(QWidget *parent = nullptr) : QScrollArea(parent) {
        viewport()->installEventFilter(this);
        setFocusPolicy(Qt::StrongFocus);
        setToolTip(QObject::tr("Wheel or Ctrl+/-: zoom. Middle-drag: pan. Ctrl+1: 100%. "
            "Click a cell to select; double-click to add a frame."));
    }
    std::function<int()> currentZoom;
    std::function<void(int)> setZoom;
    void setAtlasWidget(QWidget *atlas) {
        setWidget(atlas);
        atlas->installEventFilter(this);
    }
protected:
    void keyPressEvent(QKeyEvent *event) override {
        if (currentZoom && setZoom && (event->modifiers() & Qt::ControlModifier) &&
            (event->key() == Qt::Key_Plus || event->key() == Qt::Key_Equal ||
             event->key() == Qt::Key_Minus || event->key() == Qt::Key_1)) {
            const int value = event->key() == Qt::Key_1 ? 1 :
                qBound(1, currentZoom() + (event->key() == Qt::Key_Minus ? -1 : 1), 16);
            setZoom(value);
            event->accept();
            return;
        }
        QScrollArea::keyPressEvent(event);
    }
    bool eventFilter(QObject *watched, QEvent *event) override {
        if (watched != viewport() && watched != widget())
            return QScrollArea::eventFilter(watched, event);
        QWidget *source = qobject_cast<QWidget *>(watched);
        if (event->type() == QEvent::Wheel) {
            auto *wheel = static_cast<QWheelEvent *>(event);
            if (!currentZoom || !setZoom) return false;
            const int steps = wheel->angleDelta().y() / 120;
            const int direction = steps ? steps :
                (wheel->angleDelta().y() > 0 || wheel->pixelDelta().y() > 0) ? 1 :
                (wheel->angleDelta().y() < 0 || wheel->pixelDelta().y() < 0) ? -1 : 0;
            if (!direction) return false;
            const int before = currentZoom();
            const int after = qBound(1, before + direction, 16);
            const QPoint at = viewport()->mapFromGlobal(source->mapToGlobal(wheel->position().toPoint()));
            const double imageX = double(horizontalScrollBar()->value() + at.x()) / before;
            const double imageY = double(verticalScrollBar()->value() + at.y()) / before;
            if (after != before) {
                setZoom(after); // Resizes the original atlas widget synchronously.
                horizontalScrollBar()->setValue(qRound(imageX * after) - at.x());
                verticalScrollBar()->setValue(qRound(imageY * after) - at.y());
            }
            wheel->accept();
            return true;
        }
        if (event->type() == QEvent::MouseButtonPress) {
            auto *mouse = static_cast<QMouseEvent *>(event);
            if (mouse->button() == Qt::MiddleButton) {
                m_dragging = true;
                setFocus(Qt::MouseFocusReason);
                m_lastGlobal = source->mapToGlobal(mouse->position().toPoint());
                viewport()->setCursor(Qt::ClosedHandCursor);
                if (widget()) widget()->setCursor(Qt::ClosedHandCursor);
                mouse->accept();
                return true;
            }
        }
        if (event->type() == QEvent::MouseMove && m_dragging) {
            auto *mouse = static_cast<QMouseEvent *>(event);
            const QPoint global = source->mapToGlobal(mouse->position().toPoint());
            const QPoint delta = global - m_lastGlobal;
            m_lastGlobal = global;
            horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta.x());
            verticalScrollBar()->setValue(verticalScrollBar()->value() - delta.y());
            mouse->accept();
            return true;
        }
        if (event->type() == QEvent::MouseButtonRelease) {
            auto *mouse = static_cast<QMouseEvent *>(event);
            if (mouse->button() == Qt::MiddleButton && m_dragging) {
                m_dragging = false;
                viewport()->unsetCursor();
                if (widget()) widget()->setCursor(Qt::CrossCursor);
                mouse->accept();
                return true;
            }
        }
        return QScrollArea::eventFilter(watched, event);
    }
private:
    bool m_dragging = false;
    QPoint m_lastGlobal;
};

// Live Preview uses its own scroll area so zoomed previews can be panned
// in every animation state without affecting atlas frame selection.
class AnimationPreviewScrollArea final : public QScrollArea {
public:
    explicit AnimationPreviewScrollArea(QWidget *parent = nullptr) : QScrollArea(parent) {
        viewport()->installEventFilter(this);
        setToolTip(QObject::tr("Drag with the left or middle mouse button to pan a zoomed preview."));
    }

    void setPreviewWidget(QWidget *preview) {
        setWidget(preview);
        preview->installEventFilter(this);
    }

protected:
    bool eventFilter(QObject *watched, QEvent *event) override {
        if (watched != viewport() && watched != widget())
            return QScrollArea::eventFilter(watched, event);

        if (event->type() == QEvent::MouseButtonPress) {
            auto *mouse = static_cast<QMouseEvent *>(event);
            if ((mouse->button() == Qt::LeftButton || mouse->button() == Qt::MiddleButton)
                && (horizontalScrollBar()->maximum() > 0 || verticalScrollBar()->maximum() > 0)) {
                m_dragging = true;
                m_dragButton = mouse->button();
                m_lastGlobal = mouse->globalPosition().toPoint();
                viewport()->setCursor(Qt::ClosedHandCursor);
                if (widget()) widget()->setCursor(Qt::ClosedHandCursor);
                mouse->accept();
                return true;
            }
        }
        if (event->type() == QEvent::MouseMove && m_dragging) {
            auto *mouse = static_cast<QMouseEvent *>(event);
            const QPoint global = mouse->globalPosition().toPoint();
            const QPoint delta = global - m_lastGlobal;
            m_lastGlobal = global;
            horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta.x());
            verticalScrollBar()->setValue(verticalScrollBar()->value() - delta.y());
            mouse->accept();
            return true;
        }
        if (event->type() == QEvent::MouseButtonRelease && m_dragging) {
            auto *mouse = static_cast<QMouseEvent *>(event);
            if (mouse->button() == m_dragButton) {
                m_dragging = false;
                m_dragButton = Qt::NoButton;
                viewport()->unsetCursor();
                if (widget()) widget()->unsetCursor();
                mouse->accept();
                return true;
            }
        }
        return QScrollArea::eventFilter(watched, event);
    }
private:
    bool m_dragging = false;
    Qt::MouseButton m_dragButton = Qt::NoButton;
    QPoint m_lastGlobal;
};

QIcon frameIcon(const QImage &atlas, int frame, int w, int h)
{
    const int cols = atlas.width() / w;
    if (!cols || frame < 0 || frame >= cols * (atlas.height() / h)) return {};
    const QImage sprite = atlas.copy((frame % cols) * w, (frame / cols) * h, w, h);
    return QIcon(QPixmap::fromImage(sprite.scaled(64, 64, Qt::KeepAspectRatio, Qt::FastTransformation)));
}
}

SidboxPlayerAnimationEditor::SidboxPlayerAnimationEditor(const QString &atlasFile,
        const QString &animationFile, const QString &defaultHeaderFile,
        int cellWidth, int cellHeight, QWidget *parent, const IDETheme &theme,
        const QJsonObject &playerProfile, int worldTileSize, const QString &worldName)
    : QDialog(parent), m_theme(theme), m_file(animationFile),
      m_defaultHeaderFile(defaultHeaderFile), m_atlasFile(atlasFile),
      m_cellW(cellWidth > 0 && cellWidth <= 256 ? cellWidth : 32),
      m_cellH(cellHeight > 0 && cellHeight <= 256 ? cellHeight : 32)
{
    m_previewPhysicsProfiles = GamePlayerProfile::physicsProfiles(playerProfile);
    m_startPhysicsId = GamePlayerProfile::physicsForWorld(playerProfile, worldName);
    m_previewWorldName = worldName;
    m_worldTileSize = qBound(1, worldTileSize, 256);
    if (QFileInfo(atlasFile).suffix().compare("ppb", Qt::CaseInsensitive) == 0) {
        SidboxPpb::Picture pic;
        if (SidboxPpb::read(atlasFile, &pic)) {
            // The actual image is untouched. Index 0 is transparent only in
            // this Qt preview; all other indices are fully opaque.
            QImage indexed = pic.indexed;
            QVector<QRgb> palette = indexed.colorTable();
            if (!palette.isEmpty()) {
                m_paletteZeroBackground = QColor::fromRgb(palette.at(0));
                m_hasPaletteZeroBackground = true;
            }
            for (int i = 0; i < palette.size(); ++i)
                palette[i] = i == 0 ? qRgba(0, 0, 0, 0)
                                  : qRgba(qRed(palette[i]), qGreen(palette[i]), qBlue(palette[i]), 255);
            indexed.setColorTable(palette);
            m_atlas = indexed.convertToFormat(QImage::Format_ARGB32);
        }
    } else {
        QImageReader reader(atlasFile);
        reader.setAutoTransform(true);
        QImage decoded = reader.read();
        if (decoded.format() == QImage::Format_Indexed8 && !decoded.colorTable().isEmpty()) {
            m_paletteZeroBackground = QColor::fromRgb(decoded.colorTable().at(0));
            m_hasPaletteZeroBackground = true;
        }
        m_atlas = decoded.convertToFormat(QImage::Format_ARGB32);
    }
    QSettings previewSettings(QStringLiteral("Sidbox"), QStringLiteral("SidboxIDE"));
    m_previewBackgroundMode = qBound(0, previewSettings.value(
        QStringLiteral("PlayerAnimation/previewBackgroundMode"), 0).toInt(), 2);
    m_customPreviewBackground = previewSettings.value(
        QStringLiteral("PlayerAnimation/previewBackgroundColour"),
        QColor(145, 150, 160)).value<QColor>();
    m_previewFloorEnabled = previewSettings.value(
        QStringLiteral("PlayerAnimation/walkingFloorEnabled"), true).toBool();
    m_gameScaleWalkingFloor = previewSettings.value(
        QStringLiteral("PlayerAnimation/walkingFloorGameScale"), true).toBool();
    if (!m_customPreviewBackground.isValid())
        m_customPreviewBackground = QColor(145, 150, 160);
    setWindowTitle(tr("Player Animation Editor — %1").arg(QFileInfo(atlasFile).fileName()));
    setMinimumSize(1080, 690);
    resize(1370, 860);
    QSettings animationWindowSettings(QStringLiteral("Sidbox"), QStringLiteral("SidboxIDE"));
    const QByteArray savedWindow = animationWindowSettings.value(
        QStringLiteral("PlayerAnimationEditor/geometry")).toByteArray();
    if (!savedWindow.isEmpty()) restoreGeometry(savedWindow);
    // Stage 4.14: global theme controls the entire dialog, including checks.
    // Only artwork/preview sections retain their own scoped styles below.
    m_states = {"Idle", "Walk", "Run", "Push", "Jump", "Fall", "Slide", "Balance", "Hurt", "Land"};
    if (!m_atlas.isNull()) readDocument();
    createUi();
    if (m_atlas.isNull()) {
        QMessageBox::warning(this, tr("Animation Atlas"), tr("Could not read sprite atlas:\n%1").arg(atlasFile));
    }
}

SidboxPlayerAnimationEditor::~SidboxPlayerAnimationEditor()
{
    QSettings settings(QStringLiteral("Sidbox"), QStringLiteral("SidboxIDE"));
    settings.setValue(QStringLiteral("PlayerAnimationEditor/geometry"), saveGeometry());
}

QString SidboxPlayerAnimationEditor::currentState() const
{
    // The visible state ID is for users; the saved/exported name stays unchanged.
    return m_stateList ? m_states.value(m_stateList->currentRow()) : QString();
}
QString SidboxPlayerAnimationEditor::currentDirection() const
{
    return m_directions ? m_directions->currentText() : QString();
}
QString SidboxPlayerAnimationEditor::clipKey(const QString &state, const QString &direction) const
{
    return state + QLatin1Char('|') + direction;
}
QString SidboxPlayerAnimationEditor::mirroredSourceDirection(const QString &dir) const
{
    if (!m_mirror) return {};
    if (dir == "Left") return "Right";
    if (dir == "UpLeft") return "UpRight";
    if (dir == "DownLeft") return "DownRight";
    return {};
}
const SidboxPlayerAnimationEditor::Clip *SidboxPlayerAnimationEditor::effectiveClip(bool *flipped) const
{
    if (flipped) *flipped = false;
    const auto it = m_clips.constFind(clipKey(currentState(), currentDirection()));
    if (it != m_clips.constEnd() && !it.value().frames.isEmpty()) return &it.value();
    const QString mirrorDirection = mirroredSourceDirection(currentDirection());
    if (!mirrorDirection.isEmpty()) {
        const auto src = m_clips.constFind(clipKey(currentState(), mirrorDirection));
        if (src != m_clips.constEnd() && !src.value().frames.isEmpty()) {
            if (flipped) *flipped = true;
            return &src.value();
        }
    }
    return nullptr;
}

void SidboxPlayerAnimationEditor::createUi()
{
    auto *outer = new QVBoxLayout(this);
    outer->setContentsMargins(7, 7, 7, 7);
    auto *headline = new QHBoxLayout;
    auto *title = new QLabel(tr("PLAYER ANIMATION TOOLKIT  |  SIDBOX V1"), this);
    QFont font = title->font(); font.setBold(true); title->setFont(font);
    headline->addWidget(title);
    headline->addStretch();
    outer->addLayout(headline);

    auto *split = new QSplitter(Qt::Horizontal, this);
    split->setChildrenCollapsible(false);
    outer->addWidget(split, 1);

    auto *left = new QWidget(split);
    auto *leftLayout = new QVBoxLayout(left);
    leftLayout->addWidget(new QLabel(tr("Animation States"), left));
    m_stateList = new QListWidget(left);
    // Match the Game Object Properties type selector: square bordered cards,
    // a stronger accent selection and contrasting text in light themes.
    // Scope this styling to the state list, leaving the atlas and timeline
    // selection visuals exactly as they were.
    m_stateList->setObjectName(QStringLiteral("GGAnimationStates"));
    m_stateList->setSpacing(0);
    m_stateList->setIconSize(QSize(20, 20));
    const QColor stateSelectionBg = m_theme.accent.darker(230);
    const QColor stateSelectionFg = stateSelectionBg.lightnessF() < 0.52
        ? QColor(Qt::white) : QColor(Qt::black);
    m_stateList->setStyleSheet(QStringLiteral(R"GGSTATE(
        QListWidget#GGAnimationStates { background:%1; color:%2; border:1px solid %3;
            border-radius:0px; outline:0px; }
        QListWidget#GGAnimationStates::item { padding:8px; border:1px solid %3;
            border-radius:0px; margin-bottom:2px; }
        QListWidget#GGAnimationStates::item:selected { background:%4; color:%5;
            border:1px solid %6; border-left:3px solid %6; }
        QListWidget#GGAnimationStates::item:hover { border-color:%6; }
    )GGSTATE")
        .arg(ideThemeColorName(m_theme.panelBackground), ideThemeColorName(m_theme.text),
             ideThemeColorName(m_theme.border), ideThemeColorName(stateSelectionBg),
             ideThemeColorName(stateSelectionFg), ideThemeColorName(m_theme.accent)));
    leftLayout->addWidget(m_stateList, 1);
    auto *stateButtons = new QHBoxLayout;
    auto *addState = new QPushButton(tr("+ State"), left);
    auto *removeState = new QPushButton(tr("- State"), left);
    stateButtons->addWidget(addState); stateButtons->addWidget(removeState);
    leftLayout->addLayout(stateButtons);
    // Screenshot-style direction mode selector directly below Animation States.
    auto *modeBox = new QWidget(left);
    modeBox->setStyleSheet(QStringLiteral(
        "QWidget { background:%1; border:1px solid %2; border-radius:0px; }"
        "QLabel, QRadioButton { border:0; background:transparent; }")
        .arg(ideThemeColorName(m_theme.panelBackground), ideThemeColorName(m_theme.border)));
    auto *modeLayout = new QVBoxLayout(modeBox);
    modeLayout->setContentsMargins(8, 8, 8, 8);
    modeLayout->setSpacing(5);
    auto *modeHeading = new QLabel(tr("Direction Mode"), modeBox);
    QFont modeFont = modeHeading->font(); modeFont.setBold(true);
    modeHeading->setFont(modeFont);
    modeLayout->addWidget(modeHeading);
    m_directionModeButtons = new QButtonGroup(modeBox);
    for (int n : {2, 4, 8}) {
        auto *line = new QHBoxLayout;
        auto *radio = new QRadioButton(tr("%1-Direction").arg(n), modeBox);
        radio->setChecked(m_mode == n);
        m_directionModeButtons->addButton(radio, n);
        line->addWidget(radio);
        line->addStretch();
        auto *symbol = new QLabel(modeBox);
        symbol->setPixmap(directionModeGlyph(n, m_theme));
        line->addWidget(symbol);
        modeLayout->addLayout(line);
    }
    leftLayout->addWidget(modeBox);
    m_directions = new QComboBox(left);
    m_directions->setToolTip(tr("Direction whose frames you are editing."));
    leftLayout->addWidget(m_directions);
    m_mirrorCheck = new QCheckBox(tr("Mirror left from right"), left);
    m_mirrorCheck->setChecked(m_mirror);
    m_mirrorCheck->setToolTip(tr("Left, up-left and down-left inherit right-facing frames unless explicitly assigned."));
    leftLayout->addWidget(m_mirrorCheck);
    m_autoCheck = new QCheckBox(tr("Export auto state chooser"), left);
    m_autoCheck->setChecked(m_autoState);
    m_autoCheck->setToolTip(tr("Optional C function for Idle/Walk/Run/Jump/Fall/Slide/Balance/Push/Hurt. Your game calls it with its player physics values."));
    leftLayout->addWidget(m_autoCheck);
    leftLayout->addWidget(new QLabel(tr("Double-click atlas cells to add frames.\n"
                                       "Shift+double-click adds a range.\n"
                                       "Drag frames to reorder them."), left));
    leftLayout->addStretch();

    auto *middle = new QWidget(split);
    auto *mid = new QVBoxLayout(middle);
    auto *atlasRow = new QHBoxLayout;
    m_atlasInfo = new QLabel(middle);
    atlasRow->addWidget(m_atlasInfo, 1);
    m_width = new QSpinBox(middle); m_height = new QSpinBox(middle);
    m_width->setRange(1, 256); m_height->setRange(1, 256);
    m_width->setValue(m_cellW); m_height->setValue(m_cellH);
    m_width->setToolTip(tr("Atlas cell width. SIDBOX BOB width must match."));
    m_height->setToolTip(tr("Atlas cell height. SIDBOX BOB height must match."));
    atlasRow->addWidget(new QLabel(tr("Cell W/H"), middle));
    atlasRow->addWidget(m_width); atlasRow->addWidget(m_height);
    m_zoom = new QSpinBox(middle); m_zoom->setRange(1, 16); m_zoom->setValue(3);
    m_zoom->setToolTip(tr("Nearest-neighbour display zoom only."));
    atlasRow->addWidget(new QLabel(tr("Zoom"), middle)); atlasRow->addWidget(m_zoom);
    mid->addLayout(atlasRow);
    auto *scroll = new AnimationAtlasScrollArea(middle);
    scroll->setWidgetResizable(false);
    scroll->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    scroll->currentZoom = [this]() { return m_zoom->value(); };
    scroll->setZoom = [this](int zoom) { m_zoom->setValue(zoom); };
    auto *atlas = new AnimationAtlasView(scroll);
    atlas->image = m_atlas;
    atlas->accent = m_theme.accent;
    atlas->background = m_theme.panelBackground;
    atlas->atlasGrid = m_theme.border;
    atlas->cellNumberBackground = m_theme.alternateBackground;
    atlas->cellNumberText = m_theme.text;
    m_atlasView = atlas;
    scroll->setAtlasWidget(atlas);
    mid->addWidget(scroll, 1);
    mid->addWidget(new QLabel(tr("Frame Timeline — drag to reorder; select for individual duration"), middle));
    m_timeline = new AnimationTimelineList(middle);
    m_timeline->setViewMode(QListView::IconMode);
    m_timeline->setFlow(QListView::LeftToRight);
    m_timeline->setWrapping(false);
    m_timeline->setIconSize(QSize(64, 64));
    m_timeline->setGridSize(QSize(92, 136));
    static_cast<AnimationTimelineList *>(m_timeline)->accent = m_theme.accent;
    m_timeline->setItemDelegate(new AnimationFrameCardDelegate(m_theme, m_timeline));
    // Keep icon-mode dragging enabled; our dropEvent owns the actual reorder.
    m_timeline->setMovement(QListView::Snap);
    m_timeline->setMouseTracking(true);
    m_timeline->setSelectionMode(QAbstractItemView::SingleSelection);
    m_timeline->setDragEnabled(true);
    m_timeline->setAcceptDrops(true);
    m_timeline->setDropIndicatorShown(true);
    m_timeline->setDragDropMode(QAbstractItemView::DragDrop);
    m_timeline->setDefaultDropAction(Qt::MoveAction);
    m_timeline->setFixedHeight(157);
    mid->addWidget(m_timeline);
    auto *timelineActions = new QHBoxLayout;
    auto *removeFrame = new QPushButton(tr("Remove frame"), middle);
    auto *moveLeft = new QPushButton(tr("Move ←"), middle);
    auto *moveRight = new QPushButton(tr("Move →"), middle);
    timelineActions->addWidget(removeFrame); timelineActions->addWidget(moveLeft);
    timelineActions->addWidget(moveRight); timelineActions->addStretch();
    // Give the frame timing controls their own row so the new bulk button
    // doesn't squash the timeline or force the splitter wider.
    auto *timingActions = new QHBoxLayout;
    m_defaultDuration = new QSpinBox(middle); m_defaultDuration->setRange(1, 5000); m_defaultDuration->setSingleStep(10); m_defaultDuration->setValue(100);
    m_defaultDuration->setSuffix(tr(" ms"));
    m_defaultDuration->setToolTip(tr("Default duration for newly inserted frames. Wheel: 10 ms; type any value from 1 to 5000 ms. SIDBOX displays at 50 Hz (20 ms per screen refresh)."));
    timingActions->addWidget(new QLabel(tr("New frame duration:"), middle));
    timingActions->addWidget(m_defaultDuration);
    m_setAllFrameDurations = new QPushButton(tr("Set all frames ms"), middle);
    m_setAllFrameDurations->setToolTip(tr("Set every frame of the selected animation state and direction "
        "to the New frame duration value. Other states and directions are unchanged."));
    m_setAllFrameDurations->setEnabled(false);
    timingActions->addWidget(m_setAllFrameDurations);
    m_frameDuration = new QSpinBox(middle);
    m_frameDuration->setRange(1, 5000);
    m_frameDuration->setSingleStep(10);
    m_frameDuration->setSuffix(tr(" ms"));
    m_frameDuration->setToolTip(tr("Selected frame duration in milliseconds. Wheel: 10 ms; type any value from 1 to 5000 ms. Runtime retains the remainder across 20 ms VBlanks."));
    m_frameDuration->setEnabled(false);
    timingActions->addWidget(new QLabel(tr("Selected frame:"), middle));
    timingActions->addWidget(m_frameDuration);
    m_loop = new QCheckBox(tr("Loop"), middle); m_loop->setChecked(true);
    timelineActions->addWidget(m_loop);
    mid->addLayout(timelineActions);
    timingActions->addStretch();
    mid->addLayout(timingActions);

    auto *right = new QWidget(split);
    auto *rightLayout = new QVBoxLayout(right);
    // Display magnification only: keep the 256x256 game-pixel canvas and
    // flat-floor physics unchanged, then nearest-neighbour scale its image.
    auto *previewZoomRow = new QHBoxLayout;
    previewZoomRow->addWidget(new QLabel(tr("Preview zoom"), right));
    m_previewZoom = new QSpinBox(right);
    m_previewZoom->setRange(1, 6);
    m_previewZoom->setSingleStep(1);
    m_previewZoom->setSuffix(QStringLiteral("×"));
    m_previewZoom->setToolTip(tr("Magnify the entire Live Preview in every animation state (1–6×). "
        "Drag the zoomed preview to pan; the display zoom does not change "
        "animation timing, physics or exported data."));
    QSettings zoomSettings(QStringLiteral("Sidbox"), QStringLiteral("SidboxIDE"));
    m_previewZoom->setValue(qBound(1, zoomSettings.value(
        QStringLiteral("PlayerAnimation/livePreviewZoom"), 1).toInt(), 6));
    m_previewZoom->setMaximumWidth(95);
    previewZoomRow->addWidget(m_previewZoom);
    previewZoomRow->addSpacing(12);
    previewZoomRow->addWidget(new QLabel(tr("Preview speed"), right));
    auto *previewSpeed = new QComboBox(right);
    for (const int percent : {10, 25, 50, 75, 100})
        previewSpeed->addItem(tr("%1%").arg(percent), percent);
    previewSpeed->setToolTip(tr("Slow down the live preview's animation AND walking floor together. "
        "100% is normal 50 Hz game speed. This does not change frame timings, "
        "physics profiles, saved animation data or the generated game."));
    const int savedPreviewSpeed = zoomSettings.value(
        QStringLiteral("PlayerAnimation/livePreviewSpeedPercent"), 100).toInt();
    const int speedIndex = previewSpeed->findData(savedPreviewSpeed);
    previewSpeed->setCurrentIndex(speedIndex < 0 ? previewSpeed->findData(100) : speedIndex);
    m_previewSpeedPercent = previewSpeed->currentData().toInt();
    previewSpeed->setMaximumWidth(88);
    previewZoomRow->addWidget(previewSpeed);
    connect(previewSpeed, qOverload<int>(&QComboBox::currentIndexChanged),
            this, [this, previewSpeed](int) {
        m_previewSpeedPercent = previewSpeed->currentData().toInt();
        m_previewSpeedAccumulator = 0;
        QSettings settings(QStringLiteral("Sidbox"), QStringLiteral("SidboxIDE"));
        settings.setValue(QStringLiteral("PlayerAnimation/livePreviewSpeedPercent"),
                          m_previewSpeedPercent);
    });
    previewZoomRow->addStretch(1);
    rightLayout->addLayout(previewZoomRow);
    auto *previewHeading = new QHBoxLayout;
    previewHeading->addWidget(new QLabel(tr("Live Preview"), right));
    previewHeading->addStretch(1);
    m_previewBackgroundChoice = new QComboBox(right);
    m_previewBackgroundChoice->addItem(tr("Palette 0"), 0);
    m_previewBackgroundChoice->addItem(tr("Theme"), 1);
    m_previewBackgroundChoice->addItem(tr("Custom"), 2);
    m_previewBackgroundChoice->setToolTip(tr("Preview background only. Does not change sprite art or exported data."));
    m_previewBackgroundChoice->setCurrentIndex(m_previewBackgroundMode);
    m_previewBackgroundChoice->setMaximumWidth(120);
    previewHeading->addWidget(m_previewBackgroundChoice);
    m_previewColourButton = new QPushButton(tr("Colour…"), right);
    m_previewColourButton->setToolTip(tr("Choose a solid preview background colour."));
    m_previewColourButton->setEnabled(m_previewBackgroundMode == 2);
    m_previewColourButton->setProperty("adventureGuard", true);
    m_previewColourButton->style()->unpolish(m_previewColourButton);
    m_previewColourButton->style()->polish(m_previewColourButton);
    m_previewColourButton->setToolTip(tr("Available only when Preview Background is set to Custom. Changes the preview, not exported sprite art."));
    previewHeading->addWidget(m_previewColourButton);
    rightLayout->addLayout(previewHeading);
    connect(m_previewBackgroundChoice, qOverload<int>(&QComboBox::currentIndexChanged),
            this, [this](int mode) {
        m_previewBackgroundMode = mode;
        m_previewColourButton->setEnabled(mode == 2);
        QSettings settings(QStringLiteral("Sidbox"), QStringLiteral("SidboxIDE"));
        settings.setValue(QStringLiteral("PlayerAnimation/previewBackgroundMode"), mode);
        refreshPreview();
    });
    connect(m_previewColourButton, &QPushButton::clicked, this, [this]() {
        const QColor colour = QColorDialog::getColor(m_customPreviewBackground, this,
            tr("Player Preview Background"), QColorDialog::DontUseNativeDialog);
        if (!colour.isValid()) return;
        m_customPreviewBackground = colour;
        QSettings settings(QStringLiteral("Sidbox"), QStringLiteral("SidboxIDE"));
        settings.setValue(QStringLiteral("PlayerAnimation/previewBackgroundColour"), colour);
        refreshPreview();
    });
    m_previewScroll = new AnimationPreviewScrollArea(right);
    m_previewScroll->setWidgetResizable(false);
    m_previewScroll->setAlignment(Qt::AlignCenter);
    m_previewScroll->setMinimumSize(210, 220);
    m_previewScroll->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_previewScroll->setStyleSheet(QStringLiteral("QScrollArea { background:%1; border:1px solid %2; border-radius:0px; }")
        .arg(ideThemeColorName(m_theme.panelBackground), ideThemeColorName(m_theme.border)));
    m_preview = new QLabel;
    m_preview->setAlignment(Qt::AlignCenter);
    m_preview->setFixedSize(256 * m_previewZoom->value(), 256 * m_previewZoom->value());
    m_preview->setStyleSheet(QStringLiteral("background:transparent; border:0px; border-radius:0px;"));
    static_cast<AnimationPreviewScrollArea *>(m_previewScroll)->setPreviewWidget(m_preview);
    rightLayout->addWidget(m_previewScroll, 1);
    // Focus the sprite at its foot-anchored position after Qt has laid out the
    // viewport. Re-focus ONLY when the view/state changes, never on animation
    // ticks, so deliberate left/middle-drag panning remains under user control.
    const auto centreLivePreview = [this]() {
        QTimer::singleShot(0, this, [this]() {
            if (!m_previewScroll || !m_previewZoom || !m_footY) return;
            const int editorScale = qMax(1, qMin(6,
                qMin(220 / qMax(1, m_cellW), 220 / qMax(1, m_cellH))));
            const int scale = m_gameScaleWalkingFloor ? 1 : editorScale;
            const int spriteTop = 211 - m_footY->value() * scale;
            const int spriteCentreY = spriteTop + m_cellH * scale / 2;
            const int zoom = m_previewZoom->value();
            auto *horizontal = m_previewScroll->horizontalScrollBar();
            auto *vertical = m_previewScroll->verticalScrollBar();
            horizontal->setValue(qBound(0,
                128 * zoom - m_previewScroll->viewport()->width() / 2,
                horizontal->maximum()));
            vertical->setValue(qBound(0,
                spriteCentreY * zoom - m_previewScroll->viewport()->height() / 2,
                vertical->maximum()));
        });
    };
    connect(m_previewZoom, qOverload<int>(&QSpinBox::valueChanged), this,
            [this, centreLivePreview](int zoom) {
        QSettings settings(QStringLiteral("Sidbox"), QStringLiteral("SidboxIDE"));
        settings.setValue(QStringLiteral("PlayerAnimation/livePreviewZoom"), zoom);
        refreshPreview();
        updateWalkingPreviewControls();
        centreLivePreview();
    });
    centreLivePreview(); // Initial saved zoom, after the window is shown.
    // Walking-on-floor preview: 50 Hz profile speed, world tile geometry, no
    // effect on the .sbanim, tilemap, physics profiles or exported game.
    auto *walkingControls = new QHBoxLayout;
    m_walkingFloor = new QCheckBox(tr("Moving floor"), right);
    m_walkingFloor->setChecked(m_previewFloorEnabled);
    m_walkingFloor->setToolTip(tr("Walk preview only. Scrolls a flat, segmented floor beneath the player at the selected physics profile's actual walking speed. Does not simulate slopes or collisions."));
    walkingControls->addWidget(m_walkingFloor);
    m_gameScaleCheck = new QCheckBox(tr("Game size (1×)"), right);
    m_gameScaleCheck->setChecked(m_gameScaleWalkingFloor);
    m_gameScaleCheck->setToolTip(tr("Use the same real 1:1 SIDBOX pixel size in ALL animation states. "
        "Untick for the larger editor-scale view in ALL states. "
        "Preview zoom then magnifies that same size, without changing physics or exported timing."));
    walkingControls->addWidget(m_gameScaleCheck);
    m_previewPhysics = new QComboBox(right);
    for (const QJsonValue &value : m_previewPhysicsProfiles) {
        const QJsonObject physics = value.toObject();
        m_previewPhysics->addItem(physics.value(QStringLiteral("name")).toString(),
                                  physics.value(QStringLiteral("id")).toInt());
    }
    const int startingIndex = m_previewPhysics->findData(m_startPhysicsId);
    m_previewPhysics->setCurrentIndex(startingIndex >= 0 ? startingIndex : 0);
    m_previewPhysics->setToolTip(tr("Select an existing player physics profile to compare walking speed. Does not change the game's selected physics profile."));
    walkingControls->addWidget(m_previewPhysics, 1);
    rightLayout->addLayout(walkingControls);
    m_floorInfo = new QLabel(right);
    m_floorInfo->setWordWrap(true);
    rightLayout->addWidget(m_floorInfo);
    connect(m_walkingFloor, &QCheckBox::toggled, this, [this, centreLivePreview](bool enabled) {
        m_previewFloorEnabled = enabled;
        QSettings settings(QStringLiteral("Sidbox"), QStringLiteral("SidboxIDE"));
        settings.setValue(QStringLiteral("PlayerAnimation/walkingFloorEnabled"), enabled);
        m_floorTravel100 = 0;
        m_iceVelocity100 = 0;
        m_iceRemainder100 = 0;
        updateWalkingPreviewControls();
        refreshPreview();
        centreLivePreview();
    });
    connect(m_gameScaleCheck, &QCheckBox::toggled, this, [this, centreLivePreview](bool enabled) {
        m_gameScaleWalkingFloor = enabled;
        QSettings settings(QStringLiteral("Sidbox"), QStringLiteral("SidboxIDE"));
        settings.setValue(QStringLiteral("PlayerAnimation/walkingFloorGameScale"), enabled);
        updateWalkingPreviewControls();
        refreshPreview();
        centreLivePreview();
    });
    connect(m_previewPhysics, qOverload<int>(&QComboBox::currentIndexChanged),
            this, [this](int) {
        m_floorTravel100 = 0;
        m_iceVelocity100 = 0;
        m_iceRemainder100 = 0;
        updateWalkingPreviewControls();
        refreshPreview();
    });
    m_play = new QPushButton(tr("Pause preview"), right);
    rightLayout->addWidget(m_play);
    rightLayout->addWidget(new QLabel(tr("Animation Properties"), right));
    auto *props = new QFormLayout;
    auto *foot = new QWidget(right);
    auto *footRow = new QHBoxLayout(foot); footRow->setContentsMargins(0, 0, 0, 0);
    m_footX = new QSpinBox(foot); m_footY = new QSpinBox(foot);
    footRow->addWidget(m_footX); footRow->addWidget(m_footY);
    props->addRow(tr("Foot X / Y"), foot);
    auto *hitbox = new QWidget(right);
    auto *boxRow = new QHBoxLayout(hitbox); boxRow->setContentsMargins(0, 0, 0, 0);
    m_boxX = new QSpinBox(hitbox); m_boxY = new QSpinBox(hitbox);
    m_boxW = new QSpinBox(hitbox); m_boxH = new QSpinBox(hitbox);
    for (auto *spin : {m_footX, m_footY, m_boxX, m_boxY, m_boxW, m_boxH}) spin->setRange(0, 256);
    for (auto *spin : {m_boxX, m_boxY, m_boxW, m_boxH}) { spin->setMaximumWidth(60); boxRow->addWidget(spin); }
    m_footX->setValue(m_savedFootX < 0 ? m_cellW / 2 : m_savedFootX);
    m_footY->setValue(m_savedFootY < 0 ? m_cellH - 1 : m_savedFootY);
    m_boxX->setValue(m_savedBoxX); m_boxY->setValue(m_savedBoxY);
    m_boxW->setValue(m_savedBoxW < 0 ? m_cellW : m_savedBoxW);
    m_boxH->setValue(m_savedBoxH < 0 ? m_cellH : m_savedBoxH);
    props->addRow(tr("Hitbox X/Y/W/H"), hitbox);
    m_showFoot = new QCheckBox(tr("Show foot anchor"), right); m_showFoot->setChecked(m_savedShowFoot);
    m_showBox = new QCheckBox(tr("Show collision box"), right); m_showBox->setChecked(m_savedShowBox);
    props->addRow(m_showFoot); props->addRow(m_showBox);
    rightLayout->addLayout(props);
    rightLayout->addWidget(new QLabel(tr("The hitbox controls V1 player physics when\nanimations are enabled. Foot X/Y locates the\nplayer anchor used by dropped items. BOB pixels\nand map collision remain unchanged."), right));
    split->setSizes({185, 640, 270});

    m_status = new QLabel(this);
    outer->addWidget(m_status);
    auto *bottom = new QHBoxLayout;
    auto *exportC = new QPushButton(tr("Export V1 C Header..."), this);
    exportC->setToolTip(tr("Generate a self-contained C animation player for this atlas (indexed frames + BOB flip)."));
    bottom->addWidget(exportC); bottom->addStretch();
    auto *cancel = new QPushButton(tr("Cancel"), this);
    auto *save = new QPushButton(tr("Save Animations"), this);
    bottom->addWidget(cancel); bottom->addWidget(save);
    outer->addLayout(bottom);

    rebuildStateList(); rebuildDirections(); updateAtlas(); refreshAll();
    connect(m_stateList, &QListWidget::currentRowChanged, this,
            [this, centreLivePreview] { refreshAll(); centreLivePreview(); });
    connect(m_directions, &QComboBox::currentIndexChanged, this,
            [this, centreLivePreview] { refreshAll(); centreLivePreview(); });
    connect(m_directionModeButtons, &QButtonGroup::idClicked, this,
            [this, centreLivePreview](int mode) {
        m_mode = mode;
        rebuildDirections(); refreshAll(); centreLivePreview();
    });
    connect(m_mirrorCheck, &QCheckBox::toggled, this, [this](bool v) { m_mirror = v; refreshAll(); });
    connect(m_autoCheck, &QCheckBox::toggled, this, [this](bool v) { m_autoState = v; });
    connect(addState, &QPushButton::clicked, this, [this] {
        bool ok = false;
        const QString s = QInputDialog::getText(this, tr("New Animation State"),
                    tr("State name:"), QLineEdit::Normal, QString(), &ok).trimmed();
        if (!ok || s.isEmpty()) return;
        if (s.contains('|') || m_states.contains(s, Qt::CaseInsensitive)) {
            QMessageBox::warning(this, tr("State Name"), tr("State already exists or contains '|'.")); return;
        }
        if (m_states.size() >= 255) {
            QMessageBox::warning(this, tr("Animation States"), tr("SIDBOX uses 8-bit state numbers (maximum 255 states)."));
            return;
        }
        m_states.append(s); rebuildStateList(m_states.size() - 1); refreshAll();
    });
    connect(removeState, &QPushButton::clicked, this, [this] {
        const QString s = currentState(); if (s.isEmpty()) return;
        if (m_states.size() == 1) return;
        if (QMessageBox::question(this, tr("Remove State"), tr("Remove '%1' and its frames?").arg(s)) != QMessageBox::Yes) return;
        for (auto it = m_clips.begin(); it != m_clips.end();) {
            if (it.key().startsWith(s + QLatin1Char('|'))) it = m_clips.erase(it);
            else ++it;
        }
        const int pos = m_states.indexOf(s); m_states.removeAt(pos);
        rebuildStateList(qMin(pos, m_states.size() - 1)); refreshAll();
    });
    connect(m_width, &QSpinBox::valueChanged, this,
            [this, centreLivePreview](int v) {
        m_cellW = v; updateAtlas(); refreshAll(); centreLivePreview();
    });
    connect(m_height, &QSpinBox::valueChanged, this,
            [this, centreLivePreview](int v) {
        m_cellH = v; updateAtlas(); refreshAll(); centreLivePreview();
    });
    connect(m_zoom, &QSpinBox::valueChanged, this, [this](int) { updateAtlas(); });
    atlas->doubleClicked = [this](int index, bool range) { appendFrame(index, range); };
    static_cast<AnimationTimelineList *>(m_timeline)->reordered = [this](int from, int to) {
        if (m_refreshing) return;
        const QString key = clipKey(currentState(), currentDirection());
        auto it = m_clips.find(key);
        if (it == m_clips.end() || it->frames.isEmpty()) {
            refreshTimeline();
            return;
        }
        if (from < 0 || to < 0 || from >= it->frames.size() || to >= it->frames.size())
            return;
        // Move the *pair* — duplicate atlas cells can each have unique pauses.
        while (it->frameMs.size() < it->frames.size())
            it->frameMs.append(it->durationMs);
        const int frame = it->frames.takeAt(from);
        const int durationMs = it->frameMs.takeAt(from);
        it->frames.insert(to, frame);
        it->frameMs.insert(to, durationMs);
        m_previewPosition = to;
        m_previewElapsed = 0;
        refreshTimeline();
        m_timeline->setCurrentRow(to);
        refreshPreview();
    };
    connect(removeFrame, &QPushButton::clicked, this, [this] { this->removeFrame(); });
    connect(m_setAllFrameDurations, &QPushButton::clicked, this, [this] {
        // Work on the explicitly authored state/direction, never on a
        // mirrored/inherited clip or every animation in the document.
        const QString key = clipKey(currentState(), currentDirection());
        auto it = m_clips.find(key);
        if (it == m_clips.end() || it->frames.isEmpty()) return;
        const int milliseconds = m_defaultDuration->value();
        it->durationMs = milliseconds;
        it->frameMs.fill(milliseconds, it->frames.size());
        m_previewElapsed = 0;
        refreshTimeline();
        refreshPreview();
    });
    connect(moveLeft, &QPushButton::clicked, this, [this] { moveFrame(-1); });
    connect(moveRight, &QPushButton::clicked, this, [this] { moveFrame(1); });
    connect(m_timeline, &QListWidget::currentRowChanged, this, [this](int row) {
        if (m_refreshing) return;
        m_previewPosition = qMax(0, row); m_previewElapsed = 0;
        updateSelectedFrameDuration(); refreshPreview();
    });
    connect(m_frameDuration, &QSpinBox::valueChanged, this, [this](int) { saveSelectedFrameDuration(); });
    connect(m_defaultDuration, &QSpinBox::valueChanged, this, [this](int) { saveClipSettings(); });
    connect(m_loop, &QCheckBox::toggled, this, [this] { saveClipSettings(); });
    for (auto *spin : {m_footX, m_footY, m_boxX, m_boxY, m_boxW, m_boxH})
        connect(spin, &QSpinBox::valueChanged, this, [this] { refreshPreview(); });
    connect(m_showFoot, &QCheckBox::toggled, this, [this] { refreshPreview(); });
    connect(m_showBox, &QCheckBox::toggled, this, [this] { refreshPreview(); });
    connect(m_play, &QPushButton::clicked, this, [this] {
        m_playing = !m_playing;
        m_play->setText(m_playing ? tr("Pause preview") : tr("Play preview"));
    });
    connect(cancel, &QPushButton::clicked, this, &QDialog::reject);
    connect(save, &QPushButton::clicked, this, [this] {
        if (writeDocument() && offerHeaderUpdate()) accept();
    });
    connect(exportC, &QPushButton::clicked, this, [this] { exportHeader(); });
    updateWalkingPreviewControls();
    m_timer = new QTimer(this);
    m_timer->setTimerType(Qt::PreciseTimer); // Reduce preview timing jitter at 50 Hz.
    m_timer->setInterval(20);
    connect(m_timer, &QTimer::timeout, this, [this] {
        if (!m_playing) return;
        // Run the original 50 Hz preview simulation less frequently at slower
        // speeds. The animation AND floor advance in the same virtual tick;
        // no exported frame duration or physics value is modified.
        m_previewSpeedAccumulator += m_previewSpeedPercent;
        if (m_previewSpeedAccumulator < 100) return;
        m_previewSpeedAccumulator -= 100;
        const Clip *c = effectiveClip();
        if (!c || c->frames.isEmpty()) return;
        const int pos = qBound(0, m_previewPosition, c->frames.size() - 1);
        // A non-looping animation holds its final frame, but player physics
        // does not stop at that frame. Keep scrolling the preview floor.
        const bool showFloor = m_walkingFloor && m_walkingFloor->isChecked()
            && currentState().compare(QStringLiteral("Walk"), Qt::CaseInsensitive) == 0;
        if (showFloor && m_previewPhysics && m_previewPhysics->currentIndex() >= 0) {
            const int physicsIndex = m_previewPhysics->currentIndex();
            const QJsonObject physics = m_previewPhysicsProfiles.at(physicsIndex).toObject();
            const int walkSpeed = qBound(0, physics.value(QStringLiteral("walkSpeed")).toInt(), 16);
            int travelledPixels = walkSpeed;
            if (physics.value(QStringLiteral("mode")).toInt() == 1) {
                // Match GAME_PHYSICS_ICE's 0.35 px/tick acceleration, cap and
                // integer-pixel remainder used by game_tile_player_update().
                m_iceVelocity100 = qMin(walkSpeed * 100, m_iceVelocity100 + 35);
                const int step100 = m_iceRemainder100 + m_iceVelocity100;
                travelledPixels = step100 / 100;
                m_iceRemainder100 = step100 % 100;
            } else {
                m_iceVelocity100 = 0;
                m_iceRemainder100 = 0;
            }
            // Two tiles prevent checkerboard parity from jumping at a wrap.
            const int period100 = qMax(1, m_worldTileSize * 200);
            m_floorTravel100 = (m_floorTravel100 + travelledPixels * 100) % period100;
        }
        bool changed = false;
        if (c->loop || pos + 1 < c->frames.size()) {
            int remaining = m_previewElapsed + 20; // Same 50 Hz timebase as exported runtime.
            int durationMs = pos < c->frameMs.size() ? c->frameMs.at(pos) : c->durationMs;
            while (remaining >= qMax(1, durationMs)) {
                remaining -= qMax(1, durationMs);
                if (m_previewPosition + 1 < c->frames.size()) ++m_previewPosition;
                else if (c->loop) m_previewPosition = 0;
                else { remaining = 0; changed = true; break; }
                changed = true;
                durationMs = m_previewPosition < c->frameMs.size()
                    ? c->frameMs.at(m_previewPosition) : c->durationMs;
            }
            m_previewElapsed = remaining;
        }
        if (changed || showFloor) refreshPreview();
    });
    m_timer->start();
}

void SidboxPlayerAnimationEditor::rebuildStateList(int selected)
{
    QSignalBlocker guard(m_stateList);
    m_stateList->clear();
    for (int id = 0; id < m_states.size(); ++id) {
        const QString &state = m_states.at(id);
        // IDs are ordinal and may change when an earlier state is removed.
        // Show the exact number emitted into player_anim.h without altering
        // the true state name used by .sbanim, clips, or C header generation.
        auto *item = new QListWidgetItem(animationStateIcon(state, m_theme),
            QStringLiteral("%1   %2").arg(id).arg(state));
        item->setToolTip(tr("Runtime animation state ID: %1\n"
            "IDs follow the order shown here and may change if states are removed.").arg(id));
        item->setSizeHint(QSize(170, 43)); // Same bordered row height as object types.
        m_stateList->addItem(item);
    }
    if (!m_states.isEmpty()) m_stateList->setCurrentRow(qBound(0, selected, m_states.size() - 1));
}
void SidboxPlayerAnimationEditor::rebuildDirections(const QString &keep)
{
    const QString previous = keep.isEmpty() ? currentDirection() : keep;
    QSignalBlocker guard(m_directions);
    m_directions->clear(); m_directions->addItems(directionsFor(m_mode));
    const int index = m_directions->findText(previous);
    m_directions->setCurrentIndex(index < 0 ? 0 : index);
}
void SidboxPlayerAnimationEditor::updateAtlas()
{
    auto *view = static_cast<AnimationAtlasView *>(m_atlasView);
    if (!view) return;
    const bool gridOK = !m_atlas.isNull() && m_cellW > 0 && m_cellH > 0 &&
                        m_atlas.width() % m_cellW == 0 && m_atlas.height() % m_cellH == 0;
    const int count = gridOK ? (m_atlas.width() / m_cellW) * (m_atlas.height() / m_cellH) : 0;
    view->image = gridOK && count <= 256 ? m_atlas : QImage();
    view->cellW = m_cellW; view->cellH = m_cellH; view->zoom = m_zoom->value();
    view->selected = m_selectedAtlasFrame;
    view->resizeSheet();
    m_atlasInfo->setText(tr("%1  |  %2×%3  |  %4 cells%5")
                         .arg(QFileInfo(m_atlasFile).fileName())
                         .arg(m_atlas.width()).arg(m_atlas.height()).arg(count)
                         .arg(gridOK && count <= 256 ? QString() : tr("  [INVALID GRID / >256]")));
}
void SidboxPlayerAnimationEditor::refreshAll()
{
    m_previewPosition = 0; m_previewElapsed = 0;
    m_floorTravel100 = 0;
    m_iceVelocity100 = 0;
    m_iceRemainder100 = 0;
    refreshTimeline(); updateWalkingPreviewControls(); refreshPreview();
}
void SidboxPlayerAnimationEditor::refreshTimeline()
{
    const int previous = m_timeline->currentRow();
    m_refreshing = true;
    QSignalBlocker guard(m_timeline);
    m_timeline->clear();
    const Clip *clip = effectiveClip();
    if (m_setAllFrameDurations) {
        const auto local = m_clips.constFind(clipKey(currentState(), currentDirection()));
        m_setAllFrameDurations->setEnabled(local != m_clips.constEnd() && !local->frames.isEmpty());
    }
    if (clip) {
        for (int i = 0; i < clip->frames.size(); ++i) {
            const int frame = clip->frames.at(i);
            const int durationMs = i < clip->frameMs.size() ? clip->frameMs.at(i) : clip->durationMs;
            auto *item = new QListWidgetItem(frameIcon(m_atlas, frame, m_cellW, m_cellH),
                tr("%1\n%2 ms").arg(frame).arg(durationMs));
            item->setData(Qt::UserRole, frame);
            item->setData(Qt::UserRole + 1, durationMs);
            item->setToolTip(tr("Atlas cell %1 — %2 ms; drag to reorder")
                                 .arg(frame).arg(durationMs));
            item->setTextAlignment(Qt::AlignCenter);
            m_timeline->addItem(item);
        }
    }
    if (m_timeline->count())
        m_timeline->setCurrentRow(qBound(0, previous, m_timeline->count() - 1));
    {
        QSignalBlocker durationBlock(m_defaultDuration), loop(m_loop);
        m_defaultDuration->setValue(clip ? clip->durationMs : 100);
        m_loop->setChecked(clip ? clip->loop : true);
    }
    m_refreshing = false;
    updateSelectedFrameDuration();
    bool flipped = false; effectiveClip(&flipped);
    const int cols = m_cellW ? m_atlas.width() / m_cellW : 0;
    const int rows = m_cellH ? m_atlas.height() / m_cellH : 0;
    m_status->setText(tr("%1 / %2  |  %3 frames%4  |  %5 atlas cells  |  millisecond timings (50 Hz runtime)")
        .arg(currentState(), currentDirection()).arg(clip ? clip->frames.size() : 0)
        .arg(flipped ? tr("  [mirrored from right]") : QString())
        .arg(cols * rows));
}
void SidboxPlayerAnimationEditor::updateSelectedFrameDuration()
{
    if (!m_frameDuration) return;
    QSignalBlocker block(m_frameDuration);
    const Clip *clip = effectiveClip();
    const int row = m_timeline->currentRow();
    const bool valid = clip && row >= 0 && row < clip->frames.size();
    const bool local = !currentState().isEmpty() && !currentDirection().isEmpty()
        && m_clips.contains(clipKey(currentState(), currentDirection()))
        && !m_clips.value(clipKey(currentState(), currentDirection())).frames.isEmpty();
    m_frameDuration->setEnabled(valid && local);
    m_frameDuration->setValue(valid ? (row < clip->frameMs.size()
                              ? clip->frameMs.at(row) : clip->durationMs) : m_defaultDuration->value());
}
void SidboxPlayerAnimationEditor::saveSelectedFrameDuration()
{
    if (m_refreshing) return;
    const QString key = clipKey(currentState(), currentDirection());
    const int row = m_timeline->currentRow();
    auto it = m_clips.find(key);
    if (it == m_clips.end() || row < 0 || row >= it->frames.size()) return;
    while (it->frameMs.size() < it->frames.size()) it->frameMs.append(it->durationMs);
    it->frameMs[row] = m_frameDuration->value();
    if (auto *item = m_timeline->item(row)) {
        item->setData(Qt::UserRole + 1, it->frameMs[row]);
        item->setText(tr("%1\n%2 ms").arg(it->frames[row]).arg(it->frameMs[row]));
        item->setToolTip(tr("Atlas cell %1 — %2 ms; drag to reorder")
                             .arg(it->frames[row]).arg(it->frameMs[row]));
    }
    m_previewElapsed = 0;
}
void SidboxPlayerAnimationEditor::updateWalkingPreviewControls()
{
    if (!m_walkingFloor || !m_previewPhysics || !m_floorInfo) return;
    const bool walking = currentState().compare(QStringLiteral("Walk"), Qt::CaseInsensitive) == 0;
    m_walkingFloor->setEnabled(walking);
    m_previewPhysics->setEnabled(walking && m_walkingFloor->isChecked());
    // Game size controls the common sprite scale for EVERY animation state.
    // Disabling it outside Walk silently made Idle/Run three times bigger
    // than Walk at the same Preview zoom, so leave it available globally.
    if (m_gameScaleCheck)
        m_gameScaleCheck->setEnabled(true);
    const int index = m_previewPhysics->currentIndex();
    if (index < 0 || index >= m_previewPhysicsProfiles.size()) {
        m_floorInfo->setText(tr("No player physics profiles available."));
        return;
    }
    const QJsonObject physics = m_previewPhysicsProfiles.at(index).toObject();
    const int speed = physics.value(QStringLiteral("walkSpeed")).toInt();
    const bool ice = physics.value(QStringLiteral("mode")).toInt() == 1;
    const QString world = m_previewWorldName.isEmpty() ? tr("current world") : m_previewWorldName;
    const int editorZoom = qMax(1, qMin(6, qMin(220 / qMax(1, m_cellW),
                                                 220 / qMax(1, m_cellH))));
    const int pixelScale = m_gameScaleWalkingFloor ? 1 : editorZoom;
    const int zoom = m_previewZoom ? m_previewZoom->value() : 1;
    m_floorInfo->setText(tr("%1: %2×%2 tiles  |  %3: %4 world px/50 Hz tick%5  |  "
        "%6× game render, %7× display zoom: %8 visible px/tick")
        .arg(world).arg(m_worldTileSize)
        .arg(physics.value(QStringLiteral("name")).toString())
        .arg(speed).arg(ice ? tr(" (Ice acceleration)") : QString())
        .arg(pixelScale).arg(zoom).arg(speed * pixelScale * zoom));
}
void SidboxPlayerAnimationEditor::refreshPreview()
{
    const Clip *clip = effectiveClip();
    QImage preview(256, 256, QImage::Format_ARGB32);
    const QColor background = m_previewBackgroundMode == 2 ? m_customPreviewBackground
        : (m_previewBackgroundMode == 0 && m_hasPaletteZeroBackground
           ? m_paletteZeroBackground : m_theme.alternateBackground);
    preview.fill(background);
    QPainter painter(&preview);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, false);
    const int editorZoom = qMax(1, qMin(6, qMin(220 / qMax(1, m_cellW), 220 / qMax(1, m_cellH))));
    const bool showFloor = m_walkingFloor && m_walkingFloor->isChecked()
        && currentState().compare(QStringLiteral("Walk"), Qt::CaseInsensitive) == 0;
    // One shared game/editor scale for ALL states. Previously only Walk
    // honoured Game size (1×), while Idle/Run applied the extra editorZoom
    // beneath the global Preview zoom (e.g. Walk 2× vs Idle 6×).
    // The moving floor uses this same scale for tiles and movement; the
    // separate Preview zoom below magnifies the final 256×256 image only.
    const int scale = m_gameScaleWalkingFloor ? 1 : editorZoom;
    const int floorY = 211;
    const int x = (256 - m_cellW * scale) / 2;
    // Anchor every state to the same ground plane. Centring non-Walk art
    // ignored Foot Y and left the character hovering above its grid.
    const int y = floorY - m_footY->value() * scale;
    if (showFloor) {
        // Flat floor with one visual tile for each real world tile, rendered
        // at the SAME nearest-neighbour sprite zoom. Geometry is visual only.
        const int tilePixels = qMax(1, m_worldTileSize * scale);
        const int period = tilePixels * 2;
        const int travel = (m_floorTravel100 / 100) * scale;
        const bool left = currentDirection().contains(QStringLiteral("Left"));
        const int offset = ((left ? -travel : travel) % period + period) % period;
        const int firstX = -(offset % tilePixels);
        const int firstColumn = offset / tilePixels;
        const QColor floorBase = background.lightnessF() < 0.5
            ? background.lighter(135) : background.darker(123);
        const QColor alternate = floorBase.lightnessF() < 0.5
            ? floorBase.lighter(113) : floorBase.darker(108);
        painter.fillRect(QRect(0, floorY, 256, 256 - floorY), floorBase);
        for (int column = 0, tileX = firstX; tileX < 256;
             ++column, tileX += tilePixels) {
            if ((column + firstColumn) & 1)
                painter.fillRect(QRect(tileX, floorY, tilePixels, 256 - floorY), alternate);
        }
        QColor seam = floorBase.lightnessF() < 0.5
            ? floorBase.lighter(150) : floorBase.darker(145);
        painter.setPen(QPen(seam, 1));
        for (int tileX = firstX; tileX < 256; tileX += tilePixels)
            painter.drawLine(tileX, floorY, tileX, 255);
        for (int tileY = floorY; tileY < 256; tileY += tilePixels)
            painter.drawLine(0, tileY, 255, tileY);
        painter.setPen(QPen(seam.lighter(125), 2));
        painter.drawLine(0, floorY, 255, floorY);
    } else {
        QColor grid = background.lightnessF() < 0.5
            ? background.lighter(160) : background.darker(140);
        grid.setAlpha(125);
        painter.setPen(QPen(grid, 1));
        const QPoint horizon(128, 164);
        for (int gx = -128; gx <= 384; gx += 48)
            painter.drawLine(horizon, QPoint(gx, 255));
        for (int gy : {177, 190, floorY, 229, 251})
            painter.drawLine(0, gy, 255, gy);
    }
    if (clip && !clip->frames.isEmpty()) {
        const int cols = m_cellW ? m_atlas.width() / m_cellW : 0;
        const int frame = clip->frames[qBound(0, m_previewPosition, clip->frames.size() - 1)];
        if (cols && frame >= 0 && frame < cols * (m_atlas.height() / m_cellH)) {
            QImage image = m_atlas.copy((frame % cols) * m_cellW,
                                         (frame / cols) * m_cellH, m_cellW, m_cellH);
            bool flip = false; effectiveClip(&flip);
            if (flip) image = image.flipped(Qt::Horizontal);
            painter.drawImage(QRect(x, y, m_cellW * scale, m_cellH * scale), image);
        }
    }
    if (m_showBox->isChecked()) {
        painter.setPen(QPen(m_theme.accent, 1));
        painter.drawRect(x + m_boxX->value() * scale, y + m_boxY->value() * scale,
                         m_boxW->value() * scale, m_boxH->value() * scale);
    }
    if (m_showFoot->isChecked()) {
        painter.setPen(QPen(m_theme.brightText, 2));
        const int fx = x + m_footX->value() * scale, fy = y + m_footY->value() * scale;
        painter.drawLine(fx - 7, fy, fx + 7, fy);
        painter.drawLine(fx, fy - 7, fx, fy + 7);
    }
    painter.end();
    // Apply display-only zoom uniformly to every animation state. This
    // scales the completed image, never the animation/world simulation.
    const int zoom = m_previewZoom ? m_previewZoom->value() : 1;
    const QSize displaySize(256 * zoom, 256 * zoom);
    if (m_preview->size() != displaySize) m_preview->setFixedSize(displaySize);
    m_preview->setPixmap(QPixmap::fromImage(zoom == 1 ? preview :
        preview.scaled(displaySize, Qt::IgnoreAspectRatio, Qt::FastTransformation)));
}
void SidboxPlayerAnimationEditor::appendFrame(int index, bool range)
{
    if (!m_atlasView || static_cast<AnimationAtlasView *>(m_atlasView)->image.isNull()) return;
    const int count = (m_atlas.width() / m_cellW) * (m_atlas.height() / m_cellH);
    if (index < 0 || index >= count || index > 255) return;
    Clip &clip = m_clips[clipKey(currentState(), currentDirection())];
    if (clip.frames.isEmpty()) { clip.durationMs = m_defaultDuration->value(); clip.loop = m_loop->isChecked(); }
    // Shift-click a range using the previously selected atlas cell.
    const int start = range && m_selectedAtlasFrame >= 0 ? m_selectedAtlasFrame : index;
    const int step = start <= index ? 1 : -1;
    for (int i = start; ; i += step) {
        if (i >= 0 && i < count && clip.frames.size() < 256) {
            clip.frames.append(i);
            clip.frameMs.append(m_defaultDuration->value());
        }
        if (i == index) break;
    }
    m_selectedAtlasFrame = index;
    m_previewPosition = 0; refreshTimeline(); refreshPreview();
}
void SidboxPlayerAnimationEditor::removeFrame()
{
    const int position = m_timeline->currentRow();
    Clip &clip = m_clips[clipKey(currentState(), currentDirection())];
    if (clip.frames.isEmpty() && effectiveClip()) {
        QMessageBox::information(this, tr("Mirrored Animation"),
            tr("This direction inherits its frames from the right-facing animation. "
               "Select the right-facing direction to edit it, or add frames here for an independent sequence."));
        return;
    }
    if (position < 0 || position >= clip.frames.size()) return;
    if (QMessageBox::question(this, tr("Delete animation frame?"),
            tr("Remove frame %1 (atlas cell %2) from %3 / %4?\n"
               "This edits only the current animation sequence until you Save.")
                .arg(position+1).arg(clip.frames.at(position))
                .arg(currentState(),currentDirection()),
            QMessageBox::Yes | QMessageBox::No, QMessageBox::No) != QMessageBox::Yes)
        return;
    clip.frames.removeAt(position);
    if (position < clip.frameMs.size()) clip.frameMs.removeAt(position);
    refreshTimeline(); m_timeline->setCurrentRow(qMin(position, clip.frames.size() - 1)); refreshPreview();
}
void SidboxPlayerAnimationEditor::moveFrame(int delta)
{
    const int pos = m_timeline->currentRow();
    Clip &clip = m_clips[clipKey(currentState(), currentDirection())];
    if (clip.frames.isEmpty() && effectiveClip()) {
        QMessageBox::information(this, tr("Mirrored Animation"),
            tr("Reorder the right-facing frames, or add your own frames for this direction."));
        return;
    }
    const int to = pos + delta;
    if (pos < 0 || to < 0 || to >= clip.frames.size()) return;
    std::swap(clip.frames[pos], clip.frames[to]);
    while (clip.frameMs.size() < clip.frames.size()) clip.frameMs.append(clip.durationMs);
    std::swap(clip.frameMs[pos], clip.frameMs[to]);
    refreshTimeline(); m_timeline->setCurrentRow(to); refreshPreview();
}
void SidboxPlayerAnimationEditor::saveClipSettings()
{
    if (m_refreshing || currentState().isEmpty() || currentDirection().isEmpty()) return;
    Clip &clip = m_clips[clipKey(currentState(), currentDirection())];
    clip.durationMs = m_defaultDuration->value(); clip.loop = m_loop->isChecked();
    refreshTimeline();
}
void SidboxPlayerAnimationEditor::readDocument()
{
    QFile file(m_file);
    if (!file.open(QIODevice::ReadOnly)) return;
    QJsonParseError err;
    const QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &err);
    if (err.error != QJsonParseError::NoError || !doc.isObject()) return;
    const QJsonObject root = doc.object();
    if (root.value("format").toString() != "SIDBOX-PLAYER-ANIM") return;
    m_cellW = qBound(1, root.value("cellWidth").toInt(m_cellW), 256);
    m_cellH = qBound(1, root.value("cellHeight").toInt(m_cellH), 256);
    const int n = root.value("directions").toInt(2);
    m_mode = n == 4 || n == 8 ? n : 2;
    m_mirror = root.value("mirrorLeft").toBool(true);
    m_autoState = root.value("autoStates").toBool(true);
    m_savedFootX = root.value("footX").toInt(-1);
    m_savedFootY = root.value("footY").toInt(-1);
    m_savedBoxX = root.value("hitboxX").toInt(0);
    m_savedBoxY = root.value("hitboxY").toInt(0);
    m_savedBoxW = root.value("hitboxW").toInt(-1);
    m_savedBoxH = root.value("hitboxH").toInt(-1);
    m_savedShowFoot = root.value("showFoot").toBool(true);
    m_savedShowBox = root.value("showHitbox").toBool(true);
    if (root.value("states").isArray()) {
        QStringList fromFile;
        for (auto v : root.value("states").toArray()) {
            const QString s = v.toString();
            if (!s.isEmpty() && !s.contains('|') && !fromFile.contains(s)) fromFile << s;
        }
        if (!fromFile.isEmpty()) m_states = fromFile;
    }
    const bool millisecondFormat = root.value("version").toInt(2) >= 3;
    for (auto v : root.value("clips").toArray()) {
        const QJsonObject c = v.toObject();
        const QString state = c.value("state").toString(), dir = c.value("direction").toString();
        if (!m_states.contains(state) || !directionsFor(m_mode).contains(dir)) continue;
        // V2 .sbanim stores 50 Hz ticks. Migrate in memory without changing playback speed.
        // V3 stores exact millisecond durations, including values not divisible by 20.
        Clip clip;
        clip.durationMs = millisecondFormat
            ? qBound(1, c.value("durationMs").toInt(100), 5000)
            : qBound(1, c.value("ticks").toInt(5), 250) * 20;
        clip.loop = c.value("loop").toBool(true);
        for (auto f : c.value("frames").toArray()) {
            const int frame = f.toInt(-1);
            if (frame >= 0 && frame < 256 && clip.frames.size() < 256) clip.frames << frame;
        }
        const QJsonArray frameDurations = c.value(millisecondFormat ? "frameMs" : "frameTicks").toArray();
        for (int i = 0; i < clip.frames.size(); ++i) {
            const int duration = i < frameDurations.size()
                ? frameDurations.at(i).toInt(millisecondFormat ? clip.durationMs : clip.durationMs / 20)
                : (millisecondFormat ? clip.durationMs : clip.durationMs / 20);
            clip.frameMs.append(millisecondFormat ? qBound(1, duration, 5000)
                                                : qBound(1, duration, 250) * 20);
        }
        m_clips[clipKey(state, dir)] = clip;
    }
}

bool SidboxPlayerAnimationEditor::writeDocument()
{
    if (m_atlas.isNull() || m_cellW < 1 || m_cellH < 1 ||
        m_atlas.width() % m_cellW || m_atlas.height() % m_cellH ||
        (m_atlas.width() / m_cellW) * (m_atlas.height() / m_cellH) > 256) {
        QMessageBox::warning(this, tr("Invalid Atlas Grid"),
            tr("The image dimensions must divide evenly into the cell size, with at most 256 cells (BOB index is uint8_t)."));
        return false;
    }
    const int atlasCount = (m_atlas.width() / m_cellW) * (m_atlas.height() / m_cellH);
    for (auto it = m_clips.cbegin(); it != m_clips.cend(); ++it) {
        for (int frame : it.value().frames) {
            if (frame < 0 || frame >= atlasCount) {
                QMessageBox::warning(this, tr("Animation Frames"),
                    tr("One or more animations reference cells outside the selected atlas grid. "
                       "Fix the cell dimensions or remove the invalid frames."));
                return false;
            }
        }
    }
    if (m_boxW->value() < 1 || m_boxH->value() < 1 ||
        m_boxX->value() + m_boxW->value() > m_cellW ||
        m_boxY->value() + m_boxH->value() > m_cellH) {
        QMessageBox::warning(this, tr("Player Hitbox"),
            tr("The hitbox must fit INSIDE one atlas cell.\n"
               "X + Width must not exceed %1 and Y + Height must not exceed %2.\n"
               "Both Width and Height must be at least 1 pixel.")
               .arg(m_cellW).arg(m_cellH));
        return false;
    }
    QJsonObject root;
    root["format"] = "SIDBOX-PLAYER-ANIM"; root["version"] = 3;
    root["atlas"] = QDir(QFileInfo(m_file).absolutePath()).relativeFilePath(m_atlasFile);
    root["cellWidth"] = m_cellW; root["cellHeight"] = m_cellH;
    root["directions"] = m_mode; root["mirrorLeft"] = m_mirror;
    root["autoStates"] = m_autoState;
    root["footX"] = m_footX->value(); root["footY"] = m_footY->value();
    root["hitboxX"] = m_boxX->value(); root["hitboxY"] = m_boxY->value();
    root["hitboxW"] = m_boxW->value(); root["hitboxH"] = m_boxH->value();
    root["showFoot"] = m_showFoot->isChecked(); root["showHitbox"] = m_showBox->isChecked();
    QJsonArray states, clips;
    for (const auto &s : m_states) states.append(s);
    root["states"] = states;
    for (auto it = m_clips.cbegin(); it != m_clips.cend(); ++it) {
        const QStringList key = it.key().split('|');
        if (key.size() != 2 || !m_states.contains(key.at(0)) || !directionsFor(m_mode).contains(key.at(1))) continue;
        QJsonObject c; c["state"] = key.at(0); c["direction"] = key.at(1);
        c["durationMs"] = it.value().durationMs; c["loop"] = it.value().loop;
        QJsonArray frames;
        for (int f : it.value().frames) frames.append(f);
        c["frames"] = frames;
        QJsonArray frameDurations;
        for (int i = 0; i < it.value().frames.size(); ++i)
            frameDurations.append(i < it.value().frameMs.size()
                                  ? it.value().frameMs.at(i) : it.value().durationMs);
        c["frameMs"] = frameDurations;
        clips.append(c);
    }
    root["clips"] = clips;
    const QDir dir(QFileInfo(m_file).absolutePath());
    if (!dir.exists() && !QDir().mkpath(dir.absolutePath())) {
        QMessageBox::warning(this, tr("Save Animations"), tr("Could not create folder: %1").arg(dir.absolutePath()));
        return false;
    }
    QSaveFile out(m_file);
    if (!out.open(QIODevice::WriteOnly) || out.write(QJsonDocument(root).toJson(QJsonDocument::Indented)) < 0 || !out.commit()) {
        QMessageBox::warning(this, tr("Save Animations"), tr("Could not save: %1").arg(m_file));
        return false;
    }
    return true;
}

QString SidboxPlayerAnimationEditor::generateHeader(const QString &prefix, QString *error) const
{
    // The playeranim.ruleh owns the COMPLETE runtime C implementation.
    // Only state IDs, direction IDs, clip frame durations (ms) and defaults come from Qt.
    const QDir app(QCoreApplication::applicationDirPath());
    QStringList candidates;
    if (qEnvironmentVariableIsSet("SIDBOX_SDK"))
        candidates << qEnvironmentVariable("SIDBOX_SDK");
    candidates << app.filePath(QStringLiteral("idelibs"))
               << app.filePath(QStringLiteral("../idelibs"))
               << app.filePath(QStringLiteral("../../idelibs"))
               << app.filePath(QStringLiteral("../SidboxIDE/idelibs"))
               << QDir::current().filePath(QStringLiteral("idelibs"))
               << QDir::current().filePath(QStringLiteral("SidboxIDE/idelibs"));
    QString templatePath;
    for (const QString &root : candidates) {
        const QString candidate = QDir(root).filePath(QStringLiteral("codehelpers/game/playeranim.ruleh"));
        if (QFileInfo::exists(candidate)) { templatePath = candidate; break; }
    }
    if (templatePath.isEmpty()) {
        if (error) *error = QStringLiteral("Missing IDE template idelibs/codehelpers/game/playeranim.ruleh");
        return {};
    }
    QFile templateFile(templatePath);
    if (!templateFile.open(QIODevice::ReadOnly)) {
        if (error) *error = QStringLiteral("Cannot read Player Animation rule: %1").arg(templatePath);
        return {};
    }
    QString raw = QString::fromUtf8(templateFile.readAll());
    QMap<QString, QByteArray> sections;
    const QRegularExpression sectionRe(QStringLiteral(
        R"((?ms)^@IDE_SECTION\{([A-Z_][A-Z0-9_]*)\}[ \t]*\r?\n(.*?)^@IDE_SECTION_END[ \t]*\r?\n?)"));
    auto matches = sectionRe.globalMatch(raw);
    const int sectionCount = raw.count(QStringLiteral("@IDE_SECTION{"));
    while (matches.hasNext()) {
        const auto matched = matches.next();
        if (sections.contains(matched.captured(1))) {
            if (error) *error = QStringLiteral("Duplicate Player Animation rule section: %1").arg(matched.captured(1));
            return {};
        }
        sections.insert(matched.captured(1), matched.captured(2).toUtf8());
    }
    raw.remove(sectionRe);
    if (sections.size() != sectionCount || raw.contains(QStringLiteral("@IDE_SECTION"))) {
        if (error) *error = QStringLiteral("Malformed Player Animation rule sections.");
        return {};
    }
    for (const QString &name : {QStringLiteral("STATE"), QStringLiteral("DIRECTION"),
                                QStringLiteral("FRAME_ARRAY"), QStringLiteral("DURATION_ARRAY"),
                                QStringLiteral("CLIP_ENTRY")}) {
        if (!sections.contains(name)) {
            if (error) *error = QStringLiteral("Missing Player Animation rule section %1").arg(name);
            return {};
        }
    }
    auto renderRow = [&](const QString &name, const QMap<QString, QString> &fields,
                         QString &output) -> bool {
        QByteArray rendered;
        if (!GameHelperTemplates::renderFields(sections.value(name), fields,
                QStringLiteral("playeranim.ruleh / ") + name, &rendered, error)) return false;
        output += QString::fromUtf8(rendered);
        return true;
    };
    const QString up = prefix.toUpper();
    QString stateRows, directionRows, arrays, clips;
    QStringList identifiers;
    for (int i = 0; i < m_states.size(); ++i) {
        QString name = m_states.at(i).toUpper();
        name.replace(QRegularExpression(QStringLiteral("[^A-Z0-9_]")), QStringLiteral("_"));
        if (name.isEmpty() || name.at(0).isDigit()) name.prepend(QStringLiteral("STATE_"));
        if (identifiers.contains(name)) name += QStringLiteral("_%1").arg(i);
        identifiers.append(name);
        if (!renderRow(QStringLiteral("STATE"),
                {{QStringLiteral("PREFIX_UPPER"), up},
                 {QStringLiteral("STATE_NAME"), name},
                 {QStringLiteral("STATE_ID"), QString::number(i)}}, stateRows)) return {};
    }
    const QStringList dirs = directionsFor(m_mode);
    for (int i = 0; i < dirs.size(); ++i)
        if (!renderRow(QStringLiteral("DIRECTION"),
                {{QStringLiteral("PREFIX_UPPER"), up},
                 {QStringLiteral("DIRECTION_NAME"), dirs.at(i).toUpper()},
                 {QStringLiteral("DIRECTION_ID"), QString::number(i)}}, directionRows)) return {};

    int index = 0;
    for (const QString &state : m_states) for (const QString &dir : dirs) {
        const auto found = m_clips.constFind(clipKey(state, dir));
        const Clip *clip = found == m_clips.constEnd() || found->frames.isEmpty() ? nullptr : &found.value();
        bool flip = false;
        if (!clip && m_mirror) {
            QString src;
            if (dir == QStringLiteral("Left")) src = QStringLiteral("Right");
            else if (dir == QStringLiteral("UpLeft")) src = QStringLiteral("UpRight");
            else if (dir == QStringLiteral("DownLeft")) src = QStringLiteral("DownRight");
            if (!src.isEmpty()) {
                const auto inherited = m_clips.constFind(clipKey(state, src));
                if (inherited != m_clips.constEnd() && !inherited->frames.isEmpty()) {
                    clip = &inherited.value(); flip = true;
                }
            }
        }
        QString frameName = QStringLiteral("0"), durationName = QStringLiteral("0");
        if (clip) {
            frameName = QStringLiteral("%1_frames_%2").arg(prefix).arg(index);
            QStringList frameValues;
            for (int frame : clip->frames) frameValues.append(QString::number(frame));
            if (!renderRow(QStringLiteral("FRAME_ARRAY"),
                {{QStringLiteral("ARRAY_NAME"), frameName},
                 {QStringLiteral("FRAME_VALUES"), frameValues.join(QStringLiteral(", ")) + QStringLiteral(", ")}}, arrays)) return {};
            bool nonuniform = false;
            for (int pos = 0; pos < clip->frames.size(); ++pos) {
                if ((pos < clip->frameMs.size() ? clip->frameMs.at(pos) : clip->durationMs) != clip->durationMs) {
                    nonuniform = true; break;
                }
            }
            if (nonuniform) {
                durationName = QStringLiteral("%1_ms_%2").arg(prefix).arg(index);
                QStringList durations;
                for (int pos = 0; pos < clip->frames.size(); ++pos)
                    durations.append(QString::number(pos < clip->frameMs.size()
                                ? clip->frameMs.at(pos) : clip->durationMs));
                if (!renderRow(QStringLiteral("DURATION_ARRAY"),
                    {{QStringLiteral("ARRAY_NAME"), durationName},
                     {QStringLiteral("DURATION_VALUES"), durations.join(QStringLiteral(", ")) + QStringLiteral(", ")}}, arrays)) return {};
            }
        }
        const QMap<QString, QString> fields = {
            {QStringLiteral("FRAME_ARRAY"), frameName},
            {QStringLiteral("DURATION_ARRAY"), durationName},
            {QStringLiteral("FRAME_COUNT"), clip ? QString::number(clip->frames.size()) : QStringLiteral("0")},
            {QStringLiteral("DURATION_MS"), clip ? QString::number(clip->durationMs) : QStringLiteral("1")},
            {QStringLiteral("LOOP"), !clip || clip->loop ? QStringLiteral("1") : QStringLiteral("0")},
            {QStringLiteral("FLIP"), flip ? QStringLiteral("1") : QStringLiteral("0")}
        };
        if (!renderRow(QStringLiteral("CLIP_ENTRY"), fields, clips)) return {};
        ++index;
    }
    const auto named = [this](const QString &name) {
        for (int i = 0; i < m_states.size(); ++i)
            if (m_states.at(i).compare(name, Qt::CaseInsensitive) == 0) return i;
        return 0;
    };
    const QMap<QString, QString> fields = {
        {QStringLiteral("PREFIX"), prefix}, {QStringLiteral("PREFIX_UPPER"), up},
        {QStringLiteral("FOOT_X"), QString::number(m_footX->value())},
        {QStringLiteral("FOOT_Y"), QString::number(m_footY->value())},
        {QStringLiteral("HITBOX_X"), QString::number(m_boxX->value())},
        {QStringLiteral("HITBOX_Y"), QString::number(m_boxY->value())},
        {QStringLiteral("HITBOX_W"), QString::number(m_boxW->value())},
        {QStringLiteral("HITBOX_H"), QString::number(m_boxH->value())},
        {QStringLiteral("STATE_ENUMS"), stateRows},
        {QStringLiteral("DIRECTION_ENUMS"), directionRows},
        {QStringLiteral("STATE_COUNT"), QString::number(m_states.size())},
        {QStringLiteral("DIRECTION_COUNT"), QString::number(dirs.size())},
        {QStringLiteral("HAS_HURT"), m_states.contains(QStringLiteral("Hurt"), Qt::CaseInsensitive) ? QStringLiteral("1") : QStringLiteral("0")},
        {QStringLiteral("HAS_MELEE"), m_states.contains(QStringLiteral("Melee"), Qt::CaseInsensitive) ? QStringLiteral("1") : QStringLiteral("0")},
        {QStringLiteral("HAS_UPSTAIRS"), m_states.contains(QStringLiteral("Upstairs"), Qt::CaseInsensitive) ? QStringLiteral("1") : QStringLiteral("0")},
        {QStringLiteral("HAS_DOWNSTAIRS"), m_states.contains(QStringLiteral("Downstairs"), Qt::CaseInsensitive) ? QStringLiteral("1") : QStringLiteral("0")},
        {QStringLiteral("CLIP_ARRAYS"), arrays},
        {QStringLiteral("CLIP_COUNT"), QString::number(clips.isEmpty() ? 0 : m_states.size() * dirs.size())},
        {QStringLiteral("CLIP_ROWS"), clips},
        {QStringLiteral("IDLE_ID"), QString::number(qMax(0, m_states.indexOf(QStringLiteral("Idle"))))},
        {QStringLiteral("AUTO_STATE"), m_autoState ? QStringLiteral("1") : QStringLiteral("0")},
        {QStringLiteral("IDLE"), QString::number(named(QStringLiteral("Idle")))},
        {QStringLiteral("WALK"), QString::number(named(QStringLiteral("Walk")))},
        {QStringLiteral("RUN"), QString::number(named(QStringLiteral("Run")))},
        {QStringLiteral("PUSH"), QString::number(named(QStringLiteral("Push")))},
        {QStringLiteral("JUMP"), QString::number(named(QStringLiteral("Jump")))},
        {QStringLiteral("FALL"), QString::number(named(QStringLiteral("Fall")))},
        {QStringLiteral("BALANCE"), QString::number(named(QStringLiteral("Balance")))},
        {QStringLiteral("HURT"), QString::number(named(QStringLiteral("Hurt")))},
        {QStringLiteral("SLIDE"), QString::number(named(QStringLiteral("Slide")))}
    };
    for (const QString &name : {QStringLiteral("STATE_ENUMS"), QStringLiteral("CLIP_ROWS"),
                                QStringLiteral("CLIP_ARRAYS"), QStringLiteral("AUTO_STATE")}) {
        if (!raw.contains(QStringLiteral("@IDE{%1}").arg(name)) && name != QStringLiteral("AUTO_STATE")) {
            if (error) *error = QStringLiteral("Player Animation rule missing @IDE{%1}").arg(name);
            return {};
        }
    }
    QByteArray conditional, output;
    if (!GameHelperTemplates::renderConditionals(raw.toUtf8(), fields,
            QStringLiteral("playeranim.ruleh"), &conditional, error) ||
        !GameHelperTemplates::renderFields(conditional, fields,
            QStringLiteral("playeranim.ruleh"), &output, error)) return {};
    return QString::fromUtf8(output);
}
bool SidboxPlayerAnimationEditor::saveHeader(const QString &path)
{
    // Atomic replacement: a failed write never truncates the last working
    // player_anim.h.  The C symbol prefix is ALWAYS based on the filename,
    // keeping it consistent with the starter's #include and function names.
    QString prefix = QFileInfo(path).completeBaseName().toLower();
    prefix.replace(QRegularExpression("[^a-z0-9_]"), "_");
    if (prefix.isEmpty() || prefix.at(0).isDigit()) prefix.prepend("gg_");
    const QFileInfo info(path);
    if (!QDir().mkpath(info.absolutePath())) {
        QMessageBox::warning(this, tr("Player Animation Header"),
            tr("Could not create folder:\n%1").arg(info.absolutePath()));
        return false;
    }
    QString generationError;
    const QByteArray bytes = generateHeader(prefix, &generationError).toUtf8();
    if (bytes.isEmpty()) {
        QMessageBox::warning(this, tr("Player Animation Header"), generationError);
        return false;
    }
    QSaveFile out(path);
    if (!out.open(QIODevice::WriteOnly) || out.write(bytes) != bytes.size() || !out.commit()) {
        QMessageBox::warning(this, tr("Player Animation Header"),
            tr("Failed to write C header:\n%1").arg(path));
        return false;
    }
    return true;
}

bool SidboxPlayerAnimationEditor::offerHeaderUpdate()
{
    if (m_defaultHeaderFile.isEmpty()) return true;
    const bool exists = QFileInfo::exists(m_defaultHeaderFile);
    const QString action = exists ? tr("Update") : tr("Create");
    // Save the editable .sbanim first; then explicitly ask before changing
    // the game-facing C header. 'No' retains the .sbanim without exporting.
    const auto answer = QMessageBox::question(this, tr("Save Animations"),
        tr("Animation definitions saved.\n\n"
           "%1 the V1 game header as well?\n\n%2\n\n"
           "%3\n\n"
           "Choose Yes to keep the game animation frames and timing in sync.")
            .arg(action, QDir::toNativeSeparators(m_defaultHeaderFile),
                 exists ? tr("The existing generated header will be replaced.")
                        : tr("The generated header will be created.")),
        QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if (answer != QMessageBox::Yes) return true;
    if (!saveHeader(m_defaultHeaderFile)) return false;
    return true;
}

void SidboxPlayerAnimationEditor::exportHeader()
{
    if (!writeDocument()) return;
    const QString defaultPath = m_defaultHeaderFile.isEmpty()
        ? QDir(QFileInfo(m_file).absolutePath())
            .filePath(QFileInfo(m_file).completeBaseName() + "_playeranim.h")
        : m_defaultHeaderFile;
    const QString path = QFileDialog::getSaveFileName(this, tr("Export V1 Animation Header"),
                                                       defaultPath, tr("C Headers (*.h)"));
    if (path.isEmpty() || !saveHeader(path)) return;
    QMessageBox::information(this, tr("Export V1 C"),
        tr("Wrote %1\n\nInclude this header in your game's main.c. "
           "Call <prefix>_step(&animation, &player_bob, state, direction, 1) "
           "once per VBlank before gfx_drawbob().\n\nThe original PPB must be loaded "
           "and its BOB cell dimensions must match the editor.").arg(path));
}
