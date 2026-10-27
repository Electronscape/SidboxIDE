#include "gamequestjournaleditor.h"
#include "gamequesteditor.h"
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
#include <QSignalBlocker>
#include <QRegularExpression>
#include <QSaveFile>
#include <QScrollArea>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QVector>
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
    std::array<int,5> iconCells{{65535,65535,65535,65535,65535}};
    std::array<int,5> iconFlips{{0,0,0,0,0}};
    std::array<bool,5> icon2x2{{false,false,false,false,false}};
    std::array<std::array<int,4>,5> iconParts{{
        {{65535,65535,65535,65535}},{{65535,65535,65535,65535}},
        {{65535,65535,65535,65535}},{{65535,65535,65535,65535}},
        {{65535,65535,65535,65535}}
    }};
};
struct PreviewQuest {
    QString id,title,description,objective;
    bool initiallyHidden=false;
};
QVector<PreviewQuest> projectQuests(const QString &root,QString *error) {
    QVector<PreviewQuest> result;
    const QString fileName=QDir(root).filePath(QStringLiteral(".codergirl/quests.json"));
    QFile file(fileName);
    if(!file.exists())return result;
    if(!file.open(QIODevice::ReadOnly)){
        if(error)*error=QObject::tr("Cannot read %1").arg(fileName);
        return result;
    }
    QJsonParseError parse;
    const QJsonDocument doc=QJsonDocument::fromJson(file.readAll(),&parse);
    if(parse.error!=QJsonParseError::NoError || !doc.isObject() ||
       doc.object().value(QStringLiteral("version")).toInt()!=1 ||
       !doc.object().value(QStringLiteral("quests")).isArray()) {
        if(error)*error=QObject::tr("Invalid quest definitions: %1").arg(fileName);
        return result;
    }
    for(const QJsonValue &value:doc.object().value(QStringLiteral("quests")).toArray()){
        if(!value.isObject())continue;
        const QJsonObject quest=value.toObject();
        PreviewQuest item;
        item.id=quest.value(QStringLiteral("id")).toString();
        item.title=quest.value(QStringLiteral("title")).toString();
        item.description=quest.value(QStringLiteral("description")).toString();
        item.initiallyHidden=quest.value(QStringLiteral("initiallyHidden")).toBool(false);
        const QJsonArray objectives=quest.value(QStringLiteral("objectives")).toArray();
        if(!objectives.isEmpty())
            item.objective=objectives.at(0).toObject().value(QStringLiteral("title")).toString();
        if(!item.id.isEmpty() && !item.title.isEmpty())result.append(item);
    }
    return result;
}
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
    if(atlas.isNull()||tile<1||atlas.width()<tile||atlas.height()<tile||index==65535)return {};
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
        source=image;tile=size;selected=chosen<0?0:chosen;
        if(source.isNull()||tile<1){setFixedSize(32,32);update();return;}
        setFixedSize((source.width()/tile)*tile*zoom,(source.height()/tile)*tile*zoom);
        update();
    }
