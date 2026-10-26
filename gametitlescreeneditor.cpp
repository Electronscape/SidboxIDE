#include "gametitlescreeneditor.h"
#include "gamepalettepicker.h"
#include "ppbcodec.h"
#include "gamepalette.h"
#include "guidesigner_detail.h"

#include <QAbstractItemView>
#include <QApplication>
#include <QGraphicsPathItem>
#include <QGraphicsSceneMouseEvent>
#include <QShortcut>
#include <QTimer>
#include <QWheelEvent>
#include <QPointer>
#include <QCheckBox>
#include <QColorDialog>
#include <QGridLayout>
#include <QComboBox>
#include <QSettings>
#include <QStyle>
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
#include <QScrollBar>
#include <QPainterPath>
#include <QTransform>
#include <cmath>
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
#include <QKeyEvent>
#include <QPainter>
#include <QResizeEvent>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QSaveFile>
#include <QSignalBlocker>
#include <QSpinBox>
#include <QSlider>
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
    int outlineThickness = 1; // Radius in physical screen pixels, 1..4.
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

class TitlePreviewItem final : public QGraphicsPixmapItem {
public:
    TitlePreviewItem(const QPixmap &pixmap, const int *grid)
        : QGraphicsPixmapItem(pixmap), m_grid(grid) {
        setFlag(ItemSendsGeometryChanges, true);
    }
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
        m_dragging = event->button() == Qt::LeftButton;
        QGraphicsPixmapItem::mousePressEvent(event);
    }
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override {
        QGraphicsPixmapItem::mouseReleaseEvent(event);
        m_dragging = false;
    }
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override {
        if (change == ItemPositionChange && m_dragging && m_grid && *m_grid > 0) {
            const QPointF pos = value.toPointF();
            const int step = *m_grid;
            return QPointF(std::round(pos.x()/step)*step,
                           std::round(pos.y()/step)*step);
        }
        return QGraphicsPixmapItem::itemChange(change, value);
    }
private:
    const int *m_grid = nullptr;
    bool m_dragging = false;
};

class TitlePreviewView final : public QGraphicsView {
public:
    explicit TitlePreviewView(QGraphicsScene *scene, QWidget *parent = nullptr)
        : QGraphicsView(scene, parent) {
        setRenderHint(QPainter::Antialiasing, false);
        setRenderHint(QPainter::SmoothPixmapTransform, false);
        setDragMode(QGraphicsView::NoDrag);
        setBackgroundBrush(QColor(25,25,28));
        setFrameShape(QFrame::StyledPanel);
        setMinimumSize(480,350);
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        setFocusPolicy(Qt::StrongFocus);
        setToolTip(QObject::tr("Wheel or Ctrl+/-: zoom. Middle-drag: pan. Ctrl+1: 100%. Ctrl+F: fit."));
    }
    std::function<void()> dragFinished;
    void fitScreen() {
        m_fitOnResize = true;
        fitInView(QRectF(0,0,480,320),Qt::KeepAspectRatio);
    }
    void actualSize() {
        m_fitOnResize = false;
        resetTransform();
    }
protected:
    void keyPressEvent(QKeyEvent *event) override {
        if (!(event->modifiers() & Qt::ControlModifier)) {
            QGraphicsView::keyPressEvent(event);
            return;
        }
        if (event->key() == Qt::Key_1) {
            actualSize();
        } else if (event->key() == Qt::Key_F) {
            fitScreen();
        } else if (event->key() == Qt::Key_Plus || event->key() == Qt::Key_Equal ||
                   event->key() == Qt::Key_Minus) {
            const qreal oldScale = transform().m11();
            const qreal next = qBound(qreal(0.25), oldScale *
                (event->key() == Qt::Key_Minus ? qreal(0.8) : qreal(1.25)), qreal(12.0));
            m_fitOnResize = false;
            scale(next / oldScale, next / oldScale);
        } else {
            QGraphicsView::keyPressEvent(event);
            return;
        }
        event->accept();
    }
    void resizeEvent(QResizeEvent *event) override {
        QGraphicsView::resizeEvent(event);
        if (m_fitOnResize) fitScreen();
    }
    void wheelEvent(QWheelEvent *event) override {
        if (!event->angleDelta().y()) {
            QGraphicsView::wheelEvent(event);
            return;
        }
        const qreal oldScale=transform().m11();
        const qreal factor=std::pow(1.15,event->angleDelta().y()/120.0);
        const qreal newScale=qBound(0.25,oldScale*factor,12.0);
        m_fitOnResize = false;
        scale(newScale/oldScale,newScale/oldScale);
        event->accept();
    }
    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::MiddleButton) {
            m_middlePanning = true;
            m_lastPanPosition = event->position().toPoint();
            viewport()->setCursor(Qt::ClosedHandCursor);
            event->accept();
            return;
        }
        QGraphicsView::mousePressEvent(event);
    }
    void mouseMoveEvent(QMouseEvent *event) override {
        if (m_middlePanning) {
            const QPoint position = event->position().toPoint();
            const QPoint delta = position - m_lastPanPosition;
            m_lastPanPosition = position;
            horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta.x());
            verticalScrollBar()->setValue(verticalScrollBar()->value() - delta.y());
            event->accept();
            return;
        }
        QGraphicsView::mouseMoveEvent(event);
    }
    void mouseReleaseEvent(QMouseEvent *event) override {
        if (event->button() == Qt::MiddleButton && m_middlePanning) {
            m_middlePanning = false;
            viewport()->unsetCursor();
            event->accept();
            return;
        }
        QGraphicsView::mouseReleaseEvent(event);
        if (dragFinished && event->button()==Qt::LeftButton) dragFinished();
    }
private:
    bool m_fitOnResize=true;
    bool m_middlePanning=false;
    QPoint m_lastPanPosition;
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
            {QStringLiteral("outlineThickness"),a.outlineThickness},
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
    a.outlineThickness=qBound(1,obj.value(QStringLiteral("outlineThickness")).toInt(1),4);
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
// Private title-screen foreground CLUT. Keep every PPB's 8-bit indices unchanged.
QJsonArray paletteToJson(const QVector<QRgb> &colours) {
    QJsonArray result;
    for (QRgb c:colours) result.append(QStringLiteral("%1").arg(quint32(c),8,16,QLatin1Char('0')));
    return result;
}
QVector<QRgb> paletteFromJson(const QJsonArray &input) {
    if (input.size()!=256) return {};
    QVector<QRgb> result;result.reserve(256);
    for (const QJsonValue &v:input) {
        bool ok=false;
        const QString raw=v.toString();
        const quint32 c=raw.toUInt(&ok,16);
        if (!ok || raw.size()!=8) return {};
        result.push_back(QRgb(c));
    }
    return result;
}
// The generated title runtime installs this exact CLUT for the foreground plane.
// No per-pixel CPU alpha blend is required: the LCD handles indexed alpha.
bool editTitlePalette(QWidget *parent,QVector<QRgb> &clut) {
    if (clut.size()!=256) return false;
    QVector<QRgb> working=clut;
    QDialog dialog(parent);
    dialog.setWindowTitle(QObject::tr("Title Screen Foreground Palette (ARGB)"));
    auto *outer=new QVBoxLayout(&dialog);
    auto *help=new QLabel(QObject::tr("Edit 256 foreground colours including alpha (0 transparent, 255 opaque). "
        "The chosen rectangle uses this CLUT too. Other artwork using the same index shares its colour and alpha. "
        "Index 0 is reserved for transparent foreground clearing."),&dialog);
    help->setWordWrap(true);outer->addWidget(help);
    auto *grid=new QGridLayout;grid->setSpacing(2);
    QVector<QPushButton*> cells;
    for(int i=0;i<256;++i){
        auto *button=new QPushButton(&dialog);
        button->setFixedSize(28,25);
        grid->addWidget(button,i/16,i%16);cells.push_back(button);
    }
    auto update=[&](int i){
        const QColor c=QColor::fromRgba(working[i]);
        cells[i]->setToolTip(QObject::tr("CLUT %1: %2 (alpha %3)")
            .arg(i).arg(c.name(QColor::HexArgb)).arg(c.alpha()));
        cells[i]->setStyleSheet(QStringLiteral("QPushButton{background-color:rgb(%1,%2,%3);border:1px solid #666;border-radius:0px;}")
            .arg(c.red()).arg(c.green()).arg(c.blue()));
        cells[i]->setText(c.alpha()==255 ? QString() : QStringLiteral("%1").arg(c.alpha()));
    };
    for(int i=0;i<256;++i) {
        update(i);
        QObject::connect(cells[i],&QPushButton::clicked,&dialog,[&,i](){
            QColor chosen=QColorDialog::getColor(QColor::fromRgba(working[i]),&dialog,
                           QObject::tr("Edit title CLUT %1 (RGBA)").arg(i),QColorDialog::ShowAlphaChannel);
            if(!chosen.isValid())return;
            if(i==0)chosen.setAlpha(0);
            working[i]=chosen.rgba();update(i);
        });
    }
    auto *host=new QWidget(&dialog);host->setLayout(grid);
    auto *scroll=new QScrollArea(&dialog);scroll->setWidget(host);scroll->setWidgetResizable(true);
    outer->addWidget(scroll);
    auto *buttons=new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel,&dialog);
    outer->addWidget(buttons);
    QObject::connect(buttons,&QDialogButtonBox::accepted,&dialog,&QDialog::accept);
    QObject::connect(buttons,&QDialogButtonBox::rejected,&dialog,&QDialog::reject);
    dialog.resize(590,590);
    if(dialog.exec()!=QDialog::Accepted)return false;
    clut=working;
    return true;
}
int chooseTitleColour(QWidget *parent, const QVector<QRgb> &palette, int current, const QString &caption) {
    return SidboxPalettePicker::chooseIndex(parent, palette, current, caption,
        QObject::tr("Choose a SIDBOX foreground CLUT index. The palette indices stay unchanged."),
        true, true);
}

