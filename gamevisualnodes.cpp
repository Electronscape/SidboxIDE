#include "gamevisualnodes.h"

#include <QCryptographicHash>
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
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QSignalBlocker>
#include <QGridLayout>
#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QListWidget>
#include <QTreeWidget>
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
#include <functional>
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
    int toggleTrueDialogueNode=-1;
    int toggleFalseDialogueNode=-1;
    QVector<NodeLink> toggleTrueActions, toggleFalseActions;
};

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
};

// The drawn pen stays crisp, but hit-testing uses a generous stroke.
// boundingRect must include the wider shape for Qt scene indexing.
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
    std::function<void(const QString &, const QString &)> connectionRequested;
    std::function<void(const QPointF &, const QPoint &)> insertRequested;
    std::function<void(const QString &, const QPointF &, const QPoint &)> dropRequested;
    std::function<void(const QList<QPair<QString,int>> &, const QPoint &)> linkMenuRequested;
    std::function<void(const QString &)> cardSelected;
    std::function<void(const QString &,const QPoint &)> cardMenuRequested;
    std::function<void()> deleteRequested;
    explicit NodeCanvas(QGraphicsScene *scene, QWidget *parent = nullptr)
        : QGraphicsView(scene, parent) {
        setRenderHint(QPainter::Antialiasing);
        setDragMode(QGraphicsView::ScrollHandDrag);
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
        if (event->key()==Qt::Key_Delete && deleteRequested &&
            !(scene() && scene()->focusItem())) {
            deleteRequested();
            event->accept();
            return;
        }
        QGraphicsView::keyPressEvent(event);
    }
    void mousePressEvent(QMouseEvent *event) override {
        QGraphicsItem *item = itemAt(event->pos());
        if (event->button() == Qt::LeftButton && item &&
            item->data(0).toString() == QStringLiteral("output")) {
            m_from = item->data(1).toString();
            if (cardSelected)cardSelected(m_from);
            m_startPoint = item->sceneBoundingRect().center();
            m_dragLine = scene()->addPath(QPainterPath(), QPen(QColor(255,191,87),2,Qt::DashLine));
            m_dragLine->setZValue(4);
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
        if (m_dragLine) {
            const QString from = m_from;
            // Ignore the temporary wire when hit-testing cards.
            m_dragLine->setVisible(false);
            QGraphicsItem *hit = itemAt(event->pos());
            QString to;
            for (QGraphicsItem *p=hit; p; p=p->parentItem()) {
                if (p->data(0).toString() == QStringLiteral("card")) {
                    to=p->data(1).toString(); break;
                }
            }
            scene()->removeItem(m_dragLine);
            delete m_dragLine;
            m_dragLine = nullptr;
            m_from.clear();
            if (!to.isEmpty() && from!=to && connectionRequested)
                connectionRequested(from,to);
            else if (to.isEmpty() && dropRequested)
                dropRequested(from,mapToScene(event->pos()),event->globalPosition().toPoint());
            event->accept();
            return;
        }
        QGraphicsView::mouseReleaseEvent(event);
    }
    void contextMenuEvent(QContextMenuEvent *event) override {
        // A generous viewport-space target, especially useful when zoomed out.
        // Collect ALL overlapping links, including purple Show Dialogue wires.
        // Both wire types use the same context menu + remove-connection path.
        QGraphicsItem *top=itemAt(event->pos());
        for (QGraphicsItem *p=top;p;p=p->parentItem()) {
            if (p->data(0).toString()==QStringLiteral("card")) {
                if (cardMenuRequested)
                    cardMenuRequested(p->data(1).toString(),event->globalPos());
                event->accept();
                return;
            }
        }
        QList<QPair<QString,int>> hits;
        const QRect target(event->pos()-QPoint(10,10),QSize(21,21));
        for (QGraphicsItem *item: items(target)) {
            const QString kind=item->data(0).toString();
            if (kind!=QStringLiteral("link") && kind!=QStringLiteral("dialogue-link") &&
                kind!=QStringLiteral("state-link") && kind!=QStringLiteral("state-true-link") &&
                kind!=QStringLiteral("state-false-link") &&
                kind!=QStringLiteral("state-true-action") &&
                kind!=QStringLiteral("state-false-action"))continue;
            // -1 is reserved for a Trigger's single Show Dialogue connection.
            const QPair<QString,int> ref(item->data(1).toString(),
                kind==QStringLiteral("dialogue-link") ? -1 :
                kind==QStringLiteral("state-link") ? -2 :
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
    QString m_from;
    QPointF m_startPoint;
    QGraphicsPathItem *m_dragLine = nullptr;
};

class VisualNodesDialog final : public QDialog {
public:
    explicit VisualNodesDialog(const QString &vsgmPath, QWidget *parent = nullptr)
        : QDialog(parent), m_graphPath(QFileInfo(vsgmPath).absoluteFilePath()) {
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
        for (int i=0;i<resources.size();++i) {
            const QJsonObject resource=resources.at(i).toObject();
            if (resource.value(QStringLiteral("kind")).toString()!=QStringLiteral("sprite")) continue;
            const QJsonObject data=resource.value(QStringLiteral("gameObject")).toObject();
            const QString type=data.value(QStringLiteral("type")).toString();
            const QString id=resource.value(QStringLiteral("id")).toString();
            if (type.isEmpty() || type==QStringLiteral("decoration") || id.isEmpty()) continue;
            NodeObject node;
            node.id=id;
            node.name=resource.value(QStringLiteral("name")).toString(id);
            node.type=type;
            node.resourceIndex=i;
            if (type==QStringLiteral("trigger")) {
                node.dialogueNode=data.value(QStringLiteral("interactDialogueNode")).toInt(-1);
                node.dialogueMode=data.value(QStringLiteral("interactDialogueMode"))
                    .toString(QStringLiteral("conversation"));
                if (node.dialogueMode!=QStringLiteral("single") &&
                    node.dialogueMode!=QStringLiteral("sequence"))
                    node.dialogueMode=QStringLiteral("conversation");
                if (node.dialogueNode>=0) m_dialogueCards.insert(id);
                node.toggleStateTargetId=data.value(QStringLiteral("toggleStateTargetId")).toString();
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
            const QString legacy=data.value(QStringLiteral("targetObjectId")).toString();
            const QString action=data.value(QStringLiteral("targetAction")).toString();
            // Keep dormant "none" targets as well: editing other links must not
            // silently discard values authored in Game Object Properties.
            if (!legacy.isEmpty()) node.links.append({legacy,action});
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
                m_order.append(id);
                m_objects.insert(id,node);
                break;
            }
        }
        // Respect legacy intentionally unlinked dialogue cards, but do not
        // auto-display every unused world object just because it exists.
        for (const QString &id:m_dialogueCards)
            if (m_objects.contains(id) && m_objects.value(id).dialogueNode<0)
                m_placedCards.insert(dialogueCardId(id));
        buildUi();
        renderCards();
        // An empty graph is a valid starter document, created only for this world.
        if (!QFileInfo::exists(m_graphPath) && !saveLayout()) {
            QMessageBox::warning(this,tr("Visual Nodes"),tr("Cannot create %1").arg(m_graphPath));
            return false;
        }
        return true;
    }
    bool worldChanged() const { return m_worldChanged; }
protected:
    void showEvent(QShowEvent *event) override {
        QDialog::showEvent(event);
        if (m_viewReady) return;
        m_viewReady=true;
        // fitInView() during initialise() ran against an unlaid-out viewport.
        // Defer until the maximised dialog and splitter have their final sizes.
        QTimer::singleShot(0,this,[this] {restoreViewport();});
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
        if (graph.value(QStringLiteral("view")).toObject()==view)return true;
        graph.insert(QStringLiteral("view"),view);
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
        auto *addCondition=new QPushButton(tr("+ Boolean"),this);
        addCondition->setToolTip(tr("Select a Game Object controlled by a Trigger, then add a Boolean that reads its enabled/disabled state."));
        auto *addDialogue=new QPushButton(tr("+ Show Dialogue"),this);
        addDialogue->setToolTip(tr("Select a Trigger, then add its inline Show Dialogue card."));
        auto *save=new QPushButton(tr("Save Graph + World"),this);
        auto *closeButton=new QPushButton(tr("Close"),this);
        for (auto *b:{zoomOut,zoomIn,fit,addCondition,addDialogue,save,closeButton}) toolbar->addWidget(b);
        main->addLayout(toolbar);
        auto *hint=new QLabel(tr("Cards snap to an 8px grid when moved. Right-click empty canvas to add existing world objects. Drag a Trigger socket to connect. Right-click wires to edit/remove connections; drag from a Game Object output to Logic > Boolean for TRUE/FALSE action and dialogue branches; select a card and press Delete to remove it and disconnect its links. Objects and dialogues are never deleted."),this);
        hint->setWordWrap(true);
        main->addWidget(hint);
        auto *split=new QSplitter(Qt::Horizontal,this);
        auto *left=new QWidget(split);
        left->setMinimumWidth(135);
        left->setMaximumWidth(220);
        auto *leftLayout=new QVBoxLayout(left);
        leftLayout->addWidget(new QLabel(tr("VISIBLE NODES"),left));
        m_list=new QListWidget(left);
        m_list->installEventFilter(this); // Delete works from the card list too.
        leftLayout->addWidget(m_list);
        auto *leftNote=new QLabel(tr("Right-click empty graph space to browse world objects. Only real .sbgm objects and supported links are available."),left);
        leftNote->setWordWrap(true);
        leftLayout->addWidget(leftNote);
        m_scene=new QGraphicsScene(this);
        m_scene->setSceneRect(-2500,-1800,6000,4500);
        m_view=new NodeCanvas(m_scene,split);
        auto *right=new QWidget(split);
        auto *rightLayout=new QVBoxLayout(right);
        rightLayout->addWidget(new QLabel(tr("SELECTED CARD"),right));
        m_details=new QTextEdit(right);
        m_details->setReadOnly(true);
        rightLayout->addWidget(m_details,1);
        rightLayout->addWidget(new QLabel(tr("TRIGGER CONNECTIONS"),right));
        m_linksList=new QListWidget(right);
        m_linksList->setMinimumHeight(130);
        m_linksList->setMaximumHeight(235);
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
        split->setStretchFactor(1,1);
        split->setSizes({175,1100,255});
        main->addWidget(split,1);
        m_status=new QLabel(tr("World definitions and links come only from .sbgm. .vsgm stores placed cards, positions and camera, never gameplay rules."),this);
        m_status->setWordWrap(true);
        main->addWidget(m_status);
        connect(zoomOut,&QPushButton::clicked,this,[this] {m_view->zoom(.8);});
        connect(zoomIn,&QPushButton::clicked,this,[this] {m_view->zoom(1.25);});
        connect(fit,&QPushButton::clicked,this,[this] {m_view->fitInView(m_scene->itemsBoundingRect().adjusted(-90,-90,90,90),Qt::KeepAspectRatio);});
        connect(addDialogue,&QPushButton::clicked,this,[this] { addDialogueCard(); });
        connect(addCondition,&QPushButton::clicked,this,[this] { addBooleanFromObject(m_selectedCardId); });
        connect(save,&QPushButton::clicked,this,[this] {saveAll();});
        connect(closeButton,&QPushButton::clicked,this,[this] {this->close();});
        m_view->connectionRequested=[this](const QString &from,const QString &to) {addConnection(from,to);};
        m_view->insertRequested=[this](const QPointF &point,const QPoint &global) {
            showInsertTree(point,global,QString());
        };
        m_view->dropRequested=[this](const QString &from,const QPointF &point,const QPoint &global) {
            if (from.startsWith(QStringLiteral("@stateout:")) ||
                (m_objects.contains(from) && m_objects.value(from).type!=QStringLiteral("npc")))
                showInsertTree(point,global,from);
        };
        m_view->linkMenuRequested=[this](const QList<QPair<QString,int>> &links,const QPoint &point) {
            linkContextMenu(links,point);
        };
        m_view->cardSelected=[this](const QString &id) {showDetails(id);};
        m_view->cardMenuRequested=[this](const QString &id,const QPoint &global) {
            showCardContextMenu(id,global);
        };
        m_view->deleteRequested=[this] {removeSelectedNode();};
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
        m_linesTimer=new QTimer(this);
        m_linesTimer->setSingleShot(true);
        m_linesTimer->setInterval(20);
        connect(m_linesTimer,&QTimer::timeout,this,[this] {redrawLinks();});
    }
    // Reconcile visible cards with the real links in the design document.
    // Old .vsgm graph files used to write positions for *every* object. Those
    // positions remain useful, but are NOT evidence the user placed the card.
    QSet<QString> linkedObjectIds() const {
        QSet<QString> visible;
        for (const QString &id:m_order) {
            const NodeObject n=m_objects.value(id);
            if (n.type!=QStringLiteral("trigger"))continue;
            for (const NodeLink &link:n.links) {
                if (!supportedAction(link.action) || !m_objects.contains(link.target))continue;
                visible.insert(id);
                visible.insert(link.target);
            }
            if (n.dialogueNode>=0) visible.insert(id);
            if (!n.toggleStateTargetId.isEmpty()) {
                visible.insert(id);
                if (m_objects.contains(n.toggleStateTargetId))visible.insert(n.toggleStateTargetId);
                for (const NodeLink &link:n.toggleTrueActions)
                    if (supportedAction(link.action) && m_objects.contains(link.target))visible.insert(link.target);
                for (const NodeLink &link:n.toggleFalseActions)
                    if (supportedAction(link.action) && m_objects.contains(link.target))visible.insert(link.target);
            }
        }
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
        return ids;
    }
    void makeObjectCard(const QString &id,const QPointF &position) {
        if (m_cards.contains(id) || !m_objects.contains(id))return;
        const NodeObject node=m_objects.value(id);
        const bool trigger=node.type==QStringLiteral("trigger");
        auto *card=new NodeCard(QRectF(0,0,224,82));
        card->setData(0,QStringLiteral("card"));card->setData(1,id);
        card->setPen(QPen(trigger?QColor(238,190,86):QColor(103,153,184),1.5));
        card->setBrush(QColor(43,52,65));
        m_scene->addItem(card);
        card->setPos(position);
        card->enableGridSnap();
        m_positions.insert(id,position);
        auto *stripe=new QGraphicsRectItem(QRectF(0,0,224,26),card);
        stripe->setPen(Qt::NoPen);stripe->setBrush(trigger?QColor(138,91,35):QColor(50,88,119));
        auto *name=new QGraphicsSimpleTextItem(node.name.left(27),card);
        name->setBrush(Qt::white);name->setPos(8,4);
        auto *kind=new QGraphicsSimpleTextItem(node.type.toUpper(),card);
        kind->setBrush(QColor(201,218,230));kind->setPos(9,35);
        if (trigger || (node.resourceIndex>=0 && node.type!=QStringLiteral("npc"))) {
            // Trigger sockets issue actions. Game Object sockets expose their
            // active state to a Boolean; they never issue another game action.
            auto *port=new QGraphicsEllipseItem(QRectF(214,49,19,19),card);
            port->setData(0,QStringLiteral("output"));port->setData(1,id);
            if (trigger) {
                port->setPen(QPen(QColor(255,224,136),2));
                port->setBrush(QColor(219,148,31));
            } else {
                port->setPen(QPen(QColor(177,242,226),2));
                port->setBrush(QColor(54,148,141));
                port->setToolTip(tr("Read this Game Object's enabled/disabled state with Logic > Boolean"));
            }
        }
        card->moved=[this,id,card] {
            m_positions[id]=card->pos();m_dirty=true;m_linesTimer->start();
        };
        m_cards.insert(id,card);
        auto *rowItem=new QListWidgetItem(node.name+QStringLiteral("  (")+node.type+QStringLiteral(")"),m_list);
        rowItem->setData(Qt::UserRole,id);
        rowItem->setToolTip(node.name+QStringLiteral(" (")+node.type+QStringLiteral(")"));
    }
    void renderCards() {
        const QSet<QString> linked=linkedObjectIds();
        int triggerCount=0,targetCount=0,otherCount=0;
        for (const QString &id:m_order) {
            const NodeObject node=m_objects.value(id);
            if (!linked.contains(id) && !m_placedCards.contains(id))continue;
            const bool trigger=node.type==QStringLiteral("trigger");
            const bool actor=node.type==QStringLiteral("enemy") || node.type==QStringLiteral("collectable");
            const int col=trigger?0:(actor?2:1);
            const int row=trigger?triggerCount++:(actor?targetCount++:otherCount++);
            makeObjectCard(id,m_positions.value(id,QPointF(70+col*340,85+row*125)));
        }
        const QSet<QString> requested=m_dialogueCards;
        m_dialogueCards.clear();
        for (const QString &id:m_order)
            if (m_objects.value(id).type==QStringLiteral("trigger") &&
                (m_objects.value(id).dialogueNode>=0 ||
                 m_placedCards.contains(dialogueCardId(id)) || requested.contains(id))) {
                if (!m_cards.contains(id))
                    makeObjectCard(id,m_positions.value(id,QPointF(70,85+triggerCount++*125)));
                createDialogueCard(id);
            }
        for (const QString &id:m_order) {
            const NodeObject n=m_objects.value(id);
            if (n.type!=QStringLiteral("trigger"))continue;
            if (!n.toggleStateTargetId.isEmpty() || m_placedCards.contains(toggleCardId(id))) {
                if (!m_cards.contains(id))makeObjectCard(id,m_positions.value(id,QPointF(70,85)));
                createToggleCard(id);
            }
            if (n.toggleTrueDialogueNode>=0 || m_placedCards.contains(branchCardId(id,true)))
                createBranchCard(id,true);
            if (n.toggleFalseDialogueNode>=0 || m_placedCards.contains(branchCardId(id,false)))
                createBranchCard(id,false);
        }
        redrawLinks();
    }
    // Match the Adventure Dialogue Editor's nested folder tree and stable node
    // indices. The visual graph NEVER copies or reorders dialogue definitions.
    void populateDialogueChoices(QTreeWidget *tree,QTreeWidgetItem *parent) const {
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
            item->setText(0,tr("%1: %2 — %3").arg(i)
                .arg(dialogue.value(QStringLiteral("speaker")).toString().left(24),
                     dialogue.value(QStringLiteral("text")).toString().left(35)));
            item->setData(0,Qt::UserRole,QStringLiteral("@dialogue-node:%1").arg(i));
            item->setToolTip(0,tr("Dialogue ID %1 (folder changes never change IDs)").arg(i));
        }
        if (!unfiledCount)delete unfiled;
        // Never sort this branch: Create New must remain at the very bottom.
        auto *create=new QTreeWidgetItem(parent);
        create->setText(0,tr("+ Create New Dialogue"));
        create->setData(0,Qt::UserRole,QStringLiteral("@create-dialogue"));
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
        const bool objectSource=!from.isEmpty() && !stateOutput && m_objects.contains(from) &&
            m_objects.value(from).type!=QStringLiteral("trigger") &&
            m_objects.value(from).type!=QStringLiteral("npc");
        picker.setWindowTitle(from.isEmpty()?tr("Add World Node"):
            stateOutput?tr("Connect TRUE / FALSE to..."):
            objectSource?tr("Read Game Object State..."):tr("Connect Trigger to..."));
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
        QHash<QString,QTreeWidgetItem*> objectTypes;
        if (!objectSource) for (const QString &id:m_order) {
            if (linking && id==from)continue;
            const NodeObject object=m_objects.value(id);
            QTreeWidgetItem *parent=nullptr;
            if (object.type==QStringLiteral("npc")) {
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
                parent=objectTypes.value(object.type,nullptr);
                if (!parent) {
                    QString label=object.type;
                    label.replace(QLatin1Char('_'),QLatin1Char(' '));
                    if (!label.isEmpty())label[0]=label.at(0).toUpper();
                    parent=new QTreeWidgetItem(gameObjectsRoot,QStringList{label});
                    parent->setFlags(parent->flags() & ~Qt::ItemIsSelectable);
                    objectTypes.insert(object.type,parent);
                }
            }
            auto *item=new QTreeWidgetItem(parent,QStringList{object.name});
            item->setData(0,Qt::UserRole,id);
            item->setToolTip(0,tr("%1 | %2").arg(object.type,id));
        }
        // Sort only the Game Object/NPC branches before adding dialogue nodes:
        // the Dialogue Editor's "+ Create New Dialogue" must stay last.
        tree->sortItems(0,Qt::AscendingOrder);
        if (objectSource) {
            auto *logic=new QTreeWidgetItem(tree,QStringList{tr("Logic")});
            logic->setFlags(logic->flags() & ~Qt::ItemIsSelectable);
            auto *boolean=new QTreeWidgetItem(logic,QStringList{tr("Boolean (TRUE / FALSE)")});
            boolean->setData(0,Qt::UserRole,QStringLiteral("@logic:boolean"));
            boolean->setToolTip(0,tr("TRUE when this Game Object is enabled, FALSE when disabled. Evaluated after the controlling Trigger's actions."));
        }
        if (linking && !objectSource) {
            auto *root=new QTreeWidgetItem(tree,QStringList{tr("Dialogue Actions")});
            root->setFlags(root->flags() & ~Qt::ItemIsSelectable);
            populateDialogueChoices(tree,root);
        }
        // A large world may contain hundreds of objects: start with just the
        // root headings, not every object and dialogue expanded.
        tree->collapseAll();
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
        if (selectedId==QStringLiteral("@logic:boolean")) {
            if (!objectSource)return;
            addBooleanFromObject(from,at);
            return;
        }
        if (selectedId==QStringLiteral("@create-dialogue")) {
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
                if (stateOutput) {
                    const bool yes=from.startsWith(QStringLiteral("@stateout:true:"));
                    const QString prefix=yes?QStringLiteral("@stateout:true:"):QStringLiteral("@stateout:false:");
                    setBranchDialogue(from.mid(prefix.size()),yes,index,at);
                } else connectExistingDialogue(from,at,index);
            }
            return;
        }
        if (linking && !stateOutput && m_objects.value(from).links.size()>=64) {
            QMessageBox::warning(this,tr("Visual Nodes"),tr("Triggers allow up to 64 linked actions."));
            return;
        }
        if (m_cards.contains(selectedId)) {
            // The same .sbgm object must have one card, never duplicates.
            m_view->centerOn(m_cards.value(selectedId));
        } else {
            makeObjectCard(selectedId,at);
        }
        m_placedCards.insert(selectedId);
        m_dirty=true;
        if (linking) {
            // Every TRUE/FALSE branch can perform the same real enable,
            // disable and toggle actions as the ordinary Trigger socket.
            if (stateOutput) {
                const bool yes=from.startsWith(QStringLiteral("@stateout:true:"));
                const QString prefix=yes?QStringLiteral("@stateout:true:"):QStringLiteral("@stateout:false:");
                appendBranchConnection(from.mid(prefix.size()),yes,selectedId,QStringLiteral("enable"));
            } else appendConnection(from,selectedId,QStringLiteral("enable"));
        } else {
            showDetails(selectedId);
        }
    }
    void appendConnection(const QString &from,const QString &to,const QString &action) {
        if (!supportedAction(action) || !m_objects.contains(from) || !m_objects.contains(to) ||
            m_objects.value(from).type!=QStringLiteral("trigger"))return;
        NodeObject node=m_objects.value(from);
        if (node.links.size()>=64) {
            QMessageBox::warning(this,tr("Visual Nodes"),tr("Triggers allow up to 64 linked actions."));return;
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
        if (node.dialogueNode!=index) {
            node.dialogueNode=index;
            if (node.dialogueMode.isEmpty())node.dialogueMode=QStringLiteral("single");
            m_objects.insert(from,node);
            m_touched.insert(from);
        }
        const QString key=dialogueCardId(from);
        m_positions.insert(key,at);
        m_placedCards.insert(key);
        if (!m_cards.contains(from))makeObjectCard(from,m_positions.value(from,QPointF(70,85)));
        if (!m_cards.contains(key))createDialogueCard(from);
        else m_cards.value(key)->setPos(at);
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
        if (!m_cards.contains(from)) makeObjectCard(from,m_positions.value(from,QPointF(70,85)));
        if (!m_dialogueCards.contains(from))createDialogueCard(from);
        refreshDialogueCard(from);redrawLinks();showDetails(key);
    }
    // Separate conditional card IDs, with no duplicated gameplay links in .vsgm.
    QString toggleCardId(const QString &id) const {return QStringLiteral("@toggle:")+id;}
    QString branchCardId(const QString &id,bool yes) const {
        return (yes?QStringLiteral("@toggle-dialogue:true:"):QStringLiteral("@toggle-dialogue:false:"))+id;
    }
    // A Boolean is a visual read of a Game Object output. The real branching
    // behaviour remains owned by the Trigger in .sbgm, not by .vsgm.
    void addBooleanFromObject(const QString &source,const QPointF &dropAt=QPointF()) {
        if (!m_objects.contains(source) || m_objects.value(source).resourceIndex<0 ||
            m_objects.value(source).type==QStringLiteral("trigger")) {
            QMessageBox::information(this,tr("Boolean"),
                tr("Select a Game Object such as a lift, door or switch, then drag its state output."));
            return;
        }
        QStringList owners;
        for (const QString &id:m_order) {
            const NodeObject n=m_objects.value(id);
            if (n.type!=QStringLiteral("trigger"))continue;
            for (const NodeLink &link:n.links) {
                if (link.target==source && supportedAction(link.action)) {
                    owners.append(id);break;
                }
            }
        }
        if (owners.isEmpty()) {
            QMessageBox::information(this,tr("Boolean"),
                tr("Connect a Trigger action to %1 first. The Boolean will then read its state after that Trigger runs.")
                    .arg(m_objects.value(source).name));
            return;
        }
        QString owner=owners.first();
        if (owners.size()>1) {
            QStringList choices;
            for (const QString &id:owners)
                choices.append(tr("%1 [%2]").arg(m_objects.value(id).name,id));
            bool ok=false;
            const QString chosen=QInputDialog::getItem(this,tr("Boolean Trigger"),
                tr("Which Trigger activation should evaluate %1?").arg(m_objects.value(source).name),
                choices,0,false,&ok);
            if (!ok)return;
            const int index=choices.indexOf(chosen);
            if (index<0)return;
            owner=owners.at(index);
        }
        addToggleCondition(owner,source,dropAt);
    }
    void addToggleCondition(const QString &owner,const QString &source,const QPointF &dropAt) {
        if (!m_objects.contains(owner) || m_objects.value(owner).type!=QStringLiteral("trigger") ||
            !m_objects.contains(source) || m_objects.value(source).resourceIndex<0)return;
        NodeObject n=m_objects.value(owner);
        if (!n.toggleStateTargetId.isEmpty() && n.toggleStateTargetId!=source) {
            if (QMessageBox::question(this,tr("Change Boolean Source"),
                tr("This Trigger already has a Boolean reading %1. Change it to %2?\n"
                   "Its existing TRUE/FALSE actions will now test the new state.")
                    .arg(m_objects.value(n.toggleStateTargetId).name,m_objects.value(source).name),
                QMessageBox::Yes|QMessageBox::No,QMessageBox::No)!=QMessageBox::Yes)return;
        }
        if (n.toggleStateTargetId!=source) {
            n.toggleStateTargetId=source;
            m_objects.insert(owner,n);m_touched.insert(owner);m_dirty=true;
        }
        if (!m_cards.contains(owner))makeObjectCard(owner,m_positions.value(owner,QPointF(70,85)));
        if (!m_cards.contains(source))makeObjectCard(source,m_positions.value(source,QPointF(420,85)));
        const QString key=toggleCardId(owner);
        if (!dropAt.isNull() && !m_cards.contains(key))m_positions.insert(key,dropAt);
        m_placedCards.insert(key);
        createToggleCard(owner);
        refreshToggleCard(owner);
        m_dirty=true;redrawLinks();showDetails(key);
        if (m_cards.contains(key))m_view->centerOn(m_cards.value(key));
    }
    void createToggleCard(const QString &id) {
        if (!m_objects.contains(id) || m_cards.contains(toggleCardId(id)))return;
        const QString key=toggleCardId(id);
        auto *card=new NodeCard(QRectF(0,0,294,158));
        card->setData(0,QStringLiteral("card"));card->setData(1,key);
        card->setPen(QPen(QColor(123,201,192),1.5));card->setBrush(QColor(43,52,65));
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
        // No state dropdown: the source is determined by the incoming wire
        // from the actual Game Object, e.g. Lifty -> Boolean.
        auto *sourceLabel=new QGraphicsSimpleTextItem(card);
        sourceLabel->setBrush(QColor(231,243,238));sourceLabel->setPos(12,38);
        m_booleanSourceLabels.insert(id,sourceLabel);
        auto *note=new QGraphicsSimpleTextItem(tr("TRUE = enabled  |  FALSE = disabled"),card);
        note->setBrush(QColor(177,207,202));note->setPos(12,68);
        for (const bool yes:{true,false}) {
            const int y=yes?107:138;
            auto *label=new QGraphicsSimpleTextItem(yes?tr("TRUE / YES"):tr("FALSE / NO"),card);
            label->setBrush(yes?QColor(111,222,167):QColor(244,145,146));label->setPos(12,y-8);
            auto *port=new QGraphicsEllipseItem(QRectF(285,y-6,18,18),card);
            port->setData(0,QStringLiteral("output"));
            port->setData(1,(yes?QStringLiteral("@stateout:true:"):QStringLiteral("@stateout:false:"))+id);
            port->setPen(QPen(Qt::white,1));port->setBrush(yes?QColor(76,171,118):QColor(193,86,86));
        }
        card->moved=[this,key,card] {m_positions[key]=card->pos();m_dirty=true;m_linesTimer->start();};
        m_cards.insert(key,card);
        auto *entry=new QListWidgetItem(m_list);
        entry->setData(Qt::UserRole,key);
        entry->setForeground(QBrush(QColor(123,201,192)));
        entry->setToolTip(tr("Evaluated after the %1 Trigger runs").arg(m_objects.value(id).name));
        refreshToggleCard(id);
    }
    void refreshToggleCard(const QString &id) {
        if (!m_booleanSourceLabels.contains(id) || !m_objects.contains(id))return;
        const QString source=m_objects.value(id).toggleStateTargetId;
        const QString label=source.isEmpty()?tr("Connect from a Game Object output"):
            tr("Read: %1").arg(m_objects.contains(source)?m_objects.value(source).name:source);
        m_booleanSourceLabels.value(id)->setText(label.left(43));
        const QString key=toggleCardId(id);
        for (int i=0;i<m_list->count();++i) {
            QListWidgetItem *item=m_list->item(i);
            if (item->data(Qt::UserRole).toString()==key) {
                const QString sourceName=m_objects.contains(source)?m_objects.value(source).name:
                                         source.isEmpty()?tr("Unconnected"):source;
                item->setText(tr("Boolean: %1 (%2)").arg(sourceName,m_objects.value(id).name));
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
        card->setPen(QPen(QColor(171,126,222),1.5));card->setBrush(QColor(43,52,65));
        m_scene->addItem(card);
        const QPointF origin=m_cards.contains(toggleCardId(id))?m_cards.value(toggleCardId(id))->pos():QPointF(500,180);
        const QPointF pos=m_positions.value(key,origin+QPointF(380,yes?-40:350));
        card->setPos(pos);card->enableGridSnap();m_positions.insert(key,pos);
        auto *stripe=new QGraphicsRectItem(QRectF(0,0,324,31),card);
        stripe->setPen(Qt::NoPen);stripe->setBrush(QColor(97,65,129));
        auto *heading=new QGraphicsSimpleTextItem(yes?tr("SHOW DIALOGUE | TRUE"):tr("SHOW DIALOGUE | FALSE"),card);
        heading->setBrush(Qt::white);heading->setPos(9,5);
        auto *panel=new QWidget;
        panel->setFixedSize(302,303);
        panel->setStyleSheet(QStringLiteral(
            "QWidget { background: #293441; color: #ecedf7; } "
            "QComboBox,QLineEdit,QPlainTextEdit { background: #18202c; "
            "color: #f6f6fa; border: 1px solid #677286; padding: 3px; } "
            "QPushButton { background: #523e6e; color: white; padding: 5px; }"));
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
        info->setStyleSheet(QStringLiteral("QLabel { font-size: 10px; color: #e4ccea; }"));
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
        card->moved=[this,key,card]{m_positions[key]=card->pos();m_dirty=true;m_linesTimer->start();};
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
        if (yes)n.toggleTrueDialogueNode=index;else n.toggleFalseDialogueNode=index;
        m_objects.insert(id,n);m_touched.insert(id);m_dirty=true;
        const QString key=branchCardId(id,yes);
        if (index>=0) {
            if (!m_cards.contains(key))m_positions.insert(key,at);
            m_placedCards.insert(key);
            createToggleCard(id);
            if (!m_cards.contains(key))createBranchCard(id,yes);
            refreshBranchCard(id,yes);
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
        card->setBrush(QColor(43,52,65));
        m_scene->addItem(card);
        int triggerRow=0;
        for (const QString &candidate:m_order) {
            if (candidate==id)break;
            if (m_objects.value(candidate).type==QStringLiteral("trigger"))++triggerRow;
        }
        const QPointF pos=m_positions.value(key,QPointF(1090,85+triggerRow*365));
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
        auto *panel=new QWidget;
        panel->setFixedSize(302,303);
        panel->setStyleSheet(QStringLiteral(
            "QWidget { background: #293441; color: #ecedf7; } "
            "QComboBox,QLineEdit,QPlainTextEdit { background: #18202c; "
            "color: #f6f6fa; border: 1px solid #677286; padding: 3px; } "
            "QPushButton { background: #523e6e; color: white; padding: 5px; }"));
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
        info->setStyleSheet(QStringLiteral("QLabel { font-size: 10px; color: #e4ccea; }"));
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
        card->moved=[this,key,card] {
            m_positions[key]=card->pos();m_dirty=true;m_linesTimer->start();
        };
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
    void redrawLinks() {
        for (QGraphicsPathItem *item:m_lines) {m_scene->removeItem(item);delete item;}
        m_lines.clear();
        for (const QString &id:m_order) {
            const NodeObject node=m_objects.value(id);
            if (node.type!=QStringLiteral("trigger")) continue;
            NodeCard *from=m_cards.value(id,nullptr);
            if (!from)continue;
            for (int i=0;i<node.links.size();++i) {
                const NodeLink link=node.links.at(i);
                NodeCard *to=m_cards.value(link.target,nullptr);
                if (!to || !supportedAction(link.action))continue;
                const QPointF a=from->scenePos()+QPointF(224,58);
                const QPointF b=to->scenePos()+QPointF(0,58);
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
                wire->setToolTip(tr("%1 → %2: %3 (right-click to edit or remove)")
                    .arg(node.name,m_objects.value(link.target).name,link.action));
                wire->setZValue(0);
                m_lines.append(wire);
            }
            if (m_cards.contains(toggleCardId(id)) &&
                m_cards.contains(node.toggleStateTargetId)) {
                NodeCard *source=m_cards.value(node.toggleStateTargetId);
                NodeCard *to=m_cards.value(toggleCardId(id));
                const QPointF a=source->scenePos()+QPointF(224,58);
                const QRectF target=to->sceneBoundingRect();
                const bool targetOnLeft=target.center().x()<a.x();
                const QPointF b(targetOnLeft?target.right():target.left(),target.top()+52.0);
                const qreal bend=qMax(48.0,qMin(150.0,qAbs(b.x()-a.x())*.45));
                QPainterPath path(a);
                path.cubicTo(a+QPointF(bend,0),b+QPointF(targetOnLeft?bend:-bend,0),b);
                auto *wire=new NodeWire(path,QPen(QColor(123,201,192),3));
                wire->setData(0,QStringLiteral("state-link"));wire->setData(1,id);
                wire->setToolTip(tr("%1 state → Boolean (%2; right-click to disconnect)")
                    .arg(m_objects.value(node.toggleStateTargetId).name,node.name));
                m_scene->addItem(wire);m_lines.append(wire);
            }
            if (m_cards.contains(toggleCardId(id)))for (const bool yes:{true,false}) {
                const int index=yes?node.toggleTrueDialogueNode:node.toggleFalseDialogueNode;
                NodeCard *state=m_cards.value(toggleCardId(id));
                NodeCard *to=m_cards.value(branchCardId(id,yes),nullptr);
                if (index<0 || !to)continue;
                const QPointF a=state->scenePos()+QPointF(294,yes?115:146);
                const QPointF b=to->scenePos()+QPointF(0,57);
                const qreal bend=qMax(48.0,qAbs(b.x()-a.x())*.45);
                QPainterPath path(a);path.cubicTo(a+QPointF(bend,0),b-QPointF(bend,0),b);
                auto *wire=new NodeWire(path,QPen(yes?QColor(111,222,167):QColor(244,145,146),3));
                wire->setData(0,(yes?QStringLiteral("state-true-link"):QStringLiteral("state-false-link")));
                wire->setData(1,id);wire->setToolTip(tr("%1 dialogue #%2 (right-click to disconnect)")
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
                    const QPointF a=state->scenePos()+QPointF(294,yes?115:146);
                    const QPointF b=to->scenePos()+QPointF(0,58);
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
                    wire->setToolTip(tr("%1 branch → %2: %3 (right-click to edit/remove)")
                        .arg(yes?tr("TRUE"):tr("FALSE"),m_objects.value(link.target).name,link.action));
                    wire->setZValue(0);m_scene->addItem(wire);m_lines.append(wire);
                }
            }
            if (node.dialogueNode>=0 && m_dialogueCards.contains(id)) {
                NodeCard *to=m_cards.value(dialogueCardId(id),nullptr);
                if (to) {
                    // Purple dialogue links use the same smooth cubic curves
                    // as red/green action links. Never route dialogue wires
                    // with a square detour over the tops of the cards.
                    const QPointF a=from->scenePos()+QPointF(224,58);
                    const QRectF target=to->sceneBoundingRect();
                    // When a dialogue card is left of its Trigger, approach
                    // its RIGHT edge. Entering its left edge from a right-hand
                    // output socket causes enormous loops or crosses the card.
                    const bool targetOnLeft=target.center().x()<a.x();
                    const QPointF b(targetOnLeft?target.right():target.left(),
                                     target.top()+57.0);
                    const qreal bend=qMax(55.0,qMin(150.0,qAbs(b.x()-a.x())*.5));
                    QPainterPath path(a);
                    path.cubicTo(a+QPointF(bend,0),
                                 b+QPointF(targetOnLeft?bend:-bend,0),b);
                    auto *wire=new NodeWire(path,QPen(QColor(199,149,248),3));
                    wire->setData(0,QStringLiteral("dialogue-link"));
                    wire->setData(1,id);
                    wire->setToolTip(tr("Show dialogue %1 (right-click to disconnect)")
                        .arg(node.dialogueNode));
                    wire->setZValue(0);m_scene->addItem(wire);m_lines.append(wire);
                }
            }
        }
    }
    void showDetails(const QString &id) {
        m_selectedCardId=id;
        m_removeSelectedButton->setEnabled(m_cards.contains(id));
        if (id.isEmpty()) {
            m_details->clear();m_linksList->clear();
            m_linksList->setEnabled(false);
            m_editLinkButton->setEnabled(false);m_removeLinkButton->setEnabled(false);
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
            m_details->setPlainText(tr("Boolean\n\nState from: %2\nEvaluated when: %1 activates\n\nTRUE = Game Object enabled; FALSE = disabled. The IDE reads the incoming Game Object's state after the Trigger action. No second state selector needed.\n\nDrag TRUE or FALSE to another Game Object or Show Dialogue.")
                .arg(n.name,n.toggleStateTargetId.isEmpty()?tr("Not selected"):m_objects.value(n.toggleStateTargetId).name));
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
        if (node.type==QStringLiteral("trigger")) {
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
            text+=tr("\nDialogue: %1 (%2)\n\nUse the golden socket to connect this Trigger to another object or its Show Dialogue card. Select a connection below to edit or remove it.")
                .arg(node.dialogueNode).arg(node.dialogueMode);
        } else text+=tr("This is a target card. Its other settings remain in Game Object Properties.");
        m_editLinkButton->setEnabled(false);
        m_removeLinkButton->setEnabled(false);
        m_linksList->setEnabled(node.type==QStringLiteral("trigger"));
        m_details->setPlainText(text);
    }
    void addConnection(const QString &from,const QString &to) {
        if (from.startsWith(QStringLiteral("@stateout:"))) {
            const bool yes=from.startsWith(QStringLiteral("@stateout:true:"));
            const QString owner=from.mid(yes?QStringLiteral("@stateout:true:").size():
                                        QStringLiteral("@stateout:false:").size());
            if (to.startsWith(QStringLiteral("@dialogue:"))) {
                const QString dialogueOwner=to.mid(QStringLiteral("@dialogue:").size());
                const int selected=m_objects.value(dialogueOwner).dialogueNode;
                if (selected>=0)setBranchDialogue(owner,yes,selected,
                    m_cards.value(to)->pos()+QPointF(360,yes?-80:80));
            } else if (to==branchCardId(owner,yes)) {
                selectBranchDialogue(from,m_cards.value(to)->pos());
            } else if (m_objects.contains(to)) {
                appendBranchConnection(owner,yes,to,QStringLiteral("enable"));
            }
            return;
        }
        if (m_objects.contains(from) && m_objects.value(from).type!=QStringLiteral("trigger")) {
            if (to.startsWith(QStringLiteral("@toggle:"))) {
                const QString owner=to.mid(QStringLiteral("@toggle:").size());
                bool controlled=false;
                for (const NodeLink &link:m_objects.value(owner).links)
                    if (link.target==from && supportedAction(link.action))controlled=true;
                if (controlled)addToggleCondition(owner,from,m_cards.value(to)->pos());
                else QMessageBox::information(this,tr("Boolean"),
                    tr("Connect Trigger %1 to %2 first, then its Boolean can read that object's state.")
                        .arg(m_objects.value(owner).name,m_objects.value(from).name));
            }
            return;
        }
        if (!m_objects.contains(from) || m_objects.value(from).type!=QStringLiteral("trigger"))return;
        if (to==toggleCardId(from)) {
            showDetails(to);return;
        }
        if (to==dialogueCardId(from)) {
            if (!m_dialogueCards.contains(from))return;
            showDetails(to);
            if (m_objects.value(from).dialogueNode<0) {
                // A dropped Trigger wire on an empty dialogue card opens the
                // actual selection control, with no guessed/default action.
                m_dialogueControls.value(from).picker->showPopup();
            }
            return;
        }
        if (!m_objects.contains(to))return;
        appendConnection(from,to,QStringLiteral("enable"));
    }
    // Orphan removal is .vsgm-only. Delete/Remove Selected below additionally
    // disconnects links in the pending .sbgm edit, without deleting resources.
    int removeOrphanCard(const QString &id) {
        if (!m_cards.contains(id) || connectedCardIds().contains(id))return 0;
        int removed=0;
        // Removing an unconnected Trigger also removes its unattached purple
        // card; otherwise that dialogue card would remain stranded on screen.
        if (m_objects.contains(id)) {
            const QString dialogueId=dialogueCardId(id);
            if (m_cards.contains(dialogueId))removed+=removeOrphanCard(dialogueId);
        }
        if (id.startsWith(QStringLiteral("@dialogue:"))) {
            const QString trigger=id.mid(QStringLiteral("@dialogue:").size());
            m_dialogueControls.remove(trigger); // Qt owns the widget via its proxy.
            m_dialogueCards.remove(trigger);
        }
        if (id.startsWith(QStringLiteral("@toggle:")))
            m_booleanSourceLabels.remove(id.mid(QStringLiteral("@toggle:").size()));
        if (id.startsWith(QStringLiteral("@toggle-dialogue:")))
            m_dialogueControls.remove(id);
        NodeCard *card=m_cards.take(id);
        if (!card)return removed;
        m_scene->removeItem(card);
        delete card;
        m_placedCards.remove(id);
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
        n.toggleStateTargetId.clear();n.toggleTrueDialogueNode=-1;n.toggleFalseDialogueNode=-1;
        n.toggleTrueActions.clear();n.toggleFalseActions.clear();
        m_objects.insert(id,n);m_touched.insert(id);m_dirty=true;
        for (const QString &key:{branchCardId(id,true),branchCardId(id,false),toggleCardId(id)})
            if (m_cards.contains(key))removeOrphanCard(key);
        redrawLinks();showDetails(id);
    }
    void removeSelectedNode() {
        const QString id=m_selectedCardId;
        if (id.isEmpty() || !m_cards.contains(id))return;
        const bool dialogueCard=id.startsWith(QStringLiteral("@dialogue:"));
        if (id.startsWith(QStringLiteral("@toggle-dialogue:"))) {
            const bool yes=id.startsWith(QStringLiteral("@toggle-dialogue:true:"));
            const QString prefix=yes?QStringLiteral("@toggle-dialogue:true:"):QStringLiteral("@toggle-dialogue:false:");
            const QString owner=id.mid(prefix.size());
            NodeObject n=m_objects.value(owner);
            if (yes)n.toggleTrueDialogueNode=-1;else n.toggleFalseDialogueNode=-1;
            m_objects.insert(owner,n);m_touched.insert(owner);m_dirty=true;
            removeOrphanCard(id);redrawLinks();showDetails(toggleCardId(owner));return;
        }
        if (id.startsWith(QStringLiteral("@toggle:"))) {
            removeToggleCondition(id.mid(QStringLiteral("@toggle:").size()));return;
        }
        int removedLinks=0;
        // Count links before displaying the confirmation, including parallel
        // edges and every Trigger that points at a shared target object.
        for (const QString &source:m_order) {
            const NodeObject node=m_objects.value(source);
            if (node.type!=QStringLiteral("trigger"))continue;
            if (source==id) {
                removedLinks+=node.links.size();
                if (node.dialogueNode>=0)++removedLinks;
                if (!node.toggleStateTargetId.isEmpty())++removedLinks;
                if (node.toggleTrueDialogueNode>=0)++removedLinks;
                if (node.toggleFalseDialogueNode>=0)++removedLinks;
                removedLinks+=node.toggleTrueActions.size()+node.toggleFalseActions.size();
            } else if (!dialogueCard) {
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
        if (removedLinks>0 && QMessageBox::question(this,tr("Delete Graph Node"),
            tr("Remove this card and disconnect %1 gameplay connection(s)?\n\n"
               "The underlying Game Objects, NPCs and Adventure dialogues are NOT deleted. "
               "The changes are written to .sbgm only when you choose Save Graph + World.")
               .arg(removedLinks),
            QMessageBox::Yes|QMessageBox::No,QMessageBox::No)!=QMessageBox::Yes)return;
        if (dialogueCard) {
            disconnectDialogue(id.mid(QStringLiteral("@dialogue:").size()));
        } else {
            // For Trigger nodes, remove every outgoing action + its dialogue.
            // For any target node, remove ALL incoming links from every Trigger.
            // The Graph is a view; these are the only .sbgm fields we modify.
            for (const QString &source:m_order) {
                NodeObject node=m_objects.value(source);
                if (node.type!=QStringLiteral("trigger"))continue;
                bool changed=false;
                if (source==id) {
                    if (!node.links.isEmpty()) { node.links.clear();changed=true; }
                    if (node.dialogueNode>=0) {node.dialogueNode=-1;changed=true;}
                    if (!node.toggleStateTargetId.isEmpty() || node.toggleTrueDialogueNode>=0 ||
                        node.toggleFalseDialogueNode>=0 || !node.toggleTrueActions.isEmpty() ||
                        !node.toggleFalseActions.isEmpty()) {
                        node.toggleStateTargetId.clear();node.toggleTrueDialogueNode=-1;
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
                    if (node.toggleStateTargetId==id) {
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
            for (const QString &key:{toggleCardId(id),branchCardId(id,true),branchCardId(id,false)}) {
                if (m_cards.contains(key))removeOrphanCard(key);
            }
        }
        const int removed=removeOrphanCard(id);
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
        if (id.startsWith(QStringLiteral("@toggle-dialogue:"))) {
            branch=menu.addAction(tr("Choose Dialogue from folders..."));
            clearBranch=menu.addAction(tr("Disconnect this dialogue"));
            menu.addSeparator();
        } else if (m_objects.contains(id) && m_objects.value(id).resourceIndex>=0 &&
                   m_objects.value(id).type!=QStringLiteral("trigger")) {
            branch=menu.addAction(tr("Logic → Boolean (read enabled state)"));
            menu.addSeparator();
        }
        QAction *remove=menu.addAction(tr("Delete Node (disconnect links)"));
        remove->setToolTip(tr("Remove this card and its gameplay connections, not its underlying .sbgm object or dialogue."));
        QAction *cleanup=menu.addAction(tr("Remove All Orphaned Nodes..."));
        QAction *selected=menu.exec(at);
        if (selected==branch && m_objects.contains(id)) {
            addBooleanFromObject(id);
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
        if (node.type!=QStringLiteral("trigger") || index<0 || index>=node.links.size())return;
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
            const NodeObject node=m_objects.value(ref.first);
            if (node.type!=QStringLiteral("trigger"))continue;
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
                for (const QPair<QString,QString> &choice:{
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
            if (ref.second<=-2) {
                QMenu *actions=&menu;
                if (links.size()>1)actions=menu.addMenu(tr("%1 : state condition").arg(node.name));
                QAction *remove=actions->addAction(tr("Remove Connection"));
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
            for (const QPair<QString,QString> &choice : {
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
        if (operation==QStringLiteral("remove")) {
            if (ref.second==-1)disconnectDialogue(ref.first);
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
            if (index<0 || index>=links.size())return;
            links[index].action=operation;
            m_objects.insert(ref.first,node);m_touched.insert(ref.first);m_dirty=true;
            redrawLinks();showDetails(toggleCardId(ref.first));return;
        }
        if (ref.second<0)return;
        NodeObject node=m_objects.value(ref.first);
        if (ref.second>=node.links.size())return;
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
            if (!it.key().startsWith(QStringLiteral("@toggle:")) &&
                !it.key().startsWith(QStringLiteral("@toggle-dialogue:")))continue;
            const QPointF pt=it.value()->pos();
            positions.insert(it.key(),QJsonArray{pt.x(),pt.y()});
        }
        root.insert(QStringLiteral("positions"),positions);
        QJsonArray dialogueCards;
        for (const QString &id:m_order)
            if (m_dialogueCards.contains(id) &&
                (m_placedCards.contains(dialogueCardId(id)) ||
                 m_objects.value(id).dialogueNode>=0))dialogueCards.append(id);
        root.insert(QStringLiteral("dialogueCards"),dialogueCards);
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
        if (!m_touched.isEmpty() || m_dialoguesChanged) {
            QJsonArray resources=m_world.value(QStringLiteral("resources")).toArray();
            for (const QString &id:m_touched) {
                const NodeObject node=m_objects.value(id);
                if (node.type!=QStringLiteral("trigger") || node.resourceIndex<0 ||
                    node.resourceIndex>=resources.size())continue;
                QJsonObject resource=resources.at(node.resourceIndex).toObject();
                if (resource.value(QStringLiteral("id")).toString()!=id)
                    return fail(tr("Game Object IDs changed. Refusing to rewrite the world."));
                QJsonObject object=resource.value(QStringLiteral("gameObject")).toObject();
                object.insert(QStringLiteral("targetObjectId"),node.links.isEmpty()
                    ?QString():node.links.first().target);
                object.insert(QStringLiteral("targetAction"),node.links.isEmpty()
                    ?QStringLiteral("none"):node.links.first().action);
                QJsonArray extras;
                for (int i=1;i<node.links.size();++i)
                    extras.append(QJsonObject{{QStringLiteral("objectId"),node.links[i].target},
                                              {QStringLiteral("action"),node.links[i].action}});
                object.insert(QStringLiteral("triggerExtraActions"),extras);
                object.insert(QStringLiteral("interactDialogueNode"),node.dialogueNode);
                object.insert(QStringLiteral("interactDialogueMode"),node.dialogueMode);
                object.insert(QStringLiteral("toggleStateTargetId"),node.toggleStateTargetId);
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
            if (m_dialoguesChanged) {
                QJsonObject adventure=next.value(QStringLiteral("adventure")).toObject();
                adventure.insert(QStringLiteral("nodes"),m_dialogues);
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
        }
        if (!saveLayout())return fail(tr("Could not save .vsgm layout."));
        m_dirty=false;
        m_status->setText(tr("Saved. Gameplay links are in .sbgm; .vsgm remembers only placed cards and the view."));
        return true;
    }
    bool fail(const QString &message) {
        QMessageBox::warning(this,tr("Visual Nodes"),message);return false;
    }
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
    bool m_dialoguesChanged=false;
    QSet<QString> m_dialogueCards;
    QSet<QString> m_placedCards; // Only explicitly placed unconnected cards; .sbgm owns links.
    QHash<QString,DialogueControls> m_dialogueControls;
    QHash<QString,QGraphicsSimpleTextItem*> m_booleanSourceLabels;
    QStringList m_order;
    QHash<QString,QPointF> m_positions;
    QHash<QString,NodeCard*> m_cards;
    QSet<QString> m_touched;
    QList<QGraphicsPathItem*> m_lines;
    bool m_dirty=false,m_worldChanged=false;
    bool m_hasStoredView=false,m_hasStoredScroll=false,m_viewReady=false;
    qreal m_storedZoom=1.0;
    QPointF m_storedCenter;
    QPoint m_storedScroll;
    QSize m_storedViewport;
    QGraphicsScene *m_scene=nullptr;
    NodeCanvas *m_view=nullptr;
    QListWidget *m_list=nullptr;
    QListWidget *m_linksList=nullptr;
    QPushButton *m_editLinkButton=nullptr;
    QPushButton *m_removeLinkButton=nullptr;
    QPushButton *m_removeSelectedButton=nullptr;
    QPushButton *m_removeOrphansButton=nullptr;
    QString m_selectedCardId;
    QTextEdit *m_details=nullptr;
    QLabel *m_status=nullptr;
    QTimer *m_linesTimer=nullptr;
};
}

bool openGameVisualNodes(QWidget *parent, const QString &vsgmPath, const IDETheme &theme) {
    Q_UNUSED(theme);
    VisualNodesDialog dialog(vsgmPath,parent);
    if (!dialog.initialise())return false;
    dialog.exec();
    return dialog.worldChanged();
}
