#include "gameadventuregen.h"
#include "gamehelpertemplates.h"
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QJsonArray>
#include <QMap>
#include <QRegularExpression>
#include <QSaveFile>
#include <QSet>
#include <QStringList>
#include <QTextStream>
#include <algorithm>

namespace {
QString quoted(const QString &src)
{
    QString result = QStringLiteral("\"");
    for (const unsigned char c : src.toUtf8()) {
        if (c == '\\' || c == '"') { result += QLatin1Char('\\'); result += QChar(c); }
        else if (c == '\n') result += QStringLiteral("\\n");
        else if (c == '\r') result += QStringLiteral("\\r");
        else if (c >= 32 && c <= 126) result += QChar(c);
        else result += QStringLiteral("\\%1").arg(int(c),3,8,QLatin1Char('0'));
    }
    return result + QLatin1Char('"');
}
int clampInt(const QJsonObject &obj, const char *key, int lo, int hi, int fallback)
{
    return std::clamp(obj.value(QLatin1String(key)).toInt(fallback), lo, hi);
}
bool save(const QString &path, const QByteArray &bytes, QString *error)
{
    QSaveFile file(path);
    if (!file.open(QIODevice::WriteOnly) || file.write(bytes) != bytes.size() || !file.commit()) {
        file.cancelWriting();
        if (error) *error = QStringLiteral("Cannot write generated %1").arg(path);
        return false;
    }
    return true;
}

// A broken or incomplete story rule must not overwrite a working project.
// Require every data block: accidentally removing a marker from a customized
// rule would otherwise silently discard an NPC, dialogue or event action.
bool loadRule(const QDir &folder, const QString &extension,
              const QMap<QString,QString> &fields,
              const QStringList &required, QByteArray *output, QString *error,
              const QByteArray *preloaded = nullptr)
{
    const QString path = folder.filePath(QStringLiteral("gameadventure") + extension);
    QByteArray source;
    if (preloaded) {
        source = *preloaded;
    } else {
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly)) {
            if (error) *error = QStringLiteral("Cannot read Adventure story rule: %1").arg(path);
            return false;
        }
        source = file.readAll();
    }
    for (const QString &name : required) {
        if (!source.contains(QStringLiteral("@IDE{%1}").arg(name).toUtf8())) {
            if (error) *error = QStringLiteral("The Adventure story rule %1 is missing required @IDE{%2}. ")
                .arg(path, name) + QStringLiteral("No project files were changed.");
            return false;
        }
    }
    QByteArray conditional;
    return GameHelperTemplates::renderConditionals(source, fields, path, &conditional, error)
        && GameHelperTemplates::renderFields(conditional, fields, path, output, error);
}
} // namespace

