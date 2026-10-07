#include "codeeditor.h"

#include "csyntaxhighlighter.h"

#include <algorithm>
#include <QAbstractItemView>
#include <QCompleter>
#include <QFile>
#include <QFocusEvent>
#include <QFont>
#include <QFontDatabase>
#include <QKeyEvent>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QColor>
#include <QToolTip>
#include <QHelpEvent>
#include <QEvent>
#include <QRegularExpression>
#include <QScrollBar>
#include <QStringListModel>
#include <QTextBlock>
#include <QTextEdit>
#include <QTextDocument>
#include <QTextStream>
#include <QWidget>

namespace {
constexpr int CodeMinimapWidth = 92;

class CodeMinimap : public QWidget
{
public:
    explicit CodeMinimap(CodeEditor *editor)
        : QWidget(editor)
        , m_editor(editor)
        , m_dragging(false)
    {
        setCursor(Qt::PointingHandCursor);
        setMouseTracking(true);
        setAttribute(Qt::WA_OpaquePaintEvent);

        connect(editor->document(), &QTextDocument::contentsChanged, this, [this]() {
            update();
        });
        connect(editor->verticalScrollBar(), &QScrollBar::valueChanged, this, [this]() {
            update();
        });
        connect(editor->verticalScrollBar(), &QScrollBar::rangeChanged, this, [this](int, int) {
            update();
        });
    }

protected:
    void paintEvent(QPaintEvent *) override
    {
        QPainter painter(this);
        painter.fillRect(rect(), m_editor->theme().minimapBackground);

        if (!m_editor) {
            return;
        }

        const QStringList lines = m_editor->toPlainText().split(QLatin1Char('\n'));
        const int lineCount = qMax(1, lines.size());
        const qreal usableHeight = qMax(1, height() - 2);
        //const qreal yScale = usableHeight / static_cast<qreal>(lineCount);
        const qreal yScale = qMin<qreal>(
            3.0,
            usableHeight / static_cast<qreal>(lineCount)
            );

        for (int i = 0; i < lines.size(); ++i) {
            const QString &line = lines.at(i);
            const QString trimmed = line.trimmed();
            if (trimmed.isEmpty()) {
                continue;
            }

            int leadingSpaces = 0;
            while (leadingSpaces < line.size() && line.at(leadingSpaces).isSpace()) {
                ++leadingSpaces;
            }

            const int x = qMin(width() - 4, 3 + leadingSpaces / 2);
            const int visibleChars = qMin(120, qMax(1, trimmed.size()));
            const int lineWidth = qMin(width() - x - 2, qMax(2, visibleChars / 2));
            const int y = 1 + qRound(i * yScale);

            QColor lineColor = m_editor->theme().minimapText;
            if (trimmed.startsWith(QStringLiteral("//"))
                || trimmed.startsWith(QStringLiteral("/*"))
                || trimmed.startsWith(QLatin1Char('*'))) {
                lineColor = m_editor->theme().minimapComment;
            } else if (trimmed.startsWith(QLatin1Char('#'))) {
                lineColor = m_editor->theme().minimapPreprocessor;
            } else if (trimmed.startsWith(QStringLiteral("typedef"))
                       || trimmed.startsWith(QStringLiteral("struct"))
                       || trimmed.startsWith(QStringLiteral("enum"))) {
                lineColor = m_editor->theme().minimapType;
            } else if (trimmed.contains(QLatin1Char('"'))
                       || trimmed.contains(QLatin1Char('\''))) {
                lineColor = m_editor->theme().minimapString;
            } else if (trimmed.contains(QLatin1Char('('))
                       && trimmed.contains(QLatin1Char(')'))) {
                lineColor = m_editor->theme().minimapFunction;
            }

            painter.setPen(lineColor);
            painter.drawLine(x, y, x + lineWidth, y);
        }

        QScrollBar *bar = m_editor->verticalScrollBar();
        const int maximum = bar->maximum();
        const int pageStep = qMax(1, bar->pageStep());
        const int totalRange = maximum + pageStep;

        qreal viewTop = 0.0;
        qreal viewHeight = height();
        if (maximum > 0 && totalRange > 0) {
            viewTop = (static_cast<qreal>(bar->value()) / totalRange) * height();
            viewHeight = (static_cast<qreal>(pageStep) / totalRange) * height();
            viewHeight = qMax<qreal>(12.0, viewHeight);
            if (viewTop + viewHeight > height()) {
                viewTop = qMax<qreal>(0.0, height() - viewHeight);
            }
        }

        const QRectF viewportRect(1.5, viewTop + 0.5, width() - 2.0, qMin<qreal>(viewHeight, height()) - 1.0);
        painter.fillRect(viewportRect, m_editor->theme().minimapViewportFill);
        painter.setPen(m_editor->theme().minimapViewportBorder);
        painter.drawRect(viewportRect);

        // Compiler diagnostics: thin ticks on the far-right edge.
        // Warnings are painted first so an error wins when both share a line.
        const int markerWidth = 5;
        const int markerHeight = qMax(2, qRound(yScale));

        painter.setPen(Qt::NoPen);

        auto paintDiagnostics = [&](EditorDiagnostic::Severity severity, const QColor &color) {
            painter.setBrush(color);

            for (const EditorDiagnostic &diagnostic : m_editor->diagnostics()) {
                if (diagnostic.severity != severity
                    || diagnostic.line < 0
                    || diagnostic.line >= lineCount) {
                    continue;
                }

                const int y = qBound(
                    0,
                    1 + qRound(diagnostic.line * yScale) - markerHeight / 2,
                    qMax(0, height() - markerHeight));

                painter.drawRect(width() - markerWidth, y, markerWidth, markerHeight);
            }
        };

        paintDiagnostics(
            EditorDiagnostic::Severity::Warning,
            m_editor->theme().diagnosticWarning);
        paintDiagnostics(
            EditorDiagnostic::Severity::Error,
            m_editor->theme().diagnosticError);

        painter.setBrush(Qt::NoBrush);
        painter.setPen(m_editor->theme().minimapDivider);
        painter.drawLine(0, 0, 0, height());
    }

