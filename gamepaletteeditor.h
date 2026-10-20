#ifndef SIDBOX_GAMEPALETTEEDITOR_H
#define SIDBOX_GAMEPALETTEEDITOR_H

#include <QDialog>
#include <QVector>
#include <QColor>
#include <QString>
#include <QElapsedTimer>
#include "gamepalette.h"

class QComboBox;
class QLineEdit;
class QLabel;
class QToolButton;
class QPushButton;
class QSpinBox;
class QSlider;
class QCheckBox;
class QTimer;

// Host-side editor for SIDBOX's two 256-colour ARGB CLUT banks.
// This never rewrites PPBs or changes any indexed pixel data.
class SidboxGamePaletteEditor final : public QDialog
{
public:
    explicit SidboxGamePaletteEditor(QWidget *parent = nullptr);
    void setBank(bool background);
    bool loadFromFile(const QString &path);
    QString savedPath() const { return m_savedPath; }
    bool currentBankIsBackground() const;
    void setColourCycles(const SidboxGamePalette::ColourCycle &front,
                         const SidboxGamePalette::ColourCycle &back);
    SidboxGamePalette::ColourCycle foregroundColourCycle() const { return m_frontCycle; }
    SidboxGamePalette::ColourCycle backgroundColourCycle() const { return m_backCycle; }

protected:
    void reject() override;

private:
    void importPalette();
    void exportPalette();
    void savePalette();
    void selectIndex(int index);
    void chooseColour();
    void applyHexColour();
    void refreshGrid();
    void refreshCycleControls();
    SidboxGamePalette::ColourCycle &currentCycle();
    const SidboxGamePalette::ColourCycle &currentCycle() const;
    void refreshSelected();
    QVector<QRgb> &currentBank();
    const QVector<QRgb> &currentBank() const;
    bool confirmDiscard();

    QVector<QRgb> m_front;
    QVector<QRgb> m_back;
    QComboBox *m_bank = nullptr;
    QLineEdit *m_hex = nullptr;
    QSlider *m_alphaSlider = nullptr;
    QLabel *m_alphaValue = nullptr;
    QLabel *m_alphaSwatch = nullptr;
    QLabel *m_indexLabel = nullptr;
    QLabel *m_status = nullptr;
    QVector<QToolButton *> m_cells;
    int m_index = 0;
    bool m_modified = false;
    QString m_sourcePath;
    QString m_savedPath;
    QPushButton *m_saveButton = nullptr;
    bool m_sourceIsSingleBank = false;
    bool m_sourceBankIsBackground = false;
    SidboxGamePalette::ColourCycle m_frontCycle;
    SidboxGamePalette::ColourCycle m_backCycle;
    QCheckBox *m_cycleEnabled = nullptr;
    QCheckBox *m_cyclePreview = nullptr;
    QSpinBox *m_cycleStart = nullptr;
    QSpinBox *m_cycleLength = nullptr;
    QSpinBox *m_cycleSpeed = nullptr;
    QTimer *m_cycleTimer = nullptr;
    QElapsedTimer m_cycleClock;
    int m_cyclePreviewLastPhase = -1;
};

#endif
