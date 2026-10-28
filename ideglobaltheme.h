#ifndef SIDBOX_IDE_GLOBAL_THEME_H
#define SIDBOX_IDE_GLOBAL_THEME_H

#include "idetheme.h"
#include "gameeditoricons.h"
#include <QString>
#include <QApplication>
#include <QAbstractItemView>
#include <QComboBox>
#include <QEvent>
#include <QObject>
#include <QPointer>
#include <QWidget>
#include <QByteArray>
#include <QCryptographicHash>
#include <QDir>
#include <QFile>
#include <QImage>
#include <QPainter>
#include <QPalette>
#include <QPen>
#include <QStandardPaths>

// Stage 4.16: Both checkbox states are complete 16x16 artwork, with the
// same geometry. Drawing a CSS border only for the unchecked state made
// some KDE/Qt styles shift and squash the indicator when toggled.
// Stage 4.15: Use a native local path, not a file:/// URL, for Qt QSS.
// The source tick remains replaceable via icons/checkbox_tick.png.
inline QString ideCheckedBoxImageUrl(const IDETheme &theme, bool isChecked = true)
{
    QFile artwork(gameEditorIconOverride(QStringLiteral("checkbox_tick.png")));
    if (!artwork.exists())
        artwork.setFileName(QStringLiteral(":/icons/checkbox_tick.png"));
    QByteArray bytes;
    if (artwork.open(QIODevice::ReadOnly)) bytes = artwork.readAll();

    // Cache paths change when colours, custom artwork, or state changes.
    const QByteArray colourSpec = (theme.accent.name(QColor::HexArgb) +
        theme.border.name(QColor::HexArgb) +
        theme.inputBackground.name(QColor::HexArgb) +
        (isChecked ? QStringLiteral("on") : QStringLiteral("off"))).toLatin1();
    const QByteArray digest = QCryptographicHash::hash(colourSpec + bytes,
        QCryptographicHash::Sha256).toHex();
    QString cache = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
    if (cache.isEmpty()) cache = QDir::tempPath() + QStringLiteral("/SidboxIDE");
    const QString directory = QDir(cache).filePath(QStringLiteral("theme-icons"));
    if (QDir().mkpath(directory)) {
        const QString file = QDir(directory).filePath(
            (isChecked ? QStringLiteral("checkbox-on-") : QStringLiteral("checkbox-off-"))
            + QString::fromLatin1(digest.left(20)) + QStringLiteral(".png"));
        if (!QFile::exists(file)) {
            QImage indicator(16, 16, QImage::Format_ARGB32_Premultiplied);
            indicator.fill(Qt::transparent);
            QPainter painter(&indicator);
            painter.setRenderHint(QPainter::Antialiasing, false);
            painter.fillRect(QRect(0, 0, 16, 16),
                             isChecked ? theme.accent : theme.inputBackground);
            painter.setPen(QPen(theme.border, 1));
            painter.drawRect(QRect(0, 0, 15, 15));
            if (isChecked) {
                QImage tick;
                tick.loadFromData(bytes);
                if (!tick.isNull()) {
                    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
                    painter.drawImage(QRect(0, 0, 16, 16), tick);
                } else {
                    painter.setRenderHint(QPainter::Antialiasing, true);
                    painter.setPen(QPen(Qt::black, 4, Qt::SolidLine, Qt::SquareCap));
                    painter.drawLine(QPoint(3, 8), QPoint(7, 12));
                    painter.drawLine(QPoint(7, 12), QPoint(13, 3));
                    painter.setPen(QPen(Qt::white, 2, Qt::SolidLine, Qt::SquareCap));
                    painter.drawLine(QPoint(3, 8), QPoint(7, 12));
                    painter.drawLine(QPoint(7, 12), QPoint(13, 3));
                }
            }
            painter.end();
            if (!indicator.save(file, "PNG"))
                return QStringLiteral(":/icons/checkbox_tick.png");
        }
        return QDir::fromNativeSeparators(file);
    }
    return QStringLiteral(":/icons/checkbox_tick.png");
}

