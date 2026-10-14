#include "gamedesigner.h"
#include "ppbcodec.h"
#include "gamepalette.h"

#include <QCheckBox>
#include <QComboBox>
#include <QDir>
#include <QEvent>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QMimeData>
#include <QUrl>
#include <QAbstractItemView>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QFont>
#include <QFormLayout>
#include <QGraphicsItem>
#include <QApplication>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QImage>
#include <QImageReader>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QMenu>
#include <QAction>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QPixmap>
#include <QPalette>
#include <QPushButton>
#include <QProgressDialog>
#include <QThread>
#include <QTimer>
#include <memory>
#include <QSaveFile>
#include <QScrollArea>
#include <QSettings>
#include <QListView>
#include <QStringList>
#include <QSignalBlocker>
#include <QSpinBox>
#include <QSplitter>
#include <QToolButton>
#include <QTreeWidget>
#include <QTreeWidgetItemIterator>
#include <QSet>
#include <QRegularExpression>
#include <QVBoxLayout>
#include <QUuid>
#include <QtMath>

namespace {
constexpr int LCD_WIDTH = 480;
constexpr int LCD_HEIGHT = 320;
constexpr int MAX_WORLD = 16384; // Editor guard only; NOT a firmware/world-size claim.

class GameScene final : public QGraphicsScene
{
public:
    explicit GameScene(QObject *parent = nullptr) : QGraphicsScene(parent) {}
    bool drawGrid = true;
    QColor gridColour = QColor(88, 105, 125, 65);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override
    {
        QGraphicsScene::drawBackground(painter, rect);
        if (!drawGrid) return;
        const int spacing = 32;
        const int firstX = qFloor(rect.left() / spacing) * spacing;
        const int firstY = qFloor(rect.top() / spacing) * spacing;
        QPen pen(gridColour, 0);
        painter->setPen(pen);
        for (int x = firstX; x <= rect.right(); x += spacing)
            painter->drawLine(QPointF(x, rect.top()), QPointF(x, rect.bottom()));
        for (int y = firstY; y <= rect.bottom(); y += spacing)
            painter->drawLine(QPointF(rect.left(), y), QPointF(rect.right(), y));
    }
};

// QGraphicsPixmapItem can be dragged in the scene. Notify the document after
// the move; never touch another item's data while rebuilding the scene.
class PlacedImage final : public QGraphicsPixmapItem
{
public:
    std::function<void(QGraphicsItem *)> moved;
    std::function<QPointF(const QPointF &)> snapped;
    explicit PlacedImage(const QPixmap &pixmap)
        : QGraphicsPixmapItem(pixmap)
    {
        setFlags(ItemIsSelectable | ItemIsMovable | ItemSendsGeometryChanges);
        setTransformationMode(Qt::FastTransformation); // crisp retro pixels
        setZValue(10);
    }
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override
    {
        if (change == ItemPositionChange && snapped && scene())
            return snapped(value.toPointF());
        const QVariant result = QGraphicsPixmapItem::itemChange(change, value);
        if (change == ItemPositionHasChanged && moved) moved(this);
        return result;
    }
};


// Accept URL drags from the project explorer (and the OS file manager) without
// moving or copying files. Group roots determine the target asset category.
class GameResourceTree final : public QTreeWidget
{
public:
    using QTreeWidget::QTreeWidget;
    std::function<void(const QStringList &, const QString &, const QString &)> filesDropped;
protected:
    void dragEnterEvent(QDragEnterEvent *event) override
    {
        if (event->mimeData()->hasUrls()) event->acceptProposedAction();
        else QTreeWidget::dragEnterEvent(event);
    }
    void dragMoveEvent(QDragMoveEvent *event) override
    {
        if (event->mimeData()->hasUrls()) event->acceptProposedAction();
        else QTreeWidget::dragMoveEvent(event);
    }
    void dropEvent(QDropEvent *event) override
    {
        if (!event->mimeData()->hasUrls()) { QTreeWidget::dropEvent(event); return; }
        QStringList paths;
        for (const QUrl &url : event->mimeData()->urls())
            if (url.isLocalFile() && QFileInfo(url.toLocalFile()).isFile())
                paths.append(QFileInfo(url.toLocalFile()).absoluteFilePath());
        if (paths.isEmpty()) { event->ignore(); return; }
        QTreeWidgetItem *target = itemAt(event->position().toPoint());
        while (target && !target->data(0, Qt::UserRole + 1).isValid())
            target = target->parent();
        const QString kind = target ? target->data(0, Qt::UserRole + 1).toString() : QString();
        const QString plane = target ? target->data(0, Qt::UserRole + 2).toString() : QString();
        // Defer rebuilding: Qt is still using the current tree items during
        // QTreeWidget::dropEvent. Refreshing them synchronously risks a crash.
        const auto callback = filesDropped;
        QTimer::singleShot(0, this, [callback, paths, kind, plane]() {
            if (callback) callback(paths, kind, plane);
        });
        event->setDropAction(Qt::CopyAction); // never move disk files
        event->accept();
    }
};

QString assetKindForFile(const QString &path)
{
    const QString ext = QFileInfo(path).suffix().toLower();
    if (QStringList{QStringLiteral("ppb"),QStringLiteral("png"),QStringLiteral("bmp"),
        QStringLiteral("jpg"),QStringLiteral("jpeg"),QStringLiteral("gif")}.contains(ext))
        return QStringLiteral("sprite");
    if (QStringList{QStringLiteral("pal"),QStringLiteral("act")}.contains(ext))
        return QStringLiteral("palette");
    if (ext == QStringLiteral("wav")) return QStringLiteral("sound");
    if (QStringList{QStringLiteral("mod"),QStringLiteral("med"),QStringLiteral("s3m"),
        QStringLiteral("xm"),QStringLiteral("tfmx"),QStringLiteral("sid"),
        QStringLiteral("sba")}.contains(ext)) return QStringLiteral("music");
    return QString();
}

QString kindTitle(const QString &kind)
{
    if (kind == QStringLiteral("sprite")) return QObject::tr("Sprites");
    if (kind == QStringLiteral("background")) return QObject::tr("Backgrounds");
    if (kind == QStringLiteral("palette")) return QObject::tr("Palettes");
    if (kind == QStringLiteral("sound")) return QObject::tr("Sounds");
    return QObject::tr("Music");
}

bool visualKind(const QString &kind)
{
    return kind == QStringLiteral("sprite") || kind == QStringLiteral("background");
}

QPixmap paletteSwatches(const QVector<QRgb> &table)
{
    QImage image(128, 128, QImage::Format_RGB32);
    image.fill(QColor(45, 50, 60));
    QPainter painter(&image);
    painter.setPen(Qt::NoPen);
    for (int i = 0; i < qMin(256, table.size()); ++i) {
        const QRgb colour = table.at(i);
        painter.setBrush(QColor(qRed(colour), qGreen(colour), qBlue(colour)));
        painter.drawRect((i % 16) * 8, (i / 16) * 8, 8, 8);
    }
    return QPixmap::fromImage(image);
}

QPixmap missingImage(const QString &kind)
{
    QPixmap result(64, 64);
    result.fill(Qt::transparent);
    QPainter p(&result);
    p.fillRect(result.rect(), QColor(55, 62, 82));
    for (int y = 0; y < 64; y += 16)
        for (int x = 0; x < 64; x += 16)
            if ((x / 16 + y / 16) % 2)
                p.fillRect(x, y, 16, 16, QColor(77, 88, 111));
    p.setPen(QPen(QColor(245, 188, 94), 2));
    p.drawRect(1, 1, 61, 61);
    p.setPen(Qt::white);
    p.drawText(result.rect(), Qt::AlignCenter,
               kind == QStringLiteral("background") ? QStringLiteral("BG") : QStringLiteral("SPR"));
    return result;
}
}

SidboxGameDesigner::SidboxGameDesigner(const QString &designFilePath, QWidget *parent)
    : QWidget(parent), m_filePath(QFileInfo(designFilePath).absoluteFilePath())
{
    buildUi();
    if (QFileInfo::exists(m_filePath)) {
        if (!loadDesign()) m_valid = false;
    } else rebuildScene();
    refreshColours();
}

SidboxGameDesigner::~SidboxGameDesigner() = default;
QString SidboxGameDesigner::filePath() const { return m_filePath; }
void SidboxGameDesigner::setFilePath(const QString &path)
{
    // Retarget paths if the designer file moves to a different directory.
    // Existing asset references must keep resolving to the SAME physical files.
    QStringList absoluteResources;
    for (const auto &r : m_resources)
        absoluteResources.append(r.path.isEmpty() ? QString() : resolvedPath(r.path));
    const QString previousDir = QFileInfo(m_filePath).absolutePath();
    m_filePath = QFileInfo(path).absoluteFilePath();
    for (int i = 0; i < m_resources.size(); ++i)
        if (!absoluteResources.at(i).isEmpty())
            m_resources[i].path = storedPath(absoluteResources.at(i));
    if (QFileInfo(m_filePath).absolutePath() != previousDir) setDirty();
    if (tabTitleChanged) tabTitleChanged();
}
QString SidboxGameDesigner::displayName() const
{
    return QFileInfo(m_filePath).fileName() + (m_dirty ? QStringLiteral(" *") : QString());
}
bool SidboxGameDesigner::isModified() const { return m_dirty; }
bool SidboxGameDesigner::isValid() const { return m_valid; }
void SidboxGameDesigner::setDirty(bool value)
{
    if (m_loading || m_dirty == value) return;
    m_dirty = value;
    if (tabTitleChanged) tabTitleChanged();
}