protected:
    void paintEvent(QPaintEvent *) override {
        QPainter p(this);p.setRenderHint(QPainter::SmoothPixmapTransform,false);
        p.fillRect(rect(),QColor(20,20,20));
        if(source.isNull()||tile<1)return;
        p.drawImage(rect(),source);
        const int cols=source.width()/tile;
        if(cols && selected>=0){p.setPen(QPen(Qt::yellow,2));p.drawRect((selected%cols)*tile*zoom,(selected/cols)*tile*zoom,tile*zoom-1,tile*zoom-1);}
    }
    void mousePressEvent(QMouseEvent *e) override {
        if(source.isNull()||tile<1||e->button()!=Qt::LeftButton)return;
        const int cols=source.width()/tile;
        const int col=int(e->position().x())/(tile*zoom),row=int(e->position().y())/(tile*zoom);
        if(cols && col>=0&&col<cols&&row>=0&&row<source.height()/tile){selected=row*cols+col;update();}
    }
};
int chooseCell(QWidget *parent,const QImage &atlas,int tile,int current){
    if(atlas.isNull()||tile<=0||atlas.width()<tile||atlas.height()<tile)return -1;
    QDialog dialog(parent); dialog.setWindowTitle(QObject::tr("Select Journal Tile"));dialog.resize(780,590);
    auto *layout=new QVBoxLayout(&dialog);
    layout->addWidget(new QLabel(QObject::tr("Left-click an atlas cell. Yellow marks the selected cell."),&dialog));
    auto *scroll=new QScrollArea(&dialog);scroll->setWidgetResizable(false);
    auto *grid=new AtlasGrid(scroll);grid->updateAtlas(atlas,tile,current>=0?current:0);
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
    QVector<PreviewQuest> quests;int selectedQuest=0,descriptionScroll=0;
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
        const int headerBottom=std::max(34,style.titleY+8*style.titleScaleY+10);
        const int listX=x+std::max(inset,style.listLeft);
        const int footerY=y+h-inset-18;
        const int footerSeparatorY=footerY-8;
        const int objectiveTitleY=footerSeparatorY-38;
        const int objectiveTextY=footerSeparatorY-20;
        const int descY=y+headerBottom+8;
        const int rowH=16+(style.outline?4:0);
        /* Match ga_quest_description_visible_rows() in the game runtime:
         * leave one full glyph plus outline and an 8px objective gap. */
        const int descFree=objectiveTitleY-8-descY-(16+(style.outline?2:0));
        const int descLines=descFree<0?0:1+descFree/rowH;
        const int rowsTop=y+headerBottom+34;
        const int right=split+inset;
        const int rightLimit=x+w-inset;
        auto drawInk=[&](int tx,int ty,const QString &str,int sx=1,int sy=2,bool alignRight=false){
            if(str.isEmpty())return;
            const QByteArray latin=str.toLatin1();
            const int tw=latin.size()*8;
            if(tw<1)return;
            QImage doubled(tw,16,QImage::Format_ARGB32_Premultiplied);doubled.fill(Qt::transparent);
            {QPainter gp(&doubled);GuiDesignerDetail::drawCoderGirlText(gp,0,0,str,Qt::white);}
            const QImage native=doubled.scaled(tw,8,Qt::IgnoreAspectRatio,Qt::FastTransformation);
            const QImage glyph=native.scaled(tw*sx,8*sy,Qt::IgnoreAspectRatio,Qt::FastTransformation);
            auto tint=[&](const QColor &colour){QImage result=glyph;QPainter fill(&result);fill.setCompositionMode(QPainter::CompositionMode_SourceIn);fill.fillRect(result.rect(),colour);return result;};
            const int drawX=alignRight?tx-glyph.width():tx;
            if(style.outline){
                const QImage outline=tint(previewColour(palette,style.outlineColour));
                p.drawImage(drawX-1,ty,outline);p.drawImage(drawX+1,ty,outline);
                p.drawImage(drawX,ty-1,outline);p.drawImage(drawX,ty+1,outline);
            }
            p.drawImage(drawX,ty,tint(previewColour(palette,style.text)));
        };
        auto drawIcon=[&](int slot,int px,int py){
            if(slot<0||slot>=5)return false;
            if(style.icon2x2[slot]){
                if(style.tile!=8)return false;
                QImage composite(16,16,QImage::Format_ARGB32_Premultiplied);
                composite.fill(Qt::transparent);
                bool hasImage=false;
                {
                    QPainter cp(&composite);cp.setRenderHint(QPainter::SmoothPixmapTransform,false);
                    for(int part=0;part<4;++part){
                        const QImage im=cellImage(atlas,8,style.iconParts[slot][part],0);
                        if(!im.isNull()){
                            cp.drawImage(QPoint((part&1)*8,(part>>1)*8),im);
                            hasImage=true;
                        }
                    }
                }
                if(!hasImage)return false;
                Qt::Orientations o;
                if(style.iconFlips[slot]&4)o|=Qt::Horizontal;
                if(style.iconFlips[slot]&8)o|=Qt::Vertical;
                if(o!=Qt::Orientations{})composite=composite.flipped(o);
                p.drawImage(QPoint(px,py),composite);return true;
            }
            const QImage im=cellImage(atlas,style.tile,style.iconCells[slot],style.iconFlips[slot]);
            if(im.isNull())return false;
            p.drawImage(QPoint(px,py),im); /* Native dimensions, no BOB scaling. */
            return true;
        };
        /* Same word-boundary and explicit-newline behaviour as the native
         * ga_wrapped_scaled_skip() renderer. No desktop font reflow. */
        auto sampleWrap=[&](const QString &text,int tx,int ty,int cols,int lines,int skip,int *usedSkip){
            QStringList wrapped;
            const int maxCols=std::clamp(cols,1,60);
            int pos=0;
            while(pos<text.size() && wrapped.size()<64){
                const int start=pos;
                int n=0;
                while(pos<text.size() && text.at(pos)!=QLatin1Char('\n') && n<maxCols){
                    ++pos;++n;
                }
                QString line=text.mid(start,n);
                if(n==maxCols && pos<text.size() &&
                   text.at(pos)!=QLatin1Char(' ') && text.at(pos)!=QLatin1Char('\n')){
                    const int space=line.lastIndexOf(QLatin1Char(' '));
                    if(space>=0){ pos=start+space+1;line.truncate(space); }
                }
                while(line.endsWith(QLatin1Char(' ')))line.chop(1);
                wrapped.append(line);
                if(pos<text.size() && text.at(pos)==QLatin1Char('\n'))++pos;
                while(pos<text.size() && text.at(pos)==QLatin1Char(' '))++pos;
            }
            const int actualSkip=std::clamp(skip,0,std::max(0,int(wrapped.size())-lines));
            if(usedSkip)*usedSkip=actualSkip;
            for(int i=0;i<lines && i+actualSkip<wrapped.size();++i)
                drawInk(tx,ty+i*rowH,wrapped.at(i+actualSkip));
            return wrapped.size();
        };
        p.fillRect(x,y,w,h,previewColour(palette,style.bg));
        if(!atlas.isNull()&&style.tile>0){
            for(int yy=0;yy<h;yy+=style.tile)for(int xx=0;xx<w;xx+=style.tile){
                const int part=(yy==0?0:yy+style.tile>=h?2:1)*3+(xx==0?0:xx+style.tile>=w?2:1);
                const QImage tile=cellImage(atlas,style.tile,style.cells[part],style.flips[part]);
                if(!tile.isNull())p.drawImage(QRect(x+xx,y+yy,std::min(style.tile,w-xx),std::min(style.tile,h-yy)),tile);
            }
        }
        if(atlas.isNull()){p.setPen(previewColour(palette,style.border));p.drawRect(x,y,w-1,h-1);}        
        p.setPen(previewColour(palette,style.border));
        p.drawLine(x+inset,y+headerBottom,x+w-inset-1,y+headerBottom);
        p.drawLine(x+inset,footerSeparatorY,x+w-inset-1,footerSeparatorY);
        p.drawLine(split,y+headerBottom+4,split,footerSeparatorY);
        /* Mirror the runtime's right-aligned, atlas-safe HEADER status.
         * If the user enlarges the heading glyphs, abbreviate the heading
         * instead of allowing the two header labels to overlap. */
        /* Appearance preview depicts the selected quest as active/tracked.
         * Actual status and discovery are runtime save state, not JSON data. */
        const QString headerStatus=quests.isEmpty()?QString():QStringLiteral("ACTIVE / TRACKED");
        const int statusX=rightLimit-headerStatus.size()*8;
        const int headingX=x+std::max(inset,style.titleX);
        const int headingChars=std::max(0,(statusX-8-headingX)/(8*style.titleScaleX));
        const int statusY=y+style.titleY+std::max(0,(8*style.titleScaleY-16)/2);
        drawInk(headingX,y+style.titleY,QStringLiteral("QUEST JOURNAL").left(headingChars),style.titleScaleX,style.titleScaleY);
        drawInk(statusX,statusY,headerStatus);
        drawInk(listX,y+headerBottom+8,QStringLiteral("QUESTS"));
        /* Preview ALL authored quests, even initially hidden ones, because
         * the designer must be able to inspect artwork before discovery. */
        const int previewVisibleRows=std::max(1,std::min(8,
            (available-2*style.margin-headerBottom-32-(inset+26))/24));
        const int selected=quests.isEmpty()?0:std::clamp(selectedQuest,0,int(quests.size())-1);
        const int first=selected>=previewVisibleRows?selected-previewVisibleRows+1:0;
        if(first>0)drawInk(split-16,y+headerBottom+8,QString(QChar(0x1E)));
        if(first+previewVisibleRows<quests.size())
            drawInk(split-16,footerSeparatorY-24,QString(QChar(0x1F)));
        if(quests.isEmpty())drawInk(listX,rowsTop,QStringLiteral("No quests yet."));
        for(int row=0;row<previewVisibleRows && first+row<quests.size();++row){
            const int idx=first+row;
            const int yy=rowsTop+row*24;
            if(yy+17>=footerSeparatorY-6)break;
            if(idx==selected){
                p.setPen(previewColour(palette,style.highlight));
                p.drawRect(listX-3,yy-3,std::max(8,split-listX-4),23);
            }
            drawIcon(0,listX,yy);
            const int titleCols=std::max(1,(split-(listX+20)-22)/8);
            drawInk(listX+20,yy,quests.at(idx).title.left(titleCols));
        }
        /* The selected title is already in the left list. It is NOT
         * duplicated in this right-hand detail pane. */
        const int descIconY=descY-2;
        const bool descIcon=drawIcon(3,right,descIconY);
        const int descTextX=right+(descIcon?20:0);
        const int descCols=std::max(8,(rightLimit-descTextX)/8-1);
        const QString selectedDescription=quests.isEmpty()?QString():quests.at(selected).description;
        int previewSkip=0;
        const int previewRows=sampleWrap(selectedDescription,descTextX,descY,
                                         descCols,descLines,descriptionScroll,&previewSkip);
        if(descLines>0 && previewSkip>0)
            drawInk(rightLimit,descY-2,QString(QChar(0x1E)),1,2,true);
        if(descLines>0 && previewRows>previewSkip+descLines)
            drawInk(rightLimit,descY+(descLines-1)*rowH,QString(QChar(0x1F)),1,2,true);
        const int objIconY=objectiveTextY-2;
        const bool objIcon=drawIcon(4,right,objIconY);
        drawInk(right,objectiveTitleY,QStringLiteral("CURRENT OBJECTIVE"));
                const QString selectedObjective=quests.isEmpty()?QString():quests.at(selected).objective;
        drawInk(right+(objIcon?20:0),objectiveTextY,
                selectedObjective.isEmpty()?QStringLiteral("No active objective"):selectedObjective.left(
                    std::max(1,(rightLimit-right-(objIcon?20:0))/8)));
        drawInk(x+inset,footerY,QStringLiteral("UP/DOWN QUEST  L/R TEXT"));
        drawInk(right,footerY,QStringLiteral("FIRE1 TRACK  FIRE2 BACK"));
        if(dock.pixels){p.setPen(Qt::white);p.drawText(8,dock.mode==QStringLiteral("top")?22:306,QStringLiteral("HUD (automatic)"));}
    }
};

