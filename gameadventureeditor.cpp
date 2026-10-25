#include "gameadventureeditor.h"
#include "ppbcodec.h"
#include "gametilemap.h"
#include "guidesigner_detail.h"
#include <QAbstractItemView>
#include <QComboBox>
#include <QFrame>
#include <QGuiApplication>
#include <QScreen>
#include <QPointer>
#include <QCheckBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QFont>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QImage>
#include <QJsonArray>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QListView>
#include <QTreeWidget>
#include <QTreeWidgetItemIterator>
#include <QInputDialog>
#include <QHash>
#include <QMap>
#include <QRegularExpression>
#include <QSet>
#include <QUuid>
#include <QMessageBox>
#include <QPixmap>
#include <QPainter>
#include <QPen>
#include <QPaintEvent>
#include <QPushButton>
#include <QScrollArea>
#include <QSpinBox>
#include <QTabWidget>
#include <QTableWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QFileInfo>
#include <QFile>
#include <QSaveFile>
#include <QDateTime>
#include <QDir>
#include <QDirIterator>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QMouseEvent>
#include <QScrollBar>
#include <QSlider>
#include <QStyle>
#include <QSignalBlocker>
#include <QTimer>
#include <QIcon>
#include <QSize>
#include <QStringList>
#include <QVector>
#include <QVariant>
#include <functional>
#include <array>
#include <algorithm>

namespace {
// Stage 5.117: tag ONLY controls whose availability follows prerequisites.
// The QApplication theme owns their green/red appearance; repaint after first
// tagging so controls created in already-visible dialogs acquire that style.
// Never modify saved widget values or business logic when changing appearance.
void adventureMarkDependent(QWidget *control)
{
    if (!control || control->property("adventureGuard").toBool()) return;
    control->setProperty("adventureGuard", true);
    control->style()->unpolish(control);
    control->style()->polish(control);
    control->update();
}

// Stage 5.4h: copies only one group of saved Adventure settings from another
// .sbgm. The source is read-only; NPCs, dialogue nodes and inventory never move.
struct AdventureSavedWorld {
    QString path;
    QString displayName;
    QJsonObject adventure;
    QJsonArray resources;
};

bool chooseAdventureSavedWorld(QWidget *parent, const QString &currentDesignPath,
                               const QString &section, const QStringList &requiredKeys,
                               AdventureSavedWorld *chosen)
{
    if (!chosen || currentDesignPath.isEmpty()) return false;
    const QDir project(QFileInfo(currentDesignPath).absolutePath());
    const QString current = QDir::cleanPath(QFileInfo(currentDesignPath).absoluteFilePath());
    QVector<AdventureSavedWorld> sources;
    QDirIterator it(project.absolutePath(), QStringList{QStringLiteral("*.sbgm")},
                    QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext() && sources.size() < 256) {
        const QString path = QDir::cleanPath(QFileInfo(it.next()).absoluteFilePath());
        if (path == current) continue;
        const QString relative = QDir::fromNativeSeparators(project.relativeFilePath(path));
        if (relative.startsWith(QStringLiteral(".codergirl/"))
            || relative.startsWith(QStringLiteral("worlds/"))
            || relative.startsWith(QStringLiteral("buildv1/"))) continue;
        QFile input(path);
        if (!input.open(QIODevice::ReadOnly) || input.size() > 16 * 1024 * 1024) continue;
        QJsonParseError error;
        const QJsonDocument document = QJsonDocument::fromJson(input.readAll(), &error);
        if (error.error != QJsonParseError::NoError || !document.isObject()) continue;
        const QJsonObject design = document.object();
        if (design.value(QStringLiteral("format")).toString()
                != QStringLiteral("SIDBOX-GAME-DESIGN")
            || design.value(QStringLiteral("version")).toInt() != 1) continue;
        const QJsonObject adventure = design.value(QStringLiteral("adventure")).toObject();
        bool hasSettings = false;
        for (const QString &key : requiredKeys)
            if (adventure.contains(key)) { hasSettings = true; break; }
        if (!hasSettings) continue;
        sources.append({path, relative, adventure,
                        design.value(QStringLiteral("resources")).toArray()});
    }
    if (sources.isEmpty()) {
        QMessageBox::information(parent, QObject::tr("Copy Adventure Settings"),
            QObject::tr("No other saved world has %1 settings to copy. "
                        "Save the source world first, then try again.").arg(section));
        return false;
    }
    std::sort(sources.begin(), sources.end(), [](const auto &a, const auto &b) {
        return a.displayName.compare(b.displayName, Qt::CaseInsensitive) < 0;
    });
    QStringList names;
    for (const auto &source : sources) names.append(source.displayName);
    bool ok = false;
    const QString name = QInputDialog::getItem(parent,
        QObject::tr("Copy %1 from Another World").arg(section),
        QObject::tr("Choose a SAVED .sbgm world (only %1 settings will be copied):")
            .arg(section), names, 0, false, &ok);
    if (!ok || name.isEmpty()) return false;
    const int index = names.indexOf(name);
    if (index < 0) return false;
    *chosen = sources[index];
    return true;
}

// Resource IDs are local to each world. Never paste one world's atlas ID into
// another world: match the resolved PPB path, then a unique resource name.
int matchAdventureAtlas(QWidget *parent, const AdventureSavedWorld &source,
                        const QVector<GameAdventureAsset> &atlases)
{
    const QString sourceId = source.adventure.value(QStringLiteral("skinAtlasId")).toString();
    if (sourceId.isEmpty()) return 0; // The source explicitly uses a simple box.
    QJsonObject sourceAsset;
    for (const QJsonValue &value : source.resources) {
        const QJsonObject asset = value.toObject();
        if (asset.value(QStringLiteral("id")).toString() == sourceId
            && asset.value(QStringLiteral("kind")).toString() == QStringLiteral("tileatlas")) {
            sourceAsset = asset;
            break;
        }
    }
    if (sourceAsset.isEmpty()) {
        QMessageBox::warning(parent, QObject::tr("Copy Dialogue Box Atlas"),
            QObject::tr("The source world no longer has the tile atlas used by its dialogue box."));
        return -1;
    }
    const QString resourcePath = sourceAsset.value(QStringLiteral("path")).toString();
    const QFileInfo sourceFile(QDir(QFileInfo(source.path).absolutePath()).filePath(resourcePath));
    const QString wanted = QDir::cleanPath(sourceFile.canonicalFilePath().isEmpty()
        ? sourceFile.absoluteFilePath() : sourceFile.canonicalFilePath());
    for (int i=0; i<atlases.size(); ++i) {
        const QFileInfo targetFile(atlases[i].path);
        const QString target = QDir::cleanPath(targetFile.canonicalFilePath().isEmpty()
            ? targetFile.absoluteFilePath() : targetFile.canonicalFilePath());
        if (!resourcePath.isEmpty() && wanted == target) return i + 1;
    }
    const QString name = sourceAsset.value(QStringLiteral("name")).toString();
    int match = -1;
    for (int i=0; i<atlases.size(); ++i) {
        if (!name.isEmpty() && atlases[i].name.compare(name, Qt::CaseInsensitive) == 0) {
            if (match >= 0) { match = -1; break; } // Ambiguous; don't guess.
            match = i;
        }
    }
    if (match >= 0) {
        const auto answer = QMessageBox::question(parent,
            QObject::tr("Confirm Dialogue Tile Atlas"),
            QObject::tr("The source and destination both have a Tile Atlas named '%1', "
                        "but their PPB file paths differ. Copy the settings using the "
                        "destination atlas '%2'? Verify the cell layout is identical.")
                .arg(name, atlases[match].path),
            QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        return answer == QMessageBox::Yes ? match + 1 : -1;
    }
    QMessageBox::information(parent, QObject::tr("Copy Dialogue Box Atlas"),
        QObject::tr("The source uses the atlas '%1', which isn't present in this world's "
                    "Tile Atlas resources. Import the same atlas into this world first, "
                    "then copy its settings again. No settings have been changed.")
            .arg(name.isEmpty() ? resourcePath : name));
    return -1;
}

// Qt 6.9+ replacement for QImage::mirrored(horizontal, vertical).
// Keep the original X/Y flip semantics for dialogue atlas cells.
QImage adventureFlippedCell(const QImage &image, bool flipX, bool flipY)
{
    Qt::Orientations orientations;
    if (flipX) orientations |= Qt::Horizontal;
    if (flipY) orientations |= Qt::Vertical;
    return orientations == Qt::Orientations{} ? image : image.flipped(orientations);
}

// Stage 4.30: visual selection works with full atlas coordinates, not an
// 8-bit index; the runtime handles 16-bit dialogue tile indices.
class AdventureAtlasGrid : public QWidget {
public:
    QImage source;
    int cellSize = 8, cellHeight = 8, zoom = 3, selectedIndex = 0;
    std::function<void(int)> changed;
    explicit AdventureAtlasGrid(QWidget *parent = nullptr) : QWidget(parent) {}
    void configure(const QImage &image, int tile, int tileY, int active) {
        source = image;
        cellSize = std::max(1,tile);
        cellHeight = std::max(1,tileY);
        zoom = cellSize < 12 ? 4 : cellSize <= 24 ? 3 : 2;
        selectedIndex = active;
        setFixedSize(source.width()*zoom, source.height()*zoom);
        update();
    }
protected:
    void paintEvent(QPaintEvent *) override {
        if (source.isNull()) return;
        QPainter painter(this);
        painter.setRenderHint(QPainter::SmoothPixmapTransform,false);
        painter.drawImage(rect(),source);
        const int w=cellSize*zoom;
        const int h=cellHeight*zoom;
        painter.setPen(QPen(QColor(90,90,90,190),1));
        for (int x=0;x<=width();x+=w) painter.drawLine(x,0,x,height());
        for (int y=0;y<=height();y+=h) painter.drawLine(0,y,width(),y);
        const int columns=source.width()/cellSize;
        if (columns && selectedIndex>=0) {
            painter.setPen(QPen(QColor(255,215,0),3));
            painter.drawRect(QRect((selectedIndex%columns)*w,(selectedIndex/columns)*h,w,h).adjusted(1,1,-2,-2));
        }
    }
    void mousePressEvent(QMouseEvent *event) override {
        if (source.isNull() || !cellSize) return;
        const int columns=source.width()/cellSize;
        const int rows=source.height()/cellHeight;
        if (!columns || !rows) return;
        const int x=int(event->position().x())/(cellSize*zoom);
        const int y=int(event->position().y())/(cellHeight*zoom);
        if (x<0 || x>=columns || y<0 || y>=rows) return;
        selectedIndex = y*columns+x;
        update();
        if(changed) changed(selectedIndex);
    }
};

/* Same canonical 8x8 glyphs and nearest-neighbour X/Y scale as the Title
   Screen designer. GUI Designer draws 8x16, so collapse its doubled rows
   before scaling, exactly as gametitlescreeneditor.cpp does. */
void adventureDrawGlyphs(QPainter &painter,int x,int y,const QString &text,
                         int sx,int sy,const QColor &colour,bool outlined=false,
                         const QColor &outlineColour=QColor(10,10,16))
{
    if(text.isEmpty())return;
    const QString latin=QString::fromLatin1(text.toLatin1());
    const int sourceWidth=8*latin.size();
    if(sourceWidth<=0)return;
    QImage doubled(sourceWidth,16,QImage::Format_ARGB32_Premultiplied);
    doubled.fill(Qt::transparent);
    { QPainter glyphPainter(&doubled);
      GuiDesignerDetail::drawCoderGirlText(glyphPainter,0,0,latin,Qt::white); }
    const QImage native=doubled.scaled(sourceWidth,8,Qt::IgnoreAspectRatio,Qt::FastTransformation);
    QImage scaled=native.scaled(sourceWidth*sx,8*sy,Qt::IgnoreAspectRatio,Qt::FastTransformation);
    { QPainter tint(&scaled);tint.setCompositionMode(QPainter::CompositionMode_SourceIn);
      tint.fillRect(scaled.rect(),colour); }
    if(outlined){
        QImage edge=scaled;
        { QPainter tint(&edge);tint.setCompositionMode(QPainter::CompositionMode_SourceIn);
          tint.fillRect(edge.rect(),outlineColour); }
        painter.drawImage(x-1,y,edge);painter.drawImage(x+1,y,edge);
        painter.drawImage(x,y-1,edge);painter.drawImage(x,y+1,edge);
    }
    painter.drawImage(x,y,scaled);
}

// SIDBOX uses native 8x8 glyphs with X/Y scale (default 8x16). Keep this estimator in step with
// game/adventureruntime.c: the dialogue box fits the speaker, body and the
// largest adjacent pair of answer labels (not all three at once).
QStringList adventurePreviewRows(const QString &text, int width, int limit=64)
{
    QStringList result;
    if (width < 1 || text.isEmpty()) return result;
    const QString source=text.left(512);
    int pos=0;
    width=std::min(width,60);
    while (pos<source.size() && result.size()<limit) {
        QString line;
        while (pos<source.size() && source[pos]!=QLatin1Char('\n') && line.size()<width)
            line+=source[pos++];
        if(line.size()==width && pos<source.size() &&
           source[pos]!=QLatin1Char(' ') && source[pos]!=QLatin1Char('\n')) {
            const int space=line.lastIndexOf(QLatin1Char(' '));
            if(space>=0) {
                pos-=line.size()-space;
                line=line.left(space);
            }
        }
        while(line.endsWith(QLatin1Char(' ')))line.chop(1);
        if(pos<source.size() && source[pos]==QLatin1Char('\n'))++pos;
        while(pos<source.size() && source[pos]==QLatin1Char(' '))++pos;
        result.append(line);
    }
    return result;
}
struct AdventurePreviewMetrics {
    int rows=0, answerHeight=0, needed=96, height=96;
    int bodyColumns=0, answerColumns=0, lineHeight=16;
    bool overflow=false;
};
AdventurePreviewMetrics adventureMeasure(const QJsonObject &node, int width,
                                        int minimumHeight, bool outlined, int padding,
                                        int scaleX=1,int scaleY=2)
{
    AdventurePreviewMetrics m;
    m.lineHeight=8*scaleY+(outlined?4:0);
    m.bodyColumns=std::clamp((width-2*padding)/(8*scaleX),1,50);
    m.answerColumns=std::clamp((width-2*padding-34*scaleX)/(8*scaleX),1,54);
    m.rows=adventurePreviewRows(node.value("text").toString().left(512),m.bodyColumns).size();
    const QJsonArray answers=node.value("choices").toArray();
    QVector<int> lengths;
    for (const QJsonValue &v:answers) {
        const QString text=v.toObject().value("text").toString().left(180);
        if(!text.isEmpty())lengths.append(adventurePreviewRows(text,m.answerColumns,32).size());
    }
    if(lengths.size()==1)m.answerHeight=lengths[0]*m.lineHeight;
    for(int i=0;i+1<lengths.size();++i)
        m.answerHeight=std::max(m.answerHeight,(lengths[i]+lengths[i+1])*m.lineHeight+4);
    // Match the generated runtime: reclaim eight unused vertical pixels
    // before the choices, or between the speaker and body with no choices.
    const int bottomInset=std::max(0,padding-8);
    m.needed=(m.answerHeight?m.lineHeight+8:m.lineHeight)+padding+bottomInset+m.rows*m.lineHeight+
        (m.answerHeight?1+m.answerHeight:0);
    m.height=std::min(320,std::max(minimumHeight-16,m.needed));
    m.overflow=m.needed>320;
    return m;
}

// Drag the yellow dialogue window directly on the SIDBOX 480x320 preview.
// No Q_OBJECT needed; parent updates the X/Y spinboxes through this callback.
class AdventureDialoguePositionPreview : public QLabel {
public:
    int frameX=20, frameY=148, frameW=440, frameH=162;
    int thoughtX=20,thoughtY=12,thoughtW=240,thoughtH=64;
    std::function<void(int,int)> moved;
    std::function<void(int,int)> movedThought;
    explicit AdventureDialoguePositionPreview(QWidget *parent=nullptr) : QLabel(parent) {
        setFixedSize(480,320);
        setCursor(Qt::OpenHandCursor);
    }
protected:
    bool dragging=false,thoughtDragging=false;
    int gripX=0,gripY=0;
public:
    bool thoughtAboveDialog=true;
protected:
    void reposition(const QPointF &point) {
        if(thoughtDragging){
            const int nx=std::clamp(int(point.x())-gripX,0,480-thoughtW);
            const int ny=std::clamp(int(point.y())-gripY,0,320-thoughtH);
            if(movedThought)movedThought(nx,ny);
        } else {
            const int nx=std::clamp(int(point.x())-gripX,0,480-frameW);
            const int ny=std::clamp(int(point.y())-gripY,0,320-frameH);
            if(moved)moved(nx,ny);
        }
    }
    void mousePressEvent(QMouseEvent *event) override {
        if(event->button()!=Qt::LeftButton)return;
        const int x=int(event->position().x()),y=int(event->position().y());
        const bool overThought=x>=thoughtX && y>=thoughtY &&
            x<thoughtX+thoughtW && y<thoughtY+thoughtH;
        const bool overDialogue=x>=frameX && y>=frameY &&
            x<frameX+frameW && y<frameY+frameH;
        thoughtDragging=overThought && (thoughtAboveDialog || !overDialogue);
        if(thoughtDragging){gripX=x-thoughtX;gripY=y-thoughtY;}
        else if(x>=frameX && y>=frameY && x<frameX+frameW && y<frameY+frameH){
            gripX=x-frameX;gripY=y-frameY;
        }else{gripX=frameW/2;gripY=frameH/2;}
        dragging=true;setCursor(Qt::ClosedHandCursor);
        reposition(event->position());
    }
    void mouseMoveEvent(QMouseEvent *event) override {
        if(dragging)reposition(event->position());
    }
    void mouseReleaseEvent(QMouseEvent *event) override {
        if(event->button()==Qt::LeftButton){dragging=false;thoughtDragging=false;setCursor(Qt::OpenHandCursor);}
    }
};

int chooseAdventureAtlasCell(QWidget *parent,const QImage &source,int tile,int previous,int limit=65536,int tileHeight=0) {
    const int effectiveHeight=tileHeight>0?tileHeight:tile;
    const int columns=source.width()/std::max(1,tile);
    const int rows=source.height()/std::max(1,effectiveHeight);
    if (source.isNull() || !columns || !rows) {
        QMessageBox::warning(parent,QObject::tr("Atlas picker"),QObject::tr("No valid indexed atlas cells are available."));
        return -1;
    }
    QDialog dialog(parent); dialog.setWindowTitle(QObject::tr("Select Atlas Cell"));
    dialog.resize(750,560);
    auto *v=new QVBoxLayout(&dialog);
    auto *info=new QLabel(&dialog);v->addWidget(info);
    auto *scroll=new QScrollArea(&dialog);scroll->setWidgetResizable(false);
    auto *grid=new AdventureAtlasGrid(scroll);
    grid->configure(source,tile,effectiveHeight,std::clamp(previous,0,std::min(columns*rows,limit)-1));
    scroll->setWidget(grid);v->addWidget(scroll,1);
    auto *buttons=new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel,&dialog);
    v->addWidget(buttons);
    auto updateLabel=[&](int idx) {
        info->setText(QObject::tr("Selected cell %1 of %2  (%3 columns × %4 rows)")
            .arg(idx).arg(columns*rows).arg(columns).arg(rows));
        adventureMarkDependent(buttons->button(QDialogButtonBox::Ok)); buttons->button(QDialogButtonBox::Ok)->setEnabled(idx<limit);
    };
    grid->changed=updateLabel;updateLabel(grid->selectedIndex);
    QObject::connect(buttons,&QDialogButtonBox::accepted,&dialog,&QDialog::accept);
    QObject::connect(buttons,&QDialogButtonBox::rejected,&dialog,&QDialog::reject);
    return dialog.exec()==QDialog::Accepted?grid->selectedIndex:-1;
}

int chooseAdventurePaletteIndex(QWidget *parent,const QVector<QRgb> &palette,int previous) {
    if (palette.size()!=256) {
        QMessageBox::information(parent,QObject::tr("Foreground palette"),
            QObject::tr("Select an active 256-colour foreground palette in World Designer first."));
        return -1;
    }
    QDialog dialog(parent);dialog.setWindowTitle(QObject::tr("Pick Foreground Palette Colour"));
    dialog.resize(665,575);
    auto *layout=new QVBoxLayout(&dialog);
    auto *hint=new QLabel(QObject::tr("Choose a foreground palette index. Index 0 is transparent."),&dialog);
    layout->addWidget(hint);
    auto *scroll=new QScrollArea(&dialog);scroll->setWidgetResizable(true);
    auto *content=new QWidget(scroll);auto *swatches=new QGridLayout(content);
    swatches->setSpacing(3);int chosen=previous;
    for (int i=0;i<256;++i) {
        auto *button=new QPushButton(content);
        button->setFixedSize(32,32);
        QPixmap px(23,23);px.fill(QColor::fromRgba(palette[i]));
        button->setIcon(QIcon(px));button->setIconSize(QSize(23,23));
        button->setToolTip(QObject::tr("Index %1 — RGB %2").arg(i)
            .arg(QColor::fromRgba(palette[i]).name()));
        if(i==previous) button->setStyleSheet(QStringLiteral("border: 2px solid #ffd600; border-radius:0px;"));
        swatches->addWidget(button,i/16,i%16);
        QObject::connect(button,&QPushButton::clicked,&dialog,[&,i]{chosen=i;dialog.accept();});
    }
    scroll->setWidget(content);layout->addWidget(scroll,1);
    auto *cancel=new QDialogButtonBox(QDialogButtonBox::Cancel,&dialog);
    layout->addWidget(cancel);
    QObject::connect(cancel,&QDialogButtonBox::rejected,&dialog,&QDialog::reject);
    return dialog.exec()==QDialog::Accepted?chosen:-1;
}

QImage indexedPreview(const QString &path,const QVector<QRgb> &palette) {
    SidboxPpb::Picture pic;QString error;
    if(!SidboxPpb::read(path,&pic,&error)) return QImage();
    QImage result=pic.indexed;
    if(result.format()==QImage::Format_Indexed8 && palette.size()==256) {
        QVector<QRgb> opaquePalette=palette;
        // Keep CLUT alpha 0 for transparent foreground cell 0 only.
        for (int i=1;i<opaquePalette.size();++i) opaquePalette[i]|=0xFF000000u;
        result.setColorTable(opaquePalette);
    }
    return result;
}
// Keep all four cells independent: artists can make a 16x16 inventory icon
// without introducing another atlas or a runtime sprite allocation.
QImage adventureInventoryIcon(const QImage &atlas, int tile, int single,
                              const QJsonArray &cells, bool stamp)
{
    if (atlas.isNull() || tile < 1) return {};
    const int columns = atlas.width()/tile, rows = atlas.height()/tile;
    if (!columns || !rows) return {};
    QImage image(stamp ? 2*tile : tile, stamp ? 2*tile : tile, QImage::Format_ARGB32);
    image.fill(Qt::transparent);
    QPainter paint(&image);
    const int parts = stamp ? 4 : 1;
    for (int i=0; i<parts; ++i) {
        const int cell = stamp && cells.size()==4 ? cells[i].toInt(65535) : single;
        if (cell < 0 || cell >= columns*rows) continue;
        paint.drawImage(QPoint(stamp ? (i%2)*tile : 0, stamp ? (i/2)*tile : 0),
                        atlas.copy((cell%columns)*tile,(cell/columns)*tile,tile,tile));
    }
    return image;
}
bool editAdventureInventoryIcon(QWidget *parent, const QVector<GameAdventureAsset> &atlases,
                                const QVector<QRgb> &foregroundPalette,
                                const QString &dialogueAtlasId, int dialogueTileSize,
                                QString *iconAtlasId, int *iconTileSize,
                                int *single, QJsonArray *cells, bool *stamp)
{
    if (!single || !cells || !stamp || !iconAtlasId || !iconTileSize) return false;
    QDialog dlg(parent);
    dlg.setWindowTitle(QObject::tr("Inventory Icon Artwork"));
    auto *layout = new QVBoxLayout(&dlg);
    auto *sourceRow = new QHBoxLayout;
    auto *atlasSelect = new QComboBox(&dlg);
    atlasSelect->addItem(QObject::tr("Dialogue PPB (legacy default)"),QString());
    for (const auto &resource : atlases) {
        if (QFileInfo(resource.path).suffix().compare(QStringLiteral("ppb"),Qt::CaseInsensitive)!=0)
            continue;
        atlasSelect->addItem(QStringLiteral("%1 (%2)").arg(resource.name,QFileInfo(resource.path).fileName()), resource.id);
    }
    if (!iconAtlasId->isEmpty() && atlasSelect->findData(*iconAtlasId)<0)
        atlasSelect->addItem(QObject::tr("Missing PPB resource (%1)").arg(*iconAtlasId),*iconAtlasId);
    atlasSelect->setCurrentIndex(qMax(0,atlasSelect->findData(*iconAtlasId)));
    auto *tileSize = new QSpinBox(&dlg);
    tileSize->setRange(4,64);
    tileSize->setValue(qBound(4,*iconTileSize,64));
    sourceRow->addWidget(new QLabel(QObject::tr("Icon PPB atlas:"),&dlg));
    sourceRow->addWidget(atlasSelect,1);
    sourceRow->addWidget(new QLabel(QObject::tr("Cell size:"),&dlg));
    sourceRow->addWidget(tileSize);
    layout->addLayout(sourceRow);
    auto *mode = new QComboBox(&dlg);
    mode->addItem(QObject::tr("Single atlas cell"),false);
    mode->addItem(QObject::tr("2×2 stamp (four independent cells)"),true);
    mode->setCurrentIndex(*stamp ? 1 : 0);
    layout->addWidget(mode);
    auto *hint = new QLabel(QObject::tr("Choose the PPB sheet this item uses when carried or dropped. "
                                      "Click a quadrant to pick a cell. Indices are preserved without making another PPB."),&dlg);
    hint->setWordWrap(true); layout->addWidget(hint);
    auto *grid = new QGridLayout;
    std::array<QPushButton *,4> buttons{};
    int chosen = *single;
    QJsonArray quadrants = *cells;
    if (quadrants.size()!=4) quadrants=QJsonArray{chosen,chosen,chosen,chosen};
    QImage image;
    int effectiveSize=8;
    auto *preview=new QLabel(&dlg);
    preview->setMinimumSize(110,110);
    preview->setAlignment(Qt::AlignCenter);
    const auto readAtlas=[&] {
        const QString id=atlasSelect->currentData().toString();
        const QString selected=id.isEmpty()?dialogueAtlasId:id;
        const auto it=std::find_if(atlases.begin(),atlases.end(),
            [&](const GameAdventureAsset &a){return a.id==selected;});
        adventureMarkDependent(tileSize); tileSize->setEnabled(!id.isEmpty()); // Default uses Dialogue tile size, not this override.
        effectiveSize=id.isEmpty()?dialogueTileSize:tileSize->value();
        image=it==atlases.end()?QImage():indexedPreview(it->path,foregroundPalette);
        if (!image.isNull() && (effectiveSize>image.width() || effectiveSize>image.height())) image=QImage();
    };
    const auto refresh = [&] {
        const bool composite = mode->currentData().toBool();
        for (int i=0; i<4; ++i) {
            buttons[i]->setVisible(composite || i==0);
            buttons[i]->setText(composite
                ? QObject::tr("%1: cell %2").arg(QStringList{
                    QObject::tr("Top left"), QObject::tr("Top right"),
                    QObject::tr("Bottom left"), QObject::tr("Bottom right")}[i])
                    .arg(quadrants[i].toInt(65535))
                : QObject::tr("Cell %1").arg(chosen));
        }
        const QImage icon = adventureInventoryIcon(image,effectiveSize,chosen,quadrants,composite);
        if (icon.isNull()) {
            preview->setPixmap(QPixmap());
            preview->setText(QObject::tr("Select a valid PPB atlas"));
        } else {
            preview->setText(QString());
            preview->setPixmap(QPixmap::fromImage(icon.scaled(
                96,96,Qt::KeepAspectRatio,Qt::FastTransformation)));
        }
    };
    for (int i=0;i<4;++i) {
        buttons[i]=new QPushButton(&dlg);
        grid->addWidget(buttons[i],i/2,i%2);
        QObject::connect(buttons[i],&QPushButton::clicked,&dlg,[&,i]{
            if(image.isNull()) {
                QMessageBox::information(&dlg,QObject::tr("Choose a PPB"),
                    QObject::tr("Choose a valid Icon PPB atlas first."));
                return;
            }
            const bool composite=mode->currentData().toBool();
            const int previous = composite ? quadrants[i].toInt(65535) : chosen;
            const int value = chooseAdventureAtlasCell(&dlg,image,effectiveSize,
                                  previous==65535?0:previous);
            if (value<0) return;
            if (composite) quadrants[i]=value;
            else chosen=value;
            refresh();
        });
    }
    layout->addLayout(grid);layout->addWidget(preview);
    auto *bottom=new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel,&dlg);
    layout->addWidget(bottom);
    QObject::connect(bottom,&QDialogButtonBox::accepted,&dlg,[&] {
        if (image.isNull()) {
            QMessageBox::warning(&dlg,QObject::tr("Inventory Icon"),
                QObject::tr("Choose a PPB resource present in this world."));
            return;
        }
        dlg.accept();
    });
    QObject::connect(bottom,&QDialogButtonBox::rejected,&dlg,&QDialog::reject);
    QObject::connect(mode,QOverload<int>::of(&QComboBox::currentIndexChanged),&dlg,[&](int){refresh();});
    QObject::connect(atlasSelect,QOverload<int>::of(&QComboBox::currentIndexChanged),&dlg,[&](int){
        // An atlas is a different index coordinate system: don't reuse old cell IDs.
        chosen=0; quadrants=QJsonArray{0,0,0,0}; readAtlas();refresh();
    });
    QObject::connect(tileSize,qOverload<int>(&QSpinBox::valueChanged),&dlg,[&](int){
        chosen=0; quadrants=QJsonArray{0,0,0,0}; readAtlas();refresh();
    });
    readAtlas();refresh();
    if (dlg.exec()!=QDialog::Accepted) return false;
    *single=chosen;
    *cells=quadrants;
    *stamp=mode->currentData().toBool();
    *iconAtlasId=atlasSelect->currentData().toString();
    *iconTileSize=tileSize->value();
    return true;
}
QTableWidgetItem *cell(const QString &s) { return new QTableWidgetItem(s); }
int intAt(QTableWidget *t, int r, int c, int fallback)
{
    if (!t->item(r,c)) return fallback;
    bool ok = false;
    int v = t->item(r,c)->text().trimmed().toInt(&ok);
    return ok ? v : fallback;
}
QJsonArray tableItems(QTableWidget *table)
{
    QJsonArray result;
    for (int r = 0; r < table->rowCount() && r < 64; ++r) {
        QJsonObject item;
        item.insert("name", table->item(r,0) ? table->item(r,0)->text().trimmed().left(36) : QString());
        if (item.value("name").toString().isEmpty()) continue;
        auto *kind= qobject_cast<QComboBox *>(table->cellWidget(r,1));
        item.insert("pickupKind",kind?kind->currentData().toInt():std::clamp(intAt(table,r,1,0),0,255));
        item.insert("capacity", std::clamp(intAt(table,r,2,1),1,65535));
        item.insert("initial", std::clamp(intAt(table,r,3,0),0,65535));
        item.insert("icon",table->item(r,4)
            ? std::clamp(table->item(r,4)->data(Qt::UserRole).toInt(),0,65535)
            : 65535);
        const auto *iconEntry = table->item(r,4);
        item.insert("iconCells",iconEntry ? iconEntry->data(Qt::UserRole+1).toJsonArray() : QJsonArray());
        item.insert("icon2x2",iconEntry && iconEntry->data(Qt::UserRole+2).toBool());
        item.insert("iconAtlasId",iconEntry ? iconEntry->data(Qt::UserRole+3).toString() : QString());
        item.insert("iconTileSize",iconEntry ? (iconEntry->data(Qt::UserRole+4).isValid() ? iconEntry->data(Qt::UserRole+4).toInt() : 8) : 8);
        auto *drop = qobject_cast<QCheckBox*>(table->cellWidget(r,5));
        item.insert("droppable",drop && drop->isChecked());
        auto *discard = qobject_cast<QCheckBox*>(table->cellWidget(r,6));
        item.insert("discardable",discard && discard->isChecked() && discard->isEnabled());
        auto *use=qobject_cast<QPushButton*>(table->cellWidget(r,7));
        item.insert("useStat",use ? use->property("useStat").toString() : QString());
        item.insert("useDelta",use ? use->property("useDelta").toInt() : 0);
        item.insert("useConsume",use ? use->property("useConsume").toBool() : true);
        result.append(item);
    }
    return result;
}
QJsonArray defaultChoices()
{
    QJsonArray choices;
    for (int i=0;i<3;++i) {
        QJsonObject c; c.insert("text", ""); c.insert("reply", "");
        c.insert("next", -1); c.insert("missingNext", -1); c.insert("requires", -1);
        c.insert("give", -1); c.insert("take", -1); c.insert("action", -1);
        choices.append(c);
    }
    return choices;
}
QString dialogueTitle(const QJsonObject &node, int index);
// Stage 5.70: folder-aware dialogue drop-down.  Keep the QComboBox's flat
// (label, numeric dialogue ID) model unchanged: every existing currentData(),
// findData() and currentIndexChanged user remains binary/source compatible.
// Only its popup is a searchable expandable tree, built from the *existing*
// editor-only dialogueFolders/folderId metadata.
class DialogueTreeCombo final : public QComboBox {
public:
    explicit DialogueTreeCombo(QWidget *parent, const QJsonArray *nodes,
                               const QJsonArray *folders)
        : QComboBox(parent), m_nodes(nodes), m_folders(folders) {}

