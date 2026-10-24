#include "gamefloweditor.h"
#include "idetheme.h"
#include "ppbcodec.h"
#include "gamespritestamp.h"

#include <QCheckBox>
#include <QComboBox>
#include <QDialog>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFont>
#include <QGraphicsPathItem>
#include <QGraphicsTextItem>
#include <QPainterPathStroker>
#include <QLinearGradient>
#include <QFocusEvent>
#include <QKeyEvent>
#include <QTextCursor>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPolygonItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsView>
#include <QPainter>
#include <QImage>
#include <QSignalBlocker>
#include <QHash>
#include <QHBoxLayout>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMouseEvent>
#include <QSaveFile>
#include <QWheelEvent>
#include <QLabel>
#include <QLineEdit>
#include <QInputDialog>
#include <QShortcut>
#include <QRegularExpression>
#include <QMessageBox>
#include <QPainterPath>
#include <QPixmap>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QScrollBar>
#include <QSet>
#include <QSplitter>
#include <QVBoxLayout>
#include <algorithm>
#include <cmath>
#include <functional>

namespace {

struct FlowNode {
    QString id, world, kind, title, description;
    int column = 0;
    bool problem = false;
    // Original game-art reference for design-only card thumbnails.
    // Never writes pixels, changes CLUT indices, or creates another PPB.
    QString artPath;
    QJsonObject artStamp;
    QJsonArray artCells;
    int artFrame = 0, artWidth = 8, artHeight = 8;
    bool art2x2 = false;
};
struct FlowGroup {
    QString id, world, title;
    QStringList members;
    bool expanded = false;
    bool automatic = false;
};
struct FlowLayout {
    QHash<QString,QPointF> positions;
    QVector<FlowGroup> manualGroups;
    QHash<QString,bool> expanded;
    // Positions are LOCAL to a manual group so moving its frame preserves its wiring.
    QHash<QString,QHash<QString,QPointF>> memberPositions;
    // Array-group ID -> containing manual group ID (one nesting level).
    QHash<QString,QString> embeddedArrays;
    bool snapToGrid = true;
};
struct FlowEdge {
    QString from, to, label;
};
struct FlowGraph {
    QVector<FlowNode> nodes;
    QVector<FlowEdge> edges;
    QHash<QString,int> byId;
    QStringList worlds;
    QStringList diagnostics;