QImage textImage(const QString &text, const Artwork &a, const QVector<QRgb> &palette) {
    if (text.isEmpty()) return {};
    // Reuse the canonical 8x8 SIDBOX glyphs drawn by the GUI Designer.
    // Its GUI-specific helper doubles each font row to produce 8x16 text;
    // gfx_drawtextf(...,size_y=1) on the real game hardware is only 8px tall.
    // Collapse the doubled rows back to the native 8px BEFORE applying the
    // title designer's independent fontSizeX/fontSizeY scales. This changes
    // the preview only: no font data is duplicated and no runtime args change.
    const int width=qMax(8,int(text.toLatin1().size())*8);
    QImage guiGlyphs(width,16,QImage::Format_ARGB32_Premultiplied);
    guiGlyphs.fill(Qt::transparent);
    {
        QPainter gp(&guiGlyphs);
        GuiDesignerDetail::drawCoderGirlText(gp,0,0,text,Qt::white);
    }
    const QImage glyphs=guiGlyphs.scaled(width,8,Qt::IgnoreAspectRatio,
                                         Qt::FastTransformation);
    const auto colorAt=[&](int i, QRgb fb)->QColor {
        return QColor::fromRgba(i>=0&&i<palette.size()?palette[i]:fb);
    };
    const QColor fg=colorAt(a.foreground,qRgb(255,255,255));
    const QColor outline=colorAt(a.outline,qRgb(0,0,0));
    const int scaleX=1<<(qBound(1,a.fontSizeX,4)-1);
    const int scaleY=1<<(qBound(1,a.fontSizeY,4)-1);
    // Scale the eight native rows first: gfx_drawtextf() applies its outline
    // at +/-1 *screen pixel*, not +/-1 unscaled glyph pixel.
    const QImage scaledGlyph=glyphs.scaled(width*scaleX,8*scaleY,
                                          Qt::IgnoreAspectRatio,Qt::FastTransformation);
    auto tint=[&](QColor colour)->QImage {
        QImage result=scaledGlyph;
        QPainter paint(&result);
        paint.setCompositionMode(QPainter::CompositionMode_SourceIn);
        paint.fillRect(result.rect(),colour);
        return result;
    };
    if (!a.outlineEnabled)
        return tint(fg); // Character's (0,0) is exactly the saved X,Y.

    const int radius=qBound(1,a.outlineThickness,4);
    QImage base(scaledGlyph.width()+2*radius,scaledGlyph.height()+2*radius,
                QImage::Format_ARGB32_Premultiplied);
    base.fill(Qt::transparent);
    QPainter painter(&base);
    const QImage edge=tint(outline);
    // A Manhattan-distance outline matches runtime's four-direction offsets.
    for(int dy=-radius;dy<=radius;++dy)
        for(int dx=-radius;dx<=radius;++dx)
            if((dx || dy) && qAbs(dx)+qAbs(dy)<=radius)
                painter.drawImage(radius+dx,radius+dy,edge);
    painter.drawImage(radius,radius,tint(fg));
    painter.end();
    return base;
}
QGraphicsItem *addPreviewItem(QGraphicsScene *scene, const QString &root,
                             const Artwork &a, const QString &text,
                             const QVector<QRgb> &palette, QHash<QString,QImage> &cache,
                             const int *snapGrid) {
    QImage image=artworkImage(root,a,cache);
    if (a.mode==QStringLiteral("ppb")) {
        if (image.isNull()) return nullptr;
        if (image.format()==QImage::Format_Indexed8 && palette.size()==256)image.setColorTable(palette);
    } else {
        image=textImage(text,a,palette);
    }
    if (image.isNull()) return nullptr;
    auto *item=new TitlePreviewItem(QPixmap::fromImage(image),snapGrid);
    // Do not let outline padding shift the glyph by +1px in the preview.
    // Moving item->pos() still means the saved, unpadded artwork X/Y.
    if (a.mode!=QStringLiteral("ppb") && a.outlineEnabled)
        item->setOffset(-a.outlineThickness,-a.outlineThickness);
    scene->addItem(item);
    item->setPos(a.x,a.y);
    item->setFlag(QGraphicsItem::ItemIsMovable,true);
    item->setFlag(QGraphicsItem::ItemIsSelectable,true);
    item->setZValue(2);
    return item;
}


// Standalone second 480x320 scene. It edits the same title-screen JSON but
// deliberately never rebuilds its scene in a QGraphicsItem selection callback.
// Each control is an existing SIDBOX runtime option, not an arbitrary script.
const QStringList optionIds = {
    QStringLiteral("music"),QStringLiteral("musicVolume"),QStringLiteral("sfx"),
    QStringLiteral("sfxVolume"),QStringLiteral("shake"),QStringLiteral("textSpeed"),
    QStringLiteral("difficulty"),QStringLiteral("back")
};
const QStringList optionNames = {
    QStringLiteral("Music"),QStringLiteral("Music Volume"),QStringLiteral("Sound Effects"),
    QStringLiteral("SFX Volume"),QStringLiteral("Screen Shake"),QStringLiteral("Text Speed"),
    QStringLiteral("Difficulty"),QStringLiteral("Back")
};
QJsonObject normalisedOptions(const QJsonObject &input) {
    QJsonObject o=input;
    if(!o.contains(QStringLiteral("title")))o.insert(QStringLiteral("title"),QStringLiteral("OPTIONS"));
    if(!o.contains(QStringLiteral("background")))o.insert(QStringLiteral("background"),QJsonObject{});
    if(!o.contains(QStringLiteral("music")))o.insert(QStringLiteral("music"),true);
    if(!o.contains(QStringLiteral("musicVolume")))o.insert(QStringLiteral("musicVolume"),80);
    if(!o.contains(QStringLiteral("sfx")))o.insert(QStringLiteral("sfx"),true);
    if(!o.contains(QStringLiteral("sfxVolume")))o.insert(QStringLiteral("sfxVolume"),100);
    if(!o.contains(QStringLiteral("shake")))o.insert(QStringLiteral("shake"),true);
    if(!o.contains(QStringLiteral("textSpeed")))o.insert(QStringLiteral("textSpeed"),50);
    if(!o.contains(QStringLiteral("difficulty")))o.insert(QStringLiteral("difficulty"),1);
    if(!o.contains(QStringLiteral("easyMultiplier")))o.insert(QStringLiteral("easyMultiplier"),75);
    if(!o.contains(QStringLiteral("hardMultiplier")))o.insert(QStringLiteral("hardMultiplier"),150);
    if(!o.contains(QStringLiteral("foreground")))o.insert(QStringLiteral("foreground"),15);
    if(!o.contains(QStringLiteral("fontSizeX")))o.insert(QStringLiteral("fontSizeX"),1);
    if(!o.contains(QStringLiteral("fontSizeY")))o.insert(QStringLiteral("fontSizeY"),1);
    if(!o.contains(QStringLiteral("titleX")))o.insert(QStringLiteral("titleX"),196);
    if(!o.contains(QStringLiteral("titleY")))o.insert(QStringLiteral("titleY"),29);
    if(!o.contains(QStringLiteral("titleForeground")))o.insert(QStringLiteral("titleForeground"),o.value(QStringLiteral("foreground")));
    if(!o.contains(QStringLiteral("titleOutline")))o.insert(QStringLiteral("titleOutline"),0);
    if(!o.contains(QStringLiteral("titleOutlineEnabled")))o.insert(QStringLiteral("titleOutlineEnabled"),false);
    if(!o.contains(QStringLiteral("titleOutlineThickness")))o.insert(QStringLiteral("titleOutlineThickness"),1);
    const QJsonArray rows=o.value(QStringLiteral("items")).toArray();
    QJsonArray result;
    for(int i=0;i<optionIds.size();++i) {
        QJsonObject r=i<rows.size()?rows[i].toObject():QJsonObject{};
        if(!r.contains(QStringLiteral("label")))r.insert(QStringLiteral("label"),optionNames[i]);
        if(!r.contains(QStringLiteral("x")))r.insert(QStringLiteral("x"),72);
        if(!r.contains(QStringLiteral("y")))r.insert(QStringLiteral("y"),76+i*27);
        if(!r.contains(QStringLiteral("visible")))r.insert(QStringLiteral("visible"),true);
        if(!r.contains(QStringLiteral("foreground")))r.insert(QStringLiteral("foreground"),o.value(QStringLiteral("foreground")));
        if(!r.contains(QStringLiteral("outline")))r.insert(QStringLiteral("outline"),0);
        if(!r.contains(QStringLiteral("outlineEnabled")))r.insert(QStringLiteral("outlineEnabled"),false);
        if(!r.contains(QStringLiteral("outlineThickness")))r.insert(QStringLiteral("outlineThickness"),1);
        if((i==1 || i==3 || i==5) && !r.contains(QStringLiteral("barX")))
            r.insert(QStringLiteral("barX"),r.value(QStringLiteral("x")).toInt()+175);
        if((i==1 || i==3 || i==5) && !r.contains(QStringLiteral("barY")))
            r.insert(QStringLiteral("barY"),r.value(QStringLiteral("y")).toInt()+2);
        if((i==1 || i==3 || i==5) && !r.contains(QStringLiteral("barColour")))
            r.insert(QStringLiteral("barColour"),r.value(QStringLiteral("foreground")));
        result.append(r);
    }
    o.insert(QStringLiteral("items"),result);
    return o;
}

