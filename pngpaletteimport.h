#ifndef CODERGIRL_PNG_PALETTE_IMPORT_H
#define CODERGIRL_PNG_PALETTE_IMPORT_H

#include "ppbcodec.h"
#include <QDialog>
#include <QVector>

class QComboBox;
class QSpinBox;
class QCheckBox;
class QLabel;
class QPushButton;
class QListWidget;
class QTimer;
class QWidget;
class PngPreviewView;

// Host-only importer: 8-bit PPB indices are absolute CLUT positions. Index 0
// remains transparent; colours outside the selected range are never modified.
namespace SidboxPngImport {
enum class Dither { None, Ordered, FloydSteinberg, Noise };
struct Options {
    int first = 1;
    int last = 255;
    bool buildColours = true;     // false = reuse existing range unchanged
    bool startFresh = false;      // start with blank CLUT, not project palette
    bool keyColourEnabled = false; // map this exact RGB colour to transparent index 0
    QRgb keyColour = qRgb(255, 0, 255);
    QVector<QRgb> protectedColours; // exact opaque RGB colours reserved in output CLUT
    Dither dither = Dither::None;
};
struct Result {
    SidboxPpb::Picture picture;
    QVector<QRgb> palette;
    int paletteColours = 0;
};
bool convert(const QImage &source, const QVector<QRgb> &current,
             const Options &options, Result *result, QString *error = nullptr);
}

class PngPaletteImportDialog : public QDialog {
public:
    PngPaletteImportDialog(const QImage &source, const QVector<QRgb> &foreground,
                           const QVector<QRgb> &background, const QString &initialKind, bool dualPlane,
                           QWidget *parent = nullptr);
    SidboxPngImport::Options options() const;
    QVector<QRgb> basePalette() const;
    QString destinationKind() const;
    QString palettePlane() const;

private:
    void updateControls();
    void updatePreview();
    void queuePreview();
    void fitPreviews();
    void setPreviewZoom(double factor);
    void updateZoomLabel();
    QImage m_source;
    bool m_dualPlane = false;
    QVector<QRgb> m_front, m_back;
    QComboBox *m_destination = nullptr;
    QComboBox *m_bank = nullptr;
    QComboBox *m_mode = nullptr;
    QComboBox *m_dither = nullptr;
    QSpinBox *m_first = nullptr;
    QSpinBox *m_last = nullptr;
    QCheckBox *m_fresh = nullptr;
    QCheckBox *m_transparentKey = nullptr;
    QLabel *m_transparentColourPreview = nullptr;
    QListWidget *m_sourceColours = nullptr;
    QLabel *m_sourceColourNote = nullptr;
    QRgb m_keyColour = qRgb(255, 0, 255);
    QVector<QRgb> m_protectedColours;
    bool m_sourceColoursLimited = false;
    PngPreviewView *m_before = nullptr;
    PngPreviewView *m_after = nullptr;
    QLabel *m_zoomReadout = nullptr;
    QTimer *m_previewTimer = nullptr;
    bool m_fitPreview = true;
    double m_zoomFactor = 1.0;
    QLabel *m_status = nullptr;
    QLabel *m_swatch = nullptr;
    QPushButton *m_accept = nullptr;

    void selectTransparentColour(QRgb colour);
    void toggleProtectedColour(QRgb colour);
    void updateProtectedColourUi();
    void updateTransparentColourUi();
};

#endif
