#include "ppbcodec.h"

#include <QFile>
#include <QDir>
#include <QByteArray>
#include <QVector>
#include <QFileInfo>
#include <QHash>
#include <QSaveFile>
#include <QSet>
#include <QTextStream>
#include <QtGlobal>
#include <cstring>
#include <limits>
#include <algorithm>
#include <array>
#include <utility>

namespace SidboxPpb {
namespace {
constexpr qint64 HeaderLength = 16;
constexpr qint64 PaletteLength = 256 * 4;
constexpr qint64 DataOffset = HeaderLength + PaletteLength;
constexpr qint64 MaxPixels = 16 * 1024 * 1024; // editor memory/safety guard

void errorOut(QString *out, const QString &message) { if (out) *out = message; }
quint16 big16(const char *p) {
    return (quint16(quint8(p[0])) << 8) | quint8(p[1]);
}
quint32 big32(const char *p) {
    return (quint32(quint8(p[0])) << 24) | (quint32(quint8(p[1])) << 16)
           | (quint32(quint8(p[2])) << 8) | quint8(p[3]);
}
void append16(QByteArray &b, quint16 n) {
    b.append(char((n >> 8) & 255)); b.append(char(n & 255));
}
void append32(QByteArray &b, quint32 n) {
    b.append(char((n >> 24) & 255)); b.append(char((n >> 16) & 255));
    b.append(char((n >> 8) & 255)); b.append(char(n & 255));
}

bool checkSize(int w, int h, QString *error)
{
    if (w < 1 || h < 1 || w > 65535 || h > 65535 || qint64(w) * h > MaxPixels) {
        errorOut(error, QStringLiteral("Image dimensions exceed the editor's safe PPB limit (16M pixels)."));
        return false;
    }
    return true;
}

int colourDistance(QRgb a, QRgb b)
{
    const int dr = qRed(a) - qRed(b);
    const int dg = qGreen(a) - qGreen(b);
    const int db = qBlue(a) - qBlue(b);
    return 3 * dr * dr + 6 * dg * dg + 2 * db * db;
}

int closest(const QVector<QRgb> &colours, QRgb colour)
{
    int result = 1, best = std::numeric_limits<int>::max();
    for (int i = 1; i < colours.size(); ++i) {
        const int distance = colourDistance(colours.at(i), colour);
        if (distance < best) { best = distance; result = i; }
    }
    return result;
}

bool atomicWrite(const QString &path, const QByteArray &bytes, QString *error)
{
    QSaveFile output(path);
    if (!output.open(QIODevice::WriteOnly)) {
        errorOut(error, QStringLiteral("Cannot open %1: %2").arg(path, output.errorString()));
        return false;
    }
    if (output.write(bytes) != bytes.size() || !output.commit()) {
        errorOut(error, QStringLiteral("Cannot write %1: %2").arg(path, output.errorString()));
        return false;
    }
    return true;
}
}

bool read(const QString &path, Picture *picture, QString *error)
{
    if (!picture) return false;
    picture->indexed = QImage();
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        errorOut(error, QStringLiteral("Unable to open PPB: %1").arg(file.errorString()));
        return false;
    }
    if (file.size() < DataOffset || file.size() > DataOffset + MaxPixels) {
        errorOut(error, QStringLiteral("Invalid or oversized PPB file."));
        return false;
    }
    const QByteArray b = file.readAll();
    if (b.size() < DataOffset) { errorOut(error, QStringLiteral("Truncated PPB header.")); return false; }
    const int width = big16(b.constData() + 1);
    const int height = big16(b.constData() + 3);
    const quint32 length = big32(b.constData() + 5);
    if (!checkSize(width, height, error)) return false;
    if (length != quint32(qint64(width) * height)
        || b.size() != DataOffset + qint64(length)) {
        errorOut(error, QStringLiteral("PPB pixel length does not match width × height."));
        return false;
    }
    QImage image(width, height, QImage::Format_Indexed8);
    if (image.isNull()) { errorOut(error, QStringLiteral("Unable to allocate PPB preview.")); return false; }
    QVector<QRgb> palette;
    palette.reserve(256);
    for (int i = 0; i < 256; ++i) {
        const unsigned char *entry = reinterpret_cast<const unsigned char *>(
            b.constData() + HeaderLength + i * 4);
        // PPB palette entries use little-endian 0xAARRGGBB (BGRA byte order).
        palette.append(qRgba(entry[2], entry[1], entry[0], entry[3]));
    }
    image.setColorTable(palette);
    const char *pixels = b.constData() + DataOffset;
    for (int y = 0; y < height; ++y)
        std::memcpy(image.scanLine(y), pixels + qint64(y) * width, size_t(width));
    picture->indexed = image;
    return true;
}

