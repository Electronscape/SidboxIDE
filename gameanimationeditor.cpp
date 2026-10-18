#include "gameanimationeditor.h"
#include "ppbcodec.h"

#include <QAbstractItemView>
#include <QCheckBox>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QDir>
#include <QFile>
#include <QFileDialog>
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
#include <QPaintEvent>
#include <QAbstractItemModel>
#include <QLineEdit>
#include <QPixmap>
#include <QScrollArea>
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

// A lightweight clickable sheet with one native-zoomed 32x32 (or custom)
// grid. No pixmap interpolation or alpha blending is done by this widget.
class AnimationAtlasView final : public QWidget {
public:
    QImage image;
    int cellW = 32, cellH = 32, zoom = 3, selected = -1;
    std::function<void(int, bool)> clicked;
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
        p.fillRect(rect(), QColor(35, 39, 44));
        if (image.isNull() || cellW < 1 || cellH < 1) return;
        p.setRenderHint(QPainter::SmoothPixmapTransform, false);
        p.drawImage(QRect(0, 0, image.width() * zoom, image.height() * zoom), image);
        const int cols = image.width() / cellW;
        const int rows = image.height() / cellH;
        p.setPen(QColor(105, 107, 116, 130));
        for (int x = 0; x <= cols; ++x) p.drawLine(x * cellW * zoom, 0, x * cellW * zoom, rows * cellH * zoom);
        for (int y = 0; y <= rows; ++y) p.drawLine(0, y * cellH * zoom, cols * cellW * zoom, y * cellH * zoom);
        if (selected >= 0 && selected < cols * rows) {
            p.setPen(QPen(QColor(248, 70, 103), 2));
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
        if (clicked) clicked(frame, event->modifiers() & Qt::ShiftModifier);
    }
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
        int cellWidth, int cellHeight, QWidget *parent)
    : QDialog(parent), m_file(animationFile),
      m_defaultHeaderFile(defaultHeaderFile), m_atlasFile(atlasFile),
      m_cellW(cellWidth > 0 && cellWidth <= 256 ? cellWidth : 32),
      m_cellH(cellHeight > 0 && cellHeight <= 256 ? cellHeight : 32)
{
    if (QFileInfo(atlasFile).suffix().compare("ppb", Qt::CaseInsensitive) == 0) {
        SidboxPpb::Picture pic;
        if (SidboxPpb::read(atlasFile, &pic)) {
            // The actual image is untouched. Index 0 is transparent only in
            // this Qt preview; all other indices are fully opaque.
            QImage indexed = pic.indexed;
            QVector<QRgb> palette = indexed.colorTable();
            for (int i = 0; i < palette.size(); ++i)
                palette[i] = i == 0 ? qRgba(0, 0, 0, 0)
                                  : qRgba(qRed(palette[i]), qGreen(palette[i]), qBlue(palette[i]), 255);
            indexed.setColorTable(palette);
            m_atlas = indexed.convertToFormat(QImage::Format_ARGB32);
        }
    } else {
        QImageReader reader(atlasFile);
        reader.setAutoTransform(true);
        m_atlas = reader.read().convertToFormat(QImage::Format_ARGB32);
    }
    setWindowTitle(tr("Player Animation Editor — %1").arg(QFileInfo(atlasFile).fileName()));
    setMinimumSize(1040, 650);
    resize(1260, 790);
    setStyleSheet(QStringLiteral("QDialog, QPushButton, QComboBox, QSpinBox, QListWidget, "
                                 "QScrollArea, QLineEdit, QFrame { border-radius:0px; }"));
    m_states = {"Idle", "Walk", "Run", "Push", "Jump", "Fall", "Slide", "Balance", "Hurt", "Land"};
    if (!m_atlas.isNull()) readDocument();
    createUi();
    if (m_atlas.isNull()) {
        QMessageBox::warning(this, tr("Animation Atlas"), tr("Could not read sprite atlas:\n%1").arg(atlasFile));
    }
}