void SidboxGameDesigner::buildUi()
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(3, 3, 3, 3);
    layout->setSpacing(5);
    // Flat rectangular controls, but inherit colours from the active IDE theme.
    setStyleSheet(QStringLiteral(
        "QPushButton, QToolButton, QComboBox, QLineEdit, QSpinBox, "
        "QTreeWidget, QGraphicsView, QFrame, QMenu, QAbstractItemView { border-radius: 0px; } "
        "QComboBox::drop-down { border-radius: 0px; } "
        "QComboBox QAbstractItemView { border-radius: 0px; }"));

    auto *top = new QHBoxLayout;
    auto *caption = new QLabel(tr("Game Designer  |  V1 Gaming"), this);
    QFont titleFont = caption->font();
    titleFont.setBold(true);
    caption->setFont(titleFont);
    top->addWidget(caption);
    top->addSpacing(12);
    top->addWidget(new QLabel(tr("Planes:"), this));
    m_planeMode = new QComboBox(this);
    m_planeMode->addItem(tr("Foreground only"), QStringLiteral("single"));
    m_planeMode->addItem(tr("Foreground + Background"), QStringLiteral("dual"));
    m_planeMode->setToolTip(tr("Controls the SIDBOX graphics model, not the 480×320 viewport."));
    top->addWidget(m_planeMode);
    top->addStretch();
    top->addWidget(new QLabel(tr("World:"), this));
    m_worldWidth = new QSpinBox(this);
    m_worldHeight = new QSpinBox(this);
    for (auto *spin : {m_worldWidth, m_worldHeight}) {
        spin->setRange(LCD_WIDTH, MAX_WORLD);
        spin->setSingleStep(32);
        spin->setMaximumWidth(90);
    }
    m_worldHeight->setMinimum(LCD_HEIGHT);
    m_worldWidth->setValue(960);
    m_worldHeight->setValue(640);
    top->addWidget(m_worldWidth);
    top->addWidget(new QLabel(QStringLiteral("×"), this));
    top->addWidget(m_worldHeight);
    top->addSpacing(12);
    top->addWidget(new QLabel(tr("Camera:"), this));
    m_cameraX = new QSpinBox(this);
    m_cameraY = new QSpinBox(this);
    for (auto *spin : {m_cameraX, m_cameraY}) {
        spin->setRange(0, MAX_WORLD);
        spin->setMaximumWidth(78);
    }
    top->addWidget(m_cameraX);
    top->addWidget(new QLabel(QStringLiteral(","), this));
    top->addWidget(m_cameraY);
    auto *focusCamera = new QPushButton(tr("Centre View on LCD"), this);
    focusCamera->setToolTip(tr("Centre the editor view on the yellow LCD frame. The game camera X/Y do not change."));
    top->addWidget(focusCamera);
    auto *save = new QPushButton(tr("Save Design"), this);
    top->addSpacing(12);
    top->addWidget(save);
    layout->addLayout(top);

    auto *splitter = new QSplitter(Qt::Horizontal, this);
    splitter->setChildrenCollapsible(false);
    layout->addWidget(splitter, 1);

    auto *resourcesPanel = new QWidget(splitter);
    auto *resourcesLayout = new QVBoxLayout(resourcesPanel);
    resourcesLayout->setContentsMargins(4, 4, 4, 4);
    resourcesLayout->addWidget(new QLabel(tr("GAME RESOURCES"), resourcesPanel));
    auto *resourceTree = new GameResourceTree(resourcesPanel);
    m_resourceTree = resourceTree;
    resourceTree->installEventFilter(this);
    resourceTree->viewport()->installEventFilter(this);
    resourceTree->setDragDropMode(QAbstractItemView::DropOnly);
    resourceTree->setDefaultDropAction(Qt::CopyAction);
    resourceTree->setAcceptDrops(true);
    resourceTree->viewport()->setAcceptDrops(true);
    resourceTree->filesDropped = [this](const QStringList &paths, const QString &kind, const QString &plane) {
        importDroppedFiles(paths, kind, plane);
    };
    m_resourceTree->setHeaderHidden(true);
    m_resourceTree->setSelectionMode(QAbstractItemView::SingleSelection);
    resourcesLayout->addWidget(m_resourceTree, 1);
    resourcesLayout->addWidget(new QLabel(tr("Preview foreground CLUT"), resourcesPanel));
    m_frontPalette = new QComboBox(resourcesPanel);
    m_frontPalette->setToolTip(tr("Choose the foreground .pal / indexed PPB used by Forced Preview. "
                                  "Pixel indices in the source images are never changed."));
    auto *frontChoices = new QListView(m_frontPalette);
    frontChoices->setFrameShape(QFrame::NoFrame);
    frontChoices->setStyleSheet(QStringLiteral("QListView { border-radius: 0px; }"));
    m_frontPalette->setView(frontChoices);
    resourcesLayout->addWidget(m_frontPalette);
    resourcesLayout->addWidget(new QLabel(tr("Preview background CLUT"), resourcesPanel));
    m_backPalette = new QComboBox(resourcesPanel);
    m_backPalette->setToolTip(tr("Choose the background .pal / indexed PPB used by Forced Preview. "
                                 "This is independent of the foreground CLUT."));
    auto *backChoices = new QListView(m_backPalette);
    backChoices->setFrameShape(QFrame::NoFrame);
    backChoices->setStyleSheet(QStringLiteral("QListView { border-radius: 0px; }"));
    m_backPalette->setView(backChoices);
    resourcesLayout->addWidget(m_backPalette);
    m_forcePalette = new QCheckBox(tr("Use selected CLUTs for preview (keep indices)"), resourcesPanel);
    m_forcePalette->setToolTip(tr("Indexed PPBs keep their original pixel bytes. Only the preview CLUT changes."));
    resourcesLayout->addWidget(m_forcePalette);
    m_buildPaletteButton = new QPushButton(tr("Build Shared CLUT..."), resourcesPanel);
    m_buildPaletteButton->setToolTip(tr("Generates palette files only in gamepalettes/. "
        "Does not create or modify PPB images or change any resource paths."));
    resourcesLayout->addWidget(m_buildPaletteButton);
    m_resourceTree->setToolTip(tr("Drag files from Project Files here, or right-click a category to add resources."));
    m_resourceTree->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_resourceTree, &QWidget::customContextMenuRequested, this, [this](const QPoint &pos) {
        QTreeWidgetItem *hit = m_resourceTree->itemAt(pos);
        const int resourceIndex = hit ? hit->data(0, Qt::UserRole).toInt() : -1;
        const bool hasResource = hit && hit->data(0, Qt::UserRole).isValid()
            && resourceIndex >= 0 && resourceIndex < m_resources.size();
        QTreeWidgetItem *target = hit;
        while (target && !target->data(0, Qt::UserRole + 1).isValid())
            target = target->parent();
        const QString category = target ? target->data(0, Qt::UserRole + 1).toString() : QString();
        const QString plane = target ? target->data(0, Qt::UserRole + 2).toString() : QString();
        QMenu menu(this);
        QAction *addSprite = menu.addAction(tr("Add Sprite / Atlas..."));
        QAction *addEmpty = menu.addAction(tr("Add Empty Sprite"));
        QAction *addBackground = menu.addAction(tr("Add Background..."));
        QAction *addFrontPalette = menu.addAction(tr("Add Foreground Palette..."));
        QAction *addBackPalette = menu.addAction(tr("Add Background Palette..."));
        QAction *addSound = menu.addAction(tr("Add WAV Sound..."));
        QAction *addMusic = menu.addAction(tr("Add Music..."));
        menu.addSeparator();
        QAction *convertPng = menu.addAction(tr("Convert PNG → PPB..."));
        QAction *buildClut = menu.addAction(tr("Build Shared CLUT..."));
        QAction *useAsPreview = nullptr;
        if (hasResource && m_resources.at(resourceIndex).kind == QStringLiteral("palette")) {
            menu.addSeparator();
            const QString chosenPlane = m_resources.at(resourceIndex).plane;
            useAsPreview = menu.addAction(chosenPlane == QStringLiteral("background")
                ? tr("Use as Background Preview CLUT")
                : tr("Use as Foreground Preview CLUT"));
        }
        QAction *remove = nullptr;
        if (hasResource) {
            menu.addSeparator();
            remove = menu.addAction(tr("Remove Resource (file stays on disk)"));
        }
        // Put the likely action first through default highlighting.
        if (category == QStringLiteral("background")) menu.setDefaultAction(addBackground);
        else if (category == QStringLiteral("sprite")) menu.setDefaultAction(addSprite);
        else if (category == QStringLiteral("palette"))
            menu.setDefaultAction(plane == QStringLiteral("background") ? addBackPalette : addFrontPalette);
        else if (category == QStringLiteral("sound")) menu.setDefaultAction(addSound);
        else if (category == QStringLiteral("music")) menu.setDefaultAction(addMusic);
        QAction *chosen = menu.exec(m_resourceTree->viewport()->mapToGlobal(pos));
        if (!chosen) return;
        if (chosen == addSprite) addResource(QStringLiteral("sprite"));
        else if (chosen == addEmpty) addPlaceholder();
        else if (chosen == addBackground) addResource(QStringLiteral("background"));
        else if (chosen == addFrontPalette) addResource(QStringLiteral("palette"), QStringLiteral("foreground"));
        else if (chosen == addBackPalette) addResource(QStringLiteral("palette"), QStringLiteral("background"));
        else if (chosen == addSound) addResource(QStringLiteral("sound"));
        else if (chosen == addMusic) addResource(QStringLiteral("music"));
        else if (chosen == convertPng) importPngAsPpb();
        else if (chosen == buildClut) buildSharedPalette();
        else if (useAsPreview && chosen == useAsPreview) {
            const Resource &resource = m_resources.at(resourceIndex);
            if (resource.plane == QStringLiteral("background"))
                m_activeBackgroundPalette = resource.id;
            else m_activeForegroundPalette = resource.id;
            {
                QSignalBlocker block(m_forcePalette);
                m_forcePalette->setChecked(true);
            }
            refreshResources();
            refreshPlanePreview();
            setDirty();
        }
        else if (remove) { selectResource(resourceIndex); deleteSelectedResource(); }
    });

    auto *previewPanel = new QWidget(splitter);
    auto *previewLayout = new QVBoxLayout(previewPanel);
    previewLayout->setContentsMargins(0, 4, 0, 0);
    auto *previewControls = new QHBoxLayout;
    previewControls->addWidget(new QLabel(tr("WORLD CANVAS  |  dashed frame = LCD viewport"), previewPanel));
    previewControls->addStretch();
    m_showLabels = new QCheckBox(tr("Asset tags"), previewPanel);
    m_showLabels->setChecked(true);
    previewControls->addWidget(m_showLabels);
    m_grid = new QCheckBox(tr("Grid 32"), previewPanel);
    m_grid->setChecked(true);
    previewControls->addWidget(m_grid);
    m_snap = new QCheckBox(tr("Snap"), previewPanel);
    m_snap->setChecked(true); // New designs default to 4-pixel snapping.
    m_snap->setToolTip(tr("Snap moved sprites/backgrounds to the selected world grid."));
    previewControls->addWidget(m_snap);
    m_snapStep = new QComboBox(previewPanel);
    m_snapStep->addItems({QStringLiteral("4 px"),QStringLiteral("8 px"),
        QStringLiteral("16 px"),QStringLiteral("32 px"),QStringLiteral("64 px")});
    m_snapStep->setCurrentText(QStringLiteral("4 px"));
    previewControls->addWidget(m_snapStep);
    previewControls->addWidget(new QLabel(tr("Zoom:"), previewPanel));
    m_zoom = new QComboBox(previewPanel);
    m_zoom->addItems({QStringLiteral("25%"), QStringLiteral("50%"),
                      QStringLiteral("75%"), QStringLiteral("100%"), QStringLiteral("200%")});
    m_zoom->setCurrentText(QStringLiteral("100%"));
    previewControls->addWidget(m_zoom);
    previewLayout->addLayout(previewControls);
    m_scene = new GameScene(this);
    m_view = new QGraphicsView(m_scene, previewPanel);
    m_view->setDragMode(QGraphicsView::RubberBandDrag);
    m_view->setFocusPolicy(Qt::StrongFocus);
    m_view->installEventFilter(this);
    m_view->viewport()->installEventFilter(this);
    m_view->setRenderHint(QPainter::Antialiasing, false);
    m_view->setRenderHint(QPainter::SmoothPixmapTransform, false);
    m_view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    previewLayout->addWidget(m_view, 1);
    auto *instruction = new QLabel(tr("Drag sprites to position. SPACE + left-drag moves the camera; Delete removes a reference. Ctrl+C/V duplicates sprites; Ctrl+Z/Y undo/redo resource edits. Snap and Lock protect layouts."), previewPanel);
    instruction->setWordWrap(true);
    previewLayout->addWidget(instruction);

    // Audio settings are taller than graphics properties. Keep every control
    // accessible even at smaller screen sizes instead of clipping the bottom.
    auto *propertiesScroll = new QScrollArea(splitter);
    propertiesScroll->setWidgetResizable(true);
    propertiesScroll->setFrameShape(QFrame::NoFrame);
    propertiesScroll->setMinimumWidth(225);
    auto *propertiesPanel = new QWidget(propertiesScroll);
    auto *propertiesLayout = new QVBoxLayout(propertiesPanel);
    propertiesLayout->setContentsMargins(5, 4, 5, 4);
    propertiesLayout->addWidget(new QLabel(tr("RESOURCE PROPERTIES"), propertiesPanel));
    auto *form = new QFormLayout;
    m_propertiesForm = form;
    m_propName = new QLineEdit(propertiesPanel);
    m_propFile = new QLabel(propertiesPanel);
    m_propFile->setWordWrap(true);
    m_propFile->setTextInteractionFlags(Qt::TextSelectableByMouse);
    m_propX = new QSpinBox(propertiesPanel);
    m_propY = new QSpinBox(propertiesPanel);
    for (auto *spin : {m_propX, m_propY}) spin->setRange(-MAX_WORLD, MAX_WORLD);
    m_propScale = new QSpinBox(propertiesPanel);
    m_propScale->setRange(1, 800);
    m_propScale->setSuffix(QStringLiteral("%"));
    m_propCellWidth = new QSpinBox(propertiesPanel);
    m_propCellHeight = new QSpinBox(propertiesPanel);
    for (auto *spin : {m_propCellWidth, m_propCellHeight}) {
        spin->setRange(0, 16384);
        spin->setSpecialValueText(tr("Full atlas"));
    }
    m_propFrame = new QSpinBox(propertiesPanel);
    m_propFrame->setRange(0, 0);
    m_propLocked = new QCheckBox(tr("Lock position (no dragging)"), propertiesPanel);
    m_propPlane = new QComboBox(propertiesPanel);
    m_propPlane->addItem(tr("Foreground"), QStringLiteral("foreground"));
    m_propPlane->addItem(tr("Background"), QStringLiteral("background"));
    m_imageInfo = new QLabel(propertiesPanel);
    m_imageInfo->setWordWrap(true);
    form->addRow(tr("Name"), m_propName);
    form->addRow(tr("Plane / palette bank"), m_propPlane);
    form->addRow(tr("File"), m_propFile);
    form->addRow(tr("X"), m_propX);
    form->addRow(tr("Y"), m_propY);
    form->addRow(tr("Scale"), m_propScale);
    form->addRow(tr("Cell width"), m_propCellWidth);
    form->addRow(tr("Cell height"), m_propCellHeight);
    form->addRow(tr("Frame"), m_propFrame);
    form->addRow(QString(), m_propLocked);
    propertiesLayout->addLayout(form);
    propertiesLayout->addWidget(m_imageInfo);
    m_palettePreview = new QLabel(propertiesPanel);
    m_palettePreview->setFixedSize(128, 128);
    m_palettePreview->setToolTip(tr("Indexed colour palette: 16 × 16 entries, index 0 top-left"));
    m_palettePreview->hide();
    propertiesLayout->addWidget(m_palettePreview, 0, Qt::AlignLeft);
    m_audioPanel = new SidboxGameAudioPanel(propertiesPanel);
    propertiesLayout->addWidget(m_audioPanel);
    m_audioPanel->settingsChanged = [this](const SidboxAudioSettings &settings) {
        const int index = selectedIndex();
        if (index < 0 || m_loading) return;
        Resource &r = m_resources[index];
        if (r.kind != QStringLiteral("sound") && r.kind != QStringLiteral("music")) return;
        rememberResourceEdit();
        r.audio = settings;
        setDirty();
    };
    auto *changeFile = new QPushButton(tr("Change File..."), propertiesPanel);
    propertiesLayout->addWidget(changeFile);
    auto *exportC = new QPushButton(tr("Export Embedded C..."), propertiesPanel);
    m_exportCButton = exportC;
    propertiesLayout->addWidget(exportC);
    m_deleteButton = new QPushButton(tr("Remove Resource"), propertiesPanel);
    propertiesLayout->addWidget(m_deleteButton);
    auto *limitations = new QLabel(tr("Embedded graphics export is optional. Audio settings are saved in the design; generated gamecode/ files are planned for Stage 55."), propertiesPanel);
    limitations->setWordWrap(true);
    propertiesLayout->addWidget(limitations);
    propertiesLayout->addStretch();
    splitter->addWidget(resourcesPanel);
    splitter->addWidget(previewPanel);
    // QScrollArea requires its child layout to exist before setWidget().
    propertiesScroll->setWidget(propertiesPanel);
    splitter->addWidget(propertiesScroll);
    splitter->setStretchFactor(0, 0);
    splitter->setStretchFactor(1, 1);
    splitter->setStretchFactor(2, 0);
    splitter->setSizes({195, 670, 265});
    // Save the splitter's geometry as a user preference (not in the game file).
    // One shared layout across Game Designer tabs; restore AFTER layouts run.
    QTimer::singleShot(0, splitter, [splitter]() {
        QSettings settings(QStringLiteral("Sidbox"), QStringLiteral("SidboxIDE"));
        const QByteArray saved = settings.value(QStringLiteral("GameDesigner/mainSplitterState")).toByteArray();
        if (!saved.isEmpty()) splitter->restoreState(saved);
    });
    connect(splitter, &QSplitter::splitterMoved, this, [splitter](int, int) {
        QSettings settings(QStringLiteral("Sidbox"), QStringLiteral("SidboxIDE"));
        settings.setValue(QStringLiteral("GameDesigner/mainSplitterState"), splitter->saveState());
    });

    connect(save, &QPushButton::clicked, this, [this]() { saveDesign(); });
    connect(m_showLabels, &QCheckBox::toggled, this, [this](bool visible) {
        for (auto *item : m_sceneItems)
            if (item)
                for (auto *child : item->childItems())
                    if (auto *text = dynamic_cast<QGraphicsSimpleTextItem *>(child)) text->setVisible(visible);
        setDirty();
    });
    connect(m_planeMode, qOverload<int>(&QComboBox::currentIndexChanged), this, [this](int) {
        m_backPalette->setEnabled(m_planeMode->currentIndex() == 1);
        refreshPlanePreview(); setDirty();
    });
    for (QComboBox *combo : {m_frontPalette, m_backPalette}) {
        connect(combo, qOverload<int>(&QComboBox::currentIndexChanged), this, [this, combo](int) {
            if (m_loading) return;
            if (combo == m_frontPalette) m_activeForegroundPalette = combo->currentData().toString();
            else m_activeBackgroundPalette = combo->currentData().toString();
            refreshResources();
            refreshPlanePreview(); setDirty();
        });
    }
    connect(m_forcePalette, &QCheckBox::toggled, this, [this](bool) {
        refreshPlanePreview(); setDirty();
    });
    connect(m_buildPaletteButton, &QPushButton::clicked, this, [this]() { buildSharedPalette(); });
    connect(m_propPlane, qOverload<int>(&QComboBox::currentIndexChanged), this, [this](int) {
        if (m_loading) return;
        const int index = selectedIndex();
        if (index < 0) return;
        const QString plane = m_propPlane->currentData().toString();
        if (m_resources[index].plane == plane) return;
        rememberResourceEdit();
        m_resources[index].plane = plane;
        refreshResources(); selectResource(index);
        refreshPlanePreview(); setDirty();
    });
    connect(focusCamera, &QPushButton::clicked, this, [this]() {
        m_view->centerOn(m_cameraX->value() + LCD_WIDTH / 2,
                         m_cameraY->value() + LCD_HEIGHT / 2);
    });
    connect(exportC, &QPushButton::clicked, this, [this]() { exportSelectedC(); });
    connect(m_deleteButton, &QPushButton::clicked, this, [this]() { deleteSelectedResource(); });
    connect(m_propLocked, &QCheckBox::toggled, this, [this](bool locked) {
        const int index = selectedIndex();
        if (index < 0 || m_loading || !visualKind(m_resources[index].kind)) return;
        rememberResourceEdit();
        m_resources[index].locked = locked;
        if (index < m_sceneItems.size() && m_sceneItems[index])
            m_sceneItems[index]->setFlag(QGraphicsItem::ItemIsMovable, !locked);
        setDirty();
        refreshProperties();
    });
    connect(m_snap, &QCheckBox::toggled, this, [this](bool) { setDirty(); });
    connect(m_snapStep, &QComboBox::currentTextChanged, this, [this](const QString &) { setDirty(); });
    connect(changeFile, &QPushButton::clicked, this, [this]() { pickResourceFile(); });
    connect(m_worldWidth, qOverload<int>(&QSpinBox::valueChanged), this, [this](int) {
        refreshFrame(); setDirty();
    });
    connect(m_worldHeight, qOverload<int>(&QSpinBox::valueChanged), this, [this](int) {
        refreshFrame(); setDirty();
    });
    connect(m_cameraX, qOverload<int>(&QSpinBox::valueChanged), this, [this](int) {
        refreshFrame(); setDirty();
    });
    connect(m_cameraY, qOverload<int>(&QSpinBox::valueChanged), this, [this](int) {
        refreshFrame(); setDirty();
    });
    connect(m_grid, &QCheckBox::toggled, this, [this](bool checked) {
        static_cast<GameScene *>(m_scene)->drawGrid = checked;
        m_scene->update();
    });
    connect(m_zoom, &QComboBox::currentTextChanged, this, [this](const QString &value) {
        bool ok = false;
        const int percent = value.left(value.size() - 1).toInt(&ok);
        if (ok) {
            m_view->resetTransform();
            m_view->scale(percent / 100.0, percent / 100.0);
        }
    });
    // Initial 100%: one world pixel = one screen pixel.
    m_view->resetTransform();
    connect(m_resourceTree, &QTreeWidget::itemSelectionChanged, this, [this]() {
        if (m_syncSelection) return;
        QTreeWidgetItem *item = m_resourceTree->currentItem();
        if (!item || !item->data(0, Qt::UserRole).isValid()) return;
        const int index = item->data(0, Qt::UserRole).toInt();
        if (index >= 0 && index < m_sceneItems.size() && m_sceneItems.at(index)) {
            m_syncSelection = true;
            m_scene->clearSelection();
            m_sceneItems.at(index)->setSelected(true);
            m_syncSelection = false;
        }
        refreshProperties();
    });
    connect(m_scene, &QGraphicsScene::selectionChanged, this, [this]() {
        if (m_syncSelection) return;
        const QList<QGraphicsItem *> selected = m_scene->selectedItems();
        if (!selected.isEmpty()) selectResource(selected.first()->data(0).toInt());
    });
    connect(m_propName, &QLineEdit::textEdited, this, [this](const QString &text) {
        const int index = selectedIndex();
        if (index < 0) return;
        rememberResourceEdit();
        m_resources[index].name = text;
        if (auto *item = m_resourceTree->currentItem()) item->setText(0, text);
        if (index < m_sceneItems.size() && m_sceneItems.at(index)) {
            for (auto *child : m_sceneItems.at(index)->childItems())
                if (auto *label = dynamic_cast<QGraphicsSimpleTextItem *>(child))
                    label->setText(text);
        }
        // Keep the cursor position while the developer edits the name.
        setDirty();
    });
    for (QSpinBox *spin : {m_propX, m_propY, m_propScale}) {
        connect(spin, qOverload<int>(&QSpinBox::valueChanged), this, [this](int) {
            const int index = selectedIndex();
            if (index < 0 || m_loading) return;
            rememberResourceEdit();
            auto &r = m_resources[index];
            r.x = m_propX->value(); r.y = m_propY->value(); r.scale = m_propScale->value();
            updateSelectedItem();
            setDirty();
        });
    }
    for (QSpinBox *spin : {m_propCellWidth, m_propCellHeight, m_propFrame}) {
        connect(spin, qOverload<int>(&QSpinBox::valueChanged), this, [this](int) {
            const int index = selectedIndex();
            if (index < 0 || m_loading) return;
            rememberResourceEdit();
            auto &r = m_resources[index];
            r.cellWidth = m_propCellWidth->value();
            r.cellHeight = m_propCellHeight->value();
            r.frame = m_propFrame->value();
            updateSelectedPixmap();
            setDirty();
            refreshProperties();
        });
    }
    refreshResources();
    refreshProperties();
}

