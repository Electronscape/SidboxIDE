#include "gamedesigner.h"
#include "ppbcodec.h"

#include <QCheckBox>
#include <QComboBox>
#include <QDir>
#include <QEvent>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QFont>
#include <QFormLayout>
#include <QGraphicsItem>
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
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QPixmap>
#include <QPalette>
#include <QPushButton>
#include <QProgressDialog>
#include <QThread>
#include <memory>
#include <QSaveFile>
#include <QStringList>
#include <QSignalBlocker>
#include <QSpinBox>
#include <QSplitter>
#include <QToolButton>
#include <QTreeWidget>
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
        const QVariant result = QGraphicsPixmapItem::itemChange(change, value);
        if (change == ItemPositionHasChanged && moved) moved(this);
        return result;
    }
};

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
        "QTreeWidget, QGraphicsView, QFrame { border-radius: 0px; }"));

    auto *top = new QHBoxLayout;
    auto *caption = new QLabel(tr("Game Designer  |  V1 Gaming"), this);
    QFont titleFont = caption->font();
    titleFont.setBold(true);
    caption->setFont(titleFont);
    top->addWidget(caption);
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
    auto *focusCamera = new QPushButton(tr("Locate Camera"), this);
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
    m_resourceTree = new QTreeWidget(resourcesPanel);
    m_resourceTree->setHeaderHidden(true);
    m_resourceTree->setSelectionMode(QAbstractItemView::SingleSelection);
    resourcesLayout->addWidget(m_resourceTree, 1);
    auto *addSprite = new QPushButton(tr("+ Sprite / Atlas"), resourcesPanel);
    auto *addPlaceholderSprite = new QPushButton(tr("+ Empty Sprite"), resourcesPanel);
    auto *addBackground = new QPushButton(tr("+ Background"), resourcesPanel);
    auto *importPpb = new QPushButton(tr("PNG → PPB..."), resourcesPanel);
    m_importPpbButton = importPpb;
    auto *addPalette = new QPushButton(tr("+ Palette"), resourcesPanel);
    auto *addSound = new QPushButton(tr("+ WAV Sound"), resourcesPanel);
    auto *addMusic = new QPushButton(tr("+ Music"), resourcesPanel);
    for (QPushButton *button : {addSprite, addPlaceholderSprite, addBackground, importPpb,
                                addPalette, addSound, addMusic})
        resourcesLayout->addWidget(button);
    auto *note = new QLabel(tr("PNG → PPB creates a separate indexed file. Your original PNG is never altered."), resourcesPanel);
    note->setWordWrap(true);
    note->setStyleSheet(QStringLiteral("color: palette(mid);"));
    resourcesLayout->addWidget(note);

    auto *previewPanel = new QWidget(splitter);
    auto *previewLayout = new QVBoxLayout(previewPanel);
    previewLayout->setContentsMargins(0, 4, 0, 0);
    auto *previewControls = new QHBoxLayout;
    previewControls->addWidget(new QLabel(tr("WORLD CANVAS  |  dashed frame = LCD viewport"), previewPanel));
    previewControls->addStretch();
    m_grid = new QCheckBox(tr("Grid 32"), previewPanel);
    m_grid->setChecked(true);
    previewControls->addWidget(m_grid);
    previewControls->addWidget(new QLabel(tr("Zoom:"), previewPanel));
    m_zoom = new QComboBox(previewPanel);
    m_zoom->addItems({QStringLiteral("25%"), QStringLiteral("50%"),
                      QStringLiteral("75%"), QStringLiteral("100%"), QStringLiteral("200%")});
    m_zoom->setCurrentText(QStringLiteral("75%"));
    previewControls->addWidget(m_zoom);
    previewLayout->addLayout(previewControls);
    m_scene = new GameScene(this);
    m_view = new QGraphicsView(m_scene, previewPanel);
    m_view->setDragMode(QGraphicsView::RubberBandDrag);
    m_view->setRenderHint(QPainter::Antialiasing, false);
    m_view->setRenderHint(QPainter::SmoothPixmapTransform, false);
    m_view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    previewLayout->addWidget(m_view, 1);
    auto *instruction = new QLabel(tr("Drag sprites to position them. Scroll to pan the world. The 480×320 LCD frame can move independently."), previewPanel);
    instruction->setWordWrap(true);
    previewLayout->addWidget(instruction);

    auto *propertiesPanel = new QWidget(splitter);
    auto *propertiesLayout = new QVBoxLayout(propertiesPanel);
    propertiesLayout->setContentsMargins(5, 4, 5, 4);
    propertiesLayout->addWidget(new QLabel(tr("RESOURCE PROPERTIES"), propertiesPanel));
    auto *form = new QFormLayout;
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
    m_imageInfo = new QLabel(propertiesPanel);
    m_imageInfo->setWordWrap(true);
    form->addRow(tr("Name"), m_propName);
    form->addRow(tr("File"), m_propFile);
    form->addRow(tr("X"), m_propX);
    form->addRow(tr("Y"), m_propY);
    form->addRow(tr("Scale"), m_propScale);
    form->addRow(tr("Cell width"), m_propCellWidth);
    form->addRow(tr("Cell height"), m_propCellHeight);
    form->addRow(tr("Frame"), m_propFrame);
    propertiesLayout->addLayout(form);
    propertiesLayout->addWidget(m_imageInfo);
    m_palettePreview = new QLabel(propertiesPanel);
    m_palettePreview->setFixedSize(128, 128);
    m_palettePreview->setToolTip(tr("Indexed colour palette: 16 × 16 entries, index 0 top-left"));
    m_palettePreview->hide();
    propertiesLayout->addWidget(m_palettePreview, 0, Qt::AlignLeft);
    auto *changeFile = new QPushButton(tr("Change File..."), propertiesPanel);
    propertiesLayout->addWidget(changeFile);
    auto *exportC = new QPushButton(tr("Export Embedded C..."), propertiesPanel);
    propertiesLayout->addWidget(exportC);
    m_deleteButton = new QPushButton(tr("Remove Resource"), propertiesPanel);
    propertiesLayout->addWidget(m_deleteButton);
    auto *limitations = new QLabel(tr("Embedded C export is optional. Animation and audio code generation are future stages."), propertiesPanel);
    limitations->setWordWrap(true);
    propertiesLayout->addWidget(limitations);
    propertiesLayout->addStretch();
    splitter->addWidget(resourcesPanel);
    splitter->addWidget(previewPanel);
    splitter->addWidget(propertiesPanel);
    splitter->setStretchFactor(0, 0);
    splitter->setStretchFactor(1, 1);
    splitter->setStretchFactor(2, 0);
    splitter->setSizes({195, 700, 220});

    connect(save, &QPushButton::clicked, this, [this]() { saveDesign(); });
    connect(focusCamera, &QPushButton::clicked, this, [this]() {
        m_view->centerOn(m_cameraX->value() + LCD_WIDTH / 2,
                         m_cameraY->value() + LCD_HEIGHT / 2);
    });
    connect(addPlaceholderSprite, &QPushButton::clicked, this, [this]() { addPlaceholder(); });
    connect(addSprite, &QPushButton::clicked, this, [this]() { addResource(QStringLiteral("sprite")); });
    connect(addBackground, &QPushButton::clicked, this, [this]() { addResource(QStringLiteral("background")); });
    connect(importPpb, &QPushButton::clicked, this, [this]() { importPngAsPpb(); });
    connect(exportC, &QPushButton::clicked, this, [this]() { exportSelectedC(); });
    connect(addPalette, &QPushButton::clicked, this, [this]() { addResource(QStringLiteral("palette")); });
    connect(addSound, &QPushButton::clicked, this, [this]() { addResource(QStringLiteral("sound")); });
    connect(addMusic, &QPushButton::clicked, this, [this]() { addResource(QStringLiteral("music")); });
    connect(m_deleteButton, &QPushButton::clicked, this, [this]() { deleteSelectedResource(); });
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
    m_view->scale(0.75, 0.75);
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
    for (int i = 0; i < m_resourceTree->topLevelItemCount(); ++i) {
        auto *group = m_resourceTree->topLevelItem(i);
        for (int j = 0; j < group->childCount(); ++j) {
            auto *child = group->child(j);
            if (child->data(0, Qt::UserRole).toInt() == index) {
                m_resourceTree->setCurrentItem(child);
                break;
            }
        }
    }
    m_scene->clearSelection();
    if (index < m_sceneItems.size() && m_sceneItems.at(index))
        m_sceneItems.at(index)->setSelected(true);
    m_syncSelection = false;
    refreshProperties();
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
        for (int index = 0; index < m_resources.size(); ++index) {
            const Resource &r = m_resources.at(index);
            if (r.kind != kind) continue;
            auto *child = new QTreeWidgetItem(root, QStringList{r.name});
            child->setData(0, Qt::UserRole, index);
            child->setToolTip(0, r.path);
        }
        root->setExpanded(true);
    }
    if (preserve >= 0) selectResource(preserve);
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
    return source.copy((frame % cols) * cw, (frame / cols) * ch, cw, ch);
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
        item->setPos(r.x, r.y);
        item->setScale(r.scale / 100.0);
        if (r.kind == QStringLiteral("background")) item->setZValue(1);
        item->moved = [this](QGraphicsItem *which) { syncFromSceneItem(which); };
        m_scene->addItem(item);
        auto *title = new QGraphicsSimpleTextItem(r.name, item);
        title->setBrush(QColor(255, 241, 160));
        title->setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
        title->setPos(0, -18);
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
    for (QWidget *widget : {static_cast<QWidget *>(m_propName), static_cast<QWidget *>(m_propX),
                            static_cast<QWidget *>(m_propY), static_cast<QWidget *>(m_propScale),
                            static_cast<QWidget *>(m_propCellWidth), static_cast<QWidget *>(m_propCellHeight),
                            static_cast<QWidget *>(m_propFrame), static_cast<QWidget *>(m_deleteButton)})
        widget->setEnabled(enabled);
    QSignalBlocker block1(m_propName), block2(m_propX), block3(m_propY), block4(m_propScale);
    QSignalBlocker block5(m_propCellWidth), block6(m_propCellHeight), block7(m_propFrame);
    if (!enabled) {
        m_propName->clear(); m_propFile->clear(); m_imageInfo->clear(); m_palettePreview->hide();
        m_propX->setValue(0); m_propY->setValue(0); m_propScale->setValue(100);
        m_propCellWidth->setValue(0); m_propCellHeight->setValue(0);
        m_propFrame->setRange(0, 0);
        return;
    }
    const Resource &r = m_resources.at(index);
    m_palettePreview->hide();
    // PAL resource: the Sturdust .pal stores two 256x4-byte palettes.
    // Display the first bank, without modifying any alpha/CLUT bytes on disk.
    if (r.kind == QStringLiteral("palette") && QFileInfo(resolvedPath(r.path)).suffix().toLower() == QStringLiteral("pal")) {
        QFile palFile(resolvedPath(r.path));
        if (palFile.open(QIODevice::ReadOnly) && palFile.size() >= 1024 && palFile.size() <= 65536) {
            const QByteArray contents = palFile.read(1024);
            QVector<QRgb> colours;
            for (int j = 0; j < 256; ++j) {
                const unsigned char *entry = reinterpret_cast<const unsigned char *>(contents.constData() + j * 4);
                colours.append(qRgb(entry[2], entry[1], entry[0]));
            }
            m_palettePreview->setPixmap(paletteSwatches(colours));
            m_palettePreview->show();
            m_imageInfo->setText(tr("PAL: first 256 colours (preview only)"));
        }
    }
    m_propName->setText(r.name);
    m_propFile->setText(r.path.isEmpty() ? tr("(placeholder)") : r.path);
    m_propX->setValue(r.x);
    m_propY->setValue(r.y);
    m_propScale->setValue(r.scale);
    m_propCellWidth->setValue(r.cellWidth);
    m_propCellHeight->setValue(r.cellHeight);
    const bool visual = visualKind(r.kind);
    for (QSpinBox *spin : {m_propX, m_propY, m_propScale,
                           m_propCellWidth, m_propCellHeight, m_propFrame})
        spin->setEnabled(visual);
    if (!visual) {
        m_propFrame->setRange(0, 0);
        if (r.kind != QStringLiteral("palette")) m_imageInfo->clear();
        return;
    }
    const QImage image = cachedImage(resolvedPath(r.path));
    if (!image.isNull() && !image.colorTable().isEmpty()) {
        m_palettePreview->setPixmap(paletteSwatches(image.colorTable()));
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
    m_imageInfo->setText(tr("Atlas: %1 × %2  |  %3 frames  |  Index 0 = transparent")
        .arg(image.width()).arg(image.height()).arg(frames));
}