    void addNode(const QString &id, const QString &world, const QString &kind,
                 const QString &title, const QString &description, int col, bool problem = false) {
        if (byId.contains(id)) return;
        byId.insert(id, nodes.size());
        nodes.append({id,world,kind,title,description,col,problem});
    }
    void link(const QString &from, const QString &to, const QString &description) {
        if (byId.contains(from) && byId.contains(to)) edges.append({from,to,description});
    }
    void missing(const QString &world, const QString &from, const QString &what,
                 const QString &target) {
        const QString id = world + QStringLiteral("/missing/") + what + QStringLiteral("/") + target;
        const QString message = QStringLiteral("%1: missing %2 '%3'").arg(world,what,target);
        addNode(id,world,QStringLiteral("Broken reference"),
                QStringLiteral("Missing: ") + target,message,5,true);
        link(from,id,QStringLiteral("UNRESOLVED: ") + what);
        if (!diagnostics.contains(message)) diagnostics.append(message);
    }
};

QString objectKey(const QString &world, const QString &id) {
    return world + QStringLiteral("/object/") + id;
}
QString spawnKey(const QString &world, const QString &id) {
    return world + QStringLiteral("/start/") + id;
}
QString dialogueKey(const QString &world, int index) {
    return world + QStringLiteral("/dialogue/") + QString::number(index);
}
QString itemKey(const QString &world, int index) {
    return world + QStringLiteral("/item/") + QString::number(index);
}
QString splineKey(const QString &world, const QString &id) {
    return world + QStringLiteral("/spline/") + id;
}
QString brief(const QString &value, int length = 76) {
    const QString compact = value.simplified();
    return compact.size() > length ? compact.left(length - 3) + QStringLiteral("...") : compact;
}
QString describedAction(const QJsonObject &object) {
    const QString type = object.value(QStringLiteral("type")).toString();
    if (type == QStringLiteral("goto_world")) return QStringLiteral("World exit / transition");
    if (type == QStringLiteral("collectable")) return QStringLiteral("Collectable pickup");
    if (type == QStringLiteral("trigger")) return QStringLiteral("Touch / button trigger");
    if (type == QStringLiteral("door")) return QStringLiteral("Door / toggle object");
    if (type == QStringLiteral("breakable")) return QStringLiteral("Breakable object");
    return type.isEmpty() ? QStringLiteral("Game object") : type;
}

// All relationships are derived from the saved project design, never inferred
// from generated symbol names or runtime memory addresses.
FlowGraph loadGraph(const QString &root) {
    FlowGraph g;
    struct SavedWorld { QString name; QJsonObject doc; };
    QVector<SavedWorld> documents;
    const QDir dir(root);
    const QStringList files = dir.entryList({QStringLiteral("*.sbgm")},QDir::Files,QDir::Name);
    for (const QString &name : files) {
        QFile file(dir.filePath(name));
        if (!file.open(QIODevice::ReadOnly)) {
            g.diagnostics.append(QStringLiteral("Could not read %1").arg(name));
            continue;
        }
        QJsonParseError parse;
        const QJsonDocument json = QJsonDocument::fromJson(file.readAll(), &parse);
        if (parse.error != QJsonParseError::NoError || !json.isObject()) {
            g.diagnostics.append(QStringLiteral("Invalid %1: %2").arg(name,parse.errorString()));
            continue;
        }
        const QString world = QFileInfo(name).completeBaseName();
        documents.append({world,json.object()});
        g.worlds.append(world);
        g.addNode(world+QStringLiteral("/world"),world,QStringLiteral("World"),world,
                  QStringLiteral("World design: ")+name+QStringLiteral("\nSaved file: ")+dir.filePath(name),0);
    }
    // First pass: register all nodes and stable IDs before resolving references.
    for (const auto &entry : documents) {
        const QString w = entry.name;
        const QJsonObject doc = entry.doc;
        const QString rootKey = w+QStringLiteral("/world");
        const QJsonObject start = doc.value(QStringLiteral("playerStart")).toObject();
        g.addNode(spawnKey(w,QStringLiteral("default")),w,QStringLiteral("Player Start"),
                  QStringLiteral("Default Player Start"),
                  QStringLiteral("Position: %1, %2\nFacing: %3\nIN: %4\nOUT: %5")
                      .arg(start.value("x").toInt()).arg(start.value("y").toInt())
                      .arg(start.value("facing").toInt() ? QStringLiteral("right") : QStringLiteral("left"))
                      .arg(start.value("transitionIn").toString("none"),start.value("transitionOut").toString("none")),1);
        g.link(rootKey,spawnKey(w,QStringLiteral("default")),QStringLiteral("Initial entry"));
        for (const QJsonValue &v : doc.value(QStringLiteral("playerStarts")).toArray()) {
            const QJsonObject s = v.toObject();
            const QString id = s.value(QStringLiteral("id")).toString();
            if (id.isEmpty()) continue;
            g.addNode(spawnKey(w,id),w,QStringLiteral("Player Start"),
                      s.value(QStringLiteral("name")).toString(QStringLiteral("Player Start")),
                      QStringLiteral("Position: %1, %2\nIN: %3\nOUT: %4")
                          .arg(s.value("x").toInt()).arg(s.value("y").toInt())
                          .arg(s.value("transitionIn").toString("none"),s.value("transitionOut").toString("none")),1);
            g.link(rootKey,spawnKey(w,id),QStringLiteral("Named destination"));
        }
        for (const QJsonValue &v : doc.value(QStringLiteral("splinePaths")).toArray()) {
            const QJsonObject s = v.toObject();
            const QString id = s.value(QStringLiteral("id")).toString();
            if (id.isEmpty()) continue;
            g.addNode(splineKey(w,id),w,QStringLiteral("Spline"),
                      s.value(QStringLiteral("name")).toString("Path"),
                      QStringLiteral("Spline path\n%1 nodes, %2 frames, loop: %3")
                          .arg(s.value("points").toArray().size()).arg(s.value("frames").toInt())
                          .arg(s.value("loop").toBool() ? QStringLiteral("yes") : QStringLiteral("no")),3);
        }
        const QJsonArray resources = doc.value(QStringLiteral("resources")).toArray();
        for (const QJsonValue &v : resources) {
            const QJsonObject r = v.toObject();
            const QJsonObject o = r.value(QStringLiteral("gameObject")).toObject();
            const QString type = o.value(QStringLiteral("type")).toString(QStringLiteral("decoration"));
            if (r.value(QStringLiteral("kind")).toString() != QStringLiteral("sprite") ||
                type == QStringLiteral("decoration") || type.isEmpty()) continue;
            const QString id = r.value(QStringLiteral("id")).toString();
            if (id.isEmpty()) continue;
            QString description = QStringLiteral("%1\nPosition: %2, %3\nResource ID: %4")
                                      .arg(describedAction(o)).arg(r.value("x").toInt()).arg(r.value("y").toInt()).arg(id);
            if (!o.value(QStringLiteral("gotoWorldName")).toString().isEmpty())
                description += QStringLiteral("\nDestination: ")+o.value(QStringLiteral("gotoWorldName")).toString();
            if (type == QStringLiteral("collectable"))
                description += QStringLiteral("\nInventory kind: %1\nPersistent: %2")
                                   .arg(o.value("pickupKind").toInt())
                                   .arg(o.value("pickupPersistent").toBool() ? QStringLiteral("yes") : QStringLiteral("no"));
            g.addNode(objectKey(w,id),w,describedAction(o),r.value(QStringLiteral("name")).toString(type),description,2);
            FlowNode &node=g.nodes[g.byId.value(objectKey(w,id))];
            node.artStamp=r.value(QStringLiteral("spriteStamp")).toObject();
            node.artPath=node.artStamp.value(QStringLiteral("source")).toString();
            if (node.artPath.isEmpty())node.artPath=r.value(QStringLiteral("path")).toString();
            node.artFrame=qMax(0,r.value(QStringLiteral("frame")).toInt());
            node.artWidth=qMax(1,r.value(QStringLiteral("cellWidth")).toInt(8));
            node.artHeight=qMax(1,r.value(QStringLiteral("cellHeight")).toInt(8));
        }
        const QJsonObject adv = doc.value(QStringLiteral("adventure")).toObject();
        const QJsonArray items = adv.value(QStringLiteral("items")).toArray();
        for (int i=0;i<items.size();++i) {
            const QJsonObject item=items.at(i).toObject();
            QString detail = QStringLiteral("Inventory kind: %1\nCapacity: %2\nIcon atlas ID: %3")
                                 .arg(item.value("pickupKind").toInt()).arg(item.value("capacity").toInt())
                                 .arg(item.value("iconAtlasId").toString());
            if (!item.value("useStat").toString().isEmpty())
                detail += QStringLiteral("\nUse: %1 %2%3").arg(item.value("useStat").toString())
                              .arg(item.value("useDelta").toInt()>0 ? QStringLiteral("+") : QString())
                              .arg(item.value("useDelta").toInt());
            g.addNode(itemKey(w,i),w,QStringLiteral("Inventory Item"),
                      item.value(QStringLiteral("name")).toString(QStringLiteral("Item %1").arg(i)),detail,3);
            FlowNode &node=g.nodes[g.byId.value(itemKey(w,i))];
            node.artPath=item.value(QStringLiteral("iconPpbPath")).toString();
            const QString atlasId=item.value(QStringLiteral("iconAtlasId")).toString();
            if (node.artPath.isEmpty() && !atlasId.isEmpty()) {
                for (const QJsonValue &rv:resources) {
                    const QJsonObject resource=rv.toObject();
                    if (resource.value(QStringLiteral("id")).toString()==atlasId) {
                        node.artPath=resource.value(QStringLiteral("path")).toString();
                        break;
                    }
                }
            }
            // Older inventory entries did not save an atlas: use the matching
            // collectable's actual original PPB sheet instead.
            if (node.artPath.isEmpty()) {
                const int kind=item.value(QStringLiteral("pickupKind")).toInt(-1);
                for (const QJsonValue &rv:resources) {
                    const QJsonObject resource=rv.toObject();
                    const QJsonObject object=resource.value(QStringLiteral("gameObject")).toObject();
                    if (object.value(QStringLiteral("type")).toString()==QStringLiteral("collectable") &&
                        object.value(QStringLiteral("pickupKind")).toInt(-2)==kind) {
                        node.artStamp=resource.value(QStringLiteral("spriteStamp")).toObject();
                        node.artPath=node.artStamp.value(QStringLiteral("source")).toString();
                        if (node.artPath.isEmpty())node.artPath=resource.value(QStringLiteral("path")).toString();
                        node.artFrame=resource.value(QStringLiteral("frame")).toInt();
                        node.artWidth=qMax(1,resource.value(QStringLiteral("cellWidth")).toInt(8));
                        node.artHeight=qMax(1,resource.value(QStringLiteral("cellHeight")).toInt(8));
                        break;
                    }
                }
            } else {
                node.artFrame=item.value(QStringLiteral("icon")).toInt();
                const int cell=qBound(4,item.value(QStringLiteral("iconTileSize")).toInt(8),64);
                node.artWidth=cell;node.artHeight=cell;
                node.art2x2=item.value(QStringLiteral("icon2x2")).toBool();
                node.artCells=item.value(QStringLiteral("iconCells")).toArray();
            }
        }
        const QJsonArray nodes=adv.value(QStringLiteral("nodes")).toArray();
        for (int i=0;i<nodes.size();++i) {
            const QJsonObject node=nodes.at(i).toObject();
            const QString speaker=node.value(QStringLiteral("speaker")).toString();
            g.addNode(dialogueKey(w,i),w,QStringLiteral("Dialogue"),
                      QStringLiteral("%1 [%2]").arg(speaker.isEmpty() ? QStringLiteral("Dialogue") : speaker)
                                                    .arg(i),
                      QStringLiteral("Node %1\nSpeaker: %2\n%3")
                          .arg(i).arg(speaker, node.value("text").toString()),4);
            const QJsonArray choices=node.value(QStringLiteral("choices")).toArray();
            for (int j=0;j<choices.size();++j) {
                const QJsonObject c=choices.at(j).toObject();
                if (c.value(QStringLiteral("text")).toString().trimmed().isEmpty()) continue;
                const QString choiceKey=dialogueKey(w,i)+QStringLiteral("/choice/")+QString::number(j);
                g.addNode(choiceKey,w,QStringLiteral("Dialogue Choice"),
                          brief(c.value(QStringLiteral("text")).toString(),43),
                          QStringLiteral("Choice %1 in dialogue node %2\n%3\nReply: %4")
                              .arg(j+1).arg(i).arg(c.value("text").toString(),c.value("reply").toString()),5);
            }
        }
        const QJsonArray npcs=adv.value(QStringLiteral("npcs")).toArray();
        for (int i=0;i<npcs.size();++i) {
            const QJsonObject npc=npcs.at(i).toObject();
            const QString spriteId=npc.value(QStringLiteral("spriteId")).toString();
            QString title=QStringLiteral("NPC %1").arg(i+1);
            for (const QJsonValue &v : resources) {
                const QJsonObject r=v.toObject();
                if (r.value("id").toString()==spriteId) {
                    title=r.value("name").toString(title); break;
                }
            }
            g.addNode(w+QStringLiteral("/npc/")+QString::number(i),w,QStringLiteral("NPC"),title,
                      QStringLiteral("Dialogue starts at node %1\nCompleted dialogue: %2\nSprite ID: %3")
                          .arg(npc.value("node").toInt()).arg(npc.value("doneNode").toInt(-1)).arg(spriteId),3);
            FlowNode &node=g.nodes[g.byId.value(w+QStringLiteral("/npc/")+QString::number(i))];
            for (const QJsonValue &rv:resources) {
                const QJsonObject resource=rv.toObject();
                if (resource.value(QStringLiteral("id")).toString()!=spriteId)continue;
                node.artStamp=resource.value(QStringLiteral("spriteStamp")).toObject();
                node.artPath=node.artStamp.value(QStringLiteral("source")).toString();
                if (node.artPath.isEmpty())node.artPath=resource.value(QStringLiteral("path")).toString();
                node.artFrame=resource.value(QStringLiteral("frame")).toInt();
                node.artWidth=qMax(1,resource.value(QStringLiteral("cellWidth")).toInt(8));
                node.artHeight=qMax(1,resource.value(QStringLiteral("cellHeight")).toInt(8));
                break;
            }
        }
    }

    // Second pass: connect actual design relationships, including cross-world links.
    for (const auto &entry : documents) {
        const QString w=entry.name;
        const QJsonObject doc=entry.doc;
        const QJsonArray resources=doc.value(QStringLiteral("resources")).toArray();
        const QJsonObject adv=doc.value(QStringLiteral("adventure")).toObject();
        const QJsonArray items=adv.value(QStringLiteral("items")).toArray();
        const QJsonArray dialogs=adv.value(QStringLiteral("nodes")).toArray();
        for (const QJsonValue &v : resources) {
            const QJsonObject r=v.toObject();
            const QJsonObject obj=r.value(QStringLiteral("gameObject")).toObject();
            const QString type=obj.value(QStringLiteral("type")).toString();
            const QString from=objectKey(w,r.value(QStringLiteral("id")).toString());
            if (!g.byId.contains(from)) continue;
            const QString target=obj.value(QStringLiteral("targetObjectId")).toString();
            if (!target.isEmpty()) {
                const QString to=objectKey(w,target);
                if (g.byId.contains(to)) g.link(from,to,QStringLiteral("Object: ")+obj.value("targetAction").toString("toggle"));
                else g.missing(w,from,QStringLiteral("object"),target);
            }
            const QString drop=obj.value(QStringLiteral("breakDropCollectableId")).toString();
            if (!drop.isEmpty()) {
                const QString to=objectKey(w,drop);
                if (g.byId.contains(to)) g.link(from,to,QStringLiteral("Drops on break"));
                else g.missing(w,from,QStringLiteral("break-drop collectable"),drop);
            }
            const QString spline=obj.value(QStringLiteral("splineId")).toString();
            if (!spline.isEmpty()) {
                const QString to=splineKey(w,spline);
                if (g.byId.contains(to)) g.link(to,from,QStringLiteral("Moves along path"));
                else g.missing(w,from,QStringLiteral("spline"),spline);
            }
            if (type == QStringLiteral("collectable")) {
                const int kind=obj.value(QStringLiteral("pickupKind")).toInt(-1);
                for (int i=0;i<items.size();++i)
                    if (items.at(i).toObject().value(QStringLiteral("pickupKind")).toInt(-2)==kind)
                        g.link(from,itemKey(w,i),QStringLiteral("Adds to inventory"));
            }
            const QString destination=obj.value(QStringLiteral("gotoWorldName")).toString().trimmed();
            if (type == QStringLiteral("goto_world") && !destination.isEmpty()) {
                QString match;
                for (const QString &known:g.worlds)
                    if (known.compare(destination,Qt::CaseInsensitive)==0) {match=known;break;}
                if (match.isEmpty()) {g.missing(w,from,QStringLiteral("world"),destination);continue;}
                QString startId=obj.value(QStringLiteral("gotoStartId")).toString();
                if (startId.isEmpty()) startId=QStringLiteral("default");
                const QString to=spawnKey(match,startId);
                if (g.byId.contains(to)) g.link(from,to,QStringLiteral("Goto World: ")+match);
                else g.missing(w,from,QStringLiteral("destination Player Start in ")+match,startId);
            }
        }
        for (int i=0;i<items.size();++i) {
            const QJsonObject item=items.at(i).toObject();
            const QString stat=item.value(QStringLiteral("useStat")).toString().trimmed();
            const int delta=item.value(QStringLiteral("useDelta")).toInt();
            if (stat.isEmpty() || delta==0) continue;
            const QString key=w+QStringLiteral("/stat/")+stat.toLower();
            g.addNode(key,w,QStringLiteral("Player Stat"),stat,
                      QStringLiteral("Player statistic affected by inventory USE actions"),5);
            g.link(itemKey(w,i),key,QStringLiteral("Use item: %1%2")
                       .arg(delta>0?QStringLiteral("+"):QString()).arg(delta));
        }
        const QJsonArray npcs=adv.value(QStringLiteral("npcs")).toArray();
        for (int i=0;i<npcs.size();++i) {
            const QJsonObject npc=npcs.at(i).toObject();
            const QString npcKey=w+QStringLiteral("/npc/")+QString::number(i);
            const QString spriteKey=objectKey(w,npc.value(QStringLiteral("spriteId")).toString());
            if (g.byId.contains(spriteKey)) g.link(spriteKey,npcKey,QStringLiteral("NPC interaction"));
            const int node=npc.value(QStringLiteral("node")).toInt(-1);
            if (node>=0 && node<dialogs.size())g.link(npcKey,dialogueKey(w,node),QStringLiteral("Starts dialogue"));
            else if (node>=0)g.missing(w,npcKey,QStringLiteral("dialogue node"),QString::number(node));
            const int done=npc.value(QStringLiteral("doneNode")).toInt(-1);
            if (done>=0 && done<dialogs.size())g.link(npcKey,dialogueKey(w,done),QStringLiteral("Completed interaction"));
        }
        for (int i=0;i<dialogs.size();++i) {
            const QJsonArray choices=dialogs.at(i).toObject().value(QStringLiteral("choices")).toArray();
            for (int j=0;j<choices.size();++j) {
                const QJsonObject c=choices.at(j).toObject();
                if (c.value(QStringLiteral("text")).toString().trimmed().isEmpty()) continue;
                const QString choice=dialogueKey(w,i)+QStringLiteral("/choice/")+QString::number(j);
                g.link(dialogueKey(w,i),choice,QStringLiteral("Choice %1").arg(j+1));
                const auto next = [&](int index,const QString &reason) {
                    if (index<0) return;
                    if (index<dialogs.size())g.link(choice,dialogueKey(w,index),reason);
                    else g.missing(w,choice,QStringLiteral("dialogue node"),QString::number(index));
                };
                next(c.value(QStringLiteral("next")).toInt(-1),QStringLiteral("Next / success"));
                next(c.value(QStringLiteral("missingNext")).toInt(-1),QStringLiteral("Missing item"));
                for (const auto &pair : {qMakePair("requires","Requires item"),qMakePair("give","Gives item"),qMakePair("take","Takes item")}) {
                    const int idx=c.value(QLatin1String(pair.first)).toInt(-1);
                    if (idx<0)continue;
                    const QString item=itemKey(w,idx);
                    if (idx<items.size()) {
                        if (QLatin1String(pair.first)==QLatin1String("give"))
                            g.link(choice,item,QLatin1String(pair.second));
                        else g.link(item,choice,QLatin1String(pair.second));
                    }
                    else g.missing(w,choice,QStringLiteral("inventory item index"),QString::number(idx));
                }
                const QString target=c.value(QStringLiteral("targetObjectId")).toString();
                if (!target.isEmpty()) {
                    if (g.byId.contains(objectKey(w,target)))
                        g.link(choice,objectKey(w,target),QStringLiteral("Object: ")+c.value("targetAction").toString("enable"));
                    else g.missing(w,choice,QStringLiteral("dialogue target object"),target);
                }
                const QJsonObject exchange=c.value(QStringLiteral("exchange")).toObject();
                if (!exchange.value(QStringLiteral("enabled")).toBool()) continue;
                for (const QJsonValue &part: exchange.value(QStringLiteral("items")).toArray()) {
                    const int index=part.toInt(-1);
                    if (index>=0 && index<items.size())g.link(itemKey(w,index),choice,QStringLiteral("Exchange requirement"));
                    else if (index>=0)g.missing(w,choice,QStringLiteral("exchange item index"),QString::number(index));
                }
                for (const auto &pair : {qMakePair("wrongNext","Wrong items"),qMakePair("partialNext","Partial items")})
                    next(exchange.value(QLatin1String(pair.first)).toInt(-1),QLatin1String(pair.second));
                for (const auto &key : {"wrongTargetObjectId","partialTargetObjectId"}) {
                    const QString id=exchange.value(QLatin1String(key)).toString();
                    if (id.isEmpty()) continue;
                    if (g.byId.contains(objectKey(w,id)))g.link(choice,objectKey(w,id),QLatin1String(key));
                    else g.missing(w,choice,QStringLiteral("exchange target object"),id);
                }
            }
        }
    }
    return g;
}

QColor nodeColour(const QString &kind, bool problem, const IDETheme &theme) {
    // Node categories retain distinct stripes, but every colour comes from
    // the current IDE theme, including a user's custom .sidtheme file.
    if (problem) return theme.diagnosticError;
    if (kind == QStringLiteral("World")) return theme.accent;
    if (kind == QStringLiteral("Player Start")) return theme.outputSuccess;
    if (kind == QStringLiteral("NPC")) return theme.syntaxFunction;
    if (kind == QStringLiteral("Dialogue")) return theme.syntaxString;
    if (kind == QStringLiteral("Dialogue Choice")) return theme.syntaxAPI;
    if (kind == QStringLiteral("Inventory Item")) return theme.syntaxKeyword;
    if (kind == QStringLiteral("Player Stat")) return theme.syntaxNumber;
    if (kind == QStringLiteral("Spline")) return theme.syntaxType;
    return theme.syntaxSTM32;
}

// Return an actual 16x16 preview of the sprite/frame used by this design
// node. The atlas stays read-only. Multiple nodes sharing a PPB share a single
// decoded image in the caller's project-scoped cache.
QPixmap flowArtworkIcon(const FlowNode &node, const QString &root,
                        QHash<QString,QImage> &sheetCache) {
    if (node.artPath.isEmpty())return {};
    const QString filename=QDir(root).filePath(node.artPath);
    if (!sheetCache.contains(filename)) {
        SidboxPpb::Picture picture;
        sheetCache.insert(filename,SidboxPpb::read(filename,&picture) ? picture.indexed : QImage());
    }
    const QImage &source=sheetCache.value(filename);
    if (source.isNull() || source.format()!=QImage::Format_Indexed8)return {};
    QImage sheet=source;
    QVector<QRgb> palette=sheet.colorTable();
    if (palette.size()<256)palette.resize(256);
    for (int i=0;i<palette.size();++i)
        palette[i]=qRgba(qRed(palette[i]),qGreen(palette[i]),qBlue(palette[i]),i==0?0:255);
    sheet.setColorTable(palette); // only the temporary indexed-image CLUT
    QImage art;
    if (!node.artStamp.isEmpty()) {
        const SidboxSpriteStamp stamp=SidboxSpriteStamp::fromJson(node.artStamp);
        if (stamp.active())art=stamp.compose(sheet);
    } else {
        const int cw=qMin(qMax(1,node.artWidth),sheet.width());
        const int ch=qMin(qMax(1,node.artHeight),sheet.height());
        const int cols=sheet.width()/cw, rows=sheet.height()/ch;
        if (cols<1 || rows<1)return {};
        if (node.art2x2) {
            art=QImage(cw*2,ch*2,QImage::Format_ARGB32_Premultiplied);
            art.fill(Qt::transparent);
            QPainter painter(&art);
            for (int cell=0;cell<4;++cell) {
                const int index=node.artCells.size()==4
                    ? node.artCells.at(cell).toInt(-1) : node.artFrame;
                if (index<0 || index>=cols*rows)continue;
                const QRect sourceRect((index%cols)*cw,(index/cols)*ch,cw,ch);
                painter.drawImage(QPoint((cell%2)*cw,(cell/2)*ch),sheet.copy(sourceRect));
            }
        } else {
            const int index=qBound(0,node.artFrame,cols*rows-1);
            art=sheet.copy((index%cols)*cw,(index/cols)*ch,cw,ch);
        }
    }
    if (art.isNull())return {};
    // Nearest-neighbour scaling keeps 8x8 tile art crisp.
    QPixmap result(16,16);
    result.fill(Qt::transparent);
    QPainter painter(&result);
    const QSize size=art.size().scaled(16,16,Qt::KeepAspectRatio);
    const QRect dest((16-size.width())/2,(16-size.height())/2,size.width(),size.height());
    painter.setRenderHint(QPainter::SmoothPixmapTransform,false);
    painter.drawImage(dest,art);
    return result;
}

// Tiny, self-contained 16x16 pictograms: no theme-dependent icon files or
// larger artwork. All icons are painted into the graph only (never exported).
QPixmap flowCardIcon(const QString &kind, bool problem, const IDETheme &theme) {
    QPixmap pix(16,16);
    pix.fill(Qt::transparent);
    QPainter p(&pix);
    p.setRenderHint(QPainter::Antialiasing,true);
    const QColor colour = problem ? theme.diagnosticError : theme.text;
    QPen pen(colour,1.45,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
    p.setPen(pen);
    p.setBrush(Qt::NoBrush);
    if (problem) {
        p.drawPolygon(QPolygonF{QPointF(8,1.5),QPointF(15,14),QPointF(1,14)});
        p.drawLine(QPointF(8,5),QPointF(8,9));
        p.drawPoint(QPointF(8,11.5));
    } else if (kind == QStringLiteral("World")) {
        p.drawEllipse(QRectF(1.5,1.5,13,13));
        p.drawEllipse(QRectF(5,1.5,6,13));
        p.drawLine(QPointF(2,8),QPointF(14,8));
    } else if (kind == QStringLiteral("Player Start")) {
        p.drawLine(QPointF(3,1.5),QPointF(3,14.5));
        p.drawPolygon(QPolygonF{QPointF(3,2),QPointF(13,2),QPointF(10,6),QPointF(13,9),QPointF(3,9)});
    } else if (kind == QStringLiteral("NPC")) {
        p.drawEllipse(QRectF(5,1,6,6));
        p.drawArc(QRectF(2.5,8,11,7),0,180*16);
    } else if (kind == QStringLiteral("Dialogue")) {
        p.drawRect(QRectF(1.5,2,13,9));
        p.drawPolyline(QPolygonF{QPointF(4,11),QPointF(4,14),QPointF(8,11)});
        p.drawLine(QPointF(4,5),QPointF(12,5));
        p.drawLine(QPointF(4,8),QPointF(10,8));
    } else if (kind == QStringLiteral("Dialogue Choice")) {
        p.drawEllipse(QRectF(1,1,4,4));
        p.drawEllipse(QRectF(11,1,4,4));
        p.drawEllipse(QRectF(6,11,4,4));
        p.drawLine(QPointF(4,5),QPointF(7,11));
        p.drawLine(QPointF(12,5),QPointF(9,11));
    } else if (kind == QStringLiteral("Inventory Item") || kind == QStringLiteral("Collectable pickup")) {
        p.drawRect(QRectF(2.5,5.5,11,9));
        p.drawArc(QRectF(5,1.5,6,8),0,180*16);
    } else if (kind == QStringLiteral("Player Stat")) {
        p.drawLine(QPointF(1,13),QPointF(4,13));
        p.drawLine(QPointF(4,13),QPointF(6,4));
        p.drawLine(QPointF(6,4),QPointF(9,11));
        p.drawLine(QPointF(9,11),QPointF(11,7));
        p.drawLine(QPointF(11,7),QPointF(15,7));
    } else if (kind == QStringLiteral("Spline")) {
        p.drawLine(QPointF(2,12),QPointF(8,3));
        p.drawLine(QPointF(8,3),QPointF(14,11));
        for (const QPointF point : {QPointF(2,12),QPointF(8,3),QPointF(14,11)})
            p.drawEllipse(point,1.5,1.5);
    } else if (kind == QStringLiteral("World exit / transition")) {
        p.drawRect(QRectF(2,2,9,12));
        p.drawLine(QPointF(6,8),QPointF(15,8));
        p.drawLine(QPointF(12,5),QPointF(15,8));
        p.drawLine(QPointF(12,11),QPointF(15,8));
    } else if (kind == QStringLiteral("Door / toggle object")) {
        p.drawRect(QRectF(3,1.5,10,13));
        p.drawPoint(QPointF(10.5,8));
    } else if (kind == QStringLiteral("Breakable object")) {
        p.drawRect(QRectF(2,2,12,12));
        p.drawPolyline(QPolygonF{QPointF(8,2),QPointF(6,6),QPointF(10,8),QPointF(7,14)});
    } else {
        p.drawRect(QRectF(3,3,10,10));
        p.drawLine(QPointF(3,8),QPointF(13,8));
    }
    return pix;
}

// Alternative to Clean Layout: use real directed links to spread successive
// steps across the screen. Weakly connected chains occupy their own vertical
// blocks; breadth-first ranks terminate even when dialogue/door logic cycles.
// Cross-world links remain visible, but never distort either world's layout.
QHash<QString,QPointF> flowLeftToRightPositions(const FlowGraph &g) {
    QHash<QString,QPointF> positions;
    const int count=int(g.nodes.size());
    QVector<QVector<int>> forward(count), undirected(count);
    QVector<int> indegree(count,0);
    for (const FlowEdge &edge:g.edges) {
        const int a=g.byId.value(edge.from,-1), b=g.byId.value(edge.to,-1);
        if (a<0 || b<0 || a==b || g.nodes.at(a).world!=g.nodes.at(b).world)continue;
        forward[a].append(b);
        undirected[a].append(b);
        undirected[b].append(a);
        ++indegree[b];
    }
    QVector<bool> grouped(count,false);
    qreal worldTop=20;
    for (const QString &world:g.worlds) {
        qreal componentTop=worldTop+52;
        for (int first=0;first<count;++first) {
            if (grouped[first] || g.nodes.at(first).world!=world)continue;
            QVector<int> component{first};
            grouped[first]=true;
            for (int q=0;q<component.size();++q) {
                for (int next:undirected[component.at(q)]) {
                    if (!grouped[next]) {grouped[next]=true;component.append(next);}
                }
            }
            std::sort(component.begin(),component.end());
            QSet<int> members;
            for (int i:component)members.insert(i);
            QVector<int> rank(count,-1);
            QVector<int> visitOrder;
            // All natural entry points start on the left, including any world
            // node and independent game actions in the same connected chain.
            for (int i:component) {
                if (indegree[i]==0 || g.nodes.at(i).kind==QStringLiteral("World")) {
                    rank[i]=0;
                    visitOrder.append(i);
                }
            }
            for (int i:component) {
                if (rank[i]>=0)continue;
                // The next unreached strongly connected section has no source.
                // Seed it once rather than repeatedly raising ranks in a loop.
                if (visitOrder.isEmpty()) {rank[i]=0;visitOrder.append(i);}
            }
            for (int q=0;q<visitOrder.size();++q) {
                const int source=visitOrder.at(q);
                for (int target:forward[source]) {
                    if (!members.contains(target) || rank[target]>=0)continue;
                    rank[target]=rank[source]+1;
                    visitOrder.append(target);
                }
                // If directed links do not reach a section (cycles or edges
                // pointing back toward entry), start it on the left as well.
                if (q+1==visitOrder.size()) {
                    for (int i:component) {
                        if (rank[i]<0) {rank[i]=0;visitOrder.append(i);break;}
                    }
                }
            }
            QHash<int,int> rows;
            int tallest=0;
            for (int i:visitOrder) {
                const int column=rank[i];
                const int row=rows.value(column,0);
                positions.insert(g.nodes.at(i).id,QPointF(32+column*350,componentTop+row*116));
                rows.insert(column,row+1);
                tallest=qMax(tallest,row+1);
            }
            componentTop+=tallest*116+66;
        }
        // Reserve at least a small band for an empty world.
        worldTop=qMax(worldTop+220,componentTop+24);
    }
    return positions;
}

// A thicker invisible shape makes a narrow connector easy to click without
// turning it into a visually heavy wire.
class FlowWireItem final : public QGraphicsPathItem {
public:
    explicit FlowWireItem(QGraphicsItem *parent=nullptr) : QGraphicsPathItem(parent) {
        setAcceptedMouseButtons(Qt::LeftButton);
        setData(1,QStringLiteral("flow-wire"));
    }
    std::function<void()> onClicked;
    QRectF boundingRect() const override {
        return QGraphicsPathItem::boundingRect().adjusted(-7,-7,7,7);
    }
    QPainterPath shape() const override {
        QPainterPathStroker stroke;
        stroke.setWidth(12);
        return stroke.createStroke(path());
    }
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
        if (event->button()==Qt::LeftButton && onClicked) {
            onClicked();
            event->accept();
            return;
        }
        QGraphicsPathItem::mousePressEvent(event);
    }
};

// In-place title editor for MANUAL groups. Automatic array group names are
// derived from actual source resource names and should not be overridden.
class FlowGroupTitleItem final : public QGraphicsTextItem {
public:
    explicit FlowGroupTitleItem(const QString &name,QGraphicsItem *parent, const QColor &titleColour)
        : QGraphicsTextItem(name,parent),m_original(name) {
        setDefaultTextColor(titleColour);
        setFont(QFont(QStringLiteral("Sans Serif"),10,QFont::DemiBold));
        setTextInteractionFlags(Qt::NoTextInteraction);
        setToolTip(QObject::tr("Double-click to rename this logic group"));
    }
    std::function<void(const QString &)> onRenamed;
    void beginEditing() {
        if (m_editing)return;
        m_editing=true;
        setFlag(QGraphicsItem::ItemIsFocusable,true);
        setTextInteractionFlags(Qt::TextEditorInteraction);
        setFocus(Qt::OtherFocusReason);
        QTextCursor cursor=textCursor();
        cursor.select(QTextCursor::Document);
        setTextCursor(cursor);
    }
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
        // The first click must be accepted by the title item, otherwise Qt
        // delivers the second click to the movable parent card instead.
        if (!m_editing && event->button()==Qt::LeftButton) {
            if (parentItem())parentItem()->setSelected(true);
            event->accept();return;
        }
        QGraphicsTextItem::mousePressEvent(event);
    }
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override {
        beginEditing();
        event->accept();
    }
    void keyPressEvent(QKeyEvent *event) override {
        if (m_editing && (event->key()==Qt::Key_Return || event->key()==Qt::Key_Enter)) {
            finish(true);event->accept();return;
        }
        if (m_editing && event->key()==Qt::Key_Escape) {
            finish(false);event->accept();return;
        }
        QGraphicsTextItem::keyPressEvent(event);
    }
    void focusOutEvent(QFocusEvent *event) override {
        QGraphicsTextItem::focusOutEvent(event);
        finish(true);
    }
private:
    void finish(bool commit) {
        if (!m_editing)return;
        m_editing=false;
        const QString newName=toPlainText().trimmed();
        setTextInteractionFlags(Qt::NoTextInteraction);
        if (commit && !newName.isEmpty() && newName!=m_original && onRenamed) {
            m_original=newName;
            onRenamed(newName);
        } else {
            setPlainText(m_original);
        }
    }
    QString m_original;
    bool m_editing=false;
};