    void showPopup() override {
        if (m_popup) { m_popup->raise(); m_popup->activateWindow(); return; }
        if (!m_nodes || !m_folders || count() == 0) { QComboBox::showPopup(); return; }
        auto *popup = new QFrame(this, Qt::Popup);
        popup->setAttribute(Qt::WA_DeleteOnClose);
        popup->setObjectName(QStringLiteral("dialogueTreePopup"));
        popup->setStyleSheet(QStringLiteral(
            "QFrame#dialogueTreePopup, QTreeWidget, QLineEdit { border-radius: 0px; }"));
        m_popup = popup;
        auto *layout = new QVBoxLayout(popup);
        layout->setContentsMargins(5,5,5,5);
        layout->setSpacing(4);
        auto *search = new QLineEdit(popup);
        search->setPlaceholderText(tr("Find dialogue, speaker or folder..."));
        search->setClearButtonEnabled(true);
        layout->addWidget(search);
        auto *tree = new QTreeWidget(popup);
        tree->setHeaderHidden(true);
        tree->setUniformRowHeights(true);
        tree->setSelectionMode(QAbstractItemView::SingleSelection);
        tree->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        layout->addWidget(tree,1);
        auto *help = new QLabel(tr("Expand folders, or type to search. Enter selects a dialogue."), popup);
        help->setWordWrap(true);
        layout->addWidget(help);
        QTreeWidgetItem *selected = nullptr;
        const QVariant chosenData = currentData();
        const int chosenRow = currentIndex();

        // Special actions such as "Close conversation" or "Use normal..."
        // remain at the top and retain their original negative IDs.
        for (int row=0; row<count(); ++row) {
            const int id=itemData(row).toInt();
            if (id>=0 && id<m_nodes->size()) continue;
            auto *entry = new QTreeWidgetItem(tree);
            entry->setText(0,itemText(row));
            entry->setData(0,Qt::UserRole,row);
            entry->setData(0,Qt::UserRole+1,QStringLiteral("node"));
            if (row==chosenRow) selected=entry;
        }
        QHash<QString,QTreeWidgetItem*> folderItems;
        QSet<QString> processed;
        // Resolve parent references independent of the saved array order;
        // invalid or cyclic parents fall back to the root of the popup.
        for (int pass=0; pass<=m_folders->size(); ++pass) {
            for (const QJsonValue &v : *m_folders) {
                const QJsonObject folder=v.toObject();
                const QString id=folder.value(QStringLiteral("id")).toString();
                const QString parentId=folder.value(QStringLiteral("parentId")).toString();
                if (id.isEmpty() || processed.contains(id)) continue;
                if (!parentId.isEmpty() && !folderItems.contains(parentId)
                    && pass<m_folders->size()) continue;
                auto *parent=folderItems.value(parentId,nullptr);
                auto *entry=parent ? new QTreeWidgetItem(parent) : new QTreeWidgetItem(tree);
                entry->setText(0,folder.value(QStringLiteral("name")).toString(tr("Unnamed folder")));
                entry->setIcon(0,QIcon::fromTheme(QStringLiteral("folder")));
                entry->setData(0,Qt::UserRole+1,QStringLiteral("folder"));
                folderItems.insert(id,entry);
                processed.insert(id);
            }
            if (processed.size()>=m_folders->size()) break;
        }
        auto *unfiled=new QTreeWidgetItem(tree);
        unfiled->setText(0,tr("Unfiled dialogues"));
        unfiled->setIcon(0,QIcon::fromTheme(QStringLiteral("folder-open")));
        unfiled->setData(0,Qt::UserRole+1,QStringLiteral("folder"));
        int unfiledCount=0;
        for(int row=0;row<count();++row) {
            const int id=itemData(row).toInt();
            if(id<0 || id>=m_nodes->size()) continue;
            const QString folderId=(*m_nodes)[id].toObject().value(QStringLiteral("folderId")).toString();
            auto *parent=folderItems.value(folderId,unfiled);
            if(parent==unfiled) ++unfiledCount;
            auto *entry=new QTreeWidgetItem(parent);
            entry->setText(0,itemText(row));
            entry->setData(0,Qt::UserRole,row);
            entry->setData(0,Qt::UserRole+1,QStringLiteral("node"));
            entry->setToolTip(0,tr("Dialogue ID %1").arg(id));
            if(row==chosenRow && itemData(row)==chosenData) selected=entry;
        }
        if(unfiledCount==0) delete unfiled;
        tree->collapseAll();
        if(selected) {
            for(auto *ancestor=selected->parent(); ancestor;ancestor=ancestor->parent())
                ancestor->setExpanded(true);
            tree->setCurrentItem(selected);
            tree->scrollToItem(selected);
        }
        const auto choose = [this,popup](QTreeWidgetItem *entry) {
            if(!entry || entry->data(0,Qt::UserRole+1).toString()!=QStringLiteral("node")) return;
            const int row=entry->data(0,Qt::UserRole).toInt();
            if(row>=0 && row<count()) setCurrentIndex(row);
            popup->close();
        };
        connect(tree,&QTreeWidget::itemClicked,popup,[choose](QTreeWidgetItem *entry,int){choose(entry);});
        connect(tree,&QTreeWidget::itemActivated,popup,[choose](QTreeWidgetItem *entry,int){choose(entry);});
        connect(search,&QLineEdit::textChanged,popup,[tree,selected](const QString &raw) {
            const QString query=raw.trimmed();
            // Folder-name matches reveal all of that folder's descendants.
            std::function<bool(QTreeWidgetItem*,bool)> apply = [&](QTreeWidgetItem *entry,bool parentMatch) {
                const bool self=parentMatch || entry->text(0).contains(query,Qt::CaseInsensitive);
                bool found=self;
                for(int i=0;i<entry->childCount();++i)
                    found=apply(entry->child(i),self) || found;
                entry->setHidden(!found);
                return found;
            };
            for(int i=0;i<tree->topLevelItemCount();++i) apply(tree->topLevelItem(i),false);
            if(!query.isEmpty()) tree->expandAll();
            else {
                tree->collapseAll();
                if(selected) for(auto *p=selected->parent();p;p=p->parent())p->setExpanded(true);
            }
        });
        connect(search,&QLineEdit::returnPressed,popup,[tree,choose]() {
            auto *current=tree->currentItem();
            if(current && !current->isHidden() && current->data(0,Qt::UserRole+1).toString()==QStringLiteral("node")) {
                choose(current);return;
            }
            // Pick the first visible dialogue in tree order.
            for(QTreeWidgetItemIterator it(tree);*it;++it) {
                auto *entry=*it;
                if(!entry->isHidden() && entry->data(0,Qt::UserRole+1).toString()==QStringLiteral("node")) {
                    choose(entry);return;
                }
            }
        });
        const QPoint anchor=mapToGlobal(QPoint(0,height()));
        const QScreen *screen=QGuiApplication::screenAt(anchor);
        const QRect space=screen ? screen->availableGeometry() : QRect(anchor,QSize(600,400));
        const int popW=qMin(qMax(width(),440),space.width());
        const int popH=qMin(390,space.height());
        const int left=qBound(space.left(),anchor.x(),space.right()-popW+1);
        int top=anchor.y();
        if(top+popH>space.bottom()+1)top=mapToGlobal(QPoint(0,0)).y()-popH;
        top=qBound(space.top(),top,space.bottom()-popH+1);
        popup->setGeometry(left,top,popW,popH);
        popup->show();
        search->setFocus();
    }
    void hidePopup() override {
        if(m_popup) m_popup->close();
        else QComboBox::hidePopup();
    }
private:
    const QJsonArray *m_nodes=nullptr;
    const QJsonArray *m_folders=nullptr;
    QPointer<QFrame> m_popup;
};
/* Stage 5.34: A single GIVE exchange editor instead of a graphical circuit
 * canvas. Up to four item predicates can be grouped as AND or OR. The
 * incremental AND option remembers hand-ins across world visits. */
QJsonObject editExchange(QWidget *parent, QJsonObject saved,
                         const QJsonArray &items, const QJsonArray &nodes,
                         const QVector<GameAdventureAsset> &objects, const QJsonArray &folders)
{
    QDialog dlg(parent);
    dlg.setWindowTitle(QObject::tr("NPC Item Exchange / Quest Requirements"));
    dlg.setMinimumSize(710,560);
    /* Keep the growing Adventure controls usable on laptop-sized screens. */
    QVBoxLayout *outerLayout=new QVBoxLayout(&dlg);
    auto *scroll=new QScrollArea(&dlg);
    scroll->setWidgetResizable(true);
    auto *contents=new QWidget(scroll);
    QVBoxLayout *layout=new QVBoxLayout(contents);
    auto *guardLegend=new QLabel(QObject::tr(
        "CONTROL STATUS: Green border = editable. Red border + faded background = disabled. "
        "Hover over a disabled field to see what must be set first."),contents);
    guardLegend->setWordWrap(true);
    layout->addWidget(guardLegend);
    scroll->setWidget(contents);
    outerLayout->addWidget(scroll,1);
    QCheckBox *enabled=new QCheckBox(QObject::tr("Selecting this answer opens inventory in GIVE mode"),&dlg);
    enabled->setChecked(saved.value("enabled").toBool(false));
    layout->addWidget(enabled);
    QLabel *help=new QLabel(QObject::tr(
        "All owned items are shown without hints. Wrong offers are never consumed. "
        "ALL = all required items; ANY = one matching item. In incremental ALL, "
        "the NPC remembers delivered parts when you revisit or change worlds."),&dlg);
    help->setWordWrap(true); layout->addWidget(help);
    QFormLayout *modeForm=new QFormLayout;
    QComboBox *logic=new QComboBox(&dlg);
    logic->addItem(QObject::tr("ALL of these items (AND)"),QStringLiteral("all"));
    logic->addItem(QObject::tr("ANY one item (OR)"),QStringLiteral("any"));
    logic->setCurrentIndex(qMax(0,logic->findData(saved.value("logic").toString("all"))));
    modeForm->addRow(QObject::tr("Requirements"),logic);
    QCheckBox *incremental=new QCheckBox(QObject::tr("Accept one item per visit; remember previous hand-ins"),&dlg);
    incremental->setChecked(saved.value("incremental").toBool(false));
    modeForm->addRow(QObject::tr("Hand-ins"),incremental);
    QCheckBox *consume=new QCheckBox(QObject::tr("Consume accepted items"),&dlg);
    consume->setChecked(saved.value("consume").toBool(true));
    modeForm->addRow(QObject::tr("Inventory"),consume);
    layout->addLayout(modeForm);
    auto *requirements=new QGroupBox(QObject::tr("Requested items (maximum four)"),&dlg);
    auto *reqForm=new QFormLayout(requirements);
    QComboBox *itemSlots[4];
    const QJsonArray req=saved.value("items").toArray();
    for(int i=0;i<4;++i) {
        itemSlots[i]=new QComboBox(requirements);
        itemSlots[i]->addItem(QObject::tr("None"),-1);
        for(int k=0;k<items.size();++k)
            itemSlots[i]->addItem(QStringLiteral("%1: %2").arg(k)
                .arg(items[k].toObject().value("name").toString()),k);
        itemSlots[i]->setCurrentIndex(qMax(0,itemSlots[i]->findData(i<req.size()?req[i].toInt(-1):-1)));
        reqForm->addRow(QObject::tr("Item %1").arg(i+1),itemSlots[i]);
    }
    layout->addWidget(requirements);
    auto *response=new QGroupBox(QObject::tr("Responses & optional actions"),&dlg);
    auto *responseForm=new QFormLayout(response);
    auto makeNode=[&](const char *key, QWidget *owner=nullptr) {
        QComboBox *combo=new DialogueTreeCombo(owner ? owner : response,&nodes,&folders);
        combo->addItem(QObject::tr("Keep current NPC dialogue"),-1);
        for (int i=0;i<nodes.size();++i)
            combo->addItem(dialogueTitle(nodes[i].toObject(),i),i);
        combo->setCurrentIndex(qMax(0,combo->findData(saved.value(QLatin1String(key)).toInt(-1))));
        return combo;
    };
    // DECLARATION of dialogueTitle appears below this editor in older versions;
    // use its local presentation so item exchanges remain independent.
    QComboBox *wrong=makeNode("wrongNext");
    responseForm->addRow(QObject::tr("Wrong item → dialogue"),wrong);
    struct Event { QComboBox *kind; QSpinBox *number; QComboBox *mode; } events[1];
    const char *numberKeys[]={"wrongAction","partialAction"};
    const char *targetKeys[]={"wrongTargetObjectId","partialTargetObjectId"};
    const char *modeKeys[]={"wrongTargetAction","partialTargetAction"};
    for(int i=0;i<1;++i) {
        QWidget *line=new QWidget(response); QHBoxLayout *row=new QHBoxLayout(line);
        row->setContentsMargins(0,0,0,0);
        events[i].kind=new QComboBox(line);
        events[i].kind->addItem(QObject::tr("No action"),QStringLiteral("none"));
        for(const auto &obj:objects)
            events[i].kind->addItem(QObject::tr("Game Object: %1").arg(obj.name),obj.id);
        events[i].kind->addItem(QObject::tr("Custom event ID"),QStringLiteral("custom"));
        const QString obj=saved.value(QLatin1String(targetKeys[i])).toString();
        const int action=saved.value(QLatin1String(numberKeys[i])).toInt(-1);
        const QString prev=!obj.isEmpty()?obj:action>=0?QStringLiteral("custom"):QStringLiteral("none");
        events[i].kind->setCurrentIndex(qMax(0,events[i].kind->findData(prev)));
        events[i].number=new QSpinBox(line); events[i].number->setRange(0,29999);
        events[i].number->setValue(qMax(0,action));
        events[i].mode=new QComboBox(line);
        events[i].mode->addItem(QObject::tr("Activate"),QStringLiteral("enable"));
        events[i].mode->addItem(QObject::tr("Deactivate"),QStringLiteral("disable"));
        events[i].mode->addItem(QObject::tr("Toggle"),QStringLiteral("toggle"));
        events[i].mode->setCurrentIndex(qMax(0,events[i].mode->findData(
            saved.value(QLatin1String(modeKeys[i])).toString("enable"))));
        row->addWidget(events[i].kind,1);row->addWidget(events[i].number);row->addWidget(events[i].mode);
        auto refresh=[=](){
            const QString kind=events[i].kind->currentData().toString();
            events[i].number->setVisible(kind==QStringLiteral("custom"));
            events[i].mode->setVisible(kind!=QStringLiteral("none") && kind!=QStringLiteral("custom"));
        };
        QObject::connect(events[i].kind,QOverload<int>::of(&QComboBox::currentIndexChanged),line,[refresh](int){refresh();});
        refresh();
        responseForm->addRow(QObject::tr("Wrong item action"),line);
    }
    layout->addWidget(response);
    auto *repeated=new QGroupBox(QObject::tr("Repeated WRONG item (optional puzzle clue)"),&dlg);
    auto *repeatForm=new QFormLayout(repeated);
    QCheckBox *repeatEnabled=new QCheckBox(QObject::tr("Give one wrong item escalating dialogue on repeated offers"),repeated);
    repeatEnabled->setChecked(saved.value("wrongRepeatEnabled").toBool(false));
    repeatForm->addRow(repeatEnabled);
    auto *repeatItem=new QComboBox(repeated);
    repeatItem->addItem(QObject::tr("Choose an item..."),-1);
    for (int i=0;i<items.size();++i)
        repeatItem->addItem(QStringLiteral("%1: %2").arg(i).arg(items[i].toObject().value("name").toString()),i);
    repeatItem->setCurrentIndex(qMax(0,repeatItem->findData(saved.value("wrongRepeatItem").toInt(-1))));
    repeatForm->addRow(QObject::tr("Wrong item to remember"),repeatItem);
    const char *repeatKeys[]={"wrongRepeatFirst","wrongRepeatSecond","wrongRepeatThird","wrongRepeatLater"};
    const char *repeatLabels[]={"First offer dialogue","Second offer dialogue","Third offer (clue) dialogue","Fourth+ offer dialogue"};
    QComboBox *repeatNodes[4];
    for(int i=0;i<4;++i) {
        repeatNodes[i]=makeNode(repeatKeys[i],repeated);
        repeatForm->addRow(QObject::tr(repeatLabels[i]),repeatNodes[i]);
    }
    auto *repeatActionLine=new QWidget(repeated);
    auto *repeatActionRow=new QHBoxLayout(repeatActionLine);
    repeatActionRow->setContentsMargins(0,0,0,0);
    QComboBox *repeatActionKind=new QComboBox(repeatActionLine);
    repeatActionKind->addItem(QObject::tr("No action"),QStringLiteral("none"));
    for (const auto &obj:objects) repeatActionKind->addItem(QObject::tr("Game Object: %1").arg(obj.name),obj.id);
    repeatActionKind->addItem(QObject::tr("Custom event ID"),QStringLiteral("custom"));
    const QString repeatTarget=saved.value("wrongRepeatTargetObjectId").toString();
    const int repeatEvent=saved.value("wrongRepeatAction").toInt(-1);
    repeatActionKind->setCurrentIndex(qMax(0,repeatActionKind->findData(!repeatTarget.isEmpty()
        ? repeatTarget : repeatEvent>=0 ? QStringLiteral("custom") : QStringLiteral("none"))));
    QSpinBox *repeatEventId=new QSpinBox(repeatActionLine);
    repeatEventId->setRange(0,29999);repeatEventId->setValue(qMax(0,repeatEvent));
    QComboBox *repeatActionMode=new QComboBox(repeatActionLine);
    repeatActionMode->addItem(QObject::tr("Activate"),QStringLiteral("enable"));
    repeatActionMode->addItem(QObject::tr("Deactivate"),QStringLiteral("disable"));
    repeatActionMode->addItem(QObject::tr("Toggle"),QStringLiteral("toggle"));
    repeatActionMode->setCurrentIndex(qMax(0,repeatActionMode->findData(saved.value("wrongRepeatTargetAction").toString("enable"))));
    repeatActionRow->addWidget(repeatActionKind,1);
    repeatActionRow->addWidget(repeatEventId);
    repeatActionRow->addWidget(repeatActionMode);
    repeatForm->addRow(QObject::tr("Action on third offer (once)"),repeatActionLine);
    auto *repeatDoorHint=new QLabel(QObject::tr(
        "For a Door / Solid blocker: Deactivate opens/removes the barrier; "
        "Activate makes it solid/visible. A solid tilemap tile remains blocked "
        "even when the Game Object is deactivated."),repeated);
    repeatDoorHint->setWordWrap(true);
    repeatForm->addRow(repeatDoorHint);
    // Dependencies are presentation-only: unchecked/disabled settings retain
    // their saved values and become editable again when prerequisites return.
    auto *exchangeWarning=new QLabel(&dlg);
    exchangeWarning->setWordWrap(true);
    exchangeWarning->setVisible(false);
    layout->addWidget(exchangeWarning);
    auto refreshExchangeControls=[=]() {
        const bool active=enabled->isChecked();
        const QString enableHint=QObject::tr("Disabled: tick 'Selecting this answer opens inventory in GIVE mode' first.");
        const auto gate=[&](QWidget *control, bool allowed, const QString &reason) {
            adventureMarkDependent(control); control->setEnabled(allowed);
            control->setToolTip(allowed ? QObject::tr("Used by this GIVE exchange.") : reason);
        };
        gate(logic,active,enableHint);
        gate(consume,active,enableHint);
        int required=0;
        for (QComboBox *slot : itemSlots) {
            gate(slot,active,enableHint);
            if(slot->currentData().toInt()>=0) ++required;
        }
        const bool canIncrement=active && logic->currentData().toString()==QStringLiteral("all") && required>=2;
        gate(incremental,canIncrement,!active ? enableHint
            : QObject::tr("Disabled: incremental hand-ins need ALL (AND) and at least two required items."));
        const bool ready=active && required>0;
        const QString itemHint=QObject::tr("Disabled: add a requested item to this GIVE exchange first.");
        gate(wrong,ready,!active ? enableHint : itemHint);
        for (const Event &event : events) {
            gate(event.kind,ready,!active ? enableHint : itemHint);
            const QString kind=event.kind->currentData().toString();
            event.number->setVisible(kind==QStringLiteral("custom"));
            event.mode->setVisible(kind!=QStringLiteral("none") && kind!=QStringLiteral("custom"));
            gate(event.number,ready && kind==QStringLiteral("custom"),
                 !ready ? (!active ? enableHint : itemHint)
                 : QObject::tr("Disabled: select Custom event ID first."));
            gate(event.mode,ready && kind!=QStringLiteral("none") && kind!=QStringLiteral("custom"),
                 !ready ? (!active ? enableHint : itemHint)
                 : QObject::tr("Disabled: choose a Game Object action first."));
        }
        gate(repeatEnabled,active && required>0,!active ? enableHint
            : QObject::tr("Disabled: select at least one requested item above before configuring repeated wrong offers."));
        const bool repeat=active && required>0 && repeatEnabled->isChecked();
        const QString repeatHint=!active ? enableHint : required==0
            ? QObject::tr("Disabled: select at least one requested item first.")
            : QObject::tr("Disabled: tick 'Give one wrong item escalating dialogue' first.");
        gate(repeatItem,repeat,repeatHint);
        for(QComboBox *node:repeatNodes)gate(node,repeat,repeatHint);
        gate(repeatActionKind,repeat,repeatHint);
        const QString repeatKind=repeatActionKind->currentData().toString();
        repeatEventId->setVisible(repeatKind==QStringLiteral("custom"));
        repeatActionMode->setVisible(repeatKind!=QStringLiteral("none") && repeatKind!=QStringLiteral("custom"));
        gate(repeatEventId,repeat && repeatKind==QStringLiteral("custom"),
             !repeat ? repeatHint : QObject::tr("Disabled: select Custom event ID first."));
        gate(repeatActionMode,repeat && repeatKind!=QStringLiteral("none") && repeatKind!=QStringLiteral("custom"),
             !repeat ? repeatHint : QObject::tr("Disabled: choose a Game Object action first."));
        QStringList issues;
        if (active && required==0)
            issues << QObject::tr("Add at least one requested item before this exchange can run.");
        QSet<int> uniqueItems;
        for (QComboBox *slot:itemSlots) {
            const int id=slot->currentData().toInt();
            if (id<0)continue;
            if (uniqueItems.contains(id))
                issues << QObject::tr("The same item is selected twice. It counts only once.");
            uniqueItems.insert(id);
        }
        if (repeat) {
            const int wrongId=repeatItem->currentData().toInt();
            if (wrongId<0)
                issues << QObject::tr("Repeated wrong offers need a Wrong item to remember.");
            else if (uniqueItems.contains(wrongId))
                issues << QObject::tr("The repeated WRONG item cannot also be a requested item.");
        }
        exchangeWarning->setText(issues.isEmpty() ? QString()
            : QObject::tr("Check GIVE flow: %1").arg(issues.join(QStringLiteral("  "))));
        exchangeWarning->setVisible(!issues.isEmpty());
    };
    QObject::connect(enabled,&QCheckBox::toggled,&dlg,[=](bool){refreshExchangeControls();});
    QObject::connect(logic,QOverload<int>::of(&QComboBox::currentIndexChanged),&dlg,[=](int){refreshExchangeControls();});
    for(QComboBox *slot:itemSlots)
        QObject::connect(slot,QOverload<int>::of(&QComboBox::currentIndexChanged),&dlg,[=](int){refreshExchangeControls();});
    QObject::connect(repeatEnabled,&QCheckBox::toggled,&dlg,[=](bool){refreshExchangeControls();});
    QObject::connect(repeatItem,QOverload<int>::of(&QComboBox::currentIndexChanged),&dlg,[=](int){refreshExchangeControls();});
    QObject::connect(events[0].kind,QOverload<int>::of(&QComboBox::currentIndexChanged),&dlg,[=](int){refreshExchangeControls();});
    QObject::connect(repeatActionKind,QOverload<int>::of(&QComboBox::currentIndexChanged),&dlg,[=](int){refreshExchangeControls();});
    refreshExchangeControls();
    layout->addWidget(repeated);
    QLabel *success=new QLabel(QObject::tr("Success uses this dialogue choice's existing Next, "
        "event, item reward and NPC-completed settings."),&dlg);
    success->setWordWrap(true);layout->addWidget(success);
    QDialogButtonBox *buttons=new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel,&dlg);
    outerLayout->addWidget(buttons);
    QObject::connect(buttons,&QDialogButtonBox::accepted,&dlg,[&](){
        QJsonArray chosen;
        QSet<int> unique;
        for(QComboBox *slot:itemSlots){
            const int index=slot->currentData().toInt();
            if(index>=0 && !unique.contains(index)){ unique.insert(index);chosen.append(index); }
        }
        if(enabled->isChecked() && chosen.isEmpty()){
            QMessageBox::warning(&dlg,QObject::tr("GIVE Requirements"),
                QObject::tr("Select at least one item before enabling an exchange."));
            return;
        }
        if(enabled->isChecked()) {
            int selectedCount=0;
            for (QComboBox *slot:itemSlots)
                if (slot->currentData().toInt()>=0) ++selectedCount;
            if (selectedCount!=chosen.size()) {
                QMessageBox::warning(&dlg,QObject::tr("Duplicate GIVE Items"),
                    QObject::tr("The same requested item is selected more than once. "
                                "Use different items or set the extra slot to None."));
                return;
            }
        }
        // A remembered checkbox is inactive while GIVE is off. Never reject
        // an unrelated edit because an unavailable old option was left set.
        if(enabled->isChecked() && repeatEnabled->isChecked()) {
            const int tracked=repeatItem->currentData().toInt();
            if(!enabled->isChecked() || tracked<0) {
                QMessageBox::warning(&dlg,QObject::tr("Repeated Wrong Item"),
                    QObject::tr("Enable GIVE and choose the wrong item to track."));
                return;
            }
            if(unique.contains(tracked)) {
                QMessageBox::warning(&dlg,QObject::tr("Repeated Wrong Item"),
                    QObject::tr("Choose an item NOT requested by this exchange. Required items follow the normal hand-in path."));
                return;
            }
        }
        dlg.accept();
    });
    QObject::connect(buttons,&QDialogButtonBox::rejected,&dlg,&QDialog::reject);
    if(dlg.exec()!=QDialog::Accepted) return saved;
    QJsonArray chosen;QSet<int> unique;
    for(QComboBox *slot:itemSlots){
        const int index=slot->currentData().toInt();
        if(index>=0 && !unique.contains(index)){ unique.insert(index);chosen.append(index); }
    }
    saved.insert("items",chosen);
    saved.insert("enabled",enabled->isChecked());
    saved.insert("logic",logic->currentData().toString());
    saved.insert("incremental",incremental->isChecked());
    saved.insert("consume",consume->isChecked());
    saved.insert("wrongNext",wrong->currentData().toInt());
    saved.insert("wrongRepeatEnabled",repeatEnabled->isChecked());
    saved.insert("wrongRepeatItem",repeatItem->currentData().toInt());
    for(int i=0;i<4;++i)
        saved.insert(QLatin1String(repeatKeys[i]),repeatNodes[i]->currentData().toInt());
    const QString repeatKind=repeatActionKind->currentData().toString();
    saved.insert("wrongRepeatAction",repeatKind==QStringLiteral("custom") ? repeatEventId->value() : -1);
    saved.insert("wrongRepeatTargetObjectId",repeatKind==QStringLiteral("none") || repeatKind==QStringLiteral("custom")
        ? QString() : repeatKind);
    saved.insert("wrongRepeatTargetAction",repeatActionMode->currentData().toString());
    /* Retire the old partial dialogue; existing quest hand-in state remains. */
    saved.insert("partialNext",-1);
    saved.insert("partialAction",-1);
    saved.insert("partialTargetObjectId",QString());
    for(int i=0;i<1;++i){
        const QString kind=events[i].kind->currentData().toString();
        saved.insert(QLatin1String(numberKeys[i]),kind==QStringLiteral("custom") ? events[i].number->value() : -1);
        saved.insert(QLatin1String(targetKeys[i]),kind==QStringLiteral("custom")||kind==QStringLiteral("none") ? QString() : kind);
        saved.insert(QLatin1String(modeKeys[i]),events[i].mode->currentData().toString());
    }
    return saved;
}

