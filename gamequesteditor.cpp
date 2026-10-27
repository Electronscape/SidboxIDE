#include "gamequesteditor.h"
#include "gamequestjournaleditor.h"
#include "gamequestgen.h"
#include <QComboBox>
#include <QCheckBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFileInfo>
#include <QUuid>
#include <QMap>
#include <QVector>
#include <QSet>
#include <QAbstractItemView>
#include <QDir>
#include <QFile>
#include <QFormLayout>
#include <QFrame>
#include <QTreeWidget>
#include <QIcon>
#include <QPointer>
#include <QHash>
#include <QKeyEvent>
#include <QScreen>
#include <QGuiApplication>
#include <functional>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QSaveFile>
#include <QStandardItemModel>
#include <QSplitter>
#include <QSignalBlocker>
#include <QTableWidget>
#include <QHeaderView>
#include <QTextEdit>
#include <QUuid>
#include <QVBoxLayout>

namespace {
QString newId(const QString &prefix) {
    return prefix + QUuid::createUuid().toString(QUuid::WithoutBraces).remove(QLatin1Char('-')).left(12);
}
QString savePath(const QString &projectRoot) {
    return QDir(projectRoot).filePath(QStringLiteral(".codergirl/quests.json"));
}
/* Same folder-based dialogue navigation as the Adventure Node editor,
 * with a leaf for every answer. The stored value remains the stable choice ID
 * (or legacy numeric event), not its display location. */
class QuestDialogueTreeCombo final : public QComboBox {
public:
    explicit QuestDialogueTreeCombo(QWidget *parent):QComboBox(parent) {}
    void setDialogueTree(const QJsonArray &nodes,const QJsonArray &folders) {
        m_nodes=nodes; m_folders=folders;
    }
    void setAnswerLocation(int item,int node,int choice) {
        setItemData(item,node,Qt::UserRole+1);
        setItemData(item,choice,Qt::UserRole+2);
    }
    void showPopup() override {
        if(m_popup){m_popup->raise();m_popup->activateWindow();return;}
        if(m_nodes.isEmpty()){QComboBox::showPopup();return;}
        auto *popup=new QFrame(this,Qt::Popup);
        popup->setObjectName(QStringLiteral("questDialogueTreePopup"));
        popup->setAttribute(Qt::WA_DeleteOnClose);
        m_popup=popup;
        auto *layout=new QVBoxLayout(popup);
        layout->setContentsMargins(5,5,5,5);
        auto *search=new QLineEdit(popup);
        search->setPlaceholderText(tr("Search dialogue folders, speakers, answers..."));
        search->setClearButtonEnabled(true);
        layout->addWidget(search);
        auto *tree=new QTreeWidget(popup);
        tree->setHeaderHidden(true);
        tree->setUniformRowHeights(true);
        layout->addWidget(tree,1);
        QHash<QString,QTreeWidgetItem*> folderNodes;
        QSet<QString> visited;
        for(int pass=0;pass<=m_folders.size();++pass) {
            for(const auto &value:m_folders) {
                const QJsonObject folder=value.toObject();
                const QString id=folder.value(QStringLiteral("id")).toString();
                const QString parent=folder.value(QStringLiteral("parentId")).toString();
                if(id.isEmpty() || visited.contains(id))continue;
                if(!parent.isEmpty() && !folderNodes.contains(parent) && pass<m_folders.size())continue;
                QTreeWidgetItem *parentItem=folderNodes.value(parent,nullptr);
                auto *item=parentItem?new QTreeWidgetItem(parentItem):new QTreeWidgetItem(tree);
                item->setText(0,folder.value(QStringLiteral("name")).toString(tr("Unnamed folder")));
                item->setIcon(0,QIcon::fromTheme(QStringLiteral("folder")));
                folderNodes.insert(id,item);visited.insert(id);
            }
        }
        auto *unfiled=new QTreeWidgetItem(tree);
        unfiled->setText(0,tr("Unfiled dialogues"));
        unfiled->setIcon(0,QIcon::fromTheme(QStringLiteral("folder-open")));
        QHash<int,QTreeWidgetItem*> nodeItems;
        QTreeWidgetItem *highlight=nullptr;
        for(int row=1;row<count();++row) {
            const int ni=itemData(row,Qt::UserRole+1).toInt();
            if(ni<0 || ni>=m_nodes.size())continue;
            QTreeWidgetItem *nodeItem=nodeItems.value(ni,nullptr);
            if(!nodeItem) {
                const QJsonObject node=m_nodes.at(ni).toObject();
                auto *parent=folderNodes.value(node.value(QStringLiteral("folderId")).toString(),unfiled);
                nodeItem=new QTreeWidgetItem(parent);
                nodeItem->setText(0,tr("%1: %2 — %3").arg(ni)
                    .arg(node.value(QStringLiteral("speaker")).toString().left(30),
                         node.value(QStringLiteral("text")).toString().simplified().left(48)));
                nodeItems.insert(ni,nodeItem);
            }
            auto *item=new QTreeWidgetItem(nodeItem);
            item->setText(0,itemText(row));
            item->setData(0,Qt::UserRole,row);
            if(!model()->index(row,modelColumn()).flags().testFlag(Qt::ItemIsEnabled))
                item->setDisabled(true);
            if(row==currentIndex())highlight=item;
        }
        if(unfiled->childCount()==0)delete unfiled;
        tree->collapseAll();
        if(highlight){
            for(QTreeWidgetItem *parent=highlight->parent();parent;parent=parent->parent())
                parent->setExpanded(true);
            tree->setCurrentItem(highlight);
            tree->scrollToItem(highlight);
        }
        auto pick=[this,popup](QTreeWidgetItem *item) {
            if(!item || item->isDisabled() || !item->data(0,Qt::UserRole).isValid())return;
            const int row=item->data(0,Qt::UserRole).toInt();
            if(row>0 && row<count()){setCurrentIndex(row);popup->close();}
        };
        connect(tree,&QTreeWidget::itemClicked,popup,[pick](QTreeWidgetItem *i,int){pick(i);});
        connect(tree,&QTreeWidget::itemActivated,popup,[pick](QTreeWidgetItem *i,int){pick(i);});
        connect(tree,&QTreeWidget::itemDoubleClicked,popup,[pick](QTreeWidgetItem *i,int){pick(i);});
        connect(search,&QLineEdit::textChanged,popup,[tree](const QString &query){
            const auto filter=[&](auto &&self,QTreeWidgetItem *item)->bool {
                bool childMatch=false;
                for(int i=0;i<item->childCount();++i)
                    if(self(self,item->child(i)))childMatch=true;
                const bool match=query.isEmpty() || item->text(0).contains(query,Qt::CaseInsensitive);
                item->setHidden(!match && !childMatch);
                if(childMatch && !query.isEmpty())item->setExpanded(true);
                return match || childMatch;
            };
            for(int i=0;i<tree->topLevelItemCount();++i)
                filter(filter,tree->topLevelItem(i));
        });
        popup->resize(qMax(440,width()),420);
        QPoint location=mapToGlobal(QPoint(0,height()));
        if(QScreen *screen=window()->screen()) {
            const QRect screenRect=screen->availableGeometry();
            if(location.x()+popup->width()>screenRect.right())
                location.setX(screenRect.right()-popup->width());
            if(location.y()+popup->height()>screenRect.bottom())
                location.setY(mapToGlobal(QPoint(0,0)).y()-popup->height());
        }
        popup->move(location);
        popup->show();
        search->setFocus();
    }
private:
    QJsonArray m_nodes,m_folders;
    QPointer<QFrame> m_popup;
};

class QuestEditor final : public QDialog {
public:
    explicit QuestEditor(const QString &projectRoot, QWidget *parent,
                         const QString &selectQuestId)
        : QDialog(parent), path(savePath(projectRoot)) {
        readProjectTargets(projectRoot);
        setWindowTitle(tr("Quest Designer | Project-wide"));
        resize(1000, 640);
        auto *root = new QVBoxLayout(this);
        root->addWidget(new QLabel(tr("Quests work across every world. Track one quest while all active quests progress. "
                                     "Keep IDs stable once players have saved games.")));
        auto *split = new QSplitter(this);
        root->addWidget(split,1);
        auto *left = new QWidget(split);
        auto *lv = new QVBoxLayout(left);
        lv->addWidget(new QLabel(tr("QUEST LINES")));
        questList = new QListWidget(left);
        lv->addWidget(questList,1);
        auto *questActions = new QHBoxLayout;
        auto *addQuest = new QPushButton(tr("Add Quest"), left);
        auto *delQuest = new QPushButton(tr("Remove"), left);
        questActions->addWidget(addQuest); questActions->addWidget(delQuest);
        lv->addLayout(questActions);
        auto *right = new QWidget(split);
        auto *rv = new QVBoxLayout(right);
        auto *form = new QFormLayout;
        questId = new QLineEdit(right); questId->setReadOnly(true);
        title = new QLineEdit(right);
        description = new QLineEdit(right);
        requires = new QComboBox(right);
        excludes = new QComboBox(right);
        initiallyHidden = new QCheckBox(tr("Hide until dialogue enables this quest"),right);
        form->addRow(tr("Stable quest ID"),questId);
        form->addRow(tr("Title"),title);
        form->addRow(tr("Journal description"),description);
        form->addRow(tr("Unlock when quest completed"),requires);
        form->addRow(tr("Lock if quest completed"),excludes);
        form->addRow(tr("Quest discovery"),initiallyHidden);
        rv->addLayout(form);
        rv->addWidget(new QLabel(tr("OBJECTIVES (in order, one active step per quest)")));
        objectives = new QTableWidget(right);
        objectives->setColumnCount(5);
        objectives->setHorizontalHeaderLabels({tr("Journal objective"), tr("Condition"),
            tr("World / item / signal"), tr("Dialogue action / event ID"), tr("Hint text")});
        objectives->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        objectives->setSelectionBehavior(QAbstractItemView::SelectRows);
        objectives->setSelectionMode(QAbstractItemView::SingleSelection);
        rv->addWidget(objectives,1);
        auto *objectiveActions = new QHBoxLayout;
        auto *addObjective = new QPushButton(tr("Add Objective"),right);
        auto *delObjective = new QPushButton(tr("Remove Objective"),right);
        auto *moveUp = new QPushButton(tr("Move Up"),right);
        auto *moveDown = new QPushButton(tr("Move Down"),right);
        for (auto *b : {addObjective,delObjective,moveUp,moveDown}) objectiveActions->addWidget(b);
        rv->addLayout(objectiveActions);
        auto *info = new QLabel(tr("For a dialogue objective, choose Dialogue answer (automatic ID), a world, and an answer. "
                                   "No Custom C event ID is needed. Existing numeric Adventure events remain supported for scripts. "
                                   "World entry and inventory objectives also advance automatically."),right);
        info->setWordWrap(true); rv->addWidget(info);
        auto *buttons = new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Cancel,this);
        auto *journalDesign=new QPushButton(tr("Journal Appearance..."),this);
        journalDesign->setToolTip(tr("Design the in-game Quest Journal: colours, dialogue skin and HUD-safe layout."));
        connect(journalDesign,&QPushButton::clicked,this,[this,projectRoot] {
            QString error;
            if(!editGameQuestJournal(this,projectRoot,&error) && !error.isEmpty())
                QMessageBox::warning(this,tr("Quest Journal Designer"),error);
        });
        auto *bottomActions=new QHBoxLayout;
        bottomActions->addWidget(journalDesign);
        bottomActions->addStretch(1);
        bottomActions->addWidget(buttons);
        root->addLayout(bottomActions);
        split->setStretchFactor(0,1); split->setStretchFactor(1,3);
        QFile f(path);
        if (f.exists()) {
            if (!f.open(QIODevice::ReadOnly)) { loadError = tr("Cannot read %1").arg(path); return; }
            QJsonParseError e;
            const QJsonDocument doc=QJsonDocument::fromJson(f.readAll(),&e);
            if (e.error!=QJsonParseError::NoError || !doc.isObject() ||
                doc.object().value("version").toInt()!=1 ||
                !doc.object().value("quests").isArray()) {
                loadError=tr("Quest file is invalid: %1").arg(path); return;
            }
            quests=doc.object().value("quests").toArray();
        }
        refreshList();
        connect(questList,&QListWidget::currentRowChanged,this,[this](int row) {
            flushQuest(); selected=row; refreshDetails();
        });
        connect(addQuest,&QPushButton::clicked,this,[this] {
            flushQuest();
            if (quests.size()>=64) { QMessageBox::warning(this,tr("Quest limit"),tr("Maximum 64 quests.")); return; }
            QJsonObject q; q["id"]=newId("quest_"); q["title"]=tr("New Quest");
            q["description"]=QString();q["requires"]=QString();q["excludes"]=QString();q["initiallyHidden"]=false;
            q["objectives"]=QJsonArray{}; quests.append(q);
            refreshList();questList->setCurrentRow(quests.size()-1);
        });
        connect(delQuest,&QPushButton::clicked,this,[this] {
            const int index=questList->currentRow(); if (index<0) return;
            if (QMessageBox::question(this,tr("Remove Quest"),tr("Remove this quest and its objectives?"))!=QMessageBox::Yes) return;
            flushQuest(); quests.removeAt(index); selected=-1;
            refreshList();questList->setCurrentRow(qMin(index,quests.size()-1));
        });
        connect(addObjective,&QPushButton::clicked,this,[this] {
            if (selected<0) return;
            flushQuest();
            QJsonObject q=quests.at(selected).toObject();
            QJsonArray arr=q.value("objectives").toArray();
            int total=0;for (const auto &v:quests) total+=v.toObject().value("objectives").toArray().size();
            if (total>=256) { QMessageBox::warning(this,tr("Objective limit"),tr("Maximum 256 objectives.")); return; }
            arr.append(QJsonObject{{"id",newId("obj_")},{"title",tr("New objective")},
                                   {"kind","event"},{"target",newId("event_")},{"hint",QString()}});
            q["objectives"]=arr; quests.replace(selected,q); refreshDetails();
        });
        connect(delObjective,&QPushButton::clicked,this,[this] {
            if (selected<0 || objectives->currentRow()<0) return;
            const int row=objectives->currentRow();flushQuest();
            QJsonObject q=quests.at(selected).toObject();QJsonArray a=q.value("objectives").toArray();
            if(row<a.size())a.removeAt(row);q["objectives"]=a;quests.replace(selected,q);refreshDetails();
        });
        auto moveObjective=[this](int delta) {
            if (selected<0) return;
            const int row=objectives->currentRow();flushQuest();
            QJsonObject q=quests.at(selected).toObject();QJsonArray a=q.value("objectives").toArray();
            const int to=row+delta;
            if(row<0 || to<0 || to>=a.size())return;
            const QJsonValue v=a.at(row);a.replace(row,a.at(to));a.replace(to,v);
            q["objectives"]=a;quests.replace(selected,q);refreshDetails();objectives->selectRow(to);
        };
        connect(moveUp,&QPushButton::clicked,this,[moveObjective]{moveObjective(-1);});
        connect(moveDown,&QPushButton::clicked,this,[moveObjective]{moveObjective(1);});
        connect(buttons,&QDialogButtonBox::rejected,this,&QDialog::reject);
        connect(buttons,&QDialogButtonBox::accepted,this,[this] {
            flushQuest();
            QString why;
            if (!validate(&why) || !GameQuestGen::validate(quests,&why)) {
                QMessageBox::warning(this,tr("Quest validation"),why);return;
            }
            // Assign IDs in saved .sbgm worlds only when Save is confirmed.
            // Never overwrite another process/editor's newly saved version.
            for(const PendingWorld &world:pendingWorlds) {
                QFile current(world.filePath);
                if(!current.open(QIODevice::ReadOnly) || current.readAll()!=world.original) {
                    QMessageBox::warning(this,tr("Quest Designer"),
                        tr("World %1 changed while the Quest Designer was open. Save and reopen your worlds, then retry.")
                          .arg(world.filePath));return;
                }
            }
            for(const PendingWorld &world:pendingWorlds) {
                QSaveFile upgraded(world.filePath);
                if(!upgraded.open(QIODevice::WriteOnly) ||
                   upgraded.write(world.updated)!=world.updated.size() || !upgraded.commit()) {
                    upgraded.cancelWriting();
                    QMessageBox::warning(this,tr("Quest Designer"),tr("Could not assign stable dialogue IDs in %1").arg(world.filePath));return;
                }
            }
            QDir().mkpath(QFileInfo(path).absolutePath());
            QSaveFile file(path);
            const QByteArray bytes=QJsonDocument(QJsonObject{{"version",1},{"quests",quests}}).toJson(QJsonDocument::Indented);
            if (!file.open(QIODevice::WriteOnly) || file.write(bytes)!=bytes.size() || !file.commit()) {
                QMessageBox::warning(this,tr("Quest Designer"),tr("Could not save %1").arg(path));return;
            }
            accept();
        });
        if (!quests.isEmpty()) {
            int first=0;
            if(!selectQuestId.isEmpty()){
                for(int i=0;i<quests.size();++i)
                    if(quests.at(i).toObject().value(QStringLiteral("id")).toString()==selectQuestId)
                        {first=i;break;}
            }
            questList->setCurrentRow(first);
        }
    }
    QString loadError;
private:
    QString path;
    QJsonArray quests;
    int selected=-1;
    QListWidget *questList=nullptr;
    QLineEdit *questId=nullptr,*title=nullptr,*description=nullptr;
    QComboBox *requires=nullptr,*excludes=nullptr;
    QCheckBox *initiallyHidden=nullptr;
    QTableWidget *objectives=nullptr;
    struct DialogueAction { int id, node, choice; QString stableId,label; };
    struct PendingWorld { QString filePath; QByteArray original; QByteArray updated; };
    QVector<PendingWorld> pendingWorlds;
    QMap<QString,QVector<DialogueAction>> actionsByWorld;
    QMap<QString,QJsonArray> dialogueNodesByWorld,dialogueFoldersByWorld;
    QStringList worldNames, itemNames;

