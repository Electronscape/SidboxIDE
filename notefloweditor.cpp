#include "notefloweditor.h"
#include "idetheme.h"

#include <QApplication>
#include <QAction>
#include <QColor>
#include <QCheckBox>
#include <QCloseEvent>
#include <QDialog>
#include <QFile>
#include <QFileInfo>
#include <QFontMetrics>
#include <QFormLayout>
#include <QGraphicsItem>
#include <QHash>
#include <QGraphicsSceneMouseEvent>
#include <QLineF>
#include <QFrame>
#include <QStyleOptionGraphicsItem>
#include <QTextCharFormat>
#include <QTextCursor>
#include <QTextDocument>
#include <QTextOption>
#include <QVariant>
#include <QGraphicsPathItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QKeyEvent>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QSaveFile>
#include <QResizeEvent>
#include <QScrollBar>
#include <QShowEvent>
#include <QSettings>
#include <QSet>
#include <QStringList>
#include <QVector>
#include <QShortcut>
#include <QTimer>
#include <QUuid>
#include <QVBoxLayout>
#include <QWheelEvent>
#include <QtMath>
#include <algorithm>
#include <functional>
#include <memory>

namespace {

// Only three workflow colours. Surfaces, text and inactive strokes come from
// the active IDETheme, just as they do in the Game Visual Nodes editor.
QColor stateColour(int status)
{
    if (status == 2) return QColor(74, 169, 120);  // Done
    if (status == 1) return QColor(220, 158, 72);  // In Progress
    return QColor(113, 159, 192);                  // New
}
QString stateLabel(int status)
{
    if (status == 2) return QObject::tr("DONE");
    if (status == 1) return QObject::tr("IN PROGRESS");
    return QObject::tr("NEW");
}

struct NoteNode {
    QString id;
    QString kind; // note, checklist, decision
    QString title;
    QString text;
    QStringList tasks;
    QVector<bool> ticks;
    int state = 0;
    QPointF pos;
    bool collapsed = false;          // Card folded, outgoing branches hidden
    QSet<QString> hiddenPorts;       // Independently hidden next/yes/no routes
};
struct NoteLink {
    QString source;
    QString port; // next, yes, no
    QString target;
};

// QGraphicsPathItem paints a large dashed bounding rectangle when selected.
// A workflow connection should highlight just the actual curved wire.
class NoteWire final : public QGraphicsPathItem {
public:
    using QGraphicsPathItem::QGraphicsPathItem;
protected:
    void paint(QPainter *p, const QStyleOptionGraphicsItem *, QWidget *) override {
        QPen stroke = pen();
        if (isSelected()) {
            stroke.setColor(stroke.color().lighter(145));
            stroke.setWidthF(2.5);
        }
        p->setRenderHint(QPainter::Antialiasing, true);
        p->setPen(stroke);
        p->setBrush(Qt::NoBrush);
        p->drawPath(path());
    }
};

class NoteCard final : public QGraphicsItem {
public:
    explicit NoteCard(NoteNode *node, const IDETheme &theme)
        : m_node(node), m_theme(theme)
    {
        setFlag(ItemIsMovable);
        setFlag(ItemIsSelectable);
        setFlag(ItemSendsGeometryChanges);
        setAcceptHoverEvents(true);
        setZValue(5);
        // QTextDocument preserves explicit Enter/newline paragraphs AND wraps
        // long lines. Cache its layout so resizing/moving cards stays cheap.
        m_bodyDocument.setDocumentMargin(0);
        QTextOption wrapping;
        wrapping.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
        m_bodyDocument.setDefaultTextOption(wrapping);
        m_bodyDocument.setTextWidth(m_node->kind == QStringLiteral("decision") ? Width-96 : Width-26);
        refreshBodyText();
        setPos(node->pos);
    }
    std::function<void()> changed;
    std::function<void()> moved;
    std::function<void()> editRequested;
    NoteNode *node() const { return m_node; }
    void beginContentUpdate() { prepareGeometryChange(); }
    void endContentUpdate() { refreshBodyText(); update(); }
    static constexpr qreal Width = 270.0;
    static constexpr qreal Grid = 8.0;
    qreal cardHeight() const {
        if (m_node->collapsed) return 64.0;
        if (m_node->kind == QStringLiteral("checklist"))
            return qMax<qreal>(131.0, 86.0 + 20.0 * int(m_node->tasks.size()) + 13.0);
        // The full wrapped note, including explicit newlines, is visible.
        // Keep the original minimum height for short notes and decisions.
        return qMax<qreal>(m_node->kind == QStringLiteral("decision") ? 164.0 : 139.0,
                           82.0 + m_bodyDocument.size().height() + 16.0);
    }
    QRectF boundingRect() const override { return QRectF(-9, -4, Width + 18, cardHeight() + 9); }
    qreal inputY() const { return m_node->collapsed ? 47.0 : 70.0; }
    qreal portY(const QString &port) const {
        return m_node->kind == QStringLiteral("decision")
            ? (port == QStringLiteral("no") ? 128.0 : 95.0) : 70.0;
    }
    QPointF inputPoint() const { return mapToScene(QPointF(0, inputY())); }
    QPointF outputPoint(const QString &port) const { return mapToScene(QPointF(Width, portY(port))); }
    QString toggleAt(const QPointF &scenePos) const {
        if (m_node->collapsed) return {};
        const QPointF at=mapFromScene(scenePos);
        for (const QString &port : m_node->kind==QStringLiteral("decision")
             ? QStringList{QStringLiteral("yes"), QStringLiteral("no")}
             : QStringList{QStringLiteral("next")}) {
            if (QRectF(Width-30,portY(port)-9,17,18).contains(at)) return port;
        }
        return {};
    }
    QString outputAt(const QPointF &scenePos) const {
        if (m_node->collapsed) return {};
        const QPointF pt = mapFromScene(scenePos);
        if (m_node->kind == QStringLiteral("decision")) {
            if (!m_node->hiddenPorts.contains(QStringLiteral("yes")) &&
                QLineF(pt,QPointF(Width,95)).length() <= 12) return QStringLiteral("yes");
            if (!m_node->hiddenPorts.contains(QStringLiteral("no")) &&
                QLineF(pt,QPointF(Width,128)).length() <= 12) return QStringLiteral("no");
        } else if (!m_node->hiddenPorts.contains(QStringLiteral("next")) &&
                   QLineF(pt,QPointF(Width,70)).length() <= 12) return QStringLiteral("next");
        return {};
    }
    bool isInputAt(const QPointF &scenePos) const {
        return QLineF(mapFromScene(scenePos),QPointF(0,inputY())).length() <= 13;
    }
protected:
    void paint(QPainter *p, const QStyleOptionGraphicsItem *, QWidget *) override {
        p->setRenderHint(QPainter::Antialiasing, true);
        const qreal h = cardHeight();
        const QColor colour = stateColour(m_node->state);
        p->setPen(QPen(colour, isSelected()?2.5:1.5));
        p->setBrush(m_theme.panelBackground);
        p->drawRect(QRectF(1,1,Width-2,h-2)); // square corners, like Visual Nodes
        p->fillRect(QRectF(2,2,Width-4,31),m_theme.alternateBackground);
        p->fillRect(QRectF(2,31,Width-4,3),colour);
        p->setPen(m_theme.text);
        QFont font=p->font();font.setBold(true);p->setFont(font);
        p->drawText(QRectF(12,5,Width-83,25),Qt::AlignVCenter,
                    QFontMetrics(font).elidedText(m_node->title,Qt::ElideRight,int(Width-89)));
        // The small square folds the card and its outgoing branches.
        p->setPen(QPen(m_theme.mutedText,1.4));
        p->setBrush(Qt::NoBrush);
        p->drawRect(QRectF(Width-57,8,17,17));
        p->drawLine(QPointF(Width-53,16.5),QPointF(Width-44,16.5));
        if (m_node->collapsed)
            p->drawLine(QPointF(Width-48.5,12),QPointF(Width-48.5,21));
        p->setPen(QPen(colour,1.6));
        if(m_node->state==2)p->setBrush(colour);else p->setBrush(Qt::NoBrush);
        p->drawRect(QRectF(Width-28,8,17,17));
        if(m_node->state==2) {
            p->setPen(QPen(m_theme.windowBackground,2.0));
            p->drawLine(QPointF(Width-25,16),QPointF(Width-22,21));
            p->drawLine(QPointF(Width-22,21),QPointF(Width-14,12));
        }
        p->setFont(QFont());
        QFont secondary=p->font();secondary.setPointSize(qMax(7,secondary.pointSize()-1));
        p->setFont(secondary);
        p->setPen(colour);
        p->drawText(QRectF(12,40,Width-24,18),Qt::AlignVCenter,
                    stateLabel(m_node->state)+QStringLiteral("  |  ")+
                    (m_node->collapsed ? QObject::tr("BRANCHES HIDDEN") :
                     m_node->kind==QStringLiteral("checklist") ? QObject::tr("CHECKLIST") :
                     m_node->kind==QStringLiteral("decision") ? QObject::tr("DECISION") : QObject::tr("NOTE")));
        p->setPen(m_theme.mutedText);
        if (m_node->collapsed) {
            p->setPen(QPen(colour,2));
            p->setBrush(m_theme.panelBackground);
            p->drawEllipse(QPointF(0,inputY()),5.4,5.4);
            return;
        }
        if (m_node->kind==QStringLiteral("checklist")) {
            for(int i=0; i<int(m_node->tasks.size()); ++i) {
                const qreal y=82+i*20;
                p->setPen(QPen(colour,1.3));
                if(m_node->ticks.value(i))p->setBrush(colour);else p->setBrush(Qt::NoBrush);
                p->drawRect(QRectF(13,y,13,13));
                if(m_node->ticks.value(i)) {
                    p->setPen(QPen(m_theme.windowBackground,1.7));
                    p->drawLine(QPointF(15,y+6),QPointF(18,y+10));
                    p->drawLine(QPointF(18,y+10),QPointF(24,y+3));
                }
                p->setPen(m_node->ticks.value(i)?m_theme.mutedText:m_theme.text);
                p->drawText(QRectF(34,y-2,Width-47,19),Qt::AlignVCenter,
                    QFontMetrics(secondary).elidedText(m_node->tasks.at(i),Qt::ElideRight,int(Width-53)));
                if(m_node->ticks.value(i))p->drawLine(QPointF(34,y+7),QPointF(Width-20,y+7));
            }
        } else {
            // Wrap long lines and honour every explicit newline/blank paragraph.
            p->save();
            p->translate(13, 82);
            m_bodyDocument.drawContents(p);
            p->restore();
        }
        p->setPen(QPen(colour,2));p->setBrush(m_theme.panelBackground);
        p->drawEllipse(QPointF(0,inputY()),5.4,5.4);
        const QStringList ports=m_node->kind==QStringLiteral("decision")
            ? QStringList{QStringLiteral("yes"),QStringLiteral("no")}
            : QStringList{QStringLiteral("next")};
        for (const QString &port : ports) {
            const qreal y=portY(port);
            const bool hidden=m_node->hiddenPorts.contains(port);
            p->setPen(QPen(colour,1.6));
            p->setBrush(hidden?m_theme.alternateBackground:m_theme.panelBackground);
            p->drawEllipse(QPointF(Width,y),5.4,5.4);
            // Per-socket [+]/[-] folds an entire route without deleting it.
            p->setPen(QPen(m_theme.mutedText,1.3));
            p->setBrush(m_theme.alternateBackground);
            p->drawRect(QRectF(Width-30,y-8,16,16));
            p->drawLine(QPointF(Width-26,y),QPointF(Width-18,y));
            if (hidden) p->drawLine(QPointF(Width-22,y-4),QPointF(Width-22,y+4));
            if(m_node->kind==QStringLiteral("decision")) {
                p->setPen(colour);
                p->drawText(QRectF(Width-91,y-11,58,20),Qt::AlignRight,
                            port==QStringLiteral("yes")?QObject::tr("YES"):QObject::tr("NO"));
            }
        }
    }
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
        const QPointF at=event->pos();
        if(event->button()==Qt::LeftButton) {
            if(QRectF(Width-60,4,24,26).contains(at)) {
                selectOnlyThisCard();
                prepareGeometryChange();
                m_node->collapsed=!m_node->collapsed;
                update();if(changed)changed();event->accept();return;
            }
            const QString port=toggleAt(event->scenePos());
            if(!port.isEmpty()) {
                selectOnlyThisCard();
                if(m_node->hiddenPorts.contains(port))m_node->hiddenPorts.remove(port);
                else m_node->hiddenPorts.insert(port);
                update();if(changed)changed();event->accept();return;
            }
            if(QRectF(Width-32,4,28,27).contains(at)) {
                selectOnlyThisCard();
                if(m_node->kind==QStringLiteral("checklist")) {
                    const bool complete=m_node->state==2;
                    m_node->ticks.fill(!complete,m_node->tasks.size());
                    m_node->state=m_node->tasks.isEmpty()?0:(complete?0:2);
                } else m_node->state=m_node->state==2?0:2;
                update();if(changed)changed();event->accept();return;
            }
            if(m_node->kind==QStringLiteral("checklist") && at.x()>=8 && at.x()<Width-5 && at.y()>=80) {
                const int index=int((at.y()-80)/20);
                if(index>=0 && index<int(m_node->tasks.size())) {
                    selectOnlyThisCard();
                    if(m_node->ticks.size()<m_node->tasks.size())m_node->ticks.resize(m_node->tasks.size());
                    m_node->ticks[index]=!m_node->ticks[index];
                    const int count=std::count(m_node->ticks.cbegin(),m_node->ticks.cend(),true);
                    m_node->state=count==0?0:count==m_node->tasks.size()?2:1;
                    update();if(changed)changed();event->accept();return;
                }
            }
        }
        QGraphicsItem::mousePressEvent(event);
    }
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override {
        if(editRequested)editRequested();event->accept();
    }
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override {
        if(change==ItemPositionChange) {
            const QPointF point=value.toPointF();
            return QPointF(qRound(point.x()/Grid)*Grid,qRound(point.y()/Grid)*Grid);
        }
        if(change==ItemPositionHasChanged) {
            m_node->pos=value.toPointF();if(moved)moved();
        }
        return QGraphicsItem::itemChange(change,value);
    }
private:
    void refreshBodyText() {
        QFont font;
        font.setPointSize(qMax(7, font.pointSize()-1));
        m_bodyDocument.setDefaultFont(font);
        m_bodyDocument.setPlainText(m_node->text);
        // QTextDocument draws from its own character formats, not the painter
        // pen. Set the IDE theme's text colour explicitly for dark/light themes.
        QTextCursor cursor(&m_bodyDocument);
        cursor.select(QTextCursor::Document);
        QTextCharFormat format;
        format.setForeground(m_theme.text);
        cursor.mergeCharFormat(format);
    }
    // Controls consume the mouse press before Qt's normal selection handling.
    // Deselect previously selected cards first, otherwise a later drag moves
    // both the ticked card and whichever card was selected beforehand.
    void selectOnlyThisCard() {
        if (scene()) scene()->clearSelection();
        setSelected(true);
    }
    NoteNode *m_node;
    const IDETheme m_theme;
    QTextDocument m_bodyDocument;
};