QString dialogueTitle(const QJsonObject &node, int index)
{
    return QStringLiteral("%1: %2 — %3").arg(index)
        .arg(node.value("speaker").toString().left(24), node.value("text").toString().left(35));
}
void editNode(QWidget *parent, QJsonArray &nodes, int row, const QJsonArray &items,
              const QVector<GameAdventureAsset> &objects, QTableWidget *npcTable,
              const QJsonArray &folders, const QString &currentDesignFilePath)
{
    if (row < 0 || row >= nodes.size()) return;
    QJsonObject node = nodes[row].toObject();
    QDialog dialog(parent); dialog.setWindowTitle(QObject::tr("Dialogue Node %1").arg(row));
    dialog.setMinimumSize(820, 680); dialog.resize(1010, 815);
    /* World-qualified NPC appearance targets. The saved target contains the
       stable sprite ID, not a fragile table row; visual labels contain world
       and instance indices so two BigSteves are unmistakable. */
    auto appendNpcTargets = [npcTable,&currentDesignFilePath](QComboBox *target) {
        if (npcTable) for (int n=0; n<npcTable->rowCount(); ++n) {
            const QTableWidgetItem *entry=npcTable->item(n,0);
            if (entry) target->addItem(QObject::tr("%1 [local %2]").arg(entry->text()).arg(n),
                                       entry->data(Qt::UserRole).toString());
        }
        if (currentDesignFilePath.isEmpty()) return;
        const QDir folder(QFileInfo(currentDesignFilePath).absolutePath());
        const QString thisWorld=sidboxTilemapWorldBaseName(currentDesignFilePath);
        for (const QFileInfo &file : folder.entryInfoList(
                 QStringList{QStringLiteral("*.sbgm")},QDir::Files,QDir::Name)) {
            const QString world=sidboxTilemapWorldBaseName(file.absoluteFilePath());
            if (world==thisWorld) continue;
            QFile input(file.absoluteFilePath());
            if (!input.open(QIODevice::ReadOnly) || input.size()>16*1024*1024) continue;
            const QJsonObject design=QJsonDocument::fromJson(input.readAll()).object();
            const QJsonArray others=design.value(QStringLiteral("adventure")).toObject()
                .value(QStringLiteral("npcs")).toArray();
            const QJsonArray resources=design.value(QStringLiteral("resources")).toArray();
            for (int n=0;n<others.size();++n) {
                const QString id=others[n].toObject().value(QStringLiteral("spriteId")).toString();
                if (id.isEmpty()) continue;
                QString name=id;
                for (const QJsonValue &v : resources) {
                    const QJsonObject sprite=v.toObject();
                    if (sprite.value(QStringLiteral("id")).toString()==id) {
                        name=sprite.value(QStringLiteral("name")).toString(id);break;
                    }
                }
                target->addItem(QObject::tr("%1: %2 [%3]").arg(world,name).arg(n),
                                QStringLiteral("@npc:%1:%2").arg(world,id));
            }
        }
    };
    auto *main = new QVBoxLayout(&dialog);
    auto *scroll = new QScrollArea(&dialog);
    scroll->setWidgetResizable(true);
    auto *content = new QWidget(scroll);
    auto *detail = new QVBoxLayout(content);
    auto *guardLegend = new QLabel(QObject::tr(
        "CONTROL STATUS: Green outline = editable. Red outline + faded background = "
        "disabled until its prerequisite is set. Hover for the reason; "
        "unusable saved dialogue settings also show a warning."),content);
    guardLegend->setWordWrap(true);
    detail->addWidget(guardLegend);
    scroll->setWidget(content); main->addWidget(scroll,1);
    auto *form = new QFormLayout;
    auto *speaker = new QLineEdit(node.value("speaker").toString(), &dialog);
    auto *text = new QTextEdit(&dialog); text->setPlainText(node.value("text").toString());
    text->setMaximumHeight(115);
    form->addRow(QObject::tr("Speaker"), speaker);
    form->addRow(QObject::tr("Dialogue text (auto wraps)"), text);
    detail->addLayout(form);
    auto *thoughtHelp = new QLabel(QObject::tr(
        "Thought bubbles: For an NPC speech with NO Answer, enter text in Choice 1's "
        "Player speech and tick 'Use as thought bubble (show with this dialogue)'. "
        "The thought appears with the NPC's words; Fire2 finishes the dialogue "
        "as normal. No Answer text is needed. With Answers, 'this dialogue' "
        "follows the highlighted Answer, while 'next dialogue' appears after "
        "you select it. On a Fire2-only dialogue, only the first filled THIS-dialogue "
        "thought is shown; clear its checkbox to use one in a later Choice panel."),content);
    thoughtHelp->setWordWrap(true);
    detail->addWidget(thoughtHelp);
    QJsonArray choices = node.value("choices").toArray();
    while (choices.size() < 3) choices.append(defaultChoices().at(choices.size()));
    bool noAnswers=true;
    for (const QJsonValue &v: choices)
        if (!v.toObject().value("text").toString().trimmed().isEmpty()) noAnswers=false;
    /* Migration for Stage 5.71: appearance actions on an EMPTY answer could
     * never fire. For a terminal speech node, populate the new close fields
     * from those old selections automatically, without changing the project
     * until the user presses OK. */
    QString legacyCloseSprite[2], legacyCloseMode[2];
    int legacyCloseGive=-1;
    if (noAnswers) for (const QJsonValue &v: choices) {
        const int gift=v.toObject().value("give").toInt(-1);
        if (gift>=0 && gift<items.size()) { legacyCloseGive=gift; break; }
    }
    if (noAnswers) for (int effect=0; effect<2; ++effect) {
        const QString prefix=QStringLiteral("npcAction%1").arg(effect+1);
        for (const QJsonValue &v: choices) {
            const QJsonObject c=v.toObject();
            const QString sprite=c.value(prefix+QStringLiteral("SpriteId")).toString();
            if (sprite.isEmpty()) continue;
            legacyCloseSprite[effect]=sprite;
            legacyCloseMode[effect]=c.value(prefix+QStringLiteral("Mode")).toString("hide");
            break;
        }
    }
    struct EditorFields {
        QTextEdit *label, *reply;
        QCheckBox *thought, *thoughtThis;
        QComboBox *next, *missingNext, *event, *mode;
        QComboBox *npcTargets[2], *npcModes[2];
        QComboBox *spotlight;
        QSpinBox *customId;
        QComboBox *requires, *give, *take;
        QCheckBox *once, *completeNpc;
        QPushButton *exchange;
        QLabel *dependencyNote;
    } fields[3];
    for (int i=0;i<3;++i) {
        const QJsonObject choice = choices[i].toObject();
        auto *box = new QGroupBox(QObject::tr("Choice %1").arg(i+1), &dialog);
        auto *grid = new QGridLayout(box);
        fields[i].label = new QTextEdit(box);
        fields[i].label->setAcceptRichText(false);
        fields[i].label->setTabChangesFocus(true);
        fields[i].label->setPlainText(choice.value("text").toString());
        fields[i].label->setMaximumHeight(65);
        fields[i].label->setToolTip(QObject::tr("Answers can span multiple wrapped 8x16 text rows in the game. The dialogue box grows automatically to fit the text, up to the LCD height."));
        fields[i].reply = new QTextEdit(box);
        fields[i].reply->setAcceptRichText(false);
        fields[i].reply->setTabChangesFocus(true);
        fields[i].reply->setPlainText(choice.value("reply").toString());
        fields[i].reply->setMaximumHeight(65);
        fields[i].reply->setToolTip(QObject::tr("Player speech can be a sequential reply or a thought. For a dialogue with NO answers, enter Player speech and tick 'show with this dialogue': the thought appears with the NPC speech, and Fire2 closes normally."));
        fields[i].thought = new QCheckBox(QObject::tr("Use as thought bubble (show with next dialogue)"),box);
        fields[i].thought->setChecked(choice.value("thoughtBubble").toBool(false));
        fields[i].thought->setToolTip(QObject::tr("Shows this Player speech with the NEXT dialogue after an Answer is selected. Requires an Answer; for a Fire2-only conversation with no answers, use THIS dialogue instead."));
        fields[i].thoughtThis = new QCheckBox(QObject::tr("Use as thought bubble (show with this dialogue)"),box);
        fields[i].thoughtThis->setChecked(!fields[i].thought->isChecked() && choice.value("thoughtBubbleThis").toBool(false));
        fields[i].thoughtThis->setToolTip(QObject::tr("Shows this Player speech with the CURRENT NPC dialogue. With answers, follows the highlighted answer. With NO answers, works without an Answer: the thought appears immediately and Fire2 closes as usual. Blank answers never trigger choice actions."));
        // Both options can be unticked, but cannot be ticked simultaneously.
        QObject::connect(fields[i].thought,&QCheckBox::toggled,box,[&,i](bool checked){
            if(checked) fields[i].thoughtThis->setChecked(false);
        });
        QObject::connect(fields[i].thoughtThis,&QCheckBox::toggled,box,[&,i](bool checked){
            if(checked) fields[i].thought->setChecked(false);
        });
        fields[i].next=new DialogueTreeCombo(box,&nodes,&folders);
        fields[i].next->addItem(QObject::tr("Close conversation"),-1);
        for(int target=0;target<nodes.size();++target)
            fields[i].next->addItem(dialogueTitle(nodes[target].toObject(),target),target);
        fields[i].next->setCurrentIndex(std::max(0,fields[i].next->findData(choice.value("next").toInt(-1))));
        fields[i].missingNext = new DialogueTreeCombo(box,&nodes,&folders);
        fields[i].missingNext->addItem(QObject::tr("Keep current behaviour (do nothing)"), -1);
        for(int target=0;target<nodes.size();++target)
            fields[i].missingNext->addItem(dialogueTitle(nodes[target].toObject(),target),target);
        fields[i].missingNext->setCurrentIndex(std::max(0,fields[i].missingNext->findData(choice.value("missingNext").toInt(-1))));
        fields[i].event=new QComboBox(box);
        fields[i].event->addItem(QObject::tr("No event"),QStringLiteral("none"));
        for (const auto &obj:objects)
            fields[i].event->addItem(QObject::tr("Game Object: %1").arg(obj.name),obj.id);
        fields[i].event->addItem(QObject::tr("Custom C event ID..."),QStringLiteral("custom"));
        const QString objId=choice.value("targetObjectId").toString();
        const int savedAction=choice.value("action").toInt(-1);
        const QString previous= !objId.isEmpty()?objId:(savedAction>=0?QStringLiteral("custom"):QStringLiteral("none"));
        fields[i].event->setCurrentIndex(std::max(0,fields[i].event->findData(previous)));
        fields[i].customId=new QSpinBox(box);fields[i].customId->setRange(0,29999);
        fields[i].customId->setValue(std::max(0,savedAction));
        fields[i].customId->setVisible(previous==QStringLiteral("custom"));
        QObject::connect(fields[i].event,QOverload<int>::of(&QComboBox::currentIndexChanged),box,[&,i](int){
            fields[i].customId->setVisible(fields[i].event->currentData().toString()==QStringLiteral("custom"));
        });
        auto combo = [&](const QString &label, int selected) {
            auto *cb = new QComboBox(box);
            cb->addItem(QObject::tr("None"), -1);
            for (int k=0;k<items.size();++k)
                cb->addItem(QStringLiteral("%1: %2").arg(k)
                            .arg(items[k].toObject().value("name").toString()), k);
            cb->setCurrentIndex(std::max(0,cb->findData(selected)));
            cb->setToolTip(label); return cb;
        };
        fields[i].requires = combo(QObject::tr("Requires this item"), choice.value("requires").toInt(-1));
        fields[i].give = combo(QObject::tr("NPC gives this item TO player"), choice.value("give").toInt(-1));
        fields[i].take = combo(QObject::tr("Take this item"), choice.value("take").toInt(-1));
        grid->addWidget(new QLabel(QObject::tr("Answer"),box),0,0);
        grid->addWidget(fields[i].label,0,1,1,3);
        grid->addWidget(new QLabel(QObject::tr("Player speech"),box),1,0);
        grid->addWidget(fields[i].reply,1,1,1,3);
        auto *thoughtOptions=new QVBoxLayout;
        thoughtOptions->setContentsMargins(0,0,0,0);
        thoughtOptions->addWidget(fields[i].thought);
        thoughtOptions->addWidget(fields[i].thoughtThis);
        grid->addLayout(thoughtOptions,1,4);
        grid->addWidget(new QLabel(QObject::tr("Next"),box),2,0);
        grid->addWidget(fields[i].next,2,1);
        grid->addWidget(new QLabel(QObject::tr("Event / resource"),box),2,2);
        grid->addWidget(fields[i].event,2,3);
        grid->addWidget(fields[i].customId,3,4);
        grid->addWidget(new QLabel(QObject::tr("If missing required item"),box),3,0);
        grid->addWidget(fields[i].missingNext,3,1,1,3);
        grid->addWidget(new QLabel(QObject::tr("Needs"),box),4,0);
        grid->addWidget(fields[i].requires,4,1);
        auto *giveLabel = new QLabel(QObject::tr("NPC gives"),box);
        giveLabel->setToolTip(QObject::tr("With an Answer, grant the gift when that answer is selected. With no answers anywhere in this node, this edits the one-time 'Give item when dialogue closes' reward."));
        grid->addWidget(giveLabel,4,2);
        grid->addWidget(fields[i].give,4,3);
        grid->addWidget(new QLabel(QObject::tr("Take"),box),5,0);
        grid->addWidget(fields[i].take,5,1);
        fields[i].mode = new QComboBox(box);
        fields[i].mode->addItem(QObject::tr("Activate (close solid door)"),QStringLiteral("enable"));
        fields[i].mode->addItem(QObject::tr("Deactivate (open solid door)"),QStringLiteral("disable"));
        fields[i].mode->addItem(QObject::tr("Toggle"),QStringLiteral("toggle"));
        fields[i].mode->setCurrentIndex(std::max(0,fields[i].mode->findData(choice.value("targetAction").toString("enable"))));
        grid->addWidget(new QLabel(QObject::tr("Game Object action"),box),6,0);
        grid->addWidget(fields[i].mode,6,1,1,3);
        fields[i].once = new QCheckBox(QObject::tr("Only show this answer until successfully used"),box);
        fields[i].once->setChecked(choice.value("once").toBool(false));
        grid->addWidget(fields[i].once,7,0,1,4);
        fields[i].completeNpc = new QCheckBox(QObject::tr("Mark this NPC as helped (use its completed dialogue next visit)"),box);
        fields[i].completeNpc->setChecked(choice.value("completeNpc").toBool(false));
        grid->addWidget(fields[i].completeNpc,8,0,1,4);
        /* Two independent appearance actions can accompany a Game Object or
         * custom event. Targets are stored by placed Sprite ID, not row index. */
        for (int effect = 0; effect < 2; ++effect) {
            const QString prefix = QStringLiteral("npcAction%1").arg(effect + 1);
            fields[i].npcTargets[effect] = new QComboBox(box);
            auto *target = fields[i].npcTargets[effect];
            target->addItem(QObject::tr("No NPC change"),QString());
            target->setToolTip(QObject::tr("Runs ONLY when the player selects this answer successfully. For a final speech node with no answers, use the separate When dialogue closes actions below."));
            appendNpcTargets(target);
            target->setCurrentIndex(std::max(0,target->findData(choice.value(prefix + QStringLiteral("SpriteId")).toString())));
            fields[i].npcModes[effect] = new QComboBox(box);
            auto *mode = fields[i].npcModes[effect];
            mode->addItem(QObject::tr("Hide NPC"),QStringLiteral("hide"));
            mode->addItem(QObject::tr("Show NPC"),QStringLiteral("show"));
            mode->addItem(QObject::tr("Toggle NPC"),QStringLiteral("toggle"));
            mode->setCurrentIndex(std::max(0,mode->findData(choice.value(prefix + QStringLiteral("Mode")).toString("hide"))));
            grid->addWidget(new QLabel(QObject::tr("NPC action %1").arg(effect + 1),box),10+effect,0);
            grid->addWidget(target,10+effect,1,1,2);
            grid->addWidget(mode,10+effect,3);
        }
        fields[i].exchange=new QPushButton(box);
        const QJsonObject savedExchange=choice.value("exchange").toObject();
        fields[i].exchange->setProperty("exchange",QVariant::fromValue(savedExchange));
        auto updateExchangeLabel=[&,i]() {
            const QJsonObject value=fields[i].exchange->property("exchange").toJsonObject();
            const int n=value.value("items").toArray().size();
            fields[i].exchange->setText(value.value("enabled").toBool(false)
                ? QObject::tr("Edit GIVE exchange (%1 / %2 items)")
                      .arg(value.value("logic").toString()=="any"?QObject::tr("OR"):QObject::tr("AND"))
                      .arg(n)
                : QObject::tr("Configure GIVE inventory / AND-OR requirements..."));
        };
        updateExchangeLabel();
        QObject::connect(fields[i].exchange,&QPushButton::clicked,box,[&,i,updateExchangeLabel](){
            const QJsonObject before=fields[i].exchange->property("exchange").toJsonObject();
            fields[i].exchange->setProperty("exchange",QVariant::fromValue(editExchange(&dialog,before,items,nodes,objects,folders)));
            updateExchangeLabel();
        });
        grid->addWidget(new QLabel(QObject::tr("NPC item exchange"),box),9,0);
        grid->addWidget(fields[i].exchange,9,1,1,3);
        fields[i].spotlight = new QComboBox(box);
        fields[i].spotlight->addItem(QObject::tr("No change"), 3);
        fields[i].spotlight->addItem(QObject::tr("Switch spotlight ON"), 1);
        fields[i].spotlight->addItem(QObject::tr("Switch spotlight OFF"), 0);
        fields[i].spotlight->addItem(QObject::tr("Toggle spotlight"), 2);
        fields[i].spotlight->setCurrentIndex(std::max(0,fields[i].spotlight->findData(choice.value("spotlightAction").toInt(3))));
        fields[i].spotlight->setToolTip(QObject::tr("Runs after this answer succeeds. The spotlight is configured under Player Start."));
        grid->addWidget(new QLabel(QObject::tr("Player Spotlight"),box),12,0);
        grid->addWidget(fields[i].spotlight,12,1,1,3);
        fields[i].dependencyNote=new QLabel(box);
        fields[i].dependencyNote->setWordWrap(true);
        fields[i].dependencyNote->setVisible(false);
        grid->addWidget(fields[i].dependencyNote,13,0,1,5);
        detail->addWidget(box);
    }

    /* A final dialogue node can have no answers. Choice actions do not fire
     * in that case, so offer explicit ON-CLOSE actions independently of any
     * answer. This is exactly the case for Big Steve's "See ya!" node. */
    auto *onCloseGroup = new QGroupBox(QObject::tr("When this dialogue closes (no answers)"), &dialog);
    auto *onCloseLayout = new QGridLayout(onCloseGroup);
    auto *onCloseHint = new QLabel(QObject::tr(
        "After the final line is read, FIRE2 closes this dialogue and runs these actions. "
        "Only nodes without visible answer choices use them. On an answerless node, "
        "NPC action 1/2 inside the blank Choice panels edit these same settings too."), onCloseGroup);
    onCloseHint->setWordWrap(true);
    onCloseLayout->addWidget(onCloseHint,0,0,1,4);
    QComboBox *onCloseNpcTarget[2] = {nullptr,nullptr};
    QComboBox *onCloseNpcMode[2] = {nullptr,nullptr};
    for (int effect=0; effect<2; ++effect) {
        const QString prefix=QStringLiteral("closeNpcAction%1").arg(effect+1);
        onCloseNpcTarget[effect]=new QComboBox(onCloseGroup);
        auto *target=onCloseNpcTarget[effect];
        target->addItem(QObject::tr("No NPC change"),QString());
        appendNpcTargets(target);
        const QString savedSprite=node.value(prefix+QStringLiteral("SpriteId")).toString();
        target->setCurrentIndex(std::max(0,target->findData(savedSprite.isEmpty() && noAnswers
            ? legacyCloseSprite[effect] : savedSprite)));
        onCloseNpcMode[effect]=new QComboBox(onCloseGroup);
        auto *mode=onCloseNpcMode[effect];
        mode->addItem(QObject::tr("Hide NPC"),QStringLiteral("hide"));
        mode->addItem(QObject::tr("Show NPC"),QStringLiteral("show"));
        mode->addItem(QObject::tr("Toggle NPC"),QStringLiteral("toggle"));
        const QString closeMode=node.value(prefix+QStringLiteral("Mode")).toString();
        mode->setCurrentIndex(std::max(0,mode->findData(closeMode.isEmpty() && noAnswers
            && !legacyCloseSprite[effect].isEmpty() ? legacyCloseMode[effect]
            : (closeMode.isEmpty() ? QStringLiteral("hide") : closeMode))));
        onCloseLayout->addWidget(new QLabel(QObject::tr("On close action %1").arg(effect+1),onCloseGroup),1+effect,0);
        onCloseLayout->addWidget(target,1+effect,1,1,2);
        onCloseLayout->addWidget(mode,1+effect,3);
    }
    auto *onCloseGift = new QComboBox(onCloseGroup);
    onCloseGift->addItem(QObject::tr("No item"),-1);
    for (int k=0;k<items.size();++k)
        onCloseGift->addItem(QStringLiteral("%1: %2").arg(k)
            .arg(items[k].toObject().value("name").toString()),k);
    const int savedCloseGift=node.value("closeGiveItem").toInt(-1);
    onCloseGift->setCurrentIndex(std::max(0,onCloseGift->findData(savedCloseGift>=0
        ? savedCloseGift : (noAnswers ? legacyCloseGive : -1))));
    onCloseGift->setToolTip(QObject::tr("Grant ONE inventory item when an answerless final dialogue closes. One-time and preserved across world transitions. NPC gives on the blank Choice panels edits this same value."));
    onCloseLayout->addWidget(new QLabel(QObject::tr("Give item when dialogue closes"),onCloseGroup),3,0,1,2);
    onCloseLayout->addWidget(onCloseGift,3,2,1,2);
    auto *onCloseSpotlight = new QComboBox(onCloseGroup);
    onCloseSpotlight->addItem(QObject::tr("No change"), 3);
    onCloseSpotlight->addItem(QObject::tr("Switch spotlight ON"), 1);
    onCloseSpotlight->addItem(QObject::tr("Switch spotlight OFF"), 0);
    onCloseSpotlight->addItem(QObject::tr("Toggle spotlight"), 2);
    onCloseSpotlight->setCurrentIndex(std::max(0,onCloseSpotlight->findData(node.value("closeSpotlightAction").toInt(3))));
    onCloseLayout->addWidget(new QLabel(QObject::tr("Player Spotlight on close"),onCloseGroup),4,0,1,2);
    onCloseLayout->addWidget(onCloseSpotlight,4,2,1,2);
    /* Keep NPC Hide/Show/Toggle EDITABLE even when a terminal node has no
     * answer text. For an answerless node the three familiar choice-row NPC
     * controls are live mirrors of the two real on-close NPC actions. Updating
     * either place updates the other, and only the node-level close fields are
     * saved for such a node. This prevents the Stage 5.71.2 disabled-combo
     * regression and the earlier disappearing selection after reopen.
     *
     * When an answer exists, each choice retains its own independent NPC
     * actions; the on-close actions are inactive until the node is terminal. */
    const auto hasAnyAnswer = [&fields]() {
        for (const EditorFields &f : fields)
            if (!f.label->toPlainText().trimmed().isEmpty()) return true;
        return false;
    };
    /* Terminal dialogue nodes have no selectable answers. The familiar
     * 'NPC gives' controls must therefore edit the SAME node-level gift as
     * 'Give item when dialogue closes', rather than being disabled. Keep all
     * three blank Choice panels in sync, and block signals during mirroring.
     * For non-terminal nodes, the choice gifts remain independent. */
    bool syncingCloseGift = false;
    const auto mirrorCloseGift = [&]() {
        if (syncingCloseGift || hasAnyAnswer()) return;
        syncingCloseGift = true;
        const int giftId = onCloseGift->currentData().toInt();
        for (EditorFields &f : fields) {
            const QSignalBlocker blockGift(f.give);
            f.give->setCurrentIndex(std::max(0,f.give->findData(giftId)));
        }
        syncingCloseGift = false;
    };
    const auto chooseCloseGiftFromChoice = [&](int i) {
        if (syncingCloseGift || hasAnyAnswer()) return;
        syncingCloseGift = true;
        {
            const QSignalBlocker blockGift(onCloseGift);
            onCloseGift->setCurrentIndex(std::max(0,
                onCloseGift->findData(fields[i].give->currentData())));
        }
        syncingCloseGift = false;
        mirrorCloseGift();
    };
    QObject::connect(onCloseGift,QOverload<int>::of(&QComboBox::currentIndexChanged),
                     &dialog,[&](int){ mirrorCloseGift(); });
    bool syncingCloseNpc = false;
    const auto mirrorCloseNpc = [&](int effect) {
        if (syncingCloseNpc || hasAnyAnswer()) return;
        syncingCloseNpc = true;
        const QString targetId = onCloseNpcTarget[effect]->currentData().toString();
        const QString modeId = onCloseNpcMode[effect]->currentData().toString();
        for (EditorFields &f : fields) {
            const QSignalBlocker blockTarget(f.npcTargets[effect]);
            const QSignalBlocker blockMode(f.npcModes[effect]);
            f.npcTargets[effect]->setCurrentIndex(std::max(0,f.npcTargets[effect]->findData(targetId)));
            f.npcModes[effect]->setCurrentIndex(std::max(0,f.npcModes[effect]->findData(modeId)));
        }
        syncingCloseNpc = false;
    };
    const auto chooseCloseNpcFromChoice = [&](int i, int effect) {
        if (syncingCloseNpc || hasAnyAnswer()) return;
        syncingCloseNpc = true;
        {
            const QSignalBlocker blockTarget(onCloseNpcTarget[effect]);
            const QSignalBlocker blockMode(onCloseNpcMode[effect]);
            onCloseNpcTarget[effect]->setCurrentIndex(std::max(0,
                onCloseNpcTarget[effect]->findData(fields[i].npcTargets[effect]->currentData())));
            onCloseNpcMode[effect]->setCurrentIndex(std::max(0,
                onCloseNpcMode[effect]->findData(fields[i].npcModes[effect]->currentData())));
        }
        syncingCloseNpc = false;
        mirrorCloseNpc(effect);
    };
    for (int effect=0; effect<2; ++effect) {
        QObject::connect(onCloseNpcTarget[effect],QOverload<int>::of(&QComboBox::currentIndexChanged),
                         &dialog,[&,effect](int){ mirrorCloseNpc(effect); });
        QObject::connect(onCloseNpcMode[effect],QOverload<int>::of(&QComboBox::currentIndexChanged),
                         &dialog,[&,effect](int){ mirrorCloseNpc(effect); });
    }
    // Stage 5.116: grey out *unreachable* actions, not their saved values.
    // An answerless dialogue has a special Fire2-close route; NPC appearance
    // and inventory gifts in its blank Choice panels edit that SAME close route.
    // Do not disable those mirrors (the earlier 5.71 regression).
    const auto refreshChoiceControls = [&]() {
        const bool terminal = !hasAnyAnswer();
        // The runtime displays the first available thought when there is no
        // highlighted Answer; only one Fire2-only thought can be active.
        int firstTerminalThought=-1;
        if(terminal)for(int i=0;i<3;++i)
            if(fields[i].thoughtThis->isChecked() &&
               !fields[i].reply->toPlainText().trimmed().isEmpty()) {
                firstTerminalThought=i;break;
            }
        int choiceIndex=0;
        const QString answerNeeded = QObject::tr("Disabled: enter an Answer in THIS choice first. Blank answers cannot be selected, so their actions never run.");
        for (EditorFields &f : fields) {
            const bool hasAnswer=!f.label->toPlainText().trimmed().isEmpty();
            const bool hasSpeech=!f.reply->toPlainText().trimmed().isEmpty();
            const bool selectable=hasAnswer;
            const bool hasNext=f.next->currentData().toInt()>=0;
            const bool hasRequirement=f.requires->currentData().toInt()>=0;
            const QString kind=f.event->currentData().toString();
            const QString answerHint = selectable
                ? QObject::tr("Runs only when this Answer is selected successfully.") : answerNeeded;
            const auto gateAnswer = [&](QWidget *widget, const QString &activeHint) {
                adventureMarkDependent(widget); widget->setEnabled(selectable);
                widget->setToolTip(selectable ? activeHint : answerNeeded);
            };
            gateAnswer(f.next,QObject::tr("Dialogue to open immediately after selecting this Answer. 'Close conversation' ends it."));
            gateAnswer(f.event,QObject::tr("Choose a Game Object to activate/deactivate, or a custom C event, after selecting this Answer."));
            adventureMarkDependent(f.customId); f.customId->setEnabled(selectable && kind==QStringLiteral("custom"));
            f.customId->setToolTip(!selectable ? answerNeeded : QObject::tr("Custom event ID; choose 'Custom C event ID' above to edit it."));
            adventureMarkDependent(f.mode); f.mode->setEnabled(selectable && kind!=QStringLiteral("none") && kind!=QStringLiteral("custom"));
            f.mode->setToolTip(!selectable ? answerNeeded : QObject::tr("Disabled until Event / resource selects a Game Object. Custom events use their numeric ID instead."));
            gateAnswer(f.requires,QObject::tr("This inventory item must be owned to use this Answer."));
            gateAnswer(f.take,QObject::tr("Remove this item when the Answer is selected successfully."));
            adventureMarkDependent(f.missingNext); f.missingNext->setEnabled(selectable && hasRequirement);
            f.missingNext->setToolTip(!selectable ? answerNeeded : !hasRequirement
                ? QObject::tr("Disabled: choose an item under Needs first. With no required item, the missing-item branch cannot occur.")
                : QObject::tr("Dialogue shown when the player selects this Answer without its required item."));
            gateAnswer(f.once,QObject::tr("Once this Answer succeeds, do not show it again."));
            gateAnswer(f.completeNpc,QObject::tr("Marks this NPC helped; its 'After helped' dialogue is used on a FUTURE visit."));
            gateAnswer(f.spotlight,QObject::tr("Change the player's spotlight after the selected Answer succeeds."));
            gateAnswer(f.exchange,QObject::tr("Configure the GIVE inventory interaction opened by selecting this Answer."));

            adventureMarkDependent(f.thought); f.thought->setEnabled(selectable && hasSpeech && hasNext);
            f.thought->setToolTip(!hasSpeech
                ? QObject::tr("Disabled: enter Player speech first, then enable a thought bubble.")
                : !selectable
                    ? QObject::tr("Disabled: 'show with NEXT dialogue' requires a selectable Answer. For a Fire2-only dialogue use 'show with THIS dialogue'.")
                    : !hasNext
                        ? QObject::tr("Disabled: set Next to a dialogue node first. 'Close conversation' leaves no next dialogue to display this thought.")
                        : QObject::tr("Show this Player speech as a thought after selecting the Answer, with the NEXT dialogue."));
            const bool otherTerminalThought=terminal && firstTerminalThought>=0 &&
                firstTerminalThought!=choiceIndex;
            const bool canThinkNow=hasSpeech && (selectable || terminal) && !otherTerminalThought;
            adventureMarkDependent(f.thoughtThis); f.thoughtThis->setEnabled(canThinkNow);
            f.thoughtThis->setToolTip(!hasSpeech
                ? QObject::tr("Disabled: enter Player speech first to display a thought.")
                : otherTerminalThought
                    ? QObject::tr("Disabled: another Choice already supplies this Fire2-only thought. Untick the earlier THIS-dialogue thought first.")
                : !selectable && !terminal
                    ? QObject::tr("Disabled: this blank Choice is not selectable. Enter an Answer, or remove all Answers to make a Fire2-only dialogue.")
                    : terminal
                        ? QObject::tr("Show this thought during the current dialogue without an Answer. Fire2 still closes normally.")
                        : QObject::tr("Show this thought during the current dialogue while this Answer is highlighted."));

            // Visible warnings cover legacy values and options made inactive
            // after an edit. Qt does not reliably show tooltips for all disabled
            // controls under all widget styles, so don't rely on hover alone.
            QStringList problems;
            if(!selectable && hasSpeech && !f.thoughtThis->isChecked() && terminal)
                problems << QObject::tr("Player speech on a Fire2-only dialogue needs 'show with THIS dialogue' to be visible.");
            if(!selectable && hasSpeech && !terminal)
                problems << QObject::tr("Player speech on a blank Choice cannot run until that Choice has an Answer.");
            if(!selectable && (f.next->currentData().toInt()>=0 ||
                f.event->currentData().toString()!=QStringLiteral("none") ||
                f.requires->currentData().toInt()>=0 || f.take->currentData().toInt()>=0 ||
                f.once->isChecked() || f.completeNpc->isChecked() ||
                f.exchange->property("exchange").toJsonObject().value("enabled").toBool()))
                problems << QObject::tr("Answer-only Next, item, event or quest actions on this blank Choice cannot run.");
            if(f.thought->isChecked() && !hasSpeech)
                problems << QObject::tr("NEXT thought has no Player speech.");
            else if(f.thought->isChecked() && !selectable)
                problems << QObject::tr("NEXT thought needs an Answer. Use THIS dialogue for Fire2-only speech.");
            else if(f.thought->isChecked() && !hasNext)
                problems << QObject::tr("NEXT thought needs Next → a dialogue node (not Close conversation).");
            if(f.thoughtThis->isChecked() && !hasSpeech)
                problems << QObject::tr("THIS thought has no Player speech.");
            if(f.thoughtThis->isChecked() && !selectable && !terminal)
                problems << QObject::tr("THIS thought is on a blank Choice; only selectable Answers can show it here.");
            if(f.thoughtThis->isChecked() && otherTerminalThought)
                problems << QObject::tr("Another Fire2-only thought appears first. Only one can show.");
            if(f.missingNext->currentData().toInt()>=0 && !hasRequirement)
                problems << QObject::tr("Missing-item dialogue needs a selection under Needs.");
            f.dependencyNote->setText(problems.isEmpty() ? QString()
                : QObject::tr("Settings currently unable to run: %1").arg(problems.join(QStringLiteral("  "))));
            f.dependencyNote->setVisible(!problems.isEmpty());
            adventureMarkDependent(f.give); f.give->setEnabled(terminal || selectable);
            f.give->setToolTip(terminal
                ? QObject::tr("No answers: edits 'Give item when dialogue closes'. All three NPC gives selectors mirror that one-time gift.")
                : selectable ? QObject::tr("Award this item when this Answer is selected.") : answerNeeded);
            for (int effect=0; effect<2; ++effect) {
                // Terminal nodes mirror the ON-CLOSE NPC action; blank choices
                // on a non-terminal node are truly unreachable.
                const bool canEdit=terminal || selectable;
                const bool hasTarget=!f.npcTargets[effect]->currentData().toString().isEmpty();
                adventureMarkDependent(f.npcTargets[effect]); f.npcTargets[effect]->setEnabled(canEdit);
                f.npcTargets[effect]->setToolTip(terminal
                    ? QObject::tr("No Answers: edits the ON-CLOSE NPC action. The other blank Choice panels mirror it.")
                    : answerHint);
                adventureMarkDependent(f.npcModes[effect]); f.npcModes[effect]->setEnabled(canEdit && hasTarget);
                f.npcModes[effect]->setToolTip(!canEdit ? answerNeeded : !hasTarget
                    ? QObject::tr("Disabled: select an NPC target first, then choose Hide, Show or Toggle.")
                    : QObject::tr("Hide, Show or Toggle this NPC when the action runs."));
            }
            ++choiceIndex;
        }
        // These actions run ONLY after Fire2 closes an answerless dialogue.
        adventureMarkDependent(onCloseGroup); onCloseGroup->setEnabled(terminal);
        onCloseGroup->setToolTip(terminal
            ? QObject::tr("Runs when Fire2 closes this dialogue without selectable Answers.")
            : QObject::tr("Disabled: this dialogue has selectable Answers. Remove every Answer to enable Fire2 on-close actions."));
        for (int effect=0; effect<2; ++effect) {
            const bool hasTarget=!onCloseNpcTarget[effect]->currentData().toString().isEmpty();
            adventureMarkDependent(onCloseNpcMode[effect]); onCloseNpcMode[effect]->setEnabled(terminal && hasTarget);
            onCloseNpcMode[effect]->setToolTip(!terminal
                ? QObject::tr("Disabled: on-close actions require a dialogue with no Answers.")
                : !hasTarget
                    ? QObject::tr("Disabled: select an On close NPC target first.")
                    : QObject::tr("Choose how the selected NPC changes when Fire2 closes this dialogue."));
        }
        if (terminal) {
            mirrorCloseGift();
            mirrorCloseNpc(0);
            mirrorCloseNpc(1);
        }
    };
    for (int i=0;i<3;++i) {
        QObject::connect(fields[i].label,&QTextEdit::textChanged,&dialog,
                         [&,i] { Q_UNUSED(i); refreshChoiceControls(); });
        QObject::connect(fields[i].reply,&QTextEdit::textChanged,&dialog,
                         [&,i] { Q_UNUSED(i); refreshChoiceControls(); });
        QObject::connect(fields[i].thoughtThis,&QCheckBox::toggled,&dialog,
                         [&](bool){refreshChoiceControls();});
        QObject::connect(fields[i].thought,&QCheckBox::toggled,&dialog,
                         [&](bool){refreshChoiceControls();});
        QObject::connect(fields[i].requires,QOverload<int>::of(&QComboBox::currentIndexChanged),
                         &dialog,[&](int){ refreshChoiceControls(); });
        QObject::connect(fields[i].next,QOverload<int>::of(&QComboBox::currentIndexChanged),
                         &dialog,[&](int){ refreshChoiceControls(); });
        QObject::connect(fields[i].event,QOverload<int>::of(&QComboBox::currentIndexChanged),
                         &dialog,[&](int){ refreshChoiceControls(); });
        QObject::connect(fields[i].give,QOverload<int>::of(&QComboBox::currentIndexChanged),
                         &dialog,[&,i](int){ chooseCloseGiftFromChoice(i); });
        for (int effect=0;effect<2;++effect) {
            QObject::connect(fields[i].npcTargets[effect],QOverload<int>::of(&QComboBox::currentIndexChanged),
                             &dialog,[&,i,effect](int){ chooseCloseNpcFromChoice(i,effect); });
            QObject::connect(fields[i].npcModes[effect],QOverload<int>::of(&QComboBox::currentIndexChanged),
                             &dialog,[&,i,effect](int){ chooseCloseNpcFromChoice(i,effect); });
        }
    }
    for (int i=0; i<3; ++i) for (int effect=0; effect<2; ++effect)
        QObject::connect(fields[i].npcTargets[effect],QOverload<int>::of(&QComboBox::currentIndexChanged),
                         &dialog,[&](int){ refreshChoiceControls(); });
    for (int effect=0; effect<2; ++effect)
        QObject::connect(onCloseNpcTarget[effect],QOverload<int>::of(&QComboBox::currentIndexChanged),
                         &dialog,[&](int){ refreshChoiceControls(); });
    refreshChoiceControls();
    /* A terminal node's active controls must not be buried below three
     * unused Choice panels. The same controls remain visible inside choices. */
    detail->insertWidget(1,onCloseGroup);

    // The completed dialogue is an NPC setting, not a property of a shared
    // dialogue node. Offer an intuitive shortcut from the NPC's opening node,
    // and update the same NPC table control used by the NPCs tab.
    auto *afterHelp = new QGroupBox(QObject::tr("Already helped — on a FUTURE visit"), &dialog);
    auto *afterHelpForm = new QFormLayout(afterHelp);
    auto *helpText = new QLabel(QObject::tr(
        "When a choice above successfully marks this NPC as helped, the next time "
        "the player talks to them, use the following conversation. "
        "The choice's Next dropdown is different: it continues IMMEDIATELY."), afterHelp);
    helpText->setWordWrap(true);
    afterHelpForm->addRow(helpText);
    auto *linkedNpc = new QComboBox(afterHelp);
    auto *nextVisit = new DialogueTreeCombo(afterHelp,&nodes,&folders);
    if (npcTable) {
        for (int r = 0; r < npcTable->rowCount(); ++r) {
            auto *start = qobject_cast<QComboBox*>(npcTable->cellWidget(r,1));
            if (!start || start->currentData().toInt() != row) continue;
            auto *nameItem = npcTable->item(r,0);
            const QString npcName = nameItem ? nameItem->text() : QObject::tr("NPC %1").arg(r+1);
            linkedNpc->addItem(npcName,r);
        }
    }
    nextVisit->addItem(QObject::tr("Keep normal opening dialogue"),-1);
    for (int target=0; target<nodes.size(); ++target)
        nextVisit->addItem(dialogueTitle(nodes[target].toObject(),target),target);
    const auto loadNpc = [&]() {
        const int npcRow=linkedNpc->currentData().toInt();
        auto *saved=npcTable ? qobject_cast<QComboBox*>(npcTable->cellWidget(npcRow,3)) : nullptr;
        nextVisit->setCurrentIndex(std::max(0,nextVisit->findData(saved ? saved->currentData().toInt() : -1)));
    };
    if (linkedNpc->count()) {
        afterHelpForm->addRow(QObject::tr("NPC using this opening"),linkedNpc);
        afterHelpForm->addRow(QObject::tr("Conversation NEXT visit"),nextVisit);
        QObject::connect(linkedNpc,QOverload<int>::of(&QComboBox::currentIndexChanged),
                         afterHelp, [&,nextVisit](int){ loadNpc(); });
        loadNpc();
    } else {
        auto *noNpc=new QLabel(QObject::tr(
            "No NPC starts at this dialogue node yet. Under NPCs, select this node "
            "as an NPC's Start node to configure its future-visit response here."),afterHelp);
        noNpc->setWordWrap(true);
        afterHelpForm->addRow(noNpc);
    }
    detail->addWidget(afterHelp);
    auto *note = new QLabel(QObject::tr("Choose an existing Game Object to activate, deactivate or toggle it. "
                                       "Custom event IDs call gameadventure_on_event() in the generated game."), &dialog);
    note->setWordWrap(true); detail->addWidget(note);
    auto *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,&dialog);
    main->addWidget(buttons);
    QObject::connect(buttons,&QDialogButtonBox::accepted,&dialog,&QDialog::accept);
    QObject::connect(buttons,&QDialogButtonBox::rejected,&dialog,&QDialog::reject);
    if (dialog.exec() != QDialog::Accepted) return;
    node.insert("speaker",speaker->text().left(36));
    node.insert("text",text->toPlainText().left(512));
    QJsonArray updated;
    for (int i=0;i<3;++i) {
        QJsonObject c; c.insert("text",fields[i].label->toPlainText().left(180));
        c.insert("reply",fields[i].reply->toPlainText().left(150));
        c.insert("thoughtBubble",fields[i].thought->isChecked());
        c.insert("thoughtBubbleThis",fields[i].thoughtThis->isChecked());
        c.insert("next",fields[i].next->currentData().toInt());
        c.insert("missingNext",fields[i].missingNext->currentData().toInt());
        const QString eventSelection=fields[i].event->currentData().toString();
        c.insert("action",eventSelection==QStringLiteral("custom")?fields[i].customId->value():-1);
        c.insert("requires",fields[i].requires->currentData().toInt());
        c.insert("give",fields[i].give->currentData().toInt());
        c.insert("take",fields[i].take->currentData().toInt());
        c.insert("once",fields[i].once->isChecked());
        c.insert("completeNpc",fields[i].completeNpc->isChecked());
        c.insert("targetObjectId",(eventSelection!=QStringLiteral("none") && eventSelection!=QStringLiteral("custom"))
            ?eventSelection:QString());
        c.insert("targetAction",fields[i].mode->currentData().toString());
        c.insert("spotlightAction",fields[i].spotlight->currentData().toInt());
        for (int effect = 0; effect < 2; ++effect) {
            const QString prefix = QStringLiteral("npcAction%1").arg(effect + 1);
            c.insert(prefix + QStringLiteral("SpriteId"),fields[i].npcTargets[effect]->currentData().toString());
            c.insert(prefix + QStringLiteral("Mode"),fields[i].npcModes[effect]->currentData().toString());
        }
        c.insert("exchange",fields[i].exchange->property("exchange").toJsonObject());
        updated.append(c);
    }
    node.insert("closeGiveItem",onCloseGift->currentData().toInt());
    node.insert("closeSpotlightAction",onCloseSpotlight->currentData().toInt());
    for (int effect=0; effect<2; ++effect) {
        const QString prefix=QStringLiteral("closeNpcAction%1").arg(effect+1);
        node.insert(prefix+QStringLiteral("SpriteId"),onCloseNpcTarget[effect]->currentData().toString());
        node.insert(prefix+QStringLiteral("Mode"),onCloseNpcMode[effect]->currentData().toString());
    }
    /* Retire the unreachable empty-answer action once its setting has been
     * migrated to the no-answer dialogue-close event. */
    bool noAnswersAfterEdit=true;
    for (const QJsonValue &v: updated)
        if (!v.toObject().value("text").toString().trimmed().isEmpty()) noAnswersAfterEdit=false;
    if (noAnswersAfterEdit) for (int c=0; c<updated.size(); ++c) {
        QJsonObject choice=updated[c].toObject();
        /* The reward is now on the terminal node, not an unreachable answer. */
        choice.insert("give",-1); /* empty answers cannot award items */
        for (int effect=0; effect<2; ++effect) {
            const QString prefix=QStringLiteral("npcAction%1").arg(effect+1);
            /* Always retire empty-answer legacy actions, including when the
             * user explicitly resets the closing target to "No NPC change".
             * Otherwise an old ghost action would be migrated back next time. */
            choice.insert(prefix+QStringLiteral("SpriteId"),QString());
        }
        updated[c]=choice;
    }
    node.insert("choices",updated); nodes[row] = node;
    if (npcTable && linkedNpc->count()) {
        const int npcRow=linkedNpc->currentData().toInt();
        auto *saved=qobject_cast<QComboBox*>(npcTable->cellWidget(npcRow,3));
        if (saved) saved->setCurrentIndex(std::max(0,saved->findData(nextVisit->currentData().toInt())));
    }
}
} // namespace