QString SidboxGameDesigner::resolvedPath(const QString &path) const
{
    if (path.isEmpty()) return {};
    return QFileInfo(QDir(QFileInfo(m_filePath).absolutePath()).filePath(path)).absoluteFilePath();
}
QString SidboxGameDesigner::storedPath(const QString &path) const
{
    return QDir(QFileInfo(m_filePath).absolutePath()).relativeFilePath(QFileInfo(path).absoluteFilePath());
}

int SidboxGameDesigner::selectedIndex() const
{
    if (!m_resourceTree || !m_resourceTree->currentItem()) return -1;
    const QVariant value = m_resourceTree->currentItem()->data(0, Qt::UserRole);
    if (!value.isValid()) return -1;
    const int index = value.toInt();
    return index >= 0 && index < m_resources.size() ? index : -1;
}

void SidboxGameDesigner::selectResource(int index)
{
    if (index < 0 || index >= m_resources.size()) return;
    m_syncSelection = true;
    for (QTreeWidgetItemIterator iterator(m_resourceTree); *iterator; ++iterator) {
        auto *child = *iterator;
        const QVariant value = child->data(0, Qt::UserRole);
        if (value.isValid() && value.toInt() == index) {
            m_resourceTree->setCurrentItem(child);
            break;
        }
    }
    m_scene->clearSelection();
    if (index < m_sceneItems.size() && m_sceneItems.at(index))
        m_sceneItems.at(index)->setSelected(true);
    m_syncSelection = false;
    refreshProperties();
}

QString SidboxGameDesigner::resourcePlane(const Resource &resource) const
{
    if (m_planeMode->currentIndex() == 0) return QStringLiteral("foreground");
    return resource.plane == QStringLiteral("background")
        ? QStringLiteral("background") : QStringLiteral("foreground");
}

QVector<QRgb> SidboxGameDesigner::activePalette(const QString &plane) const
{
    if (plane == QStringLiteral("background") && m_planeMode->currentIndex() == 0)
        return {};
    const QString id = plane == QStringLiteral("background")
        ? m_activeBackgroundPalette : m_activeForegroundPalette;
    if (id.isEmpty()) return {};
    for (const Resource &r : m_resources) {
        if (r.kind != QStringLiteral("palette") || r.id != id || r.plane != plane) continue;
        const QString absolute = resolvedPath(r.path);
        const QFileInfo info(absolute);
        if (!info.isFile()) return {};
        const QString key = absolute + QLatin1Char('|') + plane;
        const auto found = m_paletteCache.constFind(key);
        if (found != m_paletteCache.constEnd()
            && found->modified == info.lastModified() && found->diskSize == info.size())
            return found->colours;
        const QVector<QRgb> bank = SidboxGamePalette::readPalette(
            absolute, plane == QStringLiteral("background"));
        if (m_paletteCache.size() > 32) m_paletteCache.clear();
        m_paletteCache.insert(key, CachedPalette{bank, info.lastModified(), info.size()});
        return bank;
    }
    return {};
}