    void mousePressEvent(QMouseEvent *event) override
    {
        if (event->button() == Qt::LeftButton) {
            if (event->position().x() >= width() - 10
                && jumpToDiagnosticAtY(event->position().y())) {
                event->accept();
                return;
            }

            m_dragging = true;
            scrollToY(event->position().y());
            event->accept();
            return;
        }
        QWidget::mousePressEvent(event);
    }

    void mouseMoveEvent(QMouseEvent *event) override
    {
        if (m_dragging && (event->buttons() & Qt::LeftButton)) {
            scrollToY(event->position().y());
            event->accept();
            return;
        }
        QWidget::mouseMoveEvent(event);
    }

    void mouseReleaseEvent(QMouseEvent *event) override
    {
        if (event->button() == Qt::LeftButton) {
            m_dragging = false;
            event->accept();
            return;
        }
        QWidget::mouseReleaseEvent(event);
    }

private:
    bool jumpToDiagnosticAtY(qreal y)
    {
        if (!m_editor || height() <= 1) {
            return false;
        }

        const int lineCount = qMax(1, m_editor->blockCount());
        const qreal usableHeight = qMax(1, height() - 2);
        const qreal yScale = qMin<qreal>(
            3.0,
            usableHeight / static_cast<qreal>(lineCount));

        int bestLine = -1;
        qreal bestDistance = 1000000.0;

        for (const EditorDiagnostic &diagnostic : m_editor->diagnostics()) {
            if (diagnostic.line < 0 || diagnostic.line >= lineCount) {
                continue;
            }

            const qreal markerY = 1.0 + diagnostic.line * yScale;
            const qreal distance = qAbs(markerY - y);
            if (distance < bestDistance) {
                bestDistance = distance;
                bestLine = diagnostic.line;
            }
        }

        const qreal hitDistance = qMax<qreal>(4.0, yScale * 2.0);
        if (bestLine < 0 || bestDistance > hitDistance) {
            return false;
        }

        const QTextBlock block = m_editor->document()->findBlockByNumber(bestLine);
        if (!block.isValid()) {
            return false;
        }

        QTextCursor cursor(block);
        m_editor->setTextCursor(cursor);
        m_editor->centerCursor();
        m_editor->setFocus();
        return true;
    }

    void scrollToY(qreal y)
    {
        if (!m_editor || height() <= 1) {
            return;
        }

        QScrollBar *bar = m_editor->verticalScrollBar();
        const qreal ratio = qBound<qreal>(0.0, y / static_cast<qreal>(height()), 1.0);
        bar->setValue(qRound(ratio * bar->maximum()));
    }

    CodeEditor *m_editor;
    bool m_dragging;
};

class LineNumberArea : public QWidget
{
    public:
        explicit LineNumberArea(CodeEditor *editor)
            : QWidget(editor)
            , m_editor(editor)
            , m_diagnosticPopup(new QLabel(nullptr, Qt::ToolTip | Qt::FramelessWindowHint))
        {
            setMouseTracking(true);

            /*
             * This is deliberately a QLabel popup rather than QToolTip.
             * That means it is completely independent of the application's
             * global QToolTip stylesheet.
             */
            m_diagnosticPopup->setObjectName(QStringLiteral("compilerDiagnosticPopup"));
            m_diagnosticPopup->setTextFormat(Qt::RichText);
            m_diagnosticPopup->setWordWrap(true);
            m_diagnosticPopup->setFixedWidth(620);
            m_diagnosticPopup->setMargin(0);
            m_diagnosticPopup->setAttribute(Qt::WA_ShowWithoutActivating);
            const IDETheme &theme = m_editor->theme();
            m_diagnosticPopup->setStyleSheet(QStringLiteral(
                "QLabel#compilerDiagnosticPopup {"
                " background-color:%1;"
                " color:%2;"
                " border:2px solid %3;"
                " padding:12px 16px;"
                " font-size:14px;"
                " font-weight:500;"
                "}")
                .arg(ideThemeColorName(theme.diagnosticPopupBackground),
                     ideThemeColorName(theme.diagnosticPopupText),
                     ideThemeColorName(theme.diagnosticError)));
            m_diagnosticPopup->hide();
        }

        ~LineNumberArea() override
        {
            delete m_diagnosticPopup;
        }

        QSize sizeHint() const override
        {
            return QSize(m_editor->lineNumberAreaWidth(), 0);
        }

    protected:
        void paintEvent(QPaintEvent *event) override
        {
            m_editor->lineNumberAreaPaintEvent(event);
        }

        void mouseMoveEvent(QMouseEvent *event) override
        {
            const QString tip =
                m_editor->diagnosticToolTipAtY(qRound(event->position().y()));

            if (!tip.isEmpty()) {
                /*
                 * Change the popup border depending on the most important
                 * diagnostic on this line. Error wins over warning.
                 */
                const bool hasError = tip.contains(QStringLiteral("ERROR"));
                const IDETheme &theme = m_editor->theme();
                const QColor borderColour =
                    hasError ? theme.diagnosticError
                             : theme.diagnosticWarning;

                m_diagnosticPopup->setStyleSheet(QStringLiteral(
                    "QLabel#compilerDiagnosticPopup {"
                    " background-color:%1;"
                    " color:%2;"
                    " border:2px solid %3;"
                    " padding:12px 16px;"
                    " font-size:14px;"
                    " font-weight:500;"
                    "}")
                    .arg(ideThemeColorName(theme.diagnosticPopupBackground),
                         ideThemeColorName(theme.diagnosticPopupText),
                         ideThemeColorName(borderColour)));

                m_diagnosticPopup->setText(tip);
                m_diagnosticPopup->adjustSize();

                const QPoint globalPos =
                    event->globalPosition().toPoint() + QPoint(16, 16);

                m_diagnosticPopup->move(globalPos);
                m_diagnosticPopup->show();
                m_diagnosticPopup->raise();
            } else {
                m_diagnosticPopup->hide();
            }

            QWidget::mouseMoveEvent(event);
        }

