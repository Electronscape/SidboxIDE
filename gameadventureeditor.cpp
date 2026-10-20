#include "gameadventureeditor.h"
#include "ppbcodec.h"
#include <QAbstractItemView>
#include <QComboBox>
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
#include <QMouseEvent>
#include <QScrollBar>
#include <QSlider>
#include <QTimer>
#include <QIcon>
#include <QSize>
#include <QStringList>
#include <QVector>
#include <functional>
#include <array>
#include <algorithm>

namespace {
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

// SIDBOX uses an 8x16 monospace font. Keep this estimator in step with
// game/adventureruntime.c: the dialogue box fits the speaker, body and the
// largest adjacent pair of answer labels (not all three at once).
QStringList adventurePreviewRows(const QString &text, int width, int limit=64)
{
    QStringList result;
    if (width < 1 || text.isEmpty()) return result;
    const QString source=text.left(512);
    int pos=0;
    width=std::min(width,54);
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
                                        int minimumHeight, bool outlined)
{
    AdventurePreviewMetrics m;
    m.lineHeight=outlined?20:16;
    m.bodyColumns=std::min(50,(width-24)/8);
    m.answerColumns=std::min(54,(width-24-34)/8);
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
    m.needed=32+m.rows*m.lineHeight+(m.answerHeight?9+m.answerHeight:0)+12;
    m.height=std::min(320,std::max(minimumHeight,m.needed));
    m.overflow=m.needed>320;
    return m;
}

// Drag the yellow dialogue window directly on the SIDBOX 480x320 preview.
// No Q_OBJECT needed; parent updates the X/Y spinboxes through this callback.
class AdventureDialoguePositionPreview : public QLabel {
public:
    int frameX=20, frameY=148, frameW=440, frameH=162;
    std::function<void(int,int)> moved;
    explicit AdventureDialoguePositionPreview(QWidget *parent=nullptr) : QLabel(parent) {
        setFixedSize(480,320);
        setCursor(Qt::OpenHandCursor);
    }
protected:
    bool dragging=false;
    int gripX=0,gripY=0;
    void reposition(const QPointF &point) {
        const int nx=std::clamp(int(point.x())-gripX,0,480-frameW);
        const int ny=std::clamp(int(point.y())-gripY,0,320-frameH);
        if(moved)moved(nx,ny);
    }
    void mousePressEvent(QMouseEvent *event) override {
        if(event->button()!=Qt::LeftButton)return;
        const int x=int(event->position().x()),y=int(event->position().y());
        if(x>=frameX && y>=frameY && x<frameX+frameW && y<frameY+frameH){
            gripX=x-frameX;gripY=y-frameY;
        }else{gripX=frameW/2;gripY=frameH/2;}
        dragging=true;setCursor(Qt::ClosedHandCursor);
        reposition(event->position());
    }
    void mouseMoveEvent(QMouseEvent *event) override {
        if(dragging)reposition(event->position());
    }
    void mouseReleaseEvent(QMouseEvent *event) override {
        if(event->button()==Qt::LeftButton){dragging=false;setCursor(Qt::OpenHandCursor);}
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
        buttons->button(QDialogButtonBox::Ok)->setEnabled(idx<limit);
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
        item.insert("pickupKind",kind?kind->currentData().toInt():std::clamp(intAt(table,r,1,0),0,4));
        item.insert("capacity", std::clamp(intAt(table,r,2,1),1,65535));
        item.insert("initial", std::clamp(intAt(table,r,3,0),0,65535));
        item.insert("icon",table->item(r,4)
            ? std::clamp(table->item(r,4)->data(Qt::UserRole).toInt(),0,65535)
            : 65535);
        result.append(item);
    }
    return result;
}
QJsonArray defaultChoices()
{
    QJsonArray choices;
    for (int i=0;i<3;++i) {
        QJsonObject c; c.insert("text", ""); c.insert("reply", "");
        c.insert("next", -1); c.insert("requires", -1);
        c.insert("give", -1); c.insert("take", -1); c.insert("action", -1);
        choices.append(c);
    }
    return choices;
}
QString dialogueTitle(const QJsonObject &node, int index)
{
    return QStringLiteral("%1: %2 — %3").arg(index)
        .arg(node.value("speaker").toString().left(24), node.value("text").toString().left(35));
}
void editNode(QWidget *parent, QJsonArray &nodes, int row, const QJsonArray &items,
              const QVector<GameAdventureAsset> &objects)
{
    if (row < 0 || row >= nodes.size()) return;
    QJsonObject node = nodes[row].toObject();
    QDialog dialog(parent); dialog.setWindowTitle(QObject::tr("Dialogue Node %1").arg(row));
    dialog.setMinimumSize(820, 680); dialog.resize(1010, 815);
    auto *main = new QVBoxLayout(&dialog);
    auto *scroll = new QScrollArea(&dialog);
    scroll->setWidgetResizable(true);
    auto *content = new QWidget(scroll);
    auto *detail = new QVBoxLayout(content);
    scroll->setWidget(content); main->addWidget(scroll,1);
    auto *form = new QFormLayout;
    auto *speaker = new QLineEdit(node.value("speaker").toString(), &dialog);
    auto *text = new QTextEdit(&dialog); text->setPlainText(node.value("text").toString());
    text->setMaximumHeight(115);
    form->addRow(QObject::tr("Speaker"), speaker);
    form->addRow(QObject::tr("Dialogue text (auto wraps)"), text);
    detail->addLayout(form);
    QJsonArray choices = node.value("choices").toArray();
    while (choices.size() < 3) choices.append(defaultChoices().at(choices.size()));
    struct EditorFields {
        QTextEdit *label, *reply;
        QComboBox *next, *event, *mode;
        QSpinBox *customId;
        QComboBox *requires, *give, *take;
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
        fields[i].reply->setToolTip(QObject::tr("The selected player reply appears above the player's head. Up to five wrapped rows are supported."));
        fields[i].next=new QComboBox(box);
        fields[i].next->addItem(QObject::tr("Close conversation"),-1);
        for(int target=0;target<nodes.size();++target)
            fields[i].next->addItem(dialogueTitle(nodes[target].toObject(),target),target);
        fields[i].next->setCurrentIndex(std::max(0,fields[i].next->findData(choice.value("next").toInt(-1))));
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
        fields[i].give = combo(QObject::tr("Give this item"), choice.value("give").toInt(-1));
        fields[i].take = combo(QObject::tr("Take this item"), choice.value("take").toInt(-1));
        grid->addWidget(new QLabel(QObject::tr("Answer"),box),0,0);
        grid->addWidget(fields[i].label,0,1,1,3);
        grid->addWidget(new QLabel(QObject::tr("Player speech"),box),1,0);
        grid->addWidget(fields[i].reply,1,1,1,3);
        grid->addWidget(new QLabel(QObject::tr("Next"),box),2,0);
        grid->addWidget(fields[i].next,2,1);
        grid->addWidget(new QLabel(QObject::tr("Event / resource"),box),2,2);
        grid->addWidget(fields[i].event,2,3);
        grid->addWidget(fields[i].customId,3,4);
        grid->addWidget(new QLabel(QObject::tr("Needs"),box),3,0);
        grid->addWidget(fields[i].requires,3,1);
        grid->addWidget(new QLabel(QObject::tr("Give"),box),3,2);
        grid->addWidget(fields[i].give,3,3);
        grid->addWidget(new QLabel(QObject::tr("Take"),box),4,0);
        grid->addWidget(fields[i].take,4,1);
        fields[i].mode = new QComboBox(box);
        fields[i].mode->addItem(QObject::tr("Activate (close solid door)"),QStringLiteral("enable"));
        fields[i].mode->addItem(QObject::tr("Deactivate (open solid door)"),QStringLiteral("disable"));
        fields[i].mode->addItem(QObject::tr("Toggle"),QStringLiteral("toggle"));
        fields[i].mode->setCurrentIndex(std::max(0,fields[i].mode->findData(choice.value("targetAction").toString("enable"))));
        grid->addWidget(new QLabel(QObject::tr("Game Object action"),box),5,0);
        grid->addWidget(fields[i].mode,5,1,1,3);
        detail->addWidget(box);
    }
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
        c.insert("next",fields[i].next->currentData().toInt());
        const QString eventSelection=fields[i].event->currentData().toString();
        c.insert("action",eventSelection==QStringLiteral("custom")?fields[i].customId->value():-1);
        c.insert("requires",fields[i].requires->currentData().toInt());
        c.insert("give",fields[i].give->currentData().toInt());
        c.insert("take",fields[i].take->currentData().toInt());
        c.insert("targetObjectId",(eventSelection!=QStringLiteral("none") && eventSelection!=QStringLiteral("custom"))
            ?eventSelection:QString());
        c.insert("targetAction",fields[i].mode->currentData().toString());
        updated.append(c);
    }
    node.insert("choices",updated); nodes[row] = node;
}
} // namespace