void SidboxGameDesigner::refreshPaletteSelectors()
{
    QSignalBlocker blockFront(m_frontPalette), blockBack(m_backPalette);
    for (auto *combo : {m_frontPalette, m_backPalette}) {
        combo->clear();
        combo->addItem(tr("None — individual PPB palettes"), QString());
    }
    for (const Resource &r : m_resources) {
        if (r.kind != QStringLiteral("palette")) continue;
        QComboBox *target = r.plane == QStringLiteral("background") ? m_backPalette : m_frontPalette;
        const QString sourceName = QFileInfo(r.path).fileName();
        target->addItem(sourceName.isEmpty() || sourceName == r.name
                            ? r.name : tr("%1  (%2)").arg(r.name, sourceName), r.id);
        target->setItemData(target->count() - 1, resolvedPath(r.path), Qt::ToolTipRole);
    }
    auto selectId = [](QComboBox *combo, QString &id) {
        const int found = combo->findData(id);
        if (found >= 0) combo->setCurrentIndex(found);
        else { id.clear(); combo->setCurrentIndex(0); }
    };
    selectId(m_frontPalette, m_activeForegroundPalette);
    selectId(m_backPalette, m_activeBackgroundPalette);
    m_backPalette->setEnabled(m_planeMode->currentIndex() == 1);
}

void SidboxGameDesigner::refreshPlanePreview()
{
    if (m_loading || !m_scene) return;
    const int index = selectedIndex();
    rebuildScene();
    if (index >= 0) selectResource(index);
    else refreshProperties();
}

void SidboxGameDesigner::refreshResources()
{
    const int preserve = selectedIndex();
    QSignalBlocker block(m_resourceTree);
    m_resourceTree->clear();
    for (const QString &kind : {QStringLiteral("sprite"), QStringLiteral("background"),
                                 QStringLiteral("palette"), QStringLiteral("sound"), QStringLiteral("music")}) {
        auto *root = new QTreeWidgetItem(m_resourceTree, QStringList{kindTitle(kind)});
        root->setFlags(root->flags() & ~Qt::ItemIsSelectable);
        root->setData(0, Qt::UserRole + 1, kind);
        QTreeWidgetItem *frontRoot = nullptr;
        QTreeWidgetItem *backRoot = nullptr;
        if (kind == QStringLiteral("palette")) {
            frontRoot = new QTreeWidgetItem(root, QStringList{tr("Foreground")});
            frontRoot->setFlags(frontRoot->flags() & ~Qt::ItemIsSelectable);
            frontRoot->setData(0, Qt::UserRole + 1, kind);
            frontRoot->setData(0, Qt::UserRole + 2, QStringLiteral("foreground"));
            backRoot = new QTreeWidgetItem(root, QStringList{tr("Background")});
            backRoot->setFlags(backRoot->flags() & ~Qt::ItemIsSelectable);
            backRoot->setData(0, Qt::UserRole + 1, kind);
            backRoot->setData(0, Qt::UserRole + 2, QStringLiteral("background"));
            frontRoot->setExpanded(true);
            backRoot->setExpanded(true);
        }
        for (int index = 0; index < m_resources.size(); ++index) {
            const Resource &r = m_resources.at(index);
            if (r.kind != kind) continue;
            QTreeWidgetItem *parent = kind == QStringLiteral("palette")
                ? (r.plane == QStringLiteral("background") ? backRoot : frontRoot) : root;
            const bool isActiveClut = kind == QStringLiteral("palette") &&
                (r.plane == QStringLiteral("background")
                     ? r.id == m_activeBackgroundPalette
                     : r.id == m_activeForegroundPalette);
            auto *child = new QTreeWidgetItem(parent, QStringList{
                isActiveClut ? tr("%1  [preview]").arg(r.name) : r.name});
            child->setData(0, Qt::UserRole, index);
            child->setToolTip(0, r.path);
            child->setData(0, Qt::UserRole + 1, kind);
            child->setData(0, Qt::UserRole + 2, r.plane);
        }
        if (kind == QStringLiteral("music")) {
            qint64 largest = 0;
            int count = 0;
            for (const Resource &r : m_resources) {
                if (r.kind != kind) continue;
                const QFileInfo info(resolvedPath(r.path));
                if (!info.isFile()) continue;
                largest = qMax(largest, info.size());
                ++count;
            }
            root->setText(0, tr("Music (%1; largest %2 KiB)")
                .arg(count).arg((largest + 1023) / 1024));
            root->setToolTip(0, tr("Project Settings → MOD size can reserve space for the largest module."));
        }
        root->setExpanded(true);
    }
    refreshPaletteSelectors();
    if (preserve >= 0 && preserve < m_resources.size()) selectResource(preserve);
}

QImage SidboxGameDesigner::cachedImage(const QString &path, QString *error) const
{
    if (path.isEmpty()) { if (error) *error = tr("No image file selected"); return {}; }
    const QFileInfo info(path);
    if (!info.isFile()) { if (error) *error = tr("Image file not found"); return {}; }
    const auto found = m_imageCache.constFind(path);
    if (found != m_imageCache.constEnd()
        && found->diskSize == info.size() && found->modified == info.lastModified()) {
        // Reused immutable Qt image data: no disk read, PPB parsing or PNG decode.
        return found->image;
    }
    if (found != m_imageCache.constEnd()) {
        m_imageCacheBytes -= found->memoryBytes;
        m_imageCache.remove(path);
        m_imageCacheOrder.removeAll(path);
    }
    QImage image;
    if (info.suffix().compare(QStringLiteral("ppb"), Qt::CaseInsensitive) == 0) {
        SidboxPpb::Picture ppb;
        QString loadError;
        if (!SidboxPpb::read(path, &ppb, &loadError)) {
            if (error) *error = tr("PPB: %1").arg(loadError);
            return {};
        }
        image = ppb.indexed;
    } else {
        QImageReader reader(path);
        reader.setAutoTransform(true);
        image = reader.read();
        if (image.isNull()) {
            if (error) *error = tr("Cannot preview: %1").arg(reader.errorString());
            return {};
        }
    }
    constexpr qint64 MaxCacheBytes = 64LL * 1024 * 1024;
    const qint64 bytes = qint64(image.sizeInBytes());
    if (bytes <= MaxCacheBytes) {
        while (!m_imageCacheOrder.isEmpty()
               && (m_imageCacheBytes + bytes > MaxCacheBytes || m_imageCache.size() >= 32)) {
            const QString oldest = m_imageCacheOrder.takeFirst();
            const auto existing = m_imageCache.constFind(oldest);
            if (existing != m_imageCache.constEnd()) {
                m_imageCacheBytes -= existing->memoryBytes;
                m_imageCache.remove(oldest);
            }
        }
        m_imageCache.insert(path, CachedImage{image, info.lastModified(), info.size(), bytes});
        m_imageCacheOrder.append(path);
        m_imageCacheBytes += bytes;
    }
    return image;
}

QImage SidboxGameDesigner::resourcePreview(const Resource &r, QString *details) const
{
    QString error;
    const QImage source = cachedImage(resolvedPath(r.path), &error);
    if (source.isNull()) { if (details) *details = error; return {}; }
    const int cw = r.cellWidth > 0 ? qMin(r.cellWidth, source.width()) : source.width();
    const int ch = r.cellHeight > 0 ? qMin(r.cellHeight, source.height()) : source.height();
    const int cols = qMax(1, source.width() / cw);
    const int rows = qMax(1, source.height() / ch);
    const int frames = cols * rows;
    const int frame = qBound(0, r.frame, frames - 1);
    if (details) {
        *details = tr("%1 × %2 pixels  |  %3 frame(s)  |  %4 bytes indexed")
                       .arg(source.width()).arg(source.height()).arg(frames)
                       .arg(qint64(source.width()) * source.height());
    }
    QImage frameImage = source.copy((frame % cols) * cw, (frame / cols) * ch, cw, ch);
    // FORCE = replace lookup table ONLY. Absolutely no pixel-index remapping.
    if (m_forcePalette && m_forcePalette->isChecked()
        && frameImage.format() == QImage::Format_Indexed8) {
        const QVector<QRgb> bank = activePalette(resourcePlane(r));
        if (bank.size() == 256) frameImage.setColorTable(bank);
    }
    return frameImage;
}

void SidboxGameDesigner::rebuildScene()
{
    m_loading = true;
    m_scene->clear();
    m_sceneItems.clear();
    m_sceneItems.resize(m_resources.size());
    m_worldFrame = nullptr;
    m_cameraFrame = nullptr;
    m_scene->setSceneRect(0, 0, m_worldWidth->value(), m_worldHeight->value());
    m_worldFrame = m_scene->addRect(m_scene->sceneRect().adjusted(0, 0, -1, -1),
                                     QPen(QColor(130, 160, 194), 2));
    m_worldFrame->setZValue(10000);
    m_worldFrame->setAcceptedMouseButtons(Qt::NoButton);

    for (int i = 0; i < m_resources.size(); ++i) {
        const Resource &r = m_resources.at(i);
        if (!visualKind(r.kind)) continue;
        const QImage preview = resourcePreview(r);
        const QPixmap pixmap = preview.isNull() ? missingImage(r.kind)
                                                 : QPixmap::fromImage(preview);
        auto *item = new PlacedImage(pixmap);
        item->setData(0, i);
        item->setFlag(QGraphicsItem::ItemIsMovable, !r.locked);
        item->snapped = [this, i](const QPointF &p) -> QPointF {
            if (m_loading || !m_snap->isChecked() || m_resources.at(i).locked) return p;
            const int step = m_snapStep->currentText().section(QLatin1Char(' '), 0, 0).toInt();
            if (step <= 0) return p;
            return QPointF(qRound(p.x() / step) * step, qRound(p.y() / step) * step);
        };
        item->setPos(r.x, r.y);
        item->setScale(r.scale / 100.0);
        if (r.kind == QStringLiteral("background")) item->setZValue(1);
        item->moved = [this](QGraphicsItem *which) { syncFromSceneItem(which); };
        m_scene->addItem(item);
        auto *title = new QGraphicsSimpleTextItem(r.name, item);
        title->setBrush(QColor(255, 241, 160));
        title->setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
        title->setPos(0, -18);
        title->setVisible(m_showLabels->isChecked());
        title->setAcceptedMouseButtons(Qt::NoButton);
        m_sceneItems[i] = item;
    }
    m_cameraFrame = m_scene->addRect(QRectF(0, 0, LCD_WIDTH, LCD_HEIGHT),
                 QPen(QColor(255, 207, 75), 2, Qt::DashLine));
    m_cameraFrame->setZValue(10001);
    m_cameraFrame->setAcceptedMouseButtons(Qt::NoButton);
    auto *lcdLabel = new QGraphicsSimpleTextItem(QStringLiteral("LCD 480 × 320"), m_cameraFrame);
    lcdLabel->setBrush(QColor(255, 207, 75));
    lcdLabel->setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
    lcdLabel->setPos(3, 3);
    lcdLabel->setAcceptedMouseButtons(Qt::NoButton);
    refreshFrame();
    m_loading = false;
}

void SidboxGameDesigner::refreshFrame()
{
    if (!m_scene) return;
    const int width = m_worldWidth->value();
    const int height = m_worldHeight->value();
    m_cameraX->setMaximum(qMax(0, width - LCD_WIDTH));
    m_cameraY->setMaximum(qMax(0, height - LCD_HEIGHT));
    m_scene->setSceneRect(0, 0, width, height);
    if (m_worldFrame) m_worldFrame->setRect(0, 0, width - 1, height - 1);
    if (m_cameraFrame) m_cameraFrame->setPos(m_cameraX->value(), m_cameraY->value());
}

void SidboxGameDesigner::syncFromSceneItem(QGraphicsItem *item)
{
    if (m_loading || !item) return;
    const int index = item->data(0).toInt();
    if (index < 0 || index >= m_resources.size()) return;
    if (m_resources[index].locked) return;
    m_resources[index].x = qRound(item->pos().x());
    m_resources[index].y = qRound(item->pos().y());
    setDirty();
    if (selectedIndex() == index) refreshProperties();
}

