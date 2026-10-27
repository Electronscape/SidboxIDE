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
    auto *subtitle=new QLineEdit(saved.value(QStringLiteral("subtitle")).toString(QStringLiteral("Choose a save to retry")),&dialog);
    title->setMaxLength(40);subtitle->setMaxLength(50);
    form->addRow(QObject::tr("Heading"),title);
    form->addRow(QObject::tr("Description"),subtitle);
    auto *pos=new QWidget(&dialog);auto *position=new QHBoxLayout(pos);position->setContentsMargins(0,0,0,0);
    auto *x=new QSpinBox(pos);x->setRange(8,400);x->setValue(saved.value(QStringLiteral("titleX")).toInt(50));
    auto *y=new QSpinBox(pos);y->setRange(16,72);y->setValue(saved.value(QStringLiteral("titleY")).toInt(45));
    position->addWidget(new QLabel(QObject::tr("X"),pos));position->addWidget(x);
    position->addWidget(new QLabel(QObject::tr("Y"),pos));position->addWidget(y);
    form->addRow(QObject::tr("Heading position"),pos);
    auto *colours=new QWidget(&dialog);auto *cols=new QHBoxLayout(colours);cols->setContentsMargins(0,0,0,0);
    QSpinBox *values[4];
    const char *keys[]={"background","border","text","accent"};
    const int defaults[]={2,15,15,14};
    for(int n=0;n<4;++n){
        cols->addWidget(new QLabel(QString::fromLatin1(keys[n]),colours));
        values[n]=new QSpinBox(colours);values[n]->setRange(0,255);
        values[n]->setValue(saved.value(QLatin1String(keys[n])).toInt(defaults[n]));
        cols->addWidget(values[n]);
    }
    form->addRow(QObject::tr("Palette indices"),colours);
    auto *preview=new QLabel(&dialog);preview->setMinimumSize(480,320);
    preview->setAlignment(Qt::AlignCenter);root->addWidget(preview,1);
    const auto redraw=[=](){
        QPixmap pix(480,320);pix.fill(QColor(16,20,31));
        QPainter paint(&pix);paint.setRenderHint(QPainter::Antialiasing,false);
        const QColor palette[]={QColor(16,20,31),QColor(193,161,99),QColor(239,238,218),QColor(105,190,235)};
        Q_UNUSED(palette);
        paint.fillRect(pix.rect(),QColor::fromHsv((values[0]->value()*7)%360,60,35));
        paint.setPen(QColor::fromHsv((values[1]->value()*7)%360,70,220));
        paint.drawRect(10,10,459,299);
        paint.setPen(QColor::fromHsv((values[2]->value()*7)%360,25,250));
        paint.setFont(QFont(QStringLiteral("Monospace"),13,QFont::Bold));
        paint.drawText(x->value(),y->value()+14,title->text());
        paint.drawText(x->value(),y->value()+38,subtitle->text());
        paint.drawText(34,110,QObject::tr("CHOOSE SAVE TO RELOAD"));
        for(int i=0;i<10;++i)
            paint.drawText(36+(i/5)*212,145+(i%5)*23,
                           QStringLiteral("  SLOT %1  SAVED").arg(i+1,2,10,QLatin1Char('0')));
        paint.drawText(28,296,QObject::tr("FIRE1 LOAD SLOT   FIRE2 LAST SAVE"));
        paint.end();preview->setPixmap(pix);
    };
    QObject::connect(enabled,&QCheckBox::toggled,&dialog,[=](bool){redraw();});
    QObject::connect(title,&QLineEdit::textChanged,&dialog,[=](const QString &){redraw();});
    QObject::connect(subtitle,&QLineEdit::textChanged,&dialog,[=](const QString &){redraw();});
    for(auto *v:values)QObject::connect(v,qOverload<int>(&QSpinBox::valueChanged),&dialog,[=](int){redraw();});
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
    return cgRpgWrite(path,out,error);
}