bool fromImage(const QImage &image, Picture *picture, QString *error)
{
    if (!picture) return false;
    picture->indexed = QImage();
    if (image.isNull() || !checkSize(image.width(), image.height(), error)) return false;
    const QImage argb = image.convertToFormat(QImage::Format_ARGB32);
    QVector<QRgb> palette;
    palette.reserve(256);
    palette.append(qRgba(0, 0, 0, 0)); // Index 0 is ALWAYS transparent on SIDBOX.
    QHash<QRgb, int> indexes;
    bool tooManyColours = false;
    for (int y = 0; y < argb.height() && !tooManyColours; ++y) {
        const QRgb *row = reinterpret_cast<const QRgb *>(argb.constScanLine(y));
        for (int x = 0; x < argb.width(); ++x) {
            if (qAlpha(row[x]) < 128) continue;
            const QRgb key = qRgb(qRed(row[x]), qGreen(row[x]), qBlue(row[x]));
            if (!indexes.contains(key)) {
                if (palette.size() == 256) { tooManyColours = true; break; }
                indexes.insert(key, palette.size());
                palette.append(key);
            }
        }
    }
    // A small (32K bin) weighted median-cut quantiser. Qt's general-purpose
    // RGB -> Indexed8 conversion is particularly expensive for large PNGs.
    // Group pixels by their high 5 bits, then split *weighted* colour boxes.
    // Runtime is bounded by 32768 bins, not pixels × 256 palette colours.
    std::array<quint8, 32768> binToIndex{};
    if (tooManyColours) {
        struct Bin {
            quint32 count = 0;
            quint64 rsum = 0, gsum = 0, bsum = 0;
        };
        QVector<Bin> histogram(32768);
        for (int y = 0; y < argb.height(); ++y) {
            const QRgb *row = reinterpret_cast<const QRgb *>(argb.constScanLine(y));
            for (int x = 0; x < argb.width(); ++x) {
                const QRgb pixel = row[x];
                if (qAlpha(pixel) < 128) continue;
                const int bin = ((qRed(pixel) >> 3) << 10)
                              | ((qGreen(pixel) >> 3) << 5) | (qBlue(pixel) >> 3);
                auto &entry = histogram[bin];
                ++entry.count;
                entry.rsum += qRed(pixel);
                entry.gsum += qGreen(pixel);
                entry.bsum += qBlue(pixel);
            }
        }
        QVector<int> order;
        order.reserve(32768);
        for (int bin = 0; bin < 32768; ++bin)
            if (histogram[bin].count) order.append(bin);
        struct Box {
            int start = 0, end = 0;
            int minimum[3] = {0, 0, 0};
            int maximum[3] = {0, 0, 0};
            quint64 count = 0;
        };
        auto channel = [](int bin, int axis) -> int {
            return axis == 0 ? (bin >> 10) : axis == 1 ? ((bin >> 5) & 31) : (bin & 31);
        };
        auto measure = [&](Box &box) {
            for (int c = 0; c < 3; ++c) { box.minimum[c] = 31; box.maximum[c] = 0; }
            box.count = 0;
            for (int i = box.start; i < box.end; ++i) {
                const int bin = order.at(i);
                box.count += histogram.at(bin).count;
                for (int c = 0; c < 3; ++c) {
                    const int component = channel(bin, c);
                    box.minimum[c] = qMin(box.minimum[c], component);
                    box.maximum[c] = qMax(box.maximum[c], component);
                }
            }
        };
        QVector<Box> boxes;
        Box initial;
        initial.end = order.size();
        measure(initial);
        boxes.append(initial);
        while (boxes.size() < 255) {
            int bestBox = -1, bestAxis = 0;
            quint64 bestScore = 0;
            for (int i = 0; i < boxes.size(); ++i) {
                const Box &box = boxes.at(i);
                if (box.end - box.start < 2) continue;
                int axis = 0, range = box.maximum[0] - box.minimum[0];
                for (int c = 1; c < 3; ++c) {
                    const int span = box.maximum[c] - box.minimum[c];
                    if (span > range) { range = span; axis = c; }
                }
                const quint64 score = quint64(range) * box.count;
                if (score > bestScore) { bestScore = score; bestBox = i; bestAxis = axis; }
            }
            if (bestBox < 0) break;
            Box original = boxes.at(bestBox);
            std::sort(order.begin() + original.start, order.begin() + original.end,
                      [&](int a, int b) { return channel(a, bestAxis) < channel(b, bestAxis); });
            quint64 accumulated = 0;
            int split = original.start + 1;
            for (int i = original.start; i < original.end - 1; ++i) {
                accumulated += histogram.at(order.at(i)).count;
                if (accumulated >= original.count / 2) { split = i + 1; break; }
            }
            Box left = original, right = original;
            left.end = split;
            right.start = split;
            measure(left);
            measure(right);
            boxes[bestBox] = left;
            boxes.append(right);
        }
        palette.clear();
        palette.append(qRgba(0, 0, 0, 0));
        for (const Box &box : std::as_const(boxes)) {
            quint64 red = 0, green = 0, blue = 0;
            for (int i = box.start; i < box.end; ++i) {
                const Bin &bin = histogram.at(order.at(i));
                red += bin.rsum; green += bin.gsum; blue += bin.bsum;
            }
            const quint64 divisor = qMax(quint64(1), box.count);
            palette.append(qRgb(int(red / divisor), int(green / divisor), int(blue / divisor)));
        }
        // Look up nearest palette colour ONCE for each populated colour bin.
        // Pixels subsequently use a constant-time lookup.
        for (int bin : std::as_const(order)) {
            const Bin &value = histogram.at(bin);
            const QRgb average = qRgb(int(value.rsum / value.count),
                                     int(value.gsum / value.count),
                                     int(value.bsum / value.count));
            binToIndex[bin] = quint8(closest(palette, average));
        }
    }
    QImage indexed(argb.size(), QImage::Format_Indexed8);
    if (indexed.isNull()) { errorOut(error, QStringLiteral("Unable to allocate converted PPB.")); return false; }
    for (int y = 0; y < argb.height(); ++y) {
        const QRgb *src = reinterpret_cast<const QRgb *>(argb.constScanLine(y));
        uchar *dest = indexed.scanLine(y);
        for (int x = 0; x < argb.width(); ++x) {
            if (qAlpha(src[x]) < 128) dest[x] = 0;
            else if (tooManyColours) {
                const int bin = ((qRed(src[x]) >> 3) << 10)
                              | ((qGreen(src[x]) >> 3) << 5) | (qBlue(src[x]) >> 3);
                dest[x] = binToIndex[bin];
            }
            else dest[x] = uchar(indexes.value(qRgb(qRed(src[x]), qGreen(src[x]), qBlue(src[x])), 0));
        }
    }
    while (palette.size() < 256) palette.append(qRgba(0, 0, 0, 255));
    indexed.setColorTable(palette);
    picture->indexed = indexed;
    return true;
}

