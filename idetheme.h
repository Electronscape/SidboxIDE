#ifndef IDETHEME_H
#define IDETHEME_H

#include <QColor>
#include <QList>

struct IDETheme
{
    // Main interface
    QColor windowBackground;
    QColor panelBackground;
    QColor inputBackground;
    QColor alternateBackground;
    QColor menuBackground;
    QColor text;
    QColor brightText;
    QColor mutedText;
    QColor accent;
    QColor hover;
    QColor border;
    QColor treeBorder;
    QColor scrollHandle;
    QColor scrollHandleHover;
    QColor tooltipBackground;
    QColor tooltipText;

    // Editor
    QColor editorBackground;
    QColor editorText;
    QColor currentLine;
    QColor gutterBackground;
    QColor lineNumber;
    QColor indentGuide;
    QColor selectionBackground;
    QColor selectionText;

    // Syntax
    QColor syntaxKeyword;
    QColor syntaxSTM32;
    QColor syntaxAPI;
    QColor syntaxType;
    QColor syntaxPreprocessor;
    QColor syntaxString;
    QColor syntaxNumber;
    QColor syntaxFunction;
    QColor syntaxComment;
    QColor syntaxMultiComment;

    // Diagnostics
    QColor diagnosticError;
    QColor diagnosticWarning;
    QColor diagnosticPopupBackground;
    QColor diagnosticPopupText;
    QColor diagnosticColumn;

    // Minimap
    QColor minimapBackground;
    QColor minimapText;
    QColor minimapComment;
    QColor minimapPreprocessor;
    QColor minimapType;
    QColor minimapString;
    QColor minimapFunction;
    QColor minimapViewportFill;
    QColor minimapViewportBorder;
    QColor minimapDivider;

    // Output / API hint
    QColor outputBackground;
    QColor outputNormal;
    QColor outputHeader;
    QColor outputPath;
    QColor outputSuccess;
    QColor outputError;
    QColor outputWarning;
    QColor outputMuted;
    QColor quickTipBackground;
    QColor quickTipText;
    QColor quickTipBorder;
};

inline IDETheme defaultIDETheme()
{
    IDETheme t;

    // Main interface: current Sidbox look.
    t.windowBackground = QColor("#101010");
    t.panelBackground = QColor("#101010");
    t.inputBackground = QColor("#050505");
    t.alternateBackground = QColor("#0b0b0b");
    t.menuBackground = QColor("#080808");
    t.text = QColor("#d8d8d8");
    t.brightText = QColor("#ffffff");
    t.mutedText = QColor("#aaaaaa");
    t.accent = QColor("#2858A8");
    t.hover = QColor("#202020");
    t.border = QColor("#303030");
    t.treeBorder = QColor("#102048");
    t.scrollHandle = QColor("#303030");
    t.scrollHandleHover = QColor("#505050");
    t.tooltipBackground = QColor("#07090d");
    t.tooltipText = QColor("#f2f2f2");

    // Editor.
    t.editorBackground = QColor("#001020");
    t.editorText = QColor("#d8e8d0");
    t.currentLine = QColor("#00172d");
    t.gutterBackground = QColor("#002030");
    t.lineNumber = QColor("#00ff40");
    t.indentGuide = QColor("#103838");
    t.selectionBackground = QColor("#2858A8");
    t.selectionText = QColor("#ffffff");

    // Syntax: values from the current highlighter.
    t.syntaxKeyword = QColor(255, 200, 0);
    t.syntaxSTM32 = QColor(72, 176, 176);
    t.syntaxAPI = QColor("#ff00ff");
    t.syntaxType = QColor(80, 255, 80);
    t.syntaxPreprocessor = QColor(0, 255, 255);
    t.syntaxString = QColor(206, 145, 120);
    t.syntaxNumber = QColor(0, 206, 0);
    t.syntaxFunction = QColor(200, 132, 192);
    t.syntaxComment = QColor(106, 153, 85);
    t.syntaxMultiComment = QColor(130, 150, 125);

    // Diagnostics.
    t.diagnosticError = QColor(255, 70, 70);
    t.diagnosticWarning = QColor(255, 205, 55);
    t.diagnosticPopupBackground = QColor("#08090d");
    t.diagnosticPopupText = QColor("#f2f2f2");
    t.diagnosticColumn = QColor("#9fb7d7");

    // Minimap.
    t.minimapBackground = QColor("#030303");
    t.minimapText = QColor(105, 120, 135);
    t.minimapComment = QColor(90, 135, 78);
    t.minimapPreprocessor = QColor(0, 190, 210);
    t.minimapType = QColor(220, 175, 45);
    t.minimapString = QColor(190, 125, 105);
    t.minimapFunction = QColor(175, 115, 170);
    t.minimapViewportFill = QColor(40, 88, 168, 45);
    t.minimapViewportBorder = QColor(80, 130, 220, 180);
    t.minimapDivider = QColor(35, 35, 35);

    // Output.
    t.outputBackground = QColor("#000000");
    t.outputNormal = QColor(220, 235, 210);
    t.outputHeader = QColor(120, 220, 255);
    t.outputPath = QColor(170, 205, 255);
    t.outputSuccess = QColor(80, 255, 120);
    t.outputError = QColor(255, 90, 90);
    t.outputWarning = QColor(255, 210, 90);
    t.outputMuted = QColor(150, 165, 150);
    t.quickTipBackground = QColor("#020402");
    t.quickTipText = QColor("#66ff8a");
    t.quickTipBorder = QColor("#15351a");

    return t;
}