struct EdgeArt { QString from,to,label; FlowWireItem *path=nullptr; QGraphicsPolygonItem *arrow=nullptr; };

// The graphics are editable ONLY as a diagram. Moving one never changes a
// resource coordinate, world design, or runtime data.
class FlowCardItem final : public QGraphicsRectItem {
public:
    explicit FlowCardItem(const QString &key) : m_key(key) {
        setRect(0,0,250,70);
        setFlag(QGraphicsItem::ItemIsSelectable,true);
        setFlag(QGraphicsItem::ItemIsMovable,true);
        setFlag(QGraphicsItem::ItemSendsGeometryChanges,true);
        setData(0,key);
    }
    std::function<void()> onMoved;
    std::function<void(const QString &)> onToggle;
    void setGroup(bool group) { m_group = group; }
    void setSnapToGrid(bool enabled) { m_snapToGrid = enabled; }
    void setAllowLeaveParent(bool enabled) { m_allowLeaveParent = enabled; }
    // Include the actual mouse release position; Qt child positions are
    // parent-local, but drag-out detection needs a scene coordinate.
    std::function<void(const QString &,const QPointF &,const QPointF &)> onDropped;
protected:
    QVariant itemChange(GraphicsItemChange change,const QVariant &value) override {
        if (change==QGraphicsItem::ItemPositionChange) {
            QPointF p=value.toPointF();
            if (parentItem() && !m_allowLeaveParent && flags().testFlag(QGraphicsItem::ItemIsMovable)) {
                // Ordinary mini cards stay inside their logic group; nested
                // array groups may cross the boundary to be pulled back out.
                p.setX(qMax(qreal(16),p.x()));
                p.setY(qMax(qreal(80),p.y()));
            }
            if (m_snapToGrid) {
                // Coordinates are scene-local for ordinary cards and
                // group-local for mini cards: both use the same 8px grid.
                p.setX(std::round(p.x()/8.0)*8.0);
                p.setY(std::round(p.y()/8.0)*8.0);
            }
            return p;
        }
        const QVariant result=QGraphicsRectItem::itemChange(change,value);
        if (change==QGraphicsItem::ItemPositionHasChanged && onMoved) onMoved();
        return result;
    }
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
        m_pressPosition=pos();
        QGraphicsRectItem::mousePressEvent(event);
    }
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override {
        const bool clickedToggle=m_group && pos()==m_pressPosition &&
             QRectF(11,3,25,23).contains(event->pos()) && bool(onToggle);
        QGraphicsRectItem::mouseReleaseEvent(event);
        if (clickedToggle) onToggle(m_key); // callback schedules a redraw AFTER this event
        if (onDropped && pos()!=m_pressPosition) onDropped(m_key,pos(),event->scenePos());
    }
private:
    QString m_key;
    QPointF m_pressPosition;
    bool m_group=false;
    bool m_snapToGrid=true;
    bool m_allowLeaveParent=false;
};