void SidboxGameDesigner::updateSelectedItem()
{
    const int index = selectedIndex();
    if (index < 0 || index >= m_sceneItems.size()) return;
    auto *item = m_sceneItems.at(index);
    if (!item) return;
    const Resource &r = m_resources.at(index);
    m_loading = true;
    item->setPos(r.x, r.y);
    item->setScale(r.scale / 100.0);
    m_loading = false;
}

void SidboxGameDesigner::updateSelectedPixmap()
{
    const int index = selectedIndex();
    if (index < 0 || index >= m_sceneItems.size() || !m_sceneItems.at(index)) return;
    auto *item = dynamic_cast<QGraphicsPixmapItem *>(m_sceneItems.at(index));
    if (!item) return;
    const QImage preview = resourcePreview(m_resources.at(index));
    item->setPixmap(preview.isNull() ? missingImage(m_resources.at(index).kind)
                                     : QPixmap::fromImage(preview));
}

void SidboxGameDesigner::refreshProperties()
{
    const int index = selectedIndex();
    const bool enabled = index >= 0;
    // Hide graphics-only properties for palettes/audio; disabled grey rows
    // would waste most of the audio editor's limited horizontal space.
    const bool visualSelection = enabled && visualKind(m_resources.at(index).kind);
    for (QWidget *field : {static_cast<QWidget *>(m_propX), static_cast<QWidget *>(m_propY),
                           static_cast<QWidget *>(m_propScale), static_cast<QWidget *>(m_propCellWidth),
                           static_cast<QWidget *>(m_propCellHeight), static_cast<QWidget *>(m_propFrame)}) {
        field->setVisible(visualSelection);
        if (QWidget *label = m_propertiesForm->labelForField(field)) label->setVisible(visualSelection);
    }
    m_exportCButton->setVisible(visualSelection);
    m_propPlane->setVisible(enabled && (visualSelection || m_resources.at(index).kind == QStringLiteral("palette")));
    if (QWidget *label = m_propertiesForm->labelForField(m_propPlane)) label->setVisible(m_propPlane->isVisible());
    m_propLocked->setVisible(visualSelection);
    if (QWidget *label = m_propertiesForm->labelForField(m_propLocked))
        label->setVisible(visualSelection);
    for (QWidget *widget : {static_cast<QWidget *>(m_propName), static_cast<QWidget *>(m_propX),
                            static_cast<QWidget *>(m_propY), static_cast<QWidget *>(m_propScale),
                            static_cast<QWidget *>(m_propCellWidth), static_cast<QWidget *>(m_propCellHeight),
                            static_cast<QWidget *>(m_propFrame), static_cast<QWidget *>(m_deleteButton)})
        widget->setEnabled(enabled);
    QSignalBlocker block1(m_propName), block2(m_propX), block3(m_propY), block4(m_propScale);
    QSignalBlocker block5(m_propCellWidth), block6(m_propCellHeight), block7(m_propFrame);
    QSignalBlocker block8(m_propLocked), block9(m_propPlane);
    if (!enabled) {
        m_propName->clear(); m_propFile->clear(); m_imageInfo->clear(); m_palettePreview->hide();
        m_audioPanel->clearAudio();
        m_exportCButton->setEnabled(false);
        m_propX->setValue(0); m_propY->setValue(0); m_propScale->setValue(100);
        m_propCellWidth->setValue(0); m_propCellHeight->setValue(0);
        m_propFrame->setRange(0, 0);
        m_propLocked->setChecked(false);
        return;
    }
    const Resource &r = m_resources.at(index);
    if (r.kind == QStringLiteral("sound") || r.kind == QStringLiteral("music"))
        m_audioPanel->showAudio(r.kind, resolvedPath(r.path), r.audio);
    else m_audioPanel->clearAudio();
    m_palettePreview->hide();
    if (r.kind == QStringLiteral("palette")) {
        QString error;
        const QVector<QRgb> bank = SidboxGamePalette::readPalette(
            resolvedPath(r.path), r.plane == QStringLiteral("background"), &error);
        if (!bank.isEmpty()) {
            m_palettePreview->setPixmap(paletteSwatches(bank));
            m_palettePreview->show();
            m_imageInfo->setText(tr("%1 CLUT: 256 indexed entries (preview only)")
                .arg(r.plane == QStringLiteral("background") ? tr("Background") : tr("Foreground")));
        } else m_imageInfo->setText(error);
    }
    m_propName->setText(r.name);
    m_propPlane->setCurrentIndex(r.plane == QStringLiteral("background") ? 1 : 0);
    m_propPlane->setEnabled(m_planeMode->currentIndex() == 1 || r.kind == QStringLiteral("palette"));
    m_propLocked->setChecked(r.locked);
    m_propLocked->setEnabled(visualSelection);
    m_propFile->setText(r.path.isEmpty() ? tr("(placeholder)") : r.path);
    m_propX->setValue(r.x);
    m_propY->setValue(r.y);
    m_propScale->setValue(r.scale);
    m_propCellWidth->setValue(r.cellWidth);
    m_propCellHeight->setValue(r.cellHeight);
    const bool visual = visualKind(r.kind);
    m_exportCButton->setEnabled(visual);
    for (QSpinBox *spin : {m_propX, m_propY})
        spin->setEnabled(visual && !r.locked);
    for (QSpinBox *spin : {m_propScale, m_propCellWidth, m_propCellHeight, m_propFrame})
        spin->setEnabled(visual);
    if (!visual) {
        m_propFrame->setRange(0, 0);
        if (r.kind != QStringLiteral("palette")) m_imageInfo->clear();
        return;
    }
    const QImage image = cachedImage(resolvedPath(r.path));
    const QVector<QRgb> shownPalette = m_forcePalette->isChecked()
        && image.format() == QImage::Format_Indexed8
        ? activePalette(resourcePlane(r)) : QVector<QRgb>();
    if (!image.isNull() && (!shownPalette.isEmpty() || !image.colorTable().isEmpty())) {
        m_palettePreview->setPixmap(paletteSwatches(shownPalette.isEmpty()
            ? image.colorTable() : shownPalette));
        m_palettePreview->show();
    }
    if (image.isNull()) {
        m_propFrame->setRange(0, 0);
        m_imageInfo->setText(r.path.isEmpty() ? tr("Placeholder sprite") : tr("Image not available"));
        return;
    }
    const int cw = r.cellWidth > 0 ? qMin(r.cellWidth, image.width()) : image.width();
    const int ch = r.cellHeight > 0 ? qMin(r.cellHeight, image.height()) : image.height();
    const int frames = qMax(1, image.width() / cw) * qMax(1, image.height() / ch);
    m_propFrame->setRange(0, frames - 1);
    m_propFrame->setValue(qMin(r.frame, frames - 1));
    m_imageInfo->setText(tr("Atlas: %1 × %2  |  %3 frames  |  Index 0 = foreground transparency%4")
        .arg(image.width()).arg(image.height()).arg(frames)
        .arg(!shownPalette.isEmpty() ? tr("  |  Forced %1 CLUT (indices unchanged)")
                .arg(resourcePlane(r))
            : (m_forcePalette->isChecked() && image.format() != QImage::Format_Indexed8
                ? tr("  |  Convert to PPB to use indexed palettes") : QString())));
}

// A bounded, lightweight history of RESOURCE METADATA, not images or files.
// This intentionally leaves world dimensions and camera navigation out of the
// history until those settings get their own transaction model.
void SidboxGameDesigner::rememberResourceEdit()
{
    if (m_loading) return;
    if (m_undoResources.size() >= 64) m_undoResources.removeFirst();
    m_undoResources.append(m_resources);
    m_redoResources.clear();
}

void SidboxGameDesigner::restoreResourceSnapshot(const QVector<Resource> &snapshot)
{
    const int previousIndex = selectedIndex();
    m_resources = snapshot;
    rebuildScene();
    refreshResources();
    if (previousIndex >= 0 && previousIndex < m_resources.size())
        selectResource(previousIndex);
    else {
        m_resourceTree->clearSelection();
        m_resourceTree->setCurrentItem(nullptr);
        refreshProperties();
    }
    setDirty();
}

void SidboxGameDesigner::undoResourceEdit()
{
    if (m_undoResources.isEmpty()) return;
    if (m_redoResources.size() >= 64) m_redoResources.removeFirst();
    m_redoResources.append(m_resources);
    const QVector<Resource> snapshot = m_undoResources.takeLast();
    restoreResourceSnapshot(snapshot);
}

void SidboxGameDesigner::redoResourceEdit()
{
    if (m_redoResources.isEmpty()) return;
    if (m_undoResources.size() >= 64) m_undoResources.removeFirst();
    m_undoResources.append(m_resources);
    const QVector<Resource> snapshot = m_redoResources.takeLast();
    restoreResourceSnapshot(snapshot);
}

void SidboxGameDesigner::copySelectedSprite()
{
    const int index = selectedIndex();
    if (index < 0 || m_resources.at(index).kind != QStringLiteral("sprite")) return;
    m_copiedSprite = m_resources.at(index);
    m_hasCopiedSprite = true;
}

void SidboxGameDesigner::pasteCopiedSprite()
{
    if (!m_hasCopiedSprite || m_resources.size() >= 8192) return;
    rememberResourceEdit();
    Resource copy = m_copiedSprite;
    copy.id = QUuid::createUuid().toString(QUuid::WithoutBraces);
    QString base = copy.name;
    base.remove(QRegularExpression(QStringLiteral("_copy\\[\\d+\\]$")));
    // Keep numbered clones together, making it obvious they form instances.
    int next = 0;
    const QRegularExpression series(QStringLiteral("^%1_copy\\[(\\d+)\\]$")
        .arg(QRegularExpression::escape(base)));
    for (const Resource &existing : m_resources) {
        const auto match = series.match(existing.name);
        if (match.hasMatch()) next = qMax(next, match.captured(1).toInt() + 1);
    }
    copy.name = QStringLiteral("%1_copy[%2]").arg(base).arg(next);
    copy.x = qBound(-MAX_WORLD, copy.x + 8, MAX_WORLD);
    copy.y = qBound(-MAX_WORLD, copy.y + 8, MAX_WORLD);
    copy.locked = false; // A duplicate is immediately movable.
    m_resources.append(copy);
    rebuildScene();
    refreshResources();
    selectResource(m_resources.size() - 1);
    setDirty();
}

// PPB stores atlas dimensions and palette, NOT sprite cell metadata. A 64x64
// tiling guess is useful for conventional sprite sheets, but never guess it
// for backgrounds. Unknown sprites show the whole atlas until edited manually.
void SidboxGameDesigner::suggestSpriteCells(Resource &resource)
{
    if (resource.kind != QStringLiteral("sprite") || resource.path.isEmpty()) return;
    const QImage image = cachedImage(resolvedPath(resource.path));
    if (image.isNull()) return;
    resource.cellWidth = image.width();
    resource.cellHeight = image.height();
    if (image.width() % 64 == 0 && image.height() % 64 == 0
        && (image.width() > 64 || image.height() > 64)
        && image.width() / 64 <= 16 && image.height() / 64 <= 16) {
        resource.cellWidth = 64;
        resource.cellHeight = 64;
    }
}

void SidboxGameDesigner::addResource(const QString &kind, const QString &plane)
{
    if (!QFileInfo(m_filePath).absoluteDir().exists()) return;
    const QString path = QFileDialog::getOpenFileName(this, tr("Choose %1 resource").arg(kindTitle(kind)),
        QFileInfo(m_filePath).absolutePath(),
        kind == QStringLiteral("sprite") || kind == QStringLiteral("background")
            ? tr("Graphics (*.ppb *.png *.bmp *.jpg *.jpeg *.gif);;All Files (*)")
            : kind == QStringLiteral("sound") ? tr("Sound (*.wav);;All Files (*)")
            : kind == QStringLiteral("music") ? tr("Music (*.mod *.s3m *.xm *.med *.tfmx *.sid *.sba);;All Files (*)")
            : tr("Palettes / Graphics (*.ppb *.pal *.act *.png *.bmp);;All Files (*)"));
    if (path.isEmpty()) return;
    Resource r;
    r.kind = kind;
    r.plane = kind == QStringLiteral("background") ? QStringLiteral("background")
        : (kind == QStringLiteral("palette") && plane == QStringLiteral("background")
          ? QStringLiteral("background") : QStringLiteral("foreground"));
    r.id = QUuid::createUuid().toString(QUuid::WithoutBraces);
    r.name = QFileInfo(path).completeBaseName();
    r.path = storedPath(path);
    r.x = m_cameraX->value() + 40;
    r.y = m_cameraY->value() + 40;
    suggestSpriteCells(r);
    rememberResourceEdit();
    m_resources.append(r);
    const int addedIndex = m_resources.size() - 1;
    if (r.kind == QStringLiteral("palette")) {
        QString &active = r.plane == QStringLiteral("background")
            ? m_activeBackgroundPalette : m_activeForegroundPalette;
        if (active.isEmpty()) active = r.id;
    } else if (r.kind == QStringLiteral("background")) suggestFirstBackgroundPalette(r);
    rebuildScene();
    refreshResources();
    selectResource(addedIndex);
    setDirty();
}