        void leaveEvent(QEvent *event) override
        {
            m_diagnosticPopup->hide();
            QWidget::leaveEvent(event);
        }

        bool event(QEvent *event) override
        {
            /*
             * Swallow Qt's normal delayed tooltip event. Diagnostics are shown
             * immediately by mouseMoveEvent() using our custom popup instead.
             */
            if (event->type() == QEvent::ToolTip) {
                event->accept();
                return true;
            }

            return QWidget::event(event);
        }

    private:
        CodeEditor *m_editor;
        QLabel *m_diagnosticPopup;
    };

    QString functionNameFromSignature(const QString &signature)
    {
        const int parenIndex = signature.indexOf(QLatin1Char('('));
        if (parenIndex < 0) {
            return signature.trimmed();
        }

        return signature.left(parenIndex).trimmed();
    }

    QStringList splitFunctionArguments(const QString &signature)
    {
        const int openIndex = signature.indexOf(QLatin1Char('('));
        const int closeIndex = signature.lastIndexOf(QLatin1Char(')'));
        if (openIndex < 0 || closeIndex <= openIndex) {
            return {};
        }

        const QString argumentText = signature.mid(openIndex + 1, closeIndex - openIndex - 1).trimmed();
        if (argumentText.isEmpty() || argumentText == QStringLiteral("void")) {
            return {};
        }

        QStringList arguments;
        for (const QString &rawArgument : argumentText.split(QLatin1Char(','))) {
            const QString argument = rawArgument.trimmed();
            if (!argument.isEmpty()) {
                arguments.append(argument);
            }
        }

        return arguments;
    }

    QString placeholderForArgument(const QString &argument, int index)
    {
        if (argument == QStringLiteral("...")) {
            return QStringLiteral("...");
        }

        static const QRegularExpression identifierExpression(QStringLiteral("([A-Za-z_][A-Za-z0-9_]*)\\s*(?:\\[[^\\]]*\\])?$"));
        const QRegularExpressionMatch match = identifierExpression.match(argument);
        if (match.hasMatch()) {
            const QString name = match.captured(1);
            if (name != QStringLiteral("const") && name != QStringLiteral("volatile")) {
                return name;
            }
        }

        return QStringLiteral("arg%1").arg(index + 1);
    }
}

CodeEditor::CodeEditor(QWidget *parent) : QPlainTextEdit(parent)
    , m_theme(defaultIDETheme())
    , m_lineNumberArea(new LineNumberArea(this))
    , m_minimap(new CodeMinimap(this))
    , m_highlighter(new CSyntaxHighlighter(document()))
    , m_completer(new QCompleter(this))
    , m_completionModel(new QStringListModel(this))
    , m_selectedArgument(-1)
{
    const QFont fixedFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    setFont(fixedFont);
    setLineWrapMode(QPlainTextEdit::NoWrap);
    setTabStopDistance(fontMetrics().horizontalAdvance(QLatin1Char(' ')) * 4);
    setMouseTracking(true);
    viewport()->setMouseTracking(true);
    document()->setModified(false);


    connect(this, &CodeEditor::blockCountChanged, this, &CodeEditor::updateLineNumberAreaWidth);
    connect(this, &CodeEditor::updateRequest, this, &CodeEditor::updateLineNumberArea);
    connect(this, &CodeEditor::cursorPositionChanged, this, &CodeEditor::highlightCurrentLine);
    connect(this, &CodeEditor::cursorPositionChanged, this, [this]() {
        emit quickTipCandidateChanged(textUnderCursor());
    });
    connect(this, &CodeEditor::updateRequest, this, [this](const QRect &, int) {
        m_minimap->update();
    });
    updateLineNumberAreaWidth(4);
    highlightCurrentLine();

    m_completer->setModel(m_completionModel);
    m_completer->setWidget(this);
    m_completer->setCaseSensitivity(Qt::CaseInsensitive);
    m_completer->setCompletionMode(QCompleter::PopupCompletion);
    m_completer->popup()->setFont(fixedFont);
    m_completer->setWrapAround(false);

    connect(m_completer, qOverload<const QString &>(&QCompleter::activated), this, [this](const QString &completion) {
        if (m_memberCompletionActive) {
            insertMemberCompletion(completion);
        } else {
            insertFunctionCompletion(completion);
        }
    });

    setTheme(m_theme);
}

CodeEditor::~CodeEditor() = default;

QString CodeEditor::filePath() const
{
    return m_filePath;
}

void CodeEditor::setFilePath(const QString &path)
{
    m_filePath = path;
}

void CodeEditor::setFunctionCompletions(const QStringList &signatures)
{
    m_functionCompletions = signatures;
    m_functionCompletions.removeDuplicates();
    m_functionCompletions.sort(Qt::CaseInsensitive);

    if (!m_memberCompletionActive) {
        m_completionModel->setStringList(m_functionCompletions);
    }
}

void CodeEditor::setProjectTypeNames(const QStringList &typeNames)
{
    if (m_highlighter) {
        m_highlighter->setExternalTypeNames(typeNames);
    }
}

void CodeEditor::setApiSyntaxNames(const QStringList &apiNames)
{
    if (m_highlighter) {
        m_highlighter->setExternalApiNames(apiNames);
    }
}

