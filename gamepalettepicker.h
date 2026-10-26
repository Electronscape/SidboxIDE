#ifndef SIDBOX_GAME_PALETTE_PICKER_H
#define SIDBOX_GAME_PALETTE_PICKER_H

// Shared 256-entry CLUT INDEX selector. This is the Game Object Properties
// flash-colour picker, reused by other IDE panels. It NEVER edits .pal files,
// palette entries, or PPB pixel indices. The .pal editor remains independent.
#include <QColor>
#include <QDialog>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QIcon>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QScrollArea>
#include <QString>
#include <QVector>
#include <QVBoxLayout>

namespace SidboxPalettePicker {
inline int chooseIndex(QWidget *parent, const QVector<QRgb> &palette,
                       int current, const QString &title,
                       const QString &description,
                       bool allowIndexZero = true,
                       bool padMissingEntries = false)
{
    if (!padMissingEntries && palette.size() != 256) return -1;

    QDialog picker(parent);
    picker.setWindowTitle(title);
    auto *layout = new QVBoxLayout(&picker);
    auto *note = new QLabel(description, &picker);
    note->setWordWrap(true);
    layout->addWidget(note);

    // Fixed-size swatches and grid matching Game Object Properties: 16x16,
    // 28px buttons, 22px actual-colour icons, 3px gaps, yellow selection.
    // Scroll on smaller desktops without shrinking or clipping the grid.
    auto *scroll = new QScrollArea(&picker);
    scroll->setWidgetResizable(false);
    auto *host = new QWidget(scroll);
    auto *cells = new QGridLayout(host);
    cells->setContentsMargins(4, 4, 4, 4);
    cells->setSpacing(3);
    int selected = -1;
    for (int index = 0; index < 256; ++index) {
        const QRgb rgba = index < palette.size() ? palette.at(index) : qRgb(0,0,0);
        const QColor colour = QColor::fromRgba(rgba);
        auto *cell = new QPushButton(host);
        cell->setFixedSize(28, 28);
        QPixmap swatch(22, 22);
        swatch.fill(colour);
        cell->setIcon(QIcon(swatch));
        cell->setIconSize(QSize(22, 22));
        cell->setAccessibleName(QObject::tr("CLUT index %1").arg(index));
        cell->setToolTip(QObject::tr("CLUT index %1: %2")
                             .arg(index).arg(colour.name(QColor::HexArgb).toUpper()));
        if (index == current)
            cell->setStyleSheet(QStringLiteral("border: 2px solid #f5c747;"));
        if (index == 0 && !allowIndexZero) {
            cell->setEnabled(false);
            cell->setToolTip(QObject::tr("CLUT index 0 is reserved for transparency."));
        }
        cells->addWidget(cell, index / 16, index % 16);
        QObject::connect(cell, &QPushButton::clicked, &picker, [&picker, &selected, index]() {
            selected = index;
            picker.accept();
        });
    }
    scroll->setWidget(host);
    scroll->setAlignment(Qt::AlignCenter);
    layout->addWidget(scroll, 1);
    auto *cancel = new QDialogButtonBox(QDialogButtonBox::Cancel, &picker);
    layout->addWidget(cancel);
    QObject::connect(cancel, &QDialogButtonBox::rejected, &picker, &QDialog::reject);
    picker.resize(580, 570);
    return picker.exec() == QDialog::Accepted ? selected : -1;
}
} // namespace SidboxPalettePicker

#endif
