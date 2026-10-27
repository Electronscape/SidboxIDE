#ifndef CODERGIRL_RPG_UI_EDITORS_H
#define CODERGIRL_RPG_UI_EDITORS_H
/* Small project-wide designers. Header-only so the existing Qt target does
 * not require CMake source-list changes; nothing writes to user-owned main.c. */
#include <QDialog>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QCheckBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QLabel>
#include <QFile>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QSaveFile>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
#include <QPen>
#include <QBrush>
#include <QPixmap>
#include <QPainter>
#include <QFont>
#include <QFileInfo>
#include <QMap>
#include <QSet>
#include <QMessageBox>
#include <QFileDialog>
#include <QComboBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QScrollArea>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QScrollBar>
#include <QSignalBlocker>
#include <QKeySequence>
#include <QShortcut>
#include <QResizeEvent>
#include <QTimer>
#include <QElapsedTimer>
#include <QPaintEvent>
#include <QStringList>
#include <QRectF>
#include <QDirIterator>
#include <QIcon>
#include <QSizePolicy>
#include "gamepalette.h"
#include "gamepalettepicker.h"
#include "guidesigner_detail.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsLineItem>
#include <QGraphicsItem>
#include <QVector>
#include <QImage>
#include "ppbcodec.h"
#include <array>
#include <functional>
#include <algorithm>
#include <cmath>

inline QJsonObject cgRpgRead(const QString &path) {
    QFile f(path);
    if(!f.open(QIODevice::ReadOnly))return {};
    const QJsonDocument doc=QJsonDocument::fromJson(f.readAll());
    return doc.isObject()?doc.object():QJsonObject{};
}
inline bool cgRpgWrite(const QString &path,const QJsonObject &root,QString *error) {
    QDir().mkpath(QFileInfo(path).absolutePath());
    QSaveFile file(path);
    const QByteArray payload=QJsonDocument(root).toJson(QJsonDocument::Indented);
    if(!file.open(QIODevice::WriteOnly)||file.write(payload)!=payload.size()||!file.commit()){
        file.cancelWriting();
        if(error)*error=QObject::tr("Could not save %1").arg(path);
        return false;
    }
    return true;
}

/* Same resource enumeration as the Journal and Title designers. */
inline QStringList cgRpgAssets(const QString &root,const QStringList &filters) {
    QStringList names;
    QDirIterator it(root,filters,QDir::Files,QDirIterator::Subdirectories);
    while(it.hasNext()) {
        const QString name=QDir(root).relativeFilePath(it.next());
        if(name.startsWith(QStringLiteral(".git/")) ||
           name.startsWith(QStringLiteral(".codergirl/")) ||
           name.startsWith(QStringLiteral("build")) ||
           name.contains(QStringLiteral("/build")))continue;
        names<<name;
    }
    names.removeDuplicates();names.sort(Qt::CaseInsensitive);return names;
}
inline QVector<QRgb> cgRpgPalette(const QString &root,const QString &relative) {
    if(relative.isEmpty())return {};
    return SidboxGamePalette::readPalette(QDir(root).filePath(relative),false);
}
inline QColor cgRpgColour(const QVector<QRgb> &palette,int index) {
    if(index>=0&&index<palette.size())return QColor::fromRgba(palette[index]);
    const QColor basic[]={Qt::black,QColor(0,0,128),QColor(24,30,55),
      QColor(22,94,128),QColor(90,12,34),QColor(110,45,85),
      QColor(60,80,28),QColor(160,160,160),QColor(65,65,65),
      Qt::blue,Qt::green,Qt::cyan,Qt::red,Qt::magenta,Qt::yellow,Qt::white};
    return basic[qBound(0,index,15)];
}
/* Match JournalPreview::drawInk, using the *actual* CoderGirl glyph bitmaps.
 * Desktop QFont is never used for authored UI lettering. */
inline void cgRpgGlyphText(QPainter &p,int x,int y,const QString &s,
         const QColor &ink,int sx=1,int sy=2,bool outline=false,
         const QColor &edge=QColor(Qt::black)) {
    if(s.isEmpty())return;
    const int width=s.toLatin1().size()*8;
    if(width<1)return;
    QImage native(width,16,QImage::Format_ARGB32_Premultiplied);
    native.fill(Qt::transparent);
    {QPainter glyph(&native);GuiDesignerDetail::drawCoderGirlText(glyph,0,0,s,Qt::white);}
    const QImage scaled=native.scaled(width,8,Qt::IgnoreAspectRatio,Qt::FastTransformation)
                              .scaled(width*qMax(1,sx),8*qMax(1,sy),
                                      Qt::IgnoreAspectRatio,Qt::FastTransformation);
    const auto tinted=[&](const QColor &c){
        QImage im=scaled;
        QPainter painter(&im);painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
        painter.fillRect(im.rect(),c);return im;
    };
    if(outline){const QImage border=tinted(edge);
        p.drawImage(x-1,y,border);p.drawImage(x+1,y,border);
        p.drawImage(x,y-1,border);p.drawImage(x,y+1,border);}
    p.drawImage(x,y,tinted(ink));
}
/* Atlas cells are wrapped into columns that FIT the available sidebar width.
 * The only scrollbar needed is vertical. Same widget serves the frame picker. */
class CgRpgMapAtlas : public QWidget {
public:
    QImage image;
    int cell=16,index=0,thumb=28;
    std::function<void(int)> onCell;
    explicit CgRpgMapAtlas(QWidget *parent):QWidget(parent) {
        setMinimumWidth(0);
        setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Minimum);
    }
    int cols() const {return qMax(1,width()/thumb);}
    int cellCount() const {
        return image.isNull()||cell<=0?0:(image.width()/cell)*(image.height()/cell);
    }
    void showAtlas() {
        const int rows=qMax(1,(cellCount()+cols()-1)/cols());
        const int height=rows*thumb+4;
        if(minimumHeight()!=height)setMinimumHeight(height);
        update();
    }
protected:
    void resizeEvent(QResizeEvent *event) override {
        QWidget::resizeEvent(event);showAtlas();
    }
    void paintEvent(QPaintEvent *event) override {
        QPainter p(this);p.setRenderHint(QPainter::SmoothPixmapTransform,false);
        p.fillRect(event->rect(),QColor(23,28,35));
        if(cellCount()==0){p.setPen(Qt::white);p.drawText(rect(),Qt::AlignCenter,tr("Choose a PPB atlas"));return;}
        const int ac=image.width()/cell;
        const int visible=cellCount();
        const int first=qMax(0,(event->rect().top()/thumb)*cols());
        const int last=qMin(visible,((event->rect().bottom()/thumb)+1)*cols());
        for(int n=first;n<last;++n){
            const QRect target((n%cols())*thumb,(n/cols())*thumb,thumb,thumb);
            const QImage src=image.copy((n%ac)*cell,(n/ac)*cell,cell,cell);
            p.drawImage(target.adjusted(2,2,-2,-2),src);
            p.setPen(n==index?QPen(QColor(255,222,70),2):QPen(QColor(63,70,82),1));
            p.drawRect(target.adjusted(1,1,-2,-2));
        }
    }
    void mousePressEvent(QMouseEvent *e) override {
        if(e->button()==Qt::LeftButton && onCell && cellCount()>0){
            const int col=int(e->position().x())/thumb;
            const int row=int(e->position().y())/thumb;
            const int n=row*cols()+col;
            if(col>=0 && col<cols() && n>=0 && n<cellCount()){
                index=n;update();onCell(n);e->accept();return;
            }
        }
        QWidget::mousePressEvent(e);
    }
};
inline int cgRpgChooseCell(QWidget *parent,const QImage &image,int tile,int selected) {
    if(image.isNull()||tile<=0||image.width()%tile||image.height()%tile)return -1;
    QDialog dialog(parent);dialog.setWindowTitle(QObject::tr("Choose PPB frame tile"));
    auto *layout=new QVBoxLayout(&dialog);
    auto *note=new QLabel(QObject::tr("Click a tile to select it. Scroll vertically for more tiles."),&dialog);
    layout->addWidget(note);
    auto *scroll=new QScrollArea(&dialog);scroll->setWidgetResizable(true);
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    auto *grid=new CgRpgMapAtlas(scroll);grid->image=image;grid->cell=tile;
    grid->index=selected;grid->showAtlas();
    int chosen=-1;
    grid->onCell=[&](int n){chosen=n;dialog.accept();};
    scroll->setWidget(grid);layout->addWidget(scroll,1);
    auto *buttons=new QDialogButtonBox(QDialogButtonBox::Cancel,&dialog);
    QObject::connect(buttons,&QDialogButtonBox::rejected,&dialog,&QDialog::reject);
    layout->addWidget(buttons);dialog.resize(420,550);
    return dialog.exec()==QDialog::Accepted?chosen:-1;
}

