#ifndef CODERGIRL_PPB_CODEC_H
#define CODERGIRL_PPB_CODEC_H

#include <QImage>
#include <QString>

// Host-side PPB utility for V1 Gaming. Keeps PPB parsing and export code out
// of MainWindow and GameDesigner. No changes to the SIDBOX firmware/SDK.
namespace SidboxPpb {
struct Picture {
    QImage indexed; // Format_Indexed8; palette BGRA in PPB, ARGB in Qt.
    bool isValid() const { return !indexed.isNull() && indexed.format() == QImage::Format_Indexed8; }
};

bool read(const QString &path, Picture *picture, QString *error = nullptr);
bool fromImage(const QImage &image, Picture *picture, QString *error = nullptr);
bool write(const QString &path, const Picture &picture, QString *error = nullptr);
bool exportC(const QString &cPath, const QString &symbol,
             const Picture &picture, QString *error = nullptr);
QString identifier(const QString &candidate);
}

#endif // CODERGIRL_PPB_CODEC_H