void CodeEditor::restoreFunctionCompletionModel()
{
    m_memberCompletionActive = false;
    m_memberCompletionPrefix.clear();
    m_completionModel->setStringList(m_functionCompletions);
}

void CodeEditor::showMemberCompletions(const QStringList &members,
                                       const QString &prefix)
{
    QStringList sortedMembers = members;
    sortedMembers.removeDuplicates();
    sortedMembers.sort(Qt::CaseInsensitive);

    if (sortedMembers.isEmpty()) {
        m_completer->popup()->hide();
        restoreFunctionCompletionModel();
        return;
    }

    m_memberCompletionActive = true;
    m_memberCompletionPrefix = prefix;
    m_completionModel->setStringList(sortedMembers);
    m_completer->setCompletionPrefix(prefix);

    if (m_completer->completionCount() == 0) {
        m_completer->popup()->hide();
        restoreFunctionCompletionModel();
        return;
    }

    QRect completionRect = cursorRect();
    completionRect.setWidth(
        m_completer->popup()->sizeHintForColumn(0)
        + m_completer->popup()->verticalScrollBar()->sizeHint().width());

    m_completer->complete(completionRect);
}


void CodeEditor::refreshMemberCompletion()
{
    /*
     * Re-run member discovery against the editor's current text. This is useful
     * after the user edits a typedef/struct or variable declaration while the
     * file is already open; no close/reopen cycle is needed.
     */
    requestMemberCompletionAtCursor();
}

void CodeEditor::setCompletionFont(const QFont &font)
{
    if (m_completer) {
        m_completer->popup()->setFont(font);
    }
}

void CodeEditor::setTheme(const IDETheme &theme)
{
    m_theme = theme;

    QPalette p = palette();
    p.setColor(QPalette::Base, m_theme.editorBackground);
    p.setColor(QPalette::Text, m_theme.editorText);
    p.setColor(QPalette::Highlight, m_theme.selectionBackground);
    p.setColor(QPalette::HighlightedText, m_theme.selectionText);
    setPalette(p);

    if (m_highlighter) {
        m_highlighter->setTheme(m_theme);
    }

    if (m_completer && m_completer->popup()) {
        m_completer->popup()->setStyleSheet(QStringLiteral(
            "QAbstractItemView {"
            " background:%1;"
            " color:%2;"
            " border:1px solid %3;"
            " selection-background-color:%4;"
            " selection-color:%5;"
            "}")
            .arg(ideThemeColorName(m_theme.inputBackground),
                 ideThemeColorName(m_theme.text),
                 ideThemeColorName(m_theme.border),
                 ideThemeColorName(m_theme.accent),
                 ideThemeColorName(m_theme.brightText)));
    }

    highlightCurrentLine();

    if (m_lineNumberArea) {
        m_lineNumberArea->update();
    }

    if (m_minimap) {
        m_minimap->update();
    }

    viewport()->update();
}

const IDETheme &CodeEditor::theme() const
{
    return m_theme;
}

const QList<EditorDiagnostic> &CodeEditor::diagnostics() const
{
    return m_diagnostics;
}

void CodeEditor::setDiagnostics(const QList<EditorDiagnostic> &diagnostics)
{
    m_diagnostics = diagnostics;

    std::sort(
        m_diagnostics.begin(),
        m_diagnostics.end(),
        [](const EditorDiagnostic &a, const EditorDiagnostic &b) {
            if (a.line != b.line) {
                return a.line < b.line;
            }
            if (a.severity != b.severity) {
                return a.severity == EditorDiagnostic::Severity::Error;
            }
            if (a.column != b.column) {
                return a.column < b.column;
            }
            return a.message < b.message;
        });

    m_diagnostics.erase(
        std::unique(
            m_diagnostics.begin(),
            m_diagnostics.end(),
            [](const EditorDiagnostic &a, const EditorDiagnostic &b) {
                return a.line == b.line
                    && a.column == b.column
                    && a.severity == b.severity
                    && a.message == b.message;
            }),
        m_diagnostics.end());

    if (m_minimap) {
        m_minimap->update();
    }
    if (m_lineNumberArea) {
        m_lineNumberArea->update();
    }
}

void CodeEditor::clearDiagnostics()
{
    m_diagnostics.clear();

    if (m_minimap) {
        m_minimap->update();
    }
    if (m_lineNumberArea) {
        m_lineNumberArea->update();
    }
}

QString CodeEditor::diagnosticToolTipAtY(int y) const
{
    QTextBlock block = firstVisibleBlock();
    int top = qRound(blockBoundingGeometry(block).translated(contentOffset()).top());

    while (block.isValid()) {
        const int bottom = top + qRound(blockBoundingRect(block).height());

        if (y >= top && y < bottom) {
            const int line = block.blockNumber();
            QStringList errors;
            QStringList warnings;

            for (const EditorDiagnostic &diagnostic : m_diagnostics) {
                if (diagnostic.line != line || diagnostic.message.isEmpty()) {
                    continue;
                }

                QString text = diagnostic.message.toHtmlEscaped();

                if (diagnostic.column >= 0) {
                    text = QStringLiteral(
                               "<span style=\"color:%1;\">Column %2:</span> %3")
                               .arg(ideThemeColorName(m_theme.diagnosticColumn))
                               .arg(diagnostic.column + 1)
                               .arg(text);
                }

                if (diagnostic.severity == EditorDiagnostic::Severity::Warning) {
                    if (!warnings.contains(text)) {
                        warnings.append(text);
                    }
                } else {
                    if (!errors.contains(text)) {
                        errors.append(text);
                    }
                }
            }

            QStringList sections;

            if (!errors.isEmpty()) {
                sections.append(
                    QStringLiteral(
                        "<div>"
                        "<span style=\"color:%1; font-weight:700;\">ERROR%2</span>"
                        "<br>%3"
                        "</div>")
                        .arg(ideThemeColorName(m_theme.diagnosticError))
                        .arg(errors.size() == 1 ? QString() : QStringLiteral("S"))
                        .arg(errors.join(QStringLiteral("<br>"))));
            }

            if (!warnings.isEmpty()) {
                sections.append(
                    QStringLiteral(
                        "<div>"
                        "<span style=\"color:%1; font-weight:700;\">WARNING%2</span>"
                        "<br>%3"
                        "</div>")
                        .arg(ideThemeColorName(m_theme.diagnosticWarning))
                        .arg(warnings.size() == 1 ? QString() : QStringLiteral("S"))
                        .arg(warnings.join(QStringLiteral("<br>"))));
            }

            if (sections.isEmpty()) {
                return {};
            }

            return QStringLiteral(
                       "<div style=\"white-space:pre-wrap;\">%1</div>")
                .arg(sections.join(QStringLiteral("<br><br>")));
        }

        if (top > y) {
            break;
        }

        block = block.next();
        top = bottom;
    }

    return {};
}