QComboBox *createGameDialogueTreeCombo(QWidget *parent,
                                       const QJsonArray *nodes,
                                       const QJsonArray *folders)
{
    return new DialogueTreeCombo(parent, nodes, folders);
}

/* Shorten repeated object instances without altering the pickup kind.
 * e.g. flower[0..4], flower[7..9]; a complete zero-based run is flower[].
 * An already-named flower[] remains the explicit all-instances notation. */
QStringList collectableInstanceSummary(const QStringList &names)
{
    const QRegularExpression indexed(QStringLiteral(R"(^(.*)\[(\d+)\]$)"));
    QMap<QString,QSet<int>> groups;
    QStringList plain;
    for (const QString &name : names) {
        const QRegularExpressionMatch match=indexed.match(name);
        if (!match.hasMatch()) { if (!plain.contains(name)) plain.append(name); continue; }
        bool ok=false;
        const int number=match.captured(2).toInt(&ok);
        if (!ok || number<0) { plain.append(name); continue; }
        groups[match.captured(1)].insert(number);
    }
    for (auto it=groups.constBegin();it!=groups.constEnd();++it) {
        QList<int> indices=it.value().values();
        std::sort(indices.begin(),indices.end());
        if(indices.isEmpty())continue;
        const bool complete=indices.first()==0 && indices.last()==indices.size()-1;
        if (complete && indices.size()>1) {
            plain.append(it.key()+QStringLiteral("[]"));
            continue;
        }
        for(int i=0;i<indices.size();) {
            const int first=indices[i];
            int last=first;
            while(++i<indices.size() && indices[i]==last+1) last=indices[i];
            plain.append(it.key()+QStringLiteral("[%1%2]").arg(first)
                .arg(last==first?QString():QStringLiteral("..%1").arg(last)));
        }
    }
    return plain;
}