// Stage 5.118: Qt stylesheet-painted QComboBoxes cannot depend on the
// platform style to draw a down-arrow. Save a small theme-coloured chevron
// once and use it in BOTH the application and KDE popup-combo stylesheets.
// This does not affect designer combos that draw their own custom chevron.
inline QString ideComboDownArrowImageUrl(const IDETheme &theme, bool disabled = false)
{
    const QColor colour = disabled
        ? QColor((theme.mutedText.red() + theme.panelBackground.red()) / 2,
                 (theme.mutedText.green() + theme.panelBackground.green()) / 2,
                 (theme.mutedText.blue() + theme.panelBackground.blue()) / 2)
        : theme.text;
    const QByteArray digest = QCryptographicHash::hash(
        (colour.name(QColor::HexArgb) + (disabled ? QStringLiteral("off")
                                                  : QStringLiteral("on"))).toLatin1(),
        QCryptographicHash::Sha256).toHex();
    QString cache = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
    if (cache.isEmpty()) cache = QDir::tempPath() + QStringLiteral("/SidboxIDE");
    const QString directory = QDir(cache).filePath(QStringLiteral("theme-icons"));
    const QString file = QDir(directory).filePath(
        QStringLiteral("combobox-chevron-") + QString::fromLatin1(digest.left(20))
            + QStringLiteral(".png"));
    if (!QFile::exists(file) && QDir().mkpath(directory)) {
        QImage arrow(12, 9, QImage::Format_ARGB32_Premultiplied);
        arrow.fill(Qt::transparent);
        QPainter painter(&arrow);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(QPen(colour, 2.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter.drawLine(QPointF(2, 2), QPointF(6, 6));
        painter.drawLine(QPointF(6, 6), QPointF(10, 2));
        painter.end();
        arrow.save(file, "PNG");
    }
    return QDir::fromNativeSeparators(file);
}

// Install the same colours in the QApplication palette as in its stylesheet.
// Native popup list views (notably on KDE) and alternating tree rows can read
// their palette rather than the parent's stylesheet. Keep both in sync.
inline QPalette ideGlobalControlPalette(const IDETheme &theme)
{
    QPalette result = QApplication::palette();
    const QColor chosen = theme.accent.darker(230);
    const QColor chosenText = chosen.lightnessF() < 0.52
        ? QColor(Qt::white) : QColor(Qt::black);
    const QColor disabledText = QColor::fromRgbF(
        theme.mutedText.redF() * 0.7 + theme.panelBackground.redF() * 0.3,
        theme.mutedText.greenF() * 0.7 + theme.panelBackground.greenF() * 0.3,
        theme.mutedText.blueF() * 0.7 + theme.panelBackground.blueF() * 0.3);
    for (QPalette::ColorGroup group : {QPalette::Active, QPalette::Inactive}) {
        result.setColor(group, QPalette::Window, theme.windowBackground);
        result.setColor(group, QPalette::WindowText, theme.text);
        result.setColor(group, QPalette::Base, theme.inputBackground);
        result.setColor(group, QPalette::AlternateBase, theme.alternateBackground);
        result.setColor(group, QPalette::Text, theme.text);
        result.setColor(group, QPalette::Button, theme.panelBackground);
        result.setColor(group, QPalette::ButtonText, theme.text);
        result.setColor(group, QPalette::Highlight, chosen);
        result.setColor(group, QPalette::HighlightedText, chosenText);
        result.setColor(group, QPalette::ToolTipBase, theme.tooltipBackground);
        result.setColor(group, QPalette::ToolTipText, theme.tooltipText);
        result.setColor(group, QPalette::Light, theme.border.lighter(130));
        result.setColor(group, QPalette::Mid, theme.border);
        result.setColor(group, QPalette::Dark, theme.border.darker(130));
    }
    result.setColor(QPalette::Disabled, QPalette::Text, disabledText);
    result.setColor(QPalette::Disabled, QPalette::WindowText, disabledText);
    result.setColor(QPalette::Disabled, QPalette::ButtonText, disabledText);
    result.setColor(QPalette::Disabled, QPalette::Base, theme.panelBackground);
    result.setColor(QPalette::Disabled, QPalette::AlternateBase, theme.alternateBackground);
    result.setColor(QPalette::Disabled, QPalette::Button, theme.panelBackground);
    return result;
}

// This is the ONE shared control style. QApplication owns it, so a newly
// opened top-level Qt dialog inherits the current IDE theme automatically.
// Editors may style individual named canvases/cards, not re-declare controls.
// One control language for the World Designer and Tilemap Editor. The Player
// Animation Toolkit and Game Object Properties use the same control language:
// square edges, framed inputs, accent-coloured states and compact spacing.
// Use actual IDETheme values (including light themes), never hard-coded hues.
// Keep this scoped to INTERFACE CONTROLS; editor canvases paint their own art.
inline QString ideGlobalControlStyle(const IDETheme &theme)
{
    const QColor chosen = theme.accent.darker(230);
    const QColor chosenText = chosen.lightnessF() < 0.52
        ? QColor(Qt::white) : QColor(Qt::black);
    // Disabled foreground must be readable in both light and dark themes.
    const QColor disabledText = QColor::fromRgbF(
        theme.mutedText.redF() * 0.7 + theme.panelBackground.redF() * 0.3,
        theme.mutedText.greenF() * 0.7 + theme.panelBackground.greenF() * 0.3,
        theme.mutedText.blueF() * 0.7 + theme.panelBackground.blueF() * 0.3);

    // Stage 5.117: dependency indicators are deliberately specific to tagged
    // Adventure Editor controls, rather than colouring every IDE control.
    // Contrast is tuned for both the built-in dark and light colour schemes.
    const bool lightTheme = theme.windowBackground.lightnessF() > 0.55;
    const QColor adventureGreen(lightTheme ? QStringLiteral("#267744") : QStringLiteral("#59c991"));
    const QColor adventureRed(lightTheme ? QStringLiteral("#b03f4b") : QStringLiteral("#dc7380"));
    const auto blend = [](const QColor &base, const QColor &tint, int percent) {
        return QColor((base.red()*(100-percent) + tint.red()*percent)/100,
                      (base.green()*(100-percent) + tint.green()*percent)/100,
                      (base.blue()*(100-percent) + tint.blue()*percent)/100);
    };
    // Muted, 1px outlines: hint at availability without glowing neon.
    const QColor adventureGreenBorder=blend(theme.border,adventureGreen,48);
    const QColor adventureRedBorder=blend(theme.border,adventureRed,58);
    const QColor adventureGreenBg=blend(theme.inputBackground,adventureGreen,5);
    const QColor adventureRedBg=blend(theme.panelBackground,adventureRed,11);

    QString css = QStringLiteral(R"GGCONTROLS(
        QWidget { color:@text; }
        QMainWindow, QDialog { background-color:@window; color:@text; }
        QLabel { color:@text; background:transparent; }
        QToolBar { background:@panel; border:0px; spacing:1px; padding:1px; }
        QToolTip { background:@tipBg; color:@tipText; border:2px solid @accent;
            padding:5px; font-size:12px; }
        QMenu { background:@menu; color:@text; border:1px solid @border; }
        QMenu::item { padding:5px 24px 5px 8px; }
        QMenu::item:selected { background:@chosen; color:@chosenText; }
        QMenu::item:disabled { color:@disabledText; }
        QStatusBar { background:@panel; color:@text; border-top:1px solid @border; }
        QProgressBar { background:@input; color:@text; border:1px solid @border;
            border-radius:0px; text-align:center; }
        QProgressBar::chunk { background:@accent; border-radius:0px; }
        QProgressBar#compileProgress::chunk { width:18px; margin:1px; }
        QPlainTextEdit, QTextEdit { background:@input; color:@text;
            border:1px solid @border; border-radius:0px;
            selection-background-color:@chosen; selection-color:@chosenText; }
        QDateEdit, QTimeEdit, QDateTimeEdit { background:@input; color:@text;
            border:1px solid @border; border-radius:0px; }
        QTabWidget::pane { background:@panel; }
        QPushButton, QToolButton {
            background:@panel; color:@text; border:1px solid @border;
            border-radius:0px; padding:5px 8px; min-height:22px;
        }
        QPushButton:hover:!disabled, QToolButton:hover:!disabled {
            border-color:@accent; background:@hover;
        }
        QPushButton:pressed, QToolButton:pressed,
        QToolButton:checked { background:@chosen; color:@chosenText;
            border-color:@accent; }
        QPushButton:default { border:2px solid @accent; }
        QPushButton:disabled, QToolButton:disabled {
            background:@panel; color:@disabledText; border-color:@border;
        }
        /* Programmer Calculator: compact sizing only. Its seven-row keypad
           was inheriting 22px min-height PLUS 10px button padding, making
           each 22px key render over 30px tall and clipping the last row.
           Keep colours/borders/hover in the central theme above. */
        QWidget#sidboxProgrammerCalculator QPushButton,
        QWidget#sidboxProgrammerCalculator QToolButton {
            min-height:0px; padding:0px 2px;
        }
        QWidget#sidboxProgrammerCalculator QLineEdit,
        QWidget#sidboxProgrammerCalculator QComboBox {
            min-height:0px; padding:1px 4px;
        }
        QComboBox, QSpinBox, QDoubleSpinBox, QLineEdit {
            background:@input; color:@text; border:1px solid @border;
            border-radius:0px; padding:4px 5px; min-height:22px;
            selection-background-color:@chosen;
            selection-color:@chosenText;
        }
        /* Always use a Qt list popup, never the platform's native menu.
           This keeps dropdown rows inside our stylesheet control on KDE. */
        /* Numeric steppers stay compact; the shared 22px text-field rule
           above is much taller than necessary once padding is included. */
        QSpinBox, QDoubleSpinBox { padding:1px 4px; min-height:16px; }
        QComboBox { padding-right:25px; combobox-popup:0; }
        QComboBox::drop-down {
            width:21px; border-left:1px solid @border;
            border-radius:0px; background:@panel;
        }
        /* Explicit chevrons are necessary when Qt uses QSS (KDE/Wayland).
           The native glyph is otherwise sometimes suppressed entirely. */
        QComboBox::down-arrow {
            image:url("@comboArrow"); width:12px; height:9px;
        }
        QComboBox::down-arrow:disabled {
            image:url("@comboArrowDisabled"); width:12px; height:9px;
        }
        /* Designer-owned combos draw their own high-contrast chevron.
           All other combos use the theme-matched arrow above. */
        QComboBox[customChevron="true"]::down-arrow {
            image:none; width:0px; height:0px;
        }
        QComboBox:focus, QSpinBox:focus, QDoubleSpinBox:focus,
        QLineEdit:focus { border:1px solid @accent; }
        QComboBox:disabled, QSpinBox:disabled, QDoubleSpinBox:disabled,
        QLineEdit:disabled { background:@panel; color:@disabledText; }
        /* Qt puts the list in a popup frame, which can be styled using the
           desktop QStyle even though the combo itself has an IDE stylesheet. */
        QComboBoxPrivateContainer {
            background:@menu; color:@text; border:1px solid @border;
            border-radius:0px;
        }
        QComboBox QAbstractItemView, QComboBoxPrivateContainer QAbstractItemView {
            background:@menu; alternate-background-color:@alternate;
            color:@text; border:1px solid @border;
            border-radius:0px; outline:0px;
            selection-background-color:@chosen;
            selection-color:@chosenText;
        }
        QComboBox QAbstractItemView::item, QComboBoxPrivateContainer QAbstractItemView::item {
            color:@text; padding:3px 5px; min-height:19px;
        }
        QComboBox QAbstractItemView::item:selected,
        QComboBoxPrivateContainer QAbstractItemView::item:selected {
            background:@chosen; color:@chosenText;
        }
        QCheckBox, QRadioButton { color:@text; background:transparent;
            spacing:7px; }
        /* Keep the exact same 16x16 geometry in EVERY state. Neither the
           border nor Qt's native checkbox background may alter its size. */
        QCheckBox::indicator {
            width:16px; height:16px; border:0px;
            border-radius:0px; background:transparent;
            image:url("@untick");
        }
        QCheckBox::indicator:hover:!disabled {
            border:0px; background:transparent;
        }
        QCheckBox::indicator:checked, QCheckBox::indicator:checked:hover {
            border:0px; background:transparent; image:url("@tick");
        }
        QCheckBox::indicator:disabled {
            border:0px; background:transparent; image:url("@untick");
        }
        QCheckBox::indicator:checked:disabled {
            border:0px; background:transparent; image:url("@tick");
        }
        QRadioButton::indicator {
            width:14px; height:14px; border:2px solid @border;
            background:@input; border-radius:0px;
        }
        QRadioButton::indicator:checked { background:@accent;
            border-color:@accent; }
        QRadioButton::indicator:disabled { background:@panel; }
        QCheckBox:disabled, QRadioButton:disabled { color:@disabledText; }
        QSlider::groove:horizontal { height:4px; background:@border;
            border:0px; border-radius:0px; }
        QSlider::sub-page:horizontal { background:@accent; border-radius:0px; }
        QSlider::handle:horizontal {
            background:@accent; border:1px solid @text; border-radius:0px;
            width:10px; margin:-4px 0;
        }
        QSlider::handle:horizontal:hover { background:@hoverHandle;
            border:1px solid @accent; }
        QSlider::groove:vertical { width:4px; background:@border;
            border:0px; border-radius:0px; }
        QSlider::sub-page:vertical { background:@accent; border-radius:0px; }
        QSlider::handle:vertical {
            background:@accent; border:1px solid @text; border-radius:0px;
            height:10px; margin:0 -4px;
        }
        QSlider:disabled { color:@disabledText; }
        QTabWidget::pane { border:1px solid @border;
            border-radius:0px; background:@panel; }
        QTabBar::tab { background:@panel; color:@text;
            border:1px solid @border; border-radius:0px;
            padding:6px 9px; margin-right:2px; }
        QTabBar::tab:selected { background:@chosen; color:@chosenText;
            border:1px solid @accent; border-bottom:2px solid @accent; }
        QTabBar::tab:hover:!selected { background:@hover;
            border-color:@accent; }
        QSplitter::handle { background:@border; }
        QGroupBox { border:1px solid @border; border-radius:0px;
            margin-top:10px; padding-top:5px; }
        QGroupBox::title { subcontrol-origin:margin; left:8px;
            padding:0px 4px; color:@text; }
        /* Explicit cross-axis sizes: KDE otherwise supplies its much
           wider native scrollbar inside dropdown popup lists. */
        QScrollBar:vertical {
            width:10px; min-width:10px; max-width:10px;
            margin:0px; padding:0px;
            background:@panel; border:0px; border-radius:0px;
        }
        QScrollBar:horizontal {
            height:10px; min-height:10px; max-height:10px;
            margin:0px; padding:0px;
            background:@panel; border:0px; border-radius:0px;
        }
        QScrollBar::handle:horizontal, QScrollBar::handle:vertical {
            background:@scroll; border-radius:0px;
        }
        QScrollBar::handle:horizontal { min-width:18px; }
        QScrollBar::handle:vertical { min-height:18px; }
        QComboBoxPrivateContainer QScrollBar:vertical,
        QComboBox QAbstractItemView QScrollBar:vertical {
            width:10px; min-width:10px; max-width:10px;
        }
        QScrollBar::handle:horizontal:hover,
        QScrollBar::handle:vertical:hover { background:@scrollHover; }
        QScrollBar::add-line, QScrollBar::sub-line { width:0px; height:0px;
            border:0px; background:transparent; }
        QScrollBar::add-page, QScrollBar::sub-page { background:transparent; }
        QTreeView, QTreeWidget, QListView, QListWidget, QTableView, QTableWidget {
            background:@panel; alternate-background-color:@alternate;
            color:@text; border:1px solid @border;
            border-radius:0px; outline:0px; }
        QTreeWidget::item:selected, QListWidget::item:selected,
        QTableWidget::item:selected {
            background:@chosen; color:@chosenText;
        }
        QTreeWidget::item:hover:!selected { background:@hover; }
        QHeaderView::section { background:@panel; color:@text;
            border:1px solid @border; padding:4px; border-radius:0px; }
        QFrame, QScrollArea, QGraphicsView, QSplitter { border-radius:0px; }

        /* Stage 5.118: softer prerequisite-dependent Adventure Editor widgets.
           Preserve box geometry across enable/disable transitions, use both
           colour and muted fill for disabled state, and keep checkmark art.
           A dynamically tagged widget is repolished exactly once by the
           Adventure Editor; future enabled changes use normal Qt states. */
        QComboBox[adventureGuard="true"]:enabled,
        QLineEdit[adventureGuard="true"]:enabled,
        QSpinBox[adventureGuard="true"]:enabled,
        QDoubleSpinBox[adventureGuard="true"]:enabled,
        QPushButton[adventureGuard="true"]:enabled,
        QToolButton[adventureGuard="true"]:enabled,
        QTextEdit[adventureGuard="true"]:enabled {
            border:1px solid @advGreenBorder; background-color:@advGreenBg;
        }
        QComboBox[adventureGuard="true"]:disabled,
        QLineEdit[adventureGuard="true"]:disabled,
        QSpinBox[adventureGuard="true"]:disabled,
        QDoubleSpinBox[adventureGuard="true"]:disabled,
        QPushButton[adventureGuard="true"]:disabled,
        QToolButton[adventureGuard="true"]:disabled,
        QTextEdit[adventureGuard="true"]:disabled {
            border:1px solid @advRedBorder; background-color:@advRedBg;
            color:@disabledText;
        }
        QPushButton[adventureGuard="true"]:enabled:hover,
        QToolButton[adventureGuard="true"]:enabled:hover {
            border:1px solid @advGreenBorder; background-color:@hover;
        }
        QPushButton[adventureGuard="true"]:enabled:pressed,
        QToolButton[adventureGuard="true"]:enabled:pressed,
        QToolButton[adventureGuard="true"]:enabled:checked {
            border:1px solid @advGreenBorder; background-color:@chosen;
            color:@chosenText;
        }
        /* Guard colours must never change checkbox geometry. The 16x16
           indicator needs space on ALL sides, including in the narrower
           Game Object Properties cards and when the guard is disabled. */
        QCheckBox[adventureGuard="true"],
        QRadioButton[adventureGuard="true"] {
            padding:5px 8px; margin:0px; spacing:8px;
            min-height:18px;
        }
        QCheckBox[adventureGuard="true"]:enabled,
        QRadioButton[adventureGuard="true"]:enabled {
            border:1px solid @advGreenBorder; background-color:@advGreenBg;
        }
        QCheckBox[adventureGuard="true"]:disabled,
        QRadioButton[adventureGuard="true"]:disabled {
            border:1px solid @advRedBorder; background-color:@advRedBg;
            color:@disabledText;
        }
        QGroupBox[adventureGuard="true"]:enabled {
            border:1px solid @advGreenBorder;
        }
        QGroupBox[adventureGuard="true"]:disabled {
            border:1px solid @advRedBorder; background-color:@advRedBg;
        }
    )GGCONTROLS");
    const struct Pair { const char *token; QColor value; } values[] = {
        {"@window", theme.windowBackground},
        {"@tipBg", theme.tooltipBackground},
        {"@tipText", theme.tooltipText},
        {"@panel", theme.panelBackground},
        {"@alternate", theme.alternateBackground},
        {"@text", theme.text},
        {"@border", theme.border},
        {"@input", theme.inputBackground},
        {"@menu", theme.menuBackground},
        {"@accent", theme.accent},
        {"@chosen", chosen},
        {"@chosenText", chosenText},
        {"@hover", theme.hover},
        {"@hoverHandle", theme.scrollHandleHover},
        {"@scroll", theme.scrollHandle},
        {"@scrollHover", theme.scrollHandleHover},
        {"@disabledText", disabledText},
        {"@advGreenBg", adventureGreenBg},
        {"@advRedBg", adventureRedBg},
        {"@advGreenBorder", adventureGreenBorder},
        {"@advRedBorder", adventureRedBorder}
    };
    // Long placeholders first: @chosen must not consume @chosenText,
    // and @scroll must not consume @scrollHover.
    for (const Pair &v : values) {
        if (QString::fromLatin1(v.token) == QStringLiteral("@chosen") ||
            QString::fromLatin1(v.token) == QStringLiteral("@scroll") ||
            QString::fromLatin1(v.token) == QStringLiteral("@hover"))
            continue;
        css.replace(QString::fromLatin1(v.token), ideThemeColorName(v.value));
    }
    css.replace(QStringLiteral("@comboArrowDisabled"), ideComboDownArrowImageUrl(theme, true));
    css.replace(QStringLiteral("@comboArrow"), ideComboDownArrowImageUrl(theme));
    css.replace(QStringLiteral("@untick"), ideCheckedBoxImageUrl(theme, false));
    css.replace(QStringLiteral("@tick"), ideCheckedBoxImageUrl(theme));
    css.replace(QStringLiteral("@hover"), ideThemeColorName(theme.hover));
    css.replace(QStringLiteral("@chosen"), ideThemeColorName(chosen));
    css.replace(QStringLiteral("@scroll"), ideThemeColorName(theme.scrollHandle));
    return css;
}

