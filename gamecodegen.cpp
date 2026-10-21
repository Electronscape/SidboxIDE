#include "gamecodegen.h"
#include "gamehelpertemplates.h"
#include "ppbcodec.h"

#include <QByteArray>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QHash>
#include <QMap>
#include <QRegularExpression>
#include <QSaveFile>
#include <QSet>
#include <QTextStream>
#include <QtEndian>
#include <algorithm>
#include <initializer_list>
#include <QtGlobal>

namespace SidboxGameCodeGen {
namespace {
struct Bitmap {
    QString path;
    QString sdPath;
    QByteArray pixels;
    int width = 0;
    int height = 0;
    QString symbol;
};
struct Sprite {
    Asset asset;
    QString group;
    bool array = false;
    int index = 0;
    int bitmap = -1;
    int cellW = 0;
    int cellH = 0;
    bool background = false;
};
struct Group {
    QString name;
    QString symbol;
    bool array = false;
    bool background = false;
    int count = 0;
    QVector<int> sprites;
};
struct DirectBackground {
    Asset asset;
    QString symbol;
    int bitmap = -1;
    bool convert = false;
};
struct Sound {
    Asset asset;
    QString id;
    QString sdPath;
    int bits = 8;
};
struct Music {
    Asset asset;
    QString id;
    QString sdPath;
};

bool isIdentifier(const QString &s)
{
    static const QRegularExpression rx(QStringLiteral("^[A-Za-z_][A-Za-z_0-9]*$"));
    return rx.match(s).hasMatch();
}
QString cString(const QString &value)
{
    const QByteArray utf8 = QDir::fromNativeSeparators(value).toUtf8();
    QString result = QStringLiteral("\"");
    for (const uchar c : utf8) {
        if (c == '\\' || c == '"') { result += QLatin1Char('\\'); result += QChar(c); }
        else if (c >= 32 && c <= 126) result += QChar(c);
        else result += QStringLiteral("\\%1").arg(unsigned(c), 3, 8, QLatin1Char('0'));
    }
    return result + QLatin1Char('"');
}
QString uniqueIdentifier(const QString &requested, const QString &label, QSet<QString> &used,
                         Result &result)
{
    QString id = SidboxPpb::identifier(requested).toLower();
    // Generated helper functions start with 'draw' or 'gameassets_', and never
    // expose implementation identifiers beginning with double underscores.
    if (!isIdentifier(id)) { result.error = QStringLiteral("Invalid %1 name: %2").arg(label, requested); return {}; }
    if (used.contains(id)) {
        result.error = QStringLiteral("Duplicate %1 C identifier '%2'. Rename one of the assets.").arg(label, id);
        return {};
    }
    used.insert(id);
    if (id != requested) result.warnings.append(QStringLiteral("'%1' will use C identifier '%2'.").arg(requested, id));
    return id;
}
QString sdLocation(const QString &absolutePath, const QString &designDirectory, Result &result)
{
    const QString relative = QDir(designDirectory).relativeFilePath(absolutePath);
    if (relative.startsWith(QStringLiteral("../")) || QDir::isAbsolutePath(relative)) {
        result.warnings.append(QStringLiteral("'%1' is outside the project. Edit the generated SD path or copy it onto the card.")
                               .arg(absolutePath));
        return QFileInfo(absolutePath).fileName();
    }
    return QDir::fromNativeSeparators(relative);
}
bool readPpb(const QString &path, Bitmap *bitmap, QString *error)
{
    SidboxPpb::Picture picture;
    if (!SidboxPpb::read(path, &picture, error)) return false;
    bitmap->width = picture.indexed.width();
    bitmap->height = picture.indexed.height();
    const qint64 count = qint64(bitmap->width) * bitmap->height;
    if (count > 16 * 1024 * 1024) { *error = QStringLiteral("PPB exceeds 16 MiB: %1").arg(path); return false; }
    QFile f(path);
    if (!f.open(QIODevice::ReadOnly) || !f.seek(1040)) {
        *error = QStringLiteral("Cannot read indexed pixels: %1").arg(path); return false;
    }
    bitmap->pixels = f.read(count);
    if (bitmap->pixels.size() != count) {
        *error = QStringLiteral("Truncated indexed pixels: %1").arg(path); return false;
    }
    return true;
}
bool readPalette(const QString &path, bool background, QVector<quint32> *out, QString *error)
{
    if (path.isEmpty()) return true;
    QFile f(path);
    if (!f.open(QIODevice::ReadOnly)) {
        *error = QStringLiteral("Cannot open palette: %1").arg(path); return false;
    }
    const QByteArray bytes = f.read(2048);
    int start = 0;
    if (QFileInfo(path).suffix().compare(QStringLiteral("ppb"), Qt::CaseInsensitive) == 0) {
        if (bytes.size() < 1040) {
            *error = QStringLiteral("Truncated PPB palette: %1").arg(path); return false;
        }
        start = 16; // PPB contains a single 256-entry CLUT.
    } else if (f.size() == 1024 || f.size() == 2048) {
        start = background && f.size() == 2048 ? 1024 : 0;
    } else {
        *error = QStringLiteral("Expected a 1024/2048-byte .pal or native PPB palette: %1").arg(path);
        return false;
    }
    for (int i = 0; i < 256; ++i) {
        quint32 colour = qFromLittleEndian<quint32>(
            reinterpret_cast<const uchar *>(bytes.constData() + start + 4*i));
        // The SIDBOX background plane has no transparency, including colour 0.
        // Keep the source .pal/.ppb unchanged; only normalise generated C data.
        if (background) colour |= 0xFF000000u;
        out->append(colour);
    }
    return true;
}
bool writeAtomic(const QString &path, const QString &contents, QString *error)
{
    QSaveFile out(path);
    const QByteArray data = contents.toUtf8();
    if (!out.open(QIODevice::WriteOnly) || out.write(data) != data.size() || !out.commit()) {
        *error = QStringLiteral("Unable to write %1: %2").arg(path, out.errorString());
        return false;
    }
    return true;
}
}

Result generate(const Request &request)
{
    Result result;
    if (request.outputDirectory.isEmpty() || request.designDirectory.isEmpty()) {
        result.error = QStringLiteral("Save the Game Designer document before generating code.");
        return result;
    }
    QSet<QString> symbols;
    QVector<Sprite> sprites;
    QVector<Group> groups;
    QHash<QString,int> groupIndex;
    QVector<Bitmap> bitmaps;
    QHash<QString,int> bitmapIndex;
    QVector<Sound> sounds;
    QVector<Music> music;
    QVector<DirectBackground> directBackgrounds;
    bool selectedTileAtlasLoaded = false;
    QVector<quint32> frontClut, backClut;
    if (!readPalette(request.foregroundPalette, false, &frontClut, &result.error)
        || !readPalette(request.backgroundPalette, true, &backClut, &result.error)) return result;

    static const QRegularExpression arrayName(QStringLiteral("^([A-Za-z_][A-Za-z_0-9]*)\\[([0-9]+)\\]$"));
    for (const Asset &a : request.assets) {
        if (a.kind == QStringLiteral("palette")) continue;
        if (a.kind == QStringLiteral("sprite") || a.kind == QStringLiteral("background")
            || a.kind == QStringLiteral("tileatlas")) {
            const bool tileAtlas = a.kind == QStringLiteral("tileatlas");
            if (a.absolutePath.isEmpty()) {
                result.warnings.append(QStringLiteral("Empty image resource '%1' omitted (no PPB yet).").arg(a.name));
                continue;
            }
            if (QFileInfo(a.absolutePath).suffix().compare(QStringLiteral("ppb"), Qt::CaseInsensitive) != 0) {
                result.error = QStringLiteral("Convert '%1' to PPB before generating V1 code.").arg(a.absolutePath);
                return result;
            }
            auto match = arrayName.match(a.name.trimmed());
            const bool array = match.hasMatch();
            QString base = array ? match.captured(1) : a.name.trimmed();
            if (base.isEmpty()) base = QFileInfo(a.absolutePath).completeBaseName();
            const int element = array ? match.captured(2).toInt() : 0;
            if (array && (element < 0 || element > 2047)) {
                result.error = QStringLiteral("Array element out of range (0..2047): %1").arg(a.name);
                return result;
            }
            const QString groupKey = base.toLower();
            const bool background = a.kind == QStringLiteral("background")
                || a.plane == QStringLiteral("background");
            const bool direct = a.kind == QStringLiteral("background")
                && a.backgroundMode != QStringLiteral("sprite");
            if (direct) {
                if (!request.dualPlane) {
                    result.error = QStringLiteral("Direct background '%1' requires Dual-plane mode.").arg(a.name);
                    return result;
                }
                if (array || !directBackgrounds.isEmpty()) {
                    result.error = QStringLiteral("Only one standalone direct background is supported per game; no arrays.");
                    return result;
                }
                if (a.scale != 100 || a.x != 0 || a.y != 0) {
                    result.warnings.append(QStringLiteral("Direct background '%1': X/Y/scale are ignored; use the SIDBOX background camera/scroll instead.")
                                           .arg(a.name));
                }
            }
            const QString path = QFileInfo(a.absolutePath).absoluteFilePath();
            int b = bitmapIndex.value(path, -1);
            if (b < 0) {
                Bitmap bitmap;
                bitmap.path = path;
                bitmap.symbol = QStringLiteral("asset_pixels_%1").arg(bitmaps.size());
                bitmap.sdPath = sdLocation(path, request.designDirectory, result);
                if (!readPpb(path, &bitmap, &result.error)) return result;
                b = bitmaps.size(); bitmaps.append(bitmap); bitmapIndex.insert(path, b);
            }
            // A tile atlas owns PPB pixels, never a BOB/sprite or draw call.
            // gameassets_find_ppb() exposes the same allocation to level1.c;
            // game_level1_unload_atlas() correctly leaves borrowed pixels alone.
            if (tileAtlas) { selectedTileAtlasLoaded = true; continue; }
            if (direct) {
                DirectBackground db;
                db.asset = a;
                db.symbol = uniqueIdentifier(base, QStringLiteral("direct background"), symbols, result);
                if (!result.error.isEmpty()) return result;
                db.bitmap = b;
                db.convert = a.backgroundMode == QStringLiteral("direct_convert");
                directBackgrounds.append(db);
                if (db.convert)
                    result.warnings.append(QStringLiteral("'%1': normal PPB pixels will be transposed into a separate %2 KiB background allocation at gameassets_init().")
                                           .arg(a.name).arg((qint64(bitmaps.at(b).width)*bitmaps.at(b).height+1023)/1024));
                continue;
            }
            int g = groupIndex.value(groupKey, -1);
            if (g < 0) {
                Group group;
                group.name = base; group.array = array; group.background = background;
                group.symbol = uniqueIdentifier(base, QStringLiteral("sprite"), symbols, result);
                if (!result.error.isEmpty()) return result;
                g = groups.size(); groups.append(group); groupIndex.insert(groupKey, g);
            } else if (groups[g].array != array || groups[g].background != background) {
                result.error = QStringLiteral("'%1' mixes array/singleton or foreground/background usage.").arg(base);
                return result;
            }
            Sprite sprite;
            sprite.asset = a; sprite.group = groupKey; sprite.array = array;
            sprite.index = element; sprite.bitmap = b; sprite.background = background;
            sprite.cellW = a.cellWidth > 0 ? a.cellWidth : bitmaps.at(b).width;
            sprite.cellH = a.cellHeight > 0 ? a.cellHeight : bitmaps.at(b).height;
            if (sprite.cellW < 1 || sprite.cellH < 1 || sprite.cellW > bitmaps.at(b).width
                || sprite.cellH > bitmaps.at(b).height || a.frame < 0 || a.frame > 255) {
                result.error = QStringLiteral("Invalid atlas cell/frame for '%1'. V1 frame index must fit 0..255.").arg(a.name);
                return result;
            }
            const int availableFrames = (bitmaps.at(b).width / sprite.cellW)
                                      * (bitmaps.at(b).height / sprite.cellH);
            if (availableFrames < 1 || a.frame >= availableFrames) {
                result.error = QStringLiteral("Frame %1 is outside the atlas for '%2' (%3 frames).")
                    .arg(a.frame).arg(a.name).arg(availableFrames);
                return result;
            }
            if ((bitmaps.at(b).width % sprite.cellW) || (bitmaps.at(b).height % sprite.cellH))
                result.warnings.append(QStringLiteral("'%1': atlas size isn't divisible by its cells.").arg(a.name));
            if (array) {
                for (int prev : groups[g].sprites) {
                    if (sprites.at(prev).index == element) {
                        result.error = QStringLiteral("Duplicate sprite array index: %1").arg(a.name);
                        return result;
                    }
                }
            } else if (!groups[g].sprites.isEmpty()) {
                result.error = QStringLiteral("Duplicate sprite name '%1'.").arg(base);
                return result;
            }
            groups[g].sprites.append(sprites.size());
            groups[g].count = qMax(groups[g].count, element + 1);
            sprites.append(sprite);
        } else if (a.kind == QStringLiteral("sound")) {
            if (a.absolutePath.isEmpty()) continue;
            Sound s; s.asset = a;
            s.id = uniqueIdentifier(a.name.trimmed().isEmpty() ? QFileInfo(a.absolutePath).completeBaseName() : a.name,
                                    QStringLiteral("sound"), symbols, result);
            if (!result.error.isEmpty()) return result;
            s.sdPath = sdLocation(a.absolutePath, request.designDirectory, result);
            QFile wav(a.absolutePath);
            if (!wav.open(QIODevice::ReadOnly)) {
                result.error = QStringLiteral("Cannot read WAV: %1").arg(a.absolutePath); return result;
            }
            QByteArray head = wav.read(44);
            if (head.size() < 44 || head.mid(0,4) != "RIFF" || head.mid(8,4) != "WAVE"
                || head.mid(12,4) != "fmt " || head.mid(36,4) != "data") {
                result.error = QStringLiteral("V1 LoadSFX requires a standard 44-byte PCM WAV: %1").arg(a.absolutePath); return result;
            }
            const auto u16 = [&](int pos) { return int(quint8(head[pos])) | (int(quint8(head[pos+1])) << 8); };
            s.bits = u16(34);
            if (u16(20) != 1 || u16(22) != 1 || (s.bits != 8 && s.bits != 16)) {
                result.error = QStringLiteral("V1 WAV must be mono PCM 8/16-bit: %1").arg(a.absolutePath); return result;
            }
            if (a.volume > 255) result.warnings.append(QStringLiteral("'%1': audio overdrive above 255 may clip (preserved by generator).").arg(a.name));
            sounds.append(s);
        } else if (a.kind == QStringLiteral("music")) {
            if (a.absolutePath.isEmpty()) continue;
            Music m; m.asset = a;
            m.id = uniqueIdentifier(a.name.trimmed().isEmpty() ? QFileInfo(a.absolutePath).completeBaseName() : a.name,
                                    QStringLiteral("music"), symbols, result);
            if (!result.error.isEmpty()) return result;
            m.sdPath = sdLocation(a.absolutePath, request.designDirectory, result);
            if (!QFileInfo::exists(a.absolutePath)) { result.error = QStringLiteral("Missing music file: %1").arg(a.absolutePath); return result; }
            music.append(m);
        }
    }
    for (const Group &g : groups) {
        if (!g.array) continue;
        for (int n = 0; n < g.count; ++n) {
            bool found = false;
            for (int at : g.sprites) if (sprites.at(at).index == n) { found = true; break; }
            if (!found) {
                result.error = QStringLiteral("'%1[]' has a gap at [%2]. Number arrays consecutively from [0].").arg(g.name).arg(n);
                return result;
            }
        }
    }
    if (request.embedPixels) {
        for (const Bitmap &bm : bitmaps) result.embeddedBytes += bm.pixels.size();
        if (result.embeddedBytes > 4 * 1024 * 1024) {
            result.error = QStringLiteral("Embedded graphics exceed 4 MiB. Use SD-loaded PPBs, or reduce assets.");
            return result;
        }
        if (result.embeddedBytes > 1024*1024)
            result.warnings.append(QStringLiteral("Embedding %1 KiB of uncompressed sprite data in the V1 app. Check SDRAM/linker budget.")
                                   .arg((result.embeddedBytes + 1023) / 1024));
    }
    // Stage 4.51: gameassets.rulec/.ruleh own every emitted C statement.
    // Qt supplies only validated resource values, image bytes, palette entries,
    // names, selected feature flags, and repeated section configurations.
    const QDir ruleDir(request.rulesDirectory);
    QMap<QString, QByteArray> mainRules;
    QMap<QString, QByteArray> sections;
    const QRegularExpression sectionRe(QStringLiteral(
        R"((?ms)^@IDE_SECTION\{([A-Z_][A-Z0-9_]*)\}[ \t]*\r?\n(.*?)^@IDE_SECTION_END[ \t]*\r?\n?)"));
    for (const QString &ext : {QStringLiteral(".rulec"), QStringLiteral(".ruleh")}) {
        const QString path = ruleDir.filePath(QStringLiteral("gameassets") + ext);
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly)) {
            result.error = QStringLiteral("Cannot read Game Assets rule: %1").arg(path);
            return result;
        }
        QString whole = QString::fromUtf8(file.readAll());
        auto matches = sectionRe.globalMatch(whole);
        const int declared = whole.count(QStringLiteral("@IDE_SECTION{"));
        int extracted = 0;
        while (matches.hasNext()) {
            const auto match = matches.next();
            const QString name = match.captured(1);
            if (sections.contains(name)) {
                result.error = QStringLiteral("Duplicate Game Assets section: %1").arg(name);
                return result;
            }
            sections.insert(name, match.captured(2).toUtf8());
            ++extracted;
        }
        whole.remove(sectionRe);
        if (extracted != declared || whole.contains(QStringLiteral("@IDE_SECTION"))) {
            result.error = QStringLiteral("Malformed Game Assets rule section in %1").arg(path);
            return result;
        }
        mainRules.insert(ext, whole.toUtf8());
    }
    const QStringList expectedSections = {
        QStringLiteral("BITMAP_EMBED"), QStringLiteral("BITMAP_EXTERNAL"),
        QStringLiteral("PALETTE"), QStringLiteral("DIRECT_DECL"),
        QStringLiteral("SPRITE_DECL"), QStringLiteral("SOUND_DECL"),
        QStringLiteral("BITMAP_LOAD"), QStringLiteral("DIRECT_INIT"),
        QStringLiteral("FRONT_CYCLE"), QStringLiteral("BACK_CYCLE"),
        QStringLiteral("SPRITE_CLEAR"), QStringLiteral("SPRITE_INIT"),
        QStringLiteral("SOUND_LOAD"), QStringLiteral("MUSIC_START"),
        QStringLiteral("BITMAP_LOOKUP"), QStringLiteral("BITMAP_FREE"),
        QStringLiteral("DIRECT_FREE"), QStringLiteral("SOUND_FREE"),
        QStringLiteral("DRAW_FUNCTION"), QStringLiteral("DRAW_CALL"),
        QStringLiteral("DIRECT_SHOW"), QStringLiteral("SOUND_FUNCTION"),
        QStringLiteral("MUSIC_FUNCTION"), QStringLiteral("HEADER_DIRECT"),
        QStringLiteral("HEADER_SPRITE"), QStringLiteral("HEADER_SOUND"),
        QStringLiteral("HEADER_MUSIC")
    };
    for (const QString &name : expectedSections) {
        if (!sections.contains(name)) {
            result.error = QStringLiteral("Game Assets rule is missing section %1").arg(name);
            return result;
        }
    }
    const auto num = [](auto value) { return QString::number(value); };
    const auto flag = [](bool enabled) { return enabled ? QStringLiteral("1") : QStringLiteral("0"); };
    auto section = [&](const QString &name, const QMap<QString, QString> &fields,
                       QString &dest) -> bool {
        if (!sections.contains(name)) {
            result.error = QStringLiteral("Missing Game Assets section: %1").arg(name);
            return false;
        }
        QByteArray conditional, finished;
        const QString label = QStringLiteral("gameassets / ") + name;
        if (!GameHelperTemplates::renderConditionals(sections.value(name), fields, label,
                                                      &conditional, &result.error) ||
            !GameHelperTemplates::renderFields(conditional, fields, label,
                                                &finished, &result.error)) return false;
        dest += QString::fromUtf8(finished);
        return true;
    };
    QMap<QString, QString> code;
    QMap<QString, QString> hdr;
    const QStringList codeFields = {
        QStringLiteral("BITMAP_DECLARATIONS"), QStringLiteral("FRONT_PALETTE"),
        QStringLiteral("BACK_PALETTE"), QStringLiteral("DIRECT_DECLARATIONS"),
        QStringLiteral("SPRITE_DECLARATIONS"), QStringLiteral("SOUND_DECLARATIONS"),
        QStringLiteral("BITMAP_LOADS"), QStringLiteral("DIRECT_INITIALIZERS"),
        QStringLiteral("PALETTE_CYCLES"), QStringLiteral("SPRITE_INITIALIZERS"),
        QStringLiteral("SOUND_LOADS"), QStringLiteral("MUSIC_START"),
        QStringLiteral("BITMAP_LOOKUPS"), QStringLiteral("BITMAP_FREES"),
        QStringLiteral("DIRECT_FREES"), QStringLiteral("SOUND_FREES"),
        QStringLiteral("SPRITE_RESETS"), QStringLiteral("SPRITE_DRAW_FUNCTIONS"),
        QStringLiteral("DRAW_BACKGROUND"), QStringLiteral("DRAW_FOREGROUND"),
        QStringLiteral("DIRECT_DRAW_CALLS"), QStringLiteral("SOUND_FUNCTIONS"),
        QStringLiteral("MUSIC_FUNCTIONS")
    };
    // Removing a required slot from a customized rule must fail, not silently
    // drop generated resources from the project.
    for (const QString &key : codeFields) {
        if (!mainRules.value(QStringLiteral(".rulec")).contains(
                QStringLiteral("@IDE{%1}").arg(key).toUtf8())) {
            result.error = QStringLiteral("gameassets.rulec is missing required @IDE{%1}").arg(key);
            return result;
        }
    }
    for (const QString &key : {QStringLiteral("DIRECT_BACK_HEADERS"),
                               QStringLiteral("SPRITE_HEADERS"),
                               QStringLiteral("SOUND_HEADERS"),
                               QStringLiteral("MUSIC_HEADERS")}) {
        if (!mainRules.value(QStringLiteral(".ruleh")).contains(
                QStringLiteral("@IDE{%1}").arg(key).toUtf8())) {
            result.error = QStringLiteral("gameassets.ruleh is missing required @IDE{%1}").arg(key);
            return result;
        }
    }
    for (const QString &key : codeFields) code.insert(key, {});
    for (const QString &key : {QStringLiteral("DIRECT_BACK_HEADERS"),
                               QStringLiteral("SPRITE_HEADERS"),
                               QStringLiteral("SOUND_HEADERS"),
                               QStringLiteral("MUSIC_HEADERS")}) hdr.insert(key, {});
    code.insert(QStringLiteral("DUAL_PLANE"), flag(request.dualPlane));
    code.insert(QStringLiteral("HAS_FRONT_PALETTE"), flag(!frontClut.isEmpty()));
    code.insert(QStringLiteral("HAS_BACK_PALETTE"), flag(request.dualPlane && !backClut.isEmpty()));
    code.insert(QStringLiteral("HAS_FOREGROUND_CYCLE"), flag(request.foregroundCycle.enabled));
    code.insert(QStringLiteral("HAS_BACKGROUND_CYCLE"), flag(request.dualPlane && request.backgroundCycle.enabled));

    for (const Bitmap &bm : bitmaps) {
        const QMap<QString, QString> fields = {
            {QStringLiteral("PIXEL_SYMBOL"), bm.symbol},
            {QStringLiteral("WIDTH"), num(bm.width)},
            {QStringLiteral("HEIGHT"), num(bm.height)},
            {QStringLiteral("RAW_WIDTH"), num(bm.width)},
            {QStringLiteral("RAW_HEIGHT"), num(bm.height)},
            {QStringLiteral("PIXEL_COUNT"), num(qint64(bm.width) * bm.height)},
            {QStringLiteral("PPB_PATH"), cString(bm.sdPath)},
            {QStringLiteral("LOAD_GUARD"), request.embedPixels ? QString() : QStringLiteral(" && ") + bm.symbol}
        };
        if (request.embedPixels) {
            // Only pixel DATA is formatted by Qt. The C declaration is in the rule.
            QString pixelData;
            QTextStream data(&pixelData);
            for (qsizetype i = 0; i < bm.pixels.size(); ++i) {
                if (i % 20 == 0) data << "    ";
                data << "0x" << QStringLiteral("%1").arg(unsigned(uchar(bm.pixels.at(i))),
                                      2, 16, QLatin1Char('0')).toUpper();
                if (i != bm.pixels.size() - 1) data << ',';
                if (i % 20 == 19 || i == bm.pixels.size() - 1) data << '\n';
                else data << ' ';
            }
            data.flush();
            QMap<QString, QString> embed = fields;
            embed.insert(QStringLiteral("PIXEL_DATA"), pixelData);
            if (!section(QStringLiteral("BITMAP_EMBED"), embed, code[QStringLiteral("BITMAP_DECLARATIONS")])) return result;
        } else {
            if (!section(QStringLiteral("BITMAP_EXTERNAL"), fields, code[QStringLiteral("BITMAP_DECLARATIONS")]) ||
                !section(QStringLiteral("BITMAP_LOAD"), fields, code[QStringLiteral("BITMAP_LOADS")]) ||
                !section(QStringLiteral("BITMAP_FREE"), fields, code[QStringLiteral("BITMAP_FREES")])) return result;
        }
        if (!section(QStringLiteral("BITMAP_LOOKUP"), fields, code[QStringLiteral("BITMAP_LOOKUPS")])) return result;
    }
    if (frontClut.isEmpty() && (!sprites.isEmpty() || selectedTileAtlasLoaded))
        result.warnings.append(QStringLiteral("No foreground CLUT selected: your main.c must initialise the active foreground palette."));
    if (request.dualPlane && backClut.isEmpty())
        result.warnings.append(QStringLiteral("No background CLUT selected: your main.c must initialise the active background palette."));
    for (bool background : {false, true}) {
        const QVector<quint32> &colours = background ? backClut : frontClut;
        if (colours.size() != 256) continue;
        QString paletteData;
        QTextStream data(&paletteData);
        for (int i = 0; i < 256; ++i) {
            if (i % 8 == 0) data << "    ";
            data << "0x" << QStringLiteral("%1").arg(colours.at(i), 8, 16,
                                 QLatin1Char('0')).toUpper() << "u";
            if (i != 255) data << ", ";
            if (i % 8 == 7) data << '\n';
        }
        data.flush();
        QMap<QString, QString> fields = {
            {QStringLiteral("PALETTE_SYMBOL"), background ? QStringLiteral("gameassets_back_clut")
                                                   : QStringLiteral("gameassets_front_clut")},
            {QStringLiteral("PALETTE_DATA"), paletteData}
        };
        if (!section(QStringLiteral("PALETTE"), fields,
                     code[background ? QStringLiteral("BACK_PALETTE") : QStringLiteral("FRONT_PALETTE")])) return result;
    }
    for (const DirectBackground &db : directBackgrounds) {
        const Bitmap &bm = bitmaps.at(db.bitmap);
        const QMap<QString, QString> fields = {
            {QStringLiteral("SYMBOL"), db.symbol},
            {QStringLiteral("CONVERT"), flag(db.convert)},
            {QStringLiteral("PIXEL_SYMBOL"), bm.symbol},
            {QStringLiteral("RAW_WIDTH"), num(bm.width)},
            {QStringLiteral("RAW_HEIGHT"), num(bm.height)},
            {QStringLiteral("PIXEL_COUNT"), num(qint64(bm.width)*bm.height)},
            {QStringLiteral("BUFFER_WIDTH"), num(db.convert ? bm.width : bm.height)},
            {QStringLiteral("BUFFER_HEIGHT"), num(db.convert ? bm.height : bm.width)}
        };
        if (!section(QStringLiteral("HEADER_DIRECT"), fields, hdr[QStringLiteral("DIRECT_BACK_HEADERS")]) ||
            !section(QStringLiteral("DIRECT_DECL"), fields, code[QStringLiteral("DIRECT_DECLARATIONS")]) ||
            !section(QStringLiteral("DIRECT_INIT"), fields, code[QStringLiteral("DIRECT_INITIALIZERS")]) ||
            !section(QStringLiteral("DIRECT_FREE"), fields, code[QStringLiteral("DIRECT_FREES")]) ||
            !section(QStringLiteral("DIRECT_SHOW"), fields, code[QStringLiteral("DIRECT_DRAW_CALLS")])) return result;
    }
    for (const Group &g : groups) {
        const QMap<QString, QString> fields = {
            {QStringLiteral("SYMBOL"), g.symbol},
            {QStringLiteral("ARRAY"), flag(g.array)},
            {QStringLiteral("ARRAY_DECL"), g.array ? QStringLiteral("[") + num(g.count) + QStringLiteral("]") : QString()},
            {QStringLiteral("ARGUMENT"), g.array ? QStringLiteral("int index") : QStringLiteral("void")},
            {QStringLiteral("COUNT"), num(g.count)},
            {QStringLiteral("DRAW_REF"), g.array ? g.symbol + QStringLiteral("[index]") : g.symbol}
        };
        if (!section(QStringLiteral("HEADER_SPRITE"), fields, hdr[QStringLiteral("SPRITE_HEADERS")]) ||
            !section(QStringLiteral("SPRITE_DECL"), fields, code[QStringLiteral("SPRITE_DECLARATIONS")]) ||
            !section(QStringLiteral("SPRITE_CLEAR"), fields, code[QStringLiteral("SPRITE_INITIALIZERS")]) ||
            !section(QStringLiteral("SPRITE_CLEAR"), fields, code[QStringLiteral("SPRITE_RESETS")]) ||
            !section(QStringLiteral("DRAW_FUNCTION"), fields, code[QStringLiteral("SPRITE_DRAW_FUNCTIONS")])) return result;
        for (int at : g.sprites) {
            const Sprite &sprite = sprites.at(at);
            const Bitmap &bm = bitmaps.at(sprite.bitmap);
            QMap<QString, QString> sf = {
                {QStringLiteral("REF"), g.array ? g.symbol + QStringLiteral("[") + num(sprite.index) + QStringLiteral("]") : g.symbol},
                {QStringLiteral("PIXEL_SYMBOL"), bm.symbol},
                {QStringLiteral("RAW_WIDTH"), num(bm.width)},
                {QStringLiteral("RAW_HEIGHT"), num(bm.height)},
                {QStringLiteral("CELL_WIDTH"), num(sprite.cellW)},
                {QStringLiteral("CELL_HEIGHT"), num(sprite.cellH)},
                {QStringLiteral("X"), num(sprite.asset.x)},
                {QStringLiteral("Y"), num(sprite.asset.y)},
                {QStringLiteral("SCALE"), num(qBound(1, sprite.asset.scale, 800))},
                {QStringLiteral("FRAME"), num(sprite.asset.frame)}
            };
            if (!section(QStringLiteral("SPRITE_INIT"), sf, code[QStringLiteral("SPRITE_INITIALIZERS")])) return result;
        }
    }
    // Draw order matches resource order: background groups, then foreground.
    // Each group's sprites keep the original placement order.
    for (bool background : {true, false}) {
        for (const Group &g : groups) {
            if (g.background != background) continue;
            for (int at : g.sprites) {
                const Sprite &sprite = sprites.at(at);
                if (sprite.asset.worldManaged) continue;
                const QMap<QString, QString> fields = {
                    {QStringLiteral("SYMBOL"), g.symbol},
                    {QStringLiteral("ARG"), g.array ? num(sprite.index) : QString()}
                };
                if (!section(QStringLiteral("DRAW_CALL"), fields,
                             code[background ? QStringLiteral("DRAW_BACKGROUND") : QStringLiteral("DRAW_FOREGROUND")])) return result;
            }
        }
    }
    for (const Sound &sfx : sounds) {
        const QMap<QString, QString> fields = {
            {QStringLiteral("SYMBOL"), sfx.id},
            {QStringLiteral("WAV_PATH"), cString(sfx.sdPath)},
            {QStringLiteral("CHANNEL"), num(qBound(0, sfx.asset.channel, 7))},
            {QStringLiteral("LENGTH_DIVISOR"), sfx.bits == 16 ? QStringLiteral(" / 2u") : QString()},
            {QStringLiteral("BITS_FLAG"), num(sfx.bits == 16 ? 1 : 0)},
            {QStringLiteral("FREQUENCY"), num(qBound(1, sfx.asset.frequency, 65535))},
            {QStringLiteral("VOLUME"), num(qBound(0, sfx.asset.volume, 1024))},
            {QStringLiteral("PAN"), num(qBound(-127, sfx.asset.pan, 127))},
            {QStringLiteral("LOOP_START"), num(sfx.asset.loop ? sfx.asset.loopStart : 0)},
            {QStringLiteral("LOOP_LENGTH"), num(sfx.asset.loop ? sfx.asset.loopLength : 0)},
            {QStringLiteral("LOOP_ENABLED"), num(sfx.asset.loop ? 1 : 0)}
        };
        if (!section(QStringLiteral("HEADER_SOUND"), fields, hdr[QStringLiteral("SOUND_HEADERS")]) ||
            !section(QStringLiteral("SOUND_DECL"), fields, code[QStringLiteral("SOUND_DECLARATIONS")]) ||
            !section(QStringLiteral("SOUND_LOAD"), fields, code[QStringLiteral("SOUND_LOADS")]) ||
            !section(QStringLiteral("SOUND_FREE"), fields, code[QStringLiteral("SOUND_FREES")]) ||
            !section(QStringLiteral("SOUND_FUNCTION"), fields, code[QStringLiteral("SOUND_FUNCTIONS")])) return result;
    }
    for (const Music &track : music) {
        const QMap<QString, QString> fields = {
            {QStringLiteral("SYMBOL"), track.id},
            {QStringLiteral("MUSIC_PATH"), cString(track.sdPath)},
            {QStringLiteral("SUBSONG"), num(qBound(0, track.asset.subsong, 255))}
        };
        if (!section(QStringLiteral("HEADER_MUSIC"), fields, hdr[QStringLiteral("MUSIC_HEADERS")]) ||
            !section(QStringLiteral("MUSIC_FUNCTION"), fields, code[QStringLiteral("MUSIC_FUNCTIONS")])) return result;
        if (track.asset.musicPlayOnStart && code[QStringLiteral("MUSIC_START")].isEmpty()) {
            if (!section(QStringLiteral("MUSIC_START"), fields, code[QStringLiteral("MUSIC_START")])) return result;
        }
    }
    if (request.foregroundCycle.enabled) {
        const auto &cycle = request.foregroundCycle;
        const int from = qBound(1, cycle.start, 254);
        const int length = qBound(2, cycle.length, 256-from);
        const QMap<QString, QString> fields = {
            {QStringLiteral("CYCLE_FROM"), num(from)},
            {QStringLiteral("CYCLE_END"), num(from + length - 1)},
            {QStringLiteral("CYCLE_SPEED"), num(qBound(1, cycle.speed, 255))}
        };
        if (!section(QStringLiteral("FRONT_CYCLE"), fields, code[QStringLiteral("PALETTE_CYCLES")])) return result;
    }
    if (request.dualPlane && request.backgroundCycle.enabled) {
        const auto &cycle = request.backgroundCycle;
        const int from = qBound(0, cycle.start, 254);
        const int length = qBound(2, cycle.length, 256-from);
        const QMap<QString, QString> fields = {
            {QStringLiteral("CYCLE_FROM"), num(from)},
            {QStringLiteral("CYCLE_END"), num(from + length - 1)},
            {QStringLiteral("CYCLE_SPEED"), num(qBound(1, cycle.speed, 255))}
        };
        if (!section(QStringLiteral("BACK_CYCLE"), fields, code[QStringLiteral("PALETTE_CYCLES")])) return result;
    }
    QString h, c;
    QByteArray conditional, expanded;
    if (!GameHelperTemplates::renderConditionals(mainRules.value(QStringLiteral(".rulec")), code,
                                                  QStringLiteral("gameassets.rulec"), &conditional, &result.error) ||
        !GameHelperTemplates::renderFields(conditional, code,
                                           QStringLiteral("gameassets.rulec"), &expanded, &result.error)) return result;
    c = QString::fromUtf8(expanded);
    if (!GameHelperTemplates::renderConditionals(mainRules.value(QStringLiteral(".ruleh")), hdr,
                                                  QStringLiteral("gameassets.ruleh"), &conditional, &result.error) ||
        !GameHelperTemplates::renderFields(conditional, hdr,
                                           QStringLiteral("gameassets.ruleh"), &expanded, &result.error)) return result;
    h = QString::fromUtf8(expanded);
    if (!QDir().mkpath(request.outputDirectory)) {
        result.error = QStringLiteral("Cannot create gameassets folder: %1").arg(request.outputDirectory);
        return result;
    }
    const QString pathH = QDir(request.outputDirectory).filePath(QStringLiteral("gameassets.h"));
    const QString pathC = QDir(request.outputDirectory).filePath(QStringLiteral("gameassets.c"));
    // Identical failures leave existing files intact; the IDE explicitly asks
    // before replacing old outputs. Both files use atomic QSaveFile writes.
    if (!writeAtomic(pathH, h, &result.error) || !writeAtomic(pathC, c, &result.error)) return result;
    result.ok = true;
    result.files << pathH << pathC;
    return result;
}
}