bool editGameAdventure(QWidget *parent, QJsonObject *payload,
                       const QVector<GameAdventureAsset> &sprites,
                       const QVector<GameAdventureAsset> &atlases,
                       const QVector<GameAdventureAsset> &worldObjects,
                       const QVector<GameAdventureAsset> &collectables,
                       const QVector<QRgb> &foregroundPalette,
                       const QString &currentDesignFilePath,
                       const QString &focusNpcSpriteId)
{
    if (!payload) return false;
    const QJsonObject old = *payload;
    QJsonArray nodes=old.value("nodes").toArray();
    // Editor-only grouping. Never reorder the nodes array when moving folders.
    QJsonArray dialogueFolders=old.value("dialogueFolders").toArray();
    QDialog dialog(parent); dialog.setWindowTitle(QObject::tr("Advanced Platformer — Adventure Editor"));
    dialog.setMinimumSize(890,670); dialog.resize(1230,800);
    auto *main = new QVBoxLayout(&dialog);
    auto *guardLegend=new QLabel(QObject::tr(
        "Dependency controls: GREEN outline = available; RED outline + faded = unavailable. "
        "Hover for the missing requirement. Other controls use the normal theme."),&dialog);
    guardLegend->setWordWrap(true);
    main->addWidget(guardLegend);
    auto *tabs = new QTabWidget(&dialog); main->addWidget(tabs,1);

    // Both inventory icons and dialogue frame tiles use the selected atlas.
    QComboBox *skinAtlas = nullptr;
    QSpinBox *tileSize = nullptr;
    QComboBox *inventoryIconAtlas = nullptr;
    QSpinBox *inventoryIconCell = nullptr;
    bool editingIconControls = false;
    auto *itemsPage = new QWidget(tabs); auto *itemsLayout = new QVBoxLayout(itemsPage);
    auto *items = new QTableWidget(0,8,itemsPage);
    items->setHorizontalHeaderLabels({QObject::tr("Item name (e.g. Brass Key)"),QObject::tr("Pick up from..."),
                                      QObject::tr("Max owned"),QObject::tr("Start with"),QObject::tr("Icon artwork"),
                                      QObject::tr("Can drop?"),QObject::tr("Can discard?"),QObject::tr("USE effect")});
    items->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    items->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
    items->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);
    items->horizontalHeader()->setSectionResizeMode(3,QHeaderView::ResizeToContents);
    items->horizontalHeader()->setSectionResizeMode(4,QHeaderView::ResizeToContents);
    items->horizontalHeader()->setSectionResizeMode(5,QHeaderView::ResizeToContents);
    items->horizontalHeader()->setSectionResizeMode(6,QHeaderView::ResizeToContents);
    items->horizontalHeader()->setSectionResizeMode(7,QHeaderView::ResizeToContents);
    items->setIconSize(QSize(36,36));
    items->verticalHeader()->setDefaultSectionSize(46);
    auto *collectionHelp=new QLabel(QObject::tr(
        "INVENTORY GUIDE: Each row is an item your game can recognise (for example, Brass Key). "
        "'Max owned' is how many can be carried; 'Start with' is how many the player begins with. "
        "Pick up from... matches the named collectable TYPE in World Designer (classic kinds 1–4, or your custom kinds 5–255). "
        "A name like Kim_copy[1] is the placed object's name, NOT an inventory item. "
        "Choosing type 2 means EVERY Health-type collectable adds this row's item. "
        "When Show in Inventory is ticked on a placed collectable, the generated world "
        "adds one per object picked up automatically. Legacy untracked pickups may "
        "still use game_adventure_collect(item->kind) in a custom on_pickup() callback. "
        "Double-click Icon artwork to choose that item's PPB atlas, cell size, and Single or 2×2 stamp. "
        "Make that PPB available in every other world where this inventory icon should appear. "
        "Can drop places an item on the floor for later recovery; Can discard destroys it permanently. "
        "NPC-required items cannot be destroyed but CAN be dropped. "
        "A 0-slot inventory limit means unlimited distinct item stacks."),itemsPage);
    collectionHelp->setWordWrap(true);itemsLayout->addWidget(collectionHelp);
    auto *inventoryCapacityRow=new QHBoxLayout;
    auto *inventoryCapacity=new QSpinBox(itemsPage);
    inventoryCapacity->setRange(0,64);
    inventoryCapacity->setValue(std::clamp(old.value("maxInventorySlots").toInt(0),0,64));
    inventoryCapacity->setToolTip(QObject::tr("Maximum distinct item stacks held. 0 = unlimited; existing stack quantities can still grow."));
    inventoryCapacityRow->addWidget(new QLabel(QObject::tr("Maximum inventory slots (0 = unlimited):"),itemsPage));
    inventoryCapacityRow->addWidget(inventoryCapacity);inventoryCapacityRow->addStretch();
    itemsLayout->addLayout(inventoryCapacityRow);
    auto *itemAtlasRow = new QHBoxLayout;
    inventoryIconAtlas = new QComboBox(itemsPage);
    inventoryIconAtlas->addItem(QObject::tr("Dialogue atlas (legacy default)"),QString());
    for(const auto &a:atlases) inventoryIconAtlas->addItem(a.name,a.id);
    inventoryIconCell = new QSpinBox(itemsPage);
    inventoryIconCell->setRange(4,64);inventoryIconCell->setValue(8);
    itemAtlasRow->addWidget(new QLabel(QObject::tr("Selected item's Icon Atlas:"),itemsPage));
    itemAtlasRow->addWidget(inventoryIconAtlas,1);
    itemAtlasRow->addWidget(new QLabel(QObject::tr("Stamp cell size:"),itemsPage));
    itemAtlasRow->addWidget(inventoryIconCell);
    itemsLayout->addLayout(itemAtlasRow);
    itemsLayout->addWidget(new QLabel(QObject::tr("Double-click Icon artwork to choose the PPB atlas and tiles together. The controls above also edit the selected item. Other worlds need the PPB registered in Game Resources."),itemsPage));
    itemsLayout->addWidget(items,1);
    // Cross-world inventory rules are opt-in. The display name identifies a
    // shared item; numeric pickup kinds and atlas IDs are local to each world.
    // Keep changes queued until this Adventure dialog is accepted.
    QHash<QString, QHash<QString, QSet<QString>>> acceptedWorldRules;
    QHash<QString, QDateTime> acceptedWorldTimestamps;
    const auto offerInventoryRuleSync = [&](int row, const QSet<QString> &fields,
                                            const QString &description) {
        if (row < 0 || row >= items->rowCount() || fields.isEmpty()
            || currentDesignFilePath.isEmpty() || !items->item(row, 0)) {
            if (fields.size() > 1)
                QMessageBox::information(&dialog, QObject::tr("Inventory World Sync"),
                    QObject::tr("Select an inventory item in a saved world first."));
            return;
        }
        const QString name = items->item(row, 0)->text().trimmed();
        if (name.isEmpty()) return;
        const QString key = name.toCaseFolded();
        int occurrences = 0;
        for (int i = 0; i < items->rowCount(); ++i)
            if (items->item(i, 0) && items->item(i, 0)->text().trimmed().toCaseFolded() == key)
                ++occurrences;
        if (occurrences != 1) {
            QMessageBox::information(&dialog, QObject::tr("Inventory World Sync"),
                QObject::tr("'%1' has duplicate names in this world. Rename the duplicates before syncing.").arg(name));
            return;
        }

        QJsonObject sourceItem;
        for (const QJsonValue &entry : tableItems(items)) {
            const QJsonObject candidate = entry.toObject();
            if (candidate.value(QStringLiteral("name")).toString().trimmed().toCaseFolded() == key) {
                sourceItem = candidate;
                break;
            }
        }
        if (sourceItem.isEmpty()) return;

        // Old worlds may omit droppable and useConsume. Compare their actual
        // UI/runtime defaults, not null JSON values, to avoid false changes.
        const auto ruleValue = [](const QJsonObject &item, const QString &field) -> QJsonValue {
            if (field == QStringLiteral("droppable"))
                return item.value(field).isBool() ? item.value(field)
                    : QJsonValue(item.value(QStringLiteral("discardable")).toBool(false));
            if (field == QStringLiteral("discardable")) return item.value(field).toBool(false);
            if (field == QStringLiteral("capacity")) return item.value(field).toInt(1);
            if (field == QStringLiteral("useStat")) return item.value(field).toString();
            if (field == QStringLiteral("useDelta")) return item.value(field).toInt(0);
            if (field == QStringLiteral("useConsume")) return item.value(field).toBool(true);
            return item.value(field);
        };
        const auto ruleLabel = [](const QString &field) -> QString {
            if (field == QStringLiteral("droppable")) return QObject::tr("Can Drop");
            if (field == QStringLiteral("discardable")) return QObject::tr("Can Discard");
            if (field == QStringLiteral("capacity")) return QObject::tr("Max Owned");
            if (field == QStringLiteral("useStat")) return QObject::tr("USE Stat");
            if (field == QStringLiteral("useDelta")) return QObject::tr("USE Amount");
            if (field == QStringLiteral("useConsume")) return QObject::tr("USE Consumes Item");
            return field;
        };
        const auto ruleText = [](const QJsonValue &value) -> QString {
            if (value.isBool()) return value.toBool() ? QObject::tr("Yes") : QObject::tr("No");
            if (value.isString()) {
                const QString valueText = value.toString();
                return valueText.isEmpty() ? QObject::tr("None") : valueText;
            }
            return QString::number(value.toInt());
        };

        const QDir project(QFileInfo(currentDesignFilePath).absolutePath());
        const QString current = QDir::cleanPath(QFileInfo(currentDesignFilePath).absoluteFilePath());
        QHash<QString, QSet<QString>> differing;
        QHash<QString, QDateTime> times;
        QStringList differences, matched, blocked;
        QDirIterator it(project.absolutePath(), QStringList{QStringLiteral("*.sbgm")},
                        QDir::Files, QDirIterator::Subdirectories);
        int scanned = 0;
        while (it.hasNext() && scanned++ < 256) {
            const QString path = QDir::cleanPath(QFileInfo(it.next()).absoluteFilePath());
            if (path == current || QFileInfo(path).isSymLink()) continue;
            const QString relative = QDir::fromNativeSeparators(project.relativeFilePath(path));
            if (relative.startsWith(QStringLiteral(".codergirl/"))
                || relative.startsWith(QStringLiteral("worlds/"))
                || relative.startsWith(QStringLiteral("buildv1/"))) continue;
            QFile input(path);
            if (!input.open(QIODevice::ReadOnly) || input.size() > 16 * 1024 * 1024) continue;
            QJsonParseError error;
            const QJsonDocument document = QJsonDocument::fromJson(input.readAll(), &error);
            if (error.error != QJsonParseError::NoError || !document.isObject()) continue;
            const QJsonObject world = document.object();
            if (world.value(QStringLiteral("format")).toString() != QStringLiteral("SIDBOX-GAME-DESIGN")
                || world.value(QStringLiteral("version")).toInt() != 1) continue;
            QJsonObject targetItem;
            int count = 0;
            for (const QJsonValue &entry : world.value(QStringLiteral("adventure")).toObject()
                                                    .value(QStringLiteral("items")).toArray()) {
                const QJsonObject candidate = entry.toObject();
                if (candidate.value(QStringLiteral("name")).toString().trimmed().toCaseFolded() == key) {
                    targetItem = candidate;
                    ++count;
                }
            }
            if (count != 1) continue; // A duplicate is ambiguous, not a sync target.
            matched.append(relative);
            times.insert(path, QFileInfo(path).lastModified());
            QStringList changeLines;
            for (const QString &field : fields) {
                const QJsonValue before = ruleValue(targetItem, field);
                const QJsonValue after = ruleValue(sourceItem, field);
                if (before == after) continue;
                if (field == QStringLiteral("discardable") && after.toBool()) {
                    // Don't offer a rule that cannot be applied: a quest item
                    // still required by an NPC cannot be destroyed.
                    const QJsonObject adventure = world.value(QStringLiteral("adventure")).toObject();
                    const QJsonArray targetItems = adventure.value(QStringLiteral("items")).toArray();
                    int targetIndex = -1;
                    for (int i = 0; i < targetItems.size(); ++i)
                        if (targetItems[i].toObject().value(QStringLiteral("name")).toString()
                                .trimmed().toCaseFolded() == key) targetIndex = i;
                    bool required = false;
                    for (const QJsonValue &nodeValue : adventure.value(QStringLiteral("nodes")).toArray()) {
                        for (const QJsonValue &choiceValue : nodeValue.toObject().value(QStringLiteral("choices")).toArray()) {
                            const QJsonObject choice = choiceValue.toObject();
                            if (choice.value(QStringLiteral("requires")).toInt(-1) == targetIndex
                                || choice.value(QStringLiteral("take")).toInt(-1) == targetIndex) required = true;
                            for (const QJsonValue &entry : choice.value(QStringLiteral("exchange")).toObject()
                                                            .value(QStringLiteral("items")).toArray())
                                if (entry.toInt(-1) == targetIndex) required = true;
                        }
                    }
                    if (required) {
                        blocked.append(QObject::tr("%1: Can Discard is locked by NPC dialogue")
                            .arg(relative));
                        continue;
                    }
                }
                differing[path].insert(field);
                changeLines.append(QObject::tr("    %1: %2 -> %3")
                    .arg(ruleLabel(field), ruleText(before), ruleText(after)));
            }
            if (!changeLines.isEmpty())
                differences.append(relative + QStringLiteral("\n") + changeLines.join(QStringLiteral("\n")));
        }
        // Each request replaces older approvals for these exact fields. A
        // previously approved Yes followed by No must never apply an old value.
        const auto clearPreviousApproval = [&] {
            auto itemIt = acceptedWorldRules.find(key);
            if (itemIt == acceptedWorldRules.end()) return;
            for (auto worldIt = itemIt->begin(); worldIt != itemIt->end();) {
                for (const QString &field : fields) worldIt->remove(field);
                if (worldIt->isEmpty()) worldIt = itemIt->erase(worldIt);
                else ++worldIt;
            }
            if (itemIt->isEmpty()) acceptedWorldRules.erase(itemIt);
        };
        if (matched.isEmpty()) {
            if (fields.size() > 1)
                QMessageBox::information(&dialog, QObject::tr("Inventory World Sync"),
                    QObject::tr("No other saved world contains one unambiguous inventory item named '%1'.\n\n"
                                "The inventory ITEM name must match (ignoring capitals). Object names and pickup numbers don't count.")
                        .arg(name));
            return;
        }
        if (differences.isEmpty()) {
            clearPreviousApproval();
            QString status = QObject::tr("No applicable differences for '%1' (%2) across %3 matching saved world(s).\n\n"
                                  "Earlier queued changes for these rules were cleared.")
                                .arg(name, description).arg(matched.size());
            if (!blocked.isEmpty())
                status += QObject::tr("\n\nProtected rules NOT copied:\n%1")
                    .arg(blocked.join(QStringLiteral("\n")));
            QMessageBox::information(&dialog, QObject::tr("Inventory World Sync"), status);
            return;
        }
        std::sort(differences.begin(), differences.end(), [](const QString &a, const QString &b) {
            return a.compare(b, Qt::CaseInsensitive) < 0;
        });
        QString proposal = QObject::tr("Item: %1\n\nChanges proposed for the other saved worlds:\n\n%2\n\n"
                       "YES: queue these differences to copy when you press OK in Adventure Editor.\n"
                       "NO: leave other worlds unchanged, clearing earlier queued choices for these rules.\n\n"
                       "Artwork, starting quantities, pickup numbers and NPC dialogue stay untouched.")
                .arg(name, differences.join(QStringLiteral("\n\n")));
        if (!blocked.isEmpty())
            proposal += QObject::tr("\n\nProtected rules NOT included:\n%1")
                .arg(blocked.join(QStringLiteral("\n")));
        const auto choice = QMessageBox::question(&dialog,
            QObject::tr("Copy Inventory Rules to Other Worlds?"), proposal,
            QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        clearPreviousApproval();
        if (choice != QMessageBox::Yes) return;
        for (auto pathIt = differing.constBegin(); pathIt != differing.constEnd(); ++pathIt) {
            acceptedWorldRules[key][pathIt.key()].unite(pathIt.value());
            acceptedWorldTimestamps.insert(pathIt.key(), times.value(pathIt.key()));
        }
    };

    const QJsonArray oldItems = old.value("items").toArray();
    const QJsonArray customKinds = old.value("pickupTypes").toArray();
    QSet<QString> protectedItemNames;
    const auto noteRequirements = [&](const QJsonObject &adventure) {
        const QJsonArray inventory=adventure.value("items").toArray();
        for (const QJsonValue &nodeValue : adventure.value("nodes").toArray()) {
            for (const QJsonValue &choiceValue : nodeValue.toObject().value("choices").toArray()) {
                const QJsonObject choice=choiceValue.toObject();
                for (const char *key : {"requires", "take"}) {
                    const int index=choice.value(QLatin1String(key)).toInt(-1);
                    if (index>=0 && index<inventory.size())
                        protectedItemNames.insert(inventory[index].toObject().value("name").toString().trimmed().toCaseFolded());
                }
                for(const QJsonValue &offered : choice.value("exchange").toObject().value("items").toArray()) {
                    const int index=offered.toInt(-1);
                    if(index>=0 && index<inventory.size())
                        protectedItemNames.insert(inventory[index].toObject().value("name").toString().trimmed().toCaseFolded());
                }
            }
        }
    };
    noteRequirements(old);
    if (!currentDesignFilePath.isEmpty()) {
        const QDir project(QFileInfo(currentDesignFilePath).absolutePath());
        QDirIterator it(project.absolutePath(),QStringList{QStringLiteral("*.sbgm")},
                        QDir::Files,QDirIterator::Subdirectories);
        while (it.hasNext()) {
            const QString filePath=it.next();
            const QString relative=project.relativeFilePath(filePath);
            if (relative.startsWith(QStringLiteral("worlds/")) ||
                relative.startsWith(QStringLiteral("buildv1/")) ||
                relative.startsWith(QStringLiteral(".codergirl/"))) continue;
            QFile file(filePath);
            if (!file.open(QIODevice::ReadOnly) || file.size()>16*1024*1024) continue;
            const QJsonDocument saved=QJsonDocument::fromJson(file.readAll());
            if (saved.isObject()) noteRequirements(saved.object().value("adventure").toObject());
        }
    }
    /* Stat list is defined in Create / Edit Player, not in an arbitrary world.
       Reading the shared .sbpi keeps spelling/case consistent with generated C. */
    QStringList useStats{QStringLiteral("health"),QStringLiteral("lives"),QStringLiteral("score")};
    if (!currentDesignFilePath.isEmpty()) {
        QDir parent(QFileInfo(currentDesignFilePath).absolutePath());
        for (int level=0; level<5; ++level) {
            QFile file(parent.filePath(QStringLiteral("players/player.sbpi")));
            if (file.open(QIODevice::ReadOnly)) {
                const QJsonObject profile=QJsonDocument::fromJson(file.readAll()).object();
                for (const QJsonValue &stat : profile.value(QStringLiteral("customStats")).toArray()) {
                    const QString name=stat.toObject().value(QStringLiteral("name")).toString().trimmed();
                    if (!name.isEmpty() && !useStats.contains(name)) useStats.append(name);
                }
                break;
            }
            if (!parent.cdUp()) break;
        }
    }
    // Inventory icon numbers are saved in Adventure data. Their QTableWidget
    // pictures are transient UI state, so rebuild them when the editor opens
    // and whenever the selected dialogue atlas or tile size changes.
    const auto refreshInventoryIcons = [&] {
        const QString dialogueId = skinAtlas ? skinAtlas->currentData().toString()
                                             : old.value("skinAtlasId").toString();
        const int dialogueSize = tileSize ? tileSize->value() : std::clamp(old.value("tileSize").toInt(8),4,32);
        for(int row=0;row<items->rowCount();++row) {
            auto *entry=items->item(row,4);
            if(!entry)continue;
            entry->setIcon(QIcon());
            const QString chosen=entry->data(Qt::UserRole+3).toString();
            const QString id=chosen.isEmpty()?dialogueId:chosen;
            const int size=chosen.isEmpty()?dialogueSize:qBound(4,(entry->data(Qt::UserRole+4).isValid() ? entry->data(Qt::UserRole+4).toInt() : 8),64);
            const auto atlas=std::find_if(atlases.begin(),atlases.end(),
                [&](const GameAdventureAsset &a){return a.id==id;});
            if(atlas==atlases.end())continue;
            const QImage image=indexedPreview(atlas->path,foregroundPalette);
            if(image.isNull()||image.width()/size==0||image.height()/size==0)continue;
            const QImage picture=adventureInventoryIcon(image,size,
                entry->data(Qt::UserRole).toInt(),
                entry->data(Qt::UserRole+1).toJsonArray(),
                entry->data(Qt::UserRole+2).toBool());
            if(!picture.isNull()) entry->setIcon(QIcon(QPixmap::fromImage(picture.scaled(
                36,36,Qt::KeepAspectRatio,Qt::FastTransformation))));
        }
    };
    const auto selectItemAtlas = [&] {
        const int row=items->currentRow();
        const auto *entry=row>=0?items->item(row,4):nullptr;
        editingIconControls=true;
        adventureMarkDependent(inventoryIconAtlas); inventoryIconAtlas->setEnabled(entry!=nullptr);
        inventoryIconAtlas->setToolTip(entry
            ? QObject::tr("Choose an atlas for this item's icon. Default uses the Dialogue Tile Atlas.")
            : QObject::tr("Disabled: select an inventory item row first."));
        const bool customIconAtlas=entry && !entry->data(Qt::UserRole+3).toString().isEmpty();
        adventureMarkDependent(inventoryIconCell); inventoryIconCell->setEnabled(customIconAtlas);
        inventoryIconCell->setToolTip(!entry
            ? QObject::tr("Disabled: select an inventory item row first.")
            : !customIconAtlas
                ? QObject::tr("Disabled: the default Dialogue Tile Atlas uses its own tile size. Choose a custom Icon Atlas to override the cell size.")
                : QObject::tr("Tile size of the selected item's custom PPB Icon Atlas."));
        if(entry){
            const QString id=entry->data(Qt::UserRole+3).toString();
            inventoryIconAtlas->setCurrentIndex(qMax(0,inventoryIconAtlas->findData(id)));
            inventoryIconCell->setValue(qBound(4,(entry->data(Qt::UserRole+4).isValid() ? entry->data(Qt::UserRole+4).toInt() : 8),64));
        }
        editingIconControls=false;
    };
    QObject::connect(items,&QTableWidget::currentCellChanged,&dialog,
        [&](int,int,int,int){selectItemAtlas();});
    QObject::connect(inventoryIconAtlas,qOverload<int>(&QComboBox::currentIndexChanged),&dialog,[&](int){
        if(editingIconControls||items->currentRow()<0||!items->item(items->currentRow(),4))return;
        items->item(items->currentRow(),4)->setData(Qt::UserRole+3,inventoryIconAtlas->currentData());
        selectItemAtlas();
        refreshInventoryIcons();
    });
    QObject::connect(inventoryIconCell,qOverload<int>(&QSpinBox::valueChanged),&dialog,[&](int n){
        if(editingIconControls||items->currentRow()<0||!items->item(items->currentRow(),4))return;
        items->item(items->currentRow(),4)->setData(Qt::UserRole+4,n);
        refreshInventoryIcons();
    });
    auto appendItem = [&](const QJsonObject &o) {
        const int row=items->rowCount(); items->insertRow(row);
        const QStringList v{ o.value("name").toString("New Item"),
            QString::number(o.value("pickupKind").toInt(0)),
            QString::number(o.value("capacity").toInt(1)),
            QString::number(o.value("initial").toInt(0)),
            QString::number(o.value("icon").toInt(65535)) };
        for(int c=0;c<5;++c) if(c!=1)items->setItem(row,c,cell(v[c]));
        const int iconIndex=std::clamp(o.value("icon").toInt(65535),0,65535);
        auto *iconCell=items->item(row,4);
        iconCell->setData(Qt::UserRole,iconIndex);
        iconCell->setData(Qt::UserRole+1,o.value("iconCells").toArray());
        iconCell->setData(Qt::UserRole+2,o.value("icon2x2").toBool(false));
        iconCell->setData(Qt::UserRole+3,o.value("iconAtlasId").toString());
        iconCell->setData(Qt::UserRole+4,o.value("iconTileSize").toInt(8));
        iconCell->setText(o.value("icon2x2").toBool(false)
            ? QObject::tr("2×2 stamp — double-click to edit")
            : (iconIndex==65535?QObject::tr("No icon — double-click to pick")
                :QObject::tr("Cell %1 — double-click to change").arg(iconIndex)));
        iconCell->setFlags(iconCell->flags() & ~Qt::ItemIsEditable);
        auto *kind=new QComboBox(items);
        kind->addItem(QObject::tr("Manual / NPC dialogue (no automatic pickup)"),0);
        for(int k=1;k<=4;++k) {
            QStringList names;
            for(const auto &object:collectables) if(object.pickupKind==k) names<<object.name;
            const QString typeName=QStringList{QString(),QObject::tr("Coin"),QObject::tr("Health"),
                QObject::tr("Key"),QObject::tr("Gem")}.at(k);
            kind->addItem(QObject::tr("%1: %2 — %3").arg(k).arg(typeName)
                .arg(names.isEmpty()?QObject::tr("no matching objects placed"):collectableInstanceSummary(names).join(QStringLiteral(", "))),k);
        }
        for(const QJsonValue &kv:customKinds){
            const QJsonObject def=kv.toObject();
            const int k=def.value("id").toInt();
            if(k<5 || k>255) continue;
            QStringList names;
            for(const auto &object:collectables) if(object.pickupKind==k) names<<object.name;
            kind->addItem(QObject::tr("%1: %2 — %3").arg(k)
                .arg(def.value("name").toString())
                .arg(names.isEmpty()?QObject::tr("no matching objects placed"):collectableInstanceSummary(names).join(QStringLiteral(", "))),k);
        }
        const int requested=o.value("pickupKind").toInt(0);
        if (kind->findData(requested)<0 && requested>4 && requested<=255)
            kind->addItem(QObject::tr("%1: missing custom pickup definition").arg(requested),requested);
        kind->setCurrentIndex(std::max(0,kind->findData(requested)));
        items->setCellWidget(row,1,kind);
        auto *drop=new QCheckBox(items);
        drop->setChecked(o.value("droppable").toBool(o.value("discardable").toBool(false)));
        drop->setToolTip(QObject::tr("Allow dropping this item on the ground, even if an NPC needs it later."));
        items->setCellWidget(row,5,drop);
        auto *discard=new QCheckBox(items);
        discard->setChecked(o.value("discardable").toBool(false));
        if (protectedItemNames.contains(o.value("name").toString().trimmed().toCaseFolded())) {
            discard->setChecked(false);
            adventureMarkDependent(discard); discard->setEnabled(false);
            discard->setToolTip(QObject::tr("Protected: this item is required/taken by NPC dialogue."));
        } else {
            discard->setToolTip(QObject::tr("Allow the player to discard one copy (confirmation required)."));
        }
        items->setCellWidget(row,6,discard);
        const auto changedRow = [items, drop]() {
            for (int i = 0; i < items->rowCount(); ++i)
                if (items->cellWidget(i, 5) == drop) return i;
            return -1;
        };
        QObject::connect(drop, &QCheckBox::toggled, &dialog, [&, changedRow](bool) {
            offerInventoryRuleSync(changedRow(), {QStringLiteral("droppable")},
                                   QObject::tr("Can Drop"));
        });
        QObject::connect(discard, &QCheckBox::toggled, &dialog, [&, changedRow](bool) {
            offerInventoryRuleSync(changedRow(), {QStringLiteral("discardable")},
                                   QObject::tr("Can Discard"));
        });
        auto *use=new QPushButton(items);
        const QString initialStat=o.value("useStat").toString();
        const int initialDelta=o.value("useDelta").toInt(0);
        use->setProperty("useStat",initialStat);
        use->setProperty("useDelta",initialDelta);
        use->setProperty("useConsume",o.value("useConsume").toBool(true));
        const auto refreshUse=[use]{
            const QString stat=use->property("useStat").toString();
            const int amount=use->property("useDelta").toInt();
            use->setText(stat.isEmpty() || !amount ? QObject::tr("Set USE...")
                : QObject::tr("%1 %2%3").arg(stat,amount>0?QStringLiteral("+"):QString(),QString::number(amount)));
        };
        refreshUse();
        QObject::connect(use,&QPushButton::clicked,&dialog,[&,use,refreshUse]{
            QDialog popup(&dialog); popup.setWindowTitle(QObject::tr("Inventory USE effect"));
            auto *form=new QFormLayout(&popup);
            auto *stat=new QComboBox(&popup);
            stat->addItem(QObject::tr("Not usable"),QString());
            for (const QString &name : useStats) stat->addItem(name,name);
            const QString saved=use->property("useStat").toString();
            if (!saved.isEmpty() && stat->findData(saved)<0) stat->addItem(saved,saved);
            stat->setCurrentIndex(std::max(0,stat->findData(saved)));
            form->addRow(QObject::tr("Change player stat"),stat);
            auto *delta=new QSpinBox(&popup);delta->setRange(-1000000,1000000);
            delta->setValue(use->property("useDelta").toInt());
            form->addRow(QObject::tr("Amount (+ or -)"),delta);
            auto *consume=new QCheckBox(QObject::tr("Consume one item after successful USE"),&popup);
            consume->setChecked(use->property("useConsume").toBool());form->addRow(consume);
            const auto refreshUseControls=[&] {
                const bool usable=!stat->currentData().toString().isEmpty();
                adventureMarkDependent(delta); delta->setEnabled(usable);
                adventureMarkDependent(consume); consume->setEnabled(usable);
                const QString hint=QObject::tr("Disabled: select a player stat above. 'Not usable' has no USE effect.");
                delta->setToolTip(usable ? QObject::tr("Amount to add or remove from the selected stat.") : hint);
                consume->setToolTip(usable ? QObject::tr("Consume one copy only after a successful USE.") : hint);
            };
            QObject::connect(stat,QOverload<int>::of(&QComboBox::currentIndexChanged),
                             &popup,[&](int){refreshUseControls();});
            refreshUseControls();
            auto *buttons=new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel,&popup);
            form->addRow(buttons);
            QObject::connect(buttons,&QDialogButtonBox::accepted,&popup,&QDialog::accept);
            QObject::connect(buttons,&QDialogButtonBox::rejected,&popup,&QDialog::reject);
            if (popup.exec()!=QDialog::Accepted) return;
            use->setProperty("useStat",stat->currentData().toString());
            use->setProperty("useDelta",delta->value());
            use->setProperty("useConsume",consume->isChecked());
            refreshUse();
        });
        items->setCellWidget(row,7,use);
        refreshInventoryIcons();
        items->setCurrentCell(row,0);
        selectItemAtlas();
    };
    for (const auto &v:oldItems) appendItem(v.toObject());
    QObject::connect(items,&QTableWidget::cellDoubleClicked,&dialog,[&](int row,int column){
        if(column!=4 || row<0 || !items->item(row,4)) return;
        auto *iconEntry=items->item(row,4);
        QString selected=iconEntry->data(Qt::UserRole+3).toString();
        int size=qBound(4,(iconEntry->data(Qt::UserRole+4).isValid()
            ? iconEntry->data(Qt::UserRole+4).toInt() : 8),64);
        int chosen=iconEntry->data(Qt::UserRole).toInt();
        QJsonArray quadrants=iconEntry->data(Qt::UserRole+1).toJsonArray();
        bool stamp=iconEntry->data(Qt::UserRole+2).toBool();
        if (!editAdventureInventoryIcon(&dialog,atlases,foregroundPalette,
                skinAtlas?skinAtlas->currentData().toString():old.value("skinAtlasId").toString(),
                tileSize?tileSize->value():old.value("tileSize").toInt(8),
                &selected,&size,&chosen,&quadrants,&stamp)) return;
        iconEntry->setData(Qt::UserRole+3,selected);
        iconEntry->setData(Qt::UserRole+4,size);
        selectItemAtlas();
        iconEntry->setData(Qt::UserRole,chosen);
        iconEntry->setData(Qt::UserRole+1,quadrants);
        iconEntry->setData(Qt::UserRole+2,stamp);
        iconEntry->setText(stamp ? QObject::tr("2×2 stamp — double-click to edit")
            : QObject::tr("Cell %1 — double-click to change").arg(chosen));
        refreshInventoryIcons();
    });
    auto *itemButtons = new QHBoxLayout;
    auto *itemAdd = new QPushButton(QObject::tr("+ Item"), itemsPage);
    auto *itemDel = new QPushButton(QObject::tr("Delete Item"), itemsPage);
    auto *itemSync = new QPushButton(QObject::tr("Sync Selected Item Rules..."), itemsPage);
    itemSync->setToolTip(QObject::tr("Offer to copy Can Drop, Can Discard, Max Owned and USE rules "
                                      "to matching inventory items in other saved worlds."));
    itemButtons->addWidget(itemAdd); itemButtons->addWidget(itemDel);
    itemButtons->addWidget(itemSync); itemButtons->addStretch();
    const auto refreshItemButtons=[&] {
        const bool selected=items->currentRow()>=0 && items->item(items->currentRow(),0);
        adventureMarkDependent(itemDel); itemDel->setEnabled(selected);
        adventureMarkDependent(itemSync); itemSync->setEnabled(selected && !currentDesignFilePath.isEmpty());
        const QString hint=QObject::tr("Disabled: select an inventory item row first.");
        itemDel->setToolTip(selected ? QObject::tr("Remove this inventory item (and remap dialogue item references).") : hint);
        itemSync->setToolTip(!selected ? hint : currentDesignFilePath.isEmpty()
            ? QObject::tr("Disabled: save the world first to locate other saved worlds.")
            : QObject::tr("Copy selected item rules to matching named items in other saved worlds."));
        adventureMarkDependent(itemAdd); itemAdd->setEnabled(items->rowCount()<64);
        itemAdd->setToolTip(items->rowCount()<64 ? QObject::tr("Add an inventory item (maximum 64).")
            : QObject::tr("Disabled: the maximum of 64 inventory items has been reached."));
    };
    QObject::connect(items,&QTableWidget::currentCellChanged,&dialog,
                     [&](int,int,int,int){refreshItemButtons();});
    refreshItemButtons();
    QObject::connect(itemSync, &QPushButton::clicked, &dialog, [&] {
        offerInventoryRuleSync(items->currentRow(),
            {QStringLiteral("droppable"), QStringLiteral("discardable"),
             QStringLiteral("capacity"), QStringLiteral("useStat"),
             QStringLiteral("useDelta"), QStringLiteral("useConsume")},
            QObject::tr("Can Drop, Can Discard, Max Owned and USE rules"));
    });
    itemsLayout->addLayout(itemButtons);
    QObject::connect(itemAdd,&QPushButton::clicked,&dialog,[&] {
        if(items->rowCount()<64) appendItem({});
        refreshItemButtons();
    });
    QObject::connect(itemDel,&QPushButton::clicked,&dialog,[&] {
        const int row=items->currentRow();
        if (row>=0 && QMessageBox::question(&dialog,QObject::tr("Remove Item"),
                QObject::tr("Delete item %1? Dialogue choice item references will be cleared.").arg(row))
                == QMessageBox::Yes) {
            items->removeRow(row);
            refreshItemButtons();
            for (int i=0;i<nodes.size();++i) {
                QJsonObject node=nodes[i].toObject();
                QJsonArray choices=node.value("choices").toArray();
                for (int j=0;j<choices.size();++j) {
                    QJsonObject c=choices[j].toObject();
                    for (const char *field : {"requires","give","take"}) {
                        int idx=c.value(QLatin1String(field)).toInt(-1);
                        if(idx==row) c.insert(QLatin1String(field),-1);
                        else if(idx>row) c.insert(QLatin1String(field),idx-1);
                    }
                    QJsonObject exchange=c.value("exchange").toObject();
                    const QJsonArray requested=exchange.value("items").toArray();
                    QJsonArray remapped;
                    for(const QJsonValue &entry:requested) {
                        const int index=entry.toInt(-1);
                        if(index==row || index<0)continue;
                        remapped.append(index>row?index-1:index);
                    }
                    exchange.insert("items",remapped);
                    const int tracked=exchange.value("wrongRepeatItem").toInt(-1);
                    if(tracked==row) {
                        exchange.insert("wrongRepeatEnabled",false);
                        exchange.insert("wrongRepeatItem",-1);
                    } else if(tracked>row) exchange.insert("wrongRepeatItem",tracked-1);
                    if(remapped.isEmpty())exchange.insert("enabled",false);
                    if(!exchange.isEmpty())c.insert("exchange",exchange);
                    choices[j]=c;
                }
                node.insert("choices",choices);nodes[i]=node;
            }
        }
    });
    tabs->addTab(itemsPage,QObject::tr("Inventory Items"));

    auto *npcPage = new QWidget(tabs); auto *npcLayout = new QVBoxLayout(npcPage);
    auto *npcHelp = new QLabel(QObject::tr(
        "NPCs use placed Sprites from the World Editor. Uncheck Initially visible to "
        "start an NPC hidden. Successful dialogue choices can Show/Hide/Toggle up "
        "to two NPCs; visibility survives world travel."),npcPage);
    npcHelp->setWordWrap(true);
    npcLayout->addWidget(npcHelp);
    auto *npcs = new QTableWidget(0,5,npcPage);
    npcs->setHorizontalHeaderLabels({QObject::tr("Sprite"),QObject::tr("Start node"),
        QObject::tr("Talk radius (px)"),QObject::tr("After helped (optional)"),
        QObject::tr("Initially visible")});
    // Give the two dialogue selectors their full selected titles. Sprite uses
    // the space left over; horizontal scrolling remains available on small screens.
    npcs->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    npcs->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Interactive);
    npcs->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Interactive);
    npcs->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Interactive);
    npcs->horizontalHeader()->setSectionResizeMode(4,QHeaderView::Interactive);
    npcs->setColumnWidth(4,140);
    npcs->horizontalHeader()->setMinimumSectionSize(100);
    npcs->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    npcLayout->addWidget(npcs,1);
    auto sizeNpcColumns = [&] {
        int startWidth = npcs->fontMetrics().horizontalAdvance(QObject::tr("Start node"))+36;
        int helpedWidth = npcs->fontMetrics().horizontalAdvance(QObject::tr("After helped (optional)"))+36;
        for (int row=0; row<npcs->rowCount(); ++row) {
            for (int column : {1,3}) {
                auto *combo=qobject_cast<QComboBox*>(npcs->cellWidget(row,column));
                if (!combo) continue;
                combo->setToolTip(combo->currentText());
                // Use the selected title, not the longest title in *every* node.
                const int needed=combo->fontMetrics().horizontalAdvance(combo->currentText())+54;
                if (column==1) startWidth=std::max(startWidth,needed);
                else helpedWidth=std::max(helpedWidth,needed);
            }
        }
        npcs->setColumnWidth(1,std::max(220,startWidth));
        npcs->setColumnWidth(2,145);
        npcs->setColumnWidth(3,std::max(250,helpedWidth));
    };
    auto appendNpc = [&](const QString &id,int node,int radius, const QJsonObject &animation = QJsonObject(), int doneNode = -1, bool initiallyVisible = true) {
        const int row=npcs->rowCount(); npcs->insertRow(row);
        auto it=std::find_if(sprites.begin(),sprites.end(),[&](const auto &s){return s.id==id;});
        auto *name=cell(it==sprites.end() ? QObject::tr("Missing Sprite") : it->name);
        name->setData(Qt::UserRole,id);
        name->setData(Qt::UserRole + 1,animation); name->setFlags(name->flags() & ~Qt::ItemIsEditable);
        npcs->setItem(row,0,name);
        auto *startNode=new DialogueTreeCombo(npcs,&nodes,&dialogueFolders);
        for(int i=0;i<nodes.size();++i) startNode->addItem(dialogueTitle(nodes[i].toObject(),i),i);
        if(startNode->count()==0)startNode->addItem(QObject::tr("Create a dialogue node first"),0);
        startNode->setCurrentIndex(std::max(0,startNode->findData(node)));
        npcs->setCellWidget(row,1,startNode);
        npcs->setItem(row,2,cell(QString::number(radius)));
        auto *completed = new DialogueTreeCombo(npcs,&nodes,&dialogueFolders);
        completed->addItem(QObject::tr("Use normal opening dialogue"),-1);
        for(int i=0;i<nodes.size();++i) completed->addItem(dialogueTitle(nodes[i].toObject(),i),i);
        completed->setCurrentIndex(std::max(0,completed->findData(doneNode)));
        npcs->setCellWidget(row,3,completed);
        auto *visible = cell(QString());
        visible->setFlags((visible->flags() | Qt::ItemIsUserCheckable) & ~Qt::ItemIsEditable);
        visible->setCheckState(initiallyVisible ? Qt::Checked : Qt::Unchecked);
        visible->setTextAlignment(Qt::AlignCenter);
        npcs->setItem(row,4,visible);
        QObject::connect(startNode,QOverload<int>::of(&QComboBox::currentIndexChanged),npcs,[&,startNode](int){
            startNode->setToolTip(startNode->currentText());sizeNpcColumns();
        });
        QObject::connect(completed,QOverload<int>::of(&QComboBox::currentIndexChanged),npcs,[&,completed](int){
            completed->setToolTip(completed->currentText());sizeNpcColumns();
        });
        sizeNpcColumns();
    };
    for(const auto &v: old.value("npcs").toArray()) {
        const QJsonObject o=v.toObject(); appendNpc(o.value("spriteId").toString(),o.value("node").toInt(),o.value("radius").toInt(48),o.value("animation").toObject(),o.value("doneNode").toInt(-1),o.value("initiallyVisible").toBool(true));
    }
    auto refreshNpcNodes=[&] {
        for(int r=0;r<npcs->rowCount();++r){
            auto *cb=qobject_cast<QComboBox*>(npcs->cellWidget(r,1)); if(!cb)continue;
            const int previous=cb->currentData().toInt();cb->clear();
            for(int i=0;i<nodes.size();++i)cb->addItem(dialogueTitle(nodes[i].toObject(),i),i);
            if(cb->count()==0)cb->addItem(QObject::tr("Create a dialogue node first"),0);
            cb->setCurrentIndex(std::max(0,cb->findData(previous)));
            auto *done=qobject_cast<QComboBox*>(npcs->cellWidget(r,3));
            if (!done) continue;
            const int donePrevious=done->currentData().toInt();
            done->clear();done->addItem(QObject::tr("Use normal opening dialogue"),-1);
            for(int i=0;i<nodes.size();++i)done->addItem(dialogueTitle(nodes[i].toObject(),i),i);
            done->setCurrentIndex(std::max(0,done->findData(donePrevious)));
        }
    };
    auto *npcButtons = new QHBoxLayout;
    auto *npcAdd = new QPushButton(QObject::tr("+ NPC"),npcPage);
    auto *npcDel = new QPushButton(QObject::tr("Delete NPC"),npcPage);
    auto *npcAnim = new QPushButton(QObject::tr("NPC Animations..."),npcPage);
    npcButtons->addWidget(npcAdd); npcButtons->addWidget(npcAnim); npcButtons->addWidget(npcDel); npcButtons->addStretch();
    npcLayout->addLayout(npcButtons);
    const auto refreshNpcButtons=[&] {
        const bool selected=npcs->currentRow()>=0 && npcs->item(npcs->currentRow(),0);
        adventureMarkDependent(npcDel); npcDel->setEnabled(selected);
        adventureMarkDependent(npcAnim); npcAnim->setEnabled(selected);
        const QString selectHint=QObject::tr("Disabled: select an NPC row first.");
        npcDel->setToolTip(selected ? QObject::tr("Remove the selected NPC, keeping its placed Sprite.") : selectHint);
        npcAnim->setToolTip(selected ? QObject::tr("Edit animation frames for the selected NPC.") : selectHint);
        bool unused=false;
        for (const auto &sprite:sprites) {
            bool taken=false;
            for(int n=0;n<npcs->rowCount();++n)
                if(npcs->item(n,0) && npcs->item(n,0)->data(Qt::UserRole).toString()==sprite.id) {taken=true;break;}
            if(!taken){unused=true;break;}
        }
        adventureMarkDependent(npcAdd); npcAdd->setEnabled(unused);
        npcAdd->setToolTip(unused ? QObject::tr("Add a placed Sprite as an Adventure NPC.")
            : QObject::tr("Disabled: place a new Sprite in World Designer first; all placed Sprites already have NPC entries (or none exist)."));
    };
    QObject::connect(npcs,&QTableWidget::currentCellChanged,&dialog,
                     [&](int,int,int,int){refreshNpcButtons();});
    refreshNpcButtons();
    QObject::connect(npcAdd,&QPushButton::clicked,&dialog,[&] {
        QDialog picker(&dialog); picker.setWindowTitle(QObject::tr("Choose Placed Sprite"));
        auto *v=new QVBoxLayout(&picker); auto *cb=new QComboBox(&picker);
        for(const auto &s:sprites) {
            bool alreadyUsed=false;
            for (int i=0;i<npcs->rowCount();++i)
                if (npcs->item(i,0) && npcs->item(i,0)->data(Qt::UserRole).toString()==s.id)
                    {alreadyUsed=true;break;}
            if (!alreadyUsed) cb->addItem(s.name,s.id);
        }
        v->addWidget(cb);
        auto *b=new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,&picker);
        v->addWidget(b);
        QObject::connect(b,&QDialogButtonBox::accepted,&picker,&QDialog::accept);
        QObject::connect(b,&QDialogButtonBox::rejected,&picker,&QDialog::reject);
        if(cb->count() && picker.exec()==QDialog::Accepted)
            appendNpc(cb->currentData().toString(),0,48);
        refreshNpcButtons();
    });
    QObject::connect(npcAnim,&QPushButton::clicked,&dialog,[&] {
        const int row=npcs->currentRow();
        if(row<0 || !npcs->item(row,0)) {
            QMessageBox::information(&dialog,QObject::tr("NPC Animations"),QObject::tr("Select an NPC row first."));
            return;
        }
        auto *name=npcs->item(row,0);
        const QString id=name->data(Qt::UserRole).toString();
        auto it=std::find_if(sprites.begin(),sprites.end(),[&](const auto&s){return s.id==id;});
        if(it==sprites.end())return;
        const QImage atlas=indexedPreview(it->path,foregroundPalette);
        if(atlas.isNull()) {
            QMessageBox::warning(&dialog,QObject::tr("NPC Animations"),QObject::tr("Cannot read this NPC sprite atlas."));
            return;
        }
        const int tileW=it->width, tileH=it->height;
        const int cols=tileW>0?atlas.width()/tileW:0;
        const int rows=tileH>0?atlas.height()/tileH:0;
        const int frames=std::min({it->atlasFrames,cols*rows,256});
        if(frames<1){QMessageBox::warning(&dialog,QObject::tr("NPC Animations"),QObject::tr("No sprite atlas cells."));return;}
        const QJsonObject saved=name->data(Qt::UserRole+1).toJsonObject();
        QDialog anim(&dialog);anim.setWindowTitle(QObject::tr("NPC Animation Designer — %1").arg(it->name));
        anim.setMinimumSize(1040,690); anim.resize(1230,820);
        auto *layout=new QVBoxLayout(&anim);
        auto *help=new QLabel(QObject::tr(
            "Build Idle and Talking animations one frame at a time. Choose any sprite-sheet cell, "
            "reorder frames with Up/Down, and set a DIFFERENT delay on each picture. "
            "Press Play for a live preview. Sprite BOB cells are 0–255."),&anim);
        help->setWordWrap(true);layout->addWidget(help);
        auto *stateTabs=new QTabWidget(&anim);layout->addWidget(stateTabs,1);
        struct AnimUi {
            QListWidget *list=nullptr;
            QLabel *preview=nullptr;
            QSpinBox *delay=nullptr;
            QTimer *timer=nullptr;
            QPushButton *play=nullptr;
            int previewIndex=0;
        } states[2];
        const char *firstKeys[]={"idleFirst","talkFirst"};
        const char *countKeys[]={"idleCount","talkCount"};
        const char *speedKeys[]={"idleSpeed","talkSpeed"};
        const char *framesKeys[]={"idleFrames","talkFrames"};
        auto previewFrame=[&](int state,int chosen){
            AnimUi &ui=states[state];
            if(ui.list->count()==0){ui.preview->setText(QObject::tr("No frames — use Add frame..."));return;}
            chosen=(chosen%ui.list->count()+ui.list->count())%ui.list->count();
            const int idx=ui.list->item(chosen)->data(Qt::UserRole).toInt();
            QImage pic=atlas.copy((idx%cols)*tileW,(idx/cols)*tileH,tileW,tileH);
            ui.preview->setPixmap(QPixmap::fromImage(pic.scaled(
                pic.size()*std::min(5,std::max(1,300/std::max(tileW,tileH))),
                Qt::KeepAspectRatio,Qt::FastTransformation)));
        };
        auto insertFrame=[&](int state,int position,int idx,int delay){
            AnimUi &ui=states[state];
            auto *entry=new QListWidgetItem(ui.list);
            entry->setData(Qt::UserRole,idx);
            entry->setData(Qt::UserRole+1,std::clamp(delay,1,255));
            entry->setText(QObject::tr("Cell %1   —   %2 game frames").arg(idx).arg(delay));
            const QImage pic=atlas.copy((idx%cols)*tileW,(idx/cols)*tileH,tileW,tileH);
            entry->setIcon(QIcon(QPixmap::fromImage(pic.scaled(40,40,Qt::KeepAspectRatio,Qt::FastTransformation))));
            // QListWidgetItem(list) initially appends itself.
            if(position>=0 && position<ui.list->count()-1){
                auto *moved=ui.list->takeItem(ui.list->count()-1);
                ui.list->insertItem(position,moved);
            }
            ui.list->setCurrentItem(entry);
        };
        for(int st=0;st<2;++st){
            const int state=st;
            auto *page=new QWidget(stateTabs);
            auto *v=new QVBoxLayout(page);
            v->addWidget(new QLabel(state?QObject::tr("TALKING — plays during this NPC's conversation")
                :QObject::tr("IDLE — plays when the NPC is not talking"),page));
            AnimUi &ui=states[state];
            ui.list=new QListWidget(page);
            ui.list->setViewMode(QListView::IconMode);
            ui.list->setFlow(QListView::LeftToRight);
            ui.list->setWrapping(true);
            ui.list->setMovement(QListView::Static);
            ui.list->setGridSize(QSize(144,92));
            ui.list->setSpacing(5);
            ui.list->setIconSize(QSize(55,55));
            ui.list->setSelectionMode(QAbstractItemView::SingleSelection);
            auto *workspace=new QHBoxLayout;
            v->addLayout(workspace,1);
            auto *timelinePanel=new QVBoxLayout;
            workspace->addLayout(timelinePanel,3);
            timelinePanel->addWidget(new QLabel(QObject::tr("ANIMATION TIMELINE — select, arrange, and set each frame's delay"),page));
            timelinePanel->addWidget(ui.list,1);
            auto *buttons=new QHBoxLayout;
            auto *add=new QPushButton(QObject::tr("+ Add frame..."),page);
            auto *remove=new QPushButton(QObject::tr("Remove"),page);
            auto *up=new QPushButton(QObject::tr("Move Up"),page);
            auto *down=new QPushButton(QObject::tr("Move Down"),page);
            buttons->addWidget(add);buttons->addWidget(remove);buttons->addWidget(up);buttons->addWidget(down);
            timelinePanel->addLayout(buttons);
            auto *delayLine=new QHBoxLayout;
            delayLine->addWidget(new QLabel(QObject::tr("Selected frame delay (50FPS ticks)"),page));
            ui.delay=new QSpinBox(page);ui.delay->setRange(1,255);ui.delay->setValue(6);
            delayLine->addWidget(ui.delay);delayLine->addStretch();timelinePanel->addLayout(delayLine);
            auto *previewPanel=new QVBoxLayout;
            workspace->addLayout(previewPanel,2);
            previewPanel->addWidget(new QLabel(QObject::tr("LIVE PREVIEW (50 FPS GAME TIMING)"),page));
            ui.preview=new QLabel(page);ui.preview->setMinimumHeight(260);
            ui.preview->setAlignment(Qt::AlignCenter);
            ui.preview->setFrameShape(QFrame::StyledPanel);
            previewPanel->addWidget(ui.preview,1);
            ui.play=new QPushButton(QObject::tr("Play / Stop preview"),page);
            previewPanel->addWidget(ui.play);
            previewPanel->addWidget(new QLabel(QObject::tr("The same frames and delays will be exported to SIDBOX."),page));
            ui.timer=new QTimer(page);
            const QJsonArray savedFrames=saved.value(framesKeys[state]).toArray();
            if(!savedFrames.isEmpty()){
                for(const auto &fv:savedFrames){
                    if(ui.list->count()>=255)break;
                    const QJsonObject o=fv.toObject();
                    insertFrame(state,-1,std::clamp(o.value("index").toInt(),0,frames-1),
                        std::clamp(o.value("delay").toInt(6),1,255));
                }
            } else {
                const int first=std::clamp(saved.value(firstKeys[state]).toInt(0),0,frames-1);
                const int count=std::clamp(saved.value(countKeys[state]).toInt(0),0,frames-first);
                const int oldDelay=std::clamp(saved.value(speedKeys[state]).toInt(state?5:6),1,255);
                for(int k=0;k<count;++k)insertFrame(state,-1,first+k,oldDelay);
            }
            const auto refreshTimeline=[&,state,add,remove,up,down] {
                const auto &a=states[state];
                const int row=a.list->currentRow();
                const int count=a.list->count();
                const bool selected=row>=0 && row<count;
                adventureMarkDependent(add); add->setEnabled(count<255);
                adventureMarkDependent(remove); remove->setEnabled(selected);
                adventureMarkDependent(up); up->setEnabled(selected && row>0);
                adventureMarkDependent(down); down->setEnabled(selected && row<count-1);
                adventureMarkDependent(a.delay); a.delay->setEnabled(selected);
                adventureMarkDependent(a.play); a.play->setEnabled(count>0 || a.timer->isActive());
                add->setToolTip(count<255 ? QObject::tr("Append another sprite frame (up to 255).")
                    : QObject::tr("Disabled: maximum 255 frames reached."));
                const QString selectHint=QObject::tr("Disabled: select an animation frame first.");
                remove->setToolTip(selected ? QObject::tr("Remove the selected frame.") : selectHint);
                a.delay->setToolTip(selected ? QObject::tr("Set the selected frame's duration in 50 FPS ticks.") : selectHint);
                up->setToolTip(!selected ? selectHint : row==0
                    ? QObject::tr("Disabled: selected frame is already first.") : QObject::tr("Move selected frame one position earlier."));
                down->setToolTip(!selected ? selectHint : row==count-1
                    ? QObject::tr("Disabled: selected frame is already last.") : QObject::tr("Move selected frame one position later."));
                a.play->setToolTip(count ? QObject::tr("Start or stop the frame preview.")
                    : QObject::tr("Disabled: add at least one animation frame first."));
            };
            QObject::connect(ui.list,&QListWidget::currentRowChanged,page,[&,state,refreshTimeline](int row){
                refreshTimeline();
                auto &a=states[state];if(row<0){a.preview->setText(QObject::tr("No frame selected"));return;}
                a.delay->blockSignals(true);
                a.delay->setValue(a.list->item(row)->data(Qt::UserRole+1).toInt());
                a.delay->blockSignals(false);
                previewFrame(state,row);
            });
            QObject::connect(ui.delay,QOverload<int>::of(&QSpinBox::valueChanged),page,[&,state](int d){
                auto *item=states[state].list->currentItem();if(!item)return;
                item->setData(Qt::UserRole+1,d);
                item->setText(QObject::tr("Cell %1   —   %2 game frames").arg(item->data(Qt::UserRole).toInt()).arg(d));
            });
            QObject::connect(add,&QPushButton::clicked,page,[&,state]{
                auto *list=states[state].list;if(list->count()>=255)return;
                const int chosen=chooseAdventureAtlasCell(&anim,atlas,tileW,0,frames,tileH);
                if(chosen<0)return;
                insertFrame(state,list->currentRow()+1,chosen,6);
                refreshTimeline();
            });
            QObject::connect(remove,&QPushButton::clicked,page,[&,state]{
                auto *list=states[state].list;
                const int row=list->currentRow();if(row<0)return;
                delete list->takeItem(row);
                if(list->count())list->setCurrentRow(std::min(row,list->count()-1));
                else states[state].preview->setText(QObject::tr("No frames"));
                if(!list->count() && states[state].timer->isActive()) {
                    states[state].timer->stop();states[state].play->setText(QObject::tr("Play preview"));
                }
                refreshTimeline();
            });
            auto move=[&](int state,int step){
                auto *list=states[state].list;const int old=list->currentRow();
                const int next=old+step;if(old<0 || next<0 || next>=list->count())return;
                QListWidgetItem *item=list->takeItem(old);list->insertItem(next,item);list->setCurrentRow(next);
            };
            QObject::connect(up,&QPushButton::clicked,page,[&,state,move,refreshTimeline]{move(state,-1);refreshTimeline();});
            QObject::connect(down,&QPushButton::clicked,page,[&,state,move,refreshTimeline]{move(state,+1);refreshTimeline();});
            QObject::connect(ui.play,&QPushButton::clicked,page,[&,state]{
                auto &a=states[state];
                if(a.timer->isActive()) {a.timer->stop();a.play->setText(QObject::tr("Play preview"));return;}
                if(a.list->count()==0)return;
                a.previewIndex=0;
                previewFrame(state,0);
                a.timer->start(20*a.list->item(0)->data(Qt::UserRole+1).toInt());
                a.play->setText(QObject::tr("Stop preview"));
            });
            QObject::connect(ui.timer,&QTimer::timeout,page,[&,state]{
                auto &a=states[state];if(!a.list->count()){a.timer->stop();return;}
                a.previewIndex=(a.previewIndex+1)%a.list->count();
                previewFrame(state,a.previewIndex);
                a.timer->setInterval(20*a.list->item(a.previewIndex)->data(Qt::UserRole+1).toInt());
            });
            stateTabs->addTab(page,state?QObject::tr("Talking"):QObject::tr("Idle"));
            if(ui.list->count())ui.list->setCurrentRow(0);
            else ui.preview->setText(QObject::tr("No animation yet — press Add frame..."));
            refreshTimeline();
        }
        auto *buttons=new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel,&anim);
        layout->addWidget(buttons);
        QObject::connect(buttons,&QDialogButtonBox::accepted,&anim,&QDialog::accept);
        QObject::connect(buttons,&QDialogButtonBox::rejected,&anim,&QDialog::reject);
        if(anim.exec()!=QDialog::Accepted)return;
        QJsonObject result;
        for(int state=0;state<2;++state){
            const auto *list=states[state].list;
            QJsonArray framesOut;
            for(int k=0;k<list->count();++k){
                const auto *entry=list->item(k);
                QJsonObject frame;
                frame.insert("index",entry->data(Qt::UserRole).toInt());
                frame.insert("delay",entry->data(Qt::UserRole+1).toInt());
                framesOut.append(frame);
            }
            result.insert(framesKeys[state],framesOut);
            // Legacy fields remain for older tools reading existing .sbgm.
            result.insert(firstKeys[state],list->count()?list->item(0)->data(Qt::UserRole).toInt():0);
            result.insert(countKeys[state],list->count());
            result.insert(speedKeys[state],list->count()?list->item(0)->data(Qt::UserRole+1).toInt():6);
        }
        name->setData(Qt::UserRole+1,result);
    });
    QObject::connect(npcDel,&QPushButton::clicked,&dialog,[&] {
        const int row=npcs->currentRow();
        if(row<0 || !npcs->item(row,0)) return;
        const QString name=npcs->item(row,0)->text();
        if(QMessageBox::question(&dialog,QObject::tr("Delete NPC?"),
              QObject::tr("Remove '%1' from Adventure NPCs?\n\nIts placed sprite and any dialogue nodes will be kept.").arg(name),
              QMessageBox::Yes|QMessageBox::No,QMessageBox::No)!=QMessageBox::Yes) return;
        const QString removedId=npcs->item(row,0)->data(Qt::UserRole).toString();
        npcs->removeRow(row);
        refreshNpcButtons();
        /* Clear only now-invalid appearance links, preserving ordinary
         * dialogue and Game Object events. IDs are stable under row reorder. */
        bool stillExists=false;
        for(int n=0;n<npcs->rowCount();++n)
            if(npcs->item(n,0) && npcs->item(n,0)->data(Qt::UserRole).toString()==removedId)
                {stillExists=true;break;}
        if(!stillExists) for(int n=0;n<nodes.size();++n) {
            QJsonObject node=nodes[n].toObject();
            QJsonArray choices=node.value("choices").toArray();
            for(int choice=0;choice<choices.size();++choice) {
                QJsonObject c=choices[choice].toObject();
                for(int e=1;e<=2;++e) {
                    const QString key=QStringLiteral("npcAction%1SpriteId").arg(e);
                    if(c.value(key).toString()==removedId)c.insert(key,QString());
                }
                choices[choice]=c;
            }
            for (int e=1;e<=2;++e) {
                const QString key=QStringLiteral("closeNpcAction%1SpriteId").arg(e);
                if(node.value(key).toString()==removedId) node.insert(key,QString());
            }
            node.insert("choices",choices);nodes[n]=node;
        }
    });
    tabs->addTab(npcPage,QObject::tr("NPCs"));
    QObject::connect(tabs,&QTabWidget::currentChanged,npcs,[&](int){sizeNpcColumns();});

    auto *dialoguePage = new QWidget(tabs); auto *dialogueLayout = new QVBoxLayout(dialoguePage);
    auto *treeHelp=new QLabel(QObject::tr(
        "Organise dialogues into folders for each NPC or part of your story. "
        "Folders change only the editor view: dialogue IDs and game links stay exactly the same. "
        "Double-click a dialogue to edit it."),dialoguePage);
    treeHelp->setWordWrap(true);dialogueLayout->addWidget(treeHelp);
    auto *nodeTree=new QTreeWidget(dialoguePage);
    nodeTree->setHeaderLabels({QObject::tr("Dialogue folders and nodes")});
    nodeTree->setSelectionMode(QAbstractItemView::SingleSelection);
    nodeTree->setUniformRowHeights(true);
    dialogueLayout->addWidget(nodeTree,1);
    auto selectedNode=[&]() -> int {
        auto *entry=nodeTree->currentItem();
        return entry && entry->data(0,Qt::UserRole+1).toString()==QStringLiteral("node")
            ?entry->data(0,Qt::UserRole).toInt():-1;
    };
    auto selectedFolder=[&]() -> QString {
        auto *entry=nodeTree->currentItem();
        if (!entry) return QString();
        if(entry->data(0,Qt::UserRole+1).toString()==QStringLiteral("folder"))
            return entry->data(0,Qt::UserRole+2).toString();
        if(entry->data(0,Qt::UserRole+1).toString()==QStringLiteral("node")) {
            const int row=entry->data(0,Qt::UserRole).toInt();
            return row>=0 && row<nodes.size()?nodes[row].toObject().value("folderId").toString():QString();
        }
        return QString();
    };
    auto redrawNodes=[&](int chooseNode=-2, const QString &chooseFolder=QString()) {
        if(chooseNode==-2)chooseNode=selectedNode();
        const QString oldFolder=chooseFolder.isNull()?selectedFolder():chooseFolder;
        // Preserve collapsed folders when a dialogue is edited or moved.
        QSet<QString> collapsed;
        bool unfiledExpanded=true;
        for(QTreeWidgetItemIterator it(nodeTree); *it; ++it){
            auto *entry=*it;
            if(entry->data(0,Qt::UserRole+1).toString()==QStringLiteral("folder") && !entry->isExpanded())
                collapsed.insert(entry->data(0,Qt::UserRole+2).toString());
            if(entry->data(0,Qt::UserRole+1).toString()==QStringLiteral("unfiled"))
                unfiledExpanded=entry->isExpanded();
        }
        nodeTree->clear();
        QHash<QString,QTreeWidgetItem*> folderItems;
        // Resolve parents before children, even when folders are stored out of order.
        QSet<QString> processed;
        for(int pass=0;pass<=dialogueFolders.size();++pass){
            bool changed=false;
            for(const auto &record:dialogueFolders){
                const QJsonObject folder=record.toObject();
                const QString id=folder.value("id").toString();
                const QString parentId=folder.value("parentId").toString();
                if(id.isEmpty() || processed.contains(id)) continue;
                // Invalid/cyclic parents are shown at root, without editing saved data.
                const bool atRoot=parentId.isEmpty() || pass==dialogueFolders.size();
                if(!atRoot && !folderItems.contains(parentId)) continue;
                auto *parent=folderItems.value(parentId,nullptr);
                auto *entry=parent ? new QTreeWidgetItem(parent) : new QTreeWidgetItem(nodeTree);
                entry->setText(0,folder.value("name").toString(QObject::tr("Unnamed folder")));
                entry->setIcon(0,QIcon::fromTheme(QStringLiteral("folder")));
                entry->setData(0,Qt::UserRole+1,QStringLiteral("folder"));
                entry->setData(0,Qt::UserRole+2,id);
                folderItems.insert(id,entry);processed.insert(id);changed=true;
            }
            if(processed.size()==dialogueFolders.size()) break;
            // On the final pass, attach invalid/cyclic folder parents at root.
            // Their saved IDs remain unchanged.
            if(!changed && pass==dialogueFolders.size()) break;
        }
        auto *unfiled=new QTreeWidgetItem(nodeTree);
        unfiled->setText(0,QObject::tr("Unfiled dialogues"));
        unfiled->setIcon(0,QIcon::fromTheme(QStringLiteral("folder-open")));
        unfiled->setData(0,Qt::UserRole+1,QStringLiteral("unfiled"));
        QTreeWidgetItem *desired=nullptr;
        for(int i=0;i<nodes.size();++i){
            const QJsonObject node=nodes[i].toObject();
            const QString folder=node.value("folderId").toString();
            auto *parent=folderItems.value(folder,unfiled);
            auto *entry=new QTreeWidgetItem(parent);
            entry->setText(0,dialogueTitle(node,i));
            entry->setData(0,Qt::UserRole,i);
            entry->setData(0,Qt::UserRole+1,QStringLiteral("node"));
            entry->setToolTip(0,QObject::tr("Dialogue ID %1 (does not change when you move folders)").arg(i));
            if(i==chooseNode)desired=entry;
        }
        if(!desired && !oldFolder.isEmpty())desired=folderItems.value(oldFolder,nullptr);
        if(!desired)desired=unfiled;
        nodeTree->expandAll();
        for(auto it=folderItems.constBegin();it!=folderItems.constEnd();++it)
            if(collapsed.contains(it.key()))it.value()->setExpanded(false);
        unfiled->setExpanded(unfiledExpanded);
        // Reveal the edited node even if its former parent was collapsed.
        for(auto *parent=desired->parent();parent;parent=parent->parent())parent->setExpanded(true);
        nodeTree->setCurrentItem(desired);
    };
    redrawNodes();
    auto *folderButtons=new QHBoxLayout;
    auto *folderAdd=new QPushButton(QObject::tr("+ Folder / Subfolder"),dialoguePage);
    auto *folderRename=new QPushButton(QObject::tr("Rename Folder..."),dialoguePage);
    auto *folderDelete=new QPushButton(QObject::tr("Delete Folder..."),dialoguePage);
    auto *nodeMove=new QPushButton(QObject::tr("Move Dialogue To..."),dialoguePage);
    folderButtons->addWidget(folderAdd);
    folderButtons->addWidget(folderRename);
    folderButtons->addWidget(folderDelete);
    folderButtons->addWidget(nodeMove);
    folderButtons->addStretch();dialogueLayout->addLayout(folderButtons);
    auto *nodeButtons=new QHBoxLayout;
    auto *nodeAdd=new QPushButton(QObject::tr("+ Dialogue Node"),dialoguePage);
    auto *nodeEdit=new QPushButton(QObject::tr("Edit Dialogue..."),dialoguePage);
    auto *nodeDel=new QPushButton(QObject::tr("Delete Dialogue..."),dialoguePage);
    nodeButtons->addWidget(nodeAdd);nodeButtons->addWidget(nodeEdit);nodeButtons->addWidget(nodeDel);
    nodeButtons->addStretch();dialogueLayout->addLayout(nodeButtons);
    const auto refreshDialogueButtons=[&] {
        const bool isNode=selectedNode()>=0;
        const auto *selectedEntry=nodeTree->currentItem();
        const bool isFolder=selectedEntry &&
            selectedEntry->data(0,Qt::UserRole+1).toString()==QStringLiteral("folder");
        adventureMarkDependent(nodeEdit); nodeEdit->setEnabled(isNode);
        adventureMarkDependent(nodeDel); nodeDel->setEnabled(isNode);
        adventureMarkDependent(nodeMove); nodeMove->setEnabled(isNode);
        adventureMarkDependent(folderRename); folderRename->setEnabled(isFolder);
        adventureMarkDependent(folderDelete); folderDelete->setEnabled(isFolder);
        const QString chooseNode=QObject::tr("Disabled: select a Dialogue node in the tree first.");
        const QString chooseFolder=QObject::tr("Disabled: select a dialogue Folder in the tree first.");
        nodeEdit->setToolTip(isNode ? QObject::tr("Edit the selected dialogue.") : chooseNode);
        nodeDel->setToolTip(isNode ? QObject::tr("Delete the selected dialogue node.") : chooseNode);
        nodeMove->setToolTip(isNode ? QObject::tr("Move this dialogue into a folder.") : chooseNode);
        folderRename->setToolTip(isFolder ? QObject::tr("Rename the selected dialogue folder.") : chooseFolder);
        folderDelete->setToolTip(isFolder ? QObject::tr("Remove the selected folder without deleting its dialogues.") : chooseFolder);
    };
    QObject::connect(nodeTree,&QTreeWidget::itemSelectionChanged,&dialog,[&]{ refreshDialogueButtons(); });
    refreshDialogueButtons();
    QObject::connect(folderAdd,&QPushButton::clicked,&dialog,[&] {
        // Selecting a folder creates a child folder; otherwise make a root folder.
        QString parentId;
        auto *entry=nodeTree->currentItem();
        if(entry && entry->data(0,Qt::UserRole+1).toString()==QStringLiteral("folder"))
            parentId=entry->data(0,Qt::UserRole+2).toString();
        bool ok=false;
        const QString name=QInputDialog::getText(&dialog,QObject::tr("New Dialogue Folder"),
            parentId.isEmpty()?QObject::tr("Folder name:"):QObject::tr("Subfolder name:"),
            QLineEdit::Normal,QString(),&ok).trimmed().left(80);
        if(!ok || name.isEmpty())return;
        QJsonObject folder;
        const QString id=QUuid::createUuid().toString(QUuid::WithoutBraces);
        folder.insert("id",id);folder.insert("name",name);folder.insert("parentId",parentId);
        dialogueFolders.append(folder);
        redrawNodes(-1,id);
    });
    QObject::connect(folderRename,&QPushButton::clicked,&dialog,[&] {
        auto *entry=nodeTree->currentItem();
        if(!entry || entry->data(0,Qt::UserRole+1).toString()!=QStringLiteral("folder")){
            QMessageBox::information(&dialog,QObject::tr("Rename Folder"),QObject::tr("Select a folder first."));return;
        }
        const QString id=entry->data(0,Qt::UserRole+2).toString();
        for(int i=0;i<dialogueFolders.size();++i){
            QJsonObject folder=dialogueFolders[i].toObject();
            if(folder.value("id").toString()!=id)continue;
            bool ok=false;
            const QString name=QInputDialog::getText(&dialog,QObject::tr("Rename Dialogue Folder"),
                QObject::tr("Folder name:"),QLineEdit::Normal,folder.value("name").toString(),&ok).trimmed().left(80);
            if(ok && !name.isEmpty()){
                folder.insert("name",name);dialogueFolders[i]=folder;redrawNodes(-1,id);
            }
            break;
        }
    });
    QObject::connect(folderDelete,&QPushButton::clicked,&dialog,[&] {
        auto *entry=nodeTree->currentItem();
        if(!entry || entry->data(0,Qt::UserRole+1).toString()!=QStringLiteral("folder")){
            QMessageBox::information(&dialog,QObject::tr("Delete Folder"),QObject::tr("Select a folder first."));return;
        }
        const QString id=entry->data(0,Qt::UserRole+2).toString();
        for(int i=0;i<dialogueFolders.size();++i){
            const QJsonObject folder=dialogueFolders[i].toObject();
            if(folder.value("id").toString()!=id)continue;
            if(QMessageBox::question(&dialog,QObject::tr("Delete Dialogue Folder?"),
                QObject::tr("Delete folder '%1'? Dialogues will be moved to its parent folder, "
                            "and subfolders will be kept. No dialogue IDs or links will be changed.")
                    .arg(folder.value("name").toString()),
                QMessageBox::Yes|QMessageBox::No,QMessageBox::No)!=QMessageBox::Yes)return;
            const QString parentId=folder.value("parentId").toString();
            dialogueFolders.removeAt(i);
            for(int j=0;j<dialogueFolders.size();++j){
                QJsonObject child=dialogueFolders[j].toObject();
                if(child.value("parentId").toString()==id){
                    child.insert("parentId",parentId);dialogueFolders[j]=child;
                }
            }
            for(int j=0;j<nodes.size();++j){
                QJsonObject node=nodes[j].toObject();
                if(node.value("folderId").toString()==id){
                    node.insert("folderId",parentId);nodes[j]=node;
                }
            }
            redrawNodes(-1,parentId);break;
        }
    });
    QObject::connect(nodeMove,&QPushButton::clicked,&dialog,[&] {
        const int row=selectedNode();
        if(row<0){
            QMessageBox::information(&dialog,QObject::tr("Move Dialogue"),QObject::tr("Select a dialogue node first."));return;
        }
        QDialog picker(&dialog);picker.setWindowTitle(QObject::tr("Move Dialogue %1 to Folder").arg(row));
        auto *layout=new QVBoxLayout(&picker);
        layout->addWidget(new QLabel(QObject::tr("Choose a folder. This does not change the dialogue ID."),&picker));
        auto *dest=new QComboBox(&picker);
        dest->addItem(QObject::tr("Unfiled dialogues"),QString());
        QHash<QString,QJsonObject> byId;
        for(const auto &record:dialogueFolders){
            QJsonObject folder=record.toObject();byId.insert(folder.value("id").toString(),folder);
        }
        for(const auto &record:dialogueFolders){
            const QJsonObject folder=record.toObject();
            QString path=folder.value("name").toString();
            QString id=folder.value("parentId").toString();QSet<QString> seen;
            while(!id.isEmpty() && byId.contains(id) && !seen.contains(id)){
                seen.insert(id); const QJsonObject parent=byId.value(id);
                path=parent.value("name").toString()+QStringLiteral(" / ")+path;
                id=parent.value("parentId").toString();
            }
            dest->addItem(path,folder.value("id").toString());
        }
        dest->setCurrentIndex(std::max(0,dest->findData(nodes[row].toObject().value("folderId").toString())));
        layout->addWidget(dest);
        auto *buttons=new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel,&picker);
        layout->addWidget(buttons);
        QObject::connect(buttons,&QDialogButtonBox::accepted,&picker,&QDialog::accept);
        QObject::connect(buttons,&QDialogButtonBox::rejected,&picker,&QDialog::reject);
        if(picker.exec()!=QDialog::Accepted)return;
        QJsonObject node=nodes[row].toObject();
        node.insert("folderId",dest->currentData().toString());nodes[row]=node;
        redrawNodes(row);
    });
    QObject::connect(nodeAdd,&QPushButton::clicked,&dialog,[&] {
        if(nodes.size()>=256)return;
        const QString folder=selectedFolder();
        // Stage 5.34.3: A new dialogue in an NPC's folder tree starts with
        // the TOP-LEVEL folder name as Speaker. Nested story folders inherit
        // the same NPC name; Unfiled keeps the original "NPC" default.
        QString speaker=QStringLiteral("NPC");
        QTreeWidgetItem *root=nodeTree->currentItem();
        if(root && root->data(0,Qt::UserRole+1).toString()==QStringLiteral("node"))
            root=root->parent();
        while(root && root->parent()
              && root->parent()->data(0,Qt::UserRole+1).toString()==QStringLiteral("folder"))
            root=root->parent();
        if(root && root->data(0,Qt::UserRole+1).toString()==QStringLiteral("folder")) {
            const QString name=root->text(0).trimmed();
            if(!name.isEmpty()) speaker=name.left(36); // Speaker field limit
        }
        QJsonObject node;node.insert("speaker",speaker);node.insert("text","Hello!");
        node.insert("choices",defaultChoices());
        if(!folder.isEmpty())node.insert("folderId",folder);
        nodes.append(node);
        redrawNodes(nodes.size()-1);refreshNpcNodes();
    });
    auto doNodeEdit=[&] {
        const int row=selectedNode();
        if(row<0){
            QMessageBox::information(&dialog,QObject::tr("Edit Dialogue"),QObject::tr("Select a dialogue node first."));return;
        }
        editNode(&dialog,nodes,row,tableItems(items),worldObjects,npcs,dialogueFolders,currentDesignFilePath);
        redrawNodes(row);refreshNpcNodes();sizeNpcColumns();
    };
    QObject::connect(nodeEdit,&QPushButton::clicked,&dialog,doNodeEdit);
    QObject::connect(nodeTree,&QTreeWidget::itemDoubleClicked,&dialog,[&](QTreeWidgetItem *entry,int){
        if(entry && entry->data(0,Qt::UserRole+1).toString()==QStringLiteral("node"))doNodeEdit();
    });
    QObject::connect(nodeDel,&QPushButton::clicked,&dialog,[&] {
        const int row=selectedNode();if(row<0)return;
        if(QMessageBox::question(&dialog,QObject::tr("Delete Dialogue"),
            QObject::tr("Remove dialogue ID %1 and update numeric references? "
                        "Deleting a dialogue is different from moving it between folders.").arg(row),
            QMessageBox::Yes|QMessageBox::No,QMessageBox::No)!=QMessageBox::Yes)return;
        nodes.removeAt(row);
        for(int i=0;i<nodes.size();++i){
            QJsonObject node=nodes[i].toObject();QJsonArray cs=node.value("choices").toArray();
            for(int c=0;c<cs.size();++c){
                QJsonObject choice=cs[c].toObject();const int next=choice.value("next").toInt(-1);
                if(next==row)choice.insert("next",-1);
                else if(next>row)choice.insert("next",next-1);
                // Branch IDs are numerical and must follow dialogue deletion.
                const auto remapNode=[&](int id){return id==row ? -1 : id>row ? id-1 : id;};
                for(const char *key : {"missingNext"})
                    choice.insert(QLatin1String(key),remapNode(choice.value(QLatin1String(key)).toInt(-1)));
                QJsonObject exchange=choice.value("exchange").toObject();
                if(!exchange.isEmpty()) {
                    exchange.insert("wrongNext",remapNode(exchange.value("wrongNext").toInt(-1)));
                    exchange.insert("partialNext",remapNode(exchange.value("partialNext").toInt(-1)));
                    for(const char *repeatKey:{"wrongRepeatFirst","wrongRepeatSecond","wrongRepeatThird","wrongRepeatLater"})
                        exchange.insert(QLatin1String(repeatKey),remapNode(exchange.value(QLatin1String(repeatKey)).toInt(-1)));
                    choice.insert("exchange",exchange);
                }
                cs[c]=choice;
            }
            node.insert("choices",cs);nodes[i]=node;
        }
        for(int r=0;r<npcs->rowCount();++r){
            auto *cb=qobject_cast<QComboBox*>(npcs->cellWidget(r,1));if(!cb)continue;
            int next=cb->currentData().toInt();
            if(next>=row)cb->setCurrentIndex(std::max(0,cb->findData(next==row?0:next-1)));
            auto *done=qobject_cast<QComboBox*>(npcs->cellWidget(r,3));
            if(done){
                const int d=done->currentData().toInt();
                if(d>=row)done->setCurrentIndex(std::max(0,done->findData(d==row?-1:d-1)));
            }
        }
        redrawNodes();refreshNpcNodes();sizeNpcColumns();
    });
    tabs->addTab(dialoguePage,QObject::tr("Dialogues & Choices"));

    auto *skinPage=new QWidget(tabs);auto *skinLayout=new QVBoxLayout(skinPage);
    auto *skinForm=new QFormLayout;
    skinAtlas=new QComboBox(skinPage); skinAtlas->addItem(QObject::tr("No atlas (simple box)"),QString());
    for(const auto &atlas:atlases) skinAtlas->addItem(atlas.name,atlas.id);
    skinAtlas->setCurrentIndex(std::max(0,skinAtlas->findData(old.value("skinAtlasId").toString())));
    tileSize=new QSpinBox(skinPage);tileSize->setRange(4,32);tileSize->setValue(old.value("tileSize").toInt(8));
    auto *speed=new QSpinBox(skinPage);speed->setRange(1,30);speed->setValue(old.value("framesPerChar").toInt(2));
    skinForm->addRow(QObject::tr("Dialogue Tile Atlas"),skinAtlas);
    skinForm->addRow(QObject::tr("Tile size (px)"),tileSize);
    int chosenText=std::clamp(old.value("textColourIndex").toInt(15),0,255);
    int chosenOutline=std::clamp(old.value("outlineColourIndex").toInt(1),0,255);
    auto *textColour=new QPushButton(skinPage);
    auto *outline=new QCheckBox(QObject::tr("Outline dialogue text (four directions)"),skinPage);
    outline->setChecked(old.value("textOutline").toBool(false));
    auto *outlineColour=new QPushButton(skinPage);
    adventureMarkDependent(outlineColour); outlineColour->setEnabled(outline->isChecked());
    outlineColour->setToolTip(outline->isChecked()
        ? QObject::tr("Pick the outline colour.")
        : QObject::tr("Disabled: tick 'Outline dialogue text' first."));
    auto decorateColour=[&](QPushButton *button,int idx){
        button->setText(QObject::tr("Index %1 — pick colour...").arg(idx));
        if(foregroundPalette.size()==256){
            QPixmap px(22,22);px.fill(QColor::fromRgba(foregroundPalette[idx]));
            button->setIcon(QIcon(px));button->setIconSize(QSize(22,22));
        }
    };
    decorateColour(textColour,chosenText);decorateColour(outlineColour,chosenOutline);
    QObject::connect(textColour,&QPushButton::clicked,&dialog,[&]{
        const int idx=chooseAdventurePaletteIndex(&dialog,foregroundPalette,chosenText);
        if(idx>=0){chosenText=idx;decorateColour(textColour,chosenText);}
    });
    QObject::connect(outlineColour,&QPushButton::clicked,&dialog,[&]{
        const int idx=chooseAdventurePaletteIndex(&dialog,foregroundPalette,chosenOutline);
        if(idx>=0){chosenOutline=idx;decorateColour(outlineColour,chosenOutline);}
    });
    QObject::connect(outline,&QCheckBox::toggled,outlineColour,[=](bool checked){
        adventureMarkDependent(outlineColour); outlineColour->setEnabled(checked);
        outlineColour->setToolTip(checked
            ? QObject::tr("Pick the outline colour.")
            : QObject::tr("Disabled: tick 'Outline dialogue text' first."));
    });
    auto *colours=new QWidget(skinPage);auto *colourRow=new QHBoxLayout(colours);
    colourRow->setContentsMargins(0,0,0,0);
    colourRow->addWidget(new QLabel(QObject::tr("Text:"),colours));
    colourRow->addWidget(textColour,1);
    colourRow->addWidget(new QLabel(QObject::tr("Outline:"),colours));
    colourRow->addWidget(outlineColour,1);
    skinForm->addRow(QObject::tr("Foreground colours"),colours);
    skinForm->addRow(QString(),outline);
    skinForm->addRow(QObject::tr("Frames per typed character"),speed);
    skinLayout->addLayout(skinForm);
    auto *instruction=new QLabel(QObject::tr("Select an atlas then click any of the nine frame parts below to pick its tile visually. "
        "Tile Atlas selections can exceed cell 255. Cell size (px) is unchanged."),skinPage);
    instruction->setWordWrap(true);skinLayout->addWidget(instruction);
    auto *tiles=new QGridLayout;QPushButton *tilePick[9];int chosenTiles[9];
    QCheckBox *tileFlipX[9],*tileFlipY[9];
    const QJsonArray indices=old.value("skinIndices").toArray();
    const QJsonArray savedFlips=old.value("skinFlips").toArray();
    for(int i=0;i<9;++i){
        chosenTiles[i]=std::clamp(i<indices.size()?indices[i].toInt(i):i,0,65535);
        tilePick[i]=new QPushButton(skinPage);
        tilePick[i]->setMinimumSize(94,58);
        auto *slot=new QWidget(skinPage);auto *horizontal=new QHBoxLayout(slot);
        horizontal->setContentsMargins(2,2,2,2);
        horizontal->setSpacing(5);
        horizontal->addWidget(tilePick[i]);
        auto *flipRow=new QVBoxLayout;
        flipRow->setSpacing(0);
        tileFlipX[i]=new QCheckBox(QObject::tr("X Flip"),slot);
        tileFlipY[i]=new QCheckBox(QObject::tr("Y Flip"),slot);
        const int flags=i<savedFlips.size()?savedFlips[i].toInt():0;
        tileFlipX[i]->setChecked((flags&4)!=0);
        tileFlipY[i]->setChecked((flags&8)!=0);
        flipRow->addWidget(tileFlipX[i]);flipRow->addWidget(tileFlipY[i]);
        horizontal->addLayout(flipRow);
        tiles->addWidget(slot,i/3,i%3);
    }
    // Dialogue and thought-bubble frames are edited side by side, using the same
    // selected atlas but different cells and flips.
    auto *frameDesignRow=new QHBoxLayout;
    auto *dialogDesign=new QGroupBox(QObject::tr("Dialogue box frame"),skinPage);
    auto *dialogDesignLayout=new QVBoxLayout(dialogDesign);
    dialogDesignLayout->addLayout(tiles);
    frameDesignRow->addWidget(dialogDesign,1);
    auto *thoughtDesign=new QGroupBox(QObject::tr("Thought bubble frame"),skinPage);
    auto *thoughtDesignLayout=new QVBoxLayout(thoughtDesign);
    auto *thoughtTiles=new QGridLayout;
    QPushButton *thoughtPick[9]; QCheckBox *thoughtFlipX[9],*thoughtFlipY[9];
    int thoughtCells[9];
    const QJsonArray thoughtSaved=old.value("thoughtSkinIndices").toArray();
    const QJsonArray thoughtSavedFlips=old.value("thoughtSkinFlips").toArray();
    for(int i=0;i<9;++i){
        thoughtCells[i]=std::clamp(i<thoughtSaved.size()?thoughtSaved[i].toInt(i):chosenTiles[i],0,65535);
        auto *slot=new QWidget(thoughtDesign);
        auto *h=new QHBoxLayout(slot); h->setContentsMargins(2,2,2,2); h->setSpacing(5);
        thoughtPick[i]=new QPushButton(slot);thoughtPick[i]->setMinimumSize(82,58);
        h->addWidget(thoughtPick[i]);
        auto *flips=new QVBoxLayout;
        thoughtFlipX[i]=new QCheckBox(QObject::tr("X Flip"),slot);
        thoughtFlipY[i]=new QCheckBox(QObject::tr("Y Flip"),slot);
        const int flags=i<thoughtSavedFlips.size()?thoughtSavedFlips[i].toInt():0;
        thoughtFlipX[i]->setChecked((flags&4)!=0);
        thoughtFlipY[i]->setChecked((flags&8)!=0);
        flips->addWidget(thoughtFlipX[i]);flips->addWidget(thoughtFlipY[i]);
        h->addLayout(flips);thoughtTiles->addWidget(slot,i/3,i%3);
    }
    thoughtDesignLayout->addLayout(thoughtTiles);
    auto *thoughtPreview=new QLabel(thoughtDesign);
    thoughtPreview->setMinimumHeight(112);thoughtPreview->setAlignment(Qt::AlignCenter);
    thoughtDesignLayout->addWidget(thoughtPreview);
    frameDesignRow->addWidget(thoughtDesign,1);
    skinLayout->addLayout(frameDesignRow);
    auto *preview=new QLabel(skinPage);preview->setMinimumHeight(112);
    preview->setAlignment(Qt::AlignCenter);dialogDesignLayout->addWidget(preview,1);
    auto updatePreview=[&] {
        auto it=std::find_if(atlases.begin(),atlases.end(),[&](const auto &a){return a.id==skinAtlas->currentData().toString();});
        if(it==atlases.end()){
            preview->setText(QObject::tr("No Tile Atlas selected — simple box used."));
            for(int i=0;i<9;++i){tilePick[i]->setText(QObject::tr("Cell %1").arg(chosenTiles[i]));tilePick[i]->setIcon(QIcon());
                thoughtPick[i]->setText(QObject::tr("Cell %1").arg(thoughtCells[i]));thoughtPick[i]->setIcon(QIcon());}
            thoughtPreview->setText(QObject::tr("Simple thought box"));
            return;
        }
        const QImage atlas=indexedPreview(it->path,foregroundPalette);
        const int t=tileSize->value();
        if(atlas.isNull() || t<1 || atlas.width()<t || atlas.height()<t){
            preview->setText(QObject::tr("Atlas unavailable or smaller than tile size"));return;
        }
        const int cols=atlas.width()/t, rows=atlas.height()/t;
        for(int i=0;i<9;++i){
            tilePick[i]->setText(QObject::tr("Cell %1").arg(chosenTiles[i]));
            if(chosenTiles[i]<cols*rows){
                const QImage cellImage=adventureFlippedCell(
                    atlas.copy((chosenTiles[i]%cols)*t,(chosenTiles[i]/cols)*t,t,t),
                    tileFlipX[i]->isChecked(), tileFlipY[i]->isChecked());
                tilePick[i]->setIcon(QIcon(QPixmap::fromImage(cellImage.scaled(40,40,Qt::KeepAspectRatio,Qt::FastTransformation))));
                tilePick[i]->setIconSize(QSize(40,40));
            } else tilePick[i]->setIcon(QIcon());
        }
        for(int i=0;i<9;++i){
            thoughtPick[i]->setText(QObject::tr("Cell %1").arg(thoughtCells[i]));
            if(thoughtCells[i]<cols*rows){
                QImage cellImage=adventureFlippedCell(atlas.copy((thoughtCells[i]%cols)*t,
                    (thoughtCells[i]/cols)*t,t,t),thoughtFlipX[i]->isChecked(),thoughtFlipY[i]->isChecked());
                thoughtPick[i]->setIcon(QIcon(QPixmap::fromImage(cellImage.scaled(36,36,Qt::KeepAspectRatio,Qt::FastTransformation))));
                thoughtPick[i]->setIconSize(QSize(36,36));
            } else thoughtPick[i]->setIcon(QIcon());
        }
        QImage thoughtResult(t*9,t*5,QImage::Format_ARGB32);thoughtResult.fill(Qt::transparent);
        QPainter thoughtPainter(&thoughtResult);
        for(int y=0;y<5;++y)for(int x=0;x<9;++x){
            const int part=(y==0?0:y==4?2:1)*3+(x==0?0:x==8?2:1);
            const int idx=thoughtCells[part];if(idx>=cols*rows)continue;
            thoughtPainter.drawImage(QRect(x*t,y*t,t,t),adventureFlippedCell(
                atlas.copy((idx%cols)*t,(idx/cols)*t,t,t),
                thoughtFlipX[part]->isChecked(),thoughtFlipY[part]->isChecked()));
        }
        thoughtPainter.end();thoughtPreview->setPixmap(QPixmap::fromImage(
            thoughtResult.scaled(thoughtResult.size()*2,Qt::KeepAspectRatio,Qt::FastTransformation)));
        QImage result(t*9,t*5,QImage::Format_ARGB32);result.fill(Qt::transparent);
        QPainter painter(&result);
        for(int y=0;y<5;++y)for(int x=0;x<9;++x){
            const int slot=(y==0?0:y==4?2:1)*3+(x==0?0:x==8?2:1);
            const int idx=chosenTiles[slot];
            if(idx>=cols*rows)continue;
            painter.drawImage(QRect(x*t,y*t,t,t), adventureFlippedCell(
                atlas.copy((idx%cols)*t,(idx/cols)*t,t,t),
                tileFlipX[slot]->isChecked(), tileFlipY[slot]->isChecked()));
        }
        painter.end();preview->setPixmap(QPixmap::fromImage(result.scaled(result.size()*2,Qt::KeepAspectRatio,Qt::FastTransformation)));
    };
    for(int i=0;i<9;++i){
        QObject::connect(thoughtPick[i],&QPushButton::clicked,&dialog,[&,i]{
            const auto it=std::find_if(atlases.begin(),atlases.end(),[&](const auto&a){return a.id==skinAtlas->currentData().toString();});
            if(it==atlases.end()){QMessageBox::information(&dialog,QObject::tr("Atlas"),QObject::tr("Choose a Tile Atlas first."));return;}
            const QImage image=indexedPreview(it->path,foregroundPalette);
            const int idx=chooseAdventureAtlasCell(&dialog,image,tileSize->value(),thoughtCells[i]);
            if(idx>=0){thoughtCells[i]=idx;updatePreview();}
        });
        QObject::connect(thoughtFlipX[i],&QCheckBox::toggled,&dialog,[&](bool){updatePreview();});
        QObject::connect(thoughtFlipY[i],&QCheckBox::toggled,&dialog,[&](bool){updatePreview();});
        QObject::connect(tilePick[i],&QPushButton::clicked,&dialog,[&,i]{
            const auto it=std::find_if(atlases.begin(),atlases.end(),[&](const auto&a){return a.id==skinAtlas->currentData().toString();});
            if(it==atlases.end()){QMessageBox::information(&dialog,QObject::tr("Atlas"),QObject::tr("Choose a Tile Atlas first."));return;}
            const QImage image=indexedPreview(it->path,foregroundPalette);
            const int idx=chooseAdventureAtlasCell(&dialog,image,tileSize->value(),chosenTiles[i]);
            if(idx>=0){chosenTiles[i]=idx;updatePreview();}
        });
    }
    for(int i=0;i<9;++i){
        QObject::connect(tileFlipX[i],&QCheckBox::toggled,&dialog,[&](bool){updatePreview();});
        QObject::connect(tileFlipY[i],&QCheckBox::toggled,&dialog,[&](bool){updatePreview();});
    }
    const auto refreshFrameControls=[&] {
        const bool hasAtlas=!skinAtlas->currentData().toString().isEmpty();
        const QString hint=hasAtlas
            ? QObject::tr("Select a tile from the chosen Dialogue Tile Atlas.")
            : QObject::tr("Disabled: choose a Dialogue Tile Atlas above first. Without an atlas, a simple frame is drawn.");
        for(int i=0;i<9;++i){
            adventureMarkDependent(tilePick[i]); tilePick[i]->setEnabled(hasAtlas);
            adventureMarkDependent(thoughtPick[i]); thoughtPick[i]->setEnabled(hasAtlas);
            adventureMarkDependent(tileFlipX[i]); tileFlipX[i]->setEnabled(hasAtlas);
            adventureMarkDependent(tileFlipY[i]); tileFlipY[i]->setEnabled(hasAtlas);
            adventureMarkDependent(thoughtFlipX[i]); thoughtFlipX[i]->setEnabled(hasAtlas);
            adventureMarkDependent(thoughtFlipY[i]); thoughtFlipY[i]->setEnabled(hasAtlas);
            tilePick[i]->setToolTip(hint);
            thoughtPick[i]->setToolTip(hint);
            tileFlipX[i]->setToolTip(hint);
            tileFlipY[i]->setToolTip(hint);
            thoughtFlipX[i]->setToolTip(hint);
            thoughtFlipY[i]->setToolTip(hint);
        }
        tileSize->setToolTip(hasAtlas
            ? QObject::tr("Atlas frame cell size in pixels.")
            : QObject::tr("Frame tile size; affects dialogue layout even when using the simple box."));
    };
    QObject::connect(skinAtlas,QOverload<int>::of(&QComboBox::currentIndexChanged),&dialog,[&](int){
        refreshFrameControls();
        updatePreview();
        refreshInventoryIcons();
    });
    QObject::connect(tileSize,QOverload<int>::of(&QSpinBox::valueChanged),&dialog,[&](int){
        updatePreview();
        refreshInventoryIcons();
    });
    refreshFrameControls();
    updatePreview();
    refreshInventoryIcons();
    auto *copyAtlas = new QPushButton(QObject::tr("Copy from Another World..."), skinPage);
    copyAtlas->setToolTip(QObject::tr("Copy the dialogue atlas and both frame designs (dialogue + thought), "
                                        "colours, outline and typing speed. NPCs and dialogue are not copied."));
    skinLayout->insertWidget(0, copyAtlas, 0, Qt::AlignLeft);
    QObject::connect(copyAtlas, &QPushButton::clicked, &dialog, [&] {
        AdventureSavedWorld source;
        if (!chooseAdventureSavedWorld(&dialog, currentDesignFilePath,
                QObject::tr("Dialogue Box Atlas"),
                {QStringLiteral("skinAtlasId"), QStringLiteral("skinIndices"),
                 QStringLiteral("tileSize")}, &source)) return;
        const int atlasIndex = matchAdventureAtlas(&dialog, source, atlases);
        if (atlasIndex < 0) return; // Don't partially copy an unavailable atlas.
        const QJsonObject &settings = source.adventure;
        skinAtlas->setCurrentIndex(atlasIndex);
        tileSize->setValue(std::clamp(settings.value(QStringLiteral("tileSize")).toInt(8),4,32));
        speed->setValue(std::clamp(settings.value(QStringLiteral("framesPerChar")).toInt(2),1,30));
        chosenText = std::clamp(settings.value(QStringLiteral("textColourIndex")).toInt(15),0,255);
        chosenOutline = std::clamp(settings.value(QStringLiteral("outlineColourIndex")).toInt(1),0,255);
        decorateColour(textColour, chosenText);
        decorateColour(outlineColour, chosenOutline);
        outline->setChecked(settings.value(QStringLiteral("textOutline")).toBool(false));
        const QJsonArray cells = settings.value(QStringLiteral("skinIndices")).toArray();
        const QJsonArray flips = settings.value(QStringLiteral("skinFlips")).toArray();
        for (int i=0; i<9; ++i) {
            chosenTiles[i] = std::clamp(i<cells.size() ? cells[i].toInt(i) : i,0,65535);
            const int flags = i<flips.size() ? flips[i].toInt() : 0;
            tileFlipX[i]->setChecked((flags & 4) != 0);
            tileFlipY[i]->setChecked((flags & 8) != 0);
        }
        const QJsonArray thoughtCellsCopy=settings.value("thoughtSkinIndices").toArray();
        const QJsonArray thoughtFlipCopy=settings.value("thoughtSkinFlips").toArray();
        for(int i=0;i<9;++i){
            thoughtCells[i]=std::clamp(i<thoughtCellsCopy.size()?thoughtCellsCopy[i].toInt(i):chosenTiles[i],0,65535);
            const int flags=i<thoughtFlipCopy.size()?thoughtFlipCopy[i].toInt():0;
            thoughtFlipX[i]->setChecked((flags&4)!=0);
            thoughtFlipY[i]->setChecked((flags&8)!=0);
        }
        updatePreview();
    });
    tabs->addTab(skinPage,QObject::tr("Dialogue + Thought Atlas"));

    // Stage 4.33: Height is a minimum, not a fixed text budget. The preview
    // uses REAL conversation nodes and the runtime's 8x16 row/choice formula.
    auto *positionPage=new QWidget(tabs);
    auto *positionLayout=new QVBoxLayout(positionPage);
    auto *positionHelp=new QLabel(QObject::tr(
        "Choose a conversation below to preview its actual name, wrapped text, "
        "and TWO visible answers. Height is a minimum: the box grows for longer "
        "dialogue and rises on screen when needed. Use Up/Down to reach other answers."),positionPage);
    positionHelp->setWordWrap(true);positionLayout->addWidget(positionHelp);
    // Left: dialogue and thought placement settings. Right: live LCD preview.
    auto *positionMainRow=new QHBoxLayout;
    auto *positionLeft=new QVBoxLayout;
    auto *positionRight=new QVBoxLayout;
    positionMainRow->addLayout(positionLeft,1);
    positionMainRow->addLayout(positionRight,1);
    positionLayout->addLayout(positionMainRow,1);
    auto *previewSelectors=new QHBoxLayout;
    auto *previewNode=new DialogueTreeCombo(positionPage,&nodes,&dialogueFolders);
    auto *previewAnswer=new QComboBox(positionPage);
    previewSelectors->addWidget(new QLabel(QObject::tr("Preview dialogue"),positionPage));
    previewSelectors->addWidget(previewNode,2);
    previewSelectors->addWidget(new QLabel(QObject::tr("Selected answer"),positionPage));
    previewSelectors->addWidget(previewAnswer,1);
    positionLeft->addLayout(previewSelectors);
    auto *positionFields=new QGridLayout;
    auto *placement=new QComboBox(positionPage);
    placement->addItems({QObject::tr("Custom position"),QObject::tr("Top centre"),
         QObject::tr("Bottom centre"),QObject::tr("Top left"),QObject::tr("Top right"),
         QObject::tr("Bottom left"),QObject::tr("Bottom right")});
    auto makeCoord=[&](int lo,int hi,int value){
        auto *field=new QSpinBox(positionPage);field->setRange(lo,hi);
        field->setValue(std::clamp(value,lo,hi));return field;
    };
    auto *dialogX=makeCoord(0,479,old.value("dialogX").toInt(20));
    auto *dialogY=makeCoord(0,319,old.value("dialogY").toInt(148));
    auto *dialogW=makeCoord(128,480,old.value("dialogWidth").toInt(440));
    auto *dialogH=makeCoord(96,320,old.value("dialogHeight").toInt(96));
    positionFields->addWidget(new QLabel(QObject::tr("Placement preset"),positionPage),0,0);
    positionFields->addWidget(placement,0,1,1,3);
    positionFields->addWidget(new QLabel(QObject::tr("X (pixels)"),positionPage),1,0);
    positionFields->addWidget(dialogX,1,1);
    positionFields->addWidget(new QLabel(QObject::tr("Y (pixels)"),positionPage),1,2);
    positionFields->addWidget(dialogY,1,3);
    positionFields->addWidget(new QLabel(QObject::tr("Width (pixels)"),positionPage),2,0);
    positionFields->addWidget(dialogW,2,1);
    positionFields->addWidget(new QLabel(QObject::tr("Minimum height"),positionPage),2,2);
    positionFields->addWidget(dialogH,2,3);
    auto *textPadding = new QComboBox(positionPage);
    textPadding->addItem(QObject::tr("Off (0 px)"),0);
    textPadding->addItem(QObject::tr("8 pixels"),8);
    textPadding->setCurrentIndex(old.value("dialogPadding").toInt(8)==0 ? 0 : 1);
    positionFields->addWidget(new QLabel(QObject::tr("Dialogue box padding (0 / 8 px)"),positionPage),3,0);
    positionFields->addWidget(textPadding,3,1,1,3);
    auto *thoughtPosition=new QGroupBox(QObject::tr("Thought bubble placement"),positionPage);
    auto *thoughtPositionFields=new QGridLayout(thoughtPosition);
    auto *thoughtX=makeCoord(0,479,old.value("thoughtX").toInt(20));
    auto *thoughtY=makeCoord(0,319,old.value("thoughtY").toInt(12));
    auto *thoughtW=makeCoord(96,480,old.value("thoughtWidth").toInt(240));
    auto *thoughtH=makeCoord(40,320,old.value("thoughtHeight").toInt(64));
    auto makeScale=[&](int saved){
        auto *scale=new QComboBox(positionPage);
        for(const int n:{1,2,4,8})scale->addItem(QObject::tr("%1×").arg(n),n);
        scale->setCurrentIndex(std::max(0,scale->findData(saved)));
        scale->setToolTip(QObject::tr("Native 8×8 SIDBOX glyphs multiplied independently on this axis."));
        return scale;
    };
    auto *dialogScaleX=makeScale(old.value("dialogFontScaleX").toInt(1));
    auto *dialogScaleY=makeScale(old.value("dialogFontScaleY").toInt(2));
    auto *thoughtScaleX=makeScale(old.value("thoughtFontScaleX").toInt(1));
    auto *thoughtScaleY=makeScale(old.value("thoughtFontScaleY").toInt(2));
    auto *stacking=new QComboBox(positionPage);
    stacking->addItem(QObject::tr("Thought bubble above dialogue"),1);
    stacking->addItem(QObject::tr("Main dialogue above thought bubble"),0);
    stacking->setCurrentIndex(std::max(0,stacking->findData(old.value("thoughtAboveDialog").toInt(1))));
    thoughtPositionFields->addWidget(new QLabel(QObject::tr("X"),thoughtPosition),0,0);
    thoughtPositionFields->addWidget(thoughtX,0,1);
    thoughtPositionFields->addWidget(new QLabel(QObject::tr("Y"),thoughtPosition),0,2);
    thoughtPositionFields->addWidget(thoughtY,0,3);
    thoughtPositionFields->addWidget(new QLabel(QObject::tr("Width"),thoughtPosition),1,0);
    thoughtPositionFields->addWidget(thoughtW,1,1);
    thoughtPositionFields->addWidget(new QLabel(QObject::tr("Height"),thoughtPosition),1,2);
    thoughtPositionFields->addWidget(thoughtH,1,3);
    thoughtPositionFields->addWidget(new QLabel(QObject::tr("Font scale X"),thoughtPosition),2,0);
    thoughtPositionFields->addWidget(thoughtScaleX,2,1);
    thoughtPositionFields->addWidget(new QLabel(QObject::tr("Font scale Y"),thoughtPosition),2,2);
    thoughtPositionFields->addWidget(thoughtScaleY,2,3);
    positionFields->addWidget(new QLabel(QObject::tr("Font scale X"),positionPage),4,0);
    positionFields->addWidget(dialogScaleX,4,1);
    positionFields->addWidget(new QLabel(QObject::tr("Font scale Y"),positionPage),4,2);
    positionFields->addWidget(dialogScaleY,4,3);
    positionFields->addWidget(new QLabel(QObject::tr("Frontmost box"),positionPage),5,0);
    positionFields->addWidget(stacking,5,1,1,3);
    auto *positionPanels=new QVBoxLayout;
    auto *dialoguePosition=new QGroupBox(QObject::tr("Dialogue box placement"),positionPage);
    dialoguePosition->setLayout(positionFields);
    positionPanels->addWidget(dialoguePosition,1);
    positionPanels->addWidget(thoughtPosition,1);
    positionLeft->addLayout(positionPanels);
    auto *copyPosition = new QPushButton(QObject::tr("Copy from Another World..."),positionPage);
    copyPosition->setToolTip(QObject::tr("Copy only dialogue window X/Y, width and minimum height. "
                                         "No dialogue text, choices or NPC settings are copied."));
    positionLeft->insertWidget(0,copyPosition,0,Qt::AlignLeft);
    auto *screenPreview=new AdventureDialoguePositionPreview(positionPage);
    screenPreview->setAlignment(Qt::AlignCenter);
    auto *previewRow=new QHBoxLayout;
    previewRow->addStretch();previewRow->addWidget(screenPreview);previewRow->addStretch();
    positionRight->addLayout(previewRow,1);
    auto *positionStatus=new QLabel(positionPage);
    positionStatus->setWordWrap(true);positionLeft->addWidget(positionStatus);
    auto chosenNode=[&]() -> QJsonObject {
        const int index=previewNode->currentData().toInt();
        return (index>=0 && index<nodes.size())?nodes[index].toObject():QJsonObject();
    };
    auto refreshAnswers=[&]{
        const int prev=previewAnswer->currentData().toInt();
        previewAnswer->blockSignals(true);previewAnswer->clear();
        const QJsonArray options=chosenNode().value("choices").toArray();
        for(int i=0;i<options.size();++i) {
            const QString label=options[i].toObject().value("text").toString();
            if(!label.isEmpty())
                previewAnswer->addItem(QObject::tr("%1: %2").arg(i+1).arg(label.left(26)),i);
        }
        const bool hasAnswers=previewAnswer->count()>0;
        if(!hasAnswers)previewAnswer->addItem(QObject::tr("No answers"),-1);
        previewAnswer->setCurrentIndex(std::max(0,previewAnswer->findData(prev)));
        adventureMarkDependent(previewAnswer); previewAnswer->setEnabled(hasAnswers);
        previewAnswer->setToolTip(hasAnswers
            ? QObject::tr("Preview the speech/thought for the highlighted Answer.")
            : QObject::tr("Disabled: this dialogue has no selectable Answers. The preview uses its Fire2-only thought instead."));
        previewAnswer->blockSignals(false);
    };
    auto refreshNodes=[&]{
        const int prev=previewNode->currentData().toInt();
        previewNode->blockSignals(true);previewNode->clear();
        for(int i=0;i<nodes.size();++i)
            previewNode->addItem(dialogueTitle(nodes[i].toObject(),i),i);
        if(previewNode->count()==0)previewNode->addItem(QObject::tr("Create a dialogue node first"),-1);
        previewNode->setCurrentIndex(std::max(0,previewNode->findData(prev)));
        previewNode->blockSignals(false);
        refreshAnswers();
    };
    // Runtime draws a complete atlas tile as each edge of the nine-slice
    // frame. The selectable 0/8 px space begins AFTER this decorative edge.
    auto previewInset=[&] {
        const int border=skinAtlas->currentData().toString().isEmpty()
            ? 0 : tileSize->value();
        return border+textPadding->currentData().toInt();
    };
    auto refreshPosition=[&] {
        const QJsonObject node=chosenNode();
        const AdventurePreviewMetrics metrics=adventureMeasure(node,dialogW->value(),dialogH->value(),outline->isChecked(),previewInset(),dialogScaleX->currentData().toInt(),dialogScaleY->currentData().toInt());
        const int w=dialogW->value(), h=metrics.height;
        if(dialogX->value()>480-w){
            dialogX->blockSignals(true);dialogX->setValue(480-w);dialogX->blockSignals(false);
        }
        const int actualY=std::min(dialogY->value(),320-h);
        const int x=dialogX->value();
        screenPreview->frameW=w;screenPreview->frameH=h;
        screenPreview->frameX=x;screenPreview->frameY=actualY;
        const int tw=thoughtW->value();
        const int thoughtInset=previewInset();
        const int thoughtSx=thoughtScaleX->currentData().toInt();
        const int thoughtSy=thoughtScaleY->currentData().toInt();
        const int thoughtRow=8*thoughtSy+(outline->isChecked()?4:0);
        const QJsonArray selectedChoices=node.value("choices").toArray();
        const int selectedAnswer=previewAnswer->currentData().toInt();
        const QJsonObject selectedChoice=(selectedAnswer>=0 && selectedAnswer<selectedChoices.size())
            ?selectedChoices[selectedAnswer].toObject():QJsonObject();
        QString thoughtText=(selectedChoice.value("thoughtBubble").toBool(false)
            || selectedChoice.value("thoughtBubbleThis").toBool(false))
            ?selectedChoice.value("reply").toString() : QString();
        if(selectedAnswer<0) {
            // Fire2-only dialogues have no highlighted answer: show the first
            // non-empty THIS-dialogue thought, just like the generated runtime.
            for(const QJsonValue &v:selectedChoices) {
                const QJsonObject choice=v.toObject();
                if(choice.value("thoughtBubbleThis").toBool(false) &&
                   !choice.value("thoughtBubble").toBool(false) &&
                   !choice.value("reply").toString().isEmpty()) {
                    thoughtText=choice.value("reply").toString();
                    break;
                }
            }
        }
        if(thoughtText.isEmpty())thoughtText=QObject::tr("Thought preview");
        const int thoughtColumns=std::clamp((tw-2*thoughtInset)/(8*thoughtSx),1,60);
        const auto thoughtLines=adventurePreviewRows(thoughtText.left(150),thoughtColumns,16);
        const int th=std::min(320,std::max(thoughtH->value(),2*thoughtInset+int(thoughtLines.size())*thoughtRow));
        const int tx=std::min(thoughtX->value(),480-tw);
        const int ty=std::min(thoughtY->value(),320-th);
        screenPreview->thoughtX=tx;screenPreview->thoughtY=ty;
        screenPreview->thoughtW=tw;screenPreview->thoughtH=th;
        QImage screen(480,320,QImage::Format_ARGB32);
        screen.fill(QColor(35,40,52));
        QPainter painter(&screen);
        painter.setPen(QColor(78,91,113));
        painter.drawRect(0,0,479,319);
        for(int gx=80;gx<480;gx+=80)painter.drawLine(gx,0,gx,320);
        for(int gy=80;gy<320;gy+=80)painter.drawLine(0,gy,480,gy);
        const QColor textInk=chosenText>=0 && chosenText<foregroundPalette.size()
            ? QColor::fromRgba(foregroundPalette[chosenText]) : QColor(234,240,250);
        const QColor outlineInk=chosenOutline>=0 && chosenOutline<foregroundPalette.size()
            ? QColor::fromRgba(foregroundPalette[chosenOutline]) : QColor(10,10,16);
        const QColor visibleTextInk=textInk.alpha()==0?QColor(textInk.red(),textInk.green(),textInk.blue()):textInk;
        const QColor visibleOutlineInk=outlineInk.alpha()==0?QColor(outlineInk.red(),outlineInk.green(),outlineInk.blue()):outlineInk;
        const bool thoughtsOnTop=stacking->currentData().toInt()!=0;
        screenPreview->thoughtAboveDialog=thoughtsOnTop;
        auto paintThought=[&]{
        painter.fillRect(QRect(tx,ty,tw,th),QColor(43,32,64,238));
        painter.setPen(QPen(QColor(183,120,242),2));
        painter.drawRect(QRect(tx,ty,tw,th).adjusted(1,1,-2,-2));
        painter.setPen(QColor(240,210,255));
        painter.setClipRect(QRect(tx+thoughtInset,ty+thoughtInset,
                                   tw-2*thoughtInset,th-2*thoughtInset));
        for(int i=0;i<std::min(int(thoughtLines.size()),std::max(0,(th-2*thoughtInset)/thoughtRow));++i)
            adventureDrawGlyphs(painter,tx+thoughtInset,ty+thoughtInset+i*thoughtRow,thoughtLines[i],
                                thoughtSx,thoughtSy,visibleTextInk,outline->isChecked(),visibleOutlineInk);
        painter.setClipping(false);
        };
        auto paintDialogue=[&]{
        painter.fillRect(QRect(x,actualY,w,h),QColor(8,14,29,223));
        painter.setPen(QPen(metrics.overflow?QColor(255,83,83):QColor(255,212,71),2));
        painter.drawRect(QRect(x,actualY,w,h).adjusted(1,1,-2,-2));
        const int skinEdge=skinAtlas->currentData().toString().isEmpty()
            ? 0 : tileSize->value();
        if (skinEdge>0) {
            painter.setPen(QPen(QColor(120,136,159),1,Qt::DotLine));
            painter.drawRect(QRect(x+skinEdge,actualY+skinEdge,
                w-2*skinEdge,h-2*skinEdge));
        }
        const int dialogueSx=dialogScaleX->currentData().toInt();
        const int dialogueSy=dialogScaleY->currentData().toInt();
        const int contentInset=previewInset();
        painter.setClipRect(QRect(x+contentInset,actualY+contentInset,w-2*contentInset,h-2*contentInset));
        painter.setPen(QColor(234,240,250));
        const int pad=previewInset();
        adventureDrawGlyphs(painter,x+pad,actualY+pad,node.value("speaker").toString().left(36),dialogueSx,dialogueSy,visibleTextInk,outline->isChecked(),visibleOutlineInk);
        const auto body=adventurePreviewRows(node.value("text").toString().left(512),metrics.bodyColumns);
        const int bodyY=actualY+pad+(metrics.answerHeight?metrics.lineHeight+8:metrics.lineHeight);
        const int choiceSpace=metrics.answerHeight?metrics.answerHeight+1:0;
        const int bottom=actualY+h-std::max(0,pad-8);
        const int visibleRows=std::clamp((bottom-bodyY-choiceSpace)/metrics.lineHeight,0,int(body.size()));
        for(int i=0;i<visibleRows;++i)
            adventureDrawGlyphs(painter,x+pad,bodyY+i*metrics.lineHeight,body[i],dialogueSx,dialogueSy,visibleTextInk,outline->isChecked(),visibleOutlineInk);
        const QJsonArray options=node.value("choices").toArray();
        QVector<QPair<int,QString>> labels;
        for(int i=0;i<options.size();++i) {
            const QString label=options[i].toObject().value("text").toString().left(180);
            if(!label.isEmpty())labels.append(qMakePair(i,label));
        }
        int selectedPos=0;
        for(int i=0;i<labels.size();++i)
            if(labels[i].first==previewAnswer->currentData().toInt())selectedPos=i;
        const int first=(labels.size()>2 && selectedPos>1)?selectedPos-1:0;
        int cy=bodyY+visibleRows*metrics.lineHeight+1;
        for(int i=first;i<std::min(first+2,int(labels.size()));++i) {
            const auto rows=adventurePreviewRows(labels[i].second,metrics.answerColumns,32);
            const int lines=std::min(int(rows.size()),std::max(0,(bottom-cy)/metrics.lineHeight));
            if(!lines)break;
            adventureDrawGlyphs(painter,x+pad,cy,i==selectedPos?QStringLiteral(">") : QStringLiteral(" "),dialogueSx,dialogueSy,visibleTextInk,outline->isChecked(),visibleOutlineInk);
            for(int k=0;k<lines;++k)
                adventureDrawGlyphs(painter,x+pad+14*dialogueSx,cy+k*metrics.lineHeight,rows[k],dialogueSx,dialogueSy,visibleTextInk,outline->isChecked(),visibleOutlineInk);
            if(i==first && first>0)adventureDrawGlyphs(painter,x+w-20*dialogueSx,cy,QStringLiteral("^"),dialogueSx,dialogueSy,visibleTextInk,outline->isChecked(),visibleOutlineInk);
            if(i==std::min(first+2,int(labels.size()))-1 && first+2<int(labels.size()))
                adventureDrawGlyphs(painter,x+w-20*dialogueSx,cy+(lines-1)*metrics.lineHeight,QStringLiteral("v"),dialogueSx,dialogueSy,visibleTextInk,outline->isChecked(),visibleOutlineInk);
            cy+=lines*metrics.lineHeight+4;
        }
        painter.setClipping(false);
        // Dashed line makes the interior text budget visible independently of the frame.
        painter.setPen(QPen(metrics.overflow?QColor(255,83,83):QColor(96,190,128),1,Qt::DashLine));
        painter.drawRect(QRect(x+pad,actualY+pad+(metrics.answerHeight?22:14),
            w-2*pad,h-2*pad-(metrics.answerHeight?metrics.lineHeight+8:metrics.lineHeight)));
        };
        if(thoughtsOnTop){paintDialogue();paintThought();}
        else {paintThought();paintDialogue();}
        painter.end();
        screenPreview->setPixmap(QPixmap::fromImage(screen));
        QString status=QObject::tr("Needed: %1 px  |  Box: %2 px (configured %3)  |  %4 NPC text rows; at most 2 choices")
            .arg(metrics.needed).arg(h).arg(dialogH->value()).arg(metrics.rows);
        if (actualY!=dialogY->value())
            status+=QObject::tr("  |  Auto-raised to Y=%1 to stay on screen").arg(actualY);
        if(QRect(x,actualY,w,h).intersects(QRect(tx,ty,tw,th)))
            status+=thoughtsOnTop ? QObject::tr("  |  Overlap: Thought on top") : QObject::tr("  |  Overlap: Dialogue on top");
        if(th>thoughtH->value())
            status+=QObject::tr("  |  Thought grows to %1px to fit scaled glyphs").arg(th);
        if(metrics.overflow)
            status+=QObject::tr("  |  WARNING: Too much text for 320px. Widen the box or shorten the conversation.");
        positionStatus->setText(status);
    };
    QObject::connect(copyPosition, &QPushButton::clicked, &dialog, [&] {
        AdventureSavedWorld source;
        if (!chooseAdventureSavedWorld(&dialog,currentDesignFilePath,
                QObject::tr("Dialogue Position"),
                {QStringLiteral("dialogX"), QStringLiteral("dialogY"),
                 QStringLiteral("dialogWidth"), QStringLiteral("dialogHeight")}, &source)) return;
        const QJsonObject &settings = source.adventure;
        placement->setCurrentIndex(0); // Copied values are a custom placement.
        dialogX->setValue(std::clamp(settings.value(QStringLiteral("dialogX")).toInt(20),0,479));
        dialogY->setValue(std::clamp(settings.value(QStringLiteral("dialogY")).toInt(148),0,319));
        dialogW->setValue(std::clamp(settings.value(QStringLiteral("dialogWidth")).toInt(440),128,480));
        dialogH->setValue(std::clamp(settings.value(QStringLiteral("dialogHeight")).toInt(96),96,320));
        textPadding->setCurrentIndex(settings.value("dialogPadding").toInt(8)==0 ? 0 : 1);
        refreshPosition();
    });
    QObject::connect(placement,QOverload<int>::of(&QComboBox::currentIndexChanged),positionPage,[&](int choice){
        if(!choice)return;
        const int w=dialogW->value();
        const int h=adventureMeasure(chosenNode(),w,dialogH->value(),outline->isChecked(),previewInset(),dialogScaleX->currentData().toInt(),dialogScaleY->currentData().toInt()).height;
        int x=(480-w)/2,y=(choice==1 || choice==3 || choice==4)?8:320-h-8;
        if(choice==3 || choice==5)x=8;
        if(choice==4 || choice==6)x=480-w-8;
        dialogX->setValue(std::max(0,x));dialogY->setValue(std::max(0,y));
        refreshPosition();
    });
    for(QSpinBox *field:{dialogX,dialogY,dialogW,dialogH,thoughtX,thoughtY,thoughtW,thoughtH})
        QObject::connect(field,QOverload<int>::of(&QSpinBox::valueChanged),positionPage,[&](int){refreshPosition();});
    for(QComboBox *field:{dialogScaleX,dialogScaleY,thoughtScaleX,thoughtScaleY,stacking})
        QObject::connect(field,QOverload<int>::of(&QComboBox::currentIndexChanged),positionPage,[&](int){refreshPosition();});
    QObject::connect(previewNode,QOverload<int>::of(&QComboBox::currentIndexChanged),positionPage,[&](int){refreshAnswers();refreshPosition();});
    QObject::connect(previewAnswer,QOverload<int>::of(&QComboBox::currentIndexChanged),positionPage,[&](int){refreshPosition();});
    QObject::connect(outline,&QCheckBox::toggled,positionPage,[&](bool){refreshPosition();});
    QObject::connect(textPadding,QOverload<int>::of(&QComboBox::currentIndexChanged),
                     positionPage,[&](int){refreshPosition();});
    screenPreview->moved=[&](int x,int y){
        dialogX->setValue(x);dialogY->setValue(y);refreshPosition();
    };
    screenPreview->movedThought=[&](int x,int y){
        thoughtX->setValue(x);thoughtY->setValue(y);refreshPosition();
    };
    const int positionTabIndex=tabs->addTab(positionPage,QObject::tr("Dialogue Position"));
    QObject::connect(tabs,&QTabWidget::currentChanged,positionPage,[&](int index){
        if(index==positionTabIndex){refreshNodes();refreshPosition();}
    });
    refreshNodes();refreshPosition();
    positionRight->addWidget(new QLabel(QObject::tr(
        "DRAG the yellow dialogue box or purple thought bubble to position either one. When boxes overlap, the frontmost box receives mouse drags. Glyphs use native SIDBOX 8×8 pixel shapes with independent X/Y scaling. The green dashed guide marks the dialogue text area; "
        "red means the conversation exceeds the LCD height. Only two answers are shown at a time."),positionPage));


    auto *buttons=new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,&dialog);
    main->addWidget(buttons);
    QObject::connect(buttons,&QDialogButtonBox::accepted,&dialog,&QDialog::accept);
    QObject::connect(buttons,&QDialogButtonBox::rejected,&dialog,&QDialog::reject);
    // Navigation shortcut from the World Designer's [NPC]-tagged sprite.
    // Sprite IDs, not display names, identify the NPC when sprites are renamed.
    if (!focusNpcSpriteId.isEmpty()) {
        for (int row = 0; row < npcs->rowCount(); ++row) {
            QTableWidgetItem *sprite = npcs->item(row, 0);
            if (!sprite || sprite->data(Qt::UserRole).toString() != focusNpcSpriteId) continue;
            tabs->setCurrentWidget(npcPage);
            npcs->setCurrentCell(row, 0);
            npcs->scrollToItem(sprite, QAbstractItemView::PositionAtCenter);
            npcs->setFocus();
            break;
        }
    }
    if(dialog.exec()!=QDialog::Accepted)return false;
    QJsonObject result=old;
    const QJsonArray finalInventory = tableItems(items);
    result.insert("items", finalInventory);
    result.insert("maxInventorySlots",inventoryCapacity->value());
    // Update approved saved worlds only after the dialog was accepted. Read
    // each target again and modify exactly the permitted inventory rule keys.
    // QSaveFile commits each full JSON document atomically, without touching
    // that world's NPCs, artwork or pickup type mappings.
    QStringList syncProblems;
    QStringList syncSkipped;
    int syncedWorlds = 0;
    int alreadyMatchedWorlds = 0;
    QSet<QString> touchedPaths;
    for (auto nameIt = acceptedWorldRules.constBegin();
         nameIt != acceptedWorldRules.constEnd(); ++nameIt) {
        int sourceMatches = 0;
        for (const QJsonValue &entry : finalInventory) {
            const QJsonObject item = entry.toObject();
            if (item.value(QStringLiteral("name")).toString().trimmed().toCaseFolded() == nameIt.key()) {
                ++sourceMatches;
            }
        }
        if (sourceMatches != 1) {
            syncSkipped.append(QObject::tr("%1 (item renamed, removed or duplicated before OK)").arg(nameIt.key()));
            continue; // Renamed/deleted/duplicate: don't guess.
        }
        for (auto pathIt = nameIt.value().constBegin(); pathIt != nameIt.value().constEnd(); ++pathIt) {
            const QString path = pathIt.key();
            if (touchedPaths.contains(path)) continue;
            // One target can contain multiple approved items. Merge all
            // changes into a single atomic save of that world.
            touchedPaths.insert(path);
            const QFileInfo fileInfo(path);
            if (!fileInfo.isFile() || fileInfo.isSymLink()
                || fileInfo.lastModified() != acceptedWorldTimestamps.value(path)) {
                syncProblems.append(QObject::tr("%1 (changed while editing)").arg(fileInfo.fileName()));
                continue;
            }
            QFile input(path);
            if (!input.open(QIODevice::ReadOnly) || input.size() > 16 * 1024 * 1024) {
                syncProblems.append(QObject::tr("%1 (cannot read)").arg(fileInfo.fileName()));
                continue;
            }
            QJsonParseError error;
            const QJsonDocument doc = QJsonDocument::fromJson(input.readAll(), &error);
            input.close();
            if (error.error != QJsonParseError::NoError || !doc.isObject()) {
                syncProblems.append(QObject::tr("%1 (invalid JSON)").arg(fileInfo.fileName()));
                continue;
            }
            QJsonObject targetWorld = doc.object();
            if (targetWorld.value(QStringLiteral("format")).toString() != QStringLiteral("SIDBOX-GAME-DESIGN")
                || targetWorld.value(QStringLiteral("version")).toInt() != 1) {
                syncProblems.append(QObject::tr("%1 (unsupported world)").arg(fileInfo.fileName()));
                continue;
            }
            QJsonObject targetAdventure = targetWorld.value(QStringLiteral("adventure")).toObject();
            QJsonArray targetItems = targetAdventure.value(QStringLiteral("items")).toArray();
            bool changed = false;
            for (auto itemIt = acceptedWorldRules.constBegin();
                 itemIt != acceptedWorldRules.constEnd(); ++itemIt) {
                if (!itemIt.value().contains(path)) continue;
                QJsonObject fromItem;
                int sourceCount = 0, targetCount = 0, targetIndex = -1;
                for (const QJsonValue &entry : finalInventory) {
                    const QJsonObject one = entry.toObject();
                    if (one.value(QStringLiteral("name")).toString().trimmed().toCaseFolded() == itemIt.key()) {
                        fromItem = one;
                        ++sourceCount;
                    }
                }
                for (int i = 0; i < targetItems.size(); ++i) {
                    if (targetItems[i].toObject().value(QStringLiteral("name")).toString()
                            .trimmed().toCaseFolded() == itemIt.key()) {
                        ++targetCount;
                        targetIndex = i;
                    }
                }
                if (sourceCount != 1 || targetCount != 1) {
                    syncSkipped.append(QObject::tr("%1: %2 (item no longer unique in one world)")
                        .arg(fileInfo.fileName(), itemIt.key()));
                    continue;
                }
                QJsonObject toItem = targetItems[targetIndex].toObject();
                for (const QString &field : itemIt.value().value(path)) {
                    if (field == QStringLiteral("discardable")
                        && fromItem.value(field).toBool()) {
                        // Safety: never allow destruction of an item required
                        // by a dialogue in the target world.
                        bool required = false;
                        for (const QJsonValue &nodeValue : targetAdventure.value(QStringLiteral("nodes")).toArray()) {
                            for (const QJsonValue &choiceValue : nodeValue.toObject().value(QStringLiteral("choices")).toArray()) {
                                const QJsonObject choice = choiceValue.toObject();
                                if (choice.value(QStringLiteral("requires")).toInt(-1) == targetIndex
                                    || choice.value(QStringLiteral("take")).toInt(-1) == targetIndex) required = true;
                                for (const QJsonValue &entry : choice.value(QStringLiteral("exchange")).toObject()
                                                                .value(QStringLiteral("items")).toArray())
                                    if (entry.toInt(-1) == targetIndex) required = true;
                            }
                        }
                        if (required) {
                            syncSkipped.append(QObject::tr("%1: %2 (Can Discard protected by NPC dialogue)")
                                .arg(fileInfo.fileName(), itemIt.key()));
                            continue;
                        }
                    }
                    if (toItem.value(field) != fromItem.value(field)) {
                        toItem.insert(field, fromItem.value(field));
                        changed = true;
                    }
                }
                targetItems[targetIndex] = toItem;
            }
            if (!changed) {
                ++alreadyMatchedWorlds;
                continue;
            }
            targetAdventure.insert(QStringLiteral("items"), targetItems);
            targetWorld.insert(QStringLiteral("adventure"), targetAdventure);
            const QByteArray data = QJsonDocument(targetWorld).toJson(QJsonDocument::Indented);
            QSaveFile output(path);
            if (!output.open(QIODevice::WriteOnly) || output.write(data) != data.size()
                || !output.commit()) {
                syncProblems.append(QObject::tr("%1 (could not save)").arg(fileInfo.fileName()));
                continue;
            }
            ++syncedWorlds;
        }
    }
    if (!acceptedWorldRules.isEmpty()) {
        QString summary = QObject::tr("Other worlds updated on disk: %1\n"
                                      "Already matching (no write needed): %2\n\n"
                                      "The CURRENT world is still in the designer. Save it, then run Update Game Project.")
                              .arg(syncedWorlds).arg(alreadyMatchedWorlds);
        if (!syncSkipped.isEmpty())
            summary += QObject::tr("\n\nRules NOT copied:\n%1")
                .arg(syncSkipped.join(QStringLiteral("\n")));
        if (!syncProblems.isEmpty())
            summary += QObject::tr("\n\nWorld files NOT saved:\n%1")
                .arg(syncProblems.join(QStringLiteral("\n")));
        if (!syncProblems.isEmpty() || !syncSkipped.isEmpty())
            QMessageBox::warning(parent, QObject::tr("Inventory World Sync: Partial Result"), summary);
        else
            QMessageBox::information(parent, QObject::tr("Inventory World Sync: Complete"), summary);
    }
    QJsonArray outNpcs;
    for(int row=0;row<npcs->rowCount();++row){
        QJsonObject o; o.insert("spriteId",npcs->item(row,0)->data(Qt::UserRole).toString());
        auto *chosen=qobject_cast<QComboBox*>(npcs->cellWidget(row,1));
        o.insert("node",std::clamp(chosen?chosen->currentData().toInt():0,0,std::max(0,int(nodes.size())-1)));
        o.insert("radius",std::clamp(intAt(npcs,row,2,48),8,512));
        auto *done=qobject_cast<QComboBox*>(npcs->cellWidget(row,3));
        o.insert("doneNode",done?done->currentData().toInt():-1);
        o.insert("initiallyVisible",!npcs->item(row,4) || npcs->item(row,4)->checkState()==Qt::Checked);
        o.insert("animation",npcs->item(row,0)->data(Qt::UserRole + 1).toJsonObject());
        outNpcs.append(o);
    }
    result.insert("npcs",outNpcs);result.insert("nodes",nodes);
    result.insert("dialogueFolders",dialogueFolders);
    result.insert("dialogX",dialogX->value());
    result.insert("dialogY",dialogY->value());
    result.insert("dialogWidth",dialogW->value());
    result.insert("dialogHeight",dialogH->value());
    result.insert("dialogPadding",textPadding->currentData().toInt());
    result.insert("thoughtX",thoughtX->value());
    result.insert("thoughtY",thoughtY->value());
    result.insert("thoughtWidth",thoughtW->value());
    result.insert("thoughtHeight",thoughtH->value());
    result.insert("dialogFontScaleX",dialogScaleX->currentData().toInt());
    result.insert("dialogFontScaleY",dialogScaleY->currentData().toInt());
    result.insert("thoughtFontScaleX",thoughtScaleX->currentData().toInt());
    result.insert("thoughtFontScaleY",thoughtScaleY->currentData().toInt());
    result.insert("thoughtAboveDialog",stacking->currentData().toInt());

    result.insert("skinAtlasId",skinAtlas->currentData().toString());
    result.insert("tileSize",tileSize->value());result.insert("framesPerChar",speed->value());
    result.insert("textColourIndex",chosenText);
    result.insert("textOutline",outline->isChecked());
    result.insert("outlineColourIndex",chosenOutline);
    QJsonArray cells;for(int i=0;i<9;++i)cells.append(chosenTiles[i]);
    result.insert("skinIndices",cells);
    QJsonArray flipFlags;
    for(int i=0;i<9;++i)flipFlags.append((tileFlipX[i]->isChecked()?4:0)|(tileFlipY[i]->isChecked()?8:0));
    result.insert("skinFlips",flipFlags);
    QJsonArray thoughtIndices, thoughtFlips;
    for(int i=0;i<9;++i){
        thoughtIndices.append(thoughtCells[i]);
        thoughtFlips.append((thoughtFlipX[i]->isChecked()?4:0)|(thoughtFlipY[i]->isChecked()?8:0));
    }
    result.insert("thoughtSkinIndices",thoughtIndices);
    result.insert("thoughtSkinFlips",thoughtFlips);
    *payload=result;return true;
}
