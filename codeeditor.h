#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>
#include <QList>
#include <QString>
#include <QStringList>
#include "idetheme.h"

class CSyntaxHighlighter;
class QCompleter;
class QFont;
class QPaintEvent;
class QResizeEvent;
class QStringListModel;
class QWidget;

struct EditorDiagnostic
{
    enum class Severity {
        Error,
        Warning
    };

    int line = -1;        // zero-based source line
    int column = -1;      // zero-based column, or -1 when the compiler omitted it
    Severity severity = Severity::Error;
    QString message;
};

class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    explicit CodeEditor(QWidget *parent = nullptr);
    ~CodeEditor() override;

    QString filePath() const;
    void setFilePath(const QString &path);
    void setFunctionCompletions(const QStringList &signatures);
    void setProjectTypeNames(const QStringList &typeNames);
    void setApiSyntaxNames(const QStringList &apiNames);
    void setResourceMode(bool enabled);
    bool isResourceMode() const;
    void showMemberCompletions(const QStringList &members, const QString &prefix);
    void refreshMemberCompletion();
    void setCompletionFont(const QFont &font);
    void setTheme(const IDETheme &theme);
    const IDETheme &theme() const;

    const QList<EditorDiagnostic> &diagnostics() const;
    void setDiagnostics(const QList<EditorDiagnostic> &diagnostics);
    void clearDiagnostics();
    QString diagnosticToolTipAtY(int y) const;

    bool loadFromFile(const QString &path, bool deferSyntaxHighlighting = false);
    void enableSyntaxHighlighting();
    bool save();
    bool saveAs(const QString &path);
    void shareDocumentFrom(CodeEditor *sourceEditor);

    int lineNumberAreaWidth() const;
    void refreshLineNumberAreaWidth();
    void lineNumberAreaPaintEvent(QPaintEvent *event);

signals:
    void quickTipRequested(const QString &symbol);
    void quickTipCandidateChanged(const QString &symbol);
    void definitionRequested(const QString &symbol, int sourceLine);
    void includeFileRequested(const QString &includeName);
    void memberCompletionRequested(const QString &objectName,
                                   int sourceLine,
                                   const QString &prefix);

protected:
    void focusInEvent(QFocusEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    /*
     * Keep the theme before the child widgets in declaration order.
     * LineNumberArea asks CodeEditor for its theme from inside its constructor,
     * so m_theme must already be fully constructed at that point.
     */
    IDETheme m_theme;

    void updateLineNumberAreaWidth(int newBlockCount);
    void updateLineNumberArea(const QRect &rect, int dy);
    void highlightCurrentLine();
    QString textUnderCursor() const;
    void insertFunctionCompletion(const QString &signature);
    void insertMemberCompletion(const QString &member);
    bool requestMemberCompletionAtCursor();
    void restoreFunctionCompletionModel();
    void selectArgument(int index);
    int indentWidthColumns() const;
    QString leadingWhitespace(const QString &text) const;
    void insertAutoIndent();
    bool handleAutoPairKey(QKeyEvent *event);
    bool handlePairedBackspace(QKeyEvent *event);
    void indentSelection();
    void unindentSelection();
    void drawIndentGuides(QPaintEvent *event);

    QWidget *m_lineNumberArea;
    QWidget *m_minimap;
    QString m_filePath;
    CSyntaxHighlighter *m_highlighter;
    QCompleter *m_completer;
    QStringListModel *m_completionModel;
    QStringList m_functionCompletions;
    QStringList m_projectTypeNames;
    QStringList m_apiSyntaxNames;
    QString m_memberCompletionPrefix;
    bool m_memberCompletionActive = false;
    bool m_resourceMode = false;
    QList<QPair<int, int>> m_argumentRanges;
    QList<EditorDiagnostic> m_diagnostics;
    int m_selectedArgument;
};

#endif // CODEEDITOR_H
