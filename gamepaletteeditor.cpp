#include "gamepaletteeditor.h"
#include "gamepalette.h"

#include <QComboBox>
#include <QColorDialog>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPainter>
#include <QDir>
#include <QPushButton>
#include <QRegularExpression>
#include <QToolButton>
#include <QVBoxLayout>

namespace {
QString argbHex(QRgb colour)
{
    return QStringLiteral("0x%1").arg(qulonglong(quint32(colour)), 8, 16, QLatin1Char('0')).toUpper()
        .replace(QStringLiteral("0X"), QStringLiteral("0x"));
}

QString rgbHex(QRgb colour)
{
    return QStringLiteral("0x%1").arg(qulonglong(quint32(colour) & 0x00FFFFFFu), 6, 16, QLatin1Char('0')).toUpper()
        .replace(QStringLiteral("0X"), QStringLiteral("0x"));
}

QIcon colourIcon(QRgb colour)
{
    QPixmap tile(18, 18);
    tile.fill(Qt::transparent);
    QPainter p(&tile);
    p.fillRect(0, 0, 18, 18, QColor(205, 205, 205));
    p.fillRect(0, 0, 9, 9, QColor(245, 245, 245));
    p.fillRect(9, 9, 9, 9, QColor(245, 245, 245));
    p.fillRect(tile.rect(), QColor::fromRgba(colour));
    return QIcon(tile);
}
}

SidboxGamePaletteEditor::SidboxGamePaletteEditor(QWidget *parent)
    : QDialog(parent), m_front(256, qRgba(0, 0, 0, 255)),
      m_back(256, qRgba(0, 0, 0, 255))
{
    m_front[0] = qRgba(0, 0, 0, 0);
    setWindowTitle(tr("SIDBOX Palette Editor"));
    setMinimumSize(460, 590);
    resize(510, 650);
    setStyleSheet(QStringLiteral(
        "QPushButton, QToolButton, QComboBox, QLineEdit { border-radius:0px; } "
        "QComboBox { border:1px solid palette(mid); background:palette(base); "
        "color:palette(text); padding:3px 23px 3px 5px; } "
        "QComboBox::drop-down { width:19px; border-left:1px solid palette(mid); "
        "border-radius:0px; }"));
    auto *root = new QVBoxLayout(this);
    auto *heading = new QLabel(tr("Edit 256 colours per palette bank. "
                                   "Foreground colours may be transparent; background colours are always opaque. "
                                   "PPB image pixels are never modified."), this);
    heading->setWordWrap(true);
    root->addWidget(heading);

    auto *top = new QHBoxLayout;
    top->addWidget(new QLabel(tr("Bank:"), this));
    m_bank = new QComboBox(this);
    m_bank->addItem(tr("Foreground (transparency supported)"));
    m_bank->addItem(tr("Background (no transparency)"));
    top->addWidget(m_bank, 1);
    root->addLayout(top);

    auto *grid = new QGridLayout;
    grid->setSpacing(2);
    grid->setContentsMargins(1, 2, 1, 2);
    for (int i = 0; i < 256; ++i) {
        auto *cell = new QToolButton(this);
        cell->setFixedSize(25, 25);
        cell->setIconSize(QSize(18, 18));
        cell->setAutoRaise(false);
        cell->setToolTip(tr("Index %1").arg(i));
        grid->addWidget(cell, i / 16, i % 16);
        connect(cell, &QToolButton::clicked, this, [this, i]() { selectIndex(i); });
        m_cells.append(cell);
    }
    root->addLayout(grid);
    auto *colourRow = new QHBoxLayout;
    m_indexLabel = new QLabel(this);
    colourRow->addWidget(m_indexLabel);
    m_hex = new QLineEdit(this);
    m_hex->setMaximumWidth(130);
    m_hex->setMaxLength(10);
    m_hex->setToolTip(tr("Foreground: 0xAARRGGBB. Background: 0xRRGGBB (always opaque)."));
    colourRow->addWidget(m_hex);
    auto *pick = new QPushButton(tr("Pick Colour..."), this);
    colourRow->addWidget(pick);
    colourRow->addStretch();
    root->addLayout(colourRow);
    m_status = new QLabel(tr("A full SIDBOX .pal contains both banks (2048 bytes)."), this);
    m_status->setWordWrap(true);
    root->addWidget(m_status);

    auto *actions = new QHBoxLayout;
    auto *import = new QPushButton(tr("Import .pal..."), this);
    auto *saveAs = new QPushButton(tr("Save As .pal..."), this);
    m_saveButton = new QPushButton(tr("Save"), this);
    m_saveButton->setEnabled(false);
    m_saveButton->setToolTip(tr("Save over the loaded palette file, keeping its original size."));
    auto *close = new QPushButton(tr("Close"), this);
    actions->addWidget(import);
    actions->addWidget(saveAs);
    actions->addStretch();
    actions->addWidget(m_saveButton);
    actions->addWidget(close);
    root->addLayout(actions);

    connect(import, &QPushButton::clicked, this, [this]() { importPalette(); });
    connect(saveAs, &QPushButton::clicked, this, [this]() { exportPalette(); });
    connect(m_saveButton, &QPushButton::clicked, this, [this]() { savePalette(); });
    connect(close, &QPushButton::clicked, this, &QDialog::reject);
    connect(m_bank, qOverload<int>(&QComboBox::currentIndexChanged), this,
            [this](int) { refreshGrid(); });
    connect(pick, &QPushButton::clicked, this, [this]() { chooseColour(); });
    connect(m_hex, &QLineEdit::returnPressed, this, [this]() { applyHexColour(); });
    connect(m_hex, &QLineEdit::editingFinished, this, [this]() { applyHexColour(); });
    refreshGrid();
}