// If no background CLUT is configured yet, the first indexed background
// provides a useful starting palette. Its PPB remains completely unchanged.
// A palette tree resource can reference a PPB directly (readPalette supports it).
void SidboxGameDesigner::suggestFirstBackgroundPalette(const Resource &background)
{
    if (background.kind != QStringLiteral("background")
        || !m_activeBackgroundPalette.isEmpty() || background.path.isEmpty()) return;
    for (const Resource &r : m_resources)
        if (r.kind == QStringLiteral("palette") && r.plane == QStringLiteral("background")) return;
    const QString absolute = resolvedPath(background.path);
    if (QFileInfo(absolute).suffix().compare(QStringLiteral("ppb"), Qt::CaseInsensitive) != 0)
        return; // PNG doesn't necessarily have meaningful absolute indices.
    QString error;
    const QVector<QRgb> bank = SidboxGamePalette::readPalette(absolute, true, &error);
    if (bank.size() != 256) return;
    Resource palette;
    palette.kind = QStringLiteral("palette");
    palette.plane = QStringLiteral("background");
    palette.name = background.name + QStringLiteral("_background_CLUT");
    palette.id = QUuid::createUuid().toString(QUuid::WithoutBraces);
    palette.path = background.path; // Reference only — never write a duplicate.
    m_activeBackgroundPalette = palette.id;
    m_resources.append(palette);
}

void SidboxGameDesigner::importDroppedFiles(const QStringList &paths, const QString &targetKind,
                                            const QString &targetPlane)
{
    QStringList warnings;
    int added = 0;
    int lastImportedIndex = -1;
    bool recorded = false;
    for (const QString &path : paths) {
        const QFileInfo info(path);
        if (!info.isFile()) continue;
        const QString guessed = assetKindForFile(path);
        const QString category = targetKind.isEmpty()
            ? (guessed.isEmpty() ? QStringLiteral("sprite") : guessed) : targetKind;
        if (guessed != category) {
            warnings << tr("%1: %2 dropped into %3")
                .arg(info.fileName(), guessed.isEmpty() ? tr("unknown type") : guessed, category);
        }
        Resource r;
        r.kind = category;
        r.plane = category == QStringLiteral("background") ? QStringLiteral("background")
            : (category == QStringLiteral("palette") && targetPlane == QStringLiteral("background")
               ? QStringLiteral("background") : QStringLiteral("foreground"));
        r.id = QUuid::createUuid().toString(QUuid::WithoutBraces);
        r.name = info.completeBaseName();
        r.path = storedPath(info.absoluteFilePath());
        r.x = m_cameraX->value() + 40;
        r.y = m_cameraY->value() + 40;
        suggestSpriteCells(r);
        if (!recorded) { rememberResourceEdit(); recorded = true; }
        m_resources.append(r);
        lastImportedIndex = m_resources.size() - 1;
        if (r.kind == QStringLiteral("palette")) {
            QString &active = r.plane == QStringLiteral("background")
                ? m_activeBackgroundPalette : m_activeForegroundPalette;
            if (active.isEmpty()) active = r.id;
        } else if (r.kind == QStringLiteral("background")) suggestFirstBackgroundPalette(r);
        ++added;
        if (added >= 128) break;
    }
    if (!added) return;
    rebuildScene();
    refreshResources();
    if (lastImportedIndex >= 0) selectResource(lastImportedIndex);
    setDirty();
    if (!warnings.isEmpty()) QMessageBox::warning(this, tr("Resource type mismatch"),
        tr("The files were added as requested, but check their type:\n%1")
            .arg(warnings.mid(0, 10).join(QLatin1Char('\n'))));
}

void SidboxGameDesigner::addPlaceholder()
{
    Resource r;
    r.kind = QStringLiteral("sprite");
    r.id = QUuid::createUuid().toString(QUuid::WithoutBraces);
    r.name = QStringLiteral("sprite_%1").arg(m_resources.size() + 1);
    r.x = m_cameraX->value() + 40;
    r.y = m_cameraY->value() + 40;
    rememberResourceEdit();
    m_resources.append(r);
    rebuildScene();
    refreshResources();
    selectResource(m_resources.size() - 1);
    setDirty();
}

void SidboxGameDesigner::deleteSelectedResource()
{
    const int index = selectedIndex();
    if (index < 0) return;
    rememberResourceEdit();
    m_resources.removeAt(index);  // only reference is removed; source file untouched
    rebuildScene();
    refreshResources();
    m_resourceTree->clearSelection();
    m_resourceTree->setCurrentItem(nullptr);
    refreshProperties();
    setDirty();
}

void SidboxGameDesigner::pickResourceFile()
{
    const int index = selectedIndex();
    if (index < 0) return;
    const QString path = QFileDialog::getOpenFileName(this, tr("Choose resource file"),
                                                      QFileInfo(m_filePath).absolutePath());
    if (path.isEmpty()) return;
    rememberResourceEdit();
    m_resources[index].path = storedPath(path);
    suggestSpriteCells(m_resources[index]);
    rebuildScene();
    refreshResources();
    selectResource(index);
    setDirty();
}

void SidboxGameDesigner::importPngAsPpb()
{
    if (m_pngConversionRunning) return;
    const QString pngPath = QFileDialog::getOpenFileName(this, tr("Import PNG / Image"),
        QFileInfo(m_filePath).absolutePath(), tr("Images (*.png *.bmp *.jpg *.jpeg);;All Files (*)"));
    if (pngPath.isEmpty()) return;
    // Ask for the destination BEFORE conversion. Conversion and file IO take
    // place on a worker thread, never in the GUI event loop.
    const QString suggested = QFileInfo(m_filePath).absoluteDir().filePath(
        QFileInfo(pngPath).completeBaseName() + QStringLiteral(".ppb"));
    const QString output = QFileDialog::getSaveFileName(this, tr("Save PPB in Game Project"),
        suggested, tr("SIDBOX pixel buffers (*.ppb)"));
    if (output.isEmpty()) return;
    const QString destination = output.endsWith(QStringLiteral(".ppb"), Qt::CaseInsensitive)
        ? output : output + QStringLiteral(".ppb");
    if (QFileInfo::exists(destination) && QMessageBox::question(this, tr("Overwrite PPB?"),
        tr("Replace the existing file?\n%1").arg(destination)) != QMessageBox::Yes) return;

    struct ConversionResult {
        bool succeeded = false;
        int width = 0, height = 0;
        QString error;
    };
    const auto result = std::make_shared<ConversionResult>();
    auto *progress = new QProgressDialog(tr("Converting image to indexed PPB..."), QString(), 0, 0, this);
    progress->setWindowTitle(tr("PNG → PPB"));
    progress->setCancelButton(nullptr); // conversion is atomic, no partial file is kept
    progress->setMinimumDuration(0);
    progress->setWindowModality(Qt::NonModal);
    progress->show();
    m_pngConversionRunning = true;

    QThread *thread = QThread::create([pngPath, destination, result]() {
        QImageReader reader(pngPath);
        reader.setAutoTransform(true);
        const QImage source = reader.read();
        if (source.isNull()) { result->error = reader.errorString(); return; }
        result->width = source.width(); result->height = source.height();
        SidboxPpb::Picture indexed;
        if (!SidboxPpb::fromImage(source, &indexed, &result->error)) return;
        result->succeeded = SidboxPpb::write(destination, indexed, &result->error);
    });
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    connect(thread, &QThread::finished, this, [this, result, destination, progress]() {
        progress->close();
        progress->deleteLater();
        m_pngConversionRunning = false;
        if (!result->succeeded) {
            QMessageBox::warning(this, tr("PNG → PPB"), result->error);
            return;
        }
        Resource r;
        r.kind = QStringLiteral("sprite");
        r.id = QUuid::createUuid().toString(QUuid::WithoutBraces);
        r.name = QFileInfo(destination).completeBaseName();
        r.path = storedPath(destination);
        r.x = m_cameraX->value() + 40;
        r.y = m_cameraY->value() + 40;
        suggestSpriteCells(r);
        rememberResourceEdit();
        m_resources.append(r);
        rebuildScene(); refreshResources(); selectResource(m_resources.size() - 1); setDirty();
        if (assetFilesChanged) assetFilesChanged();
        QMessageBox::information(this, tr("PNG → PPB"),
            tr("Created %1 (%2 × %3 indexed pixels). Original image unchanged.\n"
               "Index 0 is transparent; colours are quantised to at most 255 opaque entries.")
            .arg(QFileInfo(destination).fileName()).arg(result->width).arg(result->height));
    });
    thread->start();
}

void SidboxGameDesigner::exportSelectedC()
{
    const int index = selectedIndex();
    if (index < 0 || !visualKind(m_resources.at(index).kind)) {
        QMessageBox::information(this, tr("Embedded C Resource"), tr("Select a sprite or background first."));
        return;
    }
    const Resource &r = m_resources.at(index);
    if (r.path.isEmpty()) {
        QMessageBox::information(this, tr("Embedded C Resource"), tr("Choose an image file first.")); return;
    }
    const QString input = resolvedPath(r.path);
    SidboxPpb::Picture picture;
    QString error;
    if (QFileInfo(input).suffix().compare(QStringLiteral("ppb"), Qt::CaseInsensitive) == 0) {
        if (!SidboxPpb::read(input, &picture, &error)) {
            QMessageBox::warning(this, tr("Embedded C Resource"), error); return;
        }
    } else {
        QImageReader reader(input);
        reader.setAutoTransform(true);
        const QImage image = reader.read();
        if (image.isNull() || !SidboxPpb::fromImage(image, &picture, &error)) {
            QMessageBox::warning(this, tr("Embedded C Resource"),
                error.isEmpty() ? reader.errorString() : error); return;
        }
    }
    const QString suggested = QFileInfo(m_filePath).absoluteDir().filePath(
        SidboxPpb::identifier(r.name) + QStringLiteral("_resource.c"));
    const QString cName = QFileDialog::getSaveFileName(this, tr("Export Embedded V1 C Resource"),
        suggested, tr("C source (*.c)"));
    if (cName.isEmpty()) return;
    const QString cPath = cName.endsWith(QStringLiteral(".c"), Qt::CaseInsensitive)
        ? cName : cName + QStringLiteral(".c");
    const QFileInfo cInfo(cPath);
    const QString hPath = cInfo.dir().filePath(cInfo.completeBaseName() + QStringLiteral(".h"));
    if ((QFileInfo::exists(cPath) || QFileInfo::exists(hPath))
        && QMessageBox::question(this, tr("Overwrite Generated Resources?"),
           tr("One or both generated files already exist. Replace them?\n%1\n%2")
             .arg(cPath, hPath)) != QMessageBox::Yes) return;
    const qint64 bytes = qint64(picture.indexed.width()) * picture.indexed.height() + 1024;
    if (QMessageBox::question(this, tr("Export Embedded C"),
        tr("This will create a .c and .h file containing approximately %1 bytes of indexed "
           "graphics/palette data before compiler overhead. The project scanner may compile "
           "the .c file on the next F5. Continue?").arg(bytes)) != QMessageBox::Yes) return;
    if (!SidboxPpb::exportC(cPath, r.name, picture, &error)) {
        QMessageBox::warning(this, tr("Embedded C Resource"), error); return;
    }
    if (assetFilesChanged) assetFilesChanged();
    QMessageBox::information(this, tr("Embedded C Resource"),
        tr("Created %1 and %2.\n"
           "Use the generated pixel array and palette from your V1 game code. "
           "No existing game logic was modified.")
          .arg(cInfo.fileName(), QFileInfo(hPath).fileName()));
}