bool write(const QString &path, const Picture &picture, QString *error)
{
    if (!picture.isValid() || !checkSize(picture.indexed.width(), picture.indexed.height(), error)) return false;
    const QImage &image = picture.indexed;
    QByteArray bytes;
    bytes.reserve(qsizetype(DataOffset + qint64(image.width()) * image.height()));
    bytes.append(char(0)); // config
    append16(bytes, quint16(image.width()));
    append16(bytes, quint16(image.height()));
    append32(bytes, quint32(qint64(image.width()) * image.height()));
    bytes.append(QByteArray(7, char(0)));
    const auto palette = image.colorTable();
    for (int i = 0; i < 256; ++i) {
        const QRgb rgba = i < palette.size() ? palette.at(i) : qRgba(0, 0, 0, 255);
        bytes.append(char(qBlue(rgba)));
        bytes.append(char(qGreen(rgba)));
        bytes.append(char(qRed(rgba)));
        bytes.append(char(qAlpha(rgba)));
    }
    for (int y = 0; y < image.height(); ++y)
        bytes.append(reinterpret_cast<const char *>(image.constScanLine(y)), image.width());
    return atomicWrite(path, bytes, error);
}

QString identifier(const QString &candidate)
{
    QString result;
    for (const QChar c : candidate) result.append(c.isLetterOrNumber() && c.unicode() < 128 ? c : QLatin1Char('_'));
    if (result.isEmpty()) result = QStringLiteral("asset");
    if (!result.at(0).isLetter() && result.at(0) != QLatin1Char('_')) result.prepend(QLatin1Char('_'));
    // Avoid C language keywords and implementation-reserved leading names.
    if (result.startsWith(QStringLiteral("__"))) result.prepend(QStringLiteral("asset"));
    static const QSet<QString> keywords = {QStringLiteral("auto"), QStringLiteral("break"), QStringLiteral("case"),
        QStringLiteral("char"), QStringLiteral("const"), QStringLiteral("continue"), QStringLiteral("default"),
        QStringLiteral("do"), QStringLiteral("double"), QStringLiteral("else"), QStringLiteral("enum"),
        QStringLiteral("extern"), QStringLiteral("float"), QStringLiteral("for"), QStringLiteral("goto"),
        QStringLiteral("if"), QStringLiteral("inline"), QStringLiteral("int"), QStringLiteral("long"),
        QStringLiteral("register"), QStringLiteral("restrict"), QStringLiteral("return"),
        QStringLiteral("short"), QStringLiteral("signed"), QStringLiteral("sizeof"), QStringLiteral("static"),
        QStringLiteral("struct"), QStringLiteral("switch"), QStringLiteral("typedef"), QStringLiteral("union"),
        QStringLiteral("unsigned"), QStringLiteral("void"), QStringLiteral("volatile"), QStringLiteral("while")};
    if (keywords.contains(result)) result.prepend(QStringLiteral("asset_"));
    return result;
}

