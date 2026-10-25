#include "gameadventuregen.h"
#include "gamehelpertemplates.h"
#include "gametilemap.h"
#include <QDir>
#include <QDirIterator>
#include <QJsonDocument>
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
// Resolve story requirements by ITEM NAME, not per-world list index.
// Saved .sbgm files from other worlds are consulted as well, so a puzzle key
// required by an NPC elsewhere cannot become discardable in this world.
QSet<QString> requiredItemNames(const QJsonObject &payload, const QString &root)
{
    QSet<QString> required;
    const auto scan = [&](const QJsonObject &adventure) {
        const QJsonArray items = adventure.value(QStringLiteral("items")).toArray();
        const QJsonArray nodes = adventure.value(QStringLiteral("nodes")).toArray();
        for (const QJsonValue &nodeValue : nodes) {
            for (const QJsonValue &choiceValue : nodeValue.toObject().value(QStringLiteral("choices")).toArray()) {
                const QJsonObject choice = choiceValue.toObject();
                for (const char *key : {"requires", "take"}) {
                    const int index = choice.value(QLatin1String(key)).toInt(-1);
                    if (index < 0 || index >= items.size()) continue;
                    const QString name = items[index].toObject().value(QStringLiteral("name")).toString().trimmed().toCaseFolded();
                    if (!name.isEmpty()) required.insert(name);
                }
                for (const QJsonValue &offered : choice.value(QStringLiteral("exchange")).toObject()
                                                     .value(QStringLiteral("items")).toArray()) {
                    const int index=offered.toInt(-1);
                    if (index>=0 && index<items.size()) {
                        const QString name=items[index].toObject().value(QStringLiteral("name")).toString().trimmed().toCaseFolded();
                        if (!name.isEmpty()) required.insert(name);
                    }
                }
            }
        }
    };
    scan(payload);
    QDirIterator it(root, QStringList{QStringLiteral("*.sbgm")}, QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        const QString path = it.next();
        const QString relative = QDir(root).relativeFilePath(path);
        if (relative.startsWith(QStringLiteral("worlds/")) ||
            relative.startsWith(QStringLiteral("buildv1/")) ||
            relative.startsWith(QStringLiteral(".codergirl/"))) continue;
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly) || file.size() > 16*1024*1024) continue;
        const QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        if (doc.isObject()) scan(doc.object().value(QStringLiteral("adventure")).toObject());
    }
    return required;
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
    fields.insert(QStringLiteral("HAS_SHARED_PLAYER"),
        QFileInfo::exists(QDir(projectRoot).filePath(QStringLiteral("players/player.sbpi")))
            ? QStringLiteral("1") : QStringLiteral("0"));

    const QSet<QString> puzzleItems = requiredItemNames(payload, projectRoot);
    QString items;
    QTextStream itemOut(&items);
    if (itemList.isEmpty()) itemOut << "    {0},\n";
    for (const QJsonValue &v : itemList) {
        const QJsonObject o = v.toObject();
        itemOut << "    {" << quoted(o.value("name").toString().left(36)) << ","
                << clampInt(o,"pickupKind",0,255,0) << "u,"
                << clampInt(o,"icon",0,65535,65535) << "u,"
                << clampInt(o,"capacity",1,65535,1) << "u,"
                << clampInt(o,"initial",0,65535,0) << "u},\n";
    }
    fields.insert(QStringLiteral("ITEM_ROWS"), items.trimmed());

    QString styleRows;
    QTextStream styleOut(&styleRows);
    if (itemList.isEmpty()) styleOut << "    {{0u,0u,0u,0u},0u,0u,0u},\n";
    for (const QJsonValue &v : itemList) {
        const QJsonObject o = v.toObject();
        styleOut << "    {{";
        const QJsonArray iconCells = o.value("iconCells").toArray();
        for (int i=0; i<4; ++i) {
            if (i) styleOut << ",";
            styleOut << (iconCells.size()==4 ? std::clamp(iconCells[i].toInt(65535),0,65535)
                       : clampInt(o,"icon",0,65535,65535)) << "u";
        }
        const bool disposable = o.value("discardable").toBool(false)
            && !puzzleItems.contains(o.value("name").toString().trimmed().toCaseFolded());
        styleOut << "}," << (o.value("icon2x2").toBool(false) ? "1" : "0")
                 << "u," << (disposable ? "1" : "0") << "u,"
                 << (o.value("droppable").toBool(o.value("discardable").toBool(false)) ? "1" : "0") << "u},\n";
    }
    fields.insert(QStringLiteral("ITEM_STYLE_ROWS"),styleRows.trimmed());
    fields.insert(QStringLiteral("MAX_INVENTORY_SLOTS"),QString::number(clampInt(payload,"maxInventorySlots",0,64,0)));
    QString useRows;
    QTextStream useOut(&useRows);
    if (itemList.isEmpty()) useOut << "    {0,0,0},\n";
    for (const QJsonValue &v : itemList) {
        const QJsonObject o=v.toObject();
        const QString stat=o.value("useStat").toString().trimmed().left(64);
        const int delta=clampInt(o,"useDelta",-1000000,1000000,0);
        useOut << "    {" << (stat.isEmpty() || !delta ? QStringLiteral("0") : quoted(stat))
               << "," << delta << "," << (o.value("useConsume").toBool(true) ? "1u" : "0u") << "},\n";
    }
    fields.insert(QStringLiteral("ITEM_USE_ROWS"),useRows.trimmed());

    QStringList exchangeRows;
    QStringList wrongRepeatRows;
    QString nodeRows;
    QTextStream nodeOut(&nodeRows);
    if (nodes.isEmpty()) nodeOut << "    {0,0,{{0,0,-1,-1,-1,-1,-1,-1}}},\n";
    QStringList storyFlags, linkedActions, npcChoiceActionRows, closeGiftRows, thoughtChoiceFlags, spotlightActionRows;
    QStringList remoteNpcActionRows;
    /* NPC identity is world name plus stable sprite ID. Never use a displayed
       name or the other world's object-slot indices. */
    auto remoteNpc = [&](const QString &target, QString *world, int *slot) -> bool {
        if (!target.startsWith(QStringLiteral("@npc:"))) return false;
        const int delimiter=target.indexOf(QLatin1Char(':'),5);
        if (delimiter<0) return false;
        const QString wantedWorld=target.mid(5,delimiter-5);
        const QString wantedSprite=target.mid(delimiter+1);
        if (wantedWorld.isEmpty() || wantedSprite.isEmpty()) return false;
        QDirIterator it(projectRoot, QStringList{QStringLiteral("*.sbgm")},
                        QDir::Files, QDirIterator::NoIteratorFlags);
        while (it.hasNext()) {
            const QString source=it.next();
            if (sidboxTilemapWorldBaseName(source)!=wantedWorld) continue;
            QFile file(source);
            if (!file.open(QIODevice::ReadOnly) || file.size()>16*1024*1024) return false;
            const QJsonObject design=QJsonDocument::fromJson(file.readAll()).object();
            const QJsonArray npcs=design.value(QStringLiteral("adventure")).toObject()
                .value(QStringLiteral("npcs")).toArray();
            for (int n=0;n<npcs.size();++n) {
                if (npcs[n].toObject().value(QStringLiteral("spriteId")).toString()!=wantedSprite)
                    continue;
                *world=wantedWorld;
                *slot=n;
                return true;
            }
        }
        return false;
    };
    auto resolveNpcEffect = [&](const QString &spriteId, const QString &mode,
                                uint16_t eventId, QString *localIndex,
                                QString *localMode, const QString &where) -> bool {
        *localIndex=QStringLiteral("65535u");
        *localMode=QStringLiteral("0u");
        if (spriteId.isEmpty()) return true;
        const int action=mode==QStringLiteral("show") ? 1 : mode==QStringLiteral("toggle") ? 2 : 0;
        if (spriteId.startsWith(QStringLiteral("@npc:"))) {
            QString world;int slot=-1;
            if (!remoteNpc(spriteId,&world,&slot)) {
                if (error) *error=QStringLiteral("%1 targets an unavailable NPC '%2'. Save the destination world first.")
                    .arg(where,spriteId);
                return false;
            }
            remoteNpcActionRows << QStringLiteral("    {%1u,%2u,%3,%4u},")
                .arg(eventId).arg(slot).arg(quoted(world)).arg(action);
            return true;
        }
        for (int n=0; n<npcList.size(); ++n) {
            if (npcList[n].toObject().value(QStringLiteral("spriteId")).toString()!=spriteId) continue;
            *localIndex=QStringLiteral("%1u").arg(n);
            *localMode=QStringLiteral("%1u").arg(action);
            return true;
        }
        if (error) *error=QStringLiteral("%1 refers to a removed NPC Sprite '%2'.")
            .arg(where,spriteId);
        return false;
    };
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
            const int spotlightMode = choice.value("spotlightAction").toInt(3);
            if (spotlightMode >= 0 && spotlightMode <= 2 &&
                !choice.value("text").toString().trimmed().isEmpty())
                spotlightActionRows << QStringLiteral("    {%1u,%2u},")
                    .arg(nodeIndex*3+i).arg(spotlightMode);
            // Per-choice bit 0: show with NEXT node (legacy); bit 1: show
            // with THIS node while the answer is selected. The editor keeps
            // these mutually exclusive, and old worlds need no migration.
            const bool thoughtNext=choice.value("thoughtBubble").toBool(false);
            const bool thoughtThis=!thoughtNext && choice.value("thoughtBubbleThis").toBool(false);
            thoughtChoiceFlags << QStringLiteral("%1u").arg(thoughtNext ? 1 : (thoughtThis ? 2 : 0));
            nodeOut << "        {" << quoted(choice.value("text").toString().left(180)) << ","
                    << quoted(choice.value("reply").toString().left(150)) << ","
                    << clampInt(choice,"next",-1,nodes.size()-1,-1) << ","
                    << clampInt(choice,"missingNext",-1,nodes.size()-1,-1) << ","
                    << clampInt(choice,"requires",-1,itemList.size()-1,-1) << ","
                    << clampInt(choice,"give",-1,itemList.size()-1,-1) << ","
                    << clampInt(choice,"take",-1,itemList.size()-1,-1) << ","
                    << action << "},\n";
            /* Resolve both NPC appearance targets by stable placed Sprite ID.
             * Do not bake table-row IDs into project JSON: rows can be moved. */
            QStringList npcIndices, npcModes;
            for (int effect = 1; effect <= 2; ++effect) {
                const QString prefix = QStringLiteral("npcAction%1").arg(effect);
                const QString spriteId = choice.value(prefix + QStringLiteral("SpriteId")).toString();
                if (spriteId.isEmpty()) {
                    npcIndices << QStringLiteral("65535u");
                    npcModes << QStringLiteral("0u");
                    continue;
                }
                QString index,modeValue;
                if (!resolveNpcEffect(spriteId,
                        choice.value(prefix + QStringLiteral("Mode")).toString("hide"),
                        (uint16_t)(nodeIndex*3+i), &index, &modeValue,
                        QStringLiteral("Dialogue %1, answer %2").arg(nodeIndex).arg(i+1)))
                    return false;
                npcIndices << index;
                npcModes << modeValue;
            }
            if (npcIndices[0] != QStringLiteral("65535u") || npcIndices[1] != QStringLiteral("65535u"))
                npcChoiceActionRows << QStringLiteral("    {%1u,%2,%3,%4,%5},")
                    .arg(nodeIndex * 3 + i).arg(npcIndices[0]).arg(npcIndices[1])
                    .arg(npcModes[0]).arg(npcModes[1]);
            const QJsonObject exchange=choice.value("exchange").toObject();
            const QJsonArray exchangeItems=exchange.value("items").toArray();
            QStringList requested;
            QSet<int> seen;
            for (const QJsonValue &v : exchangeItems) {
                const int idx=v.toInt(-1);
                if (idx<0 || idx>=itemList.size() || seen.contains(idx)) continue;
                seen.insert(idx);
                requested.append(QString::number(idx));
                if (requested.size()>=4) break;
            }
            const bool active=exchange.value("enabled").toBool(false) && !requested.isEmpty();
            const int wanted=active ? requested.size() : 0;
            while (requested.size()<4) requested << QStringLiteral("-1");
            // Alternate reactions can have independent custom event IDs.
            auto exAction = [&](const char *key, const char *targetKey,
                                const char *modeKey, int offset) {
                int event=clampInt(exchange,key,-1,29999,-1);
                const QString objectId=exchange.value(QLatin1String(targetKey)).toString();
                if (objectId.isEmpty()) return event;
                const auto target=std::find_if(worldObjects.begin(),worldObjects.end(),
                    [&](const auto &item){ return item.id==objectId; });
                if (target==worldObjects.end()) {
                    if(error) *error=QStringLiteral("GIVE exchange references a deleted Game Object in dialogue %1.").arg(nodeIndex);
                    return -2;
                }
                event=31000 + nodeIndex*6 + i*2 + offset;
                const QString mode=exchange.value(QLatin1String(modeKey)).toString("enable");
                const int modeNumber=mode=="disable"?0:mode=="toggle"?2:1;
                QByteArray linked;
                if (!GameHelperTemplates::renderFields(linkedActionRule,
                    {{QStringLiteral("EVENT_ID"),QString::number(event)},
                     {QStringLiteral("WORLD_SLOT"),QString::number(target->worldSlot)},
                     {QStringLiteral("ACTION_MODE"),QString::number(modeNumber)}},
                    ruleCPath+QStringLiteral(" / EXCHANGE_ACTION"),&linked,error))
                    return -2;
                linkedActions.append(QString::fromUtf8(linked));
                return event;
            };
            const int wrongAction=active ? exAction("wrongAction","wrongTargetObjectId","wrongTargetAction",0) : -1;
            /* Partial progress is intentionally silent: do not expose
               undiscovered quest requirements through a hint node/event. */
            const int partialAction=-1;
            if(wrongAction==-2)return false;
            const bool repeatEnabled=active && exchange.value("wrongRepeatEnabled").toBool(false);
            const int tracked=clampInt(exchange,"wrongRepeatItem",-1,itemList.size()-1,-1);
            if (repeatEnabled && tracked>=0) {
                /* One tracked item per exchange; only wrong offers reach the
                 * repeat handler (required items retain their quest behaviour). */
                int reveal=clampInt(exchange,"wrongRepeatAction",-1,29999,-1);
                const QString objId=exchange.value("wrongRepeatTargetObjectId").toString();
                if (!objId.isEmpty()) {
                    const auto obj=std::find_if(worldObjects.begin(),worldObjects.end(),
                        [&](const auto &entry) {return entry.id==objId;});
                    if (obj==worldObjects.end()) {
                        if(error) *error=QStringLiteral("Repeated wrong-item clue refers to a deleted Game Object in dialogue %1.").arg(nodeIndex);
                        return false;
                    }
                    /* Keep auto IDs separate from ordinary custom IDs. They
                     * exceed INT16_MAX, so the runtime stores them as uint16_t. */
                    reveal=33000 + nodeIndex*3 + i;
                    const QString mode=exchange.value("wrongRepeatTargetAction").toString("enable");
                    const int modeNumber=mode=="disable"?0:mode=="toggle"?2:1;
                    QByteArray linked;
                    if (!GameHelperTemplates::renderFields(linkedActionRule,
                        {{QStringLiteral("EVENT_ID"),QString::number(reveal)},
                         {QStringLiteral("WORLD_SLOT"),QString::number(obj->worldSlot)},
                         {QStringLiteral("ACTION_MODE"),QString::number(modeNumber)}},
                        ruleCPath+QStringLiteral(" / WRONG_REPEAT_ACTION"),&linked,error))
                        return false;
                    linkedActions.append(QString::fromUtf8(linked));
                }
                const int index=nodeIndex*3+i;
                wrongRepeatRows << QStringLiteral("    {%1u,%2,{%3,%4,%5,%6},%7},")
                    .arg(index).arg(tracked)
                    .arg(clampInt(exchange,"wrongRepeatFirst",-1,nodes.size()-1,-1))
                    .arg(clampInt(exchange,"wrongRepeatSecond",-1,nodes.size()-1,-1))
                    .arg(clampInt(exchange,"wrongRepeatThird",-1,nodes.size()-1,-1))
                    .arg(clampInt(exchange,"wrongRepeatLater",-1,nodes.size()-1,-1))
                    .arg(reveal);
            }
            exchangeRows << QStringLiteral("    {{%1},%2,%3,%4,%5,%6u,%7u,%8u,%9u},")
                .arg(requested.join(','))
                .arg(active ? clampInt(exchange,"wrongNext",-1,nodes.size()-1,-1) : -1)
                .arg(-1)
                .arg(active ? wrongAction : -1).arg(active ? partialAction : -1)
                .arg(wanted).arg(exchange.value("logic").toString()=="any"?1:0)
                .arg(exchange.value("incremental").toBool(false)?1:0)
                .arg(exchange.value("consume").toBool(true)?1:0);
            const int flag = (choice.value("once").toBool(false) ? 1 : 0)
                           | (choice.value("completeNpc").toBool(false) ? 2 : 0);
            storyFlags.append(QString::number(flag));
        }
        nodeOut << "    }},\n";
        /* ON-CLOSE actions have a distinct ID range following the three
         * ordinary answer IDs for all nodes. A node with no answers has no
         * answer to select, but its FIRE2-close action still runs. */
        QStringList closeIndices,closeModes;
        for (int effect=1; effect<=2; ++effect) {
            const QString prefix=QStringLiteral("closeNpcAction%1").arg(effect);
            QString spriteId=o.value(prefix+QStringLiteral("SpriteId")).toString();
            QString mode=o.value(prefix+QStringLiteral("Mode")).toString("hide");
            if (spriteId.isEmpty()) {
                bool hasAnswer=false;
                for (const QJsonValue &v: choices)
                    if (!v.toObject().value(QStringLiteral("text")).toString().trimmed().isEmpty())
                        {hasAnswer=true;break;}
                if (!hasAnswer) for (const QJsonValue &v: choices) {
                    const QJsonObject choice=v.toObject();
                    spriteId=choice.value(QStringLiteral("npcAction%1SpriteId").arg(effect)).toString();
                    if (spriteId.isEmpty()) continue;
                    mode=choice.value(QStringLiteral("npcAction%1Mode").arg(effect)).toString("hide");
                    break;
                }
            }
            if (spriteId.isEmpty()) {
                closeIndices << QStringLiteral("65535u");
                closeModes << QStringLiteral("0u");
                continue;
            }
            QString index,modeValue;
            if (!resolveNpcEffect(spriteId,mode,(uint16_t)(nodes.size()*3+nodeIndex),
                                  &index,&modeValue,
                                  QStringLiteral("Dialogue %1 on-close").arg(nodeIndex))) return false;
            closeIndices << index;
            closeModes << modeValue;
        }
        const int closeSpotlight = o.value("closeSpotlightAction").toInt(3);
        if (closeSpotlight >= 0 && closeSpotlight <= 2)
            spotlightActionRows << QStringLiteral("    {%1u,%2u},")
                .arg(nodes.size()*3+nodeIndex).arg(closeSpotlight);
        /* A terminal dialogue may hand over inventory before hiding the NPC.
         * Legacy versions placed rewards on an empty answer, which never ran.
         * Only auto-migrate that gift when NO answer is selectable. */
        bool hasAnswer=false;
        for (const QJsonValue &v: choices)
            if (!v.toObject().value(QStringLiteral("text")).toString().trimmed().isEmpty())
                {hasAnswer=true;break;}
        int closeGift=o.value(QStringLiteral("closeGiveItem")).toInt(-1);
        if (!hasAnswer && closeGift<0) for (const QJsonValue &v: choices) {
            const int legacyGift=v.toObject().value(QStringLiteral("give")).toInt(-1);
            if (legacyGift>=0 && legacyGift<itemList.size()) {closeGift=legacyGift;break;}
        }
        if (!hasAnswer && closeGift>=0 && closeGift<itemList.size())
            closeGiftRows << QStringLiteral("    {%1u,%2u},").arg(nodeIndex).arg(closeGift);
        if (closeIndices[0]!=QStringLiteral("65535u") || closeIndices[1]!=QStringLiteral("65535u"))
            npcChoiceActionRows << QStringLiteral("    {%1u,%2,%3,%4,%5},")
                .arg(nodes.size()*3+nodeIndex).arg(closeIndices[0]).arg(closeIndices[1])
                .arg(closeModes[0]).arg(closeModes[1]);
        ++nodeIndex;
    }
    fields.insert(QStringLiteral("NODE_ROWS"), nodeRows.trimmed());
    fields.insert(QStringLiteral("NPC_CHOICE_ACTION_ROWS"),npcChoiceActionRows.isEmpty()
        ? QStringLiteral("    {0u,65535u,65535u,0u,0u},")
        : npcChoiceActionRows.join(QLatin1Char('\n')));
    fields.insert(QStringLiteral("NPC_CHOICE_ACTION_COUNT"),QString::number(npcChoiceActionRows.size()));
    fields.insert(QStringLiteral("REMOTE_NPC_ACTION_ROWS"),remoteNpcActionRows.isEmpty()
        ? QStringLiteral("    {0u,0u,0,0u},") : remoteNpcActionRows.join(QLatin1Char('\n')));
    fields.insert(QStringLiteral("REMOTE_NPC_ACTION_COUNT"),QString::number(remoteNpcActionRows.size()));
    fields.insert(QStringLiteral("SPOTLIGHT_ACTION_ROWS"), spotlightActionRows.isEmpty()
        ? QStringLiteral("    {0u,0u},") : spotlightActionRows.join(QLatin1Char('\n')));
    fields.insert(QStringLiteral("SPOTLIGHT_ACTION_COUNT"),QString::number(spotlightActionRows.size()));
    fields.insert(QStringLiteral("CLOSE_GIFT_ROWS"),closeGiftRows.isEmpty()
        ? QStringLiteral("    {0u,0u},") : closeGiftRows.join(QLatin1Char('\n')));
    fields.insert(QStringLiteral("CLOSE_GIFT_COUNT"),QString::number(closeGiftRows.size()));
    fields.insert(QStringLiteral("WRONG_REPEAT_ROWS"),wrongRepeatRows.isEmpty()
        ? QStringLiteral("    {0u,-1,{-1,-1,-1,-1},-1},")
        : wrongRepeatRows.join(QLatin1Char('\n')));
    fields.insert(QStringLiteral("WRONG_REPEAT_COUNT"),QString::number(wrongRepeatRows.size()));
    fields.insert(QStringLiteral("EXCHANGE_ROWS"),exchangeRows.isEmpty()
        ? QStringLiteral("    {{-1,-1,-1,-1},-1,-1,-1,-1,0u,0u,0u,0u},")
        : exchangeRows.join(QLatin1Char('\n')));
    fields.insert(QStringLiteral("CHOICE_FLAGS"),
        storyFlags.isEmpty() ? QStringLiteral("0") : storyFlags.join(QLatin1Char(',')));
    fields.insert(QStringLiteral("LINKED_ACTION_CASES"), linkedActions.join(QString()));

    QString npcRows;
    QTextStream npcOut(&npcRows);
    QStringList completedNodeIds, animations, animationFrameRows, initialVisibility;
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
        initialVisibility.append(npc.value("initiallyVisible").toBool(true) ? QStringLiteral("1u") : QStringLiteral("0u"));
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
    fields.insert(QStringLiteral("NPC_VISIBILITY_ROWS"), initialVisibility.isEmpty()
        ? QStringLiteral("1u") : initialVisibility.join(QLatin1Char(',')));
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
    fields.insert(QStringLiteral("THOUGHT_CHOICE_FLAGS"),
                  thoughtChoiceFlags.isEmpty()?QStringLiteral("0u"):thoughtChoiceFlags.join(QLatin1Char(',')));
    const QJsonArray thoughtIndices=payload.value("thoughtSkinIndices").toArray();
    const QJsonArray thoughtFlips=payload.value("thoughtSkinFlips").toArray();
    QStringList thoughtCells, thoughtFlipFlags;
    for(int i=0;i<9;++i){
        thoughtCells << QString::number(std::clamp(i<thoughtIndices.size()?thoughtIndices[i].toInt(i):
            (i<indices.size()?indices[i].toInt(i):i),0,65535));
        thoughtFlipFlags << QString::number(i<thoughtFlips.size()?thoughtFlips[i].toInt()&12:0);
    }
    fields.insert(QStringLiteral("THOUGHT_SKIN_CELLS"),thoughtCells.join(QLatin1Char(',')));
    fields.insert(QStringLiteral("THOUGHT_SKIN_FLIPS"),thoughtFlipFlags.join(QLatin1Char(',')));
    fields.insert(QStringLiteral("SKIN_CELLS"),skinCells.join(QLatin1Char(',')));
    fields.insert(QStringLiteral("SKIN_FLIPS"),skinFlips.join(QLatin1Char(',')));
    // Every world must configure the ONE shared adventure renderer after its
    // own story is activated. The common adventureruntime.c must not bake in
    // the appearance and dialogue position of whichever .sbgm updated last.
    // These are design DATA; gameadventure.rulec owns all generated C calls.
    const struct { const char *field; const char *json; int lo, hi, fallback; } appearance[] = {
        {"THOUGHT_X", "thoughtX", 0, 479, 20},
        {"THOUGHT_Y", "thoughtY", 0, 319, 12},
        {"THOUGHT_WIDTH", "thoughtWidth", 96, 480, 240},
        {"THOUGHT_HEIGHT", "thoughtHeight", 40, 320, 64},
        {"SKIN_TILE_SIZE", "tileSize", 4, 32, 8},
        {"FRAMES_PER_CHAR", "framesPerChar", 1, 30, 2},
        {"TEXT_COLOUR_INDEX", "textColourIndex", 0, 255, 15},
        {"TEXT_OUTLINE_ENABLED", "textOutline", 0, 1, 0},
        {"OUTLINE_COLOUR_INDEX", "outlineColourIndex", 0, 255, 1},
        {"DIALOG_X", "dialogX", 0, 479, 20},
        {"DIALOG_Y", "dialogY", 0, 319, 148},
        {"DIALOG_WIDTH", "dialogWidth", 128, 480, 440},
        {"DIALOG_HEIGHT", "dialogHeight", 96, 320, 96},
        {"DIALOG_PADDING", "dialogPadding", 0, 8, 8},
        {"DIALOG_FONT_SCALE_X", "dialogFontScaleX", 1, 8, 1},
        {"DIALOG_FONT_SCALE_Y", "dialogFontScaleY", 1, 8, 2},
        {"THOUGHT_FONT_SCALE_X", "thoughtFontScaleX", 1, 8, 1},
        {"THOUGHT_FONT_SCALE_Y", "thoughtFontScaleY", 1, 8, 2},
        {"THOUGHT_ABOVE", "thoughtAboveDialog", 0, 1, 1}
    };
    for (const auto &value : appearance) {
        const int number = QByteArray(value.json) == "textOutline"
            ? (payload.value(QStringLiteral("textOutline")).toBool(false) ? 1 : 0)
            : clampInt(payload, value.json, value.lo, value.hi, value.fallback);
        fields.insert(QLatin1String(value.field), QString::number(number));
    }
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
    // Individual inventory items may draw their icon from any PPB registered
    // in THIS world. Dialogue box skins remain completely independent.
    QString iconSetup;
    QTextStream iconOut(&iconSetup);
    for(int i=0;i<itemList.size();++i) {
        const QJsonObject item=itemList.at(i).toObject();
        // Portable collectables already have a project-relative PPB filename.
        // They must not depend on a destination world's local resource UUID.
        const QString portable=item.value(QStringLiteral("iconPpbPath")).toString();
        if(!portable.isEmpty()) {
            const QString absolute=QFileInfo(portable).isAbsolute() ? portable
                : QDir(projectRoot).filePath(portable);
            const QString relative=QDir::cleanPath(QDir(projectRoot).relativeFilePath(absolute));
            if(relative==QStringLiteral("..") || relative.startsWith(QStringLiteral("../")) ||
               QDir::isAbsolutePath(relative) || !QFileInfo::exists(absolute)) {
                if(error)*error=QStringLiteral("Persistent inventory item '%1' needs PPB '%2' inside this project. Check the source world artwork.")
                    .arg(item.value(QStringLiteral("name")).toString(),portable);
                return false;
            }
            QFile image(absolute);
            if(!image.open(QIODevice::ReadOnly)) {
                if(error)*error=QStringLiteral("Cannot read inventory PPB: %1").arg(absolute);
                return false;
            }
            const QByteArray hdr=image.read(16);
            if(hdr.size()!=16 || QFileInfo(absolute).size()<1040) {
                if(error)*error=QStringLiteral("Invalid inventory PPB header: %1").arg(absolute);
                return false;
            }
            const auto byte=[&hdr](int n){return static_cast<unsigned char>(hdr.at(n));};
            const int width=(byte(1)<<8)|byte(2),height=(byte(3)<<8)|byte(4);
            const quint32 payload=(quint32(byte(5))<<24)|(quint32(byte(6))<<16)|
                                  (quint32(byte(7))<<8)|quint32(byte(8));
            if(!width || !height || quint32(width)*quint32(height)!=payload ||
               payload>4u*1024u*1024u || image.size()!=1040+qint64(payload)) {
                if(error)*error=QStringLiteral("Invalid dimensions or length for inventory PPB: %1").arg(absolute);
                return false;
            }
            const int size=std::clamp(item.value(QStringLiteral("iconTileSize")).toInt(8),4,64);
            iconOut << "    { uint16_t icon_w=0,icon_h=0; const uint8_t *pixels=gameassets_find_ppb("
                    << quoted(relative) << ",&icon_w,&icon_h);\n"
                    << "      if (pixels && icon_w==" << width << "u && icon_h==" << height
                    << "u) game_adventure_item_atlas(" << i << "u,pixels,icon_w,icon_h," << size << "u);\n"
                    << "      else game_adventure_item_atlas_file(" << i << "u,"
                    << quoted(relative) << "," << width << "u," << height << "u," << size << "u); }\n";
            continue;
        }
        const QString chosen=item.value(QStringLiteral("iconAtlasId")).toString();
        if(chosen.isEmpty())continue; // legacy item uses the dialogue skin
        const auto iconAtlas=std::find_if(atlases.begin(),atlases.end(),
            [&](const auto &resource){return resource.id==chosen;});
        if(iconAtlas==atlases.end() || !QFileInfo::exists(iconAtlas->path)) {
            if(error)*error=QStringLiteral("Inventory item '%1' needs its Icon Atlas registered in this world. Reopen Inventory Items and choose an atlas.")
                .arg(item.value(QStringLiteral("name")).toString());
            return false;
        }
        QString relative=QDir(projectRoot).relativeFilePath(iconAtlas->path);
        if(relative.startsWith("../") || QDir::isAbsolutePath(relative))
            relative=QFileInfo(iconAtlas->path).fileName();
        iconOut << "    { uint16_t icon_w=0,icon_h=0; const uint8_t *pixels=gameassets_find_ppb("
                << quoted(relative) << ",&icon_w,&icon_h);\n"
                << "      game_adventure_item_atlas(" << i << "u,pixels,icon_w,icon_h,"
                << std::clamp(item.value(QStringLiteral("iconTileSize")).toInt(8),4,64)
                << "u); }\n";
    }
    fields.insert(QStringLiteral("ITEM_ICON_SETUP"),iconSetup);
    fields.insert(QStringLiteral("HAS_SKIN"),
        rel.isEmpty() ? QStringLiteral("0") : QStringLiteral("1"));
    fields.insert(QStringLiteral("SKIN_PATH"), quoted(rel));

    QByteArray renderedC, renderedH;
    const QStringList requiredC = {
        QStringLiteral("ITEM_ICON_SETUP"),
        QStringLiteral("ITEM_ROWS"),QStringLiteral("ITEM_STYLE_ROWS"),
        QStringLiteral("MAX_INVENTORY_SLOTS"),
        QStringLiteral("ITEM_USE_ROWS"),QStringLiteral("EXCHANGE_ROWS"),
        QStringLiteral("WRONG_REPEAT_ROWS"),QStringLiteral("WRONG_REPEAT_COUNT"),
        QStringLiteral("NODE_ROWS"),QStringLiteral("CHOICE_FLAGS"),QStringLiteral("NPC_ROWS"),
        QStringLiteral("NPC_CHOICE_ACTION_ROWS"),QStringLiteral("NPC_CHOICE_ACTION_COUNT"),
        QStringLiteral("REMOTE_NPC_ACTION_ROWS"),QStringLiteral("REMOTE_NPC_ACTION_COUNT"),
        QStringLiteral("CLOSE_GIFT_ROWS"),QStringLiteral("CLOSE_GIFT_COUNT"),
        QStringLiteral("SPOTLIGHT_ACTION_ROWS"),QStringLiteral("SPOTLIGHT_ACTION_COUNT"),
        QStringLiteral("NPC_VISIBILITY_ROWS"),
        QStringLiteral("NPC_COMPLETED_NODES"),QStringLiteral("NPC_FRAME_ROWS"),
        QStringLiteral("NPC_ANIMATION_ROWS"),QStringLiteral("THOUGHT_CHOICE_FLAGS"),
        QStringLiteral("THOUGHT_SKIN_CELLS"),QStringLiteral("THOUGHT_SKIN_FLIPS"),
        QStringLiteral("THOUGHT_X"),QStringLiteral("THOUGHT_Y"),
        QStringLiteral("THOUGHT_WIDTH"),QStringLiteral("THOUGHT_HEIGHT"),QStringLiteral("SKIN_CELLS"),
        QStringLiteral("SKIN_FLIPS"),QStringLiteral("LINKED_ACTION_CASES"),
        QStringLiteral("SKIN_PATH"),QStringLiteral("SKIN_TILE_SIZE"),
        QStringLiteral("FRAMES_PER_CHAR"),QStringLiteral("TEXT_COLOUR_INDEX"),
        QStringLiteral("TEXT_OUTLINE_ENABLED"),QStringLiteral("OUTLINE_COLOUR_INDEX"),
        QStringLiteral("DIALOG_X"),QStringLiteral("DIALOG_Y"),
        QStringLiteral("DIALOG_WIDTH"),QStringLiteral("DIALOG_HEIGHT"),
        QStringLiteral("DIALOG_PADDING")};
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
