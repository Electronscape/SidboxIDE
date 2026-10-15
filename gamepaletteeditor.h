#ifndef SIDBOX_GAMEPALETTEEDITOR_H
#define SIDBOX_GAMEPALETTEEDITOR_H

#include <QDialog>
#include <QVector>
#include <QColor>
#include <QString>

class QComboBox;
class QLineEdit;
class QLabel;
class QToolButton;
class QPushButton;

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
    void refreshSelected();
    QVector<QRgb> &currentBank();
    const QVector<QRgb> &currentBank() const;
    bool confirmDiscard();

    QVector<QRgb> m_front;
    QVector<QRgb> m_back;
    QComboBox *m_bank = nullptr;
    QLineEdit *m_hex = nullptr;
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
};

#endif
