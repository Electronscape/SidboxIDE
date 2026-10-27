#include "gamequestjournaleditor.h"
#include "gamepalette.h"
#include "gamepalettepicker.h"
#include "guidesigner_detail.h"
#include "ppbcodec.h"
#include <QCheckBox>
#include <QComboBox>
#include <QIcon>
#include <QPixmap>
#include <QDialog>
#include <QDialogButtonBox>
#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QFileInfo>
#include <QFormLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QImage>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QPushButton>
#include <QSaveFile>
#include <QScrollArea>
#include <QSpinBox>
#include <QVBoxLayout>
#include <algorithm>
#include <array>

namespace {
QString styleFile(const QString &root)
{ return QDir(root).filePath(QStringLiteral(".codergirl/quest-journal.json")); }
struct Style {
    int margin=6, split=42, bg=2, border=15, text=15, highlight=14;
    int titleX=11,titleY=8,titleScaleX=1,titleScaleY=2,listLeft=10;
    bool outline=false;
    int outlineColour=0;
    QString atlas;
    int tile=8;
    std::array<int,9> cells{{0,1,2,3,4,5,6,7,8}};
    std::array<int,9> flips{{0,0,0,0,0,0,0,0,0}};
};
struct HudDock {QString mode=QStringLiteral("overlay");int pixels=0;};
HudDock hudDock(const QString &root) {
    QFile file(QDir(root).filePath(QStringLiteral("gamehud.sbhud")));
    if(!file.open(QIODevice::ReadOnly))return {};
    const QJsonObject j=QJsonDocument::fromJson(file.readAll()).object();
    if(j.value(QStringLiteral("format")).toString()!=QStringLiteral("SIDBOX-SHARED-HUD"))return {};
    const QString dock=j.value(QStringLiteral("dock")).toString();
    if(dock!=QStringLiteral("top") && dock!=QStringLiteral("bottom"))return {};
    const int size=j.value(QStringLiteral("rows")).toInt()*j.value(QStringLiteral("cellHeight")).toInt();
    if(size<1||size>=320)return {};
    return {dock,size};
}
QStringList projectAssets(const QString &root,const QStringList &filters) {
    QStringList paths;
    QDirIterator scan(root,filters,QDir::Files,QDirIterator::Subdirectories);
    while(scan.hasNext()){
        const QString rel=QDir(root).relativeFilePath(scan.next());
        if(rel.startsWith(QStringLiteral("build")) || rel.startsWith(QStringLiteral(".git/")) ||
           rel.contains(QStringLiteral("/build")) || rel.startsWith(QStringLiteral(".codergirl/")))continue;
        paths.push_back(rel);
    }
    paths.removeDuplicates(); paths.sort(Qt::CaseInsensitive);return paths;
}
QImage atlasImage(const QString &root,const QString &path,const QVector<QRgb> &palette) {
    if(path.isEmpty())return {};
    SidboxPpb::Picture picture;QString err;
    if(!SidboxPpb::read(QDir(root).filePath(path),&picture,&err))return {};
    QImage image=picture.indexed;
    if(image.format()==QImage::Format_Indexed8 && palette.size()==256){
        QVector<QRgb> colours=palette;
        for(int i=1;i<256;++i)colours[i]|=0xff000000u;
        image.setColorTable(colours);
    }
    return image;
}
QColor previewColour(const QVector<QRgb> &palette,int idx) {
    if(idx>=0 && idx<palette.size())return QColor::fromRgba(palette[idx]);
    const QColor base[16]={Qt::black,QColor(0,0,128),QColor(24,30,55),QColor(22,94,128),
        QColor(90,12,34),QColor(110,45,85),QColor(60,80,28),QColor(160,160,160),
        QColor(65,65,65),Qt::blue,Qt::green,Qt::cyan,Qt::red,Qt::magenta,Qt::yellow,Qt::white};
    return base[std::clamp(idx,0,15)];
}
QImage cellImage(const QImage &atlas,int tile,int index,int flips) {
    if(atlas.isNull()||tile<1||atlas.width()<tile||atlas.height()<tile)return {};
    const int columns=atlas.width()/tile, rows=atlas.height()/tile;
    if(index<0||index>=columns*rows)return {};
    QImage cell=atlas.copy((index%columns)*tile,(index/columns)*tile,tile,tile);
    Qt::Orientations o;
    if(flips&4)o|=Qt::Horizontal;
    if(flips&8)o|=Qt::Vertical;
    return o==Qt::Orientations{}?cell:cell.flipped(o);
}
class AtlasGrid final : public QWidget {
public:
    QImage source;int tile=8,selected=0,zoom=3;
    explicit AtlasGrid(QWidget *parent=nullptr):QWidget(parent){}
    void updateAtlas(const QImage &image,int size,int chosen){
        source=image;tile=size;selected=chosen;
        setFixedSize((source.width()/tile)*tile*zoom,(source.height()/tile)*tile*zoom);
        update();
    }
protected:
    void paintEvent(QPaintEvent *) override {
        QPainter p(this);p.setRenderHint(QPainter::SmoothPixmapTransform,false);
        p.drawImage(rect(),source);
        const int cols=source.width()/tile;
        if(cols && selected>=0){p.setPen(QPen(Qt::yellow,2));p.drawRect((selected%cols)*tile*zoom,(selected/cols)*tile*zoom,tile*zoom-1,tile*zoom-1);}
    }
    void mousePressEvent(QMouseEvent *e) override {
        if(e->button()!=Qt::LeftButton)return;
        const int cols=source.width()/tile;
        const int col=int(e->position().x())/(tile*zoom),row=int(e->position().y())/(tile*zoom);
        if(cols && col>=0&&col<cols&&row>=0&&row<source.height()/tile){selected=row*cols+col;update();}
    }
};
int chooseCell(QWidget *parent,const QImage &atlas,int tile,int current){
    if(atlas.isNull()||tile<=0||atlas.width()<tile||atlas.height()<tile)return -1;
    QDialog dialog(parent); dialog.setWindowTitle(QObject::tr("Select Journal Frame Tile"));dialog.resize(780,590);
    auto *layout=new QVBoxLayout(&dialog);
    layout->addWidget(new QLabel(QObject::tr("Left-click an atlas cell. Yellow marks the selected cell."),&dialog));
    auto *scroll=new QScrollArea(&dialog);scroll->setWidgetResizable(false);
    auto *grid=new AtlasGrid(scroll);grid->updateAtlas(atlas,tile,current);
    scroll->setWidget(grid);layout->addWidget(scroll,1);
    auto *buttons=new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel,&dialog);
    layout->addWidget(buttons);
    QObject::connect(buttons,&QDialogButtonBox::accepted,&dialog,&QDialog::accept);
    QObject::connect(buttons,&QDialogButtonBox::rejected,&dialog,&QDialog::reject);
    return dialog.exec()==QDialog::Accepted?grid->selected:-1;
}
class JournalPreview final : public QWidget {
public:
    Style style;QImage atlas;QVector<QRgb> palette;HudDock dock;
    explicit JournalPreview(QWidget *parent=nullptr):QWidget(parent){setMinimumSize(480,320);}
protected:
    void paintEvent(QPaintEvent *) override {
        QPainter p(this);p.setRenderHint(QPainter::Antialiasing,false);
        p.fillRect(rect(),QColor(18,23,30));
        const qreal scale=std::min(width()/480.0,height()/320.0);
        p.translate((width()-480.0*scale)/2,(height()-320.0*scale)/2);p.scale(scale,scale);
        p.fillRect(0,0,480,320,QColor(33,46,51));
        int top=dock.mode==QStringLiteral("top")?dock.pixels:0;
        int available=320-dock.pixels;
        if(dock.mode==QStringLiteral("overlay") || available<208+2*style.margin)
            {top=0;available=320;}
        if(dock.mode==QStringLiteral("top"))p.fillRect(0,0,480,dock.pixels,QColor(62,50,72));
        if(dock.mode==QStringLiteral("bottom"))p.fillRect(0,320-dock.pixels,480,dock.pixels,QColor(62,50,72));
        const int x=style.margin,y=top+style.margin,w=480-2*x,h=available-2*style.margin;
        const int split=x+w*style.split/100;
        const int inset=atlas.isNull()?8:style.tile+8;
        const int listX=x+std::max(inset,style.listLeft);
        const int heading=std::max(34,style.titleY+8*style.titleScaleY+10);
        const int rowsTop=y+heading+32;
        /* Mirror the runtime's 8x16 footer and atlas-safe padding. */
        const int footerY=y+h-inset-18;
        const int footerSeparatorY=footerY-8;
        const int objectiveY=footerSeparatorY-55;
        p.fillRect(x,y,w,h,previewColour(palette,style.bg));
        if(!atlas.isNull()&&style.tile>0){
            // Same nine-cell tiled layout as ga_frame_skin(), including bottom/right edges.
            for(int yy=0;yy<h;yy+=style.tile)for(int xx=0;xx<w;xx+=style.tile){
                const int part=(yy==0?0:yy+style.tile>=h?2:1)*3+
                               (xx==0?0:xx+style.tile>=w?2:1);
                const QImage tile=cellImage(atlas,style.tile,style.cells[part],style.flips[part]);
                if(!tile.isNull())p.drawImage(QRect(x+xx,y+yy,std::min(style.tile,w-xx),std::min(style.tile,h-yy)),tile);
            }
        }
        if(atlas.isNull()){p.setPen(previewColour(palette,style.border));p.drawRect(x,y,w-1,h-1);}
        p.setPen(previewColour(palette,style.border));
        p.drawLine(x+inset,y+heading,x+w-inset-1,y+heading);
        if(footerSeparatorY>y+heading+4)
            p.drawLine(split,y+heading+4,split,footerSeparatorY);
        // Use the same canonical raster SIDBOX glyphs as the Title Editor.
        // gfx_drawtextf(x,y,text,sx,sy) draws native 8x8 glyphs, not Qt fonts.
        auto drawInk=[&](int tx,int ty,const QString &str,int sx=1,int sy=2){
            if(str.isEmpty())return;
            const int tw=str.toLatin1().size()*8;
            if(tw<1)return;
            QImage doubled(tw,16,QImage::Format_ARGB32_Premultiplied);
            doubled.fill(Qt::transparent);
            {QPainter gp(&doubled);GuiDesignerDetail::drawCoderGirlText(gp,0,0,str,Qt::white);}
            const QImage native=doubled.scaled(tw,8,Qt::IgnoreAspectRatio,Qt::FastTransformation);
            const QImage glyph=native.scaled(tw*sx,8*sy,Qt::IgnoreAspectRatio,Qt::FastTransformation);
            auto tint=[&](const QColor &colour){
                QImage result=glyph;
                QPainter fill(&result);fill.setCompositionMode(QPainter::CompositionMode_SourceIn);
                fill.fillRect(result.rect(),colour);return result;
            };
            p.save();p.setClipRect(x+inset,y+inset,w-2*inset,h-2*inset);
            if(style.outline){const QImage edge=tint(previewColour(palette,style.outlineColour));
                p.drawImage(tx-1,ty,edge);p.drawImage(tx+1,ty,edge);
                p.drawImage(tx,ty-1,edge);p.drawImage(tx,ty+1,edge);}
            p.drawImage(tx,ty,tint(previewColour(palette,style.text)));
            p.restore();
        };
        const int tx=x+std::max(inset,style.titleX);
        const int maxChars=std::max(0,(x+w-inset-tx)/(8*style.titleScaleX));
        drawInk(tx,y+style.titleY,QStringLiteral("QUEST JOURNAL").left(maxChars),
                style.titleScaleX,style.titleScaleY);
        drawInk(listX,y+heading+8,QStringLiteral("QUESTS"));
        const int listCols=std::max(1,(split-listX-22)/8);
        for(int i=0;i<4 && rowsTop+i*24+17<footerSeparatorY-6;++i){
            const int yy=rowsTop+i*24;
            if(!i){p.setPen(previewColour(palette,style.highlight));p.drawRect(listX-3,yy-3,std::max(8,split-listX-4),23);}
            const QString name=i==0?QStringLiteral("Forest Mystery"):
                i==1?QStringLiteral("Old Cabin"):i==2?QStringLiteral("Big Steve"):QStringLiteral("Lost Map");
            drawInk(listX,yy,(i==0?QStringLiteral("> "):QStringLiteral("- "))+name.left(listCols));
        }
        const int right=split+inset;
        drawInk(right,y+heading+8,QStringLiteral("Forest Mystery"));
        drawInk(right,y+heading+30,QStringLiteral("ACTIVE   TRACKED"));
        if(y+heading+70<objectiveY){
            drawInk(right,y+heading+52,QStringLiteral("DESCRIPTION"));
            if(y+heading+85<objectiveY)drawInk(right,y+heading+69,QStringLiteral("Who is the man"));
        }
        drawInk(right,objectiveY,QStringLiteral("CURRENT OBJECTIVE"));
        drawInk(right,objectiveY+18,QStringLiteral("Enter forest"));
        p.setPen(previewColour(palette,style.border));
        p.drawLine(x+inset,footerSeparatorY,x+w-inset-1,footerSeparatorY);
        drawInk(x+inset,footerY,QStringLiteral("UP/DOWN SELECT"));
        drawInk(right,footerY,QStringLiteral("FIRE1 TRACK  FIRE2 BACK"));
        if(dock.pixels){p.setPen(Qt::white);p.drawText(8,dock.mode==QStringLiteral("top")?22:306,QStringLiteral("HUD (automatic)"));}
    }
};
class JournalDesigner final : public QDialog {
public:
    explicit JournalDesigner(const QString &root,QWidget *parent):QDialog(parent),projectRoot(root),path(styleFile(root)) {
        setWindowTitle(tr("Quest Journal Designer | Project-wide"));resize(1200,720);
        const HudDock layoutDock=hudDock(root);
        auto *layout=new QHBoxLayout(this);
        auto *left=new QWidget(this);auto *controls=new QVBoxLayout(left);
        auto *layoutGroup=new QGroupBox(tr("Journal layout"),left);auto *form=new QFormLayout(layoutGroup);
        margin=new QSpinBox(layoutGroup);margin->setRange(2,20);margin->setValue(6);
        split=new QSpinBox(layoutGroup);split->setRange(30,60);split->setValue(42);
        form->addRow(tr("Screen margin (px)"),margin);form->addRow(tr("Quest list width (%)"),split);
        listLeft=new QSpinBox(layoutGroup);listLeft->setRange(8,80);listLeft->setValue(10);
        form->addRow(tr("Quest list left (px from panel)"),listLeft);
        titleX=new QSpinBox(layoutGroup);titleX->setRange(8,240);titleX->setValue(11);
        titleY=new QSpinBox(layoutGroup);titleY->setRange(8,48);titleY->setValue(8);
        form->addRow(tr("Journal heading X (px)"),titleX);
        form->addRow(tr("Journal heading Y (px)"),titleY);
        auto *fontRow=new QWidget(layoutGroup);auto *fontLayout=new QHBoxLayout(fontRow);
        fontLayout->setContentsMargins(0,0,0,0);
        titleFontX=new QComboBox(fontRow);titleFontY=new QComboBox(fontRow);
        for(auto *box:{titleFontX,titleFontY}){
            for(int size:{1,2,4,8})box->addItem(tr("%1× native glyph").arg(size),size);
        }
        titleFontY->setCurrentIndex(titleFontY->findData(2));
        fontLayout->addWidget(new QLabel(tr("X"),fontRow));fontLayout->addWidget(titleFontX);
        fontLayout->addWidget(new QLabel(tr("Y"),fontRow));fontLayout->addWidget(titleFontY);
        form->addRow(tr("Heading glyph size"),fontRow);
        controls->addWidget(layoutGroup);
        auto *colours=new QGroupBox(tr("Foreground palette colours"),left);auto *colourForm=new QFormLayout(colours);
        paletteChoice=new QComboBox(colours);
        paletteChoice->addItem(tr("Use HUD palette / project palette"),QString());
        for(const QString &name:projectAssets(root,{QStringLiteral("*.pal"),QStringLiteral("*.PAL"),QStringLiteral("*.act"),QStringLiteral("*.ACT"),QStringLiteral("*.ppb"),QStringLiteral("*.PPB")}))
            paletteChoice->addItem(name,name);
        colourForm->addRow(tr("Preview palette"),paletteChoice);
        const QStringList labels={tr("Background"),tr("Border / dividers"),tr("Text"),tr("Selected quest"),tr("Text outline")};
        const int defaults[5]={2,15,15,14,0};
        for(int i=0;i<5;++i){buttons[i]=new QPushButton(colours);indices[i]=defaults[i];colourForm->addRow(labels[i],buttons[i]);}
        outlineEnabled=new QCheckBox(tr("Enable journal text outline"),colours);
        colourForm->addRow(outlineEnabled);
        controls->addWidget(colours);
        auto *skinGroup=new QGroupBox(tr("Journal frame atlas (independent of dialogues)"),left);
        auto *skinLayout=new QVBoxLayout(skinGroup);
        atlasChoice=new QComboBox(skinGroup);atlasChoice->addItem(tr("No atlas (solid background)"),QString());
        for(const QString &name:projectAssets(root,{QStringLiteral("*.ppb"),QStringLiteral("*.PPB")}))atlasChoice->addItem(name,name);
        skinLayout->addWidget(atlasChoice);
        tileSize=new QSpinBox(skinGroup);tileSize->setRange(4,32);tileSize->setValue(8);
        auto *tileRow=new QFormLayout;tileRow->addRow(tr("Atlas tile size (px)"),tileSize);skinLayout->addLayout(tileRow);
        auto *grid=new QGridLayout;
        for(int i=0;i<9;++i){
            auto *cell=new QWidget(skinGroup);auto *cv=new QVBoxLayout(cell);cv->setContentsMargins(1,1,1,1);
            tiles[i]=new QPushButton(cell);tiles[i]->setMinimumWidth(90);cv->addWidget(tiles[i]);
            flipX[i]=new QCheckBox(tr("Flip X"),cell);flipY[i]=new QCheckBox(tr("Flip Y"),cell);
            cv->addWidget(flipX[i]);cv->addWidget(flipY[i]);grid->addWidget(cell,i/3,i%3);
            chosen[i]=i;flips[i]=0;
        }
        skinLayout->addLayout(grid);controls->addWidget(skinGroup);
        controls->addStretch();
        auto *leftScroll=new QScrollArea(this);leftScroll->setWidgetResizable(true);leftScroll->setWidget(left);
        leftScroll->setMinimumWidth(405);layout->addWidget(leftScroll,0);
        auto *right=new QVBoxLayout;preview=new JournalPreview(this);preview->dock=layoutDock;
        right->addWidget(preview,1);
        auto *hudNote=new QLabel(layoutDock.pixels?
            tr("HUD layout read automatically from gamehud.sbhud: %1 (%2 px). No independent HUD selector.").arg(layoutDock.mode).arg(layoutDock.pixels):
            tr("HUD layout read automatically from gamehud.sbhud: no dock."),this);
        hudNote->setWordWrap(true);right->addWidget(hudNote);
        right->addWidget(new QLabel(tr("Touch opens only; UP/DOWN select, FIRE1 track, FIRE2 close."),this));
        auto *saveButtons=new QDialogButtonBox(QDialogButtonBox::Save|QDialogButtonBox::Cancel,this);
        right->addWidget(saveButtons);layout->addLayout(right,1);
        QFile file(path);
        if(file.exists()){
            if(!file.open(QIODevice::ReadOnly)){loadError=tr("Cannot read %1").arg(path);return;}
            const QJsonDocument doc=QJsonDocument::fromJson(file.readAll());
            if(!doc.isObject()||doc.object().value(QStringLiteral("version")).toInt()!=1){loadError=tr("Invalid Quest Journal design file: %1").arg(path);return;}
            const QJsonObject s=doc.object();
            margin->setValue(std::clamp(s.value(QStringLiteral("margin")).toInt(6),2,20));
            split->setValue(std::clamp(s.value(QStringLiteral("split")).toInt(42),30,60));
            listLeft->setValue(std::clamp(s.value(QStringLiteral("listLeft")).toInt(10),8,80));
            titleX->setValue(std::clamp(s.value(QStringLiteral("titleX")).toInt(11),8,240));
            titleY->setValue(std::clamp(s.value(QStringLiteral("titleY")).toInt(8),8,48));
            titleFontX->setCurrentIndex(std::max(0,titleFontX->findData(s.value(QStringLiteral("titleFontX")).toInt(1))));
            titleFontY->setCurrentIndex(std::max(0,titleFontY->findData(s.value(QStringLiteral("titleFontY")).toInt(2))));
            outlineEnabled->setChecked(s.value(QStringLiteral("outlineEnabled")).toBool(false));
            const char *keys[]={"background","border","text","selection","outlineColour"};
            for(int i=0;i<5;++i)indices[i]=std::clamp(s.value(QLatin1String(keys[i])).toInt(defaults[i]),0,255);
            paletteChoice->setCurrentIndex(std::max(0,paletteChoice->findData(s.value(QStringLiteral("palette")).toString())));
            atlasChoice->setCurrentIndex(std::max(0,atlasChoice->findData(s.value(QStringLiteral("atlas")).toString())));
            tileSize->setValue(std::clamp(s.value(QStringLiteral("tileSize")).toInt(8),4,32));
            const QJsonArray cells=s.value(QStringLiteral("cells")).toArray(),savedFlips=s.value(QStringLiteral("flips")).toArray();
            for(int i=0;i<9;++i){chosen[i]=std::clamp(i<cells.size()?cells[i].toInt(i):i,0,65535);
                flips[i]=i<savedFlips.size()?(savedFlips[i].toInt()&12):0;
                flipX[i]->setChecked((flips[i]&4)!=0);flipY[i]->setChecked((flips[i]&8)!=0);}
        }
        auto redraw=[this]{
            const QString explicitPalette=paletteChoice->currentData().toString();
            QString source=explicitPalette;
            if(source.isEmpty()){
                QFile hud(QDir(projectRoot).filePath(QStringLiteral("gamehud.sbhud")));
                if(hud.open(QIODevice::ReadOnly))source=QJsonDocument::fromJson(hud.readAll()).object().value(QStringLiteral("textPalette")).toString();
            }
            QVector<QRgb> palette;
            if(!source.isEmpty())palette=SidboxGamePalette::readPalette(QDir(projectRoot).filePath(source),false);
            if(palette.size()!=256){
                const QString fallback=atlasChoice->currentData().toString();
                if(!fallback.isEmpty())palette=SidboxGamePalette::readPalette(QDir(projectRoot).filePath(fallback),false);
            }
            if(palette.size()!=256){palette=QVector<QRgb>(256,qRgb(0,0,0));
                for(int i=0;i<16;++i)palette[i]=previewColour({},i).rgb();}
            preview->palette=palette;
            preview->atlas=atlasImage(projectRoot,atlasChoice->currentData().toString(),palette);
            preview->style.margin=margin->value();preview->style.split=split->value();
            preview->style.listLeft=listLeft->value();
            preview->style.titleX=titleX->value();preview->style.titleY=titleY->value();
            preview->style.titleScaleX=titleFontX->currentData().toInt();
            preview->style.titleScaleY=titleFontY->currentData().toInt();
            preview->style.bg=indices[0];preview->style.border=indices[1];
            preview->style.text=indices[2];preview->style.highlight=indices[3];
            preview->style.outline=outlineEnabled->isChecked();preview->style.outlineColour=indices[4];
            buttons[4]->setEnabled(preview->style.outline);
            preview->style.tile=tileSize->value();
            for(int i=0;i<9;++i){
                preview->style.cells[i]=chosen[i];
                flips[i]=(flipX[i]->isChecked()?4:0)|(flipY[i]->isChecked()?8:0);
                preview->style.flips[i]=flips[i];
                tiles[i]->setText(tr("Tile %1").arg(chosen[i]));
                const QImage im=cellImage(preview->atlas,tileSize->value(),chosen[i],flips[i]);
                tiles[i]->setIcon(im.isNull()?QIcon():QIcon(QPixmap::fromImage(im.scaled(34,34,Qt::KeepAspectRatio,Qt::FastTransformation))));
                tiles[i]->setIconSize(QSize(34,34));
                tiles[i]->setEnabled(!preview->atlas.isNull());
            }
            for(int i=0;i<5;++i){
                buttons[i]->setText(tr("Index %1  •  Pick colour...").arg(indices[i]));
                QPixmap px(22,22);px.fill(previewColour(palette,indices[i]));
                buttons[i]->setIcon(QIcon(px));buttons[i]->setIconSize(QSize(22,22));
            }
            preview->update();
        };
        for(auto *spin:{margin,split,tileSize,listLeft,titleX,titleY})
            connect(spin,QOverload<int>::of(&QSpinBox::valueChanged),this,[redraw](int){redraw();});
        for(auto *box:{titleFontX,titleFontY})
            connect(box,QOverload<int>::of(&QComboBox::currentIndexChanged),this,[redraw](int){redraw();});
        connect(outlineEnabled,&QCheckBox::toggled,this,[redraw](bool){redraw();});
        connect(atlasChoice,QOverload<int>::of(&QComboBox::currentIndexChanged),this,[redraw](int){redraw();});
        connect(paletteChoice,QOverload<int>::of(&QComboBox::currentIndexChanged),this,[redraw](int){redraw();});
        for(int i=0;i<9;++i){
            connect(flipX[i],&QCheckBox::toggled,this,[redraw](bool){redraw();});
            connect(flipY[i],&QCheckBox::toggled,this,[redraw](bool){redraw();});
            connect(tiles[i],&QPushButton::clicked,this,[this,i,redraw]{
                const int next=chooseCell(this,preview->atlas,tileSize->value(),chosen[i]);
                if(next>=0){chosen[i]=next;redraw();}
            });
        }
        for(int i=0;i<5;++i){
            connect(buttons[i],&QPushButton::clicked,this,[this,i,redraw]{
                const int index=SidboxPalettePicker::chooseIndex(this,preview->palette,indices[i],tr("Journal Palette Colour"),
                    tr("Select an existing SIDBOX 256-colour CLUT index. The palette itself is not modified."),true,true);
                if(index>=0){indices[i]=index;redraw();}
            });
        }
        connect(saveButtons,&QDialogButtonBox::rejected,this,&QDialog::reject);
        connect(saveButtons,&QDialogButtonBox::accepted,this,[this]{
            QJsonArray cells,flipFlags;
            for(int i=0;i<9;++i){cells.append(chosen[i]);flipFlags.append(flips[i]);}
            QJsonObject data{{"version",1},{"margin",margin->value()},{"split",split->value()},
                 {"listLeft",listLeft->value()},{"titleX",titleX->value()},{"titleY",titleY->value()},
                 {"titleFontX",titleFontX->currentData().toInt()},{"titleFontY",titleFontY->currentData().toInt()},
                 {"outlineEnabled",outlineEnabled->isChecked()},{"outlineColour",indices[4]},
                 {"background",indices[0]},{"border",indices[1]},{"text",indices[2]},
                 {"selection",indices[3]},{"palette",paletteChoice->currentData().toString()},
                 {"atlas",atlasChoice->currentData().toString()},{"tileSize",tileSize->value()},
                 {"cells",cells},{"flips",flipFlags}};
            if(!QDir().mkpath(QFileInfo(path).absolutePath())){saveError=tr("Cannot create design directory");QMessageBox::warning(this,tr("Quest Journal Designer"),saveError);return;}
            QSaveFile out(path);const QByteArray json=QJsonDocument(data).toJson(QJsonDocument::Indented);
            if(!out.open(QIODevice::WriteOnly)||out.write(json)!=json.size()||!out.commit()){
                out.cancelWriting();saveError=tr("Cannot save %1").arg(path);QMessageBox::warning(this,tr("Quest Journal Designer"),saveError);return;
            }
            accept();
        });
        redraw();
    }
    QString loadError,saveError;
private:
    QString projectRoot,path;
    JournalPreview *preview=nullptr;
    QSpinBox *margin=nullptr,*split=nullptr,*tileSize=nullptr,*listLeft=nullptr,*titleX=nullptr,*titleY=nullptr;
    QComboBox *paletteChoice=nullptr,*atlasChoice=nullptr,*titleFontX=nullptr,*titleFontY=nullptr;
    QCheckBox *outlineEnabled=nullptr;
    QPushButton *buttons[5]{},*tiles[9]{};
    QCheckBox *flipX[9]{},*flipY[9]{};
    int indices[5]{},chosen[9]{},flips[9]{};
};
}
bool editGameQuestJournal(QWidget *parent,const QString &root,QString *error)
{
    JournalDesigner dialog(root,parent);
    if(!dialog.loadError.isEmpty()){if(error)*error=dialog.loadError;return false;}
    dialog.showMaximized();const bool saved=dialog.exec()==QDialog::Accepted;
    if(!saved && error)*error=dialog.saveError;
    return saved;
}