inline bool editGameDefeatScreen(QWidget *parent,const QString &projectRoot,QString *error=nullptr)
{
    const QString path=QDir(projectRoot).filePath(QStringLiteral(".codergirl/defeat-screen.json"));
    const QJsonObject saved=cgRpgRead(path);
    QDialog dialog(parent);
    dialog.setWindowTitle(QObject::tr("Defeat Screen Designer"));
    auto *root=new QVBoxLayout(&dialog);
    auto *form=new QFormLayout;
    root->addLayout(form);
    auto *enabled=new QCheckBox(QObject::tr("Enable automatic defeat screen when Health reaches zero"),&dialog);
    enabled->setChecked(saved.value(QStringLiteral("enabled")).toBool(false));
    form->addRow(enabled);
    auto *title=new QLineEdit(saved.value(QStringLiteral("title")).toString(QStringLiteral("YOU ARE DEAD")),&dialog);
    auto *subtitle=new QLineEdit(saved.value(QStringLiteral("subtitle")).toString(QStringLiteral("You carc'd it!")),&dialog);
    title->setMaxLength(40);subtitle->setMaxLength(110);
    form->addRow(QObject::tr("Heading"),title);
    form->addRow(QObject::tr("Description (below heading; fatal Game Object note overrides)"),subtitle);
    auto *pos=new QWidget(&dialog);auto *position=new QHBoxLayout(pos);position->setContentsMargins(0,0,0,0);
    auto *x=new QSpinBox(pos);x->setRange(8,400);x->setValue(saved.value(QStringLiteral("titleX")).toInt(50));
    auto *y=new QSpinBox(pos);y->setRange(16,72);y->setValue(saved.value(QStringLiteral("titleY")).toInt(45));
    position->addWidget(new QLabel(QObject::tr("X"),pos));position->addWidget(x);
    position->addWidget(new QLabel(QObject::tr("Y"),pos));position->addWidget(y);
    form->addRow(QObject::tr("Heading position"),pos);
    auto *paletteChoice=new QComboBox(&dialog);
    paletteChoice->addItem(QObject::tr("Use project / PPB palette"),QString());
    for(const QString &resource:cgRpgAssets(projectRoot,{QStringLiteral("*.pal"),
              QStringLiteral("*.PAL"),QStringLiteral("*.act"),QStringLiteral("*.ACT"),
              QStringLiteral("*.ppb"),QStringLiteral("*.PPB")}))
        paletteChoice->addItem(resource,resource);
    const QString savedPalette=saved.value(QStringLiteral("palette")).toString();
    if(!savedPalette.isEmpty() && paletteChoice->findData(savedPalette)<0)
        paletteChoice->addItem(QObject::tr("Missing: %1").arg(savedPalette),savedPalette);
    paletteChoice->setCurrentIndex(qMax(0,paletteChoice->findData(savedPalette)));
    form->addRow(QObject::tr("Preview foreground palette"),paletteChoice);
    auto *colours=new QWidget(&dialog);auto *cols=new QGridLayout(colours);cols->setContentsMargins(0,0,0,0);
    QSpinBox *values[4];
    QPushButton *colourPick[4];
    const char *keys[]={"background","border","text","accent"};
    const int defaults[]={2,15,15,14};
    for(int n=0;n<4;++n){
        const int row=n/2,base=(n%2)*3;
        cols->addWidget(new QLabel(QString::fromLatin1(keys[n]),colours),row,base);
        values[n]=new QSpinBox(colours);values[n]->setRange(0,255);
        values[n]->setValue(saved.value(QLatin1String(keys[n])).toInt(defaults[n]));
        cols->addWidget(values[n],row,base+1);
        colourPick[n]=new QPushButton(QObject::tr("Pick..."),colours);
        colourPick[n]->setToolTip(QObject::tr("Select an index using the standard 256-colour palette picker"));
        cols->addWidget(colourPick[n],row,base+2);
    }
    form->addRow(QObject::tr("Palette indices"),colours);
    auto *fontRow=new QWidget(&dialog);auto *fl=new QHBoxLayout(fontRow);fl->setContentsMargins(0,0,0,0);
    auto *sx=new QComboBox(fontRow);sx->addItems({QStringLiteral("1"),QStringLiteral("2"),QStringLiteral("4"),QStringLiteral("8")});
    auto *sy=new QComboBox(fontRow);sy->addItems({QStringLiteral("1"),QStringLiteral("2"),QStringLiteral("4"),QStringLiteral("8")});
    sx->setCurrentText(QString::number(saved.value(QStringLiteral("fontScaleX")).toInt(1)));
    sy->setCurrentText(QString::number(saved.value(QStringLiteral("fontScaleY")).toInt(2)));
    fl->addWidget(new QLabel(QObject::tr("X"),fontRow));fl->addWidget(sx);
    fl->addWidget(new QLabel(QObject::tr("Y"),fontRow));fl->addWidget(sy);
    auto *outline=new QCheckBox(QObject::tr("Glyph outline"),fontRow);
    outline->setChecked(saved.value(QStringLiteral("outlineEnabled")).toBool(false));
    auto *outlineColour=new QSpinBox(fontRow);outlineColour->setRange(0,255);
    outlineColour->setValue(saved.value(QStringLiteral("outlineColour")).toInt(0));
    fl->addWidget(outline);fl->addWidget(new QLabel(QObject::tr("Outline palette"),fontRow));
    fl->addWidget(outlineColour);
    auto *pickOutline=new QPushButton(QObject::tr("Pick..."),fontRow);
    fl->addWidget(pickOutline);
    form->addRow(QObject::tr("Native font / glyph styling"),fontRow);
    auto *skinGroup=new QGroupBox(QObject::tr("Nine-slice PPB frame (same format as Quest Journal)"),&dialog);
    auto *skinLayout=new QVBoxLayout(skinGroup);
    auto *atlasRow=new QHBoxLayout;
    auto *atlas=new QComboBox(skinGroup);
    atlas->addItem(QObject::tr("No frame (solid background)"),QString());
    for(const QString &resource:cgRpgAssets(projectRoot,
                   {QStringLiteral("*.ppb"),QStringLiteral("*.PPB")}))
        atlas->addItem(resource,resource);
    const QString savedAtlas=saved.value(QStringLiteral("atlas")).toString();
    if(!savedAtlas.isEmpty() && atlas->findData(savedAtlas)<0)
        atlas->addItem(QObject::tr("Missing: %1").arg(savedAtlas),savedAtlas);
    atlas->setCurrentIndex(qMax(0,atlas->findData(savedAtlas)));
    atlasRow->addWidget(new QLabel(QObject::tr("Project PPB frame"),skinGroup));
    atlasRow->addWidget(atlas,1);
    skinLayout->addLayout(atlasRow);
    auto *tileSize=new QComboBox(skinGroup);tileSize->addItems({QStringLiteral("8"),QStringLiteral("16"),QStringLiteral("32")});
    tileSize->setCurrentText(QString::number(saved.value(QStringLiteral("tileSize")).toInt(8)));
    skinLayout->addWidget(new QLabel(QObject::tr("Tile size / edit each of the 3x3 frame cells"),skinGroup));
    skinLayout->addWidget(tileSize);
    auto *cellsGrid=new QGridLayout;
    std::array<QSpinBox*,9> cells{};
    std::array<QPushButton*,9> pickCells{};
    std::array<QComboBox*,9> flips{};
    const QJsonArray savedFlips=saved.value(QStringLiteral("flips")).toArray();
    const QJsonArray savedCells=saved.value(QStringLiteral("cells")).toArray();
    for(int i=0;i<9;++i){
        cells[i]=new QSpinBox(skinGroup);cells[i]->setRange(0,65534);
        cells[i]->setValue(i<savedCells.size()?savedCells[i].toInt(i):i);
        cells[i]->setToolTip(QObject::tr("Atlas cell index %1 (0-based)").arg(i));
        auto *cellControl=new QWidget(skinGroup);
        auto *cellRow=new QHBoxLayout(cellControl);cellRow->setContentsMargins(0,0,0,0);
        cellRow->addWidget(cells[i]);
        pickCells[i]=new QPushButton(QObject::tr("Pick tile"),cellControl);
        pickCells[i]->setToolTip(QObject::tr("Choose frame tile %1 from the PPB preview").arg(i+1));
        cellRow->addWidget(pickCells[i]);
        flips[i]=new QComboBox(cellControl);flips[i]->addItems({QStringLiteral("None"),
            QStringLiteral("X"),QStringLiteral("Y"),QStringLiteral("XY")});
        const int existingFlip=i<savedFlips.size()?savedFlips[i].toInt()&12:0;
        flips[i]->setCurrentIndex(((existingFlip&4)?1:0)+((existingFlip&8)?2:0));
        flips[i]->setToolTip(QObject::tr("Mirror this frame tile horizontally or vertically"));
        cellRow->addWidget(flips[i]);
        cellsGrid->addWidget(cellControl,i/3,i%3);
    }
    skinLayout->addLayout(cellsGrid);
    root->addWidget(skinGroup);
    auto *preview=new QLabel(&dialog);preview->setMinimumSize(480,320);
    preview->setAlignment(Qt::AlignCenter);root->addWidget(preview,1);
    const auto redraw=[=](){
        QPixmap pix(480,320);pix.fill(QColor(16,20,31));
        QPainter paint(&pix);paint.setRenderHint(QPainter::Antialiasing,false);
        QVector<QRgb> colourTable=cgRpgPalette(projectRoot,paletteChoice->currentData().toString());
        if(colourTable.size()!=256)
            colourTable=cgRpgPalette(projectRoot,atlas->currentData().toString());
        const auto ink=[&](int i){return cgRpgColour(colourTable,i);};
        paint.fillRect(pix.rect(),ink(values[0]->value()));
        for(int n=0;n<4;++n){
            QPixmap icon(18,18);icon.fill(ink(values[n]->value()));
            colourPick[n]->setIcon(QIcon(icon));colourPick[n]->setIconSize(QSize(18,18));
        }
        QPixmap outlineSwatch(18,18);outlineSwatch.fill(ink(outlineColour->value()));
        pickOutline->setIcon(QIcon(outlineSwatch));pickOutline->setIconSize(QSize(18,18));
        SidboxPpb::Picture art;QString readError;
        const int tile=tileSize->currentText().toInt();
        if(!atlas->currentData().toString().isEmpty() &&
           SidboxPpb::read(QDir(projectRoot).filePath(atlas->currentData().toString()),&art,&readError) &&
           art.indexed.width()>=3*tile && art.indexed.height()>=3*tile &&
           art.indexed.width()%tile==0 && art.indexed.height()%tile==0){
            QImage sheet=art.indexed;
            if(sheet.format()==QImage::Format_Indexed8 && colourTable.size()==256)
                sheet.setColorTable(colourTable);
            const int atlasCols=sheet.width()/tile;
            for(int ty=10;ty<310;ty+=tile){
                for(int tx=10;tx<470;tx+=tile){
                    const int index=cells[((ty==10)?0:(ty+tile>=310)?2:1)*3+
                                          ((tx==10)?0:(tx+tile>=470)?2:1)]->value();
                    if(index>=0 && index<atlasCols*(sheet.height()/tile)){
                        const int frameSlot=((ty==10)?0:(ty+tile>=310)?2:1)*3+
                                            ((tx==10)?0:(tx+tile>=470)?2:1);
                        const int flags=flips[frameSlot]->currentIndex();
                        // Qt6's mirrored(bool,bool) is deprecated. QFlags
                        // describes both flip axes without ambiguity.
                        Qt::Orientations orientation;
                        if(flags&1)orientation|=Qt::Horizontal;
                        if(flags&2)orientation|=Qt::Vertical;
                        QImage frame=sheet.copy((index%atlasCols)*tile,
                                                 (index/atlasCols)*tile,tile,tile);
                        if(orientation)frame=frame.flipped(orientation);
                        paint.drawImage(QPoint(tx,ty),frame);
                    }
                }
            }
        } else {
            paint.setPen(ink(values[1]->value()));
            paint.drawRect(10,10,459,299);
        }
        const int fontPixelsX=sx->currentText().toInt(),fontPixelsY=sy->currentText().toInt();
        const auto glyph=[&](int px,int py,const QString &str,int gx,int gy){
            cgRpgGlyphText(paint,px,py,str,ink(values[2]->value()),gx,gy,
                           outline->isChecked(),ink(outlineColour->value()));
        };
        const int previewTitleY=10+qMax(y->value()-10,8);
        const int glyphHeight=fontPixelsY*8;
        const int previewFooterY=310-26;
        glyph(x->value(),previewTitleY,title->text(),fontPixelsX,fontPixelsY);
        const int descriptionY=previewTitleY+glyphHeight+5;
        const int maxChars=qMax(1,(470-x->value())/8);
        QString remaining=subtitle->text().simplified();
        int descriptionRows=0;
        while(!remaining.isEmpty() && descriptionRows<3){
            int take=qMin(maxChars,remaining.size());
            if(take<remaining.size()){
                const int space=remaining.lastIndexOf(QLatin1Char(' '),take);
                if(space>0)take=space;
            }
            glyph(x->value(),descriptionY+descriptionRows*16,remaining.left(take).trimmed(),1,2);
            remaining=remaining.mid(take).trimmed();
            ++descriptionRows;
        }
        const int previewListY=qMin(qMax(descriptionY+descriptionRows*16+8,52),previewFooterY-98);
        for(int i=0;i<10;++i){
            const int sx0=36+(i/5)*212,sy0=previewListY+(i%5)*20;
            if(i==0){paint.setPen(ink(values[3]->value()));
                paint.drawRect(sx0-4,sy0-4,197,21);}
            glyph(sx0,sy0,QStringLiteral("%1 SLOT %2  SAVED")
                 .arg(i==0?QStringLiteral("> "):QStringLiteral("  "))
                 .arg(i+1,2,10,QLatin1Char('0')),1,2);
        }
        glyph(28,previewFooterY,QObject::tr("FIRE1 LOAD SLOT  FIRE2 LAST SAVE"),1,2);
        const QImage tilesImage=art.indexed;
        const bool hasAtlas=!atlas->currentData().toString().isEmpty() && !tilesImage.isNull() &&
              tilesImage.width()%tile==0 && tilesImage.height()%tile==0;
        for(int i=0;i<9;++i){
            pickCells[i]->setEnabled(hasAtlas);
            if(!hasAtlas){pickCells[i]->setIcon(QIcon());continue;}
            const int cellIndex=cells[i]->value();const int ac=tilesImage.width()/tile;
            if(cellIndex>=0 && cellIndex<ac*(tilesImage.height()/tile)){
                QPixmap thumb=QPixmap::fromImage(tilesImage.copy(
                    (cellIndex%ac)*tile,(cellIndex/ac)*tile,tile,tile)
                          .scaled(24,24,Qt::IgnoreAspectRatio,Qt::FastTransformation));
                pickCells[i]->setIcon(QIcon(thumb));pickCells[i]->setIconSize(QSize(24,24));
            }else pickCells[i]->setIcon(QIcon());
        }
        paint.end();preview->setPixmap(pix);
    };
    QObject::connect(enabled,&QCheckBox::toggled,&dialog,[=](bool){redraw();});
    QObject::connect(title,&QLineEdit::textChanged,&dialog,[=](const QString &){redraw();});
    QObject::connect(subtitle,&QLineEdit::textChanged,&dialog,[=](const QString &){redraw();});
    for(auto *v:values)QObject::connect(v,qOverload<int>(&QSpinBox::valueChanged),&dialog,[=](int){redraw();});
    QObject::connect(atlas,qOverload<int>(&QComboBox::currentIndexChanged),&dialog,[=](int){redraw();});
    QObject::connect(paletteChoice,qOverload<int>(&QComboBox::currentIndexChanged),&dialog,[=](int){redraw();});
    const auto actualPalette=[&](){
        QVector<QRgb> palette=cgRpgPalette(projectRoot,paletteChoice->currentData().toString());
        if(palette.size()!=256)palette=cgRpgPalette(projectRoot,atlas->currentData().toString());
        return palette;
    };
    for(int i=0;i<4;++i){
        QObject::connect(colourPick[i],&QPushButton::clicked,&dialog,[&,i](){
            const int chosen=SidboxPalettePicker::chooseIndex(&dialog,actualPalette(),values[i]->value(),
                 QObject::tr("Defeat Screen Palette Colour"),
                 QObject::tr("Select a SIDBOX 256-colour CLUT index. No resource is modified."),true,true);
            if(chosen>=0)values[i]->setValue(chosen);
        });
    }
    QObject::connect(pickOutline,&QPushButton::clicked,&dialog,[&](){
        const int chosen=SidboxPalettePicker::chooseIndex(&dialog,actualPalette(),outlineColour->value(),
            QObject::tr("Defeat Outline Colour"),
            QObject::tr("Select a SIDBOX foreground CLUT index."),true,true);
        if(chosen>=0)outlineColour->setValue(chosen);
    });
    const auto pickedAtlas=[&](){
        SidboxPpb::Picture picture;QString readError;
        const QString relative=atlas->currentData().toString();
        if(relative.isEmpty() || !SidboxPpb::read(QDir(projectRoot).filePath(relative),&picture,&readError))
            return QImage();
        QImage image=picture.indexed;
        QVector<QRgb> bank=actualPalette();
        if(image.format()==QImage::Format_Indexed8 && bank.size()==256)image.setColorTable(bank);
        return image;
    };
    for(int i=0;i<9;++i){
        QObject::connect(pickCells[i],&QPushButton::clicked,&dialog,[&,i](){
            const QImage image=pickedAtlas();const int tile=tileSize->currentText().toInt();
            if(image.isNull() || image.width()<tile || image.height()<tile){
                QMessageBox::information(&dialog,QObject::tr("Choose a frame atlas"),
                    QObject::tr("Select a valid PPB frame atlas first."));return;
            }
            const int chosen=cgRpgChooseCell(&dialog,image,tile,cells[i]->value());
            if(chosen>=0)cells[i]->setValue(chosen);
        });
    }
    QObject::connect(tileSize,&QComboBox::currentTextChanged,&dialog,[=](const QString&){redraw();});
    QObject::connect(sx,&QComboBox::currentTextChanged,&dialog,[=](const QString&){redraw();});
    QObject::connect(sy,&QComboBox::currentTextChanged,&dialog,[=](const QString&){redraw();});
    QObject::connect(outline,&QCheckBox::toggled,&dialog,[=](bool){redraw();});
    QObject::connect(outlineColour,qOverload<int>(&QSpinBox::valueChanged),&dialog,[=](int){redraw();});
    for(auto *cell:cells)QObject::connect(cell,qOverload<int>(&QSpinBox::valueChanged),&dialog,[=](int){redraw();});
    for(auto *flip:flips)QObject::connect(flip,qOverload<int>(&QComboBox::currentIndexChanged),&dialog,[=](int){redraw();});
    QObject::connect(x,qOverload<int>(&QSpinBox::valueChanged),&dialog,[=](int){redraw();});
    QObject::connect(y,qOverload<int>(&QSpinBox::valueChanged),&dialog,[=](int){redraw();});
    redraw();
    auto *buttons=new QDialogButtonBox(QDialogButtonBox::Save|QDialogButtonBox::Cancel,&dialog);
    root->addWidget(buttons);
    QObject::connect(buttons,&QDialogButtonBox::accepted,&dialog,&QDialog::accept);
    QObject::connect(buttons,&QDialogButtonBox::rejected,&dialog,&QDialog::reject);
    if(dialog.exec()!=QDialog::Accepted)return false;
    QJsonObject out{{QStringLiteral("version"),1},{QStringLiteral("enabled"),enabled->isChecked()},
       {QStringLiteral("title"),title->text()},{QStringLiteral("subtitle"),subtitle->text()},
       {QStringLiteral("titleX"),x->value()},{QStringLiteral("titleY"),y->value()}};
    for(int i=0;i<4;++i)out.insert(QLatin1String(keys[i]),values[i]->value());
    out.insert(QStringLiteral("outlineEnabled"),outline->isChecked());
    out.insert(QStringLiteral("outlineColour"),outlineColour->value());
    out.insert(QStringLiteral("fontScaleX"),sx->currentText().toInt());
    out.insert(QStringLiteral("fontScaleY"),sy->currentText().toInt());
    out.insert(QStringLiteral("atlas"),atlas->currentData().toString());
    out.insert(QStringLiteral("palette"),paletteChoice->currentData().toString());
    out.insert(QStringLiteral("tileSize"),tileSize->currentText().toInt());
    QJsonArray skinCells,skinFlips;
    for(int i=0;i<9;++i){skinCells.append(cells[i]->value());
        skinFlips.append(((flips[i]->currentIndex()&1)?4:0)|((flips[i]->currentIndex()&2)?8:0));}
    out.insert(QStringLiteral("cells"),skinCells);
    out.insert(QStringLiteral("flips"),skinFlips);
    return cgRpgWrite(path,out,error);
}