bool generateGameAdventure(const QJsonObject &payload, const QString &projectRoot,
                           const QVector<GameAdventureAsset> &sprites,
                           const QVector<GameAdventureAsset> &atlases,
                           const QVector<GameAdventureAsset> &worldObjects,
                           const QString &gameRulesDirectory, QString *error)
{
    const QJsonArray itemList = payload.value(QStringLiteral("items")).toArray();
    const QJsonArray nodes = payload.value(QStringLiteral("nodes")).toArray();
    const QJsonArray npcList = payload.value(QStringLiteral("npcs")).toArray();
    if (itemList.size() > 64 || nodes.size() > 256 || npcList.size() > 256) {
        if (error) *error = QStringLiteral("Adventure limits: 64 items, 256 dialogue nodes, 256 NPCs.");
        return false;
    }

    const QDir rules(gameRulesDirectory);
    const QString ruleCPath = rules.filePath(QStringLiteral("gameadventure.rulec"));
    QFile ruleCFile(ruleCPath);
    if (!ruleCFile.open(QIODevice::ReadOnly)) {
        if (error) *error = QStringLiteral("Cannot read Adventure story rule: %1").arg(ruleCPath);
        return false;
    }
    QString ruleText = QString::fromUtf8(ruleCFile.readAll());
    const QRegularExpression linkedRe(QStringLiteral(
        R"((?ms)^@IDE_SECTION\{LINKED_ACTION\}[ \t]*\r?\n(.*?)^@IDE_SECTION_END[ \t]*\r?\n?)"));
    const auto linkedMatch = linkedRe.match(ruleText);
    if (!linkedMatch.hasMatch() || ruleText.count(QStringLiteral("@IDE_SECTION{")) != 1
        || ruleText.count(QStringLiteral("@IDE_SECTION_END")) != 1) {
        if (error) *error = QStringLiteral("Missing or malformed LINKED_ACTION section in %1. ")
            .arg(ruleCPath) + QStringLiteral("No project files were changed.");
        return false;
    }
    const QByteArray linkedActionRule = linkedMatch.captured(1).toUtf8();
    ruleText.remove(linkedRe);
    const QByteArray ruleCSource = ruleText.toUtf8();
    if (!ruleCSource.contains("@IDE_IF{HAS_SKIN}") ||
        !ruleCSource.contains("@IDE_IF{HAS_WORLD_OBJECTS}")) {
        if (error) *error = QStringLiteral("Missing Adventure conditional block in %1. ")
            .arg(ruleCPath) + QStringLiteral("No project files were changed.");
        return false;
    }

    // The IDE validates and serializes project DATA only. The declarations,
    // #includes, setup function, event callback and array structure all belong
    // to gameadventure.rulec/.ruleh, not the Qt program.
    QMap<QString, QString> fields;
    fields.insert(QStringLiteral("ITEM_COUNT"), QString::number(itemList.size()));
    fields.insert(QStringLiteral("NODE_COUNT"), QString::number(nodes.size()));
    fields.insert(QStringLiteral("NPC_COUNT"), QString::number(npcList.size()));
    fields.insert(QStringLiteral("HAS_WORLD_OBJECTS"),
        worldObjects.isEmpty() ? QStringLiteral("0") : QStringLiteral("1"));

    QString items;
    QTextStream itemOut(&items);
    if (itemList.isEmpty()) itemOut << "    {0,0,0,0,0},\n";
    for (const QJsonValue &v : itemList) {
        const QJsonObject o = v.toObject();
        itemOut << "    {" << quoted(o.value("name").toString().left(36)) << ","
                << clampInt(o,"pickupKind",0,255,0) << "u,"
                << clampInt(o,"icon",0,65535,65535) << "u,"
                << clampInt(o,"capacity",1,65535,1) << "u,"
                << clampInt(o,"initial",0,65535,0) << "u},\n";
    }
    fields.insert(QStringLiteral("ITEM_ROWS"), items.trimmed());

    QString nodeRows;
    QTextStream nodeOut(&nodeRows);
    if (nodes.isEmpty()) nodeOut << "    {0,0,{{0,0,-1,-1,-1,-1,-1}}},\n";
    QStringList storyFlags, linkedActions;
    int nodeIndex = 0;
    for (const QJsonValue &v : nodes) {
        const QJsonObject o = v.toObject();
        const QJsonArray choices = o.value("choices").toArray();
        nodeOut << "    {" << quoted(o.value("speaker").toString().left(36)) << ","
                << quoted(o.value("text").toString().left(512)) << ", {\n";
        for (int i=0; i<3; ++i) {
            const QJsonObject choice = i < choices.size() ? choices[i].toObject() : QJsonObject();
            int action = clampInt(choice,"action",-1,29999,-1);
            const QString targetId = choice.value("targetObjectId").toString();
            if (!targetId.isEmpty()) {
                const auto target = std::find_if(worldObjects.begin(),worldObjects.end(),
                    [&](const auto &item) { return item.id == targetId; });
                if (target == worldObjects.end()) {
                    if (error) *error = QStringLiteral("Dialogue choice refers to a deleted Game Object. Edit node %1.")
                        .arg(nodeIndex);
                    return false;
                }
                action = 30000 + nodeIndex*3 + i;
                const QString mode = choice.value("targetAction").toString("enable");
                const int modeNumber = mode == QStringLiteral("disable") ? 0
                    : mode == QStringLiteral("toggle") ? 2 : 1;
                QByteArray linkedCase;
                if (!GameHelperTemplates::renderFields(linkedActionRule,
                        {{QStringLiteral("EVENT_ID"), QString::number(action)},
                         {QStringLiteral("WORLD_SLOT"), QString::number(target->worldSlot)},
                         {QStringLiteral("ACTION_MODE"), QString::number(modeNumber)}},
                        ruleCPath + QStringLiteral(" / LINKED_ACTION"), &linkedCase, error))
                    return false;
                linkedActions.append(QString::fromUtf8(linkedCase));
            }
            nodeOut << "        {" << quoted(choice.value("text").toString().left(180)) << ","
                    << quoted(choice.value("reply").toString().left(150)) << ","
                    << clampInt(choice,"next",-1,nodes.size()-1,-1) << ","
                    << clampInt(choice,"requires",-1,itemList.size()-1,-1) << ","
                    << clampInt(choice,"give",-1,itemList.size()-1,-1) << ","
                    << clampInt(choice,"take",-1,itemList.size()-1,-1) << ","
                    << action << "},\n";
            const int flag = (choice.value("once").toBool(false) ? 1 : 0)
                           | (choice.value("completeNpc").toBool(false) ? 2 : 0);
            storyFlags.append(QString::number(flag));
        }
        nodeOut << "    }},\n";
        ++nodeIndex;
    }
    fields.insert(QStringLiteral("NODE_ROWS"), nodeRows.trimmed());
    fields.insert(QStringLiteral("CHOICE_FLAGS"),
        storyFlags.isEmpty() ? QStringLiteral("0") : storyFlags.join(QLatin1Char(',')));
    fields.insert(QStringLiteral("LINKED_ACTION_CASES"), linkedActions.join(QString()));

    QString npcRows;
    QTextStream npcOut(&npcRows);
    QStringList completedNodeIds, animations, animationFrameRows;
    int validNpcCount=0;
    for (const QJsonValue &v : npcList) {
        const QJsonObject npc = v.toObject();
        const QString id = npc.value("spriteId").toString();
        const auto it = std::find_if(sprites.begin(),sprites.end(),
            [&](const auto &s) { return s.id == id; });
        if (it == sprites.end()) {
            if (error) *error = QStringLiteral("Adventure NPC references a missing Sprite. Reopen Adventure Editor.");
            return false;
        }
        if (nodes.isEmpty()) {
            if (error) *error = QStringLiteral("NPC '%1' needs at least one dialogue node.").arg(it->name);
            return false;
        }
        if (it->symbol.isEmpty()) {
            if (error) *error = QStringLiteral("NPC '%1' has no exported sprite symbol.").arg(it->name);
            return false;
        }
        npcOut << "    {" << it->x << "," << it->y << ","
               << std::clamp(it->width,1,1024) << "u,"
               << std::clamp(it->height,1,1024) << "u,"
               << clampInt(npc,"radius",8,512,48) << "u,"
               << clampInt(npc,"node",0,nodes.size()-1,0) << "u},\n";
        completedNodeIds.append(npc.value("doneNode").toInt(-1)>=0
            ? QStringLiteral("%1u").arg(clampInt(npc,"doneNode",0,nodes.size()-1,0))
            : QStringLiteral("65535u"));

        const QJsonObject animation = npc.value("animation").toObject();
        const int cells = std::clamp(it->atlasFrames,1,256);
        auto first = [&](const char *key) { return clampInt(animation,key,0,cells-1,0); };
        auto count = [&](const char *key,int base) { return clampInt(animation,key,0,cells-base,0); };
        const int idleFirst = first("idleFirst"), talkFirst = first("talkFirst");
        QString frameNames[2];
        int frameCounts[2] = {count("idleCount",idleFirst),count("talkCount",talkFirst)};
        for (int state=0;state<2;++state) {
            const QJsonArray frames = animation.value(state ? "talkFrames" : "idleFrames").toArray();
            if (frames.isEmpty()) continue;
            const int offset = static_cast<int>(animationFrameRows.size());
            frameCounts[state] = static_cast<int>(std::min<qsizetype>(255,frames.size()));
            frameNames[state] = QStringLiteral("&npc_animation_frames[%1u]").arg(offset);
            for (int k=0;k<frameCounts[state];++k) {
                const QJsonObject frame = frames[k].toObject();
                animationFrameRows << QStringLiteral("    {%1u,%2u},")
                    .arg(std::clamp(frame.value("index").toInt(),0,cells-1))
                    .arg(std::clamp(frame.value("delay").toInt(6),1,255));
            }
        }
        animations.append(QStringLiteral("    {&%1,%2u,%3u,%4u,%5u,%6u,%7u,%8,%9,%10u},")
            .arg(it->symbol)
            .arg(idleFirst).arg(frameCounts[0])
            .arg(clampInt(animation,"idleSpeed",1,60,6))
            .arg(talkFirst).arg(frameCounts[1])
            .arg(clampInt(animation,"talkSpeed",1,60,5))
            .arg(frameNames[0].isEmpty() ? QStringLiteral("0") : frameNames[0])
            .arg(frameNames[1].isEmpty() ? QStringLiteral("0") : frameNames[1])
            .arg((it->flipX?4:0)|(it->flipY?8:0)));
        ++validNpcCount;
    }
    if (!validNpcCount) npcOut << "    {0,0,0,0,0,0},\n";
    fields.insert(QStringLiteral("NPC_ROWS"), npcRows.trimmed());
    fields.insert(QStringLiteral("NPC_COMPLETED_NODES"), completedNodeIds.isEmpty()
        ? QStringLiteral("65535u") : completedNodeIds.join(QLatin1Char(',')));
    fields.insert(QStringLiteral("NPC_FRAME_ROWS"), animationFrameRows.isEmpty()
        ? QStringLiteral("    {0u,1u},") : animationFrameRows.join(QLatin1Char('\n')));
    fields.insert(QStringLiteral("NPC_ANIMATION_ROWS"), animations.isEmpty()
        ? QStringLiteral("    {0},") : animations.join(QLatin1Char('\n')));

    const QJsonArray indices = payload.value("skinIndices").toArray();
    const QJsonArray flipValues = payload.value("skinFlips").toArray();
    QStringList skinCells, skinFlips;
    for (int i=0;i<9;++i) {
        skinCells << QString::number(std::clamp(i<indices.size()?indices[i].toInt(i):i,0,65535));
        skinFlips << QString::number(i<flipValues.size() ? (flipValues[i].toInt() & 12) : 0);
    }
    fields.insert(QStringLiteral("SKIN_CELLS"),skinCells.join(QLatin1Char(',')));
    fields.insert(QStringLiteral("SKIN_FLIPS"),skinFlips.join(QLatin1Char(',')));
    const QString skinId=payload.value("skinAtlasId").toString();
    const auto atlas=std::find_if(atlases.begin(),atlases.end(),
        [&](const auto &s) { return s.id == skinId; });
    QString rel;
    if (!skinId.isEmpty()) {
        if (atlas==atlases.end() || !QFileInfo::exists(atlas->path)) {
            if(error) *error = QStringLiteral("Dialogue Tile Atlas no longer exists. Choose it again.");
            return false;
        }
        rel=QDir(projectRoot).relativeFilePath(atlas->path);
        if (rel.startsWith("../") || QDir::isAbsolutePath(rel)) rel=QFileInfo(atlas->path).fileName();
    }
    fields.insert(QStringLiteral("HAS_SKIN"),
        rel.isEmpty() ? QStringLiteral("0") : QStringLiteral("1"));
    fields.insert(QStringLiteral("SKIN_PATH"), quoted(rel));

    QByteArray renderedC, renderedH;
    const QStringList requiredC = {
        QStringLiteral("ITEM_ROWS"),
        QStringLiteral("NODE_ROWS"),QStringLiteral("CHOICE_FLAGS"),QStringLiteral("NPC_ROWS"),
        QStringLiteral("NPC_COMPLETED_NODES"),QStringLiteral("NPC_FRAME_ROWS"),
        QStringLiteral("NPC_ANIMATION_ROWS"),QStringLiteral("SKIN_CELLS"),
        QStringLiteral("SKIN_FLIPS"),QStringLiteral("LINKED_ACTION_CASES"),
        QStringLiteral("SKIN_PATH")};
    const QStringList requiredH = {QStringLiteral("ITEM_COUNT"),QStringLiteral("NODE_COUNT"),
                                   QStringLiteral("NPC_COUNT")};
    // Both rules are read, checked and fully expanded before writing either file.
    if (!loadRule(rules,QStringLiteral(".rulec"),fields,requiredC,&renderedC,error, &ruleCSource)
        || !loadRule(rules,QStringLiteral(".ruleh"),fields,requiredH,&renderedH,error))
        return false;

    const QDir out(QDir(projectRoot).filePath("gamehelpers"));
    if (!QDir().mkpath(out.absolutePath())) {
        if (error) *error = QStringLiteral("Cannot create gamehelpers directory");
        return false;
    }
    const QString headerPath = out.filePath("gameadventure.h");
    const QString sourcePath = out.filePath("gameadventure.c");
    QFile previous(headerPath);
    const bool hadHeader = previous.exists();
    QByteArray oldHeader;
    if (hadHeader) {
        if (!previous.open(QIODevice::ReadOnly)) {
            if (error) *error = QStringLiteral("Cannot read existing %1 for rollback").arg(headerPath);
            return false;
        }
        oldHeader = previous.readAll();
    }
    if (!save(headerPath,renderedH,error)) return false;
    if (!save(sourcePath,renderedC,error)) {
        // Restore a prior header if the second write failed. Update Game
        // Project independently performs complete ZIP-backed rollback.
        if (hadHeader) {
            QString restoreError;
            if (!save(headerPath,oldHeader,&restoreError) && error)
                *error += QStringLiteral("; header restore failed: %1").arg(restoreError);
        } else if (!QFile::remove(headerPath) && error) {
            *error += QStringLiteral("; could not remove incomplete %1").arg(headerPath);
        }
        return false;
    }
    return true;
}