class NoteView final : public QGraphicsView {
public:
    explicit NoteView(QGraphicsScene *scene,QWidget *parent=nullptr) : QGraphicsView(scene,parent) {
        setRenderHint(QPainter::Antialiasing,true);
        setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        setDragMode(QGraphicsView::RubberBandDrag);
        setFrameShape(QFrame::NoFrame);
    }
    std::function<void(NoteCard *,const QString &,const QPointF &)> finishLink;
    std::function<void()> viewChanged; // Panning or zooming changes the saved viewport.
    std::function<void()> viewResized; // Restore after Qt finishes sizing the maximized canvas.
protected:
    void resizeEvent(QResizeEvent *event) override {
        QGraphicsView::resizeEvent(event);
        if (viewResized) viewResized();
    }
    void drawBackground(QPainter *p,const QRectF &rect) override {
        QGraphicsView::drawBackground(p,rect);
        const qreal step=32;
        const qreal startX=qFloor(rect.left()/step)*step;
        const qreal startY=qFloor(rect.top()/step)*step;
        QPen pen(backgroundBrush().color().lighter(121));pen.setWidthF(0.0);p->setPen(pen);
        for(qreal x=startX;x<rect.right();x+=step)
            for(qreal y=startY;y<rect.bottom();y+=step)p->drawPoint(QPointF(x,y));
    }
    void mousePressEvent(QMouseEvent *e) override {
        if(e->button()==Qt::MiddleButton) {
            m_pan=true;m_panMoved=false;m_last=e->pos();
            viewport()->setCursor(Qt::ClosedHandCursor);e->accept();return;
        }
        if(e->button()==Qt::LeftButton) {
            auto *card=dynamic_cast<NoteCard *>(itemAt(e->pos()));
            if(card) {
                const QString port=card->outputAt(mapToScene(e->pos()));
                if(!port.isEmpty()) {
                    m_source=card;m_port=port;
                    m_temp=scene()->addPath(QPainterPath(),QPen(stateColour(card->node()->state),2.2));
                    m_temp->setZValue(-2);
                    updateDrag(mapToScene(e->pos()));
                    e->accept();return;
                }
            }
        }
        QGraphicsView::mousePressEvent(e);
    }
    void mouseMoveEvent(QMouseEvent *e) override {
        if(m_pan) {
            const QPoint delta=e->pos()-m_last;m_last=e->pos();
            if(!delta.isNull())m_panMoved=true;
            horizontalScrollBar()->setValue(horizontalScrollBar()->value()-delta.x());
            verticalScrollBar()->setValue(verticalScrollBar()->value()-delta.y());
            e->accept();return;
        }
        if(m_source){updateDrag(mapToScene(e->pos()));e->accept();return;}
        QGraphicsView::mouseMoveEvent(e);
    }
    void mouseReleaseEvent(QMouseEvent *e) override {
        if(m_pan&&e->button()==Qt::MiddleButton) {
            m_pan=false;viewport()->unsetCursor();
            if(m_panMoved && viewChanged)viewChanged();
            e->accept();return;
        }
        if(m_source&&e->button()==Qt::LeftButton) {
            const QPointF drop=mapToScene(e->pos());
            auto *target=dynamic_cast<NoteCard *>(itemAt(e->pos()));
            if(target && target!=m_source && target->isInputAt(drop) && finishLink)
                finishLink(m_source,m_port,drop);
            delete m_temp;m_temp=nullptr;m_source=nullptr;m_port.clear();e->accept();return;
        }
        QGraphicsView::mouseReleaseEvent(e);
    }
    void wheelEvent(QWheelEvent *e) override {
        const qreal factor=e->angleDelta().y()>0?1.12:1.0/1.12;
        const qreal next=transform().m11()*factor;
        if(next>=0.25 && next<=2.5) {
            scale(factor,factor);
            if(viewChanged)viewChanged();
        }
        e->accept();
    }
    void keyPressEvent(QKeyEvent *e) override {
        if(e->key()==Qt::Key_Escape && m_source) {
            delete m_temp;m_temp=nullptr;m_source=nullptr;m_port.clear();e->accept();return;
        }
        QGraphicsView::keyPressEvent(e);
    }
private:
    void updateDrag(const QPointF &end) {
        if(!m_temp||!m_source)return;
        const QPointF start=m_source->outputPoint(m_port);
        QPainterPath path(start);
        const qreal bend=qMax(55.0,qAbs(end.x()-start.x())*0.45);
        path.cubicTo(start+QPointF(bend,0),end-QPointF(bend,0),end);
        m_temp->setPath(path);
    }
    QPoint m_last;bool m_pan=false;bool m_panMoved=false;
    NoteCard *m_source=nullptr;
    QString m_port;
    QGraphicsPathItem *m_temp=nullptr;
};