inline bool editGameWorldMap(QWidget *parent,const QString &projectRoot,QString *error=nullptr)
{
    const QString path=QDir(projectRoot).filePath(QStringLiteral(".codergirl/world-map.json"));
    const QJsonObject saved=cgRpgRead(path);
    QDialog dialog(parent);dialog.setWindowTitle(QObject::tr("World Map Designer"));
    auto *root=new QVBoxLayout(&dialog);
    auto *controls=new QHBoxLayout;root->addLayout(controls);
    auto *w=new QSpinBox(&dialog);w->setRange(480,4096);w->setValue(saved.value(QStringLiteral("width")).toInt(1024));
    auto *h=new QSpinBox(&dialog);h->setRange(320,4096);h->setValue(saved.value(QStringLiteral("height")).toInt(768));
    controls->addWidget(new QLabel(QObject::tr("Canvas width"),&dialog));controls->addWidget(w);
    controls->addWidget(new QLabel(QObject::tr("Height"),&dialog));controls->addWidget(h);
    controls->addStretch();
    root->addWidget(new QLabel(QObject::tr("Drag the world markers to their map positions (use scrollbars to move the canvas). "
        "The runtime map pans by touchscreen drag or D-pad. FIRE2 returns to the journal."),&dialog));
    auto *scene=new QGraphicsScene(&dialog);
    scene->setBackgroundBrush(QColor(25,35,52));
    auto *view=new QGraphicsView(scene,&dialog);
    view->setRenderHint(QPainter::Antialiasing,false);
    // Leave mouse dragging to the movable world markers; use scrollbars to pan.
    view->setDragMode(QGraphicsView::NoDrag);
    view->setMinimumSize(700,450);
    root->addWidget(view,1);
    QMap<QString,QPointF> savedPoints;
    for(const QJsonValue &v:saved.value(QStringLiteral("points")).toArray()){
        const QJsonObject p=v.toObject();
        savedPoints.insert(p.value(QStringLiteral("name")).toString(),
                           QPointF(p.value(QStringLiteral("x")).toInt(),p.value(QStringLiteral("y")).toInt()));
    }
    QStringList worlds;
    const QDir compiled(QDir(projectRoot).filePath(QStringLiteral("worlds")));
    for(const QFileInfo &entry:compiled.entryInfoList(QDir::Dirs|QDir::NoDotAndDotDot,QDir::Name))
        if(QFileInfo::exists(QDir(entry.absoluteFilePath()).filePath(QStringLiteral("world-build.json"))))
            worlds<<entry.fileName();
    // Also allow designing worlds that haven't been exported yet.
    const QDir savedDesigns(QDir(projectRoot).filePath(QStringLiteral(".codergirl/worlds")));
    for(const QFileInfo &entry:savedDesigns.entryInfoList(QDir::Dirs|QDir::NoDotAndDotDot,QDir::Name))
        if(!worlds.contains(entry.fileName()))worlds<<entry.fileName();
    if(worlds.isEmpty()){
        for(auto it=savedPoints.cbegin();it!=savedPoints.cend();++it)worlds<<it.key();
    }
    QMap<QString,QGraphicsRectItem *> markers;
    const auto resizeScene=[=](){
        scene->setSceneRect(0,0,w->value(),h->value());
        view->setSceneRect(scene->sceneRect());
    };
    QObject::connect(w,qOverload<int>(&QSpinBox::valueChanged),&dialog,[=](int){resizeScene();});
    QObject::connect(h,qOverload<int>(&QSpinBox::valueChanged),&dialog,[=](int){resizeScene();});
    resizeScene();
    int index=0;
    for(const QString &name:worlds){
        auto *marker=scene->addRect(0,0,96,34,QPen(QColor(220,190,110)),QBrush(QColor(63,84,116)));
        marker->setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable|
                         QGraphicsItem::ItemSendsGeometryChanges);
        const QPointF point=savedPoints.contains(name)?savedPoints.value(name):
            QPointF(70+(index%4)*170,80+(index/4)*110);
        marker->setPos(point);marker->setData(0,name);
        auto *label=new QGraphicsSimpleTextItem(name.left(14),marker);
        label->setBrush(QColor(Qt::white));label->setPos(6,8);
        markers.insert(name,marker);++index;
    }
    auto *buttons=new QDialogButtonBox(QDialogButtonBox::Save|QDialogButtonBox::Cancel,&dialog);
    root->addWidget(buttons);
    QObject::connect(buttons,&QDialogButtonBox::accepted,&dialog,&QDialog::accept);
    QObject::connect(buttons,&QDialogButtonBox::rejected,&dialog,&QDialog::reject);
    dialog.showMaximized();
    if(dialog.exec()!=QDialog::Accepted)return false;
    QJsonArray points;
    for(auto it=markers.cbegin();it!=markers.cend();++it){
        const QPointF pos=it.value()->pos();
        points.append(QJsonObject{{QStringLiteral("name"),it.key()},
            {QStringLiteral("x"),qBound(0,qRound(pos.x()),w->value()-16)},
            {QStringLiteral("y"),qBound(0,qRound(pos.y()),h->value()-16)}});
    }
    return cgRpgWrite(path,QJsonObject{{QStringLiteral("version"),1},
        {QStringLiteral("width"),w->value()},{QStringLiteral("height"),h->value()},
        {QStringLiteral("points"),points}},error);
}
#endif
