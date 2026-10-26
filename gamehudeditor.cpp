#include "gamehudeditor.h"
#include "gamepalettepicker.h"
#include "ppbcodec.h"
#include "gamepalette.h"
#include "guidesigner_detail.h"
#include "gamespritestamp.h"
#include <QAbstractItemView>
#include <QApplication>
#include <QCheckBox>
#include <QComboBox>
#include <QSettings>
#include <QStyle>
#include <QDialog>
#include <QDialogButtonBox>
#include <QDir>
#include <QDrag>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QMap>
#include <QPixmap>
#include <functional>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QDirIterator>
#include <QWheelEvent>
#include <QFormLayout>
#include <QGroupBox>
#include <QHash>
#include <QTimer>
#include <QHBoxLayout>
#include <QColor>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QIcon>
#include <QImage>
#include <QInputDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMessageBox>
#include <QMimeData>
#include <QMouseEvent>
#include <QPainter>
#include <QPushButton>
#include <QSaveFile>
#include <QScrollArea>
#include <QSpinBox>
#include <QSplitter>
#include <QTextStream>
#include <QVBoxLayout>
#include <algorithm>
#include <cstdlib>
#include <stdint.h>
#include <climits>

namespace {
const char *kMime = "application/x-codergirl-hud-pickup";
const char *kBarMime = "application/x-codergirl-hud-progress-bar";
const char *kStatMime = "application/x-codergirl-hud-numeric-stat";
struct Tile { int index=-1; bool fx=false, fy=false; };
struct HudLabel { QString text; int x=0,y=0; };
// A HUD counter keeps the exact source-PPB lookup, not a cropped first frame.
struct HudCounter {
    int kind=0,x=0,y=0,iw=16,ih=16;
    QString name,source;
    int icon=0,iconTileSize=8;
    bool icon2x2=false;
    QJsonArray iconCells;
    QJsonObject spriteStamp;
};
// A bar is an overlay, NOT a new PPB. Its frames are sampled from the
// existing source sheet using a frame-sized (8 or 16 pixel) cell grid.
struct HudStat { QString binding="health", label="Health"; int x=0,y=0; };
struct HudBar {
    int x=0,y=0,width=96,frameSize=8,startFrame=0,frameCount=1;
    int frameTicks=5,minimum=0,maximum=100,preview=50;
    bool loop=true;
    QString source,binding="health";
};
struct Pickup {
    int kind=0,iw=16,ih=16;
    QString name,source;
    QImage iconImage;
    int artPriority=0; // prefer an explicit inventory icon over a sprite fallback
    int icon=0,iconTileSize=8;
    bool icon2x2=false;
    QJsonArray iconCells;
    QJsonObject spriteStamp;
};
struct HudDoc {
    int columns=30, rows=5, cw=8, ch=8, colour=15, outlineColour=0;
    bool outlineEnabled=false;
    int hudX=0, hudY=0;
    QString dock="overlay"; // overlay, top, bottom (full-width reserved strip)
    QString atlas;
    QString textPalette; // shared HUD CLUT reference for tiles, text and collectible icons
    QVector<Tile> tiles;
    QVector<HudLabel> labels;
    QVector<HudCounter> counters;
    QVector<HudBar> bars;
    QVector<HudStat> stats;
    void resize(int cols,int lines) {
        QVector<Tile> updated(cols*lines);
        const int oldCols=columns, oldRows=rows;
        for (int y=0;y<std::min(lines,oldRows);++y)
            for (int x=0;x<std::min(cols,oldCols);++x)
                if (y*oldCols+x < tiles.size()) updated[y*cols+x]=tiles[y*oldCols+x];
        columns=cols; rows=lines; tiles=updated;
    }
    QJsonObject json() const {
        QJsonObject j{{"format", "SIDBOX-SHARED-HUD"}, {"version",1},
            {"columns",columns},{"rows",rows},{"cellWidth",cw},{"cellHeight",ch},
            {"atlas",atlas},{"textPalette",textPalette},{"textColour",colour},
            {"outlineEnabled",outlineEnabled},{"outlineColour",outlineColour},
            {"hudX",hudX},{"hudY",hudY},{"dock",dock}};
        QJsonArray t;
        for (const Tile &c:tiles) t.append(QJsonObject{{"index",c.index},{"flipX",c.fx},{"flipY",c.fy}});
        j.insert("cells",t);
        QJsonArray l;
        for (const HudLabel &v:labels) l.append(QJsonObject{{"text",v.text},{"x",v.x},{"y",v.y}});
        j.insert("labels",l);
        QJsonArray cnt;
        for (const HudCounter &v:counters) cnt.append(QJsonObject{{"kind",v.kind},{"x",v.x},{"y",v.y},
            {"source",v.source},{"name",v.name},{"iconWidth",v.iw},{"iconHeight",v.ih},
            {"icon",v.icon},{"iconTileSize",v.iconTileSize},{"icon2x2",v.icon2x2},
            {"iconCells",v.iconCells},{"spriteStamp",v.spriteStamp}});
        j.insert("counters",cnt);
        QJsonArray progress;
        for (const HudBar &b:bars) progress.append(QJsonObject{
            {"x",b.x},{"y",b.y},{"width",b.width},{"frameSize",b.frameSize},
            {"startFrame",b.startFrame},{"frameCount",b.frameCount},
            {"frameTicks",b.frameTicks},{"minimum",b.minimum},{"maximum",b.maximum},
            {"preview",b.preview},{"loop",b.loop},{"source",b.source},{"binding",b.binding}});
        j.insert("progressBars",progress);
        QJsonArray numbers;
        for(const HudStat &n:stats) numbers.append(QJsonObject{
            {"binding",n.binding},{"label",n.label},{"x",n.x},{"y",n.y}});
        j.insert("numericStats",numbers);
        return j;
    }
    bool load(const QJsonObject &j) {
        if (j.value("format").toString()!="SIDBOX-SHARED-HUD" || j.value("version").toInt()!=1) return false;
        columns=qBound(1,j.value("columns").toInt(30),60);
        rows=qBound(1,j.value("rows").toInt(5),40);
        cw=qBound(1,j.value("cellWidth").toInt(8),64);
        ch=qBound(1,j.value("cellHeight").toInt(8),64);
        if(columns*cw>480 || rows*ch>320) return false;
        atlas=j.value("atlas").toString();
        textPalette=j.value("textPalette").toString();
        colour=qBound(0,j.value("textColour").toInt(15),255);
        outlineEnabled=j.value("outlineEnabled").toBool(false);
        outlineColour=qBound(0,j.value("outlineColour").toInt(0),255);
        hudX=qBound(0,j.value("hudX").toInt(0),480-columns*cw);
        hudY=qBound(0,j.value("hudY").toInt(0),320-rows*ch);
        dock=j.value("dock").toString("overlay");
        if(dock!="top" && dock!="bottom")dock="overlay";
        if(dock!="overlay" && (rows*ch>=320 || columns*cw!=480))return false;
        if(dock=="top")hudY=0;
        if(dock=="bottom")hudY=320-rows*ch;
        tiles.resize(columns*rows);
        const QJsonArray arr=j.value("cells").toArray();
        for (int n=0;n<tiles.size() && n<arr.size();++n) {
            const QJsonObject c=arr[n].toObject();
            tiles[n]={c.value("index").toInt(-1),c.value("flipX").toBool(),c.value("flipY").toBool()};
        }
        labels.clear(); counters.clear(); bars.clear(); stats.clear();
        for (const QJsonValue &v:j.value("labels").toArray()) {
            const QJsonObject o=v.toObject();
            if(labels.size()<80) labels.append({o.value("text").toString().left(60),o.value("x").toInt(),o.value("y").toInt()});
        }
        for (const QJsonValue &v:j.value("counters").toArray()) {
            const QJsonObject o=v.toObject();
            if(counters.size()<32) counters.append({o.value("kind").toInt(),o.value("x").toInt(),o.value("y").toInt(),
                o.value("iconWidth").toInt(16),o.value("iconHeight").toInt(16),
                o.value("name").toString(),o.value("source").toString(),
                o.value("icon").toInt(0),o.value("iconTileSize").toInt(8),
                o.value("icon2x2").toBool(false),o.value("iconCells").toArray(),
                o.value("spriteStamp").toObject()});
        }
        for (const QJsonValue &v:j.value("numericStats").toArray()) {
            if(stats.size()>=32)break;
            const QJsonObject o=v.toObject();
            const QString binding=o.value("binding").toString();
            if(binding!="health" && binding!="lives" && binding!="score" &&
               !binding.startsWith("stat:") && !binding.startsWith("pickup:"))continue;
            stats.append({binding,o.value("label").toString(binding).left(24),
                qBound(0,o.value("x").toInt(),columns*cw-1),
                qBound(0,o.value("y").toInt(),rows*ch-1)});
        }
        for (const QJsonValue &v:j.value("progressBars").toArray()) {
            if (bars.size()>=32) break;
            const QJsonObject o=v.toObject();
            HudBar b;
            b.x=o.value("x").toInt(0); b.y=o.value("y").toInt(0);
            b.width=qBound(1,o.value("width").toInt(96),480);
            b.frameSize=o.value("frameSize").toInt(8)==16 ? 16 : 8;
            b.startFrame=qMax(0,o.value("startFrame").toInt(0));
            b.frameCount=qBound(1,o.value("frameCount").toInt(1),64);
            b.frameTicks=qBound(1,o.value("frameTicks").toInt(5),300);
            b.minimum=o.value("minimum").toInt(0);
            b.maximum=o.value("maximum").toInt(100);
            b.preview=qBound(0,o.value("preview").toInt(50),100);
            b.loop=o.value("loop").toBool(true);
            b.source=o.value("source").toString();
            b.binding=o.value("binding").toString("health");
            bars.append(b);
        }
        return true;
    }
};

static QImage loadIndexed(const QString &file) {
    SidboxPpb::Picture picture;
    if(!SidboxPpb::read(file,&picture)) return {};
    return picture.indexed;
}
// Sample individual indexed cells from the *existing* PPB. Never re-quantise
// to ARGB, change CLUT indices, or create an extra graphics file.
static QImage pickupIcon(const QString &root, const QString &path, int icon, int tileSize,
                         bool is2x2, const QJsonArray &cells, const QJsonObject &stamp)
{
    if (path.isEmpty()) return {};
    const QImage atlas=loadIndexed(QDir(root).filePath(path));
    if (atlas.isNull() || atlas.format()!=QImage::Format_Indexed8) return {};
    if (!stamp.isEmpty()) {
        const SidboxSpriteStamp sprite=SidboxSpriteStamp::fromJson(stamp);
        return sprite.active() ? sprite.compose(atlas) : QImage();
    }
    const int tile=qBound(4,tileSize,64);
    const int columns=atlas.width()/tile;
    const int rows=atlas.height()/tile;
    if (columns<=0 || rows<=0) return {};
    const int size=is2x2 ? tile*2 : tile;
    QImage result(size,size,QImage::Format_Indexed8);
    if (result.isNull()) return {};
    result.setColorTable(atlas.colorTable());
    result.fill(0);
    bool valid=false;
    for (int part=0;part<(is2x2 ? 4 : 1);++part) {
        const int index=(is2x2 && cells.size()==4) ? cells.at(part).toInt(65535) : icon;
        if (index<0 || index>=columns*rows) continue;
        valid=true;
        const int sx=(index%columns)*tile,sy=(index/columns)*tile;
        const int dx=(is2x2 ? part%2 : 0)*tile;
        const int dy=(is2x2 ? part/2 : 0)*tile;
        for (int y=0;y<tile;++y) {
            const uchar *src=atlas.constScanLine(sy+y)+sx;
            uchar *dst=result.scanLine(dy+y)+dx;
            std::copy_n(src,tile,dst);
        }
    }
    return valid ? result : QImage();
}
static QImage pickupIcon(const QString &root, const HudCounter &c) {
    return pickupIcon(root,c.source,c.icon,c.iconTileSize,c.icon2x2,c.iconCells,c.spriteStamp);
}
static QImage pickupIcon(const QString &root, const Pickup &p) {
    return pickupIcon(root,p.source,p.icon,p.iconTileSize,p.icon2x2,p.iconCells,p.spriteStamp);
}
// Frame numbers use the requested 8x8 or 16x16 grid of the source PPB.
// A 16x16 frame is four adjacent original 8x8 cells, not a baked stamp PPB.
static QImage barFrame(const QImage &atlas, int frameSize, int frame) {
    if (atlas.isNull() || atlas.format()!=QImage::Format_Indexed8 ||
        (frameSize!=8 && frameSize!=16) || frame<0) return {};
    const int columns=atlas.width()/frameSize,rows=atlas.height()/frameSize;
    if (columns<=0 || frame>=columns*rows) return {};
    return atlas.copy((frame%columns)*frameSize,(frame/columns)*frameSize,frameSize,frameSize);
}
static void updateCounterArtwork(HudDoc &doc, const QVector<Pickup> &found) {
    for (HudCounter &counter : doc.counters) {
        for (const Pickup &pickup : found) {
            if (pickup.kind != counter.kind) continue;
            counter.iw=pickup.iw; counter.ih=pickup.ih;
            counter.name=pickup.name; counter.source=pickup.source;
            counter.icon=pickup.icon; counter.iconTileSize=pickup.iconTileSize;
            counter.icon2x2=pickup.icon2x2; counter.iconCells=pickup.iconCells;
            counter.spriteStamp=pickup.spriteStamp;
            break;
        }
    }
}
static QImage visible(QImage image) {
    if(image.isNull()) return image;
    image=image.convertToFormat(QImage::Format_ARGB32);
    for(int y=0;y<image.height();++y)
        for(int x=0;x<image.width();++x)
            if(qAlpha(image.pixel(x,y))==0) image.setPixel(x,y,0x00000000u);
    return image;
}
static QVector<Pickup> discover(const QString &root) {
    QMap<int,Pickup> byKind;
    const QStringList worlds=QDir(root).entryList({"*.sbgm"},QDir::Files,QDir::Name);
    for(const QString &world:worlds) {
        QFile file(QDir(root).filePath(world));
        if(!file.open(QIODevice::ReadOnly)) continue;
        const QJsonObject design=QJsonDocument::fromJson(file.readAll()).object();
        if(design.isEmpty()) continue;
        const QJsonArray resources=design.value("resources").toArray();
        const QJsonObject adventure=design.value("adventure").toObject();
        const QJsonArray items=adventure.value("items").toArray();
        for(const QJsonValue &value:resources) {
            const QJsonObject r=value.toObject(),object=r.value("gameObject").toObject();
            if(r.value("kind").toString()!="sprite" || object.value("type").toString()!="collectable" ||
               !object.value("pickupShowHud").toBool()) continue;
            const int kind=object.value("pickupKind").toInt();
            if(kind<1 || kind>255) continue;
            Pickup p; p.kind=kind; p.name=r.value("name").toString();
            p.source=QDir::cleanPath(r.value("path").toString());
            p.iw=qBound(1,r.value("cellWidth").toInt(16),64);
            p.ih=qBound(1,r.value("cellHeight").toInt(16),64);
            p.icon=qMax(0,r.value("frame").toInt(0));
            p.iconTileSize=p.iw; // ordinary sprite cell before Inventory Items override
            p.spriteStamp=r.value("spriteStamp").toObject();
            if (!p.spriteStamp.isEmpty()) {
                const int sw=qBound(1,p.spriteStamp.value("width").toInt(2),16);
                const int sh=qBound(1,p.spriteStamp.value("height").toInt(2),16);
                p.iw=sw*8; p.ih=sh*8;
                p.source=QDir::cleanPath(p.spriteStamp.value("source").toString(p.source));
                p.iconTileSize=8;
            }
            // An Inventory Items icon selection takes precedence over the
            // placed object's frame/stamp. This is also the artwork used
            // by the game's inventory and cross-world DROP renderer.
            for(const QJsonValue &itemValue:items) {
                const QJsonObject item=itemValue.toObject();
                if(item.value("pickupKind").toInt()!=kind) continue;
                const int picked=item.value("icon").toInt(65535);
                if (picked==65535 && !item.value("icon2x2").toBool()) break;
                QString source=item.value("iconPpbPath").toString();
                if (source.isEmpty()) {
                    QString atlasId=item.value("iconAtlasId").toString();
                    if(atlasId.isEmpty())atlasId=adventure.value("skinAtlasId").toString();
                    for(const QJsonValue &candidateValue:resources) {
                        const QJsonObject candidate=candidateValue.toObject();
                        if(candidate.value("id").toString()==atlasId && !atlasId.isEmpty()) {
                            source=candidate.value("path").toString();
                            break;
                        }
                    }
                }
                if (!source.isEmpty()) {
                    p.source=QDir::cleanPath(source);
                    p.icon=picked;
                    // The legacy dialogue atlas has its own tile size. The
                    // per-item size applies only to explicitly selected PPBs.
                    const bool usesDialogue=item.value("iconAtlasId").toString().isEmpty()
                        && item.value("iconPpbPath").toString().isEmpty();
                    p.iconTileSize=qBound(4,usesDialogue
                        ? adventure.value("tileSize").toInt(8)
                        : item.value("iconTileSize").toInt(8),64);
                    p.icon2x2=item.value("icon2x2").toBool();
                    p.iconCells=item.value("iconCells").toArray();
                    p.spriteStamp=QJsonObject();
                    p.artPriority=item.value("iconAtlasId").toString().isEmpty() &&
                        item.value("iconPpbPath").toString().isEmpty() ? 1 : 2;
                    p.iw=p.iconTileSize*(p.icon2x2?2:1);
                    p.ih=p.iw;
                }
                break;
            }
            p.iconImage=pickupIcon(root,p);
            // A matching type can appear in multiple worlds. Prefer the
            // explicit Inventory Items icon, but never replace readable art
            // with a missing/invalid atlas from a different world.
            if(!byKind.contains(kind) || (!p.iconImage.isNull() &&
                (byKind.value(kind).iconImage.isNull() ||
                 p.artPriority > byKind.value(kind).artPriority)))
                byKind.insert(kind,p);
        }
    }
    QVector<Pickup> out;
    for(auto it=byKind.cbegin();it!=byKind.cend();++it)out.append(it.value());
    return out;
}
class HudZoomScroll : public QScrollArea {
public:
    std::function<void(int)> stepZoom;
    explicit HudZoomScroll(QWidget *parent=nullptr):QScrollArea(parent){}
protected:
    void wheelEvent(QWheelEvent *e) override {
        if(stepZoom){stepZoom(e->angleDelta().y()>0?1:-1);e->accept();}
        else QScrollArea::wheelEvent(e);
    }
};
class PickupList : public QListWidget {
public:
    explicit PickupList(QWidget *parent=nullptr): QListWidget(parent) {setDragEnabled(true);setSelectionMode(SingleSelection);}
protected:
    void startDrag(Qt::DropActions) override {
        QListWidgetItem *item=currentItem(); if(!item) return;
        auto *mime=new QMimeData; mime->setData(kMime,item->data(Qt::UserRole).toByteArray());
        auto *drag=new QDrag(this);drag->setMimeData(mime);drag->setPixmap(item->icon().pixmap(24,24));
        drag->exec(Qt::CopyAction);
    }
};
class ProgressBarList : public QListWidget {
public:
    const char *mimeType;
    explicit ProgressBarList(QWidget *parent=nullptr,const char *type=kBarMime):QListWidget(parent),mimeType(type) {
        setDragEnabled(true);setSelectionMode(SingleSelection);
    }
protected:
    void startDrag(Qt::DropActions) override {
        QListWidgetItem *item=currentItem();if(!item)return;
        auto *mime=new QMimeData;
        mime->setData(mimeType,item->data(Qt::UserRole).toString().toUtf8());
        auto *drag=new QDrag(this);drag->setMimeData(mime);
        drag->exec(Qt::CopyAction);
    }
};
// Render a fixed 8x16 cell per character in the editor preview, matching
// SIDBOX's glyph spacing. Qt supplies the closest available mono glyph shapes.
static QColor paletteColour(const QVector<QRgb> &palette, int index, QColor fallback) {
    return index>=0 && index<palette.size() ? QColor::fromRgba(palette.at(index)) : fallback;
}
// The HUD shares the selected foreground CLUT. Pixel numbers are absolute
// indices: NEVER recolour/reorder/map them to another PPB's palette.
static QVector<QRgb> textPaletteFor(const QString &root, const QString &paletteSource,
                                   const QImage &atlas) {
    if (paletteSource.isEmpty()) return atlas.colorTable();
    return SidboxGamePalette::readPalette(QDir(root).filePath(paletteSource),false);
}
static QImage hudPreview(const QImage &source,const QVector<QRgb> &target) {
    if(source.isNull()||target.size()!=256||source.format()!=QImage::Format_Indexed8)return source;
    QImage result=source;
    result.setColorTable(target); // preview palette ONLY, leave pixel indices untouched
    return result;
}
static int choosePaletteIndex(QWidget *parent, const QVector<QRgb> &palette, int current,
                              const QString &title) {
    if (palette.isEmpty()) return -1;
    return SidboxPalettePicker::chooseIndex(parent, palette, current, title,
        QObject::tr("Select a foreground CLUT index (actual SIDBOX colour):"), true, true);
}

static void previewText(QPainter &p, const QString &text, int x, int y, int zoom,
                        QColor foreground, bool outline, QColor outlineColour) {
    if(text.isEmpty())return;
    // Render the real SIDBOX 8x16 font, matching GUI Designer and Title Screen.
    // Do not rasterise and stretch the desktop's QFontDatabase::FixedFont:
    // it uses different glyph shapes despite having the same character grid.
    const QByteArray bytes=text.toLatin1();
    int columns=0, lineColumns=0, lines=1;
    for(const char ch:bytes) {
        if(ch=='\n') {columns=qMax(columns,lineColumns);lineColumns=0;++lines;}
        else ++lineColumns;
    }
    columns=qMax(columns,lineColumns);
    QImage glyphs(qMax(8,columns*8),lines*16,QImage::Format_ARGB32_Premultiplied);
    glyphs.fill(Qt::transparent);
    {
        QPainter gp(&glyphs);
        GuiDesignerDetail::drawCoderGirlText(gp,0,0,text,foreground);
    }
    const QRect target(x*zoom,y*zoom,glyphs.width()*zoom,glyphs.height()*zoom);
    if(outline) {
        QImage edges=glyphs;
        {
            QPainter ep(&edges);ep.setCompositionMode(QPainter::CompositionMode_SourceIn);
            ep.fillRect(edges.rect(),outlineColour);
        }
        for(const QPoint delta:{QPoint(-zoom,0),QPoint(zoom,0),QPoint(0,-zoom),QPoint(0,zoom)})
            p.drawImage(target.translated(delta),edges);
    }
    p.drawImage(target,glyphs);
}
class HudCanvas : public QWidget {
public:
    HudDoc *doc=nullptr;
    QString root;
    QImage atlasImage;
    int pickedTile=0;
    int zoom=3;
    bool flipX=false,flipY=false,painting=true,placingLabel=false,hideOverlays=false;
    bool draggingOverlay=false;
    QPoint grabOffset;
    QPoint lastPaintCell=QPoint(-1,-1);
    QString labelText;
    int selectedCounter=-1,selectedLabel=-1,selectedBar=-1,selectedStat=-1;
    uint32_t previewTick=0;
    QHash<QString,QImage> barAtlases;
    std::function<bool(int)> editBar;
    std::function<void()> labelPlaced;
    QVector<QRgb> textColors;
    std::function<void()> changed;
    std::function<void(int,int)> tilePicked;
    explicit HudCanvas(QWidget *parent=nullptr):QWidget(parent) {setAcceptDrops(true);setMouseTracking(true);}
    QSize sizeHint() const override {return doc ? QSize(doc->columns*doc->cw*zoom+2,doc->rows*doc->ch*zoom+2) : QSize(720,160);}
    void refresh() {resize(sizeHint());updateGeometry();update();}
    int scale() const {return zoom;}
    void wheelEvent(QWheelEvent *e) override {
        const int next=qBound(1,zoom+(e->angleDelta().y()>0?1:-1),10);
        if(next!=zoom){zoom=next;refresh();}
        e->accept();
    }
    QPoint pixelPoint(QPoint pos) const {return QPoint(pos.x()/scale(),pos.y()/scale());}
    QImage cellImage(const Tile &tile) const {
        if(atlasImage.isNull() || tile.index<0 || !doc) return {};
        const int cols=atlasImage.width()/doc->cw;
        const int rows=atlasImage.height()/doc->ch;
        if(cols<=0 || tile.index>=cols*rows) return {};
        QImage img=hudPreview(atlasImage.copy((tile.index%cols)*doc->cw,
            (tile.index/cols)*doc->ch,doc->cw,doc->ch),textColors);
        Qt::Orientations flips;
        if (tile.fx) flips |= Qt::Horizontal;
        if (tile.fy) flips |= Qt::Vertical;
        return visible(flips ? img.flipped(flips) : img);
    }
    void paintEvent(QPaintEvent*) override {
        if(!doc)return;
        QPainter p(this);p.fillRect(rect(),QColor(25,25,30));
        const int s=scale();
        for(int y=0;y<doc->rows;++y)for(int x=0;x<doc->columns;++x) {
            const QRect rect(x*doc->cw*s,y*doc->ch*s,doc->cw*s,doc->ch*s);
            const Tile &t=doc->tiles[y*doc->columns+x];
            const QImage img=cellImage(t);
            if(!img.isNull()) p.drawImage(rect,img);
            p.setPen(QColor(85,85,85,110));p.drawRect(rect.adjusted(0,0,-1,-1));
        }
        const QColor fg=paletteColour(textColors,doc->colour,Qt::white);
        const QColor outline=paletteColour(textColors,doc->outlineColour,Qt::black);
        p.setPen(Qt::white);
        if(hideOverlays)return; // edit tile art without changing or deleting placed overlays
        for(int i=0;i<doc->labels.size();++i) {
            const HudLabel &l=doc->labels[i];
            if(selectedLabel==i)p.fillRect(l.x*s,l.y*s,qMax(20,int(l.text.size())*8)*s,16*s,QColor(45,75,105));
            previewText(p,l.text,l.x,l.y,s,fg,doc->outlineEnabled,outline);
        }
        for(int i=0;i<doc->bars.size();++i) {
            const HudBar &b=doc->bars[i];
            if(!barAtlases.contains(b.source))
                barAtlases.insert(b.source,loadIndexed(QDir(root).filePath(b.source)));
            const QImage &atlas=barAtlases[b.source];
            const uint32_t step=previewTick/uint32_t(qMax(1,b.frameTicks));
            const int frame=b.startFrame+(b.loop ? int(step%uint32_t(b.frameCount))
                : int(qMin(step,uint32_t(b.frameCount-1))));
            QImage tile=hudPreview(barFrame(atlas,b.frameSize,frame),textColors);
            if(!tile.isNull()) {
                tile=visible(tile);
                const int filled=(b.width*b.preview)/100;
                for(int px=0;px<filled;px+=b.frameSize) {
                    const int slice=qMin(b.frameSize,filled-px);
                    p.drawImage(QPoint((b.x+px)*s,b.y*s),
                        tile.copy(0,0,slice,b.frameSize).scaled(slice*s,b.frameSize*s));
                }
            }
            if(selectedBar==i){
                p.setPen(Qt::yellow);
                p.drawRect(b.x*s,b.y*s,b.width*s-1,b.frameSize*s-1);
                p.setPen(Qt::white);
            }
        }
        for(int i=0;i<doc->stats.size();++i) {
            const HudStat &n=doc->stats[i];
            const QString message=n.label+QStringLiteral(": 000");
            if(selectedStat==i)p.fillRect(n.x*s,n.y*s,qMax(40,int(message.size())*8)*s,16*s,QColor(45,75,105));
            previewText(p,message,n.x,n.y,s,fg,doc->outlineEnabled,outline);
        }
        for(int i=0;i<doc->counters.size();++i) {
            const HudCounter &c=doc->counters[i];
            QImage icon=visible(hudPreview(pickupIcon(root,c),textColors));
            if(!icon.isNull())p.drawImage(QRect(c.x*s,c.y*s,icon.width()*s,icon.height()*s),icon);
            if(selectedCounter==i) {p.setPen(Qt::yellow);p.drawRect(c.x*s,c.y*s,icon.width()*s+3,icon.height()*s+3);p.setPen(Qt::white);}
            previewText(p,QStringLiteral("0"),c.x+c.iw+2,c.y,s,fg,doc->outlineEnabled,outline);
        }
    }
    bool validPixel(const QPoint &q) const {
        return doc && q.x()>=0 && q.y()>=0 && q.x()<doc->columns*doc->cw && q.y()<doc->rows*doc->ch;
    }
    void paintTileAt(const QPoint &q, bool erase) {
        if(!validPixel(q))return;
        Tile &cell=doc->tiles[(q.y()/doc->ch)*doc->columns+q.x()/doc->cw];
        const Tile next=erase ? Tile() : Tile{pickedTile,flipX,flipY};
        if(cell.index==next.index && cell.fx==next.fx && cell.fy==next.fy)return;
        cell=next;if(changed)changed();update();
    }
    void paintStrokeTo(const QPoint &pixel, bool erase) {
        if(!validPixel(pixel))return;
        const QPoint cell(pixel.x()/doc->cw,pixel.y()/doc->ch);
        QPoint previous=lastPaintCell;
        if(previous.x()<0 || previous.y()<0)previous=cell;
        int x=previous.x(),y=previous.y();
        const int dx=std::abs(cell.x()-x),dy=std::abs(cell.y()-y);
        const int sx=x<cell.x()?1:-1,sy=y<cell.y()?1:-1;
        int error=dx-dy;
        while(true) {
            paintTileAt(QPoint(x*doc->cw,y*doc->ch),erase);
            if(x==cell.x() && y==cell.y())break;
            const int e=2*error;
            if(e>-dy){error-=dy;x+=sx;}
            if(e<dx){error+=dx;y+=sy;}
        }
        lastPaintCell=cell;
    }
    // Drag existing overlays by the point where the mouse grabbed them.
    // Hit-test only in overlay-edit mode, never while painting hidden tiles.
    void selectOverlay(const QPoint &q) {
        selectedCounter=selectedLabel=selectedBar=selectedStat=-1;
        if(hideOverlays)return;
        for(int i=doc->stats.size()-1;i>=0;--i) {
            const HudStat &n=doc->stats[i];
            if(QRect(n.x,n.y,qMax(40,int(n.label.size()+5)*8),16).contains(q)) {
                selectedStat=i;grabOffset=q-QPoint(n.x,n.y);return;
            }
        }
        for(int i=doc->bars.size()-1;i>=0;--i) {
            const HudBar &b=doc->bars[i];
            if(QRect(b.x,b.y,b.width,b.frameSize).contains(q)) {
                selectedBar=i;grabOffset=q-QPoint(b.x,b.y);return;
            }
        }
        for(int i=doc->counters.size()-1;i>=0;--i) {
            const HudCounter &c=doc->counters[i];
            if(QRect(c.x,c.y,c.iw+32,qMax(c.ih,16)).contains(q)) {
                selectedCounter=i;grabOffset=q-QPoint(c.x,c.y);return;
            }
        }
        for(int i=doc->labels.size()-1;i>=0;--i) {
            const HudLabel &l=doc->labels[i];
            if(QRect(l.x,l.y,qMax(12,int(l.text.size())*8),16).contains(q)) {
                selectedLabel=i;grabOffset=q-QPoint(l.x,l.y);return;
            }
        }
    }
    void mousePressEvent(QMouseEvent *e) override {
        if(!doc)return;
        const QPoint q=pixelPoint(e->pos());
        if(!validPixel(q))return;
        draggingOverlay=false;lastPaintCell=QPoint(-1,-1);
        // Erase underlying tiles while overlays are hidden, or delete a
        // clicked overlay while visible. Subsequent right-drag paints empty tiles.
        if(e->button()==Qt::RightButton) {
            selectOverlay(q);
            if(selectedStat>=0)doc->stats.removeAt(selectedStat);
            else if(selectedBar>=0)doc->bars.removeAt(selectedBar);
            else if(selectedCounter>=0)doc->counters.removeAt(selectedCounter);
            else if(selectedLabel>=0)doc->labels.removeAt(selectedLabel);
            else {paintStrokeTo(q,true);return;}
            selectedCounter=selectedLabel=selectedBar=selectedStat=-1;
            if(changed)changed();update();return;
        }
        if(e->button()!=Qt::LeftButton)return;
        if(placingLabel && !labelText.isEmpty() && !hideOverlays) {
            if(doc->labels.size()>=80)return;
            doc->labels.append({labelText,q.x(),q.y()});
            placingLabel=false;labelText.clear();
            selectedCounter=selectedLabel=selectedBar=selectedStat=-1;
            if(labelPlaced)labelPlaced();
            if(changed)changed();update();return;
        }
        selectOverlay(q);
        if(selectedCounter>=0||selectedLabel>=0||selectedBar>=0||selectedStat>=0) {
            draggingOverlay=true;update();return;
        }
        if(painting)paintStrokeTo(q,false);
    }
    void mouseMoveEvent(QMouseEvent *e) override {
        if(!doc)return;
        const QPoint q=pixelPoint(e->pos());
        if((e->buttons()&Qt::RightButton) && validPixel(q)) {
            // Continuous right-drag erases individual tile cells, including
            // when the pointer passes underneath hidden overlays.
            paintStrokeTo(q,true);return;
        }
        if(!(e->buttons()&Qt::LeftButton) || !validPixel(q))return;
        if(draggingOverlay && selectedStat>=0 && selectedStat<doc->stats.size()) {
            HudStat &n=doc->stats[selectedStat];
            const QPoint position=q-grabOffset;
            n.x=qBound(0,position.x(),doc->columns*doc->cw-1);
            n.y=qBound(0,position.y(),doc->rows*doc->ch-1);
            if(changed)changed();update();
        }else if(draggingOverlay && selectedBar>=0 && selectedBar<doc->bars.size()) {
            HudBar &b=doc->bars[selectedBar];
            const QPoint position=q-grabOffset;
            const int nx=qBound(0,position.x(),doc->columns*doc->cw-1);
            const int ny=qBound(0,position.y(),doc->rows*doc->ch-1);
            if(b.x!=nx || b.y!=ny) {b.x=nx;b.y=ny;if(changed)changed();update();}
        }else if(draggingOverlay && selectedCounter>=0 && selectedCounter<doc->counters.size()) {
            HudCounter &c=doc->counters[selectedCounter];
            const QPoint position=q-grabOffset;
            const int nx=qBound(0,position.x(),doc->columns*doc->cw-1);
            const int ny=qBound(0,position.y(),doc->rows*doc->ch-1);
            if(c.x!=nx||c.y!=ny){c.x=nx;c.y=ny;if(changed)changed();update();}
        }else if(draggingOverlay && selectedLabel>=0 && selectedLabel<doc->labels.size()) {
            HudLabel &l=doc->labels[selectedLabel];
            const QPoint position=q-grabOffset;
            const int nx=qBound(0,position.x(),doc->columns*doc->cw-1);
            const int ny=qBound(0,position.y(),doc->rows*doc->ch-1);
            if(l.x!=nx||l.y!=ny){l.x=nx;l.y=ny;if(changed)changed();update();}
        }else if(!draggingOverlay && painting && !placingLabel)paintStrokeTo(q,false);
    }
    void mouseReleaseEvent(QMouseEvent *) override {draggingOverlay=false;lastPaintCell=QPoint(-1,-1);}
    void mouseDoubleClickEvent(QMouseEvent *e) override {
        if(!doc||hideOverlays||e->button()!=Qt::LeftButton)return;
        const QPoint q=pixelPoint(e->pos());
        if(!validPixel(q))return;
        selectOverlay(q);
        draggingOverlay=false;
        if(selectedBar>=0) {
            if(editBar)(void)editBar(selectedBar);
            return;
        }
        if(selectedStat>=0) {
            bool ok=false;
            const QString edited=QInputDialog::getText(this,tr("Numeric HUD Stat"),tr("Display label:"),
                QLineEdit::Normal,doc->stats[selectedStat].label,&ok);
            if(ok){doc->stats[selectedStat].label=edited.left(24);if(changed)changed();update();}
            return;
        }
        if(selectedLabel>=0) {
            bool ok=false;
            const QString edited=QInputDialog::getText(this,tr("HUD Text"),tr("Text:"),QLineEdit::Normal,
                doc->labels[selectedLabel].text,&ok);
            if(ok){doc->labels[selectedLabel].text=edited.left(60);if(changed)changed();update();}
        }
    }
    void dragEnterEvent(QDragEnterEvent *e) override {
        if(!hideOverlays && (e->mimeData()->hasFormat(kMime) || e->mimeData()->hasFormat(kBarMime) || e->mimeData()->hasFormat(kStatMime)))
            e->acceptProposedAction();
    }
    void dragMoveEvent(QDragMoveEvent *e) override {
        if(!hideOverlays && (e->mimeData()->hasFormat(kMime) || e->mimeData()->hasFormat(kBarMime) || e->mimeData()->hasFormat(kStatMime)))
            e->acceptProposedAction();
    }
    void dropEvent(QDropEvent *e) override {
        if(!doc || hideOverlays)return;
        const QPoint q=pixelPoint(e->position().toPoint());
        if(!validPixel(q))return;
        if(e->mimeData()->hasFormat(kStatMime)) {
            if(doc->stats.size()>=32)return;
            const QString binding=QString::fromUtf8(e->mimeData()->data(kStatMime));
            if(binding!="health" && binding!="lives" && binding!="score" &&
                !binding.startsWith("stat:") && !binding.startsWith("pickup:"))return;
            QString name=binding.startsWith("stat:")?binding.mid(5):
                binding.startsWith("pickup:")?QStringLiteral("Pickup ")+binding.mid(7):binding;
            if(!name.isEmpty())name[0]=name[0].toUpper();
            doc->stats.append({binding,name,q.x(),q.y()});
            selectedStat=doc->stats.size()-1;
            if(changed)changed();update();e->acceptProposedAction();return;
        }
        if(e->mimeData()->hasFormat(kBarMime)) {
            if(doc->bars.size()>=32)return;
            HudBar bar;
            bar.binding=QString::fromUtf8(e->mimeData()->data(kBarMime));
            bar.source=doc->atlas;
            bar.width=qMin(bar.width,doc->columns*doc->cw);
            bar.x=qMin(q.x(),doc->columns*doc->cw-bar.width);
            bar.y=qMin(q.y(),qMax(0,doc->rows*doc->ch-bar.frameSize));
            doc->bars.append(bar);
            const int index=doc->bars.size()-1;
            // Complete the drag operation before opening a modal editor.
            // Cancel removes the new bar rather than leaving a broken asset.
            e->acceptProposedAction();
            QTimer::singleShot(0,this,[this,index]() {
                if(!doc || index>=doc->bars.size())return;
                if(!editBar || !editBar(index))doc->bars.removeAt(index);
                selectedBar=-1;selectedStat=-1;
                if(changed)changed();update();
            });
            return;
        }
        if(!e->mimeData()->hasFormat(kMime) || doc->counters.size()>=32)return;
        const QJsonObject o=QJsonDocument::fromJson(e->mimeData()->data(kMime)).object();
        doc->counters.append({o.value("kind").toInt(),q.x(),q.y(),o.value("iw").toInt(16),
            o.value("ih").toInt(16),o.value("name").toString(),o.value("source").toString(),
            o.value("icon").toInt(0),o.value("iconTileSize").toInt(8),
            o.value("icon2x2").toBool(false),o.value("iconCells").toArray(),
            o.value("spriteStamp").toObject()});
        if(changed)changed();update();e->acceptProposedAction();
    }
};
class AtlasPicker : public QLabel {
public:
    QImage source;int cw=8,ch=8,index=0,zoom=3;
    std::function<void(int)> picked;
    explicit AtlasPicker(QWidget *parent=nullptr):QLabel(parent) {setAlignment(Qt::AlignLeft|Qt::AlignTop);}
    void wheelEvent(QWheelEvent *e) override {
        const int next=qBound(1,zoom+(e->angleDelta().y()>0?1:-1),10);
        if(next!=zoom){zoom=next;refresh();}e->accept();
    }
    void refresh() {
        if(source.isNull()) {setPixmap(QPixmap());setText(tr("Choose a PPB atlas from Game Resources"));resize(260,90);return;}
        QImage img=visible(source);
        QPainter p(&img);p.setPen(QColor(120,120,120,120));
        for(int x=cw;x<img.width();x+=cw)p.drawLine(x,0,x,img.height());
        for(int y=ch;y<img.height();y+=ch)p.drawLine(0,y,img.width(),y);
        p.setPen(Qt::yellow);
        const int cols=img.width()/cw;
        if(cols>0)p.drawRect(QRect((index%cols)*cw,(index/cols)*ch,cw,ch).adjusted(0,0,-1,-1));
        setPixmap(QPixmap::fromImage(img.scaled(img.width()*zoom,img.height()*zoom,Qt::IgnoreAspectRatio,Qt::FastTransformation)));
        resize(img.width()*zoom,img.height()*zoom);updateGeometry();
    }
protected:
    void mousePressEvent(QMouseEvent *e) override {
        if(source.isNull()||cw<=0||ch<=0)return;
        const int cols=source.width()/cw;
        const int x=e->pos().x()/(cw*zoom),y=e->pos().y()/(ch*zoom);
        if(x<0||y<0||x>=cols||y>=source.height()/ch)return;
        index=y*cols+x;refresh();if(picked)picked(index);
    }
};
class HudScreenPreview : public QWidget {
public:
    HudDoc *doc=nullptr;
    std::function<void()> moved;
    QPoint dragOffset;
    bool moving=false;
    explicit HudScreenPreview(QWidget *parent=nullptr):QWidget(parent){setFixedSize(482,322);setMouseTracking(true);}
protected:
    void paintEvent(QPaintEvent*) override {
        if(!doc)return;
        QPainter p(this);p.fillRect(rect(),QColor(14,18,26));
        p.setPen(QColor(88,103,125));p.drawRect(0,0,481,321);
        for(int x=0;x<480;x+=40){p.setPen(QColor(43,50,65));p.drawLine(x+1,1,x+1,320);}
        for(int y=0;y<320;y+=40){p.setPen(QColor(43,50,65));p.drawLine(1,y+1,480,y+1);}
        const QRect r(doc->hudX+1,doc->hudY+1,doc->columns*doc->cw,doc->rows*doc->ch);
        p.fillRect(r,QColor(52,132,164,100));p.setPen(QColor(115,225,255));p.drawRect(r.adjusted(0,0,-1,-1));
        p.setPen(Qt::white);p.drawText(r.adjusted(5,3,-2,-2),Qt::AlignTop|Qt::AlignLeft,tr("HUD"));
    }
    void moveTo(QPoint p) {
        if(!doc)return;
        doc->hudX=qBound(0,p.x(),480-doc->columns*doc->cw);
        doc->hudY=qBound(0,p.y(),320-doc->rows*doc->ch);
        update();if(moved)moved();
    }
    void mousePressEvent(QMouseEvent *e) override {
        if(!doc||e->button()!=Qt::LeftButton)return;
        const QPoint pt=e->pos()-QPoint(1,1);
        moving=true;
        const QRect r(doc->hudX,doc->hudY,doc->columns*doc->cw,doc->rows*doc->ch);
        dragOffset=r.contains(pt) ? pt-r.topLeft() : QPoint(0,0);
        moveTo(pt-dragOffset);
    }
    void mouseMoveEvent(QMouseEvent *e) override {
        if(moving&&(e->buttons()&Qt::LeftButton)) moveTo(e->pos()-QPoint(1,1)-dragOffset);
    }
    void mouseReleaseEvent(QMouseEvent*) override {moving=false;}
};
static QString cArray(const QByteArray &bytes) {
    QString out;out.reserve(bytes.size()*5);
    for(int i=0;i<bytes.size();++i) {
        if(i%20==0)out+=QStringLiteral("\n    ");
        out+=QString::number(static_cast<unsigned char>(bytes.at(i)))+',';
    }
    return out+QStringLiteral("\n");
}
static QString quoted(QString text) {
    QString s=QStringLiteral("\"");
    for (const QChar ch:text) {
        const ushort u=ch.unicode();
        if(u=='\\'||u=='"')s+=QLatin1Char('\\'),s+=ch;
        else if(u>=32&&u<=126)s+=ch;
        else s+='?';
    }
    return s+QLatin1Char('"');
}
static bool writeFile(const QString &path,const QByteArray &data,QString *error) {
    QSaveFile f(path);
    if(!f.open(QIODevice::WriteOnly) || f.write(data)!=data.size() || !f.commit()) {
        if(error)*error=QStringLiteral("Cannot write %1").arg(path);
        return false;
    }
    return true;
}
static bool registerHudFiles(const QString &root,QString *error) {
    const QDir folder(root);
    const QStringList projects=folder.entryList({"*.proj"},QDir::Files);
    if(projects.size()!=1) {if(error)*error="Expected one game .proj in the project directory";return false;}
    const QString path=folder.filePath(projects.first());
    QFile input(path);
    if(!input.open(QIODevice::ReadOnly)){if(error)*error="Cannot read game project";return false;}
    const QJsonDocument parsed=QJsonDocument::fromJson(input.readAll());
    if(!parsed.isObject() || !parsed.object().value("files").isArray()){
        if(error)*error="Invalid game project file list";return false;
    }
    QJsonObject project=parsed.object();QJsonArray files=project.value("files").toArray();
    for(const QString &name:{QStringLiteral("gamehud.sbhud"), QStringLiteral("gamehelpers/gamehud.c"), QStringLiteral("gamehelpers/gamehud.h")}) {
        if(!files.contains(name))files.append(name);
    }
    project.insert("files",files);
    return writeFile(path,QJsonDocument(project).toJson(QJsonDocument::Indented),error);
}
static bool exportHud(const QString &root,const HudDoc &doc,QString *error) {
    const QString hudFolder=QDir(root).filePath("gamehelpers");
    if(!QDir().mkpath(hudFolder)) {if(error)*error=QStringLiteral("Cannot create gamehelpers directory");return false;}
    const QImage atlas=loadIndexed(QDir(root).filePath(doc.atlas));
    const int w=doc.columns*doc.cw,h=doc.rows*doc.ch;
    QByteArray pixels(w*h,char(0));
    if(!atlas.isNull()){
        const int ncols=atlas.width()/doc.cw;
        const int nrows=atlas.height()/doc.ch;
        if(ncols==0 || nrows==0) {if(error)*error=QStringLiteral("Atlas is smaller than one cell");return false;}
        for(int ry=0;ry<doc.rows;++ry)for(int rx=0;rx<doc.columns;++rx) {
            const Tile &tile=doc.tiles[ry*doc.columns+rx];
            if(tile.index<0)continue;
            if(tile.index>=ncols*nrows){if(error)*error=QStringLiteral("HUD references a tile outside its atlas");return false;}
            const int sx=(tile.index%ncols)*doc.cw,sy=(tile.index/ncols)*doc.ch;
            for(int iy=0;iy<doc.ch;++iy)for(int ix=0;ix<doc.cw;++ix){
                const int px=sx+(tile.fx?(doc.cw-1-ix):ix);
                const int py=sy+(tile.fy?(doc.ch-1-iy):iy);
                pixels[(ry*doc.ch+iy)*w+rx*doc.cw+ix]=char(atlas.pixelIndex(px,py));
            }
        }
    }else {
        for(const Tile &tile:doc.tiles) if(tile.index>=0){if(error)*error="Missing HUD atlas PPB";return false;}
    }
    // Generate complete C in dependency order: headers, all static arrays,
    // text helper, then public draw routines. Keep game source user-owned.
    QString c=QStringLiteral("/* GENERATED by CoderGirl HUD Designer. Changes here are overwritten. */\n"
        "#include \"gamehud.h\"\n#include \"gameworlds.h\"\n#include \"apis.h\"\n#include <stdio.h>\n#include <string.h>\n"
        "static const unsigned char hud_pixels[%1] __attribute__((aligned(32))) = {%2};\n")
        .arg(pixels.size()).arg(cArray(pixels));
    QString iconDraws;
    int i=0;
    for(const HudCounter &cnt:doc.counters) {
        const QImage icon=pickupIcon(root,cnt);
        if(icon.isNull() || icon.format()!=QImage::Format_Indexed8) {
            if(error)*error=QStringLiteral("Missing HUD icon PPB: %1").arg(cnt.source);
            return false;
        }
        QByteArray bytes;bytes.reserve(icon.width()*icon.height());
        for(int yy=0;yy<icon.height();++yy)for(int xx=0;xx<icon.width();++xx)
            bytes.append(char(icon.pixelIndex(xx,yy)));
        const QString sym=QStringLiteral("icon_%1").arg(i++);
        c+=QStringLiteral("static const unsigned char %1[%2] __attribute__((aligned(32))) = {%3};\n")
            .arg(sym).arg(bytes.size()).arg(cArray(bytes));
        // Use %u, not %%lu: %% in a C printf format prints a literal percent.
        // The pickup counter is 32-bit on the STM32. Qt does not interpolate %u.
        iconDraws+=QStringLiteral("    { gfxbob_t icon = {0}; icon.imgdat=(uint8_t *)%1;\n"
            "      icon.atlas_stride=%2u; icon.atlas_height=%3u; icon.width=%2u; icon.height=%3u;\n"
            "      icon.scale=100u; icon.drawx=x+%4; icon.drawy=y+%5; gfx_drawbob(&icon);\n"
            "      char count[16]; snprintf(count,sizeof(count),\"%u\",(unsigned int)gameworlds_hud_total(%6u));\n"
            "      hud_draw_text(x+%7,y+%8,count); }\n")
            .arg(sym).arg(icon.width()).arg(icon.height()).arg(cnt.x).arg(cnt.y).arg(cnt.kind)
            .arg(cnt.x+icon.width()+2).arg(cnt.y);
    }
    // Generate an animated tiled bar by sampling only its selected frames from
    // the existing PPB. The last tile is drawn with a shorter bob.width, giving
    // true pixel clipping without a framebuffer readback or an extra PPB.
    QString barDraws;
    QString statDraws;
    bool customStatsUsed=false;
    int barIndex=0;
    for (const HudBar &bar:doc.bars) {
        const int id=barIndex++;
        if(bar.minimum>=bar.maximum || bar.width<1 || bar.width>480 ||
           bar.frameCount<1 || bar.frameCount>64 || bar.frameTicks<1 ||
           bar.x<0 || bar.y<0 || bar.x+bar.width>w || bar.y+bar.frameSize>h) {
            if(error)*error=QStringLiteral("Invalid/out-of-bounds HUD bar %1. Double-click it to edit.").arg(id+1);
            return false;
        }
        const QString path=QDir::cleanPath(bar.source);
        if(path.isEmpty() || path.startsWith("../") || QDir::isAbsolutePath(path)) {
            if(error)*error=QStringLiteral("Invalid PPB path for HUD bar %1").arg(id+1);
            return false;
        }
        const QImage src=loadIndexed(QDir(root).filePath(path));
        if(src.isNull() || src.format()!=QImage::Format_Indexed8) {
            if(error)*error=QStringLiteral("Missing PPB for HUD bar %1: %2").arg(id+1).arg(path);
            return false;
        }
        QByteArray bytes;
        bytes.reserve(bar.frameCount*bar.frameSize*bar.frameSize);
        for(int fi=0;fi<bar.frameCount;++fi) {
            const QImage frame=barFrame(src,bar.frameSize,bar.startFrame+fi);
            if(frame.isNull()) {
                if(error)*error=QStringLiteral("HUD bar %1: frame %2 is outside %3")
                    .arg(id+1).arg(bar.startFrame+fi).arg(path);
                return false;
            }
            for(int py=0;py<bar.frameSize;++py)
                for(int px=0;px<bar.frameSize;++px)
                    bytes.append(char(frame.pixelIndex(px,py)));
        }
        c+=QStringLiteral("static const unsigned char hud_bar_%1_frames[%2] __attribute__((aligned(32))) = {%3};\n")
            .arg(id).arg(bytes.size()).arg(cArray(bytes));
        QString valueExpression;
        if(bar.binding=="health" || bar.binding=="lives" || bar.binding=="score") {
            valueExpression=QStringLiteral("int64_t value=(int64_t)gameworlds_state()->%1;\n").arg(bar.binding);
        } else if(bar.binding.startsWith("stat:") && bar.binding.size()>5) {
            customStatsUsed=true;
            valueExpression=QStringLiteral("int32_t stat_value=0; (void)gameplayer_stat_get(%1,&stat_value); "
                "int64_t value=(int64_t)stat_value;\n").arg(quoted(bar.binding.mid(5)));
        } else if(bar.binding.startsWith("pickup:")) {
            bool ok=false;const int kind=bar.binding.mid(7).toInt(&ok);
            if(!ok || kind<1 || kind>255) {
                if(error)*error=QStringLiteral("Invalid collectable binding on HUD bar %1").arg(id+1);
                return false;
            }
            // Pickup bindings are only offered from valid discovered resources.
            // If an item was removed, catch it before emitting an undefined API.
            bool known=false;
            for(const Pickup &p:discover(root)) if(p.kind==kind){known=true;break;}
            if(!known) {
                if(error)*error=QStringLiteral("HUD bar %1 uses a missing collectable type %2")
                    .arg(id+1).arg(kind);
                return false;
            }
            valueExpression=QStringLiteral("int64_t value=(int64_t)gameworlds_hud_total(%1u);\n").arg(kind);
        } else {
            if(error)*error=QStringLiteral("Unknown value binding on HUD bar %1: %2").arg(id+1).arg(bar.binding);
            return false;
        }
        // Keep each QString::arg() template small. The original 13-argument
        // format leaked placeholders such as %13 into generated gamehud.c.
        // Leave the C modulo operator separate from Qt's %N substitutions.
        barDraws+=QStringLiteral("    { /* Progress bar %1: %2 */\n      %3")
            .arg(id).arg(quoted(bar.binding)).arg(valueExpression);
        barDraws+=QStringLiteral("      int32_t filled=0;\n"
            "      if(value>=%1LL) filled=%2;\n"
            "      else if(value>%3LL) filled=(int32_t)(((value-%3LL)*(int64_t)%2)/(%1LL-%3LL));\n")
            .arg(bar.maximum).arg(bar.width).arg(bar.minimum);
        barDraws+=QStringLiteral("      uint32_t phase=hud_bar_tick/%1u;\n"
            "      uint32_t frame=%2 ? (phase % %3u) : (phase<%3u?phase:%3u-1u);\n")
            .arg(bar.frameTicks).arg(bar.loop?1:0).arg(bar.frameCount);
        barDraws+=QStringLiteral("      gfxbob_t tile={0}; tile.imgdat=hud_bar_%1_frames+frame*%2u;\n"
            "      tile.atlas_stride=%3u; tile.atlas_height=%3u; tile.height=%3u; tile.scale=100u;\n")
            .arg(id).arg(bar.frameSize*bar.frameSize).arg(bar.frameSize);
        barDraws+=QStringLiteral("      for(int32_t dx=0;dx<filled;dx+=%1) {\n"
            "          int32_t portion=filled-dx; if(portion>%1)portion=%1;\n"
            "          tile.width=(uint16_t)portion; tile.drawx=(int16_t)(x+%2+dx);\n"
            "          tile.drawy=(int16_t)(y+%3); gfx_drawbob(&tile);\n"
            "      }\n    }\n")
            .arg(bar.frameSize).arg(bar.x).arg(bar.y);
    }
    for (const HudStat &stat:doc.stats) {
        QString value;
        if(stat.binding=="health" || stat.binding=="lives" || stat.binding=="score")
            value=QStringLiteral("(unsigned long)gameworlds_state()->%1").arg(stat.binding);
        else if(stat.binding.startsWith("stat:") && stat.binding.size()>5) {
            customStatsUsed=true;
            value=QStringLiteral("(long)numeric_value");
        } else if(stat.binding.startsWith("pickup:")) {
            bool ok=false;int kind=stat.binding.mid(7).toInt(&ok);
            if(!ok || kind<1 || kind>255) {if(error)*error="Invalid HUD numeric pickup";return false;}
            value=QStringLiteral("(unsigned long)gameworlds_hud_total(%1u)").arg(kind);
        } else {if(error)*error=QStringLiteral("Invalid HUD stat: %1").arg(stat.binding);return false;}
        const QString field=QStringLiteral("    { char number[64]; ");
        statDraws+=field;
        if(stat.binding.startsWith("stat:"))
            statDraws+=QStringLiteral("int32_t numeric_value=0; (void)gameplayer_stat_get(%1,&numeric_value); ")
                .arg(quoted(stat.binding.mid(5)));
        const QString numberFormat=stat.binding.startsWith("stat:") ?
            QStringLiteral("%s: %ld") : QStringLiteral("%s: %lu");
        statDraws+=QStringLiteral("snprintf(number,sizeof(number),%1,%2,%3); ")
            .arg(quoted(numberFormat)).arg(quoted(stat.label)).arg(value);
        statDraws+=QStringLiteral("hud_draw_text(x+%1,y+%2,number); }\n")
            .arg(stat.x).arg(stat.y);
    }
    if(customStatsUsed) {
        const QDir playerFolder(QDir(root).filePath("players"));
        if(playerFolder.entryList({"*.sbpi"},QDir::Files).isEmpty()) {
            if(error)*error=QStringLiteral("HUD uses a custom player stat but has no shared Player definition.");
            return false;
        }
        c+=QStringLiteral("#include \"gameplayer.h\"\n");
    }
    if(!doc.bars.isEmpty()) c+=QStringLiteral("static uint32_t hud_bar_tick; /* rendered HUD frames, 50 FPS */\n");
    // Shared 8x16 text style, matching Adventure dialogue's four-direction outline.
    c+=QStringLiteral("static void hud_draw_text(int32_t x,int32_t y,char *text) __attribute__((unused));\n"
        "static void hud_draw_text(int32_t x,int32_t y,char *text) {\n");
    if(doc.outlineEnabled) {
        c+=QStringLiteral("    gfx_setcolour(%1u);\n"
            "    gfx_drawtext(x-1,y,text); gfx_drawtext(x+1,y,text);\n"
            "    gfx_drawtext(x,y-1,text); gfx_drawtext(x,y+1,text);\n").arg(doc.outlineColour);
    }
    c+=QStringLiteral("    gfx_setcolour(%1u); gfx_drawtext(x,y,text);\n}\n")
        .arg(doc.colour);
    const int dockPixels=doc.dock=="overlay"?0:h;
    const bool dockTop=doc.dock=="top";
    c+=QStringLiteral("uint16_t gamehud_dock_height(void) {return %1u;}\n"
        "uint8_t gamehud_dock_top(void) {return %2u;}\n")
        .arg(dockPixels).arg(dockTop?1:0);
    c+=QStringLiteral(
        "/* SIDBOX foreground is 8-bit column-major: stride is bytes per column.\n"
        "   Crop to the actual play area and shift it down for top docking.\n"
        "   No framebuffer rescale or palette conversion is performed. */\n"
        "void gamehud_apply_dock(gfx_bitmap_t *buffer) {\n"
        "    const uint16_t dock=gamehud_dock_height();\n"
        "    if(!dock || dock>=320u || !buffer || !buffer->bitmap ||\n"
        "       buffer->width<480u || buffer->height<320u || buffer->stride<320u ||\n"
        "       buffer->memspacelen<(uint32_t)buffer->stride*480u) return;\n"
        "    const uint16_t play=(uint16_t)(320u-dock);\n"
        "    for(uint32_t x=0;x<480u;++x) {\n"
        "        uint8_t *column=buffer->bitmap+x*buffer->stride;\n"
        "        if(gamehud_dock_top()) { memmove(column+dock,column,play); memset(column,0,dock); }\n"
        "        else memset(column+play,0,dock);\n"
        "    }\n"
        "}\n");
    c+=QStringLiteral("void game_show_hud_at(int32_t x, int32_t y) {\n"
        "    gfxbob_t background = {0};\n"
        "    background.imgdat=(uint8_t *)hud_pixels; background.atlas_stride=%1u;\n"
        "    background.atlas_height=%2u; background.width=%1u; background.height=%2u;\n"
        "    background.scale=100u; background.drawx=x; background.drawy=y;\n"
        "    gfx_drawbob(&background);\n").arg(w).arg(h);
    for(const HudLabel &label:doc.labels) {
        if(label.text.isEmpty())continue;
        c+=QStringLiteral("    hud_draw_text(x+%1,y+%2,(char *)%3);\n")
            .arg(qBound(-480,label.x,480)).arg(qBound(-320,label.y,320)).arg(quoted(label.text));
    }
    c+=iconDraws;
    c+=barDraws;
    c+=statDraws;
    if(!doc.bars.isEmpty())c+=QStringLiteral("    ++hud_bar_tick;\n");
    c+=QStringLiteral("}\n"
        "void game_show_hud(int32_t x, int32_t y) {\n"
        "    /* (0,0) uses the designer's saved LCD position. */\n"
        "    if (x==0 && y==0) { x=%1; y=%2; }\n"
        "    game_show_hud_at(x,y);\n}\n").arg(doc.hudX).arg(doc.hudY);
    const QString header=QStringLiteral("/* GENERATED shared HUD API. */\n#ifndef CODERGIRL_GAMEHUD_H\n#define CODERGIRL_GAMEHUD_H\n#include <stdint.h>\n#include \"apis.h\"\n"
        "/* Screen coordinates. (0,0) uses the saved HUD Designer position. */\n"
        "void game_show_hud(int32_t x,int32_t y);\n"
        "/* Explicit screen position, including actual top-left (0,0). */\n"
        "void game_show_hud_at(int32_t x,int32_t y);\n"
        "uint16_t gamehud_dock_height(void);\n"
        "uint8_t gamehud_dock_top(void);\n"
        "void gamehud_apply_dock(gfx_bitmap_t *buffer);\n#endif\n");
    // Two files are generated only after all referenced assets are validated.
    if(!writeFile(QDir(hudFolder).filePath("gamehud.c"),c.toUtf8(),error))return false;
    if(!writeFile(QDir(hudFolder).filePath("gamehud.h"),header.toUtf8(),error))return false;
    return true;
}
}