class NoteFlowDialog final : public QDialog {
public:
    explicit NoteFlowDialog(const QString &path, const IDETheme &theme, QWidget *parent)
        : QDialog(parent),m_path(QFileInfo(path).absoluteFilePath()),m_theme(theme)
    {
        setWindowTitle(tr("Workflow Notes | %1").arg(QFileInfo(path).fileName()));
        setMinimumSize(850,560);
        setWindowState(windowState()|Qt::WindowMaximized);
        const QString style=QStringLiteral(
            "QDialog,QWidget { background:%1; color:%2; } "
            "QPushButton {background:%3;color:%2;border:1px solid %4;padding:6px;} "
            "QPushButton:hover {background:%5;} "
            "QLineEdit,QPlainTextEdit {background:%6;color:%2;border:1px solid %4;padding:5px;} "
            "QMenu {background:%3;color:%2;border:1px solid %4;} "
            "QMenu::item:selected {background:%5;} "
            "QToolTip {background:%3;color:%2;border:1px solid %4;}")
            .arg(theme.windowBackground.name(),theme.text.name(),theme.panelBackground.name(),
                 theme.border.name(),theme.hover.name(),theme.inputBackground.name());
        setStyleSheet(style);
        auto *root=new QVBoxLayout(this);
        auto *buttons=new QHBoxLayout;
        auto *title=new QLabel(tr("WORKFLOW NOTES"),this);
        QFont font=title->font();font.setBold(true);title->setFont(font);
        buttons->addWidget(title);
        for(const auto &entry: {QStringLiteral("+ Note"),QStringLiteral("+ Checklist"),QStringLiteral("+ Yes / No")}) {
            auto *b=new QPushButton(entry,this);buttons->addWidget(b);
            const QString kind=entry.contains(QStringLiteral("Checklist"))?QStringLiteral("checklist"):
                entry.contains(QStringLiteral("Yes"))?QStringLiteral("decision"):QStringLiteral("note");
            connect(b,&QPushButton::clicked,this,[this,kind]{addNode(kind,m_view->mapToScene(m_view->viewport()->rect().center()));});
        }
        buttons->addStretch();
        for(const auto &action:{QStringLiteral("−"),QStringLiteral("+"),QStringLiteral("Fit")}) {
            auto *b=new QPushButton(action,this);buttons->addWidget(b);
            connect(b,&QPushButton::clicked,this,[this,action]{
                if(action==QStringLiteral("Fit")){fitAll();markViewChanged();return;}
                const qreal factor=action==QStringLiteral("+")?1.2:1.0/1.2;
                const qreal zoom=m_view->transform().m11()*factor;
                if(zoom>=0.25&&zoom<=2.5) {
                    m_view->scale(factor,factor);
                    markViewChanged();
                }
            });
        }
        auto *saveButton=new QPushButton(tr("Save"),this);
        auto *closeButton=new QPushButton(tr("Close"),this);
        buttons->addWidget(saveButton);buttons->addWidget(closeButton);
        root->addLayout(buttons);
        m_scene=new QGraphicsScene(this);m_scene->setSceneRect(-15000,-15000,30000,30000);
        m_view=new NoteView(m_scene,this);
        m_view->setBackgroundBrush(m_theme.editorBackground);
        m_view->viewChanged=[this]{markViewChanged();};
        // centerOn() can run before the maximized QGraphicsView has its final
        // viewport size. Reapply the saved position after any initial resize,
        // but stop doing so as soon as the user deliberately pans or zooms.
        m_view->viewResized=[this]{
            if (!m_keepSavedCenter) return;
            QTimer::singleShot(0,this,[this]{
                if (m_keepSavedCenter) restoreViewCenter();
            });
        };
        // Keyboard/scrollbar panning is also a user view change. actionTriggered
        // only fires for user actions, not programmatic centerOn()/setValue().
        connect(m_view->horizontalScrollBar(),&QScrollBar::actionTriggered,
                this,[this](int){markViewChanged();});
        connect(m_view->verticalScrollBar(),&QScrollBar::actionTriggered,
                this,[this](int){markViewChanged();});
        root->addWidget(m_view,1);
        m_hint=new QLabel(tr("Drag cards: 8px snap  |  Checklists colour automatically  |  Drag sockets for multiple wires  |  [-] fold card or branch, [+] restore  |  Double-click to edit  |  Middle mouse pan  |  Wheel zoom"),this);
        m_hint->setWordWrap(true);root->addWidget(m_hint);
        connect(saveButton,&QPushButton::clicked,this,[this]{save();});
        connect(closeButton,&QPushButton::clicked,this,[this]{close();});
        auto *saveShortcut=new QShortcut(QKeySequence::Save,this);
        connect(saveShortcut,&QShortcut::activated,this,[this]{save();});
        auto *removeShortcut=new QShortcut(QKeySequence::Delete,m_view);
        connect(removeShortcut,&QShortcut::activated,this,[this]{deleteSelected();});
        m_view->finishLink=[this](NoteCard *source,const QString &port,const QPointF &point){
            for(NoteCard *target:m_cards) {
                if(target!=source && target->isVisible() && target->isInputAt(point)) {
                    // Fan-out is allowed from every socket; multi-input is allowed
                    // too. Only an identical duplicate connection is ignored.
                    for(const NoteLink &link:m_links)
                        if(link.source==source->node()->id && link.port==port &&
                           link.target==target->node()->id) return;
                    m_links.append({source->node()->id,port,target->node()->id});
                    markChanged();redrawLinks();return;
                }
            }
        };
        m_view->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(m_view,&QWidget::customContextMenuRequested,this,[this](const QPoint &local){
            const QPoint viewportPoint=m_view->viewport()->mapFrom(m_view,local);
            contextMenuAt(viewportPoint);
        });
        m_view->viewport()->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(m_view->viewport(),&QWidget::customContextMenuRequested,this,[this](const QPoint &pt){contextMenuAt(pt);});
    }
    bool load() {
        QFile file(m_path);
        if(!file.open(QIODevice::ReadOnly)) {
            QMessageBox::warning(this,tr("Workflow Notes"),tr("Cannot open %1: %2").arg(m_path,file.errorString()));return false;
        }
        QJsonParseError error;
        const QJsonDocument doc=QJsonDocument::fromJson(file.readAll(),&error);
        if(error.error!=QJsonParseError::NoError||!doc.isObject()) {
            QMessageBox::warning(this,tr("Workflow Notes"),tr("Invalid .notef file: %1").arg(error.errorString()));return false;
        }
        const QJsonObject obj=doc.object();
        if(obj.value(QStringLiteral("format")).toString()!=QStringLiteral("SIDBOX-NOTE-FLOW") ||
           obj.value(QStringLiteral("version")).toInt()!=1) {
            QMessageBox::warning(this,tr("Workflow Notes"),tr("Unsupported .notef format/version. No changes were made."));return false;
        }
        for(const QJsonValue &val:obj.value(QStringLiteral("nodes")).toArray()) {
            if(!val.isObject())continue;
            const QJsonObject n=val.toObject();
            const QString id=n.value(QStringLiteral("id")).toString();
            const QString kind=n.value(QStringLiteral("kind")).toString();
            if(id.isEmpty()||m_nodes.contains(id)||
               (kind!=QStringLiteral("note")&&kind!=QStringLiteral("checklist")&&kind!=QStringLiteral("decision")))continue;
            auto model=std::make_shared<NoteNode>();
            model->id=id;model->kind=kind;model->title=n.value(QStringLiteral("title")).toString();
            model->text=n.value(QStringLiteral("text")).toString();
            model->state=qBound(0,n.value(QStringLiteral("state")).toInt(),2);
            model->pos=QPointF(n.value(QStringLiteral("x")).toDouble(),n.value(QStringLiteral("y")).toDouble());
            model->collapsed=n.value(QStringLiteral("collapsed")).toBool(false);
            for(const QJsonValue &port:n.value(QStringLiteral("hiddenPorts")).toArray()) {
                const QString name=port.toString();
                if(model->kind==QStringLiteral("decision")
                   ? (name==QStringLiteral("yes") || name==QStringLiteral("no"))
                   : name==QStringLiteral("next")) model->hiddenPorts.insert(name);
            }
            for(const QJsonValue &task:n.value(QStringLiteral("tasks")).toArray()) {
                const QJsonObject t=task.toObject();
                if(!t.contains(QStringLiteral("text")))continue;
                model->tasks.append(t.value(QStringLiteral("text")).toString());
                model->ticks.append(t.value(QStringLiteral("done")).toBool());
            }
            if(model->kind==QStringLiteral("checklist")) {
                const int checked=std::count(model->ticks.cbegin(),model->ticks.cend(),true);
                model->state=checked==0?0:checked==model->tasks.size()?2:1;
            }
            m_nodes.insert(id,model);addCard(model.get());
        }
        for(const QJsonValue &value:obj.value(QStringLiteral("links")).toArray()) {
            const QJsonObject l=value.toObject();
            NoteLink link{l.value(QStringLiteral("source")).toString(),
                          l.value(QStringLiteral("port")).toString(),
                          l.value(QStringLiteral("target")).toString()};
            if(!m_nodes.contains(link.source)||!m_nodes.contains(link.target)||link.source==link.target)continue;
            const QString sourceKind=m_nodes.value(link.source)->kind;
            if(link.port!=QStringLiteral("next")&&link.port!=QStringLiteral("yes")&&link.port!=QStringLiteral("no"))continue;
            if(sourceKind==QStringLiteral("decision") ? link.port==QStringLiteral("next") : link.port!=QStringLiteral("next"))continue;
            bool duplicate=false;
            for(const NoteLink &existing:m_links)
                if(existing.source==link.source && existing.port==link.port &&
                   existing.target==link.target) duplicate=true;
            if(!duplicate)m_links.append(link);
        }
        redrawLinks();
        const QJsonObject view=obj.value(QStringLiteral("view")).toObject();
        const qreal zoom=qBound(0.25,view.value(QStringLiteral("zoom")).toDouble(1),2.5);
        m_view->scale(zoom,zoom);
        m_hasSavedView=view.contains(QStringLiteral("cx")) && view.contains(QStringLiteral("cy"));
        if(m_hasSavedView)
            m_savedViewCenter=QPointF(view.value(QStringLiteral("cx")).toDouble(),
                                     view.value(QStringLiteral("cy")).toDouble());
        m_hasSavedScroll=view.contains(QStringLiteral("scrollX")) && view.contains(QStringLiteral("scrollY")) &&
                         view.contains(QStringLiteral("viewportWidth")) && view.contains(QStringLiteral("viewportHeight"));
        if(m_hasSavedScroll) {
            m_savedScrollX=view.value(QStringLiteral("scrollX")).toInt();
            m_savedScrollY=view.value(QStringLiteral("scrollY")).toInt();
            m_savedViewportSize=QSize(view.value(QStringLiteral("viewportWidth")).toInt(),
                                       view.value(QStringLiteral("viewportHeight")).toInt());
        }
        m_keepSavedCenter=m_hasSavedView;
        m_viewRestorePending=true;
        return true;
    }
protected:
    void showEvent(QShowEvent *event) override {
        QDialog::showEvent(event);
        if(!m_viewRestorePending)return;
        m_viewRestorePending=false;
        // Wait for the graphics view's layout before using its scene centre.
        // The viewResized callback above reapplies the saved position if the
        // window manager performs another maximize/viewport resize afterwards.
        QTimer::singleShot(0,this,[this]{
            if(m_hasSavedView) restoreViewCenter();
            else fitAll();
        });
    }
    void closeEvent(QCloseEvent *event) override {
        if(m_dirty) {
            const auto answer=QMessageBox::question(this,tr("Unsaved Workflow Notes"),
                tr("Save changes to %1?").arg(QFileInfo(m_path).fileName()),
                QMessageBox::Save|QMessageBox::Discard|QMessageBox::Cancel,QMessageBox::Save);
            if(answer==QMessageBox::Cancel) {event->ignore();return;}
            if(answer==QMessageBox::Save) {
                if(!save()) {event->ignore();return;}
            } else if(m_viewDirty && !saveViewOnly()) {
                event->ignore();return;
            }
        } else if(m_viewDirty && !saveViewOnly()) {
            event->ignore();return;
        }
        event->accept();
    }
private:
    void markChanged() {m_dirty=true;setWindowTitle(tr("Workflow Notes | %1 *").arg(QFileInfo(m_path).fileName()));}
    void markViewChanged() {
        m_keepSavedCenter=false; // Never overwrite a user's new pan with the old saved centre.
        m_viewDirty=true;
    }
    void restoreViewCenter() {
        if(!m_hasSavedView || !m_view || m_view->viewport()->width()<1 || m_view->viewport()->height()<1)return;
        // Exact scroll values give pixel-for-pixel restoration at the same
        // viewport size. For a different window size, preserve scene centre.
        if(m_hasSavedScroll && m_view->viewport()->size()==m_savedViewportSize) {
            m_view->horizontalScrollBar()->setValue(m_savedScrollX);
            m_view->verticalScrollBar()->setValue(m_savedScrollY);
        } else {
            m_view->centerOn(m_savedViewCenter);
        }
    }
    QJsonObject currentView() const {
        const QPointF center=m_view->mapToScene(m_view->viewport()->rect().center());
        return {{QStringLiteral("zoom"),m_view->transform().m11()},
                {QStringLiteral("cx"),center.x()},{QStringLiteral("cy"),center.y()},
                {QStringLiteral("scrollX"),m_view->horizontalScrollBar()->value()},
                {QStringLiteral("scrollY"),m_view->verticalScrollBar()->value()},
                {QStringLiteral("viewportWidth"),m_view->viewport()->width()},
                {QStringLiteral("viewportHeight"),m_view->viewport()->height()}};
    }
    // Panning is editor navigation, not a content edit. Save the viewport
    // automatically on Close, without forcing a Save/Discard notes prompt.
    bool saveViewOnly() {
        QFile input(m_path);
        if(!input.open(QIODevice::ReadOnly)) {
            QMessageBox::warning(this,tr("Workflow Notes"),tr("Cannot read %1: %2").arg(m_path,input.errorString()));
            return false;
        }
        QJsonParseError error;
        QJsonDocument document=QJsonDocument::fromJson(input.readAll(),&error);
        input.close();
        if(error.error!=QJsonParseError::NoError || !document.isObject()) {
            QMessageBox::warning(this,tr("Workflow Notes"),tr("Cannot save viewport: invalid .notef file."));
            return false;
        }
        QJsonObject obj=document.object();
        if(obj.value(QStringLiteral("format")).toString()!=QStringLiteral("SIDBOX-NOTE-FLOW")) return false;
        obj.insert(QStringLiteral("view"),currentView());
        QSaveFile output(m_path);
        if(!output.open(QIODevice::WriteOnly) ||
           output.write(QJsonDocument(obj).toJson(QJsonDocument::Indented))<0 || !output.commit()) {
            QMessageBox::warning(this,tr("Workflow Notes"),tr("Cannot save viewport to %1: %2").arg(m_path,output.errorString()));
            return false;
        }
        m_viewDirty=false;
        return true;
    }
    void addCard(NoteNode *node) {
        auto *item=new NoteCard(node,m_theme);m_scene->addItem(item);
        item->changed=[this]{markChanged();redrawLinks();};
        item->moved=[this]{markChanged();redrawLinks();};
        item->editRequested=[this,node]{editNode(node);};
        m_cards.insert(node->id,item);
    }
    void addNode(const QString &kind,const QPointF &center) {
        auto node=std::make_shared<NoteNode>();
        node->id=QUuid::createUuid().toString(QUuid::WithoutBraces);
        node->kind=kind;
        node->title=kind==QStringLiteral("decision")?tr("A decision"):
            kind==QStringLiteral("checklist")?tr("Things to do"):tr("New note");
        node->text=kind==QStringLiteral("decision")?tr("Is this ready?"):tr("Double-click to edit this note.");
        if(kind==QStringLiteral("checklist")){node->tasks={tr("First task")};node->ticks={false};}
        node->pos=center-QPointF(NoteCard::Width/2,70);
        m_nodes.insert(node->id,node);addCard(node.get());markChanged();
        m_cards[node->id]->setSelected(true);
        editNode(node.get());
    }
    void editNode(NoteNode *node) {
        QDialog dialog(this);dialog.setWindowTitle(tr("Edit %1").arg(node->title));dialog.resize(470,340);
        dialog.setStyleSheet(styleSheet());
        auto *layout=new QVBoxLayout(&dialog);
        auto *form=new QFormLayout;
        auto *name=new QLineEdit(node->title,&dialog);form->addRow(tr("Title:"),name);
        layout->addLayout(form);
        auto *body=new QPlainTextEdit(&dialog);
        body->setPlaceholderText(node->kind==QStringLiteral("checklist") ? tr("One task per line") : tr("Write your note or question"));
        body->setPlainText(node->kind==QStringLiteral("checklist") ? node->tasks.join(QLatin1Char('\n')):node->text);
        layout->addWidget(body,1);
        auto *controls=new QHBoxLayout;
        auto *cancel=new QPushButton(tr("Cancel"),&dialog);
        auto *ok=new QPushButton(tr("Apply"),&dialog);ok->setDefault(true);
        controls->addStretch();controls->addWidget(cancel);controls->addWidget(ok);layout->addLayout(controls);
        connect(cancel,&QPushButton::clicked,&dialog,&QDialog::reject);
        connect(ok,&QPushButton::clicked,&dialog,&QDialog::accept);
        if(dialog.exec()!=QDialog::Accepted)return;
        if(auto *card=m_cards.value(node->id,nullptr))card->beginContentUpdate();
        const QString newTitle=name->text().trimmed().left(120);
        if(!newTitle.isEmpty())node->title=newTitle;
        if(node->kind==QStringLiteral("checklist")) {
            QStringList lines=body->toPlainText().split(QLatin1Char('\n'));
            for(int i=lines.size()-1;i>=0;--i)if(lines[i].trimmed().isEmpty())lines.removeAt(i);
            QVector<bool> ticks;
            for(int i=0;i<lines.size();++i)
                ticks.append(i<node->tasks.size()&&lines[i]==node->tasks[i]&&node->ticks.value(i));
            node->tasks=lines;node->ticks=ticks;
            const int checked=std::count(node->ticks.cbegin(),node->ticks.cend(),true);
            node->state=checked==0?0:checked==node->tasks.size()?2:1;
        }else node->text=body->toPlainText();
        if(auto *card=m_cards.value(node->id,nullptr))card->endContentUpdate();
        markChanged();redrawLinks();
    }
    void deleteSelected() {
        // Snapshot identities BEFORE deleting any scene items. The scene's
        // selectedItems() list is not updated when we delete a pointer from
        // it, so a second dynamic_cast pass would dereference freed memory.
        QSet<QString> cardIds;
        QSet<int> edgeIndices;
        for (QGraphicsItem *item : m_scene->selectedItems()) {
            if (auto *card = dynamic_cast<NoteCard *>(item)) {
                cardIds.insert(card->node()->id);
            } else if (auto *edge = dynamic_cast<QGraphicsPathItem *>(item)) {
                const int index = edge->data(0).toInt();
                if (index >= 0 && index < m_links.size()) edgeIndices.insert(index);
            }
        }

        bool removed = false;
        for (int i = m_links.size() - 1; i >= 0; --i) {
            if (edgeIndices.contains(i) || cardIds.contains(m_links[i].source)
                    || cardIds.contains(m_links[i].target)) {
                m_links.removeAt(i);
                removed = true;
            }
        }
        for (const QString &id : cardIds) {
            NoteCard *card = m_cards.take(id);
            if (!card) continue;
            m_scene->removeItem(card);
            delete card;
            m_nodes.remove(id);
            removed = true;
        }
        if (removed) { markChanged(); redrawLinks(); }
    }
    void redrawLinks() {
        // Keep every node and wire in the file. Collapsing changes *visibility*
        // only. Follow open routes from the roots so a join stays visible when
        // at least one other active path still reaches it.
        QSet<QString> roots;
        QHash<QString,QStringList> neighbours;
        QHash<QString,QVector<NoteLink>> outgoing;
        for(auto it=m_nodes.cbegin();it!=m_nodes.cend();++it)roots.insert(it.key());
        for(const NoteLink &link:m_links) {
            roots.remove(link.target);
            neighbours[link.source].append(link.target);
            neighbours[link.target].append(link.source);
            outgoing[link.source].append(link);
        }
        // A standalone cycle may have no incoming-free root. Give that
        // component one stable entry point instead of making it disappear.
        QSet<QString> componentSeen;
        QStringList ids=m_nodes.keys();ids.sort();
        for(const QString &id:ids) {
            if(componentSeen.contains(id))continue;
            QStringList work{id};componentSeen.insert(id);
            bool hasRoot=roots.contains(id);
            for(int i=0;i<work.size();++i) {
                for(const QString &other:neighbours.value(work[i])) {
                    if(componentSeen.contains(other))continue;
                    componentSeen.insert(other);work.append(other);
                    if(roots.contains(other))hasRoot=true;
                }
            }
            if(!hasRoot)roots.insert(id);
        }
        QSet<QString> visible=roots;
        QStringList work=roots.values();
        for(int i=0;i<work.size();++i) {
            const auto node=m_nodes.value(work[i]);
            if(!node || node->collapsed)continue;
            for(const NoteLink &link:outgoing.value(work[i])) {
                if(node->hiddenPorts.contains(link.port) || visible.contains(link.target))continue;
                visible.insert(link.target);work.append(link.target);
            }
        }
        for(auto it=m_cards.cbegin();it!=m_cards.cend();++it) {
            const bool show=visible.contains(it.key());
            if(it.value()->isVisible()!=show)it.value()->setVisible(show);
        }
        for(QGraphicsPathItem *edge:m_edges){m_scene->removeItem(edge);delete edge;}
        m_edges.clear();
        for(int i=0;i<m_links.size();++i) {
            const NoteLink &link=m_links[i];
            NoteCard *a=m_cards.value(link.source,nullptr),*b=m_cards.value(link.target,nullptr);
            if(!a||!b || !a->isVisible() || !b->isVisible() ||
               a->node()->collapsed || a->node()->hiddenPorts.contains(link.port))continue;
            const QPointF from=a->outputPoint(link.port),to=b->inputPoint();
            const qreal bend=qMax(50.0,qAbs(from.x()-to.x())*.5);
            QPainterPath path(from);path.cubicTo(from+QPointF(bend,0),to-QPointF(bend,0),to);
            auto *edge=new NoteWire;
            edge->setPath(path);
            edge->setPen(QPen(stateColour(a->node()->state),2.0));
            m_scene->addItem(edge);
            edge->setFlag(QGraphicsItem::ItemIsSelectable,true);
            edge->setData(0,i);edge->setZValue(-5);
            m_edges.append(edge);
        }
    }
    void fitAll() {
        if(m_cards.isEmpty()){m_view->centerOn(0,0);return;}
        QRectF rect;
        for(NoteCard *card:m_cards)
            if(card->isVisible())rect=rect.united(card->sceneBoundingRect());
        if(rect.isEmpty()){m_view->centerOn(0,0);return;}
        m_view->resetTransform();m_view->fitInView(rect.adjusted(-125,-100,125,100),Qt::KeepAspectRatio);
        if(m_view->transform().m11()>1.3)m_view->resetTransform();
    }
    void contextMenuAt(const QPoint &pt) {
        QGraphicsItem *item=m_view->itemAt(pt);
        auto *card=dynamic_cast<NoteCard *>(item);
        QMenu menu(this);
        if(card){
            auto *edit=menu.addAction(tr("Edit node..."));
            auto *fold=menu.addAction(card->node()->collapsed ? tr("Expand card and branches") : tr("Collapse card and branches"));
            auto *foldNext=card->node()->kind==QStringLiteral("decision") ? nullptr :
                menu.addAction(card->node()->hiddenPorts.contains(QStringLiteral("next")) ? tr("Show NEXT branch") : tr("Hide NEXT branch"));
            auto *foldYes=card->node()->kind==QStringLiteral("decision") ?
                menu.addAction(card->node()->hiddenPorts.contains(QStringLiteral("yes")) ? tr("Show YES branch") : tr("Hide YES branch")) : nullptr;
            auto *foldNo=card->node()->kind==QStringLiteral("decision") ?
                menu.addAction(card->node()->hiddenPorts.contains(QStringLiteral("no")) ? tr("Show NO branch") : tr("Hide NO branch")) : nullptr;
            menu.addSeparator();
            QAction *newState=nullptr,*progress=nullptr,*done=nullptr;
            if(card->node()->kind!=QStringLiteral("checklist")) {
                newState=menu.addAction(tr("New"));
                progress=menu.addAction(tr("In Progress"));
                done=menu.addAction(tr("Done"));
            } else menu.addAction(tr("Checklist state follows its ticks"))->setEnabled(false);
            menu.addSeparator();
            auto *disconnect=menu.addAction(tr("Remove all connections"));
            auto *remove=menu.addAction(tr("Delete node"));
            QAction *chosen=menu.exec(m_view->viewport()->mapToGlobal(pt));
            if(chosen==edit)editNode(card->node());
            else if(chosen==fold) {
                card->beginContentUpdate();card->node()->collapsed=!card->node()->collapsed;
                card->update();markChanged();redrawLinks();
            } else if((foldNext && chosen==foldNext) || (foldYes && chosen==foldYes) || (foldNo && chosen==foldNo)) {
                const QString port=chosen==foldNext?QStringLiteral("next"):
                    chosen==foldYes?QStringLiteral("yes"):QStringLiteral("no");
                if(card->node()->hiddenPorts.contains(port))card->node()->hiddenPorts.remove(port);
                else card->node()->hiddenPorts.insert(port);
                card->update();markChanged();redrawLinks();
            } else if(chosen && (chosen==newState||chosen==progress||chosen==done)) {
                card->node()->state=chosen==done?2:chosen==progress?1:0;
                card->update();markChanged();redrawLinks();
            }else if(chosen==disconnect) {
                const QString id=card->node()->id;
                for(int i=m_links.size()-1;i>=0;--i)
                    if(m_links[i].source==id||m_links[i].target==id)m_links.removeAt(i);
                markChanged();redrawLinks();
            }else if(chosen==remove) {
                const QString id=card->node()->id;
                m_scene->removeItem(card);m_cards.remove(id);delete card;m_nodes.remove(id);
                for(int i=m_links.size()-1;i>=0;--i)
                    if(m_links[i].source==id||m_links[i].target==id)m_links.removeAt(i);
                markChanged();redrawLinks();
            }
            return;
        }
        auto *note=menu.addAction(tr("Add Note"));
        auto *list=menu.addAction(tr("Add Checklist"));
        auto *decision=menu.addAction(tr("Add Yes / No Decision"));
        QAction *removeLink=nullptr;
        auto *edge=dynamic_cast<QGraphicsPathItem *>(item);
        if(edge){menu.addSeparator();removeLink=menu.addAction(tr("Remove connection"));}
        QAction *choice=menu.exec(m_view->viewport()->mapToGlobal(pt));
        const QPointF at=m_view->mapToScene(pt);
        if(choice==note)addNode(QStringLiteral("note"),at);
        else if(choice==list)addNode(QStringLiteral("checklist"),at);
        else if(choice==decision)addNode(QStringLiteral("decision"),at);
        else if(choice==removeLink&&edge) {
            const int index=edge->data(0).toInt();
            if(index>=0&&index<m_links.size()){m_links.removeAt(index);markChanged();redrawLinks();}
        }
    }
    bool save() {
        QJsonArray nodes;
        for(auto it=m_nodes.cbegin();it!=m_nodes.cend();++it) {
            const NoteNode &n=*it.value();
            QJsonObject obj{{QStringLiteral("id"),n.id},{QStringLiteral("kind"),n.kind},
                {QStringLiteral("title"),n.title},{QStringLiteral("text"),n.text},
                {QStringLiteral("state"),n.state},{QStringLiteral("x"),n.pos.x()},
                {QStringLiteral("y"),n.pos.y()},
                {QStringLiteral("collapsed"),n.collapsed}};
            QJsonArray hidden;
            QStringList ports=n.hiddenPorts.values();ports.sort();
            for(const QString &port:ports)hidden.append(port);
            obj.insert(QStringLiteral("hiddenPorts"),hidden);
            QJsonArray tasks;
            for(int i=0;i<n.tasks.size();++i)
                tasks.append(QJsonObject{{QStringLiteral("text"),n.tasks[i]},
                    {QStringLiteral("done"),n.ticks.value(i)}});
            obj.insert(QStringLiteral("tasks"),tasks);
            nodes.append(obj);
        }
        QJsonArray links;
        for(const NoteLink &l:m_links)
            links.append(QJsonObject{{QStringLiteral("source"),l.source},
                {QStringLiteral("port"),l.port},{QStringLiteral("target"),l.target}});
        const QJsonObject obj{{QStringLiteral("format"),QStringLiteral("SIDBOX-NOTE-FLOW")},
            {QStringLiteral("version"),1},{QStringLiteral("nodes"),nodes},
            {QStringLiteral("links"),links},{QStringLiteral("view"),currentView()}};
        QSaveFile file(m_path);
        if(!file.open(QIODevice::WriteOnly)||file.write(QJsonDocument(obj).toJson(QJsonDocument::Indented))<0||!file.commit()) {
            QMessageBox::warning(this,tr("Workflow Notes"),tr("Cannot save %1: %2").arg(m_path,file.errorString()));
            return false;
        }
        m_dirty=false;
        m_viewDirty=false;
        setWindowTitle(tr("Workflow Notes | %1").arg(QFileInfo(m_path).fileName()));
        return true;
    }
    const QString m_path;
    const IDETheme m_theme;
    QGraphicsScene *m_scene=nullptr;
    NoteView *m_view=nullptr;
    QLabel *m_hint=nullptr;
    QHash<QString,std::shared_ptr<NoteNode>> m_nodes;
    QHash<QString,NoteCard *> m_cards;
    QVector<NoteLink> m_links;
    QVector<QGraphicsPathItem *> m_edges;
    QPointF m_savedViewCenter;
    bool m_hasSavedView=false;
    bool m_viewRestorePending=false;
    bool m_keepSavedCenter=false;
    bool m_hasSavedScroll=false;
    int m_savedScrollX=0;
    int m_savedScrollY=0;
    QSize m_savedViewportSize;
    bool m_viewDirty=false;
    bool m_dirty=false;
};
} // namespace

bool createEmptyNoteFlowFile(const QString &path,QString *error)
{
    if(QFileInfo::exists(path)) {
        if(error)*error=QObject::tr("The file already exists.");
        return false;
    }
    QSaveFile file(path);
    if(!file.open(QIODevice::WriteOnly)) {
        if(error)*error=file.errorString();return false;
    }
    const QJsonObject data{{QStringLiteral("format"),QStringLiteral("SIDBOX-NOTE-FLOW")},
        {QStringLiteral("version"),1},{QStringLiteral("nodes"),QJsonArray()},
        {QStringLiteral("links"),QJsonArray()}};
    if(file.write(QJsonDocument(data).toJson(QJsonDocument::Indented))<0||!file.commit()) {
        if(error)*error=file.errorString();return false;
    }
    return true;
}

bool openNoteFlowEditor(QWidget *parent,const QString &path,const IDETheme &theme)
{
    NoteFlowDialog dialog(path,theme,parent);
    if(!dialog.load())return false;
    dialog.exec();
    return true;
}