bool SidboxGameDesigner::loadDesign()
{
    QFile file(m_filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, tr("Game Designer"), tr("Cannot open %1").arg(m_filePath));
        return false;
    }
    QJsonParseError error;
    const QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &error);
    const QJsonObject obj = doc.object();
    if (error.error != QJsonParseError::NoError || !doc.isObject()
        || obj.value(QStringLiteral("format")).toString() != QStringLiteral("SIDBOX-GAME-DESIGN")
        || obj.value(QStringLiteral("version")).toInt() != 1) {
        QMessageBox::warning(this, tr("Game Designer"), tr("Unsupported or invalid .sbgm design: %1").arg(m_filePath));
        return false;
    }
    m_loading = true;
    m_worldWidth->setValue(qBound(LCD_WIDTH, obj.value(QStringLiteral("worldWidth")).toInt(960), MAX_WORLD));
    m_worldHeight->setValue(qBound(LCD_HEIGHT, obj.value(QStringLiteral("worldHeight")).toInt(640), MAX_WORLD));
    m_cameraX->setValue(qBound(0, obj.value(QStringLiteral("cameraX")).toInt(),
                               m_worldWidth->value() - LCD_WIDTH));
    m_cameraY->setValue(qBound(0, obj.value(QStringLiteral("cameraY")).toInt(),
                               m_worldHeight->value() - LCD_HEIGHT));
    { QSignalBlocker b1(m_snap), b2(m_snapStep), b3(m_zoom);
      m_snap->setChecked(obj.value(QStringLiteral("snapEnabled")).toBool(true));
      const int step = obj.value(QStringLiteral("snapStep")).toInt(4);
      m_snapStep->setCurrentText(QStringLiteral("%1 px").arg(
          QStringList{QStringLiteral("4"),QStringLiteral("8"),QStringLiteral("16"),
                      QStringLiteral("32"),QStringLiteral("64")}.contains(QString::number(step)) ? step : 32));
      const int zoom = obj.value(QStringLiteral("zoomPercent")).toInt(100);
      m_zoom->setCurrentText(QStringLiteral("%1%").arg(
          QStringList{QStringLiteral("25"), QStringLiteral("50"), QStringLiteral("75"),
                      QStringLiteral("100"), QStringLiteral("200")}.contains(QString::number(zoom)) ? zoom : 100));
      m_view->resetTransform(); m_view->scale(zoom > 0 ? qBound(25, zoom, 200) / 100.0 : 1.,
                                             zoom > 0 ? qBound(25, zoom, 200) / 100.0 : 1.);
    }
    {
        QSignalBlocker b1(m_planeMode), b2(m_showLabels), b3(m_forcePalette);
        m_planeMode->setCurrentIndex(obj.value(QStringLiteral("planeMode")).toString() == QStringLiteral("dual") ? 1 : 0);
        m_showLabels->setChecked(obj.value(QStringLiteral("showAssetLabels")).toBool(true));
        m_forcePalette->setChecked(obj.value(QStringLiteral("forcePalette")).toBool(false));
        m_activeForegroundPalette = obj.value(QStringLiteral("activeForegroundPalette")).toString();
        m_activeBackgroundPalette = obj.value(QStringLiteral("activeBackgroundPalette")).toString();
    }
    m_backPalette->setEnabled(m_planeMode->currentIndex() == 1);
    m_resources.clear();
    const QJsonArray assets = obj.value(QStringLiteral("resources")).toArray();
    for (const QJsonValue &value : assets) {
        if (!value.isObject()) continue;
        const QJsonObject a = value.toObject();
        Resource r;
        r.kind = a.value(QStringLiteral("kind")).toString();
        if (!QStringList{QStringLiteral("sprite"), QStringLiteral("background"),
                         QStringLiteral("palette"), QStringLiteral("sound"), QStringLiteral("music")}.contains(r.kind))
            continue;
        r.name = a.value(QStringLiteral("name")).toString();
        r.id = a.value(QStringLiteral("id")).toString();
        if (r.id.isEmpty()) r.id = QUuid::createUuid().toString(QUuid::WithoutBraces);
        r.plane = a.value(QStringLiteral("plane")).toString(
            r.kind == QStringLiteral("background") ? QStringLiteral("background") : QStringLiteral("foreground"));
        if (r.plane != QStringLiteral("background")) r.plane = QStringLiteral("foreground");
        r.path = a.value(QStringLiteral("path")).toString();
        r.x = qBound(-MAX_WORLD, a.value(QStringLiteral("x")).toInt(), MAX_WORLD);
        r.y = qBound(-MAX_WORLD, a.value(QStringLiteral("y")).toInt(), MAX_WORLD);
        r.scale = qBound(1, a.value(QStringLiteral("scale")).toInt(100), 800);
        r.cellWidth = qBound(0, a.value(QStringLiteral("cellWidth")).toInt(0), 16384);
        r.cellHeight = qBound(0, a.value(QStringLiteral("cellHeight")).toInt(0), 16384);
        r.frame = qBound(0, a.value(QStringLiteral("frame")).toInt(0), 65535);
        r.locked = a.value(QStringLiteral("locked")).toBool(false);
        // Optional Stage 54 fields: old Stage 52/53 documents load unchanged.
        const QJsonObject audio = a.value(QStringLiteral("audio")).toObject();
        r.audio.channel = qBound(0, audio.value(QStringLiteral("channel")).toInt(0), 7);
        r.audio.frequency = qBound(0, audio.value(QStringLiteral("frequency")).toInt(22050), 65535);
        r.audio.volume = qBound(0, audio.value(QStringLiteral("volume")).toInt(255), 1024);
        r.audio.pan = qBound(-127, audio.value(QStringLiteral("pan")).toInt(0), 127);
        r.audio.loop = audio.value(QStringLiteral("loop")).toBool(false);
        r.audio.loopStart = qBound(0, audio.value(QStringLiteral("loopStart")).toInt(0), 2147483647);
        r.audio.loopLength = qBound(0, audio.value(QStringLiteral("loopLength")).toInt(0), 2147483647);
        r.audio.subsong = qBound(0, audio.value(QStringLiteral("subsong")).toInt(0), 255);
        m_resources.append(r);
        if (m_resources.size() >= 8192) break; // corrupt/hostile data guard
    }
    // Older .sbgm documents may have backgrounds but no separate Background
    // palette category yet. Seed it from the first valid background PPB only;
    // never overwrite the file or override an existing bank choice.
    const int originalResourceCount = m_resources.size();
    if (m_activeBackgroundPalette.isEmpty()) {
        for (int i = 0; i < originalResourceCount; ++i) {
            if (m_resources.at(i).kind == QStringLiteral("background")) {
                const Resource background = m_resources.at(i);
                suggestFirstBackgroundPalette(background);
                if (m_resources.size() != originalResourceCount) break;
            }
        }
    }
    const bool seededBackgroundPalette = m_resources.size() != originalResourceCount;
    m_loading = false;
    m_undoResources.clear();
    m_redoResources.clear();
    m_hasCopiedSprite = false;
    rebuildScene();
    refreshResources();
    refreshProperties();
    setDirty(seededBackgroundPalette); // prompt to save new reference, never silently save
    return true;
}

bool SidboxGameDesigner::saveDesign()
{
    QJsonObject obj;
    obj.insert(QStringLiteral("format"), QStringLiteral("SIDBOX-GAME-DESIGN"));
    obj.insert(QStringLiteral("version"), 1);
    obj.insert(QStringLiteral("worldWidth"), m_worldWidth->value());
    obj.insert(QStringLiteral("worldHeight"), m_worldHeight->value());
    obj.insert(QStringLiteral("cameraX"), m_cameraX->value());
    obj.insert(QStringLiteral("cameraY"), m_cameraY->value());
    obj.insert(QStringLiteral("snapEnabled"), m_snap->isChecked());
    obj.insert(QStringLiteral("snapStep"), m_snapStep->currentText().section(QLatin1Char(' '), 0, 0).toInt());
    obj.insert(QStringLiteral("zoomPercent"), m_zoom->currentText().chopped(1).toInt());
    obj.insert(QStringLiteral("showAssetLabels"), m_showLabels->isChecked());
    obj.insert(QStringLiteral("planeMode"), m_planeMode->currentData().toString());
    obj.insert(QStringLiteral("forcePalette"), m_forcePalette->isChecked());
    obj.insert(QStringLiteral("activeForegroundPalette"), m_activeForegroundPalette);
    obj.insert(QStringLiteral("activeBackgroundPalette"), m_activeBackgroundPalette);
    QJsonArray assets;
    for (const Resource &r : m_resources) {
        QJsonObject a;
        a.insert(QStringLiteral("kind"), r.kind);
        a.insert(QStringLiteral("name"), r.name);
        a.insert(QStringLiteral("id"), r.id);
        a.insert(QStringLiteral("plane"), r.plane);
        a.insert(QStringLiteral("path"), r.path);
        a.insert(QStringLiteral("x"), r.x);
        a.insert(QStringLiteral("y"), r.y);
        a.insert(QStringLiteral("scale"), r.scale);
        a.insert(QStringLiteral("cellWidth"), r.cellWidth);
        a.insert(QStringLiteral("cellHeight"), r.cellHeight);
        a.insert(QStringLiteral("frame"), r.frame);
        a.insert(QStringLiteral("locked"), r.locked);
        if (r.kind == QStringLiteral("sound") || r.kind == QStringLiteral("music")) {
            QJsonObject audio;
            audio.insert(QStringLiteral("channel"), r.audio.channel);
            audio.insert(QStringLiteral("frequency"), r.audio.frequency);
            audio.insert(QStringLiteral("volume"), r.audio.volume);
            audio.insert(QStringLiteral("pan"), r.audio.pan);
            audio.insert(QStringLiteral("loop"), r.audio.loop);
            audio.insert(QStringLiteral("loopStart"), r.audio.loopStart);
            audio.insert(QStringLiteral("loopLength"), r.audio.loopLength);
            audio.insert(QStringLiteral("subsong"), r.audio.subsong);
            a.insert(QStringLiteral("audio"), audio);
        }
        assets.append(a);
    }
    obj.insert(QStringLiteral("resources"), assets);
    QSaveFile output(m_filePath);
    const QByteArray payload = QJsonDocument(obj).toJson(QJsonDocument::Indented);
    if (!output.open(QIODevice::WriteOnly)
        || output.write(payload) != payload.size()
        || !output.commit()) {
        QMessageBox::warning(this, tr("Game Designer"), tr("Unable to save design:\n%1").arg(m_filePath));
        return false;
    }
    setDirty(false);
    return true;
}

