#include "gamepaletteeditor.h"
#include "gamepalette.h"

#include <QComboBox>
#include <QCheckBox>
#include <QGroupBox>
#include <QSpinBox>
#include <QSlider>
#include <QTimer>
#include <QSignalBlocker>
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
    m_backCycle.start = 0;
    setWindowTitle(tr("SIDBOX Palette Editor"));
    setMinimumSize(460, 590);
    resize(550, 710);
    // Standard palette-editor controls inherit the global IDE theme.
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

    // These are DESIGN settings kept in .sbgm; Save .pal never serialises them.
    auto *cycleBox = new QGroupBox(tr("Colour Cycle — Selected Bank"), this);
    auto *cycleRoot = new QVBoxLayout(cycleBox);
    auto *cycleRow = new QHBoxLayout;
    m_cycleEnabled = new QCheckBox(tr("Enabled"), cycleBox);
    cycleRow->addWidget(m_cycleEnabled);
    cycleRow->addWidget(new QLabel(tr("Start:"), cycleBox));
    m_cycleStart = new QSpinBox(cycleBox);
    m_cycleStart->setRange(0, 254);
    m_cycleStart->setToolTip(tr("First palette index. Foreground starts at 1; background may use 0."));
    cycleRow->addWidget(m_cycleStart);
    cycleRow->addWidget(new QLabel(tr("Length:"), cycleBox));
    m_cycleLength = new QSpinBox(cycleBox);
    m_cycleLength->setRange(2, 255);
    cycleRow->addWidget(m_cycleLength);
    cycleRow->addWidget(new QLabel(tr("Frames/step:"), cycleBox));
    m_cycleSpeed = new QSpinBox(cycleBox);
    m_cycleSpeed->setRange(1, 255);
    m_cycleSpeed->setToolTip(tr("LCD update frames per palette step. At 50 FPS: 5 frames = 100 ms. Independent of monitor refresh rate."));
    cycleRow->addWidget(m_cycleSpeed);
    m_cyclePreview = new QCheckBox(tr("Preview"), cycleBox);
    m_cyclePreview->setToolTip(tr("Animate the palette swatches without changing the actual .pal file."));
    m_cyclePreview->setChecked(true);
    cycleRow->addWidget(m_cyclePreview);
    cycleRoot->addLayout(cycleRow);
    auto *cycleNote = new QLabel(tr("Foreground and background have independent ranges, speeds and enable flags. "
                                    "Select Bank above to edit each one. Preview uses the SIDBOX 50 FPS frame clock."), cycleBox);
    cycleNote->setWordWrap(true);
    cycleRoot->addWidget(cycleNote);
    root->addWidget(cycleBox);
    auto refreshCycle = [this]() { refreshCycleControls(); refreshGrid(); };
    connect(m_cycleEnabled, &QCheckBox::toggled, this, [this, refreshCycle](bool checked) {
        currentCycle().enabled = checked; refreshCycle();
    });
    connect(m_cycleStart, qOverload<int>(&QSpinBox::valueChanged), this,
            [this, refreshCycle](int start) { currentCycle().start = start; refreshCycle(); });
    connect(m_cycleLength, qOverload<int>(&QSpinBox::valueChanged), this,
            [this, refreshCycle](int length) { currentCycle().length = length; refreshCycle(); });
    connect(m_cycleSpeed, qOverload<int>(&QSpinBox::valueChanged), this,
            [this, refreshCycle](int speed) { currentCycle().speed = speed; refreshCycle(); });
    connect(m_cyclePreview, &QCheckBox::toggled, this,
            [this](bool) { m_cycleClock.restart(); m_cyclePreviewLastPhase = -1; refreshGrid(); });
    m_cycleClock.start();
    m_cycleTimer = new QTimer(this);
    m_cycleTimer->setInterval(20);
    connect(m_cycleTimer, &QTimer::timeout, this, [this]() {
        const auto &cycle = currentCycle();
        if (!isVisible() || !m_cyclePreview->isChecked() || !cycle.enabled) return;
        const int phase = int((m_cycleClock.elapsed() / 20 / qMax(1, cycle.speed))
                              % cycle.length);
        if (phase != m_cyclePreviewLastPhase) refreshGrid();
    });
    m_cycleTimer->start();
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

    // Foreground CLUT entries store their alpha in the high byte of 0xAARRGGBB.
    // Background is always opaque; index 0 in front is reserved transparent.
    auto *alphaRow = new QHBoxLayout;
    auto *alphaLabel = new QLabel(tr("Alpha:"), this);
    alphaRow->addWidget(alphaLabel);
    m_alphaSlider = new QSlider(Qt::Horizontal, this);
    m_alphaSlider->setRange(0, 255);
    m_alphaSlider->setSingleStep(1);
    m_alphaSlider->setPageStep(16);
    m_alphaSlider->setToolTip(tr("Selected foreground colour alpha: 0 = transparent, 255 = opaque. "
                                 "Foreground index 0 is reserved transparent."));
    alphaRow->addWidget(m_alphaSlider, 1);
    m_alphaValue = new QLabel(this);
    m_alphaValue->setMinimumWidth(112);
    alphaRow->addWidget(m_alphaValue);
    m_alphaSwatch = new QLabel(this);
    m_alphaSwatch->setFixedSize(48, 22);
    m_alphaSwatch->setToolTip(tr("Selected colour over a checkerboard (alpha preview)."));
    alphaRow->addWidget(m_alphaSwatch);
    root->addLayout(alphaRow);
    connect(m_alphaSlider, &QSlider::valueChanged, this, [this](int alpha) {
        if (currentBankIsBackground() || m_index == 0) return;
        QRgb &colour = currentBank()[m_index];
        if (qAlpha(colour) == alpha) return;
        colour = qRgba(qRed(colour), qGreen(colour), qBlue(colour), alpha);
        m_modified = true;
        refreshGrid(); // ARGB field, swatch and palette-cell preview follow the slider.
    });

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
            [this](int) { refreshCycleControls(); refreshGrid(); });
    connect(pick, &QPushButton::clicked, this, [this]() { chooseColour(); });
    connect(m_hex, &QLineEdit::returnPressed, this, [this]() { applyHexColour(); });
    connect(m_hex, &QLineEdit::editingFinished, this, [this]() { applyHexColour(); });
    // Initialise after index/hex widgets exist: setColourCycle refreshes them.
    setColourCycles(m_frontCycle, m_backCycle);
}

