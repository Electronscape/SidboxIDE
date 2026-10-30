#ifndef SIDBOX_GAME_VISUAL_GRAPH_LOGIC_H
#define SIDBOX_GAME_VISUAL_GRAPH_LOGIC_H

// Stage 5.166.60: real, independent, typed Boolean logic nodes.
// This data belongs to .sbgm object logic, never to the .vsgm layout.
// A node is evaluated once per activation, after the owner's ordinary actions.
// Node-to-node edges form a DAG; cycles and dangling inputs are rejected.
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QHash>
#include <QSet>
#include <QString>
#include <QStringList>
#include <QVector>
#include <functional>

namespace SidboxVisualLogic {

struct Input {
    QString kind;            // "object", "node", or one-frame "event"
    QString id;              // stable resource ID or logic node ID
    bool invert = false;     // a FALSE output means NOT the upstream result
};
struct Node {
    QString id;
    QString op;              // boolean/not (1), and (2..16), or (2..8)
    QVector<Input> inputs;
    QJsonArray trueActions, falseActions;
    QStringList resultTargets; // RESULT directly drives each Game Object active state.
    int trueDialogue = -1, falseDialogue = -1;
};

inline bool read(const QJsonArray &raw, QVector<Node> *nodes, QString *error) {
    if (raw.size()>64) { if(error)*error=QStringLiteral("Maximum 64 logic nodes per Game Object.");return false; }
    QSet<QString> ids;
    QVector<Node> parsed;
    for (const QJsonValue &item:raw) {
        if (!item.isObject()) {if(error)*error=QStringLiteral("Logic node must be an object.");return false;}
        const QJsonObject o=item.toObject();
        Node n;
        n.id=o.value(QStringLiteral("id")).toString();
        n.op=o.value(QStringLiteral("op")).toString();
        if(n.id.isEmpty() || n.id.size()>64 || ids.contains(n.id)) {
            if(error)*error=QStringLiteral("Duplicate, missing or overly long logic node ID: %1").arg(n.id);
            return false;
        }
        for (const QChar c:n.id) if(!c.isLetterOrNumber() && c!=QLatin1Char('_') && c!=QLatin1Char('-')) {
            if(error)*error=QStringLiteral("Invalid logic node ID: %1").arg(n.id);return false;
        }
        ids.insert(n.id);
        if(n.op!=QStringLiteral("boolean") && n.op!=QStringLiteral("not") &&
           n.op!=QStringLiteral("and") && n.op!=QStringLiteral("or")) {
            if(error)*error=QStringLiteral("Unknown operator on logic node %1.").arg(n.id);
            return false;
        }
        const QJsonArray rawInputs=o.value(QStringLiteral("inputs")).toArray();
        if(rawInputs.size()>16 || (n.op==QStringLiteral("boolean") || n.op==QStringLiteral("not")
              ? rawInputs.size()!=1 : n.op==QStringLiteral("or") ? (rawInputs.size()<2 || rawInputs.size()>8) : rawInputs.size()<2)) {
            if(error)*error=QStringLiteral("Logic node %1 has an invalid number of inputs.").arg(n.id);
            return false;
        }
        QSet<QString> unique;
        for(int inputIndex=0;inputIndex<rawInputs.size();++inputIndex) {
            const QJsonObject input=rawInputs.at(inputIndex).toObject();
            Input in{input.value(QStringLiteral("kind")).toString(),
                     input.value(QStringLiteral("id")).toString(),
                     input.value(QStringLiteral("invert")).toBool(false)};
            const QString eventKind=in.id.section(QLatin1Char(':'),1,1);
            const bool eventIdValid=in.id.startsWith(QStringLiteral("@event:")) &&
                (eventKind==QStringLiteral("arrival") || eventKind==QStringLiteral("hit") ||
                 eventKind==QStringLiteral("destroy") || eventKind==QStringLiteral("pickup") ||
                 eventKind==QStringLiteral("player_hit") || eventKind==QStringLiteral("enter") ||
                 eventKind==QStringLiteral("save") || eventKind==QStringLiteral("defeat") ||
                 eventKind==QStringLiteral("trigger"));
            if ((in.kind!=QStringLiteral("object") && in.kind!=QStringLiteral("node") &&
                 in.kind!=QStringLiteral("event")) || in.id.isEmpty() ||
                (in.kind==QStringLiteral("event") &&
                 (!eventIdValid || in.id.section(QLatin1Char(':'),2).isEmpty()))) {
                // State exactly which saved input is wrong. Older, mixed-version
                // installations accepted arrival events but not breakable events.
                if(error)*error=QStringLiteral("Logic node %1 INPUT %2 is invalid: kind='%3', id='%4'.")
                    .arg(n.id).arg(inputIndex+1).arg(in.kind).arg(in.id);
                return false;
            }
            const QString identity=in.kind+QLatin1Char(':')+in.id+(in.invert?QStringLiteral(":not"):QString());
            if(unique.contains(identity)) {
                if(error)*error=QStringLiteral("Logic node %1 contains a duplicate input.").arg(n.id);
                return false;
            }
            unique.insert(identity);
            n.inputs.append(in);
        }
        const QJsonArray rawResultTargets=o.value(QStringLiteral("resultTargets")).toArray();
        if(rawResultTargets.size()>64) {
            if(error)*error=QStringLiteral("Logic node %1 exceeds 64 RESULT targets.").arg(n.id);
            return false;
        }
        QSet<QString> bound;
        for(const QJsonValue &v:rawResultTargets) {
            if(!v.isString() || v.toString().isEmpty() || bound.contains(v.toString())) {
                if(error)*error=QStringLiteral("Logic node %1 has an invalid or duplicate RESULT target.").arg(n.id);
                return false;
            }
            bound.insert(v.toString());n.resultTargets.append(v.toString());
        }
        n.trueActions=o.value(QStringLiteral("trueActions")).toArray();
        n.falseActions=o.value(QStringLiteral("falseActions")).toArray();
        n.trueDialogue=o.value(QStringLiteral("trueDialogueNode")).toInt(-1);
        n.falseDialogue=o.value(QStringLiteral("falseDialogueNode")).toInt(-1);
        if(n.trueActions.size()>64 || n.falseActions.size()>64) {
            if(error)*error=QStringLiteral("Logic node %1 exceeds 64 actions per branch.").arg(n.id);
            return false;
        }
        parsed.append(n);
    }
    if(nodes)*nodes=parsed;
    return true;
}

// Build a topological schedule. Independently validates missing objects,
// dangling logic links and cycles. No graph is partially generated on error.
inline bool order(const QVector<Node> &nodes,const QSet<QString> &objects,
                  QVector<int> *sorted,QString *error) {
    QHash<QString,int> byId;
    for(int i=0;i<nodes.size();++i)byId.insert(nodes[i].id,i);
    QVector<int> states(nodes.size(),0),result;
    std::function<bool(int)> visit=[&](int i) -> bool {
        if(states[i]==2)return true;
        if(states[i]==1) {
            if(error)*error=QStringLiteral("Logic cycle involving node %1.").arg(nodes[i].id);
            return false;
        }
        states[i]=1;
        for(const QString &target:nodes[i].resultTargets)
            if(target.startsWith(QStringLiteral("@event:")) ||
               target.startsWith(QStringLiteral("@triggerstate:")) || !objects.contains(target)) {
                if(error)*error=QStringLiteral("Logic node %1 drives missing Game Object %2.")
                    .arg(nodes[i].id,target);
                return false;
            }
        for(const Input &input:nodes[i].inputs) {
            if(input.kind==QStringLiteral("object") && !objects.contains(input.id)) {
                if(error)*error=QStringLiteral("Logic node %1 reads missing Game Object %2.")
                    .arg(nodes[i].id,input.id);
                return false;
            }
            if(input.kind==QStringLiteral("event")) {
                // Event sockets are pulses belonging to real Game Objects, not
                // separately saved resources. Accept the source object's UUID
                // even when the caller supplies only ordinary object IDs.
                // The exporter additionally checks the event kind and owner.
                const QString sourceId=input.id.section(QLatin1Char(':'),2);
                if(!objects.contains(sourceId) && !objects.contains(input.id)) {
                    if(error)*error=QStringLiteral("Logic node %1 reads a missing event %2 (source Game Object %3 is missing).")
                        .arg(nodes[i].id).arg(input.id).arg(sourceId);
                    return false;
                }
            }
            if(input.kind==QStringLiteral("node")) {
                if(!byId.contains(input.id)) {
                    if(error)*error=QStringLiteral("Logic node %1 references missing node %2.")
                        .arg(nodes[i].id,input.id);
                    return false;
                }
                if(!visit(byId.value(input.id)))return false;
            }
        }
        states[i]=2;result.append(i);return true;
    };
    for(int i=0;i<nodes.size();++i)if(!visit(i))return false;
    if(sorted)*sorted=result;
    return true;
}

inline QString expression(const Node &node,const QHash<QString,QString> &objects,
                          const QHash<QString,QString> &values) {
    QStringList parts;
    for(const Input &input:node.inputs) {
        QString x=input.kind==QStringLiteral("object")
            ? objects.value(input.id)+QStringLiteral(".active")
            : input.kind==QStringLiteral("event") ? objects.value(input.id) : values.value(input.id);
        if(input.invert)x=QStringLiteral("!(%1)").arg(x);
        parts.append(QStringLiteral("(%1)").arg(x));
    }
    QString joined=parts.join(node.op==QStringLiteral("or")?QStringLiteral(" || "):
                              QStringLiteral(" && "));
    if(node.op==QStringLiteral("not"))joined=QStringLiteral("!(%1)").arg(joined);
    return joined;
}
}
#endif