    // The quest runtime stores adventure event targets as "world:eventNumber".
    // Populate the UI from actual authored dialogue choices, never invented IDs.
    void readProjectTargets(const QString &projectRoot) {
        const QDir dir(projectRoot);
        for(const QString &fileName:dir.entryList({QStringLiteral("*.sbgm")},QDir::Files,QDir::Name)) {
            const QString world=QFileInfo(fileName).completeBaseName();
            QFile file(dir.filePath(fileName));
            if(!file.open(QIODevice::ReadOnly))continue;
            const QByteArray original=file.readAll();
            const auto doc=QJsonDocument::fromJson(original);
            if(!doc.isObject())continue;
            worldNames.append(world);
            QJsonObject updatedRoot=doc.object();
            QJsonObject adv=updatedRoot.value(QStringLiteral("adventure")).toObject();
            for(const auto &item:adv.value(QStringLiteral("items")).toArray()) {
                const QString name=item.toObject().value(QStringLiteral("name")).toString().trimmed();
                if(!name.isEmpty() && !itemNames.contains(name))itemNames.append(name);
            }
            QJsonArray nodes=adv.value(QStringLiteral("nodes")).toArray();
            dialogueNodesByWorld.insert(world,nodes);
            dialogueFoldersByWorld.insert(world,adv.value(QStringLiteral("dialogueFolders")).toArray());
            bool changed=false;
            QSet<QString> usedChoiceIds;
            for(const QJsonValue &nv:nodes)
                for(const QJsonValue &cv:nv.toObject().value(QStringLiteral("choices")).toArray()) {
                    const QString id=cv.toObject().value(QStringLiteral("questChoiceId")).toString();
                    if(!id.isEmpty())usedChoiceIds.insert(id);
                }
            for(int nodeIndex=0;nodeIndex<nodes.size();++nodeIndex) {
                QJsonObject node=nodes.at(nodeIndex).toObject();
                QJsonArray choices=node.value(QStringLiteral("choices")).toArray();
                const QString speaker=node.value(QStringLiteral("speaker")).toString().trimmed();
                for(int choiceIndex=0;choiceIndex<choices.size();++choiceIndex) {
                    QJsonObject choice=choices.at(choiceIndex).toObject();
                    const int event=choice.value(QStringLiteral("action")).toInt(-1);
                    const QString reply=choice.value(QStringLiteral("text")).toString().simplified();
                    // Blank dialogue answers are ignored by generated gameplay.
                    // Only genuine configured numeric actions can fire quest events.
                    if(reply.isEmpty())continue;
                    QString stableId=choice.value(QStringLiteral("questChoiceId")).toString();
                    if(stableId.isEmpty()) {
                        do {stableId=newId(QStringLiteral("dlg_"));} while(usedChoiceIds.contains(stableId));
                        usedChoiceIds.insert(stableId);
                        choice.insert(QStringLiteral("questChoiceId"),stableId);
                        choices.replace(choiceIndex,choice);changed=true;
                    }
                    const bool objectAction=!choice.value(QStringLiteral("targetObjectId")).toString().isEmpty();
                    const QString name=speaker.isEmpty()?tr("Dialogue %1").arg(nodeIndex)
                                        :QStringLiteral("%1 [dialogue %2]").arg(speaker).arg(nodeIndex);
                    const QString label=event>=0 && !objectAction
                        ? tr("%1 → %2  (event %3)").arg(name,reply.left(70)).arg(event)
                        : tr("%1 → %2  [no Custom C event ID]").arg(name,reply.left(70));
                    actionsByWorld[world].append({(objectAction?-1:event),nodeIndex,choiceIndex,stableId,label});
                }
                if(changed){node.insert(QStringLiteral("choices"),choices);nodes.replace(nodeIndex,node);}
            }
            if(changed) {
                adv.insert(QStringLiteral("nodes"),nodes);
                updatedRoot.insert(QStringLiteral("adventure"),adv);
                pendingWorlds.append({dir.filePath(fileName),original,
                    QJsonDocument(updatedRoot).toJson(QJsonDocument::Indented)});
            }
        }
        itemNames.sort(Qt::CaseInsensitive);
    }