/* A paintable PPB map canvas. Markers retain Qt's normal drag behaviour;
 * painting anywhere else never accidentally pans the world map. */
class CgRpgMapCanvas : public QGraphicsView {
public:
    int cellSize=16;
    QRectF mapBounds{0,0,1024,768};
    QColor boundaryPreview=QColor(255,203,72);
    bool draggingMarker=false;
    bool markerEditing=false;
    bool middlePanning=false;
    QPoint panStart;
    int initialH=0,initialV=0;
    std::function<void(const QPointF &,bool)> onPaint;
    std::function<void(qreal)> onZoom;
    std::function<void()> onStrokeFinished;
    explicit CgRpgMapCanvas(QGraphicsScene *scene,QWidget *parent)
        :QGraphicsView(scene,parent) {
        setRenderHint(QPainter::Antialiasing,false);
        setDragMode(QGraphicsView::NoDrag);
        setMouseTracking(true);
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        setResizeAnchor(QGraphicsView::AnchorViewCenter);
        setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    }
protected:
    void drawBackground(QPainter *painter,const QRectF &area) override {
        painter->fillRect(area,QColor(16,20,27));
        const QRectF visible=mapBounds.intersected(area);
        if(visible.isEmpty())return;
        painter->fillRect(visible,QColor(22,29,42));
        painter->setPen(QPen(QColor(44,53,67),0));
        const int x0=int(std::floor(visible.left()/cellSize))*cellSize;
        const int y0=int(std::floor(visible.top()/cellSize))*cellSize;
        for(int x=x0;x<=visible.right();x+=cellSize)
            painter->drawLine(QPointF(x,visible.top()),QPointF(x,visible.bottom()));
        for(int y=y0;y<=visible.bottom();y+=cellSize)
            painter->drawLine(QPointF(visible.left(),y),QPointF(visible.right(),y));
    }
    void drawForeground(QPainter *p,const QRectF &) override {
        p->setPen(QPen(boundaryPreview,2));
        p->setBrush(Qt::NoBrush);p->drawRect(mapBounds);
        p->fillRect(QRectF(0,0,190,22),QColor(8,13,21,220));
        p->setPen(QColor(255,222,128));
        p->drawText(QRectF(5,2,185,18),Qt::AlignLeft|Qt::AlignVCenter,
           QStringLiteral("%1 x %2 px   (%3 x %4)")
              .arg(int(mapBounds.width())).arg(int(mapBounds.height()))
              .arg(int(mapBounds.width())/cellSize).arg(int(mapBounds.height())/cellSize));
    }
    bool overMarker(const QPoint &pos) const {
        for(QGraphicsItem *item=itemAt(pos);item;item=item->parentItem())
            if(item->data(0).toString()==QStringLiteral("mapMarker"))return true;
        return false;
    }
    void mousePressEvent(QMouseEvent *e) override {
        if(e->button()==Qt::MiddleButton){
            middlePanning=true;panStart=e->pos();
            initialH=horizontalScrollBar()->value();initialV=verticalScrollBar()->value();
            viewport()->setCursor(Qt::ClosedHandCursor);e->accept();return;
        }
        draggingMarker=markerEditing && e->button()==Qt::LeftButton && overMarker(e->pos());
        if((e->button()==Qt::LeftButton||e->button()==Qt::RightButton) &&
           !draggingMarker && (!markerEditing || !overMarker(e->pos())) &&
           mapBounds.contains(mapToScene(e->pos())) && onPaint){
            onPaint(mapToScene(e->pos()),e->button()==Qt::RightButton);
            e->accept();return;
        }
        QGraphicsView::mousePressEvent(e);
    }
    void mouseReleaseEvent(QMouseEvent *e) override {
        if(e->button()==Qt::MiddleButton){
            middlePanning=false;viewport()->unsetCursor();e->accept();return;
        }
        QGraphicsView::mouseReleaseEvent(e);draggingMarker=false;
        /* A whole brush/erase drag, bucket click, or moved flag is ONE edit. */
        if((e->button()==Qt::LeftButton || e->button()==Qt::RightButton) && onStrokeFinished)
            onStrokeFinished();
    }
    void mouseMoveEvent(QMouseEvent *e) override {
        if(middlePanning){
            const QPoint diff=e->pos()-panStart;
            horizontalScrollBar()->setValue(initialH-diff.x());
            verticalScrollBar()->setValue(initialV-diff.y());
            e->accept();return;
        }
        if(!draggingMarker && (e->buttons()&(Qt::LeftButton|Qt::RightButton)) &&
           mapBounds.contains(mapToScene(e->pos())) &&
           (!markerEditing || !overMarker(e->pos())) && onPaint){
            onPaint(mapToScene(e->pos()),!!(e->buttons()&Qt::RightButton));
            e->accept();return;
        }
        QGraphicsView::mouseMoveEvent(e);
    }
    void wheelEvent(QWheelEvent *e) override {
        if(e->angleDelta().y()==0){QGraphicsView::wheelEvent(e);return;}
        const qreal factor=e->angleDelta().y()>0?1.25:0.8;
        const qreal next=transform().m11()*factor;
        if(next>=0.25 && next<=8.0){
            scale(factor,factor);
            if(onZoom)onZoom(transform().m11());
        }
        e->accept();
    }
};