// Qt can create a QComboBox popup as a separate top-level window. In
// particular KDE may paint that view using the system palette even when the
// QComboBox itself inherits the QApplication stylesheet. Style the REAL popup
// view instead of relying on a QSS descendant selector to reach it.
// This lives in the single shared theme header and works for new dialogs too.
class IDEComboPopupThemeFilter final : public QObject
{
public:
    explicit IDEComboPopupThemeFilter(QObject *parent = nullptr)
        : QObject(parent) {}

    void setIDETheme(const IDETheme &theme)
    {
        m_theme = theme;
    }

    void styleCombo(QComboBox *combo)
    {
        if (!combo)
            return;
        QAbstractItemView *view = combo->view();
        if (!view)
            return;

        const QColor selected = m_theme.accent.darker(230);
        const QColor selectedText = selected.lightnessF() < 0.52
            ? QColor(Qt::white) : QColor(Qt::black);
        const auto C = [](const QColor &colour) {
            return ideThemeColorName(colour);
        };

        // The popup's QStyle on KDE may ignore *application* QSS. The
        // per-combo stylesheet was what worked before centralisation. Keep
        // its rules here in the central manager and apply them to every combo
        // when it appears (including those created by future dialogs).
        static const char *comboBaseProperty = "_sidboxComboBaseStyle";
        if (!combo->property(comboBaseProperty).isValid())
            combo->setProperty(comboBaseProperty, combo->styleSheet());
        QString comboRules = QStringLiteral(R"IDECOMBOLOCAL(
            QComboBox {
                background-color:%1; color:%2; border:1px solid %3;
                border-radius:0px; padding:2px 25px 2px 5px;
                min-height:22px; combobox-popup:0;
                selection-background-color:%5; selection-color:%6;
            }
            QComboBox::drop-down {
                background-color:%7; border-left:1px solid %3;
                border-radius:0px; width:21px;
            }
            QComboBox::down-arrow {
                image:url("@localComboArrow"); width:12px; height:9px;
            }
            QComboBox::down-arrow:disabled {
                image:url("@localComboArrowDisabled"); width:12px; height:9px;
            }
            /* Guard controls need LOCAL rules because this per-combo QSS
               takes precedence over the application's global stylesheet. */
            QComboBox[adventureGuard="true"]:enabled {
                border:1px solid @localAdvGreen;
                background-color:@localAdvGreenBg;
            }
            QComboBox[adventureGuard="true"]:disabled {
                border:1px solid @localAdvRed;
                background-color:@localAdvRedBg;
                color:@localDisabledText;
            }
            QComboBox QAbstractItemView {
                background-color:%4; alternate-background-color:%8;
                color:%2; border:1px solid %3; border-radius:0px;
                outline:0px; selection-background-color:%5;
                selection-color:%6;
            }
            QComboBox QAbstractItemView::item {
                color:%2; padding:3px 5px; min-height:19px;
            }
            QComboBox QAbstractItemView::item:selected {
                background-color:%5; color:%6;
            }
            QComboBox[customChevron="true"]::down-arrow {
                image:none; width:0px; height:0px;
            }
        )IDECOMBOLOCAL")
            .arg(C(m_theme.inputBackground), C(m_theme.text),
                 C(m_theme.border), C(m_theme.menuBackground),
                 C(selected), C(selectedText), C(m_theme.panelBackground),
                 C(m_theme.alternateBackground));
        // Use the exact same colour blend and chevrons as the global theme.
        const auto blend = [](const QColor &base, const QColor &tint, int percent) {
            return QColor((base.red()*(100-percent)+tint.red()*percent)/100,
                          (base.green()*(100-percent)+tint.green()*percent)/100,
                          (base.blue()*(100-percent)+tint.blue()*percent)/100);
        };
        const bool lightTheme=m_theme.windowBackground.lightnessF()>0.55;
        const QColor green(lightTheme ? QStringLiteral("#267744") : QStringLiteral("#59c991"));
        const QColor red(lightTheme ? QStringLiteral("#b03f4b") : QStringLiteral("#dc7380"));
        const QColor disabledText=blend(m_theme.panelBackground,m_theme.mutedText,70);
        comboRules.replace(QStringLiteral("@localComboArrowDisabled"),
                           ideComboDownArrowImageUrl(m_theme,true));
        comboRules.replace(QStringLiteral("@localComboArrow"),
                           ideComboDownArrowImageUrl(m_theme));
        comboRules.replace(QStringLiteral("@localAdvGreenBg"),C(blend(m_theme.inputBackground,green,5)));
        comboRules.replace(QStringLiteral("@localAdvRedBg"),C(blend(m_theme.panelBackground,red,11)));
        comboRules.replace(QStringLiteral("@localAdvGreen"),C(blend(m_theme.border,green,48)));
        comboRules.replace(QStringLiteral("@localAdvRed"),C(blend(m_theme.border,red,58)));
        comboRules.replace(QStringLiteral("@localDisabledText"),C(disabledText));
        const QString newComboStyle = combo->property(comboBaseProperty).toString()
                                    + QStringLiteral("\n") + comboRules;
        if (combo->styleSheet() != newComboStyle)
            combo->setStyleSheet(newComboStyle);

        QPalette palette = ideGlobalControlPalette(m_theme);
        for (QPalette::ColorGroup group : {QPalette::Active, QPalette::Inactive}) {
            palette.setColor(group, QPalette::Base, m_theme.menuBackground);
            palette.setColor(group, QPalette::AlternateBase, m_theme.alternateBackground);
            palette.setColor(group, QPalette::Text, m_theme.text);
            palette.setColor(group, QPalette::Highlight, selected);
            palette.setColor(group, QPalette::HighlightedText, selectedText);
        }
        view->setPalette(palette);
        view->viewport()->setPalette(palette);
        view->viewport()->setAutoFillBackground(true);

        // Do not accumulate stylesheets when the user changes IDE themes.
        // Retain any view-specific rules that existed before the central theme.
        static const char *baseProperty = "_sidboxComboPopupBaseStyle";
        if (!view->property(baseProperty).isValid())
            view->setProperty(baseProperty, view->styleSheet());
        const QString popupStyle = QStringLiteral(R"IDECOMBO(
            QAbstractItemView, QListView, QTreeView {
                background-color:%1; alternate-background-color:%2;
                color:%3; border:1px solid %4; border-radius:0px;
                outline:0px; selection-background-color:%5;
                selection-color:%6;
            }
            QListView::item, QTreeView::item {
                color:%3; padding:3px 5px; min-height:19px;
            }
            QListView::item:selected, QTreeView::item:selected {
                background-color:%5; color:%6;
            }
            QScrollBar:vertical {
                width:10px; min-width:10px; max-width:10px;
                margin:0px; background:%7; border:0px; border-radius:0px;
            }
            QScrollBar::handle:vertical {
                background:%8; min-height:18px; border-radius:0px;
            }
            QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
                height:0px; border:0px;
            }
        )IDECOMBO")
            .arg(C(m_theme.menuBackground), C(m_theme.alternateBackground),
                 C(m_theme.text), C(m_theme.border), C(selected),
                 C(selectedText), C(m_theme.panelBackground),
                 C(m_theme.scrollHandle));
        const QString combined = view->property(baseProperty).toString()
                               + QStringLiteral("\n") + popupStyle;
        if (view->styleSheet() != combined)
            view->setStyleSheet(combined);