void SidboxGamePaletteEditor::setBank(bool background)
{
    m_bank->setCurrentIndex(background ? 1 : 0);
}

bool SidboxGamePaletteEditor::currentBankIsBackground() const
{
    return m_bank->currentIndex() == 1;
}

QVector<QRgb> &SidboxGamePaletteEditor::currentBank()
{
    return currentBankIsBackground() ? m_back : m_front;
}

const QVector<QRgb> &SidboxGamePaletteEditor::currentBank() const
{
    return currentBankIsBackground() ? m_back : m_front;
}

bool SidboxGamePaletteEditor::confirmDiscard()
{
    return !m_modified || QMessageBox::question(this, tr("Unsaved palette changes"),
        tr("Discard unsaved palette edits?"), QMessageBox::Discard | QMessageBox::Cancel,
        QMessageBox::Cancel) == QMessageBox::Discard;
}

bool SidboxGamePaletteEditor::loadFromFile(const QString &path)
{
    if (!confirmDiscard()) return false;
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly) || (file.size() != 1024 && file.size() != 2048)) {
        QMessageBox::warning(this, tr("Import Palette"),
            tr("Expected a 1024-byte one-bank or 2048-byte two-bank SIDBOX .pal."));
        return false;
    }
    const bool twoBanks = file.size() == 2048;
    const bool importedToBackground = currentBankIsBackground();
    QString error;
    const QVector<QRgb> first = SidboxGamePalette::readPalette(path, false, &error);
    const QVector<QRgb> second = twoBanks
        ? SidboxGamePalette::readPalette(path, true, &error) : QVector<QRgb>();
    if (first.size() != 256 || (twoBanks && second.size() != 256)) {
        QMessageBox::warning(this, tr("Import Palette"), error);
        return false;
    }
    if (twoBanks) {
        m_front = first;
        m_back = second;
    } else {
        currentBank() = first; // A one-bank .pal imports into the selected plane only.
    }
    // Background CLUTs never use transparency, even at index 0.
    bool correctedAlpha = false;
    for (QRgb &colour : m_back) {
        const QRgb opaque = colour | 0xFF000000u;
        if (opaque != colour) { colour = opaque; correctedAlpha = true; }
    }
    m_modified = correctedAlpha;
    m_sourceIsSingleBank = !twoBanks;
    m_sourceBankIsBackground = importedToBackground;
    m_sourcePath = QFileInfo(path).absoluteFilePath();
    m_saveButton->setEnabled(true);
    // A one-bank .pal has just one editable plane; avoid edits that Save cannot preserve.
    m_bank->setEnabled(twoBanks);
    m_savedPath.clear();
    m_status->setText((twoBanks
        ? tr("Loaded both banks from %1").arg(QFileInfo(path).fileName())
        : tr("Loaded one bank into %1; the other bank was preserved.")
            .arg(currentBankIsBackground() ? tr("Background") : tr("Foreground"))
            + tr(" Save keeps the single-bank format; Save As creates both banks."))
        + (correctedAlpha ? tr(" Background colours were made opaque; click Save to keep this change.") : QString()));
    refreshGrid();
    return true;
}

