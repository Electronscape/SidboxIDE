#include "gamecodegen.h"
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
void emitPalette(QTextStream &c, const QString &name, const QVector<quint32> &colours)
{
    if (colours.size() != 256) return;
    c << "static uint32_t " << name << "[256] __attribute__((aligned(32))) = {\n";
    for (int i = 0; i < 256; ++i) {
        if (i % 8 == 0) c << "    ";
        c << "0x" << QStringLiteral("%1").arg(colours.at(i), 8, 16, QLatin1Char('0')).toUpper() << "u";
        if (i != 255) c << ", ";
        if (i % 8 == 7) c << "\n";
    }
    c << "};\n\n";
}
void emitBytes(QTextStream &c, const Bitmap &bm)
{
    c << "/* Original PPB indexed pixels, unchanged; " << bm.width << " x " << bm.height << ". */\n";
    c << "static const uint8_t " << bm.symbol << "[] __attribute__((aligned(32))) = {\n";
    for (qsizetype i = 0; i < bm.pixels.size(); ++i) {
        if (i % 20 == 0) c << "    ";
        c << "0x" << QStringLiteral("%1").arg(unsigned(uchar(bm.pixels.at(i))), 2, 16, QLatin1Char('0')).toUpper();
        if (i != bm.pixels.size() - 1) c << ',';
        if (i % 20 == 19 || i == bm.pixels.size() - 1) c << '\n';
        else c << ' ';
    }
    c << "};\n\n";
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
    QString h, c;
    QTextStream header(&h), source(&c);
    header << "/* CoderGirl V1 auto-generated. Recreate from .sbgm; do not hand-edit. */\n"
              "#ifndef CODERGIRL_GENERATED_GAMEASSETS_H\n#define CODERGIRL_GENERATED_GAMEASSETS_H\n"
              "#include <stdint.h>\n#include \"apis.h\"\n#ifdef __cplusplus\nextern \"C\" {\n#endif\n\n"
              "/* Call AFTER initMalloc(), before the first draw. Returns 1 on success. */\n"
              "int gameassets_init(void);\nvoid gameassets_shutdown(void);\n"
              "/* Exposes sprite PPB pixels for a matching tilemap atlas (no copy). */\n"
              "#define GAMEASSETS_HAS_PPB_LOOKUP 1\n"
              "const uint8_t *gameassets_find_ppb(const char *sd_path, uint16_t *width, uint16_t *height);\n"
              "/* Uses the CURRENT graphics draw buffer; does not flip/display. */\n"
              "void gameassets_draw_foreground(void);\nvoid gameassets_draw_background(void);\n"
              "/* Single plane: all placed assets. Dual plane: foreground only. */\n"
              "void drawworld(void);\n"
              "/* Convenience: supply your actual active front/back gfx_bitmap_t pointers. */\n"
              "void gameassets_draw_layers(gfx_bitmap_t *front, gfx_bitmap_t *back);\n"
              "/* Direct background: assigns the bitmap to the display, no sprite blit. */\n"
              "void gameassets_show_background(void);\n\n";
    source << "/* Auto-generated by CoderGirl V1 Game Designer. Regeneration overwrites THIS file only. */\n"
              "#include \"gameassets.h\"\n#include <stdlib.h>\n#include <string.h>\n\n";
    if (request.dualPlane)
        source << "/* Dual-plane: call gameassets_draw_background() with a BACKGROUND target set,\n"
                  "   then call drawworld() while the foreground draw buffer is active.\n"
                  "   The V1 game itself owns its gfx_mode(), buffers and camera scrolling. */\n\n";
    if (request.embedPixels) {
        for (const Bitmap &bm : bitmaps) emitBytes(source, bm);
    } else {
        for (const Bitmap &bm : bitmaps)
            source << "static uint8_t *" << bm.symbol << " = NULL;\n";
        source << '\n';
    }
    if (frontClut.isEmpty() && (!sprites.isEmpty() || selectedTileAtlasLoaded))
        result.warnings.append(QStringLiteral("No foreground CLUT selected: your main.c must initialise the active foreground palette."));
    if (request.dualPlane && backClut.isEmpty())
        result.warnings.append(QStringLiteral("No background CLUT selected: your main.c must initialise the active background palette."));
    if (!frontClut.isEmpty()) emitPalette(source, QStringLiteral("gameassets_front_clut"), frontClut);
    if (!backClut.isEmpty()) emitPalette(source, QStringLiteral("gameassets_back_clut"), backClut);

    for (const DirectBackground &db : directBackgrounds) {
        header << "extern gfx_bitmap_t " << db.symbol << "_backbitmap;\n";
        source << "gfx_bitmap_t " << db.symbol << "_backbitmap __attribute__((aligned(32)));\n";
        if (db.convert)
            source << "static uint8_t *gameassets_column_pixels_" << db.symbol << " = NULL;\n";
    }
    if (!directBackgrounds.isEmpty()) source << '\n';
    for (const Group &g : groups) {
        header << "extern gfxbob_t " << g.symbol;
        if (g.array) header << '[' << g.count << ']';
        header << ";\n";
        header << "void draw" << g.symbol << '(' << (g.array ? "int index" : "void") << ");\n";
        source << "gfxbob_t " << g.symbol;
        if (g.array) source << '[' << g.count << ']';
        source << " __attribute__((aligned(32)));\n";
    }
    header << '\n'; source << '\n';
    for (const Sound &s : sounds) {
        source << "static uint8_t *gameassets_sfx_" << s.id << " = NULL;\n"
               << "static uint32_t gameassets_sfx_length_" << s.id << " = 0;\n";
        header << "void playsound" << s.id << "(void);\n";
    }
    for (const Music &m : music) header << "void playmusic" << m.id << "(void);\n";
    header << "\n#ifdef __cplusplus\n}\n#endif\n#endif\n";

    source << "\nint gameassets_init(void)\n{\n"
              "    /* Graphics mode, drawing buffers and initMalloc belong to main.c. */\n"
              "    gameassets_shutdown();\n";
    if (!request.embedPixels) {
        for (const Bitmap &bm : bitmaps) {
            const qint64 count = qint64(bm.width) * bm.height;
            source << "    " << bm.symbol << " = (uint8_t *)malloc(" << count << "u);\n"
                   << "    if (!" << bm.symbol << ") goto failed;\n"
                   << "    LoadPPB((char *)" << cString(bm.sdPath) << ", " << bm.symbol << ");\n";
        }
    }
    for (const DirectBackground &db : directBackgrounds) {
        const Bitmap &bm = bitmaps.at(db.bitmap);
        const QString desc = db.symbol + QStringLiteral("_backbitmap");
        const QString bytes = QString::number(qint64(bm.width) * bm.height);
        source << "    memset(&" << desc << ", 0, sizeof(" << desc << "));\n";
        if (db.convert) {
            const QString dst = QStringLiteral("gameassets_column_pixels_") + db.symbol;
            source << "    " << dst << " = (uint8_t *)malloc(" << bytes << "u);\n"
                   << "    if (!" << dst << ") goto failed;\n"
                   << "    /* Flip X + rotate CCW = transpose into SIDBOX column-major pixels. */\n"
                   << "    for (uint32_t y = 0; y < " << bm.height << "u; ++y)\n"
                   << "        for (uint32_t x = 0; x < " << bm.width << "u; ++x)\n"
                   << "            " << dst << "[x * " << bm.height << "u + y] = "
                   << bm.symbol << "[y * " << bm.width << "u + x];\n";
            source << "    " << desc << ".bitmap = " << dst << ";\n";
        } else {
            // PPB on disk is already in column-major order. No transpose,
            // no extra SDRAM allocation and no change to original bytes.
            source << "    " << desc << ".bitmap = (uint8_t *)" << bm.symbol << ";\n";
        }
        // Prepared PPBs store the background sideways. Their PPB image
        // dimensions describe the raw file, not the on-screen framebuffer.
        // Converted PPBs start upright and are transposed above instead.
        const int bufferWidth = db.convert ? bm.width : bm.height;
        const int bufferHeight = db.convert ? bm.height : bm.width;
        if (db.convert) {
            source << "    // SIDBOX stores background images sideways in memory.\n"
                      "    // This image has been converted into that layout so\n"
                      "    // it can display and scroll without distortion.\n";
        } else {
            source << "    // SIDBOX stores background images sideways in memory.\n"
                      "    // This means the width and height look swapped around.\n"
                      "    // These values are correct and allow the background to\n"
                      "    // display and scroll properly without image distortion.\n";
        }
        source << "    " << desc << ".width = " << bufferWidth << "u;\n"
               << "    " << desc << ".height = " << bufferHeight << "u;\n"
               << "    " << desc << ".stride = " << bufferHeight << "u;\n"
               << "    " << desc << ".memspacelen = " << bytes << "u;\n";
    }
    if (!frontClut.isEmpty()) source << "    gfx_usefpalette(gameassets_front_clut);\n";
    if (!backClut.isEmpty() && request.dualPlane) source << "    gfx_usebpalette(gameassets_back_clut);\n";
    for (const Group &g : groups) {
        const QString dst = g.symbol;
        source << "    memset(&" << dst << ", 0, sizeof(" << dst << "));\n";
        for (int at : g.sprites) {
            const Sprite &s = sprites.at(at);
            const Bitmap &bm = bitmaps.at(s.bitmap);
            const QString ref = g.array ? QStringLiteral("%1[%2]").arg(dst).arg(s.index) : dst;
            source << "    " << ref << ".imgdat = " << bm.symbol << ";\n"
                   << "    " << ref << ".atlas_stride = " << bm.width << ";\n"
                   << "    " << ref << ".atlas_height = " << bm.height << ";\n"
                   << "    " << ref << ".width = " << s.cellW << ";\n"
                   << "    " << ref << ".height = " << s.cellH << ";\n"
                   << "    " << ref << ".drawx = " << s.asset.x << ";\n"
                   << "    " << ref << ".drawy = " << s.asset.y << ";\n"
                   << "    " << ref << ".scale = " << qBound(1, s.asset.scale, 800) << ";\n"
                   << "    " << ref << ".index = " << s.asset.frame << ";\n";
        }
    }
    for (const Sound &s : sounds) {
        source << "    gameassets_sfx_length_" << s.id << " = LoadSFX((char *)"
               << cString(s.sdPath) << ", &gameassets_sfx_" << s.id << ");\n"
               << "    if (!gameassets_sfx_length_" << s.id << " || !gameassets_sfx_" << s.id << ") goto failed;\n";
    }
    source << "    return 1;\nfailed:\n    gameassets_shutdown();\n    return 0;\n}\n\n";

    source << "/* Borrow-only lookup. The returned memory belongs to gameassets.\n"
              "   Do not free it or use it after gameassets_shutdown(). */\n"
              "const uint8_t *gameassets_find_ppb(const char *sd_path, uint16_t *width, uint16_t *height)\n{\n"
              "    if (!sd_path) return NULL;\n";
    for (const Bitmap &bm : bitmaps) {
        source << "    if (strcmp(sd_path, " << cString(bm.sdPath) << ") == 0";
        if (!request.embedPixels) source << " && " << bm.symbol;
        source << ") {\n"
               << "        if (width) *width = " << bm.width << "u;\n"
               << "        if (height) *height = " << bm.height << "u;\n"
               << "        return " << bm.symbol << ";\n"
               << "    }\n";
    }
    source << "    return NULL;\n}\n\n";

    source << "void gameassets_shutdown(void)\n{\n";
    if (!request.embedPixels) {
        for (const Bitmap &bm : bitmaps)
            source << "    free(" << bm.symbol << "); " << bm.symbol << " = NULL;\n";
    }
    for (const DirectBackground &db : directBackgrounds) {
        if (db.convert)
            source << "    free(gameassets_column_pixels_" << db.symbol << "); gameassets_column_pixels_" << db.symbol << " = NULL;\n";
        source << "    memset(&" << db.symbol << "_backbitmap, 0, sizeof(" << db.symbol << "_backbitmap));\n";
    }
    for (const Sound &s : sounds)
        source << "    free(gameassets_sfx_" << s.id << "); gameassets_sfx_" << s.id << " = NULL;\n"
               << "    gameassets_sfx_length_" << s.id << " = 0;\n";
    for (const Group &g : groups) source << "    memset(&" << g.symbol << ", 0, sizeof(" << g.symbol << "));\n";
    source << "}\n\n";

    for (const Group &g : groups) {
        source << "void draw" << g.symbol << '(' << (g.array ? "int index" : "void") << ")\n{\n";
        if (g.array) source << "    if (index < 0 || index >= " << g.count << ") return;\n";
        const QString ref = g.array ? g.symbol + QStringLiteral("[index]") : g.symbol;
        source << "    if (" << ref << ".imgdat) gfx_drawbob(&" << ref << ");\n}\n\n";
    }
    for (bool background : {true, false}) {
        source << "void gameassets_draw_" << (background ? "background" : "foreground") << "(void)\n{\n";
        for (const Group &g : groups) {
            if (g.background != background) continue;
            // World Objects and Collectables own their drawing and camera
            // translation. Do not draw their unmoved world-space clones here.
            for (int spriteIndex : g.sprites) {
                const Sprite &sprite = sprites.at(spriteIndex);
                if (sprite.asset.worldManaged) continue;
                if (g.array)
                    source << "    draw" << g.symbol << "(" << sprite.index << ");\n";
                else source << "    draw" << g.symbol << "();\n";
            }
        }
        source << "}\n\n";
    }
    source << "void drawworld(void)\n{\n";
    if (!request.dualPlane) source << "    gameassets_draw_background();\n";
    source << "    gameassets_draw_foreground();\n}\n\n";
    source << "void gameassets_draw_layers(gfx_bitmap_t *front, gfx_bitmap_t *back)\n{\n";
    if (request.dualPlane) {
        source << "    if (back) { gfx_usebuffer(back); gameassets_draw_background(); }\n"
                  "    if (front) { gfx_usebuffer(front); gameassets_draw_foreground(); }\n";
    } else {
        source << "    (void)back;\n"
                  "    if (front) { gfx_usebuffer(front); drawworld(); }\n";
    }
    source << "}\n\n";
    source << "void gameassets_show_background(void)\n{\n";
    for (const DirectBackground &db : directBackgrounds) {
        source << "    if (" << db.symbol << "_backbitmap.bitmap)\n"
               << "        gfx_showbbuffer(&" << db.symbol << "_backbitmap);\n";
    }
    source << "}\n\n";
    for (const Sound &s : sounds) {
        const int chan = qBound(0, s.asset.channel, 7);
        const int bitsFlag = s.bits == 16 ? 1 : 0;
        source << "void playsound" << s.id << "(void)\n{\n"
               << "    if (!gameassets_sfx_" << s.id << ") return;\n"
               << "    sound_stop(" << chan << ");\n"
               << "    sound_assign(" << chan << ", gameassets_sfx_" << s.id << ", "
               << "gameassets_sfx_length_" << s.id << (bitsFlag ? " / 2u" : "") << ", " << bitsFlag << ");\n"
               << "    sound_setfrequency(" << chan << ", " << qBound(1, s.asset.frequency, 65535) << ");\n"
               << "    sound_setvolume(" << chan << ", " << qBound(0, s.asset.volume, 1024) << ");\n"
               << "    sound_setpanning(" << chan << ", " << qBound(-127, s.asset.pan, 127) << ");\n"
               << "    sound_setloop(" << chan << ", " << (s.asset.loop ? s.asset.loopStart : 0) << ", "
               << (s.asset.loop ? s.asset.loopLength : 0) << ");\n"
               << "    sound_enableloop(" << chan << ", " << (s.asset.loop ? 1 : 0) << ");\n"
               << "    sound_play(" << chan << ");\n}\n\n";
    }
    for (const Music &m : music) {
        source << "void playmusic" << m.id << "(void)\n{\n"
               << "    music_play((char *)" << cString(m.sdPath) << ", "
               << qBound(0, m.asset.subsong, 255) << ");\n}\n\n";
    }
    header.flush();
    source.flush();
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