bool editOptionsDesign(QWidget *parent,const QString &root,QJsonObject &options,
                       const QStringList &ppbs,const QVector<QRgb> &clut,
                       int *snapGrid,const QString &fallbackBackground,
                       const QString &fallbackMode,const QString &selectorType,
                       int selectorColour) {
    QJsonObject state=normalisedOptions(options);
    QDialog dialog(parent);
    dialog.setWindowTitle(QObject::tr("Title Screen Designer / Options Screen"));
    dialog.resize(1480,840);
    auto *whole=new QVBoxLayout(&dialog);
    auto *hint=new QLabel(QObject::tr("Design the 480 x 320 Options screen. Tick only the options your game needs. "
        "Drag labels and individual sliders. FIRE2 always returns to the main menu."),&dialog);
    hint->setWordWrap(true);whole->addWidget(hint);
    auto *columns=new QHBoxLayout;whole->addLayout(columns,1);

    auto *left=new QWidget(&dialog);left->setMinimumWidth(285);left->setMaximumWidth(345);
    auto *leftCol=new QVBoxLayout(left);columns->addWidget(left);
    auto *form=new QFormLayout;leftCol->addLayout(form);
    auto *heading=new QLineEdit(state.value(QStringLiteral("title")).toString(),left);
    form->addRow(QObject::tr("Heading"),heading);
    auto *bg=new QComboBox(left);bg->addItem(QObject::tr("Use Main Menu background"),QString());
    for(const QString &ppb:ppbs)bg->addItem(ppb,ppb);
    const QJsonObject oldBg=state.value(QStringLiteral("background")).toObject();
    const QString bgPath=oldBg.value(QStringLiteral("path")).toString();
    if(!bgPath.isEmpty() && bg->findData(bgPath)<0)bg->addItem(QObject::tr("Missing: %1").arg(bgPath),bgPath);
    bg->setCurrentIndex(qMax(0,bg->findData(bgPath)));
    form->addRow(QObject::tr("Background PPB"),bg);
    auto *bgMode=new QComboBox(left);
    bgMode->addItem(QObject::tr("Sprite / blit"),QStringLiteral("sprite"));
    bgMode->addItem(QObject::tr("Direct, prepared PPB"),QStringLiteral("direct_ready"));
    bgMode->addItem(QObject::tr("Direct, convert PPB"),QStringLiteral("direct_convert"));
    bgMode->setCurrentIndex(qMax(0,bgMode->findData(oldBg.value(QStringLiteral("mode")).toString(QStringLiteral("sprite")))));
    form->addRow(QObject::tr("Rendering"),bgMode);
    auto *sizeRow=new QWidget(left);auto *sizeLayout=new QHBoxLayout(sizeRow);sizeLayout->setContentsMargins(0,0,0,0);
    auto *sizeX=new QSpinBox(left);auto *sizeY=new QSpinBox(left);
    for(QSpinBox *s:{sizeX,sizeY})s->setRange(1,4);
    sizeX->setValue(state.value(QStringLiteral("fontSizeX")).toInt(1));
    sizeY->setValue(state.value(QStringLiteral("fontSizeY")).toInt(1));
    sizeLayout->addWidget(new QLabel(QStringLiteral("X"),sizeRow));sizeLayout->addWidget(sizeX);
    sizeLayout->addWidget(new QLabel(QStringLiteral("Y"),sizeRow));sizeLayout->addWidget(sizeY);
    form->addRow(QObject::tr("Font size"),sizeRow);
    auto *gridChoice=new QComboBox(left);
    for(int n:{0,1,2,4,8})gridChoice->addItem(n?QObject::tr("%1 pixels").arg(n):QObject::tr("Off"),n);
    gridChoice->setCurrentIndex(qMax(0,gridChoice->findData(*snapGrid)));
    form->addRow(QObject::tr("Snap grid"),gridChoice);
    leftCol->addWidget(new QLabel(QObject::tr("Default preferences (start-of-game values)"),left));
    auto *prefs=new QFormLayout;leftCol->addLayout(prefs);
    auto check=[&](const char *key){auto *c=new QCheckBox(left);c->setChecked(state.value(QLatin1String(key)).toBool());prefs->addRow(QLatin1String(key),c);return c;};
    auto *musicOn=check("music");auto *sfxOn=check("sfx");auto *shakeOn=check("shake");
    auto slider=[&](const char *label,const char *key){auto *s=new QSlider(Qt::Horizontal,left);s->setRange(0,100);
        s->setSingleStep(5);s->setPageStep(10);s->setValue(state.value(QLatin1String(key)).toInt());
        prefs->addRow(QLatin1String(label),s);return s;};
    auto *musicVol=slider("Music volume","musicVolume");
    auto *sfxVol=slider("SFX volume","sfxVolume");
    auto *speed=slider("Text speed","textSpeed");
    auto *diff=new QComboBox(left);diff->addItems({QObject::tr("Easy"),QObject::tr("Normal"),QObject::tr("Hard")});
    diff->setCurrentIndex(qBound(0,state.value(QStringLiteral("difficulty")).toInt(1),2));
    prefs->addRow(QObject::tr("Difficulty"),diff);
    auto *multis=new QWidget(left);auto *multiLayout=new QHBoxLayout(multis);multiLayout->setContentsMargins(0,0,0,0);
    auto *easy=new QSpinBox(left);auto *hard=new QSpinBox(left);
    for(QSpinBox *spin:{easy,hard}){spin->setRange(25,300);spin->setSuffix(QStringLiteral("%"));}
    easy->setValue(state.value(QStringLiteral("easyMultiplier")).toInt(75));
    hard->setValue(state.value(QStringLiteral("hardMultiplier")).toInt(150));
    multiLayout->addWidget(new QLabel(QObject::tr("Easy"),multis));multiLayout->addWidget(easy);
    multiLayout->addWidget(new QLabel(QObject::tr("Hard"),multis));multiLayout->addWidget(hard);
    prefs->addRow(QObject::tr("Difficulty multipliers"),multis);
    leftCol->addStretch(1);

    auto *middle=new QVBoxLayout;columns->addLayout(middle,2);
    auto *scene=new QGraphicsScene(&dialog);scene->setSceneRect(0,0,480,320);
    auto *view=new TitlePreviewView(scene,&dialog);middle->addWidget(view,1);
    auto *toolbar=new QHBoxLayout;auto *fit=new QPushButton(QObject::tr("Fit"),&dialog);
    auto *actual=new QPushButton(QObject::tr("100%"),&dialog);
    auto *undo=new QPushButton(QObject::tr("Undo"),&dialog);auto *redo=new QPushButton(QObject::tr("Redo"),&dialog);
    for(auto *b:{fit,actual,undo,redo})toolbar->addWidget(b);
    toolbar->addStretch();middle->addLayout(toolbar);
    QObject::connect(fit,&QPushButton::clicked,view,&TitlePreviewView::fitScreen);
    QObject::connect(actual,&QPushButton::clicked,view,&TitlePreviewView::actualSize);

    auto *right=new QWidget(&dialog);right->setMinimumWidth(340);right->setMaximumWidth(420);
    auto *rightCol=new QVBoxLayout(right);columns->addWidget(right);
    auto *table=new QTableWidget(8,3,right);
    table->setHorizontalHeaderLabels({QObject::tr("Show"),QObject::tr("Setting"),QObject::tr("Label")});
    table->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Stretch);
    table->verticalHeader()->setVisible(false);table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);table->setMinimumHeight(260);
    rightCol->addWidget(new QLabel(QObject::tr("Visible elements / editable labels"),right));
    rightCol->addWidget(table,1);
    auto *formRight=new QFormLayout;rightCol->addLayout(formRight);
    auto *selected=new QComboBox(right);
    selected->addItem(QObject::tr("Options Heading"),-1);
    for(int i=0;i<optionIds.size();++i)selected->addItem(optionNames[i],i);
    selected->addItem(QObject::tr("Music Volume Bar"),8);
    selected->addItem(QObject::tr("SFX Volume Bar"),9);
    selected->addItem(QObject::tr("Text Speed Bar"),10);
    formRight->addRow(QObject::tr("Selected element"),selected);
    auto *text=new QLineEdit(right);formRight->addRow(QObject::tr("Label"),text);
    auto *coords=new QWidget(right);auto *coordRow=new QHBoxLayout(coords);coordRow->setContentsMargins(0,0,0,0);
    auto *x=new QSpinBox(right);auto *y=new QSpinBox(right);x->setRange(-4096,4096);y->setRange(-4096,4096);
    coordRow->addWidget(new QLabel(QStringLiteral("X"),coords));coordRow->addWidget(x);
    coordRow->addWidget(new QLabel(QStringLiteral("Y"),coords));coordRow->addWidget(y);
    formRight->addRow(QObject::tr("Position"),coords);
    auto *foreground=new QSpinBox(right);foreground->setRange(0,255);
    auto *fgBtn=new QPushButton(QObject::tr("CLUT..."),right);
    auto *foreRow=new QWidget(right);auto *foreLayout=new QHBoxLayout(foreRow);foreLayout->setContentsMargins(0,0,0,0);
    foreLayout->addWidget(foreground);foreLayout->addWidget(fgBtn);
    formRight->addRow(QObject::tr("Foreground / bar colour"),foreRow);
    auto *outlined=new QCheckBox(QObject::tr("Enable outline"),right);formRight->addRow(QString(),outlined);
    auto *outline=new QSpinBox(right);outline->setRange(0,255);
    auto *outlineBtn=new QPushButton(QObject::tr("CLUT..."),right);
    auto *thickness=new QSpinBox(right);thickness->setRange(1,4);
    thickness->setToolTip(QObject::tr("Physical screen-pixel outline radius. Thicker outlines cost more draw calls."));
    auto *outRow=new QWidget(right);auto *outLayout=new QHBoxLayout(outRow);outLayout->setContentsMargins(0,0,0,0);
    outLayout->addWidget(outline);outLayout->addWidget(outlineBtn);
    formRight->addRow(QObject::tr("Outline colour"),outRow);
    formRight->addRow(QObject::tr("Outline thickness"),thickness);
    rightCol->addWidget(new QLabel(QObject::tr("Sliders have independent X/Y positions. A hidden row and its slider are omitted from the game menu."),right));
    rightCol->addStretch(1);
    auto *buttons=new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel,&dialog);
    whole->addWidget(buttons);
    QObject::connect(buttons,&QDialogButtonBox::accepted,&dialog,&QDialog::accept);
    QObject::connect(buttons,&QDialogButtonBox::rejected,&dialog,&QDialog::reject);

    QHash<QString,QImage> cache;
    QVector<QGraphicsItem*> items(12,nullptr); // heading, 8 labels, 3 independent bars
    QGraphicsPathItem *selectionOverlay=nullptr;
    int grid=gridChoice->currentData().toInt();
    bool redrawing=false;
    bool restoring=false;
    QVector<QJsonObject> history;
    int historyIndex=0;
    auto rowAt=[&](int i){return state.value(QStringLiteral("items")).toArray().at(i).toObject();};
    auto setRow=[&](int i,const QJsonObject &r){QJsonArray rows=state.value(QStringLiteral("items")).toArray();
        rows.replace(i,r);state.insert(QStringLiteral("items"),rows);};
    auto controlRow=[&](int idx){return idx==8?1:idx==9?3:idx==10?5:idx;};
    auto isBar=[&](int idx){return idx>=8 && idx<=10;};
    auto getPos=[&](int idx)->QPoint {
        if(idx<0)return {state.value(QStringLiteral("titleX")).toInt(),state.value(QStringLiteral("titleY")).toInt()};
        const QJsonObject r=rowAt(controlRow(idx));
        return isBar(idx) ? QPoint(r.value(QStringLiteral("barX")).toInt(),r.value(QStringLiteral("barY")).toInt())
                          : QPoint(r.value(QStringLiteral("x")).toInt(),r.value(QStringLiteral("y")).toInt());
    };
    auto setPos=[&](int idx,QPoint pos){
        if(idx<0){state.insert(QStringLiteral("titleX"),pos.x());state.insert(QStringLiteral("titleY"),pos.y());return;}
        QJsonObject r=rowAt(controlRow(idx));
        r.insert(isBar(idx)?QStringLiteral("barX"):QStringLiteral("x"),pos.x());
        r.insert(isBar(idx)?QStringLiteral("barY"):QStringLiteral("y"),pos.y());setRow(controlRow(idx),r);
    };
    auto styleFor=[&](int idx)->Artwork {
        Artwork art;art.mode=QStringLiteral("text");
        art.fontSizeX=sizeX->value();art.fontSizeY=sizeY->value();
        if(idx<0){art.foreground=state.value(QStringLiteral("titleForeground")).toInt(15);
            art.outline=state.value(QStringLiteral("titleOutline")).toInt();
            art.outlineEnabled=state.value(QStringLiteral("titleOutlineEnabled")).toBool();
            art.outlineThickness=state.value(QStringLiteral("titleOutlineThickness")).toInt(1);}
        else {const QJsonObject r=rowAt(controlRow(idx));
            art.foreground=r.value(isBar(idx)?QStringLiteral("barColour"):QStringLiteral("foreground")).toInt(15);
            art.outline=r.value(QStringLiteral("outline")).toInt();
            art.outlineEnabled=!isBar(idx) && r.value(QStringLiteral("outlineEnabled")).toBool();
            art.outlineThickness=r.value(QStringLiteral("outlineThickness")).toInt(1);}
        const QPoint point=getPos(idx);art.x=point.x();art.y=point.y();return art;
    };
    auto syncGlobals=[&]() {
        state.insert(QStringLiteral("title"),heading->text());
        state.insert(QStringLiteral("background"),QJsonObject{{QStringLiteral("path"),bg->currentData().toString()},
                     {QStringLiteral("mode"),bgMode->currentData().toString()}});
        state.insert(QStringLiteral("fontSizeX"),sizeX->value());state.insert(QStringLiteral("fontSizeY"),sizeY->value());
        state.insert(QStringLiteral("music"),musicOn->isChecked());state.insert(QStringLiteral("musicVolume"),musicVol->value());
        state.insert(QStringLiteral("sfx"),sfxOn->isChecked());state.insert(QStringLiteral("sfxVolume"),sfxVol->value());
        state.insert(QStringLiteral("shake"),shakeOn->isChecked());state.insert(QStringLiteral("textSpeed"),speed->value());
        state.insert(QStringLiteral("difficulty"),diff->currentIndex());
        state.insert(QStringLiteral("easyMultiplier"),easy->value());state.insert(QStringLiteral("hardMultiplier"),hard->value());
    };
    auto fillTable=[&]() {
        QSignalBlocker blocker(table);
        for(int i=0;i<8;++i){const QJsonObject r=rowAt(i);
            auto *visible=new QTableWidgetItem;visible->setFlags(Qt::ItemIsEnabled|Qt::ItemIsSelectable|Qt::ItemIsUserCheckable);
            visible->setCheckState(r.value(QStringLiteral("visible")).toBool(true)?Qt::Checked:Qt::Unchecked);
            table->setItem(i,0,visible);
            auto *name=new QTableWidgetItem(optionNames[i]);name->setFlags(Qt::ItemIsEnabled|Qt::ItemIsSelectable);
            table->setItem(i,1,name);
            auto *label=new QTableWidgetItem(r.value(QStringLiteral("label")).toString());
            table->setItem(i,2,label);
        }
    };
    auto loadElement=[&]() {
        const int idx=selected->currentData().toInt();
        QSignalBlocker b1(text),b2(x),b3(y),b4(foreground),b5(outline),b6(outlined),b7(thickness);
        const QPoint pos=getPos(idx);x->setValue(pos.x());y->setValue(pos.y());
        const Artwork art=styleFor(idx);
        foreground->setValue(art.foreground);outline->setValue(art.outline);outlined->setChecked(art.outlineEnabled);thickness->setValue(art.outlineThickness);
        text->setEnabled(!isBar(idx));outlined->setEnabled(!isBar(idx));
        outline->setEnabled(!isBar(idx) && art.outlineEnabled);
        outlineBtn->setEnabled(!isBar(idx) && art.outlineEnabled);
        thickness->setEnabled(!isBar(idx) && art.outlineEnabled);
        text->setText(idx<0 ? state.value(QStringLiteral("title")).toString() :
                      isBar(idx) ? QObject::tr("(independent slider)") : rowAt(idx).value(QStringLiteral("label")).toString());
    };
    auto refreshSelector=[&]() {
        if(!selectionOverlay)return;
        const int idx=selected->currentIndex();
        if(idx<1 || idx>8 || !items[idx]){selectionOverlay->setPath(QPainterPath());return;}
        QRectF r=items[idx]->sceneBoundingRect();
        // The runtime highlights the *label text*, not the value rendered
        // beside it (ON/OFF/difficulty). Derive the exact native 8x8 glyph
        // bounds from the live item's origin; optional outlines add no size.
        if (idx>=1 && idx<=8) {
            const QString label=rowAt(idx-1).value(QStringLiteral("label")).toString();
            const int sx=1<<(qBound(1,sizeX->value(),4)-1);
            const int sy=1<<(qBound(1,sizeY->value(),4)-1);
            r=QRectF(items[idx]->pos(),QSizeF(label.toLatin1().size()*8*sx,8*sy));
        }
        const QColor colour=QColor::fromRgba(clut.value(selectorColour,qRgb(255,255,255)));
        QPainterPath path;
        if(selectorType==QStringLiteral("rect")){
            // Exact runtime rule: (x-8,y-8,width+16,height+16).
            path.addRect(r.adjusted(-8,-8,8,8));selectionOverlay->setPen(QPen(Qt::NoPen));selectionOverlay->setBrush(QBrush(colour));
        }else{
            selectionOverlay->setBrush(Qt::NoBrush);
            selectionOverlay->setPen(QPen(colour,1,Qt::SolidLine,Qt::SquareCap));
            if(selectorType==QStringLiteral("underline")){
                path.moveTo(r.left(),r.bottom()+1);path.lineTo(r.right(),r.bottom()+1);
            }else if(selectorType==QStringLiteral("arrow")){
                path.moveTo(r.left()-12,r.top());path.lineTo(r.left()-5,r.center().y());path.lineTo(r.left()-12,r.bottom());
            }else{
                path.moveTo(r.left()-10,r.top());path.lineTo(r.left()-13,r.top());
                path.lineTo(r.left()-13,r.bottom());path.lineTo(r.left()-10,r.bottom());
                path.moveTo(r.right()+10,r.top());path.lineTo(r.right()+13,r.top());
                path.lineTo(r.right()+13,r.bottom());path.lineTo(r.right()+10,r.bottom());
            }
        }
        selectionOverlay->setPath(path);
    };
    std::function<void()> render;
    render=[&]() {
        redrawing=true;
        {QSignalBlocker block(scene);
            scene->clear();items.fill(nullptr);selectionOverlay=nullptr;
            scene->addRect(0,0,480,320,QPen(Qt::NoPen),QBrush(Qt::black))->setZValue(-3);
            QString path=bg->currentData().toString(),mode=bgMode->currentData().toString();
            if(path.isEmpty()){path=fallbackBackground;mode=fallbackMode;}
            if(!path.isEmpty()){
                Artwork image;image.mode=QStringLiteral("ppb");image.path=path;
                QImage preview=artworkImage(root,image,cache);
                if(mode==QStringLiteral("direct_ready") && preview.format()==QImage::Format_Indexed8){
                    QImage transpose(preview.height(),preview.width(),QImage::Format_Indexed8);
                    transpose.setColorTable(preview.colorTable());
                    for(int iy=0;iy<preview.height();++iy)for(int ix=0;ix<preview.width();++ix)
                        transpose.scanLine(ix)[iy]=preview.constScanLine(iy)[ix];
                    preview=transpose;
                }
                if(!preview.isNull()){
                    if(preview.format()==QImage::Format_Indexed8) {
                        // BACK's PPB palette is independent of the editable
                        // foreground/title palette and always opaque.
                        QVector<QRgb> bgColours=preview.colorTable();
                        for(QRgb &c:bgColours)c=qRgba(qRed(c),qGreen(c),qBlue(c),255);
                        preview.setColorTable(bgColours);
                    }
                    auto *pic=scene->addPixmap(QPixmap::fromImage(preview));pic->setZValue(-1);
                    pic->setAcceptedMouseButtons(Qt::NoButton);
                }
            }
            if(auto *item=addPreviewItem(scene,root,styleFor(-1),heading->text(),clut,cache,&grid))items[0]=item;
            for(int i=0;i<8;++i){
                const QJsonObject r=rowAt(i);
                if(!r.value(QStringLiteral("visible")).toBool(true))continue;
                const QString label=r.value(QStringLiteral("label")).toString();
                const Artwork style=styleFor(i);
                if(auto *item=addPreviewItem(scene,root,style,label,clut,cache,&grid))items[i+1]=item;
                QString value;
                if(i==0)value=musicOn->isChecked()?QStringLiteral("ON"):QStringLiteral("OFF");
                if(i==2)value=sfxOn->isChecked()?QStringLiteral("ON"):QStringLiteral("OFF");
                if(i==4)value=shakeOn->isChecked()?QStringLiteral("ON"):QStringLiteral("OFF");
                if(i==6)value=diff->currentText();
                if(!value.isEmpty()) {
                    Artwork valueArt=style;
                    valueArt.x += label.toLatin1().size()*8*(1<<(qBound(1,style.fontSizeX,4)-1))+16;
                    if(QGraphicsItem *v=addPreviewItem(scene,root,valueArt,value,clut,cache,&grid)) {
                        v->setFlag(QGraphicsItem::ItemIsMovable,false);
                        v->setFlag(QGraphicsItem::ItemIsSelectable,false);
                        v->setAcceptedMouseButtons(Qt::NoButton);
                    }
                }
            }
            for(int j=0;j<3;++j){
                const int i=j==0?1:j==1?3:5;
                const QJsonObject r=rowAt(i);
                if(!r.value(QStringLiteral("visible")).toBool(true))continue;
                const int val=j==0?musicVol->value():j==1?sfxVol->value():speed->value();
                const int index=8+j;
                const QColor colour=QColor::fromRgba(clut.value(styleFor(index).foreground,qRgb(255,255,255)));
                QImage bar(102,8,QImage::Format_ARGB32_Premultiplied);bar.fill(Qt::black);
                QPainter paint(&bar);paint.fillRect(1,1,val,6,colour);paint.end();
                auto *item=new TitlePreviewItem(QPixmap::fromImage(bar),&grid);
                scene->addItem(item);item->setPos(getPos(index));
                item->setFlag(QGraphicsItem::ItemIsMovable,true);
                item->setFlag(QGraphicsItem::ItemIsSelectable,true);
                item->setZValue(3);items[index+1]=item;
            }
            selectionOverlay=scene->addPath(QPainterPath(),QPen(Qt::NoPen));
            selectionOverlay->setZValue(1.5);selectionOverlay->setAcceptedMouseButtons(Qt::NoButton);
            for(int i=0;i<items.size();++i)if(items[i])items[i]->setSelected(i==selected->currentIndex());
        }
        redrawing=false;refreshSelector();
    };
    auto updateHistoryButtons=[&]() {undo->setEnabled(historyIndex>0);redo->setEnabled(historyIndex+1<history.size());};
    auto commit=[&]() {
        if(restoring)return;
        syncGlobals();
        if(historyIndex>=0 && state==history[historyIndex]){render();return;}
        history.resize(historyIndex+1);
        history.push_back(state);
        if(history.size()>256)history.removeFirst();
        historyIndex=history.size()-1;
        updateHistoryButtons();render();
    };
    auto restore=[&](const QJsonObject &entry){
        restoring=true;state=entry;
        QSignalBlocker b1(heading),b2(bg),b3(bgMode),b4(sizeX),b5(sizeY),b6(musicOn),b7(sfxOn),b8(shakeOn),
            b9(musicVol),b10(sfxVol),b11(speed),b12(diff),b13(easy),b14(hard);
        heading->setText(state.value(QStringLiteral("title")).toString());
        const QJsonObject back=state.value(QStringLiteral("background")).toObject();
        bg->setCurrentIndex(qMax(0,bg->findData(back.value(QStringLiteral("path")).toString())));
        bgMode->setCurrentIndex(qMax(0,bgMode->findData(back.value(QStringLiteral("mode")).toString())));
        sizeX->setValue(state.value(QStringLiteral("fontSizeX")).toInt(1));
        sizeY->setValue(state.value(QStringLiteral("fontSizeY")).toInt(1));
        musicOn->setChecked(state.value(QStringLiteral("music")).toBool());
        sfxOn->setChecked(state.value(QStringLiteral("sfx")).toBool());
        shakeOn->setChecked(state.value(QStringLiteral("shake")).toBool());
        musicVol->setValue(state.value(QStringLiteral("musicVolume")).toInt());
        sfxVol->setValue(state.value(QStringLiteral("sfxVolume")).toInt());
        speed->setValue(state.value(QStringLiteral("textSpeed")).toInt());
        diff->setCurrentIndex(state.value(QStringLiteral("difficulty")).toInt(1));
        easy->setValue(state.value(QStringLiteral("easyMultiplier")).toInt(75));
        hard->setValue(state.value(QStringLiteral("hardMultiplier")).toInt(150));
        fillTable();loadElement();restoring=false;updateHistoryButtons();render();
    };
    QObject::connect(undo,&QPushButton::clicked,&dialog,[&](){if(historyIndex>0)restore(history[--historyIndex]);});
    QObject::connect(redo,&QPushButton::clicked,&dialog,[&](){if(historyIndex+1<history.size())restore(history[++historyIndex]);});
    auto *undoKey=new QShortcut(QKeySequence::Undo,&dialog);
    auto *redoKey=new QShortcut(QKeySequence::Redo,&dialog);
    auto *redoAlt=new QShortcut(QKeySequence(QStringLiteral("Ctrl+Shift+Z")),&dialog);
    QObject::connect(undoKey,&QShortcut::activated,undo,&QPushButton::click);
    QObject::connect(redoKey,&QShortcut::activated,redo,&QPushButton::click);
    QObject::connect(redoAlt,&QShortcut::activated,redo,&QPushButton::click);

    view->dragFinished=[&]() {
        bool changed=false;
        for(int i=0;i<items.size();++i){
            if(!items[i])continue;
            const int idx=i-1;
            const QPoint point(qRound(items[i]->pos().x()),qRound(items[i]->pos().y()));
            if(point!=getPos(idx)){setPos(idx,point);changed=true;}
        }
        if(changed)commit();else refreshSelector();
        loadElement();
    };
    QObject::connect(scene,&QGraphicsScene::selectionChanged,&dialog,[&](){
        if(redrawing)return;
        for(int i=0;i<items.size();++i){
            if(items[i] && items[i]->isSelected()){
                // Never rebuild QGraphicsScene from a live mousePressEvent.
                if(selected->currentIndex()!=i){QSignalBlocker b(selected);selected->setCurrentIndex(i);loadElement();}
                refreshSelector();return;
            }
        }
    });
    QObject::connect(selected,qOverload<int>(&QComboBox::currentIndexChanged),&dialog,[&](int idx){
        loadElement();
        if(idx>=1 && idx<=8 && table->currentRow()!=idx-1){QSignalBlocker blocker(table);table->selectRow(idx-1);}
        QSignalBlocker blocker(scene);
        for(int i=0;i<items.size();++i)if(items[i])items[i]->setSelected(i==idx);
        refreshSelector();
    });
    QObject::connect(table,&QTableWidget::currentCellChanged,&dialog,[&](int row,int,int,int){
        if(row>=0 && row<8 && selected->currentIndex()!=row+1)selected->setCurrentIndex(row+1);
    });
    QObject::connect(table,&QTableWidget::itemChanged,&dialog,[&](QTableWidgetItem *item){
        if(restoring || !item || item->row()<0 || item->row()>=8)return;
        const int i=item->row();QJsonObject r=rowAt(i);
        if(item->column()==0)r.insert(QStringLiteral("visible"),item->checkState()==Qt::Checked);
        if(item->column()==2)r.insert(QStringLiteral("label"),item->text());
        setRow(i,r);loadElement();commit();
    });
    QObject::connect(heading,&QLineEdit::textChanged,&dialog,[&](const QString &){
        commit();
        if(selected->currentData().toInt()==-1)loadElement();
    });
    QObject::connect(text,&QLineEdit::textChanged,&dialog,[&](const QString &value){
        const int idx=selected->currentData().toInt();
        if(idx<0){heading->setText(value);return;}
        if(isBar(idx))return;
        QJsonObject r=rowAt(idx);r.insert(QStringLiteral("label"),value);setRow(idx,r);
        {QSignalBlocker blocker(table);table->item(idx,2)->setText(value);}
        commit();
    });
    auto applyElement=[&]() {
        if(restoring)return;
        const int idx=selected->currentData().toInt();
        setPos(idx,QPoint(x->value(),y->value()));
        if(idx<0){state.insert(QStringLiteral("titleForeground"),foreground->value());
            state.insert(QStringLiteral("titleOutline"),outline->value());
            state.insert(QStringLiteral("titleOutlineEnabled"),outlined->isChecked());
            state.insert(QStringLiteral("titleOutlineThickness"),thickness->value());}
        else {QJsonObject r=rowAt(controlRow(idx));
            r.insert(isBar(idx)?QStringLiteral("barColour"):QStringLiteral("foreground"),foreground->value());
            if(!isBar(idx)){
                r.insert(QStringLiteral("outline"),outline->value());
                r.insert(QStringLiteral("outlineEnabled"),outlined->isChecked());
                r.insert(QStringLiteral("outlineThickness"),thickness->value());
            }
            setRow(controlRow(idx),r);
        }
        outline->setEnabled(!isBar(idx) && outlined->isChecked());
        outlineBtn->setEnabled(!isBar(idx) && outlined->isChecked());
        thickness->setEnabled(!isBar(idx) && outlined->isChecked());
        commit();
    };
    for(QSpinBox *s:{x,y,foreground,outline,thickness})QObject::connect(s,qOverload<int>(&QSpinBox::valueChanged),&dialog,[&](int){applyElement();});
    QObject::connect(outlined,&QCheckBox::toggled,&dialog,[&](bool){applyElement();});
    QObject::connect(fgBtn,&QPushButton::clicked,&dialog,[&](){
        const int n=chooseTitleColour(&dialog,clut,foreground->value(),QObject::tr("Options foreground CLUT"));
        if(n>=0)foreground->setValue(n);
    });
    QObject::connect(outlineBtn,&QPushButton::clicked,&dialog,[&](){
        const int n=chooseTitleColour(&dialog,clut,outline->value(),QObject::tr("Options outline CLUT"));
        if(n>=0)outline->setValue(n);
    });
    for(QComboBox *c:{bg,bgMode,diff})QObject::connect(c,qOverload<int>(&QComboBox::currentIndexChanged),&dialog,[&](int){commit();});
    for(QSpinBox *s:{sizeX,sizeY,easy,hard})QObject::connect(s,qOverload<int>(&QSpinBox::valueChanged),&dialog,[&](int){commit();});
    for(QCheckBox *c:{musicOn,sfxOn,shakeOn})QObject::connect(c,&QCheckBox::toggled,&dialog,[&](bool){commit();});
    for(QSlider *s:{musicVol,sfxVol,speed})QObject::connect(s,&QSlider::valueChanged,&dialog,[&](int){commit();});
    QObject::connect(gridChoice,qOverload<int>(&QComboBox::currentIndexChanged),&dialog,[&](int){grid=gridChoice->currentData().toInt();});
    fillTable();loadElement();syncGlobals();history.append(state);updateHistoryButtons();
    render();view->fitScreen();
    const bool accepted=dialog.exec()==QDialog::Accepted;
    QObject::disconnect(scene,nullptr,&dialog,nullptr);
    view->dragFinished={};
    if(!accepted)return false;
    syncGlobals();options=state;*snapGrid=grid;
    return true;
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
    QString selectorType=QStringLiteral("brackets");
    int selectorColour=15;
    QVector<QRgb> titleClutOverride;
    int snapGrid=8;
    QJsonObject optionsScreen;

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
        optionsScreen=obj.value(QStringLiteral("optionsScreen")).toObject();
        titleEnabled=obj.value(QStringLiteral("enabled")).toBool(true);
        title=obj.value(QStringLiteral("title")).toString();
        subtitle=obj.value(QStringLiteral("subtitle")).toString();
        titleMusic=obj.value(QStringLiteral("music")).toString();
        selectorType=obj.value(QStringLiteral("menuSelector")).toString(QStringLiteral("brackets"));
        if(!QStringList{QStringLiteral("brackets"),QStringLiteral("rect"),
                        QStringLiteral("arrow"),QStringLiteral("underline")}.contains(selectorType))
            selectorType=QStringLiteral("brackets");
        selectorColour=qBound(0,obj.value(QStringLiteral("selectorColour")).toInt(15),255);
        titleClutOverride=paletteFromJson(obj.value(QStringLiteral("titleClut")).toArray());
        snapGrid=obj.value(QStringLiteral("snapGrid")).toInt(8);
        if(snapGrid!=0&&snapGrid!=1&&snapGrid!=2&&snapGrid!=4&&snapGrid!=8) snapGrid=8;
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
    auto *outer=new QVBoxLayout(&dialog);
    outer->setContentsMargins(8,8,8,8);
    outer->setSpacing(6);
    auto *header=new QHBoxLayout;
    auto *enabled=new QCheckBox(QObject::tr("Enable project title screen"),&dialog);
    enabled->setChecked(titleEnabled);
    header->addWidget(enabled);
    header->addSpacing(12);
    auto *undoButton=new QPushButton(QObject::tr("Undo"),&dialog);
    auto *redoButton=new QPushButton(QObject::tr("Redo"),&dialog);
    undoButton->setToolTip(QObject::tr("Undo last edit (Ctrl+Z)"));
    redoButton->setToolTip(QObject::tr("Redo last edit (Ctrl+Y or Ctrl+Shift+Z)"));
    header->addWidget(undoButton);
    header->addWidget(redoButton);
    auto *editOptions=new QPushButton(QObject::tr("Edit Options Screen..."),&dialog);
    editOptions->setToolTip(QObject::tr("Edit the second 480x320 Options screen, its controls and optional PPB background."));
    header->addWidget(editOptions);
    header->addSpacing(8);
    header->addWidget(new QLabel(QObject::tr("Snap"),&dialog));
    auto *snapCombo=new QComboBox(&dialog);
    for(const int grid : {0,1,2,4,8})
        snapCombo->addItem(grid==0?QObject::tr("Off"):QObject::tr("%1 px").arg(grid),grid);
    snapCombo->setCurrentIndex(qMax(0,snapCombo->findData(snapGrid)));
    snapCombo->setToolTip(QObject::tr("Snap dragged title/menu artwork to this pixel grid. Saved per project."));
    header->addWidget(snapCombo);
    auto *fitButton=new QPushButton(QObject::tr("Fit"),&dialog);
    auto *actualButton=new QPushButton(QObject::tr("100%"),&dialog);
    header->addWidget(fitButton);
    header->addWidget(actualButton);
    header->addStretch(1);
    header->addWidget(new QLabel(QObject::tr("Preview: 480 × 320  |  wheel = zoom  |  middle-drag = pan"),&dialog));
    outer->addLayout(header);

    auto *columns=new QHBoxLayout;
    outer->addLayout(columns,1);
    auto *settings=new QVBoxLayout;
    columns->addLayout(settings,2);
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
    auto *paletteEdit=new QPushButton(QObject::tr("Edit 256 RGBA colours..."),paletteBox);
    paletteEdit->setToolTip(QObject::tr("Edit the title's foreground CLUT with alpha. The PPB pixel indices and source palettes are never rewritten."));
    paletteForm->addRow(paletteEdit);
    settings->addWidget(paletteBox);

    auto *selectorBox=new QGroupBox(QObject::tr("Menu Selection (runtime)"),&dialog);
    auto *selectorForm=new QFormLayout(selectorBox);
    auto *selectorCombo=new QComboBox(selectorBox);
    selectorCombo->addItem(QObject::tr("[   ] brackets"),QStringLiteral("brackets"));
    selectorCombo->addItem(QObject::tr("Filled rectangle"),QStringLiteral("rect"));
    selectorCombo->addItem(QObject::tr("> pointer"),QStringLiteral("arrow"));
    selectorCombo->addItem(QObject::tr("Underline"),QStringLiteral("underline"));
    selectorCombo->setCurrentIndex(qMax(0,selectorCombo->findData(selectorType)));
    auto *selectorColourSpin=new QSpinBox(selectorBox);
    selectorColourSpin->setRange(0,255);
    selectorColourSpin->setValue(selectorColour);
    auto *selectorColourPicker=new QPushButton(QObject::tr("Choose..."),selectorBox);
    auto *selectorColourRow=new QWidget(selectorBox);
    auto *selectorColourLayout=new QHBoxLayout(selectorColourRow);
    selectorColourLayout->setContentsMargins(0,0,0,0);
    selectorColourLayout->addWidget(selectorColourSpin);
    selectorColourLayout->addWidget(selectorColourPicker);
    selectorForm->addRow(QObject::tr("Selector"),selectorCombo);
    selectorForm->addRow(QObject::tr("CLUT index"),selectorColourRow);
    auto *selectorOpacity=new QSpinBox(selectorBox);selectorOpacity->setRange(0,255);
    selectorOpacity->setToolTip(QObject::tr("CLUT alpha for the selected rectangle colour (0 transparent, 255 opaque). Uses the hardware foreground palette."));
    selectorForm->addRow(QObject::tr("Rectangle alpha / blend"),selectorOpacity);
    auto *controlsNote=new QLabel(QObject::tr("FIRE1: activate selected option.  FIRE2: go back from a submenu.\nThe highlight does not change item positions."),selectorBox);
    controlsNote->setWordWrap(true);
    selectorForm->addRow(controlsNote);
    settings->addWidget(selectorBox);

    auto *help=new QLabel(QObject::tr("Select Title, Subtitle or a menu row, then choose Text or PPB artwork below. Drag the element inside the screen to position it. No new PPB files are created."),&dialog);
    help->setWordWrap(true);
    settings->addWidget(help);
    settings->addStretch(1);

    auto *previewColumn=new QVBoxLayout;
    columns->addLayout(previewColumn,5);
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
    table->setMinimumWidth(360);
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
        box->addItem(QObject::tr("1 — 1× (8×8 native font)"),1);
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
    auto *outlineThickness=new QSpinBox(artBox);outlineThickness->setRange(1,4);
    artForm->addRow(QObject::tr("Outline thickness (px)"),outlineThickness);

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
    // Title text and selector share one FRONT CLUT. The background PPB has
    // its own independent, opaque BACK CLUT in the V1 runtime. Prefer the
    // background's colours as a starting point for editable foreground ink.
    auto titleColours=[&]() {
        QStringList order=ppbs;
        const QString backgroundPath=backgroundAtlas->currentData().toString();
        if(!backgroundPath.isEmpty()) {
            order.removeAll(backgroundPath);
            order.prepend(backgroundPath);
        }
        QVector<QRgb> source=titlePalette(projectRoot,paletteCombo->currentData().toString(),order,cache);
        if(titleClutOverride.size()==256)source=titleClutOverride;
        return source;
    };
    QHash<QGraphicsItem*,int> rendered;
    bool rebuilding=false;
    // The scene selection callback can run inside QGraphicsItem::mousePressEvent.
    // Never destroy or re-select the clicked item before Qt finishes that event.
    bool handlingPreviewSelection=false;
    std::function<void()> render;
    std::function<void()> updateProperties;
    std::function<void()> updateSelector;
    QGraphicsPathItem *selectorOverlay=nullptr;
    QVector<QJsonObject> history;
    int historyCursor=-1;
    bool restoringHistory=false;
    std::function<void()> remember;
    std::function<void(int)> restoreHistory;

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
                    if(remember)remember();
                });
            QObject::connect(worldCombo,qOverload<int>(&QComboBox::currentIndexChanged),&dialog,
                [&,row,worldCombo,startCombo](int) {
                    if(row>=entries.size())return;
                    entries[row].world=worldCombo->currentData().toString();
                    entries[row].start=QStringLiteral("default");
                    populateStarts(startCombo,entries[row].world,entries[row].start);
                    if(remember)remember();
                });
            QObject::connect(startCombo,qOverload<int>(&QComboBox::currentIndexChanged),&dialog,
                [&,row,startCombo](int) {
                    if(row<entries.size()){
                        entries[row].start=startCombo->currentData().toString();
                        if(remember)remember();
                    }
                });
        }
        if(selectedRow>=0 && selectedRow<table->rowCount())table->selectRow(selectedRow);
    };

    // Theme-managed dependency indicators shared with the Adventure Editor.
    for (QWidget *guarded : {static_cast<QWidget *>(fontSizeX),
                             static_cast<QWidget *>(fontSizeY),
                             static_cast<QWidget *>(foreground),
                             static_cast<QWidget *>(fgPicker),
                             static_cast<QWidget *>(outlineCheck),
                             static_cast<QWidget *>(outline),
                             static_cast<QWidget *>(outlinePicker),
                             static_cast<QWidget *>(outlineThickness),
                             static_cast<QWidget *>(atlas),
                             static_cast<QWidget *>(cellSize),
                             static_cast<QWidget *>(frame)}) {
        guarded->setProperty("adventureGuard", true);
        guarded->style()->unpolish(guarded);
        guarded->style()->polish(guarded);
    }
    updateProperties=[&]() {
        const Artwork *a=currentArt(target->currentIndex());
        if(!a)return;
        QSignalBlocker b0(displayMode),b1(atlas),b2(cellSize),b3(frame),b4(posX),b5(posY);
        QSignalBlocker b6(fontSizeX),b7(fontSizeY),b8(foreground),b9(outlineCheck),b10(outline),b11(outlineThickness);
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
        outlineThickness->setValue(a->outlineThickness);
        const bool text=a->mode==QStringLiteral("text");
        fontSizeX->setEnabled(text);
        fontSizeY->setEnabled(text);
        foreground->setEnabled(text);fgPicker->setEnabled(text);
        outlineCheck->setEnabled(text);
        outline->setEnabled(text&&a->outlineEnabled);
        outlinePicker->setEnabled(text&&a->outlineEnabled);
        outlineThickness->setEnabled(text&&a->outlineEnabled);
        atlas->setEnabled(a->mode==QStringLiteral("ppb"));
        cellSize->setEnabled(a->mode==QStringLiteral("ppb"));
        frame->setEnabled(a->mode==QStringLiteral("ppb")&&a->cellSize!=0);
        const QString textHint = QObject::tr("Disabled: choose Text instead of PPB in Display mode.");
        const QString ppbHint = QObject::tr("Disabled: choose PPB instead of Text in Display mode.");
        for (QWidget *control : {static_cast<QWidget *>(fontSizeX),
                                 static_cast<QWidget *>(fontSizeY),
                                 static_cast<QWidget *>(foreground),
                                 static_cast<QWidget *>(fgPicker),
                                 static_cast<QWidget *>(outlineCheck)})
            control->setToolTip(text ? QObject::tr("Text artwork setting.") : textHint);
        for (QWidget *control : {static_cast<QWidget *>(outline),
                                 static_cast<QWidget *>(outlinePicker),
                                 static_cast<QWidget *>(outlineThickness)})
            control->setToolTip(!text ? textHint : !a->outlineEnabled
                ? QObject::tr("Disabled: enable Text outline first.") : QObject::tr("Text outline setting."));
        for (QWidget *control : {static_cast<QWidget *>(atlas), static_cast<QWidget *>(cellSize)})
            control->setToolTip(text ? ppbHint : QObject::tr("PPB artwork setting."));
        frame->setToolTip(text ? ppbHint : a->cellSize == 0
            ? QObject::tr("Disabled: choose a nonzero PPB cell size first.")
            : QObject::tr("Choose the PPB cell to display."));
    };
    updateSelector=[&]() {
        if(!selectorOverlay) return;
        selectorOverlay->setPath(QPainterPath());
        selectorOverlay->setBrush(Qt::NoBrush);
        const int row=target->currentIndex()-2;
        if(row<0 || row>=entries.size()) return;
        QGraphicsItem *selected=nullptr;
        for(auto it=rendered.cbegin();it!=rendered.cend();++it) {
            if(it.value()==row+2) {selected=it.key();break;}
        }
        if(!selected) return;
        const auto colours=titleColours();
        const QColor ink=QColor::fromRgba(selectorColourSpin->value()<colours.size()
            ?colours[selectorColourSpin->value()]:qRgb(255,255,255));
        QRectF r=selected->sceneBoundingRect();
        // Use the actual glyph rectangle, not the transparent outline border.
        // For the native 8x8 font its upper-left pixel must be saved X,Y.
        const Artwork &a=entries[row].art;
        if (a.mode==QStringLiteral("text")) {
            const int sx=1<<(qBound(1,a.fontSizeX,4)-1);
            const int sy=1<<(qBound(1,a.fontSizeY,4)-1);
            r=QRectF(selected->pos(),QSizeF(entries[row].label.toLatin1().size()*8*sx,8*sy));
        }
        QPainterPath outlinePath;
        const QString type=selectorCombo->currentData().toString();
        if(type==QStringLiteral("brackets")) {
            const qreal l=r.left()-6, right=r.right()+6;
            outlinePath.moveTo(l+3,r.top()-1);outlinePath.lineTo(l,r.top()-1);
            outlinePath.lineTo(l,r.bottom()+1);outlinePath.lineTo(l+3,r.bottom()+1);
            outlinePath.moveTo(right-3,r.top()-1);outlinePath.lineTo(right,r.top()-1);
            outlinePath.lineTo(right,r.bottom()+1);outlinePath.lineTo(right-3,r.bottom()+1);
        } else if(type==QStringLiteral("arrow")) {
            const qreal x=r.left()-11, cy=r.center().y();
            outlinePath.moveTo(x,cy-5);outlinePath.lineTo(x+6,cy);
            outlinePath.lineTo(x,cy+5);
        } else if(type==QStringLiteral("underline")) {
            outlinePath.moveTo(r.left(),r.bottom()+1);
            outlinePath.lineTo(r.right(),r.bottom()+1);
        } else if(type==QStringLiteral("rect")) {
            // Exact runtime footprint: glyph X/Y minus 8 pixels, with
            // 8 pixels of padding on every side. Penless = no inflation.
            outlinePath.addRect(r.adjusted(-8,-8,8,8));
            QColor fill=ink;
            selectorOverlay->setBrush(fill);
        }
        selectorOverlay->setPen(type==QStringLiteral("rect")
            ? QPen(Qt::NoPen)
            : QPen(ink,1,Qt::SolidLine,Qt::SquareCap,Qt::MiterJoin));
        selectorOverlay->setPath(outlinePath);
    };
    render=[&]() {
        rebuilding=true;
        {
            QSignalBlocker blocker(scene);
            scene->clear();
            rendered.clear();
            selectorOverlay=nullptr;
            auto *background=scene->addRect(QRectF(0,0,480,320),QPen(QColor(110,110,110)),QBrush(Qt::black));
            background->setZValue(-2);
            const QVector<QRgb> colours=titleColours();
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
                    // Hardware has two CLUTs. BACK uses the source PPB's
                    // opaque palette, FRONT uses the editable title RGBA CLUT.
                    // Do not recolour the background using title text colours.
                    if (back.format()==QImage::Format_Indexed8) {
                        QVector<QRgb> bgColours=back.colorTable();
                        for (QRgb &c:bgColours)
                            c=qRgba(qRed(c),qGreen(c),qBlue(c),255);
                        back.setColorTable(bgColours);
                    }
                    auto *tile=scene->addPixmap(QPixmap::fromImage(back));
                    tile->setPos(0,0);
                    tile->setZValue(-1);
                    tile->setAcceptedMouseButtons(Qt::NoButton);
                }
            }
            const QStringList labels={titleEdit->text(),subtitleEdit->text()};
            for(int i=0;i<2;++i) {
                const Artwork &a=(i==0)?titleArt:subtitleArt;
                if(QGraphicsItem *item=addPreviewItem(scene,projectRoot,a,labels[i],colours,cache,&snapGrid))
                    rendered.insert(item,i);
            }
            for(int i=0;i<entries.size();++i) {
                const MenuEntry &e=entries[i];
                if(QGraphicsItem *item=addPreviewItem(scene,projectRoot,e.art,e.label,colours,cache,&snapGrid))
                    rendered.insert(item,i+2);
            }
            scene->setSceneRect(0,0,480,320);
            selectorOverlay=scene->addPath(QPainterPath(),QPen(Qt::NoPen));
            selectorOverlay->setZValue(1.5);
            selectorOverlay->setAcceptedMouseButtons(Qt::NoButton);
            for(auto it=rendered.cbegin();it!=rendered.cend();++it)
                it.key()->setSelected(it.value()==target->currentIndex());
            if(updateSelector) updateSelector();
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
        if(changed) {
            updateProperties();
            if(updateSelector)updateSelector();
            if(remember)remember();
        }
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
        if(updateSelector)updateSelector();
    });
    QObject::connect(target,qOverload<int>(&QComboBox::currentIndexChanged),&dialog,[&](int idx) {
        updateProperties();
        if(idx>=2 && table->currentRow()!=idx-2)table->selectRow(idx-2);
        // A selection change does not alter the artwork. Keep the original
        // QGraphicsItems alive and simply update their selected state.
        // In particular, never call render() from a preview mouse press.
        if(handlingPreviewSelection || rebuilding)return;
        if(updateSelector)updateSelector();
        QSignalBlocker blocker(scene);
        for(auto it=rendered.cbegin();it!=rendered.cend();++it) {
            const bool shouldSelect=(it.value()==idx);
            if(it.key()->isSelected()!=shouldSelect)
                it.key()->setSelected(shouldSelect);
        }
    });
    QObject::connect(titleEdit,&QLineEdit::textChanged,&dialog,[&](const QString &){render();if(remember)remember();});
    QObject::connect(subtitleEdit,&QLineEdit::textChanged,&dialog,[&](const QString &){render();if(remember)remember();});
    QObject::connect(table,&QTableWidget::itemChanged,&dialog,[&](QTableWidgetItem *item){
        const int row=item->row();
        if(row>=entries.size()||item->column()!=0)return;
        entries[row].label=item->text();
        refreshTargets(target->currentIndex());
        render();
        if(remember)remember();
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
        a->outlineThickness=outlineThickness->value();
        updateProperties();render();
        if(remember)remember();
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
    QObject::connect(outlineThickness,qOverload<int>(&QSpinBox::valueChanged),&dialog,[&](int){applyArt();});
    QObject::connect(fgPicker,&QPushButton::clicked,&dialog,[&]() {
        const auto colours=titleColours();
        const int chosen=chooseTitleColour(&dialog,colours,foreground->value(),QObject::tr("Text foreground index"));
        if(chosen>=0)foreground->setValue(chosen);
    });
    QObject::connect(outlinePicker,&QPushButton::clicked,&dialog,[&]() {
        const auto colours=titleColours();
        const int chosen=chooseTitleColour(&dialog,colours,outline->value(),QObject::tr("Text outline index"));
        if(chosen>=0)outline->setValue(chosen);
    });
    QObject::connect(backgroundAtlas,qOverload<int>(&QComboBox::currentIndexChanged),&dialog,[&](int){render();if(remember)remember();});
    QObject::connect(backgroundMode,qOverload<int>(&QComboBox::currentIndexChanged),&dialog,[&](int){render();if(remember)remember();});
    // The private title palette is stored in the project JSON, never written
    // back to an imported PPB or shared palette asset.
    auto refreshSelectorOpacity=[&]() {
        QSignalBlocker blocker(selectorOpacity);
        const QVector<QRgb> colours=titleColours();
        selectorOpacity->setValue(qAlpha(colours.value(selectorColourSpin->value(),qRgba(255,255,255,255))));
        selectorOpacity->setEnabled(selectorCombo->currentData().toString()==QStringLiteral("rect"));
    };
    QObject::connect(paletteEdit,&QPushButton::clicked,&dialog,[&](){
        QVector<QRgb> edited=titleColours();
        if(editTitlePalette(&dialog,edited)){
            titleClutOverride=edited;refreshSelectorOpacity();render();if(remember)remember();
        }
    });
    QObject::connect(selectorOpacity,qOverload<int>(&QSpinBox::valueChanged),&dialog,[&](int alpha){
        if(titleClutOverride.size()!=256)titleClutOverride=titleColours();
        const int i=selectorColourSpin->value();
        QColor c=QColor::fromRgba(titleClutOverride[i]);
        c.setAlpha(i==0?0:alpha);titleClutOverride[i]=c.rgba();
        render();if(remember)remember();
    });
    refreshSelectorOpacity();
    QObject::connect(paletteCombo,qOverload<int>(&QComboBox::currentIndexChanged),&dialog,[&](int){
        titleClutOverride.clear();refreshSelectorOpacity();render();if(remember)remember();
    });
    QObject::connect(selectorCombo,qOverload<int>(&QComboBox::currentIndexChanged),&dialog,[&](int){
        refreshSelectorOpacity();if(updateSelector)updateSelector();
        if(remember)remember();
    });
    QObject::connect(selectorColourSpin,qOverload<int>(&QSpinBox::valueChanged),&dialog,[&](int){
        refreshSelectorOpacity();if(updateSelector)updateSelector();
        if(remember)remember();
    });
    QObject::connect(selectorColourPicker,&QPushButton::clicked,&dialog,[&]() {
        const auto colours=titleColours();
        const int colour=chooseTitleColour(&dialog,colours,selectorColourSpin->value(),QObject::tr("Menu selector CLUT index"));
        if(colour>=0) selectorColourSpin->setValue(colour);
    });
    QObject::connect(snapCombo,qOverload<int>(&QComboBox::currentIndexChanged),&dialog,[&](int){
        snapGrid=snapCombo->currentData().toInt();
        if(remember)remember();
    });
    QObject::connect(fitButton,&QPushButton::clicked,view,&TitlePreviewView::fitScreen);
    QObject::connect(actualButton,&QPushButton::clicked,view,&TitlePreviewView::actualSize);
    QObject::connect(enabled,&QCheckBox::toggled,&dialog,[&](bool){if(remember)remember();});
    QObject::connect(musicCombo,qOverload<int>(&QComboBox::currentIndexChanged),&dialog,[&](int){if(remember)remember();});
    QObject::connect(notesEdit,&QPlainTextEdit::textChanged,&dialog,[&](){if(remember)remember();});


    QObject::connect(add,&QPushButton::clicked,&dialog,[&]() {
        MenuEntry e;e.label=QObject::tr("New Option");e.action=QStringLiteral("start");
        e.art.x=175;e.art.y=145+entries.size()*29;
        entries.append(e);
        const int newRow=entries.size()-1;
        fillTable(newRow);refreshTargets(newRow+2);updateProperties();render();
        if(remember)remember();
    });
    QObject::connect(remove,&QPushButton::clicked,&dialog,[&]() {
        const int row=table->currentRow();
        if(row<0||row>=entries.size())return;
        entries.removeAt(row);
        const int next=qMin(row,entries.size()-1);
        fillTable(next);refreshTargets(next<0?0:next+2);updateProperties();render();
        if(remember)remember();
    });
    auto moveRow=[&](int delta) {
        const int row=table->currentRow();const int next=row+delta;
        if(row<0||next<0||next>=entries.size())return;
        entries.swapItemsAt(row,next);
        fillTable(next);refreshTargets(next+2);updateProperties();render();
        if(remember)remember();
    };
    QObject::connect(up,&QPushButton::clicked,&dialog,[&](){moveRow(-1);});
    QObject::connect(down,&QPushButton::clicked,&dialog,[&](){moveRow(+1);});

    QObject::connect(editOptions,&QPushButton::clicked,&dialog,[&](){
        const QVector<QRgb> colours=titleColours();
        if(editOptionsDesign(&dialog,projectRoot,optionsScreen,ppbs,colours,&snapGrid,
                             backgroundAtlas->currentData().toString(),backgroundMode->currentData().toString(),
                             selectorCombo->currentData().toString(),selectorColourSpin->value())){
            QSignalBlocker blocker(snapCombo);snapCombo->setCurrentIndex(qMax(0,snapCombo->findData(snapGrid)));
            if(remember)remember();
        }
    });
    auto capture=[&]() -> QJsonObject {
        QJsonObject obj;
        obj.insert(QStringLiteral("enabled"),enabled->isChecked());
        obj.insert(QStringLiteral("title"),titleEdit->text());
        obj.insert(QStringLiteral("subtitle"),subtitleEdit->text());
        obj.insert(QStringLiteral("music"),musicCombo->currentData().toString());
        obj.insert(QStringLiteral("notes"),notesEdit->toPlainText());
        obj.insert(QStringLiteral("backgroundPath"),backgroundAtlas->currentData().toString());
        obj.insert(QStringLiteral("backgroundMode"),backgroundMode->currentData().toString());
        obj.insert(QStringLiteral("palette"),paletteCombo->currentData().toString());
        obj.insert(QStringLiteral("selector"),selectorCombo->currentData().toString());
        obj.insert(QStringLiteral("selectorColour"),selectorColourSpin->value());
        obj.insert(QStringLiteral("titleClut"),paletteToJson(titleClutOverride));
        obj.insert(QStringLiteral("snapGrid"),snapGrid);
        obj.insert(QStringLiteral("titleArt"),artJson(titleArt));
        obj.insert(QStringLiteral("subtitleArt"),artJson(subtitleArt));
        obj.insert(QStringLiteral("optionsScreen"),optionsScreen);
        QJsonArray menu;
        for(const MenuEntry &e : entries) {
            menu.append(QJsonObject{{QStringLiteral("label"),e.label},
                                    {QStringLiteral("action"),e.action},
                                    {QStringLiteral("world"),e.world},
                                    {QStringLiteral("start"),e.start},
                                    {QStringLiteral("art"),artJson(e.art)}});
        }
        obj.insert(QStringLiteral("menu"),menu);
        return obj;
    };
    auto updateHistoryButtons=[&]() {
        undoButton->setEnabled(historyCursor>0);
        redoButton->setEnabled(historyCursor>=0 && historyCursor+1<history.size());
    };
    remember=[&]() {
        if(restoringHistory)return;
        const QJsonObject obj=capture();
        if(historyCursor>=0 && history[historyCursor]==obj)return;
        while(history.size()>historyCursor+1) history.removeLast();
        history.append(obj);
        if(history.size()>256)history.removeFirst();
        historyCursor=history.size()-1;
        updateHistoryButtons();
    };
    restoreHistory=[&](int index) {
        if(index<0 || index>=history.size())return;
        restoringHistory=true;
        const QJsonObject obj=history[index];
        const int oldSelection=target->currentIndex();
        {
            QSignalBlocker b0(enabled),b1(titleEdit),b2(subtitleEdit),b3(musicCombo),b4(notesEdit);
            QSignalBlocker b5(backgroundAtlas),b6(backgroundMode),b7(paletteCombo);
            QSignalBlocker b8(selectorCombo),b9(selectorColourSpin),b10(snapCombo);
            enabled->setChecked(obj.value(QStringLiteral("enabled")).toBool());
            titleEdit->setText(obj.value(QStringLiteral("title")).toString());
            subtitleEdit->setText(obj.value(QStringLiteral("subtitle")).toString());
            notesEdit->setPlainText(obj.value(QStringLiteral("notes")).toString());
            musicCombo->setCurrentIndex(qMax(0,musicCombo->findData(obj.value(QStringLiteral("music")).toString())));
            backgroundAtlas->setCurrentIndex(qMax(0,backgroundAtlas->findData(obj.value(QStringLiteral("backgroundPath")).toString())));
            backgroundMode->setCurrentIndex(qMax(0,backgroundMode->findData(obj.value(QStringLiteral("backgroundMode")).toString())));
            paletteCombo->setCurrentIndex(qMax(0,paletteCombo->findData(obj.value(QStringLiteral("palette")).toString())));
            selectorCombo->setCurrentIndex(qMax(0,selectorCombo->findData(obj.value(QStringLiteral("selector")).toString())));
            selectorColourSpin->setValue(obj.value(QStringLiteral("selectorColour")).toInt(15));
            snapGrid=obj.value(QStringLiteral("snapGrid")).toInt(8);
            snapCombo->setCurrentIndex(qMax(0,snapCombo->findData(snapGrid)));
        }
        optionsScreen=obj.value(QStringLiteral("optionsScreen")).toObject();
        titleClutOverride=paletteFromJson(obj.value(QStringLiteral("titleClut")).toArray());
        { QSignalBlocker block(selectorOpacity); const auto clut=titleColours();
          selectorOpacity->setValue(qAlpha(clut.value(selectorColourSpin->value(),qRgba(255,255,255,255)))); }
        titleArt=artFromJson(obj.value(QStringLiteral("titleArt")).toObject(),Artwork());
        subtitleArt=artFromJson(obj.value(QStringLiteral("subtitleArt")).toObject(),Artwork());
        entries.clear();
        for(const QJsonValue &v:obj.value(QStringLiteral("menu")).toArray()) {
            const QJsonObject m=v.toObject();
            MenuEntry e;
            e.label=m.value(QStringLiteral("label")).toString();
            e.action=m.value(QStringLiteral("action")).toString();
            e.world=m.value(QStringLiteral("world")).toString();
            e.start=m.value(QStringLiteral("start")).toString();
            e.art=artFromJson(m.value(QStringLiteral("art")).toObject(),Artwork());
            entries.append(e);
        }
        fillTable(qBound(0,oldSelection-2,qMax(0,entries.size()-1)));
        refreshTargets(qBound(0,oldSelection,entries.size()+1));
        updateProperties();
        render();
        historyCursor=index;
        restoringHistory=false;
        updateHistoryButtons();
    };
    QObject::connect(undoButton,&QPushButton::clicked,&dialog,[&](){restoreHistory(historyCursor-1);});
    QObject::connect(redoButton,&QPushButton::clicked,&dialog,[&](){restoreHistory(historyCursor+1);});
    auto *undoShortcut=new QShortcut(QKeySequence::Undo,&dialog);
    auto *redoShortcut=new QShortcut(QKeySequence(QKeyCombination(Qt::ControlModifier, Qt::Key_Y)),&dialog);
    auto *redoAltShortcut=new QShortcut(QKeySequence(QKeyCombination(Qt::ControlModifier | Qt::ShiftModifier, Qt::Key_Z)),&dialog);
    // Deferring shortcut handling avoids deleting an in-place QTableWidget
    // editor while Qt is still processing that editor's key event.
    QObject::connect(undoShortcut,&QShortcut::activated,&dialog,[&](){
        QTimer::singleShot(0,&dialog,[&](){if(dialog.isVisible())restoreHistory(historyCursor-1);});
    });
    QObject::connect(redoShortcut,&QShortcut::activated,&dialog,[&](){
        QTimer::singleShot(0,&dialog,[&](){if(dialog.isVisible())restoreHistory(historyCursor+1);});
    });
    QObject::connect(redoAltShortcut,&QShortcut::activated,&dialog,[&](){
        QTimer::singleShot(0,&dialog,[&](){if(dialog.isVisible())restoreHistory(historyCursor+1);});
    });

    QObject::connect(saveBox,&QDialogButtonBox::accepted,&dialog,[&]() {
        // Keep the default title screen fully optional; no runtime or .sbgm changes.
        QJsonObject obj;
        obj.insert(QStringLiteral("version"),8);
        obj.insert(QStringLiteral("menuSelector"),selectorCombo->currentData().toString());
        obj.insert(QStringLiteral("selectorColour"),selectorColourSpin->value());
        obj.insert(QStringLiteral("titleClut"),paletteToJson(titleClutOverride));
        obj.insert(QStringLiteral("snapGrid"),snapGrid);
        obj.insert(QStringLiteral("controls"),QJsonObject{
            {QStringLiteral("activate"),QStringLiteral("fire1")},
            {QStringLiteral("back"),QStringLiteral("fire2")}});
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
        obj.insert(QStringLiteral("optionsScreen"),optionsScreen);
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
    view->fitScreen();
    remember();
    // Widening/Maximising the window should not alter the virtual 480×320 canvas.
    QSettings titleWindowSettings(QStringLiteral("Sidbox"), QStringLiteral("SidboxIDE"));
    if (!dialog.restoreGeometry(titleWindowSettings.value(
            QStringLiteral("GameTitleScreenEditor/geometry")).toByteArray()))
        dialog.setWindowState(dialog.windowState() | Qt::WindowMaximized);
    const bool accepted=dialog.exec()==QDialog::Accepted;
    titleWindowSettings.setValue(QStringLiteral("GameTitleScreenEditor/geometry"), dialog.saveGeometry());
    // Detach scene callbacks from model references before local state is torn down.
    QObject::disconnect(scene,nullptr,&dialog,nullptr);
    QObject::disconnect(table,nullptr,&dialog,nullptr);
    QObject::disconnect(target,nullptr,&dialog,nullptr);
    view->dragFinished={};
    return accepted;
}