void SidboxGamePaletteEditor::importPalette()
{
    const QString path = QFileDialog::getOpenFileName(this, tr("Import SIDBOX Palette"),
        QFileInfo(m_sourcePath).absolutePath(), tr("SIDBOX palettes (*.pal)"));
    if (!path.isEmpty()) loadFromFile(path);
}

void SidboxGamePaletteEditor::exportPalette()
{
    const QFileInfo source(m_sourcePath);
    const QString suggestion = source.isFile()
        ? source.dir().filePath(source.completeBaseName() + QStringLiteral("_edited.pal"))
        : QStringLiteral("game_palette.pal");
    QString path = QFileDialog::getSaveFileName(this, tr("Save Both SIDBOX Palette Banks"),
        suggestion, tr("SIDBOX palettes (*.pal)"));
    if (path.isEmpty()) return;
    if (!path.endsWith(QStringLiteral(".pal"), Qt::CaseInsensitive)) path += QStringLiteral(".pal");
    if (QFileInfo::exists(path)) {
        if (QMessageBox::question(this, tr("Overwrite palette?"),
            tr("Replace the existing palette file?\n%1").arg(path),
            QMessageBox::Yes | QMessageBox::No, QMessageBox::No) != QMessageBox::Yes) return;
    }
    QString error;
    if (!SidboxGamePalette::writePal(path, m_front, m_back, &error)) {
        QMessageBox::warning(this, tr("Save Palette"), error);
        return;
    }
    m_savedPath = QFileInfo(path).absoluteFilePath();
    m_sourcePath = m_savedPath;
    m_sourceIsSingleBank = false;
    m_bank->setEnabled(true);
    m_saveButton->setEnabled(true);
    m_modified = false;
    m_status->setText(tr("Saved 2048-byte palette (foreground + background): %1")
        .arg(QFileInfo(path).fileName()));
}

void SidboxGamePaletteEditor::savePalette()
{
    if (m_sourcePath.isEmpty() || !QFileInfo::exists(m_sourcePath)
        || QFileInfo(m_sourcePath).suffix().compare(QStringLiteral("pal"), Qt::CaseInsensitive) != 0) {
        QMessageBox::information(this, tr("Save Palette"),
            tr("Import an existing .pal first, or use Save As to create one."));
        return;
    }
    QString error;
    const bool ok = m_sourceIsSingleBank
        ? SidboxGamePalette::writeSinglePal(m_sourcePath,
              m_sourceBankIsBackground ? m_back : m_front, &error)
        : SidboxGamePalette::writePal(m_sourcePath, m_front, m_back, &error);
    if (!ok) {
        QMessageBox::warning(this, tr("Save Palette"), error);
        return;
    }
    m_savedPath = m_sourcePath;
    m_modified = false;
    m_status->setText(tr("Saved changes to %1 (%2 bank%3).")
        .arg(QFileInfo(m_sourcePath).fileName())
        .arg(m_sourceIsSingleBank ? 1 : 2)
        .arg(m_sourceIsSingleBank ? QString() : QStringLiteral("s")));
}

