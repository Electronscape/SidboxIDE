#include "gameadventureeditor.h"
#include "ppbcodec.h"
#include <QAbstractItemView>
#include <QComboBox>
#include <QCheckBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QImage>
#include <QJsonArray>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
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
#include <QIcon>
#include <QSize>
#include <functional>
#include <array>
#include <algorithm>

namespace {
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
        item.insert("icon", std::clamp(intAt(table,r,4,0),0,255));
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
    dialog.resize(730, 640);
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
        QLineEdit *label, *reply;
        QComboBox *next, *event, *mode;
        QSpinBox *customId;
        QComboBox *requires, *give, *take;
    } fields[3];
    for (int i=0;i<3;++i) {
        const QJsonObject choice = choices[i].toObject();
        auto *box = new QGroupBox(QObject::tr("Choice %1").arg(i+1), &dialog);
        auto *grid = new QGridLayout(box);
        fields[i].label = new QLineEdit(choice.value("text").toString(), box);
        fields[i].reply = new QLineEdit(choice.value("reply").toString(), box);
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
        QJsonObject c; c.insert("text",fields[i].label->text().left(75));
        c.insert("reply",fields[i].reply->text().left(75));
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
    dialog.resize(810,630);
    auto *main = new QVBoxLayout(&dialog);
    auto *tabs = new QTabWidget(&dialog); main->addWidget(tabs,1);

    auto *itemsPage = new QWidget(tabs); auto *itemsLayout = new QVBoxLayout(itemsPage);
    auto *items = new QTableWidget(0,5,itemsPage);
    items->setHorizontalHeaderLabels({QObject::tr("Item name"),QObject::tr("Collectable kind (0–4)"),
                                      QObject::tr("Capacity"),QObject::tr("Start qty"),QObject::tr("Icon index")});
    items->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    items->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
    items->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);
    items->horizontalHeader()->setSectionResizeMode(3,QHeaderView::ResizeToContents);
    items->horizontalHeader()->setSectionResizeMode(4,QHeaderView::ResizeToContents);
    auto *collectionHelp=new QLabel(QObject::tr("Automatic pickup: select the SAME Collectable kind used by your placed Game Object. "
        "When the generated on_pickup callback calls game_adventure_collect(item->kind), "
        "it adds one matching item. Kind 0 is manual/dialogue only. "
        "If your main.c is hand-edited, retain that bridge call."),itemsPage);
    collectionHelp->setWordWrap(true);itemsLayout->addWidget(collectionHelp);
    itemsLayout->addWidget(items,1);
    const QJsonArray oldItems = old.value("items").toArray();
    auto appendItem = [&](const QJsonObject &o) {
        const int row=items->rowCount(); items->insertRow(row);
        const QStringList v{ o.value("name").toString("New Item"),
            QString::number(o.value("pickupKind").toInt(0)),
            QString::number(o.value("capacity").toInt(1)),
            QString::number(o.value("initial").toInt(0)),
            QString::number(o.value("icon").toInt(0)) };
        for(int c=0;c<5;++c) if(c!=1)items->setItem(row,c,cell(v[c]));
        auto *kind=new QComboBox(items);
        kind->addItem(QObject::tr("0 — Manual / dialogue"),0);
        for(int k=1;k<=4;++k) {
            QStringList names;
            for(const auto &object:collectables) if(object.pickupKind==k) names<<object.name;
            kind->addItem(QObject::tr("%1 — %2").arg(k)
                .arg(names.isEmpty()?QObject::tr("No placed collectables"):names.join(QStringLiteral(", "))),k);
        }
        kind->setCurrentIndex(std::max(0,kind->findData(o.value("pickupKind").toInt(0))));
        items->setCellWidget(row,1,kind);
    };
    for (const auto &v:oldItems) appendItem(v.toObject());
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
        npcs->setItem(row,0,name); npcs->setItem(row,1,cell(QString::number(node)));
        npcs->setItem(row,2,cell(QString::number(radius)));
    };
    for(const auto &v: old.value("npcs").toArray()) {
        const QJsonObject o=v.toObject(); appendNpc(o.value("spriteId").toString(),o.value("node").toInt(),o.value("radius").toInt(48),o.value("animation").toObject());
    }
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
        anim.resize(710,485);
        auto *layout=new QVBoxLayout(&anim);
        auto *help=new QLabel(QObject::tr("Select an Idle or Talking state, choose its first and last frame from the sprite atlas, then set the speed. "
            "NPC animations use consecutive cells. The SIDBOX Sprite BOB supports cells 0–255."),&anim);
        help->setWordWrap(true);layout->addWidget(help);
        auto *stateTabs=new QTabWidget(&anim);layout->addWidget(stateTabs,1);
        struct AnimUi {
            int first=0,last=0;
            QCheckBox *enabled=nullptr;
            QLabel *range=nullptr,*strip=nullptr,*speedText=nullptr;
            QPushButton *firstButton=nullptr,*lastButton=nullptr;
            QSlider *speed=nullptr;
        } states[2];
        const char *firstKeys[]={"idleFirst","talkFirst"};
        const char *countKeys[]={"idleCount","talkCount"};
        const char *speedKeys[]={"idleSpeed","talkSpeed"};
        auto previewState=[&](int s) {
            AnimUi &ui=states[s];
            ui.first=std::clamp(ui.first,0,frames-1);
            ui.last=std::clamp(ui.last,ui.first,frames-1);
            const int total=ui.enabled->isChecked()?ui.last-ui.first+1:0;
            ui.range->setText(total?QObject::tr("Frames %1–%2 (%3 pictures)").arg(ui.first).arg(ui.last).arg(total)
                :QObject::tr("Disabled — keep this sprite static in this state"));
            ui.firstButton->setText(QObject::tr("First: %1 — choose...").arg(ui.first));
            ui.lastButton->setText(QObject::tr("Last: %1 — choose...").arg(ui.last));
            ui.firstButton->setEnabled(ui.enabled->isChecked());
            ui.lastButton->setEnabled(ui.enabled->isChecked());
            ui.speed->setEnabled(ui.enabled->isChecked());
            ui.speedText->setText(QObject::tr("%1 game frames / picture").arg(ui.speed->value()));
            const int thumbnails=std::min(total,10);
            if(!thumbnails){ui.strip->setPixmap(QPixmap());ui.strip->setText(QObject::tr("No animation frames"));return;}
            const int scale=std::min(4,std::max(1,560/(std::max(1,thumbnails)*tileW)));
            QImage output(thumbnails*tileW*scale,tileH*scale,QImage::Format_ARGB32);
            output.fill(Qt::transparent);QPainter painter(&output);
            painter.setRenderHint(QPainter::SmoothPixmapTransform,false);
            for(int i=0;i<thumbnails;++i){
                int idx=ui.first+i;
                painter.drawImage(QRect(i*tileW*scale,0,tileW*scale,tileH*scale),atlas,
                    QRect((idx%cols)*tileW,(idx/cols)*tileH,tileW,tileH));
            }
            painter.end();ui.strip->setText(QString());ui.strip->setPixmap(QPixmap::fromImage(output));
        };
        for (int s=0;s<2;++s) {
            AnimUi &ui=states[s];
            ui.first=std::clamp(saved.value(firstKeys[s]).toInt(0),0,frames-1);
            const int count=saved.value(countKeys[s]).toInt(0);
            ui.last=std::min(frames-1,ui.first+std::max(0,count-1));
            QWidget *page=new QWidget(stateTabs);auto *v=new QVBoxLayout(page);
            ui.enabled=new QCheckBox(QObject::tr("Enable %1 animation").arg(s==0?QObject::tr("Idle"):QObject::tr("Talking")),page);
            ui.enabled->setChecked(count>0);v->addWidget(ui.enabled);
            auto *rangeButtons=new QHBoxLayout;
            ui.firstButton=new QPushButton(page);ui.lastButton=new QPushButton(page);
            rangeButtons->addWidget(ui.firstButton);rangeButtons->addWidget(ui.lastButton);
            v->addLayout(rangeButtons);
            ui.range=new QLabel(page);v->addWidget(ui.range);
            ui.strip=new QLabel(page);ui.strip->setAlignment(Qt::AlignCenter);
            ui.strip->setMinimumHeight(std::max(80,tileH*4+10));v->addWidget(ui.strip,1);
            auto *speedRow=new QHBoxLayout;speedRow->addWidget(new QLabel(QObject::tr("Speed"),page));
            ui.speed=new QSlider(Qt::Horizontal,page);ui.speed->setRange(1,60);
            ui.speed->setValue(std::clamp(saved.value(speedKeys[s]).toInt(s?5:6),1,60));
            speedRow->addWidget(ui.speed,1);
            ui.speedText=new QLabel(page);speedRow->addWidget(ui.speedText);v->addLayout(speedRow);
            stateTabs->addTab(page,s?QObject::tr("Talking"):QObject::tr("Idle"));
            QObject::connect(ui.firstButton,&QPushButton::clicked,&anim,[&,s] {
                AnimUi &a=states[s];
                const int next=chooseAdventureAtlasCell(&anim,atlas,tileW,a.first,frames,tileH);
                if(next<0)return;
                a.first=next;
                if(a.last<a.first)a.last=a.first;
                previewState(s);
            });
            QObject::connect(ui.lastButton,&QPushButton::clicked,&anim,[&,s] {
                AnimUi &a=states[s];
                const int next=chooseAdventureAtlasCell(&anim,atlas,tileW,a.last,frames,tileH);
                if(next<0)return;
                a.last=next;
                if(a.first>a.last)a.first=a.last;
                previewState(s);
            });
            QObject::connect(ui.enabled,&QCheckBox::toggled,&anim,[&,s](bool){previewState(s);});
            QObject::connect(ui.speed,&QSlider::valueChanged,&anim,[&,s](int){previewState(s);});
            previewState(s);
        }
        auto *buttons=new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel,&anim);
        layout->addWidget(buttons);
        QObject::connect(buttons,&QDialogButtonBox::accepted,&anim,&QDialog::accept);
        QObject::connect(buttons,&QDialogButtonBox::rejected,&anim,&QDialog::reject);
        if(anim.exec()!=QDialog::Accepted)return;
        QJsonObject result;
        for(int s=0;s<2;++s) {
            const AnimUi &ui=states[s];
            result.insert(firstKeys[s],ui.first);
            result.insert(countKeys[s],ui.enabled->isChecked()?ui.last-ui.first+1:0);
            result.insert(speedKeys[s],ui.speed->value());
        }
        name->setData(Qt::UserRole+1,result);
    });
    QObject::connect(npcDel,&QPushButton::clicked,&dialog,[&] {
        if(npcs->currentRow()>=0) npcs->removeRow(npcs->currentRow());
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
        redrawNodes(); nodeList->setCurrentRow(nodes.size()-1);
    });
    auto doNodeEdit=[&] {
        editNode(&dialog,nodes,nodeList->currentRow(),tableItems(items),worldObjects); redrawNodes();
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
        for(int r=0;r<npcs->rowCount();++r){ int next=intAt(npcs,r,1,0);
            if(next>=row) npcs->item(r,1)->setText(QString::number(next==row?0:next-1));
        }
        redrawNodes();
    });
    tabs->addTab(dialoguePage,QObject::tr("Dialogues & Choices"));

    auto *skinPage=new QWidget(tabs);auto *skinLayout=new QVBoxLayout(skinPage);
    auto *skinForm=new QFormLayout;
    auto *skinAtlas=new QComboBox(skinPage); skinAtlas->addItem(QObject::tr("No atlas (simple box)"),QString());
    for(const auto &atlas:atlases) skinAtlas->addItem(atlas.name,atlas.id);
    skinAtlas->setCurrentIndex(std::max(0,skinAtlas->findData(old.value("skinAtlasId").toString())));
    auto *tileSize=new QSpinBox(skinPage);tileSize->setRange(4,32);tileSize->setValue(old.value("tileSize").toInt(8));
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
    skinForm->addRow(QObject::tr("Text colour (foreground palette)"),textColour);
    skinForm->addRow(QString(),outline);
    skinForm->addRow(QObject::tr("Outline colour (foreground palette)"),outlineColour);
    skinForm->addRow(QObject::tr("Frames per typed character"),speed);
    skinLayout->addLayout(skinForm);
    auto *instruction=new QLabel(QObject::tr("Select an atlas then click any of the nine frame parts below to pick its tile visually. "
        "Tile Atlas selections can exceed cell 255. Cell size (px) is unchanged."),skinPage);
    instruction->setWordWrap(true);skinLayout->addWidget(instruction);
    auto *tiles=new QGridLayout;QPushButton *tilePick[9];int chosenTiles[9];
    const QJsonArray indices=old.value("skinIndices").toArray();
    for(int i=0;i<9;++i){
        chosenTiles[i]=std::clamp(i<indices.size()?indices[i].toInt(i):i,0,65535);
        tilePick[i]=new QPushButton(skinPage);
        tilePick[i]->setFixedSize(120,54);
        tiles->addWidget(tilePick[i],i/3,i%3);
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
                const QImage cellImage=atlas.copy((chosenTiles[i]%cols)*t,(chosenTiles[i]/cols)*t,t,t);
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
            painter.drawImage(QRect(x*t,y*t,t,t),atlas,QRect((idx%cols)*t,(idx/cols)*t,t,t));
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
    QObject::connect(skinAtlas,QOverload<int>::of(&QComboBox::currentIndexChanged),&dialog,[&](int){updatePreview();});
    QObject::connect(tileSize,QOverload<int>::of(&QSpinBox::valueChanged),&dialog,[&](int){updatePreview();});
    updatePreview();
    tabs->addTab(skinPage,QObject::tr("Dialogue Box Atlas"));

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
        o.insert("node",std::clamp(intAt(npcs,row,1,0),0,std::max(0,int(nodes.size())-1)));
        o.insert("radius",std::clamp(intAt(npcs,row,2,48),8,512));
        o.insert("animation",npcs->item(row,0)->data(Qt::UserRole + 1).toJsonObject());
        outNpcs.append(o);
    }
    result.insert("npcs",outNpcs);result.insert("nodes",nodes);
    result.insert("skinAtlasId",skinAtlas->currentData().toString());
    result.insert("tileSize",tileSize->value());result.insert("framesPerChar",speed->value());
    result.insert("textColourIndex",chosenText);
    result.insert("textOutline",outline->isChecked());
    result.insert("outlineColourIndex",chosenOutline);
    QJsonArray cells;for(int i=0;i<9;++i)cells.append(chosenTiles[i]);
    result.insert("skinIndices",cells);
    *payload=result;return true;
}
