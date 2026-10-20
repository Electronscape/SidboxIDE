#ifndef GAMEEDITORCONTROLSTYLE_H
#define GAMEEDITORCONTROLSTYLE_H

#include "idetheme.h"
#include <QString>

// One control language for the World Designer and Tilemap Editor. The Player
// Animation Toolkit and Game Object Properties use the same control language:
// square edges, framed inputs, accent-coloured states and compact spacing.
// Use actual IDETheme values (including light themes), never hard-coded hues.
// Keep this scoped to INTERFACE CONTROLS; editor canvases paint their own art.
inline QString gameEditorControlStyle(const IDETheme &theme)
{
    const QColor chosen = theme.accent.darker(230);
    const QColor chosenText = chosen.lightnessF() < 0.52
        ? QColor(Qt::white) : QColor(Qt::black);
    // Disabled foreground must be readable in both light and dark themes.
    const QColor disabledText = QColor::fromRgbF(
        theme.mutedText.redF() * 0.7 + theme.panelBackground.redF() * 0.3,
        theme.mutedText.greenF() * 0.7 + theme.panelBackground.greenF() * 0.3,
        theme.mutedText.blueF() * 0.7 + theme.panelBackground.blueF() * 0.3);

    QString css = QStringLiteral(R"GGCONTROLS(
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
        QComboBox, QSpinBox, QDoubleSpinBox, QLineEdit {
            background:@input; color:@text; border:1px solid @border;
            border-radius:0px; padding:4px 5px; min-height:22px;
            selection-background-color:@chosen;
            selection-color:@chosenText;
        }
        QComboBox { padding-right:25px; }
        QComboBox::drop-down {
            width:21px; border-left:1px solid @border;
            border-radius:0px; background:@panel;
        }
        /* GameComboBox / TilemapComboBox paint their own high-contrast chevrons. */
        QComboBox::down-arrow { image:none; width:0px; height:0px; }
        QComboBox:focus, QSpinBox:focus, QDoubleSpinBox:focus,
        QLineEdit:focus { border:1px solid @accent; }
        QComboBox:disabled, QSpinBox:disabled, QDoubleSpinBox:disabled,
        QLineEdit:disabled { background:@panel; color:@disabledText; }
        QComboBox QAbstractItemView {
            background:@menu; color:@text; border:1px solid @border;
            border-radius:0px; outline:0px;
            selection-background-color:@chosen;
            selection-color:@chosenText;
        }
        QComboBox QAbstractItemView::item:selected {
            background:@chosen; color:@chosenText;
        }
        QCheckBox, QRadioButton { color:@text; background:transparent;
            spacing:7px; }
        QCheckBox::indicator {
            width:16px; height:16px; border:1px solid @border;
            border-radius:0px; background:@input;
        }
        QCheckBox::indicator:hover:!disabled { border:1px solid @accent; }
        QCheckBox::indicator:checked {
            background:@accent; border:1px solid @accent;
        }
        QCheckBox::indicator:disabled { background:@panel; border-color:@border; }
        QRadioButton::indicator {
            width:14px; height:14px; border:2px solid @border;
            background:@input; border-radius:0px;
        }
        QRadioButton::indicator:checked { background:@accent;
            border-color:@accent; }
        QRadioButton::indicator:disabled { background:@panel; }
        QCheckBox:disabled, QRadioButton:disabled { color:@disabledText; }
        QSlider::groove:horizontal { height:6px; background:@border;
            border:0px; border-radius:0px; }
        QSlider::sub-page:horizontal { background:@accent; border-radius:0px; }
        QSlider::handle:horizontal {
            background:@accent; border:1px solid @text; border-radius:0px;
            width:12px; margin:-6px 0;
        }
        QSlider::handle:horizontal:hover { background:@hoverHandle;
            border:1px solid @accent; }
        QSlider::groove:vertical { width:6px; background:@border;
            border:0px; border-radius:0px; }
        QSlider::sub-page:vertical { background:@accent; border-radius:0px; }
        QSlider::handle:vertical {
            background:@accent; border:1px solid @text; border-radius:0px;
            height:12px; margin:0 -6px;
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
        QScrollBar:horizontal, QScrollBar:vertical {
            background:@panel; border:0px; border-radius:0px;
        }
        QScrollBar::handle:horizontal, QScrollBar::handle:vertical {
            background:@scroll; border-radius:0px;
            min-width:18px; min-height:18px;
        }
        QScrollBar::handle:horizontal:hover,
        QScrollBar::handle:vertical:hover { background:@scrollHover; }
        QScrollBar::add-line, QScrollBar::sub-line { width:0px; height:0px;
            border:0px; background:transparent; }
        QScrollBar::add-page, QScrollBar::sub-page { background:transparent; }
        QTreeWidget, QListWidget, QTableWidget {
            background:@panel; color:@text; border:1px solid @border;
            border-radius:0px; outline:0px; }
        QTreeWidget::item:selected, QTableWidget::item:selected {
            background:@chosen; color:@chosenText;
        }
        QTreeWidget::item:hover:!selected { background:@hover; }
        QHeaderView::section { background:@panel; color:@text;
            border:1px solid @border; padding:4px; border-radius:0px; }
        QFrame, QScrollArea, QGraphicsView, QSplitter { border-radius:0px; }
    )GGCONTROLS");
    const struct Pair { const char *token; QColor value; } values[] = {
        {"@panel", theme.panelBackground},
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
        {"@disabledText", disabledText}
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
    css.replace(QStringLiteral("@hover"), ideThemeColorName(theme.hover));
    css.replace(QStringLiteral("@chosen"), ideThemeColorName(chosen));
    css.replace(QStringLiteral("@scroll"), ideThemeColorName(theme.scrollHandle));
    return css;
}

#endif // GAMEEDITORCONTROLSTYLE_H
