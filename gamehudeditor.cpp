#include "gamehudeditor.h"
#include "ppbcodec.h"
#include "gamepalette.h"
#include <QAbstractItemView>
#include <QApplication>
#include <QCheckBox>
#include <QComboBox>
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
#include <QFontDatabase>
#include <QWheelEvent>
#include <QFontMetrics>
#include <QFormLayout>
#include <QGroupBox>
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
#include <climits>

namespace {
const char *kMime = "application/x-codergirl-hud-pickup";
struct Tile { int index=-1; bool fx=false, fy=false; };
struct HudLabel { QString text; int x=0,y=0; };
struct HudCounter { int kind=0,x=0,y=0,iw=16,ih=16; QString name,source; };
struct Pickup { int kind=0,iw=16,ih=16; QString name,source; QImage icon; };
struct HudDoc {
    int columns=30, rows=5, cw=8, ch=8, colour=15, outlineColour=0;
    bool outlineEnabled=false;
    int hudX=0, hudY=0;
    QString atlas;
    QString textPalette; // shared HUD CLUT reference for tiles, text and collectible icons
    QVector<Tile> tiles;
    QVector<HudLabel> labels;
    QVector<HudCounter> counters;
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
            {"hudX",hudX},{"hudY",hudY}};
        QJsonArray t;
        for (const Tile &c:tiles) t.append(QJsonObject{{"index",c.index},{"flipX",c.fx},{"flipY",c.fy}});
        j.insert("cells",t);
        QJsonArray l;
        for (const HudLabel &v:labels) l.append(QJsonObject{{"text",v.text},{"x",v.x},{"y",v.y}});
        j.insert("labels",l);
        QJsonArray cnt;
        for (const HudCounter &v:counters) cnt.append(QJsonObject{{"kind",v.kind},{"x",v.x},{"y",v.y},
            {"source",v.source},{"name",v.name},{"iconWidth",v.iw},{"iconHeight",v.ih}});
        j.insert("counters",cnt);
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
        tiles.resize(columns*rows);
        const QJsonArray arr=j.value("cells").toArray();
        for (int n=0;n<tiles.size() && n<arr.size();++n) {
            const QJsonObject c=arr[n].toObject();
            tiles[n]={c.value("index").toInt(-1),c.value("flipX").toBool(),c.value("flipY").toBool()};
        }
        labels.clear(); counters.clear();
        for (const QJsonValue &v:j.value("labels").toArray()) {
            const QJsonObject o=v.toObject();
            if(labels.size()<80) labels.append({o.value("text").toString().left(60),o.value("x").toInt(),o.value("y").toInt()});
        }
        for (const QJsonValue &v:j.value("counters").toArray()) {
            const QJsonObject o=v.toObject();
            if(counters.size()<32) counters.append({o.value("kind").toInt(),o.value("x").toInt(),o.value("y").toInt(),
                o.value("iconWidth").toInt(16),o.value("iconHeight").toInt(16),o.value("name").toString(),o.value("source").toString()});
        }
        return true;
    }
};