void SidboxGamePaletteEditor::selectIndex(int index)
{
    m_index = qBound(0, index, 255);
    refreshSelected();
}

void SidboxGamePaletteEditor::refreshGrid()
{
    const auto &colours = currentBank();
    for (int i = 0; i < m_cells.size(); ++i) {
        m_cells[i]->setIcon(colourIcon(colours.at(i)));
        m_cells[i]->setToolTip(tr("Index %1 — %2").arg(i).arg(
            currentBankIsBackground() ? rgbHex(colours.at(i)) : argbHex(colours.at(i))));
    }
    refreshSelected();
}

void SidboxGamePaletteEditor::refreshSelected()
{
    m_indexLabel->setText(tr("Index %1 (0x%2):")
        .arg(m_index).arg(m_index, 2, 16, QLatin1Char('0')).toUpper());
    m_hex->setMaxLength(currentBankIsBackground() ? 8 : 10);
    m_hex->setToolTip(currentBankIsBackground()
        ? tr("Background colour: 0xRRGGBB (all colours are opaque).")
        : tr("Foreground colour: 0xAARRGGBB (alpha controls transparency)."));
    m_hex->setText(currentBankIsBackground()
        ? rgbHex(currentBank().at(m_index)) : argbHex(currentBank().at(m_index)));
    for (int i = 0; i < m_cells.size(); ++i)
        m_cells[i]->setStyleSheet(i == m_index
            ? QStringLiteral("QToolButton { border:2px solid palette(highlight); border-radius:0px; padding:0px; }")
            : QStringLiteral("QToolButton { border:1px solid palette(mid); border-radius:0px; padding:0px; }"));
}

void SidboxGamePaletteEditor::chooseColour()
{
    const QColor initial = QColor::fromRgba(currentBank().at(m_index));
    const QColor chosen = QColorDialog::getColor(initial, this,
        currentBankIsBackground() ? tr("Edit background RGB colour") : tr("Edit foreground ARGB colour"),
        currentBankIsBackground() ? QColorDialog::ColorDialogOptions()
                                  : QColorDialog::ColorDialogOptions(QColorDialog::ShowAlphaChannel));
    if (!chosen.isValid()) return;
    const QRgb updated = currentBankIsBackground() ? qRgb(chosen.red(), chosen.green(), chosen.blue()) : chosen.rgba();
    if (updated == currentBank().at(m_index)) return;
    currentBank()[m_index] = updated;
    m_modified = true;
    refreshGrid();
}

void SidboxGamePaletteEditor::applyHexColour()
{
    const QString raw = m_hex->text().trimmed();
    static const QRegularExpression frontValid(QStringLiteral("^(?:0x)?([0-9A-Fa-f]{8})$"));
    static const QRegularExpression backValid(QStringLiteral("^(?:0x)?([0-9A-Fa-f]{6})$"));
    const bool background = currentBankIsBackground();
    const auto match = (background ? backValid : frontValid).match(raw);
    if (!match.hasMatch()) {
        m_status->setText(background
            ? tr("Enter 6 RGB hex digits: 0xRRGGBB. Backgrounds cannot be transparent.")
            : tr("Enter 8 ARGB hex digits: 0xAARRGGBB."));
        return;
    }
    bool ok = false;
    quint32 colour = match.captured(1).toUInt(&ok, 16);
    if (background) colour |= 0xFF000000u;
    if (!ok || currentBank().at(m_index) == colour) return;
    currentBank()[m_index] = QRgb(colour);
    m_modified = true;
    refreshGrid();
}

void SidboxGamePaletteEditor::reject()
{
    if (confirmDiscard()) QDialog::reject();
}