bool CodeEditor::loadFromFile(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream stream(&file);
    setPlainText(stream.readAll());
    setFilePath(path);
    document()->setModified(false);
    return true;
}

bool CodeEditor::save()
{
    if (m_filePath.isEmpty()) {
        return false;
    }

    return saveAs(m_filePath);
}

bool CodeEditor::saveAs(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream stream(&file);
    stream << toPlainText();
    setFilePath(path);
    document()->setModified(false);
    return true;
}

int CodeEditor::lineNumberAreaWidth() const
{
    int digits = 4;
    int max = qMax(1, blockCount());
    while (max >= 10000) {
        max /= 10000;
        ++digits;
    }

    return 12 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;
}

void CodeEditor::refreshLineNumberAreaWidth()
{
    updateLineNumberAreaWidth(0);
}

void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(m_lineNumberArea);
    painter.fillRect(event->rect(), m_theme.gutterBackground);

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + qRound(blockBoundingRect(block).height());

    while (block.isValid() && top <= event->rect().bottom()) {

        if (block.isVisible() && bottom >= event->rect().top()) {

            // Compiler diagnostic marker. Error wins if both severities share a line.
            bool hasError = false;
            bool hasWarning = false;

            for (const EditorDiagnostic &diagnostic : m_diagnostics) {
                if (diagnostic.line != blockNumber) {
                    continue;
                }

                if (diagnostic.severity == EditorDiagnostic::Severity::Error) {
                    hasError = true;
                    break;
                }

                hasWarning = true;
            }

            if (hasError) {
                painter.fillRect(
                    0,
                    top,
                    4,
                    fontMetrics().height(),
                    m_theme.diagnosticError);
            } else if (hasWarning) {
                painter.fillRect(
                    0,
                    top,
                    4,
                    fontMetrics().height(),
                    m_theme.diagnosticWarning);
            }

            const QString number = QString::number(blockNumber + 1);

            painter.setPen(m_theme.lineNumber);

            painter.drawText(
                6,
                top,
                m_lineNumberArea->width() - 12,
                fontMetrics().height(),
                Qt::AlignRight,
                number
                );
        }

        block = block.next();
        top = bottom;
        bottom = top + qRound(blockBoundingRect(block).height());
        ++blockNumber;
    }
}

void CodeEditor::focusInEvent(QFocusEvent *event)
{
    if (m_completer) {
        m_completer->setWidget(this);
    }

    QPlainTextEdit::focusInEvent(event);
}

int CodeEditor::indentWidthColumns() const
{
    const int spaceWidth = qMax(1, fontMetrics().horizontalAdvance(QLatin1Char(' ')));
    return qMax(1, qRound(tabStopDistance() / spaceWidth));
}

QString CodeEditor::leadingWhitespace(const QString &text) const
{
    int index = 0;
    while (index < text.length() && text.at(index).isSpace()) {
        ++index;
    }
    return text.left(index);
}

void CodeEditor::insertAutoIndent()
{
    QTextCursor cursor = textCursor();
    const QString blockText = cursor.block().text();
    const int positionInBlock = cursor.positionInBlock();
    const QString beforeCursor = blockText.left(positionInBlock);
    const QString afterCursor = blockText.mid(positionInBlock);

    QString baseIndent = leadingWhitespace(blockText);
    QString nextIndent = baseIndent;
    const QString trimmedBefore = beforeCursor.trimmed();
    const bool opensBlock = trimmedBefore.endsWith(QLatin1Char(123));
    if (opensBlock) {
        nextIndent += QString(indentWidthColumns(), QLatin1Char(32));
    }

    cursor.beginEditBlock();
    cursor.insertBlock();
    cursor.insertText(nextIndent);

    if (opensBlock && afterCursor.trimmed().startsWith(QLatin1Char(125))) {
        cursor.insertBlock();
        cursor.insertText(baseIndent);
        cursor.movePosition(QTextCursor::PreviousBlock);
        cursor.movePosition(QTextCursor::EndOfBlock);
    }

    cursor.endEditBlock();
    setTextCursor(cursor);
}

void CodeEditor::indentSelection()
{
    QTextCursor cursor = textCursor();
    const int start = cursor.selectionStart();
    int end = cursor.selectionEnd();
    cursor.setPosition(end);
    if (cursor.positionInBlock() == 0 && end > start) {
        cursor.movePosition(QTextCursor::PreviousCharacter);
        end = cursor.position();
    }

    QTextCursor editCursor(document()->findBlock(start));
    const QTextBlock endBlock = document()->findBlock(end);
    const QString indent(indentWidthColumns(), QLatin1Char(32));

    editCursor.beginEditBlock();
    while (editCursor.block().isValid()) {
        editCursor.movePosition(QTextCursor::StartOfBlock);
        editCursor.insertText(indent);
        if (editCursor.block() == endBlock) {
            break;
        }
        editCursor.movePosition(QTextCursor::NextBlock);
    }
    editCursor.endEditBlock();
}

