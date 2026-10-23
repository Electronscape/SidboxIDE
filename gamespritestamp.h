#ifndef SIDBOX_GAME_SPRITE_STAMP_H
#define SIDBOX_GAME_SPRITE_STAMP_H

#include <QImage>
#include <QJsonArray>
#include <QJsonObject>
#include <QVector>
#include <QString>
#include <QtGlobal>

// Game Object Sprite Stamps are IDE-only arrangements of indexed PPB 8x8 cells.
// 0-based tile IDs; -1 = transparent empty cell. Bits 16/17 are per-cell X/Y flips.
// At export the arrangement becomes a C lookup table of cell IDs and flips.
// The STM32 reads the original PPB pixels and draws those cells directly.
struct SidboxSpriteStamp {
    QString sourcePath; // original project-relative PPB sheet; no generated PPB
    int width = 2, height = 2; // units of 8x8 pixels, 1..16 each
    QVector<int> cells; // encoded tile IDs + flips, row major
    bool active() const { return !sourcePath.isEmpty(); }

    static constexpr int cellPixels = 8;
    static constexpr int maxDimension = 16;
    static constexpr int tileMask = 0xFFFF;
    static constexpr int flipX = 0x10000;
    static constexpr int flipY = 0x20000;

    static SidboxSpriteStamp fromJson(const QJsonObject &json) {
        SidboxSpriteStamp stamp;
        stamp.sourcePath = json.value(QStringLiteral("source")).toString();
        stamp.width = qBound(1, json.value(QStringLiteral("width")).toInt(2), maxDimension);
        stamp.height = qBound(1, json.value(QStringLiteral("height")).toInt(2), maxDimension);
        const QJsonArray encoded = json.value(QStringLiteral("cells")).toArray();
        stamp.cells.fill(-1, stamp.width * stamp.height);
        for (int i = 0; i < stamp.cells.size() && i < encoded.size(); ++i) {
            const int code = encoded.at(i).toInt(-1);
            stamp.cells[i] = code < 0 ? -1 : (code & (tileMask | flipX | flipY));
        }
        return stamp;
    }
    QJsonObject toJson() const {
        QJsonObject result;
        if (!active()) return result;
        result.insert(QStringLiteral("source"), sourcePath);
        result.insert(QStringLiteral("width"), width);
        result.insert(QStringLiteral("height"), height);
        QJsonArray encoded;
        for (int i = 0; i < width * height; ++i)
            encoded.append(i < cells.size() ? cells.at(i) : -1);
        result.insert(QStringLiteral("cells"), encoded);
        return result;
    }
    void resize(int w, int h) {
        w = qBound(1, w, maxDimension); h = qBound(1, h, maxDimension);
        QVector<int> next(w * h, -1);
        for (int y = 0; y < qMin(h, height); ++y)
            for (int x = 0; x < qMin(w, width); ++x)
                if (y * width + x < cells.size()) next[y * w + x] = cells.at(y * width + x);
        width = w; height = h; cells = next;
    }
    void mirror(bool xAxis) {
        QVector<int> next(width * height, -1);
        for (int y = 0; y < height; ++y)
            for (int x = 0; x < width; ++x) {
                const int from = y * width + x;
                if (from >= cells.size() || cells.at(from) < 0) continue;
                const int to = xAxis ? y * width + (width - 1 - x)
                                     : (height - 1 - y) * width + x;
                next[to] = cells.at(from) ^ (xAxis ? flipX : flipY);
            }
        cells = next;
    }
    QImage compose(const QImage &source, QString *error = nullptr) const {
        if (source.format() != QImage::Format_Indexed8 || source.isNull() ||
            source.width() % cellPixels || source.height() % cellPixels) {
            if (error) *error = QStringLiteral("Source PPB must be indexed and have 8x8-aligned dimensions.");
            return {};
        }
        if (width < 1 || height < 1 || width > maxDimension || height > maxDimension ||
            cells.size() != width * height) {
            if (error) *error = QStringLiteral("Invalid sprite stamp dimensions or cells.");
            return {};
        }
        const int sourceCols = source.width() / cellPixels;
        const int sourceCount = sourceCols * (source.height() / cellPixels);
        QImage output(width * cellPixels, height * cellPixels, QImage::Format_Indexed8);
        if (output.isNull()) {
            if (error) *error = QStringLiteral("Cannot allocate sprite stamp output.");
            return {};
        }
        QVector<QRgb> palette = source.colorTable();
        if (palette.size() < 256) palette.resize(256);
        // Foreground BOBs use transparent pixel INDEX 0, regardless of source alpha.
        palette[0] = qRgba(qRed(palette[0]), qGreen(palette[0]), qBlue(palette[0]), 0);
        for (int i = 1; i < palette.size(); ++i)
            palette[i] = qRgba(qRed(palette[i]), qGreen(palette[i]), qBlue(palette[i]), 255);
        output.setColorTable(palette);
        output.fill(0);
        for (int cell = 0; cell < cells.size(); ++cell) {
            const int encoded = cells.at(cell);
            if (encoded < 0) continue;
            const int index = encoded & tileMask;
            if (index >= sourceCount) {
                if (error) *error = QStringLiteral("Sprite stamp refers to an out-of-range source tile.");
                return {};
            }
            const int sx = (index % sourceCols) * cellPixels;
            const int sy = (index / sourceCols) * cellPixels;
            const int dx = (cell % width) * cellPixels;
            const int dy = (cell / width) * cellPixels;
            for (int py = 0; py < cellPixels; ++py) {
                const int ry = (encoded & flipY) ? cellPixels - 1 - py : py;
                const uchar *src = source.constScanLine(sy + ry);
                uchar *dst = output.scanLine(dy + py);
                for (int px = 0; px < cellPixels; ++px) {
                    const int rx = (encoded & flipX) ? cellPixels - 1 - px : px;
                    dst[dx + px] = src[sx + rx];
                }
            }
        }
        return output;
    }
};

#endif