class JournalDesigner final : public QDialog {
public:
    explicit JournalDesigner(const QString &root,QWidget *parent):QDialog(parent),projectRoot(root),path(styleFile(root)) {
        setWindowTitle(tr("Quest Journal Designer | Project-wide"));resize(1280,760);
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
        for(auto *box:{titleFontX,titleFontY}) for(int size:{1,2,4,8}) box->addItem(tr("%1× native glyph").arg(size),size);
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
        outlineEnabled=new QCheckBox(tr("Enable journal text outline"),colours);colourForm->addRow(outlineEnabled);
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

        auto *iconGroup=new QGroupBox(tr("Journal icons (native 8px atlas tiles)"),left);
        auto *iconForm=new QGridLayout(iconGroup);
        const QStringList iconLabels={tr("Quest list: active"),tr("Quest list: completed"),
                                      tr("Reserved legacy icon"),tr("Description"),tr("Current objective")};
        const QStringList quadrantLabels={tr("TL"),tr("TR"),tr("BL"),tr("BR")};
        for(int i=0;i<5;++i){
            const int row=i*2;
            iconButtons[i]=new QPushButton(tr("None"),iconGroup); iconButtons[i]->setMinimumWidth(100);
            iconClear[i]=new QPushButton(tr("Clear"),iconGroup);
            iconFlipX[i]=new QCheckBox(tr("Flip X"),iconGroup);iconFlipY[i]=new QCheckBox(tr("Flip Y"),iconGroup);
            iconTwoByTwo[i]=new QCheckBox(tr("2×2 tiles (16×16 native)"),iconGroup);
            auto *iconLabel=new QLabel(iconLabels[i],iconGroup);
            iconForm->addWidget(iconLabel,row,0);
            iconForm->addWidget(iconButtons[i],row,1);
            iconForm->addWidget(iconClear[i],row,2);
            iconForm->addWidget(iconFlipX[i],row,3);
            iconForm->addWidget(iconFlipY[i],row,4);
            iconForm->addWidget(iconTwoByTwo[i],row+1,0);
            auto *partsWidget=new QWidget(iconGroup);
            auto *partsGrid=new QGridLayout(partsWidget);
            partsGrid->setContentsMargins(0,0,0,0);
            for(int part=0;part<4;++part){
                iconPartButtons[i][part]=new QPushButton(quadrantLabels[part],partsWidget);
                iconPartButtons[i][part]->setToolTip(tr("Select %1 8×8 atlas tile").arg(quadrantLabels[part]));
                partsGrid->addWidget(iconPartButtons[i][part],part/2,part%2);
                iconPartChosen[i][part]=65535;
            }
            iconForm->addWidget(partsWidget,row+1,1,1,4);
            if(i==2){ /* Retire duplicate title icon without renumbering
                         * existing saved array slots or generated C data. */
                iconLabel->hide();iconButtons[i]->hide();iconClear[i]->hide();
                iconFlipX[i]->hide();iconFlipY[i]->hide();
                iconTwoByTwo[i]->hide();partsWidget->hide();
            }
            iconChosen[i]=65535;iconFlips[i]=0;
        }
        controls->addWidget(iconGroup);
        controls->addStretch();

        auto *leftScroll=new QScrollArea(this);leftScroll->setWidgetResizable(true);leftScroll->setWidget(left);leftScroll->setMinimumWidth(460);layout->addWidget(leftScroll,0);
        auto *right=new QVBoxLayout;
        auto *previewSelector=new QHBoxLayout;
        previewSelector->addWidget(new QLabel(tr("Preview actual quest:"),this));
        questPreviewChoice=new QComboBox(this);
        questPreviewChoice->setMinimumWidth(240);
        previewSelector->addWidget(questPreviewChoice,1);
        previewSelector->addWidget(new QLabel(tr("Description row:"),this));
        previewScroll=new QSpinBox(this);
        previewScroll->setRange(0,63);
        previewScroll->setToolTip(tr("Preview scrolling a long quest description, without changing game state."));
        previewSelector->addWidget(previewScroll);
        auto *editQuest=new QPushButton(tr("Edit selected quest..."),this);
        previewSelector->addWidget(editQuest);
        right->addLayout(previewSelector);
        preview=new JournalPreview(this);preview->dock=layoutDock;right->addWidget(preview,1);
        auto *previewHelp=new QLabel(tr("Preview assumes ACTIVE / TRACKED. Hidden quests are shown for design; the first objective is displayed. Actual progress is not changed."),this);
        previewHelp->setWordWrap(true);right->addWidget(previewHelp);
        auto reloadQuests=[this]{
            const QString previous=questPreviewChoice->currentData().toString();
            QString error;
            preview->quests=projectQuests(projectRoot,&error);
            QSignalBlocker blocker(questPreviewChoice);
            questPreviewChoice->clear();
            for(const PreviewQuest &quest:preview->quests){
                questPreviewChoice->addItem(quest.title+
                    (quest.initiallyHidden?tr(" (initially hidden)"):QString()),quest.id);
            }
            if(questPreviewChoice->count()==0)
                questPreviewChoice->addItem(error.isEmpty()?tr("No quests defined"):error,QString());
            const int found=questPreviewChoice->findData(previous);
            questPreviewChoice->setCurrentIndex(found>=0?found:0);
            preview->selectedQuest=questPreviewChoice->currentIndex();
            previewScroll->setValue(0);
            preview->update();
        };
        connect(questPreviewChoice,QOverload<int>::of(&QComboBox::currentIndexChanged),
                this,[this](int index){
                    preview->selectedQuest=index;
                    previewScroll->setValue(0);
                    preview->update();
                });
        connect(previewScroll,QOverload<int>::of(&QSpinBox::valueChanged),
                this,[this](int offset){preview->descriptionScroll=offset;preview->update();});
        connect(editQuest,&QPushButton::clicked,this,[this,reloadQuests]{
            QString error;
            if(!editGameQuests(this,projectRoot,&error,
                              questPreviewChoice->currentData().toString()) && !error.isEmpty())
                QMessageBox::warning(this,tr("Quest Designer"),error);
            reloadQuests();
        });
        reloadQuests();
        auto *hudNote=new QLabel(layoutDock.pixels?
            tr("HUD layout read automatically from gamehud.sbhud: %1 (%2 px). No independent HUD selector.").arg(layoutDock.mode).arg(layoutDock.pixels):
            tr("HUD layout read automatically from gamehud.sbhud: no dock."),this);
        hudNote->setWordWrap(true);right->addWidget(hudNote);
        right->addWidget(new QLabel(tr("Touch opens only; UP/DOWN choose quest, LEFT/RIGHT scroll description, FIRE1 track, FIRE2 close."),this));
        auto *saveButtons=new QDialogButtonBox(QDialogButtonBox::Save|QDialogButtonBox::Cancel,this);right->addWidget(saveButtons);layout->addLayout(right,1);

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
            const char *keys[]={("background"),("border"),("text"),("selection"),("outlineColour")};
            const int defaults[5]={2,15,15,14,0};
            for(int i=0;i<5;++i)indices[i]=std::clamp(s.value(QLatin1String(keys[i])).toInt(defaults[i]),0,255);
            paletteChoice->setCurrentIndex(std::max(0,paletteChoice->findData(s.value(QStringLiteral("palette")).toString())));
            atlasChoice->setCurrentIndex(std::max(0,atlasChoice->findData(s.value(QStringLiteral("atlas")).toString())));
            tileSize->setValue(std::clamp(s.value(QStringLiteral("tileSize")).toInt(8),4,32));
            const QJsonArray cells=s.value(QStringLiteral("cells")).toArray(),savedFlips=s.value(QStringLiteral("flips")).toArray();
            for(int i=0;i<9;++i){chosen[i]=std::clamp(i<cells.size()?cells[i].toInt(i):i,0,65535); flips[i]=i<savedFlips.size()?(savedFlips[i].toInt()&12):0; flipX[i]->setChecked((flips[i]&4)!=0); flipY[i]->setChecked((flips[i]&8)!=0);}            
            const QJsonArray icons=s.value(QStringLiteral("iconCells")).toArray(), iconFlipArr=s.value(QStringLiteral("iconFlips")).toArray();
            const QJsonArray modes=s.value(QStringLiteral("icon2x2")).toArray(), partSets=s.value(QStringLiteral("iconParts")).toArray();
            for(int i=0;i<5;++i){
                iconChosen[i]=i==2?65535:(i<icons.size()?icons[i].toInt(65535):65535);
                iconFlips[i]=i!=2 && i<iconFlipArr.size()?(iconFlipArr[i].toInt()&12):0;
                iconFlipX[i]->setChecked((iconFlips[i]&4)!=0);iconFlipY[i]->setChecked((iconFlips[i]&8)!=0);
                iconTwoByTwo[i]->setChecked(i!=2 && i<modes.size() && modes[i].toBool());
                const QJsonArray parts=i<partSets.size()?partSets[i].toArray():QJsonArray();
                for(int j=0;j<4;++j)
                    iconPartChosen[i][j]=i==2?65535:(j<parts.size()?parts[j].toInt(65535):65535);
            }
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
            if(palette.size()!=256){ const QString fallback=atlasChoice->currentData().toString(); if(!fallback.isEmpty())palette=SidboxGamePalette::readPalette(QDir(projectRoot).filePath(fallback),false); }
            if(palette.size()!=256){palette=QVector<QRgb>(256,qRgb(0,0,0)); for(int i=0;i<16;++i)palette[i]=previewColour({},i).rgb();}
            preview->palette=palette;
            preview->atlas=atlasImage(projectRoot,atlasChoice->currentData().toString(),palette);
            preview->style.margin=margin->value(); preview->style.split=split->value(); preview->style.listLeft=listLeft->value();
            preview->style.titleX=titleX->value(); preview->style.titleY=titleY->value(); preview->style.titleScaleX=titleFontX->currentData().toInt(); preview->style.titleScaleY=titleFontY->currentData().toInt();
            preview->style.bg=indices[0]; preview->style.border=indices[1]; preview->style.text=indices[2]; preview->style.highlight=indices[3];
            preview->style.outline=outlineEnabled->isChecked(); preview->style.outlineColour=indices[4]; buttons[4]->setEnabled(preview->style.outline);
            preview->style.tile=tileSize->value();
            for(int i=0;i<9;++i){ preview->style.cells[i]=chosen[i]; flips[i]=(flipX[i]->isChecked()?4:0)|(flipY[i]->isChecked()?8:0); preview->style.flips[i]=flips[i]; tiles[i]->setText(tr("Tile %1").arg(chosen[i])); const QImage im=cellImage(preview->atlas,tileSize->value(),chosen[i],flips[i]); tiles[i]->setIcon(im.isNull()?QIcon():QIcon(QPixmap::fromImage(im.scaled(34,34,Qt::KeepAspectRatio,Qt::FastTransformation)))); tiles[i]->setIconSize(QSize(34,34)); tiles[i]->setEnabled(!preview->atlas.isNull()); }
            for(int i=0;i<5;++i){ buttons[i]->setText(tr("Index %1  •  Pick colour...").arg(indices[i])); QPixmap px(22,22);px.fill(previewColour(palette,indices[i])); buttons[i]->setIcon(QIcon(px));buttons[i]->setIconSize(QSize(22,22)); }
            for(int i=0;i<5;++i){
                const bool composite=iconTwoByTwo[i]->isChecked();
                preview->style.iconCells[i]=iconChosen[i];
                preview->style.icon2x2[i]=composite;
                iconFlips[i]=(iconFlipX[i]->isChecked()?4:0)|(iconFlipY[i]->isChecked()?8:0);
                preview->style.iconFlips[i]=iconFlips[i];
                const QImage im=cellImage(preview->atlas,tileSize->value(),iconChosen[i],iconFlips[i]);
                iconButtons[i]->setText(iconChosen[i]==65535?tr("None"):tr("Tile %1").arg(iconChosen[i]));
                iconButtons[i]->setIcon(im.isNull()?QIcon():QIcon(QPixmap::fromImage(im.scaled(24,24,Qt::KeepAspectRatio,Qt::FastTransformation))));
                iconButtons[i]->setIconSize(QSize(24,24));
                iconButtons[i]->setEnabled(!composite && !preview->atlas.isNull());
                iconClear[i]->setEnabled(!preview->atlas.isNull());
                iconFlipX[i]->setEnabled(!preview->atlas.isNull());iconFlipY[i]->setEnabled(!preview->atlas.isNull());
                iconTwoByTwo[i]->setEnabled(!preview->atlas.isNull() && tileSize->value()==8);
                iconTwoByTwo[i]->setToolTip(tr("Combines four different 8×8 atlas tiles with no scaling."));
                for(int part=0;part<4;++part){
                    preview->style.iconParts[i][part]=iconPartChosen[i][part];
                    auto *button=iconPartButtons[i][part];
                    button->setText(iconPartChosen[i][part]==65535?tr("Choose %1").arg(part+1):tr("%1: Tile %2").arg(part+1).arg(iconPartChosen[i][part]));
                    const QImage tile=cellImage(preview->atlas,tileSize->value(),iconPartChosen[i][part],0);
                    button->setIcon(tile.isNull()?QIcon():QIcon(QPixmap::fromImage(tile.scaled(24,24,Qt::KeepAspectRatio,Qt::FastTransformation))));
                    button->setIconSize(QSize(24,24));
                    button->setEnabled(composite && tileSize->value()==8 && !preview->atlas.isNull());
                }
            }
            preview->update();
        };
        for(auto *spin:{margin,split,tileSize,listLeft,titleX,titleY}) connect(spin,QOverload<int>::of(&QSpinBox::valueChanged),this,[redraw](int){redraw();});
        for(auto *box:{titleFontX,titleFontY}) connect(box,QOverload<int>::of(&QComboBox::currentIndexChanged),this,[redraw](int){redraw();});
        connect(outlineEnabled,&QCheckBox::toggled,this,[redraw](bool){redraw();});
        connect(atlasChoice,QOverload<int>::of(&QComboBox::currentIndexChanged),this,[redraw](int){redraw();});
        connect(paletteChoice,QOverload<int>::of(&QComboBox::currentIndexChanged),this,[redraw](int){redraw();});
        for(int i=0;i<9;++i){ connect(flipX[i],&QCheckBox::toggled,this,[redraw](bool){redraw();}); connect(flipY[i],&QCheckBox::toggled,this,[redraw](bool){redraw();}); connect(tiles[i],&QPushButton::clicked,this,[this,i,redraw]{ const int next=chooseCell(this,preview->atlas,tileSize->value(),chosen[i]); if(next>=0){chosen[i]=next;redraw();} }); }
        for(int i=0;i<5;++i){
            connect(buttons[i],&QPushButton::clicked,this,[this,i,redraw]{ const int index=SidboxPalettePicker::chooseIndex(this,preview->palette,indices[i],tr("Journal Palette Colour"), tr("Select an existing SIDBOX 256-colour CLUT index. The palette itself is not modified."),true,true); if(index>=0){indices[i]=index;redraw();} });
            connect(iconButtons[i],&QPushButton::clicked,this,[this,i,redraw]{ const int next=chooseCell(this,preview->atlas,tileSize->value(),iconChosen[i]==65535?0:iconChosen[i]); if(next>=0){iconChosen[i]=next;redraw();} });
            connect(iconClear[i],&QPushButton::clicked,this,[this,i,redraw]{
                iconChosen[i]=65535;iconFlips[i]=0;
                for(int part=0;part<4;++part)iconPartChosen[i][part]=65535;
                iconFlipX[i]->setChecked(false);iconFlipY[i]->setChecked(false);
                iconTwoByTwo[i]->setChecked(false);redraw();
            });
            connect(iconTwoByTwo[i],&QCheckBox::toggled,this,[this,i,redraw](bool enabled){
                if(enabled){
                    const int cols=preview->atlas.isNull()?0:preview->atlas.width()/8;
                    const int rows=preview->atlas.isNull()?0:preview->atlas.height()/8;
                    if(cols>=2 && rows>=2){
                        int base=iconChosen[i]==65535?0:iconChosen[i];
                        if(base%cols>=cols-1 || base/cols>=rows-1)base=0;
                        const int defaults[4]={base,base+1,base+cols,base+cols+1};
                        for(int part=0;part<4;++part)
                            if(iconPartChosen[i][part]==65535)iconPartChosen[i][part]=defaults[part];
                    }
                }
                redraw();
            });
            for(int part=0;part<4;++part){
                connect(iconPartButtons[i][part],&QPushButton::clicked,this,[this,i,part,redraw]{
                    const int next=chooseCell(this,preview->atlas,tileSize->value(),
                                              iconPartChosen[i][part]==65535?0:iconPartChosen[i][part]);
                    if(next>=0){iconPartChosen[i][part]=next;redraw();}
                });
            }
            connect(iconFlipX[i],&QCheckBox::toggled,this,[redraw](bool){redraw();});
            connect(iconFlipY[i],&QCheckBox::toggled,this,[redraw](bool){redraw();});
        }
        connect(saveButtons,&QDialogButtonBox::rejected,this,&QDialog::reject);
        connect(saveButtons,&QDialogButtonBox::accepted,this,[this]{
            /* Quest title icon was retired. Keep the legacy slot empty so
             * the old five-element JSON / generated-runtime ABI remains stable. */
            iconChosen[2]=65535;
            iconFlips[2]=0;
            iconTwoByTwo[2]->setChecked(false);
            for(int part=0;part<4;++part)iconPartChosen[2][part]=65535;
            QJsonArray cells,flipFlags,iconCellsArr,iconFlipFlags,iconModes,iconParts;
            for(int i=0;i<9;++i){cells.append(chosen[i]);flipFlags.append(flips[i]);}
            for(int i=0;i<5;++i){
                iconCellsArr.append(iconChosen[i]);iconFlipFlags.append(iconFlips[i]);
                iconModes.append(iconTwoByTwo[i]->isChecked());
                QJsonArray parts;
                for(int part=0;part<4;++part){
                    if(iconTwoByTwo[i]->isChecked() && (tileSize->value()!=8 || iconPartChosen[i][part]==65535)){
                        QMessageBox::warning(this,tr("Quest Journal Designer"),
                            tr("2×2 icon %1 requires four selected 8×8 tiles.").arg(i+1));
                        return;
                    }
                    parts.append(iconPartChosen[i][part]);
                }
                iconParts.append(parts);
            }
            QJsonObject data{{"version",1},{"margin",margin->value()},{"split",split->value()},{"listLeft",listLeft->value()},{"titleX",titleX->value()},{"titleY",titleY->value()},{"titleFontX",titleFontX->currentData().toInt()},{"titleFontY",titleFontY->currentData().toInt()},{"outlineEnabled",outlineEnabled->isChecked()},{"outlineColour",indices[4]},{"background",indices[0]},{"border",indices[1]},{"text",indices[2]},{"selection",indices[3]},{"palette",paletteChoice->currentData().toString()},{"atlas",atlasChoice->currentData().toString()},{"tileSize",tileSize->value()},{"cells",cells},{"flips",flipFlags},{"iconCells",iconCellsArr},{"iconFlips",iconFlipFlags},
                              {"icon2x2",iconModes},{"iconParts",iconParts}};
            if(!QDir().mkpath(QFileInfo(path).absolutePath())){saveError=tr("Cannot create design directory");QMessageBox::warning(this,tr("Quest Journal Designer"),saveError);return;}
            QSaveFile out(path);const QByteArray json=QJsonDocument(data).toJson(QJsonDocument::Indented); if(!out.open(QIODevice::WriteOnly)||out.write(json)!=json.size()||!out.commit()){ out.cancelWriting();saveError=tr("Cannot save %1").arg(path);QMessageBox::warning(this,tr("Quest Journal Designer"),saveError);return; }
            accept();
        });
        redraw();
    }
    QString loadError,saveError;
private:
    QString projectRoot,path;
    JournalPreview *preview=nullptr;
    QComboBox *questPreviewChoice=nullptr;
    QSpinBox *previewScroll=nullptr;
    QSpinBox *margin=nullptr,*split=nullptr,*tileSize=nullptr,*listLeft=nullptr,*titleX=nullptr,*titleY=nullptr;
    QComboBox *paletteChoice=nullptr,*atlasChoice=nullptr,*titleFontX=nullptr,*titleFontY=nullptr;
    QCheckBox *outlineEnabled=nullptr;
    QPushButton *buttons[5]{},*tiles[9]{},*iconButtons[5]{},*iconClear[5]{};
    QPushButton *iconPartButtons[5][4]{};
    QCheckBox *flipX[9]{},*flipY[9]{},*iconFlipX[5]{},*iconFlipY[5]{},*iconTwoByTwo[5]{};
    int indices[5]{},chosen[9]{},flips[9]{},iconChosen[5]{},iconFlips[5]{},iconPartChosen[5][4]{};
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
