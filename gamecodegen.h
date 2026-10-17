#ifndef SIDBOX_GAME_CODEGEN_H
#define SIDBOX_GAME_CODEGEN_H

#include <QString>
#include <QStringList>
#include <QVector>

// Stand-alone QtCore generator: deliberately independent of MainWindow and
// of Game Designer's widget classes. It never modifies user-authored C files.
namespace SidboxGameCodeGen {
struct Asset {
    QString name;
    QString kind; // sprite, tileatlas (resource only), background, palette, sound, music
    QString plane;
    QString backgroundMode = QStringLiteral("sprite");
    QString absolutePath;
    int x = 0, y = 0, scale = 100, cellWidth = 0, cellHeight = 0, frame = 0;
    int channel = 0, frequency = 22050, volume = 255, pan = 0;
    bool worldManaged = false; // drawn by gameworlditems, not by drawworld()
    bool loop = false;
    int loopStart = 0, loopLength = 0, subsong = 0;
};
struct Request {
    QString designDirectory;
    QString outputDirectory; // typically <project>/gameassets
    QVector<Asset> assets;
    QString foregroundPalette;
    QString backgroundPalette;
    bool dualPlane = false;
    bool embedPixels = false;
};
struct Result {
    bool ok = false;
    QString error;
    QStringList warnings;
    QStringList files;
    qint64 embeddedBytes = 0;
};
Result generate(const Request &request);
}
#endif