    // Column 2 is always a combo, editable only for custom signal targets.
    // Column 3 is the actual configured dialogue action, not an arbitrary ID.
    void configureTarget(int row,const QString &kind,const QString &savedTarget) {
        auto *target=new QComboBox(objectives);
        target->setProperty("questKind",kind);
        target->setEditable(kind==QStringLiteral("event"));
        if(kind==QStringLiteral("world") || kind==QStringLiteral("adventure_event") ||
           kind==QStringLiteral("dialogue_choice")) {
            target->addItem(tr("Select world..."),QString());
            for(const QString &world:worldNames)target->addItem(world,world);
        } else if(kind==QStringLiteral("item")) {
            target->addItem(tr("Select inventory item..."),QString());
            for(const QString &item:itemNames)target->addItem(item,item);
        } else {
            target->setInsertPolicy(QComboBox::NoInsert);
            target->setEditText(savedTarget);
        }
        const QString world=(kind==QStringLiteral("adventure_event") || kind==QStringLiteral("dialogue_choice"))
            ? savedTarget.section(QLatin1Char(':'),0,0) : savedTarget;
        if(!target->isEditable() && !world.isEmpty() && target->findData(world)<0)
            target->addItem(tr("Missing: %1").arg(world),world);
        if(!target->isEditable())target->setCurrentIndex(qMax(0,target->findData(world)));
        objectives->setCellWidget(row,2,target);
        auto *event=new QuestDialogueTreeCombo(objectives);
        if(kind==QStringLiteral("adventure_event") || kind==QStringLiteral("dialogue_choice")) {
            const QString eventText=savedTarget.section(QLatin1Char(':'),1);
            updateDialogueChoices(event,world,eventText,kind==QStringLiteral("dialogue_choice"));
            QObject::connect(target,QOverload<int>::of(&QComboBox::currentIndexChanged),
                             objectives,[this,target,event](int){
                updateDialogueChoices(event,target->currentData().toString(),QString(),
                                      target->property("questKind").toString()==QStringLiteral("dialogue_choice"));
            });
        } else {
            event->addItem(tr("Not used"),QString());
            event->setEnabled(false);
        }
        objectives->setCellWidget(row,3,event);
    }