bool editGameAdventure(QWidget *parent, QJsonObject *payload,
                       const QVector<GameAdventureAsset> &sprites,
                       const QVector<GameAdventureAsset> &atlases,
                       const QVector<GameAdventureAsset> &worldObjects,
                       const QVector<GameAdventureAsset> &collectables,
                       const QVector<QRgb> &foregroundPalette)
{
    if (!payload) return false;
    const QJsonObject old = *payload;
    QJsonArray nodes=old.value("nodes").toArray();
    QDialog dialog(parent); dialog.setWindowTitle(QObject::tr("Advanced Platformer — Adventure Editor"));
    dialog.setMinimumSize(890,670); dialog.resize(1060,800);
    auto *main = new QVBoxLayout(&dialog);
    auto *tabs = new QTabWidget(&dialog); main->addWidget(tabs,1);

    // Both inventory icons and dialogue frame tiles use the selected atlas.
    QComboBox *skinAtlas = nullptr;
    QSpinBox *tileSize = nullptr;
    auto *itemsPage = new QWidget(tabs); auto *itemsLayout = new QVBoxLayout(itemsPage);
    auto *items = new QTableWidget(0,5,itemsPage);
    items->setHorizontalHeaderLabels({QObject::tr("Item name (e.g. Brass Key)"),QObject::tr("Pick up from..."),
                                      QObject::tr("Max owned"),QObject::tr("Start with"),QObject::tr("Icon artwork")});
    items->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    items->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
    items->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);
    items->horizontalHeader()->setSectionResizeMode(3,QHeaderView::ResizeToContents);
    items->horizontalHeader()->setSectionResizeMode(4,QHeaderView::ResizeToContents);
    auto *collectionHelp=new QLabel(QObject::tr(
        "INVENTORY GUIDE: Each row is an item your game can recognise (for example, Brass Key). "
        "'Max owned' is how many can be carried; 'Start with' is how many the player begins with. "
        "Pick up from... matches the collectable TYPE in World Designer (Coin=1, Health=2, Key=3, Gem=4). "
        "A name like Kim_copy[1] is the placed object's name, NOT an inventory item. "
        "Choosing type 2 means EVERY Health-type collectable adds this row's item. "
        "Important for custom main.c: in on_pickup(), add game_adventure_collect(item->kind); "
        "after your existing score logic. Without that line, pickups will NOT enter inventory. "
        "Icon artwork comes from the Dialogue Box Tile Atlas; select one there first, or leave it empty."),itemsPage);
    collectionHelp->setWordWrap(true);itemsLayout->addWidget(collectionHelp);
    itemsLayout->addWidget(items,1);
    const QJsonArray oldItems = old.value("items").toArray();
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
        iconCell->setText(iconIndex==65535?QObject::tr("No icon — double-click to pick")
            :QObject::tr("Cell %1 — double-click to change").arg(iconIndex));
        iconCell->setFlags(iconCell->flags() & ~Qt::ItemIsEditable);
        auto *kind=new QComboBox(items);
        kind->addItem(QObject::tr("Manual / NPC dialogue (no automatic pickup)"),0);
        for(int k=1;k<=4;++k) {
            QStringList names;
            for(const auto &object:collectables) if(object.pickupKind==k) names<<object.name;
            const QString typeName=QStringList{QString(),QObject::tr("Coin"),QObject::tr("Health"),
                QObject::tr("Key"),QObject::tr("Gem")}.at(k);
            kind->addItem(QObject::tr("%1: %2 — %3").arg(k).arg(typeName)
                .arg(names.isEmpty()?QObject::tr("no matching objects placed"):names.join(QStringLiteral(", "))),k);
        }
        kind->setCurrentIndex(std::max(0,kind->findData(o.value("pickupKind").toInt(0))));
        items->setCellWidget(row,1,kind);
    };
    for (const auto &v:oldItems) appendItem(v.toObject());
    QObject::connect(items,&QTableWidget::cellDoubleClicked,&dialog,[&](int row,int column){
        if(column!=4 || row<0 || !items->item(row,4)) return;
        const QString id=skinAtlas?skinAtlas->currentData().toString():old.value("skinAtlasId").toString();
        const auto at=std::find_if(atlases.begin(),atlases.end(),[&](const auto &a){return a.id==id;});
        if(at==atlases.end()){
            QMessageBox::information(&dialog,QObject::tr("Choose inventory artwork"),
                QObject::tr("First select a Dialogue Tile Atlas in the 'Dialogue Box Atlas' tab. "
                            "Inventory icons currently use that same atlas."));
            return;
        }
        const QImage image=indexedPreview(at->path,foregroundPalette);
        const int size=tileSize?tileSize->value():old.value("tileSize").toInt(8);
        const int previous=items->item(row,4)->data(Qt::UserRole).toInt();
        const int chosen=chooseAdventureAtlasCell(&dialog,image,size,previous==65535?0:previous);
        if(chosen<0)return;
        auto *cell=items->item(row,4);
        cell->setData(Qt::UserRole,chosen);
        cell->setText(QObject::tr("Cell %1 — double-click to change").arg(chosen));
        QImage crop=image.copy((chosen%(image.width()/size))*size,(chosen/(image.width()/size))*size,size,size);
        cell->setIcon(QIcon(QPixmap::fromImage(crop.scaled(28,28,Qt::KeepAspectRatio,Qt::FastTransformation))));
    });
    auto *itemButtons = new QHBoxLayout;
    auto *itemAdd = new QPushButton(QObject::tr("+ Item"), itemsPage);
    auto *itemDel = new QPushButton(QObject::tr("Delete Item"), itemsPage);
    itemButtons->addWidget(itemAdd); itemButtons->addWidget(itemDel); itemButtons->addStretch();
    itemsLayout->addLayout(itemButtons);
    QObject::connect(itemAdd,&QPushButton::clicked,&dialog,[&] {
        if(items->rowCount()<64) appendItem({});
    });
    QObject::connect(itemDel,&QPushButton::clicked,&dialog,[&] {
        const int row=items->currentRow();
        if (row>=0 && QMessageBox::question(&dialog,QObject::tr("Remove Item"),
                QObject::tr("Delete item %1? Dialogue choice item references will be cleared.").arg(row))
                == QMessageBox::Yes) {
            items->removeRow(row);
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
                    choices[j]=c;
                }
                node.insert("choices",choices);nodes[i]=node;
            }
        }
    });
    tabs->addTab(itemsPage,QObject::tr("Inventory Items"));

    auto *npcPage = new QWidget(tabs); auto *npcLayout = new QVBoxLayout(npcPage);
    npcLayout->addWidget(new QLabel(QObject::tr("NPCs use existing placed Sprite resources. Move their sprites in the World Editor."),npcPage));
    auto *npcs = new QTableWidget(0,3,npcPage);
    npcs->setHorizontalHeaderLabels({QObject::tr("Sprite"),QObject::tr("Start node"),QObject::tr("Talk radius (px)")});
    npcs->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    npcLayout->addWidget(npcs,1);
    auto appendNpc = [&](const QString &id,int node,int radius, const QJsonObject &animation = QJsonObject()) {
        const int row=npcs->rowCount(); npcs->insertRow(row);
        auto it=std::find_if(sprites.begin(),sprites.end(),[&](const auto &s){return s.id==id;});
        auto *name=cell(it==sprites.end() ? QObject::tr("Missing Sprite") : it->name);
        name->setData(Qt::UserRole,id);
        name->setData(Qt::UserRole + 1,animation); name->setFlags(name->flags() & ~Qt::ItemIsEditable);
        npcs->setItem(row,0,name);
        auto *startNode=new QComboBox(npcs);
        for(int i=0;i<nodes.size();++i) startNode->addItem(dialogueTitle(nodes[i].toObject(),i),i);
        if(startNode->count()==0)startNode->addItem(QObject::tr("Create a dialogue node first"),0);
        startNode->setCurrentIndex(std::max(0,startNode->findData(node)));
        npcs->setCellWidget(row,1,startNode);
        npcs->setItem(row,2,cell(QString::number(radius)));
    };
    for(const auto &v: old.value("npcs").toArray()) {
        const QJsonObject o=v.toObject(); appendNpc(o.value("spriteId").toString(),o.value("node").toInt(),o.value("radius").toInt(48),o.value("animation").toObject());
    }
    auto refreshNpcNodes=[&] {
        for(int r=0;r<npcs->rowCount();++r){
            auto *cb=qobject_cast<QComboBox*>(npcs->cellWidget(r,1)); if(!cb)continue;
            const int previous=cb->currentData().toInt();cb->clear();
            for(int i=0;i<nodes.size();++i)cb->addItem(dialogueTitle(nodes[i].toObject(),i),i);
            if(cb->count()==0)cb->addItem(QObject::tr("Create a dialogue node first"),0);
            cb->setCurrentIndex(std::max(0,cb->findData(previous)));
        }
    };
    auto *npcButtons = new QHBoxLayout;
    auto *npcAdd = new QPushButton(QObject::tr("+ NPC"),npcPage);
    auto *npcDel = new QPushButton(QObject::tr("Delete NPC"),npcPage);
    auto *npcAnim = new QPushButton(QObject::tr("NPC Animations..."),npcPage);
    npcButtons->addWidget(npcAdd); npcButtons->addWidget(npcAnim); npcButtons->addWidget(npcDel); npcButtons->addStretch();
    npcLayout->addLayout(npcButtons);
    QObject::connect(npcAdd,&QPushButton::clicked,&dialog,[&] {
        QDialog picker(&dialog); picker.setWindowTitle(QObject::tr("Choose Placed Sprite"));
        auto *v=new QVBoxLayout(&picker); auto *cb=new QComboBox(&picker);
        for(const auto &s:sprites) cb->addItem(s.name,s.id);
        v->addWidget(cb);
        auto *b=new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,&picker);
        v->addWidget(b);
        QObject::connect(b,&QDialogButtonBox::accepted,&picker,&QDialog::accept);
        QObject::connect(b,&QDialogButtonBox::rejected,&picker,&QDialog::reject);
        if(!sprites.isEmpty() && picker.exec()==QDialog::Accepted)
            appendNpc(cb->currentData().toString(),0,48);
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
            QObject::connect(ui.list,&QListWidget::currentRowChanged,page,[&,state](int row){
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
            });
            QObject::connect(remove,&QPushButton::clicked,page,[&,state]{
                auto *list=states[state].list;
                const int row=list->currentRow();if(row<0)return;
                delete list->takeItem(row);
                if(list->count())list->setCurrentRow(std::min(row,list->count()-1));
                else states[state].preview->setText(QObject::tr("No frames"));
            });
            auto move=[&](int state,int step){
                auto *list=states[state].list;const int old=list->currentRow();
                const int next=old+step;if(old<0 || next<0 || next>=list->count())return;
                QListWidgetItem *item=list->takeItem(old);list->insertItem(next,item);list->setCurrentRow(next);
            };
            QObject::connect(up,&QPushButton::clicked,page,[&,state,move]{move(state,-1);});
            QObject::connect(down,&QPushButton::clicked,page,[&,state,move]{move(state,+1);});
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
        npcs->removeRow(row);
    });
    tabs->addTab(npcPage,QObject::tr("NPCs"));

    auto *dialoguePage = new QWidget(tabs); auto *dialogueLayout = new QVBoxLayout(dialoguePage);
    dialogueLayout->addWidget(new QLabel(QObject::tr("Double-click a node to edit the speaker, wrapped dialogue and its three choices."),dialoguePage));
    auto *nodeList = new QListWidget(dialoguePage); dialogueLayout->addWidget(nodeList,1);
    auto redrawNodes = [&] {
        const int row=nodeList->currentRow(); nodeList->clear();
        for(int i=0;i<nodes.size();++i) nodeList->addItem(dialogueTitle(nodes[i].toObject(),i));
        if(!nodes.isEmpty()) nodeList->setCurrentRow(std::clamp(row,0,int(nodes.size())-1));
    };
    redrawNodes();
    auto *nodeButtons=new QHBoxLayout;
    auto *nodeAdd=new QPushButton(QObject::tr("+ Dialogue Node"),dialoguePage);
    auto *nodeEdit=new QPushButton(QObject::tr("Edit Node..."),dialoguePage);
    auto *nodeDel=new QPushButton(QObject::tr("Delete Node"),dialoguePage);
    nodeButtons->addWidget(nodeAdd);nodeButtons->addWidget(nodeEdit);nodeButtons->addWidget(nodeDel);nodeButtons->addStretch();
    dialogueLayout->addLayout(nodeButtons);
    QObject::connect(nodeAdd,&QPushButton::clicked,&dialog,[&] {
        if(nodes.size()>=256) return;
        QJsonObject node; node.insert("speaker","NPC"); node.insert("text","Hello!");
        node.insert("choices",defaultChoices()); nodes.append(node);
        redrawNodes(); nodeList->setCurrentRow(nodes.size()-1);refreshNpcNodes();
    });
    auto doNodeEdit=[&] {
        editNode(&dialog,nodes,nodeList->currentRow(),tableItems(items),worldObjects);
        redrawNodes();refreshNpcNodes();
    };
    QObject::connect(nodeEdit,&QPushButton::clicked,&dialog,doNodeEdit);
    QObject::connect(nodeList,&QListWidget::itemDoubleClicked,&dialog,[&](QListWidgetItem*){doNodeEdit();});
    QObject::connect(nodeDel,&QPushButton::clicked,&dialog,[&] {
        const int row=nodeList->currentRow(); if(row<0) return;
        if(QMessageBox::question(&dialog,QObject::tr("Delete Dialogue"),
                                 QObject::tr("Remove node %1 and fix node references?").arg(row))!=QMessageBox::Yes) return;
        nodes.removeAt(row);
        for(int i=0;i<nodes.size();++i){
            QJsonObject node=nodes[i].toObject(); QJsonArray cs=node.value("choices").toArray();
            for(int c=0;c<cs.size();++c){ QJsonObject choice=cs[c].toObject();
                const int next=choice.value("next").toInt(-1);
                if(next==row) choice.insert("next",-1);
                else if(next>row) choice.insert("next",next-1);
                cs[c]=choice;
            }
            node.insert("choices",cs);nodes[i]=node;
        }
        for(int r=0;r<npcs->rowCount();++r){
            auto *cb=qobject_cast<QComboBox*>(npcs->cellWidget(r,1));if(!cb)continue;
            int next=cb->currentData().toInt();
            if(next>=row)cb->setCurrentIndex(std::max(0,cb->findData(next==row?0:next-1)));
        }
        redrawNodes();refreshNpcNodes();
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
    outlineColour->setEnabled(outline->isChecked());
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
    QObject::connect(outline,&QCheckBox::toggled,outlineColour,&QWidget::setEnabled);
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
    skinLayout->addLayout(tiles);
    auto *preview=new QLabel(skinPage);preview->setMinimumHeight(112);
    preview->setAlignment(Qt::AlignCenter);skinLayout->addWidget(preview,1);
    auto updatePreview=[&] {
        auto it=std::find_if(atlases.begin(),atlases.end(),[&](const auto &a){return a.id==skinAtlas->currentData().toString();});
        if(it==atlases.end()){
            preview->setText(QObject::tr("No Tile Atlas selected — simple box used."));
            for(int i=0;i<9;++i){tilePick[i]->setText(QObject::tr("Cell %1").arg(chosenTiles[i]));tilePick[i]->setIcon(QIcon());}
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
    QObject::connect(skinAtlas,QOverload<int>::of(&QComboBox::currentIndexChanged),&dialog,[&](int){updatePreview();});
    QObject::connect(tileSize,QOverload<int>::of(&QSpinBox::valueChanged),&dialog,[&](int){updatePreview();});
    updatePreview();
    tabs->addTab(skinPage,QObject::tr("Dialogue Box Atlas"));

    // Stage 4.33: Height is a minimum, not a fixed text budget. The preview
    // uses REAL conversation nodes and the runtime's 8x16 row/choice formula.
    auto *positionPage=new QWidget(tabs);
    auto *positionLayout=new QVBoxLayout(positionPage);
    auto *positionHelp=new QLabel(QObject::tr(
        "Choose a conversation below to preview its actual name, wrapped text, "
        "and TWO visible answers. Height is a minimum: the box grows for longer "
        "dialogue and rises on screen when needed. Use Up/Down to reach other answers."),positionPage);
    positionHelp->setWordWrap(true);positionLayout->addWidget(positionHelp);
    auto *previewSelectors=new QHBoxLayout;
    auto *previewNode=new QComboBox(positionPage);
    auto *previewAnswer=new QComboBox(positionPage);
    previewSelectors->addWidget(new QLabel(QObject::tr("Preview dialogue"),positionPage));
    previewSelectors->addWidget(previewNode,2);
    previewSelectors->addWidget(new QLabel(QObject::tr("Selected answer"),positionPage));
    previewSelectors->addWidget(previewAnswer,1);
    positionLayout->addLayout(previewSelectors);
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
    positionLayout->addLayout(positionFields);
    auto *screenPreview=new AdventureDialoguePositionPreview(positionPage);
    screenPreview->setAlignment(Qt::AlignCenter);
    auto *previewRow=new QHBoxLayout;
    previewRow->addStretch();previewRow->addWidget(screenPreview);previewRow->addStretch();
    positionLayout->addLayout(previewRow,1);
    auto *positionStatus=new QLabel(positionPage);
    positionStatus->setWordWrap(true);positionLayout->addWidget(positionStatus);
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
        if(previewAnswer->count()==0)previewAnswer->addItem(QObject::tr("No answers"),-1);
        previewAnswer->setCurrentIndex(std::max(0,previewAnswer->findData(prev)));
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
    auto refreshPosition=[&] {
        const QJsonObject node=chosenNode();
        const AdventurePreviewMetrics metrics=adventureMeasure(node,dialogW->value(),dialogH->value(),outline->isChecked());
        const int w=dialogW->value(), h=metrics.height;
        if(dialogX->value()>480-w){
            dialogX->blockSignals(true);dialogX->setValue(480-w);dialogX->blockSignals(false);
        }
        const int actualY=std::min(dialogY->value(),320-h);
        const int x=dialogX->value();
        screenPreview->frameW=w;screenPreview->frameH=h;
        screenPreview->frameX=x;screenPreview->frameY=actualY;
        QImage screen(480,320,QImage::Format_ARGB32);
        screen.fill(QColor(35,40,52));
        QPainter painter(&screen);
        painter.setPen(QColor(78,91,113));
        painter.drawRect(0,0,479,319);
        for(int gx=80;gx<480;gx+=80)painter.drawLine(gx,0,gx,320);
        for(int gy=80;gy<320;gy+=80)painter.drawLine(0,gy,480,gy);
        painter.fillRect(QRect(x,actualY,w,h),QColor(8,14,29,223));
        painter.setPen(QPen(metrics.overflow?QColor(255,83,83):QColor(255,212,71),2));
        painter.drawRect(QRect(x,actualY,w,h).adjusted(1,1,-2,-2));
        QFont font=QFont(QStringLiteral("Monospace"));font.setStyleHint(QFont::TypeWriter);
        font.setPixelSize(13);painter.setFont(font);
        painter.setClipRect(QRect(x+2,actualY+2,w-4,h-4));
        painter.setPen(QColor(234,240,250));
        painter.drawText(x+12,actualY+20,node.value("speaker").toString().left(36));
        const auto body=adventurePreviewRows(node.value("text").toString().left(512),metrics.bodyColumns);
        const int bodyY=actualY+32;
        const int choiceSpace=metrics.answerHeight?metrics.answerHeight+9:0;
        const int bottom=actualY+h-12;
        const int visibleRows=std::clamp((bottom-bodyY-choiceSpace)/metrics.lineHeight,0,int(body.size()));
        for(int i=0;i<visibleRows;++i)
            painter.drawText(x+12,bodyY+i*metrics.lineHeight+12,body[i]);
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
        int cy=bodyY+visibleRows*metrics.lineHeight+9;
        for(int i=first;i<std::min(first+2,int(labels.size()));++i) {
            const auto rows=adventurePreviewRows(labels[i].second,metrics.answerColumns,32);
            const int lines=std::min(int(rows.size()),std::max(0,(bottom-cy)/metrics.lineHeight));
            if(!lines)break;
            painter.drawText(x+12,cy+12,i==selectedPos?QStringLiteral(">") : QStringLiteral(" "));
            for(int k=0;k<lines;++k)
                painter.drawText(x+26,cy+k*metrics.lineHeight+12,rows[k]);
            if(i==first && first>0)painter.drawText(x+w-20,cy+12,QStringLiteral("^"));
            if(i==std::min(first+2,int(labels.size()))-1 && first+2<int(labels.size()))
                painter.drawText(x+w-20,cy+(lines-1)*metrics.lineHeight+12,QStringLiteral("v"));
            cy+=lines*metrics.lineHeight+4;
        }
        painter.setClipping(false);
        // Dashed line makes the interior text budget visible independently of the frame.
        painter.setPen(QPen(metrics.overflow?QColor(255,83,83):QColor(96,190,128),1,Qt::DashLine));
        painter.drawRect(QRect(x+8,actualY+27,w-16,h-36));
        painter.end();
        screenPreview->setPixmap(QPixmap::fromImage(screen));
        QString status=QObject::tr("Needed: %1 px  |  Box: %2 px (min %3)  |  %4 NPC text rows; at most 2 choices")
            .arg(metrics.needed).arg(h).arg(dialogH->value()).arg(metrics.rows);
        if (actualY!=dialogY->value())
            status+=QObject::tr("  |  Auto-raised to Y=%1 to stay on screen").arg(actualY);
        if(metrics.overflow)
            status+=QObject::tr("  |  WARNING: Too much text for 320px. Widen the box or shorten the conversation.");
        positionStatus->setText(status);
    };
    QObject::connect(placement,QOverload<int>::of(&QComboBox::currentIndexChanged),positionPage,[&](int choice){
        if(!choice)return;
        const int w=dialogW->value();
        const int h=adventureMeasure(chosenNode(),w,dialogH->value(),outline->isChecked()).height;
        int x=(480-w)/2,y=(choice==1 || choice==3 || choice==4)?8:320-h-8;
        if(choice==3 || choice==5)x=8;
        if(choice==4 || choice==6)x=480-w-8;
        dialogX->setValue(std::max(0,x));dialogY->setValue(std::max(0,y));
        refreshPosition();
    });
    for(QSpinBox *field:{dialogX,dialogY,dialogW,dialogH})
        QObject::connect(field,QOverload<int>::of(&QSpinBox::valueChanged),positionPage,[&](int){refreshPosition();});
    QObject::connect(previewNode,QOverload<int>::of(&QComboBox::currentIndexChanged),positionPage,[&](int){refreshAnswers();refreshPosition();});
    QObject::connect(previewAnswer,QOverload<int>::of(&QComboBox::currentIndexChanged),positionPage,[&](int){refreshPosition();});
    QObject::connect(outline,&QCheckBox::toggled,positionPage,[&](bool){refreshPosition();});
    screenPreview->moved=[&](int x,int y){
        dialogX->setValue(x);dialogY->setValue(y);refreshPosition();
    };
    const int positionTabIndex=tabs->addTab(positionPage,QObject::tr("Dialogue Position"));
    QObject::connect(tabs,&QTabWidget::currentChanged,positionPage,[&](int index){
        if(index==positionTabIndex){refreshNodes();refreshPosition();}
    });
    refreshNodes();refreshPosition();
    positionLayout->addWidget(new QLabel(QObject::tr(
        "DRAG the yellow box to move it. The green dashed guide marks its text area; "
        "red means the conversation exceeds the LCD height. Only two answers are shown at a time."),positionPage));


    auto *buttons=new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,&dialog);
    main->addWidget(buttons);
    QObject::connect(buttons,&QDialogButtonBox::accepted,&dialog,&QDialog::accept);
    QObject::connect(buttons,&QDialogButtonBox::rejected,&dialog,&QDialog::reject);
    if(dialog.exec()!=QDialog::Accepted)return false;
    QJsonObject result=old;
    result.insert("items",tableItems(items));
    QJsonArray outNpcs;
    for(int row=0;row<npcs->rowCount();++row){
        QJsonObject o; o.insert("spriteId",npcs->item(row,0)->data(Qt::UserRole).toString());
        auto *chosen=qobject_cast<QComboBox*>(npcs->cellWidget(row,1));
        o.insert("node",std::clamp(chosen?chosen->currentData().toInt():0,0,std::max(0,int(nodes.size())-1)));
        o.insert("radius",std::clamp(intAt(npcs,row,2,48),8,512));
        o.insert("animation",npcs->item(row,0)->data(Qt::UserRole + 1).toJsonObject());
        outNpcs.append(o);
    }
    result.insert("npcs",outNpcs);result.insert("nodes",nodes);
    result.insert("dialogX",dialogX->value());
    result.insert("dialogY",dialogY->value());
    result.insert("dialogWidth",dialogW->value());
    result.insert("dialogHeight",dialogH->value());
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
    *payload=result;return true;
}