void SidboxGameDesigner::addResource(const QString &kind)
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
    r.name = QFileInfo(path).completeBaseName();
    r.path = storedPath(path);
    r.x = m_cameraX->value() + 40;
    r.y = m_cameraY->value() + 40;
    m_resources.append(r);
    rebuildScene();
    refreshResources();
    selectResource(m_resources.size() - 1);
    setDirty();
}

void SidboxGameDesigner::addPlaceholder()
{
    Resource r;
    r.kind = QStringLiteral("sprite");
    r.name = QStringLiteral("sprite_%1").arg(m_resources.size() + 1);
    r.x = m_cameraX->value() + 40;
    r.y = m_cameraY->value() + 40;
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
    m_resources[index].path = storedPath(path);
    rebuildScene();
    refreshResources();
    selectResource(index);
    setDirty();
}

void SidboxGameDesigner::importPngAsPpb()
{
    if (m_importPpbButton && !m_importPpbButton->isEnabled()) return;
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
    if (m_importPpbButton) m_importPpbButton->setEnabled(false);

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
        if (m_importPpbButton) m_importPpbButton->setEnabled(true);
        if (!result->succeeded) {
            QMessageBox::warning(this, tr("PNG → PPB"), result->error);
            return;
        }
        Resource r;
        r.kind = QStringLiteral("sprite");
        r.name = QFileInfo(destination).completeBaseName();
        r.path = storedPath(destination);
        r.x = m_cameraX->value() + 40;
        r.y = m_cameraY->value() + 40;
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
        r.path = a.value(QStringLiteral("path")).toString();
        r.x = qBound(-MAX_WORLD, a.value(QStringLiteral("x")).toInt(), MAX_WORLD);
        r.y = qBound(-MAX_WORLD, a.value(QStringLiteral("y")).toInt(), MAX_WORLD);
        r.scale = qBound(1, a.value(QStringLiteral("scale")).toInt(100), 800);
        r.cellWidth = qBound(0, a.value(QStringLiteral("cellWidth")).toInt(0), 16384);
        r.cellHeight = qBound(0, a.value(QStringLiteral("cellHeight")).toInt(0), 16384);
        r.frame = qBound(0, a.value(QStringLiteral("frame")).toInt(0), 65535);
        m_resources.append(r);
        if (m_resources.size() >= 8192) break; // corrupt/hostile data guard
    }
    m_loading = false;
    rebuildScene();
    refreshResources();
    refreshProperties();
    setDirty(false);
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
    QJsonArray assets;
    for (const Resource &r : m_resources) {
        QJsonObject a;
        a.insert(QStringLiteral("kind"), r.kind);
        a.insert(QStringLiteral("name"), r.name);
        a.insert(QStringLiteral("path"), r.path);
        a.insert(QStringLiteral("x"), r.x);
        a.insert(QStringLiteral("y"), r.y);
        a.insert(QStringLiteral("scale"), r.scale);
        a.insert(QStringLiteral("cellWidth"), r.cellWidth);
        a.insert(QStringLiteral("cellHeight"), r.cellHeight);
        a.insert(QStringLiteral("frame"), r.frame);
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
