#include "gametitlescreeneditor.h"
#include "ppbcodec.h"
#include "gamepalette.h"
#include "guidesigner_detail.h"

#include <QAbstractItemView>
#include <QCheckBox>
#include <QComboBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QFileInfo>
#include <QFormLayout>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QScrollArea>
#include <QPainterPath>
#include <QColor>
#include <QGraphicsView>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QResizeEvent>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QSaveFile>
#include <QSignalBlocker>
#include <QSpinBox>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QVector>
#include <functional>

namespace {

// Graphical/title-screen state is intentionally separate from .sbgm and the
// game runtime. A later generator can consume these saved PPB references.
struct Artwork {
    QString mode = QStringLiteral("text"); // text or ppb
    QString path;
    int cellSize = 0; // 0 = entire PPB, otherwise 8, 16 or 32
    int frame = 0;    // cell index in the selected cell-size grid
    int x = 0;
    int y = 0;
    int foreground = 15;   // Foreground CLUT index, never an RGB remap.
    int outline = 0;       // Foreground CLUT index.
    bool outlineEnabled = false;
    int fontSizeX = 1;     // Design levels: 1x, 2x, 4x, 8x.
    int fontSizeY = 1;     // Design levels: 1x, 2x, 4x, 8x.
};
struct TitleBackground {
    QString path;
    QString mode = QStringLiteral("sprite"); // sprite, direct_ready, direct_convert
};
struct MenuEntry {
    QString label;
    QString action = QStringLiteral("start");
    QString world;
    QString start = QStringLiteral("default");
    Artwork art;
};
struct WorldStart {
    QString id;
    QString name;
};

class TitlePreviewView final : public QGraphicsView {
public:
    explicit TitlePreviewView(QGraphicsScene *scene, QWidget *parent = nullptr)
        : QGraphicsView(scene, parent) {
        setRenderHint(QPainter::Antialiasing, false);
        setRenderHint(QPainter::SmoothPixmapTransform, false);
        setDragMode(QGraphicsView::NoDrag);
        setBackgroundBrush(QColor(25, 25, 28));
        setFrameShape(QFrame::StyledPanel);
        setMinimumSize(500, 350);
    }
    std::function<void()> dragFinished;
protected:
    void resizeEvent(QResizeEvent *event) override {
        QGraphicsView::resizeEvent(event);
        fitInView(QRectF(0,0,480,320),Qt::KeepAspectRatio);
    }
    void mouseReleaseEvent(QMouseEvent *event) override {
        QGraphicsView::mouseReleaseEvent(event);
        if (dragFinished) dragFinished();
    }
};

QString fileName(const QString &root) {
    return QDir(root).filePath(QStringLiteral(".sidbox-title-screen.json"));
}
QJsonObject artJson(const Artwork &a) {
    return {{QStringLiteral("mode"),a.mode}, {QStringLiteral("path"),a.path},
            {QStringLiteral("cellSize"),a.cellSize}, {QStringLiteral("frame"),a.frame},
            {QStringLiteral("x"),a.x}, {QStringLiteral("y"),a.y},
            {QStringLiteral("foreground"),a.foreground}, {QStringLiteral("outline"),a.outline},
            {QStringLiteral("outlineEnabled"),a.outlineEnabled},
            {QStringLiteral("fontSizeX"),a.fontSizeX},
            {QStringLiteral("fontSizeY"),a.fontSizeY},
            {QStringLiteral("fontSize"),a.fontSizeX}};
}
Artwork artFromJson(const QJsonObject &obj, const Artwork &fallback) {
    Artwork a = fallback;
    if (obj.isEmpty()) return a;
    a.mode = obj.value(QStringLiteral("mode")).toString(a.mode);
    if (a.mode != QStringLiteral("ppb")) a.mode = QStringLiteral("text");
    a.path = obj.value(QStringLiteral("path")).toString(a.path);
    const int sz = obj.value(QStringLiteral("cellSize")).toInt(a.cellSize);
    a.cellSize = (sz==8 || sz==16 || sz==32) ? sz : 0;
    a.frame = qMax(0,obj.value(QStringLiteral("frame")).toInt(a.frame));
    a.x = obj.value(QStringLiteral("x")).toInt(a.x);
    a.y = obj.value(QStringLiteral("y")).toInt(a.y);
    a.foreground = qBound(0,obj.value(QStringLiteral("foreground")).toInt(a.foreground),255);
    a.outline = qBound(0,obj.value(QStringLiteral("outline")).toInt(a.outline),255);
    a.outlineEnabled = obj.value(QStringLiteral("outlineEnabled")).toBool(a.outlineEnabled);
    const int legacyFont = qBound(1,obj.value(QStringLiteral("fontSize")).toInt(a.fontSizeX),4);
    a.fontSizeX = qBound(1,obj.value(QStringLiteral("fontSizeX")).toInt(legacyFont),4);
    a.fontSizeY = qBound(1,obj.value(QStringLiteral("fontSizeY")).toInt(legacyFont),4);
    return a;
}
QStringList listAssets(const QString &root, const QStringList &folders,
                       const QStringList &suffixes) {
    QStringList paths;
    const QDir base(root);
    for (const QString &folder : folders) {
        const QString absolute = base.filePath(folder);
        if (!QDir(absolute).exists()) continue;
        QDirIterator it(absolute,QDir::Files | QDir::NoSymLinks,QDirIterator::Subdirectories);
        while (it.hasNext()) {
            const QString found = it.next();
            if (!suffixes.contains(QFileInfo(found).suffix().toLower())) continue;
            const QString relative = QDir::cleanPath(base.relativeFilePath(found));
            if (!paths.contains(relative)) paths.append(relative);
        }
    }
    paths.sort(Qt::CaseInsensitive);
    return paths;
}
QVector<QPair<QString,QVector<WorldStart>>> listWorlds(const QString &root) {
    QVector<QPair<QString,QVector<WorldStart>>> worlds;
    const QDir dir(root);
    const QStringList files = dir.entryList({QStringLiteral("*.sbgm")}, QDir::Files, QDir::Name);
    for (const QString &name : files) {
        QFile f(dir.filePath(name));
        if (!f.open(QIODevice::ReadOnly)) continue;
        QJsonParseError error;
        const QJsonDocument doc=QJsonDocument::fromJson(f.readAll(),&error);
        if (error.error != QJsonParseError::NoError || !doc.isObject()) continue;
        QVector<WorldStart> starts;
        starts.append({QStringLiteral("default"),QObject::tr("Default")});
        for (const QJsonValue &v : doc.object().value(QStringLiteral("playerStarts")).toArray()) {
            const QJsonObject s=v.toObject();
            const QString id=s.value(QStringLiteral("id")).toString();
            if (id.isEmpty()) continue;
            QString display=s.value(QStringLiteral("name")).toString();
            if (display.isEmpty()) display = id;
            starts.append({id,display});
        }
        worlds.append({QFileInfo(name).completeBaseName(),starts});
    }
    return worlds;
}
QImage artworkImage(const QString &root, const Artwork &a, QHash<QString,QImage> &cache) {
    if (a.mode != QStringLiteral("ppb") || a.path.isEmpty()) return {};
    if (!cache.contains(a.path)) {
        SidboxPpb::Picture pic;
        if (SidboxPpb::read(QDir(root).filePath(a.path),&pic)) cache.insert(a.path,pic.indexed);
        else cache.insert(a.path,QImage());
    }
    const QImage full=cache.value(a.path);
    if (full.isNull()) return {};
    if (a.cellSize == 0) return full;
    const int cols=full.width()/a.cellSize;
    const int rows=full.height()/a.cellSize;
    if (cols<=0 || rows<=0 || a.frame>=cols*rows) return {};
    return full.copy((a.frame%cols)*a.cellSize,(a.frame/cols)*a.cellSize,a.cellSize,a.cellSize);
}
// The preview reflects the selected CLUT, without changing PPB index bytes.
QVector<QRgb> titlePalette(const QString &root, const QString &source,
                            const QStringList &ppbs, QHash<QString,QImage> &cache) {
    if (!source.isEmpty()) {
        const QVector<QRgb> palette=SidboxGamePalette::readPalette(QDir(root).filePath(source),false);
        if (palette.size()==256) return palette;
    }
    for (const QString &path:ppbs) {
        Artwork a;a.mode=QStringLiteral("ppb");a.path=path;
        QImage img=artworkImage(root,a,cache);
        if (img.colorTable().size()==256) return img.colorTable();
    }
    QVector<QRgb> fallback(256,qRgb(0,0,0));
    fallback[15]=qRgb(255,255,255);
    return fallback;
}
int chooseTitleColour(QWidget *parent, const QVector<QRgb> &palette, int current, const QString &caption) {
    QDialog chooser(parent);
    chooser.setWindowTitle(caption);
    auto *layout=new QVBoxLayout(&chooser);
    layout->addWidget(new QLabel(QObject::tr("Choose a SIDBOX foreground CLUT index. The palette indices stay unchanged."),&chooser));
    auto *scroller=new QScrollArea(&chooser);
    auto *host=new QWidget(scroller);
    auto *grid=new QGridLayout(host);
    grid->setContentsMargins(4,4,4,4);grid->setSpacing(2);
    int chosen=-1;
    for (int i=0;i<256;++i) {
        const QRgb rgb=i<palette.size()?palette[i]:qRgb(0,0,0);
        QColor colour=QColor::fromRgba(rgb);
        if (colour.alpha()==0) colour.setAlpha(255);
        auto *button=new QPushButton(host);
        button->setFixedSize(29,25);
        button->setStyleSheet(QStringLiteral("QPushButton{background:%1;border:%2px solid %3;border-radius:0px;}")
            .arg(colour.name()).arg(i==current?3:1).arg(i==current?QStringLiteral("#FFFFFF"):QStringLiteral("#666666")));
        button->setToolTip(QObject::tr("Index %1  %2").arg(i).arg(colour.name(QColor::HexArgb)));
        grid->addWidget(button,i/16,i%16);
        QObject::connect(button,&QPushButton::clicked,&chooser,[&chooser,&chosen,i]{chosen=i;chooser.accept();});
    }
    scroller->setWidget(host);
    layout->addWidget(scroller);
    chooser.resize(610,510);
    return chooser.exec()==QDialog::Accepted?chosen:-1;
}
QImage textImage(const QString &text, const Artwork &a, const QVector<QRgb> &palette) {
    if (text.isEmpty()) return {};
    // Draw the exact 8x16 SIDBOX system glyphs from the GUI Designer's
    // firmware-matched font table. QFontDatabase::FixedFont selected an OS font
    // and made the title preview differ from the actual device glyphs.
    const int width=qMax(8,int(text.toLatin1().size())*8);
    QImage glyphs(width,16,QImage::Format_ARGB32_Premultiplied);
    glyphs.fill(Qt::transparent);
    {
        QPainter gp(&glyphs);
        GuiDesignerDetail::drawCoderGirlText(gp,0,0,text,Qt::white);
    }
    const auto colorAt=[&](int i, QRgb fb)->QColor {
        return QColor::fromRgba(i>=0&&i<palette.size()?palette[i]:fb);
    };
    const QColor fg=colorAt(a.foreground,qRgb(255,255,255));
    const QColor outline=colorAt(a.outline,qRgb(0,0,0));
    auto tint=[&](QColor colour)->QImage {
        QImage result=glyphs;
        QPainter paint(&result);
        paint.setCompositionMode(QPainter::CompositionMode_SourceIn);
        paint.fillRect(result.rect(),colour);
        return result;
    };
    QImage base(width+2,18,QImage::Format_ARGB32_Premultiplied);
    base.fill(Qt::transparent);
    QPainter painter(&base);
    if (a.outlineEnabled) {
        const QImage edge=tint(outline);
        for(const QPoint &offset : {QPoint(-1,0),QPoint(1,0),QPoint(0,-1),QPoint(0,1)})
            painter.drawImage(QPoint(1,1)+offset,edge);
    }
    painter.drawImage(1,1,tint(fg));
    painter.end();
    const int scaleX=1<<(qBound(1,a.fontSizeX,4)-1);
    const int scaleY=1<<(qBound(1,a.fontSizeY,4)-1);
    return base.scaled(base.width()*scaleX,base.height()*scaleY,
                       Qt::IgnoreAspectRatio,Qt::FastTransformation);
}
QGraphicsItem *addPreviewItem(QGraphicsScene *scene, const QString &root,
                             const Artwork &a, const QString &text,
                             const QVector<QRgb> &palette, QHash<QString,QImage> &cache) {
    QImage image=artworkImage(root,a,cache);
    if (a.mode==QStringLiteral("ppb")) {
        if (image.isNull()) return nullptr;
        if (image.format()==QImage::Format_Indexed8 && palette.size()==256)image.setColorTable(palette);
    } else {
        image=textImage(text,a,palette);
    }
    if (image.isNull()) return nullptr;
    auto *item=scene->addPixmap(QPixmap::fromImage(image));
    item->setPos(a.x,a.y);
    item->setFlag(QGraphicsItem::ItemIsMovable,true);
    item->setFlag(QGraphicsItem::ItemIsSelectable,true);
    item->setZValue(2);
    return item;
}

} // namespace