/* 0-based PPB atlas animation, identical playback to the Visual Tilemap
 * editor. A cell stores the first frame, not the current animated frame. */
struct CgRpgMapAnimation {
    int cell=0, frames=4, ticks=5;
    bool loop=true,bounce=false;
    bool operator==(const CgRpgMapAnimation &other) const {
        return cell==other.cell && frames==other.frames && ticks==other.ticks &&
               loop==other.loop && bounce==other.bounce;
    }
};
/* Complete editable map state for bounded, stroke-grouped Undo/Redo. */
struct CgRpgMapEditState {
    int width=0,height=0,tileSize=16,border=15,flash=14;
    QString atlas,palette;
    QVector<int> tiles;
    QMap<QString,int> flags;
    QMap<QString,bool> largeFlags;
    QMap<QString,QPointF> positions;
    QMap<int,CgRpgMapAnimation> animations;
    bool operator==(const CgRpgMapEditState &other) const {
        return width==other.width && height==other.height && tileSize==other.tileSize &&
               border==other.border && flash==other.flash && atlas==other.atlas &&
               palette==other.palette && tiles==other.tiles && flags==other.flags &&
               largeFlags==other.largeFlags && positions==other.positions &&
               animations==other.animations;
    }
};
inline int cgRpgMapAnimationFrame(const CgRpgMapAnimation &a,qint64 ticks) {
    if(a.frames<2 || a.ticks<1)return 0;
    const qint64 step=ticks/a.ticks;
    if(a.bounce){
        const qint64 last=a.frames-1,cycle=last*2;
        const qint64 pos=a.loop?step%cycle:qMin(step,cycle);
        return int(pos<=last?pos:cycle-pos);
    }
    return int(a.loop?step%a.frames:qMin(step,qint64(a.frames-1)));
}
inline bool editGameWorldMap(QWidget *parent,const QString &projectRoot,QString *error=nullptr)
{
    const QString path=QDir(projectRoot).filePath(QStringLiteral(".codergirl/world-map.json"));
    const QJsonObject saved=cgRpgRead(path);
    QDialog dialog(parent);dialog.setWindowTitle(QObject::tr("World Map Tile Painter"));
    auto *root=new QVBoxLayout(&dialog);
    auto *settings=new QHBoxLayout;
    auto *w=new QSpinBox(&dialog);w->setRange(480,2048);w->setSingleStep(64);
    auto *h=new QSpinBox(&dialog);h->setRange(320,2048);h->setSingleStep(64);
    w->setValue(saved.value(QStringLiteral("width")).toInt(1024));
    h->setValue(saved.value(QStringLiteral("height")).toInt(768));
    auto *size=new QComboBox(&dialog);size->addItems({QStringLiteral("8"),QStringLiteral("16")});
    size->setCurrentText(QString::number(saved.value(QStringLiteral("tileSize")).toInt(16)));
    settings->addWidget(new QLabel(QObject::tr("Canvas W"),&dialog));settings->addWidget(w);
    settings->addWidget(new QLabel(QObject::tr("H"),&dialog));settings->addWidget(h);
    settings->addWidget(new QLabel(QObject::tr("Cell size"),&dialog));settings->addWidget(size);
    auto *fit=new QPushButton(QObject::tr("Fit canvas"),&dialog);
    auto *zoomReadout=new QLabel(QObject::tr("Zoom 100%"),&dialog);
    settings->addWidget(fit);settings->addWidget(zoomReadout);
    w->setMaximumWidth(90);h->setMaximumWidth(90);size->setMaximumWidth(70);

    auto *colourSettings=new QHBoxLayout;
    root->addLayout(colourSettings);
    auto *split=new QHBoxLayout;root->addLayout(split,1);
    auto *scene=new QGraphicsScene(&dialog);
    auto *view=new CgRpgMapCanvas(scene,&dialog);
    view->setMinimumSize(600,410);
    view->onZoom=[zoomReadout](qreal factor){
        zoomReadout->setText(QObject::tr("Zoom %1%").arg(qRound(factor*100.0)));
    };
    QObject::connect(fit,&QPushButton::clicked,&dialog,[view](){
        view->fitInView(view->mapBounds.adjusted(-24,-24,24,24),Qt::KeepAspectRatio);
        if(view->onZoom)view->onZoom(view->transform().m11());
    });
    auto *side=new QWidget(&dialog);
    side->setMinimumWidth(0);
    auto *right=new QVBoxLayout(side);
    auto *sideScroll=new QScrollArea(&dialog);
    sideScroll->setWidgetResizable(true);
    sideScroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    sideScroll->setMinimumWidth(300);
    sideScroll->setMaximumWidth(355);
    sideScroll->setWidget(side);
    split->addWidget(sideScroll);
    split->addWidget(view,1);
    auto *atlasEdit=new QComboBox(side);
    atlasEdit->addItem(QObject::tr("No atlas"),QString());
    for(const QString &name:cgRpgAssets(projectRoot,{QStringLiteral("*.ppb"),QStringLiteral("*.PPB")}))
        atlasEdit->addItem(name,name);
    const QString storedAtlas=saved.value(QStringLiteral("atlas")).toString();
    if(!storedAtlas.isEmpty() && atlasEdit->findData(storedAtlas)<0)
        atlasEdit->addItem(QObject::tr("Missing: %1").arg(storedAtlas),storedAtlas);
    atlasEdit->setCurrentIndex(qMax(0,atlasEdit->findData(storedAtlas)));
    right->addWidget(new QLabel(QObject::tr("Game resource PPB tilesheet"),side));
    right->addWidget(atlasEdit);
    auto *paletteChoice=new QComboBox(side);
    paletteChoice->addItem(QObject::tr("Use PPB / project palette"),QString());
    for(const QString &name:cgRpgAssets(projectRoot,{QStringLiteral("*.pal"),
                QStringLiteral("*.PAL"),QStringLiteral("*.act"),
                QStringLiteral("*.ACT"),QStringLiteral("*.ppb"),
                QStringLiteral("*.PPB")}))
        paletteChoice->addItem(name,name);
    const QString selectedPalette=saved.value(QStringLiteral("palette")).toString();
    if(!selectedPalette.isEmpty() && paletteChoice->findData(selectedPalette)<0)
        paletteChoice->addItem(QObject::tr("Missing: %1").arg(selectedPalette),selectedPalette);
    paletteChoice->setCurrentIndex(qMax(0,paletteChoice->findData(selectedPalette)));
    right->addWidget(new QLabel(QObject::tr("Preview palette (game resources)"),side));
    right->addWidget(paletteChoice);
    /* Keep both world-map colours visible alongside the palette. The old
       boundary picker was squeezed out of the long canvas-size toolbar. */
    auto *borderColour=new QSpinBox(side);borderColour->setRange(0,255);
    borderColour->setValue(qBound(0,saved.value(QStringLiteral("borderColour")).toInt(15),255));
    auto *borderChoose=new QPushButton(QObject::tr("Pick boundary colour..."),side);
    colourSettings->addWidget(new QLabel(QObject::tr("World Map outer boundary"),&dialog));
    auto *boundaryRow=new QHBoxLayout;
    boundaryRow->addWidget(borderColour);boundaryRow->addWidget(borderChoose);
    colourSettings->addLayout(boundaryRow);
    auto *flagFlashColour=new QSpinBox(side);flagFlashColour->setRange(0,255);
    flagFlashColour->setValue(qBound(0,saved.value(QStringLiteral("flagFlashColour")).toInt(14),255));
    auto *flagFlashPick=new QPushButton(QObject::tr("Pick flash colour..."),side);
    colourSettings->addWidget(new QLabel(QObject::tr("Flashing current-world flag outline"),&dialog));
    auto *flashRow=new QHBoxLayout;
    flashRow->addWidget(flagFlashColour);flashRow->addWidget(flagFlashPick);
    colourSettings->addLayout(flashRow);
    colourSettings->addStretch();
    /* One palette load per selection, not one filesystem read per marker. */
    QVector<QRgb> currentBank;
    const auto activePalette=[&](){return currentBank;};
    const auto reloadPalette=[&](){
        currentBank=cgRpgPalette(projectRoot,paletteChoice->currentData().toString());
        if(currentBank.size()!=256)
            currentBank=cgRpgPalette(projectRoot,atlasEdit->currentData().toString());
    };
    reloadPalette();
    const auto updateBoundaryPreview=[&](){
        view->boundaryPreview=cgRpgColour(currentBank,borderColour->value());
        view->viewport()->update();
    };
    QObject::connect(borderColour,qOverload<int>(&QSpinBox::valueChanged),
                     &dialog,[&](int){updateBoundaryPreview();});
    updateBoundaryPreview();
    QObject::connect(borderChoose,&QPushButton::clicked,&dialog,[&](){
        const int v=SidboxPalettePicker::chooseIndex(&dialog,activePalette(),borderColour->value(),
            QObject::tr("World Map boundary colour"),
            QObject::tr("Select the runtime World Map boundary CLUT index."),true,true);
        if(v>=0)borderColour->setValue(v);
    });
    QObject::connect(flagFlashPick,&QPushButton::clicked,&dialog,[&](){
        const int v=SidboxPalettePicker::chooseIndex(&dialog,activePalette(),flagFlashColour->value(),
            QObject::tr("Flashing world flag outline"),
            QObject::tr("Select the flashing outline CLUT index for the current world flag."),true,true);
        if(v>=0)flagFlashColour->setValue(v);
    });
    auto *palette=new CgRpgMapAtlas(side);
    auto *paletteScroll=new QScrollArea(side);paletteScroll->setWidgetResizable(true);
    paletteScroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    paletteScroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    paletteScroll->setWidget(palette);
    paletteScroll->setMinimumHeight(180);
    paletteScroll->setMaximumHeight(300);
    right->addWidget(new QLabel(QObject::tr("Tile Atlas (click a cell)"),side));
    right->addWidget(paletteScroll);
    right->addWidget(new QLabel(QObject::tr("Painting Cells"),side));
    auto *modeButtons=new QHBoxLayout;
    auto *paintMode=new QPushButton(QObject::tr("Paint map tiles"),side);
    auto *flagMode=new QPushButton(QObject::tr("Choose flag art"),side);
    paintMode->setCheckable(true);flagMode->setCheckable(true);
    paintMode->setChecked(true);
    modeButtons->addWidget(paintMode);modeButtons->addWidget(flagMode);
    paintMode->setToolTip(QObject::tr("Paint the map using atlas cells; flag dragging is disabled."));
    flagMode->setToolTip(QObject::tr("Pick flag artwork or drag world markers without painting tiles."));
    auto selectMode=[&](bool flags){
        paintMode->setChecked(!flags);flagMode->setChecked(flags);
        view->markerEditing=flags;
    };
    /* The mode toggles are exclusive, unlike two unrelated checkboxes. */
    QObject::connect(paintMode,&QPushButton::clicked,&dialog,[&](){selectMode(false);});
    QObject::connect(flagMode,&QPushButton::clicked,&dialog,[&](){selectMode(true);});
    right->addLayout(modeButtons);
    auto *bucket=new QPushButton(QObject::tr("Flood fill bucket (click to arm)"),side);
    bucket->setCheckable(true);
    bucket->setToolTip(QObject::tr("Choose a replacement atlas tile, arm the bucket, then click a map cell. "
                                      "The entire connected region matching the clicked cell is replaced. "
                                      "Click the button again to return to the normal paint brush."));
    right->addWidget(bucket);
    QObject::connect(bucket,&QPushButton::toggled,&dialog,[&](bool armed){
        bucket->setText(armed?QObject::tr("Flood fill ARMED (click to cancel)"):
                   QObject::tr("Flood fill bucket (click to arm)"));
        if(armed)selectMode(false);
    });
    QObject::connect(flagMode,&QPushButton::clicked,&dialog,[&](){bucket->setChecked(false);});
    auto *index=new QSpinBox(side);index->setRange(0,65534);index->setValue(0);
    right->addWidget(new QLabel(QObject::tr("Atlas cell (click preview to select)"),side));
    right->addWidget(index);
    auto *fillEmpty=new QPushButton(QObject::tr("Fill empty cells with selected tile"),side);
    fillEmpty->setToolTip(QObject::tr("Paint the selected atlas tile into every unpainted map cell, ideal for water or grass backgrounds."));
    right->addWidget(fillEmpty);
    auto *animationGroup=new QGroupBox(QObject::tr("Selected Tile Animation"),side);
    auto *animLayout=new QVBoxLayout(animationGroup);
    auto *animPreviewRow=new QHBoxLayout;
    auto *animPreview=new QLabel(animationGroup);
    animPreview->setFixedSize(72,72);
    animPreview->setAlignment(Qt::AlignCenter);
    auto *animStatus=new QLabel(QObject::tr("Choose an atlas cell to animate."),animationGroup);
    animStatus->setWordWrap(true);
    animPreviewRow->addWidget(animPreview);animPreviewRow->addWidget(animStatus,1);
    animLayout->addLayout(animPreviewRow);
    auto *animValues=new QHBoxLayout;
    auto *animFrames=new QSpinBox(animationGroup);animFrames->setRange(1,16);animFrames->setValue(4);
    auto *animDelay=new QSpinBox(animationGroup);animDelay->setRange(1,255);animDelay->setValue(5);
    animValues->addWidget(new QLabel(QObject::tr("Frames"),animationGroup));
    animValues->addWidget(animFrames);
    animValues->addWidget(new QLabel(QObject::tr("VBlanks/frame"),animationGroup));
    animValues->addWidget(animDelay);
    animLayout->addLayout(animValues);
    auto *animOptions=new QHBoxLayout;
    auto *animLoop=new QCheckBox(QObject::tr("Loop"),animationGroup);
    auto *animBounce=new QCheckBox(QObject::tr("Ping-pong"),animationGroup);
    animLoop->setChecked(true);
    animOptions->addWidget(animLoop);animOptions->addWidget(animBounce);
    animLayout->addLayout(animOptions);
    auto *animButtons=new QHBoxLayout;
    auto *setAnimation=new QPushButton(QObject::tr("Set Animation"),animationGroup);
    auto *removeAnimation=new QPushButton(QObject::tr("Remove Animation"),animationGroup);
    animButtons->addWidget(setAnimation);animButtons->addWidget(removeAnimation);
    animLayout->addLayout(animButtons);
    right->addWidget(animationGroup);

    auto *markerGroup=new QGroupBox(QObject::tr("Selected world flag"),side);
    auto *markerLayout=new QFormLayout(markerGroup);
    auto *worldPick=new QComboBox(markerGroup);
    auto *flagCell=new QSpinBox(markerGroup);flagCell->setRange(0,65534);
    auto *flagLarge=new QCheckBox(QObject::tr("2x2 tiles (otherwise 1 tile)"),markerGroup);
    markerLayout->addRow(QObject::tr("World"),worldPick);
    auto *flagRow=new QWidget(markerGroup);
    auto *flagRowLayout=new QHBoxLayout(flagRow);flagRowLayout->setContentsMargins(0,0,0,0);
    flagRowLayout->addWidget(flagCell);
    auto *flagChoose=new QPushButton(QObject::tr("Pick from atlas..."),flagRow);
    flagRowLayout->addWidget(flagChoose);
    markerLayout->addRow(QObject::tr("Flag top-left tile"),flagRow);
    markerLayout->addRow(flagLarge);
    right->addWidget(markerGroup);
    auto *status=new QLabel(QObject::tr("No PPB atlas selected"),side);
    status->setWordWrap(true);right->addWidget(status);
    right->addStretch();
    const int initialCell=size->currentText().toInt();
    int columns=qMax(1,w->value()/initialCell),rows=qMax(1,h->value()/initialCell);
    QVector<int> painted(columns*rows,65535);
    const QJsonArray savedTiles=saved.value(QStringLiteral("tiles")).toArray();
    if(savedTiles.size()==painted.size())
        for(int n=0;n<painted.size();++n)painted[n]=savedTiles[n].toInt(65535);
    QMap<int,CgRpgMapAnimation> mapAnimations;
    for(const QJsonValue &v:saved.value(QStringLiteral("animations")).toArray()){
        const QJsonObject a=v.toObject();
        CgRpgMapAnimation entry;
        entry.cell=a.value(QStringLiteral("cell")).toInt(-1);
        entry.frames=a.value(QStringLiteral("frames")).toInt(1);
        entry.ticks=a.value(QStringLiteral("ticks")).toInt(5);
        entry.loop=a.value(QStringLiteral("loop")).toBool(true);
        entry.bounce=a.value(QStringLiteral("bounce")).toBool(false);
        if(entry.cell>=0 && entry.frames>=2 && entry.frames<=16 &&
           entry.ticks>=1 && entry.ticks<=255 && mapAnimations.size()<256)
            mapAnimations.insert(entry.cell,entry);
    }
    QElapsedTimer animationClock;animationClock.start();
    QMap<int,QSet<int>> animatedSections;
    QMap<int,int> previousFrames;
    std::function<void()> updateAnimControls;
    std::function<void()> updateAnimPreview;
    /* A 256px cached map section is one scene item, rather than one scene
       item per 8/16px tile. Flood fill repaints each affected section ONCE. */
    constexpr int chunkPixels=256;
    int chunkColumns=0;
    QVector<QImage> chunkImages;
    QVector<QGraphicsPixmapItem *> chunkItems;
    QImage sheet,sourceSheet;
    QString loadedAtlas;
    const auto readSheet=[&]()->bool{
        sheet=QImage();
        const QString relative=atlasEdit->currentData().toString();
        if(relative.isEmpty()){
            loadedAtlas.clear();sourceSheet=QImage();return false;
        }
        /* Changing preview CLUT must not decode the same PPB again. Keep
           the untouched indexed source and apply the new colour table only
           to the cheap implicit-sharing copy. */
        if(relative!=loadedAtlas || sourceSheet.isNull()){
            SidboxPpb::Picture ppb;QString readError;
            if(!SidboxPpb::read(QDir(projectRoot).filePath(relative),&ppb,&readError)){
                loadedAtlas.clear();sourceSheet=QImage();
                status->setText(QObject::tr("Cannot open PPB: %1").arg(readError));return false;
            }
            sourceSheet=ppb.indexed;loadedAtlas=relative;
        }
        if(sourceSheet.width()%size->currentText().toInt()||
           sourceSheet.height()%size->currentText().toInt()){
            status->setText(QObject::tr("PPB dimensions must divide evenly into %1px cells.").arg(size->currentText()));
            return false;
        }
        sheet=sourceSheet;
        if(sheet.format()==QImage::Format_Indexed8 && currentBank.size()==256)
            sheet.setColorTable(currentBank);
        return true;
    };
    const auto sectionForCell=[&](int n){
        const int tile=size->currentText().toInt();
        return (((n/columns)*tile)/chunkPixels)*chunkColumns+
               (((n%columns)*tile)/chunkPixels);
    };
    const auto repaintSection=[&](int section){
        if(section<0 || section>=chunkItems.size())return;
        QImage &surface=chunkImages[section];
        surface.fill(Qt::transparent);
        if(!sheet.isNull()){
            QPainter p(&surface);
            p.setCompositionMode(QPainter::CompositionMode_Source);
            const int tile=size->currentText().toInt();
            const int left=(section%chunkColumns)*chunkPixels;
            const int top=(section/chunkColumns)*chunkPixels;
            const int ac=sheet.width()/tile,ar=sheet.height()/tile;
            const int fromX=left/tile,fromY=top/tile;
            const int toX=qMin(columns,(left+surface.width()+tile-1)/tile);
            const int toY=qMin(rows,(top+surface.height()+tile-1)/tile);
            for(int yy=fromY;yy<toY;++yy)for(int xx=fromX;xx<toX;++xx){
                const int base=painted[yy*columns+xx];
                if(base==65535 || base<0 || base>=ac*ar)continue;
                int cell=base;
                if(mapAnimations.contains(base))
                    cell+=cgRpgMapAnimationFrame(mapAnimations.value(base),animationClock.elapsed()/20);
                if(cell>=ac*ar)continue;
                p.drawImage(QRect(xx*tile-left,yy*tile-top,tile,tile),sheet,
                    QRect((cell%ac)*tile,(cell/ac)*tile,tile,tile));
            }
        }
        chunkItems[section]->setPixmap(QPixmap::fromImage(surface));
    };
    const auto rebuildAnimatedSections=[&](){
        animatedSections.clear();
        for(int n=0;n<painted.size();++n)
            if(mapAnimations.contains(painted[n]))
                animatedSections[painted[n]].insert(sectionForCell(n));
    };
    const auto changeCell=[&](int n,int value){
        const int old=painted[n];
        if(old==value)return;
        const int section=sectionForCell(n);
        if(mapAnimations.contains(old))animatedSections[old].remove(section);
        painted[n]=value;
        /* Rebuild on any animated-cell edit: neighbouring instances may
         * still use the old section. The 16K-cell bound keeps this cheap. */
        if(mapAnimations.contains(old) || mapAnimations.contains(value))
            rebuildAnimatedSections();
    };
    const auto updateTile=[&](int n){
        if(n>=0 && n<painted.size())repaintSection(sectionForCell(n));
    };
    const auto repaintAllSections=[&](){
        for(int section=0;section<chunkItems.size();++section)repaintSection(section);
    };
    QMap<QString,QGraphicsRectItem *> markers;
    QMap<QString,QJsonObject> initialPoints;
    for(const QJsonValue &v:saved.value(QStringLiteral("points")).toArray()){
        const QJsonObject point=v.toObject();
        initialPoints.insert(point.value(QStringLiteral("name")).toString(),point);
    }
    QStringList worlds;
    const QDir compiled(QDir(projectRoot).filePath(QStringLiteral("worlds")));
    for(const QFileInfo &entry:compiled.entryInfoList(QDir::Dirs|QDir::NoDotAndDotDot,QDir::Name))
        if(QFileInfo::exists(QDir(entry.absoluteFilePath()).filePath(QStringLiteral("world-build.json"))))
            worlds<<entry.fileName();
    const QDir savedDesigns(QDir(projectRoot).filePath(QStringLiteral(".codergirl/worlds")));
    for(const QFileInfo &entry:savedDesigns.entryInfoList(QDir::Dirs|QDir::NoDotAndDotDot,QDir::Name))
        if(!worlds.contains(entry.fileName()))worlds<<entry.fileName();
    for(auto it=initialPoints.cbegin();it!=initialPoints.cend();++it)
        if(!worlds.contains(it.key()))worlds<<it.key();
    QMap<QString,int> flagCells;
    QMap<QString,bool> flagsLarge;
    int worldIndex=0;
    for(const QString &name:worlds){
        worldPick->addItem(name);
        const QJsonObject existing=initialPoints.value(name);
        auto *marker=scene->addRect(0,0,initialCell,initialCell,
                           QPen(cgRpgColour(activePalette(),flagFlashColour->value()),2),
                           QBrush(QColor(92,61,42,160)));
        marker->setFlag(QGraphicsItem::ItemIsMovable);
        marker->setFlag(QGraphicsItem::ItemIsSelectable);
        marker->setData(0,QStringLiteral("mapMarker"));marker->setData(1,name);
        marker->setZValue(20);
        marker->setPos(existing.contains(QStringLiteral("x"))?existing.value(QStringLiteral("x")).toInt():
                       80+(worldIndex%4)*140,
                       existing.contains(QStringLiteral("y"))?existing.value(QStringLiteral("y")).toInt():
                       80+(worldIndex/4)*100);
        auto *label=new QGraphicsSimpleTextItem(name,marker);
        label->setBrush(Qt::white);label->setPos(0,-19);
        flagCells.insert(name,existing.value(QStringLiteral("flagCell")).toInt(65535));
        flagsLarge.insert(name,existing.value(QStringLiteral("flag2x2")).toBool(false));
        markers.insert(name,marker);++worldIndex;
    }
    auto updateMarker=[&](const QString &name){
        auto *marker=markers.value(name,nullptr);if(!marker)return;
        marker->setPen(QPen(cgRpgColour(activePalette(),flagFlashColour->value()),2));
        const int tile=size->currentText().toInt();
        const bool two=flagsLarge.value(name,false);
        marker->setRect(0,0,two?2*tile:tile,two?2*tile:tile);
        for(QGraphicsItem *child:marker->childItems())
            if(child->data(0).toString()==QStringLiteral("flagImage"))delete child;
        if(sheet.isNull()||flagCells.value(name,65535)==65535)return;
        const int ac=sheet.width()/tile,index=flagCells.value(name);
        if(index<0||index>=ac*(sheet.height()/tile))return;
        for(int dy=0;dy<(two?2:1);++dy)for(int dx=0;dx<(two?2:1);++dx){
            if((index%ac)+dx>=ac||index+dy*ac+dx>=ac*(sheet.height()/tile))continue;
            auto *art=new QGraphicsPixmapItem(QPixmap::fromImage(sheet.copy(
                        ((index+dy*ac+dx)%ac)*tile,((index+dy*ac+dx)/ac)*tile,tile,tile)),marker);
            art->setPos(dx*tile,dy*tile);art->setData(0,QStringLiteral("flagImage"));
            art->setAcceptedMouseButtons(Qt::NoButton);
        }
    };
    auto paintCells=[&](const QPointF &point,bool erase){
        if(!paintMode->isChecked())return;
        const int tile=size->currentText().toInt();
        const int x=(int)std::floor(point.x()/tile),y=(int)std::floor(point.y()/tile);
        if(x<0||y<0||x>=columns||y>=rows)return;
        const int n=y*columns+x;
        const int chosen=erase?65535:index->value();
        if(!erase && (sheet.isNull()||chosen>=(sheet.width()/tile)*(sheet.height()/tile)))return;
        if(painted[n]==chosen)return;
        if(bucket->isChecked()){
            /* Bounded flood fill, iteratively, so a large sea doesn't overflow
               the UI thread's stack or flood across dissimilar terrain. */
            const int original=painted[n];
            /* Entire queue is allocated on the heap. No recursive calls,
             * call-stack growth or fixed-capacity neighbour arrays. */
            QVector<int> pending;pending.reserve(painted.size());pending.append(n);
            QVector<uint8_t> dirty(chunkItems.size(),0);
            painted[n]=chosen;dirty[sectionForCell(n)]=1u;
            while(!pending.isEmpty()){
                const int at=pending.takeLast();const int xx=at%columns,yy=at/columns;
                const int neighbours[4]={xx>0?at-1:-1,xx+1<columns?at+1:-1,
                                         yy>0?at-columns:-1,yy+1<rows?at+columns:-1};
                for(const int next:neighbours)if(next>=0 && painted[next]==original){
                    painted[next]=chosen;dirty[sectionForCell(next)]=1u;
                    pending.append(next);
                }
            }
            rebuildAnimatedSections();
            for(int section=0;section<dirty.size();++section)
                if(dirty[section])repaintSection(section);
            status->setText(QObject::tr("Bucket filled connected region from (%1, %2) with cell %3")
                .arg(x).arg(y).arg(chosen==65535?-1:chosen));
        } else {changeCell(n,chosen);updateTile(n);}
    };
    view->onPaint=paintCells;
    QObject::connect(fillEmpty,&QPushButton::clicked,&dialog,[&](){
        const int tile=size->currentText().toInt(),chosen=index->value();
        if(sheet.isNull() || chosen>=(sheet.width()/tile)*(sheet.height()/tile)){
            QMessageBox::information(&dialog,QObject::tr("Choose a tile"),
                QObject::tr("Choose a valid PPB atlas cell before filling the map."));return;
        }
        int count=0;
        QVector<uint8_t> dirty(chunkItems.size(),0);
        for(int n=0;n<painted.size();++n)if(painted[n]==65535){
            painted[n]=chosen;dirty[sectionForCell(n)]=1u;++count;
        }
        rebuildAnimatedSections();
        for(int section=0;section<dirty.size();++section)
            if(dirty[section])repaintSection(section);
        status->setText(QObject::tr("Filled %1 empty map cells. Use Flood fill to replace a connected region.").arg(count));
    });
    QObject::connect(flagChoose,&QPushButton::clicked,&dialog,[&](){
        if(sheet.isNull()){
            QMessageBox::information(&dialog,QObject::tr("Choose an atlas"),
                QObject::tr("Select a project PPB atlas for the world flag first."));return;
        }
        const int chosen=cgRpgChooseCell(&dialog,sheet,size->currentText().toInt(),flagCell->value());
        if(chosen<0)return;
        if(flagLarge->isChecked()){
            const int ac=sheet.width()/size->currentText().toInt();
            const int ar=sheet.height()/size->currentText().toInt();
            if((chosen%ac)+1>=ac || (chosen/ac)+1>=ar){
                QMessageBox::warning(&dialog,QObject::tr("2x2 flag"),
                    QObject::tr("Choose a top-left tile with room for two columns and two rows."));return;
            }
        }
        flagCell->setValue(chosen);
    });
    updateAnimPreview=[&](){
        if(sheet.isNull()){animPreview->clear();return;}
        const int tile=size->currentText().toInt();
        const int ac=sheet.width()/tile;
        const int total=ac*(sheet.height()/tile);
        const int base=index->value();
        if(base<0 || base>=total){animPreview->clear();return;}
        int cell=base;
        if(mapAnimations.contains(base))
            cell+=cgRpgMapAnimationFrame(mapAnimations.value(base),animationClock.elapsed()/20);
        animPreview->setPixmap(QPixmap::fromImage(sheet.copy((cell%ac)*tile,(cell/ac)*tile,tile,tile))
            .scaled(64,64,Qt::KeepAspectRatio,Qt::FastTransformation));
    };
    updateAnimControls=[&](){
        const int tile=size->currentText().toInt();
        const int total=sheet.isNull()?0:(sheet.width()/tile)*(sheet.height()/tile);
        const int cell=index->value();
        const bool valid=cell>=0 && cell<total;
        const bool defined=mapAnimations.contains(cell);
        const CgRpgMapAnimation a=mapAnimations.value(cell);
        animFrames->setMaximum(qMax(1,qMin(16,total-cell)));
        animFrames->setValue(defined?a.frames:qMin(4,animFrames->maximum()));
        animDelay->setValue(defined?a.ticks:5);
        animLoop->setChecked(defined?a.loop:true);
        animBounce->setChecked(defined?a.bounce:false);
        setAnimation->setEnabled(valid && cell+1<total);
        removeAnimation->setEnabled(defined);
        animStatus->setText(!valid?QObject::tr("Select a tile from the atlas."):
            defined?QObject::tr("Tile %1: animated (%2 frames). Every painted copy moves.").arg(cell).arg(a.frames):
            QObject::tr("Tile %1: static. Frames follow the atlas order.").arg(cell));
        updateAnimPreview();
    };
    QObject::connect(setAnimation,&QPushButton::clicked,&dialog,[&](){
        if(sheet.isNull())return;
        const int tile=size->currentText().toInt();
        const int total=(sheet.width()/tile)*(sheet.height()/tile);
        CgRpgMapAnimation a;
        a.cell=index->value();a.frames=animFrames->value();a.ticks=animDelay->value();
        a.loop=animLoop->isChecked();a.bounce=animBounce->isChecked();
        if(a.frames<2 || a.cell+a.frames>total)return;
        if(!mapAnimations.contains(a.cell) && mapAnimations.size()>=256){
            QMessageBox::warning(&dialog,QObject::tr("Too many animations"),
                QObject::tr("World Map supports at most 256 animated tiles."));return;
        }
        mapAnimations.insert(a.cell,a);
        previousFrames.remove(a.cell);
        rebuildAnimatedSections();
        for(int section:animatedSections.value(a.cell))repaintSection(section);
        updateAnimControls();
    });
    QObject::connect(removeAnimation,&QPushButton::clicked,&dialog,[&](){
        const int cell=index->value();
        const QSet<int> sections=animatedSections.value(cell);
        mapAnimations.remove(cell);previousFrames.remove(cell);
        rebuildAnimatedSections();
        for(int section:sections)repaintSection(section);
        updateAnimControls();
    });
    auto *animationTimer=new QTimer(&dialog);animationTimer->setInterval(40);
    QObject::connect(animationTimer,&QTimer::timeout,&dialog,[&](){
        const qint64 ticks=animationClock.elapsed()/20;
        for(auto it=mapAnimations.cbegin();it!=mapAnimations.cend();++it){
            const int frame=cgRpgMapAnimationFrame(it.value(),ticks);
            if(previousFrames.value(it.key(),-1)==frame)continue;
            previousFrames[it.key()]=frame;
            for(int section:animatedSections.value(it.key()))repaintSection(section);
        }
        if(mapAnimations.contains(index->value()))updateAnimPreview();
    });
    animationTimer->start();
    const auto loadAtlas=[&](){
        reloadPalette();
        updateBoundaryPreview();
        const bool ok=readSheet();
        palette->image=sheet;palette->cell=size->currentText().toInt();
        palette->index=index->value();palette->showAtlas();
        if(ok){
            const int count=(sheet.width()/palette->cell)*(sheet.height()/palette->cell);
            index->setMaximum(qMax(0,count-1));flagCell->setMaximum(qMax(0,count-1));
            status->setText(QObject::tr("%1 tiles available. Left paint, right erase. %2 painted cells.")
              .arg(count).arg(std::count_if(painted.cbegin(),painted.cend(),[](int t){return t!=65535;})));
        }
        repaintAllSections();
        for(const QString &name:worlds)updateMarker(name);
        updateAnimControls();
    };
    const auto updateSelection=[&](){
        const QString name=worldPick->currentText();
        if(name.isEmpty())return;
        flagCell->blockSignals(true);flagLarge->blockSignals(true);
        flagCell->setValue(flagCells.value(name,65535)==65535?0:flagCells.value(name));
        flagLarge->setChecked(flagsLarge.value(name,false));
        flagCell->blockSignals(false);flagLarge->blockSignals(false);
        for(auto it=markers.cbegin();it!=markers.cend();++it)
            it.value()->setSelected(it.key()==name);
    };
    QObject::connect(worldPick,qOverload<int>(&QComboBox::currentIndexChanged),&dialog,[=](int){updateSelection();});
    QObject::connect(flagCell,qOverload<int>(&QSpinBox::valueChanged),&dialog,[&](int v){
        const QString name=worldPick->currentText();if(name.isEmpty())return;
        flagCells[name]=v;updateMarker(name);
    });
    QObject::connect(flagLarge,&QCheckBox::toggled,&dialog,[&](bool b){
        const QString name=worldPick->currentText();if(name.isEmpty())return;
        flagsLarge[name]=b;updateMarker(name);
    });
    QObject::connect(scene,&QGraphicsScene::selectionChanged,&dialog,[&](){
        for(QGraphicsItem *item:scene->selectedItems()){
            if(item->data(0).toString()==QStringLiteral("mapMarker")){
                const int i=worldPick->findText(item->data(1).toString());
                if(i>=0 && i!=worldPick->currentIndex())worldPick->setCurrentIndex(i);
                break;
            }
        }
    });
    QObject::connect(atlasEdit,qOverload<int>(&QComboBox::currentIndexChanged),
                     &dialog,[&](int){loadAtlas();});
    QObject::connect(paletteChoice,qOverload<int>(&QComboBox::currentIndexChanged),
                     &dialog,[&](int){loadAtlas();});
    QObject::connect(flagFlashColour,qOverload<int>(&QSpinBox::valueChanged),
                     &dialog,[&](int){
        for(const QString &name:worlds)updateMarker(name);
    });
    palette->onCell=[&](int v){index->setValue(v);if(flagMode->isChecked())flagCell->setValue(v);};
    QObject::connect(index,qOverload<int>(&QSpinBox::valueChanged),&dialog,[&](int v){
        palette->index=v;palette->showAtlas();
        if(flagMode->isChecked() && !worldPick->currentText().isEmpty())flagCell->setValue(v);
        updateAnimControls();
    });
    const auto resizeMap=[&](int newTile){
        const int newCols=w->value()/newTile,newRows=h->value()/newTile;
        if(newCols<1||newRows<1)return;
        QVector<int> newPainted(newCols*newRows,65535);
        const int mx=qMin(columns,newCols),my=qMin(rows,newRows);
        for(int yy=0;yy<my;++yy)for(int xx=0;xx<mx;++xx)
            newPainted[yy*newCols+xx]=painted[yy*columns+xx];
        for(QGraphicsPixmapItem *item:chunkItems){scene->removeItem(item);delete item;}
        chunkItems.clear();chunkImages.clear();
        columns=newCols;rows=newRows;painted=newPainted;
        const int pixelWidth=columns*newTile,pixelHeight=rows*newTile;
        chunkColumns=(pixelWidth+chunkPixels-1)/chunkPixels;
        const int chunkRows=(pixelHeight+chunkPixels-1)/chunkPixels;
        for(int cy=0;cy<chunkRows;++cy)for(int cx=0;cx<chunkColumns;++cx){
            const int width=qMin(chunkPixels,pixelWidth-cx*chunkPixels);
            const int height=qMin(chunkPixels,pixelHeight-cy*chunkPixels);
            chunkImages.append(QImage(width,height,QImage::Format_ARGB32_Premultiplied));
            auto *item=scene->addPixmap(QPixmap());
            item->setPos(cx*chunkPixels,cy*chunkPixels);
            item->setZValue(0);item->setAcceptedMouseButtons(Qt::NoButton);
            chunkItems.append(item);
        }
        /* IMPORTANT: sectionForCell() uses chunkColumns. On initial open
           this used to run before chunkColumns was calculated (still 0),
           folding every animated map row into the first cache row. A brush
           stroke rebuilt it with valid geometry, making the entire map
           suddenly start animating. Rebuild only after the cache exists. */
        rebuildAnimatedSections();
        previousFrames.clear();
        view->cellSize=newTile;view->mapBounds=QRectF(0,0,pixelWidth,pixelHeight);
        scene->setSceneRect(-56,-56,columns*newTile+112,rows*newTile+112);
        view->setSceneRect(scene->sceneRect());view->viewport()->update();
        loadAtlas();
    };
    QObject::connect(w,qOverload<int>(&QSpinBox::valueChanged),&dialog,[&](int){resizeMap(size->currentText().toInt());});
    QObject::connect(h,qOverload<int>(&QSpinBox::valueChanged),&dialog,[&](int){resizeMap(size->currentText().toInt());});
    QObject::connect(size,&QComboBox::currentTextChanged,&dialog,[&](const QString &){
        // A tile-size change reinterprets the grid. Never silently reinterpret art.
        if(std::any_of(painted.cbegin(),painted.cend(),[](int v){return v!=65535;})){
            if(QMessageBox::question(&dialog,QObject::tr("Change map tile size?"),
                  QObject::tr("Changing cell size clears painted map tiles (world flags remain). Continue?"))
                  !=QMessageBox::Yes){
                size->blockSignals(true);size->setCurrentText(QString::number(view->cellSize));
                size->blockSignals(false);return;
            }
            std::fill(painted.begin(),painted.end(),65535);
        }
        resizeMap(size->currentText().toInt());
    });
    resizeMap(initialCell);updateSelection();
    view->centerOn(view->mapBounds.center());

    /* Save complete editable states, but commit a brush stroke only on mouse
       RELEASE, not once for every tile touched. The same history covers
       flood fills, flag placement/art, tile animations, size and palette. */
    auto *undoButton=new QPushButton(QObject::tr("Undo"),&dialog);
    auto *redoButton=new QPushButton(QObject::tr("Redo"),&dialog);
    undoButton->setToolTip(QObject::tr("Undo last World Map edit (Ctrl+Z)."));
    redoButton->setToolTip(QObject::tr("Redo last undone edit (Ctrl+Y or Ctrl+Shift+Z)."));
    auto captureState=[&](){
        CgRpgMapEditState state;
        state.width=w->value();state.height=h->value();
        state.tileSize=size->currentText().toInt();
        state.border=borderColour->value();state.flash=flagFlashColour->value();
        state.atlas=atlasEdit->currentData().toString();
        state.palette=paletteChoice->currentData().toString();
        state.tiles=painted;state.flags=flagCells;state.largeFlags=flagsLarge;
        state.animations=mapAnimations;
        for(auto it=markers.cbegin();it!=markers.cend();++it)
            state.positions.insert(it.key(),it.value()->pos());
        return state;
    };
    QVector<CgRpgMapEditState> undoHistory,redoHistory;
    CgRpgMapEditState lastState=captureState();
    bool restoringHistory=false;
    const auto refreshHistoryButtons=[&](){
        undoButton->setEnabled(!undoHistory.isEmpty());
        redoButton->setEnabled(!redoHistory.isEmpty());
    };
    /* Every snapshot represents the state BEFORE one complete edit. */
    const auto recordEdit=[&](){
        if(restoringHistory)return;
        CgRpgMapEditState now=captureState();
        if(now==lastState)return;
        if(undoHistory.size()>=64)undoHistory.removeFirst();
        undoHistory.append(lastState);
        redoHistory.clear();
        lastState=now;
        refreshHistoryButtons();
    };
    const auto restoreState=[&](const CgRpgMapEditState &state){
        restoringHistory=true;
        {
            const QSignalBlocker bw(w),bh(h),bs(size),ba(atlasEdit),bp(paletteChoice),
                                 bb(borderColour),bf(flagFlashColour);
            w->setValue(state.width);h->setValue(state.height);
            size->setCurrentText(QString::number(state.tileSize));
            atlasEdit->setCurrentIndex(atlasEdit->findData(state.atlas));
            paletteChoice->setCurrentIndex(paletteChoice->findData(state.palette));
            borderColour->setValue(state.border);flagFlashColour->setValue(state.flash);
        }
        mapAnimations=state.animations;
        previousFrames.clear();
        resizeMap(state.tileSize); /* Recreate chunk geometry if dimensions changed. */
        painted=state.tiles;
        flagCells=state.flags;flagsLarge=state.largeFlags;
        for(auto it=markers.cbegin();it!=markers.cend();++it)
            if(state.positions.contains(it.key()))it.value()->setPos(state.positions.value(it.key()));
        rebuildAnimatedSections();
        loadAtlas(); /* Also refreshes CLUT, markers, animation preview and chunks. */
        updateSelection();
        for(const QString &name:worlds)updateMarker(name);
        restoringHistory=false;
        lastState=captureState();
    };
    QObject::connect(undoButton,&QPushButton::clicked,&dialog,[&](){
        if(undoHistory.isEmpty())return;
        redoHistory.append(captureState());
        const CgRpgMapEditState prior=undoHistory.takeLast();
        restoreState(prior);refreshHistoryButtons();
    });
    QObject::connect(redoButton,&QPushButton::clicked,&dialog,[&](){
        if(redoHistory.isEmpty())return;
        undoHistory.append(captureState());
        const CgRpgMapEditState next=redoHistory.takeLast();
        restoreState(next);refreshHistoryButtons();
    });
    auto *undoShortcut=new QShortcut(QKeySequence::Undo,&dialog);
    QObject::connect(undoShortcut,&QShortcut::activated,undoButton,&QPushButton::click);
    auto *redoShortcut=new QShortcut(QKeySequence(Qt::CTRL|Qt::Key_Y),&dialog);
    QObject::connect(redoShortcut,&QShortcut::activated,redoButton,&QPushButton::click);
    auto *redoShiftShortcut=new QShortcut(QKeySequence(Qt::CTRL|Qt::SHIFT|Qt::Key_Z),&dialog);
    QObject::connect(redoShiftShortcut,&QShortcut::activated,redoButton,&QPushButton::click);
    view->onStrokeFinished=recordEdit;
    QObject::connect(fillEmpty,&QPushButton::clicked,&dialog,recordEdit);
    QObject::connect(setAnimation,&QPushButton::clicked,&dialog,recordEdit);
    QObject::connect(removeAnimation,&QPushButton::clicked,&dialog,recordEdit);
    QObject::connect(flagCell,qOverload<int>(&QSpinBox::valueChanged),&dialog,recordEdit);
    QObject::connect(flagLarge,&QCheckBox::toggled,&dialog,recordEdit);
    QObject::connect(w,qOverload<int>(&QSpinBox::valueChanged),&dialog,recordEdit);
    QObject::connect(h,qOverload<int>(&QSpinBox::valueChanged),&dialog,recordEdit);
    QObject::connect(size,&QComboBox::currentTextChanged,&dialog,recordEdit);
    QObject::connect(atlasEdit,qOverload<int>(&QComboBox::currentIndexChanged),&dialog,recordEdit);
    QObject::connect(paletteChoice,qOverload<int>(&QComboBox::currentIndexChanged),&dialog,recordEdit);
    QObject::connect(borderColour,qOverload<int>(&QSpinBox::valueChanged),&dialog,recordEdit);
    QObject::connect(flagFlashColour,qOverload<int>(&QSpinBox::valueChanged),&dialog,recordEdit);
    refreshHistoryButtons();

    /* Single compact bottom toolbar: canvas controls, history and Save/Cancel. */
    settings->addWidget(undoButton);settings->addWidget(redoButton);
    settings->addStretch();
    auto *buttons=new QDialogButtonBox(QDialogButtonBox::Save|QDialogButtonBox::Cancel,&dialog);
    settings->addWidget(buttons);
    root->addLayout(settings);
    QObject::connect(buttons,&QDialogButtonBox::accepted,&dialog,[&](){
        if(columns*rows>16384){
            QMessageBox::warning(&dialog,QObject::tr("Map too large"),
              QObject::tr("The map can contain at most 16,384 tiles. Reduce its width/height or use 16px tiles."));
            return;
        }
        if(!painted.isEmpty() &&
           std::any_of(painted.cbegin(),painted.cend(),[](int v){return v!=65535;}) && sheet.isNull()){
            QMessageBox::warning(&dialog,QObject::tr("No valid atlas"),
              QObject::tr("Please select a valid PPB atlas before saving painted tiles."));return;
        }
        const int atlasCount=sheet.isNull()?0:(sheet.width()/size->currentText().toInt())*
                         (sheet.height()/size->currentText().toInt());
        for(auto it=mapAnimations.cbegin();it!=mapAnimations.cend();++it){
            const CgRpgMapAnimation &a=it.value();
            if(a.cell<0 || a.cell+a.frames>atlasCount || a.frames<2){
                QMessageBox::warning(&dialog,QObject::tr("Invalid tile animation"),
                    QObject::tr("Animated tile %1 goes beyond the selected PPB atlas.").arg(a.cell));
                return;
            }
        }
        for(const QString &name:worlds){
            const int fc=flagCells.value(name,65535);
            if(fc==65535 || !flagsLarge.value(name,false) || sheet.isNull())continue;
            const int ac=sheet.width()/size->currentText().toInt();
            if((fc%ac)+1>=ac||fc+ac+1>=ac*(sheet.height()/size->currentText().toInt())){
                QMessageBox::warning(&dialog,QObject::tr("Invalid 2x2 flag"),
                    QObject::tr("Flag for '%1' must have room for a full 2x2 group in the atlas.").arg(name));return;
            }
        }
        dialog.accept();
    });
    QObject::connect(buttons,&QDialogButtonBox::rejected,&dialog,&QDialog::reject);
    dialog.showMaximized();
    if(dialog.exec()!=QDialog::Accepted)return false;
    QJsonArray points;
    for(auto it=markers.cbegin();it!=markers.cend();++it){
        const QPointF pos=it.value()->pos();
        const int tile=size->currentText().toInt();
        points.append(QJsonObject{{QStringLiteral("name"),it.key()},
             {QStringLiteral("x"),qBound(0,qRound(pos.x()/tile)*tile,columns*tile-tile)},
             {QStringLiteral("y"),qBound(0,qRound(pos.y()/tile)*tile,rows*tile-tile)},
             {QStringLiteral("flagCell"),flagCells.value(it.key(),65535)},
             {QStringLiteral("flag2x2"),flagsLarge.value(it.key(),false)}});
    }
    QJsonArray savedLayer;
    for(const int cell:painted)savedLayer.append(cell);
    QJsonArray savedAnimations;
    for(auto it=mapAnimations.cbegin();it!=mapAnimations.cend();++it){
        const CgRpgMapAnimation &a=it.value();
        savedAnimations.append(QJsonObject{{QStringLiteral("cell"),a.cell},
            {QStringLiteral("frames"),a.frames},{QStringLiteral("ticks"),a.ticks},
            {QStringLiteral("loop"),a.loop},{QStringLiteral("bounce"),a.bounce}});
    }
    return cgRpgWrite(path,QJsonObject{{QStringLiteral("version"),1},
         {QStringLiteral("width"),columns*size->currentText().toInt()},
         {QStringLiteral("height"),rows*size->currentText().toInt()},
         {QStringLiteral("tileSize"),size->currentText().toInt()},
         {QStringLiteral("atlas"),atlasEdit->currentData().toString()},
         {QStringLiteral("palette"),paletteChoice->currentData().toString()},
         {QStringLiteral("borderColour"),borderColour->value()},
         {QStringLiteral("flagFlashColour"),flagFlashColour->value()},
         {QStringLiteral("tiles"),savedLayer},{QStringLiteral("points"),points},
         {QStringLiteral("animations"),savedAnimations}},error);
}
#endif