void SidboxGamePaletteEditor::setColourCycles(const SidboxGamePalette::ColourCycle &front,
                                             const SidboxGamePalette::ColourCycle &back)
{
    m_frontCycle = front;
    m_backCycle = back;
    m_frontCycle.start = qBound(1, m_frontCycle.start, 254);
    m_backCycle.start = qBound(0, m_backCycle.start, 254);
    m_frontCycle.length = qBound(2, m_frontCycle.length, 256 - m_frontCycle.start);
    m_backCycle.length = qBound(2, m_backCycle.length, 256 - m_backCycle.start);
    m_frontCycle.speed = qBound(1, m_frontCycle.speed, 255);
    m_backCycle.speed = qBound(1, m_backCycle.speed, 255);
    refreshCycleControls();
    refreshGrid();
}

SidboxGamePalette::ColourCycle &SidboxGamePaletteEditor::currentCycle()
{
    return currentBankIsBackground() ? m_backCycle : m_frontCycle;
}

const SidboxGamePalette::ColourCycle &SidboxGamePaletteEditor::currentCycle() const
{
    return currentBankIsBackground() ? m_backCycle : m_frontCycle;
}

void SidboxGamePaletteEditor::refreshCycleControls()
{
    SidboxGamePalette::ColourCycle &cycle = currentCycle();
    cycle.start = qBound(currentBankIsBackground() ? 0 : 1, cycle.start, 254);
    cycle.length = qBound(2, cycle.length, 256 - cycle.start);
    cycle.speed = qBound(1, cycle.speed, 255);
    QSignalBlocker b1(m_cycleEnabled), b2(m_cycleStart), b3(m_cycleLength), b4(m_cycleSpeed);
    m_cycleEnabled->setChecked(cycle.enabled);
    m_cycleStart->setMinimum(currentBankIsBackground() ? 0 : 1);
    m_cycleStart->setValue(cycle.start);
    m_cycleLength->setMaximum(256 - cycle.start);
    m_cycleLength->setValue(cycle.length);
    m_cycleSpeed->setValue(cycle.speed);
    m_cycleStart->setEnabled(cycle.enabled);
    m_cycleLength->setEnabled(cycle.enabled);
    m_cycleSpeed->setEnabled(cycle.enabled);
    m_cyclePreview->setEnabled(cycle.enabled);
    m_cyclePreviewLastPhase = -1;
    m_cycleClock.restart();
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
    // Older .pal files sometimes have a zero alpha byte for ordinary foreground
    // colours. Keep the file's alpha untouched unless the user explicitly asks
    // us to repair these entries: alpha 0 may also be intentional.
    QVector<QRgb> foreground = twoBanks ? first
        : (importedToBackground ? m_front : first);
    int missingForegroundAlpha = 0;
    if (twoBanks || !importedToBackground) {
        for (int i = 1; i < foreground.size(); ++i) {
            if (qAlpha(foreground.at(i)) == 0) ++missingForegroundAlpha;
        }
    }
    bool repairedForeground = false;
    if (missingForegroundAlpha > 0) {
        const auto answer = QMessageBox::question(
            this, tr("Foreground Palette Transparency"),
            tr("%1 foreground palette colour(s), other than index 0, have zero alpha "
               "and will appear transparent on SIDBOX.\n\n"
               "Make these colours opaque (alpha FF)?\n\n"
               "Yes: Fix zero-alpha entries only (other alpha values are preserved).\n"
               "No: Keep the palette exactly as it was.\n"
               "Cancel: Do not import this palette.")
                .arg(missingForegroundAlpha),
            QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,
            QMessageBox::Yes);
        if (answer == QMessageBox::Cancel) return false;
        if (answer == QMessageBox::Yes) {
            for (int i = 1; i < foreground.size(); ++i) {
                if (qAlpha(foreground.at(i)) == 0)
                    foreground[i] |= 0xFF000000u;
            }
            repairedForeground = true;
        }
    }
    if (twoBanks) {
        m_front = foreground;
        m_back = second;
    } else {
        currentBank() = importedToBackground ? first : foreground;
        // A one-bank .pal imports into the selected plane only.
    }
    // Background CLUTs never use transparency, even at index 0.
    bool correctedBackgroundAlpha = false;
    for (QRgb &colour : m_back) {
        const QRgb opaque = colour | 0xFF000000u;
        if (opaque != colour) { colour = opaque; correctedBackgroundAlpha = true; }
    }
    m_modified = repairedForeground || correctedBackgroundAlpha;
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
        + (repairedForeground ? tr(" Zero-alpha foreground colours were made opaque; click Save to keep this change.") : QString())
        + (correctedBackgroundAlpha ? tr(" Background colours were made opaque; click Save to keep this change.") : QString()));
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
    // Save succeeded: return to the World Designer so it can refresh the
    // palette resource and apply any colour-cycle settings from this dialog.
    QDialog::accept();
}