struct IDEThemeColorField
{
    const char *key;
    QColor IDETheme::*member;
};

inline const QList<IDEThemeColorField> &ideThemeColorFields()
{
    static const QList<IDEThemeColorField> fields = {
        {"windowBackground", &IDETheme::windowBackground},
        {"panelBackground", &IDETheme::panelBackground},
        {"inputBackground", &IDETheme::inputBackground},
        {"alternateBackground", &IDETheme::alternateBackground},
        {"menuBackground", &IDETheme::menuBackground},
        {"text", &IDETheme::text},
        {"brightText", &IDETheme::brightText},
        {"mutedText", &IDETheme::mutedText},
        {"accent", &IDETheme::accent},
        {"hover", &IDETheme::hover},
        {"border", &IDETheme::border},
        {"treeBorder", &IDETheme::treeBorder},
        {"scrollHandle", &IDETheme::scrollHandle},
        {"scrollHandleHover", &IDETheme::scrollHandleHover},
        {"tooltipBackground", &IDETheme::tooltipBackground},
        {"tooltipText", &IDETheme::tooltipText},

        {"editorBackground", &IDETheme::editorBackground},
        {"editorText", &IDETheme::editorText},
        {"currentLine", &IDETheme::currentLine},
        {"gutterBackground", &IDETheme::gutterBackground},
        {"lineNumber", &IDETheme::lineNumber},
        {"indentGuide", &IDETheme::indentGuide},
        {"selectionBackground", &IDETheme::selectionBackground},
        {"selectionText", &IDETheme::selectionText},

        {"syntaxKeyword", &IDETheme::syntaxKeyword},
        {"syntaxSTM32", &IDETheme::syntaxSTM32},
        {"syntaxAPI", &IDETheme::syntaxAPI},
        {"syntaxType", &IDETheme::syntaxType},
        {"syntaxPreprocessor", &IDETheme::syntaxPreprocessor},
        {"syntaxString", &IDETheme::syntaxString},
        {"syntaxNumber", &IDETheme::syntaxNumber},
        {"syntaxFunction", &IDETheme::syntaxFunction},
        {"syntaxComment", &IDETheme::syntaxComment},
        {"syntaxMultiComment", &IDETheme::syntaxMultiComment},

        {"diagnosticError", &IDETheme::diagnosticError},
        {"diagnosticWarning", &IDETheme::diagnosticWarning},
        {"diagnosticPopupBackground", &IDETheme::diagnosticPopupBackground},
        {"diagnosticPopupText", &IDETheme::diagnosticPopupText},
        {"diagnosticColumn", &IDETheme::diagnosticColumn},

        {"minimapBackground", &IDETheme::minimapBackground},
        {"minimapText", &IDETheme::minimapText},
        {"minimapComment", &IDETheme::minimapComment},
        {"minimapPreprocessor", &IDETheme::minimapPreprocessor},
        {"minimapType", &IDETheme::minimapType},
        {"minimapString", &IDETheme::minimapString},
        {"minimapFunction", &IDETheme::minimapFunction},
        {"minimapViewportFill", &IDETheme::minimapViewportFill},
        {"minimapViewportBorder", &IDETheme::minimapViewportBorder},
        {"minimapDivider", &IDETheme::minimapDivider},

        {"outputBackground", &IDETheme::outputBackground},
        {"outputNormal", &IDETheme::outputNormal},
        {"outputHeader", &IDETheme::outputHeader},
        {"outputPath", &IDETheme::outputPath},
        {"outputSuccess", &IDETheme::outputSuccess},
        {"outputError", &IDETheme::outputError},
        {"outputWarning", &IDETheme::outputWarning},
        {"outputMuted", &IDETheme::outputMuted},
        {"quickTipBackground", &IDETheme::quickTipBackground},
        {"quickTipText", &IDETheme::quickTipText},
        {"quickTipBorder", &IDETheme::quickTipBorder}
    };
    return fields;
}

inline QString ideThemeColorName(const QColor &color)
{
    return color.name(color.alpha() == 255 ? QColor::HexRgb : QColor::HexArgb);
}

#endif // IDETHEME_H