bool editGameTitleScreen(QWidget *parent, const QString &projectRoot, QString *errorOut) {
    if (errorOut) errorOut->clear();
    const QVector<QPair<QString,QVector<WorldStart>>> worlds=listWorlds(projectRoot);
    const QStringList ppbs=listAssets(projectRoot,{QStringLiteral(".")},
                                     {QStringLiteral("ppb")});
    const QStringList music=listAssets(projectRoot,{QStringLiteral("music"),QStringLiteral("audio")},
                                      {QStringLiteral("mod"),QStringLiteral("s3m"),QStringLiteral("xm"),QStringLiteral("it"),
                                       QStringLiteral("med"),QStringLiteral("tfmx"),QStringLiteral("sba"),QStringLiteral("spc"),
                                       QStringLiteral("mid"),QStringLiteral("midi"),QStringLiteral("wav"),QStringLiteral("ogg"),
                                       QStringLiteral("mp3"),QStringLiteral("flac"),QStringLiteral("sid")});
    bool titleEnabled=true;
    QString title,subtitle,titleMusic,notes;
    TitleBackground background;
    QString textPalettePath;
    Artwork titleArt;titleArt.x=90;titleArt.y=42;
    Artwork subtitleArt;subtitleArt.x=105;subtitleArt.y=87;
    QVector<MenuEntry> entries;
    bool savedMenuExists=false;
    QFile in(fileName(projectRoot));
    if (in.exists()) {
        if (!in.open(QIODevice::ReadOnly)) {
            if (errorOut) *errorOut=QObject::tr("Cannot read title screen file: %1").arg(in.errorString());
            return false;
        }
        QJsonParseError parse;
        const QJsonDocument doc=QJsonDocument::fromJson(in.readAll(),&parse);
        if (parse.error!=QJsonParseError::NoError || !doc.isObject()) {
            if (errorOut) *errorOut=QObject::tr("Invalid title screen data: %1").arg(parse.errorString());
            return false;
        }
        const QJsonObject obj=doc.object();
        titleEnabled=obj.value(QStringLiteral("enabled")).toBool(true);
        title=obj.value(QStringLiteral("title")).toString();
        subtitle=obj.value(QStringLiteral("subtitle")).toString();
        titleMusic=obj.value(QStringLiteral("music")).toString();
        notes=obj.value(QStringLiteral("notes")).toString();
        const QJsonObject bg=obj.value(QStringLiteral("background")).toObject();
        background.path=bg.value(QStringLiteral("path")).toString();
        background.mode=bg.value(QStringLiteral("mode")).toString(QStringLiteral("sprite"));
        if(background.mode!=QStringLiteral("sprite") &&
           background.mode!=QStringLiteral("direct_ready") &&
           background.mode!=QStringLiteral("direct_convert"))
            background.mode=QStringLiteral("sprite");
        textPalettePath=obj.value(QStringLiteral("textPalette")).toString();
        titleArt=artFromJson(obj.value(QStringLiteral("titleArt")).toObject(),titleArt);
        subtitleArt=artFromJson(obj.value(QStringLiteral("subtitleArt")).toObject(),subtitleArt);
        savedMenuExists=obj.contains(QStringLiteral("menuItems"));
        for (const QJsonValue &v:obj.value(QStringLiteral("menuItems")).toArray()) {
            const QJsonObject item=v.toObject();
            MenuEntry e;
            e.label=item.value(QStringLiteral("label")).toString();
            e.action=item.value(QStringLiteral("action")).toString(QStringLiteral("start"));
            e.world=item.value(QStringLiteral("world")).toString();
            e.start=item.value(QStringLiteral("playerStart")).toString(QStringLiteral("default"));
            e.art.x=170;e.art.y=140+entries.size()*26;
            e.art=artFromJson(item.value(QStringLiteral("display")).toObject(),e.art);
            entries.append(e);
        }
    }
    if (!savedMenuExists) {
        const QStringList labels={QObject::tr("Start Game"),QObject::tr("Load Game"),
                                  QObject::tr("Options"),QObject::tr("Quit")};
        const QStringList actions={QStringLiteral("start"),QStringLiteral("load"),
                                   QStringLiteral("options"),QStringLiteral("quit")};
        for(int i=0;i<4;++i) {
            MenuEntry e;e.label=labels[i];e.action=actions[i];
            e.start=(i==0)?QStringLiteral("default"):QString();
            e.art.x=175;e.art.y=145+i*29;
            entries.append(e);
        }
    }

    QDialog dialog(parent);
    dialog.setWindowTitle(QObject::tr("Title Screen Designer"));
    dialog.resize(1440,900);
    dialog.setWindowState(dialog.windowState() | Qt::WindowMaximized);
    auto *outer=new QVBoxLayout(&dialog);
    outer->setContentsMargins(8,8,8,8);
    outer->setSpacing(6);
    auto *header=new QHBoxLayout;
    auto *enabled=new QCheckBox(QObject::tr("Enable project title screen"),&dialog);
    enabled->setChecked(titleEnabled);
    header->addWidget(enabled);
    header->addStretch(1);
    header->addWidget(new QLabel(QObject::tr("Design-time preview: 480 × 320"),&dialog));
    outer->addLayout(header);

    auto *columns=new QHBoxLayout;
    outer->addLayout(columns,1);
    auto *settings=new QVBoxLayout;
    columns->addLayout(settings,1);
    auto *generalBox=new QGroupBox(QObject::tr("Title Screen"),&dialog);
    auto *general=new QFormLayout(generalBox);
    auto *titleEdit=new QLineEdit(title,generalBox);
    auto *subtitleEdit=new QLineEdit(subtitle,generalBox);
    auto *musicCombo=new QComboBox(generalBox);
    musicCombo->addItem(QObject::tr("None"),QString());
    for(const QString &path:music) musicCombo->addItem(path,path);
    int musicIndex=musicCombo->findData(titleMusic);
    if(musicIndex<0 && !titleMusic.isEmpty()) {
        musicCombo->addItem(QObject::tr("Missing: %1").arg(titleMusic),titleMusic);
        musicIndex=musicCombo->count()-1;
    }
    musicCombo->setCurrentIndex(qMax(0,musicIndex));
    auto *notesEdit=new QPlainTextEdit(notes,generalBox);
    notesEdit->setMinimumHeight(90);
    general->addRow(QObject::tr("Game title"),titleEdit);
    general->addRow(QObject::tr("Subtitle"),subtitleEdit);
    general->addRow(QObject::tr("Title music"),musicCombo);
    general->addRow(QObject::tr("Notes"),notesEdit);
    settings->addWidget(generalBox);
    auto *backgroundBox=new QGroupBox(QObject::tr("Background (480 × 320)"),&dialog);
    auto *backgroundForm=new QFormLayout(backgroundBox);
    auto *backgroundAtlas=new QComboBox(backgroundBox);
    backgroundAtlas->addItem(QObject::tr("None (black)"),QString());
    for(const QString &path:ppbs) backgroundAtlas->addItem(path,path);
    int bgIndex=backgroundAtlas->findData(background.path);
    if(bgIndex<0 && !background.path.isEmpty()) {
        backgroundAtlas->addItem(QObject::tr("Missing: %1").arg(background.path),background.path);
        bgIndex=backgroundAtlas->count()-1;
    }
    backgroundAtlas->setCurrentIndex(qMax(0,bgIndex));
    auto *backgroundMode=new QComboBox(backgroundBox);
    backgroundMode->addItem(QObject::tr("Sprite / blit"),QStringLiteral("sprite"));
    backgroundMode->addItem(QObject::tr("Direct — prepared PPB"),QStringLiteral("direct_ready"));
    backgroundMode->addItem(QObject::tr("Direct — convert PPB"),QStringLiteral("direct_convert"));
    backgroundMode->setCurrentIndex(qMax(0,backgroundMode->findData(background.mode)));
    backgroundMode->setToolTip(QObject::tr("Same modes as Game Designer background resources. Direct-ready expects an already prepared column-major PPB; Direct-convert expects ordinary PPB data. This is design data for the future title runtime."));
    backgroundForm->addRow(QObject::tr("PPB artwork"),backgroundAtlas);
    backgroundForm->addRow(QObject::tr("Rendering"),backgroundMode);
    settings->addWidget(backgroundBox);
    auto *paletteBox=new QGroupBox(QObject::tr("Text foreground CLUT"),&dialog);
    auto *paletteForm=new QFormLayout(paletteBox);
    auto *paletteCombo=new QComboBox(paletteBox);
    paletteCombo->addItem(QObject::tr("Use a project PPB palette"),QString());
    const QStringList palettes=listAssets(projectRoot,{QStringLiteral(".")},
                                          {QStringLiteral("pal"),QStringLiteral("act"),QStringLiteral("ppb")});
    for(const QString &path:palettes) paletteCombo->addItem(path,path);
    int paletteIndex=paletteCombo->findData(textPalettePath);
    if(paletteIndex<0 && !textPalettePath.isEmpty()) {
        paletteCombo->addItem(QObject::tr("Missing: %1").arg(textPalettePath),textPalettePath);
        paletteIndex=paletteCombo->count()-1;
    }
    paletteCombo->setCurrentIndex(qMax(0,paletteIndex));
    paletteForm->addRow(QObject::tr("Display palette"),paletteCombo);
    settings->addWidget(paletteBox);

    auto *help=new QLabel(QObject::tr("Select Title, Subtitle or a menu row, then choose Text or PPB artwork below. Drag the element inside the screen to position it. No new PPB files are created."),&dialog);
    help->setWordWrap(true);
    settings->addWidget(help);
    settings->addStretch(1);

    auto *previewColumn=new QVBoxLayout;
    columns->addLayout(previewColumn,2);
    auto *scene=new QGraphicsScene(&dialog);
    scene->setSceneRect(0,0,480,320);
    auto *view=new TitlePreviewView(scene,&dialog);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    previewColumn->addWidget(view,1);
    auto *previewHint=new QLabel(QObject::tr("Drag title, subtitle and menu artwork. Background PPB is shown at its original size (no scaling), clipped to 480×320. Sprite/direct mode is saved for the later runtime. Pixel indices are never remapped."),&dialog);
    previewHint->setWordWrap(true);
    previewColumn->addWidget(previewHint);

    auto *right=new QVBoxLayout;
    columns->addLayout(right,3);
    auto *menuBox=new QGroupBox(QObject::tr("Menu Items"),&dialog);
    auto *menuLayout=new QVBoxLayout(menuBox);
    auto *table=new QTableWidget(menuBox);
    table->setColumnCount(4);
    table->setHorizontalHeaderLabels({QObject::tr("Option Name"),QObject::tr("Action"),
                                   QObject::tr("Destination World"),QObject::tr("Player Start")});
    table->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    table->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Stretch);
    table->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Stretch);
    table->verticalHeader()->setVisible(false);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setMinimumHeight(245);
    menuLayout->addWidget(table,1);
    auto *rowButtons=new QHBoxLayout;
    auto *add=new QPushButton(QObject::tr("Add"),menuBox);
    auto *remove=new QPushButton(QObject::tr("Remove"),menuBox);
    auto *up=new QPushButton(QObject::tr("Up"),menuBox);
    auto *down=new QPushButton(QObject::tr("Down"),menuBox);
    for(auto *b:{add,remove,up,down}) rowButtons->addWidget(b);
    rowButtons->addStretch(1);
    menuLayout->addLayout(rowButtons);
    right->addWidget(menuBox,2);

    auto *artBox=new QGroupBox(QObject::tr("Selected Element Artwork / Position"),&dialog);
    auto *artForm=new QFormLayout(artBox);
    auto *target=new QComboBox(artBox);
    auto *displayMode=new QComboBox(artBox);
    displayMode->addItem(QObject::tr("Text"),QStringLiteral("text"));
    displayMode->addItem(QObject::tr("PPB graphic"),QStringLiteral("ppb"));
    auto *atlas=new QComboBox(artBox);
    atlas->addItem(QObject::tr("None"),QString());
    for(const QString &path:ppbs) atlas->addItem(path,path);
    auto *cellSize=new QComboBox(artBox);
    cellSize->addItem(QObject::tr("Entire PPB"),0);
    cellSize->addItem(QObject::tr("8×8 cell"),8);
    cellSize->addItem(QObject::tr("16×16 cell"),16);
    cellSize->addItem(QObject::tr("32×32 cell"),32);
    auto *frame=new QSpinBox(artBox);frame->setRange(0,65535);
    auto *posX=new QSpinBox(artBox);posX->setRange(-4096,4096);
    auto *posY=new QSpinBox(artBox);posY->setRange(-4096,4096);
    artForm->addRow(QObject::tr("Element"),target);
    artForm->addRow(QObject::tr("Display as"),displayMode);
    artForm->addRow(QObject::tr("PPB atlas"),atlas);
    artForm->addRow(QObject::tr("Artwork selection"),cellSize);
    artForm->addRow(QObject::tr("Cell index"),frame);
    artForm->addRow(QObject::tr("X"),posX);
    artForm->addRow(QObject::tr("Y"),posY);
    auto *fontSizeX=new QComboBox(artBox);
    auto *fontSizeY=new QComboBox(artBox);
    for (QComboBox *box : {fontSizeX, fontSizeY}) {
        box->addItem(QObject::tr("1 — 1× (8×16 font)"),1);
        box->addItem(QObject::tr("2 — 2×"),2);
        box->addItem(QObject::tr("3 — 4×"),3);
        box->addItem(QObject::tr("4 — 8×"),4);
    }
    auto *foreground=new QSpinBox(artBox); foreground->setRange(0,255);
    auto *outlineCheck=new QCheckBox(QObject::tr("Enable outline"),artBox);
    auto *outline=new QSpinBox(artBox); outline->setRange(0,255);
    auto *fgPicker=new QPushButton(QObject::tr("Choose..."),artBox);
    auto *outlinePicker=new QPushButton(QObject::tr("Choose..."),artBox);
    auto *fgRow=new QWidget(artBox);
    auto *fgLayout=new QHBoxLayout(fgRow);fgLayout->setContentsMargins(0,0,0,0);
    fgLayout->addWidget(foreground);fgLayout->addWidget(fgPicker);
    auto *outRow=new QWidget(artBox);
    auto *outLayout=new QHBoxLayout(outRow);outLayout->setContentsMargins(0,0,0,0);
    outLayout->addWidget(outline);outLayout->addWidget(outlinePicker);
    auto *fontRow=new QWidget(artBox);
    auto *fontLayout=new QHBoxLayout(fontRow);fontLayout->setContentsMargins(0,0,0,0);
    fontLayout->addWidget(new QLabel(QObject::tr("X"),fontRow));
    fontLayout->addWidget(fontSizeX);
    fontLayout->addSpacing(8);
    fontLayout->addWidget(new QLabel(QObject::tr("Y"),fontRow));
    fontLayout->addWidget(fontSizeY);
    artForm->addRow(QObject::tr("Font size"),fontRow);
    artForm->addRow(QObject::tr("Foreground colour"),fgRow);
    artForm->addRow(QString(),outlineCheck);
    artForm->addRow(QObject::tr("Outline colour"),outRow);

    right->addWidget(artBox);
    auto *saveBox=new QDialogButtonBox(QDialogButtonBox::Save|QDialogButtonBox::Cancel,&dialog);
    outer->addWidget(saveBox);

    // Target indices: 0=title, 1=subtitle, 2+ = menu row.
    auto currentArt=[&](int index)->Artwork* {
        if(index==0)return &titleArt;
        if(index==1)return &subtitleArt;
        if(index>=2 && index-2<entries.size())return &entries[index-2].art;
        return nullptr;
    };
    QHash<QString,QImage> cache;
    QHash<QGraphicsItem*,int> rendered;
    bool rebuilding=false;
    // The scene selection callback can run inside QGraphicsItem::mousePressEvent.
    // Never destroy or re-select the clicked item before Qt finishes that event.
    bool handlingPreviewSelection=false;
    std::function<void()> render;
    std::function<void()> updateProperties;

    auto refreshTargets=[&](int selected) {
        QSignalBlocker blocker(target);
        target->clear();
        target->addItem(QObject::tr("Game Title"));
        target->addItem(QObject::tr("Subtitle"));
        for(const MenuEntry &e:entries)
            target->addItem(QObject::tr("Menu: %1").arg(e.label));
        target->setCurrentIndex(qBound(0,selected,target->count()-1));
    };
    auto populateStarts=[&](QComboBox *combo,const QString &world,const QString &selected) {
        QSignalBlocker blocker(combo);
        combo->clear();
        combo->addItem(QObject::tr("Default"),QStringLiteral("default"));
        for(const auto &w:worlds) if(w.first==world) {
            for(const WorldStart &s:w.second) {
                if(s.id==QStringLiteral("default"))continue;
                combo->addItem(s.name,s.id);
            }
            break;
        }
        int idx=combo->findData(selected);
        if(idx<0 && selected!=QStringLiteral("default") && !selected.isEmpty()) {
            combo->addItem(QObject::tr("Missing: %1").arg(selected),selected);
            idx=combo->count()-1;
        }
        combo->setCurrentIndex(qMax(0,idx));
    };
    std::function<void(int)> fillTable;
    fillTable=[&](int selectedRow) {
        QSignalBlocker blocker(table);
        table->setRowCount(0);
        for(int row=0;row<entries.size();++row) {
            const MenuEntry &e=entries[row];
            table->insertRow(row);
            auto *labelItem=new QTableWidgetItem(e.label);
            labelItem->setFlags(labelItem->flags()|Qt::ItemIsEditable);
            table->setItem(row,0,labelItem);
            auto *actionCombo=new QComboBox(table);
            actionCombo->addItem(QObject::tr("Start Game"),QStringLiteral("start"));
            actionCombo->addItem(QObject::tr("Load Game"),QStringLiteral("load"));
            actionCombo->addItem(QObject::tr("Options"),QStringLiteral("options"));
            actionCombo->addItem(QObject::tr("Quit"),QStringLiteral("quit"));
            actionCombo->addItem(QObject::tr("Goto World"),QStringLiteral("goto"));
            int actionIndex=actionCombo->findData(e.action);
            actionCombo->setCurrentIndex(qMax(0,actionIndex));
            auto *worldCombo=new QComboBox(table);
            worldCombo->addItem(QObject::tr("(First / Default World)"),QString());
            for(const auto &w:worlds)worldCombo->addItem(w.first,w.first);
            const bool destination=(e.action==QStringLiteral("goto")||e.action==QStringLiteral("start"));
            int worldIndex=worldCombo->findData(destination ? e.world : QString());
            if(destination&&worldIndex<0&&!e.world.isEmpty()){
                worldCombo->addItem(QObject::tr("Missing: %1").arg(e.world),e.world);
                worldIndex=worldCombo->count()-1;
            }
            worldCombo->setCurrentIndex(qMax(0,worldIndex));
            auto *startCombo=new QComboBox(table);
            populateStarts(startCombo,destination?e.world:QString(),destination?e.start:QStringLiteral("default"));
            worldCombo->setEnabled(destination);
            startCombo->setEnabled(destination);
            if(!destination) {
                worldCombo->setItemText(0,QObject::tr("(Not used)"));
                startCombo->setItemText(0,QObject::tr("(Not used)"));
            }
            table->setCellWidget(row,1,actionCombo);
            table->setCellWidget(row,2,worldCombo);
            table->setCellWidget(row,3,startCombo);
            QObject::connect(actionCombo,qOverload<int>(&QComboBox::currentIndexChanged),&dialog,
                [&,row,actionCombo,worldCombo,startCombo](int) {
                    if(row>=entries.size())return;
                    entries[row].action=actionCombo->currentData().toString();
                    const bool canTarget=(entries[row].action==QStringLiteral("goto")||
                                          entries[row].action==QStringLiteral("start"));
                    worldCombo->setEnabled(canTarget);
                    startCombo->setEnabled(canTarget);
                    worldCombo->setItemText(0,canTarget ? QObject::tr("(First / Default World)") : QObject::tr("(Not used)"));
                    startCombo->setItemText(0,canTarget ? QObject::tr("Default") : QObject::tr("(Not used)"));
                    if(!canTarget){
                        entries[row].world.clear();entries[row].start.clear();
                        QSignalBlocker bw(worldCombo),bs(startCombo);
                        worldCombo->setCurrentIndex(0);startCombo->setCurrentIndex(0);
                    }else if(entries[row].start.isEmpty()){
                        entries[row].start=QStringLiteral("default");
                    }
                });
            QObject::connect(worldCombo,qOverload<int>(&QComboBox::currentIndexChanged),&dialog,
                [&,row,worldCombo,startCombo](int) {
                    if(row>=entries.size())return;
                    entries[row].world=worldCombo->currentData().toString();
                    entries[row].start=QStringLiteral("default");
                    populateStarts(startCombo,entries[row].world,entries[row].start);
                });
            QObject::connect(startCombo,qOverload<int>(&QComboBox::currentIndexChanged),&dialog,
                [&,row,startCombo](int) {
                    if(row<entries.size())entries[row].start=startCombo->currentData().toString();
                });
        }
        if(selectedRow>=0 && selectedRow<table->rowCount())table->selectRow(selectedRow);
    };

    updateProperties=[&]() {
        const Artwork *a=currentArt(target->currentIndex());
        if(!a)return;
        QSignalBlocker b0(displayMode),b1(atlas),b2(cellSize),b3(frame),b4(posX),b5(posY);
        QSignalBlocker b6(fontSizeX),b7(fontSizeY),b8(foreground),b9(outlineCheck),b10(outline);
        displayMode->setCurrentIndex(a->mode==QStringLiteral("ppb")?1:0);
        int pi=atlas->findData(a->path);
        if(pi<0 && !a->path.isEmpty()) {
            atlas->addItem(QObject::tr("Missing: %1").arg(a->path),a->path);
            pi=atlas->count()-1;
        }
        atlas->setCurrentIndex(qMax(0,pi));
        cellSize->setCurrentIndex(qMax(0,cellSize->findData(a->cellSize)));
        frame->setValue(a->frame);
        posX->setValue(a->x);
        posY->setValue(a->y);
        fontSizeX->setCurrentIndex(qMax(0,fontSizeX->findData(a->fontSizeX)));
        fontSizeY->setCurrentIndex(qMax(0,fontSizeY->findData(a->fontSizeY)));
        foreground->setValue(a->foreground);
        outline->setValue(a->outline);
        outlineCheck->setChecked(a->outlineEnabled);
        const bool text=a->mode==QStringLiteral("text");
        fontSizeX->setEnabled(text);
        fontSizeY->setEnabled(text);
        foreground->setEnabled(text);fgPicker->setEnabled(text);
        outlineCheck->setEnabled(text);
        outline->setEnabled(text&&a->outlineEnabled);
        outlinePicker->setEnabled(text&&a->outlineEnabled);
        atlas->setEnabled(a->mode==QStringLiteral("ppb"));
        cellSize->setEnabled(a->mode==QStringLiteral("ppb"));
        frame->setEnabled(a->mode==QStringLiteral("ppb")&&a->cellSize!=0);
    };
    render=[&]() {
        rebuilding=true;
        {
            QSignalBlocker blocker(scene);
            scene->clear();
            rendered.clear();
            auto *background=scene->addRect(QRectF(0,0,480,320),QPen(QColor(110,110,110)),QBrush(Qt::black));
            background->setZValue(-2);
            if(!backgroundAtlas->currentData().toString().isEmpty()) {
                Artwork bg;bg.mode=QStringLiteral("ppb");bg.path=backgroundAtlas->currentData().toString();
                QImage back=artworkImage(projectRoot,bg,cache);
                // Match Game Designer::resourcePreview for an already column-major
                // framebuffer PPB. This changes the editor preview only, never bytes.
                if(backgroundMode->currentData().toString()==QStringLiteral("direct_ready")
                   &&back.format()==QImage::Format_Indexed8) {
                    QImage upright(back.height(),back.width(),QImage::Format_Indexed8);
                    if(!upright.isNull()) {
                        upright.setColorTable(back.colorTable());
                        for(int y=0;y<back.height();++y) {
                            const uchar *input=back.constScanLine(y);
                            for(int x=0;x<back.width();++x)upright.scanLine(x)[y]=input[x];
                        }
                        back=upright;
                    }
                }
                if(!back.isNull()) {
                    auto *tile=scene->addPixmap(QPixmap::fromImage(back));
                    tile->setPos(0,0);
                    tile->setZValue(-1);
                    tile->setAcceptedMouseButtons(Qt::NoButton);
                }
            }
            const QVector<QRgb> colours=titlePalette(projectRoot,paletteCombo->currentData().toString(),ppbs,cache);
            const QStringList labels={titleEdit->text(),subtitleEdit->text()};
            for(int i=0;i<2;++i) {
                const Artwork &a=(i==0)?titleArt:subtitleArt;
                if(QGraphicsItem *item=addPreviewItem(scene,projectRoot,a,labels[i],colours,cache))
                    rendered.insert(item,i);
            }
            for(int i=0;i<entries.size();++i) {
                const MenuEntry &e=entries[i];
                if(QGraphicsItem *item=addPreviewItem(scene,projectRoot,e.art,e.label,colours,cache))
                    rendered.insert(item,i+2);
            }
            scene->setSceneRect(0,0,480,320);
            for(auto it=rendered.cbegin();it!=rendered.cend();++it)
                it.key()->setSelected(it.value()==target->currentIndex());
        }
        rebuilding=false;
    };
    view->dragFinished=[&]() {
        bool changed=false;
        for(auto it=rendered.cbegin();it!=rendered.cend();++it) {
            Artwork *a=currentArt(it.value());
            if(!a)continue;
            const int x=qRound(it.key()->pos().x());
            const int y=qRound(it.key()->pos().y());
            if(a->x!=x||a->y!=y){a->x=x;a->y=y;changed=true;}
        }
        if(changed)updateProperties();
    };
    QObject::connect(scene,&QGraphicsScene::selectionChanged,&dialog,[&]() {
        if(rebuilding)return;
        const auto selected=scene->selectedItems();
        if(selected.isEmpty())return;
        QGraphicsItem *item=selected.first();
        if(!rendered.contains(item))return;
        const int idx=rendered.value(item);
        if(idx==target->currentIndex())return;
        // This signal is emitted synchronously *inside* QGraphicsItem::setSelected().
        // Only update the controls here. Rebuilding the scene would delete `item`
        // while Qt is still handling its mouse press (Stage 5.60 crash).
        handlingPreviewSelection=true;
        target->setCurrentIndex(idx);
        if(idx>=2)table->selectRow(idx-2);
        handlingPreviewSelection=false;
    });
    QObject::connect(target,qOverload<int>(&QComboBox::currentIndexChanged),&dialog,[&](int idx) {
        updateProperties();
        if(idx>=2 && table->currentRow()!=idx-2)table->selectRow(idx-2);
        // A selection change does not alter the artwork. Keep the original
        // QGraphicsItems alive and simply update their selected state.
        // In particular, never call render() from a preview mouse press.
        if(handlingPreviewSelection || rebuilding)return;
        QSignalBlocker blocker(scene);
        for(auto it=rendered.cbegin();it!=rendered.cend();++it) {
            const bool shouldSelect=(it.value()==idx);
            if(it.key()->isSelected()!=shouldSelect)
                it.key()->setSelected(shouldSelect);
        }
    });
    QObject::connect(titleEdit,&QLineEdit::textChanged,&dialog,[&](const QString &){render();});
    QObject::connect(subtitleEdit,&QLineEdit::textChanged,&dialog,[&](const QString &){render();});
    QObject::connect(table,&QTableWidget::itemChanged,&dialog,[&](QTableWidgetItem *item){
        const int row=item->row();
        if(row>=entries.size()||item->column()!=0)return;
        entries[row].label=item->text();
        refreshTargets(target->currentIndex());
        render();
    });
    QObject::connect(table,&QTableWidget::currentCellChanged,&dialog,
        [&](int row,int,int,int) {
            if(row>=0 && row<entries.size() && target->currentIndex()!=row+2)
                target->setCurrentIndex(row+2);
        });
    auto applyArt=[&]() {
        Artwork *a=currentArt(target->currentIndex());
        if(!a)return;
        a->mode=displayMode->currentData().toString();
        a->path=atlas->currentData().toString();
        a->cellSize=cellSize->currentData().toInt();
        a->frame=frame->value();
        a->x=posX->value();a->y=posY->value();
        a->fontSizeX=fontSizeX->currentData().toInt();
        a->fontSizeY=fontSizeY->currentData().toInt();
        a->foreground=foreground->value();
        a->outline=outline->value();
        a->outlineEnabled=outlineCheck->isChecked();
        updateProperties();render();
    };
    QObject::connect(displayMode,qOverload<int>(&QComboBox::currentIndexChanged),&dialog,[&](int){applyArt();});
    QObject::connect(atlas,qOverload<int>(&QComboBox::currentIndexChanged),&dialog,[&](int){applyArt();});
    QObject::connect(cellSize,qOverload<int>(&QComboBox::currentIndexChanged),&dialog,[&](int){applyArt();});
    QObject::connect(frame,qOverload<int>(&QSpinBox::valueChanged),&dialog,[&](int){applyArt();});
    QObject::connect(posX,qOverload<int>(&QSpinBox::valueChanged),&dialog,[&](int){applyArt();});
    QObject::connect(posY,qOverload<int>(&QSpinBox::valueChanged),&dialog,[&](int){applyArt();});
    QObject::connect(fontSizeX,qOverload<int>(&QComboBox::currentIndexChanged),&dialog,[&](int){applyArt();});
    QObject::connect(fontSizeY,qOverload<int>(&QComboBox::currentIndexChanged),&dialog,[&](int){applyArt();});
    QObject::connect(foreground,qOverload<int>(&QSpinBox::valueChanged),&dialog,[&](int){applyArt();});
    QObject::connect(outline,qOverload<int>(&QSpinBox::valueChanged),&dialog,[&](int){applyArt();});
    QObject::connect(outlineCheck,&QCheckBox::toggled,&dialog,[&](bool){applyArt();});
    QObject::connect(fgPicker,&QPushButton::clicked,&dialog,[&]() {
        const auto colours=titlePalette(projectRoot,paletteCombo->currentData().toString(),ppbs,cache);
        const int chosen=chooseTitleColour(&dialog,colours,foreground->value(),QObject::tr("Text foreground index"));
        if(chosen>=0)foreground->setValue(chosen);
    });
    QObject::connect(outlinePicker,&QPushButton::clicked,&dialog,[&]() {
        const auto colours=titlePalette(projectRoot,paletteCombo->currentData().toString(),ppbs,cache);
        const int chosen=chooseTitleColour(&dialog,colours,outline->value(),QObject::tr("Text outline index"));
        if(chosen>=0)outline->setValue(chosen);
    });
    QObject::connect(backgroundAtlas,qOverload<int>(&QComboBox::currentIndexChanged),&dialog,[&](int){render();});
    QObject::connect(backgroundMode,qOverload<int>(&QComboBox::currentIndexChanged),&dialog,[&](int){render();});
    QObject::connect(paletteCombo,qOverload<int>(&QComboBox::currentIndexChanged),&dialog,[&](int){render();});


    QObject::connect(add,&QPushButton::clicked,&dialog,[&]() {
        MenuEntry e;e.label=QObject::tr("New Option");e.action=QStringLiteral("start");
        e.art.x=175;e.art.y=145+entries.size()*29;
        entries.append(e);
        const int newRow=entries.size()-1;
        fillTable(newRow);refreshTargets(newRow+2);updateProperties();render();
    });
    QObject::connect(remove,&QPushButton::clicked,&dialog,[&]() {
        const int row=table->currentRow();
        if(row<0||row>=entries.size())return;
        entries.removeAt(row);
        const int next=qMin(row,entries.size()-1);
        fillTable(next);refreshTargets(next<0?0:next+2);updateProperties();render();
    });
    auto moveRow=[&](int delta) {
        const int row=table->currentRow();const int next=row+delta;
        if(row<0||next<0||next>=entries.size())return;
        entries.swapItemsAt(row,next);
        fillTable(next);refreshTargets(next+2);updateProperties();render();
    };
    QObject::connect(up,&QPushButton::clicked,&dialog,[&](){moveRow(-1);});
    QObject::connect(down,&QPushButton::clicked,&dialog,[&](){moveRow(+1);});

    QObject::connect(saveBox,&QDialogButtonBox::accepted,&dialog,[&]() {
        // Keep the default title screen fully optional; no runtime or .sbgm changes.
        QJsonObject obj;
        obj.insert(QStringLiteral("version"),4);
        obj.insert(QStringLiteral("saveSlots"),10); // reserved for the future Load Game menu runtime
        obj.insert(QStringLiteral("enabled"),enabled->isChecked());
        obj.insert(QStringLiteral("title"),titleEdit->text());
        obj.insert(QStringLiteral("subtitle"),subtitleEdit->text());
        obj.insert(QStringLiteral("music"),musicCombo->currentData().toString());
        obj.insert(QStringLiteral("notes"),notesEdit->toPlainText());
        obj.insert(QStringLiteral("background"),QJsonObject{
            {QStringLiteral("path"),backgroundAtlas->currentData().toString()},
            {QStringLiteral("mode"),backgroundMode->currentData().toString()}});
        obj.insert(QStringLiteral("textPalette"),paletteCombo->currentData().toString());
        obj.insert(QStringLiteral("titleArt"),artJson(titleArt));
        obj.insert(QStringLiteral("subtitleArt"),artJson(subtitleArt));
        QJsonArray menu;
        for(const MenuEntry &e:entries) {
            QJsonObject item;
            item.insert(QStringLiteral("label"),e.label);
            item.insert(QStringLiteral("action"),e.action);
            const bool hasDestination=(e.action==QStringLiteral("start")||e.action==QStringLiteral("goto"));
            item.insert(QStringLiteral("world"),hasDestination ? QJsonValue(e.world) : QJsonValue(QJsonValue::Null));
            item.insert(QStringLiteral("playerStart"),hasDestination ?
                        QJsonValue(e.start.isEmpty()?QStringLiteral("default"):e.start) : QJsonValue(QJsonValue::Null));
            item.insert(QStringLiteral("display"),artJson(e.art));
            menu.append(item);
        }
        obj.insert(QStringLiteral("menuItems"),menu);
        QSaveFile file(fileName(projectRoot));
        if(!file.open(QIODevice::WriteOnly)) {
            QMessageBox::warning(&dialog,QObject::tr("Title Screen Designer"),
                                 QObject::tr("Unable to save title screen: %1").arg(file.errorString()));
            return;
        }
        const QByteArray bytes=QJsonDocument(obj).toJson(QJsonDocument::Indented);
        if(file.write(bytes)!=bytes.size()||!file.commit()) {
            QMessageBox::warning(&dialog,QObject::tr("Title Screen Designer"),
                                 QObject::tr("Unable to write title-screen project file."));
            return;
        }
        dialog.accept();
    });
    QObject::connect(saveBox,&QDialogButtonBox::rejected,&dialog,&QDialog::reject);

    fillTable(0);
    refreshTargets(0);
    updateProperties();
    render();
    view->fitInView(QRectF(0,0,480,320),Qt::KeepAspectRatio);
    // Widening/Maximising the window should not alter the virtual 480×320 canvas.
    const bool accepted=dialog.exec()==QDialog::Accepted;
    // Detach scene callbacks from model references before local state is torn down.
    QObject::disconnect(scene,nullptr,&dialog,nullptr);
    QObject::disconnect(table,nullptr,&dialog,nullptr);
    QObject::disconnect(target,nullptr,&dialog,nullptr);
    view->dragFinished={};
    return accepted;
}