        // The containing QFrame can otherwise keep the KDE menu background.
        QWidget *popupWindow = view->window();
        if (popupWindow && popupWindow != combo->window()) {
            popupWindow->setPalette(palette);
            popupWindow->setAutoFillBackground(true);
            const QString frameStyle = QStringLiteral(
                "background-color:%1; color:%2; border:1px solid %3; "
                "border-radius:0px;")
                .arg(C(m_theme.menuBackground), C(m_theme.text),
                     C(m_theme.border));
            if (popupWindow->styleSheet() != frameStyle)
                popupWindow->setStyleSheet(frameStyle);
        }
    }

protected:
    bool eventFilter(QObject *watched, QEvent *event) override
    {
        // Catch both the combo's first show and its popup's Show. Some
        // platform styles initialise the popup only when it first opens,
        // after the combo's initial show event has already run.
        if (event->type() == QEvent::Show) {
            if (auto *combo = qobject_cast<QComboBox *>(watched)) {
                styleCombo(combo);
            } else if (watched->inherits("QComboBoxPrivateContainer")) {
                if (auto *popup = qobject_cast<QWidget *>(watched)) {
                    if (auto *combo = qobject_cast<QComboBox *>(popup->parentWidget()))
                        styleCombo(combo);
                }
            }
        }
        return QObject::eventFilter(watched, event);
    }

private:
    IDETheme m_theme = defaultIDETheme();
};

inline void ideApplyComboPopupTheme(const IDETheme &theme)
{
    static QPointer<IDEComboPopupThemeFilter> filter;
    if (!filter) {
        filter = new IDEComboPopupThemeFilter(qApp);
        qApp->installEventFilter(filter);
    }
    filter->setIDETheme(theme);
    // When a theme is changed while the IDE is open, repaint popups of all
    // existing combos, not only those opened after the change.
    for (QWidget *widget : QApplication::allWidgets()) {
        if (auto *combo = qobject_cast<QComboBox *>(widget))
            filter->styleCombo(combo);
    }
}

#endif // SIDBOX_IDE_GLOBAL_THEME_H