void CodeEditor::unindentSelection()
{
    QTextCursor cursor = textCursor();
    const int start = cursor.selectionStart();
    int end = cursor.selectionEnd();
    cursor.setPosition(end);
    if (cursor.positionInBlock() == 0 && end > start) {
        cursor.movePosition(QTextCursor::PreviousCharacter);
        end = cursor.position();
    }

    QTextCursor editCursor(document()->findBlock(start));
    const QTextBlock endBlock = document()->findBlock(end);
    const int indentWidth = indentWidthColumns();

    editCursor.beginEditBlock();
    while (editCursor.block().isValid()) {
        const QString text = editCursor.block().text();
        int removeCount = 0;
        while (removeCount < text.length() && removeCount < indentWidth && text.at(removeCount) == QLatin1Char(32)) {
            ++removeCount;
        }
        if (removeCount == 0 && text.startsWith(QLatin1Char(9))) {
            removeCount = 1;
        }

        if (removeCount > 0) {
            editCursor.movePosition(QTextCursor::StartOfBlock);
            editCursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor, removeCount);
            editCursor.removeSelectedText();
        }

        if (editCursor.block() == endBlock) {
            break;
        }
        editCursor.movePosition(QTextCursor::NextBlock);
    }
    editCursor.endEditBlock();
}

void CodeEditor::drawIndentGuides(QPaintEvent *event)
{
    QPainter painter(viewport());
    QPen pen(m_theme.indentGuide);
    pen.setStyle(Qt::DotLine);
    painter.setPen(pen);

    const int spaceWidth = qMax(1, fontMetrics().horizontalAdvance(QLatin1Char(32)));
    const int indentWidth = indentWidthColumns();
    QTextBlock block = firstVisibleBlock();
    int top = qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + qRound(blockBoundingRect(block).height());

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            int columns = 0;
            const QString text = block.text();
            for (const QChar ch : text) {
                if (ch == QLatin1Char(32)) {
                    ++columns;
                } else if (ch == QLatin1Char(9)) {
                    columns += indentWidth - (columns % indentWidth);
                } else {
                    break;
                }
            }

            const qreal left = blockBoundingGeometry(block).translated(contentOffset()).left();
            for (int column = indentWidth; column <= columns; column += indentWidth) {
                const int x = qRound(left + column * spaceWidth);
                if (x >= event->rect().left() && x <= event->rect().right()) {

                    painter.drawLine(x, top, x, bottom);
                }
            }
        }

        block = block.next();
        top = bottom;
        bottom = top + qRound(blockBoundingRect(block).height());
    }
}

void CodeEditor::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton
        && (event->modifiers() & Qt::ControlModifier)) {

        QTextCursor cursor = cursorForPosition(event->position().toPoint());
        cursor.select(QTextCursor::WordUnderCursor);
        const QString symbol = cursor.selectedText().trimmed();

        static const QRegularExpression identifierExpression(
            QStringLiteral("^[A-Za-z_][A-Za-z0-9_]*$"));

        if (identifierExpression.match(symbol).hasMatch()) {
            emit definitionRequested(symbol, cursor.blockNumber());
            event->accept();
            return;
        }
    }

    QPlainTextEdit::mousePressEvent(event);
}

void CodeEditor::mouseMoveEvent(QMouseEvent *event)
{
    if (event->modifiers() & Qt::ControlModifier) {
        QTextCursor cursor = cursorForPosition(event->position().toPoint());
        cursor.select(QTextCursor::WordUnderCursor);
        const QString symbol = cursor.selectedText().trimmed();

        static const QRegularExpression identifierExpression(
            QStringLiteral("^[A-Za-z_][A-Za-z0-9_]*$"));

        viewport()->setCursor(
            identifierExpression.match(symbol).hasMatch()
                ? Qt::PointingHandCursor
                : Qt::IBeamCursor);
    } else {
        viewport()->setCursor(Qt::IBeamCursor);
    }

    QPlainTextEdit::mouseMoveEvent(event);
}

void CodeEditor::paintEvent(QPaintEvent *event)
{
    QPlainTextEdit::paintEvent(event);
    drawIndentGuides(event);
}

bool CodeEditor::handleAutoPairKey(QKeyEvent *event)
{
    if (!event
        || event->modifiers().testFlag(Qt::ControlModifier)
        || event->modifiers().testFlag(Qt::AltModifier)
        || event->modifiers().testFlag(Qt::MetaModifier)) {
        return false;
    }

    const QString typed = event->text();
    if (typed.size() != 1) {
        return false;
    }

    const QChar ch = typed.at(0);
    QChar closing;

    if (ch == QLatin1Char('(')) {
        closing = QLatin1Char(')');
    } else if (ch == QLatin1Char('[')) {
        closing = QLatin1Char(']');
    } else if (ch == QLatin1Char('{')) {
        closing = QLatin1Char('}');
    } else if (ch == QLatin1Char(')')
               || ch == QLatin1Char(']')
               || ch == QLatin1Char('}')) {
        /*
         * If the closer already exists under the caret, step over it instead
         * of creating "))", "]]" or "}}".
         */
        QTextCursor cursor = textCursor();
        const QString text = toPlainText();

        if (cursor.position() < text.size()
            && text.at(cursor.position()) == ch) {
            cursor.movePosition(QTextCursor::NextCharacter);
            setTextCursor(cursor);
            return true;
        }

        return false;
    } else {
        return false;
    }

    QTextCursor cursor = textCursor();

    /*
     * If text is selected, wrap it rather than throwing the selection away.
     * Example: select "fish" and type '(' -> "(fish)".
     */
    if (cursor.hasSelection()) {
        const QString selected = cursor.selectedText();
        cursor.insertText(QString(ch) + selected + QString(closing));
        setTextCursor(cursor);
        return true;
    }

    cursor.insertText(QString(ch) + QString(closing));
    cursor.movePosition(QTextCursor::PreviousCharacter);
    setTextCursor(cursor);
    return true;
}