// Drag empty canvas to rubber-band select. Middle or Alt+drag pans.
// Ctrl+click adds/removes individual cards from a multi-selection.
class FlowView final : public QGraphicsView {
public:
    FlowView(QGraphicsScene *scene,QWidget *parent) : QGraphicsView(scene,parent) {
        setDragMode(QGraphicsView::NoDrag);
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    }
    void zoom(qreal multiplier) {
        const qreal now=transform().m11();
        if (!std::isfinite(now) || now<=0 || !std::isfinite(multiplier))return;
        const qreal next=qBound(qreal(0.04),now*multiplier,qreal(5.0));
        scale(next/now,next/now);
    }
protected:
    void wheelEvent(QWheelEvent *event) override {
        const int steps=event->angleDelta().y();
        const int pixels=event->pixelDelta().y();
        if (steps || pixels) {
            zoom(std::exp((steps ? steps : pixels*2)*0.0016));
            event->accept();
            return;
        }
        QGraphicsView::wheelEvent(event);
    }
    void mousePressEvent(QMouseEvent *event) override {
        // Raise the clicked card above its siblings. An embedded card must
        // also bring each enclosing group forward; child z-values alone
        // cannot place it above a different top-level logic group.
        // Use the card key rather than Qt item types so clicks on a group's
        // editable title, labels, and artwork all work the same way.
        if (event->button()==Qt::LeftButton) {
            for (QGraphicsItem *card=itemAt(event->pos());card;card=card->parentItem()) {
                if (card->data(0).toString().isEmpty())continue;
                qreal front=card->zValue();
                if (QGraphicsItem *parent=card->parentItem()) {
                    for (QGraphicsItem *sibling:parent->childItems()) {
                        if (sibling!=card && !sibling->data(0).toString().isEmpty())
                            front=qMax(front,sibling->zValue());
                    }
                } else if (scene()) {
                    for (QGraphicsItem *sibling:scene()->items()) {
                        if (sibling!=card && !sibling->parentItem() &&
                            !sibling->data(0).toString().isEmpty())
                            front=qMax(front,sibling->zValue());
                    }
                }
                card->setZValue(front+1.0);
            }
        }
        const bool middle=event->button()==Qt::MiddleButton;
        const bool blank=event->button()==Qt::LeftButton && !cardAt(event->pos());
        if (blank && !(event->modifiers() & Qt::AltModifier)) {
            m_rubber=true;
            setDragMode(QGraphicsView::RubberBandDrag);
            QGraphicsView::mousePressEvent(event);
            return;
        }
        if (middle || (blank && (event->modifiers() & Qt::AltModifier))) {
            m_pan=true;
            m_last=event->pos();
            setCursor(Qt::ClosedHandCursor);
            event->accept();
            return;
        }
        QGraphicsView::mousePressEvent(event);
    }
    void mouseMoveEvent(QMouseEvent *event) override {
        if (m_pan) {
            const QPoint offset=event->pos()-m_last;
            m_last=event->pos();
            horizontalScrollBar()->setValue(horizontalScrollBar()->value()-offset.x());
            verticalScrollBar()->setValue(verticalScrollBar()->value()-offset.y());
            event->accept();
            return;
        }
        QGraphicsView::mouseMoveEvent(event);
    }
    void mouseReleaseEvent(QMouseEvent *event) override {
        if (m_rubber) {
            QGraphicsView::mouseReleaseEvent(event);
            setDragMode(QGraphicsView::NoDrag);
            m_rubber=false;
            return;
        }
        if (m_pan) {
            m_pan=false;
            unsetCursor();
            event->accept();
            return;
        }
        QGraphicsView::mouseReleaseEvent(event);
    }
private:
    bool cardAt(QPoint point) const {
        QGraphicsItem *item=itemAt(point);
        while (item) {
            if (!item->data(0).toString().isEmpty() ||
                item->data(1).toString()==QStringLiteral("flow-wire"))return true;
            item=item->parentItem();
        }
        return false;
    }
    bool m_pan=false;
    bool m_rubber=false;
    QPoint m_last;
};

// Design-only layout V3: V1/V2 positions remain readable. Manual group
// membership, expansion states and group positions never touch .sbgm data.
FlowLayout readFlowLayout(const QString &filename) {
    FlowLayout result;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) return result;
    const QJsonObject document=QJsonDocument::fromJson(file.readAll()).object();
    const QJsonObject positions=document.value(QStringLiteral("positions")).toObject();
    for (auto it=positions.begin();it!=positions.end();++it) {
        if (!it.value().isObject())continue;
        const QJsonObject p=it.value().toObject();
        if (!p.value(QStringLiteral("x")).isDouble() || !p.value(QStringLiteral("y")).isDouble())continue;
        const qreal x=p.value(QStringLiteral("x")).toDouble();
        const qreal y=p.value(QStringLiteral("y")).toDouble();
        if (std::isfinite(x) && std::isfinite(y) && std::abs(x)<100000 && std::abs(y)<100000)
            result.positions.insert(it.key(),QPointF(x,y));
    }
    for (const QJsonValue &value:document.value(QStringLiteral("groups")).toArray()) {
        const QJsonObject o=value.toObject();
        FlowGroup g;
        g.id=o.value(QStringLiteral("id")).toString();
        g.world=o.value(QStringLiteral("world")).toString();
        g.title=o.value(QStringLiteral("title")).toString();
        for (const QJsonValue &member:o.value(QStringLiteral("members")).toArray()) {
            const QString id=member.toString();
            if (!id.isEmpty() && !g.members.contains(id))g.members.append(id);
        }
        if (g.id.startsWith(QStringLiteral("flow-group/manual/")) && !g.world.isEmpty()
            && g.members.size()>=2 && result.manualGroups.size()<512)
            result.manualGroups.append(g);
    }
    const QJsonObject states=document.value(QStringLiteral("expanded")).toObject();
    for (auto it=states.begin();it!=states.end();++it)
        if (it.value().isBool())result.expanded.insert(it.key(),it.value().toBool());
    const QJsonObject embedded=document.value(QStringLiteral("embeddedArrays")).toObject();
    for (auto it=embedded.constBegin();it!=embedded.constEnd();++it) {
        const QString parent=it.value().toString();
        if (it.key().startsWith(QStringLiteral("flow-group/array/")) &&
            parent.startsWith(QStringLiteral("flow-group/manual/")))
            result.embeddedArrays.insert(it.key(),parent);
    }
    result.snapToGrid=document.value(QStringLiteral("snapToGrid")).toBool(true);
    const QJsonObject offsets=document.value(QStringLiteral("memberPositions")).toObject();
    for (auto group=offsets.begin();group!=offsets.end();++group) {
        if (!group.value().isObject())continue;
        const QJsonObject members=group.value().toObject();
        for (auto member=members.begin();member!=members.end();++member) {
            if (!member.value().isObject())continue;
            const QJsonObject point=member.value().toObject();
            if (!point.value(QStringLiteral("x")).isDouble() || !point.value(QStringLiteral("y")).isDouble())continue;
            const QPointF pos(point.value(QStringLiteral("x")).toDouble(),point.value(QStringLiteral("y")).toDouble());
            if (std::isfinite(pos.x()) && std::isfinite(pos.y()) && pos.x()>=0 && pos.y()>=0
                && pos.x()<100000 && pos.y()<100000)
                result.memberPositions[group.key()].insert(member.key(),pos);
        }
    }
    return result;
}
bool writeFlowLayout(const QString &filename,const FlowLayout &layout) {
    QJsonObject points;
    for (auto it=layout.positions.cbegin();it!=layout.positions.cend();++it) {
        const QPointF p=it.value();
        points.insert(it.key(),QJsonObject{{QStringLiteral("x"),p.x()}, {QStringLiteral("y"),p.y()}});
    }
    QJsonArray groups;
    for (const FlowGroup &g:layout.manualGroups) {
        QJsonArray members;
        for (const QString &id:g.members)members.append(id);
        groups.append(QJsonObject{{QStringLiteral("id"),g.id},
                                  {QStringLiteral("world"),g.world},
                                  {QStringLiteral("title"),g.title},
                                  {QStringLiteral("members"),members}});
    }
    QJsonObject states;
    for (auto it=layout.expanded.cbegin();it!=layout.expanded.cend();++it)
        states.insert(it.key(),it.value());
    QJsonObject memberPositions;
    for (auto group=layout.memberPositions.cbegin();group!=layout.memberPositions.cend();++group) {
        QJsonObject members;
        for (auto member=group.value().cbegin();member!=group.value().cend();++member)
            members.insert(member.key(),QJsonObject{{QStringLiteral("x"),member.value().x()},
                                                     {QStringLiteral("y"),member.value().y()}});
        memberPositions.insert(group.key(),members);
    }
    QJsonObject embeddedArrays;
    for (auto it=layout.embeddedArrays.cbegin();it!=layout.embeddedArrays.cend();++it)
        embeddedArrays.insert(it.key(),it.value());
    const QJsonDocument doc(QJsonObject{{QStringLiteral("version"),4},
                                         {QStringLiteral("positions"),points},
                                         {QStringLiteral("groups"),groups},
                                         {QStringLiteral("expanded"),states},
                                         {QStringLiteral("memberPositions"),memberPositions},
                                         {QStringLiteral("embeddedArrays"),embeddedArrays},
                                         {QStringLiteral("snapToGrid"),layout.snapToGrid}});
    QSaveFile file(filename);
    if (!file.open(QIODevice::WriteOnly))return false;
    if (file.write(doc.toJson(QJsonDocument::Indented))<0) {file.cancelWriting();return false;}
    return file.commit();
}

// Manual groups win over automatic array groups. Both are scoped to a world;
// e.g. Guard[0], Guard[1] become "Guard[]", not an unrelated-world group.
void buildFlowGroups(const FlowGraph &graph,const FlowLayout &layout,
                     QHash<QString,FlowGroup> &groups,QHash<QString,QString> &memberGroup) {
    groups.clear();memberGroup.clear();
    for (const FlowGroup &saved:layout.manualGroups) {
        FlowGroup group=saved;
        group.members.clear();
        for (const QString &id:saved.members) {
            const int index=graph.byId.value(id,-1);
            if (index>=0 && graph.nodes.at(index).world==group.world && !memberGroup.contains(id))
                group.members.append(id);
        }
        if (group.members.size()<2)continue;
        group.expanded=layout.expanded.value(group.id,false);
        for (const QString &id:group.members)memberGroup.insert(id,group.id);
        groups.insert(group.id,group);
    }
    const QRegularExpression arrayName(QStringLiteral(R"(^(.*?)\[(\d+)\]$)"));
    QHash<QString,QVector<QPair<int,QString>>> arrays;
    QHash<QString,QString> titles;
    QHash<QString,QString> worlds;
    for (const FlowNode &node:graph.nodes) {
        if (memberGroup.contains(node.id))continue;
        const QRegularExpressionMatch match=arrayName.match(node.title.trimmed());
        if (!match.hasMatch() || match.captured(1).trimmed().isEmpty())continue;
        const QString base=match.captured(1).trimmed();
        const QString key=QStringLiteral("flow-group/array/")+node.world+QStringLiteral("/")+
                          base.toCaseFolded();
        arrays[key].append(qMakePair(match.captured(2).toInt(),node.id));
        titles.insert(key,base+QStringLiteral("[]"));
        worlds.insert(key,node.world);
    }
    for (auto it=arrays.begin();it!=arrays.end();++it) {
        if (it.value().size()<2)continue;
        std::sort(it.value().begin(),it.value().end(),[](const auto &a,const auto &b){
            return a.first<b.first || (a.first==b.first && a.second<b.second);
        });
        FlowGroup group;
        group.id=it.key();group.world=worlds.value(it.key());
        group.title=titles.value(it.key());group.automatic=true;
        group.expanded=layout.expanded.value(group.id,false);
        for (const auto &entry:it.value()) {
            group.members.append(entry.second);
            memberGroup.insert(entry.second,group.id);
        }
        groups.insert(group.id,group);
    }
}

FlowGraph groupLayoutGraph(const FlowGraph &graph,const QHash<QString,FlowGroup> &groups,
                           const QHash<QString,QString> &memberGroup,
                           const QHash<QString,QString> &embeddedArrays) {
    FlowGraph display;
    display.worlds=graph.worlds;
    for (const FlowNode &node:graph.nodes) {
        if (memberGroup.contains(node.id))continue;
        display.addNode(node.id,node.world,node.kind,node.title,node.description,node.column,node.problem);
    }
    for (auto it=groups.cbegin();it!=groups.cend();++it) {
        if (embeddedArrays.contains(it.key()) && groups.contains(embeddedArrays.value(it.key())) &&
            groups.value(embeddedArrays.value(it.key())).world==it.value().world)
            continue; // This array is a child of the visible manual group.
        int column=5;
        for (const QString &id:it.value().members)
            column=qMin(column,graph.nodes.at(graph.byId.value(id)).column);
        display.addNode(it.key(),it.value().world,QStringLiteral("Group"),it.value().title,
                        QStringLiteral("Collapsed logic group"),column);
    }
    QSet<QString> seen;
    for (const FlowEdge &edge:graph.edges) {
        QString from=memberGroup.value(edge.from,edge.from);
        QString to=memberGroup.value(edge.to,edge.to);
        if (groups.contains(embeddedArrays.value(from)) &&
            groups.value(embeddedArrays.value(from)).world==groups.value(from).world)
            from=embeddedArrays.value(from);
        if (groups.contains(embeddedArrays.value(to)) &&
            groups.value(embeddedArrays.value(to)).world==groups.value(to).world)
            to=embeddedArrays.value(to);
        if (from==to)continue;
        const QString key=from+QChar(0x1f)+to;
        if (seen.contains(key))continue;
        seen.insert(key);display.link(from,to,edge.label);
    }
    return display;
}

} // namespace