void SidboxGamePaletteEditor::selectIndex(int index)
{
    m_index = qBound(0, index, 255);
    refreshSelected();
}

void SidboxGamePaletteEditor::refreshGrid()
{
    const auto &colours = currentBank();
    const auto &cycle = currentCycle();
    const int steps = (m_cyclePreview && m_cyclePreview->isChecked() && cycle.enabled)
        ? int((m_cycleClock.elapsed() / 20 / qMax(1, cycle.speed)) % cycle.length) : 0;
    m_cyclePreviewLastPhase = steps;
    const QVector<QRgb> shown = SidboxGamePalette::cyclePreview(
        colours, cycle, steps, currentBankIsBackground());
    for (int i = 0; i < m_cells.size(); ++i) {
        m_cells[i]->setIcon(colourIcon(shown.at(i)));
        m_cells[i]->setToolTip(tr("Index %1 — %2%3").arg(i).arg(
            currentBankIsBackground() ? rgbHex(colours.at(i)) : argbHex(colours.at(i)),
            steps ? tr(" (animated preview)") : QString()));
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
    const QRgb selected = currentBank().at(m_index);
    m_hex->setText(currentBankIsBackground()
        ? rgbHex(selected) : argbHex(selected));
    const bool editableAlpha = !currentBankIsBackground() && m_index != 0;
    {
        QSignalBlocker block(m_alphaSlider);
        m_alphaSlider->setValue(currentBankIsBackground() ? 255 : qAlpha(selected));
    }
    m_alphaSlider->setEnabled(editableAlpha);
    m_alphaValue->setText(currentBankIsBackground() ? tr("Opaque (255)")
        : m_index == 0 ? tr("Index 0 reserved")
        : tr("%1 / 255 (%2%)").arg(qAlpha(selected)).arg(qRound(qAlpha(selected) * 100.0 / 255.0)));
    QPixmap preview(48, 22);
    preview.fill(Qt::transparent);
    {
        QPainter painter(&preview);
        painter.fillRect(preview.rect(), QColor(200, 200, 200));
        for (int y = 0; y < 22; y += 11)
            for (int x = 0; x < 48; x += 11)
                if (((x / 11) + (y / 11)) % 2 == 0)
                    painter.fillRect(x, y, 11, 11, QColor(240, 240, 240));
        painter.fillRect(preview.rect(), QColor::fromRgba(selected));
        painter.setPen(QColor(45, 45, 45));
        painter.drawRect(0, 0, 47, 21);
    }
    m_alphaSwatch->setPixmap(preview);
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