bool CodeEditor::handlePairedBackspace(QKeyEvent *event)
{
    if (!event || event->key() != Qt::Key_Backspace) {
        return false;
    }

    QTextCursor cursor = textCursor();

    if (cursor.hasSelection() || cursor.position() <= 0) {
        return false;
    }

    const QString text = toPlainText();
    const int position = cursor.position();

    if (position >= text.size()) {
        return false;
    }

    const QChar left = text.at(position - 1);
    const QChar right = text.at(position);

    const bool isPair =
        (left == QLatin1Char('(') && right == QLatin1Char(')'))
        || (left == QLatin1Char('[') && right == QLatin1Char(']'))
        || (left == QLatin1Char('{') && right == QLatin1Char('}'));

    if (!isPair) {
        return false;
    }

    cursor.beginEditBlock();
    cursor.movePosition(QTextCursor::PreviousCharacter);
    cursor.movePosition(
        QTextCursor::NextCharacter,
        QTextCursor::KeepAnchor,
        2);
    cursor.removeSelectedText();
    cursor.endEditBlock();

    setTextCursor(cursor);
    return true;
}

void CodeEditor::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_F1) {
        emit quickTipRequested(textUnderCursor());
        event->accept();
        return;
    }

    // If the completion popup is open, Tab/Enter accept the current completion first.
    if (m_completer && m_completer->popup()->isVisible()) {
        switch (event->key()) {
        case Qt::Key_Tab:
        case Qt::Key_Return:
        case Qt::Key_Enter: {
            QString completion = m_completer->currentCompletion();

            /*
             * When the user moves through the popup with Up/Down, QCompleter's
             * currentCompletion() can still point at the first proxy-model item.
             * The popup selection is the authoritative keyboard choice.
             */
            if (m_completer->popup()->currentIndex().isValid()) {
                completion =
                    m_completer->popup()->currentIndex()
                        .data(Qt::DisplayRole)
                        .toString();
            }

            if (m_memberCompletionActive) {
                insertMemberCompletion(completion);
            } else {
                insertFunctionCompletion(completion);
                m_completer->popup()->hide();
            }

            event->accept();
            return;
        }
        case Qt::Key_Escape:
            m_completer->popup()->hide();
            if (m_memberCompletionActive) {
                restoreFunctionCompletionModel();
            }
            event->accept();
            return;
        default:
            break;
        }
    }

    // Enter keeps the current indentation.
    // If the caret is between {}, create the inner line and leave the closing
    // brace aligned with the line which opened the block.
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        QTextCursor cursor = textCursor();
        const QString blockText = cursor.block().text();
        const int pos = cursor.positionInBlock();

        const bool betweenBraces =
            pos > 0
            && pos < blockText.size()
            && blockText.at(pos - 1) == QLatin1Char('{')
            && blockText.at(pos) == QLatin1Char('}');

        if (betweenBraces) {
            const QString baseIndent = leadingWhitespace(blockText);
            const QString innerIndent =
                baseIndent + QString(indentWidthColumns(), QLatin1Char(' '));

            cursor.beginEditBlock();
            cursor.insertBlock();
            cursor.insertText(innerIndent);
            cursor.insertBlock();
            cursor.insertText(baseIndent);
            cursor.movePosition(QTextCursor::PreviousBlock);
            cursor.movePosition(QTextCursor::EndOfBlock);
            cursor.endEditBlock();

            setTextCursor(cursor);
        } else {
            insertAutoIndent();
        }

        event->accept();
        return;
    }

    // Tab indents either the selected block or the current cursor position.
    if (event->key() == Qt::Key_Tab && !(event->modifiers() & Qt::ShiftModifier)) {
        QTextCursor cursor = textCursor();

        if (cursor.hasSelection()) {
            indentSelection();
        } else {
            cursor.insertText(QString(indentWidthColumns(), QLatin1Char(' ')));
            setTextCursor(cursor);
        }

        event->accept();
        return;
    }

    if (handlePairedBackspace(event)) {
        event->accept();
        return;
    }

    if (handleAutoPairKey(event)) {
        event->accept();
        return;
    }

    // Shift+Tab removes one indentation level from every selected line,
    // or from the current line when there is no selection.
    if (event->key() == Qt::Key_Backtab
        || (event->key() == Qt::Key_Tab && (event->modifiers() & Qt::ShiftModifier))) {

        QTextCursor cursor = textCursor();

        if (!cursor.hasSelection()) {
            cursor.movePosition(QTextCursor::StartOfBlock);
            cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
            setTextCursor(cursor);
        }

        unindentSelection();
        event->accept();
        return;
    }

    QPlainTextEdit::keyPressEvent(event);

    if (m_completer && requestMemberCompletionAtCursor()) {
        return;
    }

    const QString completionPrefix = textUnderCursor();
    if (!m_completer || completionPrefix.length() < 2 || event->text().isEmpty()) {
        if (m_completer) {
            m_completer->popup()->hide();
        }
        return;
    }

    m_completer->setCompletionPrefix(completionPrefix);
    if (m_completer->completionCount() == 0) {
        m_completer->popup()->hide();
        return;
    }

    QRect completionRect = cursorRect();
    completionRect.setWidth(
        m_completer->popup()->sizeHintForColumn(0)
        + m_completer->popup()->verticalScrollBar()->sizeHint().width());
    m_completer->complete(completionRect);
}