bool exportC(const QString &cPath, const QString &symbol, const Picture &picture, QString *error)
{
    if (!picture.isValid()) { errorOut(error, QStringLiteral("No valid indexed asset.")); return false; }
    const QImage &img = picture.indexed;
    if (qint64(img.width()) * img.height() > 2 * 1024 * 1024) {
        errorOut(error, QStringLiteral("Embedded C exports are limited to 2M pixels. "
                                       "Use external PPB for large backgrounds."));
        return false;
    }
    const QString id = identifier(symbol);
    const QFileInfo file(cPath);
    const QString headerPath = file.dir().filePath(file.completeBaseName() + QStringLiteral(".h"));
    const QString headerName = QFileInfo(headerPath).fileName();
    QString guard = identifier(file.completeBaseName()).toUpper() + QStringLiteral("_GAME_RESOURCE_H");
    if (guard.startsWith(QLatin1Char('_'))) guard.prepend(QStringLiteral("SB"));
    QByteArray header;
    {
        QTextStream out(&header, QIODevice::WriteOnly);
        out << "/* Generated by CoderGirl Game Designer. 8-bit indexed pixels, row-major. */\n";
        out << "#ifndef " << guard << "\n#define " << guard << "\n";
        out << "#include <stdint.h>\n";
        out << "#define " << id.toUpper() << "_WIDTH " << img.width() << "\n";
        out << "#define " << id.toUpper() << "_HEIGHT " << img.height() << "\n";
        out << "extern const uint8_t " << id << "_pixels[" << qint64(img.width()) * img.height() << "];\n";
        out << "extern uint32_t " << id << "_palette[256];\n";
        out << "#endif\n";
    }
    QByteArray source;
    {
        QTextStream out(&source, QIODevice::WriteOnly);
        out << "/* Generated by CoderGirl Game Designer; do not hand-edit.\n";
        out << " * Pixel indices are row-major (atlas stride = WIDTH).\n";
        out << " * Palette entries are 0xAARRGGBB; index 0 is transparent.\n";
        out << " * These are EMBEDDED data: the V1 app includes the full uncompressed pixels.\n";
        out << " */\n#include \"" << headerName << "\"\n\n";
        out << "const uint8_t " << id << "_pixels[] __attribute__((aligned(32))) = {\n";
        int n = 0;
        for (int y = 0; y < img.height(); ++y) {
            const uchar *row = img.constScanLine(y);
            for (int x = 0; x < img.width(); ++x) {
                if ((n % 16) == 0) out << "    ";
                out << int(row[x]);
                if (n != qint64(img.width()) * img.height() - 1) out << ',';
                ++n;
                out << (((n % 16) == 0) ? "\n" : " ");
            }
        }
        if ((n % 16) != 0) out << "\n";
        out << "};\n\nuint32_t " << id << "_palette[256] __attribute__((aligned(32))) = {\n";
        const auto table = img.colorTable();
        for (int i = 0; i < 256; ++i) {
            const QRgb entry = i < table.size() ? table.at(i) : qRgba(0, 0, 0, 255);
            out << ((i % 8) == 0 ? "    " : " ")
                << QStringLiteral("0x%1").arg(qulonglong(entry), 8, 16, QLatin1Char('0')).toUpper()
                << (i == 255 ? "" : ",") << (((i % 8) == 7) ? "\n" : " ");
        }
        out << "};\n";
    }
    // Save header before source. Warn in UI and do not silently clobber files.
    if (!atomicWrite(headerPath, header, error)) return false;
    return atomicWrite(cPath, source, error);
}
}