QString SidboxPlayerAnimationEditor::currentState() const
{
    return m_stateList && m_stateList->currentItem() ? m_stateList->currentItem()->text() : QString();
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
    auto *title = new QLabel(tr("PLAYER ANIMATION EDITOR  |  V1 SIDBOX"), this);
    QFont font = title->font(); font.setBold(true); title->setFont(font);
    headline->addWidget(title);
    headline->addStretch();
    headline->addWidget(new QLabel(tr("Direction mode:"), this));
    m_directionMode = new QComboBox(this);
    for (int n : {2, 4, 8}) m_directionMode->addItem(tr("%1 directions").arg(n), n);
    m_directionMode->setCurrentIndex(m_mode == 2 ? 0 : m_mode == 4 ? 1 : 2);
    headline->addWidget(m_directionMode);
    outer->addLayout(headline);

    auto *split = new QSplitter(Qt::Horizontal, this);
    split->setChildrenCollapsible(false);
    outer->addWidget(split, 1);

    auto *left = new QWidget(split);
    auto *leftLayout = new QVBoxLayout(left);
    leftLayout->addWidget(new QLabel(tr("ANIMATION STATES"), left));
    m_stateList = new QListWidget(left);
    leftLayout->addWidget(m_stateList, 1);
    auto *stateButtons = new QHBoxLayout;
    auto *addState = new QPushButton(tr("+ State"), left);
    auto *removeState = new QPushButton(tr("- State"), left);
    stateButtons->addWidget(addState); stateButtons->addWidget(removeState);
    leftLayout->addLayout(stateButtons);
    leftLayout->addWidget(new QLabel(tr("DIRECTION"), left));
    m_directions = new QComboBox(left);
    leftLayout->addWidget(m_directions);
    m_mirrorCheck = new QCheckBox(tr("Mirror left from right"), left);
    m_mirrorCheck->setChecked(m_mirror);
    m_mirrorCheck->setToolTip(tr("Left, up-left and down-left inherit right-facing frames unless explicitly assigned."));
    leftLayout->addWidget(m_mirrorCheck);
    m_autoCheck = new QCheckBox(tr("Export auto state chooser"), left);
    m_autoCheck->setChecked(m_autoState);
    m_autoCheck->setToolTip(tr("Optional C function for Idle/Walk/Run/Jump/Fall/Slide/Balance/Push/Hurt. Your game calls it with its player physics values."));
    leftLayout->addWidget(m_autoCheck);
    leftLayout->addWidget(new QLabel(tr("Tip: click atlas frames to add them.\nShift-click adds a range.\nEmpty left sequences inherit right."), left));
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
    auto *scroll = new QScrollArea(middle);
    scroll->setWidgetResizable(false);
    auto *atlas = new AnimationAtlasView(scroll);
    atlas->image = m_atlas;
    m_atlasView = atlas;
    scroll->setWidget(atlas);
    mid->addWidget(scroll, 1);
    mid->addWidget(new QLabel(tr("FRAME TIMELINE — select frames, then remove/reorder them"), middle));
    m_timeline = new QListWidget(middle);
    m_timeline->setViewMode(QListView::IconMode);
    m_timeline->setFlow(QListView::LeftToRight);
    m_timeline->setWrapping(false);
    m_timeline->setIconSize(QSize(64, 64));
    m_timeline->setGridSize(QSize(85, 93));
    m_timeline->setMovement(QListView::Snap);
    m_timeline->setDragDropMode(QAbstractItemView::InternalMove);
    m_timeline->setDefaultDropAction(Qt::MoveAction);
    m_timeline->setFixedHeight(125);
    mid->addWidget(m_timeline);
    auto *timelineActions = new QHBoxLayout;
    auto *removeFrame = new QPushButton(tr("Remove frame"), middle);
    auto *moveLeft = new QPushButton(tr("Move ←"), middle);
    auto *moveRight = new QPushButton(tr("Move →"), middle);
    timelineActions->addWidget(removeFrame); timelineActions->addWidget(moveLeft);
    timelineActions->addWidget(moveRight); timelineActions->addStretch();
    m_ticks = new QSpinBox(middle); m_ticks->setRange(1, 250); m_ticks->setValue(5);
    m_ticks->setSuffix(tr(" ticks"));
    m_ticks->setToolTip(tr("50Hz VBlank frames per animation image. 5 ticks = 100 ms."));
    timelineActions->addWidget(new QLabel(tr("Frame time:"), middle));
    timelineActions->addWidget(m_ticks);
    m_loop = new QCheckBox(tr("Loop"), middle); m_loop->setChecked(true);
    timelineActions->addWidget(m_loop);
    mid->addLayout(timelineActions);

    auto *right = new QWidget(split);
    auto *rightLayout = new QVBoxLayout(right);
    rightLayout->addWidget(new QLabel(tr("LIVE PREVIEW"), right));
    m_preview = new QLabel(right);
    m_preview->setAlignment(Qt::AlignCenter);
    m_preview->setMinimumSize(210, 220);
    m_preview->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_preview->setStyleSheet(QStringLiteral("background:#24282c; border:1px solid #646a71; border-radius:0px;"));
    rightLayout->addWidget(m_preview, 1);
    m_play = new QPushButton(tr("Pause preview"), right);
    rightLayout->addWidget(m_play);
    rightLayout->addWidget(new QLabel(tr("SPRITE ANCHORS"), right));
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
    rightLayout->addWidget(new QLabel(tr("The hitbox controls V1 player physics when\nanimations are enabled. Foot anchor is\npreview-only; BOB pixels remain unchanged."), right));
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
    connect(m_stateList, &QListWidget::currentRowChanged, this, [this] { refreshAll(); });
    connect(m_directions, &QComboBox::currentIndexChanged, this, [this] { refreshAll(); });
    connect(m_directionMode, &QComboBox::currentIndexChanged, this, [this] {
        m_mode = m_directionMode->currentData().toInt();
        rebuildDirections(); refreshAll();
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
    connect(m_width, &QSpinBox::valueChanged, this, [this](int v) { m_cellW = v; updateAtlas(); refreshAll(); });
    connect(m_height, &QSpinBox::valueChanged, this, [this](int v) { m_cellH = v; updateAtlas(); refreshAll(); });
    connect(m_zoom, &QSpinBox::valueChanged, this, [this](int) { updateAtlas(); });
    atlas->clicked = [this](int index, bool range) { appendFrame(index, range); };
    connect(m_timeline->model(), &QAbstractItemModel::rowsMoved, this,
        [this] {
            if (m_refreshing) return;
            const QString key = clipKey(currentState(), currentDirection());
            Clip &local = m_clips[key];
            // Inherited leftward frames cannot be silently edited, because
            // that would unexpectedly stop hardware X mirroring.
            if (local.frames.isEmpty()) {
                QTimer::singleShot(0, this, [this] { refreshTimeline(); });
                return;
            }
            QVector<int> reordered;
            for (int i = 0; i < m_timeline->count(); ++i)
                reordered.append(m_timeline->item(i)->data(Qt::UserRole).toInt());
            if (reordered.size() == local.frames.size()) local.frames = reordered;
        });
    connect(removeFrame, &QPushButton::clicked, this, [this] { this->removeFrame(); });
    connect(moveLeft, &QPushButton::clicked, this, [this] { moveFrame(-1); });
    connect(moveRight, &QPushButton::clicked, this, [this] { moveFrame(1); });
    connect(m_ticks, &QSpinBox::valueChanged, this, [this](int) { saveClipSettings(); });
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
    m_timer = new QTimer(this); m_timer->setInterval(20);
    connect(m_timer, &QTimer::timeout, this, [this] {
        if (!m_playing) return;
        const Clip *c = effectiveClip();
        if (!c || c->frames.isEmpty()) return;
        if (++m_previewElapsed < c->ticks) return;
        m_previewElapsed = 0;
        if (m_previewPosition + 1 < c->frames.size()) ++m_previewPosition;
        else if (c->loop) m_previewPosition = 0;
        refreshPreview();
    });
    m_timer->start();
}

void SidboxPlayerAnimationEditor::rebuildStateList(int selected)
{
    QSignalBlocker guard(m_stateList);
    m_stateList->clear(); m_stateList->addItems(m_states);
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
    refreshTimeline(); refreshPreview();
}
void SidboxPlayerAnimationEditor::refreshTimeline()
{
    m_refreshing = true;
    QSignalBlocker guard(m_timeline);
    m_timeline->clear();
    const Clip *clip = effectiveClip();
    if (clip) {
        for (int frame : clip->frames) {
            auto *item = new QListWidgetItem(frameIcon(m_atlas, frame, m_cellW, m_cellH), QString::number(frame));
            item->setData(Qt::UserRole, frame);
            m_timeline->addItem(item);
        }
    }
    {
        QSignalBlocker ticks(m_ticks), loop(m_loop);
        m_ticks->setValue(clip ? clip->ticks : 5);
        m_loop->setChecked(clip ? clip->loop : true);
    }
    m_refreshing = false;
    bool flipped = false; effectiveClip(&flipped);
    const int cols = m_cellW ? m_atlas.width() / m_cellW : 0;
    const int rows = m_cellH ? m_atlas.height() / m_cellH : 0;
    m_status->setText(tr("%1 / %2  |  %3 frames%4  |  %5 atlas cells  |  1 image = %6 ms at 50Hz")
        .arg(currentState(), currentDirection()).arg(clip ? clip->frames.size() : 0)
        .arg(flipped ? tr("  [mirrored from right]") : QString())
        .arg(cols * rows).arg(m_ticks->value() * 20));
}
void SidboxPlayerAnimationEditor::refreshPreview()
{
    const Clip *clip = effectiveClip();
    QImage preview(256, 256, QImage::Format_ARGB32);
    preview.fill(QColor(35, 39, 44));
    QPainter painter(&preview);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, false);
    const int scale = qMax(1, qMin(6, qMin(220 / qMax(1, m_cellW), 220 / qMax(1, m_cellH))));
    const int x = (256 - m_cellW * scale) / 2, y = (256 - m_cellH * scale) / 2;
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
        painter.setPen(QPen(QColor(105, 227, 240), 1));
        painter.drawRect(x + m_boxX->value() * scale, y + m_boxY->value() * scale,
                         m_boxW->value() * scale, m_boxH->value() * scale);
    }
    if (m_showFoot->isChecked()) {
        painter.setPen(QPen(QColor(246, 213, 65), 2));
        const int fx = x + m_footX->value() * scale, fy = y + m_footY->value() * scale;
        painter.drawLine(fx - 7, fy, fx + 7, fy);
        painter.drawLine(fx, fy - 7, fx, fy + 7);
    }
    painter.end();
    m_preview->setPixmap(QPixmap::fromImage(preview));
}
void SidboxPlayerAnimationEditor::appendFrame(int index, bool range)
{
    if (!m_atlasView || static_cast<AnimationAtlasView *>(m_atlasView)->image.isNull()) return;
    const int count = (m_atlas.width() / m_cellW) * (m_atlas.height() / m_cellH);
    if (index < 0 || index >= count || index > 255) return;
    Clip &clip = m_clips[clipKey(currentState(), currentDirection())];
    if (clip.frames.isEmpty()) { clip.ticks = m_ticks->value(); clip.loop = m_loop->isChecked(); }
    // Shift-click a range using the previously selected atlas cell.
    const int start = range && m_selectedAtlasFrame >= 0 ? m_selectedAtlasFrame : index;
    const int step = start <= index ? 1 : -1;
    for (int i = start; ; i += step) {
        if (i >= 0 && i < count && clip.frames.size() < 256) clip.frames.append(i);
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
    clip.frames.removeAt(position);
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
    refreshTimeline(); m_timeline->setCurrentRow(to); refreshPreview();
}
void SidboxPlayerAnimationEditor::saveClipSettings()
{
    if (m_refreshing || currentState().isEmpty() || currentDirection().isEmpty()) return;
    Clip &clip = m_clips[clipKey(currentState(), currentDirection())];
    clip.ticks = m_ticks->value(); clip.loop = m_loop->isChecked();
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
    for (auto v : root.value("clips").toArray()) {
        const QJsonObject c = v.toObject();
        const QString state = c.value("state").toString(), dir = c.value("direction").toString();
        if (!m_states.contains(state) || !directionsFor(m_mode).contains(dir)) continue;
        Clip clip; clip.ticks = qBound(1, c.value("ticks").toInt(5), 250);
        clip.loop = c.value("loop").toBool(true);
        for (auto f : c.value("frames").toArray()) {
            const int frame = f.toInt(-1);
            if (frame >= 0 && frame < 256 && clip.frames.size() < 256) clip.frames << frame;
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
    root["format"] = "SIDBOX-PLAYER-ANIM"; root["version"] = 1;
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
        c["ticks"] = it.value().ticks; c["loop"] = it.value().loop;
        QJsonArray frames;
        for (int f : it.value().frames) frames.append(f);
        c["frames"] = frames; clips.append(c);
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

QString SidboxPlayerAnimationEditor::generateHeader(const QString &prefix) const
{
    // Fully standalone C99 header: no dynamic allocation, no source bitmap,
    // noncontiguous frames supported. One runtime instance per player.
    QString s;
    s += "/* GamerGirl Player Animation - generated from .sbanim. DO NOT EDIT.\n"
         " * Requires the original atlas loaded into gfxbob_t (cell dimensions match).\n"
         " * Call after moving the player and before gfx_drawbob().\n"
         " * State/direction numbers follow the enums below. 50 ticks/second.\n */\n"
         "#ifndef " + prefix.toUpper() + "_PLAYERANIM_H\n#define " + prefix.toUpper() + "_PLAYERANIM_H\n"
         "#include \"apis.h\"\n#include <stdint.h>\n\n";
    // Runtime physics can consume this without parsing .sbanim on SIDBOX.
    // The BOB still uses its full 32/48/64px atlas cell for rendering.
    s += QString("#define %1_HITBOX_X %2u\n"
                 "#define %1_HITBOX_Y %3u\n"
                 "#define %1_HITBOX_W %4u\n"
                 "#define %1_HITBOX_H %5u\n\n")
             .arg(prefix.toUpper()).arg(m_boxX->value()).arg(m_boxY->value())
             .arg(m_boxW->value()).arg(m_boxH->value());
    s += "enum {\n";
    QStringList identifiers;
    for (int i = 0; i < m_states.size(); ++i) {
        QString name = m_states.at(i).toUpper();
        name.replace(QRegularExpression("[^A-Z0-9_]"), "_");
        if (name.isEmpty() || name.at(0).isDigit()) name.prepend("STATE_");
        if (identifiers.contains(name)) name += QStringLiteral("_%1").arg(i);
        identifiers.append(name);
        s += QString("    %1_STATE_%2 = %3,\n").arg(prefix.toUpper(), name).arg(i);
    }
    s += "};\n\nenum {\n";
    const QStringList dirs = directionsFor(m_mode);
    for (int i = 0; i < dirs.size(); ++i) {
        QString name = dirs.at(i).toUpper();
        s += QString("    %1_DIR_%2 = %3,\n").arg(prefix.toUpper(), name).arg(i);
    }
    s += "};\n\n";
    s += QString("#define %1_STATE_COUNT %2u\n#define %1_DIRECTION_COUNT %3u\n\n")
        .arg(prefix.toUpper()).arg(m_states.size()).arg(dirs.size());
    s += QString("typedef struct { const uint8_t *frames; uint16_t count; uint16_t ticks; uint8_t loop; uint8_t flip_x; } %1_clip_t;\n")
        .arg(prefix);
    s += QString("typedef struct { uint16_t elapsed, position; uint8_t state, direction, started; } %1_playeranim_t;\n\n")
        .arg(prefix);
    QString arrays;
    QStringList entries;
    int index = 0;
    for (const QString &state : m_states) for (const QString &dir : dirs) {
        const auto found = m_clips.constFind(clipKey(state, dir));
        const Clip *clip = found == m_clips.constEnd() || found->frames.isEmpty() ? nullptr : &found.value();
        bool flip = false;
        if (!clip && m_mirror) {
            QString src;
            if (dir == "Left") src = "Right";
            else if (dir == "UpLeft") src = "UpRight";
            else if (dir == "DownLeft") src = "DownRight";
            if (!src.isEmpty()) {
                const auto inherited = m_clips.constFind(clipKey(state, src));
                if (inherited != m_clips.constEnd() && !inherited->frames.isEmpty()) {
                    clip = &inherited.value(); flip = true;
                }
            }
        }
        if (!clip) {
            entries << "    { 0, 0, 1, 1, 0 },";
        } else {
            const QString name = QString("%1_frames_%2").arg(prefix).arg(index);
            arrays += QString("static const uint8_t %1[] = { ").arg(name);
            for (int f : clip->frames) arrays += QString::number(f) + ", ";
            arrays += "};\n";
            entries << QString("    { %1, %2u, %3u, %4u, %5u },")
                          .arg(name).arg(clip->frames.size()).arg(clip->ticks)
                          .arg(clip->loop ? 1 : 0).arg(flip ? 1 : 0);
        }
        ++index;
    }
    s += arrays + "\n";
    s += QString("static const %1_clip_t %1_clips[%2] = {\n")
         .arg(prefix).arg(entries.size());
    for (const QString &e : entries) s += e + '\n';
    s += "};\n\n";
    s += QString("static inline void %1_step(%1_playeranim_t *a, gfxbob_t *bob,\n"
                 "                           uint8_t state, uint8_t direction, uint16_t frame_step)\n"
                 "{\n"
                 "    const %1_clip_t *clip;\n"
                 "    if (!a || !bob || !bob->imgdat) return;\n"
                 "    if (state >= %2u || direction >= %3u) return;\n"
                 "    clip = &%1_clips[(uint16_t)state * %3u + direction];\n"
                 "    if (!clip->count) {\n"
                 "        state = %4u; /* missing animation: use Idle */\n"
                 "        clip = &%1_clips[(uint16_t)state * %3u + direction];\n"
                 "        if (!clip->count) { direction = 0; clip = &%1_clips[(uint16_t)state * %3u]; }\n"
                 "        if (!clip->count) return;\n"
                 "    }\n"
                 "    if (!a->started || a->state != state || a->direction != direction) {\n"
                 "        a->started = 1; a->state = state; a->direction = direction;\n"
                 "        a->position = 0; a->elapsed = 0;\n"
                 "    } else if (frame_step && (clip->loop || a->position + 1u < clip->count)) {\n"
                 "        uint32_t ticks = (uint32_t)a->elapsed + frame_step;\n"
                 "        uint32_t steps = ticks / clip->ticks;\n"
                 "        a->elapsed = (uint16_t)(ticks %% clip->ticks);\n"
                 "        if (steps) {\n"
                 "            uint32_t next = (uint32_t)a->position + steps;\n"
                 "            a->position = clip->loop ? (uint16_t)(next %% clip->count)\n"
                 "                         : (uint16_t)(next >= clip->count ? clip->count - 1u : next);\n"
                 "        }\n"
                 "    }\n"
                 "    bob->index = clip->frames[a->position];\n"
                 "    bob->flags = (uint8_t)((bob->flags & (uint8_t)~BLIT_FLAG_FLIP_X)\n"
                 "                  | (clip->flip_x ? BLIT_FLAG_FLIP_X : 0));\n"
                 "}\n\n#endif\n")
            .arg(prefix).arg(m_states.size()).arg(dirs.size())
            .arg(qMax(0, m_states.indexOf("Idle")));
    if (m_autoState) {
        // The caller supplies game physics readings; no main.c or physics
        // solver is modified by the IDE. All missing states fall back to Idle.
        const auto named = [this](const QString &n) {
            for (int i = 0; i < m_states.size(); ++i)
                if (m_states.at(i).compare(n, Qt::CaseInsensitive) == 0) return i;
            return 0;
        };
        const int idle = named("Idle"), walking = named("Walk"), running = named("Run");
        const int pushing = named("Push"), jumping = named("Jump"), falling = named("Fall");
        const int sliding = named("Slide"), balancing = named("Balance"), hurt = named("Hurt");
        s.replace("\n#endif\n", "\n");
        s += QString(
            "/* Optional automatic state selection. horizontal=-1/0/+1.\n"
            " * running / pushing / sliding / balancing / hurt are game-provided flags.\n"
            " * Balancing is not detected automatically by the physics helper yet. */\n"
            "static inline uint8_t %1_auto_state(uint8_t on_ground, int32_t vy100,\n"
            "                                      int8_t horizontal, uint8_t is_running,\n"
            "                                      uint8_t is_pushing, uint8_t is_sliding,\n"
            "                                      uint8_t is_balancing, uint8_t is_hurt)\n"
            "{\n"
            "    if (is_hurt) return %10u;\n"
            "    if (!on_ground) return vy100 < 0 ? %7u : %8u;\n"
            "    if (is_pushing) return %6u;\n"
            "    if (is_balancing) return %9u;\n"
            "    if (is_sliding) return %11u;\n"
            "    if (horizontal) return is_running ? %5u : %4u;\n"
            "    return %3u;\n"
            "}\n\n#endif\n")
            .arg(prefix).arg(m_states.size()).arg(idle).arg(walking).arg(running)
            .arg(pushing).arg(jumping).arg(falling).arg(balancing).arg(hurt).arg(sliding);
    }
    s.replace("%%", "%");
    return s;
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
    const QByteArray bytes = generateHeader(prefix).toUtf8();
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