    void updateDialogueChoices(QuestDialogueTreeCombo *combo,const QString &world,const QString &savedId,
                               bool automatic) {
        QSignalBlocker block(combo);
        combo->clear();
        combo->addItem(automatic ? tr("Select dialogue answer...")
                                 : tr("Select a configured dialogue event..."),QString());
        combo->setDialogueTree(dialogueNodesByWorld.value(world),
                               dialogueFoldersByWorld.value(world));
        for(const DialogueAction &action:actionsByWorld.value(world)) {
            const QString value=automatic?action.stableId
                                         :(action.id<0?QString():QString::number(action.id));
            combo->addItem(automatic ? action.label.section(QStringLiteral("  ["),0,0) : action.label,value);
            combo->setAnswerLocation(combo->count()-1,action.node,action.choice);
            if(!automatic && action.id<0) {
                // Show unconfigured answers for discoverability, but never let
                // them silently create an objective that cannot be completed.
                if(auto *model=qobject_cast<QStandardItemModel *>(combo->model()))
                    if(auto *item=model->item(combo->count()-1)) {
                        item->setEnabled(false);
                        item->setToolTip(tr("Open this answer in Adventure Designer and choose "
                                             "Event / resource → Custom C event ID."));
                    }
            }
        }
        if(!savedId.isEmpty() && combo->findData(savedId)<0)
            combo->addItem(automatic ? tr("Missing dialogue ID %1").arg(savedId)
                                     : tr("Event %1 (not found in saved dialogue actions)").arg(savedId),savedId);
        combo->setCurrentIndex(qMax(0,combo->findData(savedId)));
        bool hasConfigured=false;
        for(const DialogueAction &action:actionsByWorld.value(world))
            if(action.id>=0){hasConfigured=true;break;}
        if(!automatic && !hasConfigured && savedId.isEmpty()) {
            combo->setItemText(0,actionsByWorld.value(world).isEmpty()
                ? tr("No dialogue answers in this world")
                : tr("Grey answers need a Custom C event ID"));
            combo->setToolTip(tr("In Adventure Designer, select an answer and set "
                                 "Event / resource → Custom C event ID."));
        } else {
            combo->setToolTip(automatic ? tr("Each answer has an automatically assigned stable ID. Custom C events are optional.")
                                        : tr("The number comes from the Custom C event ID on a dialogue answer."));
        }
    }