void CodeEditor::resizeEvent(QResizeEvent *event)
{
    QPlainTextEdit::resizeEvent(event);

    const QRect contents = contentsRect();
    m_lineNumberArea->setGeometry(
        QRect(contents.left(), contents.top(), lineNumberAreaWidth(), contents.height()));

    const QRect view = viewport()->geometry();
    m_minimap->setGeometry(
        QRect(view.right() + 1, view.top(), CodeMinimapWidth, view.height()));
}

void CodeEditor::updateLineNumberAreaWidth(int)
{
    setViewportMargins(lineNumberAreaWidth(), 0, CodeMinimapWidth, 0);
}

void CodeEditor::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy) {
        m_lineNumberArea->scroll(0, dy);
    } else {
        m_lineNumberArea->update(0, rect.y(), m_lineNumberArea->width(), rect.height());
    }

    if (rect.contains(viewport()->rect())) {
        updateLineNumberAreaWidth(0);
    }
}

void CodeEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> selections;

    /*
     * Read-only API reference tabs should still show the line we navigated to.
     * "Read only" means the user cannot edit the source; it should not remove
     * the editor's navigation highlight.
     */
    QTextEdit::ExtraSelection selection;
    selection.format.setBackground(m_theme.currentLine);
    selection.format.setProperty(QTextFormat::FullWidthSelection, true);
    selection.cursor = textCursor();
    selection.cursor.clearSelection();
    selections.append(selection);

    setExtraSelections(selections);
}

QString CodeEditor::textUnderCursor() const
{
    const QString text = toPlainText();
    int position = textCursor().position();
    if (position > text.length()) {
        position = text.length();
    }

    auto isIdentifierChar = [](QChar ch) {
        return ch.isLetterOrNumber() || ch == QLatin1Char('_');
    };

    if (position > 0 && (position == text.length() || !isIdentifierChar(text.at(position)))
        && isIdentifierChar(text.at(position - 1))) {
        --position;
    }

    if (position >= text.length() || !isIdentifierChar(text.at(position))) {
        return {};
    }

    int start = position;
    while (start > 0 && isIdentifierChar(text.at(start - 1))) {
        --start;
    }

    int end = position + 1;
    while (end < text.length() && isIdentifierChar(text.at(end))) {
        ++end;
    }

    return text.mid(start, end - start);
}

bool CodeEditor::requestMemberCompletionAtCursor()
{
    QTextCursor cursor = textCursor();
    const QString beforeCursor =
        cursor.block().text().left(cursor.positionInBlock());

    /*
     * Match the common/basic-C forms:
     *
     *     bob.
     *     bob.x
     *     bob->
     *     bob->x
     *
     * The member prefix is optional, so the popup can appear immediately
     * after '.' or '>'.
     */
    static const QRegularExpression memberExpression(
        QStringLiteral(
            R"(([A-Za-z_][A-Za-z0-9_]*)\s*(?:\.|->)\s*([A-Za-z_][A-Za-z0-9_]*)?$)"));

    const QRegularExpressionMatch match =
        memberExpression.match(beforeCursor);

    if (!match.hasMatch()) {
        if (m_memberCompletionActive) {
            m_completer->popup()->hide();
            restoreFunctionCompletionModel();
        }
        return false;
    }

    const QString objectName = match.captured(1);
    const QString prefix = match.captured(2);

    emit memberCompletionRequested(
        objectName,
        cursor.blockNumber(),
        prefix);

    return true;
}

void CodeEditor::insertMemberCompletion(const QString &member)
{
    if (member.isEmpty()) {
        restoreFunctionCompletionModel();
        return;
    }

    QTextCursor cursor = textCursor();

    if (!m_memberCompletionPrefix.isEmpty()) {
        cursor.movePosition(
            QTextCursor::PreviousCharacter,
            QTextCursor::KeepAnchor,
            m_memberCompletionPrefix.length());
    }

    cursor.insertText(member);
    setTextCursor(cursor);

    m_completer->popup()->hide();
    restoreFunctionCompletionModel();
}

void CodeEditor::insertFunctionCompletion(const QString &signature)
{
    if (signature.isEmpty()) {
        return;
    }

    QTextCursor cursor = textCursor();
    cursor.select(QTextCursor::WordUnderCursor);

    const QString name = functionNameFromSignature(signature);
    if (!signature.contains(QLatin1Char('('))) {
        cursor.insertText(name);
        setTextCursor(cursor);
        m_argumentRanges.clear();
        m_selectedArgument = -1;
        return;
    }
    const QStringList arguments = splitFunctionArguments(signature);
    QStringList placeholders;
    for (int i = 0; i < arguments.count(); ++i) {
        placeholders.append(placeholderForArgument(arguments.at(i), i));
    }

    const int insertionStart = cursor.selectionStart();
    const QString callText = QStringLiteral("%1(%2)").arg(name, placeholders.join(QStringLiteral(", ")));

    cursor.insertText(callText);
    setTextCursor(cursor);

    m_argumentRanges.clear();
    int searchOffset = name.length() + 1;
    for (const QString &placeholder : placeholders) {
        const int relativeIndex = callText.indexOf(placeholder, searchOffset);
        if (relativeIndex >= 0) {
            m_argumentRanges.append({insertionStart + relativeIndex, placeholder.length()});
            searchOffset = relativeIndex + placeholder.length();
        }
    }

    m_selectedArgument = -1;
    selectArgument(0);
}

void CodeEditor::selectArgument(int index)
{
    if (index < 0 || index >= m_argumentRanges.count()) {
        m_argumentRanges.clear();
        m_selectedArgument = -1;
        return;
    }

    m_selectedArgument = index;
    QTextCursor cursor = textCursor();
    cursor.setPosition(m_argumentRanges.at(index).first);
    cursor.setPosition(m_argumentRanges.at(index).first + m_argumentRanges.at(index).second, QTextCursor::KeepAnchor);
    setTextCursor(cursor);
}
