#include "gamepalette.h"
#include "ppbcodec.h"

#include <QFile>
#include <QFileInfo>
#include <QHash>
#include <QSaveFile>
#include <QtGlobal>

namespace SidboxGamePalette {
namespace {
QVector<QRgb> blankBank()
{
    return QVector<QRgb>(256, qRgba(0, 0, 0, 0));
}
QRgb decode(const char *entry)
{
    const auto *b = reinterpret_cast<const unsigned char *>(entry);
    return qRgba(b[2], b[1], b[0], b[3]); // 0xAARRGGBB little-endian
}
void appendBank(QByteArray &bytes, const QVector<QRgb> &bank)
{
    for (int i = 0; i < 256; ++i) {
        const QRgb colour = i < bank.size() ? bank.at(i) : qRgba(0, 0, 0, 0);
        bytes.append(char(qBlue(colour)));
        bytes.append(char(qGreen(colour)));
        bytes.append(char(qRed(colour)));
        bytes.append(char(qAlpha(colour)));
    }
}
}

QVector<QRgb> readPalette(const QString &fileName, bool backgroundBank, QString *error)
{
    const QFileInfo info(fileName);
    if (!info.isFile()) {
        if (error) *error = QStringLiteral("Palette file is missing: %1").arg(fileName);
        return {};
    }
    const QString ext = info.suffix().toLower();
    if (ext == QStringLiteral("ppb")) {
        SidboxPpb::Picture picture;
        if (!SidboxPpb::read(fileName, &picture, error)) return {};
        return picture.indexed.colorTable();
    }
    if (ext == QStringLiteral("pal")) {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly) || (file.size() != 1024 && file.size() != 2048)) {
            if (error) *error = QStringLiteral("PAL must contain one or two 256 x 4-byte CLUT banks.");
            return {};
        }
        const QByteArray bytes = file.readAll();
        const int offset = backgroundBank && bytes.size() == 2048 ? 1024 : 0;
        QVector<QRgb> colours;
        colours.reserve(256);
        for (int i = 0; i < 256; ++i)
            colours.append(decode(bytes.constData() + offset + i * 4));
        return colours;
    }
    if (ext == QStringLiteral("act")) {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly) || file.size() < 768 || file.size() > 772) {
            if (error) *error = QStringLiteral("ACT palette must contain 256 RGB triples.");
            return {};
        }
        const QByteArray bytes = file.read(768);
        QVector<QRgb> colours;
        colours.reserve(256);
        for (int i = 0; i < 256; ++i) {
            const auto *p = reinterpret_cast<const unsigned char *>(bytes.constData() + i * 3);
            colours.append(qRgb(p[0], p[1], p[2]));
        }
        return colours;
    }
    QImage image(fileName);
    if (image.isNull()) {
        if (error) *error = QStringLiteral("Cannot load palette source %1").arg(fileName);
        return {};
    }
    // Do not guess a palette from arbitrary true-colour image pixels.
    if (image.format() != QImage::Format_Indexed8 || image.colorTable().isEmpty()) {
        if (error) *error = QStringLiteral("Palette image must be indexed (or use PPB/PAL/ACT).");
        return {};
    }
    QVector<QRgb> colours = image.colorTable();
    colours.resize(256);
    return colours;
}

bool writePal(const QString &fileName, const QVector<QRgb> &front,
              const QVector<QRgb> &back, QString *error)
{
    if (front.size() != 256 || back.size() != 256) {
        if (error) *error = QStringLiteral("Palette banks must each contain 256 entries.");
        return false;
    }
    QByteArray bytes;
    bytes.reserve(2048);
    appendBank(bytes, front);
    appendBank(bytes, back);
    QSaveFile output(fileName);
    if (!output.open(QIODevice::WriteOnly) || output.write(bytes) != bytes.size()
        || !output.commit()) {
        if (error) *error = QStringLiteral("Cannot write CLUT file: %1").arg(fileName);
        return false;
    }
    return true;
}

bool writeSinglePal(const QString &fileName, const QVector<QRgb> &bank, QString *error)
{
    if (bank.size() != 256) {
        if (error) *error = QStringLiteral("A single CLUT must have 256 entries.");
        return false;
    }
    QByteArray bytes;
    bytes.reserve(1024);
    appendBank(bytes, bank);
    QSaveFile output(fileName);
    if (!output.open(QIODevice::WriteOnly) || output.write(bytes) != bytes.size()
        || !output.commit()) {
        if (error) *error = QStringLiteral("Cannot write CLUT file: %1").arg(fileName);
        return false;
    }
    return true;
}