bool editGameHud(QWidget *parent,const QString &projectRoot,QString *error) {
    HudDoc doc;
    const QString sharedFile=QDir(projectRoot).filePath("gamehud.sbhud");
    if(QFileInfo::exists(sharedFile)) {
        QFile f(sharedFile);
        if(!f.open(QIODevice::ReadOnly)||!doc.load(QJsonDocument::fromJson(f.readAll()).object())){
            if(error)*error=QStringLiteral("Invalid shared HUD file: %1").arg(sharedFile);
            return false;
        }
    }else doc.resize(doc.columns,doc.rows);
    const QVector<Pickup> pickups=discover(projectRoot);
    updateCounterArtwork(doc,pickups); // migrate old first-cell HUD placements
    QDialog dialog(parent);dialog.setWindowTitle(QObject::tr("Shared HUD Designer"));
    auto *outer=new QVBoxLayout(&dialog);
    auto *geometry=new QHBoxLayout;
    auto *columns=new QSpinBox(&dialog),*rows=new QSpinBox(&dialog),*cw=new QSpinBox(&dialog),*ch=new QSpinBox(&dialog);
    columns->setRange(1,60);rows->setRange(1,40);cw->setRange(1,64);ch->setRange(1,64);
    columns->setValue(doc.columns);rows->setValue(doc.rows);cw->setValue(doc.cw);ch->setValue(doc.ch);
    for(auto pair: {qMakePair(QObject::tr("Width (cells)"),columns),qMakePair(QObject::tr("Height (cells)"),rows),
                    qMakePair(QObject::tr("Cell W"),cw),qMakePair(QObject::tr("Cell H"),ch)}){
        geometry->addWidget(new QLabel(pair.first,&dialog));geometry->addWidget(pair.second);
    }
    // The selected HUD palette affects display only. All PPB pixel indices
    // stay exactly as stored, including tiles and collectable icons.
    auto *paletteRow=new QHBoxLayout;
    auto *textPaletteCombo=new QComboBox(&dialog);
    textPaletteCombo->addItem(QObject::tr("HUD tile atlas palette (default)"),QString());
    QStringList paletteFiles;
    QDirIterator palettes(projectRoot,{"*.pal","*.PAL","*.act","*.ACT","*.ppb","*.PPB"},QDir::Files,QDirIterator::Subdirectories);
    while(palettes.hasNext()) {
        const QString relative=QDir(projectRoot).relativeFilePath(palettes.next());
        if(!relative.startsWith("build/",Qt::CaseInsensitive) && !relative.contains("/backup/",Qt::CaseInsensitive))
            paletteFiles.append(relative);
    }
    paletteFiles.removeDuplicates();paletteFiles.sort(Qt::CaseInsensitive);
    for(const QString &file:paletteFiles)textPaletteCombo->addItem(file,file);
    if(!doc.textPalette.isEmpty() && textPaletteCombo->findData(doc.textPalette)<0)
        textPaletteCombo->addItem(doc.textPalette,doc.textPalette);
    textPaletteCombo->setCurrentIndex(qMax(0,textPaletteCombo->findData(doc.textPalette)));
    paletteRow->addWidget(new QLabel(QObject::tr("HUD palette source (tiles, text, items):"),&dialog));
    paletteRow->addWidget(textPaletteCombo,1);
    paletteRow->addWidget(new QLabel(QObject::tr("Use the same CLUT as the world's foreground"),&dialog));
    outer->addLayout(paletteRow);
    auto *colour=new QSpinBox(&dialog);colour->setRange(0,255);colour->setValue(doc.colour);
    geometry->addWidget(new QLabel(QObject::tr("Text foreground"),&dialog));geometry->addWidget(colour);
    auto *foregroundSwatch=new QLabel(&dialog);foregroundSwatch->setFixedSize(24,20);
    geometry->addWidget(foregroundSwatch);
    auto *pickForeground=new QPushButton(QObject::tr("Choose..."),&dialog);
    geometry->addWidget(pickForeground);
    auto *enableOutline=new QCheckBox(QObject::tr("Outline text"),&dialog);
    enableOutline->setChecked(doc.outlineEnabled);geometry->addWidget(enableOutline);
    auto *outlineColour=new QSpinBox(&dialog);
    outlineColour->setRange(0,255);outlineColour->setValue(doc.outlineColour);
    outlineColour->setEnabled(doc.outlineEnabled);
    outlineColour->setProperty("adventureGuard", true);
    outlineColour->style()->unpolish(outlineColour);
    outlineColour->style()->polish(outlineColour);
    outlineColour->setToolTip(QObject::tr("Only available when HUD text outline is enabled."));
    geometry->addWidget(new QLabel(QObject::tr("Outline colour"),&dialog));geometry->addWidget(outlineColour);
    auto *outlineSwatch=new QLabel(&dialog);outlineSwatch->setFixedSize(24,20);
    geometry->addWidget(outlineSwatch);
    auto *pickOutline=new QPushButton(QObject::tr("Choose..."),&dialog);
    geometry->addWidget(pickOutline);
    geometry->addStretch(1);outer->addLayout(geometry);
    auto *mainSplit=new QSplitter(Qt::Horizontal,&dialog);outer->addWidget(mainSplit,1);
    auto *side=new QWidget(mainSplit);auto *sideLayout=new QVBoxLayout(side);
    sideLayout->addWidget(new QLabel(QObject::tr("HUD tile atlas (Game Resources PPB)"),side));
    auto *atlasCombo=new QComboBox(side);
    const QStringList worlds=QDir(projectRoot).entryList({"*.sbgm"},QDir::Files,QDir::Name);
    QStringList atlasPaths;
    // Include ALL PPB Game Resources, not only tileatlas resources. The user may
    // build a HUD from sprites, decorative graphics, or a dedicated HUD sheet.
    for(const QString &world:worlds){
        QFile f(QDir(projectRoot).filePath(world));if(!f.open(QIODevice::ReadOnly))continue;
        for(const QJsonValue &v:QJsonDocument::fromJson(f.readAll()).object().value("resources").toArray()){
            const QJsonObject r=v.toObject();
            const QString path=QDir::cleanPath(r.value("path").toString());
            if(path.endsWith(".ppb",Qt::CaseInsensitive)&&!atlasPaths.contains(path))atlasPaths.append(path);
        }
    }
    // Also offer PPBs not yet assigned to a world (e.g. a HUD-only atlas).
    QDirIterator allPpbs(projectRoot,{"*.ppb","*.PPB"},QDir::Files,QDirIterator::Subdirectories);
    while(allPpbs.hasNext()){
        const QString relative=QDir(projectRoot).relativeFilePath(allPpbs.next());
        if(relative.startsWith("build/",Qt::CaseInsensitive)||relative.startsWith(".git/",Qt::CaseInsensitive) ||
           relative.contains("/backup/",Qt::CaseInsensitive))continue;
        if(!atlasPaths.contains(relative))atlasPaths.append(relative);
    }
    atlasPaths.sort(Qt::CaseInsensitive);
    if(!doc.atlas.isEmpty()&&!atlasPaths.contains(doc.atlas))atlasPaths.append(doc.atlas);
    atlasCombo->addItem(QObject::tr("No atlas"),QString());
    for(const QString &path:atlasPaths)atlasCombo->addItem(path,path);
    atlasCombo->setCurrentIndex(qMax(0,atlasCombo->findData(doc.atlas)));
    sideLayout->addWidget(atlasCombo);
    auto *picker=new AtlasPicker(side);
    auto *pickerScroll=new HudZoomScroll(side);pickerScroll->setWidgetResizable(false);pickerScroll->setWidget(picker);
    pickerScroll->stepZoom=[picker](int d){picker->zoom=qBound(1,picker->zoom+d,10);picker->refresh();};
    pickerScroll->setMinimumHeight(175);pickerScroll->setMinimumWidth(180);
    sideLayout->addWidget(pickerScroll,3);
    sideLayout->addWidget(new QLabel(QObject::tr("Mouse wheel: zoom atlas (scrollbars show the complete sheet)"),side));
    auto *flipRow=new QHBoxLayout;
    auto *flipX=new QCheckBox(QObject::tr("Flip X"),side),*flipY=new QCheckBox(QObject::tr("Flip Y"),side);
    flipRow->addWidget(flipX);flipRow->addWidget(flipY);sideLayout->addLayout(flipRow);
    auto *mirrorRow=new QHBoxLayout;
    auto *mirrorX=new QPushButton(QObject::tr("Mirror whole X"),side),*mirrorY=new QPushButton(QObject::tr("Mirror whole Y"),side);
    mirrorRow->addWidget(mirrorX);mirrorRow->addWidget(mirrorY);sideLayout->addLayout(mirrorRow);
    auto *pickupLabel=new QLabel(QObject::tr("Show in HUD collectables (all worlds):"),side);
    sideLayout->addWidget(pickupLabel);
    auto *list=new PickupList(side);
    list->setIconSize(QSize(28,28));
    for(const Pickup &p:pickups){
        auto *item=new QListWidgetItem(QIcon(QPixmap::fromImage(visible(p.iconImage)).scaled(28,28)),
            QStringLiteral("%1 (type %2)").arg(p.name).arg(p.kind),list);
        const QJsonObject data{{"kind",p.kind},{"name",p.name},{"source",p.source},
            {"iw",p.iw},{"ih",p.ih},{"icon",p.icon},{"iconTileSize",p.iconTileSize},
            {"icon2x2",p.icon2x2},{"iconCells",p.iconCells},{"spriteStamp",p.spriteStamp}};
        item->setData(Qt::UserRole,QJsonDocument(data).toJson(QJsonDocument::Compact));
    }
    sideLayout->addWidget(list,2);
    sideLayout->addWidget(new QLabel(QObject::tr("Drag numeric player stats onto HUD:"),side));
    auto *numbersList=new ProgressBarList(side,kStatMime);
    const auto addNumeric=[&](const QString &title,const QString &binding) {
        auto *item=new QListWidgetItem(title,numbersList);item->setData(Qt::UserRole,binding);
    };
    addNumeric(QObject::tr("Health"),"health");
    addNumeric(QObject::tr("Lives"),"lives");
    addNumeric(QObject::tr("Score"),"score");
    const QStringList playerFiles=QDir(QDir(projectRoot).filePath("players"))
        .entryList({"*.sbpi"},QDir::Files,QDir::Name);
    for(const QString &player:playerFiles) {
        QFile pf(QDir(projectRoot).filePath(QStringLiteral("players/")+player));
        if(!pf.open(QIODevice::ReadOnly))continue;
        for(const QJsonValue &value:QJsonDocument::fromJson(pf.readAll()).object().value("customStats").toArray()) {
            const QString name=value.toObject().value("name").toString();
            if(!name.isEmpty())addNumeric(name,QStringLiteral("stat:")+name);
        }
    }
    sideLayout->addWidget(numbersList,1);
    sideLayout->addWidget(new QLabel(QObject::tr("Drag an animated progress bar onto the HUD:"),side));
    auto *barsList=new ProgressBarList(side);
    const auto addBarChoice=[&](const QString &name,const QString &key) {
        auto *item=new QListWidgetItem(name,barsList);
        item->setData(Qt::UserRole,key);
    };
    addBarChoice(QObject::tr("Health"),"health");
    addBarChoice(QObject::tr("Lives"),"lives");
    addBarChoice(QObject::tr("Score"),"score");
    const QStringList players=QDir(QDir(projectRoot).filePath("players"))
        .entryList({"*.sbpi"},QDir::Files,QDir::Name);
    for(const QString &player:players) {
        QFile f(QDir(projectRoot).filePath(QStringLiteral("players/")+player));
        if(!f.open(QIODevice::ReadOnly))continue;
        const QJsonArray stats=QJsonDocument::fromJson(f.readAll()).object().value("customStats").toArray();
        for(const QJsonValue &v:stats) {
            const QString name=v.toObject().value("name").toString();
            if(!name.isEmpty())addBarChoice(QObject::tr("Stat: %1").arg(name),"stat:"+name);
        }
    }
    for(const Pickup &pickup:pickups)
        addBarChoice(QObject::tr("Collectable: %1").arg(pickup.name),
            QStringLiteral("pickup:%1").arg(pickup.kind));
    sideLayout->addWidget(barsList,1);
    sideLayout->addWidget(new QLabel(QObject::tr("Double-click a placed bar to choose PPB frames, animation and value limits."),side));
    auto *kindNote=new QLabel(QObject::tr("Counters use Pickup Type IDs. Give different collectable TYPES different IDs; the same ID across worlds shares one total."),side);
    kindNote->setWordWrap(true);sideLayout->addWidget(kindNote);
    if(list->count()==0) {
        auto *note=new QLabel(QObject::tr("Not seeing anything in the list? Double-check your collectables' Show in HUD setting in each world, then Save Design."),side);
        note->setWordWrap(true);sideLayout->addWidget(note);
    }
    auto *right=new QWidget(mainSplit);auto *rightLayout=new QVBoxLayout(right);
    rightLayout->addWidget(new QLabel(QObject::tr("Drag collectables onto the HUD. Grab icons, text or progress bars to move; right-click to delete."),right));
    auto *addBarButton=new QPushButton(QObject::tr("+ Animated progress bar (PPB)"),right);
    rightLayout->addWidget(addBarButton);
    auto *hideOverlays=new QCheckBox(QObject::tr("Hide text and items (paint tiles underneath)"),right);
    rightLayout->addWidget(hideOverlays);
    HudCanvas *canvas=new HudCanvas(right);canvas->doc=&doc;canvas->root=projectRoot;
    auto *scroll=new HudZoomScroll(right);scroll->setWidgetResizable(false);scroll->setWidget(canvas);
    scroll->stepZoom=[canvas](int d){canvas->zoom=qBound(1,canvas->zoom+d,10);canvas->refresh();};
    rightLayout->addWidget(scroll,1);
    // Bars belong to this HUD, and can be repositioned like labels and counters.
    // Their animated frames are selected from a normal existing PPB sheet.
    const auto editProgressBar = [&](int index) -> bool {
        if(index<0 && doc.bars.size()>=32) {
            QMessageBox::warning(&dialog,QObject::tr("HUD Bars"),QObject::tr("Maximum 32 progress bars."));return false;
        }
        HudBar b=index>=0 ? doc.bars.at(index) : HudBar();
        if(index<0 && b.width>doc.columns*doc.cw)b.width=doc.columns*doc.cw;
        QDialog editor(&dialog);
        editor.setWindowTitle(index>=0 ? QObject::tr("Edit Animated Progress Bar")
            : QObject::tr("Add Animated Progress Bar"));
        auto *layout=new QVBoxLayout(&editor);
        auto *form=new QFormLayout;
        auto *binding=new QComboBox(&editor);
        binding->addItem(QObject::tr("Player Health"),"health");
        binding->addItem(QObject::tr("Player Lives"),"lives");
        binding->addItem(QObject::tr("Player Score"),"score");
        const QStringList playerFiles=QDir(QDir(projectRoot).filePath("players"))
            .entryList({"*.sbpi"},QDir::Files,QDir::Name);
        for(const QString &playerFile:playerFiles) {
            QFile f(QDir(projectRoot).filePath(QStringLiteral("players/")+playerFile));
            if(!f.open(QIODevice::ReadOnly))continue;
            const QJsonArray stats=QJsonDocument::fromJson(f.readAll()).object().value("customStats").toArray();
            for(const QJsonValue &value:stats) {
                const QString name=value.toObject().value("name").toString();
                if(!name.isEmpty() && binding->findData("stat:"+name)<0)
                    binding->addItem(QObject::tr("Player stat: %1").arg(name),"stat:"+name);
            }
        }
        for(const Pickup &pickup:pickups) {
            const QString key=QStringLiteral("pickup:%1").arg(pickup.kind);
            if(binding->findData(key)<0)
                binding->addItem(QObject::tr("Collectable: %1 (type %2)").arg(pickup.name).arg(pickup.kind),key);
        }
        if(binding->findData(b.binding)<0)binding->addItem(b.binding,b.binding);
        binding->setCurrentIndex(qMax(0,binding->findData(b.binding)));
        form->addRow(QObject::tr("Bar reads"),binding);
        auto *ppb=new QComboBox(&editor);
        for(const QString &path:atlasPaths)ppb->addItem(path,path);
        if(!b.source.isEmpty() && ppb->findData(b.source)<0)ppb->addItem(b.source,b.source);
        ppb->setCurrentIndex(qMax(0,ppb->findData(b.source)));
        form->addRow(QObject::tr("PPB atlas"),ppb);
        auto *frameSize=new QComboBox(&editor);
        frameSize->addItem(QObject::tr("8 x 8 cell"),8);
        frameSize->addItem(QObject::tr("16 x 16 (2x2 8px cells)"),16);
        frameSize->setCurrentIndex(b.frameSize==16?1:0);
        form->addRow(QObject::tr("Animation cell"),frameSize);
        auto *start=new QSpinBox(&editor);start->setRange(0,65535);start->setValue(b.startFrame);
        form->addRow(QObject::tr("First frame index"),start);
        auto *count=new QSpinBox(&editor);count->setRange(1,64);count->setValue(b.frameCount);
        form->addRow(QObject::tr("Number of frames"),count);
        auto *ticks=new QSpinBox(&editor);ticks->setRange(1,300);ticks->setValue(b.frameTicks);
        ticks->setSuffix(QObject::tr(" frames (50 FPS)"));
        form->addRow(QObject::tr("Time per frame"),ticks);
        auto *loop=new QCheckBox(QObject::tr("Loop animation"),&editor);loop->setChecked(b.loop);
        form->addRow(QString(),loop);
        auto *width=new QSpinBox(&editor);width->setRange(1,480);width->setValue(b.width);
        width->setSuffix(QObject::tr(" pixels"));
        form->addRow(QObject::tr("Filled width at 100%"),width);
        auto *minimum=new QSpinBox(&editor);minimum->setRange(-1000000,1000000);minimum->setValue(b.minimum);
        form->addRow(QObject::tr("Value for 0% (empty)"),minimum);
        auto *maximum=new QSpinBox(&editor);maximum->setRange(-1000000,1000000);maximum->setValue(b.maximum);
        form->addRow(QObject::tr("Value for 100% (full)"),maximum);
        auto *preview=new QSpinBox(&editor);preview->setRange(0,100);preview->setValue(b.preview);
        preview->setSuffix("%");
        form->addRow(QObject::tr("Editor preview fill"),preview);
        layout->addLayout(form);
        layout->addWidget(new QLabel(QObject::tr("Click a frame in the original PPB. At runtime all segments use\n"
            "the SAME frame, and the final segment is clipped to the pixel.\n"
            "Frames advance left-to-right then top-to-bottom on the chosen grid."),&editor));
        auto *framePicker=new AtlasPicker(&editor);
        auto *frameScroll=new QScrollArea(&editor);frameScroll->setWidgetResizable(false);
        frameScroll->setWidget(framePicker);frameScroll->setMinimumSize(320,140);
        layout->addWidget(frameScroll,1);
        const auto refreshFrames=[&]() {
            const QImage image=loadIndexed(QDir(projectRoot).filePath(ppb->currentData().toString()));
            framePicker->source=hudPreview(image,canvas->textColors);
            framePicker->cw=framePicker->ch=frameSize->currentData().toInt();
            const int total=(image.width()/framePicker->cw)*(image.height()/framePicker->ch);
            start->setMaximum(qMax(0,total-1));
            count->setMaximum(qMax(1,qMin(64,total-start->value())));
            framePicker->index=start->value();framePicker->refresh();
        };
        framePicker->picked=[&](int frame){start->setValue(frame);};
        QObject::connect(ppb,qOverload<int>(&QComboBox::currentIndexChanged),&editor,[&](int){refreshFrames();});
        QObject::connect(frameSize,qOverload<int>(&QComboBox::currentIndexChanged),&editor,[&](int){refreshFrames();});
        QObject::connect(start,qOverload<int>(&QSpinBox::valueChanged),&editor,[&](int){refreshFrames();});
        refreshFrames();
        auto *buttons=new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel,&editor);
        layout->addWidget(buttons);
        QObject::connect(buttons,&QDialogButtonBox::rejected,&editor,&QDialog::reject);
        QObject::connect(buttons,&QDialogButtonBox::accepted,&editor,[&]() {
            if(ppb->currentData().toString().isEmpty() || framePicker->source.isNull()) {
                QMessageBox::warning(&editor,QObject::tr("Progress Bar"),QObject::tr("Choose an existing PPB atlas."));return;
            }
            if(minimum->value()>=maximum->value()) {
                QMessageBox::warning(&editor,QObject::tr("Progress Bar"),QObject::tr("100% value must exceed 0% value."));return;
            }
            if(width->value()>doc.columns*doc.cw || width->value()>480 ||
               frameSize->currentData().toInt()>doc.rows*doc.ch) {
                QMessageBox::warning(&editor,QObject::tr("Progress Bar"),
                    QObject::tr("Bar must fit inside the HUD. Resize the HUD first."));return;
            }
            b.source=ppb->currentData().toString();b.binding=binding->currentData().toString();
            b.frameSize=frameSize->currentData().toInt();b.startFrame=start->value();
            b.frameCount=count->value();b.frameTicks=ticks->value();b.loop=loop->isChecked();
            b.width=width->value();b.minimum=minimum->value();b.maximum=maximum->value();
            b.preview=preview->value();
            b.x=qBound(0,b.x,doc.columns*doc.cw-b.width);
            b.y=qBound(0,b.y,doc.rows*doc.ch-b.frameSize);
            editor.accept();
        });
        editor.resize(570,700);
        if(editor.exec()!=QDialog::Accepted)return false;
        if(index>=0)doc.bars[index]=b;
        else doc.bars.append(b);
        canvas->barAtlases.remove(b.source);
        canvas->previewTick=0;
        canvas->selectedBar=index>=0 ? index : doc.bars.size()-1;
        canvas->selectedCounter=canvas->selectedLabel=-1;
        canvas->update();
        return true;
    };
    canvas->editBar=editProgressBar;
    QObject::connect(addBarButton,&QPushButton::clicked,&dialog,[&](){editProgressBar(-1);});
    auto *animationPreviewTimer=new QTimer(&dialog);
    animationPreviewTimer->setInterval(20); // preview uses the same 50 FPS count as SIDBOX
    QObject::connect(animationPreviewTimer,&QTimer::timeout,&dialog,[canvas](){
        if(!canvas->doc->bars.isEmpty() && !canvas->hideOverlays){++canvas->previewTick;canvas->update();}
    });
    animationPreviewTimer->start();
    rightLayout->addWidget(new QLabel(QObject::tr("Mouse wheel: zoom HUD tiles • 8×16 pixel font preview"),right));
    auto *labelRow=new QHBoxLayout;
    auto *textEdit=new QLineEdit(right);textEdit->setPlaceholderText(QObject::tr("Score:  /  Mana:  /  Coins:"));
    auto *placeText=new QCheckBox(QObject::tr("Place text (once)"),right);
    labelRow->addWidget(new QLabel(QObject::tr("Label:"),right));labelRow->addWidget(textEdit,1);labelRow->addWidget(placeText);
    rightLayout->addLayout(labelRow);
    rightLayout->addWidget(new QLabel(QObject::tr("Text is placed once and cleared. Double-click existing text to rename. HUD uses LCD coordinates."),right));
    auto *screenRow=new QHBoxLayout;
    auto *positionColumn=new QVBoxLayout;
    positionColumn->addWidget(new QLabel(QObject::tr("HUD SCREEN POSITION (480×320): click or drag the box"),right));
    auto *screenPreview=new HudScreenPreview(right);screenPreview->doc=&doc;
    positionColumn->addWidget(screenPreview);screenRow->addLayout(positionColumn);
    auto *xyColumn=new QVBoxLayout;
    auto *posX=new QSpinBox(right), *posY=new QSpinBox(right);
    posX->setRange(0,480-doc.columns*doc.cw);
    posY->setRange(0,320-doc.rows*doc.ch);
    posX->setValue(doc.hudX);posY->setValue(doc.hudY);
    auto *dockMode=new QComboBox(right);
    dockMode->addItem(QObject::tr("Overlay (original)"),QStringLiteral("overlay"));
    dockMode->addItem(QObject::tr("Dock HUD at top"),QStringLiteral("top"));
    dockMode->addItem(QObject::tr("Dock HUD at bottom"),QStringLiteral("bottom"));
    dockMode->setCurrentIndex(qMax(0,dockMode->findData(doc.dock)));
    xyColumn->addWidget(new QLabel(QObject::tr("HUD placement"),right));
    xyColumn->addWidget(dockMode);
    xyColumn->addWidget(new QLabel(QObject::tr("HUD X"),right));xyColumn->addWidget(posX);
    xyColumn->addWidget(new QLabel(QObject::tr("HUD Y"),right));xyColumn->addWidget(posY);
    xyColumn->addWidget(new QLabel(QObject::tr("game_show_hud(0, 0) uses this position.\n"
                                            "Nonzero x/y overrides it.\n"
                                            "game_show_hud_at(0, 0) forces top-left."),right));
    xyColumn->addStretch(1);screenRow->addLayout(xyColumn,1);
    rightLayout->addLayout(screenRow);
    mainSplit->setStretchFactor(0,1);mainSplit->setStretchFactor(1,3);
    const auto updateSwatches=[&]() {
        const auto style=[&](QLabel *widget,int index,QColor fallback){
            QColor c=paletteColour(canvas->textColors,index,fallback);
            if(c.alpha()==0)c.setAlpha(255);
            widget->setStyleSheet(QStringLiteral("background-color: %1; border: 1px solid #777;").arg(c.name()));
            widget->setToolTip(QObject::tr("CLUT index %1").arg(index));
        };
        style(foregroundSwatch,doc.colour,Qt::white);
        style(outlineSwatch,doc.outlineColour,Qt::black);
    };
    const auto updateAtlas=[&]() {
        doc.atlas=atlasCombo->currentData().toString();
        const QImage src=loadIndexed(QDir(projectRoot).filePath(doc.atlas));
        canvas->atlasImage=src;canvas->pickedTile=0;
        canvas->textColors=textPaletteFor(projectRoot,doc.textPalette,src);
        picker->source=hudPreview(src,canvas->textColors);
        picker->cw=doc.cw;picker->ch=doc.ch;picker->index=0;picker->refresh();
        for(int n=0;n<pickups.size();++n){
            QImage image=visible(hudPreview(pickups[n].iconImage,canvas->textColors));
            list->item(n)->setIcon(QIcon(QPixmap::fromImage(image).scaled(28,28)));
        }
        canvas->refresh();updateSwatches();
    };
    QObject::connect(atlasCombo,qOverload<int>(&QComboBox::currentIndexChanged),&dialog,[&](int){updateAtlas();});
    QObject::connect(textPaletteCombo,qOverload<int>(&QComboBox::currentIndexChanged),&dialog,[&](int){
        doc.textPalette=textPaletteCombo->currentData().toString();
        canvas->textColors=textPaletteFor(projectRoot,doc.textPalette,canvas->atlasImage);
        picker->source=hudPreview(canvas->atlasImage,canvas->textColors);
        picker->refresh();
        for(int n=0;n<pickups.size();++n){
            QImage image=visible(hudPreview(pickups[n].iconImage,canvas->textColors));
            list->item(n)->setIcon(QIcon(QPixmap::fromImage(image).scaled(28,28)));
        }
        canvas->update();updateSwatches();
    });
    QObject::connect(pickForeground,&QPushButton::clicked,&dialog,[&](){
        const int n=choosePaletteIndex(&dialog,canvas->textColors,doc.colour,QObject::tr("Text foreground index"));
        if(n>=0)colour->setValue(n);
    });
    QObject::connect(pickOutline,&QPushButton::clicked,&dialog,[&](){
        const int n=choosePaletteIndex(&dialog,canvas->textColors,doc.outlineColour,QObject::tr("Text outline index"));
        if(n>=0)outlineColour->setValue(n);
    });
    auto updateGeometry=[&]() {
        if(columns->value()*cw->value()>480||rows->value()*ch->value()>320){
            QMessageBox::warning(&dialog,QObject::tr("HUD Size"),QObject::tr("HUD must fit within the 480×320 LCD."));
            return;
        }
        // Never erase the composition just because the cell size changes.
        // Tile indices are retained; their sampling uses the new atlas grid.
        doc.resize(columns->value(),rows->value());doc.cw=cw->value();doc.ch=ch->value();
        doc.hudX=doc.dock=="overlay" ? qMin(doc.hudX,480-doc.columns*doc.cw) : 0;
        doc.hudY=doc.dock=="top" ? 0 : doc.dock=="bottom" ? 320-doc.rows*doc.ch
            : qMin(doc.hudY,320-doc.rows*doc.ch);
        posX->setMaximum(480-doc.columns*doc.cw);posY->setMaximum(320-doc.rows*doc.ch);
        posX->setValue(doc.hudX);posY->setValue(doc.hudY);
        screenPreview->update();
        picker->cw=doc.cw;picker->ch=doc.ch;picker->refresh();canvas->refresh();
    };
    for(QSpinBox *spin:{columns,rows,cw,ch})QObject::connect(spin,qOverload<int>(&QSpinBox::valueChanged),&dialog,[&](int){updateGeometry();});
    QObject::connect(colour,qOverload<int>(&QSpinBox::valueChanged),&dialog,[&](int n){doc.colour=n;canvas->update();updateSwatches();});
    QObject::connect(enableOutline,&QCheckBox::toggled,&dialog,[&](bool enabled){
        doc.outlineEnabled=enabled;outlineColour->setEnabled(enabled);canvas->update();
    });
    QObject::connect(outlineColour,qOverload<int>(&QSpinBox::valueChanged),&dialog,[&](int n){
        doc.outlineColour=n;canvas->update();updateSwatches();
    });
    QObject::connect(posX,qOverload<int>(&QSpinBox::valueChanged),&dialog,[&](int n){doc.hudX=n;screenPreview->update();});
    QObject::connect(posY,qOverload<int>(&QSpinBox::valueChanged),&dialog,[&](int n){doc.hudY=n;screenPreview->update();});
    screenPreview->moved=[&](){
        if(doc.dock!="overlay") {
            doc.hudX=0;doc.hudY=doc.dock=="top"?0:320-doc.rows*doc.ch;
            screenPreview->update();
        }
        posX->setValue(doc.hudX);posY->setValue(doc.hudY);
    };
    QObject::connect(dockMode,qOverload<int>(&QComboBox::currentIndexChanged),&dialog,[&](int){
        doc.dock=dockMode->currentData().toString();
        if(doc.dock!="overlay") {
            doc.hudX=0;doc.hudY=doc.dock=="top"?0:320-doc.rows*doc.ch;
        }
        posX->setEnabled(doc.dock=="overlay");posY->setEnabled(doc.dock=="overlay");
        posX->setValue(doc.hudX);posY->setValue(doc.hudY);
        screenPreview->update();
    });
    posX->setEnabled(doc.dock=="overlay");posY->setEnabled(doc.dock=="overlay");
    for (QSpinBox *position : {posX, posY}) {
        position->setProperty("adventureGuard", true);
        position->style()->unpolish(position);
        position->style()->polish(position);
        position->setToolTip(QObject::tr("Available only when HUD dock is set to Overlay. Other docking positions are automatic."));
    }
    QObject::connect(flipX,&QCheckBox::toggled,&dialog,[&](bool b){canvas->flipX=b;});
    QObject::connect(flipY,&QCheckBox::toggled,&dialog,[&](bool b){canvas->flipY=b;});
    QObject::connect(textEdit,&QLineEdit::textChanged,&dialog,[&](const QString &s){
        canvas->labelText=s;
        // Typing a label automatically arms one-shot placement. Clearing the
        // field after that placement disarms it, preventing accidental copies.
        if(!s.isEmpty() && !hideOverlays->isChecked())placeText->setChecked(true);
        else if(s.isEmpty())placeText->setChecked(false);
    });
    QObject::connect(placeText,&QCheckBox::toggled,&dialog,[&](bool b){canvas->placingLabel=b;});
    QObject::connect(hideOverlays,&QCheckBox::toggled,&dialog,[&](bool b){
        canvas->hideOverlays=b;canvas->selectedCounter=canvas->selectedLabel=canvas->selectedBar=canvas->selectedStat=-1;
        canvas->draggingOverlay=false;canvas->update();
        if(b)placeText->setChecked(false);
    });
    canvas->labelPlaced=[&](){
        // One-shot text stamping: after placing a label the edit is blank and
        // Place text is disarmed, so the next click cannot clone that label.
        placeText->setChecked(false);textEdit->clear();
    };
    picker->picked=[&](int index){canvas->pickedTile=index;};
    QObject::connect(mirrorX,&QPushButton::clicked,&dialog,[&] {
        for(int y=0;y<doc.rows;++y)for(int x=0;x<doc.columns/2;++x)
            std::swap(doc.tiles[y*doc.columns+x],doc.tiles[y*doc.columns+(doc.columns-1-x)]);
        for(Tile &t:doc.tiles) if(t.index>=0)t.fx=!t.fx;
        canvas->refresh();
    });
    QObject::connect(mirrorY,&QPushButton::clicked,&dialog,[&] {
        for(int y=0;y<doc.rows/2;++y)for(int x=0;x<doc.columns;++x)
            std::swap(doc.tiles[y*doc.columns+x],doc.tiles[(doc.rows-1-y)*doc.columns+x]);
        for(Tile &t:doc.tiles)if(t.index>=0)t.fy=!t.fy;
        canvas->refresh();
    });
    auto *buttons=new QDialogButtonBox(QDialogButtonBox::Save|QDialogButtonBox::Cancel,&dialog);outer->addWidget(buttons);
    QObject::connect(buttons,&QDialogButtonBox::rejected,&dialog,&QDialog::reject);
    QObject::connect(buttons,&QDialogButtonBox::accepted,&dialog,[&] {
        if(doc.dock!="overlay" && (doc.rows*doc.ch>=320 || doc.columns*doc.cw!=480)) {
            QMessageBox::warning(&dialog,QObject::tr("HUD Dock"),
                QObject::tr("Docked HUDs must be exactly 480 pixels wide and shorter than 320 pixels. "
                            "Set the HUD width (cells x cell width) to 480 first."));return;
        }
        if(doc.columns*doc.cw>480||doc.rows*doc.ch>320) {QMessageBox::warning(&dialog,QObject::tr("HUD"),QObject::tr("The HUD is larger than the LCD."));return;}
        QString issue;
        if(!doc.textPalette.isEmpty() && textPaletteFor(projectRoot,doc.textPalette,canvas->atlasImage).size()!=256) {
            QMessageBox::warning(&dialog,QObject::tr("HUD Text Palette"),
                QObject::tr("Selected HUD palette is missing or invalid. Choose a valid 256-colour .pal/.act/.ppb source."));
            return;
        }
        if(!exportHud(projectRoot,doc,&issue) || !writeFile(sharedFile,QJsonDocument(doc.json()).toJson(QJsonDocument::Indented),&issue) || !registerHudFiles(projectRoot,&issue)){
            QMessageBox::warning(&dialog,QObject::tr("HUD Export"),issue);return;
        }
        dialog.accept();
    });
    updateAtlas();canvas->refresh();
    QSettings hudWindowSettings(QStringLiteral("Sidbox"), QStringLiteral("SidboxIDE"));
    if (!dialog.restoreGeometry(hudWindowSettings.value(
            QStringLiteral("GameHudEditor/geometry")).toByteArray()))
        dialog.setWindowState(dialog.windowState() | Qt::WindowMaximized);
    const int hudResult = dialog.exec();
    hudWindowSettings.setValue(QStringLiteral("GameHudEditor/geometry"), dialog.saveGeometry());
    return hudResult == QDialog::Accepted;
}


bool regenerateGameHud(const QString &projectRoot,QString *error) {
    QFile f(QDir(projectRoot).filePath(QStringLiteral("gamehud.sbhud")));
    if(!f.exists()) return true; // Existing projects without a HUD remain unchanged.
    if(!f.open(QIODevice::ReadOnly)) {if(error)*error=QStringLiteral("Cannot read shared HUD layout");return false;}
    HudDoc d;
    if(!d.load(QJsonDocument::fromJson(f.readAll()).object())) {
        if(error)*error=QStringLiteral("Invalid shared HUD layout");return false;
    }
    updateCounterArtwork(d,discover(projectRoot));
    return exportHud(projectRoot,d,error);
}