    void refreshList() {
        QSignalBlocker block(questList);questList->clear();
        for (const auto &v:quests) questList->addItem(v.toObject().value("title").toString());
    }
    void refreshDetails() {
        const bool valid=selected>=0 && selected<quests.size();
        title->setEnabled(valid);description->setEnabled(valid);
        requires->setEnabled(valid);excludes->setEnabled(valid);initiallyHidden->setEnabled(valid);objectives->setEnabled(valid);
        QSignalBlocker b1(objectives),b2(requires),b3(excludes);
        questId->clear(); title->clear();description->clear();initiallyHidden->setChecked(false);objectives->setRowCount(0);
        requires->clear();excludes->clear();
        requires->addItem(tr("None"),QString()); excludes->addItem(tr("None"),QString());
        for(int i=0;i<quests.size();++i) if(i!=selected) {
            const QJsonObject q=quests.at(i).toObject();
            requires->addItem(q.value("title").toString(),q.value("id").toString());
            excludes->addItem(q.value("title").toString(),q.value("id").toString());
        }
        if (!valid) return;
        const QJsonObject q=quests.at(selected).toObject();
        questId->setText(q.value("id").toString());title->setText(q.value("title").toString());
        description->setText(q.value("description").toString());
        initiallyHidden->setChecked(q.value("initiallyHidden").toBool(false));
        requires->setCurrentIndex(qMax(0,requires->findData(q.value("requires").toString())));
        excludes->setCurrentIndex(qMax(0,excludes->findData(q.value("excludes").toString())));
        const QJsonArray a=q.value("objectives").toArray(); objectives->setRowCount(a.size());
        for(int i=0;i<a.size();++i) {
            const QJsonObject o=a.at(i).toObject();
            objectives->setItem(i,0,new QTableWidgetItem(o.value("title").toString()));
            auto *kind=new QComboBox(objectives);
            kind->addItem(tr("Enter world"),QStringLiteral("world"));
            kind->addItem(tr("Own inventory item"),QStringLiteral("item"));
            kind->addItem(tr("Event signal"),QStringLiteral("event"));
            kind->addItem(tr("Dialogue answer (automatic ID)"),QStringLiteral("dialogue_choice"));
            kind->addItem(tr("Adventure event ID (legacy)"),QStringLiteral("adventure_event"));
            kind->setCurrentIndex(qMax(0,kind->findData(o.value("kind").toString())));
            objectives->setCellWidget(i,1,kind);
            configureTarget(i,o.value("kind").toString(),o.value("target").toString());
            objectives->setItem(i,4,new QTableWidgetItem(o.value("hint").toString()));
            connect(kind,QOverload<int>::of(&QComboBox::currentIndexChanged),objectives,
                    [this,i,kind](int) {
                // Switching condition types must not reuse a stale target of
                // a different type (e.g. 'forest:42' as an inventory item).
                configureTarget(i,kind->currentData().toString(),QString());
            });
        }
    }
    void flushQuest() {
        if(selected<0 || selected>=quests.size())return;
        QJsonObject q=quests.at(selected).toObject();
        q["title"]=title->text().trimmed();q["description"]=description->text().trimmed();
        q["requires"]=requires->currentData().toString();q["excludes"]=excludes->currentData().toString();
        q["initiallyHidden"]=initiallyHidden->isChecked();
        QJsonArray old=q.value("objectives").toArray(),next;
        for(int i=0;i<objectives->rowCount();++i) {
            QJsonObject o=i<old.size()?old.at(i).toObject():QJsonObject{};
            o["title"]=objectives->item(i,0)?objectives->item(i,0)->text().trimmed():QString();
            auto *kind=qobject_cast<QComboBox *>(objectives->cellWidget(i,1));
            o["kind"]=kind?kind->currentData().toString():QStringLiteral("event");
            auto *target=qobject_cast<QComboBox *>(objectives->cellWidget(i,2));
            auto *event=qobject_cast<QComboBox *>(objectives->cellWidget(i,3));
            const QString kindName=o.value("kind").toString();
            const QString targetValue=target?(target->isEditable()?target->currentText().trimmed()
                                                  :target->currentData().toString()):QString();
            const QString eventValue=event?event->currentData().toString():QString();
            o["target"]=(kindName==QStringLiteral("adventure_event") || kindName==QStringLiteral("dialogue_choice"))
                ? ((!targetValue.isEmpty() && !eventValue.isEmpty())
                    ? targetValue+QLatin1Char(':')+eventValue : QString()) : targetValue;
            o["hint"]=objectives->item(i,4)?objectives->item(i,4)->text().trimmed():QString();
            next.append(o);
        }
        q["objectives"]=next;quests.replace(selected,q);
        if (auto *item=questList->item(selected))item->setText(q.value("title").toString());
    }
    bool validate(QString *why) {
        QSet<QString> ids;
        for(const auto &v:quests) {
            const QJsonObject q=v.toObject();const QString id=q.value("id").toString();
            if(id.isEmpty() || ids.contains(id) || q.value("title").toString().isEmpty()) {
                *why=tr("Every quest needs a unique ID and nonempty title.");return false;
            }
            ids.insert(id);
        }
        int count=0; QSet<QString> objectiveIds;
        for(const auto &v:quests) {
            const QJsonObject q=v.toObject();
            for(const char *field:{"requires","excludes"}) {
                const QString ref=q.value(field).toString();
                if(!ref.isEmpty() && (!ids.contains(ref)||ref==q.value("id").toString())) {
                    *why=tr("Quest '%1' has an invalid %2 reference.").arg(q.value("title").toString(),QLatin1String(field));return false;
                }
            }
            const QJsonArray arr=q.value("objectives").toArray();
            if(arr.isEmpty()) { *why=tr("Quest '%1' needs at least one objective.").arg(q.value("title").toString());return false; }
            for(const auto &iv:arr) {
                const QJsonObject o=iv.toObject();++count;
                const QString id=o.value("id").toString(),target=o.value("target").toString();
                if(id.isEmpty()||objectiveIds.contains(id)||target.isEmpty()||o.value("title").toString().isEmpty()) {
                    *why=tr("Objective in '%1' needs unique ID, title and target.").arg(q.value("title").toString());return false;
                }
                objectiveIds.insert(id);
            }
        }
        if(count>256){*why=tr("Maximum 256 objectives in the game.");return false;}
        // A prerequisite cycle would produce permanently locked quests.
        for(const auto &v:quests) {
            QSet<QString> chain;QString id=v.toObject().value("id").toString();
            while(!id.isEmpty()) {
                if(chain.contains(id)){*why=tr("Quest prerequisites contain a cycle.");return false;}
                chain.insert(id);QString next;
                for(const auto &x:quests)if(x.toObject().value("id").toString()==id)
                    next=x.toObject().value("requires").toString();
                id=next;
            }
        }
        return true;
    }
};
}
bool editGameQuests(QWidget *parent, const QString &projectRoot, QString *error,
                    const QString &selectQuestId)
{
    QuestEditor dialog(projectRoot,parent,selectQuestId);
    if(!dialog.loadError.isEmpty()) {if(error)*error=dialog.loadError;return false;}
    // Open at the user's available desktop size, not a cramped fixed dialog.
    dialog.setWindowState(dialog.windowState() | Qt::WindowMaximized);
    return dialog.exec()==QDialog::Accepted;
}