// Build separate foreground/background banks from absolute index votes.
// Do NOT create PPBs, rewrite palette tables inside PPBs, or relink assets.
// Hardware-ready shared.pal contains BOTH 256x4 banks; the optional one-bank
// palette files make it easy to select each bank independently for preview.
void SidboxGameDesigner::buildSharedPalette()
{
    struct Input { QString path; QString plane; };
    QVector<Input> inputs;
    const QRectF viewport(m_cameraX->value(), m_cameraY->value(), LCD_WIDTH, LCD_HEIGHT);
    QSet<QString> seenFiles;
    for (const Resource &r : m_resources) {
        if (!visualKind(r.kind) || r.path.isEmpty()) continue;
        const QString plane = resourcePlane(r);
        if (plane == QStringLiteral("background") && m_planeMode->currentIndex() == 0) continue;
        const QString absolute = resolvedPath(r.path);
        if (!QFileInfo(absolute).isFile()) continue;
        // Only indexed graphics carry stable hardware palette indices.
        const QImage image = cachedImage(absolute);
        if (image.isNull() || image.format() != QImage::Format_Indexed8) continue;
        const int cw = r.cellWidth > 0 ? qMin(r.cellWidth, image.width()) : image.width();
        const int ch = r.cellHeight > 0 ? qMin(r.cellHeight, image.height()) : image.height();
        const QRectF bounds(r.x, r.y, cw * r.scale / 100.0, ch * r.scale / 100.0);
        const QString key = absolute + QLatin1Char('|') + plane;
        if (!bounds.intersects(viewport) || seenFiles.contains(key)) continue;
        seenFiles.insert(key);
        inputs.append(Input{absolute, plane});
    }
    if (inputs.isEmpty()) {
        QMessageBox::information(this, tr("Build Shared CLUT"), tr(
            "No indexed PPB / indexed PNG graphics intersect the yellow LCD camera frame. "
            "Convert any truecolour images with PNG → PPB first."));
        return;
    }
    const bool dual = m_planeMode->currentIndex() == 1;
    int foregroundCount = 0, backgroundCount = 0;
    for (const Input &input : inputs) {
        if (input.plane == QStringLiteral("background")) ++backgroundCount;
        else ++foregroundCount;
    }
    const QString question = tr(
        "Build shared palette bank(s) from %1 foreground and %2 background resource(s)?\n\n"
        "Each PPB retains its existing source file and every original pixel index. "
        "NO PPB copies will be created.\n\n"
        "A 2048-byte shared.pal (foreground + background) and separate per-plane .pal "
        "files will be saved under gamepalettes/.\n\n"
        "Where two images disagree about the colour at an index, similar colours "
        "will be averaged; substantial conflicts retain the first value and are reported.\n\n"
        "Only indexed graphics intersecting the LCD camera are included "
        "(their complete sprite atlases are analysed).\n\n"
        "You can choose either generated CLUT in the preview dropdowns. "
        "Please verify the result on SIDBOX hardware.")
        .arg(foregroundCount).arg(dual ? backgroundCount : 0);
    if (QMessageBox::question(this, tr("Build Shared CLUT"), question) != QMessageBox::Yes) return;

    const QString projectDir = QFileInfo(m_filePath).absolutePath();
    const QString outputDir = QDir(projectDir).filePath(QStringLiteral("gamepalettes/shared_")
        + QUuid::createUuid().toString(QUuid::WithoutBraces).left(10));
    const QVector<QRgb> previousForeground = activePalette(QStringLiteral("foreground"));
    const QVector<QRgb> previousBackground = activePalette(QStringLiteral("background"));
    struct Result {
        QString error;
        QString sharedPath;
        QString foregroundPath;
        QString backgroundPath;
        int fgConflicts = 0;
        int bgConflicts = 0;
        int fgSevere = 0;
        int bgSevere = 0;
        bool madeForeground = false;
        bool madeBackground = false;
        bool success = false;
    };
    const auto result = std::make_shared<Result>();
    auto *progress = new QProgressDialog(tr("Building palette files (original graphics untouched)..."),
                                        QString(), 0, 0, this);
    progress->setWindowTitle(tr("SIDBOX CLUT Builder"));
    progress->setCancelButton(nullptr);
    progress->setMinimumDuration(0);
    progress->setWindowModality(Qt::ApplicationModal);
    progress->show();
    m_buildPaletteButton->setEnabled(false);
    QThread *thread = QThread::create([inputs, dual, outputDir, previousForeground,
                                      previousBackground, result]() {
        QVector<QImage> frontImages, backImages;
        for (const Input &input : inputs) {
            QImage image;
            if (QFileInfo(input.path).suffix().compare(QStringLiteral("ppb"), Qt::CaseInsensitive) == 0) {
                SidboxPpb::Picture picture;
                if (!SidboxPpb::read(input.path, &picture, &result->error)) return;
                image = picture.indexed;
            } else {
                QImageReader reader(input.path);
                reader.setAutoTransform(true);
                image = reader.read();
                if (image.isNull()) { result->error = reader.errorString(); return; }
            }
            if (image.format() != QImage::Format_Indexed8) {
                result->error = QStringLiteral("Resource has no absolute 8-bit indices: %1").arg(input.path);
                return;
            }
            if (input.plane == QStringLiteral("background")) backImages.append(image);
            else frontImages.append(image);
        }
        QVector<QRgb> foreground = previousForeground.size() == 256
            ? previousForeground : QVector<QRgb>(256, qRgba(0, 0, 0, 255));
        QVector<QRgb> background = previousBackground.size() == 256
            ? previousBackground : QVector<QRgb>(256, qRgba(0, 0, 0, 255));
        if (!frontImages.isEmpty()) {
            SidboxGamePalette::IndexBuildResult built;
            if (!SidboxGamePalette::buildIndexPreserving(frontImages, false, &built, &result->error)) return;
            foreground = built.colours;
            result->fgConflicts = built.collisions;
            result->fgSevere = built.severeCollisions;
            result->madeForeground = true;
        }
        if (dual && !backImages.isEmpty()) {
            SidboxGamePalette::IndexBuildResult built;
            if (!SidboxGamePalette::buildIndexPreserving(backImages, true, &built, &result->error)) return;
            background = built.colours;
            result->bgConflicts = built.collisions;
            result->bgSevere = built.severeCollisions;
            result->madeBackground = true;
        }
        QDir directory;
        if (!directory.mkpath(outputDir)) {
            result->error = QStringLiteral("Cannot create palette output directory.");
            return;
        }
        const auto failAndClean = [outputDir, result]() {
            QDir(outputDir).removeRecursively();
            if (result->error.isEmpty()) result->error = QStringLiteral("Failed to write palette outputs.");
        };
        result->sharedPath = QDir(outputDir).filePath(QStringLiteral("shared.pal"));
        if (!SidboxGamePalette::writePal(result->sharedPath, foreground, background, &result->error)) {
            failAndClean(); return;
        }
        if (result->madeForeground) {
            result->foregroundPath = QDir(outputDir).filePath(QStringLiteral("foreground.pal"));
            if (!SidboxGamePalette::writeSinglePal(result->foregroundPath, foreground, &result->error)) {
                failAndClean(); return;
            }
        }
        if (result->madeBackground) {
            result->backgroundPath = QDir(outputDir).filePath(QStringLiteral("background.pal"));
            if (!SidboxGamePalette::writeSinglePal(result->backgroundPath, background, &result->error)) {
                failAndClean(); return;
            }
        }
        result->success = true;
    });
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    connect(thread, &QThread::finished, this, [this, result, progress]() {
        progress->close();
        progress->deleteLater();
        m_buildPaletteButton->setEnabled(true);
        if (!result->success) {
            QMessageBox::warning(this, tr("Build Shared CLUT"),
                result->error.isEmpty() ? tr("Palette build failed.") : result->error);
            return;
        }
        rememberResourceEdit();
        int selectedPalette = -1;
        for (const QString &plane : {QStringLiteral("foreground"), QStringLiteral("background")}) {
            const QString path = plane == QStringLiteral("foreground")
                ? result->foregroundPath : result->backgroundPath;
            if (path.isEmpty()) continue;
            Resource resource;
            resource.kind = QStringLiteral("palette");
            resource.plane = plane;
            resource.name = QStringLiteral("shared_%1").arg(plane);
            resource.id = QUuid::createUuid().toString(QUuid::WithoutBraces);
            resource.path = storedPath(path);
            m_resources.append(resource);
            selectedPalette = m_resources.size() - 1;
            if (plane == QStringLiteral("foreground")) m_activeForegroundPalette = resource.id;
            else m_activeBackgroundPalette = resource.id;
        }
        {
            QSignalBlocker block(m_forcePalette);
            m_forcePalette->setChecked(true);
        }
        rebuildScene();
        refreshResources();
        if (selectedPalette >= 0) selectResource(selectedPalette);
        setDirty();
        if (assetFilesChanged) assetFilesChanged();
        QMessageBox::information(this, tr("Shared CLUT Created"), tr(
            "Created CLUT files under:\n%1\n\n"
            "shared.pal contains BOTH hardware banks. Separate foreground.pal and "
            "background.pal files contain the individual banks when built.\n\n"
            "Your original PPBs, pixel indices and design asset paths are untouched.\n\n"
            "Foreground: %2 differing indices (%3 major conflicts)\n"
            "Background: %4 differing indices (%5 major conflicts)\n\n"
            "The generated banks are selected for Forced Preview. "
            "Check the result on real SIDBOX hardware.")
            .arg(QFileInfo(result->sharedPath).absolutePath())
            .arg(result->fgConflicts).arg(result->fgSevere)
            .arg(result->bgConflicts).arg(result->bgSevere));
    });
    thread->start();
}

void SidboxGameDesigner::refreshColours()
{
    if (!m_scene) return;
    const QColor base = palette().color(QPalette::Base);
    m_scene->setBackgroundBrush(QBrush(base));
    static_cast<GameScene *>(m_scene)->gridColour = palette().color(QPalette::Mid);
    m_scene->update();
}

void SidboxGameDesigner::changeEvent(QEvent *event)
{
    QWidget::changeEvent(event);
    if (event->type() == QEvent::PaletteChange || event->type() == QEvent::StyleChange)
        refreshColours();
}

// The Delete key removes references only. Never intercept Delete inside text
// editors/spinboxes. Space+left-drag shifts the world camera, not a sprite.
bool SidboxGameDesigner::eventFilter(QObject *watched, QEvent *event)
{
    const bool onView = m_view && (watched == m_view || watched == m_view->viewport());
    const bool onResources = watched == m_resourceTree ||
        (m_resourceTree && watched == m_resourceTree->viewport());
    if (onView || onResources) {
        if (event->type() == QEvent::KeyPress) {
            auto *key = static_cast<QKeyEvent *>(event);
            if ((key->modifiers() & Qt::ControlModifier) && !key->isAutoRepeat()) {
                // Shortcuts are only captured in the canvas or resource tree;
                // Ctrl+C/Z in the properties' text editors keep their normal meaning.
                switch (key->key()) {
                case Qt::Key_C: copySelectedSprite(); return true;
                case Qt::Key_V: pasteCopiedSprite(); return true;
                case Qt::Key_Z:
                    if (key->modifiers() & Qt::ShiftModifier) redoResourceEdit();
                    else undoResourceEdit();
                    return true;
                case Qt::Key_Y: redoResourceEdit(); return true;
                default: break;
                }
            }
            if (key->key() == Qt::Key_Delete && !key->isAutoRepeat()) {
                deleteSelectedResource();
                return true;
            }
            if (onView && key->key() == Qt::Key_Space && !key->isAutoRepeat()) {
                m_spaceHeld = true;
                m_view->viewport()->setCursor(Qt::OpenHandCursor);
                return true;
            }
        }
        if (onView && event->type() == QEvent::KeyRelease) {
            auto *key = static_cast<QKeyEvent *>(event);
            if (key->key() == Qt::Key_Space && !key->isAutoRepeat()) {
                m_spaceHeld = false;
                m_panningCamera = false;
                m_view->viewport()->unsetCursor();
                return true;
            }
        }
    }
    if (m_view && watched == m_view->viewport()) {
        if (event->type() == QEvent::MouseButtonPress) {
            auto *mouse = static_cast<QMouseEvent *>(event);
            m_dragResourceIndex = -1;
            if (!m_spaceHeld && mouse->button() == Qt::LeftButton) {
                QGraphicsItem *item = m_view->itemAt(mouse->position().toPoint());
                while (item && !item->data(0).isValid()) item = item->parentItem();
                if (item && item->flags().testFlag(QGraphicsItem::ItemIsMovable)) {
                    const int index = item->data(0).toInt();
                    if (index >= 0 && index < m_resources.size()) {
                        m_dragResourceIndex = index;
                        m_dragResourceStart = QPoint(m_resources[index].x, m_resources[index].y);
                        m_dragBefore = m_resources;
                    }
                }
            }
            if (m_spaceHeld && mouse->button() == Qt::LeftButton) {
                m_panningCamera = true;
                m_panLastPos = mouse->position().toPoint();
                m_view->viewport()->setCursor(Qt::ClosedHandCursor);
                return true;
            }
        }
        if (event->type() == QEvent::MouseMove && m_panningCamera) {
            auto *mouse = static_cast<QMouseEvent *>(event);
            const QPoint next = mouse->position().toPoint();
            const QPointF lastWorld = m_view->mapToScene(m_panLastPos);
            const QPointF nowWorld = m_view->mapToScene(next);
            const QPointF delta = nowWorld - lastWorld;
            m_panLastPos = next;
            m_cameraX->setValue(qBound(0, m_cameraX->value() + qRound(delta.x()),
                                      m_cameraX->maximum()));
            m_cameraY->setValue(qBound(0, m_cameraY->value() + qRound(delta.y()),
                                      m_cameraY->maximum()));
            return true;
        }
        if (event->type() == QEvent::MouseButtonRelease) {
            auto *mouse = static_cast<QMouseEvent *>(event);
            if (mouse->button() == Qt::LeftButton && m_dragResourceIndex >= 0) {
                const int index = m_dragResourceIndex;
                if (index < m_resources.size() &&
                    m_dragResourceStart != QPoint(m_resources[index].x, m_resources[index].y)) {
                    if (m_undoResources.size() >= 64) m_undoResources.removeFirst();
                    m_undoResources.append(m_dragBefore);
                    m_redoResources.clear();
                }
                m_dragResourceIndex = -1;
                m_dragBefore.clear();
            }
        }
        if (event->type() == QEvent::MouseButtonRelease && m_panningCamera) {
            auto *mouse = static_cast<QMouseEvent *>(event);
            if (mouse->button() == Qt::LeftButton) {
                m_panningCamera = false;
                m_view->viewport()->setCursor(m_spaceHeld ? Qt::OpenHandCursor : Qt::ArrowCursor);
                return true;
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}
