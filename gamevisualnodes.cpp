#include "gamevisualnodes.h"
#include "idetheme.h"
#include "gameadventureeditor.h"
#include "gamevisualgraphlogic.h"
#include "gamecrossworldlinks.h"
#include "gametilemap.h"

#include <QCryptographicHash>
#include <QElapsedTimer>
#include <QBrush>
#include <QColor>
#include <QContextMenuEvent>
#include <QCursor>
#include <QMap>
#include <QGraphicsItem>
#include <QPen>
#include <QFont>
#include <QDialog>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QGraphicsEllipseItem>
#include <QGraphicsPathItem>
#include <QPainterPathStroker>
#include <QPair>
#include <QGraphicsRectItem>
#include <QGraphicsProxyWidget>
#include <QComboBox>
#include <QAbstractItemView>
#include <QCheckBox>
#include <QSpinBox>
#include <QShortcut>
#include <QApplication>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QSignalBlocker>
#include <QGridLayout>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QListWidget>
#include <QLineF>
#include <QTreeWidget>
#include <QHeaderView>
#include <QAbstractItemModel>
#include <QAbstractItemView>
#include <QTreeWidgetItemIterator>
#include <QDialogButtonBox>
#include <QMenu>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QEvent>
#include <QMessageBox>
#include <QPainter>
#include <QPainterPath>
#include <QPushButton>
#include <QSaveFile>
#include <QScrollBar>
#include <QSplitter>
#include <QTextEdit>
#include <QTimer>
#include <QVBoxLayout>
#include <QWheelEvent>
#include <QCloseEvent>
#include <QShowEvent>
#include <QTransform>
#include <QVariant>
#include <QSet>
#include <QStringList>
#include <functional>
#include <algorithm>
#include <cmath>

namespace {

struct NodeLink {
    QString target;
    QString action;
};
struct NodeObject {
    QString id, name, type;
    int resourceIndex = -1;
    QVector<NodeLink> links;
    int dialogueNode = -1;
    QString dialogueMode = QStringLiteral("conversation");
    // Separate TRUE/FALSE dialogue condition. Values live only in .sbgm.
    QString toggleStateTargetId;
    QString toggleStateOperator=QStringLiteral("boolean");
    QStringList toggleStateInputIds;
    int toggleTrueDialogueNode=-1;
    int toggleFalseDialogueNode=-1;
    QVector<NodeLink> toggleTrueActions, toggleFalseActions;
    QJsonArray logicNodes; // Independent nodes owned by a Game Object in .sbgm.
    QHash<QString,QVector<NodeLink>> eventLinks; // Dedicated named event outputs on this placed object.
    int pickupKind=1; // Only key collectables (3) fire linked object actions.
    bool triggerPress=false;
    bool triggerOneShot=false;
    QString interactItemName;
    // Adventure NPC configuration in .sbgm/adventure/npcs, not sprite.gameObject.
    int npcStartNode=-1, npcDoneNode=-1, npcRadius=48;
    bool npcInitiallyVisible=true;
};

// These are the three object kinds whose targetObjectId is executed by the
// generated runtime. Other sprites can carry stale/inert target fields.
QStringList eventKinds(const QString &type) {
    if(type==QStringLiteral("breakable"))return {QStringLiteral("hit"),QStringLiteral("destroy")};
    if(type==QStringLiteral("collectable"))return {QStringLiteral("pickup")};
    if(type==QStringLiteral("hazard"))return {QStringLiteral("player_hit")};
    if(type==QStringLiteral("goto_world"))return {QStringLiteral("enter")};
    if(type==QStringLiteral("save_checkpoint"))return {QStringLiteral("save")};
    if(type==QStringLiteral("lift"))return {QStringLiteral("arrival")};
    if(type==QStringLiteral("enemy"))return {QStringLiteral("hit")};
    return {};
}
bool isEventOutput(const QString &id) {return id.startsWith(QStringLiteral("@event:"));}
QString eventKey(const QString &id) {return id.section(QLatin1Char(':'),1,1);}
QString eventOwner(const QString &id) {return id.section(QLatin1Char(':'),2);}
QString eventOutput(const QString &key,const QString &owner) {
    return QStringLiteral("@event:")+key+QLatin1Char(':')+owner;
}
QString eventLabel(const QString &key) {
    if(key==QStringLiteral("hit"))return QStringLiteral("ON HIT");
    if(key==QStringLiteral("destroy"))return QStringLiteral("ON DESTROY");
    if(key==QStringLiteral("pickup"))return QStringLiteral("ON PICKUP");
    if(key==QStringLiteral("player_hit"))return QStringLiteral("ON PLAYER HIT");
    if(key==QStringLiteral("enter"))return QStringLiteral("ON ENTER");
    if(key==QStringLiteral("save"))return QStringLiteral("ON SAVE");
    return QStringLiteral("ON ARRIVAL");
}
bool isEnemyDefeatOutput(const QString &id) {
    return id.startsWith(QStringLiteral("@enemydefeat:"));
}
QString enemyDefeatOwner(const QString &id) {
    return id.mid(QStringLiteral("@enemydefeat:").size());
}
bool isActionSource(const NodeObject &node) {
    return node.type==QStringLiteral("trigger") ||
           node.type==QStringLiteral("enemy") ||
           (node.type==QStringLiteral("collectable") && node.pickupKind==3);
}
bool isWeatherTarget(const QString &id) {
    return id.startsWith(QStringLiteral("@player_weather:"));
}
bool isPlayerCommand(const QString &id) {
    return id.startsWith(QStringLiteral("@player_time:")) ||
           id.startsWith(QStringLiteral("@player_world:"));
}
QString defaultPlayerAction(const QString &id,const QString &ordinary) {
    return isPlayerCommand(id)?QStringLiteral("enable"):ordinary;
}
bool supportedAction(const QString &action) {
    return action == QStringLiteral("enable") || action == QStringLiteral("disable") ||
           action == QStringLiteral("toggle");
}

bool readJson(const QString &fileName, QJsonObject *object, QByteArray *bytes = nullptr) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) return false;
    const QByteArray input = file.readAll();
    QJsonParseError error;
    const QJsonDocument document = QJsonDocument::fromJson(input, &error);
    if (error.error != QJsonParseError::NoError || !document.isObject()) return false;
    *object = document.object();
    if (bytes) *bytes = input;
    return true;
}

bool writeJson(const QString &fileName, const QJsonObject &object) {
    QSaveFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) return false;
    const QByteArray bytes = QJsonDocument(object).toJson(QJsonDocument::Indented);
    return file.write(bytes) == bytes.size() && file.commit();
}

// A dialogue choice is edited through a real top-level QDialog, not a popup
// embedded in a QGraphicsProxyWidget. This avoids the QGraphicsScene z-order
// clipping/stacking problem while retaining the ordinary combobox on the card.
class ConversationTreeCombo final : public QComboBox {
public:
    using QComboBox::QComboBox;
    std::function<bool(int,int*)> chooseDestination;

    void showPopup() override {
        if (!chooseDestination) {QComboBox::showPopup();return;}
        int selected=currentData().toInt();
        if (!chooseDestination(selected,&selected))return; // Cancel changes nothing.
        const int row=findData(selected);
        if (row>=0)setCurrentIndex(row); // Retains existing numeric .sbgm ID.
    }
};

class NodeFoldButton final : public QGraphicsSimpleTextItem {
public:
    std::function<void()> clicked;
    explicit NodeFoldButton(QGraphicsItem *parent) : QGraphicsSimpleTextItem(parent) {
        setAcceptedMouseButtons(Qt::LeftButton);
        setBrush(QColor(245,245,251));
        setZValue(9);
        setToolTip(QObject::tr("Expand / collapse this node"));
    }
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
        if (event->button()==Qt::LeftButton && clicked) {
            clicked();event->accept();return;
        }
        QGraphicsSimpleTextItem::mousePressEvent(event);
    }
};

class FlowGroupBox final : public QGraphicsRectItem {
public:
    std::function<void(const QPointF &)> moved;
    std::function<void()> dragFinished;
    std::function<void()> foldClicked;
    explicit FlowGroupBox(const QString &title,const QColor &panelFill) : QGraphicsRectItem() {
        setZValue(-1.0);
        // Only the header receives mouse hits. An expanded group must never
        // steal normal canvas panning or clicks in its otherwise empty body.
        setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemSendsGeometryChanges);
        setAcceptedMouseButtons(Qt::LeftButton);
        setPen(QPen(QColor(161,133,92),1.4,Qt::DashLine));
        QColor fill=panelFill;fill.setAlpha(95);
        setBrush(fill);
        m_header=new QGraphicsRectItem(this);
        m_header->setPen(Qt::NoPen);
        m_header->setBrush(QColor(109,79,42));
        m_header->setAcceptedMouseButtons(Qt::NoButton);
        m_title=new QGraphicsSimpleTextItem(this);
        m_title->setBrush(Qt::white);
        m_title->setPos(10,4);
        m_title->setAcceptedMouseButtons(Qt::NoButton);
        // The collapsed group is a genuine visible destination for its NPC's
        // preview wire. The dialogue root is hidden in compact mode, so that
        // wire must end at this group-header port instead of disappearing.
        m_input=new QGraphicsRectItem(QRectF(-6.0,9.0,12.0,12.0),this);
        m_input->setData(0,QStringLiteral("flowgroup-input"));
        m_input->setPen(QPen(QColor(214,176,245),1.5));
        m_input->setBrush(QColor(120,76,157));
        m_input->setZValue(6);
        m_input->setAcceptedMouseButtons(Qt::NoButton);
        m_input->setToolTip(QObject::tr("NPC conversation flow input. Expand the group to see the dialogue connections."));
        m_fold=new NodeFoldButton(this);
        m_fold->setToolTip(QObject::tr("Expand / collapse the whole conversation flow"));
        m_fold->clicked=[this] {if(foldClicked)foldClicked();};
        setTitle(title);
        setExpandedRect(QRectF(0,0,360,240));
    }
    void setTitle(const QString &title) {
        // A compact group remains small even with a long NPC title.
        m_title->setText(title.left(48));
        m_title->setToolTip(title);
        m_compactWidth=qBound(290.0,m_title->boundingRect().width()+57.0,445.0);
        if(m_collapsed)setCollapsed(true);
    }
    bool collapsed() const {return m_collapsed;}
    QPointF inputPoint() const {return m_input->sceneBoundingRect().center();}
    void setCollapsed(bool collapsed) {
        m_collapsed=collapsed;
        m_input->setVisible(collapsed);
        const QRectF body=collapsed ? QRectF(0,0,m_compactWidth,34.0):
            QRectF(0,0,m_expandedRect.width(),m_expandedRect.height());
        QGraphicsRectItem::setRect(body);
        updateChrome();
        m_fold->setText(collapsed?QStringLiteral("[+]"):QStringLiteral("[-]"));
    }
    void setExpandedRect(const QRectF &sceneRect) {
        m_expandedRect=sceneRect;
        // Geometry refreshes follow the child nodes. They are never a user
        // group drag and must not drag the children a second time.
        m_adjustingGeometry=true;
        setPos(sceneRect.topLeft());
        m_adjustingGeometry=false;
        setCollapsed(m_collapsed);
    }
    QPainterPath shape() const override {
        // Only the header is draggable, not the group background.
        QPainterPath header;
        header.addRect(QRectF(0,0,rect().width(),28));
        return header;
    }
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
        if(event->button()==Qt::LeftButton && event->pos().y()>=0.0 && event->pos().y()<28.0) {
            m_dragging=true;
            m_dragOrigin=pos();
            m_previousDragPos=pos();
        }
        QGraphicsRectItem::mousePressEvent(event);
    }
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override {
        const bool wasDragging=m_dragging;
        m_dragging=false;
        QGraphicsRectItem::mouseReleaseEvent(event);
        if(wasDragging && dragFinished)dragFinished();
    }
    QVariant itemChange(GraphicsItemChange change,const QVariant &value) override {
        if(change==QGraphicsItem::ItemPositionChange && m_dragging && !m_adjustingGeometry) {
            const QPointF requested=value.toPointF();
            // Move whole groups in the same 8px increments as their cards.
            // Otherwise the frame moves before the snapped children do.
            const QPointF delta=requested-m_dragOrigin;
            return QGraphicsRectItem::itemChange(change,QVariant(m_dragOrigin+
                QPointF(std::round(delta.x()/8.0)*8.0,std::round(delta.y()/8.0)*8.0)));
        }
        const QVariant result=QGraphicsRectItem::itemChange(change,value);
        if(change==QGraphicsItem::ItemPositionHasChanged && m_dragging && !m_adjustingGeometry) {
            const QPointF delta=pos()-m_previousDragPos;
            m_previousDragPos=pos();
            if(!qFuzzyIsNull(delta.x()) || !qFuzzyIsNull(delta.y()))
                if(moved)moved(delta);
        }
        return result;
    }
private:
    void updateChrome() {
        m_header->setRect(QRectF(0,0,rect().width(),28));
        m_fold->setPos(rect().width()-30,3);
    }
    bool m_collapsed=false,m_dragging=false,m_adjustingGeometry=false;
    qreal m_compactWidth=360.0;
    QPointF m_previousDragPos,m_dragOrigin;
    QRectF m_expandedRect;
    QGraphicsRectItem *m_header=nullptr;
    QGraphicsSimpleTextItem *m_title=nullptr;
    QGraphicsRectItem *m_input=nullptr;
    NodeFoldButton *m_fold=nullptr;
};

class NodeCard final : public QGraphicsRectItem {
public:
    std::function<void()> moved;
    explicit NodeCard(const QRectF &rect) : QGraphicsRectItem(rect) {
        setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable |
                 QGraphicsItem::ItemSendsGeometryChanges);
        setZValue(2);
    }
    // Keep older .vsgm coordinates unchanged on load. Snap every subsequent
    // user drag, for both ordinary Game Object cards and purple dialogue cards.
    void enableGridSnap() { m_gridSnap=true; }
    bool collapsed() const {return m_collapsed;}
    QPointF wirePoint(const QPointF &original) const {
        if (data(1).toString().startsWith(QStringLiteral("@graph:")) &&
            original.x()>=rect().width()*.5) {
            const QString role=original.y()<98.0?QStringLiteral("@graphvalue:"):
                original.y()<132.0?QStringLiteral("@graphbranch:true:"):
                                    QStringLiteral("@graphbranch:false:");
            for(QGraphicsItem *child:childItems()) {
                auto *port=dynamic_cast<QGraphicsEllipseItem*>(child);
                if(port && port->data(0).toString()==QStringLiteral("output") &&
                   port->data(1).toString().startsWith(role))
                    return port->sceneBoundingRect().center();
            }
        }
        if (original.x()<rect().width()*.5) {
            // Every incoming wire ends at the visible square, including
            // controls whose final Qt row differs from the old fixed Y value.
            QGraphicsItem *nearest=nullptr;
            qreal gap=1000000.0;
            for (QGraphicsItem *child:childItems()) {
                const QString kind=child->data(0).toString();
                if (kind!=QStringLiteral("input") && kind!=QStringLiteral("npc-input") &&
                    kind!=QStringLiteral("conversation-input") &&
                    kind!=QStringLiteral("exchange-input"))continue;
                const qreal delta=qAbs(child->boundingRect().center().y()-original.y());
                if(delta<gap) {gap=delta;nearest=child;}
            }
            if(nearest)return nearest->sceneBoundingRect().center();
            return scenePos()+QPointF(0,m_collapsed?18.0:original.y());
        }
        if (!m_collapsed) {
            QGraphicsEllipseItem *nearest=nullptr;
            qreal nearestGap=1000000.0;
            for(QGraphicsItem *child:childItems()) {
                auto *port=dynamic_cast<QGraphicsEllipseItem*>(child);
                if(!port)continue;
                const QString kind=port->data(0).toString();
                if(kind!=QStringLiteral("output") &&
                   kind!=QStringLiteral("enemy-action-output") &&
                   kind!=QStringLiteral("event-output") &&
                   kind!=QStringLiteral("conversation-output") &&
                   kind!=QStringLiteral("conversation-missing-output") &&
                   kind!=QStringLiteral("exchange-output") &&
                   kind!=QStringLiteral("give-anchor"))continue;
                const qreal gap=qAbs(port->rect().center().y()-original.y());
                if(gap<nearestGap) {nearestGap=gap;nearest=port;}
            }
            if(nearest && nearestGap<20.0)return nearest->sceneBoundingRect().center();
            return scenePos()+original;
        }
        // Preserve output socket identity even when the detail body is hidden.
        int slot=0;
        for (QGraphicsItem *child:childItems()) {
            auto *port=dynamic_cast<QGraphicsEllipseItem*>(child);
            if (!port || (port->data(0).toString()!=QStringLiteral("output") &&
                     port->data(0).toString()!=QStringLiteral("enemy-action-output") &&
                     port->data(0).toString()!=QStringLiteral("event-output") &&
                     port->data(0).toString()!=QStringLiteral("conversation-output") &&
                     port->data(0).toString()!=QStringLiteral("conversation-missing-output") &&
                     port->data(0).toString()!=QStringLiteral("exchange-output") &&
                     port->data(0).toString()!=QStringLiteral("give-anchor")))continue;
            if (qAbs(port->rect().center().y()-original.y())<12.0)
                return port->sceneBoundingRect().center();
            ++slot;
        }
        return scenePos()+QPointF(rect().width(),18);
    }
    void setCollapsed(bool state) {
        if (m_collapsed==state)return;
        m_collapsed=state;
        // Size compact cards to accommodate all their output sockets.
        // One consistent output order for compact and expanded conversations:
        // GIVE first, missing-item second, followed by normal answer routes.
        // Sorting visual sockets never changes their answer IDs or dialogue links.
        QVector<QGraphicsEllipseItem*> compactOutputs;
        for(QGraphicsItem *child:childItems()) {
            auto *port=dynamic_cast<QGraphicsEllipseItem*>(child);
            if(!port)continue;
            const QString kind=port->data(0).toString();
            if(kind==QStringLiteral("output") || kind==QStringLiteral("enemy-action-output") || kind==QStringLiteral("event-output") ||
               kind==QStringLiteral("conversation-output") ||
               kind==QStringLiteral("conversation-missing-output") ||
               kind==QStringLiteral("exchange-output") || kind==QStringLiteral("give-anchor"))
                compactOutputs.append(port);
        }
        if(data(1).toString().startsWith(QStringLiteral("@conversation:"))) {
            const auto rank=[](const QGraphicsEllipseItem *port) {
                const QString kind=port->data(0).toString();
                if(kind==QStringLiteral("give-anchor"))return 0;
                if(kind==QStringLiteral("conversation-missing-output"))return 1;
                if(kind==QStringLiteral("conversation-output"))return 2;
                return 3;
            };
            std::stable_sort(compactOutputs.begin(),compactOutputs.end(),
                [&rank](const QGraphicsEllipseItem *a,const QGraphicsEllipseItem *b) {
                    if(rank(a)!=rank(b))return rank(a)<rank(b);
                    return a->data(2).toInt()<b->data(2).toInt();
                });
        }
        int graphInputs=0;
        if(data(1).toString().startsWith(QStringLiteral("@graph:")))
            for(QGraphicsItem *child:childItems())
                if(child->data(4).toString()==QStringLiteral("graph-input"))++graphInputs;
        const qreal compactHeight=qMax(m_compactHeight,
            12.0+qMax(compactOutputs.size(),graphInputs)*17.0);
        QRectF body=rect();body.setHeight(state?compactHeight:m_fullHeight);
        setRect(body);
        for (QGraphicsItem *child:childItems()) {
            if (child==m_fold)continue;
            const QString portKind=child->data(0).toString();
            if (portKind==QStringLiteral("input") || portKind==QStringLiteral("npc-input") ||
                portKind==QStringLiteral("conversation-input") ||
                portKind==QStringLiteral("exchange-input")) {
                const bool helped=child->data(2).toString()==QStringLiteral("helped");
                const qreal compactY=child->data(4).toString()==QStringLiteral("graph-input")
                    ?14.0+17.0*child->data(2).toInt():m_compactHeight>35.0 ?
                    (portKind==QStringLiteral("npc-input")?(helped?39.0:24.0):9.0):18.0;
                child->setPos(state?QPointF(0,compactY-child->boundingRect().center().y()):QPointF());
                child->setVisible(true);
                continue;
            }
            if (auto *port=dynamic_cast<QGraphicsEllipseItem*>(child)) {
                if (portKind==QStringLiteral("output") ||
                    portKind==QStringLiteral("enemy-action-output") ||
                    portKind==QStringLiteral("event-output") ||
                    portKind==QStringLiteral("conversation-output") ||
                    portKind==QStringLiteral("conversation-missing-output") ||
                    portKind==QStringLiteral("exchange-output") ||
                    portKind==QStringLiteral("give-anchor")) {
                    const QRectF original=port->rect();
                    // Centres sit ON the right border with a 17px pitch.
                    // Save the original geometry in rect() for wire lookup.
                    const int slot=compactOutputs.indexOf(port);
                    port->setPos(state?
                        QPointF(rect().width()-original.center().x(),
                                14.0+17.0*slot-original.center().y()):QPointF());
                    continue;
                }
            }
            // Keep only the coloured stripe and the title in the compact view.
            const bool header=(dynamic_cast<QGraphicsRectItem*>(child)!=nullptr &&
                               child->boundingRect().height()<=32) ||
                              (dynamic_cast<QGraphicsSimpleTextItem*>(child)!=nullptr &&
                               child->pos().y()<10);
            child->setVisible(!state || header);
        }
        if (m_fold)m_fold->setText(state?QStringLiteral("[+]"):QStringLiteral("[-]"));
    }
    void setCompactHeight(qreal height) {m_compactHeight=height;}
    void setFullHeight(qreal height) {
        if(qAbs(m_fullHeight-height)<0.5)return;
        const bool folded=m_collapsed;
        if(folded)setCollapsed(false);
        m_fullHeight=height;
        QRectF body=rect();body.setHeight(height);setRect(body);
        if(folded)setCollapsed(true);
    }
    void setFoldButton(NodeFoldButton *fold) {
        m_fold=fold;
        m_fullHeight=rect().height();
        m_fold->setText(QStringLiteral("[-]"));
        m_fold->setPos(rect().width()-31,3);
    }
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override {
        if (change==QGraphicsItem::ItemPositionChange && m_gridSnap) {
            const QPointF p=value.toPointF();
            constexpr qreal cell=8.0;
            return QGraphicsRectItem::itemChange(change,
                QVariant(QPointF(std::round(p.x()/cell)*cell,std::round(p.y()/cell)*cell)));
        }
        if (change==QGraphicsItem::ItemPositionHasChanged && moved) moved();
        return QGraphicsRectItem::itemChange(change, value);
    }
private:
    bool m_gridSnap=false;
    bool m_collapsed=false;
    qreal m_fullHeight=0;
    qreal m_compactHeight=35.0;
    NodeFoldButton *m_fold=nullptr;
};

// The drawn pen stays crisp, but hit-testing uses a generous stroke.
// boundingRect must include the wider shape for Qt scene indexing.
// Shared port-to-port cubic for ordinary and missing-item dialogue routes.
// Both tangent handles stay level with their own sockets: no arbitrary
// downward control-point offset (the previous U-shaped "bow" on short links).
QPainterPath smoothNodeCurve(const QPointF &a,const QPointF &b) {
    const qreal separation=b.x()-a.x();
    const qreal bend=qBound(24.0,qAbs(separation)*.40,135.0);
    QPainterPath path(a);
    path.cubicTo(a+QPointF(bend,0),b-QPointF(bend,0),b);
    return path;
}

// An answer that leads back to its OWN dialogue is legal, but the ordinary
// back-edge cubic disappears underneath the card. Route it visibly around
// the top instead. The per-answer clearance separates multiple loop routes.
QPainterPath conversationSelfLoopCurve(const QPointF &a,const QPointF &b,
                                       const QRectF &cardBounds,int option,bool missing) {
    const qreal clearance=48.0+option*18.0+(missing?9.0:0.0);
    const qreal right=cardBounds.right()+clearance;
    const qreal left=cardBounds.left()-clearance;
    const qreal above=cardBounds.top()-clearance;
    QPainterPath path(a);
    path.cubicTo(a+QPointF(26,0),QPointF(right,a.y()+12),QPointF(right,a.y()-12));
    path.cubicTo(QPointF(right,above+30),QPointF(right-12,above),
                 QPointF(right-38,above));
    path.lineTo(QPointF(left+38,above));
    path.cubicTo(QPointF(left+10,above),QPointF(left,b.y()-35),
                 QPointF(left,b.y()-12));
    path.cubicTo(QPointF(left,b.y()+12),b-QPointF(18,0),b);
    return path;
}

class NodeWire final : public QGraphicsPathItem {
public:
    explicit NodeWire(const QPainterPath &path, const QPen &pen)
        : QGraphicsPathItem(path) { setPen(pen); }
    QRectF boundingRect() const override {
        return QGraphicsPathItem::boundingRect().adjusted(-12,-12,12,12);
    }
    QPainterPath shape() const override {
        QPainterPathStroker stroker;
        stroker.setWidth(20.0);
        stroker.setCapStyle(Qt::RoundCap);
        stroker.setJoinStyle(Qt::RoundJoin);
        return stroker.createStroke(path());
    }
};

class NodeCanvas final : public QGraphicsView {
public:
    std::function<void(const QString &, const QString &, const QString &)> connectionRequested;
    std::function<void(const QString &,int,bool,const QString &)> conversationConnectionRequested;
    std::function<void(const QString &,int,bool,const QPoint &)> conversationDropRequested;
    // Right-click a conversation route, including a legal self-loop, to
    // disconnect just that Adventure answer destination.
    std::function<void(const QString &,int,bool,const QPoint &)> conversationWireMenuRequested;
    std::function<void(const QString &,int,const QPoint &)> giveWireMenuRequested;
    // The teal GIVE anchor points to one existing Adventure exchange. Pulling
    // it out positions that exchange card, never creates a second exchange.
    std::function<void(const QString &,int,const QPointF &,const QString &)> giveAnchorDropped;
    std::function<void(const QPointF &, const QPoint &)> insertRequested;
    std::function<void(const QString &, const QPointF &, const QPoint &)> dropRequested;
    std::function<void(const QList<QPair<QString,int>> &, const QPoint &)> linkMenuRequested;
    std::function<void(const QString &,const QString &,int,const QPoint &)> graphLinkMenuRequested;
    std::function<void(const QString &)> cardSelected;
    // Native rubber-band selection is translated into stable card IDs for
    // connection highlighting. The QGraphicsScene owns actual selection/motion.
    std::function<void(const QStringList &)> cardsSelectionChanged;
    std::function<void(const QString &)> wireSelected;
    std::function<void()> cardDragFinished;
    std::function<void(const QString &,const QPoint &)> cardMenuRequested;
    std::function<void()> deleteRequested;
    explicit NodeCanvas(QGraphicsScene *scene, QWidget *parent = nullptr)
        : QGraphicsView(scene, parent) {
        setRenderHint(QPainter::Antialiasing);
        // Left-drag on empty canvas selects cards; middle-drag remains panning.
        // Qt moves every selected ItemIsMovable card together when dragged.
        setDragMode(QGraphicsView::RubberBandDrag);
        setRubberBandSelectionMode(Qt::IntersectsItemShape);
        setMouseTracking(true);
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        // Preserve the same scene point when Qt resizes the maximised splitter.
        // Without this, restoring the saved pan before its final resize can shift it.
        setResizeAnchor(QGraphicsView::AnchorViewCenter);
        setBackgroundBrush(QColor(26, 31, 41));
        setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    }
    void zoom(qreal factor) {
        const qreal current=transform().m11();
        if (current<=0)return;
        // Fit All may yield a scale smaller than normal wheel-zoom bounds.
        // Let the user zoom back in instead of locking the camera there.
        const qreal target=qBound(0.03,current*factor,2.5);
        if (!qFuzzyCompare(current,target))scale(target/current,target/current);
    }
protected:
    void wheelEvent(QWheelEvent *event) override {
        zoom(event->angleDelta().y() >= 0 ? 1.12 : 1.0/1.12);
        event->accept();
    }
    void keyPressEvent(QKeyEvent *event) override {
        // Do not steal Delete from QLineEdit/QPlainTextEdit inside a purple
        // dialogue-card proxy. Delete applies to a selected canvas card only.
        if (event->key()==Qt::Key_Escape && cardSelected) {
            if(scene())scene()->clearSelection();
            if(cardsSelectionChanged)cardsSelectionChanged(QStringList());
            cardSelected(QString());
            event->accept();
            return;
        }
        if (event->key()==Qt::Key_Delete && deleteRequested &&
            !(scene() && scene()->focusItem() &&
              scene()->focusItem()->type()==QGraphicsProxyWidget::Type)) {
            deleteRequested();
            event->accept();
            return;
        }
        QGraphicsView::keyPressEvent(event);
    }
    void mousePressEvent(QMouseEvent *event) override {
        if (event->button()==Qt::MiddleButton) {
            m_panning=true;
            m_panPosition=event->pos();
            viewport()->setCursor(Qt::ClosedHandCursor);
            event->accept();
            return;
        }
        QGraphicsItem *item = itemAt(event->pos());
        if (event->button()==Qt::LeftButton || event->button()==Qt::RightButton) {
            for (QGraphicsItem *candidate=item;candidate;candidate=candidate->parentItem()) {
                if (candidate->data(0).toString()!=QStringLiteral("card"))continue;
                qreal highest=2.0;
                for (QGraphicsItem *top:scene()->items()) {
                    if (!top->parentItem() &&
                        top->data(0).toString()==QStringLiteral("card"))
                        highest=qMax(highest,top->zValue());
                }
                // Normalise occasionally so thousands of selections don't
                // accumulate an unbounded sequence of z-values.
                if(highest>10000.0) {
                    QList<QGraphicsItem*> cards;
                    for(QGraphicsItem *top:scene()->items())
                        if(!top->parentItem() &&
                           top->data(0).toString()==QStringLiteral("card"))cards.append(top);
                    std::sort(cards.begin(),cards.end(),[](QGraphicsItem *a,QGraphicsItem *b){
                        return a->zValue()<b->zValue();
                    });
                    highest=1.0;
                    for(QGraphicsItem *card:cards)card->setZValue(++highest);
                }
                candidate->setZValue(highest+1.0);
                break;
            }
        }
        const QString socketKind=item?item->data(0).toString():QString();
        if (event->button() == Qt::LeftButton && item &&
            (socketKind==QStringLiteral("output") ||
             socketKind==QStringLiteral("enemy-action-output") ||
             socketKind==QStringLiteral("event-output") ||
             socketKind==QStringLiteral("conversation-output") ||
             socketKind==QStringLiteral("conversation-missing-output") ||
             socketKind==QStringLiteral("exchange-output") ||
             socketKind==QStringLiteral("give-anchor"))) {
            m_giveDrag=socketKind==QStringLiteral("give-anchor");
            m_choiceDrag=socketKind.startsWith(QStringLiteral("conversation-")) ||
                socketKind==QStringLiteral("exchange-output");
            m_choiceMissing=socketKind==QStringLiteral("conversation-missing-output");
            m_choiceOption=item->data(2).toInt();
            m_from = socketKind==QStringLiteral("enemy-action-output")
                ? QStringLiteral("@enemydefeat:")+item->data(1).toString()
                : socketKind==QStringLiteral("event-output")
                ? eventOutput(item->data(2).toString(),item->data(1).toString())
                : item->data(1).toString();
            // Selecting a socket should focus its owning card, not the
            // synthetic output ID (e.g. @graphbranch:true:...). Otherwise
            // dimming would mistakenly fade EVERY card while starting a wire.
            if (cardSelected) {
                for (QGraphicsItem *parent=item->parentItem();parent;parent=parent->parentItem()) {
                    if(parent->data(0).toString()==QStringLiteral("card")) {
                        cardSelected(parent->data(1).toString());
                        break;
                    }
                }
            }
            m_startPoint = item->sceneBoundingRect().center();
            m_dragLine = scene()->addPath(QPainterPath(), QPen(
                m_giveDrag?QColor(80,196,180):QColor(255,191,87),2,Qt::DashLine));
            m_dragLine->setZValue(4);
            event->accept();
            return;
        }
        // Wire hit-testing uses NodeWire's 20px stroke, so a tangled route
        // can be selected without hitting its tiny visible 2-3px line.
        if (event->button()==Qt::LeftButton && item &&
            dynamic_cast<NodeWire*>(item) && wireSelected) {
            if(scene())scene()->clearSelection();
            if(cardsSelectionChanged)cardsSelectionChanged(QStringList());
            setFocus(Qt::MouseFocusReason);
            wireSelected(item->data(6).toString());
            event->accept();
            return;
        }
        if (event->button()==Qt::LeftButton && cardSelected) {
            QString selectedId;
            bool editingChild=false;
            for (QGraphicsItem *p=item; p; p=p->parentItem()) {
                if (p->type()==QGraphicsProxyWidget::Type)editingChild=true;
                if (p->data(0).toString() == QStringLiteral("card"))
                    selectedId=p->data(1).toString();
            }
            if (!editingChild) {
                scene()->setFocusItem(nullptr);
                setFocus(Qt::MouseFocusReason);
            }
            // Clicking empty canvas also clears the keyboard deletion target.
            // A line click alone doesn't select an unrelated, old card.
            cardSelected(selectedId);
        }
        QGraphicsView::mousePressEvent(event);
    }
    void mouseMoveEvent(QMouseEvent *event) override {
        if (m_panning) {
            const QPoint movement=event->pos()-m_panPosition;
            m_panPosition=event->pos();
            horizontalScrollBar()->setValue(horizontalScrollBar()->value()-movement.x());
            verticalScrollBar()->setValue(verticalScrollBar()->value()-movement.y());
            event->accept();
            return;
        }
        if (m_dragLine) {
            const QPointF end = mapToScene(event->pos());
            QPainterPath path(m_startPoint);
            const qreal bend = qMax(42.0, qAbs(end.x()-m_startPoint.x())*0.45);
            path.cubicTo(m_startPoint+QPointF(bend,0),end-QPointF(bend,0),end);
            m_dragLine->setPath(path);
            event->accept();
            return;
        }
        QGraphicsView::mouseMoveEvent(event);
    }
    void mouseReleaseEvent(QMouseEvent *event) override {
        if (event->button()==Qt::MiddleButton && m_panning) {
            m_panning=false;
            viewport()->unsetCursor();
            event->accept();
            return;
        }
        if (m_dragLine) {
            const QString from = m_from;
            const bool choiceDrag=m_choiceDrag, missingRoute=m_choiceMissing;
            const bool giveDrag=m_giveDrag;
            const int choiceOption=m_choiceOption;
            const QPointF dropPoint=mapToScene(event->pos());
            // Ignore the temporary wire when hit-testing cards.
            m_dragLine->setVisible(false);
            // Prefer an actual input/socket or card over a nearby crossing
            // NodeWire. The line's broad 20px hit shape otherwise makes an
            // apparently correct drop miss the target card altogether.
            QString to, inputPort;
            const QList<QGraphicsItem*> hits=scene()->items(
                QRectF(dropPoint-QPointF(5,5),QSizeF(10,10)),
                Qt::IntersectsItemShape,Qt::DescendingOrder,transform());
            for(QGraphicsItem *hit:hits) {
                if(dynamic_cast<NodeWire*>(hit))continue;
                QString candidate, port;
                for(QGraphicsItem *p=hit;p;p=p->parentItem()) {
                    if(p->data(0).toString()==QStringLiteral("npc-input") ||
                       (p->data(0).toString()==QStringLiteral("input") &&
                        p->data(2).toString()==QStringLiteral("state")))
                        port=p->data(2).toString();
                    if(p->data(0).toString()==QStringLiteral("card")) {
                        candidate=p->data(1).toString();break;
                    }
                }
                if(candidate.isEmpty() || candidate==m_from)continue;
                // Match the explicit socket before the card body, when both
                // are under this mouse position.
                to=candidate;inputPort=port;
                if(!port.isEmpty() || hit->data(0).toString()==QStringLiteral("input") ||
                   hit->data(0).toString()==QStringLiteral("npc-input"))break;
            }
            scene()->removeItem(m_dragLine);
            delete m_dragLine;
            m_dragLine = nullptr;
            m_from.clear();m_choiceDrag=false;m_giveDrag=false;
            if(giveDrag) {
                if(giveAnchorDropped)
                    giveAnchorDropped(from,choiceOption,dropPoint,to);
            } else if (choiceDrag) {
                // A conversation answer is an Adventure choice, NOT a Game
                // Object action. Preserve its existing next/missingNext field.
                // setConversationAnswer confirms new self-loops before saving.
                if (to.startsWith(QStringLiteral("@conversation:")) && conversationConnectionRequested)
                    conversationConnectionRequested(from,choiceOption,missingRoute,to);
                else if (to.isEmpty() && conversationDropRequested)
                    conversationDropRequested(from,choiceOption,missingRoute,event->globalPosition().toPoint());
            } else if (!to.isEmpty() && from!=to && connectionRequested)
                connectionRequested(from,to,inputPort);
            else if (to.isEmpty() && dropRequested)
                dropRequested(from,mapToScene(event->pos()),event->globalPosition().toPoint());
            event->accept();
            return;
        }
        QGraphicsView::mouseReleaseEvent(event);
        if(event->button()==Qt::LeftButton && cardsSelectionChanged && scene()) {
            QStringList selected;
            for(QGraphicsItem *item:scene()->selectedItems())
                if(item && item->data(0).toString()==QStringLiteral("card"))
                    selected.append(item->data(1).toString());
            selected.removeDuplicates();
            selected.sort();
            cardsSelectionChanged(selected);
        }
        // The live paths already follow the card. Recalculate their final
        // tangents just once after Qt completes the drag, not on a timer
        // repeatedly reset by each mouse movement.
        if (event->button()==Qt::LeftButton && cardDragFinished)
            cardDragFinished();
    }
    void contextMenuEvent(QContextMenuEvent *event) override {
        // A generous viewport-space target, especially useful when zoomed out.
        // Collect ALL overlapping links, including purple Show Dialogue wires.
        // Both wire types use the same context menu + remove-connection path.
        QGraphicsItem *top=itemAt(event->pos());
        const QRect target(event->pos()-QPoint(10,10),QSize(21,21));
        // A card can cover a link in the scene. Right-clicking the card
        // should open its own menu, which also lists all its answer routes;
        // never silently select a hidden wire underneath a Qt text control.
        for (QGraphicsItem *p=top;p;p=p->parentItem()) {
            if (p->data(0).toString()==QStringLiteral("card")) {
                if (cardMenuRequested)
                    cardMenuRequested(p->data(1).toString(),event->globalPos());
                event->accept();
                return;
            }
        }
        // The self-loop runs OUTSIDE the card and remains easy to right-click.
        for(QGraphicsItem *wire:items(event->pos())) {
            const QString kind=wire->data(0).toString();
            if(kind==QStringLiteral("conversation-next-wire") ||
               kind==QStringLiteral("conversation-missing-wire")) {
                if(conversationWireMenuRequested)
                    conversationWireMenuRequested(wire->data(1).toString(),
                        wire->data(2).toInt(),kind==QStringLiteral("conversation-missing-wire"),
                        event->globalPos());
                event->accept();return;
            }
            if(kind==QStringLiteral("give-response-wire")) {
                if(giveWireMenuRequested)
                    giveWireMenuRequested(wire->data(1).toString(),wire->data(2).toInt(),
                                         event->globalPos());
                event->accept();return;
            }
        }
        QList<QPair<QString,int>> hits;
        for(QGraphicsItem *wire:items(target)) {
            const QString kind=wire->data(0).toString();
            if(kind.startsWith(QStringLiteral("graph-"))) {
                if(graphLinkMenuRequested)
                    graphLinkMenuRequested(kind,wire->data(1).toString(),
                                           wire->data(2).toInt(),event->globalPos());
                event->accept();return;
            }
        }
        for (QGraphicsItem *item: items(target)) {
            const QString kind=item->data(0).toString();
            if (kind!=QStringLiteral("link") && kind!=QStringLiteral("event-link") && kind!=QStringLiteral("dialogue-link") &&
                kind!=QStringLiteral("state-link") && kind!=QStringLiteral("state-true-link") &&
                kind!=QStringLiteral("state-false-link") &&
                kind!=QStringLiteral("state-true-action") &&
                kind!=QStringLiteral("state-false-action"))continue;
            // -1 is reserved for a Trigger's single Show Dialogue connection.
            const QPair<QString,int> ref(item->data(1).toString(),
                kind==QStringLiteral("dialogue-link") ? -1 :
                kind==QStringLiteral("state-link") ? -10-item->data(2).toInt() :
                kind==QStringLiteral("state-true-link") ? -3 :
                kind==QStringLiteral("state-false-link") ? -4 :
                kind==QStringLiteral("state-true-action") ? -1000-item->data(2).toInt() :
                kind==QStringLiteral("state-false-action") ? -2000-item->data(2).toInt() :
                item->data(2).toInt());
            if (!hits.contains(ref)) hits.append(ref);
        }
        if (!hits.isEmpty()) {
            if (linkMenuRequested) linkMenuRequested(hits,event->globalPos());
            event->accept();
            return;
        }
        if (insertRequested) {
            insertRequested(mapToScene(event->pos()),event->globalPos());
            event->accept();
            return;
        }
        QGraphicsView::contextMenuEvent(event);
    }
private:
    bool m_panning=false;
    QPoint m_panPosition;
    QString m_from;
    bool m_choiceDrag=false,m_choiceMissing=false,m_giveDrag=false;
    int m_choiceOption=-1;
    QPointF m_startPoint;
    QGraphicsPathItem *m_dragLine = nullptr;
};

class VisualNodesDialog final : public QDialog {
public:
    explicit VisualNodesDialog(const QString &vsgmPath,const IDETheme &theme,QWidget *parent = nullptr)
        : QDialog(parent), m_theme(theme),
          m_graphPath(QFileInfo(vsgmPath).absoluteFilePath()) {
        // One control palette for all node types, regardless of their coloured
        // frame/header/socket identities. The IDE theme is the source of truth.
        m_controlsStyle=QStringLiteral(
            "QWidget { background-color: @panel@; color: @text@; } "
            "QDialog { background-color: @window@; } "
            "QLabel, QCheckBox { background: transparent; color: @text@; } "
            "QLineEdit, QPlainTextEdit, QTextEdit, QComboBox, QSpinBox, "
            "QListWidget, QTreeWidget { background: @input@; color: @text@; "
            "border: 1px solid @border@; padding: 3px; "
            "selection-background-color: @selection@; selection-color: @selectionText@; } "
            "QComboBox QAbstractItemView { background: @menu@; color: @text@; "
            "selection-background-color: @selection@; selection-color: @selectionText@; } "
            "QPushButton { background: @accent@; color: @selectionText@; "
            "border: 1px solid @border@; padding: 5px; } "
            "QPushButton:hover { background: @hover@; color: @text@; } "
            "QPushButton:disabled { background: @panel@; color: @muted@; } "
            "QLineEdit:disabled, QPlainTextEdit:disabled, QTextEdit:disabled, "
            "QComboBox:disabled, QSpinBox:disabled { color: @muted@; } "
            "QToolTip { background: @tooltip@; color: @tooltipText@; "
            "border: 1px solid @border@; }");
        m_controlsStyle.replace(QStringLiteral("@panel@"),m_theme.panelBackground.name());
        m_controlsStyle.replace(QStringLiteral("@window@"),m_theme.windowBackground.name());
        m_controlsStyle.replace(QStringLiteral("@input@"),m_theme.inputBackground.name());
        m_controlsStyle.replace(QStringLiteral("@menu@"),m_theme.menuBackground.name());
        m_controlsStyle.replace(QStringLiteral("@text@"),m_theme.text.name());
        m_controlsStyle.replace(QStringLiteral("@muted@"),m_theme.mutedText.name());
        m_controlsStyle.replace(QStringLiteral("@accent@"),m_theme.accent.name());
        m_controlsStyle.replace(QStringLiteral("@hover@"),m_theme.hover.name());
        m_controlsStyle.replace(QStringLiteral("@border@"),m_theme.border.name());
        m_controlsStyle.replace(QStringLiteral("@selection@"),m_theme.selectionBackground.name());
        m_controlsStyle.replace(QStringLiteral("@selectionText@"),m_theme.selectionText.name());
        m_controlsStyle.replace(QStringLiteral("@tooltip@"),m_theme.tooltipBackground.name());
        m_controlsStyle.replace(QStringLiteral("@tooltipText@"),m_theme.tooltipText.name());
        setStyleSheet(m_controlsStyle);
        setWindowTitle(tr("Visual Nodes | %1").arg(QFileInfo(vsgmPath).fileName()));
        setMinimumSize(950,620);
        setWindowState(windowState() | Qt::WindowMaximized);
        m_worldPath = QFileInfo(m_graphPath).absolutePath() + QLatin1Char('/') +
            QFileInfo(m_graphPath).completeBaseName() + QStringLiteral(".sbgm");
        m_worldName = QFileInfo(m_worldPath).completeBaseName();
    }
    bool initialise() {
        QByteArray contents;
        if (!readJson(m_worldPath,&m_world,&contents) ||
            m_world.value(QStringLiteral("format")).toString() != QStringLiteral("SIDBOX-GAME-DESIGN") ||
            m_world.value(QStringLiteral("version")).toInt() != 1) {
            QMessageBox::warning(this,tr("Visual Nodes"),
                tr("Cannot read the matching world design:\n%1").arg(m_worldPath));
            return false;
        }
        m_originalHash = QCryptographicHash::hash(contents,QCryptographicHash::Sha256);
        QJsonObject graph;
        if (QFileInfo::exists(m_graphPath)) {
            QByteArray layoutBytes;
            if (!readJson(m_graphPath,&graph,&layoutBytes) ||
                graph.value(QStringLiteral("format")).toString() != QStringLiteral("SIDBOX-VISUAL-NODES") ||
                graph.value(QStringLiteral("version")).toInt() != 1 ||
                graph.value(QStringLiteral("world")).toString() != m_worldName) {
                QMessageBox::warning(this,tr("Visual Nodes"),tr("Invalid .vsgm graph:\n%1").arg(m_graphPath));
                return false;
            }
            m_layoutHash=QCryptographicHash::hash(layoutBytes,QCryptographicHash::Sha256);
        }
        // Stage 5.166.41: camera settings belong only to .vsgm, never .sbgm.
        // Earlier Phase 1 .vsgm files have no view field and remain valid.
        const QJsonObject storedView = graph.value(QStringLiteral("view")).toObject();
        // View-only splitter proportions belong in .vsgm, never the game world.
        const QJsonArray paneWidths=graph.value(QStringLiteral("paneWidths")).toArray();
        if(paneWidths.size()==3) {
            QList<int> sizes;
            bool valid=true;
            for(const QJsonValue &value:paneWidths) {
                const int width=value.toInt(-1);
                if(width<80 || width>16000) {valid=false;break;}
                sizes.append(width);
            }
            if(valid)m_savedPaneWidths=sizes;
        }
        const QJsonArray storedCenter = storedView.value(QStringLiteral("center")).toArray();
        const QJsonValue storedZoom = storedView.value(QStringLiteral("zoom"));
        // Store exact scrollbar positions as well as scene centre. QGraphicsView
        // scrollbars use integer pixels: restoring only centre can lose the pan
        // when a maximised splitter finishes resizing or scrollbar rounding shifts.
        const QJsonArray storedScroll = storedView.value(QStringLiteral("scrollbars")).toArray();
        const QJsonArray storedViewport = storedView.value(QStringLiteral("viewportPixels")).toArray();
        if (storedScroll.size()==2 && storedViewport.size()==2 &&
            storedScroll.at(0).isDouble() && storedScroll.at(1).isDouble() &&
            storedViewport.at(0).isDouble() && storedViewport.at(1).isDouble()) {
            const int width=storedViewport.at(0).toInt();
            const int height=storedViewport.at(1).toInt();
            if (width>=10 && height>=10 && width<=16384 && height<=16384) {
                m_hasStoredScroll=true;
                m_storedScroll=QPoint(storedScroll.at(0).toInt(),storedScroll.at(1).toInt());
                m_storedViewport=QSize(width,height);
            }
        }
        if (storedZoom.isDouble() && storedCenter.size()==2 &&
            storedCenter.at(0).isDouble() && storedCenter.at(1).isDouble()) {
            const double z=storedZoom.toDouble();
            const double x=storedCenter.at(0).toDouble();
            const double y=storedCenter.at(1).toDouble();
            if (std::isfinite(z) && std::isfinite(x) && std::isfinite(y) &&
                z>=0.001 && z<=2.5 && qAbs(x)<=30000 && qAbs(y)<=30000) {
                m_hasStoredView=true;
                m_storedZoom=z;
                m_storedCenter=QPointF(x,y);
            }
        }
        for (const QJsonValue &value:graph.value(QStringLiteral("collapsedCards")).toArray())
            if (value.isString())m_collapsedCards.insert(value.toString());
        // Explicitly hidden NPC cards are a view preference, not a change to
        // their required opening dialogue in adventure.npcs.
        for (const QJsonValue &value:graph.value(QStringLiteral("hiddenNpcCards")).toArray())
            if (value.isString())m_hiddenNpcCards.insert(value.toString());
        // Conversation-flow roots are purely visual. The dialogue graph itself
        // is always reconstructed from adventure.nodes[*].choices[*].next.
        for (const QJsonValue &value:graph.value(QStringLiteral("conversationFlowRoots")).toArray())
            if (value.isDouble() && value.toInt(-1)>=0)
                m_conversationRoots.insert(value.toInt());
        // Hidden flow groups remain remembered so Show Conversation Flow can
        // reopen them exactly where they were without recreating the layout.
        for (const QJsonValue &value:graph.value(QStringLiteral("hiddenConversationFlowRoots")).toArray())
            if (value.isDouble() && value.toInt(-1)>=0)
                m_hiddenConversationRoots.insert(value.toInt());
        // Optional VISUAL routing hints, never another source of gameplay rules.
        // Every route must still match the dialogue ID read from .sbgm.
        const QJsonObject npcRoutes=graph.value(QStringLiteral("npcDialogueRoutes")).toObject();
        for (auto it=npcRoutes.begin();it!=npcRoutes.end();++it)
            if (it.value().isObject())m_npcDialogueRoutes.insert(it.key(),it.value().toObject());
        // Display-only grouping of multiple independent logic actions onto a
        // single existing Show Dialogue card. Never duplicate the authored node.
        const QJsonObject dialogueRoutes=graph.value(QStringLiteral("graphDialogueRoutes")).toObject();
        for(auto it=dialogueRoutes.begin();it!=dialogueRoutes.end();++it)
            if(it.key().startsWith(QStringLiteral("@graph-dialogue:")) && it.value().isString() &&
               !it.value().toString().isEmpty())
                m_graphDialogueRoutes.insert(it.key(),it.value().toString());
        const QJsonObject positions = graph.value(QStringLiteral("positions")).toObject();
        for (auto it=positions.begin();it!=positions.end();++it) {
            const QJsonArray xy=it.value().toArray();
            if (xy.size()==2 && xy.at(0).isDouble() && xy.at(1).isDouble())
                m_positions.insert(it.key(),QPointF(qBound(-30000.,xy.at(0).toDouble(),30000.),
                                                    qBound(-30000.,xy.at(1).toDouble(),30000.)));
        }
        // Dialogue entries are index-addressed by the runtime. Editing or adding
        // them preserves all existing node indices and advanced choice fields.
        const QJsonObject adventure=m_world.value(QStringLiteral("adventure")).toObject();
        m_dialogues=adventure.value(QStringLiteral("nodes")).toArray();
        m_npcEntries=adventure.value(QStringLiteral("npcs")).toArray();
        // This is exactly the Dialogue Editor folder metadata, not a new tree.
        m_dialogueFolders=adventure.value(QStringLiteral("dialogueFolders")).toArray();
        // The world is the authority for logic. The graph stores only explicitly
        // placed *unconnected* cards and their layout; existing links are read
        // from .sbgm on every open. Legacy .vsgm positions do not imply visibility.
        const QJsonArray placed=graph.value(QStringLiteral("placedCards")).toArray();
        for (const QJsonValue &v:placed) if (v.isString()) m_placedCards.insert(v.toString());
        const QJsonArray cards=graph.value(QStringLiteral("dialogueCards")).toArray();
        for (const QJsonValue &v:cards) if (v.isString()) m_dialogueCards.insert(v.toString());
        const QJsonArray resources=m_world.value(QStringLiteral("resources")).toArray();
        const QJsonArray npcEntries=m_npcEntries;
        QSet<QString> npcSpriteIds;
        for (const QJsonValue &entry:npcEntries)
            npcSpriteIds.insert(entry.toObject().value(QStringLiteral("spriteId")).toString());
        for (int i=0;i<resources.size();++i) {
            const QJsonObject resource=resources.at(i).toObject();
            if (resource.value(QStringLiteral("kind")).toString()!=QStringLiteral("sprite")) continue;
            const QJsonObject data=resource.value(QStringLiteral("gameObject")).toObject();
            const QString type=data.value(QStringLiteral("type")).toString();
            const QString id=resource.value(QStringLiteral("id")).toString();
            if (id.isEmpty() || npcSpriteIds.contains(id) ||
                ((type.isEmpty() || type==QStringLiteral("decoration")) &&
                 resource.value(QStringLiteral("name")).toString().trimmed().compare(
                     QStringLiteral("player"),Qt::CaseInsensitive)==0))continue;
            // Older .sbgm sprites may omit gameObject.type entirely.
            // They are ordinary scenery until connected, not missing nodes.
            const QString effectiveType = type.isEmpty() ? QStringLiteral("decoration") : type;
            NodeObject node;
            node.id=id;
            node.name=resource.value(QStringLiteral("name")).toString(id);
            node.type=effectiveType;
            node.resourceIndex=i;
            node.pickupKind=data.value(QStringLiteral("pickupKind")).toInt(1);
            const QJsonObject savedEvents=data.value(QStringLiteral("eventActions")).toObject();
            for(const QString &key:eventKinds(effectiveType)) {
                QVector<NodeLink> &actions=node.eventLinks[key];
                for(const QJsonValue &v:savedEvents.value(key).toArray()) {
                    const QJsonObject entry=v.toObject();
                    const QString target=entry.value(QStringLiteral("objectId")).toString();
                    const QString op=entry.value(QStringLiteral("action")).toString();
                    if(!target.isEmpty() && supportedAction(op))actions.append({target,op});
                }
            }
            if (type==QStringLiteral("trigger")) {
                node.triggerPress=data.value(QStringLiteral("triggerPress")).toBool(false);
                node.triggerOneShot=data.value(QStringLiteral("triggerOneShot")).toBool(false);
                node.interactItemName=data.value(QStringLiteral("interactItemName")).toString();
                node.dialogueNode=data.value(QStringLiteral("interactDialogueNode")).toInt(-1);
                node.dialogueMode=data.value(QStringLiteral("interactDialogueMode"))
                    .toString(QStringLiteral("conversation"));
                if (node.dialogueMode!=QStringLiteral("single") &&
                    node.dialogueMode!=QStringLiteral("sequence"))
                    node.dialogueMode=QStringLiteral("conversation");
                if (node.dialogueNode>=0) m_dialogueCards.insert(id);
                node.logicNodes=data.value(QStringLiteral("logicNodes")).toArray();
                // Upgrade Stage 5.166.67 weather wires: the editor used to
                // store Enable on BOTH branches when they targeted the same
                // Rain/Snow/Storm card. FALSE must actually disable it.
                for(int gi=0;gi<node.logicNodes.size();++gi) {
                    QJsonObject graphNode=node.logicNodes.at(gi).toObject();
                    QSet<QString> trueWeather;
                    for(const QJsonValue &entry:graphNode.value(QStringLiteral("trueActions")).toArray()) {
                        const QJsonObject link=entry.toObject();
                        const QString target=link.value(QStringLiteral("objectId")).toString();
                        if(isWeatherTarget(target) &&
                           link.value(QStringLiteral("action")).toString()==QStringLiteral("enable"))
                            trueWeather.insert(target);
                    }
                    QJsonArray falseLinks=graphNode.value(QStringLiteral("falseActions")).toArray();
                    bool updated=false;
                    for(int fi=0;fi<falseLinks.size();++fi) {
                        QJsonObject link=falseLinks.at(fi).toObject();
                        if(trueWeather.contains(link.value(QStringLiteral("objectId")).toString()) &&
                           link.value(QStringLiteral("action")).toString()==QStringLiteral("enable")) {
                            link.insert(QStringLiteral("action"),QStringLiteral("disable"));
                            falseLinks.replace(fi,link);updated=true;
                        }
                    }
                    if(updated) {
                        graphNode.insert(QStringLiteral("falseActions"),falseLinks);
                        node.logicNodes.replace(gi,graphNode);
                        m_touched.insert(id);m_dirty=true;
                    }
                }
                node.toggleStateTargetId=data.value(QStringLiteral("toggleStateTargetId")).toString();
                node.toggleStateOperator=data.value(QStringLiteral("toggleStateOperator"))
                    .toString(QStringLiteral("boolean"));
                if (node.toggleStateOperator!=QStringLiteral("and") &&
                    node.toggleStateOperator!=QStringLiteral("or"))
                    node.toggleStateOperator=QStringLiteral("boolean");
                for (const QJsonValue &input:data.value(QStringLiteral("toggleStateInputIds")).toArray()) {
                    const QString inputId=input.toString();
                    if (!inputId.isEmpty() && inputId!=node.toggleStateTargetId &&
                        !node.toggleStateInputIds.contains(inputId))node.toggleStateInputIds.append(inputId);
                }
                node.toggleTrueDialogueNode=data.value(QStringLiteral("toggleTrueDialogueNode")).toInt(-1);
                node.toggleFalseDialogueNode=data.value(QStringLiteral("toggleFalseDialogueNode")).toInt(-1);
                for (const bool yes:{true,false}) {
                    QVector<NodeLink> &actions=yes?node.toggleTrueActions:node.toggleFalseActions;
                    const QJsonArray stored=data.value(yes?QStringLiteral("toggleTrueActions"):
                        QStringLiteral("toggleFalseActions")).toArray();
                    for (const QJsonValue &entry:stored) {
                        const QJsonObject link=entry.toObject();
                        const QString target=link.value(QStringLiteral("objectId")).toString();
                        const QString action=link.value(QStringLiteral("action")).toString();
                        if (!target.isEmpty() && supportedAction(action))actions.append({target,action});
                    }
                }
            }
            if (type!=QStringLiteral("trigger") && type!=QStringLiteral("npc") &&
                type!=QStringLiteral("player_action") && type!=QStringLiteral("collectable"))
                node.logicNodes=data.value(QStringLiteral("logicNodes")).toArray();
            const QString legacy=data.value(QStringLiteral("targetObjectId")).toString();
            const QString action=data.value(QStringLiteral("targetAction")).toString();
            // Keep dormant "none" targets as well: editing other links must not
            // silently discard values authored in Game Object Properties.
            if (!legacy.isEmpty()) node.links.append({legacy,action});
            if (type==QStringLiteral("enemy"))
                for (const QJsonValue &value:data.value(QStringLiteral("enemyDefeatExtraActions")).toArray()) {
                    const QJsonObject link=value.toObject();
                    const QString target=link.value(QStringLiteral("objectId")).toString();
                    const QString action=link.value(QStringLiteral("action")).toString();
                    if (!target.isEmpty() && supportedAction(action)) node.links.append({target,action});
                }
            if (type==QStringLiteral("trigger"))
                for (const QJsonValue &value:data.value(QStringLiteral("triggerExtraActions")).toArray()) {
                    const QJsonObject o=value.toObject();
                    node.links.append({o.value(QStringLiteral("objectId")).toString(),
                                       o.value(QStringLiteral("action")).toString()});
                }
            m_order.append(id);
            m_objects.insert(id,node);
        }
        // Adventure NPCs are authored separately from Game Object sprites.
        // They are still valid enable/disable/toggle targets in the generator,
        // so surface their actual sprite IDs without inventing graph entities.
        const QJsonArray npcs=m_world.value(QStringLiteral("adventure")).toObject()
            .value(QStringLiteral("npcs")).toArray();
        for (const QJsonValue &npcValue:npcs) {
            const QString id=npcValue.toObject().value(QStringLiteral("spriteId")).toString();
            if (id.isEmpty() || m_objects.contains(id))continue;
            for (int i=0;i<resources.size();++i) {
                const QJsonObject resource=resources.at(i).toObject();
                if (resource.value(QStringLiteral("id")).toString()!=id ||
                    resource.value(QStringLiteral("kind")).toString()!=QStringLiteral("sprite"))continue;
                NodeObject node;
                node.id=id;
                node.name=resource.value(QStringLiteral("name")).toString(id);
                node.type=QStringLiteral("npc");
                node.resourceIndex=i;
                node.npcStartNode=npcValue.toObject().value(QStringLiteral("node")).toInt(-1);
                node.npcDoneNode=npcValue.toObject().value(QStringLiteral("doneNode")).toInt(-1);
                node.npcRadius=npcValue.toObject().value(QStringLiteral("radius")).toInt(48);
                node.npcInitiallyVisible=npcValue.toObject().value(QStringLiteral("initiallyVisible")).toBool(true);
                m_order.append(id);
                m_objects.insert(id,node);
                break;
            }
        }
        // Virtual PLAYER commands are graph targets, never .sbgm resources.
        // Stored links keep their stable IDs; the canvas rebuilds these cards.
        const auto addPlayer=[&](const QString &id,const QString &name) {
            if (m_objects.contains(id))return;
            NodeObject node;
            node.id=id;node.name=name;node.type=QStringLiteral("player_action");
            m_objects.insert(id,node);m_order.append(id);
        };
        addPlayer(QStringLiteral("@player_spotlight"),tr("Spotlight"));
        for (const QPair<QString,QString> &option:QVector<QPair<QString,QString>>{
             {QStringLiteral("@player_weather:0"),tr("Clear Weather")},
             {QStringLiteral("@player_weather:1"),tr("Rain")},
             {QStringLiteral("@player_weather:2"),tr("Snow")},
             {QStringLiteral("@player_weather:3"),tr("Thunderstorm")},
             {QStringLiteral("@player_time:0"),tr("Daylight")},
             {QStringLiteral("@player_time:1"),tr("Night")},
             {QStringLiteral("@player_time:2"),tr("Resume Day/Night Cycle")}})
            addPlayer(option.first,option.second);
        // Match the Goto World editor: the project's .sbgm worlds are siblings.
        // Use the same runtime-name conversion as the game's world registry.
        const QDir projectDir(QFileInfo(m_worldPath).absolutePath());
        for(const QFileInfo &file:projectDir.entryInfoList(
                QStringList{QStringLiteral("*.sbgm")},QDir::Files,QDir::Name)) {
            const QString name=sidboxTilemapWorldBaseName(file.absoluteFilePath());
            addPlayer(QStringLiteral("@player_world:")+name,
                      tr("Go to %1 (default Player Start)").arg(name));
        }
        // Stage 5.166.71: legacy Property-editor targets may be saved as a
        // cross-world link or as @npc:<world>:<spriteId>. Neither is a local
        // sprite ID, so earlier Visual Nodes silently omitted their wires.
        // Surface them as read-only target cards while retaining the original
        // IDs for the exporter and for exact disconnect operations.
        QSet<QString> referencedTargets;
        for (const QString &source:m_order) {
            const NodeObject node=m_objects.value(source);
            if (isActionSource(node))
                for (const NodeLink &link:node.links)
                    if (supportedAction(link.action))referencedTargets.insert(link.target);
            if (node.type!=QStringLiteral("trigger"))continue;
            for (const NodeLink &link:node.toggleTrueActions)
                if (supportedAction(link.action))referencedTargets.insert(link.target);
            for (const NodeLink &link:node.toggleFalseActions)
                if (supportedAction(link.action))referencedTargets.insert(link.target);
            for (const QJsonValue &entry:node.logicNodes) {
                const QJsonObject logic=entry.toObject();
                for (const QString &field:{QStringLiteral("trueActions"),QStringLiteral("falseActions")})
                    for (const QJsonValue &v:logic.value(field).toArray())
                        if (supportedAction(v.toObject().value(QStringLiteral("action")).toString()))
                            referencedTargets.insert(v.toObject().value(QStringLiteral("objectId")).toString());
            }
        }
        QHash<QString,QJsonObject> siblingWorlds;
        for (const QFileInfo &file:projectDir.entryInfoList(
                 QStringList{QStringLiteral("*.sbgm")},QDir::Files)) {
            QJsonObject design;
            if (readJson(file.absoluteFilePath(),&design))
                siblingWorlds.insert(sidboxTilemapWorldBaseName(file.absoluteFilePath()),design);
        }
        for (const QString &id:referencedTargets) {
            if (id.isEmpty() || m_objects.contains(id))continue;
            QString world, spriteId;
            const bool remote=cgDecodeCrossWorldLink(id,&world,&spriteId);
            const bool npc=id.startsWith(QStringLiteral("@npc:"));
            if (npc) {
                const int split=id.indexOf(QLatin1Char(':'),5);
                if (split>5) {world=id.mid(5,split-5);spriteId=id.mid(split+1);}
            }
            if (!remote && !npc) {
                // A deleted local resource can still be referenced by an old
                // Properties link. Show a clearly broken target rather than
                // hiding the wire and making the saved world appear healthy.
                NodeObject missing;
                missing.id=id;missing.type=QStringLiteral("missing_reference");
                missing.name=tr("MISSING: %1").arg(id);
                m_order.append(id);m_objects.insert(id,missing);
                continue;
            }
            if (world.isEmpty() || spriteId.isEmpty())continue;
            NodeObject reference;
            reference.id=id;reference.type=npc?QStringLiteral("npc_reference"):
                QStringLiteral("world_reference");
            reference.name=tr("MISSING: %1 / %2").arg(world,spriteId);
            const QJsonObject design=siblingWorlds.value(world);
            const QJsonArray resources=design.value(QStringLiteral("resources")).toArray();
            bool found=false;
            for (const QJsonValue &v:resources) {
                const QJsonObject r=v.toObject();
                if (r.value(QStringLiteral("id")).toString()!=spriteId)continue;
                reference.name=tr("%1 / %2").arg(world,
                    r.value(QStringLiteral("name")).toString(spriteId));
                found=true;
                break;
            }
            // A remote NPC must exist in Adventure's NPC table; a remote
            // object must actually be exportable as a world-object slot.
            if (npc) {
                bool valid=false;
                for (const QJsonValue &v:design.value(QStringLiteral("adventure")).toObject()
                         .value(QStringLiteral("npcs")).toArray())
                    if (v.toObject().value(QStringLiteral("spriteId")).toString()==spriteId)
                        {valid=true;break;}
                found=found && valid;
            } else found=found && cgCrossWorldObjectSlot(design,spriteId)>=0;
            if (!found)reference.name=tr("MISSING: %1 / %2").arg(world,spriteId);
            m_order.append(id);m_objects.insert(id,reference);
        }
        // Respect legacy intentionally unlinked dialogue cards, but do not
        // auto-display every unused world object just because it exists.
        for (const QString &id:m_dialogueCards)
            if (m_objects.contains(id) && m_objects.value(id).dialogueNode<0)
                m_placedCards.insert(dialogueCardId(id));
        buildUi();
        renderCards();
        updateCanvasBounds();
        resetGraphHistory();
        // An empty graph is a valid starter document, created only for this world.
        if (!QFileInfo::exists(m_graphPath) && !saveLayout()) {
            QMessageBox::warning(this,tr("Visual Nodes"),tr("Cannot create %1").arg(m_graphPath));
            return false;
        }
        return true;
    }
    bool worldChanged() const { return m_worldChanged; }
    int requestedAdventureDialogue() const {return m_openAdventureDialogue;}
protected:
    void showEvent(QShowEvent *event) override {
        QDialog::showEvent(event);
        if (m_viewReady) return;
        m_viewReady=true;
        // fitInView() during initialise() ran against an unlaid-out viewport.
        // Defer until the maximised dialog and splitter have their final sizes.
        QTimer::singleShot(0,this,[this] {
            if(m_splitter && m_savedPaneWidths.size()==3)
                m_splitter->setSizes(m_savedPaneWidths);
            restoreViewport();
            // First real Qt layout may differ from construction-time sizes.
            // Re-anchor GIVE sockets and refresh their wires after showing.
            redrawLinks();
        });
    }
    void reject() override {
        // Esc is routed through QDialog::reject(), not necessarily closeEvent.
        if (confirmClose()) QDialog::reject();
    }
    void closeEvent(QCloseEvent *event) override {
        if (!confirmClose()) { event->ignore(); return; }
        QDialog::closeEvent(event);
    }
protected:
    bool eventFilter(QObject *watched,QEvent *event) override {
        if (watched==m_list && event->type()==QEvent::KeyPress) {
            auto *key=static_cast<QKeyEvent*>(event);
            if (key->key()==Qt::Key_Delete) {
                removeSelectedNode();
                return true;
            }
        }
        return QDialog::eventFilter(watched,event);
    }
private:
    bool confirmClose() {
        if (m_dirty) {
            const QMessageBox::StandardButton answer = QMessageBox::question(this,tr("Unsaved Visual Nodes"),
                tr("Save node connections and card positions before closing?"),
                QMessageBox::Save|QMessageBox::Discard|QMessageBox::Cancel,QMessageBox::Save);
            if (answer==QMessageBox::Cancel)return false;
            if (answer==QMessageBox::Save && !saveAll())return false;
            // Discard never changes saved node links or positions. Camera is
            // a separate preference and may still be remembered below.
            if (answer==QMessageBox::Discard)m_dirty=false;
        }
        if (!saveViewportOnly())
            QMessageBox::warning(this,tr("Visual Nodes"),
                tr("Could not remember the graph zoom/pan. The saved gameplay and node connections were not changed."));
        return true;
    }
    void restoreViewport() {
        if (!m_view) return;
        // A saved camera must work even after all graph cards were removed.
        if (m_hasStoredView) {
            m_view->resetTransform();
            m_view->scale(m_storedZoom,m_storedZoom);
            // Centre is resolution-independent and works with older .vsgm files.
            m_view->centerOn(m_storedCenter);
            // For the SAME viewport size, exact scrollbar offsets reproduce the
            // previous pan without the QGraphicsView centre/rounding ambiguity.
            if (m_hasStoredScroll && m_storedViewport==m_view->viewport()->size()) {
                m_view->horizontalScrollBar()->setValue(m_storedScroll.x());
                m_view->verticalScrollBar()->setValue(m_storedScroll.y());
            }
            return;
        }
        if (m_cards.isEmpty()) {
            m_view->resetTransform();
            m_view->centerOn(QPointF(0,0));
            return;
        }
        const QRectF bounds=m_scene->itemsBoundingRect().adjusted(-80,-80,80,80);
        const QRect viewport=m_view->viewport()->rect();
        if (bounds.isEmpty() || viewport.width()<10 || viewport.height()<10)return;
        const qreal fit=qMin(viewport.width()/bounds.width(),viewport.height()/bounds.height());
        if (fit>=0.7) {
            m_view->fitInView(bounds,Qt::KeepAspectRatio);
            if (m_view->transform().m11()>1.25) {
                m_view->resetTransform();
                m_view->scale(1.25,1.25);
                m_view->centerOn(bounds.center());
            }
        } else {
            // On dense maps, Fit All makes every card illegibly tiny.
            // Start at a usable scale focused on the first Trigger instead.
            m_view->resetTransform();
            m_view->scale(0.85,0.85);
            QString first=m_order.value(0);
            for (const QString &id:m_order)
                if (m_objects.value(id).type==QStringLiteral("trigger")) { first=id;break; }
            if (NodeCard *card=m_cards.value(first,nullptr))m_view->centerOn(card);
        }
    }
    QRectF cardsBounds() const {
        QRectF result;
        for (NodeCard *card:m_cards) {
            if (!card || !card->isVisible())continue;
            result=result.isNull()?card->sceneBoundingRect():result.united(card->sceneBoundingRect());
        }
        for (FlowGroupBox *group:m_flowGroups) {
            if(!group || !group->isVisible())continue;
            result=result.isNull()?group->sceneBoundingRect():result.united(group->sceneBoundingRect());
        }
        return result;
    }
    void updateCanvasBounds() {
        if (!m_scene)return;
        const QRectF visible=cardsBounds();
        if (visible.isNull())return;
        // A moving card expands the scrollable world immediately. Avoid a
        // fixed-size virtual canvas that clips long graphs at its boundary.
        m_scene->setSceneRect(visible.adjusted(-900,-700,900,700));
    }
    // Unwired/unused sockets are outlined; a wire ending at the socket fills
    // it. This applies to real action wires and read-only dialogue previews.
    void updateSocketStates() {
        QVector<QPointF> starts,ends;
        starts.reserve(m_lines.size());ends.reserve(m_lines.size());
        for(QGraphicsPathItem *wire:m_lines) {
            if(!wire || wire->path().isEmpty())continue;
            starts.append(wire->path().pointAtPercent(0));
            ends.append(wire->path().pointAtPercent(1));
        }
        for(NodeCard *card:m_cards)if(card)for(QGraphicsItem *child:card->childItems()) {
            const QString kind=child->data(0).toString();
            const bool isInput=kind==QStringLiteral("input") ||
                kind==QStringLiteral("npc-input") ||
                kind==QStringLiteral("conversation-input") ||
                kind==QStringLiteral("exchange-input");
            const bool isOutput=kind==QStringLiteral("output") ||
                kind==QStringLiteral("enemy-action-output") ||
                kind==QStringLiteral("conversation-output") ||
                kind==QStringLiteral("conversation-missing-output") ||
                kind==QStringLiteral("exchange-output") ||
                kind==QStringLiteral("give-anchor");
            if(!isInput && !isOutput)continue;
            auto *square=dynamic_cast<QGraphicsRectItem*>(child);
            auto *circle=dynamic_cast<QGraphicsEllipseItem*>(child);
            if(!square && !circle)continue;
            const QBrush brush=square?square->brush():circle->brush();
            if(!child->data(3).isValid())child->setData(3,brush.color());
            const QColor fill=child->data(3).value<QColor>();
            const QPointF socket=child->sceneBoundingRect().center();
            bool connected=false;
            const QVector<QPointF> &points=isInput?ends:starts;
            for(const QPointF &p:points)if(QLineF(socket,p).length()<19.0) {
                connected=true;break;
            }
            // An unused conversation answer has no navigable destination.
            if(kind==QStringLiteral("exchange-output")) {
                const QStringList pieces=card->data(1).toString().split(QLatin1Char(':'));
                if(pieces.size()==3) {
                    const int dialogue=pieces.at(1).toInt(),option=pieces.at(2).toInt();
                    const QJsonObject ex=giveExchange(dialogue,option);
                    const QString key=giveRouteKey(child->data(2).toInt());
                    if(key.isEmpty() || ex.value(key).toInt(-1)<0)connected=false;
                }
            }
            if(kind==QStringLiteral("conversation-output") ||
               kind==QStringLiteral("conversation-missing-output")) {
                bool ok=false;
                const QString cid=card->data(1).toString();
                const int index=cid.mid(QStringLiteral("@conversation:").size()).toInt(&ok);
                const int option=child->data(2).toInt();
                if(ok && index>=0 && index<m_dialogues.size()) {
                    const QJsonArray answers=m_dialogues.at(index).toObject()
                        .value(QStringLiteral("choices")).toArray();
                    if(option>=answers.size() || answers.at(option).toObject()
                        .value(QStringLiteral("text")).toString().trimmed().isEmpty() ||
                       (kind==QStringLiteral("conversation-missing-output") &&
                        answers.at(option).toObject().value(QStringLiteral("requires")).toInt(-1)<0))
                        connected=false;
                }
            }
            // 'Hollow' means outlined with an OPAQUE theme-coloured core.
            // Match the node fill, never let card borders/wires shine through.
            const QBrush socketBrush(connected?fill:m_theme.panelBackground);
            if(square)square->setBrush(socketBrush);
            if(circle)circle->setBrush(socketBrush);
            child->setZValue(qMax(child->zValue(),4.0));
        }
    }
    // Session-only undo history. Snapshot the in-memory game model AND the
    // .vsgm layout: restoring a graph must not undo just the drawing while
    // silently leaving old .sbgm connections in pending state.
    struct GraphHistory {
        QHash<QString,NodeObject> objects;
        QHash<QString,QPointF> positions;
        QSet<QString> placed,collapsed,hiddenNpc,dialogueCards,touched;
        QSet<int> roots,hiddenConversationRoots;
        QHash<QString,QJsonObject> npcRoutes;
        QHash<QString,QString> graphDialogueRoutes;
        QJsonArray dialogues,npcs;
        bool dirty=false,dialoguesChanged=false,npcsChanged=false;
        QByteArray digest;
    };
    QByteArray graphDigest() const {
        QJsonObject data;
        QStringList ids=m_objects.keys();
        std::sort(ids.begin(),ids.end());
        QJsonArray objects;
        for(const QString &id:ids) {
            const NodeObject n=m_objects.value(id);
            QJsonArray actions,yes,no,inputs;
            for(const NodeLink &a:n.links)
                actions.append(QJsonArray{a.target,a.action});
            for(const NodeLink &a:n.toggleTrueActions)
                yes.append(QJsonArray{a.target,a.action});
            for(const NodeLink &a:n.toggleFalseActions)
                no.append(QJsonArray{a.target,a.action});
            for(const QString &input:n.toggleStateInputIds)inputs.append(input);
            objects.append(QJsonObject{
                {QStringLiteral("id"),id},
                {QStringLiteral("links"),actions},
                {QStringLiteral("dialogue"),n.dialogueNode},
                {QStringLiteral("dialogueMode"),n.dialogueMode},
                {QStringLiteral("toggleTarget"),n.toggleStateTargetId},
                {QStringLiteral("toggleOp"),n.toggleStateOperator},
                {QStringLiteral("toggleInputs"),inputs},
                {QStringLiteral("toggleYes"),yes},
                {QStringLiteral("toggleNo"),no},
                {QStringLiteral("toggleYesDialogue"),n.toggleTrueDialogueNode},
                {QStringLiteral("toggleNoDialogue"),n.toggleFalseDialogueNode},
                {QStringLiteral("logic"),n.logicNodes},
                {QStringLiteral("press"),n.triggerPress},
                {QStringLiteral("oneShot"),n.triggerOneShot},
                {QStringLiteral("item"),n.interactItemName},
                {QStringLiteral("npcStart"),n.npcStartNode},
                {QStringLiteral("npcDone"),n.npcDoneNode},
                {QStringLiteral("npcRadius"),n.npcRadius},
                {QStringLiteral("npcVisible"),n.npcInitiallyVisible}
            });
        }
        data.insert(QStringLiteral("objects"),objects);
        data.insert(QStringLiteral("dialogues"),m_dialogues);
        data.insert(QStringLiteral("npcs"),m_npcEntries);
        QJsonObject positions,routes;
        QStringList positionsKeys=m_positions.keys();std::sort(positionsKeys.begin(),positionsKeys.end());
        for(const QString &id:positionsKeys) {
            const QPointF point=m_positions.value(id);
            positions.insert(id,QJsonArray{point.x(),point.y()});
        }
        data.insert(QStringLiteral("positions"),positions);
        QStringList routeKeys=m_npcDialogueRoutes.keys();std::sort(routeKeys.begin(),routeKeys.end());
        for(const QString &id:routeKeys)routes.insert(id,m_npcDialogueRoutes.value(id));
        data.insert(QStringLiteral("routes"),routes);
        QJsonObject sharedRoutes;
        QStringList sharedKeys=m_graphDialogueRoutes.keys();std::sort(sharedKeys.begin(),sharedKeys.end());
        for(const QString &id:sharedKeys)sharedRoutes.insert(id,m_graphDialogueRoutes.value(id));
        data.insert(QStringLiteral("graphDialogueRoutes"),sharedRoutes);
        const auto addStringSet=[&](const QString &key,const QSet<QString> &values) {
            QStringList sorted=values.values();std::sort(sorted.begin(),sorted.end());
            QJsonArray array;for(const QString &value:sorted)array.append(value);
            data.insert(key,array);
        };
        addStringSet(QStringLiteral("placed"),m_placedCards);
        addStringSet(QStringLiteral("collapsed"),m_collapsedCards);
        addStringSet(QStringLiteral("hiddenNpc"),m_hiddenNpcCards);
        addStringSet(QStringLiteral("dialogueCards"),m_dialogueCards);
        QList<int> sortedRoots=m_conversationRoots.values();std::sort(sortedRoots.begin(),sortedRoots.end());
        QJsonArray roots;for(const int root:sortedRoots)roots.append(root);
        data.insert(QStringLiteral("roots"),roots);
        QList<int> hiddenRoots=m_hiddenConversationRoots.values();std::sort(hiddenRoots.begin(),hiddenRoots.end());
        QJsonArray hidden;for(const int root:hiddenRoots)hidden.append(root);
        data.insert(QStringLiteral("hiddenConversationRoots"),hidden);
        return QCryptographicHash::hash(QJsonDocument(data).toJson(QJsonDocument::Compact),
                                        QCryptographicHash::Sha256);
    }
    GraphHistory captureGraphHistory() const {
        GraphHistory snap;
        snap.objects=m_objects;snap.positions=m_positions;
        snap.placed=m_placedCards;snap.collapsed=m_collapsedCards;
        snap.hiddenNpc=m_hiddenNpcCards;snap.dialogueCards=m_dialogueCards;
        snap.touched=m_touched;snap.roots=m_conversationRoots;
        snap.hiddenConversationRoots=m_hiddenConversationRoots;
        snap.npcRoutes=m_npcDialogueRoutes;
        snap.graphDialogueRoutes=m_graphDialogueRoutes;
        snap.dialogues=m_dialogues;snap.npcs=m_npcEntries;
        snap.dirty=m_dirty;snap.dialoguesChanged=m_dialoguesChanged;
        snap.npcsChanged=m_npcsChanged;
        snap.digest=graphDigest();
        return snap;
    }
    void updateUndoButtons() {
        if(m_historyUndoButton)m_historyUndoButton->setEnabled(m_historyPos>0);
        if(m_historyRedoButton)m_historyRedoButton->setEnabled(
            m_historyPos>=0 && m_historyPos+1<m_history.size());
    }
    void resetGraphHistory() {
        m_history.clear();m_history.append(captureGraphHistory());
        m_historyPos=0;m_historyObserved=m_history.first().digest;
        m_historyQuiet=0;updateUndoButtons();
        if(!m_historyWatch) {
            m_historyWatch=new QTimer(this);
            m_historyWatch->setInterval(120);
            connect(m_historyWatch,&QTimer::timeout,this,[this] {
                if(m_restoringHistory || m_history.isEmpty())return;
                const QByteArray digest=graphDigest();
                if(digest!=m_historyObserved) {
                    m_historyObserved=digest;m_historyQuiet=0;
                } else if(digest!=m_history[m_historyPos].digest && ++m_historyQuiet>=3)
                    recordHistoryNow();
            });
            m_historyWatch->start();
        }
    }
    void recordHistoryNow() {
        if(m_restoringHistory || m_history.isEmpty())return;
        GraphHistory now=captureGraphHistory();
        if(now.digest==m_history[m_historyPos].digest)return;
        while(m_history.size()>m_historyPos+1)m_history.removeLast();
        m_history.append(now);
        if(m_history.size()>80)m_history.removeFirst();
        m_historyPos=m_history.size()-1;
        m_historyObserved=now.digest;m_historyQuiet=0;
        updateUndoButtons();
    }
    void restoreGraphHistory(const GraphHistory &snap) {
        m_restoringHistory=true;
        // Clear scene-owned cards, proxy widgets, sockets and wires before
        // regenerating from the restored real .sbgm model state.
        m_cards.clear();m_lines.clear();
        m_liveWiresByCard.clear();m_liveWirePositions.clear();m_liveWireDrag=false;
        m_dialogueControls.clear();m_booleanSourceLabels.clear();
        m_logicTitles.clear();m_logicNotes.clear();
        // QGraphicsScene::clear() DELETES every scene-owned graphics item,
        // including FlowGroupBox and its child title/fold controls. The hash
        // is non-owning and must be invalidated FIRST. Otherwise renderCards()
        // reuses dangling FlowGroupBox pointers during Undo/Redo (use-after-free).
        m_flowGroups.clear();
        m_scene->clear();m_list->clear();
        m_selectedCardId.clear();m_multiSelectedCards.clear();m_selectedWireKey.clear();
        m_objects=snap.objects;m_positions=snap.positions;
        m_placedCards=snap.placed;m_collapsedCards=snap.collapsed;
        m_hiddenNpcCards=snap.hiddenNpc;m_dialogueCards=snap.dialogueCards;
        m_touched=snap.touched;m_conversationRoots=snap.roots;
        m_hiddenConversationRoots=snap.hiddenConversationRoots;
        m_npcDialogueRoutes=snap.npcRoutes;
        m_graphDialogueRoutes=snap.graphDialogueRoutes;
        m_dialogues=snap.dialogues;m_npcEntries=snap.npcs;
        m_dialoguesChanged=snap.dialoguesChanged;m_npcsChanged=snap.npcsChanged;
        renderCards();updateCanvasBounds();showDetails(QString());
        m_dirty=snap.dirty;
        m_restoringHistory=false;
        // Some virtual cards are materialised during rendering; reconcile the
        // restored snapshot so an immediate Redo never treats those cards as
        // a fresh user edit and clears the redo stack.
        if(m_historyPos>=0 && m_historyPos<m_history.size())
            m_history[m_historyPos]=captureGraphHistory();
        m_historyObserved=m_history[m_historyPos].digest;m_historyQuiet=0;
        updateUndoButtons();
    }
    void undoGraph() {
        recordHistoryNow();
        if(m_historyPos<=0)return;
        --m_historyPos;
        restoreGraphHistory(m_history.at(m_historyPos));
        m_status->setText(tr("Undo: restored earlier nodes, connections and layout."));
    }
    void redoGraph() {
        recordHistoryNow();
        if(m_historyPos+1>=m_history.size())return;
        ++m_historyPos;
        restoreGraphHistory(m_history.at(m_historyPos));
        m_status->setText(tr("Redo: reapplied nodes, connections and layout."));
    }
    void tidyCards() {
        if(!m_view || m_cards.size()<2)return;
        if(QMessageBox::question(this,tr("Tidy Visual Nodes"),
            tr("Arrange connected nodes into compact conversation and logic branches?\n\n"
               "Only card positions change. Connections and dialogue IDs stay unchanged.\n"
               "Use Ctrl+Z to undo the arrangement."),
            QMessageBox::Yes|QMessageBox::Cancel,QMessageBox::Cancel)!=QMessageBox::Yes)return;
        recordHistoryNow(); // Preserve any pending drag/text edit as its own step.
        redrawLinks();
        QHash<QString,QSet<QString>> adjacent,outgoing,incoming;
        auto endpointCard=[this](const QPointF &p,bool from)->QString {
            QString nearest;
            qreal best=40.0;
            for(auto it=m_cards.cbegin();it!=m_cards.cend();++it) {
                const QRectF r=it.value()->sceneBoundingRect();
                const qreal dx=p.x()-(from?r.right():r.left());
                const qreal dy=p.y()<r.top()?r.top()-p.y():
                    p.y()>r.bottom()?p.y()-r.bottom():0.0;
                const qreal distance=std::hypot(dx,dy);
                if(distance<best){best=distance;nearest=it.key();}
            }
            return nearest;
        };
        for(QGraphicsPathItem *wire:m_lines) {
            if(!wire || wire->path().isEmpty())continue;
            const QString from=endpointCard(wire->path().pointAtPercent(0),true);
            const QString to=endpointCard(wire->path().pointAtPercent(1),false);
            if(from.isEmpty() || to.isEmpty() || from==to)continue;
            adjacent[from].insert(to);adjacent[to].insert(from);
            outgoing[from].insert(to);incoming[to].insert(from);
        }
        QStringList original=m_cards.keys();
        std::sort(original.begin(),original.end(),[this](const QString &a,const QString &b) {
            const QPointF pa=m_cards.value(a)->pos(),pb=m_cards.value(b)->pos();
            return pa.y()==pb.y()?pa.x()<pb.x():pa.y()<pb.y();
        });
        // Weakly connected components keep unrelated quest chains separate.
        QSet<QString> unseen;
        for(const QString &id:original)unseen.insert(id);
        QVector<QStringList> groups;
        for(const QString &seed:original) {
            if(!unseen.contains(seed))continue;
            QStringList component,queue{seed};unseen.remove(seed);
            for(int i=0;i<queue.size();++i) {
                const QString id=queue.at(i);component.append(id);
                QStringList neighbours=adjacent.value(id).values();
                std::sort(neighbours.begin(),neighbours.end());
                for(const QString &next:neighbours)
                    if(unseen.remove(next))queue.append(next);
            }
            groups.append(component);
        }
        qreal left=0,top=0;
        bool first=true;
        for(NodeCard *card:m_cards)if(card) {
            if(first){left=card->pos().x();top=card->pos().y();first=false;}
            else {left=qMin(left,card->pos().x());top=qMin(top,card->pos().y());}
        }
        qreal groupY=top;
        for(const QStringList &group:groups) {
            QSet<QString> members;
            for(const QString &id:group)members.insert(id);
            // Layering uses a Kahn traversal. When a component has feedback
            // cycles, release the leftmost remaining node as an extra root,
            // instead of getting trapped or giving the whole cycle depth 0.
            QHash<QString,int> pending,level;
            QSet<QString> remaining=members;
            for(const QString &id:group) {
                int n=0;
                for(const QString &src:incoming.value(id))if(members.contains(src))++n;
                pending.insert(id,n);level.insert(id,0);
            }
            QStringList ready;
            for(const QString &id:group)if(!pending.value(id))ready.append(id);
            while(!remaining.isEmpty()) {
                if(ready.isEmpty()) {
                    QString seed;
                    for(const QString &id:group)if(remaining.contains(id) &&
                        (seed.isEmpty() || m_cards.value(id)->pos().x()<m_cards.value(seed)->pos().x()))seed=id;
                    ready.append(seed);
                }
                const QString id=ready.takeFirst();
                if(!remaining.remove(id))continue;
                QStringList children=outgoing.value(id).values();
                std::sort(children.begin(),children.end(),[this](const QString &a,const QString &b) {
                    return m_cards.value(a)->pos().y()<m_cards.value(b)->pos().y();
                });
                for(const QString &dst:children)if(remaining.contains(dst)) {
                    level[dst]=qMax(level.value(dst),level.value(id)+1);
                    pending[dst]=pending.value(dst)-1;
                    if(pending.value(dst)<=0)ready.append(dst);
                }
            }
            QMap<int,QStringList> columns;
            for(const QString &id:group)columns[level.value(id)].append(id);
            // Barycentric crossing reduction: average connected neighbour
            // ordering over repeated forward/backward sweeps, rather than
            // dumping all same-depth nodes in arbitrary column order.
            QHash<QString,qreal> rank;
            for(auto it=columns.begin();it!=columns.end();++it) {
                auto &column=it.value();
                std::sort(column.begin(),column.end(),[this](const QString &a,const QString &b) {
                    return m_cards.value(a)->pos().y()<m_cards.value(b)->pos().y();
                });
                for(int n=0;n<column.size();++n)rank[column[n]]=n;
            }
            for(int pass=0;pass<8;++pass) {
                const bool forward=(pass%2==0);
                QList<int> keys=columns.keys();
                if(!forward)std::reverse(keys.begin(),keys.end());
                for(const int layer:keys) {
                    auto &column=columns[layer];
                    QHash<QString,qreal> desired;
                    for(const QString &id:column) {
                        const QSet<QString> neighbours=forward?incoming.value(id):outgoing.value(id);
                        qreal sum=0;int count=0;
                        for(const QString &near:neighbours)if(members.contains(near) &&
                            level.value(near)==layer+(forward?-1:1)) {
                            sum+=rank.value(near);++count;
                        }
                        desired.insert(id,count?sum/count:rank.value(id));
                    }
                    std::stable_sort(column.begin(),column.end(),[&](const QString &a,const QString &b) {
                        return desired.value(a)<desired.value(b);
                    });
                    for(int n=0;n<column.size();++n)rank[column[n]]=n;
                }
            }
            QHash<int,qreal> columnX;
            qreal x=left;
            for(auto it=columns.cbegin();it!=columns.cend();++it) {
                columnX.insert(it.key(),x);
                qreal width=0;
                for(const QString &id:it.value())width=qMax(width,m_cards.value(id)->rect().width());
                x+=width+100.0;
            }
            // Position children near their immediate parents, and center
            // parents between downstream branches where space permits.
            QHash<QString,qreal> centers;
            qreal minTop=1e30,maxBottom=-1e30;
            for(auto it=columns.cbegin();it!=columns.cend();++it) {
                const QStringList column=it.value();
                qreal cursor=groupY;
                for(int i=0;i<column.size();++i) {
                    const QString id=column.at(i);
                    NodeCard *card=m_cards.value(id);
                    const qreal h=card->rect().height();
                    qreal target=groupY+rank.value(id)*(h+65.0)+h/2.0;
                    qreal sum=0;int count=0;
                    for(const QString &parent:incoming.value(id))if(centers.contains(parent)) {
                        sum+=centers.value(parent);++count;
                    }
                    if(count)target=sum/count+(i-(column.size()-1)/2.0)*28.0;
                    const qreal y=qMax(cursor,target-h/2.0);
                    card->setPos(QPointF(columnX.value(it.key()),y));
                    centers.insert(id,y+h/2.0);
                    cursor=y+h+54.0;
                    minTop=qMin(minTop,y);maxBottom=qMax(maxBottom,y+h);
                }
            }
            // Recursive-style branch centering: pull upstream decision nodes
            // towards the average centers of their downstream children. This
            // makes a fork appear as a family instead of unrelated rows.
            // Respect existing order and minimum vertical gaps on each pass.
            for(int pass=0;pass<3;++pass) {
                QList<int> layers=columns.keys();
                std::reverse(layers.begin(),layers.end());
                for(const int layer:layers) {
                    const QStringList column=columns.value(layer);
                    qreal cursor=-1e30;
                    for(const QString &id:column) {
                        NodeCard *card=m_cards.value(id);
                        const qreal height=card->rect().height();
                        qreal total=0;int count=0;
                        for(const QString &child:outgoing.value(id))
                            if(level.value(child)>layer && centers.contains(child)) {
                                total+=centers.value(child);++count;
                            }
                        const qreal oldCenter=card->pos().y()+height/2.0;
                        const qreal wanted=count?(oldCenter+2.0*total/count)/3.0:oldCenter;
                        const qreal y=qMax(cursor,wanted-height/2.0);
                        card->setPos(QPointF(card->pos().x(),y));
                        centers[id]=y+height/2.0;
                        cursor=y+height+54.0;
                    }
                }
            }
            // Recompute bounds after branch centering (the previous height
            // measurements were from the first placement pass).
            minTop=1e30;maxBottom=-1e30;
            for(const QString &id:group) {
                NodeCard *card=m_cards.value(id);
                minTop=qMin(minTop,card->pos().y());
                maxBottom=qMax(maxBottom,card->pos().y()+card->rect().height());
            }
            // Recenter the entire component rather than spreading each
            // column from its independent origin.
            const qreal shift=groupY-minTop;
            for(const QString &id:group) {
                NodeCard *card=m_cards.value(id);
                card->setPos(card->pos()+QPointF(0,shift));
                m_positions[id]=card->pos();
            }
            groupY+=maxBottom-minTop+130.0;
        }
        m_dirty=true;
        redrawLinks();updateCanvasBounds();
        recordHistoryNow();
        m_status->setText(tr("Tidy grouped %1 connected/isolated node clusters. Ctrl+Z restores the previous arrangement.")
            .arg(groups.size()));
    }
    void fitAllCards() {
        const QRectF visible=cardsBounds();
        if (visible.isNull() || !m_view)return;
        updateCanvasBounds();
        // Reset saved pan/zoom influence: Fit All means ALL actual cards,
        // including cards added far outside the old scene rectangle.
        m_view->resetTransform();
        m_view->fitInView(visible.adjusted(-110,-110,110,110),Qt::KeepAspectRatio);
    }
    QPointF viewportInsertionPoint(const QSizeF &size=QSizeF(250,130)) {
        const QPointF center=m_view->mapToScene(m_view->viewport()->rect().center());
        // Search nearby locations, not absolute scene coordinates. Respect
        // whatever part of the graph the designer is currently looking at.
        const qreal stepX=qMax<qreal>(size.width()+45.0,300.0);
        const qreal stepY=qMax<qreal>(size.height()+45.0,175.0);
        for (int ring=0;ring<12;++ring) {
            for (int dy=-ring;dy<=ring;++dy)for (int dx=-ring;dx<=ring;++dx) {
                if (ring>0 && qMax(qAbs(dx),qAbs(dy))!=ring)continue;
                const QPointF candidate=center-QPointF(size.width()*.5,size.height()*.5)
                    +QPointF(dx*stepX,dy*stepY);
                const QRectF target(candidate,size);
                bool occupied=false;
                for(NodeCard *card:m_cards)if(card &&
                    target.adjusted(-18,-18,18,18).intersects(card->sceneBoundingRect())) {
                    occupied=true;break;
                }
                if(!occupied)return candidate;
            }
        }
        return center-QPointF(size.width()*.5,size.height()*.5);
    }
    void addFoldButton(NodeCard *card,const QString &id) {
        auto *button=new NodeFoldButton(card);
        card->setFoldButton(button);
        button->clicked=[this,id,card] {
            const bool next=!card->collapsed();
            card->setCollapsed(next);
            if(next)m_collapsedCards.insert(id);else m_collapsedCards.remove(id);
            m_dirty=true;
            if(id.startsWith(QStringLiteral("@conversation:")) ||
               id.startsWith(QStringLiteral("@give:")))updateConversationFlowGroups();
            redrawLinks();
        };
        if (m_collapsedCards.contains(id))card->setCollapsed(true);
    }
    QJsonObject viewportJson() const {
        QJsonObject view;
        if (!m_view || !m_viewReady)return view;
        const QPointF center=m_view->mapToScene(m_view->viewport()->rect().center());
        view.insert(QStringLiteral("zoom"),m_view->transform().m11());
        view.insert(QStringLiteral("center"),QJsonArray{center.x(),center.y()});
        view.insert(QStringLiteral("scrollbars"),QJsonArray{
            m_view->horizontalScrollBar()->value(),m_view->verticalScrollBar()->value()});
        view.insert(QStringLiteral("viewportPixels"),QJsonArray{
            m_view->viewport()->width(),m_view->viewport()->height()});
        return view;
    }
    bool saveViewportOnly() {
        if (!m_viewReady || !m_view)return true;
        QFile existing(m_graphPath);
        if (!existing.open(QIODevice::ReadOnly))return false;
        const QByteArray input=existing.readAll();
        if (QCryptographicHash::hash(input,QCryptographicHash::Sha256)!=m_layoutHash)
            return false; // Another editor modified the graph; never overwrite it.
        QJsonParseError error;
        const QJsonDocument doc=QJsonDocument::fromJson(input,&error);
        if (error.error!=QJsonParseError::NoError || !doc.isObject())return false;
        QJsonObject graph=doc.object();
        const QJsonObject view=viewportJson();
        const QList<int> widths=m_splitter?m_splitter->sizes():QList<int>();
        QJsonArray paneWidths;
        for(int width:widths)paneWidths.append(width);
        if (graph.value(QStringLiteral("view")).toObject()==view &&
            graph.value(QStringLiteral("paneWidths")).toArray()==paneWidths)return true;
        graph.insert(QStringLiteral("view"),view);
        if(widths.size()==3)graph.insert(QStringLiteral("paneWidths"),paneWidths);
        if (!writeJson(m_graphPath,graph))return false;
        m_layoutHash=QCryptographicHash::hash(
            QJsonDocument(graph).toJson(QJsonDocument::Indented),QCryptographicHash::Sha256);
        return true;
    }
    void buildUi() {
        auto *main = new QVBoxLayout(this);
        auto *toolbar = new QHBoxLayout;
        auto *title = new QLabel(tr("%1  |  VISUAL NODE GRAPH").arg(m_worldName),this);
        QFont font=title->font();font.setBold(true);font.setPointSize(font.pointSize()+2);title->setFont(font);
        toolbar->addWidget(title);
        toolbar->addStretch();
        auto *zoomOut=new QPushButton(tr("−"),this);
        auto *zoomIn=new QPushButton(tr("+"),this);
        auto *fit=new QPushButton(tr("Fit All"),this);
        auto *tidy=new QPushButton(tr("Tidy"),this);
        m_historyUndoButton=new QPushButton(tr("Undo"),this);
        m_historyRedoButton=new QPushButton(tr("Redo"),this);
        m_historyUndoButton->setEnabled(false);
        m_historyRedoButton->setEnabled(false);
        m_historyUndoButton->setToolTip(tr("Undo the last node/wire/property/layout edit (Ctrl+Z)."));
        m_historyRedoButton->setToolTip(tr("Redo the last undone edit (Ctrl+Shift+Z or Ctrl+Y)."));
        tidy->setToolTip(tr("Group connected cards into readable columns. Changes positions only; does not change game events."));
        auto *refresh=new QPushButton(tr("Refresh from World"),this);
        refresh->setToolTip(tr("Re-read Game Object, NPC conversation and Dialogue Editor links from .sbgm. Preserve the .vsgm layout."));
        auto *addCondition=new QPushButton(tr("+ Boolean"),this);
        addCondition->setToolTip(tr("Select an enemy or a Trigger-controlled Game Object, then add Boolean logic that reads its active state."));
        auto *conversationFlow=new QPushButton(tr("+ Conversation Flow"),this);
        conversationFlow->setToolTip(tr("Edit an NPC's existing conversation: speaker, text, answers and next dialogue. For advanced actions, open the exact dialogue in Adventure Editor."));
        auto *addDialogue=new QPushButton(tr("+ Show Dialogue"),this);
        addDialogue->setToolTip(tr("Select a Trigger, then add its inline Show Dialogue card."));
        auto *save=new QPushButton(tr("Save Graph + World"),this);
        auto *closeButton=new QPushButton(tr("Close"),this);
        for (auto *b:{zoomOut,zoomIn,fit,tidy,m_historyUndoButton,m_historyRedoButton,refresh,addCondition,addDialogue,conversationFlow,save,closeButton}) toolbar->addWidget(b);
        main->addLayout(toolbar);
        auto *split=new QSplitter(Qt::Horizontal,this);
        m_splitter=split;
        split->setChildrenCollapsible(false);
        split->setHandleWidth(6);
        auto *left=new QWidget(split);
        left->setMinimumWidth(130);
        auto *leftLayout=new QVBoxLayout(left);
        leftLayout->setContentsMargins(6,6,6,6);
        leftLayout->addWidget(new QLabel(tr("VISIBLE NODES"),left));
        m_treeSearch=new QLineEdit(left);
        m_treeSearch->setPlaceholderText(tr("Find a node...") );
        m_treeSearch->setClearButtonEnabled(true);
        leftLayout->addWidget(m_treeSearch);
        m_visibleTree=new QTreeWidget(left);
        m_visibleTree->setHeaderHidden(true);
        m_visibleTree->setUniformRowHeights(true);
        m_visibleTree->setSelectionMode(QAbstractItemView::SingleSelection);
        m_visibleTree->setToolTip(tr("Browse cards by type and conversation flow. Double-click to locate a node on the canvas."));
        leftLayout->addWidget(m_visibleTree,1);
        // Preserve the established list-based card registration in all node
        // constructors; its rows are mirrored into the visible grouped tree.
        m_list=new QListWidget(this);
        m_list->hide();
        m_list->installEventFilter(this);
        m_scene=new QGraphicsScene(this);
        m_scene->setSceneRect(-1400,-1000,2800,2000);
        m_view=new NodeCanvas(m_scene,split);
        m_view->setMinimumWidth(280);
        m_view->setBackgroundBrush(m_theme.editorBackground);
        auto *right=new QWidget(split);
        right->setMinimumWidth(185);
        auto *rightLayout=new QVBoxLayout(right);
        rightLayout->setContentsMargins(6,6,6,6);
        m_inspectorTitle=new QLabel(tr("SELECT A NODE OR WIRE"),right);
        QFont inspectorFont=m_inspectorTitle->font();
        inspectorFont.setBold(true);inspectorFont.setPointSize(inspectorFont.pointSize()+1);
        m_inspectorTitle->setFont(inspectorFont);
        m_inspectorTitle->setWordWrap(true);
        rightLayout->addWidget(m_inspectorTitle);
        m_inspectorType=new QLabel(tr("Details of the selection appear here."),right);
        m_inspectorType->setWordWrap(true);
        m_inspectorType->setStyleSheet(QStringLiteral("color:%1;").arg(m_theme.mutedText.name()));
        rightLayout->addWidget(m_inspectorType);
        m_inspectorTree=new QTreeWidget(right);
        m_inspectorTree->setColumnCount(2);
        m_inspectorTree->setHeaderLabels({tr("Property"),tr("Value")});
        m_inspectorTree->setRootIsDecorated(false);
        m_inspectorTree->setAlternatingRowColors(true);
        m_inspectorTree->setSelectionMode(QAbstractItemView::NoSelection);
        m_inspectorTree->setTextElideMode(Qt::ElideRight);
        m_inspectorTree->setMinimumHeight(155);
        m_inspectorTree->header()->setStretchLastSection(true);
        m_inspectorTree->header()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
        rightLayout->addWidget(m_inspectorTree,1);
        m_technicalButton=new QPushButton(tr("Show technical notes"),right);
        m_technicalButton->setCheckable(true);
        m_technicalButton->setToolTip(tr("Show the longer reference notes for the selected node."));
        rightLayout->addWidget(m_technicalButton);
        m_details=new QTextEdit(right);
        m_details->setReadOnly(true);
        m_details->setVisible(false);
        rightLayout->addWidget(m_details,1);
        connect(m_technicalButton,&QPushButton::toggled,this,[this](bool open) {
            m_details->setVisible(open);
            m_technicalButton->setText(open?tr("Hide technical notes"):tr("Show technical notes"));
        });
        m_actionsHeader=new QLabel(tr("ACTION CONNECTIONS"),right);
        rightLayout->addWidget(m_actionsHeader);
        m_linksList=new QListWidget(right);
        m_linksList->setMinimumHeight(130);
        m_linksList->setToolTip(tr("Select an action here to edit or remove it without clicking a wire."));
        rightLayout->addWidget(m_linksList);
        auto *linkButtons=new QHBoxLayout;
        m_editLinkButton=new QPushButton(tr("Edit Action"),right);
        m_removeLinkButton=new QPushButton(tr("Remove"),right);
        m_editLinkButton->setEnabled(false);
        m_removeLinkButton->setEnabled(false);
        linkButtons->addWidget(m_editLinkButton);
        linkButtons->addWidget(m_removeLinkButton);
        rightLayout->addLayout(linkButtons);
        rightLayout->addWidget(new QLabel(tr("CANVAS CLEANUP"),right));
        auto *cleanupButtons=new QHBoxLayout;
        m_removeSelectedButton=new QPushButton(tr("Delete Selected"),right);
        m_removeSelectedButton->setToolTip(tr("Delete selected graph card and disconnect its actions. The real Game Object, NPC or dialogue is never deleted."));
        m_removeSelectedButton->setEnabled(false);
        m_removeOrphansButton=new QPushButton(tr("Remove Orphans"),right);
        m_removeOrphansButton->setToolTip(tr("Remove all cards without a gameplay connection. Does not change .sbgm."));
        cleanupButtons->addWidget(m_removeSelectedButton);
        cleanupButtons->addWidget(m_removeOrphansButton);
        rightLayout->addLayout(cleanupButtons);
        split->addWidget(left);split->addWidget(m_view);split->addWidget(right);
        split->setStretchFactor(0,0);
        split->setStretchFactor(1,1);
        split->setStretchFactor(2,0);
        split->setSizes({255,1000,340});
        main->addWidget(split,1);
        m_status=new QLabel(tr("Ready"),this);
        m_status->setToolTip(tr("Game logic is saved in .sbgm; node layout and pane sizes are saved in .vsgm."));
        m_status->setWordWrap(true);
        main->addWidget(m_status);
        connect(zoomOut,&QPushButton::clicked,this,[this] {m_view->zoom(.8);});
        connect(zoomIn,&QPushButton::clicked,this,[this] {m_view->zoom(1.25);});
        connect(fit,&QPushButton::clicked,this,[this] {fitAllCards();});
        connect(tidy,&QPushButton::clicked,this,[this] {tidyCards();});
        connect(m_historyUndoButton,&QPushButton::clicked,this,[this] {undoGraph();});
        connect(m_historyRedoButton,&QPushButton::clicked,this,[this] {redoGraph();});
        // In a QGraphicsProxyWidget, preserve ordinary text-field Undo/Redo.
        // Everywhere else these shortcuts restore whole graph transactions.
        const auto setupHistoryShortcut=[this](const QString &keys,bool redo) {
            auto *shortcut=new QShortcut(QKeySequence(keys),this);
            shortcut->setContext(Qt::WidgetWithChildrenShortcut);
            connect(shortcut,&QShortcut::activated,this,[this,redo] {
                QWidget *focus=QApplication::focusWidget();
                if(auto *edit=qobject_cast<QLineEdit*>(focus)) {
                    if(redo)edit->redo();else edit->undo();return;
                }
                if(auto *edit=qobject_cast<QPlainTextEdit*>(focus)) {
                    if(redo)edit->redo();else edit->undo();return;
                }
                if(auto *edit=qobject_cast<QTextEdit*>(focus)) {
                    if(redo)edit->redo();else edit->undo();return;
                }
                if(redo)redoGraph();else undoGraph();
            });
        };
        setupHistoryShortcut(QStringLiteral("Ctrl+Z"),false);
        setupHistoryShortcut(QStringLiteral("Ctrl+Shift+Z"),true);
        setupHistoryShortcut(QStringLiteral("Ctrl+Y"),true);
        connect(refresh,&QPushButton::clicked,this,[this] {
            if(m_dirty) {
                const auto answer=QMessageBox::question(this,tr("Refresh from World"),
                    tr("You have unsaved graph changes. Save them before refreshing?\n\n"
                       "Yes: save and refresh. No: discard pending edits and refresh. Cancel: stay here."),
                    QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel,QMessageBox::Cancel);
                if(answer==QMessageBox::Cancel)return;
                if(answer==QMessageBox::Yes && !saveAll())return;
                // Discard changes only in memory; the saved .sbgm and .vsgm
                // are never rewritten on this path.
            }
            done(2); // openGameVisualNodes creates a new dialog from disk.
        });
        connect(addDialogue,&QPushButton::clicked,this,[this] { addDialogueCard(); });
        connect(conversationFlow,&QPushButton::clicked,this,[this,conversationFlow] {
            showConversationFlowPicker(conversationFlow);
        });
        connect(addCondition,&QPushButton::clicked,this,[this] {
            createGraphLogic(m_selectedCardId,viewportInsertionPoint(),QStringLiteral("boolean"));
        });
        connect(save,&QPushButton::clicked,this,[this] {saveAll();});
        connect(closeButton,&QPushButton::clicked,this,[this] {this->close();});
        m_view->connectionRequested=[this](const QString &from,const QString &to,const QString &port) {
            addConnection(from,to,port);
        };
        m_view->conversationConnectionRequested=[this](const QString &from,int option,bool missing,const QString &to) {
            if(from.startsWith(QStringLiteral("@give:"))) {
                int dialogue=-1,answer=-1;
                bool targetOk=false;
                const int target=to.mid(QStringLiteral("@conversation:").size()).toInt(&targetOk);
                if(targetOk && target>=0 && target<m_dialogues.size() &&
                   giveCardReference(from,&dialogue,&answer))
                    setGiveDestination(dialogue,answer,option,target);
                return;
            }
            bool sourceOk=false,targetOk=false;
            const int source=from.mid(QStringLiteral("@conversation:").size()).toInt(&sourceOk);
            const int target=to.mid(QStringLiteral("@conversation:").size()).toInt(&targetOk);
            if(!sourceOk || !targetOk || source<0 || source>=m_dialogues.size() ||
               target<0 || target>=m_dialogues.size() || option<0 || option>=3)return;
            const QJsonArray choices=m_dialogues.at(source).toObject().value(QStringLiteral("choices")).toArray();
            const QJsonObject answer=option<choices.size()?choices.at(option).toObject():QJsonObject();
            if(answer.value(QStringLiteral("text")).toString().trimmed().isEmpty() ||
               (missing && answer.value(QStringLiteral("requires")).toInt(-1)<0)) {
                m_status->setText(tr("Enter an answer and select its required inventory item in Adventure Editor before connecting this route."));
                return;
            }
            setConversationAnswer(source,option,missing?QStringLiteral("missingNext"):QStringLiteral("next"),target);
            m_status->setText(missing?
                tr("Missing-item branch: dialogue #%1 answer %2 → #%3").arg(source).arg(option+1).arg(target):
                tr("Answer branch: dialogue #%1 answer %2 → #%3").arg(source).arg(option+1).arg(target));
        };
        m_view->conversationDropRequested=[this](const QString &from,int option,bool missing,const QPoint &) {
            if(from.startsWith(QStringLiteral("@give:"))) {
                int dialogue=-1,answer=-1;
                if(!giveCardReference(from,&dialogue,&answer))return;
                const QJsonObject exchange=giveExchange(dialogue,answer);
                const QString key=giveRouteKey(option);
                if(key.isEmpty())return;
                int selected=exchange.value(key).toInt(-1);
                if(browseConversationDestination(selected,&selected,false,true))
                    setGiveDestination(dialogue,answer,option,selected);
                return;
            }
            bool sourceOk=false;
            const int source=from.mid(QStringLiteral("@conversation:").size()).toInt(&sourceOk);
            if(!sourceOk || source<0 || source>=m_dialogues.size() || option<0 || option>=3)return;
            const QJsonArray choices=m_dialogues.at(source).toObject().value(QStringLiteral("choices")).toArray();
            const QJsonObject answer=option<choices.size()?choices.at(option).toObject():QJsonObject();
            if(answer.value(QStringLiteral("text")).toString().trimmed().isEmpty() ||
               (missing && answer.value(QStringLiteral("requires")).toInt(-1)<0))return;
            const QString field=missing?QStringLiteral("missingNext"):QStringLiteral("next");
            int chosen=answer.value(field).toInt(-1);
            if(browseConversationDestination(chosen,&chosen,missing))
                setConversationAnswer(source,option,field,chosen);
        };
        m_view->giveAnchorDropped=[this](const QString &from,int answer,
                                          const QPointF &point,const QString &onto) {
            bool ok=false;
            const int dialogue=from.mid(QStringLiteral("@conversation:").size()).toInt(&ok);
            if(!ok || !from.startsWith(QStringLiteral("@conversation:")) ||
               dialogue<0 || dialogue>=m_dialogues.size() || answer<0 || answer>=3)return;
            const QJsonObject exchange=giveExchange(dialogue,answer);
            if(!exchange.value(QStringLiteral("enabled")).toBool(false))return;
            const QString targetId=giveCardId(dialogue,answer);
            // A GIVE card belongs to this exact dialogue answer. Dropping
            // over another node must NEVER reassign or duplicate the rule.
            if(!onto.isEmpty() && onto!=targetId) {
                m_status->setText(tr("GIVE belongs to Dialogue #%1, answer %2. Drop on empty canvas to move its existing card.")
                    .arg(dialogue).arg(answer+1));
                return;
            }
            if(!m_cards.contains(targetId)) {
                // A saved layout may have hidden the card; recreate only its
                // visual representation from the existing Adventure exchange.
                makeGiveCard(dialogue,answer,point+QPointF(24,-52));
            }
            NodeCard *card=m_cards.value(targetId,nullptr);
            if(!card)return;
            if(onto.isEmpty()) {
                const QPointF next=point+QPointF(24,-52);
                if(QLineF(card->pos(),next).length()>1.0) {
                    card->setPos(next);
                    m_positions[targetId]=card->pos();
                    m_dirty=true;
                    redrawLinks();
                    recordHistoryNow();
                }
            }
            showDetails(targetId);
            m_status->setText(tr("GIVE exchange for Dialogue #%1, answer %2: existing card selected. No gameplay rules changed.")
                .arg(dialogue).arg(answer+1));
        };
        m_view->insertRequested=[this](const QPointF &point,const QPoint &global) {
            showInsertTree(point,global,QString());
        };
        m_view->dropRequested=[this](const QString &from,const QPointF &point,const QPoint &global) {
            if (from.startsWith(QStringLiteral("@stateout:")) ||
                from.startsWith(QStringLiteral("@graphvalue:")) ||
                from.startsWith(QStringLiteral("@graphbranch:")) ||
                isEnemyDefeatOutput(from) || isEventOutput(from) ||
                (m_objects.contains(from) && m_objects.value(from).type!=QStringLiteral("npc")))
                showInsertTree(point,global,from);
        };
        m_view->conversationWireMenuRequested=[this](const QString &sourceId,int option,
                                                       bool missing,const QPoint &at) {
            bool ok=false;
            const int dialogue=sourceId.mid(QStringLiteral("@conversation:").size()).toInt(&ok);
            if(!ok || !sourceId.startsWith(QStringLiteral("@conversation:")) ||
               dialogue<0 || dialogue>=m_dialogues.size() || option<0 || option>=3)return;
            const QString field=missing?QStringLiteral("missingNext"):QStringLiteral("next");
            const QJsonArray choices=m_dialogues.at(dialogue).toObject().value(QStringLiteral("choices")).toArray();
            const QJsonObject answer=option<choices.size()?choices.at(option).toObject():QJsonObject();
            const int destination=answer.value(field).toInt(-1);
            if(destination<0)return;
            QMenu menu(this);
            QAction *remove=menu.addAction(missing?
                tr("Disconnect missing-item route (answer %1 → #%2)").arg(option+1).arg(destination):
                tr("Disconnect answer %1 → #%2 (close conversation)").arg(option+1).arg(destination));
            if(menu.exec(at)==remove) {
                setConversationAnswer(dialogue,option,field,-1);
                m_status->setText(tr("Disconnected Dialogue #%1 answer %2 %3 route. Undo with Ctrl+Z.")
                    .arg(dialogue).arg(option+1).arg(missing?tr("missing-item"):tr("normal")));
            }
        };
        m_view->giveWireMenuRequested=[this](const QString &sourceId,int branch,const QPoint &at) {
            int dialogue=-1,answer=-1;
            if(!giveCardReference(sourceId,&dialogue,&answer))return;
            const QString key=giveRouteKey(branch);
            if(key.isEmpty())return;
            const int destination=giveExchange(dialogue,answer).value(key).toInt(-1);
            if(destination<0)return;
            QMenu menu(this);
            QAction *remove=menu.addAction(tr("Disconnect GIVE response → #%1").arg(destination));
            if(menu.exec(at)==remove)setGiveDestination(dialogue,answer,branch,-1);
        };
        m_view->linkMenuRequested=[this](const QList<QPair<QString,int>> &links,const QPoint &point) {
            linkContextMenu(links,point);
        };
        m_view->graphLinkMenuRequested=[this](const QString &kind,const QString &key,int index,const QPoint &at) {
            showGraphWireMenu(kind,key,index,at);
        };
        m_view->cardSelected=[this](const QString &id) {
            // Preserve multi-selection while pressing one of its members to
            // drag the entire selection. A click elsewhere changes the focus.
            if(!m_multiSelectedCards.contains(id))m_multiSelectedCards.clear();
            showDetails(id);
        };
        m_view->cardsSelectionChanged=[this](const QStringList &ids) {
            QSet<QString> selected;
            for(const QString &id:ids)
                if(m_cards.contains(id) && m_cards.value(id)->isVisible())selected.insert(id);
            m_multiSelectedCards=selected.size()>1?selected:QSet<QString>();
            if(selected.size()>1) {
                m_selectedCardId.clear();m_selectedWireKey.clear();
                m_inspectorTitle->setText(tr("%1 nodes selected").arg(selected.size()));
                m_inspectorType->setText(tr("Multiple selection"));
                m_inspectorTree->clear();
                auto *total=new QTreeWidgetItem(m_inspectorTree,QStringList{tr("Selected"),QString::number(selected.size())});
                Q_UNUSED(total);
                m_details->setPlainText(tr("%1 NODES SELECTED\n\nDrag any selected node to move all of them together. Ctrl-click toggles individual nodes; click empty canvas to clear.\n\nOnly the visual layout changes.").arg(selected.size()));
                m_linksList->clear();m_linksList->setEnabled(false);
                m_editLinkButton->setEnabled(false);
                m_removeLinkButton->setEnabled(false);
                // Delete remains a single-card operation, never silently
                // destroy a group of selected connections.
                m_removeSelectedButton->setEnabled(false);
                if(m_status)m_status->setText(tr("%1 nodes selected. Drag a selected card to move the group; middle-drag to pan.").arg(selected.size()));
                applyWireFocus();
            } else if(selected.size()==1) {
                showDetails(*selected.constBegin());
            } else if(m_selectedWireKey.isEmpty()) {
                showDetails(QString());
            }
        };
        m_view->wireSelected=[this](const QString &key) {
            m_multiSelectedCards.clear();
            showDetails(QString()); // A selected wire is not a Delete-card target.
            m_selectedWireKey=key;
            applyWireFocus();
            for (QGraphicsPathItem *wire:m_lines) {
                if (wire->data(6).toString()!=key)continue;
                const QString from=wire->data(4).toString();
                const QString to=wire->data(5).toString();
                const QString source=m_objects.contains(from)?m_objects.value(from).name:from;
                const QString target=m_objects.contains(to)?m_objects.value(to).name:to;
                m_inspectorTitle->setText(tr("CONNECTION"));
                m_inspectorType->setText(wire->data(0).toString().replace(QLatin1Char('-'),QLatin1Char(' ')));
                m_inspectorTree->clear();
                new QTreeWidgetItem(m_inspectorTree,QStringList{tr("Source"),source});
                new QTreeWidgetItem(m_inspectorTree,QStringList{tr("Destination"),target});
                new QTreeWidgetItem(m_inspectorTree,QStringList{tr("Route"),wire->toolTip().section(QLatin1Char('\n'),0,0)});
                m_details->setPlainText(tr("SELECTED CONNECTION\n\n%1 → %2\n\n%3\n\nRight-click the line for connection actions; Esc clears focus.")
                    .arg(source,target,wire->toolTip()));
                if (m_status)m_status->setText(tr("Connection selected: %1 → %2 (Esc to clear)").arg(source,target));
                break;
            }
        };
        m_view->cardMenuRequested=[this](const QString &id,const QPoint &global) {
            showCardContextMenu(id,global);
        };
        m_view->deleteRequested=[this] {removeSelectedNode();};
        // Delete also works if focus is on the card list or the dialog rather
        // than the canvas. Never swallow Delete while editing text or a combo.
        auto *deleteShortcut=new QShortcut(QKeySequence(Qt::Key_Delete),this);
        deleteShortcut->setContext(Qt::WidgetWithChildrenShortcut);
        connect(deleteShortcut,&QShortcut::activated,this,[this] {
            QWidget *focus=QApplication::focusWidget();
            if (qobject_cast<QLineEdit*>(focus) ||
                qobject_cast<QPlainTextEdit*>(focus) ||
                qobject_cast<QTextEdit*>(focus) ||
                qobject_cast<QComboBox*>(focus) ||
                (m_scene && m_scene->focusItem() &&
                 m_scene->focusItem()->type()==QGraphicsProxyWidget::Type))return;
            removeSelectedNode();
        });
        connect(m_removeSelectedButton,&QPushButton::clicked,this,[this] {
            removeSelectedNode();
        });
        connect(m_removeOrphansButton,&QPushButton::clicked,this,[this] {
            removeAllOrphans();
        });
        connect(m_linksList,&QListWidget::itemSelectionChanged,this,[this] {
            const bool selected=m_linksList->currentItem() &&
                m_linksList->currentItem()->isSelected();
            m_editLinkButton->setEnabled(selected);
            m_removeLinkButton->setEnabled(selected);
        });
        connect(m_removeLinkButton,&QPushButton::clicked,this,[this] {
            if (!m_linksList->currentItem() || !m_linksList->currentItem()->isSelected())return;
            const int index=m_linksList->currentItem()->data(Qt::UserRole).toInt();
            if (m_selectedCardId.startsWith(QStringLiteral("@toggle:")) && index<=-1000)
                removeBranchConnection(m_selectedCardId.mid(QStringLiteral("@toggle:").size()),
                    index>-2000,index>-2000?-1000-index:-2000-index);
            else removeConnection(m_selectedCardId,index);
        });
        connect(m_editLinkButton,&QPushButton::clicked,this,[this] {
            if (!m_linksList->currentItem() || !m_linksList->currentItem()->isSelected())return;
            linkContextMenu({qMakePair(m_selectedCardId.startsWith(QStringLiteral("@toggle:"))?
                m_selectedCardId.mid(QStringLiteral("@toggle:").size()):m_selectedCardId,
                m_linksList->currentItem()->data(Qt::UserRole).toInt())},
                            m_editLinkButton->mapToGlobal(QPoint(0,m_editLinkButton->height())));
        });
        connect(m_linksList,&QListWidget::itemDoubleClicked,this,[this](QListWidgetItem *item) {
            if (!item)return;
            linkContextMenu({qMakePair(m_selectedCardId.startsWith(QStringLiteral("@toggle:"))?
                m_selectedCardId.mid(QStringLiteral("@toggle:").size()):m_selectedCardId,
                item->data(Qt::UserRole).toInt())},
                            m_linksList->mapToGlobal(QPoint(m_linksList->width()/2,m_linksList->height()/2)));
        });
        connect(m_list,&QListWidget::itemClicked,this,[this](QListWidgetItem *item) {
            if (item)showDetails(item->data(Qt::UserRole).toString());
        });
        connect(m_list,&QListWidget::itemDoubleClicked,this,[this](QListWidgetItem *item) {
            if (!item)return;
            const QString id=item->data(Qt::UserRole).toString();
            if (!m_cards.contains(id))return;
            m_view->centerOn(m_cards.value(id));showDetails(id);
        });
        connect(m_visibleTree,&QTreeWidget::itemClicked,this,[this](QTreeWidgetItem *item,int) {
            if(!item)return;
            const QString id=item->data(0,Qt::UserRole).toString();
            if(m_cards.contains(id))showDetails(id);
        });
        connect(m_visibleTree,&QTreeWidget::itemDoubleClicked,this,[this](QTreeWidgetItem *item,int) {
            if(!item)return;
            const QString id=item->data(0,Qt::UserRole).toString();
            if(m_cards.contains(id) && m_cards.value(id)->isVisible()) {
                m_view->centerOn(m_cards.value(id));showDetails(id);
            } else if(id.startsWith(QStringLiteral("@flowgroup:"))) {
                bool ok=false;
                const int root=id.mid(QStringLiteral("@flowgroup:").size()).toInt(&ok);
                if(ok && m_flowGroups.contains(root))m_view->centerOn(m_flowGroups.value(root));
            }
        });
        connect(m_visibleTree,&QTreeWidget::itemCollapsed,this,[this](QTreeWidgetItem *item) {
            if(item && item->childCount())m_treeCollapsed.insert(item->data(0,Qt::UserRole).toString());
        });
        connect(m_visibleTree,&QTreeWidget::itemExpanded,this,[this](QTreeWidgetItem *item) {
            if(item && item->childCount())m_treeCollapsed.remove(item->data(0,Qt::UserRole).toString());
        });
        connect(m_treeSearch,&QLineEdit::textChanged,this,[this](const QString &filter) {
            // Keep matching leaves and their ancestor folders visible.
            if(!m_visibleTree)return;
            std::function<bool(QTreeWidgetItem*)> match=[&](QTreeWidgetItem *item)->bool {
                bool found=item->text(0).contains(filter,Qt::CaseInsensitive);
                for(int i=0;i<item->childCount();++i)found=match(item->child(i)) || found;
                item->setHidden(!filter.isEmpty() && !found);
                if(found && !filter.isEmpty() && item->childCount())item->setExpanded(true);
                return found;
            };
            for(int i=0;i<m_visibleTree->topLevelItemCount();++i)
                match(m_visibleTree->topLevelItem(i));
        });
        connect(m_list->model(),&QAbstractItemModel::rowsInserted,this,
                [this] {scheduleVisibleTreeRefresh();});
        connect(m_list->model(),&QAbstractItemModel::rowsRemoved,this,
                [this] {scheduleVisibleTreeRefresh();});
        connect(m_list->model(),&QAbstractItemModel::modelReset,this,
                [this] {scheduleVisibleTreeRefresh();});
        connect(m_list->model(),&QAbstractItemModel::dataChanged,this,
                [this] {scheduleVisibleTreeRefresh();});
        m_view->cardDragFinished=[this] {
            if (!m_liveWireDrag)return;
            m_liveWireDrag=false;
            // Use the authored socket geometry for final curves and update
            // scroll bounds after the movement, never during every pixel.
            redrawLinks();
        };
    }
    // Reconcile visible cards with the real links in the design document.
    // Old .vsgm graph files used to write positions for *every* object. Those
    // positions remain useful, but are NOT evidence the user placed the card.
    QSet<QString> linkedObjectIds() const {
        QSet<QString> visible;
        for (const QString &id:m_order) {
            const NodeObject n=m_objects.value(id);
            if (!isActionSource(n) && eventKinds(n.type).isEmpty() && n.logicNodes.isEmpty())continue;
            for(const QVector<NodeLink> &links:n.eventLinks)
                for(const NodeLink &link:links) {
                    if(!supportedAction(link.action) || !m_objects.contains(link.target))continue;
                    visible.insert(id);visible.insert(link.target);
                }
            for (const NodeLink &link:n.links) {
                if (!supportedAction(link.action) || !m_objects.contains(link.target))continue;
                visible.insert(id);
                visible.insert(link.target);
            }
            if (n.type==QStringLiteral("trigger") && n.dialogueNode>=0) visible.insert(id);
            if (!n.logicNodes.isEmpty()) {
                visible.insert(id);
                for(const QJsonValue &v:n.logicNodes) {
                    const QJsonObject logic=v.toObject();
                    for(const QJsonValue &input:logic.value(QStringLiteral("inputs")).toArray()) {
                        const QJsonObject ref=input.toObject();
                        if(ref.value(QStringLiteral("kind")).toString()==QStringLiteral("object"))
                            visible.insert(ref.value(QStringLiteral("id")).toString());
                    }
                    for(const QString &field:{QStringLiteral("trueActions"),QStringLiteral("falseActions")})
                        for(const QJsonValue &v:logic.value(field).toArray())
                            visible.insert(v.toObject().value(QStringLiteral("objectId")).toString());
                    for(const QJsonValue &v:logic.value(QStringLiteral("resultTargets")).toArray())
                        visible.insert(v.toString());
                }
            }
            if (n.type==QStringLiteral("trigger") && !n.toggleStateTargetId.isEmpty()) {
                visible.insert(id);
                if (m_objects.contains(n.toggleStateTargetId))visible.insert(n.toggleStateTargetId);
                for (const QString &extra:n.toggleStateInputIds)
                    if (m_objects.contains(extra))visible.insert(extra);
                for (const NodeLink &link:n.toggleTrueActions)
                    if (supportedAction(link.action) && m_objects.contains(link.target))visible.insert(link.target);
                for (const NodeLink &link:n.toggleFalseActions)
                    if (supportedAction(link.action) && m_objects.contains(link.target))visible.insert(link.target);
            }
        }
        // NPCs already have authored conversation links in adventure.npcs;
        // surface them without requiring a second action wire to be placed.
        for(const QString &id:m_order)
            if(m_objects.value(id).type==QStringLiteral("npc") &&
               !m_hiddenNpcCards.contains(id))visible.insert(id);
        return visible;
    }
    // Real links from .sbgm define which cards are connected. .vsgm merely
    // remembers cards deliberately placed by the user, never game logic.
    QSet<QString> connectedCardIds() const {
        QSet<QString> ids=linkedObjectIds();
        for (const QString &id:m_order)
            if (m_objects.value(id).type==QStringLiteral("trigger") &&
                m_objects.value(id).dialogueNode>=0)
                ids.insert(dialogueCardId(id));
        for (const QString &id:m_order) {
            const NodeObject n=m_objects.value(id);
            if (n.type!=QStringLiteral("trigger") || n.toggleStateTargetId.isEmpty())continue;
            ids.insert(toggleCardId(id));
            if (n.toggleTrueDialogueNode>=0)ids.insert(branchCardId(id,true));
            if (n.toggleFalseDialogueNode>=0)ids.insert(branchCardId(id,false));
        }
        for(const QString &owner:m_order) {
            const NodeObject n=m_objects.value(owner);
            if(n.logicNodes.isEmpty())continue;
            for(const QJsonValue &v:n.logicNodes) {
                const QJsonObject o=v.toObject();
                const QString key=graphKey(owner,o.value(QStringLiteral("id")).toString());
                ids.insert(key);
                for(const bool yes:{true,false})
                    if(o.value(yes?QStringLiteral("trueDialogueNode"):QStringLiteral("falseDialogueNode")).toInt(-1)>=0)
                        ids.insert(graphDialogueKey(key,yes));
            }
        }
        for (const QString &id:m_cards.keys())
            if(id.startsWith(QStringLiteral("@conversation:")) ||
               id.startsWith(QStringLiteral("@give:")))ids.insert(id);
        return ids;
    }
    // NPC rows belong to Adventure, not gameObject. Preserve animations and
    // any future/unknown NPC keys when the graph edits just these four fields.
    void updateNpcProperty(const QString &id,const QString &field,const QJsonValue &value) {
        if (!m_objects.contains(id) || m_objects.value(id).type!=QStringLiteral("npc"))return;
        for(int index=0;index<m_npcEntries.size();++index) {
            QJsonObject entry=m_npcEntries.at(index).toObject();
            if(entry.value(QStringLiteral("spriteId")).toString()!=id)continue;
            if(entry.value(field)==value)return;
            entry.insert(field,value);
            m_npcEntries.replace(index,entry);
            NodeObject node=m_objects.value(id);
            if(field==QStringLiteral("node"))node.npcStartNode=value.toInt(-1);
            else if(field==QStringLiteral("doneNode"))node.npcDoneNode=value.toInt(-1);
            else if(field==QStringLiteral("radius"))node.npcRadius=value.toInt(48);
            else if(field==QStringLiteral("initiallyVisible"))node.npcInitiallyVisible=value.toBool(true);
            m_objects.insert(id,node);
            m_npcsChanged=true;
            m_dirty=true;
            if(field==QStringLiteral("node") || field==QStringLiteral("doneNode")) {
                // A wire deliberately dropped onto the NPC input follows
                // that INPUT when the dialogue selector changes. Unrelated
                // Show Dialogue nodes still reference their original IDs.
                const QString slot=field==QStringLiteral("node")?
                    QStringLiteral("start"):QStringLiteral("helped");
                const int selected=value.toInt(-1);
                const QList<QString> sources=m_npcDialogueRoutes.keys();
                for(const QString &source:sources) {
                    QJsonObject route=m_npcDialogueRoutes.value(source);
                    if(route.value(QStringLiteral("npc")).toString()!=id ||
                       route.value(QStringLiteral("slot")).toString()!=slot)continue;
                    if(selected>=0 && selected<m_dialogues.size()) {
                        route.insert(QStringLiteral("dialogue"),selected);
                        m_npcDialogueRoutes.insert(source,route);
                    } else m_npcDialogueRoutes.remove(source);
                    if(source.startsWith(QStringLiteral("@graphbranch:"))) {
                        const bool yes=source.startsWith(QStringLiteral("@graphbranch:true:"));
                        const QString key=source.mid(yes?QStringLiteral("@graphbranch:true:").size():
                            QStringLiteral("@graphbranch:false:").size());
                        setGraphDialogue(key,yes,selected);
                    } else if(source.startsWith(QStringLiteral("@stateout:"))) {
                        const bool yes=source.startsWith(QStringLiteral("@stateout:true:"));
                        const QString owner=source.mid(yes?QStringLiteral("@stateout:true:").size():
                            QStringLiteral("@stateout:false:").size());
                        setBranchDialogue(owner,yes,selected,QPointF());
                    } else if(m_objects.contains(source) &&
                            m_objects.value(source).type==QStringLiteral("trigger")) {
                        if(selected>=0)connectExistingDialogue(source,QPointF(),selected);
                        else disconnectDialogue(source);
                    }
                }
            }
            redrawLinks();
            showDetails(id);
            return;
        }
    }
    QString npcDialogueTitle(int index) const {
        if(index<0 || index>=m_dialogues.size())return tr("No dialogue selected");
        const QJsonObject node=m_dialogues.at(index).toObject();
        return tr("#%1  %2: %3").arg(index)
            .arg(node.value(QStringLiteral("speaker")).toString().left(25),
                 node.value(QStringLiteral("text")).toString().left(42));
    }
    QString flowGroupId(int root) const {
        return QStringLiteral("@flowgroup:")+QString::number(root);
    }
    QString conversationFlowTitle(int root) const {
        for(const QString &id:m_order) {
            if(!m_objects.contains(id))continue;
            const NodeObject npc=m_objects.value(id);
            if(npc.type!=QStringLiteral("npc"))continue;
            if(npc.npcStartNode==root)
                return tr("%1 - opening conversation flow").arg(npc.name);
            if(npc.npcDoneNode==root)
                return tr("%1 - after helped conversation flow").arg(npc.name);
        }
        return tr("Dialogue #%1 - conversation flow").arg(root);
    }
    QSet<QString> reachableGiveCards(const QSet<int> &dialogues) const {
        QSet<QString> giveIds;
        for(int current:dialogues) {
            if(current<0 || current>=m_dialogues.size())continue;
            const QJsonArray choices=m_dialogues.at(current).toObject()
                .value(QStringLiteral("choices")).toArray();
            for(int option=0;option<choices.size() && option<3;++option) {
                const QJsonObject choice=choices.at(option).toObject();
                if(choice.value(QStringLiteral("text")).toString().trimmed().isEmpty())continue;
                if(choice.value(QStringLiteral("exchange")).toObject().value(QStringLiteral("enabled")).toBool(false))
                    giveIds.insert(giveCardId(current,option));
            }
        }
        return giveIds;
    }
    bool flowRootHidden(int root) const {
        return m_hiddenConversationRoots.contains(root);
    }
    bool flowRootCollapsed(int root) const {
        return m_collapsedCards.contains(flowGroupId(root));
    }
    void ensureConversationFlowGroup(int root) {
        if(m_flowGroups.contains(root))return;
        auto *group=new FlowGroupBox(conversationFlowTitle(root),m_theme.alternateBackground);
        group->foldClicked=[this,root,group] {
            const QString id=flowGroupId(root);
            const bool next=!group->collapsed();
            group->setCollapsed(next);
            if(next)m_collapsedCards.insert(id); else m_collapsedCards.remove(id);
            updateConversationFlowGroups();
            updateConversationFlowVisibility();
            redrawLinks();
            m_dirty=true;
        };
        group->moved=[this,root](const QPointF &delta) {
            // The visible compact group is also a wire destination. Follow
            // its header immediately while dragging; the final release pass
            // recomputes the proper cubic curve once.
            for(QGraphicsPathItem *wire:m_liveWiresByCard.value(flowGroupId(root))) {
                if(!wire || wire->scene()!=m_scene)continue;
                QPainterPath path=wire->path();
                const int count=path.elementCount();
                if(count<2)continue;
                const int end=count-1;
                const auto last=path.elementAt(end);
                path.setElementPositionAt(end,last.x+delta.x(),last.y+delta.y());
                if(end>0 && path.elementAt(end-1).type==QPainterPath::CurveToDataElement) {
                    const auto control=path.elementAt(end-1);
                    path.setElementPositionAt(end-1,control.x+delta.x(),control.y+delta.y());
                }
                wire->setPath(path);
            }
            // Move the actual cards (not copies or a nested graphics parent).
            // Their existing ItemPositionHasChanged path updates wire endpoints
            // synchronously, keeping the smooth Stage 5.166.88 behaviour.
            m_movingFlowGroup=true;
            const QSet<int> dialogues=conversationReachable(root);
            const QSet<QString> giveIds=reachableGiveCards(dialogues);
            for(int index:dialogues) {
                NodeCard *card=m_cards.value(conversationCardId(index),nullptr);
                if(card)card->setPos(card->pos()+delta);
            }
            for(const QString &id:giveIds) {
                NodeCard *card=m_cards.value(id,nullptr);
                if(card)card->setPos(card->pos()+delta);
            }
            m_movingFlowGroup=false;
            m_dirty=true;
        };
        group->dragFinished=[this] {
            updateConversationFlowGroups();
            redrawLinks();
            m_dirty=true;
        };
        group->setCollapsed(flowRootCollapsed(root));
        m_scene->addItem(group);
        m_flowGroups.insert(root,group);
    }
    void updateConversationFlowGroups() {
        if(m_movingFlowGroup)return;
        QList<int> existing=m_flowGroups.keys();
        for(int root:existing) {
            if(m_conversationRoots.contains(root))continue;
            FlowGroupBox *group=m_flowGroups.take(root);
            if(group) {m_scene->removeItem(group);delete group;}
            m_collapsedCards.remove(flowGroupId(root));
        }
        QList<int> roots=m_conversationRoots.values();
        std::sort(roots.begin(),roots.end());
        for(int root:roots) {
            ensureConversationFlowGroup(root);
            FlowGroupBox *group=m_flowGroups.value(root,nullptr);
            if(!group)continue;
            group->setTitle(conversationFlowTitle(root));
            QRectF bounds;
            const QSet<int> dialogues=conversationReachable(root);
            const QSet<QString> giveIds=reachableGiveCards(dialogues);
            for(int dialogue:dialogues) {
                const QString id=conversationCardId(dialogue);
                if(m_cards.contains(id))bounds=bounds.united(m_cards.value(id)->sceneBoundingRect());
            }
            for(const QString &id:giveIds)
                if(m_cards.contains(id))bounds=bounds.united(m_cards.value(id)->sceneBoundingRect());
            if(bounds.isNull() || !bounds.isValid()) {
                const QString cardId=conversationCardId(root);
                const QPointF pos=m_positions.value(cardId,QPointF(80,80));
                bounds=QRectF(pos,QSizeF(420,220));
            }
            const QRectF framed=bounds.adjusted(-28,-40,28,28);
            group->setExpandedRect(framed);
            group->setCollapsed(flowRootCollapsed(root));
            group->setVisible(!flowRootHidden(root));
        }
    }
    void updateConversationFlowVisibility() {
        QSet<int> visibleDialogues;
        QSet<QString> visibleGiveIds;
        for(int root:m_conversationRoots) {
            if(flowRootHidden(root) || flowRootCollapsed(root))continue;
            const QSet<int> reachable=conversationReachable(root);
            visibleDialogues.unite(reachable);
            visibleGiveIds.unite(reachableGiveCards(reachable));
        }
        for(auto it=m_cards.begin();it!=m_cards.end();++it) {
            const QString id=it.key();
            NodeCard *card=it.value();
            if(!card)continue;
            if(id.startsWith(QStringLiteral("@conversation:"))) {
                bool ok=false;
                const int index=id.mid(QStringLiteral("@conversation:").size()).toInt(&ok);
                card->setVisible(ok && visibleDialogues.contains(index));
            } else if(id.startsWith(QStringLiteral("@give:"))) {
                card->setVisible(visibleGiveIds.contains(id));
            }
        }
        for(auto it=m_flowGroups.begin();it!=m_flowGroups.end();++it)
            if(it.value())it.value()->setVisible(!flowRootHidden(it.key()));
    }
    void makeObjectCard(const QString &id,const QPointF &position) {
        if (m_cards.contains(id) || !m_objects.contains(id))return;
        const NodeObject node=m_objects.value(id);
        const bool trigger=node.type==QStringLiteral("trigger");
        const bool npc=node.type==QStringLiteral("npc");
        const bool player=node.type==QStringLiteral("player_action");
        const bool eventSource=isActionSource(node) || !eventKinds(node.type).isEmpty();
        const qreal width=npc?344:(trigger?280:224);
        auto *card=new NodeCard(QRectF(0,0,width,npc?266:(trigger?201:
            node.type==QStringLiteral("enemy")?142:
            !eventKinds(node.type).isEmpty()?92+eventKinds(node.type).size()*29:82)));
        card->setData(0,QStringLiteral("card"));card->setData(1,id);
        card->setPen(QPen(eventSource?QColor(238,190,86):npc?QColor(207,153,236):player?QColor(198,149,226):QColor(103,153,184),1.5));
        card->setBrush(m_theme.panelBackground);
        m_scene->addItem(card);
        card->setPos(position);
        card->enableGridSnap();
        m_positions.insert(id,position);
        auto *stripe=new QGraphicsRectItem(QRectF(0,0,width,26),card);
        stripe->setPen(Qt::NoPen);stripe->setBrush(eventSource?QColor(138,91,35):npc?QColor(97,65,129):player?QColor(103,60,132):QColor(50,88,119));
        auto *name=new QGraphicsSimpleTextItem(node.name.left(27),card);
        name->setBrush(Qt::white);name->setPos(8,4);
        auto *kind=new QGraphicsSimpleTextItem(player?tr("PLAYER ACTION"):
            node.type==QStringLiteral("npc_reference")?tr("NPC (OTHER WORLD)"):
            node.type==QStringLiteral("world_reference")?tr("WORLD OBJECT TARGET"):
            node.type==QStringLiteral("missing_reference")?tr("BROKEN CONNECTION"):
            (node.type==QStringLiteral("collectable") && node.pickupKind==3)?tr("KEY COLLECTABLE"):
            node.type==QStringLiteral("enemy")?tr("ENEMY STATE / DEFEAT"):node.type.toUpper(),card);
        kind->setBrush(m_theme.text);kind->setPos(9,35);
        if (!npc) {
            // An incoming action is not the same thing as an outgoing state:
            // a small square on the left denotes a command/state assignment.
            auto *input=new QGraphicsRectItem(QRectF(-7,51,14,14),card);
            input->setData(0,QStringLiteral("input"));
            input->setData(1,id);
            const QColor colour=player?QColor(176,119,212):QColor(115,190,213);
            input->setPen(QPen(colour.lighter(150),1.5));
            input->setBrush(colour);
            input->setZValue(4);
            input->setToolTip(player ? tr("INPUT: receive a PLAYER command from a Trigger or logic branch") :
                tr("INPUT: receive Enable / Disable / Toggle or a logic RESULT assignment (where supported)"));
        }
        if (trigger || (node.resourceIndex>=0 && node.type!=QStringLiteral("npc"))) {
            // Trigger sockets issue actions. Game Object sockets expose their
            // active state to a Boolean; they never issue another game action.
            auto *port=new QGraphicsEllipseItem(QRectF(trigger?270:214,49,19,19),card);
            port->setData(0,QStringLiteral("output"));port->setData(1,id);
            if (trigger) {
                port->setPen(QPen(QColor(255,224,136),2));
                port->setBrush(QColor(219,148,31));
            } else {
                port->setPen(QPen(QColor(177,242,226),2));
                port->setBrush(QColor(54,148,141));
                port->setToolTip(node.type==QStringLiteral("enemy")
                    ? tr("STATE OUTPUT: read this enemy as a Boolean input. Create AND/NOT/OR logic directly from here without a Trigger. TRUE means active, FALSE means defeated/disabled. For actions when defeated use the gold socket below.")
                    : eventSource ? tr("This object's existing pickup action is shown as a coloured wire. The teal socket still reads enabled state.") :
                    tr("Read this Game Object's enabled/disabled state with Logic > Boolean"));
            }
        }
        if (node.type==QStringLiteral("enemy")) {
            auto *label=new QGraphicsSimpleTextItem(tr("ON DEFEAT"),card);
            label->setBrush(QColor(238,190,86));label->setPos(9,75);
            auto *defeat=new QGraphicsEllipseItem(QRectF(214,81,19,19),card);
            defeat->setData(0,QStringLiteral("enemy-action-output"));
            defeat->setData(1,id);
            defeat->setPen(QPen(QColor(255,225,147),2));
            defeat->setBrush(QColor(205,140,37));
            defeat->setZValue(5);
            defeat->setToolTip(tr("ON DEFEAT ACTION: drag to a Game Object or PLAYER command to Enable, Disable or Toggle when the final stomp defeats this enemy. Multiple ordered actions are supported."));
        }
        // Gold executable EVENT outputs are distinct from the teal state
        // socket; a source can expose several independent named events.
        const QStringList kinds=eventKinds(node.type);
        for(int eventIndex=0;eventIndex<kinds.size();++eventIndex) {
            const QString key=kinds.at(eventIndex);
            const qreal y=(node.type==QStringLiteral("enemy")?108.0:79.0)+eventIndex*29.0;
            auto *label=new QGraphicsSimpleTextItem(eventLabel(key),card);
            label->setBrush(QColor(238,190,86));label->setPos(9,y-6);
            auto *port=new QGraphicsEllipseItem(QRectF(214,y,19,19),card);
            port->setData(0,QStringLiteral("event-output"));
            port->setData(1,id);port->setData(2,key);
            port->setPen(QPen(QColor(255,225,147),2));
            port->setBrush(QColor(205,140,37));port->setZValue(5);
            port->setToolTip(key==QStringLiteral("arrival")
                ? tr("GOLD ON ARRIVAL: drag to empty canvas → Logic (Boolean/AND/OR/NOT), or to a Game Object and right-click the action wire → Toggle to alternate its state each arrival. The teal socket above reads the lift's active state instead.")
                : ((node.type==QStringLiteral("breakable") &&
                    (key==QStringLiteral("hit") || key==QStringLiteral("destroy")))
                  ? tr("%1: drag to empty canvas → Logic (Boolean/AND/OR/NOT), or to a Game Object for an unconditional action.").arg(eventLabel(key))
                  : tr("%1: drag to an action target. Executes only when this real game event occurs.").arg(eventLabel(key))));
        }
        if (npc) {
            // NPC visibility is a genuine Enable/Disable/Toggle action,
            // separate from the two dialogue-command inputs below.
            card->setCompactHeight(49);
            auto *stateInput=new QGraphicsRectItem(QRectF(-7,51,14,14),card);
            stateInput->setData(0,QStringLiteral("input"));
            stateInput->setData(1,id);
            stateInput->setData(2,QStringLiteral("state"));
            stateInput->setPen(QPen(QColor(174,222,244),1.5));
            stateInput->setBrush(QColor(88,159,199));
            stateInput->setZValue(4);
            stateInput->setToolTip(tr("NPC visibility INPUT: Enable / Disable / Toggle; not a conversation"));
            // NPCs are conversation DESTINATIONS. These two left-hand ports
            // consume a Trigger or logic TRUE/FALSE event; they do NOT expose
            // a Boolean NPC state or duplicate the Adventure dialogue data.
            for (const bool helped:{false,true}) {
                const qreal y=helped?163.0:101.0;
                auto *port=new QGraphicsRectItem(QRectF(-7,y-7,14,14),card);
                port->setData(0,QStringLiteral("npc-input"));
                port->setData(1,id);
                port->setData(2,helped?QStringLiteral("helped"):QStringLiteral("start"));
                port->setPen(QPen(QColor(226,179,251),2));
                port->setBrush(helped?QColor(131,82,167):QColor(169,104,208));
                port->setZValue(4);
                port->setToolTip(helped?
                    tr("Dialogue input: play this NPC's After helped conversation (no helped-state check)"):
                    tr("Dialogue input: play this NPC's opening conversation"));
            }
            // These are the Dialogue Editor's exact NPC fields. The graph
            // never creates a duplicate conversation or changes dialogue IDs.
            auto *panel=new QWidget;
            panel->setFixedSize(321,198);
            panel->setStyleSheet(m_controlsStyle);
            auto *layout=new QVBoxLayout(panel);
            layout->setContentsMargins(6,3,6,3);
            layout->setSpacing(4);
            auto *startLabel=new QLabel(tr("Start conversation"),panel);
            layout->addWidget(startLabel);
            auto *startRow=new QHBoxLayout;
            auto *start=new QComboBox(panel);
            start->setProperty("npcDialogueInputSlot",QStringLiteral("start"));
            start->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLengthWithIcon);
            start->setMinimumContentsLength(16);
            auto *startBrowse=new QPushButton(tr("..."),panel);
            startBrowse->setToolTip(tr("Browse the Dialogue Editor's folders"));
            startBrowse->setFixedWidth(27);
            startRow->addWidget(start,1);startRow->addWidget(startBrowse);
            layout->addLayout(startRow);
            layout->addWidget(new QLabel(tr("After helped (optional)"),panel));
            auto *doneRow=new QHBoxLayout;
            auto *done=new QComboBox(panel);
            done->setProperty("npcDialogueInputSlot",QStringLiteral("helped"));
            done->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLengthWithIcon);
            done->setMinimumContentsLength(16);
            auto *doneBrowse=new QPushButton(tr("..."),panel);
            doneBrowse->setFixedWidth(27);
            doneBrowse->setToolTip(tr("Browse the Dialogue Editor's folders"));
            doneRow->addWidget(done,1);doneRow->addWidget(doneBrowse);
            layout->addLayout(doneRow);
            done->addItem(tr("Use normal opening dialogue"),-1);
            for(int i=0;i<m_dialogues.size();++i) {
                const QString label=npcDialogueTitle(i);
                start->addItem(label,i);
                done->addItem(label,i);
                start->setItemData(i,label,Qt::ToolTipRole);
                done->setItemData(i+1,label,Qt::ToolTipRole);
            }
            // Missing IDs remain visible rather than silently selecting a
            // different dialogue and rewriting gameplay on the next save.
            if(start->findData(node.npcStartNode)<0)
                start->addItem(tr("MISSING dialogue #%1").arg(node.npcStartNode),node.npcStartNode);
            if(done->findData(node.npcDoneNode)<0)
                done->addItem(tr("MISSING dialogue #%1").arg(node.npcDoneNode),node.npcDoneNode);
            start->setCurrentIndex(start->findData(node.npcStartNode));
            done->setCurrentIndex(done->findData(node.npcDoneNode));
            auto *options=new QHBoxLayout;
            auto *visible=new QCheckBox(tr("Initially visible"),panel);
            visible->setChecked(node.npcInitiallyVisible);
            auto *radius=new QSpinBox(panel);
            radius->setRange(8,512);
            radius->setSuffix(tr(" px"));
            radius->setValue(qBound(8,node.npcRadius,512));
            options->addWidget(visible);
            options->addStretch();
            options->addWidget(new QLabel(tr("Talk radius"),panel));
            options->addWidget(radius);
            layout->addLayout(options);
            layout->addStretch();
            auto *proxy=new QGraphicsProxyWidget(card);
            proxy->setWidget(panel);
            proxy->setPos(9,60);
            proxy->setZValue(3);
            connect(start,qOverload<int>(&QComboBox::currentIndexChanged),this,[this,id,start](int) {
                updateNpcProperty(id,QStringLiteral("node"),start->currentData().toInt());
            });
            connect(done,qOverload<int>(&QComboBox::currentIndexChanged),this,[this,id,done](int) {
                updateNpcProperty(id,QStringLiteral("doneNode"),done->currentData().toInt());
            });
            connect(visible,&QCheckBox::toggled,this,[this,id](bool checked) {
                updateNpcProperty(id,QStringLiteral("initiallyVisible"),checked);
            });
            connect(radius,qOverload<int>(&QSpinBox::valueChanged),this,[this,id](int value) {
                updateNpcProperty(id,QStringLiteral("radius"),value);
            });
            connect(startBrowse,&QPushButton::clicked,this,[this,id,start] {
                const int selected=browseDialogueTree(m_objects.value(id).npcStartNode);
                if(selected>=0 && start->findData(selected)>=0)
                    start->setCurrentIndex(start->findData(selected));
            });
            connect(doneBrowse,&QPushButton::clicked,this,[this,id,done] {
                const int selected=browseDialogueTree(m_objects.value(id).npcDoneNode);
                if(selected>=0 && done->findData(selected)>=0)
                    done->setCurrentIndex(done->findData(selected));
            });
        }
        if (trigger) {
            auto *panel=new QWidget;
            panel->setFixedSize(258,112);
            panel->setStyleSheet(m_controlsStyle);
            auto *layout=new QVBoxLayout(panel);
            layout->setContentsMargins(5,2,5,2);
            layout->setSpacing(3);
            auto *fire=new QCheckBox(tr("Require FIRE2"),panel);
            auto *once=new QCheckBox(tr("Remove after switch"),panel);
            fire->setChecked(node.triggerPress);
            once->setChecked(node.triggerOneShot);
            layout->addWidget(fire);
            layout->addWidget(once);
            auto *itemRow=new QHBoxLayout;
            itemRow->addWidget(new QLabel(tr("USE inventory:"),panel));
            auto *items=new QComboBox(panel);
            items->addItem(tr("None (touch / FIRE2)"),QString());
            const QJsonArray inventory=m_world.value(QStringLiteral("adventure")).toObject()
                .value(QStringLiteral("items")).toArray();
            for(const QJsonValue &entry:inventory) {
                const QString itemName=entry.toObject().value(QStringLiteral("name")).toString().trimmed();
                if(!itemName.isEmpty() && items->findData(itemName)<0)items->addItem(itemName,itemName);
            }
            if(!node.interactItemName.isEmpty() && items->findData(node.interactItemName)<0)
                items->addItem(tr("Missing: %1").arg(node.interactItemName),node.interactItemName);
            items->setCurrentIndex(qMax(0,items->findData(node.interactItemName)));
            fire->setEnabled(node.interactItemName.isEmpty());
            itemRow->addWidget(items,1);
            layout->addLayout(itemRow);
            auto *proxy=new QGraphicsProxyWidget(card);
            proxy->setWidget(panel);
            proxy->setPos(8,79);
            proxy->setZValue(3);
            connect(fire,&QCheckBox::toggled,this,[this,id](bool enabled) {
                NodeObject n=m_objects.value(id);n.triggerPress=enabled;
                m_objects.insert(id,n);m_touched.insert(id);m_dirty=true;
            });
            connect(once,&QCheckBox::toggled,this,[this,id](bool enabled) {
                NodeObject n=m_objects.value(id);n.triggerOneShot=enabled;
                m_objects.insert(id,n);m_touched.insert(id);m_dirty=true;
            });
            connect(items,qOverload<int>(&QComboBox::currentIndexChanged),this,
                    [this,id,fire,items](int) {
                NodeObject n=m_objects.value(id);
                n.interactItemName=items->currentData().toString();
                fire->setEnabled(n.interactItemName.isEmpty());
                m_objects.insert(id,n);m_touched.insert(id);m_dirty=true;
            });
        }
        card->moved=[this,id,card] {updateLiveWires(id,card);};
        addFoldButton(card,id);
        m_cards.insert(id,card);
        auto *rowItem=new QListWidgetItem(node.name+QStringLiteral("  (")+node.type+QStringLiteral(")"),m_list);
        rowItem->setData(Qt::UserRole,id);
        rowItem->setToolTip(node.name+QStringLiteral(" (")+node.type+QStringLiteral(")"));
    }
    // Dialogue cards read/edit Adventure's original .sbgm nodes. Numeric IDs
    // are stable and the graph cannot duplicate or renumber dialogue data.
    QString conversationCardId(int dialogue) const {
        return QStringLiteral("@conversation:%1").arg(dialogue);
    }
    QString giveCardId(int dialogue,int answer) const {
        return QStringLiteral("@give:%1:%2").arg(dialogue).arg(answer);
    }
    QString giveRouteKey(int branch) const {
        static const char *keys[]={"wrongNext","wrongRepeatFirst","wrongRepeatSecond",
                                   "wrongRepeatThird","wrongRepeatLater"};
        return branch>=0 && branch<5?QString::fromLatin1(keys[branch]):QString();
    }
    bool giveCardReference(const QString &id,int *dialogue,int *answer) const {
        if(!id.startsWith(QStringLiteral("@give:")))return false;
        const QStringList parts=id.split(QLatin1Char(':'));
        if(parts.size()!=3)return false;
        bool ok1=false,ok2=false;
        const int d=parts.at(1).toInt(&ok1),a=parts.at(2).toInt(&ok2);
        if(!ok1 || !ok2 || d<0 || d>=m_dialogues.size() || a<0 || a>=3)return false;
        if(dialogue)*dialogue=d;
        if(answer)*answer=a;
        return true;
    }
    QJsonObject giveExchange(int dialogue,int answer) const {
        if(dialogue<0 || dialogue>=m_dialogues.size() || answer<0 || answer>=3)return {};
        const QJsonArray choices=m_dialogues.at(dialogue).toObject().value(QStringLiteral("choices")).toArray();
        return answer<choices.size()?choices.at(answer).toObject().value(QStringLiteral("exchange")).toObject():QJsonObject();
    }
    void setGiveDestination(int dialogue,int answer,int branch,int destination) {
        const QString key=giveRouteKey(branch);
        if(key.isEmpty())return;
        QJsonObject exchange=giveExchange(dialogue,answer);
        if(!exchange.value(QStringLiteral("enabled")).toBool(false))return;
        if(branch>0 && !exchange.value(QStringLiteral("wrongRepeatEnabled")).toBool(false))return;
        if(exchange.value(key).toInt(-1)==destination)return;
        exchange.insert(key,destination);
        setConversationAnswer(dialogue,answer,QStringLiteral("exchange"),exchange);
        m_status->setText(tr("GIVE exchange: dialogue #%1 answer %2, %3 → %4")
            .arg(dialogue).arg(answer+1).arg(key,destination<0?tr("Keep NPC dialogue"):tr("Dialogue #%1").arg(destination)));
    }
    QSet<int> conversationReachable(int root) const {
        QSet<int> visited;
        if (root<0 || root>=m_dialogues.size())return visited;
        QList<int> queue{root};
        for (int head=0;head<queue.size();++head) {
            const int current=queue.at(head);
            if (current<0 || current>=m_dialogues.size() || visited.contains(current))continue;
            visited.insert(current);
            const QJsonArray choices=m_dialogues.at(current).toObject()
                .value(QStringLiteral("choices")).toArray();
            for (const QJsonValue &value:choices) {
                const QJsonObject choice=value.toObject();
                // The runtime skips blank answers. A stale 'next' on a blank
                // answer is NOT a real dialogue branch.
                if (choice.value(QStringLiteral("text")).toString().trimmed().isEmpty())continue;
                const int next=choice.value(QStringLiteral("next")).toInt(-1);
                if (next>=0 && next<m_dialogues.size() && !visited.contains(next))
                    queue.append(next);
                // Item-gated answers may lead to a different conversation when
                // the required inventory item is absent. This is also a real
                // Adventure branch and must be shown in the preview.
                const int missing=choice.value(QStringLiteral("missingNext")).toInt(-1);
                if(choice.value(QStringLiteral("requires")).toInt(-1)>=0 &&
                   missing>=0 && missing<m_dialogues.size() && !visited.contains(missing))
                    queue.append(missing);
                const QJsonObject exchange=choice.value(QStringLiteral("exchange")).toObject();
                if(exchange.value(QStringLiteral("enabled")).toBool(false)) {
                    const bool repeated=exchange.value(QStringLiteral("wrongRepeatEnabled")).toBool(false);
                    for(int branch=0;branch<(repeated?5:1);++branch) {
                        const int target=exchange.value(giveRouteKey(branch)).toInt(-1);
                        if(target>=0 && target<m_dialogues.size() && !visited.contains(target))
                            queue.append(target);
                    }
                }
            }
        }
        return visited;
    }
    // Stage 5.166.76: The card is a small editor for the existing Adventure
    // node, not a second dialogue object. Its answer IDs remain index-stable.
    void setConversationField(int index,const QString &field,const QString &text) {
        if(index<0 || index>=m_dialogues.size())return;
        QJsonObject node=m_dialogues.at(index).toObject();
        if(node.value(field).toString()==text)return;
        node.insert(field,text);
        m_dialogues.replace(index,node);
        m_dialoguesChanged=true;
        m_dirty=true;
    }
    void setConversationAnswer(int index,int option,const QString &field,const QJsonValue &value) {
        if(index<0 || index>=m_dialogues.size() || option<0 || option>=3)return;
        QJsonObject node=m_dialogues.at(index).toObject();
        QJsonArray choices=node.value(QStringLiteral("choices")).toArray();
        while(choices.size()<3)choices.append(QJsonObject());
        QJsonObject answer=choices.at(option).toObject();
        if(answer.value(field)==value)return;
        if((field==QStringLiteral("next") || field==QStringLiteral("missingNext")) &&
           value.isDouble() && value.toInt(-1)==index) {
            const auto decision=QMessageBox::question(this,tr("Dialogue links to itself"),
                tr("Dialogue #%1, answer %2 would lead straight back to Dialogue #%1.\n\n"
                   "This creates a repeating conversation, not an engine crash, but "
                   "the player might get stuck repeating this line.\n\n"
                   "Create this loop intentionally?").arg(index).arg(option+1),
                QMessageBox::Yes|QMessageBox::No,QMessageBox::No);
            if(decision!=QMessageBox::Yes) {
                // A combo can already display the proposed destination; put
                // it back in sync with the unchanged Adventure data.
                QTimer::singleShot(0,this,[this] {
                    rebuildConversationFlow();redrawLinks();
                });
                return;
            }
        }
        answer.insert(field,value);
        choices.replace(option,answer);
        node.insert(QStringLiteral("choices"),choices);
        m_dialogues.replace(index,node);
        m_dialoguesChanged=true;
        m_dirty=true;
        // A newly selected destination can introduce or remove entire cards.
        // Defer graph rebuild until the combobox/line-edit signal completes.
        QTimer::singleShot(0,this,[this] {
            rebuildConversationFlow();
            redrawLinks();
            if(m_selectedCardId.startsWith(QStringLiteral("@conversation:")))
                showDetails(m_selectedCardId);
        });
    }
    void editGiveExchangeInPlace(int dialogue,int option) {
        if (dialogue<0 || dialogue>=m_dialogues.size() || option<0 || option>=3)return;
        const QJsonObject node=m_dialogues.at(dialogue).toObject();
        const QJsonArray choices=node.value(QStringLiteral("choices")).toArray();
        if (option>=choices.size())return;
        QJsonObject exchange=choices.at(option).toObject()
            .value(QStringLiteral("exchange")).toObject();

        const QJsonObject adventure=m_world.value(QStringLiteral("adventure")).toObject();
        const QJsonArray items=adventure.value(QStringLiteral("items")).toArray();
        QVector<GameAdventureAsset> objects;
        // Match the Adventure Editor's world-object picker. IDs are the
        // original resource IDs, never graph-card IDs or world slots.
        for (const QJsonValue &entry:m_world.value(QStringLiteral("resources")).toArray()) {
            const QJsonObject resource=entry.toObject();
            if (resource.value(QStringLiteral("kind")).toString()!=QStringLiteral("sprite"))continue;
            const QString type=resource.value(QStringLiteral("gameObject")).toObject()
                .value(QStringLiteral("type")).toString();
            if(type.isEmpty() || type==QStringLiteral("decoration") ||
               type==QStringLiteral("collectable"))continue;
            GameAdventureAsset object;
            object.id=resource.value(QStringLiteral("id")).toString();
            object.name=resource.value(QStringLiteral("name")).toString();
            if(!object.id.isEmpty())objects.append(object);
        }
        if(!editGameAdventureGiveExchange(this,&exchange,items,m_dialogues,
                                           objects,m_dialogueFolders))return;
        if(exchange==choices.at(option).toObject().value(QStringLiteral("exchange")).toObject()) {
            m_status->setText(tr("GIVE exchange: no changes to Dialogue #%1 answer %2.")
                .arg(dialogue).arg(option+1));
            return;
        }
        QJsonObject updatedChoice=choices.at(option).toObject();
        updatedChoice.insert(QStringLiteral("exchange"),exchange);
        QJsonArray updatedChoices=choices;
        updatedChoices.replace(option,updatedChoice);
        QJsonObject updatedNode=node;
        updatedNode.insert(QStringLiteral("choices"),updatedChoices);
        m_dialogues.replace(dialogue,updatedNode);
        m_dialoguesChanged=true;
        m_dirty=true;

        // The button lives in a QGraphicsProxyWidget owned by the GIVE card.
        // Rebuilding that card inside its own clicked signal would destroy
        // the sender mid-dispatch. Defer only the UI refresh, not the edit.
        QTimer::singleShot(0,this,[this,dialogue,option] {
            const QString id=giveCardId(dialogue,option);
            if(NodeCard *card=m_cards.value(id,nullptr)) {
                const QPointF position=card->pos();
                const bool collapsed=m_collapsedCards.contains(id);
                removeOrphanCard(id,true); // Removes only the visual card.
                if(giveExchange(dialogue,option).value(QStringLiteral("enabled")).toBool(false)) {
                    m_positions.insert(id,position);
                    if(collapsed)m_collapsedCards.insert(id);
                }
            }
            rebuildConversationFlow();
            redrawLinks();
            updateCanvasBounds();
            if(!saveAll())return; // Keep pending edits if disk validation fails.
            if(m_cards.contains(id))showDetails(id);
            m_status->setText(tr("Updated Dialogue #%1 answer %2 GIVE exchange in .sbgm. Visual Nodes remains open.")
                .arg(dialogue).arg(option+1));
        });
    }
    void openConversationInAdventure(int index) {
        if(index<0 || index>=m_dialogues.size())return;
        // Two independent editors must NEVER write the same world concurrently.
        // Commit pending edits (including graph layout) before handing off.
        if(m_dirty && !saveAll())return;
        // done(3) bypasses the usual window-close handler; remember where the
        // canvas was panned before handing off to the Adventure dialogue.
        if(!saveViewportOnly()) {
            fail(tr("Could not preserve the current graph view before opening Adventure Editor."));
            return;
        }
        m_openAdventureDialogue=index;
        done(3);
    }
    void makeConversationCard(int index,const QPointF &position) {
        const QString id=conversationCardId(index);
        if(index<0 || index>=m_dialogues.size() || m_cards.contains(id))return;
        const QJsonObject node=m_dialogues.at(index).toObject();
        constexpr qreal width=376.0;
        constexpr qreal height=456.0;
        auto *card=new NodeCard(QRectF(0,0,width,height));
        card->setData(0,QStringLiteral("card"));
        card->setData(1,id);
        card->setPen(QPen(QColor(190,139,229),1.5));
        card->setBrush(m_theme.panelBackground);
        m_scene->addItem(card);
        card->setPos(position);
        card->enableGridSnap();
        m_positions.insert(id,position);
        auto *header=new QGraphicsRectItem(QRectF(0,0,width,27),card);
        header->setPen(Qt::NoPen);
        header->setBrush(QColor(105,65,146));
        const QString speakerValue=node.value(QStringLiteral("speaker")).toString();
        auto *title=new QGraphicsSimpleTextItem(tr("Dialogue #%1  |  %2")
            .arg(index).arg(speakerValue.isEmpty()?tr("(no speaker)"):speakerValue.left(25)),card);
        title->setBrush(Qt::white);
        title->setPos(10,4);
        title->setToolTip(tr("Edits the existing Adventure dialogue ID %1; no IDs are renumbered.").arg(index));
        auto *input=new QGraphicsRectItem(QRectF(-6,104,12,12),card);
        input->setData(0,QStringLiteral("conversation-input"));
        input->setPen(QPen(QColor(229,199,253),1.5));
        input->setBrush(QColor(147,99,193));
        input->setToolTip(tr("Conversation flow input (visual only)"));
        input->setZValue(4);

        auto *panel=new QWidget;
        panel->setFixedWidth(354);
        panel->setStyleSheet(m_controlsStyle);
        auto *layout=new QVBoxLayout(panel);
        layout->setContentsMargins(3,2,3,2);
        layout->setSpacing(3);
        auto *speaker=new QLineEdit(node.value(QStringLiteral("speaker")).toString(),panel);
        speaker->setMaxLength(36);
        speaker->setPlaceholderText(tr("Speaker"));
        layout->addWidget(new QLabel(tr("Speaker"),panel));
        layout->addWidget(speaker);
        auto *speech=new QPlainTextEdit(node.value(QStringLiteral("text")).toString(),panel);
        speech->setProperty("conversationSpeechInput",true);
        speech->setFixedHeight(74);
        speech->setTabChangesFocus(true);
        speech->setPlaceholderText(tr("Dialogue text"));
        layout->addWidget(new QLabel(tr("Dialogue text"),panel));
        layout->addWidget(speech);
        auto *answerHead=new QLabel(tr("Answers → destination dialogue"),panel);
        layout->addWidget(answerHead);
        const QJsonArray choices=node.value(QStringLiteral("choices")).toArray();
        for(int option=0;option<3;++option) {
            const QJsonObject answer=option<choices.size()?choices.at(option).toObject():QJsonObject();
            auto *answerLine=new QHBoxLayout;
            answerLine->setSpacing(3);
            auto *answerLabel=new QLabel(tr("%1.").arg(option+1),panel);
            auto *answerText=new QLineEdit(answer.value(QStringLiteral("text")).toString(),panel);
            answerText->setProperty("conversationAnswerIndex",option);
            answerText->setPlaceholderText(tr("Answer %1 (blank = unused)").arg(option+1));
            answerText->setMaxLength(256);
            answerLine->addWidget(answerLabel);
            answerLine->addWidget(answerText,1);
            layout->addLayout(answerLine);

            // The destination has its own full-width row. A narrow dropdown
            // clipped the speaker and text, leaving only opaque numeric IDs.
            auto *nextLine=new QHBoxLayout;
            nextLine->setSpacing(3);
            nextLine->addWidget(new QLabel(tr("Next →"),panel));
            auto *next=new ConversationTreeCombo(panel);
            next->chooseDestination=[this](int current,int *chosen) {
                return browseConversationDestination(current,chosen);
            };
            next->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
            next->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLengthWithIcon);
            next->setMinimumContentsLength(18);
            next->setMaxVisibleItems(15);
            next->addItem(tr("Close conversation"),-1);
            next->setItemData(0,tr("Close this conversation after this answer."),Qt::ToolTipRole);
            for(int target=0;target<m_dialogues.size();++target) {
                const QJsonObject destination=m_dialogues.at(target).toObject();
                QString speakerName=destination.value(QStringLiteral("speaker")).toString().simplified();
                QString snippet=destination.value(QStringLiteral("text")).toString().simplified();
                if(speakerName.isEmpty())speakerName=tr("(no speaker)");
                if(snippet.isEmpty())snippet=tr("(empty dialogue)");
                const QString label=tr("#%1 | %2: %3").arg(target)
                    .arg(speakerName.left(32),snippet.left(75));
                next->addItem(label,target);  // numeric ID is still the saved .sbgm value.
                next->setItemData(next->count()-1,
                    tr("Dialogue #%1\nSpeaker: %2\nText: %3")
                        .arg(target).arg(speakerName,snippet),Qt::ToolTipRole);
            }
            // The actual selector is a modal folder tree outside the graphics
            // scene, avoiding popup clipping behind other cards/wires.
            const int selected=answer.value(QStringLiteral("next")).toInt(-1);
            // Preserve invalid legacy references visibly; never silently
            // replace them with Close when a card is opened.
            if(selected>=m_dialogues.size()) {
                next->addItem(tr("MISSING dialogue #%1").arg(selected),selected);
                next->setItemData(next->count()-1,
                    tr("This dialogue ID does not exist in this world."),Qt::ToolTipRole);
            }
            next->setCurrentIndex(qMax(0,next->findData(selected)));
            next->setToolTip(next->currentData(Qt::ToolTipRole).toString());
            nextLine->addWidget(next,1);
            layout->addLayout(nextLine);
            const int required=answer.value(QStringLiteral("requires")).toInt(-1);
            if(required>=0) {
                const QJsonArray items=m_world.value(QStringLiteral("adventure")).toObject()
                    .value(QStringLiteral("items")).toArray();
                const QString itemName=(required<items.size())?
                    items.at(required).toObject().value(QStringLiteral("name")).toString():QString();
                auto *gate=new QLabel(tr("Needs item #%1%2: amber route runs if missing")
                    .arg(required).arg(itemName.isEmpty()?QString():QStringLiteral(" (")+itemName+QStringLiteral(")")),panel);
                gate->setWordWrap(true);
                gate->setToolTip(tr("If the player selects this answer without item #%1, Adventure follows missingNext instead of Next.").arg(required));
                layout->addWidget(gate);
                auto *missingLine=new QHBoxLayout;
                missingLine->addWidget(new QLabel(tr("No item →"),panel));
                auto *missingNext=new ConversationTreeCombo(panel);
                missingNext->chooseDestination=[this](int current,int *chosen) {
                    return browseConversationDestination(current,chosen,true);
                };
                missingNext->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
                missingNext->addItem(tr("No alternate dialogue (keep behaviour)"),-1);
                for(int target=0;target<m_dialogues.size();++target) {
                    const QJsonObject destination=m_dialogues.at(target).toObject();
                    missingNext->addItem(tr("#%1 | %2: %3").arg(target)
                        .arg(destination.value(QStringLiteral("speaker")).toString().simplified().left(32),
                             destination.value(QStringLiteral("text")).toString().simplified().left(75)),target);
                }
                const int alternate=answer.value(QStringLiteral("missingNext")).toInt(-1);
                if(alternate>=m_dialogues.size())
                    missingNext->addItem(tr("MISSING dialogue #%1").arg(alternate),alternate);
                missingNext->setCurrentIndex(qMax(0,missingNext->findData(alternate)));
                missingNext->setToolTip(tr("AMBER: when item #%1 is missing, go to the selected dialogue. Same missingNext field as Adventure Editor.").arg(required));
                missingLine->addWidget(missingNext,1);
                layout->addLayout(missingLine);
                auto *missingPort=new QGraphicsEllipseItem(QRectF(width-8,0,13,13),card);
                missingPort->setData(0,QStringLiteral("conversation-missing-output"));
                missingPort->setData(1,id);
                missingPort->setData(2,option);
                missingPort->setPen(QPen(QColor(255,215,142),1.5));
                missingPort->setBrush(QColor(233,177,98));
                missingPort->setZValue(4);
                missingPort->setToolTip(tr("AMBER · ANSWER %1 · ITEM MISSING\nWhen the player lacks required item #%2, use the dashed amber route.\nDrag to a dialogue's input square, or choose a destination under 'No item'.\nHollow = no alternate dialogue selected.").arg(option+1).arg(required));
                connect(missingNext,qOverload<int>(&QComboBox::currentIndexChanged),this,
                    [this,index,option,missingNext](int) {
                        setConversationAnswer(index,option,QStringLiteral("missingNext"),
                                              QJsonValue(missingNext->currentData().toInt()));
                    });
            }
            const QJsonObject exchange=answer.value(QStringLiteral("exchange")).toObject();
            if(exchange.value(QStringLiteral("enabled")).toBool(false)) {
                auto *giveAnchor=new QGraphicsEllipseItem(QRectF(width-6.5,0,13,13),card);
                giveAnchor->setData(0,QStringLiteral("give-anchor"));
                giveAnchor->setData(1,id);
                giveAnchor->setData(2,option);
                giveAnchor->setPen(QPen(QColor(133,224,205),1.4));
                giveAnchor->setBrush(QColor(63,151,144));
                giveAnchor->setZValue(4);
                giveAnchor->setToolTip(tr("TEAL · GIVE EXCHANGE · Answer %1\nThis answer owns an existing Adventure inventory exchange.\nDrag from here onto empty canvas to position its GIVE card.\nThe required items and game logic are unchanged.").arg(option+1));
            }
            auto *port=new QGraphicsEllipseItem(QRectF(width-8,0,13,13),card);
            port->setData(0,QStringLiteral("conversation-output"));
            port->setData(1,id);
            port->setData(2,option);
            port->setPen(QPen(QColor(237,206,252),1.4));
            port->setBrush(QColor(151,104,202));
            port->setZValue(4);
            port->setToolTip(tr("PURPLE · ANSWER %1 · NORMAL ROUTE\nIf the answer is allowed (required item is present), go to Next.\nDrag to another dialogue's input square, or choose Next below.\nHollow = no connected dialogue.").arg(option+1));
            connect(answerText,&QLineEdit::textEdited,this,[this,index,option](const QString &text) {
                setConversationAnswer(index,option,QStringLiteral("text"),text);
            });
            connect(next,qOverload<int>(&QComboBox::currentIndexChanged),this,[this,index,option,next](int) {
                next->setToolTip(next->currentData(Qt::ToolTipRole).toString());
                setConversationAnswer(index,option,QStringLiteral("next"),QJsonValue(next->currentData().toInt()));
            });
        }
        auto *advanced=new QPushButton(tr("Open this dialogue in Adventure Editor..."),panel);
        advanced->setToolTip(tr("Save changes and open this exact dialogue ID in Adventure Editor for items, effects and advanced actions."));
        layout->addWidget(advanced);
        // Widget coordinates are only reliable once Qt has embedded/polished
        // the form. redrawLinks() owns the final port geometry.
        // Don't use QWidget::mapTo(panel) here: it returns provisional rows.
        auto *proxy=new QGraphicsProxyWidget(card);
        proxy->setWidget(panel);
        proxy->setPos(9,33);
        proxy->setZValue(3);
        // Item-gated answers can add extra explanatory lines. Size this card
        // to its actual controls, instead of clipping the Adventure button.
        const qreal neededHeight=33.0+panel->sizeHint().height()+12.0;
        if(neededHeight>card->rect().height())
            card->setRect(QRectF(0,0,width,neededHeight));
        connect(speaker,&QLineEdit::textEdited,this,[this,index,title](const QString &text) {
            setConversationField(index,QStringLiteral("speaker"),text.left(36));
            title->setText(tr("Dialogue #%1  |  %2").arg(index).arg(text.isEmpty()?tr("(no speaker)"):text.left(25)));
        });
        connect(speech,&QPlainTextEdit::textChanged,this,[this,index,speech] {
            setConversationField(index,QStringLiteral("text"),speech->toPlainText().left(2048));
        });
        connect(advanced,&QPushButton::clicked,this,[this,index] {openConversationInAdventure(index);});
        card->moved=[this,id,card] {updateLiveWires(id,card);};
        addFoldButton(card,id);
        m_cards.insert(id,card);
        auto *item=new QListWidgetItem(tr("Dialogue #%1  (%2)").arg(index)
            .arg(speakerValue.isEmpty()?tr("no speaker"):speakerValue),m_list);
        item->setData(Qt::UserRole,id);
        item->setToolTip(tr("Editable Adventure dialogue. The .sbgm remains the only gameplay source."));
    }
    void makeGiveCard(int dialogue,int option,const QPointF &position) {
        const QString id=giveCardId(dialogue,option);
        if(m_cards.contains(id))return;
        const QJsonObject exchange=giveExchange(dialogue,option);
        if(!exchange.value(QStringLiteral("enabled")).toBool(false))return;
        const bool repeated=exchange.value(QStringLiteral("wrongRepeatEnabled")).toBool(false);
        const QJsonArray inventory=m_world.value(QStringLiteral("adventure")).toObject()
            .value(QStringLiteral("items")).toArray();
        const auto itemName=[&inventory](int item)->QString {
            if(item<0)return QObject::tr("not selected");
            if(item>=inventory.size())return QObject::tr("MISSING item #%1").arg(item);
            const QString name=inventory.at(item).toObject().value(QStringLiteral("name")).toString();
            return name.isEmpty()?QObject::tr("Item #%1").arg(item):name;
        };
        QStringList requested;
        for(const QJsonValue &v:exchange.value(QStringLiteral("items")).toArray())
            requested<<itemName(v.toInt(-1));
        const QString requestedLabel=requested.isEmpty()?tr("No requested items configured"):
            requested.join(exchange.value(QStringLiteral("logic")).toString()==QStringLiteral("any")?
                tr(" OR "):tr(" AND "));
        constexpr qreal width=386.0;
        auto *card=new NodeCard(QRectF(0,0,width,repeated?447.0:250.0));
        card->setData(0,QStringLiteral("card"));card->setData(1,id);
        card->setPen(QPen(QColor(105,207,189),1.6));
        card->setBrush(m_theme.panelBackground);
        m_scene->addItem(card);
        card->setPos(position);card->enableGridSnap();m_positions.insert(id,position);
        auto *header=new QGraphicsRectItem(QRectF(0,0,width,27),card);
        header->setPen(Qt::NoPen);header->setBrush(QColor(34,115,111));
        auto *title=new QGraphicsSimpleTextItem(tr("GIVE | Dialogue #%1 · Answer %2")
            .arg(dialogue).arg(option+1),card);
        title->setBrush(Qt::white);title->setPos(10,4);
        title->setToolTip(tr("This is the existing Adventure Editor GIVE exchange, not a new game object."));
        auto *input=new QGraphicsRectItem(QRectF(-6,50,12,12),card);
        input->setData(0,QStringLiteral("exchange-input"));
        input->setPen(QPen(QColor(144,231,217),1.6));
        input->setBrush(QColor(56,153,141));input->setZValue(4);
        input->setToolTip(tr("From dialogue #%1 answer %2, GIVE mode. This input is automatic from Adventure data.")
            .arg(dialogue).arg(option+1));
        auto *panel=new QWidget;
        panel->setFixedWidth(365);
        panel->setStyleSheet(m_controlsStyle);
        auto *layout=new QVBoxLayout(panel);
        layout->setContentsMargins(6,4,6,4);layout->setSpacing(5);
        auto *requirements=new QLabel(tr("Required: %1").arg(requestedLabel),panel);
        requirements->setWordWrap(true);
        requirements->setToolTip(tr("Requested items, AND/OR mode and consume options are edited in Adventure Editor."));
        layout->addWidget(requirements);
        auto *flags=new QLabel(tr("%1   |   %2")
            .arg(exchange.value(QStringLiteral("incremental")).toBool(false)?tr("Remembers hand-ins"):tr("Single exchange"))
            .arg(exchange.value(QStringLiteral("consume")).toBool(true)?tr("Consumes items"):tr("Keeps items")),panel);
        layout->addWidget(flags);
        if(repeated) {
            auto *tracked=new QLabel(tr("Repeated wrong offer: %1").arg(itemName(exchange.value(QStringLiteral("wrongRepeatItem")).toInt(-1))),panel);
            tracked->setWordWrap(true);layout->addWidget(tracked);
        }
        const QStringList names={tr("Any wrong item"),tr("Tracked item · first offer"),
             tr("Tracked item · second offer"),tr("Tracked item · third offer"),
             tr("Tracked item · fourth+ offer")};
        const int count=repeated?5:1;
        QVector<QPair<QGraphicsEllipseItem*,QWidget*>> outputs;
        for(int branch=0;branch<count;++branch) {
            auto *label=new QLabel(names.at(branch),panel);
            label->setToolTip(branch==0?
                tr("General response when the offered inventory item is not accepted. A tracked repeated wrong item may use its own dialogue instead."):
                tr("Special response for the tracked wrong item on this numbered offer. This is an existing Adventure GIVE exchange rule."));
            layout->addWidget(label);
            auto *destination=new ConversationTreeCombo(panel);
            destination->chooseDestination=[this](int current,int *chosen) {
                return browseConversationDestination(current,chosen,false,true);
            };
            destination->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
            // Match each socket to its specific GIVE route even if the form
            // gains further comboboxes or Qt changes child traversal order.
            destination->setProperty("giveRouteBranch",branch);
            destination->addItem(tr("Keep current NPC dialogue"),-1);
            for(int target=0;target<m_dialogues.size();++target)
                destination->addItem(npcDialogueTitle(target),target);
            const int value=exchange.value(giveRouteKey(branch)).toInt(-1);
            if(value>=m_dialogues.size())destination->addItem(tr("MISSING dialogue #%1").arg(value),value);
            destination->setCurrentIndex(qMax(0,destination->findData(value)));
            destination->setToolTip(tr("Select the existing Adventure destination; the saved exchange field '%1' is updated. A value of -1 keeps the normal NPC dialogue.")
                .arg(giveRouteKey(branch)));
            layout->addWidget(destination);
            auto *output=new QGraphicsEllipseItem(QRectF(width-8,0,13,13),card);
            output->setData(0,QStringLiteral("exchange-output"));
            output->setData(1,id);output->setData(2,branch);
            output->setPen(QPen(branch==0?QColor(255,169,135):QColor(250,205,118),1.5));
            output->setBrush(branch==0?QColor(180,92,73):QColor(186,145,61));
            output->setZValue(4);
            output->setToolTip(tr("%1: drag to a dialogue input, or use the destination selector. Hollow = no selected dialogue.")
                .arg(names.at(branch)));
            outputs.append(qMakePair(output,static_cast<QWidget*>(destination)));
            connect(destination,qOverload<int>(&QComboBox::currentIndexChanged),this,
                    [this,dialogue,option,branch,destination](int) {
                setGiveDestination(dialogue,option,branch,destination->currentData().toInt());
            });
        }
        auto *advanced=new QPushButton(tr("Edit full GIVE exchange in Adventure Editor..."),panel);
        advanced->setToolTip(tr("Edit this answer's GIVE exchange directly. Save updates the existing .sbgm rules and refreshes this graph; Cancel changes nothing."));
        layout->addWidget(advanced);
        auto *proxy=new QGraphicsProxyWidget(card);
        proxy->setWidget(panel);proxy->setPos(9,33);proxy->setZValue(3);
        // Position outputs AFTER proxy embedding and Qt style/layout polish.
        // mapTo(panel) before setWidget() used provisional widget geometry,
        // placing sockets progressively farther below their real dropdowns.
        panel->ensurePolished();
        layout->activate();
        panel->adjustSize();
        layout->activate();
        for(const auto &pair:outputs) {
            const QRectF row=proxy->subWidgetRect(pair.second);
            if(row.isEmpty())continue;
            const qreal y=proxy->pos().y()+row.center().y();
            pair.first->setRect(QRectF(width-6.5,y-6.5,13,13));
        }
        const qreal neededHeight=proxy->pos().y()+panel->height()+12.0;
        if(neededHeight>card->rect().height())card->setRect(QRectF(0,0,width,neededHeight));
        connect(advanced,&QPushButton::clicked,this,[this,dialogue,option] {
            editGiveExchangeInPlace(dialogue,option);
        });
        card->moved=[this,id,card] {updateLiveWires(id,card);};
        addFoldButton(card,id);m_cards.insert(id,card);
        auto *row=new QListWidgetItem(tr("GIVE | Dialogue #%1 Answer %2").arg(dialogue).arg(option+1),m_list);
        row->setData(Qt::UserRole,id);
        row->setToolTip(tr("Real Adventure GIVE exchange. Wrong-item and repeated-offer response destinations are editable here."));
    }
    void rebuildConversationFlow() {
        QSet<int> wanted;
        QSet<QString> wantedGive;
        QHash<int,int> depth;
        QList<int> roots=m_conversationRoots.values();
        std::sort(roots.begin(),roots.end());
        for (int root:roots) {
            if(root<0 || root>=m_dialogues.size())continue;
            QList<int> queue{root};
            if(!depth.contains(root))depth.insert(root,0);
            for(int head=0;head<queue.size();++head) {
                const int current=queue.at(head);
                if(wanted.contains(current))continue;
                wanted.insert(current);
                const QJsonArray choices=m_dialogues.at(current).toObject()
                    .value(QStringLiteral("choices")).toArray();
                for(int option=0;option<choices.size();++option) {
                    const QJsonObject c=choices.at(option).toObject();
                    if(c.value(QStringLiteral("text")).toString().trimmed().isEmpty())continue;
                    const int next=c.value(QStringLiteral("next")).toInt(-1);
                    const int missing=c.value(QStringLiteral("missingNext")).toInt(-1);
                    const int requires=c.value(QStringLiteral("requires")).toInt(-1);
                    for(int destination:{next,(requires>=0?missing:-1)}) {
                        if(destination<0 || destination>=m_dialogues.size())continue;
                        if(!depth.contains(destination))depth.insert(destination,depth.value(current)+1);
                        if(!wanted.contains(destination) && !queue.contains(destination))queue.append(destination);
                    }
                    const QJsonObject exchange=c.value(QStringLiteral("exchange")).toObject();
                    if(!exchange.value(QStringLiteral("enabled")).toBool(false))continue;
                    if(option<3)wantedGive.insert(giveCardId(current,option));
                    const int count=exchange.value(QStringLiteral("wrongRepeatEnabled")).toBool(false)?5:1;
                    for(int branch=0;branch<count;++branch) {
                        const int destination=exchange.value(giveRouteKey(branch)).toInt(-1);
                        if(destination<0 || destination>=m_dialogues.size())continue;
                        if(!depth.contains(destination))depth.insert(destination,depth.value(current)+2);
                        if(!wanted.contains(destination) && !queue.contains(destination))queue.append(destination);
                    }
                }
            }
        }
        // Remove only preview cards no longer reached by ANY remembered root.
        // Hiding a flow should preserve the layout, so hidden roots still count.
        for (const QString &id:m_cards.keys()) {
            if(id.startsWith(QStringLiteral("@give:"))) {
                if(!wantedGive.contains(id))removeOrphanCard(id,true);
                continue;
            }
            if (!id.startsWith(QStringLiteral("@conversation:")))continue;
            const int index=id.mid(QStringLiteral("@conversation:").size()).toInt();
            if (!wanted.contains(index))removeOrphanCard(id,true);
        }
        QList<int> indices=wanted.values();
        std::sort(indices.begin(),indices.end(),[&depth](int a,int b) {
            if(depth.value(a)!=depth.value(b))return depth.value(a)<depth.value(b);
            return a<b;
        });
        QHash<int,int> row;
        const QPointF anchor=m_flowAnchor.isNull()?
            viewportInsertionPoint(QSizeF(376,456)):m_flowAnchor;
        for (int index:indices) {
            const int level=qMin(depth.value(index),100);
            const int ordinal=row.value(level,0);
            row[level]=ordinal+1;
            const QString id=conversationCardId(index);
            if(!m_cards.contains(id))makeConversationCard(index,m_positions.value(id,
                anchor+QPointF(level*435.0,ordinal*520.0)));
        }
        QStringList giveIds=wantedGive.values();std::sort(giveIds.begin(),giveIds.end());
        for(const QString &id:giveIds) {
            int dialogue=-1,answer=-1;
            if(!giveCardReference(id,&dialogue,&answer) || m_cards.contains(id))continue;
            const QPointF parent=m_cards.contains(conversationCardId(dialogue))?
                m_cards.value(conversationCardId(dialogue))->pos():anchor;
            makeGiveCard(dialogue,answer,m_positions.value(id,
                parent+QPointF(435.0,580.0+answer*500.0)));
        }
        updateConversationFlowGroups();
        updateConversationFlowVisibility();
    }
    void showConversationFlow(int root) {
        if(root<0 || root>=m_dialogues.size())return;
        const QString rootId=conversationCardId(root);
        m_flowAnchor=m_positions.contains(rootId)?m_positions.value(rootId):
            viewportInsertionPoint(QSizeF(376,456));
        m_conversationRoots.insert(root);
        m_hiddenConversationRoots.remove(root);
        rebuildConversationFlow();
        redrawLinks();
        m_dirty=true;
        const QString id=conversationCardId(root);
        if (m_cards.contains(id)) {m_view->centerOn(m_cards.value(id));showDetails(id);}
        m_status->setText(tr("Conversation #%1: edit text/answers/next links here, or open Adventure Editor for advanced settings. Save Graph + World to commit.").arg(root));
    }
    void showConversationFlowPicker(QWidget *button) {
        if(m_dialogues.isEmpty()) {
            QMessageBox::information(this,tr("Conversation Flow"),tr("This world has no Adventure dialogues."));
            return;
        }
        QMenu menu(this);
        for(const QString &id:m_order) {
            const NodeObject npc=m_objects.value(id);
            if(npc.type!=QStringLiteral("npc"))continue;
            const bool start=npc.npcStartNode>=0 && npc.npcStartNode<m_dialogues.size();
            const bool done=npc.npcDoneNode>=0 && npc.npcDoneNode<m_dialogues.size();
            if(!start && !done)continue;
            auto *sub=menu.addMenu(npc.name);
            if(start)sub->addAction(tr("Opening: %1").arg(npcDialogueTitle(npc.npcStartNode)))
                ->setData(npc.npcStartNode);
            if(done)sub->addAction(tr("After helped: %1").arg(npcDialogueTitle(npc.npcDoneNode)))
                ->setData(npc.npcDoneNode);
        }
        menu.addSeparator();
        QAction *byId=menu.addAction(tr("Choose dialogue by ID..."));
        QAction *hideAll=menu.addAction(tr("Hide all conversation previews"));
        QAction *choice=menu.exec(button->mapToGlobal(QPoint(0,button->height())));
        if(!choice)return;
        if(choice==hideAll) {
            m_hiddenConversationRoots=m_conversationRoots;
            rebuildConversationFlow();redrawLinks();m_dirty=true;
            return;
        }
        if(choice==byId) {
            bool ok=false;
            const int index=QInputDialog::getInt(this,tr("Conversation Flow"),
                tr("Existing dialogue ID (0 to %1)").arg(m_dialogues.size()-1),
                0,0,m_dialogues.size()-1,1,&ok);
            if(ok)showConversationFlow(index);
        } else if(choice->data().isValid())showConversationFlow(choice->data().toInt());
    }
    void hideConversationContaining(int index) {
        QList<int> roots=m_conversationRoots.values();
        for(int root:roots)
            if(conversationReachable(root).contains(index))m_hiddenConversationRoots.insert(root);
        rebuildConversationFlow();redrawLinks();m_dirty=true;
        m_status->setText(tr("Conversation preview hidden. Gameplay dialogue is unchanged."));
    }
    // The route in .vsgm tells only WHERE to draw a dialogue link.
    // The branch's actual selected dialogue is always stored in .sbgm.
    bool npcRoutePoint(const QString &source,int dialogue,QPointF *point=nullptr) const {
        const QJsonObject route=m_npcDialogueRoutes.value(source);
        const QString npcId=route.value(QStringLiteral("npc")).toString();
        const QString slot=route.value(QStringLiteral("slot")).toString();
        if(dialogue<0 || route.value(QStringLiteral("dialogue")).toInt(-1)!=dialogue ||
           !m_objects.contains(npcId) || m_objects.value(npcId).type!=QStringLiteral("npc") ||
           !m_cards.contains(npcId))return false;
        const NodeObject npc=m_objects.value(npcId);
        if ((slot==QStringLiteral("start") && npc.npcStartNode!=dialogue) ||
            (slot==QStringLiteral("helped") && npc.npcDoneNode!=dialogue))return false;
        if(slot!=QStringLiteral("start") && slot!=QStringLiteral("helped"))return false;
        if(point)*point=m_cards.value(npcId)->wirePoint(QPointF(0,slot==QStringLiteral("start")?101:163));
        return true;
    }
    void renderCards() {
        const QSet<QString> linked=linkedObjectIds();
        int triggerCount=0,targetCount=0,otherCount=0;
        for (const QString &id:m_order) {
            const NodeObject node=m_objects.value(id);
            if (!linked.contains(id) && !m_placedCards.contains(id))continue;
            const bool source=isActionSource(node) || !eventKinds(node.type).isEmpty();
            const int col=source?0:(node.type==QStringLiteral("npc")?2:1);
            const int row=source?triggerCount++:(col==2?targetCount++:otherCount++);
            // Expanded NPC cards contain two dialogue selectors and must not
            // overlap the next automatically placed NPC in a populated world.
            makeObjectCard(id,m_positions.value(id,QPointF(70+col*340,
                85+row*(node.type==QStringLiteral("npc")?305:125))));
        }
        const QSet<QString> requested=m_dialogueCards;
        m_dialogueCards.clear();
        for (const QString &id:m_order)
            if (m_objects.value(id).type==QStringLiteral("trigger") &&
                (m_objects.value(id).dialogueNode>=0 ||
                 m_placedCards.contains(dialogueCardId(id)) || requested.contains(id))) {
                if (!m_cards.contains(id))
                    makeObjectCard(id,m_positions.value(id,QPointF(70,85+triggerCount++*125)));
                if (!npcRoutePoint(id,m_objects.value(id).dialogueNode))createDialogueCard(id);
            }
        for (const QString &id:m_order) {
            const NodeObject n=m_objects.value(id);
            if (n.type!=QStringLiteral("trigger"))continue;
            if (!n.toggleStateTargetId.isEmpty() || m_placedCards.contains(toggleCardId(id))) {
                if (!m_cards.contains(id))makeObjectCard(id,m_positions.value(id,QPointF(70,85)));
                createToggleCard(id);
            }
            if ((n.toggleTrueDialogueNode>=0 || m_placedCards.contains(branchCardId(id,true))) &&
                !npcRoutePoint(QStringLiteral("@stateout:true:")+id,n.toggleTrueDialogueNode))
                createBranchCard(id,true);
            if ((n.toggleFalseDialogueNode>=0 || m_placedCards.contains(branchCardId(id,false))) &&
                !npcRoutePoint(QStringLiteral("@stateout:false:")+id,n.toggleFalseDialogueNode))
                createBranchCard(id,false);
        }
        for(const QString &owner:m_order) {
            const NodeObject node=m_objects.value(owner);
            if(node.logicNodes.isEmpty())continue;
            for(const QJsonValue &entry:node.logicNodes) {
                const QJsonObject o=entry.toObject();
                const QString id=o.value(QStringLiteral("id")).toString();
                const QString key=graphKey(owner,id);
                if(!m_cards.contains(owner))makeObjectCard(owner,m_positions.value(owner,QPointF(70,85)));
                for(const QJsonValue &v:o.value(QStringLiteral("inputs")).toArray()) {
                    const QJsonObject ref=v.toObject();
                    const QString obj=ref.value(QStringLiteral("id")).toString();
                    if(ref.value(QStringLiteral("kind")).toString()==QStringLiteral("object") &&
                       m_objects.contains(obj) && !m_cards.contains(obj))
                        makeObjectCard(obj,m_positions.value(obj,QPointF(390,90)));
                }
                makeGraphCard(owner,id);
                for(const bool yes:{true,false}) {
                    const QString branch=yes?QStringLiteral("trueActions"):QStringLiteral("falseActions");
                    for(const QJsonValue &a:o.value(branch).toArray()) {
                        const QString obj=a.toObject().value(QStringLiteral("objectId")).toString();
                        if(m_objects.contains(obj) && !m_cards.contains(obj))
                            makeObjectCard(obj,m_positions.value(obj,QPointF(700,90)));
                    }
                    const int dialogue=o.value(yes?QStringLiteral("trueDialogueNode"):
                        QStringLiteral("falseDialogueNode")).toInt(-1);
                    if(dialogue>=0 && !npcRoutePoint(
                        QStringLiteral("@graphbranch:")+(yes?QStringLiteral("true:"):QStringLiteral("false:"))+key,dialogue) &&
                       !m_graphDialogueRoutes.contains(graphDialogueKey(key,yes)))
                        makeGraphDialogueCard(key,yes);
                }
            }
        }
        rebuildConversationFlow();
        // The target might be a card created later in this rendering pass.
        // If a saved visual route is no longer valid, restore its own card.
        for(const QString &owner:m_order) {
            const NodeObject trigger=m_objects.value(owner);
            if(trigger.logicNodes.isEmpty())continue;
            for(const QJsonValue &v:trigger.logicNodes) {
                const QJsonObject node=v.toObject();
                const QString key=graphKey(owner,node.value(QStringLiteral("id")).toString());
                for(bool yes:{true,false}) {
                    const int dialogue=node.value(yes?QStringLiteral("trueDialogueNode"):
                        QStringLiteral("falseDialogueNode")).toInt(-1);
                    const QString own=graphDialogueKey(key,yes);
                    if(dialogue<0 || !m_graphDialogueRoutes.contains(own))continue;
                    if(!validSharedGraphDialogue(own,dialogue)) {
                        m_graphDialogueRoutes.remove(own);
                        if(!m_cards.contains(own))makeGraphDialogueCard(key,yes);
                    }
                }
            }
        }
        redrawLinks();
    }
    // Match the Adventure Dialogue Editor's nested folder tree and stable node
    // indices. The visual graph NEVER copies or reorders dialogue definitions.
    void populateDialogueChoices(QTreeWidget *tree,QTreeWidgetItem *parent,
                                 bool allowCreate=true) const {
        QHash<QString,QTreeWidgetItem*> folders;
        QSet<QString> processed;
        for (int pass=0;pass<=m_dialogueFolders.size();++pass) {
            for (const QJsonValue &entry:m_dialogueFolders) {
                const QJsonObject folder=entry.toObject();
                const QString id=folder.value(QStringLiteral("id")).toString();
                const QString parentId=folder.value(QStringLiteral("parentId")).toString();
                if (id.isEmpty() || processed.contains(id))continue;
                if (!parentId.isEmpty() && !folders.contains(parentId) &&
                    pass<m_dialogueFolders.size())continue;
                QTreeWidgetItem *owner=folders.value(parentId,parent);
                auto *item=new QTreeWidgetItem(owner);
                item->setText(0,folder.value(QStringLiteral("name")).toString(tr("Unnamed folder")));
                item->setFlags(item->flags() & ~Qt::ItemIsSelectable);
                folders.insert(id,item);
                processed.insert(id);
            }
            if (processed.size()>=m_dialogueFolders.size())break;
        }
        auto *unfiled=new QTreeWidgetItem(parent);
        unfiled->setText(0,tr("Unfiled dialogues"));
        unfiled->setFlags(unfiled->flags() & ~Qt::ItemIsSelectable);
        int unfiledCount=0;
        for (int i=0;i<m_dialogues.size();++i) {
            const QJsonObject dialogue=m_dialogues.at(i).toObject();
            const QString folderId=dialogue.value(QStringLiteral("folderId")).toString();
            QTreeWidgetItem *owner=folders.value(folderId,unfiled);
            if (owner==unfiled)++unfiledCount;
            auto *item=new QTreeWidgetItem(owner);
            const QString speaker=dialogue.value(QStringLiteral("speaker")).toString().simplified();
            const QString speech=dialogue.value(QStringLiteral("text")).toString().simplified();
            item->setText(0,tr("#%1 | %2: %3").arg(i)
                .arg(speaker.isEmpty()?tr("(no speaker)"):speaker.left(32),
                     speech.isEmpty()?tr("(empty dialogue)"):speech.left(95)));
            item->setData(0,Qt::UserRole,QStringLiteral("@dialogue-node:%1").arg(i));
            item->setToolTip(0,tr("Dialogue #%1\nSpeaker: %2\nText: %3\nFolder changes do not change dialogue IDs.")
                .arg(i).arg(speaker,speech));
        }
        if (!unfiledCount)delete unfiled;
        // The normal action picker can create new dialogues; routing an answer
        // cannot. Keep its destination tree restricted to existing IDs.
        if (allowCreate) {
            auto *create=new QTreeWidgetItem(parent);
            create->setText(0,tr("+ Create New Dialogue"));
            create->setData(0,Qt::UserRole,QStringLiteral("@create-dialogue"));
        }
    }
    // The selector lives in a separate modal window rather than the scene's
    // proxy-widget popup stack. Folder hierarchy comes directly from Adventure
    // dialogueFolders/folderId; clicking a folder never changes the answer.
    bool browseConversationDestination(int current,int *chosen,bool missingRoute=false,bool giveRoute=false) {
        if (!chosen)return false;
        QDialog browser(this);
        browser.setWindowTitle(giveRoute?tr("Choose GIVE Exchange Response"):missingRoute?
            tr("Choose Missing-Item Dialogue"):tr("Choose Next Dialogue"));
        browser.setWindowModality(Qt::ApplicationModal);
        browser.resize(650,520);
        auto *layout=new QVBoxLayout(&browser);
        auto *search=new QLineEdit(&browser);
        search->setPlaceholderText(tr("Search folder, speaker or dialogue text..."));
        search->setClearButtonEnabled(true);
        layout->addWidget(search);
        auto *tree=new QTreeWidget(&browser);
        tree->setHeaderHidden(true);
        tree->setUniformRowHeights(true);
        tree->setSelectionMode(QAbstractItemView::SingleSelection);
        layout->addWidget(tree,1);
        auto *root=new QTreeWidgetItem(tree);
        root->setText(0,tr("Adventure Dialogues"));
        root->setFlags(root->flags() & ~Qt::ItemIsSelectable);
        auto *close=new QTreeWidgetItem(root);
        close->setText(0,giveRoute?tr("Keep current NPC dialogue (no separate response)"):
            missingRoute?tr("No missing-item dialogue (keep current behaviour)"):
            tr("Close conversation"));
        close->setData(0,Qt::UserRole,QStringLiteral("@close-conversation"));
        close->setToolTip(0,giveRoute?
            tr("-1: no specific GIVE-response dialogue; the existing NPC conversation behaviour is retained."):
            missingRoute?tr("No alternate dialogue will be started when the required item is absent."):
            tr("End the conversation after this answer."));
        populateDialogueChoices(tree,root,false);
        QTreeWidgetItem *selected=(current==-1)?close:nullptr;
        const QString key=QStringLiteral("@dialogue-node:%1").arg(current);
        for(QTreeWidgetItemIterator it(tree);*it;++it) {
            if((*it)->data(0,Qt::UserRole).toString()==key) {selected=*it;break;}
        }
        if (!selected && current>=0) {
            // Keep invalid legacy targets visible instead of silently closing.
            selected=new QTreeWidgetItem(root);
            selected->setText(0,tr("MISSING dialogue #%1").arg(current));
            selected->setData(0,Qt::UserRole,QStringLiteral("@missing-dialogue:%1").arg(current));
            selected->setToolTip(0,tr("This saved destination does not exist; select a valid dialogue or Close."));
        }
        root->setExpanded(true);
        if(selected) {
            for(auto *parent=selected->parent();parent;parent=parent->parent())
                parent->setExpanded(true);
            tree->setCurrentItem(selected);
            tree->scrollToItem(selected);
        }
        auto *buttons=new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,&browser);
        layout->addWidget(buttons);
        auto *ok=buttons->button(QDialogButtonBox::Ok);
        const auto targetOf=[this](QTreeWidgetItem *item,int *destination)->bool {
            if(!item || !destination)return false;
            const QString id=item->data(0,Qt::UserRole).toString();
            if(id==QStringLiteral("@close-conversation")) {*destination=-1;return true;}
            const QString prefix=QStringLiteral("@dialogue-node:");
            if(!id.startsWith(prefix))return false;
            bool valid=false;
            const int value=id.mid(prefix.size()).toInt(&valid);
            if(!valid || value<0 || value>=m_dialogues.size())return false;
            *destination=value;
            return true;
        };
        int value=current;
        const auto select=[&](QTreeWidgetItem *item) {
            int candidate=-1;
            if(!targetOf(item,&candidate))return;
            value=candidate;
            browser.accept();
        };
        connect(tree,&QTreeWidget::currentItemChanged,&browser,
            [ok,targetOf](QTreeWidgetItem *item,QTreeWidgetItem *) {
                int value=0;
                ok->setEnabled(targetOf(item,&value));
            });
        {
            int test=0;
            ok->setEnabled(targetOf(tree->currentItem(),&test));
        }
        connect(tree,&QTreeWidget::itemDoubleClicked,&browser,
            [&](QTreeWidgetItem *item,int) {select(item);});
        connect(buttons,&QDialogButtonBox::accepted,&browser,
            [&] {select(tree->currentItem());});
        connect(buttons,&QDialogButtonBox::rejected,&browser,&QDialog::reject);
        connect(search,&QLineEdit::textChanged,&browser,[tree,selected](const QString &raw) {
            const QString query=raw.trimmed();
            std::function<bool(QTreeWidgetItem*,bool)> filter=[&](QTreeWidgetItem *item,bool parentMatch) {
                const bool match=parentMatch || item->text(0).contains(query,Qt::CaseInsensitive);
                bool visible=match;
                for(int i=0;i<item->childCount();++i)
                    visible=filter(item->child(i),match) || visible;
                item->setHidden(!visible);
                return visible;
            };
            for(int i=0;i<tree->topLevelItemCount();++i)filter(tree->topLevelItem(i),false);
            if(!query.isEmpty())tree->expandAll();
            else {
                tree->collapseAll();
                for(auto *parent=selected;parent;parent=parent->parent())
                    parent->setExpanded(true);
            }
        });
        if(browser.exec()!=QDialog::Accepted)return false;
        *chosen=value;
        return true;
    }
    int browseDialogueTree(int current) {
        QDialog browser(this);
        browser.setWindowTitle(tr("Choose Adventure Dialogue"));
        browser.resize(510,540);
        auto *layout=new QVBoxLayout(&browser);
        auto *search=new QLineEdit(&browser);
        search->setPlaceholderText(tr("Search dialogues or folders..."));
        layout->addWidget(search);
        auto *tree=new QTreeWidget(&browser);
        tree->setHeaderHidden(true);
        layout->addWidget(tree);
        auto *root=new QTreeWidgetItem(tree);
        root->setText(0,tr("Dialogue Actions"));
        root->setFlags(root->flags() & ~Qt::ItemIsSelectable);
        populateDialogueChoices(tree,root);
        tree->expandAll();
        QTreeWidgetItem *selected=nullptr;
        const QString currentId=QStringLiteral("@dialogue-node:%1").arg(current);
        for (QTreeWidgetItemIterator it(tree);*it;++it)
            if ((*it)->data(0,Qt::UserRole).toString()==currentId) {selected=*it;break;}
        if (selected) {tree->setCurrentItem(selected);tree->scrollToItem(selected);}
        connect(search,&QLineEdit::textChanged,&browser,[tree](const QString &raw) {
            const QString query=raw.trimmed();
            std::function<bool(QTreeWidgetItem*,bool)> filter=[&](QTreeWidgetItem *item,bool parentMatch) {
                const bool match=parentMatch || item->text(0).contains(query,Qt::CaseInsensitive);
                bool visible=match;
                for (int i=0;i<item->childCount();++i)
                    visible=filter(item->child(i),match) || visible;
                item->setHidden(!visible);
                return visible;
            };
            for (int i=0;i<tree->topLevelItemCount();++i)
                filter(tree->topLevelItem(i),false);
            if (!query.isEmpty())tree->expandAll();
        });
        int chosen=-1;
        connect(tree,&QTreeWidget::itemDoubleClicked,&browser,[&](QTreeWidgetItem *item,int) {
            if (!item)return;
            const QString key=item->data(0,Qt::UserRole).toString();
            if (key==QStringLiteral("@create-dialogue"))chosen=-2;
            else if (key.startsWith(QStringLiteral("@dialogue-node:"))) {
                bool ok=false;
                const int index=key.mid(QStringLiteral("@dialogue-node:").size()).toInt(&ok);
                if (!ok || index<0 || index>=m_dialogues.size())return;
                chosen=index;
            } else return;
            browser.accept();
        });
        auto *buttons=new QDialogButtonBox(QDialogButtonBox::Cancel,&browser);
        layout->addWidget(buttons);
        connect(buttons,&QDialogButtonBox::rejected,&browser,&QDialog::reject);
        return browser.exec()==QDialog::Accepted?chosen:-1;
    }
    // The context menu catalog is a read-only view of .sbgm resources. A
    // Trigger output offers only compatible object actions and Show Dialogue.
    void showInsertTree(const QPointF &at,const QPoint &global,const QString &from) {
        QDialog picker(this);
        const bool stateOutput=from.startsWith(QStringLiteral("@stateout:true:")) ||
                               from.startsWith(QStringLiteral("@stateout:false:"));
        const bool graphValue=from.startsWith(QStringLiteral("@graphvalue:"));
        const bool graphBranch=from.startsWith(QStringLiteral("@graphbranch:true:")) ||
                               from.startsWith(QStringLiteral("@graphbranch:false:"));
        const bool eventOutputPort=isEventOutput(from) &&
            m_objects.contains(eventOwner(from)) &&
            eventKinds(m_objects.value(eventOwner(from)).type).contains(eventKey(from));
        const bool enemyOutput=isEnemyDefeatOutput(from) &&
            m_objects.value(enemyDefeatOwner(from)).type==QStringLiteral("enemy");
        // Event outputs are action ports, not ordinary object-state outputs.
        // Keep their conditional logic choice both visible and easy to find.
        const bool eventLogicSource=eventOutputPort &&
            ((eventKey(from)==QStringLiteral("arrival") &&
              m_objects.value(eventOwner(from)).type==QStringLiteral("lift")) ||
             ((eventKey(from)==QStringLiteral("hit") ||
               eventKey(from)==QStringLiteral("destroy")) &&
              m_objects.value(eventOwner(from)).type==QStringLiteral("breakable")));
        const bool objectSource=graphValue || (!from.isEmpty() && !stateOutput && m_objects.contains(from) &&
            m_objects.value(from).type!=QStringLiteral("trigger") &&
            m_objects.value(from).type!=QStringLiteral("npc") &&
            m_objects.value(from).type!=QStringLiteral("player_action") &&
            m_objects.value(from).type!=QStringLiteral("collectable") &&
            m_objects.value(from).type!=QStringLiteral("player"));
        picker.setWindowTitle(from.isEmpty()?tr("Add World Node"):
            graphValue?tr("Connect RESULT to Logic or Game Object..."):
            (stateOutput || graphBranch)?tr("Connect TRUE / FALSE to..."):
            objectSource?tr("Read Game Object State..."):
            eventOutputPort?tr("Connect %1 to...").arg(eventLabel(eventKey(from))):
            enemyOutput?tr("Connect Enemy ON DEFEAT to..."):tr("Connect Trigger to..."));
        if (stateOutput) {
            const bool yes=from.startsWith(QStringLiteral("@stateout:true:"));
            const QString owner=from.mid(yes?QStringLiteral("@stateout:true:").size():
                                          QStringLiteral("@stateout:false:").size());
            if (!m_objects.contains(owner) || m_objects.value(owner).toggleStateTargetId.isEmpty()) {
                QMessageBox::information(this,tr("Boolean"),
                    tr("Connect a Game Object's state output to the Boolean first."));
                return;
            }
        }
        picker.resize(405,460);
        auto *layout=new QVBoxLayout(&picker);
        auto *search=new QLineEdit(&picker);
        search->setPlaceholderText(tr("Filter available nodes..."));
        layout->addWidget(search);
        if(eventLogicSource) {
            auto *hint=new QLabel(tr("%1: select Logic to combine this one-frame event with object states, "
                "or connect directly for an unconditional action.").arg(eventLabel(eventKey(from))),&picker);
            hint->setWordWrap(true);
            layout->addWidget(hint);
        }
        auto *tree=new QTreeWidget(&picker);
        tree->setHeaderHidden(true);
        tree->setSelectionMode(QAbstractItemView::SingleSelection);
        layout->addWidget(tree);
        // The .sbgm supplies all available targets. Organise Game Objects by
        // their real type rather than flattening them into "Game Objects / type"
        // categories, and keep Adventure NPCs in their own branch.
        const bool linking=!from.isEmpty();
        QTreeWidgetItem *gameObjectsRoot=nullptr;
        QTreeWidgetItem *npcsRoot=nullptr;
        QTreeWidgetItem *playerRoot=nullptr;
        QTreeWidgetItem *worldTransitionsRoot=nullptr;
        QTreeWidgetItem *logicRoot=nullptr;
        QHash<QString,QTreeWidgetItem*> objectTypes;
        if (!objectSource || graphValue) for (const QString &id:m_order) {
            if (linking && (id==from || (enemyOutput && id==enemyDefeatOwner(from)) ||
                (eventOutputPort && id==eventOwner(from))))continue;
            const NodeObject object=m_objects.value(id);
            // An enemy death can change an object's active state, but cannot
            // start an NPC conversation. Never offer a no-op target.
            if ((enemyOutput || eventOutputPort) && object.type==QStringLiteral("npc"))continue;
            if(object.type==QStringLiteral("player_action") ||
               object.type==QStringLiteral("missing_reference"))continue;
            if(graphValue && (object.type==QStringLiteral("trigger") ||
                object.type==QStringLiteral("npc") || object.resourceIndex<0))continue;
            QTreeWidgetItem *parent=nullptr;
            if (object.type==QStringLiteral("goto_world")) {
                // Existing Goto World resources belong to PLAYER, rather than
                // being mislabeled as ordinary state-driven Game Objects.
                // They remain their original .sbgm resources and retain the
                // existing interaction-based world transition semantics.
                if (linking)continue; // Not an enable/disable/toggle target.
                if (!playerRoot) {
                    playerRoot=new QTreeWidgetItem(tree,QStringList{tr("PLAYER")});
                    playerRoot->setFlags(playerRoot->flags() & ~Qt::ItemIsSelectable);
                    worldTransitionsRoot=new QTreeWidgetItem(playerRoot,
                        QStringList{tr("World Transitions")});
                    worldTransitionsRoot->setFlags(worldTransitionsRoot->flags() & ~Qt::ItemIsSelectable);
                }
                parent=worldTransitionsRoot;
            } else if (object.type==QStringLiteral("npc")) {
                if (!npcsRoot) {
                    npcsRoot=new QTreeWidgetItem(tree,QStringList{tr("NPCs")});
                    npcsRoot->setFlags(npcsRoot->flags() & ~Qt::ItemIsSelectable);
                }
                parent=npcsRoot;
            } else {
                if (!gameObjectsRoot) {
                    gameObjectsRoot=new QTreeWidgetItem(tree,QStringList{tr("Game Objects")});
                    gameObjectsRoot->setFlags(gameObjectsRoot->flags() & ~Qt::ItemIsSelectable);
                }
                // Ordinary and logic-controlled Decoration sprites share one
                // category, not two identically named folders.
                const QString groupType=object.type==QStringLiteral("decoration_object")
                    ? QStringLiteral("decoration") : object.type;
                parent=objectTypes.value(groupType,nullptr);
                if (!parent) {
                    QString label=groupType;
                    label.replace(QLatin1Char('_'),QLatin1Char(' '));
                    if (!label.isEmpty())label[0]=label.at(0).toUpper();
                    parent=new QTreeWidgetItem(gameObjectsRoot,QStringList{label});
                    parent->setFlags(parent->flags() & ~Qt::ItemIsSelectable);
                    objectTypes.insert(groupType,parent);
                }
            }
            auto *item=new QTreeWidgetItem(parent,QStringList{object.name});
            item->setData(0,Qt::UserRole,id);
            item->setToolTip(0,tr("%1 | %2").arg(object.type,id));
        }
        // PLAYER branches are real actions, not RESULT bindings or inputs.
        if (!graphValue && !objectSource) {
            if(!playerRoot) {
                playerRoot=new QTreeWidgetItem(tree,QStringList{tr("PLAYER")});
                playerRoot->setFlags(playerRoot->flags() & ~Qt::ItemIsSelectable);
            }
            auto section=[&](const QString &label) {
                auto *item=new QTreeWidgetItem(playerRoot,QStringList{label});
                item->setFlags(item->flags() & ~Qt::ItemIsSelectable);
                return item;
            };
            auto *light=section(tr("Spotlight"));
            auto *weather=section(tr("Weather & Effects"));
            auto *time=section(tr("Time of Day"));
            if(!worldTransitionsRoot)worldTransitionsRoot=section(tr("World Transitions"));
            for(const QString &id:m_order) {
                const NodeObject n=m_objects.value(id);
                if(n.type!=QStringLiteral("player_action"))continue;
                QTreeWidgetItem *parent=id==QStringLiteral("@player_spotlight")?light:
                    id.startsWith(QStringLiteral("@player_weather:"))?weather:
                    id.startsWith(QStringLiteral("@player_time:"))?time:worldTransitionsRoot;
                auto *item=new QTreeWidgetItem(parent,QStringList{n.name});
                item->setData(0,Qt::UserRole,id);
                item->setToolTip(0,isWeatherTarget(id)?
                    tr("Weather: Enable starts, Disable stops this mode, Toggle switches it on/off. FALSE defaults to Disable."):
                    isPlayerCommand(id)?tr("Runs this PLAYER command once when the branch fires."):
                    tr("Use Enable / Disable / Toggle for the player's spotlight."));
            }
        }
        // NPC start/after-helped selections point to the existing Adventure
        // dialogue IDs. TRUE/FALSE actions use the same runtime Show Dialogue
        // command as ordinary Dialogue Actions, never a new NPC event type.
        if(linking && !objectSource && !graphValue && !enemyOutput) {
            auto *npcConversations=new QTreeWidgetItem(tree,QStringList{tr("NPC Conversations")});
            npcConversations->setFlags(npcConversations->flags() & ~Qt::ItemIsSelectable);
            for(const QString &id:m_order) {
                const NodeObject npc=m_objects.value(id);
                if(npc.type!=QStringLiteral("npc"))continue;
                auto *parent=new QTreeWidgetItem(npcConversations,QStringList{npc.name});
                parent->setFlags(parent->flags() & ~Qt::ItemIsSelectable);
                if(npc.npcStartNode>=0 && npc.npcStartNode<m_dialogues.size()) {
                    auto *opening=new QTreeWidgetItem(parent,QStringList{
                        tr("Opening: %1").arg(npcDialogueTitle(npc.npcStartNode))});
                    opening->setData(0,Qt::UserRole,
                        QStringLiteral("@npc-dialogue:start:")+id);
                }
                if(npc.npcDoneNode>=0 && npc.npcDoneNode<m_dialogues.size()) {
                    auto *helped=new QTreeWidgetItem(parent,QStringList{
                        tr("After helped: %1").arg(npcDialogueTitle(npc.npcDoneNode))});
                    helped->setData(0,Qt::UserRole,
                        QStringLiteral("@npc-dialogue:helped:")+id);
                }
            }
        }
        // Sort only the Game Object/NPC branches before adding dialogue nodes:
        // the Dialogue Editor's "+ Create New Dialogue" must stay last.
        tree->sortItems(0,Qt::AscendingOrder);
        if (objectSource || eventLogicSource) {
            auto *logic=new QTreeWidgetItem(tree,QStringList{tr("Logic")});
            logicRoot=logic;
            logic->setFlags(logic->flags() & ~Qt::ItemIsSelectable);
            auto *boolean=new QTreeWidgetItem(logic,QStringList{eventLogicSource?tr("Boolean (event pulse)"):
                tr("Boolean (TRUE / FALSE)")});
            boolean->setData(0,Qt::UserRole,QStringLiteral("@logic:boolean"));
            boolean->setToolTip(0,eventLogicSource?tr("TRUE only when this one-frame event occurs."):
                tr("TRUE when this object is enabled. One input."));
            auto *andNode=new QTreeWidgetItem(logic,QStringList{tr("AND (all enabled)")});
            andNode->setData(0,Qt::UserRole,QStringLiteral("@logic:and"));
            andNode->setToolTip(0,eventLogicSource?tr("TRUE when this event occurs AND the other connected object states are enabled."):
                tr("TRUE only when at least two connected Game Objects are all enabled."));
            auto *orNode=new QTreeWidgetItem(logic,QStringList{tr("OR (any enabled, 2–8 inputs)")});
            orNode->setData(0,Qt::UserRole,QStringLiteral("@logic:or"));
            orNode->setToolTip(0,tr("TRUE when any of 2–8 connected Game Objects is enabled."));
            auto *notNode=new QTreeWidgetItem(logic,QStringList{tr("NOT (invert input)")});
            notNode->setData(0,Qt::UserRole,QStringLiteral("@logic:not"));
        }
        // Named Breakable events can show an Adventure dialogue. Selecting one
        // creates the existing one-frame BOOLEAN -> TRUE dialogue chain, so
        // event playback uses the same validated runtime path as graph dialogue.
        if (linking && !objectSource && !enemyOutput &&
            (!eventOutputPort || eventLogicSource)) {
            auto *root=new QTreeWidgetItem(tree,QStringList{tr("Dialogue Actions")});
            root->setFlags(root->flags() & ~Qt::ItemIsSelectable);
            populateDialogueChoices(tree,root);
        }
        // A large world may contain hundreds of objects: start with just the
        // root headings, not every object and dialogue expanded. Exception:
        // the arrival event's four existing logic choices are the purpose of
        // this picker, so put Logic FIRST and leave it expanded.
        tree->collapseAll();
        if((eventLogicSource || objectSource) && logicRoot) {
            const int previousIndex=tree->indexOfTopLevelItem(logicRoot);
            if(previousIndex>0) {
                QTreeWidgetItem *first=tree->takeTopLevelItem(previousIndex);
                tree->insertTopLevelItem(0,first);
            }
            logicRoot->setExpanded(true);
        }
        auto *buttons=new QDialogButtonBox(QDialogButtonBox::Cancel,&picker);
        layout->addWidget(buttons);
        connect(buttons,&QDialogButtonBox::rejected,&picker,&QDialog::reject);
        QString selectedId;
        auto choose=[&](QTreeWidgetItem *item) {
            if (!item)return;
            const QString id=item->data(0,Qt::UserRole).toString();
            if (id.isEmpty())return;
            selectedId=id;
            picker.accept();
        };
        connect(tree,&QTreeWidget::itemDoubleClicked,&picker,
                [&](QTreeWidgetItem *item,int) {choose(item);});
        connect(search,&QLineEdit::textChanged,&picker,[tree](const QString &raw) {
            const QString query=raw.trimmed();
            std::function<bool(QTreeWidgetItem*,bool)> filter=[&](QTreeWidgetItem *item,bool parentMatch) {
                const bool match=parentMatch || item->text(0).contains(query,Qt::CaseInsensitive);
                bool found=match;
                for (int i=0;i<item->childCount();++i)
                    found=filter(item->child(i),match) || found;
                item->setHidden(!found);
                return found;
            };
            for (int i=0;i<tree->topLevelItemCount();++i)
                filter(tree->topLevelItem(i),false);
            // Searching reveals matching nested branches; clearing the search
            // returns to the compact category view instead of leaving a huge
            // fully expanded tree behind.
            if (query.isEmpty())tree->collapseAll();
            else tree->expandAll();
        });
        // Opening by right-click keeps the popup near the insertion point.
        picker.move(global-QPoint(20,45));
        search->setFocus();
        if (picker.exec()!=QDialog::Accepted || selectedId.isEmpty())return;
        // Resolve a chosen NPC conversation to its actual dialogue node ID.
        // The emitted action is identical to choosing that dialogue directly.
        if(selectedId.startsWith(QStringLiteral("@npc-dialogue:"))) {
            const bool opening=selectedId.startsWith(QStringLiteral("@npc-dialogue:start:"));
            const QString prefix=opening?QStringLiteral("@npc-dialogue:start:"):
                QStringLiteral("@npc-dialogue:helped:");
            const NodeObject npc=m_objects.value(selectedId.mid(prefix.size()));
            const int dialogue=opening?npc.npcStartNode:npc.npcDoneNode;
            if(npc.type!=QStringLiteral("npc") || dialogue<0 || dialogue>=m_dialogues.size()) {
                QMessageBox::warning(this,tr("NPC Conversations"),
                    tr("This NPC no longer references a valid Adventure dialogue."));
                return;
            }
            selectedId=QStringLiteral("@dialogue-node:%1").arg(dialogue);
        }
        if (selectedId.startsWith(QStringLiteral("@logic:"))) {
            if (!objectSource && !eventLogicSource)return;
            createGraphLogic(from,at,selectedId.mid(QStringLiteral("@logic:").size()));
            return;
        }
        if (selectedId==QStringLiteral("@create-dialogue")) {
            if(eventLogicSource) {
                if(m_dialogues.size()>=256) {
                    QMessageBox::warning(this,tr("Visual Nodes"),tr("Adventure dialogues are limited to 256 nodes."));
                    return;
                }
                const QString owner=eventOwner(from);
                const int before=m_objects.value(owner).logicNodes.size();
                createGraphLogic(from,at,QStringLiteral("boolean"));
                const QJsonArray nodes=m_objects.value(owner).logicNodes;
                if(nodes.size()!=before+1)return;
                const QString key=graphKey(owner,nodes.last().toObject().value(QStringLiteral("id")).toString());
                setGraphDialogue(key,true,-2,at+QPointF(350,0));
                m_status->setText(tr("%1: event pulse → BOOLEAN TRUE → new Adventure dialogue. Save Graph + World to apply.")
                    .arg(eventLabel(eventKey(from))));
                return;
            }
            if(graphBranch) {
                const bool yes=from.startsWith(QStringLiteral("@graphbranch:true:"));
                const QString key=from.mid((yes?QStringLiteral("@graphbranch:true:"):
                    QStringLiteral("@graphbranch:false:")).size());
                setGraphDialogue(key,yes,-2,at);
                return;
            }
            if (stateOutput) {
                if (m_dialogues.size()>=256) {
                    QMessageBox::warning(this,tr("Visual Nodes"),tr("Adventure dialogue limit reached."));return;
                }
                m_dialogues.append(QJsonObject{{QStringLiteral("speaker"),QStringLiteral("NPC")},
                    {QStringLiteral("text"),QStringLiteral("Hello!")},{QStringLiteral("choices"),QJsonArray()}});
                m_dialoguesChanged=true;
                const bool yes=from.startsWith(QStringLiteral("@stateout:true:"));
                const QString prefix=yes?QStringLiteral("@stateout:true:"):QStringLiteral("@stateout:false:");
                setBranchDialogue(from.mid(prefix.size()),yes,m_dialogues.size()-1,at);
            } else connectNewDialogue(from,at);
            return;
        }
        if (selectedId.startsWith(QStringLiteral("@dialogue-node:"))) {
            bool ok=false;
            const int index=selectedId.mid(QStringLiteral("@dialogue-node:").size()).toInt(&ok);
            if (ok && index>=0 && index<m_dialogues.size()) {
                if(eventLogicSource) {
                    const QString owner=eventOwner(from);
                    const int before=m_objects.value(owner).logicNodes.size();
                    createGraphLogic(from,at,QStringLiteral("boolean"));
                    const QJsonArray nodes=m_objects.value(owner).logicNodes;
                    if(nodes.size()!=before+1)return;
                    const QString key=graphKey(owner,nodes.last().toObject().value(QStringLiteral("id")).toString());
                    setGraphDialogue(key,true,index,at+QPointF(350,0));
                    m_status->setText(tr("%1: event pulse → BOOLEAN TRUE → Dialogue #%2. Save Graph + World to apply.")
                        .arg(eventLabel(eventKey(from))).arg(index));
                    return;
                }
                if(graphBranch) {
                    const bool yes=from.startsWith(QStringLiteral("@graphbranch:true:"));
                    const QString key=from.mid((yes?QStringLiteral("@graphbranch:true:"):
                        QStringLiteral("@graphbranch:false:")).size());
                    setGraphDialogue(key,yes,index,at);
                    return;
                }
                if (stateOutput) {
                    const bool yes=from.startsWith(QStringLiteral("@stateout:true:"));
                    const QString prefix=yes?QStringLiteral("@stateout:true:"):QStringLiteral("@stateout:false:");
                    setBranchDialogue(from.mid(prefix.size()),yes,index,at);
                } else connectExistingDialogue(from,at,index);
            }
            return;
        }
        if (linking && !stateOutput && !graphBranch && !graphValue &&
            (m_objects.contains(from) || enemyOutput) &&
            (eventOutputPort ? m_objects.value(eventOwner(from)).eventLinks.value(eventKey(from)).size() :
              m_objects.value(enemyOutput?enemyDefeatOwner(from):from).links.size())>=64) {
            QMessageBox::warning(this,tr("Visual Nodes"),tr("At most 64 actions per event output."));
            return;
        }
        if (m_objects.contains(selectedId) &&
            m_objects.value(selectedId).type==QStringLiteral("npc"))
            m_hiddenNpcCards.remove(selectedId);
        if (m_cards.contains(selectedId)) {
            // The same .sbgm object must have one card, never duplicates.
            m_view->centerOn(m_cards.value(selectedId));
        } else {
            makeObjectCard(selectedId,at);
        }
        m_placedCards.insert(selectedId);
        m_dirty=true;
        if (linking) {
            if(graphValue) {
                addGraphResultTarget(from.mid(QStringLiteral("@graphvalue:").size()),selectedId);
                return;
            }
            if(graphBranch) {
                const bool yes=from.startsWith(QStringLiteral("@graphbranch:true:"));
                const QString key=from.mid((yes?QStringLiteral("@graphbranch:true:"):
                    QStringLiteral("@graphbranch:false:")).size());
                addGraphAction(key,yes,selectedId,
                               defaultPlayerAction(selectedId,yes?QStringLiteral("enable"):QStringLiteral("disable")));
                return;
            }
            // Every TRUE/FALSE branch can perform the same real enable,
            // disable and toggle actions as the ordinary Trigger socket.
            if (stateOutput) {
                const bool yes=from.startsWith(QStringLiteral("@stateout:true:"));
                const QString prefix=yes?QStringLiteral("@stateout:true:"):QStringLiteral("@stateout:false:");
                appendBranchConnection(from.mid(prefix.size()),yes,selectedId,
                    defaultPlayerAction(selectedId,yes?QStringLiteral("enable"):QStringLiteral("disable")));
            } else if(eventOutputPort)
                appendEventConnection(eventOwner(from),eventKey(from),selectedId,
                    defaultPlayerAction(selectedId,QStringLiteral("enable")));
            else appendConnection(enemyOutput?enemyDefeatOwner(from):from,
                                    selectedId,defaultPlayerAction(selectedId,QStringLiteral("enable")));
        } else {
            showDetails(selectedId);
        }
    }
    void appendEventConnection(const QString &owner,const QString &event,
                               const QString &target,const QString &operation) {
        if(!m_objects.contains(owner) || !m_objects.contains(target) || owner==target ||
           !eventKinds(m_objects.value(owner).type).contains(event) || !supportedAction(operation))return;
        NodeObject node=m_objects.value(owner);
        QVector<NodeLink> &links=node.eventLinks[event];
        if(links.size()>=64) {
            QMessageBox::warning(this,tr("Visual Nodes"),tr("At most 64 actions per event."));return;
        }
        links.append({target,operation});
        m_objects.insert(owner,node);m_touched.insert(owner);m_dirty=true;
        redrawLinks();showDetails(owner);
    }
    void appendConnection(const QString &from,const QString &to,const QString &action) {
        if (!supportedAction(action) || !m_objects.contains(from) || !m_objects.contains(to) ||
            from==to || !isActionSource(m_objects.value(from)) ||
            m_objects.value(from).type==QStringLiteral("collectable"))return;
        NodeObject node=m_objects.value(from);
        if (node.links.size()>=64) {
            QMessageBox::warning(this,tr("Visual Nodes"),tr("At most 64 linked actions per Trigger or Stompable Enemy."));return;
        }
        node.links.append({to,action});
        m_objects.insert(from,node);m_touched.insert(from);m_dirty=true;
        redrawLinks();showDetails(from);
    }
    void appendBranchConnection(const QString &owner,bool yes,const QString &target,const QString &action) {
        if (!m_objects.contains(owner) || !m_objects.contains(target) ||
            m_objects.value(owner).type!=QStringLiteral("trigger") || !supportedAction(action))return;
        NodeObject node=m_objects.value(owner);
        if (node.toggleStateTargetId.isEmpty()) {
            QMessageBox::information(this,tr("Boolean"),
                tr("Choose the Game Object state to read before connecting TRUE/FALSE actions."));return;
        }
        QVector<NodeLink> &links=yes?node.toggleTrueActions:node.toggleFalseActions;
        if (links.size()>=64) {
            QMessageBox::warning(this,tr("Visual Nodes"),tr("Each TRUE/FALSE branch supports up to 64 actions."));return;
        }
        links.append({target,action});
        m_objects.insert(owner,node);m_touched.insert(owner);m_dirty=true;
        redrawLinks();showDetails(toggleCardId(owner));
    }
    void removeBranchConnection(const QString &owner,bool yes,int index) {
        if (!m_objects.contains(owner))return;
        NodeObject node=m_objects.value(owner);
        QVector<NodeLink> &links=yes?node.toggleTrueActions:node.toggleFalseActions;
        if (index<0 || index>=links.size())return;
        links.removeAt(index);
        m_objects.insert(owner,node);m_touched.insert(owner);m_dirty=true;
        hideDisconnectedCards();redrawLinks();showDetails(toggleCardId(owner));
    }
    void connectExistingDialogue(const QString &from,const QPointF &at,int index) {
        if (!m_objects.contains(from) || m_objects.value(from).type!=QStringLiteral("trigger") ||
            index<0 || index>=m_dialogues.size())return;
        NodeObject node=m_objects.value(from);
        if (m_npcDialogueRoutes.value(from).value(QStringLiteral("dialogue")).toInt(-1)!=index)
            m_npcDialogueRoutes.remove(from);
        if (node.dialogueNode!=index) {
            node.dialogueNode=index;
            if (node.dialogueMode.isEmpty())node.dialogueMode=QStringLiteral("single");
            m_objects.insert(from,node);
            m_touched.insert(from);
        }
        const QString key=dialogueCardId(from);
        m_positions.insert(key,at);
        m_placedCards.insert(key);
        if (!m_cards.contains(from))makeObjectCard(from,m_positions.contains(from)?
            m_positions.value(from):viewportInsertionPoint(QSizeF(285,215)));
        if (!npcRoutePoint(from,index)) {
            if (!m_cards.contains(key))createDialogueCard(from);
            else m_cards.value(key)->setPos(at);
        }
        m_dirty=true;
        refreshDialogueCard(from);
        redrawLinks();showDetails(key);
    }
    void connectNewDialogue(const QString &from,const QPointF &at) {
        if (!m_objects.contains(from) || m_objects.value(from).type!=QStringLiteral("trigger"))return;
        // Only one Show Dialogue setting is supported per Trigger by .sbgm.
        // Reconnecting must never silently replace an existing dialogue.
        if (m_objects.value(from).dialogueNode>=0) {
            const QString key=dialogueCardId(from);
            m_positions.insert(key,at);
            m_placedCards.insert(key);
            if (!m_dialogueCards.contains(from))createDialogueCard(from);
            m_dirty=true;redrawLinks();showDetails(key);
            return;
        }
        if (m_dialogues.size()>=256) {
            QMessageBox::warning(this,tr("Visual Nodes"),tr("Adventure dialogues are limited to 256 nodes."));return;
        }
        // Create an independent placeholder, rather than silently selecting
        // another character's existing dialogue from the world.
        QJsonArray choices;
        for (int i=0;i<3;++i)
            choices.append(QJsonObject{{QStringLiteral("text"),QString()},
                {QStringLiteral("reply"),QString()},
                {QStringLiteral("next"),-1},{QStringLiteral("missingNext"),-1},
                {QStringLiteral("requires"),-1},{QStringLiteral("give"),-1},
                {QStringLiteral("take"),-1},{QStringLiteral("action"),-1}});
        m_dialogues.append(QJsonObject{{QStringLiteral("speaker"),QStringLiteral("NPC")},
            {QStringLiteral("text"),QStringLiteral("Hello!")},
            {QStringLiteral("choices"),choices}});
        NodeObject node=m_objects.value(from);
        node.dialogueNode=m_dialogues.size()-1;
        node.dialogueMode=QStringLiteral("single");
        m_objects.insert(from,node);
        m_dialoguesChanged=true;m_touched.insert(from);m_dirty=true;
        const QString key=dialogueCardId(from);
        m_positions.insert(key,at);
        m_placedCards.insert(key);
        if (!m_cards.contains(from))makeObjectCard(from,m_positions.contains(from)?
            m_positions.value(from):viewportInsertionPoint(QSizeF(285,215)));
        if (!m_dialogueCards.contains(from))createDialogueCard(from);
        refreshDialogueCard(from);redrawLinks();showDetails(key);
    }
    // Independent graph cards. Unlike legacy @toggle:<trigger>, every one has
    // a stable node ID and separate inputs, operator, and TRUE/FALSE actions.
    QString graphKey(const QString &owner,const QString &node) const {
        return QStringLiteral("@graph:")+owner+QLatin1Char(':')+node;
    }
    QString graphDialogueKey(const QString &key,bool yes) const {
        return (yes?QStringLiteral("@graph-dialogue:true:"):
                    QStringLiteral("@graph-dialogue:false:"))+key;
    }
    bool dialogueCardHasLiveAction(const QString &cardId) const {
        if(cardId.startsWith(QStringLiteral("@conversation:")))return true;
        if(cardId.startsWith(QStringLiteral("@graph-dialogue:"))) {
            const bool yes=cardId.startsWith(QStringLiteral("@graph-dialogue:true:"));
            const QString prefix=yes?QStringLiteral("@graph-dialogue:true:"):
                QStringLiteral("@graph-dialogue:false:");
            QJsonObject node;
            if(lookupGraph(cardId.mid(prefix.size()),nullptr,nullptr,&node))
                return node.value(yes?QStringLiteral("trueDialogueNode"):
                    QStringLiteral("falseDialogueNode")).toInt(-1)>=0;
        } else if(cardId.startsWith(QStringLiteral("@toggle-dialogue:"))) {
            const bool yes=cardId.startsWith(QStringLiteral("@toggle-dialogue:true:"));
            const QString prefix=yes?QStringLiteral("@toggle-dialogue:true:"):
                QStringLiteral("@toggle-dialogue:false:");
            const NodeObject owner=m_objects.value(cardId.mid(prefix.size()));
            return (yes?owner.toggleTrueDialogueNode:owner.toggleFalseDialogueNode)>=0;
        } else if(cardId.startsWith(QStringLiteral("@dialogue:"))) {
            return m_objects.value(cardId.mid(QStringLiteral("@dialogue:").size())).dialogueNode>=0;
        }
        return false;
    }
    bool validSharedGraphDialogue(const QString &own,int dialogue) const {
        const QString to=m_graphDialogueRoutes.value(own);
        if(to.isEmpty() || to==own || !m_cards.contains(to))return false;
        return selectedDialogueOnCard(to)==dialogue;
    }
    QString graphDialogueVisualTarget(const QString &key,bool yes,int dialogue) const {
        const QString own=graphDialogueKey(key,yes);
        return validSharedGraphDialogue(own,dialogue)?m_graphDialogueRoutes.value(own):own;
    }
    bool lookupGraph(const QString &key,QString *owner,int *index,QJsonObject *found=nullptr) const {
        if(!key.startsWith(QStringLiteral("@graph:")))return false;
        const QString text=key.mid(7);
        const int colon=text.lastIndexOf(QLatin1Char(':'));
        if(colon<1)return false;
        const QString who=text.left(colon),name=text.mid(colon+1);
        if(!m_objects.contains(who) || m_objects.value(who).resourceIndex<0 ||
           m_objects.value(who).type==QStringLiteral("npc") ||
           m_objects.value(who).type==QStringLiteral("player_action") ||
           m_objects.value(who).type==QStringLiteral("collectable"))return false;
        const QJsonArray nodes=m_objects.value(who).logicNodes;
        for(int i=0;i<nodes.size();++i)
            if(nodes[i].toObject().value(QStringLiteral("id")).toString()==name) {
                if(owner)*owner=who;
                if(index)*index=i;
                if(found)*found=nodes[i].toObject();
                return true;
            }
        return false;
    }
    bool graphUpdate(const QString &key,const QJsonObject &node) {
        QString owner;int index=-1;
        if(!lookupGraph(key,&owner,&index))return false;
        NodeObject n=m_objects.value(owner);
        n.logicNodes.replace(index,node);
        m_objects.insert(owner,n);
        m_touched.insert(owner);m_dirty=true;
        return true;
    }
    QString graphOwnerForObject(const QString &source) {
        // The source's active STATE is a legitimate independent graph input.
        // It does not need an unrelated Trigger or a defeated enemy to own it.
        // The runtime evaluates when a real action/event changes that state.
        const NodeObject n=m_objects.value(source);
        if(n.resourceIndex<0 || n.type==QStringLiteral("collectable") ||
           n.type==QStringLiteral("npc") || n.type==QStringLiteral("player_action") ||
           n.type==QStringLiteral("trigger") || n.type==QStringLiteral("player"))
            return QString();
        return source;
    }
    void createGraphLogic(const QString &source,const QPointF &at,const QString &operation) {
        QString owner;
        QJsonObject input;
        if(isEventOutput(source) && m_objects.contains(eventOwner(source)) &&
           ((eventKey(source)==QStringLiteral("arrival") &&
             m_objects.value(eventOwner(source)).type==QStringLiteral("lift")) ||
            ((eventKey(source)==QStringLiteral("hit") || eventKey(source)==QStringLiteral("destroy")) &&
             m_objects.value(eventOwner(source)).type==QStringLiteral("breakable")))) {
            owner=eventOwner(source);
            input={{QStringLiteral("kind"),QStringLiteral("event")},
                   {QStringLiteral("id"),source}};
        } else if(source.startsWith(QStringLiteral("@graphvalue:"))) {
            const QString upstream=source.mid(QStringLiteral("@graphvalue:").size());
            QJsonObject upstreamNode;
            if(!lookupGraph(upstream,&owner,nullptr,&upstreamNode))return;
            input={{QStringLiteral("kind"),QStringLiteral("node")},
                   {QStringLiteral("id"),upstreamNode.value(QStringLiteral("id"))}};
        } else if(m_objects.contains(source) && m_objects.value(source).resourceIndex>=0 &&
                  m_objects.value(source).type!=QStringLiteral("trigger") &&
                  m_objects.value(source).type!=QStringLiteral("npc")) {
            owner=graphOwnerForObject(source);
            input={{QStringLiteral("kind"),QStringLiteral("object")},{QStringLiteral("id"),source}};
        } else return;
        if(owner.isEmpty() || !m_objects.contains(owner))return;
        NodeObject n=m_objects.value(owner);
        if(n.logicNodes.size()>=64) {
            QMessageBox::information(this,tr("Logic Nodes"),tr("Maximum 64 logic nodes per Game Object."));return;
        }
        QSet<QString> existing;
        for(const QJsonValue &v:n.logicNodes)existing.insert(v.toObject().value(QStringLiteral("id")).toString());
        int serial=1;while(existing.contains(QStringLiteral("logic%1").arg(serial)))++serial;
        const QString name=QStringLiteral("logic%1").arg(serial);
        const QString op=QStringList{QStringLiteral("boolean"),QStringLiteral("and"),
                           QStringLiteral("or"),QStringLiteral("not")}.contains(operation)
            ?operation:QStringLiteral("boolean");
        QJsonObject node{{QStringLiteral("id"),name},{QStringLiteral("op"),op},
            {QStringLiteral("inputs"),QJsonArray{input}},
            {QStringLiteral("trueDialogueNode"),-1},{QStringLiteral("falseDialogueNode"),-1},
            {QStringLiteral("trueActions"),QJsonArray()},{QStringLiteral("falseActions"),QJsonArray()}};
        n.logicNodes.append(node);
        m_objects.insert(owner,n);m_touched.insert(owner);m_dirty=true;
        const QString key=graphKey(owner,name);
        m_positions.insert(key,at);
        m_placedCards.insert(key);
        makeGraphCard(owner,name);
        redrawLinks();showDetails(key);
        if(op==QStringLiteral("and") || op==QStringLiteral("or"))
            m_status->setText(tr("Connect at least one more input to %1 before saving.").arg(op.toUpper()));
    }
    void addGraphInput(const QString &source,const QString &key) {
        QString owner;int index;QJsonObject node;
        if(!lookupGraph(key,&owner,&index,&node))return;
        QJsonObject input;
        if(isEventOutput(source) && eventOwner(source)==owner &&
           ((eventKey(source)==QStringLiteral("arrival") &&
             m_objects.value(owner).type==QStringLiteral("lift")) ||
            ((eventKey(source)==QStringLiteral("hit") || eventKey(source)==QStringLiteral("destroy")) &&
             m_objects.value(owner).type==QStringLiteral("breakable")))) {
            input={{QStringLiteral("kind"),QStringLiteral("event")},
                   {QStringLiteral("id"),source}};
        } else if(source.startsWith(QStringLiteral("@graphvalue:"))) {
            const QString upstream=source.mid(QStringLiteral("@graphvalue:").size());
            QString otherOwner;QJsonObject other;
            if(!lookupGraph(upstream,&otherOwner,nullptr,&other) || otherOwner!=owner || upstream==key)return;
            input={{QStringLiteral("kind"),QStringLiteral("node")},
                   {QStringLiteral("id"),other.value(QStringLiteral("id"))}};
        } else if(m_objects.contains(source) && m_objects.value(source).resourceIndex>=0 &&
                  m_objects.value(source).type!=QStringLiteral("trigger") &&
                  m_objects.value(source).type!=QStringLiteral("npc"))
            input={{QStringLiteral("kind"),QStringLiteral("object")},{QStringLiteral("id"),source}};
        else return;
        QJsonArray inputs=node.value(QStringLiteral("inputs")).toArray();
        for(const QJsonValue &v:inputs)
            if(v.toObject().value(QStringLiteral("id"))==input.value(QStringLiteral("id")) &&
               v.toObject().value(QStringLiteral("kind"))==input.value(QStringLiteral("kind")))return;
        const QString op=node.value(QStringLiteral("op")).toString();
        if((op==QStringLiteral("boolean") || op==QStringLiteral("not")) && inputs.size()>=1) {
            if(QMessageBox::question(this,tr("Replace Logic Input"),
                tr("Replace the existing input on this %1 node?").arg(op.toUpper()),
                QMessageBox::Yes|QMessageBox::No,QMessageBox::No)!=QMessageBox::Yes)return;
            inputs=QJsonArray();
        }
        if((op==QStringLiteral("or") && inputs.size()>=8) || inputs.size()>=16) {
            QMessageBox::information(this,tr("Logic Inputs"),
                op==QStringLiteral("or")?tr("OR accepts at most eight inputs."):tr("Maximum sixteen inputs."));return;
        }
        inputs.append(input);node.insert(QStringLiteral("inputs"),inputs);
        QVector<SidboxVisualLogic::Node> parsed;
        // A partly wired AND/OR is allowed while editing, but never a cycle.
        // Check the dependency graph independently so cycles are rejected even
        // before the final input count is satisfied.
        NodeObject pending=m_objects.value(owner);
        pending.logicNodes.replace(index,node);
        QHash<QString,QStringList> deps;
        for(const QJsonValue &v:pending.logicNodes) {
            const QJsonObject record=v.toObject();
            QStringList edges;
            for(const QJsonValue &i:record.value(QStringLiteral("inputs")).toArray())
                if(i.toObject().value(QStringLiteral("kind")).toString()==QStringLiteral("node"))
                    edges.append(i.toObject().value(QStringLiteral("id")).toString());
            deps.insert(record.value(QStringLiteral("id")).toString(),edges);
        }
        QSet<QString> seen,visiting;
        std::function<bool(const QString &)> visit=[&](const QString &id) -> bool {
            if(visiting.contains(id))return false;
            if(seen.contains(id))return true;
            visiting.insert(id);
            for(const QString &dep:deps.value(id))if(!deps.contains(dep) || !visit(dep))return false;
            visiting.remove(id);seen.insert(id);return true;
        };
        for(const QString &id:deps.keys())if(!visit(id)) {
            QMessageBox::warning(this,tr("Logic Cycle"),tr("This wire would create a circular logic dependency."));return;
        }
        graphUpdate(key,node);redrawLinks();showDetails(key);
    }
    void setGraphDialogue(const QString &key,bool yes,int selected,const QPointF &at=QPointF()) {
        QJsonObject node;
        if(!lookupGraph(key,nullptr,nullptr,&node))return;
        if(selected==-2) {
            if(m_dialogues.size()>=256)return;
            m_dialogues.append(QJsonObject{{QStringLiteral("speaker"),QStringLiteral("NPC")},
                {QStringLiteral("text"),QStringLiteral("Hello!")},{QStringLiteral("choices"),QJsonArray()}});
            selected=m_dialogues.size()-1;m_dialoguesChanged=true;
        }
        if(selected>=m_dialogues.size() || selected < -1)return;
        const QString source=QStringLiteral("@graphbranch:")+
            (yes?QStringLiteral("true:"):QStringLiteral("false:"))+key;
        if (selected<0 || m_npcDialogueRoutes.value(source).value(QStringLiteral("dialogue")).toInt(-1)!=selected)
            m_npcDialogueRoutes.remove(source);
        const QString display=graphDialogueKey(key,yes);
        if(selected<0 || !validSharedGraphDialogue(display,selected))
            m_graphDialogueRoutes.remove(display);
        node.insert(yes?QStringLiteral("trueDialogueNode"):QStringLiteral("falseDialogueNode"),selected);
        graphUpdate(key,node);
        if(selected>=0) {
            if(!at.isNull() && !m_cards.contains(display))m_positions.insert(display,at);
            if (!npcRoutePoint(source,selected) &&
                !validSharedGraphDialogue(display,selected)) {
                makeGraphDialogueCard(key,yes);
                refreshGraphDialogueCard(key,yes);
            }
        }
        redrawLinks();showDetails(key);
    }
    void addGraphResultTarget(const QString &key,const QString &target) {
        QJsonObject node;
        if(!lookupGraph(key,nullptr,nullptr,&node) || !m_objects.contains(target) ||
           m_objects.value(target).type==QStringLiteral("trigger") ||
           m_objects.value(target).type==QStringLiteral("npc") ||
           m_objects.value(target).resourceIndex<0)return;
        QJsonArray bindings=node.value(QStringLiteral("resultTargets")).toArray();
        for(const QJsonValue &v:bindings)if(v.toString()==target)return;
        if(bindings.size()>=64)return;
        bindings.append(target);
        node.insert(QStringLiteral("resultTargets"),bindings);
        // A direct assignment replaces separate branch actions to the same
        // target. Otherwise old TRUE and FALSE Enable wires would override it.
        for(const QString &field:{QStringLiteral("trueActions"),QStringLiteral("falseActions")}) {
            QJsonArray retained;
            for(const QJsonValue &v:node.value(field).toArray())
                if(v.toObject().value(QStringLiteral("objectId")).toString()!=target)
                    retained.append(v);
            node.insert(field,retained);
        }
        graphUpdate(key,node);
        if(!m_cards.contains(target))makeObjectCard(target,m_positions.contains(target)?
            m_positions.value(target):viewportInsertionPoint(QSizeF(240,125)));
        m_placedCards.insert(target);
        redrawLinks();showDetails(key);
        m_status->setText(tr("RESULT now directly controls %1's enabled state (TRUE = on, FALSE = off). Save Graph + World to apply.")
            .arg(m_objects.value(target).name));
    }
    void addGraphAction(const QString &key,bool yes,const QString &target,const QString &action) {
        QJsonObject node;
        if(!lookupGraph(key,nullptr,nullptr,&node) || !m_objects.contains(target) || !supportedAction(action))return;
        if(isPlayerCommand(target) && action!=QStringLiteral("enable"))return;
        const QString field=yes?QStringLiteral("trueActions"):QStringLiteral("falseActions");
        QJsonArray links=node.value(field).toArray();
        if(links.size()>=64)return;
        // Conventional branch action supersedes a direct RESULT assignment for
        // that target. Never silently maintain conflicting connections.
        QJsonArray bindings;
        for(const QJsonValue &v:node.value(QStringLiteral("resultTargets")).toArray())
            if(v.toString()!=target)bindings.append(v);
        node.insert(QStringLiteral("resultTargets"),bindings);
        links.append(QJsonObject{{QStringLiteral("objectId"),target},{QStringLiteral("action"),action}});
        node.insert(field,links);graphUpdate(key,node);
        if(!m_cards.contains(target))makeObjectCard(target,m_positions.contains(target)?
            m_positions.value(target):viewportInsertionPoint(QSizeF(240,125)));
        redrawLinks();showDetails(key);
    }
    void syncGraphCardSockets(const QString &key) {
        NodeCard *card=m_cards.value(key,nullptr);
        QJsonObject node;
        if(!card || !lookupGraph(key,nullptr,nullptr,&node))return;
        const QString op=node.value(QStringLiteral("op")).toString();
        const QJsonArray inputs=node.value(QStringLiteral("inputs")).toArray();
        // AND supports 2..16, OR supports 2..8, BOOLEAN/NOT exactly one.
        // Show a spare socket until each gate reaches its maximum input count.
        const int inputSocketCount=op==QStringLiteral("and")?
            qMin(16,qMax(2,static_cast<int>(inputs.size())+1)):
            op==QStringLiteral("or")?qMin(8,qMax(2,static_cast<int>(inputs.size())+1)):1;
        const int resultY=86+24*(inputSocketCount-1);
        const int trueY=resultY+31,falseY=resultY+60;
        const bool folded=card->collapsed();
        if(folded)card->setCollapsed(false);
        QVector<QGraphicsItem*> stale;
        for(QGraphicsItem *child:card->childItems()) {
            const QString role=child->data(4).toString();
            if((role==QStringLiteral("graph-input") ||
                role==QStringLiteral("graph-input-label")) && child->data(2).toInt()>=inputSocketCount)
                stale.append(child);
        }
        for(QGraphicsItem *child:stale)delete child;
        for(int i=0;i<inputSocketCount;++i) {
            QGraphicsRectItem *socket=nullptr;
            QGraphicsSimpleTextItem *label=nullptr;
            for(QGraphicsItem *child:card->childItems()) {
                if(child->data(2).toInt()!=i)continue;
                if(child->data(4).toString()==QStringLiteral("graph-input"))
                    socket=dynamic_cast<QGraphicsRectItem*>(child);
                else if(child->data(4).toString()==QStringLiteral("graph-input-label"))
                    label=dynamic_cast<QGraphicsSimpleTextItem*>(child);
            }
            const bool connected=i<inputs.size();
            const QJsonObject entry=connected?inputs.at(i).toObject():QJsonObject();
            const QString kind=entry.value(QStringLiteral("kind")).toString();
            const QString id=entry.value(QStringLiteral("id")).toString();
            const QString name=kind==QStringLiteral("node")?id:
                kind==QStringLiteral("event")?eventLabel(eventKey(id)):
                m_objects.contains(id)?m_objects.value(id).name:id;
            if(!socket) {
                socket=new QGraphicsRectItem(card);
                socket->setData(0,QStringLiteral("input"));socket->setData(1,key);
                socket->setData(2,i);socket->setData(4,QStringLiteral("graph-input"));
                socket->setPen(QPen(QColor(160,237,232),1.5));
                socket->setBrush(QColor(75,173,177));socket->setZValue(4);
            }
            socket->setPos(QPointF());
            socket->setRect(QRectF(-7,45+24*i,14,14));
            socket->setToolTip(connected?tr("INPUT %1: %2. Right-click its wire to disconnect.")
                .arg(i+1).arg(name):tr("INPUT %1: drag a Game Object STATE or logic RESULT here.").arg(i+1));
            if(!label) {
                label=new QGraphicsSimpleTextItem(card);
                label->setData(2,i);label->setData(4,QStringLiteral("graph-input-label"));
            }
            label->setText(connected?tr("INPUT %1: %2").arg(i+1).arg(name).left(31):
                tr("INPUT %1: (connect)").arg(i+1));
            label->setBrush(connected?m_theme.text:m_theme.mutedText);
            label->setPos(10,43+24*i);
        }
        for(QGraphicsItem *child:card->childItems()) {
            const QString role=child->data(4).toString();
            if(role==QStringLiteral("graph-result-label"))child->setPos(9,resultY-13);
            else if(role==QStringLiteral("graph-true-label"))child->setPos(9,trueY-13);
            else if(role==QStringLiteral("graph-false-label"))child->setPos(9,falseY-13);
            else if(role==QStringLiteral("graph-result-port") ||
                    role==QStringLiteral("graph-true-port") ||
                    role==QStringLiteral("graph-false-port")) {
                auto *port=dynamic_cast<QGraphicsEllipseItem*>(child);
                if(port) {
                    const int y=role==QStringLiteral("graph-result-port")?resultY:
                        role==QStringLiteral("graph-true-port")?trueY:falseY;
                    port->setPos(QPointF());port->setRect(QRectF(265,y-9,18,18));
                }
            } else if(role==QStringLiteral("graph-operator"))child->setPos(9,falseY+17);
        }
        card->setFullHeight(falseY+59);
        if(folded)card->setCollapsed(true);
    }
    void makeGraphCard(const QString &owner,const QString &id) {
        const QString key=graphKey(owner,id);
        if(m_cards.contains(key))return;
        QJsonObject data;
        if(!lookupGraph(key,nullptr,nullptr,&data))return;
        auto *card=new NodeCard(QRectF(0,0,274,195));
        card->setData(0,QStringLiteral("card"));card->setData(1,key);
        card->setPen(QPen(QColor(98,206,202),1.5));card->setBrush(m_theme.panelBackground);
        m_scene->addItem(card);
        const QPointF position=m_positions.contains(key)?m_positions.value(key):
            viewportInsertionPoint(QSizeF(290,210));
        card->setPos(position);card->enableGridSnap();m_positions.insert(key,position);
        auto *stripe=new QGraphicsRectItem(QRectF(0,0,274,26),card);
        stripe->setPen(Qt::NoPen);stripe->setBrush(QColor(35,102,110));
        auto *title=new QGraphicsSimpleTextItem(data.value(QStringLiteral("op")).toString().toUpper()+
                                             QStringLiteral(" | ")+id,card);
        title->setBrush(Qt::white);title->setPos(9,3);
        // Numbered inputs are created and resized by syncGraphCardSockets().
        // They are graphical ports only; authored input order in .sbgm is unchanged.
        auto *valueLabel=new QGraphicsSimpleTextItem(tr("RESULT"),card);
        valueLabel->setData(4,QStringLiteral("graph-result-label"));
        valueLabel->setBrush(QColor(150,218,221));valueLabel->setPos(9,65);
        auto *valuePort=new QGraphicsEllipseItem(QRectF(265,69,18,18),card);
        valuePort->setData(0,QStringLiteral("output"));valuePort->setData(1,QStringLiteral("@graphvalue:")+key);
        valuePort->setData(4,QStringLiteral("graph-result-port"));
        valuePort->setBrush(QColor(76,169,176));valuePort->setPen(QPen(Qt::white,1));
        valuePort->setToolTip(tr("RESULT: connect to another Logic node or a Game Object (TRUE = enabled, FALSE = disabled)."));
        for(const bool yes:{true,false}) {
            const int y=yes?109:138;
            auto *label=new QGraphicsSimpleTextItem(yes?tr("TRUE / YES"):tr("FALSE / NO"),card);
            label->setData(4,yes?QStringLiteral("graph-true-label"):QStringLiteral("graph-false-label"));
            label->setBrush(yes?QColor(111,222,167):QColor(244,145,146));label->setPos(9,y-8);
            auto *port=new QGraphicsEllipseItem(QRectF(265,y-6,18,18),card);
            port->setData(0,QStringLiteral("output"));
            port->setData(4,yes?QStringLiteral("graph-true-port"):QStringLiteral("graph-false-port"));
            port->setData(1,(yes?QStringLiteral("@graphbranch:true:"):
                                  QStringLiteral("@graphbranch:false:"))+key);
            port->setPen(QPen(Qt::white,1));port->setBrush(yes?QColor(76,171,118):QColor(193,86,86));
            port->setToolTip(yes?tr("TRUE action: defaults to Enable"):tr("FALSE action: defaults to Disable"));
        }
        auto *operatorPanel=new QWidget;
        operatorPanel->setFixedSize(254,33);
        operatorPanel->setStyleSheet(m_controlsStyle);
        auto *operatorRow=new QHBoxLayout(operatorPanel);
        operatorRow->setContentsMargins(3,1,3,1);
        operatorRow->addWidget(new QLabel(tr("Logic:"),operatorPanel));
        auto *operation=new QComboBox(operatorPanel);
        for(const QString &op:{QStringLiteral("boolean"),QStringLiteral("not"),
                               QStringLiteral("and"),QStringLiteral("or")})
            operation->addItem(op.toUpper(),op);
        operation->setCurrentIndex(qMax(0,operation->findData(data.value(QStringLiteral("op")).toString())));
        operatorRow->addWidget(operation,1);
        auto *operatorProxy=new QGraphicsProxyWidget(card);
        operatorProxy->setWidget(operatorPanel);
        operatorProxy->setData(4,QStringLiteral("graph-operator"));
        operatorProxy->setPos(9,153);
        operatorProxy->setZValue(3);
        connect(operation,qOverload<int>(&QComboBox::currentIndexChanged),this,
                [this,key,operation,title,id](int) {
            QJsonObject current;
            if(!lookupGraph(key,nullptr,nullptr,&current))return;
            const QString op=operation->currentData().toString();
            const QString previousOp=current.value(QStringLiteral("op")).toString();
            if(previousOp==op)return;
            if(op==QStringLiteral("or") && current.value(QStringLiteral("inputs")).toArray().size()>8) {
                QMessageBox::information(this,tr("OR Inputs"),
                    tr("OR supports up to eight inputs. Disconnect extra inputs before switching this gate to OR."));
                const QSignalBlocker block(operation);
                operation->setCurrentIndex(operation->findData(previousOp));
                return;
            }
            current.insert(QStringLiteral("op"),op);
            graphUpdate(key,current);
            title->setText(op.toUpper()+QStringLiteral(" | ")+id);
            redrawLinks();showDetails(key);
        });
        card->moved=[this,key,card] {updateLiveWires(key,card);};
        addFoldButton(card,key);
        m_cards.insert(key,card);
        syncGraphCardSockets(key);
        auto *entry=new QListWidgetItem(tr("%1 : %2 (%3)")
            .arg(data.value(QStringLiteral("op")).toString().toUpper(),id,m_objects.value(owner).name),m_list);
        entry->setData(Qt::UserRole,key);entry->setForeground(QBrush(QColor(130,215,214)));
    }
    void refreshGraphDialogueCard(const QString &key,bool yes) {
        const QString display=graphDialogueKey(key,yes);
        if(!m_dialogueControls.contains(display))return;
        QJsonObject node;
        if(!lookupGraph(key,nullptr,nullptr,&node))return;
        const int index=node.value(yes?QStringLiteral("trueDialogueNode"):
                                      QStringLiteral("falseDialogueNode")).toInt(-1);
        const DialogueControls c=m_dialogueControls.value(display);
        const QSignalBlocker pblock(c.picker);
        const QSignalBlocker sblock(c.speaker);
        const QSignalBlocker tblock(c.message);
        c.picker->clear();c.picker->addItem(tr("None (not connected)"),-1);
        for(int i=0;i<m_dialogues.size();++i) {
            const QJsonObject dialogue=m_dialogues.at(i).toObject();
            c.picker->addItem(tr("%1: %2 | %3").arg(i)
                .arg(dialogue.value(QStringLiteral("speaker")).toString().left(14),
                     dialogue.value(QStringLiteral("text")).toString().simplified().left(25)),i);
        }
        c.picker->addItem(tr("+ Create new dialogue"),-2);
        c.picker->setCurrentIndex(qMax(0,c.picker->findData(index)));
        const bool valid=index>=0 && index<m_dialogues.size();
        const QJsonObject dialogue=valid?m_dialogues.at(index).toObject():QJsonObject();
        c.speaker->setText(dialogue.value(QStringLiteral("speaker")).toString());
        c.message->setPlainText(dialogue.value(QStringLiteral("text")).toString());
        c.speaker->setEnabled(valid);c.message->setEnabled(valid);
        c.info->setText(valid?tr("Dialogue #%1 is shared. Advanced choices stay in the Adventure Editor.").arg(index):
                               tr("Pick or create a dialogue. Runtime executes one message without advanced actions."));
        for(int i=0;i<m_list->count();++i) {
            auto *entry=m_list->item(i);
            if(entry->data(Qt::UserRole).toString()==display) {
                entry->setText(tr("Show Dialogue: %1 %2 (#%3)")
                    .arg(key,yes?QStringLiteral("TRUE"):QStringLiteral("FALSE"))
                    .arg(index));break;
            }
        }
    }
    void makeGraphDialogueCard(const QString &key,bool yes) {
        const QString display=graphDialogueKey(key,yes);
        if(m_cards.contains(display))return;
        if(!lookupGraph(key,nullptr,nullptr))return;
        auto *card=new NodeCard(QRectF(0,0,324,352));
        card->setData(0,QStringLiteral("card"));card->setData(1,display);
        card->setPen(QPen(QColor(171,126,222),1.5));card->setBrush(m_theme.panelBackground);
        m_scene->addItem(card);
        const QPointF at=m_positions.contains(display)?m_positions.value(display):
            viewportInsertionPoint(QSizeF(345,380));
        card->setPos(at);card->enableGridSnap();m_positions.insert(display,at);
        auto *stripe=new QGraphicsRectItem(QRectF(0,0,324,31),card);
        stripe->setPen(Qt::NoPen);stripe->setBrush(QColor(97,65,129));
        auto *heading=new QGraphicsSimpleTextItem(yes?tr("SHOW DIALOGUE | TRUE"):tr("SHOW DIALOGUE | FALSE"),card);
        heading->setBrush(Qt::white);heading->setPos(9,5);
        auto *input=new QGraphicsRectItem(QRectF(-7,50,14,14),card);
        input->setData(0,QStringLiteral("input"));input->setData(1,key);
        input->setPen(QPen(QColor(234,190,255),1.5));input->setBrush(QColor(159,103,203));
        input->setZValue(4);
        input->setToolTip(tr("INPUT: show this existing Adventure dialogue when the linked event runs"));
        auto *panel=new QWidget;
        panel->setFixedSize(302,303);
        panel->setStyleSheet(m_controlsStyle);
        auto *layout=new QVBoxLayout(panel);
        layout->setContentsMargins(5,4,5,4);layout->setSpacing(3);
        auto *picker=new QComboBox(panel);
        auto *browse=new QPushButton(tr("Browse Dialogue Folders..."),panel);
        auto *mode=new QComboBox(panel);
        mode->addItem(tr("Single message (no actions)"),QStringLiteral("single"));mode->setEnabled(false);
        auto *speaker=new QLineEdit(panel);speaker->setMaxLength(36);
        auto *message=new QPlainTextEdit(panel);message->setTabChangesFocus(true);
        auto *info=new QLabel(panel);info->setWordWrap(true);
        info->setStyleSheet(QStringLiteral("QLabel { background: transparent; font-size: 10px; color: %1; }").arg(m_theme.mutedText.name()));
        auto *disconnect=new QPushButton(tr("Disconnect Dialogue"),panel);
        layout->addWidget(new QLabel(tr("Adventure dialogue"),panel));
        layout->addWidget(picker);layout->addWidget(browse);layout->addWidget(mode);
        layout->addWidget(new QLabel(tr("Speaker"),panel));layout->addWidget(speaker);
        layout->addWidget(new QLabel(tr("Message"),panel));layout->addWidget(message,1);
        layout->addWidget(info);layout->addWidget(disconnect);
        auto *proxy=new QGraphicsProxyWidget(card);
        proxy->setWidget(panel);proxy->setPos(10,37);proxy->setZValue(3);
        DialogueControls controls;
        controls.picker=picker;controls.mode=mode;
        controls.speaker=speaker;controls.message=message;controls.info=info;
        m_dialogueControls.insert(display,controls);
        card->moved=[this,display,card]{updateLiveWires(display,card);};
        addFoldButton(card,display);
        m_cards.insert(display,card);
        auto *item=new QListWidgetItem(m_list);
        item->setData(Qt::UserRole,display);item->setForeground(QBrush(QColor(199,149,248)));
        refreshGraphDialogueCard(key,yes);
        connect(browse,&QPushButton::clicked,this,[this,key,yes,display] {
            QJsonObject n;
            if(!lookupGraph(key,nullptr,nullptr,&n))return;
            const int existing=n.value(yes?QStringLiteral("trueDialogueNode"):
                                        QStringLiteral("falseDialogueNode")).toInt(-1);
            const int selected=browseDialogueTree(existing);
            if(selected==-1 || !m_dialogueControls.contains(display))return;
            setGraphDialogue(key,yes,selected);
            refreshGraphDialogueCard(key,yes);
        });
        connect(picker,qOverload<int>(&QComboBox::currentIndexChanged),this,[this,key,yes,display](int) {
            if(!m_dialogueControls.contains(display))return;
            const QVariant data=m_dialogueControls.value(display).picker->currentData();
            setGraphDialogue(key,yes,data.isValid()?data.toInt():-1);
            refreshGraphDialogueCard(key,yes);
        });
        connect(speaker,&QLineEdit::textEdited,this,[this,key,yes](const QString &text) {
            QJsonObject n;
            if(!lookupGraph(key,nullptr,nullptr,&n))return;
            const int idx=n.value(yes?QStringLiteral("trueDialogueNode"):
                                  QStringLiteral("falseDialogueNode")).toInt(-1);
            if(idx<0 || idx>=m_dialogues.size())return;
            QJsonObject d=m_dialogues[idx].toObject();d.insert(QStringLiteral("speaker"),text.left(36));
            m_dialogues.replace(idx,d);m_dialoguesChanged=true;m_dirty=true;
        });
        connect(message,&QPlainTextEdit::textChanged,this,[this,key,yes,display] {
            if(!m_dialogueControls.contains(display))return;
            QJsonObject n;
            if(!lookupGraph(key,nullptr,nullptr,&n))return;
            const int idx=n.value(yes?QStringLiteral("trueDialogueNode"):
                                  QStringLiteral("falseDialogueNode")).toInt(-1);
            if(idx<0 || idx>=m_dialogues.size())return;
            const QString text=m_dialogueControls.value(display).message->toPlainText().left(2048);
            QJsonObject d=m_dialogues[idx].toObject();
            if(d.value(QStringLiteral("text")).toString()==text)return;
            d.insert(QStringLiteral("text"),text);
            m_dialogues.replace(idx,d);m_dialoguesChanged=true;m_dirty=true;
        });
        connect(disconnect,&QPushButton::clicked,this,[this,key,yes]{setGraphDialogue(key,yes,-1);});
    }
    void redrawGraphLinks() {
        auto append=[this](const QPointF &a,const QPointF &b,const QColor &color,
                           const QString &kind,const QString &key,int index,
                           const QString &fromId,const QString &toId) {
            const qreal bend=qMax(48.0,qAbs(b.x()-a.x())*.45);
            QPainterPath path(a);
            path.cubicTo(a+QPointF(bend,0),b-QPointF(bend,0),b);
            auto *wire=new NodeWire(path,QPen(color,3));
            wire->setData(0,kind);wire->setData(1,key);wire->setData(2,index);
            wire->setData(4,fromId);wire->setData(5,toId);
            wire->setZValue(0);m_scene->addItem(wire);m_lines.append(wire);
        };
        for(const QString &owner:m_order) {
            const NodeObject trigger=m_objects.value(owner);
            if(trigger.logicNodes.isEmpty())continue;
            for(const QJsonValue &value:trigger.logicNodes) {
                const QJsonObject n=value.toObject();
                const QString key=graphKey(owner,n.value(QStringLiteral("id")).toString());
                NodeCard *target=m_cards.value(key,nullptr);
                if(!target)continue;
                const QJsonArray inputs=n.value(QStringLiteral("inputs")).toArray();
                for(int i=0;i<inputs.size();++i) {
                    const QJsonObject v=inputs.at(i).toObject();
                    const QString kind=v.value(QStringLiteral("kind")).toString();
                    const QString id=v.value(QStringLiteral("id")).toString();
                    const QString from=kind==QStringLiteral("node")?graphKey(owner,id):
                        kind==QStringLiteral("event")?eventOwner(id):id;
                    NodeCard *source=m_cards.value(from,nullptr);
                    if(!source)continue;
                    const QPointF a=source->wirePoint(QPointF(kind==QStringLiteral("node")?274:224,
                        kind==QStringLiteral("node")?78:
                        kind==QStringLiteral("event")?
                        (eventKey(id)==QStringLiteral("destroy")?117.5:88.5):58));
                    const QPointF b=target->wirePoint(QPointF(0,52+24*i));
                    append(a,b,QColor(105,206,207),QStringLiteral("graph-input"),key,i,from,key);
                }
                // RESULT can directly drive any target Game Object's enabled
                // state. One teal wire replaces the misleading TRUE+FALSE pair.
                const QJsonArray resultTargets=n.value(QStringLiteral("resultTargets")).toArray();
                for(int j=0;j<resultTargets.size();++j) {
                    NodeCard *card=m_cards.value(resultTargets[j].toString(),nullptr);
                    if(!card)continue;
                    append(target->wirePoint(QPointF(274,78)),
                           card->wirePoint(QPointF(0,58)),QColor(90,208,213),
                           QStringLiteral("graph-result-binding"),key,j,key,resultTargets[j].toString());
                }
                for(const bool yes:{true,false}) {
                    const QColor color=yes?QColor(111,222,167):QColor(244,145,146);
                    const QPointF a=target->wirePoint(QPointF(274,yes?117:146));
                    const QString field=yes?QStringLiteral("trueActions"):QStringLiteral("falseActions");
                    const QJsonArray actions=n.value(field).toArray();
                    for(int j=0;j<actions.size();++j) {
                        const QString dest=actions[j].toObject().value(QStringLiteral("objectId")).toString();
                        NodeCard *card=m_cards.value(dest,nullptr);
                        if(!card)continue;
                        append(a,card->wirePoint(QPointF(0,58)),color,
                               yes?QStringLiteral("graph-true-action"):QStringLiteral("graph-false-action"),key,j,key,dest);
                    }
                    const int dialogue=n.value(yes?QStringLiteral("trueDialogueNode"):
                                                 QStringLiteral("falseDialogueNode")).toInt(-1);
                    QPointF npcPoint;
                    const QString source=QStringLiteral("@graphbranch:")+
                        (yes?QStringLiteral("true:"):QStringLiteral("false:"))+key;
                    const QString visualTo=graphDialogueVisualTarget(key,yes,dialogue);
                    NodeCard *card=m_cards.value(visualTo,nullptr);
                    if(dialogue>=0 && npcRoutePoint(source,dialogue,&npcPoint))
                        append(a,npcPoint,color,yes?QStringLiteral("graph-true-dialogue"):
                            QStringLiteral("graph-false-dialogue"),key,0,key,
                            m_npcDialogueRoutes.value(source).value(QStringLiteral("npc")).toString());
                    else if(dialogue>=0 && card)
                        append(a,card->wirePoint(QPointF(0,57)),color,
                               yes?QStringLiteral("graph-true-dialogue"):QStringLiteral("graph-false-dialogue"),key,0,
                               key,visualTo);
                }
            }
        }
    }
    void showGraphWireMenu(const QString &kind,const QString &key,int index,const QPoint &at) {
        QJsonObject n;
        if(!lookupGraph(key,nullptr,nullptr,&n))return;
        QMenu menu(this);
        const bool action=kind.endsWith(QStringLiteral("-action"));
        QHash<QAction*,QString> changes;
        if(action) {
            const QString field=kind.startsWith(QStringLiteral("graph-true"))?
                QStringLiteral("trueActions"):QStringLiteral("falseActions");
            const QJsonArray actions=n.value(field).toArray();
            const QString target=index>=0 && index<actions.size()?
                actions[index].toObject().value(QStringLiteral("objectId")).toString():QString();
            if(!isPlayerCommand(target))
                for(const QString &op:{QStringLiteral("enable"),QStringLiteral("disable"),QStringLiteral("toggle")})
                    changes.insert(menu.addAction(tr("Set %1").arg(op)),op);
        }
        QAction *remove=menu.addAction(tr("Remove Connection"));
        QAction *selected=menu.exec(at);
        if(!selected)return;
        if(kind==QStringLiteral("graph-result-binding")) {
            if(selected!=remove)return;
            QJsonArray outputs=n.value(QStringLiteral("resultTargets")).toArray();
            if(index<0 || index>=outputs.size())return;
            outputs.removeAt(index);n.insert(QStringLiteral("resultTargets"),outputs);
        } else if(kind==QStringLiteral("graph-input")) {
            if(selected!=remove)return;
            QJsonArray inputs=n.value(QStringLiteral("inputs")).toArray();
            if(index<0 || index>=inputs.size())return;
            inputs.removeAt(index);n.insert(QStringLiteral("inputs"),inputs);
        } else if(action) {
            const QString field=kind.startsWith(QStringLiteral("graph-true"))?
                QStringLiteral("trueActions"):QStringLiteral("falseActions");
            QJsonArray actions=n.value(field).toArray();
            if(index<0 || index>=actions.size())return;
            if(selected==remove)actions.removeAt(index);
            else if(changes.contains(selected)) {
                QJsonObject item=actions[index].toObject();
                item.insert(QStringLiteral("action"),changes.value(selected));actions.replace(index,item);
            } else return;
            n.insert(field,actions);
        } else if(selected==remove) {
            n.insert(kind==QStringLiteral("graph-true-dialogue")?
                QStringLiteral("trueDialogueNode"):QStringLiteral("falseDialogueNode"),-1);
        } else return;
        if(kind==QStringLiteral("graph-true-dialogue") || kind==QStringLiteral("graph-false-dialogue")) {
            const bool yes=kind==QStringLiteral("graph-true-dialogue");
            m_npcDialogueRoutes.remove(QStringLiteral("@graphbranch:")+
                (yes?QStringLiteral("true:"):QStringLiteral("false:"))+key);
            m_graphDialogueRoutes.remove(graphDialogueKey(key,yes));
        }
        graphUpdate(key,n);redrawLinks();showDetails(key);
    }

    // Separate conditional card IDs, with no duplicated gameplay links in .vsgm.
    QString toggleCardId(const QString &id) const {return QStringLiteral("@toggle:")+id;}
    QString branchCardId(const QString &id,bool yes) const {
        return (yes?QStringLiteral("@toggle-dialogue:true:"):QStringLiteral("@toggle-dialogue:false:"))+id;
    }
    // A Boolean is a visual read of a Game Object output. The real branching
    // behaviour remains owned by the Trigger in .sbgm, not by .vsgm.
    void convertLegacyToggle(const QString &owner) {
        if(!m_objects.contains(owner))return;
        NodeObject n=m_objects.value(owner);
        if(n.type!=QStringLiteral("trigger") || n.toggleStateTargetId.isEmpty())return;
        if(QMessageBox::question(this,tr("Convert Legacy Condition"),
            tr("Convert this Trigger's old single condition into an independent graph node?\n\n"
               "All inputs, TRUE/FALSE actions and dialogue IDs will be copied. The old "
               "condition will be cleared so it cannot run twice. The source .sbgm is backed "
               "up when you save."),
            QMessageBox::Yes|QMessageBox::No,QMessageBox::No)!=QMessageBox::Yes)return;
        QSet<QString> used;
        for(const QJsonValue &v:n.logicNodes)
            used.insert(v.toObject().value(QStringLiteral("id")).toString());
        int serial=1;while(used.contains(QStringLiteral("logic%1").arg(serial)))++serial;
        const QString name=QStringLiteral("logic%1").arg(serial);
        QJsonArray inputs;
        const QStringList sources=QStringList{n.toggleStateTargetId}+n.toggleStateInputIds;
        for(const QString &id:sources)
            inputs.append(QJsonObject{{QStringLiteral("kind"),QStringLiteral("object")},
                                      {QStringLiteral("id"),id}});
        const auto links=[](const QVector<NodeLink> &from) {
            QJsonArray result;
            for(const NodeLink &link:from)
                result.append(QJsonObject{{QStringLiteral("objectId"),link.target},
                                          {QStringLiteral("action"),link.action}});
            return result;
        };
        QJsonObject node{{QStringLiteral("id"),name},
            {QStringLiteral("op"),n.toggleStateOperator},
            {QStringLiteral("inputs"),inputs},
            {QStringLiteral("trueActions"),links(n.toggleTrueActions)},
            {QStringLiteral("falseActions"),links(n.toggleFalseActions)},
            {QStringLiteral("trueDialogueNode"),n.toggleTrueDialogueNode},
            {QStringLiteral("falseDialogueNode"),n.toggleFalseDialogueNode}};
        n.logicNodes.append(node);
        n.toggleStateTargetId.clear();n.toggleStateInputIds.clear();
        n.toggleStateOperator=QStringLiteral("boolean");
        n.toggleTrueDialogueNode=-1;n.toggleFalseDialogueNode=-1;
        n.toggleTrueActions.clear();n.toggleFalseActions.clear();
        m_objects.insert(owner,n);m_touched.insert(owner);m_dirty=true;
        const QString old=toggleCardId(owner),key=graphKey(owner,name);
        m_positions.insert(key,m_cards.contains(old)?m_cards.value(old)->pos():
            viewportInsertionPoint(QSizeF(290,215)));
        for(const bool yes:{true,false}) {
            const QString legacy=branchCardId(owner,yes);
            const QString next=graphDialogueKey(key,yes);
            if(m_cards.contains(legacy))m_positions.insert(next,m_cards.value(legacy)->pos());
        }
        for(const QString &oldCard:{branchCardId(owner,true),branchCardId(owner,false),old})
            removeOrphanCard(oldCard);
        makeGraphCard(owner,name);
        for(const bool yes:{true,false})
            if(node.value(yes?QStringLiteral("trueDialogueNode"):
                             QStringLiteral("falseDialogueNode")).toInt(-1)>=0)
                makeGraphDialogueCard(key,yes);
        redrawLinks();showDetails(key);
        m_status->setText(tr("Converted legacy condition into independent node %1. Save Graph + World to commit.").arg(name));
    }
    void addToggleCondition(const QString &owner,const QString &source,const QPointF &dropAt,
                            const QString &op=QStringLiteral("boolean")) {
        if (!m_objects.contains(owner) || m_objects.value(owner).type!=QStringLiteral("trigger") ||
            !m_objects.contains(source) || m_objects.value(source).resourceIndex<0 ||
            m_objects.value(source).type==QStringLiteral("npc"))return;
        NodeObject n=m_objects.value(owner);
        const QString mode=(op==QStringLiteral("and") || op==QStringLiteral("or"))
            ? op : QStringLiteral("boolean");
        if (!n.toggleStateTargetId.isEmpty() && n.toggleStateTargetId!=source &&
            n.toggleStateOperator==QStringLiteral("boolean")) {
            if (QMessageBox::question(this,tr("Change Boolean Source"),
                tr("Change this Trigger's state source from %1 to %2?")
                  .arg(m_objects.value(n.toggleStateTargetId).name,m_objects.value(source).name),
                QMessageBox::Yes|QMessageBox::No,QMessageBox::No)!=QMessageBox::Yes)return;
        }
        if (n.toggleStateTargetId!=source || n.toggleStateOperator!=mode ||
            !n.toggleStateInputIds.isEmpty()) {
            n.toggleStateTargetId=source;
            n.toggleStateOperator=mode;
            n.toggleStateInputIds.clear();
            m_objects.insert(owner,n);m_touched.insert(owner);m_dirty=true;
        }
        if (!m_cards.contains(owner))makeObjectCard(owner,m_positions.contains(owner)?
            m_positions.value(owner):viewportInsertionPoint(QSizeF(285,215)));
        if (!m_cards.contains(source))makeObjectCard(source,m_positions.contains(source)?
            m_positions.value(source):viewportInsertionPoint(QSizeF(240,110)));
        const QString key=toggleCardId(owner);
        if (!dropAt.isNull() && !m_cards.contains(key))m_positions.insert(key,dropAt);
        m_placedCards.insert(key);
        createToggleCard(owner);
        refreshToggleCard(owner);
        m_dirty=true;redrawLinks();showDetails(key);
        if (m_cards.contains(key))m_view->centerOn(m_cards.value(key));
    }
    void addInputToCondition(const QString &owner,const QString &source) {
        if (!m_objects.contains(owner) || !m_objects.contains(source) ||
            m_objects.value(owner).type!=QStringLiteral("trigger") ||
            m_objects.value(source).type==QStringLiteral("trigger") ||
            m_objects.value(source).resourceIndex<0 ||
            m_objects.value(source).type==QStringLiteral("npc"))return;
        NodeObject n=m_objects.value(owner);
        if (n.toggleStateTargetId.isEmpty()) { addToggleCondition(owner,source,QPointF());return; }
        if (n.toggleStateOperator==QStringLiteral("boolean")) {
            addToggleCondition(owner,source,QPointF());return;
        }
        if (source==n.toggleStateTargetId || n.toggleStateInputIds.contains(source))return;
        if ((n.toggleStateOperator==QStringLiteral("or") && n.toggleStateInputIds.size()>=7) ||
            n.toggleStateInputIds.size()>=15) {
            QMessageBox::information(this,tr("Logic inputs"),
                n.toggleStateOperator==QStringLiteral("or") ? tr("OR accepts at most eight inputs.") :
                tr("AND accepts at most sixteen inputs."));return;
        }
        n.toggleStateInputIds.append(source);
        m_objects.insert(owner,n);m_touched.insert(owner);m_dirty=true;
        if (!m_cards.contains(source))makeObjectCard(source,m_positions.contains(source)?
            m_positions.value(source):viewportInsertionPoint(QSizeF(240,110)));
        refreshToggleCard(owner);redrawLinks();showDetails(toggleCardId(owner));
    }
    void createToggleCard(const QString &id) {
        if (!m_objects.contains(id) || m_cards.contains(toggleCardId(id)))return;
        const QString key=toggleCardId(id);
        auto *card=new NodeCard(QRectF(0,0,294,199));
        card->setData(0,QStringLiteral("card"));card->setData(1,key);
        card->setPen(QPen(QColor(123,201,192),1.5));card->setBrush(m_theme.panelBackground);
        m_scene->addItem(card);
        const QString stateSource=m_objects.value(id).toggleStateTargetId;
        const QPointF origin=m_cards.contains(stateSource)?m_cards.value(stateSource)->pos():
                             m_cards.contains(id)?m_cards.value(id)->pos():QPointF(70,85);
        const QPointF pos=m_positions.value(key,origin+QPointF(350,30));
        card->setPos(pos);card->enableGridSnap();m_positions.insert(key,pos);
        auto *stripe=new QGraphicsRectItem(QRectF(0,0,294,27),card);
        stripe->setPen(Qt::NoPen);stripe->setBrush(QColor(41,104,106));
        auto *title=new QGraphicsSimpleTextItem(tr("BOOLEAN | ENABLED?"),card);
        title->setBrush(Qt::white);title->setPos(8,4);
        m_logicTitles.insert(id,title);
        auto *input=new QGraphicsRectItem(QRectF(-7,51,14,14),card);
        input->setData(0,QStringLiteral("input"));input->setData(1,key);
        input->setPen(QPen(QColor(160,237,232),1.5));input->setBrush(QColor(75,173,177));
        input->setZValue(4);
        input->setToolTip(tr("INPUT: read an existing Game Object enabled state"));
        // No state dropdown: the source is determined by the incoming wire
        // from the actual Game Object, e.g. Lifty -> Boolean.
        auto *sourceLabel=new QGraphicsSimpleTextItem(card);
        sourceLabel->setBrush(m_theme.text);sourceLabel->setPos(12,38);
        m_booleanSourceLabels.insert(id,sourceLabel);
        auto *note=new QGraphicsSimpleTextItem(tr("TRUE = enabled  |  FALSE = disabled"),card);
        note->setBrush(m_theme.mutedText);note->setPos(12,68);
        m_logicNotes.insert(id,note);
        for (const bool yes:{true,false}) {
            const int y=yes?107:138;
            auto *label=new QGraphicsSimpleTextItem(yes?tr("TRUE / YES"):tr("FALSE / NO"),card);
            label->setBrush(yes?QColor(111,222,167):QColor(244,145,146));label->setPos(12,y-8);
            auto *port=new QGraphicsEllipseItem(QRectF(285,y-6,18,18),card);
            port->setData(0,QStringLiteral("output"));
            port->setData(1,(yes?QStringLiteral("@stateout:true:"):QStringLiteral("@stateout:false:"))+id);
            port->setPen(QPen(Qt::white,1));port->setBrush(yes?QColor(76,171,118):QColor(193,86,86));
        }
        auto *opCombo=new QComboBox;
        opCombo->setFixedSize(205,27);
        opCombo->setStyleSheet(m_controlsStyle);
        for(const QString &op:{QStringLiteral("boolean"),QStringLiteral("and"),QStringLiteral("or")})
            opCombo->addItem(op.toUpper(),op);
        opCombo->setCurrentIndex(qMax(0,opCombo->findData(m_objects.value(id).toggleStateOperator)));
        auto *opProxy=new QGraphicsProxyWidget(card);
        opProxy->setWidget(opCombo);
        opProxy->setPos(12,158);
        opProxy->setZValue(3);
        connect(opCombo,qOverload<int>(&QComboBox::currentIndexChanged),this,
                [this,id,opCombo](int) {
            NodeObject n=m_objects.value(id);
            const QString op=opCombo->currentData().toString();
            if(op==n.toggleStateOperator)return;
            if(op==QStringLiteral("or") && n.toggleStateInputIds.size()>7) {
                QMessageBox::information(this,tr("OR Inputs"),
                    tr("OR supports up to eight inputs. Disconnect extra inputs before switching this gate to OR."));
                const QSignalBlocker block(opCombo);
                opCombo->setCurrentIndex(opCombo->findData(n.toggleStateOperator));
                return;
            }
            n.toggleStateOperator=op;
            if(op==QStringLiteral("boolean"))n.toggleStateInputIds.clear();
            m_objects.insert(id,n);m_touched.insert(id);m_dirty=true;
            refreshToggleCard(id);redrawLinks();showDetails(toggleCardId(id));
        });
        card->moved=[this,key,card] {updateLiveWires(key,card);};
        addFoldButton(card,key);
        m_cards.insert(key,card);
        auto *entry=new QListWidgetItem(m_list);
        entry->setData(Qt::UserRole,key);
        entry->setForeground(QBrush(QColor(123,201,192)));
        entry->setToolTip(tr("Evaluated after the %1 Trigger runs").arg(m_objects.value(id).name));
        refreshToggleCard(id);
    }
    void refreshToggleCard(const QString &id) {
        if (!m_booleanSourceLabels.contains(id) || !m_objects.contains(id))return;
        const NodeObject node=m_objects.value(id);
        const QString source=node.toggleStateTargetId;
        QStringList names;
        if (!source.isEmpty())names.append(m_objects.value(source).name);
        for (const QString &extra:node.toggleStateInputIds)names.append(m_objects.value(extra).name);
        const QString op=node.toggleStateOperator.toUpper();
        if (m_logicTitles.contains(id))m_logicTitles.value(id)->setText(
            op==QStringLiteral("BOOLEAN")?tr("BOOLEAN | ENABLED?"):op+tr(" | STATES?"));
        if (m_logicNotes.contains(id))m_logicNotes.value(id)->setText(
            op==QStringLiteral("AND")?tr("TRUE = all enabled  |  FALSE = not all"):
            op==QStringLiteral("OR")?tr("TRUE = either enabled  |  FALSE = both off"):
            tr("TRUE = enabled  |  FALSE = disabled"));
        const QString label=names.isEmpty()?tr("Drag Game Object output here"):
            tr("Read: %1").arg(names.join(node.toggleStateOperator==QStringLiteral("or")?
                QStringLiteral(" OR "):QStringLiteral(" AND ")));
        m_booleanSourceLabels.value(id)->setText(label.left(43));
        const QString key=toggleCardId(id);
        for (int i=0;i<m_list->count();++i) {
            QListWidgetItem *item=m_list->item(i);
            if (item->data(Qt::UserRole).toString()==key) {
                const QString sourceName=m_objects.contains(source)?m_objects.value(source).name:
                                         source.isEmpty()?tr("Unconnected"):source;
                item->setText(tr("%1: %2 (%3)").arg(op,sourceName,m_objects.value(id).name));
                break;
            }
        }
    }
    // Legacy Read Toggle State data is displayed as a Boolean node.
    // TRUE/FALSE uses the same full purple dialogue editor as a Trigger:
    // folder browser, existing/new dialogue, speaker and message. Both routes
    // edit the exact same Adventure dialogue IDs in .sbgm. Branch playback
    // is currently single-message only in the V1 generator, so the mode is
    // displayed honestly as read-only rather than offering unsupported modes.
    void createBranchCard(const QString &id,bool yes) {
        const QString key=branchCardId(id,yes);
        if (m_cards.contains(key))return;
        auto *card=new NodeCard(QRectF(0,0,324,352));
        card->setData(0,QStringLiteral("card"));card->setData(1,key);
        card->setPen(QPen(QColor(171,126,222),1.5));card->setBrush(m_theme.panelBackground);
        m_scene->addItem(card);
        const QPointF origin=m_cards.contains(toggleCardId(id))?m_cards.value(toggleCardId(id))->pos():QPointF(500,180);
        const QPointF pos=m_positions.value(key,origin+QPointF(380,yes?-40:350));
        card->setPos(pos);card->enableGridSnap();m_positions.insert(key,pos);
        auto *stripe=new QGraphicsRectItem(QRectF(0,0,324,31),card);
        stripe->setPen(Qt::NoPen);stripe->setBrush(QColor(97,65,129));
        auto *heading=new QGraphicsSimpleTextItem(yes?tr("SHOW DIALOGUE | TRUE"):tr("SHOW DIALOGUE | FALSE"),card);
        heading->setBrush(Qt::white);heading->setPos(9,5);
        auto *input=new QGraphicsRectItem(QRectF(-7,50,14,14),card);
        input->setData(0,QStringLiteral("input"));input->setData(1,key);
        input->setPen(QPen(QColor(234,190,255),1.5));input->setBrush(QColor(159,103,203));
        input->setZValue(4);
        input->setToolTip(tr("INPUT: show this existing Adventure dialogue when the linked event runs"));
        auto *panel=new QWidget;
        panel->setFixedSize(302,303);
        panel->setStyleSheet(m_controlsStyle);
        auto *layout=new QVBoxLayout(panel);
        layout->setContentsMargins(5,4,5,4);layout->setSpacing(3);
        auto *picker=new QComboBox(panel);
        auto *browse=new QPushButton(tr("Browse Dialogue Folders..."),panel);
        auto *mode=new QComboBox(panel);
        mode->addItem(tr("Single message (no actions)"),QStringLiteral("single"));
        mode->setEnabled(false);
        mode->setToolTip(tr("Conditional dialogue currently plays one message. Other playback modes remain available for ordinary Trigger dialogue."));
        auto *speaker=new QLineEdit(panel);speaker->setMaxLength(36);
        auto *message=new QPlainTextEdit(panel);message->setTabChangesFocus(true);
        auto *info=new QLabel(panel);info->setWordWrap(true);
        info->setStyleSheet(QStringLiteral("QLabel { background: transparent; font-size: 10px; color: %1; }").arg(m_theme.mutedText.name()));
        auto *disconnect=new QPushButton(tr("Disconnect Dialogue"),panel);
        layout->addWidget(new QLabel(tr("Adventure dialogue"),panel));
        layout->addWidget(picker);layout->addWidget(browse);layout->addWidget(mode);
        layout->addWidget(new QLabel(tr("Speaker"),panel));layout->addWidget(speaker);
        layout->addWidget(new QLabel(tr("Message"),panel));layout->addWidget(message,1);
        layout->addWidget(info);layout->addWidget(disconnect);
        auto *proxy=new QGraphicsProxyWidget(card);
        proxy->setWidget(panel);proxy->setPos(10,37);proxy->setZValue(3);
        DialogueControls controls;
        controls.picker=picker;controls.mode=mode;
        controls.speaker=speaker;controls.message=message;controls.info=info;
        m_dialogueControls.insert(key,controls);
        card->moved=[this,key,card]{updateLiveWires(key,card);};
        addFoldButton(card,key);
        m_cards.insert(key,card);
        auto *entry=new QListWidgetItem(m_list);
        entry->setData(Qt::UserRole,key);entry->setForeground(QBrush(QColor(199,149,248)));
        refreshBranchCard(id,yes);
        connect(browse,&QPushButton::clicked,this,[this,id,yes,key] {
            const NodeObject n=m_objects.value(id);
            const int existing=yes?n.toggleTrueDialogueNode:n.toggleFalseDialogueNode;
            const int selected=browseDialogueTree(existing);
            if (selected==-1 || !m_dialogueControls.contains(key))return;
            const int row=m_dialogueControls.value(key).picker->findData(selected);
            if (row>=0)m_dialogueControls.value(key).picker->setCurrentIndex(row);
        });
        connect(picker,qOverload<int>(&QComboBox::currentIndexChanged),this,[this,id,yes,key](int) {
            if (!m_dialogueControls.contains(key) || !m_objects.contains(id))return;
            const QVariant data=m_dialogueControls.value(key).picker->currentData();
            int selected=data.isValid()?data.toInt():-1;
            if (selected==-2) {
                if (m_dialogues.size()>=256) {
                    QMessageBox::warning(this,tr("Visual Nodes"),tr("Adventure dialogue limit reached."));
                    refreshBranchCard(id,yes);return;
                }
                QJsonArray choices;
                for (int i=0;i<3;++i)
                    choices.append(QJsonObject{{QStringLiteral("text"),QString()},
                        {QStringLiteral("reply"),QString()},
                        {QStringLiteral("next"),-1},{QStringLiteral("missingNext"),-1},
                        {QStringLiteral("requires"),-1},{QStringLiteral("give"),-1},
                        {QStringLiteral("take"),-1},{QStringLiteral("action"),-1}});
                m_dialogues.append(QJsonObject{{QStringLiteral("speaker"),QStringLiteral("NPC")},
                    {QStringLiteral("text"),QStringLiteral("Hello!")},{QStringLiteral("choices"),choices}});
                selected=m_dialogues.size()-1;m_dialoguesChanged=true;
            }
            NodeObject n=m_objects.value(id);
            int &index=yes?n.toggleTrueDialogueNode:n.toggleFalseDialogueNode;
            if (index!=selected) {
                index=selected;m_objects.insert(id,n);m_touched.insert(id);m_dirty=true;
            }
            refreshBranchCard(id,yes);redrawLinks();showDetails(key);
        });
        connect(speaker,&QLineEdit::textEdited,this,[this,id,yes](const QString &value) {
            const NodeObject n=m_objects.value(id);
            const int index=yes?n.toggleTrueDialogueNode:n.toggleFalseDialogueNode;
            if (index<0 || index>=m_dialogues.size())return;
            QJsonObject dialogue=m_dialogues.at(index).toObject();
            if (dialogue.value(QStringLiteral("speaker")).toString()==value)return;
            dialogue.insert(QStringLiteral("speaker"),value.left(36));
            m_dialogues.replace(index,dialogue);m_dialoguesChanged=true;m_dirty=true;
            for (const QString &other:m_dialogueCards)
                if (m_objects.value(other).dialogueNode==index)refreshDialogueCard(other);
            for (const QString &owner:m_order) {
                const NodeObject linked=m_objects.value(owner);
                if ((owner!=id || !yes) && linked.toggleTrueDialogueNode==index)
                    refreshBranchCard(owner,true);
                if ((owner!=id || yes) && linked.toggleFalseDialogueNode==index)
                    refreshBranchCard(owner,false);
            }
        });
        connect(message,&QPlainTextEdit::textChanged,this,[this,id,yes,key] {
            if (!m_dialogueControls.contains(key))return;
            const NodeObject n=m_objects.value(id);
            const int index=yes?n.toggleTrueDialogueNode:n.toggleFalseDialogueNode;
            if (index<0 || index>=m_dialogues.size())return;
            const QString value=m_dialogueControls.value(key).message->toPlainText().left(2048);
            QJsonObject dialogue=m_dialogues.at(index).toObject();
            if (dialogue.value(QStringLiteral("text")).toString()==value)return;
            dialogue.insert(QStringLiteral("text"),value);
            m_dialogues.replace(index,dialogue);m_dialoguesChanged=true;m_dirty=true;
            for (const QString &other:m_dialogueCards)
                if (m_objects.value(other).dialogueNode==index)refreshDialogueCard(other);
            for (const QString &owner:m_order) {
                const NodeObject linked=m_objects.value(owner);
                if ((owner!=id || !yes) && linked.toggleTrueDialogueNode==index)
                    refreshBranchCard(owner,true);
                if ((owner!=id || yes) && linked.toggleFalseDialogueNode==index)
                    refreshBranchCard(owner,false);
            }
        });
        connect(disconnect,&QPushButton::clicked,this,[this,id,yes] {
            const QString key=branchCardId(id,yes);
            NodeObject n=m_objects.value(id);
            int &index=yes?n.toggleTrueDialogueNode:n.toggleFalseDialogueNode;
            if (index<0)return;
            index=-1;m_objects.insert(id,n);m_touched.insert(id);m_dirty=true;
            refreshBranchCard(id,yes);redrawLinks();showDetails(key);
        });
    }
    void refreshBranchCard(const QString &id,bool yes) {
        const QString key=branchCardId(id,yes);
        if (!m_dialogueControls.contains(key))return;
        const DialogueControls c=m_dialogueControls.value(key);
        const NodeObject n=m_objects.value(id);
        const int index=yes?n.toggleTrueDialogueNode:n.toggleFalseDialogueNode;
        const QSignalBlocker pblock(c.picker);
        const QSignalBlocker sblock(c.speaker);
        const QSignalBlocker tblock(c.message);
        c.picker->clear();c.picker->addItem(tr("None (not connected)"),-1);
        for (int i=0;i<m_dialogues.size();++i) {
            const QJsonObject d=m_dialogues.at(i).toObject();
            c.picker->addItem(tr("%1: %2 | %3").arg(i)
                .arg(d.value(QStringLiteral("speaker")).toString().left(14),
                     d.value(QStringLiteral("text")).toString().simplified().left(25)),i);
        }
        c.picker->addItem(tr("+ Create new dialogue"),-2);
        c.picker->setCurrentIndex(qMax(0,c.picker->findData(index)));
        const bool valid=index>=0 && index<m_dialogues.size();
        const QJsonObject d=valid?m_dialogues.at(index).toObject():QJsonObject();
        c.speaker->setText(d.value(QStringLiteral("speaker")).toString());
        c.message->setPlainText(d.value(QStringLiteral("text")).toString());
        c.speaker->setEnabled(valid);c.message->setEnabled(valid);
        c.info->setText(valid?tr("Editing dialogue %1 updates all references. Advanced choices remain in the Adventure Editor.").arg(index):
                              tr("Choose an existing dialogue or create one. This branch plays one message."));
        for (int i=0;i<m_list->count();++i) {
            QListWidgetItem *item=m_list->item(i);
            if (item->data(Qt::UserRole).toString()!=key)continue;
            item->setText(tr("Show Dialogue: %1 / %2 (%3)")
                .arg(n.name,yes?tr("TRUE"):tr("FALSE"),valid?QString::number(index):tr("unlinked")));
            break;
        }
    }
    void setBranchDialogue(const QString &id,bool yes,int index,const QPointF &at) {
        if (!m_objects.contains(id) || m_objects.value(id).type!=QStringLiteral("trigger"))return;
        if (index<-1 || index>=m_dialogues.size())return;
        NodeObject n=m_objects.value(id);
        if (index>=0 && n.toggleStateTargetId.isEmpty()) {
            QMessageBox::information(this,tr("Boolean"),
                tr("Choose the Game Object state in the Boolean card first."));return;
        }
        const QString source=QStringLiteral("@stateout:")+
            (yes?QStringLiteral("true:"):QStringLiteral("false:"))+id;
        if (index<0 || m_npcDialogueRoutes.value(source).value(QStringLiteral("dialogue")).toInt(-1)!=index)
            m_npcDialogueRoutes.remove(source);
        if (yes)n.toggleTrueDialogueNode=index;else n.toggleFalseDialogueNode=index;
        m_objects.insert(id,n);m_touched.insert(id);m_dirty=true;
        const QString key=branchCardId(id,yes);
        if (index>=0) {
            if (!m_cards.contains(key))m_positions.insert(key,at);
            m_placedCards.insert(key);
            createToggleCard(id);
            if (!npcRoutePoint(source,index)) {
                if (!m_cards.contains(key))createBranchCard(id,yes);
                refreshBranchCard(id,yes);
            }
        } else if (m_cards.contains(key)) {
            // A disconnected card stays on the layout, just like ordinary
            // Show Dialogue. Delete removes the card; Disconnect removes wire.
            m_placedCards.insert(key);
            refreshBranchCard(id,yes);
        }
        redrawLinks();showDetails(toggleCardId(id));
    }
    void selectBranchDialogue(const QString &output,const QPointF &at) {
        const bool yes=output.startsWith(QStringLiteral("@stateout:true:"));
        const QString prefix=yes?QStringLiteral("@stateout:true:"):QStringLiteral("@stateout:false:");
        if (!output.startsWith(prefix))return;
        const QString id=output.mid(prefix.size());
        if (!m_objects.contains(id))return;
        const NodeObject n=m_objects.value(id);
        if (n.toggleStateTargetId.isEmpty()) {
            QMessageBox::information(this,tr("Boolean"),
                tr("Choose a Game Object in the Boolean card before adding branch actions."));return;
        }
        const int old=yes?n.toggleTrueDialogueNode:n.toggleFalseDialogueNode;
        const int selected=browseDialogueTree(old);
        if (selected==-1)return;
        int index=selected;
        if (selected==-2) {
            if (m_dialogues.size()>=256) {QMessageBox::warning(this,tr("Visual Nodes"),tr("Adventure dialogue limit reached."));return;}
            m_dialogues.append(QJsonObject{{QStringLiteral("speaker"),QStringLiteral("NPC")},
              {QStringLiteral("text"),QStringLiteral("Hello!")},{QStringLiteral("choices"),QJsonArray()}});
            index=m_dialogues.size()-1;m_dialoguesChanged=true;
        }
        setBranchDialogue(id,yes,index,at);
    }
    // Phase 2: one editable Show Dialogue card per Trigger. The card's
    // gameplay values live in .sbgm; .vsgm stores only presence and location.
    QString dialogueCardId(const QString &id) const {
        return QStringLiteral("@dialogue:")+id;
    }
    void addDialogueCard() {
        const QString id=m_selectedCardId;
        if (!m_objects.contains(id) || m_objects.value(id).type!=QStringLiteral("trigger")) {
            QMessageBox::information(this,tr("Show Dialogue"),
                tr("Select a Trigger card first, then click + Show Dialogue."));
            return;
        }
        if (!m_dialogueCards.contains(id)) {
            m_placedCards.insert(dialogueCardId(id));
            createDialogueCard(id);
            m_dirty=true;
            redrawLinks();
        }
        const QString cardId=dialogueCardId(id);
        m_view->centerOn(m_cards.value(cardId));
        showDetails(cardId);
    }
    void createDialogueCard(const QString &id) {
        if (m_dialogueCards.contains(id) || !m_objects.contains(id))return;
        m_dialogueCards.insert(id);
        const QString key=dialogueCardId(id);
        auto *card=new NodeCard(QRectF(0,0,324,352));
        card->setData(0,QStringLiteral("card"));card->setData(1,key);
        card->setPen(QPen(QColor(171,126,222),1.5));
        card->setBrush(m_theme.panelBackground);
        m_scene->addItem(card);
        int triggerRow=0;
        for (const QString &candidate:m_order) {
            if (candidate==id)break;
            if (m_objects.value(candidate).type==QStringLiteral("trigger"))++triggerRow;
        }
        const QPointF pos=m_positions.contains(key)?m_positions.value(key):
            viewportInsertionPoint(QSizeF(345,380));
        card->setPos(pos);
        card->enableGridSnap();
        m_positions.insert(key,pos);
        auto *stripe=new QGraphicsRectItem(QRectF(0,0,324,31),card);
        stripe->setPen(Qt::NoPen);stripe->setBrush(QColor(97,65,129));
        auto *heading=new QGraphicsSimpleTextItem(tr("SHOW DIALOGUE  |  %1")
            .arg(m_objects.value(id).name.left(21)),card);
        heading->setBrush(Qt::white);heading->setPos(9,5);
        // Only the header is the drag handle. The proxy occupies the body,
        // so text editing / dropdown clicks never drag the entire card.
        auto *input=new QGraphicsRectItem(QRectF(-7,50,14,14),card);
        input->setData(0,QStringLiteral("input"));input->setData(1,key);
        input->setPen(QPen(QColor(234,190,255),1.5));input->setBrush(QColor(159,103,203));
        input->setZValue(4);
        input->setToolTip(tr("INPUT: show this existing Adventure dialogue when the linked event runs"));
        auto *panel=new QWidget;
        panel->setFixedSize(302,303);
        panel->setStyleSheet(m_controlsStyle);
        auto *layout=new QVBoxLayout(panel);
        layout->setContentsMargins(5,4,5,4);
        layout->setSpacing(3);
        auto *picker=new QComboBox(panel);
        picker->setToolTip(tr("Choose an existing Adventure dialogue or create a new one."));
        auto *browse=new QPushButton(tr("Browse Dialogue Folders..."),panel);
        browse->setToolTip(tr("Browse the same folder tree as the Adventure Dialogue Editor."));
        auto *mode=new QComboBox(panel);
        mode->addItem(tr("Single message (no actions)"),QStringLiteral("single"));
        mode->addItem(tr("Message sequence (no actions)"),QStringLiteral("sequence"));
        mode->addItem(tr("Full conversation (actions)"),QStringLiteral("conversation"));
        auto *speaker=new QLineEdit(panel);
        speaker->setMaxLength(36);
        auto *message=new QPlainTextEdit(panel);
        message->setTabChangesFocus(true);
        auto *info=new QLabel(panel);
        info->setWordWrap(true);
        info->setStyleSheet(QStringLiteral("QLabel { background: transparent; font-size: 10px; color: %1; }").arg(m_theme.mutedText.name()));
        auto *disconnect=new QPushButton(tr("Disconnect Dialogue"),panel);
        disconnect->setToolTip(tr("Unlink the dialogue from this Trigger; the Adventure dialogue remains intact."));
        layout->addWidget(new QLabel(tr("Adventure dialogue"),panel));
        layout->addWidget(picker);
        layout->addWidget(browse);
        layout->addWidget(mode);
        layout->addWidget(new QLabel(tr("Speaker"),panel));
        layout->addWidget(speaker);
        layout->addWidget(new QLabel(tr("Message"),panel));
        layout->addWidget(message,1);
        layout->addWidget(info);
        layout->addWidget(disconnect);
        auto *proxy=new QGraphicsProxyWidget(card);
        proxy->setWidget(panel);
        proxy->setPos(10,37);
        proxy->setZValue(3);
        DialogueControls controls;
        controls.picker=picker;controls.mode=mode;
        controls.speaker=speaker;controls.message=message;controls.info=info;
        m_dialogueControls.insert(id,controls);
        refreshDialogueCard(id);
        connect(browse,&QPushButton::clicked,this,[this,id] {
            if (!m_dialogueControls.contains(id) || !m_objects.contains(id))return;
            const int selected=browseDialogueTree(m_objects.value(id).dialogueNode);
            if (selected==-1)return;
            const auto controls=m_dialogueControls.value(id);
            const int row=controls.picker->findData(selected);
            if (row>=0)controls.picker->setCurrentIndex(row);
        });
        connect(picker,qOverload<int>(&QComboBox::currentIndexChanged),this,
            [this,id](int) {
                if (!m_objects.contains(id))return;
                // QComboBox::currentData() returns QVariant, whose toInt() takes
                // bool *ok (not an integer fallback like QJsonValue::toInt()).
                const QVariant selectedData=m_dialogueControls.value(id).picker->currentData();
                int choice=selectedData.isValid() ? selectedData.toInt() : -1;
                if (choice==-2) {
                    if (m_dialogues.size()>=256) {
                        QMessageBox::warning(this,tr("Visual Nodes"),
                            tr("Adventure dialogues are limited to 256 nodes."));
                        refreshDialogueCard(id);return;
                    }
                    QJsonArray choices;
                    for (int i=0;i<3;++i)
                        choices.append(QJsonObject{{QStringLiteral("text"),QString()},
                            {QStringLiteral("reply"),QString()},
                            {QStringLiteral("next"),-1},{QStringLiteral("missingNext"),-1},
                            {QStringLiteral("requires"),-1},{QStringLiteral("give"),-1},
                            {QStringLiteral("take"),-1},{QStringLiteral("action"),-1}});
                    m_dialogues.append(QJsonObject{{QStringLiteral("speaker"),QStringLiteral("NPC")},
                        {QStringLiteral("text"),QStringLiteral("Hello!")},
                        {QStringLiteral("choices"),choices}});
                    choice=m_dialogues.size()-1;
                    m_dialoguesChanged=true;
                }
                NodeObject n=m_objects.value(id);
                if (n.dialogueNode!=choice) {
                    n.dialogueNode=choice;m_objects.insert(id,n);
                    m_touched.insert(id);m_dirty=true;
                }
                refreshDialogueCard(id);redrawLinks();showDetails(id);
            });
        connect(mode,qOverload<int>(&QComboBox::currentIndexChanged),this,[this,id](int) {
            NodeObject n=m_objects.value(id);
            const QString selected=m_dialogueControls.value(id).mode->currentData().toString();
            if (n.dialogueMode!=selected) {
                n.dialogueMode=selected;m_objects.insert(id,n);
                m_touched.insert(id);m_dirty=true;
            }
        });
        connect(speaker,&QLineEdit::textEdited,this,[this,id](const QString &value) {
            editDialogueText(id,QStringLiteral("speaker"),value);
        });
        connect(message,&QPlainTextEdit::textChanged,this,[this,id] {
            const auto controls=m_dialogueControls.value(id);
            editDialogueText(id,QStringLiteral("text"),controls.message->toPlainText());
        });
        connect(disconnect,&QPushButton::clicked,this,[this,id] {
            NodeObject n=m_objects.value(id);
            if (n.dialogueNode<0)return;
            n.dialogueNode=-1;m_objects.insert(id,n);
            m_touched.insert(id);m_dirty=true;
            refreshDialogueCard(id);redrawLinks();showDetails(id);
        });
        card->moved=[this,key,card] {updateLiveWires(key,card);};
        addFoldButton(card,key);
        m_cards.insert(key,card);
        // Dialogue cards are real visible graph cards too: selecting, locating,
        // double-clicking and Delete all use the same id as on the canvas.
        auto *rowItem=new QListWidgetItem(m_list);
        rowItem->setData(Qt::UserRole,key);
        rowItem->setForeground(QBrush(QColor(199,149,248)));
        refreshDialogueCard(id);
    }
    void refreshDialogueCard(const QString &id) {
        if (!m_dialogueControls.contains(id) || !m_objects.contains(id))return;
        const DialogueControls c=m_dialogueControls.value(id);
        const NodeObject n=m_objects.value(id);
        const QSignalBlocker pblock(c.picker);
        const QSignalBlocker mblock(c.mode);
        const QSignalBlocker sblock(c.speaker);
        const QSignalBlocker tblock(c.message);
        c.picker->clear();
        c.picker->addItem(tr("None (not connected)"),-1);
        for (int j=0;j<m_dialogues.size();++j) {
            const QJsonObject d=m_dialogues.at(j).toObject();
            c.picker->addItem(tr("%1: %2 | %3").arg(j)
                .arg(d.value(QStringLiteral("speaker")).toString().left(14),
                     d.value(QStringLiteral("text")).toString().simplified().left(25)),j);
        }
        c.picker->addItem(tr("+ Create new dialogue"),-2);
        c.picker->setCurrentIndex(qMax(0,c.picker->findData(n.dialogueNode)));
        c.mode->setCurrentIndex(qMax(0,c.mode->findData(n.dialogueMode)));
        const bool valid=n.dialogueNode>=0 && n.dialogueNode<m_dialogues.size();
        const QJsonObject d=valid?m_dialogues.at(n.dialogueNode).toObject():QJsonObject();
        c.speaker->setText(d.value(QStringLiteral("speaker")).toString());
        c.message->setPlainText(d.value(QStringLiteral("text")).toString());
        c.mode->setEnabled(valid);c.speaker->setEnabled(valid);c.message->setEnabled(valid);
        c.info->setText(valid?tr("Editing this dialogue updates every place that references dialogue %1. Advanced choices remain untouched.").arg(n.dialogueNode)
                             :tr("Select an existing dialogue or create one, then edit it here."));
        // Keep the Visible Nodes sidebar in sync with dialogue selection.
        // This is presentation only: dialogue IDs still belong to .sbgm.
        const QString key=dialogueCardId(id);
        for (int i=0;i<m_list->count();++i) {
            QListWidgetItem *item=m_list->item(i);
            if (item->data(Qt::UserRole).toString()!=key)continue;
            const QString owner=n.name;
            if (valid) {
                const QString preview=d.value(QStringLiteral("text")).toString().simplified();
                item->setText(tr("Show Dialogue: %1  (#%2)").arg(owner).arg(n.dialogueNode));
                item->setToolTip(tr("%1 → Dialogue #%2: %3")
                    .arg(owner).arg(n.dialogueNode).arg(preview));
            } else {
                item->setText(tr("Show Dialogue: %1  (unlinked)").arg(owner));
                item->setToolTip(tr("Unlinked Show Dialogue card for %1").arg(owner));
            }
            break;
        }
    }
    void editDialogueText(const QString &id,const QString &field,const QString &value) {
        if (!m_objects.contains(id))return;
        const int index=m_objects.value(id).dialogueNode;
        if (index<0 || index>=m_dialogues.size())return;
        QJsonObject node=m_dialogues.at(index).toObject();
        const QString next=field==QStringLiteral("speaker")?value.left(36):value.left(2048);
        if (node.value(field).toString()==next)return;
        node.insert(field,next);
        m_dialogues.replace(index,node);
        m_dialoguesChanged=true;m_dirty=true;
        // Another Trigger may reference the same dialogue. Refresh its card,
        // but never overwrite the active editor's cursor or selection.
        for (const QString &other:m_dialogueCards)
            if (other!=id && m_objects.value(other).dialogueNode==index)
                refreshDialogueCard(other);
        for (const QString &owner:m_order) {
            const NodeObject n=m_objects.value(owner);
            if (n.toggleTrueDialogueNode==index)refreshBranchCard(owner,true);
            if (n.toggleFalseDialogueNode==index)refreshBranchCard(owner,false);
        }
    }
    void applyWireFocus() {
        // A removed or rerouted wire must not leave the rest of the canvas
        // permanently dimmed after the selected connection disappears.
        if (!m_selectedWireKey.isEmpty()) {
            bool exists=false;
            for (QGraphicsPathItem *wire:m_lines)
                if(wire && wire->data(6).toString()==m_selectedWireKey) {exists=true;break;}
            if(!exists)m_selectedWireKey.clear();
        }
        QSet<QString> focusedCards=m_multiSelectedCards;
        if(!m_selectedCardId.isEmpty())focusedCards.insert(m_selectedCardId);
        const bool focused=!focusedCards.isEmpty() || !m_selectedWireKey.isEmpty();
        QSet<QString> emphasisedCards=focusedCards;
        for (QGraphicsPathItem *wire:m_lines) {
            if (!wire)continue;
            if (!wire->data(8).isValid())wire->setData(8,QVariant::fromValue(wire->pen()));
            const QPen original=wire->data(8).value<QPen>();
            const bool selected=!m_selectedWireKey.isEmpty() &&
                wire->data(6).toString()==m_selectedWireKey;
            const bool incident=focusedCards.contains(wire->data(4).toString()) ||
                focusedCards.contains(wire->data(5).toString());
            const bool active=selected || incident;
            QPen pen=original;
            if(active) {
                pen.setWidthF(qMax(3.7,original.widthF()+2.0));
                emphasisedCards.insert(wire->data(4).toString());
                emphasisedCards.insert(wire->data(5).toString());
            }
            wire->setPen(pen);
            wire->setOpacity(!focused || active?1.0:0.12);
            // Keep bright wires above other wires, never above a node card.
            wire->setZValue(active?0.8:0.0);
        }
        for(auto it=m_cards.cbegin();it!=m_cards.cend();++it) {
            NodeCard *card=it.value();
            if(!card)continue;
            if(!card->data(9).isValid())card->setData(9,QVariant::fromValue(card->pen()));
            QPen pen=card->data(9).value<QPen>();
            const bool related=emphasisedCards.contains(it.key());
            if(related) {
                pen.setColor(focusedCards.contains(it.key())?QColor(252,223,145):QColor(137,208,249));
                pen.setWidthF(2.8);
            }
            card->setPen(pen);
            // Fade the entire unrelated card (including its proxy controls),
            // never disable it: a dim card remains clickable to change focus.
            // No selection restores every node to full opacity.
            card->setOpacity(focused && !related ? 0.24 : 1.0);
        }
    }
    void updateLiveWires(const QString &id,NodeCard *card) {
        if (!card)return;
        const QPointF now=card->pos();
        const QPointF previous=m_liveWirePositions.value(id,now);
        m_positions.insert(id,now);
        const QPointF delta=now-previous;
        if (qFuzzyIsNull(delta.x()) && qFuzzyIsNull(delta.y()))return;
        m_dirty=true;
        m_liveWirePositions.insert(id,now);
        m_liveWireDrag=true;
        // Keep the visible frame snug around moved conversation/GIVE cards.
        // This is a cheap geometry pass: do not recreate any wires here.
        if(!m_movingFlowGroup && (id.startsWith(QStringLiteral("@conversation:")) ||
                                  id.startsWith(QStringLiteral("@give:"))))
            updateConversationFlowGroups();

        // Wires have already been created by redrawLinks(). During a drag
        // merely shift the affected endpoint and the matching cubic handle.
        // This follows the card synchronously on EVERY ItemPositionHasChanged
        // event, while avoiding deletion/recreation of the entire wire graph.
        const auto attached=m_liveWiresByCard.value(id);
        for (QGraphicsPathItem *wire:attached) {
            if (!wire || wire->scene()!=m_scene)continue;
            const bool source=wire->data(4).toString()==id;
            const bool destination=wire->data(5).toString()==id;
            if (!source && !destination)continue;
            QPainterPath path=wire->path();
            const int count=path.elementCount();
            if (count<2)continue;
            if (source && destination) {
                // An intentional self-loop moves WITH its entire card.
                path.translate(delta);
            } else {
                if (source) {
                    const auto start=path.elementAt(0);
                    path.setElementPositionAt(0,start.x+delta.x(),start.y+delta.y());
                    if (count>1 && path.elementAt(1).type==QPainterPath::CurveToElement) {
                        const auto control=path.elementAt(1);
                        path.setElementPositionAt(1,control.x+delta.x(),control.y+delta.y());
                    }
                }
                if (destination) {
                    const int end=count-1;
                    const auto last=path.elementAt(end);
                    path.setElementPositionAt(end,last.x+delta.x(),last.y+delta.y());
                    if (end>0 && path.elementAt(end-1).type==QPainterPath::CurveToDataElement) {
                        const auto control=path.elementAt(end-1);
                        path.setElementPositionAt(end-1,control.x+delta.x(),control.y+delta.y());
                    }
                }
            }
            wire->setPath(path);
        }
        // Usually the existing 900px canvas margin suffices. Only enlarge
        // the scrollable scene if a card actually leaves its current bounds.
        if (m_scene && !m_scene->sceneRect().contains(card->sceneBoundingRect()))
            updateCanvasBounds();
    }

    void redrawLinks() {
        // A shared Show Dialogue target can be changed or deleted independently.
        // Restore the source branch's owned card if its display route is stale.
        // Authored .sbgm actions never depend on the .vsgm layout hints.
        for(const QString &owner:m_order) {
            const NodeObject trigger=m_objects.value(owner);
            if(trigger.logicNodes.isEmpty())continue;
            for(const QJsonValue &v:trigger.logicNodes) {
                const QJsonObject node=v.toObject();
                const QString key=graphKey(owner,node.value(QStringLiteral("id")).toString());
                for(bool yes:{true,false}) {
                    const int dialogue=node.value(yes?QStringLiteral("trueDialogueNode"):
                        QStringLiteral("falseDialogueNode")).toInt(-1);
                    if(dialogue<0)continue;
                    const QString own=graphDialogueKey(key,yes);
                    const QString source=QStringLiteral("@graphbranch:")+
                        (yes?QStringLiteral("true:"):QStringLiteral("false:"))+key;
                    if(!m_cards.contains(own) && !validSharedGraphDialogue(own,dialogue) &&
                       !npcRoutePoint(source,dialogue)) {
                        m_graphDialogueRoutes.remove(own);
                        makeGraphDialogueCard(key,yes);
                    }
                }
            }
        }
        // Reconcile each numbered logic input socket before calculating wire
        // endpoints. Adding/removing a .sbgm input changes only this UI geometry.
        for(const QString &cardId:m_cards.keys())
            if(cardId.startsWith(QStringLiteral("@graph:")))syncGraphCardSockets(cardId);
        // NPC preview wires can terminate at collapsed group headers. Refresh
        // those header bounds BEFORE constructing wires, not afterwards.
        updateConversationFlowGroups();
        // Standard socket geometry for every node: squares exactly on the
        // left border, circles exactly on the right border. For editable
        // cards, align sockets to the FINAL Qt control rows, never provisional
        // construction-time heights. Collapsed ports keep their own stack.
        for(auto it=m_cards.cbegin();it!=m_cards.cend();++it) {
            NodeCard *card=it.value();
            if(!card || card->collapsed())continue;
            QGraphicsProxyWidget *proxy=nullptr;
            for(QGraphicsItem *child:card->childItems()) {
                proxy=dynamic_cast<QGraphicsProxyWidget*>(child);
                if(proxy)break;
            }
            QWidget *panel=proxy?proxy->widget():nullptr;
            QHash<int,qreal> answerCentres;
            QHash<int,qreal> giveCentres;
            QHash<QString,qreal> npcCentres;
            qreal speechCentre=-1.0;
            if(panel) {
                for(QLineEdit *edit:panel->findChildren<QLineEdit*>()) {
                    if(!edit->property("conversationAnswerIndex").isValid())continue;
                    const QRectF row=proxy->subWidgetRect(edit);
                    if(!row.isEmpty())answerCentres.insert(
                        edit->property("conversationAnswerIndex").toInt(),
                        proxy->pos().y()+row.center().y());
                }
                for(QPlainTextEdit *edit:panel->findChildren<QPlainTextEdit*>()) {
                    if(!edit->property("conversationSpeechInput").toBool())continue;
                    const QRectF row=proxy->subWidgetRect(edit);
                    if(!row.isEmpty())speechCentre=proxy->pos().y()+row.center().y();
                }
                for(QComboBox *combo:panel->findChildren<QComboBox*>()) {
                    const QRectF row=proxy->subWidgetRect(combo);
                    if(row.isEmpty())continue;
                    const qreal centre=proxy->pos().y()+row.center().y();
                    if(combo->property("giveRouteBranch").isValid())
                        giveCentres.insert(combo->property("giveRouteBranch").toInt(),centre);
                    if(combo->property("npcDialogueInputSlot").isValid())
                        npcCentres.insert(combo->property("npcDialogueInputSlot").toString(),centre);
                }
            }
            for(QGraphicsItem *child:card->childItems()) {
                const QString kind=child->data(0).toString();
                auto *circle=dynamic_cast<QGraphicsEllipseItem*>(child);
                auto *square=dynamic_cast<QGraphicsRectItem*>(child);
                const bool output=kind==QStringLiteral("output") ||
                    kind==QStringLiteral("enemy-action-output") ||
                    kind==QStringLiteral("conversation-output") ||
                    kind==QStringLiteral("conversation-missing-output") ||
                    kind==QStringLiteral("exchange-output") ||
                    kind==QStringLiteral("give-anchor");
                const bool input=kind==QStringLiteral("input") ||
                    kind==QStringLiteral("npc-input") ||
                    kind==QStringLiteral("conversation-input") ||
                    kind==QStringLiteral("exchange-input");
                if(output && circle) {
                    const QRectF r=circle->rect();
                    qreal cy=r.center().y();
                    if(kind==QStringLiteral("exchange-output") &&
                       giveCentres.contains(child->data(2).toInt()))
                        cy=giveCentres.value(child->data(2).toInt());
                    else if((kind==QStringLiteral("conversation-output") ||
                             kind==QStringLiteral("conversation-missing-output") ||
                             kind==QStringLiteral("give-anchor")) &&
                            answerCentres.contains(child->data(2).toInt())) {
                        const int option=child->data(2).toInt();
                        const qreal centre=answerCentres.value(option);
                        bool hasGive=false,hasMissing=false;
                        for(QGraphicsItem *other:card->childItems()) {
                            if(other->data(2).toInt()!=option)continue;
                            const QString role=other->data(0).toString();
                            hasGive|=role==QStringLiteral("give-anchor");
                            hasMissing|=role==QStringLiteral("conversation-missing-output");
                        }
                        // Pitch of 15px gives each 13px circle a clean gap.
                        if(hasGive && hasMissing)
                            cy=centre+(kind==QStringLiteral("give-anchor")?-15.0:
                                 kind==QStringLiteral("conversation-missing-output")?0.0:15.0);
                        else if(hasGive || hasMissing)
                            cy=centre+(kind==QStringLiteral("conversation-output")?7.5:-7.5);
                        else cy=centre;
                    }
                    if(qAbs(r.center().x()-card->rect().right())>.25 ||
                       qAbs(r.center().y()-cy)>.25)
                        circle->setRect(QRectF(card->rect().right()-r.width()*.5,
                                               cy-r.height()*.5,r.width(),r.height()));
                } else if(input && square) {
                    const QRectF r=square->rect();
                    qreal cy=r.center().y();
                    if(kind==QStringLiteral("conversation-input") && speechCentre>=0.0)
                        cy=speechCentre;
                    else if(kind==QStringLiteral("npc-input") &&
                            npcCentres.contains(child->data(2).toString()))
                        cy=npcCentres.value(child->data(2).toString());
                    if(qAbs(r.center().x()-card->rect().left())>.25 ||
                       qAbs(r.center().y()-cy)>.25)
                        square->setRect(QRectF(card->rect().left()-r.width()*.5,
                                               cy-r.height()*.5,r.width(),r.height()));
                }
            }
        }
        m_liveWiresByCard.clear();
        for (QGraphicsPathItem *item:m_lines) {m_scene->removeItem(item);delete item;}
        m_lines.clear();
        for (const QString &id:m_order) {
            const NodeObject node=m_objects.value(id);
            if (!isActionSource(node) && eventKinds(node.type).isEmpty()) continue;
            NodeCard *from=m_cards.value(id,nullptr);
            if (!from || !from->isVisible())continue;
            for (int i=0;i<node.links.size();++i) {
                const NodeLink link=node.links.at(i);
                NodeCard *to=m_cards.value(link.target,nullptr);
                if (!to || !supportedAction(link.action))continue;
                const QPointF a=from->wirePoint(QPointF(node.type==QStringLiteral("trigger")?280:224,
                    node.type==QStringLiteral("enemy")?90:58));
                const QPointF b=to->wirePoint(QPointF(0,58));
                const qreal bend=qMax(55.0,qAbs(b.x()-a.x())*.5);
                // Fan out multiple actions to the same target so both remain
                // visibly separate and individually selectable.
                int matching=0,ordinal=0;
                for (int j=0;j<node.links.size();++j) {
                    if (node.links[j].target!=link.target || !supportedAction(node.links[j].action))continue;
                    if (j<i)++ordinal;
                    ++matching;
                }
                const qreal offset=(ordinal-(matching-1)*0.5)*42.0;
                QPainterPath path(a);
                path.cubicTo(a+QPointF(bend,offset),b+QPointF(-bend,offset),b);
                auto *wire=new NodeWire(path,QPen(link.action==QStringLiteral("enable")
                    ? QColor(108,211,159) : link.action==QStringLiteral("disable")
                    ? QColor(245,127,126) : QColor(238,202,113),3));
                m_scene->addItem(wire);
                wire->setData(0,QStringLiteral("link"));wire->setData(1,id);wire->setData(2,i);
                wire->setData(4,id);wire->setData(5,link.target);
                wire->setToolTip(tr("%1 → %2: %3 (right-click to edit or remove)")
                    .arg(node.name,m_objects.value(link.target).name,link.action));
                wire->setZValue(0);
                m_lines.append(wire);
            }
            const QStringList kinds=eventKinds(node.type);
            for(int eventIndex=0;eventIndex<kinds.size();++eventIndex) {
                const QString key=kinds.at(eventIndex);
                const QVector<NodeLink> &links=node.eventLinks.value(key);
                for(int linkIndex=0;linkIndex<links.size();++linkIndex) {
                    const NodeLink link=links.at(linkIndex);
                    NodeCard *to=m_cards.value(link.target,nullptr);
                    if(!to || !supportedAction(link.action))continue;
                    const qreal y=(node.type==QStringLiteral("enemy")?117.5:88.5)+eventIndex*29.0;
                    const QPointF a=from->wirePoint(QPointF(224,y));
                    const QPointF b=to->wirePoint(QPointF(0,58));
                    const qreal bend=qMax(55.0,qAbs(b.x()-a.x())*.5);
                    QPainterPath path(a);
                    path.cubicTo(a+QPointF(bend,0),b-QPointF(bend,0),b);
                    auto *wire=new NodeWire(path,QPen(link.action==QStringLiteral("enable")
                        ?QColor(108,211,159):link.action==QStringLiteral("disable")
                        ?QColor(245,127,126):QColor(238,202,113),3));
                    m_scene->addItem(wire);
                    wire->setData(0,QStringLiteral("event-link"));
                    wire->setData(1,eventOutput(key,id));wire->setData(2,linkIndex);
                    wire->setData(4,id);wire->setData(5,link.target);
                    wire->setToolTip(tr("%1: %2 → %3 (%4)")
                        .arg(eventLabel(key),node.name,m_objects.value(link.target).name,link.action));
                    wire->setZValue(0);m_lines.append(wire);
                }
            }
            if (node.type!=QStringLiteral("trigger"))continue;
            if (m_cards.contains(toggleCardId(id))) {
                QStringList sources{node.toggleStateTargetId};
                if (node.toggleStateOperator!=QStringLiteral("boolean"))
                    sources.append(node.toggleStateInputIds);
                for (int input=0;input<sources.size();++input) {
                    const QString sourceId=sources.at(input);
                    if (!m_cards.contains(sourceId))continue;
                    NodeCard *source=m_cards.value(sourceId);
                    NodeCard *to=m_cards.value(toggleCardId(id));
                    const QPointF a=source->wirePoint(QPointF(224,58));
                    const QRectF target=to->sceneBoundingRect();
                    const bool targetOnLeft=target.center().x()<a.x();
                    const QPointF b=to->wirePoint(QPointF(0,58));
                    const qreal bend=qMax(48.0,qMin(150.0,qAbs(b.x()-a.x())*.45));
                    QPainterPath path(a);
                    path.cubicTo(a+QPointF(bend,0),b+QPointF(targetOnLeft?bend:-bend,0),b);
                    auto *wire=new NodeWire(path,QPen(QColor(123,201,192),3));
                    wire->setData(0,QStringLiteral("state-link"));
                    wire->setData(1,id);wire->setData(2,input);
                    wire->setData(4,sourceId);wire->setData(5,toggleCardId(id));
                    wire->setToolTip(tr("%1 state → %2 (%3; right-click to disconnect)")
                        .arg(m_objects.value(sourceId).name,node.toggleStateOperator,node.name));
                    m_scene->addItem(wire);m_lines.append(wire);
                }
            }
            if (m_cards.contains(toggleCardId(id)))for (const bool yes:{true,false}) {
                const int index=yes?node.toggleTrueDialogueNode:node.toggleFalseDialogueNode;
                NodeCard *state=m_cards.value(toggleCardId(id));
                NodeCard *to=m_cards.value(branchCardId(id,yes),nullptr);
                QPointF b;
                const QString source=QStringLiteral("@stateout:")+
                    (yes?QStringLiteral("true:"):QStringLiteral("false:"))+id;
                const bool routed=npcRoutePoint(source,index,&b);
                if (index<0 || (!routed && !to))continue;
                const QPointF a=state->wirePoint(QPointF(294,yes?115:146));
                if(!routed)b=to->wirePoint(QPointF(0,57));
                const qreal bend=qMax(48.0,qAbs(b.x()-a.x())*.45);
                QPainterPath path(a);path.cubicTo(a+QPointF(bend,0),b-QPointF(bend,0),b);
                auto *wire=new NodeWire(path,QPen(yes?QColor(111,222,167):QColor(244,145,146),3));
                wire->setData(0,(yes?QStringLiteral("state-true-link"):QStringLiteral("state-false-link")));
                wire->setData(1,id);wire->setData(4,toggleCardId(id));
                wire->setData(5,routed?m_npcDialogueRoutes.value(source).value(QStringLiteral("npc")).toString():branchCardId(id,yes));
                wire->setToolTip(tr("%1 dialogue #%2 (right-click to disconnect)")
                    .arg(yes?tr("TRUE"):tr("FALSE")).arg(index));
                m_scene->addItem(wire);m_lines.append(wire);
            }
            if (m_cards.contains(toggleCardId(id)))for (const bool yes:{true,false}) {
                const QVector<NodeLink> &links=yes?node.toggleTrueActions:node.toggleFalseActions;
                NodeCard *state=m_cards.value(toggleCardId(id));
                for (int i=0;i<links.size();++i) {
                    const NodeLink link=links.at(i);
                    NodeCard *to=m_cards.value(link.target,nullptr);
                    if (!to || !supportedAction(link.action))continue;
                    const QPointF a=state->wirePoint(QPointF(294,yes?115:146));
                    const QPointF b=to->wirePoint(QPointF(0,58));
                    const qreal bend=qMax(55.0,qAbs(b.x()-a.x())*.5);
                    int matching=0,ordinal=0;
                    for (int j=0;j<links.size();++j) {
                        if (links[j].target!=link.target || !supportedAction(links[j].action))continue;
                        if (j<i)++ordinal;
                        ++matching;
                    }
                    const qreal offset=(ordinal-(matching-1)*.5)*40.0;
                    QPainterPath path(a);
                    path.cubicTo(a+QPointF(bend,offset),b+QPointF(-bend,offset),b);
                    const QColor color=link.action==QStringLiteral("enable")?QColor(108,211,159):
                        link.action==QStringLiteral("disable")?QColor(245,127,126):QColor(238,202,113);
                    auto *wire=new NodeWire(path,QPen(color,3));
                    wire->setData(0,yes?QStringLiteral("state-true-action"):QStringLiteral("state-false-action"));
                    wire->setData(1,id);wire->setData(2,i);
                    wire->setData(4,toggleCardId(id));wire->setData(5,link.target);
                    wire->setToolTip(tr("%1 branch → %2: %3 (right-click to edit/remove)")
                        .arg(yes?tr("TRUE"):tr("FALSE"),m_objects.value(link.target).name,link.action));
                    wire->setZValue(0);m_scene->addItem(wire);m_lines.append(wire);
                }
            }
            if (node.dialogueNode>=0) {
                QPointF npcPoint;
                const bool routed=npcRoutePoint(id,node.dialogueNode,&npcPoint);
                NodeCard *to=m_cards.value(dialogueCardId(id),nullptr);
                if (routed || (to && m_dialogueCards.contains(id))) {
                    // Purple dialogue links use the same smooth cubic curves
                    // as red/green action links. Never route dialogue wires
                    // with a square detour over the tops of the cards.
                    const QPointF a=from->wirePoint(QPointF(280,58));
                    const QPointF b=routed?npcPoint:to->wirePoint(QPointF(0,57));
                    const QPainterPath path=smoothNodeCurve(a,b);
                    auto *wire=new NodeWire(path,QPen(QColor(199,149,248),3));
                    wire->setData(0,QStringLiteral("dialogue-link"));
                    wire->setData(1,id);
                    wire->setData(4,id);
                    wire->setData(5,routed?m_npcDialogueRoutes.value(id).value(QStringLiteral("npc")).toString():dialogueCardId(id));
                    wire->setToolTip(tr("Show dialogue %1 (right-click to disconnect)")
                        .arg(node.dialogueNode));
                    wire->setZValue(0);m_scene->addItem(wire);m_lines.append(wire);
                }
            }
        }
        redrawGraphLinks();
        // Conversation-choice edges mirror the real Adventure `next` and
        // `missingNext` fields. The drawn wires have no action context menu,
        // but dragging their source sockets updates those fields directly.
        for (const QString &id:m_cards.keys()) {
            if (!id.startsWith(QStringLiteral("@conversation:")))continue;
            bool indexOk=false;
            const int index=id.mid(QStringLiteral("@conversation:").size()).toInt(&indexOk);
            if(!indexOk || index<0 || index>=m_dialogues.size())continue;
            NodeCard *source=m_cards.value(id);
            if(!source || !source->isVisible())continue;
            const QJsonArray choices=m_dialogues.at(index).toObject()
                .value(QStringLiteral("choices")).toArray();
            for(int option=0;option<choices.size();++option) {
                const QJsonObject choice=choices.at(option).toObject();
                if(choice.value(QStringLiteral("text")).toString().trimmed().isEmpty())continue;
                const int next=choice.value(QStringLiteral("next")).toInt(-1);
                NodeCard *target=m_cards.value(conversationCardId(next),nullptr);
                if(!target || !target->isVisible())continue; // Close, missing IDs, or unimported nodes.
                QPointF a;
                for(QGraphicsItem *child:source->childItems())
                    if(child->data(0).toString()==QStringLiteral("conversation-output") &&
                       child->data(2).toInt()==option) {
                        // Use this exact output socket, not a Y-coordinate lookup.
                        // On first load a collapsed card has not yet computed
                        // its expanded rows, so multiple sockets can share
                        // the same provisional rect().center().y().
                        auto *port=static_cast<QGraphicsEllipseItem*>(child);
                        a=port->sceneBoundingRect().center();
                        break;
                    }
                if(a.isNull())continue;
                const QPointF b=target->wirePoint(QPointF(0,110));
                const QPainterPath path=(next==index)?
                    conversationSelfLoopCurve(a,b,source->sceneBoundingRect(),option,false):
                    smoothNodeCurve(a,b);
                auto *wire=new NodeWire(path,QPen(QColor(186,133,227),2.5));
                wire->setData(0,QStringLiteral("conversation-next-wire"));
                wire->setData(1,id);wire->setData(2,option);
                wire->setData(4,id);wire->setData(5,conversationCardId(next));
                wire->setToolTip(tr("PURPLE · NORMAL ANSWER ROUTE\nDialogue #%1, answer %2 → dialogue #%3.\nRuns when the answer succeeds (and its required item is owned, if any).\nDrag the purple socket or edit 'Next' to change this destination. Right-click this wire to disconnect it.")
                    .arg(index).arg(option+1).arg(next));
                wire->setZValue(0);m_scene->addItem(wire);m_lines.append(wire);
            }
            // A missing-item branch is a separate alternate route, drawn
            // dashed amber so it cannot be mistaken for the regular answer.
            for(int option=0;option<choices.size();++option) {
                const QJsonObject choice=choices.at(option).toObject();
                if(choice.value(QStringLiteral("text")).toString().trimmed().isEmpty() ||
                   choice.value(QStringLiteral("requires")).toInt(-1)<0)continue;
                const int missing=choice.value(QStringLiteral("missingNext")).toInt(-1);
                NodeCard *target=m_cards.value(conversationCardId(missing),nullptr);
                if(!target || !target->isVisible())continue;
                QPointF a;
                for(QGraphicsItem *child:source->childItems())
                    if(child->data(0).toString()==QStringLiteral("conversation-missing-output") &&
                       child->data(2).toInt()==option) {
                        // Use this exact output socket, not a Y-coordinate lookup.
                        // On first load a collapsed card has not yet computed
                        // its expanded rows, so multiple sockets can share
                        // the same provisional rect().center().y().
                        auto *port=static_cast<QGraphicsEllipseItem*>(child);
                        a=port->sceneBoundingRect().center();
                        break;
                    }
                if(a.isNull())continue;
                const QPointF b=target->wirePoint(QPointF(0,110));
                const QPainterPath path=(missing==index)?
                    conversationSelfLoopCurve(a,b,source->sceneBoundingRect(),option,true):
                    smoothNodeCurve(a,b);
                auto *wire=new NodeWire(path,QPen(QColor(233,177,98),2,Qt::DashLine));
                wire->setData(0,QStringLiteral("conversation-missing-wire"));
                wire->setData(1,id);wire->setData(2,option);
                wire->setData(4,id);wire->setData(5,conversationCardId(missing));
                wire->setToolTip(tr("AMBER DASHED · REQUIRED ITEM MISSING\nDialogue #%1, answer %2 → dialogue #%3.\nRuns only when the player does NOT own item #%4.\nDrag the amber socket or edit 'No item' to change this destination. Right-click this wire to disconnect it.")
                    .arg(index).arg(option+1).arg(missing)
                    .arg(choice.value(QStringLiteral("requires")).toInt(-1)));
                wire->setZValue(0);m_scene->addItem(wire);m_lines.append(wire);
            }
        }
        // A GIVE exchange is authored on an Adventure dialogue answer. Its
        // own graph card exposes all existing wrong-item response branches.
        for(const QString &id:m_cards.keys()) {
            int sourceIndex=-1,option=-1;
            if(!giveCardReference(id,&sourceIndex,&option))continue;
            NodeCard *exchangeCard=m_cards.value(id,nullptr);
            NodeCard *dialogueCard=m_cards.value(conversationCardId(sourceIndex),nullptr);
            if(!exchangeCard || !exchangeCard->isVisible() || !dialogueCard || !dialogueCard->isVisible())continue;
            QPointF from;
            for(QGraphicsItem *child:dialogueCard->childItems())
                if(child->data(0).toString()==QStringLiteral("give-anchor") &&
                   child->data(2).toInt()==option) {
                    auto *circle=dynamic_cast<QGraphicsEllipseItem*>(child);
                    if(circle)from=circle->sceneBoundingRect().center();
                    break;
                }
            if(!from.isNull()) {
                const QPointF to=exchangeCard->wirePoint(QPointF(0,56));
                auto *wire=new NodeWire(smoothNodeCurve(from,to),QPen(QColor(80,196,180),2,Qt::DashLine));
                wire->setData(0,QStringLiteral("give-preview-wire"));
                wire->setData(1,id);wire->setData(2,option);
                wire->setData(4,conversationCardId(sourceIndex));wire->setData(5,id);
                wire->setToolTip(tr("GIVE EXCHANGE · Dialogue #%1 answer %2\nThis inventory exchange already exists in Adventure Editor; this card edits its response destinations.")
                    .arg(sourceIndex).arg(option+1));
                wire->setZValue(0);m_scene->addItem(wire);m_lines.append(wire);
            }
            const QJsonObject exchange=giveExchange(sourceIndex,option);
            const int count=exchange.value(QStringLiteral("wrongRepeatEnabled")).toBool(false)?5:1;
            for(int branch=0;branch<count;++branch) {
                const int targetIndex=exchange.value(giveRouteKey(branch)).toInt(-1);
                NodeCard *target=m_cards.value(conversationCardId(targetIndex),nullptr);
                if(!target || !target->isVisible())continue;
                QPointF a;
                for(QGraphicsItem *child:exchangeCard->childItems())
                    if(child->data(0).toString()==QStringLiteral("exchange-output") &&
                       child->data(2).toInt()==branch) {
                        auto *circle=dynamic_cast<QGraphicsEllipseItem*>(child);
                        if(circle)a=circle->sceneBoundingRect().center();
                        break;
                    }
                if(a.isNull())continue;
                const QPointF b=target->wirePoint(QPointF(0,110));
                const QColor colour=branch==0?QColor(241,149,117):QColor(244,194,107);
                auto *wire=new NodeWire(smoothNodeCurve(a,b),QPen(colour,2.5,Qt::DashLine));
                wire->setData(0,QStringLiteral("give-response-wire"));
                wire->setData(1,id);wire->setData(2,branch);
                wire->setData(4,id);wire->setData(5,conversationCardId(targetIndex));
                const QString route=branch==0?tr("ANY WRONG ITEM"):
                    QStringList{tr("FIRST"),tr("SECOND"),tr("THIRD"),tr("FOURTH+")}.at(branch-1)+tr(" TRACKED WRONG ITEM");
                wire->setToolTip(tr("GIVE · %1\nDialogue #%2, answer %3 → dialogue #%4.\nChange it on the GIVE card or drag its output circle. Right-click this wire to disconnect it.")
                    .arg(route).arg(sourceIndex).arg(option+1).arg(targetIndex));
                wire->setZValue(0);m_scene->addItem(wire);m_lines.append(wire);
            }
        }
        for(const QString &npcId:m_order) {
            const NodeObject npc=m_objects.value(npcId);
            if(npc.type!=QStringLiteral("npc"))continue;
            NodeCard *source=m_cards.value(npcId,nullptr);
            if(!source || !source->isVisible())continue;
            for(const bool helped:{false,true}) {
                const int root=helped?npc.npcDoneNode:npc.npcStartNode;
                if(!m_conversationRoots.contains(root) || flowRootHidden(root))continue;
                NodeCard *target=m_cards.value(conversationCardId(root),nullptr);
                FlowGroupBox *group=m_flowGroups.value(root,nullptr);
                const bool compact=group && group->isVisible() && group->collapsed();
                if(!compact && (!target || !target->isVisible()))continue;
                const QPointF a=source->wirePoint(QPointF(344,helped?164:103));
                const QPointF b=compact?group->inputPoint():target->wirePoint(QPointF(0,110));
                const QPainterPath path=smoothNodeCurve(a,b);
                auto *wire=new NodeWire(path,QPen(QColor(146,114,179),2,Qt::DashLine));
                wire->setData(0,QStringLiteral("conversation-preview-wire"));
                wire->setData(1,npcId);wire->setData(2,helped?1:0);
                wire->setData(4,npcId);
                wire->setData(5,compact?flowGroupId(root):conversationCardId(root));
                wire->setToolTip(compact?
                    tr("NPC %1 %2 → Collapsed Conversation Flow #%3. Expand the group to see individual dialogues.")
                        .arg(npc.name,helped?tr("After helped"):tr("Opening")).arg(root):
                    tr("NPC %1 %2 → Dialogue #%3 (read-only preview)")
                        .arg(npc.name,helped?tr("After helped"):tr("Opening")).arg(root));
                wire->setZValue(0);m_scene->addItem(wire);m_lines.append(wire);
            }
        }
        // Wire identities use authored source/target and branch indexes, not
        // ephemeral QGraphicsItem pointers or curve geometry; selection survives
        // redrawLinks() while panning, moving and collapsing cards.
        for (QGraphicsPathItem *wire:m_lines) {
            const QString key=QStringLiteral("%1|%2|%3|%4|%5")
                .arg(wire->data(0).toString(),wire->data(1).toString(),
                     wire->data(2).toString(),wire->data(4).toString(),
                     wire->data(5).toString());
            wire->setData(6,key);
            const QString from=wire->data(4).toString();
            const QString to=wire->data(5).toString();
            if (m_cards.contains(from))m_liveWiresByCard[from].append(wire);
            if (to!=from && (m_cards.contains(to) || to.startsWith(QStringLiteral("@flowgroup:"))))
                m_liveWiresByCard[to].append(wire);
        }
        m_liveWirePositions.clear();
        for (auto it=m_cards.cbegin();it!=m_cards.cend();++it)
            if (it.value())m_liveWirePositions.insert(it.key(),it.value()->pos());
        m_liveWireDrag=false;
        updateSocketStates();
        applyWireFocus();
        updateConversationFlowGroups();
        updateCanvasBounds();
        scheduleVisibleTreeRefresh();
    }
    void scheduleVisibleTreeRefresh() {
        if(m_treeRefreshPending || !m_visibleTree)return;
        m_treeRefreshPending=true;
        QTimer::singleShot(0,this,[this] {
            m_treeRefreshPending=false;
            if(!m_visibleTree || !m_list)return;
            QSignalBlocker blocker(m_visibleTree);
            m_visibleTree->clear();
            QHash<QString,QTreeWidgetItem*> groups;
            const auto folder=[this,&groups](const QString &path,const QString &title,
                                              QTreeWidgetItem *parent=nullptr)->QTreeWidgetItem* {
                if(groups.contains(path))return groups.value(path);
                QTreeWidgetItem *item=parent?new QTreeWidgetItem(parent):
                    new QTreeWidgetItem(m_visibleTree);
                item->setText(0,title);
                item->setData(0,Qt::UserRole,path);
                QFont font=item->font(0);font.setBold(true);item->setFont(0,font);
                item->setExpanded(!m_treeCollapsed.contains(path));
                groups.insert(path,item);
                return item;
            };
            for(int i=0;i<m_list->count();++i) {
                QListWidgetItem *source=m_list->item(i);
                if(!source)continue;
                const QString id=source->data(Qt::UserRole).toString();
                if(id.isEmpty() || !m_cards.contains(id) ||
                   !m_cards.value(id)->isVisible())continue;
                QString path,label;
                QTreeWidgetItem *parent=nullptr;
                if(id.startsWith(QStringLiteral("@conversation:")) ||
                   id.startsWith(QStringLiteral("@give:"))) {
                    parent=folder(QStringLiteral("flows"),tr("Conversation Flows"));
                    bool found=false;
                    QList<int> roots=m_conversationRoots.values();
                    std::sort(roots.begin(),roots.end());
                    int dialogue=-1;
                    if(id.startsWith(QStringLiteral("@conversation:")))
                        dialogue=id.mid(QStringLiteral("@conversation:").size()).toInt();
                    else {int answer=-1;giveCardReference(id,&dialogue,&answer);}
                    for(int root:roots) {
                        if(!conversationReachable(root).contains(dialogue))continue;
                        path=QStringLiteral("@flowgroup:")+QString::number(root);
                        parent=folder(path,conversationFlowTitle(root),parent);
                        found=true;break;
                    }
                    if(!found)parent=folder(QStringLiteral("flows/other"),tr("Other Dialogue"),parent);
                } else if(id.startsWith(QStringLiteral("@graph:")) ||
                          id.startsWith(QStringLiteral("@toggle:"))) {
                    parent=folder(QStringLiteral("logic"),tr("Logic"));
                } else if(id.startsWith(QStringLiteral("@graph-dialogue:")) ||
                          id.startsWith(QStringLiteral("@toggle-dialogue:")) ||
                          id.startsWith(QStringLiteral("@dialogue:"))) {
                    parent=folder(QStringLiteral("actions"),tr("Dialogue Actions"));
                } else if(m_objects.contains(id)) {
                    const QString type=m_objects.value(id).type;
                    if(type==QStringLiteral("npc"))parent=folder(QStringLiteral("npcs"),tr("NPCs"));
                    else if(type==QStringLiteral("player_action"))
                        parent=folder(QStringLiteral("player"),tr("PLAYER"));
                    else {
                        parent=folder(QStringLiteral("objects"),tr("Game Objects"));
                        const QString group=type==QStringLiteral("trigger")?tr("Triggers"):
                            type==QStringLiteral("enemy")?tr("Enemies"):
                            type==QStringLiteral("collectable")?tr("Collectables"):
                            type==QStringLiteral("decoration_object")?tr("Decorations"):
                            type==QStringLiteral("platform")?tr("Platforms"):
                            type==QStringLiteral("npc_reference")?tr("Remote NPCs"):
                            type==QStringLiteral("world_reference")?tr("Remote Worlds"):
                            type.toUpper();
                        parent=folder(QStringLiteral("objects/")+type,group,parent);
                    }
                } else parent=folder(QStringLiteral("other"),tr("Other Cards"));
                auto *entry=new QTreeWidgetItem(parent);
                entry->setText(0,source->text());
                entry->setToolTip(0,source->toolTip());
                entry->setData(0,Qt::UserRole,id);
                if(id==m_selectedCardId) {
                    m_visibleTree->setCurrentItem(entry);
                }
            }
            const QString filter=m_treeSearch?m_treeSearch->text():QString();
            if(!filter.isEmpty()) {
                std::function<bool(QTreeWidgetItem*)> visit=[&](QTreeWidgetItem *item)->bool {
                    bool found=item->text(0).contains(filter,Qt::CaseInsensitive);
                    for(int c=0;c<item->childCount();++c)found=visit(item->child(c))||found;
                    item->setHidden(!found);
                    if(found && item->childCount())item->setExpanded(true);
                    return found;
                };
                for(int i=0;i<m_visibleTree->topLevelItemCount();++i)
                    visit(m_visibleTree->topLevelItem(i));
            }
        });
    }
    void refreshCardInspector(const QString &id) {
        if(!m_inspectorTree)return;
        m_inspectorTree->clear();
        const auto row=[this](const QString &name,const QString &value) {
            auto *item=new QTreeWidgetItem(m_inspectorTree,QStringList{name,value});
            item->setToolTip(1,value);
        };
        if(id.isEmpty() || !m_cards.contains(id)) {
            m_inspectorTitle->setText(tr("SELECT A NODE OR WIRE"));
            m_inspectorType->setText(tr("Choose a card to inspect its properties and connections."));
            return;
        }
        if(id.startsWith(QStringLiteral("@conversation:"))) {
            bool ok=false;
            const int index=id.mid(QStringLiteral("@conversation:").size()).toInt(&ok);
            if(ok && index>=0 && index<m_dialogues.size()) {
                const QJsonObject node=m_dialogues.at(index).toObject();
                const QJsonArray choices=node.value(QStringLiteral("choices")).toArray();
                m_inspectorTitle->setText(tr("Dialogue #%1").arg(index));
                m_inspectorType->setText(tr("Adventure conversation"));
                row(tr("Speaker"),node.value(QStringLiteral("speaker")).toString());
                row(tr("Message"),node.value(QStringLiteral("text")).toString().simplified().left(130));
                int count=0;
                for(const QJsonValue &v:choices)
                    if(!v.toObject().value(QStringLiteral("text")).toString().trimmed().isEmpty())++count;
                row(tr("Answers"),QString::number(count));
                for(int i=0;i<choices.size();++i) {
                    const QJsonObject choice=choices.at(i).toObject();
                    if(choice.value(QStringLiteral("text")).toString().trimmed().isEmpty())continue;
                    const int next=choice.value(QStringLiteral("next")).toInt(-1);
                    row(tr("Answer %1 →").arg(i+1),next<0?tr("Close"):
                        tr("Dialogue #%1").arg(next));
                    const int requires=choice.value(QStringLiteral("requires")).toInt(-1);
                    if(requires>=0)row(tr("Item required"),tr("Item #%1; missing → #%2")
                        .arg(requires).arg(choice.value(QStringLiteral("missingNext")).toInt(-1)));
                    if(choice.value(QStringLiteral("exchange")).toObject().value(QStringLiteral("enabled")).toBool(false))
                        row(tr("GIVE exchange"),tr("Answer %1 enabled").arg(i+1));
                }
                row(tr("Data source"),QStringLiteral(".sbgm / adventure.nodes"));
                return;
            }
        }
        if(id.startsWith(QStringLiteral("@give:"))) {
            int dialogue=-1,option=-1;
            if(giveCardReference(id,&dialogue,&option)) {
                const QJsonObject ex=giveExchange(dialogue,option);
                m_inspectorTitle->setText(tr("GIVE · Dialogue #%1").arg(dialogue));
                m_inspectorType->setText(tr("Inventory exchange · Answer %1").arg(option+1));
                const QJsonArray inventory=m_world.value(QStringLiteral("adventure")).toObject()
                    .value(QStringLiteral("items")).toArray();
                const auto displayItem=[&inventory](int item)->QString {
                    if(item<0)return QObject::tr("None");
                    if(item>=inventory.size())return QObject::tr("MISSING item #%1").arg(item);
                    const QString name=inventory.at(item).toObject().value(QStringLiteral("name")).toString();
                    return name.isEmpty()?QObject::tr("Item #%1").arg(item):name;
                };
                QStringList required;
                for(const QJsonValue &v:ex.value(QStringLiteral("items")).toArray())
                    required.append(displayItem(v.toInt(-1)));
                row(tr("Required items"),required.isEmpty()?tr("None selected"):
                    required.join(ex.value(QStringLiteral("logic")).toString()==QStringLiteral("any")?
                        tr(" OR "):tr(" AND ")));
                row(tr("Rule"),ex.value(QStringLiteral("logic")).toString()==QStringLiteral("any")?
                    tr("Any requested item"):tr("All requested items"));
                row(tr("Consumes items"),ex.value(QStringLiteral("consume")).toBool(true)?tr("Yes"):tr("No"));
                row(tr("Wrong item →"),QString::number(ex.value(QStringLiteral("wrongNext")).toInt(-1)));
                row(tr("Repeat tracking"),ex.value(QStringLiteral("wrongRepeatEnabled")).toBool(false)?tr("Enabled"):tr("Disabled"));
                if(ex.value(QStringLiteral("wrongRepeatEnabled")).toBool(false)) {
                    row(tr("Tracked item"),displayItem(ex.value(QStringLiteral("wrongRepeatItem")).toInt(-1)));
                    for(int b=1;b<5;++b)
                        row(tr("Attempt %1 →").arg(b==4?tr("4+"):QString::number(b)),
                            QString::number(ex.value(giveRouteKey(b)).toInt(-1)));
                }
                row(tr("Data source"),QStringLiteral(".sbgm / exchange"));
                return;
            }
        }
        if(id.startsWith(QStringLiteral("@graph:"))) {
            QString owner;QJsonObject node;
            if(lookupGraph(id,&owner,nullptr,&node)) {
                m_inspectorTitle->setText(node.value(QStringLiteral("id")).toString());
                m_inspectorType->setText(tr("Independent logic"));
                row(tr("Operator"),node.value(QStringLiteral("op")).toString().toUpper());
                row(tr("Inputs"),QString::number(node.value(QStringLiteral("inputs")).toArray().size()));
                row(tr("Game Object"),m_objects.value(owner).name);
                row(tr("Data source"),QStringLiteral(".sbgm / logic"));
                return;
            }
        }
        if(id.startsWith(QStringLiteral("@toggle:"))) {
            const NodeObject node=m_objects.value(id.mid(QStringLiteral("@toggle:").size()));
            m_inspectorTitle->setText(node.name);
            m_inspectorType->setText(tr("Boolean / logic state"));
            row(tr("Operator"),node.toggleStateOperator.toUpper());
            row(tr("Inputs"),QString::number((node.toggleStateTargetId.isEmpty()?0:1)+node.toggleStateInputIds.size()));
            row(tr("TRUE actions"),QString::number(node.toggleTrueActions.size()));
            row(tr("FALSE actions"),QString::number(node.toggleFalseActions.size()));
            return;
        }
        if(id.startsWith(QStringLiteral("@dialogue:"))) {
            const QString owner=id.mid(QStringLiteral("@dialogue:").size());
            const NodeObject node=m_objects.value(owner);
            m_inspectorTitle->setText(tr("Show Dialogue"));
            m_inspectorType->setText(tr("Dialogue action · %1").arg(node.name));
            row(tr("Conversation"),npcDialogueTitle(node.dialogueNode));
            row(tr("Playback"),node.dialogueMode);
            row(tr("Data source"),QStringLiteral(".sbgm"));
            return;
        }
        if(id.startsWith(QStringLiteral("@toggle-dialogue:"))) {
            const bool yes=id.startsWith(QStringLiteral("@toggle-dialogue:true:"));
            const QString prefix=yes?QStringLiteral("@toggle-dialogue:true:"):
                QStringLiteral("@toggle-dialogue:false:");
            const NodeObject node=m_objects.value(id.mid(prefix.size()));
            m_inspectorTitle->setText(tr("Show Dialogue · %1").arg(yes?tr("TRUE"):tr("FALSE")));
            m_inspectorType->setText(tr("Logic dialogue action"));
            row(tr("Trigger"),node.name);
            row(tr("Conversation"),npcDialogueTitle(yes?node.toggleTrueDialogueNode:node.toggleFalseDialogueNode));
            row(tr("Data source"),QStringLiteral(".sbgm"));
            return;
        }
        if(id.startsWith(QStringLiteral("@graph-dialogue:"))) {
            m_inspectorTitle->setText(tr("Show Dialogue"));
            m_inspectorType->setText(tr("Independent logic dialogue action"));
            row(tr("Card"),id.section(QLatin1Char(':'),-1));
            row(tr("Data source"),QStringLiteral(".sbgm"));
            return;
        }
        if(m_objects.contains(id)) {
            const NodeObject node=m_objects.value(id);
            m_inspectorTitle->setText(node.name);
            m_inspectorType->setText(node.type.toUpper().replace(QLatin1Char('_'),QLatin1Char(' ')));
            row(tr("Game object"),node.name);
            if(node.type==QStringLiteral("trigger")) {
                row(tr("Requires FIRE2"),node.triggerPress?tr("Yes"):tr("No"));
                row(tr("Remove after use"),node.triggerOneShot?tr("Yes"):tr("No"));
                row(tr("Inventory item"),node.interactItemName.isEmpty()?tr("None"):node.interactItemName);
            }
            if(node.type==QStringLiteral("npc")) {
                row(tr("Opening dialogue"),npcDialogueTitle(node.npcStartNode));
                row(tr("After helped"),node.npcDoneNode<0?tr("Uses opening"):npcDialogueTitle(node.npcDoneNode));
                row(tr("Talk radius"),tr("%1 px").arg(node.npcRadius));
                row(tr("Initially visible"),node.npcInitiallyVisible?tr("Yes"):tr("No"));
            }
            if(isActionSource(node)) {
                row(tr("Linked actions"),QString::number(node.links.size()));
                if(node.dialogueNode>=0)row(tr("Show Dialogue"),npcDialogueTitle(node.dialogueNode));
            }
            row(tr("Data source"),QStringLiteral(".sbgm"));
            return;
        }
        m_inspectorTitle->setText(m_cards.value(id)->data(1).toString());
        m_inspectorType->setText(tr("Graph action card"));
        row(tr("Node"),id);
        row(tr("Status"),tr("Editable on the card"));
    }
    void showDetails(const QString &id) {
        refreshCardInspector(id);
        const bool actionsVisible=(m_objects.contains(id) &&
            (isActionSource(m_objects.value(id)) || !eventKinds(m_objects.value(id).type).isEmpty())) ||
            id.startsWith(QStringLiteral("@toggle:"));
        if(m_actionsHeader)m_actionsHeader->setVisible(actionsVisible);
        if(m_linksList)m_linksList->setVisible(actionsVisible);
        if(m_editLinkButton)m_editLinkButton->setVisible(actionsVisible);
        if(m_removeLinkButton)m_removeLinkButton->setVisible(actionsVisible);
        m_selectedWireKey.clear();
        m_selectedCardId=id;
        applyWireFocus();
        m_removeSelectedButton->setEnabled(m_cards.contains(id));
        if (id.isEmpty()) {
            m_details->clear();m_linksList->clear();
            m_linksList->setEnabled(false);
            m_editLinkButton->setEnabled(false);m_removeLinkButton->setEnabled(false);
            return;
        }
        if(id.startsWith(QStringLiteral("@give:"))) {
            m_linksList->clear();m_linksList->setEnabled(false);
            m_editLinkButton->setEnabled(false);m_removeLinkButton->setEnabled(false);
            int dialogue=-1,answer=-1;
            if(giveCardReference(id,&dialogue,&answer)) {
                const QJsonObject ex=giveExchange(dialogue,answer);
                QString details=tr("EXISTING NPC GIVE EXCHANGE\n\nDialogue #%1 · Answer %2\n\n")
                    .arg(dialogue).arg(answer+1);
                details+=tr("General wrong item → %1\n")
                    .arg(ex.value(QStringLiteral("wrongNext")).toInt(-1));
                if(ex.value(QStringLiteral("wrongRepeatEnabled")).toBool(false)) {
                    details+=tr("Repeated wrong item ID: %1\n")
                        .arg(ex.value(QStringLiteral("wrongRepeatItem")).toInt(-1));
                    for(int b=1;b<5;++b)
                        details+=tr("Offer %1 → dialogue %2\n")
                            .arg(b==4?tr("4+"):QString::number(b))
                            .arg(ex.value(giveRouteKey(b)).toInt(-1));
                }
                details+=tr("\nChange destinations on the card. Use its Adventure Editor button for requested items, exchange requirements and event actions. Stored in adventure.nodes[].choices[].exchange, not in .vsgm.");
                m_details->setPlainText(details);
            }
            return;
        }
        if(id.startsWith(QStringLiteral("@conversation:"))) {
            m_linksList->clear();m_linksList->setEnabled(false);
            m_editLinkButton->setEnabled(false);m_removeLinkButton->setEnabled(false);
            bool indexOk=false;
            const int index=id.mid(QStringLiteral("@conversation:").size()).toInt(&indexOk);
            if(indexOk && index>=0 && index<m_dialogues.size()) {
                const QJsonObject node=m_dialogues.at(index).toObject();
                QString details=tr("EDITABLE CONVERSATION FLOW\n\nDialogue #%1\nSpeaker: %2\n\n%3\n\n")
                    .arg(index).arg(node.value(QStringLiteral("speaker")).toString(),
                                      node.value(QStringLiteral("text")).toString());
                const QJsonArray choices=node.value(QStringLiteral("choices")).toArray();
                int count=0;
                for(int option=0;option<choices.size();++option) {
                    const QJsonObject c=choices.at(option).toObject();
                    const QString answer=c.value(QStringLiteral("text")).toString().trimmed();
                    if(answer.isEmpty())continue;
                    ++count;
                    const int next=c.value(QStringLiteral("next")).toInt(-1);
                    details+=tr("Answer %1: %2\nNext: %3\n").arg(option+1).arg(answer,
                        next<0?tr("Close conversation"):next>=m_dialogues.size()
                            ?tr("MISSING dialogue #%1").arg(next):tr("Dialogue #%1").arg(next));
                    const int requires=c.value(QStringLiteral("requires")).toInt(-1);
                    if(requires>=0) {
                        const int missing=c.value(QStringLiteral("missingNext")).toInt(-1);
                        details+=tr("Requires inventory item #%1; if missing: %2\n")
                            .arg(requires).arg(missing<0?tr("Close conversation"):
                                missing>=m_dialogues.size()?tr("MISSING #%1").arg(missing):
                                tr("Dialogue #%1").arg(missing));
                    }
                    details+=QStringLiteral("\n");
                }
                if(!count)details+=tr("No answers: conversation ends when FIRE2 closes this dialogue.\n\n");
                details+=tr("Source: adventure.nodes in this world's .sbgm.\nSpeaker, text, answer labels and next links edit this world's .sbgm directly on Save Graph + World. Use Open in Adventure Editor for rewards, inventory gates and advanced choices. Moving/collapsing cards changes .vsgm only.");
                m_details->setPlainText(details);
            }
            return;
        }
        if(id.startsWith(QStringLiteral("@graph-dialogue:"))) {
            m_linksList->clear();m_linksList->setEnabled(false);
            m_details->setPlainText(tr("Shared Adventure dialogue. Change speaker/text here or select an existing dialogue. The original dialogue is never deleted when a graph card is disconnected."));
            return;
        }
        if(id.startsWith(QStringLiteral("@graph:"))) {
            QString owner;QJsonObject node;
            if(lookupGraph(id,&owner,nullptr,&node)) {
                m_linksList->clear();m_linksList->setEnabled(false);
                m_details->setPlainText(tr("Independent logic node %1 (%2)\n\n"
                    "Evaluated when Trigger %3 activates.\nInputs: %4\n\n"
                    "RESULT can feed other logic nodes OR directly set a Game Object's enabled state (TRUE = on, FALSE = off). TRUE/FALSE can also run actions and dialogues. Right-click a wire to edit/remove it.")
                    .arg(node.value(QStringLiteral("id")).toString(),node.value(QStringLiteral("op")).toString(),
                         m_objects.value(owner).name)
                    .arg(node.value(QStringLiteral("inputs")).toArray().size()));
            }
            return;
        }
        if (id.startsWith(QStringLiteral("@toggle-dialogue:"))) {
            m_linksList->clear();m_linksList->setEnabled(false);
            const bool yes=id.startsWith(QStringLiteral("@toggle-dialogue:true:"));
            const QString prefix=yes?QStringLiteral("@toggle-dialogue:true:"):QStringLiteral("@toggle-dialogue:false:");
            const QString owner=id.mid(prefix.size());
            const NodeObject n=m_objects.value(owner);
            m_details->setPlainText(tr("%1 branch for %2\nDialogue #%3\n\nRight-click this purple card to change or disconnect the dialogue. The actual Adventure dialogue is never deleted.")
                .arg(yes?tr("TRUE"):tr("FALSE"),n.name).arg(yes?n.toggleTrueDialogueNode:n.toggleFalseDialogueNode));
            return;
        }
        if (id.startsWith(QStringLiteral("@toggle:"))) {
            const QString owner=id.mid(QStringLiteral("@toggle:").size());
            const NodeObject n=m_objects.value(owner);
            m_linksList->clear();m_linksList->setEnabled(true);
            for (const bool yes:{true,false}) {
                const QVector<NodeLink> &links=yes?n.toggleTrueActions:n.toggleFalseActions;
                for (int i=0;i<links.size();++i) {
                    const NodeLink link=links.at(i);
                    auto *item=new QListWidgetItem(tr("%1: %2 → %3")
                        .arg(yes?tr("TRUE"):tr("FALSE"),link.action,
                             m_objects.contains(link.target)?m_objects.value(link.target).name:link.target),m_linksList);
                    item->setData(Qt::UserRole,(yes?-1000:-2000)-i);
                }
            }
            QStringList names;
            if (!n.toggleStateTargetId.isEmpty()) names.append(m_objects.value(n.toggleStateTargetId).name);
            for (const QString &input : n.toggleStateInputIds) names.append(m_objects.value(input).name);
            m_details->setPlainText(tr("%1 condition\n\nInputs: %2\nEvaluated when: %3 activates\n\nConnect Game Object state outputs to add inputs. Right-click a state wire to disconnect it. TRUE/FALSE output wires share the ordinary Game Object actions and Show Dialogue nodes.")
                .arg(n.toggleStateOperator.toUpper(),names.join(QStringLiteral(", ")),n.name));
            return;
        }
        if (id.startsWith(QStringLiteral("@dialogue:"))) {
            const QString triggerId=id.mid(QStringLiteral("@dialogue:").size());
            const NodeObject trigger=m_objects.value(triggerId);
            m_linksList->clear();m_linksList->setEnabled(false);
            m_editLinkButton->setEnabled(false);m_removeLinkButton->setEnabled(false);
            m_details->setPlainText(tr("Show Dialogue for %1\n\nSelect or create an Adventure dialogue in this card. Edit speaker, text and playback mode directly in the card.\n\nAdvanced choices, quest actions and dialogue branches remain in the Adventure Editor.\n\nCurrent dialogue ID: %2")
                .arg(trigger.name).arg(trigger.dialogueNode));
            return;
        }
        if (!m_objects.contains(id))return;
        const NodeObject node=m_objects.value(id);
        QString text=tr("%1\nType: %2\n\nID: %3\n\n")
            .arg(node.name,node.type,node.id);
        m_linksList->clear();
        if (isActionSource(node) || !eventKinds(node.type).isEmpty()) {
            text+=tr("LINKED ACTIONS\n");
            for (int i=0;i<node.links.size();++i) {
                const NodeLink &link=node.links[i];
                const QString target=m_objects.contains(link.target)
                    ?m_objects.value(link.target).name:link.target;
                text+=QStringLiteral("• %1 → %2\n").arg(link.action,target);
                auto *row=new QListWidgetItem(QStringLiteral("%1. %2 → %3")
                    .arg(i+1).arg(link.action,target),m_linksList);
                row->setData(Qt::UserRole,i);
                row->setToolTip(tr("%1 → %2: %3").arg(node.name,target,link.action));
            }
            for (const QString &key:eventKinds(node.type)) {
                const QVector<NodeLink> actions=node.eventLinks.value(key);
                text+=QStringLiteral("\n%1 (%2 actions)\n").arg(eventLabel(key)).arg(actions.size());
                for(int i=0;i<actions.size();++i) {
                    const NodeLink &link=actions.at(i);
                    const QString target=m_objects.contains(link.target)?m_objects.value(link.target).name:link.target;
                    text+=QStringLiteral("  • %1 → %2\n").arg(link.action,target);
                    auto *row=new QListWidgetItem(tr("%1: %2 → %3")
                        .arg(eventLabel(key),link.action,target),m_linksList);
                    // Inspect/edit via the corresponding wire context menu.
                    row->setData(Qt::UserRole,-30000-eventKinds(node.type).indexOf(key)*100-i);
                    row->setToolTip(tr("Right-click its coloured event wire to edit this action."));
                }
            }
            if (node.type==QStringLiteral("trigger"))
                text+=tr("\nDialogue: %1 (%2)\n\nUse the golden socket to connect this Trigger to another object or its Show Dialogue card. Select a connection below to edit or remove it.")
                    .arg(node.dialogueNode).arg(node.dialogueMode);
            else if(node.type==QStringLiteral("enemy"))
                text+=tr("\nGOLD ON DEFEAT socket: drag to a Game Object or PLAYER action. The linked actions run IN ORDER when this enemy is defeated.\n"
                         "TEAL STATE socket: feed the enemy's enabled state into Boolean / AND / OR / NOT.\n"
                         "LEFT square: receive Enable / Disable / Toggle commands from Triggers or logic branches.\n"
                         "Right-click an action wire to change Enable / Disable / Toggle or disconnect it.");
            else text+=tr("\nThis pre-existing key-pickup action runs when collected. Edit the link below or use Game Object Properties.");
        } else if(node.type==QStringLiteral("npc")) {
            text+=tr("NPC CONVERSATIONS (Adventure Editor)\n\n"
                "Opening: %1\nAfter helped: %2\nTalk radius: %3 px\nInitially visible: %4\n\n"
                "Edit these fields directly on the expanded NPC card. "
                "Drag Trigger or logic TRUE/FALSE wires onto the small square Opening or "
                "After helped INPUT sockets at the left of this card; NPC visibility has its own square input. "
                "The old NPC Conversations picker is still supported. "
                "The Dialogue Editor still owns conversation text, choices and quest effects.")
                .arg(npcDialogueTitle(node.npcStartNode),
                     node.npcDoneNode<0?tr("Use opening dialogue"):npcDialogueTitle(node.npcDoneNode))
                .arg(node.npcRadius).arg(node.npcInitiallyVisible?tr("Yes"):tr("No"));
        } else text+=tr("This is a target card. Its other settings remain in Game Object Properties.");
        m_editLinkButton->setEnabled(false);
        m_removeLinkButton->setEnabled(false);
        m_linksList->setEnabled(isActionSource(node) || !eventKinds(node.type).isEmpty());
        m_details->setPlainText(text);
    }
    void connectNpcDialogue(const QString &from,const QString &npcId,QString slot) {
        if(!m_objects.contains(npcId) || m_objects.value(npcId).type!=QStringLiteral("npc"))return;
        const NodeObject npc=m_objects.value(npcId);
        if(slot.isEmpty()) {
            const QStringList choices{tr("Opening conversation"),tr("After helped conversation")};
            bool ok=false;
            const QString selected=QInputDialog::getItem(this,tr("NPC Dialogue Input"),
                tr("Which conversation on %1?").arg(npc.name),choices,0,false,&ok);
            if(!ok)return;
            slot=selected==choices.at(0)?QStringLiteral("start"):QStringLiteral("helped");
        }
        const int dialogue=slot==QStringLiteral("start")?npc.npcStartNode:
                           slot==QStringLiteral("helped")?npc.npcDoneNode:-1;
        if(dialogue<0 || dialogue>=m_dialogues.size()) {
            QMessageBox::information(this,tr("NPC Dialogue Input"),
                tr("Choose an existing %1 conversation on %2 first.")
                    .arg(slot==QStringLiteral("start")?tr("opening"):tr("after-helped"),npc.name));
            return;
        }
        const bool graph=from.startsWith(QStringLiteral("@graphbranch:true:")) ||
                         from.startsWith(QStringLiteral("@graphbranch:false:"));
        const bool state=from.startsWith(QStringLiteral("@stateout:true:")) ||
                         from.startsWith(QStringLiteral("@stateout:false:"));
        const bool trigger=m_objects.contains(from) && m_objects.value(from).type==QStringLiteral("trigger");
        if(!graph && !state && !trigger)return;
        if(state) {
            const bool yes=from.startsWith(QStringLiteral("@stateout:true:"));
            const QString owner=from.mid(yes?QStringLiteral("@stateout:true:").size():
                QStringLiteral("@stateout:false:").size());
            if(!m_objects.contains(owner) || m_objects.value(owner).toggleStateTargetId.isEmpty()) {
                QMessageBox::information(this,tr("NPC Dialogue Input"),
                    tr("Connect the Boolean condition's state input first."));return;
            }
        }
        m_hiddenNpcCards.remove(npcId);
        if(!m_cards.contains(npcId))makeObjectCard(npcId,m_positions.contains(npcId)?
            m_positions.value(npcId):viewportInsertionPoint(QSizeF(355,280)));
        m_npcDialogueRoutes.insert(from,QJsonObject{
            {QStringLiteral("npc"),npcId},{QStringLiteral("slot"),slot},
            {QStringLiteral("dialogue"),dialogue}});
        // The .sbgm still contains only the existing dialogue ID. The route
        // belongs to .vsgm and can be discarded without changing gameplay.
        if(graph) {
            const bool yes=from.startsWith(QStringLiteral("@graphbranch:true:"));
            const QString key=from.mid(yes?QStringLiteral("@graphbranch:true:").size():
                QStringLiteral("@graphbranch:false:").size());
            setGraphDialogue(key,yes,dialogue);
            if(m_cards.contains(graphDialogueKey(key,yes)))
                removeOrphanCard(graphDialogueKey(key,yes),true);
        } else if(state) {
            const bool yes=from.startsWith(QStringLiteral("@stateout:true:"));
            const QString owner=from.mid(yes?QStringLiteral("@stateout:true:").size():
                QStringLiteral("@stateout:false:").size());
            setBranchDialogue(owner,yes,dialogue,m_cards.value(npcId)->pos());
            if(m_cards.contains(branchCardId(owner,yes)))
                removeOrphanCard(branchCardId(owner,yes),true);
        } else {
            connectExistingDialogue(from,m_cards.value(npcId)->pos(),dialogue);
            if(m_cards.contains(dialogueCardId(from)))
                removeOrphanCard(dialogueCardId(from),true);
        }
        m_dirty=true;
        redrawLinks();showDetails(npcId);
    }
    int selectedDialogueOnCard(const QString &cardId) const {
        // A Show Dialogue card is an action VIEW of one Adventure dialogue.
        // Reusing it must reuse the numeric ID, not copy its dialogue data.
        int selected=-1;
        if(cardId.startsWith(QStringLiteral("@graph-dialogue:"))) {
            const bool yes=cardId.startsWith(QStringLiteral("@graph-dialogue:true:"));
            const QString prefix=yes?QStringLiteral("@graph-dialogue:true:"):
                                     QStringLiteral("@graph-dialogue:false:");
            QJsonObject node;
            if(lookupGraph(cardId.mid(prefix.size()),nullptr,nullptr,&node))
                selected=node.value(yes?QStringLiteral("trueDialogueNode"):
                                     QStringLiteral("falseDialogueNode")).toInt(-1);
        } else if(cardId.startsWith(QStringLiteral("@toggle-dialogue:"))) {
            const bool yes=cardId.startsWith(QStringLiteral("@toggle-dialogue:true:"));
            const QString prefix=yes?QStringLiteral("@toggle-dialogue:true:"):
                                     QStringLiteral("@toggle-dialogue:false:");
            const NodeObject owner=m_objects.value(cardId.mid(prefix.size()));
            selected=yes?owner.toggleTrueDialogueNode:owner.toggleFalseDialogueNode;
        } else if(cardId.startsWith(QStringLiteral("@dialogue:"))) {
            const QString owner=cardId.mid(QStringLiteral("@dialogue:").size());
            selected=m_objects.value(owner).dialogueNode;
        } else if(cardId.startsWith(QStringLiteral("@conversation:"))) {
            bool ok=false;
            const int id=cardId.mid(QStringLiteral("@conversation:").size()).toInt(&ok);
            if(ok)selected=id;
        }
        // Disconnect retains the displayed selection on an already opened
        // card, so its old ID is still useful when attaching a new branch.
        if(selected<0 && m_dialogueControls.contains(cardId)) {
            QComboBox *picker=m_dialogueControls.value(cardId).picker;
            if(picker && picker->currentData().isValid())
                selected=picker->currentData().toInt();
        }
        return selected>=0 && selected<m_dialogues.size()?selected:-1;
    }
    void addConnection(const QString &from,const QString &to,const QString &port=QString()) {
        if(isEventOutput(from)) {
            if((eventKey(from)==QStringLiteral("hit") || eventKey(from)==QStringLiteral("destroy")) &&
               m_objects.value(eventOwner(from)).type==QStringLiteral("breakable") &&
               (to.startsWith(QStringLiteral("@graph-dialogue:")) ||
                to.startsWith(QStringLiteral("@toggle-dialogue:")) ||
                to.startsWith(QStringLiteral("@dialogue:")) ||
                to.startsWith(QStringLiteral("@conversation:")))) {
                const int dialogue=selectedDialogueOnCard(to);
                if(dialogue<0)return;
                const QString owner=eventOwner(from);
                const int before=m_objects.value(owner).logicNodes.size();
                const QPointF at=m_cards.contains(to)?m_cards.value(to)->pos()-QPointF(350,0):viewportInsertionPoint();
                createGraphLogic(from,at,QStringLiteral("boolean"));
                const QJsonArray nodes=m_objects.value(owner).logicNodes;
                if(nodes.size()!=before+1)return;
                const QString key=graphKey(owner,nodes.last().toObject().value(QStringLiteral("id")).toString());
                setGraphDialogue(key,true,dialogue,at+QPointF(350,0));
                const QString display=graphDialogueKey(key,true);
                if(dialogueCardHasLiveAction(to)) {
                    // One canvas dialogue card can represent multiple real
                    // actions; each graph still retains its own .sbgm ID.
                    if(m_cards.contains(display))removeOrphanCard(display,true);
                    m_graphDialogueRoutes.insert(display,to);
                    redrawLinks();showDetails(to);
                }
                m_status->setText(tr("%1 → BOOLEAN TRUE → Dialogue #%2. Save Graph + World to apply.")
                    .arg(eventLabel(eventKey(from))).arg(dialogue));
                return;
            }
            if(to.startsWith(QStringLiteral("@graph:")) &&
               (eventKey(from)==QStringLiteral("arrival") ||
                eventKey(from)==QStringLiteral("hit") ||
                eventKey(from)==QStringLiteral("destroy"))) {
                QString graphOwner;
                if(lookupGraph(to,&graphOwner,nullptr) && graphOwner!=eventOwner(from)) {
                    const QString owner=eventOwner(from);
                    QJsonObject existing;
                    if(!lookupGraph(to,nullptr,nullptr,&existing))return;
                    QMessageBox message(QMessageBox::Information,tr("Event-driven Logic"),
                        tr("This gate belongs to another Game Object. %1 must own its %2 gate "
                           "so the one-frame event is evaluated at the right time.\n\n"
                           "Create a separate %3 gate from this event, then reconnect the other STATE inputs.")
                            .arg(m_objects.value(owner).name,eventLabel(eventKey(from)),
                                 existing.value(QStringLiteral("op")).toString().toUpper()),
                        QMessageBox::NoButton,this);
                    auto *create=message.addButton(tr("Create Event Gate"),QMessageBox::AcceptRole);
                    message.addButton(QMessageBox::Cancel);
                    message.exec();
                    if(message.clickedButton()==create) {
                        const QString operation=existing.value(QStringLiteral("op")).toString();
                        const QPointF point=m_cards.contains(to)?m_cards.value(to)->pos()+QPointF(0,260):viewportInsertionPoint();
                        createGraphLogic(from,point,operation);
                        m_status->setText(tr("Created an event-owned %1 gate. Reconnect its other STATE inputs.")
                            .arg(operation.toUpper()));
                    }
                    return;
                }
                addGraphInput(from,to);return;
            }
            if(!m_objects.contains(to) || m_objects.value(to).type==QStringLiteral("npc"))return;
            appendEventConnection(eventOwner(from),eventKey(from),to,
                defaultPlayerAction(to,QStringLiteral("enable")));
            return;
        }
        if (isEnemyDefeatOutput(from)) {
            const QString owner=enemyDefeatOwner(from);
            if (m_objects.value(owner).type!=QStringLiteral("enemy"))return;
            if (to.startsWith(QStringLiteral("@graph:")) || to.startsWith(QStringLiteral("@toggle:"))) {
                QMessageBox::information(this,tr("Enemy ON DEFEAT"),
                    tr("The gold ON DEFEAT output sends Enable / Disable / Toggle actions. "
                       "Use the teal STATE output to connect this enemy to a Boolean input."));
                return;
            }
            if (!m_objects.contains(to))return;
            if (m_objects.value(to).type==QStringLiteral("npc")) {
                QMessageBox::information(this,tr("Enemy ON DEFEAT"),
                    tr("This NPC input starts a conversation, not a visibility action. "
                       "Use a Trigger or Boolean dialogue branch for NPC conversations."));
                return;
            }
            appendConnection(owner,to,defaultPlayerAction(to,QStringLiteral("enable")));
            return;
        }
        if(m_objects.contains(to) && m_objects.value(to).type==QStringLiteral("npc") &&
           port!=QStringLiteral("state") &&
           (from.startsWith(QStringLiteral("@graphbranch:")) ||
            from.startsWith(QStringLiteral("@stateout:")) ||
            (m_objects.contains(from) && m_objects.value(from).type==QStringLiteral("trigger")))) {
            connectNpcDialogue(from,to,port);
            return;
        }
        if(from.startsWith(QStringLiteral("@graphvalue:"))) {
            if(to.startsWith(QStringLiteral("@graph:")))addGraphInput(from,to);
            else if(m_objects.contains(to))
                addGraphResultTarget(from.mid(QStringLiteral("@graphvalue:").size()),to);
            return;
        }
        if(from.startsWith(QStringLiteral("@graphbranch:"))) {
            const bool yes=from.startsWith(QStringLiteral("@graphbranch:true:"));
            const QString key=from.mid((yes?QStringLiteral("@graphbranch:true:"):
                QStringLiteral("@graphbranch:false:")).size());
            if(to.startsWith(QStringLiteral("@graph-dialogue:")) ||
               to.startsWith(QStringLiteral("@toggle-dialogue:")) ||
               to.startsWith(QStringLiteral("@dialogue:")) ||
               to.startsWith(QStringLiteral("@conversation:"))) {
                if(!m_cards.contains(to))return;
                // The target card is a VISUAL shared destination, not another
                // action to create. Each source branch still owns its own
                // numeric dialogue ID in the real .sbgm logic graph.
                int selected=selectedDialogueOnCard(to);
                if(selected<0) {
                    selected=browseDialogueTree(-1);
                    if(selected==-1)return;
                }
                const QString own=graphDialogueKey(key,yes);
                const QPointF where=m_cards.value(to)->pos();
                if(to!=own && !dialogueCardHasLiveAction(to)) {
                    // An orphaned Show Dialogue card has no authored action.
                    // Re-home its visible position to the new source branch;
                    // otherwise it would disappear on the next graph reopen.
                    removeOrphanCard(to,true);
                    if(m_cards.contains(own))removeOrphanCard(own,true);
                    m_graphDialogueRoutes.remove(own);
                    m_positions.insert(own,where);
                    setGraphDialogue(key,yes,selected,where);
                    redrawLinks();showDetails(own);
                } else if(to!=own) {
                    // Share an already active display card. Both source
                    // branches keep their own .sbgm dialogue action.
                    setGraphDialogue(key,yes,selected,where);
                    if(m_cards.contains(own))removeOrphanCard(own,true);
                    m_graphDialogueRoutes.insert(own,to);
                    redrawLinks();showDetails(to);
                } else {
                    m_graphDialogueRoutes.remove(own);
                    setGraphDialogue(key,yes,selected,where);
                }
                m_dirty=true;
                m_status->setText(tr("%1 connected directly to the existing Dialogue #%2 card (shared view, independent gameplay action).")
                    .arg(yes?tr("TRUE"):tr("FALSE")).arg(selected));
                return;
            }
            if(m_objects.contains(to))addGraphAction(key,yes,to,
                defaultPlayerAction(to,yes?QStringLiteral("enable"):QStringLiteral("disable")));
            return;
        }
        if (from.startsWith(QStringLiteral("@stateout:"))) {
            const bool yes=from.startsWith(QStringLiteral("@stateout:true:"));
            const QString owner=from.mid(yes?QStringLiteral("@stateout:true:").size():
                                        QStringLiteral("@stateout:false:").size());
            if ((to.startsWith(QStringLiteral("@dialogue:")) ||
                 to.startsWith(QStringLiteral("@graph-dialogue:")) ||
                 to.startsWith(QStringLiteral("@conversation:"))) && m_cards.contains(to)) {
                int selected=selectedDialogueOnCard(to);
                if(selected<0)selected=browseDialogueTree(-1);
                if(selected>=0)setBranchDialogue(owner,yes,selected,
                    m_cards.value(to)->pos()+QPointF(360,yes?-80:80));
            } else if (to==branchCardId(owner,yes)) {
                // Reattach the existing legacy Boolean dialogue card instead
                // of always opening a new picker when its wire was removed.
                int selected=yes?m_objects.value(owner).toggleTrueDialogueNode:
                                 m_objects.value(owner).toggleFalseDialogueNode;
                if(m_dialogueControls.contains(to)) {
                    const QVariant data=m_dialogueControls.value(to).picker->currentData();
                    if(data.isValid() && data.toInt()>=0 && data.toInt()<m_dialogues.size())
                        selected=data.toInt();
                }
                if(selected>=0 && selected<m_dialogues.size())
                    setBranchDialogue(owner,yes,selected,m_cards.value(to)->pos());
                else
                    selectBranchDialogue(from,m_cards.value(to)->pos());
            } else if (m_objects.contains(to)) {
                appendBranchConnection(owner,yes,to,
                    defaultPlayerAction(to,yes?QStringLiteral("enable"):QStringLiteral("disable")));
            }
            return;
        }
        if (m_objects.contains(from) && m_objects.value(from).type!=QStringLiteral("trigger") &&
            m_objects.value(from).type!=QStringLiteral("player_action")) {
            if(to.startsWith(QStringLiteral("@graph:"))) {addGraphInput(from,to);return;}
            if (to.startsWith(QStringLiteral("@toggle:"))) {
                const QString owner=to.mid(QStringLiteral("@toggle:").size());
                addInputToCondition(owner,from);
            }
            return;
        }
        if (!m_objects.contains(from) || m_objects.value(from).type!=QStringLiteral("trigger"))return;
        if (to==toggleCardId(from)) {
            showDetails(to);return;
        }
        if (to==dialogueCardId(from)) {
            if (!m_dialogueCards.contains(from) || !m_dialogueControls.contains(from))return;
            if (m_objects.value(from).dialogueNode<0) {
                // A disconnected Trigger card may still display its last
                // dialogue ID. Reconnect it without creating another card.
                const QVariant data=m_dialogueControls.value(from).picker->currentData();
                const int selected=data.isValid()?data.toInt():-1;
                if(selected>=0 && selected<m_dialogues.size())
                    connectExistingDialogue(from,m_cards.value(to)->pos(),selected);
                else
                    m_dialogueControls.value(from).picker->showPopup();
            }
            showDetails(to);
            return;
        }
        if (!m_objects.contains(to))return;
        appendConnection(from,to,QStringLiteral("enable"));
    }
    // Orphan removal is .vsgm-only. Delete/Remove Selected below additionally
    // disconnects links in the pending .sbgm edit, without deleting resources.
    int removeOrphanCard(const QString &id,bool force=false) {
        if (!m_cards.contains(id) || (!force && connectedCardIds().contains(id)))return 0;
        int removed=0;
        // Removing an unconnected Trigger also removes its unattached purple
        // card; otherwise that dialogue card would remain stranded on screen.
        if (m_objects.contains(id)) {
            const QString dialogueId=dialogueCardId(id);
            if (m_cards.contains(dialogueId))removed+=removeOrphanCard(dialogueId,force);
        }
        if (id.startsWith(QStringLiteral("@dialogue:"))) {
            const QString trigger=id.mid(QStringLiteral("@dialogue:").size());
            m_dialogueControls.remove(trigger); // Qt owns the widget via its proxy.
            m_dialogueCards.remove(trigger);
        }
        if (id.startsWith(QStringLiteral("@toggle:"))) {
            const QString owner=id.mid(QStringLiteral("@toggle:").size());
            m_booleanSourceLabels.remove(owner);
            m_logicTitles.remove(owner);
            m_logicNotes.remove(owner);
        }
        if (id.startsWith(QStringLiteral("@toggle-dialogue:")))
            m_dialogueControls.remove(id);
        if(id.startsWith(QStringLiteral("@graph-dialogue:")))m_dialogueControls.remove(id);
        NodeCard *card=m_cards.take(id);
        if (!card)return removed;
        // Discard visual routes to an explicitly removed target. Real action
        // values remain in .sbgm and regenerate their own cards when needed.
        for(auto it=m_graphDialogueRoutes.begin();it!=m_graphDialogueRoutes.end();) {
            if(it.key()==id || it.value()==id)it=m_graphDialogueRoutes.erase(it);
            else ++it;
        }
        m_scene->removeItem(card);
        delete card;
        m_placedCards.remove(id);
        m_collapsedCards.remove(id);
        m_positions.remove(id);
        for (int i=m_list->count()-1;i>=0;--i)
            if (m_list->item(i)->data(Qt::UserRole).toString()==id)
                delete m_list->takeItem(i);
        if (m_selectedCardId==id) {
            m_selectedCardId.clear();
            m_details->clear();
            m_linksList->clear();
            m_editLinkButton->setEnabled(false);
            m_removeLinkButton->setEnabled(false);
            m_removeSelectedButton->setEnabled(false);
        }
        m_dirty=true;
        return removed+1;
    }
    void disconnectDialogue(const QString &triggerId) {
        if (!m_objects.contains(triggerId))return;
        NodeObject node=m_objects.value(triggerId);
        if (node.type!=QStringLiteral("trigger") || node.dialogueNode<0)return;
        node.dialogueNode=-1;
        m_npcDialogueRoutes.remove(triggerId);
        m_objects.insert(triggerId,node);
        m_touched.insert(triggerId);
        m_dirty=true;
        if (m_dialogueControls.contains(triggerId))refreshDialogueCard(triggerId);
        redrawLinks();
        if (m_cards.contains(dialogueCardId(triggerId)))
            showDetails(dialogueCardId(triggerId));
        else if (m_cards.contains(triggerId))showDetails(triggerId);
    }
    void removeToggleCondition(const QString &id) {
        if (!m_objects.contains(id))return;
        NodeObject n=m_objects.value(id);
        if (n.toggleStateTargetId.isEmpty() && n.toggleTrueDialogueNode<0 &&
            n.toggleFalseDialogueNode<0 && n.toggleTrueActions.isEmpty() &&
            n.toggleFalseActions.isEmpty() && !m_cards.contains(toggleCardId(id)))return;
        n.toggleStateTargetId.clear();n.toggleStateInputIds.clear();
        n.toggleStateOperator=QStringLiteral("boolean");
        n.toggleTrueDialogueNode=-1;n.toggleFalseDialogueNode=-1;
        n.toggleTrueActions.clear();n.toggleFalseActions.clear();
        m_npcDialogueRoutes.remove(QStringLiteral("@stateout:true:")+id);
        m_npcDialogueRoutes.remove(QStringLiteral("@stateout:false:")+id);
        m_objects.insert(id,n);m_touched.insert(id);m_dirty=true;
        for (const QString &key:{branchCardId(id,true),branchCardId(id,false),toggleCardId(id)})
            if (m_cards.contains(key))removeOrphanCard(key,true);
        redrawLinks();showDetails(id);
    }
    void removeSelectedNode() {
        const QString id=m_selectedCardId;
        if(id.startsWith(QStringLiteral("@conversation:")) || id.startsWith(QStringLiteral("@give:"))) {
            bool indexOk=false;
            int index=id.mid(QStringLiteral("@conversation:").size()).toInt(&indexOk);
            if(id.startsWith(QStringLiteral("@give:"))) {
                int option=-1;
                indexOk=giveCardReference(id,&index,&option);
            }
            if(!indexOk || index<0)return;
            if (QMessageBox::question(this,tr("Hide Conversation Preview"),
                tr("Hide the conversation flow containing dialogue #%1?\n\nOnly the graph preview is removed. No Adventure dialogue, answer or gameplay wire will be changed.").arg(index),
                QMessageBox::Yes|QMessageBox::No,QMessageBox::No)==QMessageBox::Yes)
                hideConversationContaining(index);
            return;
        }
        if (id.isEmpty() || !m_cards.contains(id))return;
        // One explicit confirmation for every destructive node deletion.
        if (QMessageBox::question(this,tr("Delete Visual Node"),
            tr("Delete '%1' from the graph and disconnect ALL its wires?\n\n"
               "The actual Game Object, NPC and Adventure dialogue resources remain intact. "
               "The changes are committed when you save the graph.")
                .arg(m_objects.contains(id)?m_objects.value(id).name:id),
            QMessageBox::Yes|QMessageBox::No,QMessageBox::No)!=QMessageBox::Yes)return;
        if(id.startsWith(QStringLiteral("@graph-dialogue:"))) {
            const bool yes=id.startsWith(QStringLiteral("@graph-dialogue:true:"));
            const QString key=id.mid((yes?QStringLiteral("@graph-dialogue:true:"):
                QStringLiteral("@graph-dialogue:false:")).size());
            setGraphDialogue(key,yes,-1);
            removeOrphanCard(id,true);redrawLinks();showDetails(key);return;
        }
        if(id.startsWith(QStringLiteral("@graph:"))) {
            QString owner;int index=-1;QJsonObject node;
            if(!lookupGraph(id,&owner,&index,&node))return;
            // User already confirmed the destructive removal above.
            NodeObject trigger=m_objects.value(owner);
            QJsonArray updated;
            const QString nodeId=node.value(QStringLiteral("id")).toString();
            for(int i=0;i<trigger.logicNodes.size();++i) {
                if(i==index)continue;
                QJsonObject item=trigger.logicNodes.at(i).toObject();
                QJsonArray inputs;
                for(const QJsonValue &v:item.value(QStringLiteral("inputs")).toArray())
                    if(v.toObject().value(QStringLiteral("kind")).toString()!=QStringLiteral("node") ||
                       v.toObject().value(QStringLiteral("id")).toString()!=nodeId)
                        inputs.append(v);
                item.insert(QStringLiteral("inputs"),inputs);updated.append(item);
            }
            trigger.logicNodes=updated;m_objects.insert(owner,trigger);
            m_npcDialogueRoutes.remove(QStringLiteral("@graphbranch:true:")+id);
            m_npcDialogueRoutes.remove(QStringLiteral("@graphbranch:false:")+id);
            m_graphDialogueRoutes.remove(graphDialogueKey(id,true));
            m_graphDialogueRoutes.remove(graphDialogueKey(id,false));
            m_touched.insert(owner);m_dirty=true;
            for(const bool yes:{true,false}) {
                const QString display=graphDialogueKey(id,yes);
                removeOrphanCard(display,true);
            }
            removeOrphanCard(id,true);
            redrawLinks();showDetails(owner);
            m_status->setText(tr("Deleted graph node. Reconnect incomplete downstream inputs before saving."));
            return;
        }
        if(m_objects.contains(id) && m_objects.value(id).type==QStringLiteral("npc")) {
            // Deleting an NPC CARD must disconnect its special conversation
            // inputs too. Do not delete the NPC or any Adventure dialogue.
            const QList<QString> sources=m_npcDialogueRoutes.keys();
            for(const QString &source:sources) {
                if(m_npcDialogueRoutes.value(source).value(QStringLiteral("npc")).toString()!=id)continue;
                if(source.startsWith(QStringLiteral("@graphbranch:"))) {
                    const bool yes=source.startsWith(QStringLiteral("@graphbranch:true:"));
                    const QString key=source.mid(yes?QStringLiteral("@graphbranch:true:").size():
                        QStringLiteral("@graphbranch:false:").size());
                    setGraphDialogue(key,yes,-1);
                } else if(source.startsWith(QStringLiteral("@stateout:"))) {
                    const bool yes=source.startsWith(QStringLiteral("@stateout:true:"));
                    const QString owner=source.mid(yes?QStringLiteral("@stateout:true:").size():
                        QStringLiteral("@stateout:false:").size());
                    setBranchDialogue(owner,yes,-1,QPointF());
                } else disconnectDialogue(source);
                m_npcDialogueRoutes.remove(source);
            }
        }
        if(id.startsWith(QStringLiteral("@graph:"))) {
            m_npcDialogueRoutes.remove(QStringLiteral("@graphbranch:true:")+id);
            m_npcDialogueRoutes.remove(QStringLiteral("@graphbranch:false:")+id);
        }
        const bool dialogueCard=id.startsWith(QStringLiteral("@dialogue:"));
        if (id.startsWith(QStringLiteral("@toggle-dialogue:"))) {
            const bool yes=id.startsWith(QStringLiteral("@toggle-dialogue:true:"));
            const QString prefix=yes?QStringLiteral("@toggle-dialogue:true:"):QStringLiteral("@toggle-dialogue:false:");
            const QString owner=id.mid(prefix.size());
            NodeObject n=m_objects.value(owner);
            if (yes)n.toggleTrueDialogueNode=-1;else n.toggleFalseDialogueNode=-1;
            m_npcDialogueRoutes.remove(QStringLiteral("@stateout:")+
                (yes?QStringLiteral("true:"):QStringLiteral("false:"))+owner);
            m_objects.insert(owner,n);m_touched.insert(owner);m_dirty=true;
            removeOrphanCard(id,true);redrawLinks();showDetails(toggleCardId(owner));return;
        }
        if (id.startsWith(QStringLiteral("@toggle:"))) {
            removeToggleCondition(id.mid(QStringLiteral("@toggle:").size()));return;
        }
        int removedLinks=0;
        // Count links before displaying the confirmation, including parallel
        // edges and every Trigger that points at a shared target object.
        for (const QString &source:m_order) {
            const NodeObject node=m_objects.value(source);
            if (!isActionSource(node) && eventKinds(node.type).isEmpty() &&
                node.logicNodes.isEmpty())continue;
            if (source==id) {
                for(const QVector<NodeLink> &events:node.eventLinks)removedLinks+=events.size();
                removedLinks+=node.links.size();
                if (node.dialogueNode>=0)++removedLinks;
                if (!node.toggleStateTargetId.isEmpty())++removedLinks;
                if (node.toggleTrueDialogueNode>=0)++removedLinks;
                if (node.toggleFalseDialogueNode>=0)++removedLinks;
                removedLinks+=node.toggleTrueActions.size()+node.toggleFalseActions.size();
            } else if (!dialogueCard) {
                for (const QVector<NodeLink> &events:node.eventLinks)
                    for(const NodeLink &link:events)if(link.target==id)++removedLinks;
                for (const NodeLink &link:node.links)
                    if (link.target==id)++removedLinks;
                for (const NodeLink &link:node.toggleTrueActions)
                    if (link.target==id)++removedLinks;
                for (const NodeLink &link:node.toggleFalseActions)
                    if (link.target==id)++removedLinks;
                if (node.toggleStateTargetId==id) {
                    ++removedLinks;
                    if (node.toggleTrueDialogueNode>=0)++removedLinks;
                    if (node.toggleFalseDialogueNode>=0)++removedLinks;
                removedLinks+=node.toggleTrueActions.size()+node.toggleFalseActions.size();
                }
            }
        }
        if (dialogueCard && m_objects.value(id.mid(QStringLiteral("@dialogue:").size())).dialogueNode>=0)
            ++removedLinks;
        // The confirmation above covers these linked-card removals too.
        if (dialogueCard) {
            disconnectDialogue(id.mid(QStringLiteral("@dialogue:").size()));
        } else {
            // For Trigger nodes, remove every outgoing action + its dialogue.
            // For any target node, remove ALL incoming links from every Trigger.
            // The Graph is a view; these are the only .sbgm fields we modify.
            for (const QString &source:m_order) {
                NodeObject node=m_objects.value(source);
                if (!isActionSource(node) && eventKinds(node.type).isEmpty() &&
                    node.logicNodes.isEmpty())continue;
                bool changed=false;
                if(source==id) {
                    for(auto &links:node.eventLinks)if(!links.isEmpty()) {links.clear();changed=true;}
                } else {
                    for(auto &links:node.eventLinks) {
                        const int before=links.size();
                        links.erase(std::remove_if(links.begin(),links.end(),
                            [&](const NodeLink &link){return link.target==id;}),links.end());
                        if(before!=links.size())changed=true;
                    }
                }
                if (source==id) {
                    if (!node.links.isEmpty()) { node.links.clear();changed=true; }
                    if (node.type!=QStringLiteral("trigger")) {
                        if(!node.logicNodes.isEmpty()) {node.logicNodes=QJsonArray();changed=true;}
                        if(changed) {m_objects.insert(source,node);m_touched.insert(source);m_dirty=true;}
                        continue;
                    }
                    if (node.dialogueNode>=0) {node.dialogueNode=-1;changed=true;}
                    m_npcDialogueRoutes.remove(source);
                    if (!node.toggleStateTargetId.isEmpty() || node.toggleTrueDialogueNode>=0 ||
                        node.toggleFalseDialogueNode>=0 || !node.toggleTrueActions.isEmpty() ||
                        !node.toggleFalseActions.isEmpty()) {
                        node.toggleStateTargetId.clear();node.toggleStateInputIds.clear();
                        node.toggleStateOperator=QStringLiteral("boolean");
                        node.toggleTrueDialogueNode=-1;
                        node.toggleFalseDialogueNode=-1;
                        node.toggleTrueActions.clear();node.toggleFalseActions.clear();changed=true;
                    }
                } else {
                    for (int i=node.links.size()-1;i>=0;--i)
                        if (node.links[i].target==id) {node.links.removeAt(i);changed=true;}
                    for (int i=node.toggleTrueActions.size()-1;i>=0;--i)
                        if (node.toggleTrueActions[i].target==id) {node.toggleTrueActions.removeAt(i);changed=true;}
                    for (int i=node.toggleFalseActions.size()-1;i>=0;--i)
                        if (node.toggleFalseActions[i].target==id) {node.toggleFalseActions.removeAt(i);changed=true;}
                    if (node.toggleStateInputIds.removeAll(id)>0)changed=true;
                    if (node.toggleStateTargetId==id && !node.toggleStateInputIds.isEmpty()) {
                        node.toggleStateTargetId=node.toggleStateInputIds.takeFirst();
                        changed=true;
                    } else if (node.toggleStateTargetId==id) {
                        node.toggleStateTargetId.clear();
                        node.toggleTrueDialogueNode=-1;
                        node.toggleFalseDialogueNode=-1;
                        node.toggleTrueActions.clear();node.toggleFalseActions.clear();
                        changed=true;
                        // The condition card is no longer connected to a real
                        // object; remove its visual branches as well.
                        for (const QString &key:{branchCardId(source,true),
                                                 branchCardId(source,false),toggleCardId(source)}) {
                            if (m_cards.contains(key)) {
                                // removeOrphanCard consults m_objects: publish
                                // the cleared state before removing its cards.
                                m_objects.insert(source,node);
                                removeOrphanCard(key);
                            }
                        }
                    }
                }
                if (node.type!=QStringLiteral("trigger") && node.logicNodes.isEmpty()) {
                    if(changed) {m_objects.insert(source,node);m_touched.insert(source);m_dirty=true;}
                    continue;
                }
                // Independent logic DAGs also reference Game Objects via
                // input IDs, action objectIds and direct RESULT bindings.
                // Detach every such reference before removing the card.
                QJsonArray cleaned;
                for (const QJsonValue &entry:node.logicNodes) {
                    QJsonObject logic=entry.toObject();
                    QJsonArray inputs;
                    for(const QJsonValue &v:logic.value(QStringLiteral("inputs")).toArray()) {
                        const QJsonObject ref=v.toObject();
                        if ((ref.value(QStringLiteral("kind")).toString()==QStringLiteral("object") &&
                             ref.value(QStringLiteral("id")).toString()==id) ||
                            (ref.value(QStringLiteral("kind")).toString()==QStringLiteral("event") &&
                             (ref.value(QStringLiteral("id")).toString()==QStringLiteral("@event:arrival:")+id ||
                              ref.value(QStringLiteral("id")).toString()==QStringLiteral("@event:hit:")+id ||
                              ref.value(QStringLiteral("id")).toString()==QStringLiteral("@event:destroy:")+id))) {changed=true;continue;}
                        inputs.append(v);
                    }
                    logic.insert(QStringLiteral("inputs"),inputs);
                    QJsonArray result;
                    for(const QJsonValue &v:logic.value(QStringLiteral("resultTargets")).toArray()) {
                        if (v.toString()==id) {changed=true;continue;}
                        result.append(v);
                    }
                    logic.insert(QStringLiteral("resultTargets"),result);
                    for(const QString &field:{QStringLiteral("trueActions"),QStringLiteral("falseActions")}) {
                        QJsonArray actions;
                        for(const QJsonValue &v:logic.value(field).toArray()) {
                            if(v.toObject().value(QStringLiteral("objectId")).toString()==id) {
                                changed=true;continue;
                            }
                            actions.append(v);
                        }
                        logic.insert(field,actions);
                    }
                    cleaned.append(logic);
                }
                if(changed)node.logicNodes=cleaned;
                if (changed) {
                    m_objects.insert(source,node);
                    m_touched.insert(source);
                    m_dirty=true;
                }
            }
        }
        // Removal of a Trigger recursively clears its attached purple card,
        // but does not destroy unrelated nodes merely because they are now
        // orphans. The separate Remove Orphans command remains available.
        if (!dialogueCard && m_objects.contains(id)) {
            if (!m_objects.value(id).logicNodes.isEmpty()) {
                for(const QJsonValue &v:m_objects.value(id).logicNodes) {
                    const QString key=graphKey(id,v.toObject().value(QStringLiteral("id")).toString());
                    for(const bool yes:{true,false})removeOrphanCard(graphDialogueKey(key,yes),true);
                    removeOrphanCard(key,true);
                }
                NodeObject owner=m_objects.value(id);owner.logicNodes=QJsonArray();
                m_objects.insert(id,owner);m_touched.insert(id);
            }
            for (const QString &key:{toggleCardId(id),branchCardId(id,true),branchCardId(id,false)}) {
                if (m_cards.contains(key))removeOrphanCard(key,true);
            }
        }
        const int removed=removeOrphanCard(id,true);
        if(removed && m_objects.contains(id) &&
           m_objects.value(id).type==QStringLiteral("npc")) {
            // Hiding the NPC card must not erase its required Start dialogue.
            // Graph action wires are still disconnected above, as requested.
            m_hiddenNpcCards.insert(id);
            m_dirty=true;
        }
        // Remaining cards should not vanish unexpectedly on the next open
        // just because deleting their neighbour made them disconnected.
        for (const QString &remaining:m_cards.keys())
            if (!connectedCardIds().contains(remaining))m_placedCards.insert(remaining);
        redrawLinks();
        if (removed)m_status->setText(tr("Removed %1 graph card(s), disconnected %2 link(s). Save Graph + World to apply the action changes. World objects/dialogues remain intact.")
            .arg(removed).arg(removedLinks));
    }
    void removeAllOrphans() {
        const QSet<QString> connected=connectedCardIds();
        int total=0;
        for (const QString &id:m_cards.keys())
            if (!connected.contains(id))++total;
        if (!total) {
            m_status->setText(tr("No orphaned graph cards found."));
            return;
        }
        if (QMessageBox::question(this,tr("Remove Orphaned Nodes"),
            tr("Remove %1 unconnected card(s) from the graph?\n\n"
               "Only the .vsgm layout changes. All Game Objects, dialogues and gameplay actions in .sbgm are preserved.").arg(total),
            QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes)!=QMessageBox::Yes)return;
        int removed=0;
        for (const QString &id:m_cards.keys())
            if (!connected.contains(id))removed+=removeOrphanCard(id);
        // Scrub stale explicitly placed IDs that no longer exist in this world.
        for (const QString &id:m_placedCards.values())
            if (!m_cards.contains(id))m_placedCards.remove(id);
        redrawLinks();
        m_status->setText(tr("Removed %1 orphaned graph card(s). The .sbgm world is unchanged.").arg(removed));
    }
    void showCardContextMenu(const QString &id,const QPoint &at) {
        if (!m_cards.contains(id))return;
        showDetails(id);
        QMenu menu(this);
        QAction *branch=nullptr,*clearBranch=nullptr;
        if(id.startsWith(QStringLiteral("@give:"))) {
            int dialogue=-1,answer=-1;
            if(!giveCardReference(id,&dialogue,&answer))return;
            QAction *advanced=menu.addAction(tr("Edit GIVE exchange in Adventure Editor..."));
            QAction *hide=menu.addAction(tr("Hide this conversation flow preview"));
            QAction *chosen=menu.exec(at);
            if(chosen==advanced)editGiveExchangeInPlace(dialogue,answer);
            else if(chosen==hide)hideConversationContaining(dialogue);
            return;
        }
        if(id.startsWith(QStringLiteral("@conversation:"))) {
            bool indexOk=false;
            const int index=id.mid(QStringLiteral("@conversation:").size()).toInt(&indexOk);
            if(!indexOk || index<0 || index>=m_dialogues.size())return;
            QHash<QAction*,QPair<int,QString>> routes;
            QMenu *disconnect=menu.addMenu(tr("Disconnect answer route"));
            const QJsonArray choices=m_dialogues.at(index).toObject().value(QStringLiteral("choices")).toArray();
            for(int option=0;option<choices.size() && option<3;++option) {
                const QJsonObject answer=choices.at(option).toObject();
                if(answer.value(QStringLiteral("text")).toString().trimmed().isEmpty())continue;
                const int next=answer.value(QStringLiteral("next")).toInt(-1);
                if(next>=0)routes.insert(disconnect->addAction(
                    tr("Answer %1: normal → #%2%3").arg(option+1).arg(next)
                        .arg(next==index?tr(" (SELF-LOOP)"):QString())),
                    qMakePair(option,QStringLiteral("next")));
                const int missing=answer.value(QStringLiteral("missingNext")).toInt(-1);
                if(answer.value(QStringLiteral("requires")).toInt(-1)>=0 && missing>=0)
                    routes.insert(disconnect->addAction(
                        tr("Answer %1: item missing → #%2%3").arg(option+1).arg(missing)
                            .arg(missing==index?tr(" (SELF-LOOP)"):QString())),
                        qMakePair(option,QStringLiteral("missingNext")));
            }
            disconnect->setEnabled(!routes.isEmpty());
            menu.addSeparator();
            QAction *advanced=menu.addAction(tr("Open this dialogue in Adventure Editor..."));
            QAction *hide=menu.addAction(tr("Hide this Conversation Flow preview"));
            QAction *selected=menu.exec(at);
            if(routes.contains(selected)) {
                const auto route=routes.value(selected);
                setConversationAnswer(index,route.first,route.second,-1);
                m_status->setText(tr("Disconnected Dialogue #%1, answer %2. Undo with Ctrl+Z.")
                    .arg(index).arg(route.first+1));
            } else if(selected==advanced)openConversationInAdventure(index);
            else if(selected==hide)hideConversationContaining(index);
            return;
        }
        if(id.startsWith(QStringLiteral("@graph:"))) {
            QJsonObject n;
            if(!lookupGraph(id,nullptr,nullptr,&n))return;
            QMenu *opMenu=menu.addMenu(tr("Logic operator"));
            QHash<QAction*,QString> operators;
            for(const QString &op:{QStringLiteral("boolean"),QStringLiteral("not"),
                                   QStringLiteral("and"),QStringLiteral("or")})
                operators.insert(opMenu->addAction(op.toUpper()),op);
            menu.addSeparator();
            QAction *trueDialogue=menu.addAction(tr("TRUE → Show Dialogue..."));
            QAction *falseDialogue=menu.addAction(tr("FALSE → Show Dialogue..."));
            QAction *remove=menu.addAction(tr("Delete Logic Node (disconnect links)"));
            QAction *selected=menu.exec(at);
            if(operators.contains(selected)) {
                n.insert(QStringLiteral("op"),operators.value(selected));
                graphUpdate(id,n);redrawLinks();showDetails(id);
            } else if(selected==trueDialogue || selected==falseDialogue) {
                const bool yes=selected==trueDialogue;
                const int old=n.value(yes?QStringLiteral("trueDialogueNode"):
                                    QStringLiteral("falseDialogueNode")).toInt(-1);
                const int chosen=browseDialogueTree(old);
                if(chosen!=-1)setGraphDialogue(id,yes,chosen);
                else if(old>=0)makeGraphDialogueCard(id,yes);
            } else if(selected==remove)removeSelectedNode();
            return;
        }
        if(id.startsWith(QStringLiteral("@graph-dialogue:"))) {
            const bool yes=id.startsWith(QStringLiteral("@graph-dialogue:true:"));
            const QString key=id.mid((yes?QStringLiteral("@graph-dialogue:true:"):
                QStringLiteral("@graph-dialogue:false:")).size());
            QAction *disconnect=menu.addAction(tr("Disconnect Dialogue"));
            if(menu.exec(at)==disconnect)setGraphDialogue(key,yes,-1);
            return;
        }
        if (id.startsWith(QStringLiteral("@toggle:"))) {
            const QString owner=id.mid(QStringLiteral("@toggle:").size());
            QMenu *operators=menu.addMenu(tr("Logic operator"));
            QHash<QAction*,QString> choices;
            for (const QPair<QString,QString> &option:{
                qMakePair(QStringLiteral("boolean"),tr("Boolean (one input)")),
                qMakePair(QStringLiteral("and"),tr("AND (2–16 inputs)")),
                qMakePair(QStringLiteral("or"),tr("OR (2–8 inputs)"))}) {
                QAction *item=operators->addAction(option.second);
                choices.insert(item,option.first);
            }
            QAction *convert=menu.addAction(tr("Convert to Independent Logic Node..."));
            QAction *remove=menu.addAction(tr("Delete Node (disconnect links)"));
            QAction *selected=menu.exec(at);
            if (choices.contains(selected)) {
                NodeObject n=m_objects.value(owner);
                if(choices.value(selected)==QStringLiteral("or") && n.toggleStateInputIds.size()>7) {
                    QMessageBox::information(this,tr("OR Inputs"),
                        tr("OR supports up to eight inputs. Disconnect extra inputs before switching this gate to OR."));
                    return;
                }
                n.toggleStateOperator=choices.value(selected);
                if (n.toggleStateOperator==QStringLiteral("boolean"))n.toggleStateInputIds.clear();
                m_objects.insert(owner,n);m_touched.insert(owner);m_dirty=true;
                refreshToggleCard(owner);redrawLinks();showDetails(id);
            } else if (selected==convert)convertLegacyToggle(owner);
            else if (selected==remove)removeSelectedNode();
            return;
        }
        if (id.startsWith(QStringLiteral("@toggle-dialogue:"))) {
            branch=menu.addAction(tr("Choose Dialogue from folders..."));
            clearBranch=menu.addAction(tr("Disconnect this dialogue"));
            menu.addSeparator();
        } else if (m_objects.contains(id) && m_objects.value(id).resourceIndex>=0 &&
                   m_objects.value(id).type!=QStringLiteral("trigger") &&
                   m_objects.value(id).type!=QStringLiteral("npc")) {
            branch=menu.addAction(tr("Logic → Boolean (read enabled state)"));
            menu.addSeparator();
        }
        QAction *npcOpening=nullptr,*npcAfter=nullptr;
        if(m_objects.contains(id) && m_objects.value(id).type==QStringLiteral("npc")) {
            const NodeObject npc=m_objects.value(id);
            if(npc.npcStartNode>=0 && npc.npcStartNode<m_dialogues.size())
                npcOpening=menu.addAction(tr("Show Opening Conversation Flow..."));
            if(npc.npcDoneNode>=0 && npc.npcDoneNode<m_dialogues.size())
                npcAfter=menu.addAction(tr("Show After-helped Conversation Flow..."));
            if(npcOpening || npcAfter)menu.addSeparator();
        }
        QAction *remove=menu.addAction(tr("Delete Node (disconnect links)"));
        remove->setToolTip(tr("Remove this card and its gameplay connections, not its underlying .sbgm object or dialogue."));
        QAction *cleanup=menu.addAction(tr("Remove All Orphaned Nodes..."));
        QAction *selected=menu.exec(at);
        if(selected==npcOpening && npcOpening) {
            showConversationFlow(m_objects.value(id).npcStartNode);
        } else if(selected==npcAfter && npcAfter) {
            showConversationFlow(m_objects.value(id).npcDoneNode);
        } else if (selected==branch && m_objects.contains(id)) {
            createGraphLogic(id,m_cards.value(id)->pos()+QPointF(360,30),QStringLiteral("boolean"));
        } else if (selected==branch || selected==clearBranch) {
            const bool yes=id.startsWith(QStringLiteral("@toggle-dialogue:true:"));
            const QString prefix=yes?QStringLiteral("@toggle-dialogue:true:"):QStringLiteral("@toggle-dialogue:false:");
            if (selected==clearBranch)setBranchDialogue(id.mid(prefix.size()),yes,-1,QPointF());
            else selectBranchDialogue((yes?QStringLiteral("@stateout:true:"):QStringLiteral("@stateout:false:"))+
                id.mid(prefix.size()),m_cards.value(id)->pos());
        } else if (selected==remove)removeSelectedNode();
        else if (selected==cleanup)removeAllOrphans();
    }
    void hideDisconnectedCards() {
        const QSet<QString> linked=linkedObjectIds();
        for (const QString &id:m_order) {
            if (linked.contains(id) || m_placedCards.contains(id) || !m_cards.contains(id))continue;
            NodeCard *card=m_cards.take(id);
            m_scene->removeItem(card);
            delete card;
            for (int i=m_list->count()-1;i>=0;--i)
                if (m_list->item(i)->data(Qt::UserRole).toString()==id)
                    delete m_list->takeItem(i);
            if (m_selectedCardId==id) {
                m_selectedCardId.clear();
                m_details->clear();
                m_linksList->clear();
            }
        }
    }
    void removeConnection(const QString &from,int index) {
        if (!m_objects.contains(from))return;
        NodeObject node=m_objects.value(from);
        if (!isActionSource(node) || index<0 || index>=node.links.size())return;
        node.links.removeAt(index);
        m_objects.insert(from,node);
        m_touched.insert(from);
        m_dirty=true;
        hideDisconnectedCards();
        redrawLinks();
        if (m_cards.contains(from))showDetails(from);
    }
    void linkContextMenu(const QList<QPair<QString,int>> &links,const QPoint &globalPoint) {
        QMenu menu(this);
        QHash<QAction*,QPair<QString,int>> actionTargets;
        for (const QPair<QString,int> &ref:links) {
            if(isEventOutput(ref.first)) {
                const QString owner=eventOwner(ref.first),key=eventKey(ref.first);
                const NodeObject node=m_objects.value(owner);
                const QVector<NodeLink> eventActions=node.eventLinks.value(key);
                if(ref.second<0 || ref.second>=eventActions.size())continue;
                const NodeLink link=eventActions.at(ref.second);
                QMenu *actions=menu.addMenu(tr("%1 · %2 → %3")
                    .arg(node.name,eventLabel(key),m_objects.value(link.target).name));
                if(!isPlayerCommand(link.target))
                    for(const QPair<QString,QString> &choice:{
                        qMakePair(QStringLiteral("enable"),tr("Set Enable")),
                        qMakePair(QStringLiteral("disable"),tr("Set Disable")),
                        qMakePair(QStringLiteral("toggle"),tr("Set Toggle"))}) {
                        QAction *action=actions->addAction(choice.second);
                        action->setData(choice.first);actionTargets.insert(action,ref);
                    }
                QAction *remove=actions->addAction(tr("Remove Connection"));
                remove->setData(QStringLiteral("remove"));actionTargets.insert(remove,ref);
                continue;
            }
            const NodeObject node=m_objects.value(ref.first);
            if (!isActionSource(node))continue;
            // -1 identifies a purple Show Dialogue wire. It has no
            // Enable/Disable/Toggle action, only Disconnect.
            if (ref.second<=-1000) {
                const bool yes=ref.second>-2000;
                const int index=(yes?-1000:-2000)-ref.second;
                const QVector<NodeLink> &links= yes?node.toggleTrueActions:node.toggleFalseActions;
                if (index<0 || index>=links.size())continue;
                const NodeLink link=links.at(index);
                QMenu *actions=&menu;
                // Always identify the exact TRUE/FALSE action being edited,
                // even when two differently sourced wires overlap.
                actions=menu.addMenu(tr("%1 %2 → %3: %4")
                        .arg(node.name,yes?tr("TRUE"):tr("FALSE"),
                             m_objects.value(link.target).name,link.action));
                if(!isPlayerCommand(link.target))for (const QPair<QString,QString> &choice:{
                         qMakePair(QStringLiteral("enable"),tr("Set Enable")),
                         qMakePair(QStringLiteral("disable"),tr("Set Disable")),
                         qMakePair(QStringLiteral("toggle"),tr("Set Toggle"))}) {
                    QAction *action=actions->addAction(choice.second);
                    action->setData(choice.first);actionTargets.insert(action,ref);
                }
                QAction *remove=actions->addAction(tr("Remove Connection"));
                remove->setData(QStringLiteral("remove"));actionTargets.insert(remove,ref);
                continue;
            }
            if (ref.second<=-10 && ref.second>=-25) {
                const int input=-10-ref.second;
                QStringList sources{node.toggleStateTargetId};
                sources.append(node.toggleStateInputIds);
                if (input>=sources.size())continue;
                QMenu *actions=&menu;
                if (links.size()>1)actions=menu.addMenu(tr("%1 state → %2")
                    .arg(m_objects.value(sources.at(input)).name,node.toggleStateOperator.toUpper()));
                QAction *remove=actions->addAction(tr("Remove Connection"));
                remove->setData(QStringLiteral("remove"));actionTargets.insert(remove,ref);
                continue;
            }
            if (ref.second<=-2) {
                QAction *remove=menu.addAction(tr("Remove Connection"));
                remove->setData(QStringLiteral("remove"));actionTargets.insert(remove,ref);
                continue;
            }
            if (ref.second==-1) {
                if (node.dialogueNode<0)continue;
                QMenu *actions=&menu;
                if (links.size()>1)
                    actions=menu.addMenu(tr("%1 → Show Dialogue %2")
                        .arg(node.name).arg(node.dialogueNode));
                QAction *remove=actions->addAction(tr("Remove Connection"));
                remove->setData(QStringLiteral("remove"));
                actionTargets.insert(remove,ref);
                continue;
            }
            if (ref.second<0 || ref.second>=node.links.size())continue;
            const NodeLink link=node.links.at(ref.second);
            QMenu *actions=&menu;
            if (links.size()>1) {
                const QString target=m_objects.contains(link.target)
                    ?m_objects.value(link.target).name:link.target;
                actions=menu.addMenu(tr("%1 → %2: %3 (#%4)")
                    .arg(node.name,target,link.action,QString::number(ref.second+1)));
            }
            if(!isPlayerCommand(link.target))for (const QPair<QString,QString> &choice : {
                     qMakePair(QStringLiteral("enable"),tr("Set Enable")),
                     qMakePair(QStringLiteral("disable"),tr("Set Disable")),
                     qMakePair(QStringLiteral("toggle"),tr("Set Toggle"))}) {
                QAction *action=actions->addAction(choice.second);
                action->setData(choice.first);
                actionTargets.insert(action,ref);
            }
            actions->addSeparator();
            QAction *remove=actions->addAction(tr("Remove Connection"));
            remove->setData(QStringLiteral("remove"));
            actionTargets.insert(remove,ref);
        }
        if (actionTargets.isEmpty())return;
        QAction *selected=menu.exec(globalPoint);
        if (!selected || !actionTargets.contains(selected))return;
        const QPair<QString,int> ref=actionTargets.value(selected);
        const QString operation=selected->data().toString();
        if (isEventOutput(ref.first)) {
            const QString owner=eventOwner(ref.first),key=eventKey(ref.first);
            NodeObject node=m_objects.value(owner);
            QVector<NodeLink> &actions=node.eventLinks[key];
            if(ref.second<0 || ref.second>=actions.size())return;
            if(operation==QStringLiteral("remove"))actions.removeAt(ref.second);
            else if(supportedAction(operation) && !isPlayerCommand(actions[ref.second].target))
                actions[ref.second].action=operation;
            else return;
            m_objects.insert(owner,node);m_touched.insert(owner);m_dirty=true;
            hideDisconnectedCards();redrawLinks();showDetails(owner);
            return;
        }
        if (operation==QStringLiteral("remove")) {
            if (ref.second==-1)disconnectDialogue(ref.first);
            else if (ref.second<=-10 && ref.second>=-25) {
                const int input=-10-ref.second;
                NodeObject node=m_objects.value(ref.first);
                if (input==0) {
                    if (node.toggleStateInputIds.isEmpty())removeToggleCondition(ref.first);
                    else {
                        node.toggleStateTargetId=node.toggleStateInputIds.takeFirst();
                        m_objects.insert(ref.first,node);m_touched.insert(ref.first);m_dirty=true;
                        refreshToggleCard(ref.first);redrawLinks();
                    }
                } else if (input-1<node.toggleStateInputIds.size()) {
                    node.toggleStateInputIds.removeAt(input-1);
                    m_objects.insert(ref.first,node);m_touched.insert(ref.first);m_dirty=true;
                    refreshToggleCard(ref.first);redrawLinks();
                }
            }
            else if (ref.second==-2)removeToggleCondition(ref.first);
            else if (ref.second==-3 || ref.second==-4)
                setBranchDialogue(ref.first,ref.second==-3,-1,QPointF());
            else if (ref.second<=-1000)
                removeBranchConnection(ref.first,ref.second>-2000,
                    (ref.second>-2000?-1000:-2000)-ref.second);
            else removeConnection(ref.first,ref.second);
            return;
        }
        if (!supportedAction(operation))return;
        if (ref.second<=-1000) {
            NodeObject node=m_objects.value(ref.first);
            const bool yes=ref.second>-2000;
            const int index=(yes?-1000:-2000)-ref.second;
            QVector<NodeLink> &links=yes?node.toggleTrueActions:node.toggleFalseActions;
            if (index<0 || index>=links.size() || isPlayerCommand(links[index].target))return;
            links[index].action=operation;
            m_objects.insert(ref.first,node);m_touched.insert(ref.first);m_dirty=true;
            redrawLinks();showDetails(toggleCardId(ref.first));return;
        }
        if (ref.second<0)return;
        NodeObject node=m_objects.value(ref.first);
        if (ref.second>=node.links.size() || isPlayerCommand(node.links[ref.second].target))return;
        node.links[ref.second].action=operation;
        m_objects.insert(ref.first,node);
        m_touched.insert(ref.first);
        m_dirty=true;
        redrawLinks();
        showDetails(ref.first);
    }
    QJsonObject graphJson() const {
        QJsonObject root;
        root.insert(QStringLiteral("format"),QStringLiteral("SIDBOX-VISUAL-NODES"));
        root.insert(QStringLiteral("version"),1);
        root.insert(QStringLiteral("world"),m_worldName);
        if(m_splitter) {
            const QList<int> widths=m_splitter->sizes();
            if(widths.size()==3)
                root.insert(QStringLiteral("paneWidths"),
                    QJsonArray{widths.at(0),widths.at(1),widths.at(2)});
        }
        QJsonObject positions;
        QJsonArray placedCards;
        for (const QString &id:m_order)
            if (m_placedCards.contains(id))placedCards.append(id);
        for (const QString &id:m_order)
            if (m_placedCards.contains(dialogueCardId(id)))placedCards.append(dialogueCardId(id));
        for (const QString &id:m_order)
            if (m_placedCards.contains(toggleCardId(id)))placedCards.append(toggleCardId(id));
        root.insert(QStringLiteral("placedCards"),placedCards);
        for (const QString &id:m_order) {
            if (!m_cards.contains(id))continue;
            // Scene item position is authoritative. Mouse dragging may update
            // between the final move event and a Save Graph click.
            const QPointF p=m_cards.value(id)->pos();
            positions.insert(id,QJsonArray{p.x(),p.y()});
        }
        for (const QString &id:m_dialogueCards) {
            const QString key=dialogueCardId(id);
            if (m_cards.contains(key)) {
                const QPointF p=m_cards.value(key)->pos();
                positions.insert(key,QJsonArray{p.x(),p.y()});
            }
        }
        for (auto it=m_cards.constBegin();it!=m_cards.constEnd();++it) {
            if (it.key().startsWith(QStringLiteral("@graph:")) ||
                it.key().startsWith(QStringLiteral("@graph-dialogue:")) ||
                it.key().startsWith(QStringLiteral("@conversation:")) ||
                it.key().startsWith(QStringLiteral("@give:"))) {
                const QPointF pt=it.value()->pos();
                positions.insert(it.key(),QJsonArray{pt.x(),pt.y()});
                continue;
            }
            if (!it.key().startsWith(QStringLiteral("@toggle:")) &&
                !it.key().startsWith(QStringLiteral("@toggle-dialogue:")))continue;
            const QPointF pt=it.value()->pos();
            positions.insert(it.key(),QJsonArray{pt.x(),pt.y()});
        }
        for(auto it=m_flowGroups.constBegin();it!=m_flowGroups.constEnd();++it) {
            if(!it.value())continue;
            const QPointF pt=it.value()->pos();
            positions.insert(flowGroupId(it.key()),QJsonArray{pt.x(),pt.y()});
        }
        root.insert(QStringLiteral("positions"),positions);
        QJsonArray collapsed;
        for(const QString &id:m_collapsedCards)
            if(m_cards.contains(id) || id.startsWith(QStringLiteral("@flowgroup:")))collapsed.append(id);
        root.insert(QStringLiteral("collapsedCards"),collapsed);
        QJsonArray hiddenNpc;
        for(const QString &id:m_hiddenNpcCards)
            if(m_objects.contains(id) && m_objects.value(id).type==QStringLiteral("npc"))
                hiddenNpc.append(id);
        root.insert(QStringLiteral("hiddenNpcCards"),hiddenNpc);
        QJsonArray dialogueCards;
        for (const QString &id:m_order)
            if (m_dialogueCards.contains(id) &&
                (m_placedCards.contains(dialogueCardId(id)) ||
                 m_objects.value(id).dialogueNode>=0))dialogueCards.append(id);
        root.insert(QStringLiteral("dialogueCards"),dialogueCards);
        QJsonObject npcRoutes;
        for(auto it=m_npcDialogueRoutes.constBegin();it!=m_npcDialogueRoutes.constEnd();++it) {
            const int dialogue=it.value().value(QStringLiteral("dialogue")).toInt(-1);
            // UI hints only: a route cannot create/alter a gameplay action.
            if(dialogue>=0 && m_objects.value(it.value().value(QStringLiteral("npc")).toString()).type==
                QStringLiteral("npc"))npcRoutes.insert(it.key(),it.value());
        }
        root.insert(QStringLiteral("npcDialogueRoutes"),npcRoutes);
        QJsonObject sharedDialogueRoutes;
        for(auto it=m_graphDialogueRoutes.constBegin();it!=m_graphDialogueRoutes.constEnd();++it) {
            const QString own=it.key(), target=it.value();
            const bool yes=own.startsWith(QStringLiteral("@graph-dialogue:true:"));
            const QString prefix=yes?QStringLiteral("@graph-dialogue:true:"):
                QStringLiteral("@graph-dialogue:false:");
            QJsonObject node;
            if(!own.startsWith(prefix) || !lookupGraph(own.mid(prefix.size()),nullptr,nullptr,&node))continue;
            const int dialogue=node.value(yes?QStringLiteral("trueDialogueNode"):
                QStringLiteral("falseDialogueNode")).toInt(-1);
            if(dialogue>=0 && validSharedGraphDialogue(own,dialogue) && target!=own)
                sharedDialogueRoutes.insert(own,target);
        }
        root.insert(QStringLiteral("graphDialogueRoutes"),sharedDialogueRoutes);
        QJsonArray conversationRoots;
        QList<int> roots=m_conversationRoots.values();
        std::sort(roots.begin(),roots.end());
        for(int root:roots)if(root>=0 && m_cards.contains(conversationCardId(root)))
            conversationRoots.append(root);
        root.insert(QStringLiteral("conversationFlowRoots"),conversationRoots);
        QJsonArray hiddenConversationRoots;
        QList<int> hiddenRoots=m_hiddenConversationRoots.values();
        std::sort(hiddenRoots.begin(),hiddenRoots.end());
        for(int root:hiddenRoots)if(root>=0 && m_conversationRoots.contains(root))
            hiddenConversationRoots.append(root);
        root.insert(QStringLiteral("hiddenConversationFlowRoots"),hiddenConversationRoots);
        // No connection snapshots: on every open, .sbgm is the ONLY source
        // of actual trigger actions and dialogue references.
        if (m_viewReady)root.insert(QStringLiteral("view"),viewportJson());
        return root;
    }
    bool saveLayout() {
        QFile existing(m_graphPath);
        if (existing.exists()) {
            if (!existing.open(QIODevice::ReadOnly)) return false;
            if (QCryptographicHash::hash(existing.readAll(),QCryptographicHash::Sha256)!=m_layoutHash)
                return fail(tr("The .vsgm was changed by another editor. Reopen it before saving."));
        } else if (!m_layoutHash.isEmpty()) {
            return fail(tr("The .vsgm was deleted while you were editing. Save cancelled."));
        }
        const QJsonObject graph=graphJson();
        if (!writeJson(m_graphPath,graph))return false;
        m_layoutHash=QCryptographicHash::hash(QJsonDocument(graph).toJson(QJsonDocument::Indented),
                                               QCryptographicHash::Sha256);
        return true;
    }
    bool saveAll() {
        // Never overwrite another editor's newer changes to this .sbgm.
        QFile input(m_worldPath);
        if (!input.open(QIODevice::ReadOnly))return fail(tr("Cannot reopen the source .sbgm."));
        const QByteArray current=input.readAll();
        if (QCryptographicHash::hash(current,QCryptographicHash::Sha256)!=m_originalHash)
            return fail(tr("The .sbgm changed in another editor since this graph opened.\n"
                           "Close this graph and reopen it to avoid overwriting those changes."));
        if (!m_touched.isEmpty() || m_dialoguesChanged || m_npcsChanged) {
            for(const QString &owner:m_touched) {
                const NodeObject n=m_objects.value(owner);
                if(n.logicNodes.isEmpty())continue;
                QVector<SidboxVisualLogic::Node> parsed;
                QVector<int> schedule;
                QString issue;
                QSet<QString> locals;
                for(const QString &id:m_order)
                    if(m_objects.value(id).resourceIndex>=0 &&
                       m_objects.value(id).type!=QStringLiteral("npc")) {
                        locals.insert(id);
                        if(m_objects.value(id).type==QStringLiteral("lift"))
                            locals.insert(QStringLiteral("@event:arrival:")+id);
                        if(m_objects.value(id).type==QStringLiteral("breakable")) {
                            locals.insert(QStringLiteral("@event:hit:")+id);
                            locals.insert(QStringLiteral("@event:destroy:")+id);
                        }
                    }
                if(!SidboxVisualLogic::read(n.logicNodes,&parsed,&issue) ||
                   !SidboxVisualLogic::order(parsed,locals,&schedule,&issue))
                    return fail(tr("%1: %2").arg(n.name,issue));
            }
            for (const QString &id:m_touched) {
                const NodeObject node=m_objects.value(id);
                if (node.type!=QStringLiteral("trigger"))continue;
                const int count=(node.toggleStateTargetId.isEmpty()?0:1)+
                    (node.toggleStateOperator==QStringLiteral("boolean")?0:node.toggleStateInputIds.size());
                if ((!node.toggleStateTargetId.isEmpty() ||
                     !node.toggleTrueActions.isEmpty() || !node.toggleFalseActions.isEmpty() ||
                     node.toggleTrueDialogueNode>=0 || node.toggleFalseDialogueNode>=0) &&
                    ((node.toggleStateOperator==QStringLiteral("and") && (count<2 || count>16)) ||
                     (node.toggleStateOperator==QStringLiteral("or") && (count<2 || count>8)) ||
                     (node.toggleStateOperator==QStringLiteral("boolean") && count!=1)))
                    return fail(tr("%1: incomplete %2 state condition. Connect the required Game Object inputs before saving.")
                        .arg(node.name,node.toggleStateOperator.toUpper()));
            }
            QJsonArray resources=m_world.value(QStringLiteral("resources")).toArray();
            // A plain sprite is scenery, not part of gameworlditems. Promote it
            // only when graph logic ACTUALLY references it. This makes its
            // enable/disable/toggle actions real, saved and drawn by the world
            // object runtime, without changing unrelated scenery or the player.
            QSet<QString> actionTargets;
            for (const QString &id:m_order) {
                const NodeObject owner=m_objects.value(id);
                if (!isActionSource(owner) && eventKinds(owner.type).isEmpty() &&
                    owner.logicNodes.isEmpty())continue;
                for (const NodeLink &link:owner.links)
                    if (supportedAction(link.action)) actionTargets.insert(link.target);
                for(const QVector<NodeLink> &links:owner.eventLinks)
                    for(const NodeLink &link:links)
                        if(supportedAction(link.action))actionTargets.insert(link.target);
                // Legacy Boolean branches remain Trigger-only; independent DAGs
                // can also belong to Stompable Enemies.
                if (owner.type==QStringLiteral("trigger")) {
                for (const NodeLink &link:owner.toggleTrueActions)
                    if (supportedAction(link.action)) actionTargets.insert(link.target);
                for (const NodeLink &link:owner.toggleFalseActions)
                    if (supportedAction(link.action)) actionTargets.insert(link.target);
                if (!owner.toggleStateTargetId.isEmpty())
                    actionTargets.insert(owner.toggleStateTargetId);
                for (const QString &input:owner.toggleStateInputIds) actionTargets.insert(input);
                }
                // Independent logic nodes can reference decorations as either
                // value inputs or TRUE/FALSE action targets.
                for (const QJsonValue &value:owner.logicNodes) {
                    const QJsonObject logic=value.toObject();
                    for (const QJsonValue &v:logic.value(QStringLiteral("inputs")).toArray()) {
                        const QJsonObject input=v.toObject();
                        if (input.value(QStringLiteral("kind")).toString()==QStringLiteral("object"))
                            actionTargets.insert(input.value(QStringLiteral("id")).toString());
                    }
                    for (const QString &branch:{QStringLiteral("trueActions"),QStringLiteral("falseActions")})
                        for (const QJsonValue &v:logic.value(branch).toArray())
                            actionTargets.insert(v.toObject().value(QStringLiteral("objectId")).toString());
                    for (const QJsonValue &v:logic.value(QStringLiteral("resultTargets")).toArray())
                        actionTargets.insert(v.toString());
                }
            }
            for (const QString &id:actionTargets) {
                if (!m_objects.contains(id) || m_objects.value(id).type!=QStringLiteral("decoration"))
                    continue;
                NodeObject decoration=m_objects.value(id);
                if (decoration.resourceIndex<0 || decoration.resourceIndex>=resources.size())continue;
                QJsonObject resource=resources.at(decoration.resourceIndex).toObject();
                if (resource.value(QStringLiteral("id")).toString()!=id)continue;
                const QString path=resource.value(QStringLiteral("path")).toString();
                const int scale=resource.value(QStringLiteral("scale")).toInt(100);
                if (path.isEmpty() || !path.endsWith(QStringLiteral(".ppb"),Qt::CaseInsensitive) || scale!=100)
                    return fail(tr("Decoration '%1' must use a PPB sprite at 100% scale before it can be controlled by logic.")
                        .arg(decoration.name));
                QJsonObject object=resource.value(QStringLiteral("gameObject")).toObject();
                object.insert(QStringLiteral("type"),QStringLiteral("decoration_object"));
                resource.insert(QStringLiteral("gameObject"),object);
                resources.replace(decoration.resourceIndex,resource);
                decoration.type=QStringLiteral("decoration_object");
                m_objects.insert(id,decoration);
            }
            for (const QString &id:m_touched) {
                const NodeObject node=m_objects.value(id);
                if(node.resourceIndex<0 || node.resourceIndex>=resources.size())continue;
                const bool hadGraphField=resources.at(node.resourceIndex).toObject()
                    .value(QStringLiteral("gameObject")).toObject()
                    .contains(QStringLiteral("logicNodes"));
                if(!isActionSource(node) && eventKinds(node.type).isEmpty() &&
                   node.logicNodes.isEmpty() && !hadGraphField)continue;
                QJsonObject resource=resources.at(node.resourceIndex).toObject();
                if (resource.value(QStringLiteral("id")).toString()!=id)
                    return fail(tr("Game Object IDs changed. Refusing to rewrite the world."));
                QJsonObject object=resource.value(QStringLiteral("gameObject")).toObject();
                if(isActionSource(node))object.insert(QStringLiteral("targetObjectId"),node.links.isEmpty()
                    ?QString():node.links.first().target);
                if(isActionSource(node))object.insert(QStringLiteral("targetAction"),node.links.isEmpty()
                    ?QStringLiteral("none"):node.links.first().action);
                QJsonObject events=object.value(QStringLiteral("eventActions")).toObject();
                for(const QString &key:eventKinds(node.type)) {
                    QJsonArray actions;
                    for(const NodeLink &link:node.eventLinks.value(key))
                        actions.append(QJsonObject{{QStringLiteral("objectId"),link.target},
                            {QStringLiteral("action"),link.action}});
                    if(actions.isEmpty())events.remove(key);
                    else events.insert(key,actions);
                }
                object.insert(QStringLiteral("eventActions"),events);
                if (node.type==QStringLiteral("enemy")) {
                    QJsonArray extras;
                    for (int i=1;i<node.links.size();++i)
                        extras.append(QJsonObject{{QStringLiteral("objectId"),node.links[i].target},
                                                  {QStringLiteral("action"),node.links[i].action}});
                    object.insert(QStringLiteral("enemyDefeatExtraActions"),extras);
                    object.insert(QStringLiteral("logicNodes"),node.logicNodes);
                    resource.insert(QStringLiteral("gameObject"),object);
                    resources.replace(node.resourceIndex,resource);
                    continue;
                }
                if (node.type!=QStringLiteral("trigger")) {
                    if(node.type!=QStringLiteral("collectable") &&
                       node.type!=QStringLiteral("npc") && node.type!=QStringLiteral("player_action"))
                        object.insert(QStringLiteral("logicNodes"),node.logicNodes);
                    resource.insert(QStringLiteral("gameObject"),object);
                    resources.replace(node.resourceIndex,resource);
                    continue; // Never write Trigger fields into a key.
                }
                QJsonArray extras;
                for (int i=1;i<node.links.size();++i)
                    extras.append(QJsonObject{{QStringLiteral("objectId"),node.links[i].target},
                                              {QStringLiteral("action"),node.links[i].action}});
                object.insert(QStringLiteral("triggerExtraActions"),extras);
                object.insert(QStringLiteral("interactDialogueNode"),node.dialogueNode);
                object.insert(QStringLiteral("interactDialogueMode"),node.dialogueMode);
                object.insert(QStringLiteral("logicNodes"),node.logicNodes);
                object.insert(QStringLiteral("triggerPress"),node.triggerPress);
                object.insert(QStringLiteral("triggerOneShot"),node.triggerOneShot);
                object.insert(QStringLiteral("interactItemName"),node.interactItemName);
                object.insert(QStringLiteral("toggleStateTargetId"),node.toggleStateTargetId);
                object.insert(QStringLiteral("toggleStateOperator"),node.toggleStateOperator);
                QJsonArray stateInputs;
                for (const QString &input:node.toggleStateInputIds) stateInputs.append(input);
                object.insert(QStringLiteral("toggleStateInputIds"),stateInputs);
                object.insert(QStringLiteral("toggleTrueDialogueNode"),node.toggleTrueDialogueNode);
                object.insert(QStringLiteral("toggleFalseDialogueNode"),node.toggleFalseDialogueNode);
                for (const bool yes:{true,false}) {
                    QJsonArray links;
                    const QVector<NodeLink> &actions=yes?node.toggleTrueActions:node.toggleFalseActions;
                    for (const NodeLink &link:actions)
                        links.append(QJsonObject{{QStringLiteral("objectId"),link.target},
                                                 {QStringLiteral("action"),link.action}});
                    object.insert(yes?QStringLiteral("toggleTrueActions"):
                                      QStringLiteral("toggleFalseActions"),links);
                }
                resource.insert(QStringLiteral("gameObject"),object);
                resources.replace(node.resourceIndex,resource);
            }
            QJsonObject next=m_world;
            next.insert(QStringLiteral("resources"),resources);
            if (m_dialoguesChanged || m_npcsChanged) {
                QJsonObject adventure=next.value(QStringLiteral("adventure")).toObject();
                if(m_dialoguesChanged)adventure.insert(QStringLiteral("nodes"),m_dialogues);
                if(m_npcsChanged)adventure.insert(QStringLiteral("npcs"),m_npcEntries);
                next.insert(QStringLiteral("adventure"),adventure);
            }
            // Keep one backup per save for recovery without touching game builds.
            const QString backup=m_worldPath+QStringLiteral(".vsgm-backup");
            QFile::remove(backup);
            if (!QFile::copy(m_worldPath,backup))
                return fail(tr("Could not back up the world design. Save cancelled."));
            if (!writeJson(m_worldPath,next))
                return fail(tr("Could not save the updated .sbgm. Your backup is at:\n%1").arg(backup));
            m_world=next;
            const QByteArray saved=QJsonDocument(m_world).toJson(QJsonDocument::Indented);
            m_originalHash=QCryptographicHash::hash(saved,QCryptographicHash::Sha256);
            m_worldChanged=true;
            m_touched.clear();
            m_dialoguesChanged=false;
            m_npcsChanged=false;
        }
        if (!saveLayout())return fail(tr("Could not save .vsgm layout."));
        m_dirty=false;
        resetGraphHistory(); // A save becomes the new undo baseline; never replay a stale .sbgm snapshot.
        m_status->setText(tr("Saved. Gameplay links are in .sbgm; .vsgm remembers only placed cards and the view."));
        return true;
    }
    bool fail(const QString &message) {
        QMessageBox::warning(this,tr("Visual Nodes"),message);return false;
    }
    IDETheme m_theme;
    QString m_controlsStyle;
    QString m_graphPath,m_worldPath,m_worldName;
    QJsonObject m_world;
    QByteArray m_originalHash,m_layoutHash;
    QHash<QString,NodeObject> m_objects;
    struct DialogueControls {
        QComboBox *picker=nullptr;
        QComboBox *mode=nullptr;
        QLineEdit *speaker=nullptr;
        QPlainTextEdit *message=nullptr;
        QLabel *info=nullptr;
    };
    QJsonArray m_dialogues;
    QJsonArray m_dialogueFolders;
    QJsonArray m_npcEntries;
    bool m_dialoguesChanged=false, m_npcsChanged=false;
    QSet<QString> m_dialogueCards;
    QSet<QString> m_placedCards; // Only explicitly placed unconnected cards; .sbgm owns links.
    QSet<QString> m_collapsedCards; // Pure UI preference; stored only in .vsgm.
    QSet<QString> m_hiddenNpcCards; // Hiding an NPC never destroys its opening dialogue.
    QSet<int> m_conversationRoots; // Selected flow roots; .sbgm is authoritative.
    QSet<int> m_hiddenConversationRoots; // Hidden flow groups preserve layout for reopening.
    QHash<QString,QJsonObject> m_npcDialogueRoutes; // .vsgm-only visual wire destinations.
    QHash<QString,QString> m_graphDialogueRoutes; // .vsgm-only: multiple action wires share one existing card.
    QHash<QString,DialogueControls> m_dialogueControls;
    QHash<QString,QGraphicsSimpleTextItem*> m_booleanSourceLabels;
    QHash<QString,QGraphicsSimpleTextItem*> m_logicTitles;
    QHash<QString,QGraphicsSimpleTextItem*> m_logicNotes;
    QStringList m_order;
    QHash<QString,QPointF> m_positions;
    QHash<QString,NodeCard*> m_cards;
    QHash<int,FlowGroupBox*> m_flowGroups;
    bool m_movingFlowGroup=false;
    QSet<QString> m_touched;
    QList<QGraphicsPathItem*> m_lines;
    // Live drag cache: wire identity remains stable between mouse press/release.
    // Only lines incident to the moved card are changed per mouse event.
    QHash<QString,QList<QGraphicsPathItem*>> m_liveWiresByCard;
    QHash<QString,QPointF> m_liveWirePositions;
    bool m_liveWireDrag=false;
    int m_openAdventureDialogue=-1;
    bool m_dirty=false,m_worldChanged=false;
    bool m_hasStoredView=false,m_hasStoredScroll=false,m_viewReady=false;
    qreal m_storedZoom=1.0;
    QPointF m_storedCenter;
    QPoint m_storedScroll;
    QSize m_storedViewport;
    QPointF m_flowAnchor;
    QGraphicsScene *m_scene=nullptr;
    NodeCanvas *m_view=nullptr;
    QListWidget *m_list=nullptr; // Hidden registration model; mirrored into the tree.
    QTreeWidget *m_visibleTree=nullptr;
    QLineEdit *m_treeSearch=nullptr;
    QSet<QString> m_treeCollapsed;
    bool m_treeRefreshPending=false;
    QTreeWidget *m_inspectorTree=nullptr;
    QLabel *m_inspectorTitle=nullptr;
    QLabel *m_inspectorType=nullptr;
    QPushButton *m_technicalButton=nullptr;
    QLabel *m_actionsHeader=nullptr;
    QSplitter *m_splitter=nullptr;
    QList<int> m_savedPaneWidths;
    QListWidget *m_linksList=nullptr;
    QPushButton *m_editLinkButton=nullptr;
    QPushButton *m_removeLinkButton=nullptr;
    QPushButton *m_removeSelectedButton=nullptr;
    QPushButton *m_removeOrphansButton=nullptr;
    QString m_selectedCardId;
    QSet<QString> m_multiSelectedCards; // UI-only selection, never saved to .vsgm.
    QString m_selectedWireKey; // Transient selection; never written to .sbgm/.vsgm.
    QTextEdit *m_details=nullptr;
    QLabel *m_status=nullptr;
    QVector<GraphHistory> m_history;
    int m_historyPos=-1,m_historyQuiet=0;
    bool m_restoringHistory=false;
    QByteArray m_historyObserved;
    QTimer *m_historyWatch=nullptr;
    QPushButton *m_historyUndoButton=nullptr,*m_historyRedoButton=nullptr;
};
}

bool openGameVisualNodes(QWidget *parent, const QString &vsgmPath, const IDETheme &theme, int *openAdventureDialogue) {
    bool worldChanged=false;
    if(openAdventureDialogue)*openAdventureDialogue=-1;
    for (;;) {
        VisualNodesDialog dialog(vsgmPath,theme,parent);
        if (!dialog.initialise())return worldChanged;
        const int result=dialog.exec();
        worldChanged=worldChanged || dialog.worldChanged();
        if(result==3 && openAdventureDialogue)*openAdventureDialogue=dialog.requestedAdventureDialogue();
        if(result!=2)break; // Refresh requested: rebuild from saved .sbgm.
    }
    return worldChanged;
}