void openGameFlowEditor(QWidget *parent, const QString &projectRoot, const IDETheme &theme) {
    // The graph is design-time only. Take the current designer theme as a
    // snapshot when opened, as this dialog is modal.
    // Blend existing theme fields only: no independent flowchart palette.
    const auto mix = [](const QColor &a, const QColor &b, qreal fraction) -> QColor {
        return QColor::fromRgbF(a.redF() * (1.0 - fraction) + b.redF() * fraction,
                                a.greenF() * (1.0 - fraction) + b.greenF() * fraction,
                                a.blueF() * (1.0 - fraction) + b.blueF() * fraction);
    };
    const QColor cardBackground = mix(theme.panelBackground, theme.brightText, 0.07);
    const QColor groupBackground = mix(theme.panelBackground, theme.accent, 0.36);
    const QColor arrayBackground = mix(groupBackground, theme.accent, 0.13);
    const QColor nestedBackground = mix(groupBackground, theme.accent, 0.28);
    const QColor miniBackground = mix(cardBackground, theme.windowBackground, 0.20);
    const QColor cardBorder = mix(theme.border, theme.mutedText, 0.45);
    QDialog dialog(parent);
    dialog.setWindowTitle(QObject::tr("Game Flow Debugger - Design Time"));
    dialog.setWindowState(dialog.windowState() | Qt::WindowMaximized);
    dialog.setMinimumSize(780,480);
    auto *rootLayout=new QVBoxLayout(&dialog);
    rootLayout->setContentsMargins(7,7,7,7);
    rootLayout->setSpacing(5);
    auto *tools=new QHBoxLayout();
    auto *worldSelect=new QComboBox(&dialog);
    worldSelect->setMinimumWidth(160);
    auto *search=new QLineEdit(&dialog);
    search->setPlaceholderText(QObject::tr("Find object, NPC, dialogue, stat..."));
    search->setMaximumWidth(320);
    auto *connectionsOnly=new QCheckBox(QObject::tr("Highlight selected links"),&dialog);
    auto *greenLinks=new QCheckBox(QObject::tr("Green trace (no dim)"),&dialog);
    greenLinks->setToolTip(QObject::tr("Colour links of selected cards bright green without dimming the rest of the graph."));
    auto *reload=new QPushButton(QObject::tr("Reload Saved Worlds"),&dialog);
    auto *zoomIn=new QPushButton(QStringLiteral("+"),&dialog);
    auto *zoomOut=new QPushButton(QStringLiteral("-"),&dialog);
    auto *fit=new QPushButton(QObject::tr("Fit Graph"),&dialog);
    auto *actualSize=new QPushButton(QObject::tr("100%"),&dialog);
    auto *clean=new QPushButton(QObject::tr("Clean Layout"),&dialog);
    auto *spread=new QPushButton(QObject::tr("Spread Left to Right"),&dialog);
    auto *groupButton=new QPushButton(QObject::tr("Group (Ctrl+G)"),&dialog);
    auto *ungroupButton=new QPushButton(QObject::tr("Ungroup (Ctrl+Shift+G)"),&dialog);
    auto *snapGrid=new QCheckBox(QObject::tr("Snap 8px"),&dialog);
    spread->setToolTip(QObject::tr("Arrange each connected logic chain from left to right and save the new card positions."));
    clean->setToolTip(QObject::tr("Reset all manually placed cards to an automatic layout."));
    auto *close=new QPushButton(QObject::tr("Close"),&dialog);
    for (QPushButton *b : {zoomIn,zoomOut})b->setFixedWidth(28);
    tools->addWidget(new QLabel(QObject::tr("World:"),&dialog));
    tools->addWidget(worldSelect);
    tools->addWidget(search,1);
    tools->addWidget(connectionsOnly);
    tools->addWidget(greenLinks);
    tools->addWidget(reload);
    tools->addWidget(zoomOut); tools->addWidget(zoomIn); tools->addWidget(actualSize);
    tools->addWidget(fit); tools->addWidget(clean); tools->addWidget(spread);
    tools->addWidget(groupButton); tools->addWidget(ungroupButton);
    tools->addWidget(snapGrid); tools->addWidget(close);
    rootLayout->addLayout(tools);
    auto *split=new QSplitter(Qt::Horizontal,&dialog);
    split->setChildrenCollapsible(false);
    auto *scene=new QGraphicsScene(split);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    auto *view=new FlowView(scene,split);
    view->setRenderHint(QPainter::Antialiasing,true);
    view->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    view->setBackgroundBrush(theme.windowBackground);
    auto *right=new QWidget(split);
    right->setMinimumWidth(215);
    auto *rightLayout=new QVBoxLayout(right);
    rightLayout->setContentsMargins(7,7,7,7);
    auto *help=new QLabel(QObject::tr("Drag cards to rearrange the graph.\n"
                                   "Drag empty space to select cards; middle/Alt+drag to pan.\n"
                                   "Ctrl+click adds individual selections. Ctrl+G groups.\n"
                                   "Click a group's +/- to expand or collapse; drag its header to move.\n"
                                   "Drop a card or array group onto a logic group to place it inside.\n"
                                   "Drag a nested array group outside its logic group to detach it.\n"
                                   "Manual groups show internal arrows and movable mini cards.\n"
                                   "Ctrl+Shift+G ungroups a selected manual group or its child.\n"
                                   "Snap 8px aligns all cards (including mini cards) while dragging.\n"
                                   "Positions and groups are saved per project.\n"
                                   "Clean Layout restores the original columns.\n"
                                   "Spread Left to Right lays out linked logic chains.\n"
                                   "Red cards indicate broken references.\n"
                                   "Wire colours flow RED (outgoing) to GREEN (incoming).\n"
                                   "Two opposite links are drawn as separate parallel wires.\n"
                                   "Click a wire to select both connected cards.\n"
                                   "Double-click a manual group title or press F2 to rename it."),right);
    help->setWordWrap(true);
    rightLayout->addWidget(help);
    auto *details=new QPlainTextEdit(right);
    details->setReadOnly(true);
    details->setLineWrapMode(QPlainTextEdit::WidgetWidth);
    rightLayout->addWidget(details,1);
    auto *status=new QLabel(right);
    status->setWordWrap(true);
    rootLayout->addWidget(split,1);
    rootLayout->addWidget(status);
    split->setStretchFactor(0,4);split->setStretchFactor(1,1);
    split->setSizes({1000,270});

    FlowGraph graph;
    QHash<QString,QGraphicsRectItem *> cards;
    QHash<QString,FlowGroupTitleItem *> groupTitles;
    QHash<QString,QGraphicsRectItem *> worldBands;
    QHash<QString,QGraphicsSimpleTextItem *> worldHeaders;
    QHash<QString,QImage> artworkSheets;
    QHash<QString,FlowGroup> groups;
    QHash<QString,QString> memberGroup;
    QVector<EdgeArt> edges;
    QString selectedId;
    const QString layoutFile=QDir(projectRoot).filePath(QStringLiteral(".sidbox-flow-layout.json"));
    FlowLayout layout=readFlowLayout(layoutFile);
    snapGrid->setChecked(layout.snapToGrid);
    QHash<QString,QPointF> &savedPositions=layout.positions;
    const auto savePositions=[&]() {
        if (!writeFlowLayout(layoutFile,layout))
            status->setText(QObject::tr("Could not save card positions to %1").arg(layoutFile));
    };
    const auto setDetails=[&]() {
        if (groups.contains(selectedId)) {
            const FlowGroup &g=groups.value(selectedId);
            QStringList lines{g.title, QStringLiteral("Type: ")+(g.automatic ? QStringLiteral("Automatic array group") : QStringLiteral("Manual group")),
                              QStringLiteral("World: ")+g.world,
                              QStringLiteral("Members: %1").arg(g.members.size()),
                              QString(),QObject::tr("Click +/- to show or hide individual cards. Drag the group header to move it.")};
            if (!g.automatic) {
                for (auto it=layout.embeddedArrays.cbegin();it!=layout.embeddedArrays.cend();++it)
                    if (it.value()==g.id && groups.contains(it.key()))
                        lines << QStringLiteral(" • ")+groups.value(it.key()).title+QStringLiteral(" (array group)");
            }
            for (const QString &id:g.members) {
                const int index=graph.byId.value(id,-1);
                if (index>=0)lines << QStringLiteral(" • ")+graph.nodes.at(index).title;
            }
            details->setPlainText(lines.join('\n'));
            return;
        }
        if (!graph.byId.contains(selectedId)) {
            details->setPlainText(QObject::tr("Select a card to view its source data and incoming/outgoing links.\n\n"
                                                "This is a read-only map of saved .sbgm files.\n"
                                                "Save a world before reloading to include unsaved edits."));
            return;
        }
        const FlowNode &n=graph.nodes.at(graph.byId.value(selectedId));
        QStringList lines{n.title,QStringLiteral("Type: ")+n.kind,
                          QStringLiteral("World: ")+n.world,QString(),n.description,
                          QString(),QStringLiteral("Connections:")};
        for (const FlowEdge &e:graph.edges) {
            if (e.from!=selectedId && e.to!=selectedId)continue;
            const QString other=e.from==selectedId?e.to:e.from;
            const auto it=graph.byId.constFind(other);
            const QString name=it!=graph.byId.cend()?graph.nodes.at(it.value()).title:other;
            lines << ((e.from==selectedId?QStringLiteral(" -> "):QStringLiteral(" <- "))+name+
                      QStringLiteral("  [")+e.label+QStringLiteral("]"));
        }
        if (lines.last()==QStringLiteral("Connections:"))lines<<QObject::tr("(No explicit logic references)");
        if (n.problem)lines<<QString()<<QObject::tr("WARNING: Repair this reference in the Game Designer or Adventure Editor.");
        details->setPlainText(lines.join('\n'));
    };
    std::function<void()> refreshEdges;
    auto refreshHighlight=[&]() {
        const QString query=search->text().trimmed();
        QSet<QString> selectedCards;
        for (QGraphicsItem *item:scene->selectedItems()) {
            const QString id=item->data(0).toString();
            if (cards.contains(id))selectedCards.insert(id);
        }
        if (selectedCards.isEmpty() && !selectedId.isEmpty())selectedCards.insert(selectedId);
        const auto isSelectedEndpoint=[&](const QString &id) {
            const QString groupId=memberGroup.value(id);
            return selectedCards.contains(id) || selectedCards.contains(groupId) ||
                   selectedCards.contains(layout.embeddedArrays.value(groupId));
        };
        QSet<QString> neighbours=selectedCards;
        for (const EdgeArt &e:edges) {
            if (isSelectedEndpoint(e.from))neighbours.insert(e.to);
            if (isSelectedEndpoint(e.to))neighbours.insert(e.from);
        }
        for (auto it=cards.cbegin();it!=cards.cend();++it) {
            const int idx=graph.byId.value(it.key(),-1);
            QString title,desc,kind;
            if (idx>=0) {
                const FlowNode &n=graph.nodes.at(idx);
                title=n.title;desc=n.description;kind=n.kind;
            } else if (groups.contains(it.key())) {
                const FlowGroup &g=groups.value(it.key());
                title=g.title;kind=QStringLiteral("Group");
                for (const QString &id:g.members) {
                    const int memberIndex=graph.byId.value(id,-1);
                    if (memberIndex>=0)desc+=graph.nodes.at(memberIndex).title+QChar(' ');
                }
            } else continue;
            const bool matches=query.isEmpty() || title.contains(query,Qt::CaseInsensitive) ||
                               desc.contains(query,Qt::CaseInsensitive) ||
                               kind.contains(query,Qt::CaseInsensitive);
            const bool near=!connectionsOnly->isChecked() || selectedCards.isEmpty() || neighbours.contains(it.key()) ||
                            (memberGroup.value(it.key())==selectedId) ||
                            (layout.embeddedArrays.value(memberGroup.value(it.key()))==selectedId);
            it.value()->setOpacity(matches && near ? 1.0 : 0.16);
            const bool arrayGroup = groups.contains(it.key()) && groups.value(it.key()).automatic;
            it.value()->setPen(QPen(selectedCards.contains(it.key()) || arrayGroup
                                      ? theme.accent : cardBorder,
                                      selectedCards.contains(it.key())?2.5:1));
        }
        for (const EdgeArt &e:edges) {
            const bool connected=selectedCards.isEmpty() || isSelectedEndpoint(e.from) || isSelectedEndpoint(e.to);
            const bool visible=!connectionsOnly->isChecked() || connected;
            const qreal opacity=visible?(selectedCards.isEmpty()?0.80:(connected?1.0:0.28)):0.10;
            e.path->setOpacity(opacity);e.arrow->setOpacity(opacity);
        }
        if (refreshEdges)refreshEdges();
    };
    refreshEdges=[&]() {
        QSet<QString> directed;
        for (const EdgeArt &edge:edges)
            directed.insert(edge.from+QChar(0x1f)+edge.to);
        for (const EdgeArt &e:edges) {
            QGraphicsRectItem *aItem=cards.value(e.from,nullptr);
            QGraphicsRectItem *bItem=cards.value(e.to,nullptr);
            if (!aItem || !bItem)continue;
            const QRectF a=aItem->mapRectToScene(aItem->rect());
            const QRectF b=bItem->mapRectToScene(bItem->rect());
            const QPointF ac=a.center(),bc=b.center();
            // Neighbours in the same column connect top-to-bottom so the
            // lines do not make a pointless loop through the cards.
            const bool vertical=std::abs(ac.x()-bc.x())<170;
            const bool positive=vertical ? bc.y()>=ac.y() : bc.x()>=ac.x();
            QPointF start=vertical ? QPointF(ac.x(),positive?a.bottom():a.top())
                                    : QPointF(positive?a.right():a.left(),ac.y());
            QPointF end=vertical ? QPointF(bc.x(),positive?b.top():b.bottom())
                                  : QPointF(positive?b.left():b.right(),bc.y());
            // A->B and B->A must not sit exactly on the same path: each gets
            // its own lane and its own RED -> GREEN arrow at the destination.
            const bool reciprocal=directed.contains(e.to+QChar(0x1f)+e.from);
            if (reciprocal) {
                const qreal side=e.from<e.to ? qreal(-12) : qreal(12);
                const QPointF lane=vertical ? QPointF(side,0) : QPointF(0,side);
                start+=lane;
                end+=lane;
            }
            const qreal length=vertical?std::abs(end.y()-start.y()):std::abs(end.x()-start.x());
            const qreal bend=qMax(qreal(28),length*0.40);
            QPainterPath path(start);
            if (vertical) {
                const qreal dy=positive?bend:-bend;
                path.cubicTo(start+QPointF(0,dy),end-QPointF(0,dy),end);
            } else {
                const qreal dx=positive?bend:-bend;
                path.cubicTo(start+QPointF(dx,0),end-QPointF(dx,0),end);
            }
            // Nested manual-group wires live in group-local coordinates.
            // Ordinary wires use scene coordinates, and the same anchors.
            e.path->setPath(e.path->parentItem()
                ? e.path->parentItem()->mapFromScene(path) : path);
            const qreal sign=positive?1.0:-1.0;
            const QPolygonF head=vertical
                ? QPolygonF{end,end-QPointF(-4,sign*9),end-QPointF(4,sign*9)}
                : QPolygonF{end,end-QPointF(sign*9,-4),end-QPointF(sign*9,4)};
            e.arrow->setPolygon(e.arrow->parentItem()
                ? e.arrow->parentItem()->mapFromScene(head) : head);
            // Saved graph edges establish direction: red at SOURCE, green at
            // DESTINATION. This works for backward/cyclic wires too, and
            // never assumes that nodes on the left execute first.
            const QPointF penFrom=e.path->parentItem() ? e.path->parentItem()->mapFromScene(start) : start;
            const QPointF penTo=e.path->parentItem() ? e.path->parentItem()->mapFromScene(end) : end;
            const bool incident=!selectedId.isEmpty() && (e.from==selectedId || e.to==selectedId ||
                         memberGroup.value(e.from)==selectedId || memberGroup.value(e.to)==selectedId ||
                         (cards.value(e.from) && cards.value(e.from)->isSelected()) ||
                         (cards.value(e.to) && cards.value(e.to)->isSelected()));
            const bool allGreen=greenLinks->isChecked() && !connectionsOnly->isChecked() && incident;
            const QColor source=allGreen?QColor(75,237,141):QColor(226,105,99);
            const QColor target=allGreen?QColor(75,237,141):QColor(93,207,131);
            QLinearGradient paint(penFrom,penTo);
            paint.setColorAt(0,source);
            paint.setColorAt(1,target);
            e.path->setPen(QPen(QBrush(paint),allGreen?2.4:(incident?1.9:1.5)));
            e.arrow->setBrush(target);
        }
    };
    // Recompute world backplanes from CURRENT card coordinates, not from the
    // last layout pass. Moving a group changes its outer bounds immediately;
    // changing world filters rebuilds these rectangles from visible cards.
    const auto resizeWorldBands=[&](bool updateScrollArea) {
        for (auto it=worldBands.cbegin();it!=worldBands.cend();++it) {
            const QString world=it.key();
            QRectF bounds;
            bool found=false;
            for (auto card=cards.cbegin();card!=cards.cend();++card) {
                if (card.value()->parentItem())continue; // mini-cards are in their group frame
                const int index=graph.byId.value(card.key(),-1);
                const QString cardWorld=index>=0 ? graph.nodes.at(index).world
                                                  : groups.value(card.key()).world;
                if (cardWorld!=world)continue;
                bounds=found?bounds.united(card.value()->sceneBoundingRect())
                            :card.value()->sceneBoundingRect();
                found=true;
            }
            if (!found)continue;
            const QRectF old=it.value()->rect();
            const QRectF next(bounds.left()-18,bounds.top()-52,
                              qMax(qreal(2030),bounds.width()+36),
                              qMax(qreal(160),bounds.height()+104));
            if (old!=next) {
                it.value()->setRect(next);
                if (worldHeaders.contains(world))
                    worldHeaders.value(world)->setPos(next.left()+20,next.top()+8);
            }
        }
        if (updateScrollArea)
            scene->setSceneRect(scene->itemsBoundingRect().adjusted(-80,-80,80,80));
        view->viewport()->update();
    };
    std::function<void()> redraw;
    redraw=[&]() {
        QSignalBlocker blocker(scene);
        cards.clear();groupTitles.clear();worldBands.clear();worldHeaders.clear();edges.clear();
        scene->clear();
        const QString selectedWorld=worldSelect->currentData().toString();
        const QStringList worlds=selectedWorld.isEmpty()?graph.worlds:QStringList{selectedWorld};
        FlowGraph display=groupLayoutGraph(graph,groups,memberGroup,layout.embeddedArrays);
        qreal laneTop=20;
        for (const QString &world:worlds) {
            QVector<int> columns[6];
            for (int i=0;i<display.nodes.size();++i)
                if (display.nodes.at(i).world==world)
                    columns[qBound(0,display.nodes.at(i).column,5)].append(i);
            int maxCount=1;
            for (const auto &col:columns)maxCount=qMax(maxCount,int(col.size()));
            const qreal laneHeight=105+maxCount*118;
            QRectF worldBounds;
            bool worldHasCards=false;
            for (int col=0;col<6;++col) {
                for (int j=0;j<columns[col].size();++j) {
                    const FlowNode &n=display.nodes.at(columns[col].at(j));
                    const bool isGroup=groups.contains(n.id);
                    const FlowGroup g=isGroup ? groups.value(n.id) : FlowGroup();
                    const qreal x=30+col*335,y=laneTop+52+j*118;
                    auto *card=new FlowCardItem(n.id);
                    const int rows=(g.members.size()+1)/2;
                    QHash<QString,QPointF> miniPositions;
                    QStringList embeddedIds;
                    if (isGroup && !g.automatic) {
                        for (auto it=layout.embeddedArrays.cbegin();it!=layout.embeddedArrays.cend();++it)
                            if (it.value()==g.id && groups.contains(it.key()) && groups.value(it.key()).automatic &&
                                groups.value(it.key()).world==g.world)
                                embeddedIds.append(it.key());
                        embeddedIds.sort();
                    }
                    if (isGroup && g.expanded && !g.automatic) {
                        // Layout the manual group's INTERNAL graph, not a blind
                        // list. Directed steps advance right; unrelated branches
                        // occupy distinct rows. Cycles are visited once only.
                        QSet<QString> members;
                        QHash<QString,int> incoming;
                        QHash<QString,QStringList> onward;
                        for (const QString &id:g.members) {members.insert(id);incoming.insert(id,0);}
                        for (const FlowEdge &edge:graph.edges) {
                            if (!members.contains(edge.from) || !members.contains(edge.to) || edge.from==edge.to)continue;
                            onward[edge.from].append(edge.to);
                            incoming[edge.to]=incoming.value(edge.to)+1;
                        }
                        QHash<QString,int> depths;
                        QStringList queue;
                        for (const QString &id:g.members)
                            if (incoming.value(id)==0) {depths.insert(id,0);queue.append(id);}
                        for (int pos=0;pos<g.members.size();) {
                            if (queue.isEmpty()) {
                                // A wholly cyclic component has no source.
                                for (const QString &id:g.members) {
                                    if (!depths.contains(id)) {depths.insert(id,0);queue.append(id);break;}
                                }
                            }
                            if (queue.isEmpty())break;
                            for (int q=0;q<queue.size();++q) {
                                const QString from=queue.at(q);
                                for (const QString &to:onward.value(from)) {
                                    if (depths.contains(to))continue;
                                    depths.insert(to,qMin(4,depths.value(from)+1));
                                    queue.append(to);
                                }
                            }
                            pos=depths.size();
                            queue.clear();
                        }
                        QHash<int,int> countByColumn;
                        for (const QString &id:g.members) {
                            const int rank=depths.value(id,0);
                            const int row=countByColumn.value(rank,0);
                            countByColumn.insert(rank,row+1);
                            const QPointF initial(24+rank*224,88+row*88);
                            miniPositions.insert(id,layout.memberPositions.value(g.id).value(id,initial));
                        }
                        // Array-group cards occupy their own local frame. Their
                        // constituent cards remain inside, not flattened.
                        qreal nextRow=88;
                        for (const QPointF &existing:miniPositions)
                            nextRow=qMax(nextRow,existing.y()+88);
                        for (const QString &embeddedId:embeddedIds) {
                            const QPointF initial(24,nextRow);
                            const QPointF position=layout.memberPositions.value(g.id).value(embeddedId,initial);
                            miniPositions.insert(embeddedId,position);
                            nextRow=qMax(nextRow,position.y()+88);
                        }
                    }
                    if (isGroup) {
                        card->setGroup(true);
                        qreal width=270,height=70;
                        if (g.expanded && g.automatic) {width=550;height=88+rows*82;}
                        if (g.expanded && !g.automatic) {
                            width=280;height=170;
                            for (auto it=miniPositions.cbegin();it!=miniPositions.cend();++it) {
                                const bool nested=groups.contains(it.key());
                                const FlowGroup inner=groups.value(it.key());
                                const int nestedRows=(inner.members.size()+1)/2;
                                width=qMax(width,it.value().x()+(nested && inner.expanded ? 550 : 224)+24);
                                height=qMax(height,it.value().y()+(nested && inner.expanded ? 88+nestedRows*82 : 88)+24);
                            }
                        }
                        card->setRect(0,0,width,height);
                    }
                    scene->addItem(card);
                    card->setSnapToGrid(layout.snapToGrid);
                    card->setPen(QPen(isGroup && g.automatic ? theme.accent : cardBorder));
                    card->setBrush(QBrush(isGroup ? (g.automatic ? arrayBackground : groupBackground) : cardBackground));
                    card->setPos(savedPositions.value(n.id,QPointF(x,y)));
                    card->setZValue(2);
                    card->setToolTip(isGroup?QObject::tr("Click +/- to expand or collapse. Drag this group to move its contents."):n.description);
                    auto *stripe=scene->addRect(0,0,7,isGroup?70:70,Qt::NoPen,QBrush(isGroup?theme.accent:nodeColour(n.kind,n.problem,theme)));
                    stripe->setParentItem(card);stripe->setPos(0,0);
                    stripe->setAcceptedMouseButtons(Qt::NoButton);
                    if (isGroup) {
                        QFont toggleFont(QStringLiteral("Sans Serif"));
                        toggleFont.setPixelSize(14);
                        toggleFont.setBold(true);
                        auto *toggle=scene->addSimpleText(g.expanded?QStringLiteral("−"):QStringLiteral("+"),toggleFont);
                        toggle->setParentItem(card);toggle->setPos(14,0);toggle->setBrush(theme.brightText);
                        toggle->setAcceptedMouseButtons(Qt::NoButton);
                        auto *kind=scene->addSimpleText(g.automatic?QStringLiteral("ARRAY GROUP"):QStringLiteral("LOGIC GROUP"),QFont(QStringLiteral("Sans Serif"),8,QFont::Bold));
                        kind->setParentItem(card);kind->setPos(45,4);kind->setBrush(theme.text);
                        kind->setAcceptedMouseButtons(Qt::NoButton);
                        if (g.automatic) {
                            auto *name=scene->addSimpleText(brief(g.title,42),QFont(QStringLiteral("Sans Serif"),10,QFont::DemiBold));
                            name->setParentItem(card);name->setPos(14,26);name->setBrush(theme.brightText);
                            name->setAcceptedMouseButtons(Qt::NoButton);
                        } else {
                            auto *name=new FlowGroupTitleItem(g.title,card,theme.brightText);
                            name->setPos(11,20);
                            name->setTextWidth(qMax(qreal(230),card->rect().width()-22));
                            groupTitles.insert(g.id,name);
                            const QString id=g.id;
                            name->onRenamed=[&,id](const QString &title) {
                                // The current item is destroyed during redraw; defer
                                // that work until after its focus event returns.
                                QMetaObject::invokeMethod(&dialog,[&,id,title]() {
                                    for (FlowGroup &manual:layout.manualGroups)
                                        if (manual.id==id)manual.title=title;
                                    if (groups.contains(id))groups[id].title=title;
                                    redraw();savePositions();
                                },Qt::QueuedConnection);
                            };
                        }
                        auto *count=scene->addSimpleText(
                            embeddedIds.isEmpty() ? QObject::tr("%1 cards").arg(g.members.size())
                                                  : QObject::tr("%1 cards + %2 arrays")
                                                      .arg(g.members.size()).arg(embeddedIds.size()),
                            QFont(QStringLiteral("Sans Serif"),8));
                        count->setParentItem(card);count->setPos(14,48);count->setBrush(theme.mutedText);
                        count->setAcceptedMouseButtons(Qt::NoButton);
                        if (g.expanded) {
                            for (int i=0;i<g.members.size();++i) {
                                const QString &memberId=g.members.at(i);
                                const int index=graph.byId.value(memberId,-1);
                                if (index<0)continue;
                                const FlowNode &member=graph.nodes.at(index);
                                auto *child=new FlowCardItem(member.id);
                                child->setParentItem(card);
                                child->setSnapToGrid(layout.snapToGrid);
                                if (!g.automatic) {
                                    child->setRect(0,0,200,60);
                                    child->setPos(miniPositions.value(memberId));
                                    child->setFlag(QGraphicsItem::ItemIsMovable,true);
                                } else {
                                    // Automatic array groups stay as simple lists.
                                    child->setPos(16+(i%2)*272,80+(i/2)*88);
                                    child->setFlag(QGraphicsItem::ItemIsMovable,false);
                                }
                                child->setZValue(3); // above embedded wires
                                child->setBrush(miniBackground);
                                child->setPen(QPen(cardBorder));
                                child->setToolTip(member.description);
                                auto *label=scene->addSimpleText(brief(member.title,g.automatic?34:26),QFont(QStringLiteral("Sans Serif"),9,QFont::DemiBold));
                                label->setParentItem(child);label->setPos(12,5);label->setBrush(theme.brightText);
                                label->setAcceptedMouseButtons(Qt::NoButton);
                                auto *type=scene->addSimpleText(brief(member.kind,32),QFont(QStringLiteral("Sans Serif"),8));
                                type->setParentItem(child);type->setPos(12,29);type->setBrush(theme.mutedText);
                                type->setAcceptedMouseButtons(Qt::NoButton);
                                const QPixmap art=flowArtworkIcon(member,projectRoot,artworkSheets);
                                if (!art.isNull()) {
                                    auto *thumbnail=new QGraphicsPixmapItem(art,child);
                                    thumbnail->setPos(child->rect().right()-20,child->rect().bottom()-20);
                                    thumbnail->setAcceptedMouseButtons(Qt::NoButton);
                                    thumbnail->setToolTip(QObject::tr("Artwork: %1, frame %2")
                                        .arg(member.artPath).arg(member.artFrame));
                                }
                                cards.insert(memberId,child);
                            }
                            // A manually placed automatic array group stays a
                            // selectable, movable container inside this logic group.
                            for (const QString &embeddedId:embeddedIds) {
                                const FlowGroup inner=groups.value(embeddedId);
                                const int nestedRows=(inner.members.size()+1)/2;
                                auto *sub=new FlowCardItem(embeddedId);
                                sub->setParentItem(card);
                                sub->setGroup(true);
                                sub->setSnapToGrid(layout.snapToGrid);
                                // Only these nested ARRAY GROUP cards can be
                                // dragged outside their owner's frame.
                                sub->setAllowLeaveParent(true);
                                sub->setRect(0,0,inner.expanded?550:270,
                                             inner.expanded?88+nestedRows*82:70);
                                sub->setPos(miniPositions.value(embeddedId));
                                sub->setZValue(3);
                                sub->setBrush(nestedBackground);
                                sub->setPen(QPen(theme.accent));
                                sub->setToolTip(QObject::tr("Array group nested in %1; click +/- to expand it, or drag outside the parent to detach.").arg(g.title));
                                auto *subtitle=new QGraphicsSimpleTextItem(brief(inner.title,35),sub);
                                subtitle->setPos(14,26);
                                subtitle->setBrush(theme.brightText);
                                subtitle->setAcceptedMouseButtons(Qt::NoButton);
                                auto *subtype=new QGraphicsSimpleTextItem(QStringLiteral("ARRAY GROUP"),sub);
                                subtype->setPos(45,4);
                                subtype->setBrush(theme.text);
                                subtype->setAcceptedMouseButtons(Qt::NoButton);
                                auto *subCount=new QGraphicsSimpleTextItem(
                                    QObject::tr("%1 cards").arg(inner.members.size()),sub);
                                subCount->setPos(14,48);
                                subCount->setBrush(theme.mutedText);
                                subCount->setAcceptedMouseButtons(Qt::NoButton);
                                auto *subToggle=new QGraphicsSimpleTextItem(inner.expanded?QStringLiteral("−"):QStringLiteral("+"),sub);
                                QFont subFont(QStringLiteral("Sans Serif"));
                                subFont.setPixelSize(14);subFont.setBold(true);
                                subToggle->setFont(subFont);
                                subToggle->setPos(14,0);
                                subToggle->setBrush(theme.brightText);
                                subToggle->setAcceptedMouseButtons(Qt::NoButton);
                                cards.insert(embeddedId,sub);
                                if (inner.expanded) {
                                    for (int i=0;i<inner.members.size();++i) {
                                        const QString memberId=inner.members.at(i);
                                        const int index=graph.byId.value(memberId,-1);
                                        if (index<0)continue;
                                        const FlowNode &member=graph.nodes.at(index);
                                        auto *mini=new FlowCardItem(memberId);
                                        mini->setParentItem(sub);
                                        mini->setSnapToGrid(layout.snapToGrid);
                                        mini->setFlag(QGraphicsItem::ItemIsMovable,false);
                                        mini->setPos(16+(i%2)*272,80+(i/2)*88);
                                        mini->setZValue(3);
                                        mini->setBrush(miniBackground);
                                        mini->setPen(QPen(cardBorder));
                                        mini->setToolTip(member.description);
                                        auto *label=new QGraphicsSimpleTextItem(brief(member.title,34),mini);
                                        label->setPos(12,5);label->setBrush(theme.brightText);
                                        label->setAcceptedMouseButtons(Qt::NoButton);
                                        auto *kind=new QGraphicsSimpleTextItem(brief(member.kind,32),mini);
                                        kind->setPos(12,29);kind->setBrush(theme.mutedText);
                                        kind->setAcceptedMouseButtons(Qt::NoButton);
                                        cards.insert(memberId,mini);
                                    }
                                }
                                sub->onToggle=[&](const QString &id) {
                                    QMetaObject::invokeMethod(&dialog,[&,id]() {
                                        if (!groups.contains(id))return;
                                        const bool expanded=!groups.value(id).expanded;
                                        groups[id].expanded=expanded;
                                        layout.expanded.insert(id,expanded);
                                        redraw();savePositions();
                                    },Qt::QueuedConnection);
                                };
                            }
                        }
                        card->onToggle=[&](const QString &id) {
                            // Defer scene destruction until after Qt dispatches the click.
                            QMetaObject::invokeMethod(&dialog,[&,id]() {
                                if (!groups.contains(id))return;
                                const bool expanded=!groups.value(id).expanded;
                                groups[id].expanded=expanded;
                                layout.expanded.insert(id,expanded);
                                redraw();savePositions();
                            },Qt::QueuedConnection);
                        };
                    } else {
                        auto *kind=scene->addSimpleText(n.kind.toUpper(),QFont(QStringLiteral("Sans Serif"),8,QFont::Bold));
                        kind->setParentItem(card);kind->setPos(36,4);kind->setBrush(theme.mutedText);
                        kind->setAcceptedMouseButtons(Qt::NoButton);
                        auto *symbol=scene->addPixmap(flowCardIcon(n.kind,n.problem,theme));
                        symbol->setParentItem(card);symbol->setPos(15,4);
                        symbol->setAcceptedMouseButtons(Qt::NoButton);
                        auto *name=scene->addSimpleText(brief(n.title,36),QFont(QStringLiteral("Sans Serif"),10,QFont::DemiBold));
                        name->setParentItem(card);name->setPos(14,24);name->setBrush(theme.brightText);
                        name->setAcceptedMouseButtons(Qt::NoButton);
                        const QPixmap art=flowArtworkIcon(n,projectRoot,artworkSheets);
                        if (!art.isNull()) {
                            auto *thumbnail=new QGraphicsPixmapItem(art,card);
                            thumbnail->setPos(card->rect().right()-20,card->rect().bottom()-20);
                            thumbnail->setAcceptedMouseButtons(Qt::NoButton);
                            thumbnail->setToolTip(QObject::tr("Artwork: %1, frame %2")
                                .arg(n.artPath).arg(n.artFrame));
                        }
                    }
                    cards.insert(n.id,card);
                    const QRectF bounds=card->sceneBoundingRect();
                    worldBounds=worldHasCards?worldBounds.united(bounds):bounds;
                    worldHasCards=true;
                }
            }
            const QRectF bandRect=worldHasCards
                ? QRectF(worldBounds.left()-18,worldBounds.top()-52,
                         qMax(qreal(2030),worldBounds.width()+36),
                         qMax(laneHeight,worldBounds.height()+104))
                : QRectF(12,laneTop,2030,laneHeight);
            auto *band=scene->addRect(bandRect,QPen(theme.border),QBrush(theme.alternateBackground));
            band->setZValue(-5);band->setAcceptedMouseButtons(Qt::NoButton);
            worldBands.insert(world,band);
            auto *header=scene->addSimpleText(world.toUpper());
            worldHeaders.insert(world,header);
            header->setBrush(theme.text);
            header->setPos(bandRect.left()+20,bandRect.top()+8);
            header->setAcceptedMouseButtons(Qt::NoButton);
            laneTop=qMax(laneTop+laneHeight+18,bandRect.bottom()+18);
        }
        QHash<QString,int> sharedLines;
        const auto visibleEndpoint=[&](const QString &id) -> QString {
            const QString groupId=memberGroup.value(id);
            if (groupId.isEmpty())return id;
            const FlowGroup group=groups.value(groupId);
            if (group.automatic) {
                const QString outer=layout.embeddedArrays.value(groupId);
                if (groups.contains(outer) && groups.value(outer).world==group.world &&
                    groups.value(outer).expanded)
                    return groupId; // A nested automatic array is still a group.
                return groups.contains(outer) && groups.value(outer).world==group.world
                    ? outer : groupId;
            }
            return group.expanded?id:groupId;
        };
        for (const FlowEdge &e:graph.edges) {
            const QString from=visibleEndpoint(e.from);
            const QString to=visibleEndpoint(e.to);
            if (from==to || !cards.contains(from) || !cards.contains(to))continue;
            const QString pair=from+QChar(0x1f)+to;
            if (sharedLines.contains(pair)) {
                EdgeArt &existing=edges[sharedLines.value(pair)];
                existing.path->setToolTip(existing.path->toolTip()+QStringLiteral("\n")+e.label);
                continue;
            }
            // Lines leaving an EXPANDED manual group are children of that
            // group. They stay above its background and below its mini cards.
            // All other links remain behind the regular top-level cards.
            QGraphicsItem *wireParent=nullptr;
            if (cards.value(from) && cards.value(from)->parentItem())
                wireParent=cards.value(from)->parentItem();
            else if (cards.value(to) && cards.value(to)->parentItem())
                wireParent=cards.value(to)->parentItem();
            FlowWireItem *line=new FlowWireItem(wireParent);
            if (!wireParent)scene->addItem(line);
            QGraphicsPolygonItem *arrowItem=new QGraphicsPolygonItem(wireParent);
            if (!wireParent)scene->addItem(arrowItem);
            line->setPen(QPen(theme.border,1.5));
            arrowItem->setPen(Qt::NoPen);
            arrowItem->setBrush(QColor(93,207,131));
            arrowItem->setAcceptedMouseButtons(Qt::NoButton);
            arrowItem->setData(1,QStringLiteral("flow-wire"));
            line->setZValue(wireParent?1:-1);
            arrowItem->setZValue(wireParent?2:0);
            line->setToolTip(e.label+QStringLiteral("\nClick to select both connected cards"));
            const QString first=from,second=to,linkLabel=e.label;
            line->onClicked=[&,first,second,linkLabel]() {
                // Click selection is separate from rubber-band selection: wires
                // are NOT selectable graphics items, so drag-to-group is safe.
                {
                    QSignalBlocker blocker(scene);
                    scene->clearSelection();
                    if (cards.value(first))cards.value(first)->setSelected(true);
                    if (cards.value(second))cards.value(second)->setSelected(true);
                }
                selectedId=first;
                setDetails();
                const auto titleOf=[&](const QString &id) -> QString {
                    const int index=graph.byId.value(id,-1);
                    if (index>=0)return graph.nodes.at(index).title;
                    return groups.contains(id)?groups.value(id).title:id;
                };
                details->appendPlainText(QObject::tr("\nSelected connection: %1\n%2 -> %3")
                    .arg(linkLabel,titleOf(first),titleOf(second)));
                refreshHighlight();
            };
            sharedLines.insert(pair,edges.size());
            edges.append({from,to,e.label,line,arrowItem});
        }
        for (auto it=cards.begin();it!=cards.end();++it) {
            auto *card=static_cast<FlowCardItem *>(it.value());
            // Array members stay fixed; manual-group mini cards can be moved.
            if (card->parentItem() && !layout.embeddedArrays.contains(it.key()) &&
                (!memberGroup.contains(it.key()) ||
                 groups.value(memberGroup.value(it.key())).automatic))continue;
            card->onMoved=[&]() {
                refreshEdges();
                resizeWorldBands(false);
            };
            card->onDropped=[&](const QString &id,const QPointF &position,const QPointF &releaseScenePos) {
                // Root cards may be dropped INTO logic groups. Nested array
                // groups may also be dragged OUT of their current parent;
                // ordinary mini cards remain group-local.
                auto *moved=cards.value(id,nullptr);
                QString dropTarget;
                QPointF childPosition;
                const bool rootCard=moved && !moved->parentItem();
                const bool mayNest=rootCard && (graph.byId.contains(id) ||
                                   (groups.contains(id) && groups.value(id).automatic &&
                                    !layout.embeddedArrays.contains(id)));
                if (mayNest) {
                    const QRectF source=moved->sceneBoundingRect();
                    const QString world=graph.byId.contains(id)
                        ? graph.nodes.at(graph.byId.value(id)).world : groups.value(id).world;
                    // A large expanded array can cover a small collapsed
                    // logic group without its centre entering the header.
                    // Require substantial overlap, not a grazing corner.
                    qreal bestOverlap=0;
                    for (auto it=groups.cbegin();it!=groups.cend();++it) {
                        if (it.value().automatic || it.value().world!=world || it.key()==id ||
                            memberGroup.contains(id))continue;
                        auto *target=cards.value(it.key(),nullptr);
                        if (!target || target->parentItem())continue;
                        const QRectF targetRect=target->sceneBoundingRect();
                        const QRectF overlap=targetRect.intersected(source);
                        const qreal smallArea=qMin(source.width()*source.height(),
                                                   targetRect.width()*targetRect.height());
                        const qreal score=smallArea>0
                            ? overlap.width()*overlap.height()/smallArea : 0;
                        if (score<0.35 || score<=bestOverlap)continue;
                        bestOverlap=score;
                        dropTarget=it.key();
                        childPosition=target->mapFromScene(source.topLeft());
                        if (!it.value().expanded || childPosition.y()<80) {
                            qreal nextRow=88;
                            for (const QPointF &existing:layout.memberPositions.value(it.key()))
                                nextRow=qMax(nextRow,existing.y()+88);
                            childPosition=QPointF(24,nextRow);
                        }
                        childPosition.setX(qMax(qreal(16),childPosition.x()));
                        childPosition.setY(qMax(qreal(80),childPosition.y()));
                    }
                }
                bool detachNestedArray=false;
                QString oldParent;
                QPointF detachedScenePosition;
                if (moved && moved->parentItem() && layout.embeddedArrays.contains(id)) {
                    oldParent=layout.embeddedArrays.value(id);
                    auto *frame=cards.value(oldParent,nullptr);
                    // The mouse leaving the logic frame is the deliberate
                    // drag-out gesture. Check BEFORE resizing the frame, or
                    // the parent would grow to swallow the departing array.
                    // The 12px margin avoids accidental detach at an edge.
                    detachNestedArray=frame &&
                        !frame->sceneBoundingRect().adjusted(-12,-12,12,12).contains(releaseScenePos);
                    if (detachNestedArray) {
                        detachedScenePosition=moved->scenePos();
                    } else {
                        layout.memberPositions[oldParent].insert(id,position);
                        if (frame) {
                            QRectF rect=frame->rect();
                            rect.setWidth(qMax(rect.width(),position.x()+moved->rect().width()+24));
                            rect.setHeight(qMax(rect.height(),position.y()+moved->rect().height()+24));
                            frame->setRect(rect);
                        }
                    }
                } else if (memberGroup.contains(id) && groups.contains(memberGroup.value(id)) &&
                    !groups.value(memberGroup.value(id)).automatic) {
                    const QString owner=memberGroup.value(id);
                    auto *frame=cards.value(owner,nullptr);
                    if (frame) {
                        // Let the mini-canvas grow when a member is dragged
                        // further right/down. The frame itself stays movable.
                        QRectF rect=frame->rect();
                        rect.setWidth(qMax(rect.width(),position.x()+224));
                        rect.setHeight(qMax(rect.height(),position.y()+88));
                        frame->setRect(rect);
                    }
                    // Preserve any multi-selection moves of mini cards.
                    for (const QString &member:groups.value(owner).members) {
                        auto *miniCard=cards.value(member,nullptr);
                        if (miniCard && miniCard->parentItem()==frame)
                            layout.memberPositions[owner].insert(member,miniCard->pos());
                    }
                } else {
                    savedPositions.insert(id,position);
                }
                // Qt only emits mouseRelease for the actively dragged item
                // when a selection of multiple cards is moved together.
                for (auto current=cards.cbegin();current!=cards.cend();++current)
                    if (!current.value()->parentItem())
                        savedPositions.insert(current.key(),current.value()->pos());
                refreshEdges();
                resizeWorldBands(true);
                if (detachNestedArray) {
                    // A nested ARRAY GROUP becomes an independent root card.
                    // Preserve scene coordinates (not its old parent-local
                    // position), all array members, links and expand state.
                    // Redraw only AFTER Qt finishes the mouse release event.
                    QMetaObject::invokeMethod(&dialog,[&,id,oldParent,detachedScenePosition]() {
                        if (layout.embeddedArrays.value(id)!=oldParent)return;
                        layout.embeddedArrays.remove(id);
                        layout.memberPositions[oldParent].remove(id);
                        savedPositions.insert(id,detachedScenePosition);
                        buildFlowGroups(graph,layout,groups,memberGroup);
                        redraw();savePositions();
                    },Qt::QueuedConnection);
                } else if (!dropTarget.isEmpty()) {
                    // The dragged item is processing mouseRelease; Qt must
                    // finish that event before we destroy/rebuild the scene.
                    QMetaObject::invokeMethod(&dialog,[&,id,dropTarget,childPosition]() {
                        if (!groups.contains(dropTarget) || groups.value(dropTarget).automatic)return;
                        if (groups.contains(id) && groups.value(id).automatic) {
                            layout.embeddedArrays.insert(id,dropTarget);
                        } else if (graph.byId.contains(id) && !memberGroup.contains(id)) {
                            for (FlowGroup &manual:layout.manualGroups)
                                if (manual.id==dropTarget && !manual.members.contains(id))
                                    manual.members.append(id);
                        } else return;
                        layout.memberPositions[dropTarget].insert(id,childPosition);
                        layout.expanded.insert(dropTarget,true);
                        buildFlowGroups(graph,layout,groups,memberGroup);
                        redraw();savePositions();
                    },Qt::QueuedConnection);
                } else savePositions();
            };
        }
        refreshEdges();
        resizeWorldBands(true);
        selectedId.clear();setDetails();refreshHighlight();
        status->setText(QObject::tr("Design time | %1 nodes | %2 visible cards | %3 groups | %4 links | %5 unresolved")
                        .arg(graph.nodes.size()).arg(cards.size()).arg(groups.size())
                        .arg(edges.size()).arg(graph.diagnostics.size()));
    };
    const auto reloadGraph=[&]() {
        artworkSheets.clear();
        const QString previous=worldSelect->currentData().toString();
        graph=loadGraph(projectRoot);
        buildFlowGroups(graph,layout,groups,memberGroup);
        worldSelect->blockSignals(true);
        worldSelect->clear();worldSelect->addItem(QObject::tr("All Worlds"),QString());
        for (const QString &name:graph.worlds)worldSelect->addItem(name,name);
        const int index=worldSelect->findData(previous);
        worldSelect->setCurrentIndex(qMax(0,index));
        worldSelect->blockSignals(false);
        redraw();
        if (graph.worlds.isEmpty()) {
            details->setPlainText(QObject::tr("No readable .sbgm design files in:\n%1").arg(projectRoot));
        } else if (!graph.diagnostics.isEmpty()) {
            details->setPlainText(QObject::tr("Design warnings (%1):\n\n%2\n\nClick a card for details.")
                                       .arg(graph.diagnostics.size()).arg(graph.diagnostics.join('\n')));
        }
    };
    QObject::connect(scene,&QGraphicsScene::selectionChanged,&dialog,[&]() {
        selectedId.clear();
        for (QGraphicsItem *item:scene->selectedItems()) {
            const QString id=item->data(0).toString();
            if (cards.contains(id)) {selectedId=id;break;}
        }
        setDetails();refreshHighlight();
    });
    QObject::connect(worldSelect,qOverload<int>(&QComboBox::currentIndexChanged),&dialog,[&](int){
        redraw();
        const QString world=worldSelect->currentData().toString();
        if (!world.isEmpty() && worldBands.contains(world)) {
            const QRectF band=worldBands.value(world)->rect();
            view->centerOn(QPointF(band.left()+qMin(qreal(420),band.width()/2),
                                   band.top()+qMin(qreal(170),band.height()/2)));
        }
        // Scene contents have been replaced; repaint right away rather than
        // depending on the next mouse-wheel/scroll event to refresh the view.
        view->viewport()->update();
    });
    QObject::connect(search,&QLineEdit::textChanged,&dialog,[&](const QString &){refreshHighlight();});
    QObject::connect(connectionsOnly,&QCheckBox::toggled,&dialog,[&](bool enabled){
        greenLinks->setEnabled(!enabled);
        refreshHighlight();
    });
    QObject::connect(greenLinks,&QCheckBox::toggled,&dialog,[&](bool){refreshHighlight();});
    QObject::connect(reload,&QPushButton::clicked,&dialog,reloadGraph);
    QObject::connect(zoomIn,&QPushButton::clicked,&dialog,[&](){view->zoom(1.25);});
    QObject::connect(zoomOut,&QPushButton::clicked,&dialog,[&](){view->zoom(0.8);});
    QObject::connect(actualSize,&QPushButton::clicked,&dialog,[&](){
        view->resetTransform();
    });
    QObject::connect(fit,&QPushButton::clicked,&dialog,[&](){
        const QRectF rect=scene->itemsBoundingRect();
        if (rect.isValid() && !rect.isEmpty())
            view->fitInView(rect.adjusted(-40,-40,40,40),Qt::KeepAspectRatio);
    });
    QObject::connect(clean,&QPushButton::clicked,&dialog,[&](){
        savedPositions.clear();
        redraw();
        savePositions();
        // The previous view may have been parked far to the right of a spread
        // graph. Return to the beginning of the original compact layout.
        view->resetTransform();
        view->scale(0.90,0.90);
        view->centerOn(QPointF(160,150));
    });
    QObject::connect(spread,&QPushButton::clicked,&dialog,[&](){
        savedPositions=flowLeftToRightPositions(groupLayoutGraph(graph,groups,memberGroup,layout.embeddedArrays));
        redraw();
        savePositions();
        // Keep the graph readable after switching from a tiny Fit Graph zoom.
        // Use the chosen world's root as the starting point of the new layout.
        const QString world=worldSelect->currentData().toString().isEmpty()
                                ? graph.worlds.value(0) : worldSelect->currentData().toString();
        const QPointF start=savedPositions.value(world+QStringLiteral("/world"),QPointF(30,75));
        view->resetTransform();
        view->scale(0.90,0.90);
        view->centerOn(start+QPointF(125,35));
    });
    const auto makeGroup=[&]() {
        QStringList members;
        QString world;
        for (QGraphicsItem *item:scene->selectedItems()) {
            const QString id=item->data(0).toString();
            const int idx=graph.byId.value(id,-1);
            if (idx<0)continue; // Do not nest group containers.
            const QString w=graph.nodes.at(idx).world;
            if (!world.isEmpty() && world!=w) {
                QMessageBox::information(&dialog,QObject::tr("Logic Flow"),
                    QObject::tr("Select cards from one world to create a group."));
                return;
            }
            world=w;
            if (!members.contains(id))members.append(id);
        }
        if (members.size()<2) {
            QMessageBox::information(&dialog,QObject::tr("Logic Flow"),
                QObject::tr("Select at least two cards (drag a rectangle) and press Ctrl+G."));
            return;
        }
        for (const QString &member:members) {
            if (memberGroup.contains(member)) {
                QMessageBox::information(&dialog,QObject::tr("Logic Flow"),
                    QObject::tr("Ungroup the existing manual group first. Nested groups are not supported."));
                return;
            }
        }
        bool ok=false;
        const QString title=QInputDialog::getText(&dialog,QObject::tr("Group Logic Cards"),
            QObject::tr("Group name:"),QLineEdit::Normal,QObject::tr("New Logic Group"),&ok).trimmed();
        if (!ok || title.isEmpty())return;
        int serial=1;
        QString id;
        do {id=QStringLiteral("flow-group/manual/")+world+QStringLiteral("/")+QString::number(serial++);}
        while (groups.contains(id) || std::any_of(layout.manualGroups.cbegin(),layout.manualGroups.cend(),
            [&](const FlowGroup &g){return g.id==id;}));
        // Put the new group where the selected cards were, not at the origin.
        QRectF bounds;
        bool first=true;
        for (const QString &member:members) {
            const auto *card=cards.value(member,nullptr);
            if (!card)continue;
            bounds=first?card->sceneBoundingRect():bounds.united(card->sceneBoundingRect());
            first=false;
        }
        FlowGroup group;
        group.id=id;group.world=world;group.title=title;group.members=members;
        layout.manualGroups.append(group);
        layout.expanded.insert(id,false);
        savedPositions.insert(id,bounds.topLeft());
        buildFlowGroups(graph,layout,groups,memberGroup);
        redraw();savePositions();
    };
    // F2 edits the title ON the selected manual-group card. It also works
    // after selecting one of its children inside the expanded mini-graph.
    const auto renameSelectedGroup=[&]() {
        const QString id=groups.contains(selectedId) ? selectedId : memberGroup.value(selectedId);
        if (!groups.contains(id) || groups.value(id).automatic)return;
        FlowGroupTitleItem *title=groupTitles.value(id,nullptr);
        if (!title)return;
        view->ensureVisible(title);
        title->beginEditing();
    };
    const auto ungroup=[&]() {
        // A selected mini card identifies its containing manual group too.
        const QString id=groups.contains(selectedId) ? selectedId : memberGroup.value(selectedId);
        if (!groups.contains(id) || groups.value(id).automatic) {
            QMessageBox::information(&dialog,QObject::tr("Logic Flow"),
                QObject::tr("Select a manual group or one of its mini cards to ungroup it. Automatic array groups stay available."));
            return;
        }
        // Restore moved mini cards to their present scene positions when the
        // frame is dissolved, instead of teleporting them to an old layout.
        auto *frame=cards.value(id,nullptr);
        if (frame && groups.value(id).expanded) {
            for (const QString &member:groups.value(id).members) {
                auto *mini=cards.value(member,nullptr);
                if (mini && mini->parentItem()==frame)
                    savedPositions.insert(member,mini->scenePos());
            }
        } else if (frame) {
            const auto offsets=layout.memberPositions.value(id);
            for (auto it=offsets.cbegin();it!=offsets.cend();++it)
                savedPositions.insert(it.key(),frame->pos()+it.value());
        }
        for (auto it=layout.embeddedArrays.begin();it!=layout.embeddedArrays.end();) {
            if (it.value()==id) {
                const QString arrayId=it.key();
                auto *inner=cards.value(arrayId,nullptr);
                if (inner && inner->parentItem()==frame)
                    savedPositions.insert(arrayId,inner->scenePos());
                else if (frame)
                    savedPositions.insert(arrayId,frame->pos()+
                        layout.memberPositions.value(id).value(arrayId,QPointF(24,88)));
                it=layout.embeddedArrays.erase(it);
            } else ++it;
        }
        for (int i=layout.manualGroups.size()-1;i>=0;--i)
            if (layout.manualGroups.at(i).id==id)layout.manualGroups.removeAt(i);
        savedPositions.remove(id);
        layout.memberPositions.remove(id);
        layout.expanded.remove(id);
        buildFlowGroups(graph,layout,groups,memberGroup);
        redraw();savePositions();
    };
    QObject::connect(groupButton,&QPushButton::clicked,&dialog,makeGroup);
    QObject::connect(ungroupButton,&QPushButton::clicked,&dialog,ungroup);
    QObject::connect(snapGrid,&QCheckBox::toggled,&dialog,[&](bool enabled) {
        layout.snapToGrid=enabled;
        for (auto it=cards.cbegin();it!=cards.cend();++it)
            static_cast<FlowCardItem *>(it.value())->setSnapToGrid(enabled);
        savePositions();
    });
    auto *groupShortcut=new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_G),&dialog);
    QObject::connect(groupShortcut,&QShortcut::activated,&dialog,makeGroup);
    auto *ungroupShortcut=new QShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_G),&dialog);
    QObject::connect(ungroupShortcut,&QShortcut::activated,&dialog,ungroup);
    auto *renameShortcut=new QShortcut(QKeySequence(Qt::Key_F2),&dialog);
    QObject::connect(renameShortcut,&QShortcut::activated,&dialog,renameSelectedGroup);
    QObject::connect(close,&QPushButton::clicked,&dialog,&QDialog::accept);
    reloadGraph();
    // Start with readable cards. 'Fit Graph' is optional for a whole-project overview.
    view->scale(0.90,0.90);
    view->centerOn(QPointF(430,185));
    dialog.exec();
    // IMPORTANT: the dialog (and its child scene/widgets) outlives local graph
    // state. Disconnect closures BEFORE destroying their captured references.
    // In particular QGraphicsScene::clear during QWidget teardown can emit
    // selectionChanged; the previous version left a dangling stack capture.
    QObject::disconnect(scene,nullptr,&dialog,nullptr);
    QObject::disconnect(worldSelect,nullptr,&dialog,nullptr);
    QObject::disconnect(search,nullptr,&dialog,nullptr);
    QObject::disconnect(connectionsOnly,nullptr,&dialog,nullptr);
    QObject::disconnect(greenLinks,nullptr,&dialog,nullptr);
    QObject::disconnect(reload,nullptr,&dialog,nullptr);
    QObject::disconnect(zoomIn,nullptr,&dialog,nullptr);
    QObject::disconnect(zoomOut,nullptr,&dialog,nullptr);
    QObject::disconnect(actualSize,nullptr,&dialog,nullptr);
    QObject::disconnect(fit,nullptr,&dialog,nullptr);
    QObject::disconnect(clean,nullptr,&dialog,nullptr);
    QObject::disconnect(spread,nullptr,&dialog,nullptr);
    QObject::disconnect(groupButton,nullptr,&dialog,nullptr);
    QObject::disconnect(ungroupButton,nullptr,&dialog,nullptr);
    QObject::disconnect(snapGrid,nullptr,&dialog,nullptr);
    QObject::disconnect(groupShortcut,nullptr,&dialog,nullptr);
    QObject::disconnect(ungroupShortcut,nullptr,&dialog,nullptr);
    QObject::disconnect(renameShortcut,nullptr,&dialog,nullptr);
    QObject::disconnect(close,nullptr,&dialog,nullptr);
    scene->clear();
    cards.clear();
    edges.clear();
}
