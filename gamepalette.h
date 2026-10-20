#ifndef SIDBOX_GAMEPALETTE_H
#define SIDBOX_GAMEPALETTE_H

#include <QImage>
#include <QString>
#include <QVector>

// Host-side palette utilities. This never edits source graphics or firmware.
// SIDBOX uses absolute 8-bit palette indices: foreground and background CLUTs
// are independent, and forcing a palette must not modify the pixel index bytes.
namespace SidboxGamePalette {
// Independent firmware CLUT cycles. Stored only in .sbgm, not .pal.
struct ColourCycle {
    bool enabled = false;
    int start = 1;     // Foreground index 0 is reserved; background may use index 0.
    int length = 8;    // Number of entries, not final index.
    int speed = 5;     // LCD update frames per palette rotation (50 FPS preview).
};
// Produce a temporary CLUT; original indices, image bytes and files are unchanged.
QVector<QRgb> cyclePreview(const QVector<QRgb> &palette, const ColourCycle &cycle,
                          int steps, bool backgroundBank = false);
QVector<QRgb> readPalette(const QString &fileName, bool backgroundBank,
                         QString *error = nullptr);
bool writePal(const QString &fileName, const QVector<QRgb> &front,
              const QVector<QRgb> &back, QString *error = nullptr);
// Single 256 x 4-byte bank, for explicit FG/BG preview selection.
bool writeSinglePal(const QString &fileName, const QVector<QRgb> &bank,
                    QString *error = nullptr);

// Index-preserving CLUT construction: never alters input image pixels.
// Each distinct asset contributes one colour vote for every index it uses.
struct IndexBuildResult {
    QVector<QRgb> colours; // 256-entry CLUT for one hardware plane
    int collisions = 0; // used indices whose input colours disagree
    int severeCollisions = 0; // disagreements too large to blend safely
};
bool buildIndexPreserving(const QVector<QImage> &images, bool background,
                          IndexBuildResult *result, QString *error = nullptr);

struct BuildResult {
    QVector<QRgb> colours; // 256 entries in target bank; foreground slot 0 transparent
    QVector<QImage> indexed; // one complete indexed atlas for each input image
};

// Legacy remapping helper (kept for API compatibility, not used by the
// index-preserving Game Designer builder).
// Strict lossless palette merger. Fails rather than silently quantising colours
// when the combined assets exceed 255 foreground / 256 background entries.
bool buildLossless(const QVector<QImage> &images, bool background,
                   BuildResult *result, QString *error = nullptr);
} // namespace SidboxGamePalette

#endif