static QImage loadIndexed(const QString &file) {
    SidboxPpb::Picture picture;
    if(!SidboxPpb::read(file,&picture)) return {};
    return picture.indexed;
}
static QImage firstIcon(const QString &file,int w,int h) {
    const QImage src=loadIndexed(file);
    if(src.isNull()) return {};
    return src.copy(0,0,qMin(src.width(),qBound(1,w,64)),qMin(src.height(),qBound(1,h,64)));
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
    QVector<Pickup> out; QMap<int,Pickup> byKind;
    const QStringList worlds=QDir(root).entryList({"*.sbgm"},QDir::Files,QDir::Name);
    for(const QString &world:worlds) {
        QFile file(QDir(root).filePath(world));
        if(!file.open(QIODevice::ReadOnly)) continue;
        const QJsonDocument d=QJsonDocument::fromJson(file.readAll());
        if(!d.isObject()) continue;
        for(const QJsonValue &value:d.object().value("resources").toArray()) {
            const QJsonObject r=value.toObject(), object=r.value("gameObject").toObject();
            if(r.value("kind").toString()!="sprite" || object.value("type").toString()!="collectable" ||
               !object.value("pickupShowHud").toBool()) continue;
            const int kind=object.value("pickupKind").toInt();
            if(kind<1 || kind>255 || byKind.contains(kind)) continue;
            const QString source=QDir::cleanPath(r.value("path").toString());
            Pickup p; p.kind=kind; p.name=r.value("name").toString(); p.source=source;
            p.iw=qBound(1,r.value("cellWidth").toInt(16),64);
            p.ih=qBound(1,r.value("cellHeight").toInt(16),64);
            p.icon=firstIcon(QDir(root).filePath(source),p.iw,p.ih);
            byKind.insert(kind,p);
        }
    }
    for(auto it=byKind.cbegin();it!=byKind.cend();++it) out.append(it.value());
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
// Render a fixed 8x16 cell per character in the editor preview, matching
// SIDBOX's glyph spacing. Qt supplies the closest available mono glyph shapes.
static QColor paletteColour(const QVector<QRgb> &palette, int index, QColor fallback) {
    return index>=0 && index<palette.size() ? QColor::fromRgba(palette.at(index)) : fallback;
}
// The HUD is one indexed foreground layer: all tile and sprite pixels must
// refer to the SAME active foreground CLUT. Preserve PPB source colours by
// mapping them into the selected HUD palette at export time. An exact colour
// wins; if the bank lacks it, choose the closest available opaque colour.
// Index zero is always reserved for foreground transparency.
static QVector<QRgb> textPaletteFor(const QString &root, const QString &paletteSource,
                                   const QImage &atlas) {
    if (paletteSource.isEmpty()) return atlas.colorTable();
    return SidboxGamePalette::readPalette(QDir(root).filePath(paletteSource),false);
}
static QVector<uchar> hudColourMap(const QImage &source, const QVector<QRgb> &target) {
    QVector<uchar> lookup(256);
    for (int i=0;i<256;++i) lookup[i]=(uchar)i;
    if (source.isNull() || target.size()!=256) return lookup;
    const auto colours=source.colorTable();
    if (colours.isEmpty()) return lookup;
    lookup[0]=0;
    for (int i=1;i<256;++i) {
        if(i>=colours.size()) {lookup[i]=0;continue;}
        const QRgb wanted=colours.at(i);
        // In indexed foreground art, only index 0 is transparent. Older
        // PPBs sometimes carry zero alpha in otherwise valid colour slots.
        int choice=1, distance=INT_MAX;
        for(int j=1;j<256;++j) {
            const QRgb candidate=target.at(j);
            const int dr=qRed(wanted)-qRed(candidate);
            const int dg=qGreen(wanted)-qGreen(candidate);
            const int db=qBlue(wanted)-qBlue(candidate);
            const int score=dr*dr+dg*dg+db*db;
            if(score<distance){distance=score;choice=j;if(!score)break;}
        }
        lookup[i]=(uchar)choice;
    }
    return lookup;
}
static QImage hudPreview(const QImage &source,const QVector<QRgb> &target) {
    if(source.isNull()||target.size()!=256||source.format()!=QImage::Format_Indexed8)return source;
    QImage result=source;
    result.detach();
    const auto mapping=hudColourMap(source,target);
    for(int y=0;y<result.height();++y) {
        uchar *line=result.scanLine(y);
        for(int x=0;x<result.width();++x)line[x]=mapping[line[x]];
    }
    result.setColorTable(target);
    return result;
}
static int choosePaletteIndex(QWidget *parent, const QVector<QRgb> &palette, int current,
                              const QString &title) {
    if (palette.isEmpty()) return -1;
    QDialog dlg(parent);
    dlg.setWindowTitle(title);
    auto *layout=new QVBoxLayout(&dlg);
    layout->addWidget(new QLabel(QObject::tr("Select a foreground CLUT index (actual SIDBOX colour):"),&dlg));
    auto *scroller=new QScrollArea(&dlg);scroller->setWidgetResizable(true);
    auto *gridHost=new QWidget(scroller);
    auto *grid=new QGridLayout(gridHost);
    grid->setSpacing(2);grid->setContentsMargins(4,4,4,4);
    const int count=qMin(256,int(palette.size()));
    int chosen=-1;
    for(int n=0;n<count;++n) {
        QPushButton *button=new QPushButton(gridHost);
        button->setFixedSize(30,26);
        QColor color=QColor::fromRgba(palette[n]);
        if(color.alpha()==0)color.setAlpha(255);
        button->setStyleSheet(QStringLiteral("QPushButton { background-color: %1; border: %2px solid %3; border-radius: 0px; }")
            .arg(color.name()).arg(n==current?3:1).arg(n==current?"#FFFFFF":"#404040"));
        button->setToolTip(QObject::tr("Index %1  |  %2").arg(n).arg(color.name(QColor::HexArgb)));
        grid->addWidget(button,n/16,n%16);
        QObject::connect(button,&QPushButton::clicked,&dlg,[&dlg,&chosen,n](){chosen=n;dlg.accept();});
    }
    scroller->setWidget(gridHost);
    layout->addWidget(scroller);
    dlg.resize(610,510);
    return dlg.exec()==QDialog::Accepted?chosen:-1;
}
static void previewText(QPainter &p, const QString &text, int x, int y, int zoom,
                        QColor foreground, bool outline, QColor outlineColour) {
    if(text.isEmpty())return;
    const int baseWidth=qMax(8,8*int(text.size()));
    QFont font=QFontDatabase::systemFont(QFontDatabase::FixedFont);
    font.setPixelSize(15);font.setFixedPitch(true);
    const QFontMetrics fm(font);
    // Rasterise at Qt's native mono width, then fit exactly eight pixels per
    // character and sixteen pixels high, matching SIDBOX's character grid.
    QImage glyphs(qMax(baseWidth,fm.horizontalAdvance(text)+2),16,QImage::Format_ARGB32_Premultiplied);
    glyphs.fill(Qt::transparent);
    {
        QPainter t(&glyphs);t.setFont(font);t.setPen(foreground);
        t.drawText(glyphs.rect(),Qt::AlignLeft|Qt::AlignVCenter,text);
    }
    const QRect target(x*zoom,y*zoom,baseWidth*zoom,16*zoom);
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
    int selectedCounter=-1,selectedLabel=-1;
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
        return visible(img.mirrored(tile.fx,tile.fy));
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
        for(int i=0;i<doc->counters.size();++i) {
            const HudCounter &c=doc->counters[i];
            QImage icon=visible(hudPreview(firstIcon(QDir(root).filePath(c.source),c.iw,c.ih),textColors));
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
        selectedCounter=selectedLabel=-1;
        if(hideOverlays)return;
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
            if(selectedCounter>=0)doc->counters.removeAt(selectedCounter);
            else if(selectedLabel>=0)doc->labels.removeAt(selectedLabel);
            else {paintStrokeTo(q,true);return;}
            selectedCounter=selectedLabel=-1;
            if(changed)changed();update();return;
        }
        if(e->button()!=Qt::LeftButton)return;
        if(placingLabel && !labelText.isEmpty() && !hideOverlays) {
            if(doc->labels.size()>=80)return;
            doc->labels.append({labelText,q.x(),q.y()});
            placingLabel=false;labelText.clear();
            selectedCounter=selectedLabel=-1;
            if(labelPlaced)labelPlaced();
            if(changed)changed();update();return;
        }
        selectOverlay(q);
        if(selectedCounter>=0||selectedLabel>=0) {
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
        if(draggingOverlay && selectedCounter>=0 && selectedCounter<doc->counters.size()) {
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
        if(selectedLabel>=0) {
            bool ok=false;
            const QString edited=QInputDialog::getText(this,tr("HUD Text"),tr("Text:"),QLineEdit::Normal,
                doc->labels[selectedLabel].text,&ok);
            if(ok){doc->labels[selectedLabel].text=edited.left(60);if(changed)changed();update();}
        }
    }
    void dragEnterEvent(QDragEnterEvent *e) override {if(!hideOverlays && e->mimeData()->hasFormat(kMime)) e->acceptProposedAction();}
    void dragMoveEvent(QDragMoveEvent *e) override {if(!hideOverlays && e->mimeData()->hasFormat(kMime)) e->acceptProposedAction();}
    void dropEvent(QDropEvent *e) override {
        if(!doc || hideOverlays || !e->mimeData()->hasFormat(kMime) || doc->counters.size()>=32)return;
        const QJsonObject o=QJsonDocument::fromJson(e->mimeData()->data(kMime)).object();
        const QPoint q=pixelPoint(e->position().toPoint());
        if(q.x()<0||q.y()<0||q.x()>=doc->columns*doc->cw||q.y()>=doc->rows*doc->ch)return;
        doc->counters.append({o.value("kind").toInt(),q.x(),q.y(),o.value("iw").toInt(16),
            o.value("ih").toInt(16),o.value("name").toString(),o.value("source").toString()});
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
    const QVector<QRgb> hudPalette=textPaletteFor(root,doc.textPalette,atlas);
    const QVector<uchar> tileRemap=hudColourMap(atlas,hudPalette);
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
                pixels[(ry*doc.ch+iy)*w+rx*doc.cw+ix]=char(tileRemap[atlas.pixelIndex(px,py)]);
            }
        }
    }else {
        for(const Tile &tile:doc.tiles) if(tile.index>=0){if(error)*error="Missing HUD atlas PPB";return false;}
    }
    // Generate complete C in dependency order: headers, all static arrays,
    // text helper, then public draw routines. Keep game source user-owned.
    QString c=QStringLiteral("/* GENERATED by CoderGirl HUD Designer. Changes here are overwritten. */\n"
        "#include \"gamehud.h\"\n#include \"gameworlds.h\"\n#include \"apis.h\"\n#include <stdio.h>\n"
        "static const unsigned char hud_pixels[%1] __attribute__((aligned(32))) = {%2};\n")
        .arg(pixels.size()).arg(cArray(pixels));
    QString iconDraws;
    int i=0;
    for(const HudCounter &cnt:doc.counters) {
        const QImage icon=firstIcon(QDir(root).filePath(cnt.source),cnt.iw,cnt.ih);
        if(icon.isNull() || icon.format()!=QImage::Format_Indexed8) {
            if(error)*error=QStringLiteral("Missing HUD icon PPB: %1").arg(cnt.source);
            return false;
        }
        const QVector<uchar> iconRemap=hudColourMap(icon,hudPalette);
        QByteArray bytes;bytes.reserve(icon.width()*icon.height());
        for(int yy=0;yy<icon.height();++yy)for(int xx=0;xx<icon.width();++xx)
            bytes.append(char(iconRemap[icon.pixelIndex(xx,yy)]));
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
    c+=QStringLiteral("}\n"
        "void game_show_hud(int32_t x, int32_t y) {\n"
        "    /* (0,0) uses the designer's saved LCD position. */\n"
        "    if (x==0 && y==0) { x=%1; y=%2; }\n"
        "    game_show_hud_at(x,y);\n}\n").arg(doc.hudX).arg(doc.hudY);
    const QString header=QStringLiteral("/* GENERATED shared HUD API. */\n#ifndef CODERGIRL_GAMEHUD_H\n#define CODERGIRL_GAMEHUD_H\n#include <stdint.h>\n"
        "/* Screen coordinates. (0,0) uses the saved HUD Designer position. */\n"
        "void game_show_hud(int32_t x,int32_t y);\n"
        "/* Explicit screen position, including actual top-left (0,0). */\n"
        "void game_show_hud_at(int32_t x,int32_t y);\n#endif\n");
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
    QDialog dialog(parent);dialog.setWindowTitle(QObject::tr("Shared HUD Designer"));dialog.resize(1130,740);
    auto *outer=new QVBoxLayout(&dialog);
    auto *geometry=new QHBoxLayout;
    auto *columns=new QSpinBox(&dialog),*rows=new QSpinBox(&dialog),*cw=new QSpinBox(&dialog),*ch=new QSpinBox(&dialog);
    columns->setRange(1,60);rows->setRange(1,40);cw->setRange(1,64);ch->setRange(1,64);
    columns->setValue(doc.columns);rows->setValue(doc.rows);cw->setValue(doc.cw);ch->setValue(doc.ch);
    for(auto pair: {qMakePair(QObject::tr("Width (cells)"),columns),qMakePair(QObject::tr("Height (cells)"),rows),
                    qMakePair(QObject::tr("Cell W"),cw),qMakePair(QObject::tr("Cell H"),ch)}){
        geometry->addWidget(new QLabel(pair.first,&dialog));geometry->addWidget(pair.second);
    }
    // A single HUD palette governs background tiles, text AND icons. Pixels
    // imported from other PPBs are mapped into its foreground CLUT indices.
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
        auto *item=new QListWidgetItem(QIcon(QPixmap::fromImage(visible(p.icon)).scaled(28,28)),
            QStringLiteral("%1 (type %2)").arg(p.name).arg(p.kind),list);
        const QJsonObject data{{"kind",p.kind},{"name",p.name},{"source",p.source},{"iw",p.iw},{"ih",p.ih}};
        item->setData(Qt::UserRole,QJsonDocument(data).toJson(QJsonDocument::Compact));
    }
    sideLayout->addWidget(list,2);
    auto *kindNote=new QLabel(QObject::tr("Counters use Pickup Type IDs. Give different collectable TYPES different IDs; the same ID across worlds shares one total."),side);
    kindNote->setWordWrap(true);sideLayout->addWidget(kindNote);
    if(list->count()==0) {
        auto *note=new QLabel(QObject::tr("Not seeing anything in the list? Double-check your collectables' Show in HUD setting in each world, then Save Design."),side);
        note->setWordWrap(true);sideLayout->addWidget(note);
    }
    auto *right=new QWidget(mainSplit);auto *rightLayout=new QVBoxLayout(right);
    rightLayout->addWidget(new QLabel(QObject::tr("Drag collectables onto the HUD. Grab existing icons/text to move them; hold right mouse to erase tiles."),right));
    auto *hideOverlays=new QCheckBox(QObject::tr("Hide text and items (paint tiles underneath)"),right);
    rightLayout->addWidget(hideOverlays);
    HudCanvas *canvas=new HudCanvas(right);canvas->doc=&doc;canvas->root=projectRoot;
    auto *scroll=new HudZoomScroll(right);scroll->setWidgetResizable(false);scroll->setWidget(canvas);
    scroll->stepZoom=[canvas](int d){canvas->zoom=qBound(1,canvas->zoom+d,10);canvas->refresh();};
    rightLayout->addWidget(scroll,1);
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
            QImage image=visible(hudPreview(pickups[n].icon,canvas->textColors));
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
            QImage image=visible(hudPreview(pickups[n].icon,canvas->textColors));
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
        doc.hudX=qMin(doc.hudX,480-doc.columns*doc.cw);
        doc.hudY=qMin(doc.hudY,320-doc.rows*doc.ch);
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
    screenPreview->moved=[&](){posX->setValue(doc.hudX);posY->setValue(doc.hudY);};
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
        canvas->hideOverlays=b;canvas->selectedCounter=canvas->selectedLabel=-1;
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
    return dialog.exec()==QDialog::Accepted;
}


bool regenerateGameHud(const QString &projectRoot,QString *error) {
    QFile f(QDir(projectRoot).filePath(QStringLiteral("gamehud.sbhud")));
    if(!f.exists()) return true; // Existing projects without a HUD remain unchanged.
    if(!f.open(QIODevice::ReadOnly)) {if(error)*error=QStringLiteral("Cannot read shared HUD layout");return false;}
    HudDoc d;
    if(!d.load(QJsonDocument::fromJson(f.readAll()).object())) {
        if(error)*error=QStringLiteral("Invalid shared HUD layout");return false;
    }
    return exportHud(projectRoot,d,error);
}