// Build one shared CLUT by absolute index. No index translation, no output PPB.
// When different assets assign colours to the same index, similar shades are
// averaged (one vote per asset), while substantially different colours keep the
// first asset's definition. The severe conflict count is surfaced to the user.
bool buildIndexPreserving(const QVector<QImage> &images, bool background,
                          IndexBuildResult *result, QString *error)
{
    if (!result || images.isEmpty()) {
        if (error) *error = QStringLiteral("No indexed resources on this plane.");
        return false;
    }
    struct Votes { qint64 r = 0, g = 0, b = 0; int count = 0; bool conflict = false; bool severe = false; QRgb reference = 0; };
    Votes votes[256];
    for (const QImage &image : images) {
        if (image.isNull() || image.format() != QImage::Format_Indexed8
            || qint64(image.width()) * image.height() > 16LL * 1024 * 1024) {
            if (error) *error = QStringLiteral("Expected a valid indexed 8-bit PPB or image.");
            return false;
        }
        const QVector<QRgb> table = image.colorTable();
        if (table.isEmpty()) {
            if (error) *error = QStringLiteral("Indexed image has no palette.");
            return false;
        }
        bool used[256] = {};
        for (int y = 0; y < image.height(); ++y) {
            const uchar *row = image.constScanLine(y);
            for (int x = 0; x < image.width(); ++x) used[row[x]] = true;
        }
        // Palette slot 0 is reserved by SIDBOX's foreground transparency.
        if (!background) used[0] = false;
        for (int i = 0; i < 256; ++i) {
            if (!used[i]) continue;
            if (i >= table.size()) {
                if (error) *error = QStringLiteral("Used index %1 is missing from image palette.").arg(i);
                return false;
            }
            const QRgb colour = table.at(i);
            Votes &v = votes[i];
            if (v.count == 0) v.reference = colour;
            else {
                const int dr = qRed(colour) - qRed(v.reference);
                const int dg = qGreen(colour) - qGreen(v.reference);
                const int db = qBlue(colour) - qBlue(v.reference);
                const int dist2 = dr * dr + dg * dg + db * db;
                if (dist2 != 0) v.conflict = true;
                // A distance > 48 in RGB space is a severe conflict.
                if (dist2 > 48 * 48) v.severe = true;
            }
            ++v.count;
            // Major conflicts do not get blended into a completely unrelated
            // shade: retain the first asset's index colour as a predictable base.
            if (!v.severe) {
                v.r += qRed(colour);
                v.g += qGreen(colour);
                v.b += qBlue(colour);
            }
        }
    }
    IndexBuildResult built;
    built.colours = QVector<QRgb>(256, qRgba(0, 0, 0, 255));
    for (int i = 0; i < 256; ++i) {
        const Votes &v = votes[i];
        if (v.count == 0) continue;
        if (v.conflict) ++built.collisions;
        if (v.severe) ++built.severeCollisions;
        built.colours[i] = v.severe ? qRgba(qRed(v.reference), qGreen(v.reference), qBlue(v.reference), 255)
            : qRgba(int(v.r / v.count), int(v.g / v.count), int(v.b / v.count), 255);
    }
    if (!background) built.colours[0] = qRgba(0, 0, 0, 0);
    *result = built;
    return true;
}

bool buildLossless(const QVector<QImage> &images, bool background,
                   BuildResult *result, QString *error)
{
    if (!result || images.isEmpty()) {
        if (error) *error = QStringLiteral("No visible image resources on this plane.");
        return false;
    }
    BuildResult generated;
    generated.colours = blankBank();
    generated.indexed.reserve(images.size());
    QHash<QRgb, int> lookup;
    int nextIndex = background ? 0 : 1;
    for (const QImage &input : images) {
        if (input.isNull() || input.width() < 1 || input.height() < 1
            || qint64(input.width()) * input.height() > 16LL * 1024 * 1024) {
            if (error) *error = QStringLiteral("Image exceeds safe editor dimensions.");
            return false;
        }
        QImage mapped(input.size(), QImage::Format_Indexed8);
        if (mapped.isNull()) {
            if (error) *error = QStringLiteral("Unable to allocate remapped image.");
            return false;
        }
        const bool sourceIndexed = input.format() == QImage::Format_Indexed8;
        const QImage argb = sourceIndexed ? QImage() : input.convertToFormat(QImage::Format_ARGB32);
        const auto table = input.colorTable();
        for (int y = 0; y < input.height(); ++y) {
            auto *dst = mapped.scanLine(y);
            const uchar *indexRow = sourceIndexed ? input.constScanLine(y) : nullptr;
            const QRgb *pixelRow = sourceIndexed ? nullptr
                : reinterpret_cast<const QRgb *>(argb.constScanLine(y));
            for (int x = 0; x < input.width(); ++x) {
                const uchar index = sourceIndexed ? indexRow[x] : 0;
                const QRgb raw = sourceIndexed
                    ? (index < table.size() ? table.at(index) : qRgba(0, 0, 0, 0))
                    : pixelRow[x];
                if (!background && ((sourceIndexed && index == 0) || qAlpha(raw) < 128)) {
                    dst[x] = 0;
                    continue;
                }
                const QRgb colour = qRgb(qRed(raw), qGreen(raw), qBlue(raw));
                const auto found = lookup.constFind(colour);
                int assigned;
                if (found != lookup.constEnd()) assigned = *found;
                else {
                    if (nextIndex >= 256) {
                        if (error) *error = QStringLiteral(
                            "The visible resources require more than %1 colours on one plane. "
                            "No files were changed. Reduce the colours or use separate palette modes."
                        ).arg(background ? 256 : 255);
                        return false;
                    }
                    assigned = nextIndex++;
                    generated.colours[assigned] = qRgba(qRed(raw), qGreen(raw), qBlue(raw), 255);
                    lookup.insert(colour, assigned);
                }
                dst[x] = uchar(assigned);
            }
        }
        mapped.setColorTable(generated.colours); // final table assigned again below
        generated.indexed.append(mapped);
    }
    if (!background) generated.colours[0] = qRgba(0, 0, 0, 0);
    for (QImage &image : generated.indexed)
        image.setColorTable(generated.colours);
    *result = generated;
    return true;
}
} // namespace SidboxGamePalette
