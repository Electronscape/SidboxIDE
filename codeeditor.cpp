#include "codeeditor.h"

#include "csyntaxhighlighter.h"

#include <algorithm>
#include <utility>
#include <QAbstractItemView>
#include <QCompleter>
#include <QFile>
#include <QFocusEvent>
#include <QFont>
#include <QFontDatabase>
#include <QKeyEvent>
#include <QLabel>
#include <QMouseEvent>
#include <QMenu>
#include <QPainter>
#include <QPolygon>
#include <QColor>
#include <QToolTip>
#include <QHelpEvent>
#include <QHash>
#include <QEvent>
#include <QRegularExpression>
#include <QScrollBar>
#include <QSet>
#include <QStringListModel>
#include <QTextBlock>
#include <QTextEdit>
#include <QTextDocument>
#include <QTextStream>
#include <QTextLayout>
#include <QTimer>
#include <QWidget>

namespace {
constexpr int CodeMinimapWidth = 92;
constexpr int FoldGutterWidth = 16;
constexpr int FoldMarkerHitLeft = 4;
constexpr int FoldMarkerHitRight = 20;

class FoldBlockData : public QTextBlockUserData
{
public:
    bool folded = false;
};

FoldBlockData *foldDataForBlock(QTextBlock block, bool create)
{
    auto *data =
        dynamic_cast<FoldBlockData *>(block.userData());

    if (!data && create) {
        data = new FoldBlockData;
        block.setUserData(data);
    }

    return data;
}

QString includePathAtCursor(const QTextCursor &cursor)
{
    const QString line = cursor.block().text();

    /*
     * Recognise both:
     *
     *     #include "thing.h"
     *     #include <thing.h>
     *
     * Only the filename/path between the delimiters is clickable. This keeps
     * Ctrl+Click on ordinary identifiers using the normal go-to-definition
     * path.
     */
    static const QRegularExpression includeExpression(
        QStringLiteral(
            R"(^\s*#\s*include\s*[<"]([^>"]+)[>"])"));

    const QRegularExpressionMatch match =
        includeExpression.match(line);

    if (!match.hasMatch()) {
        return {};
    }

    const int start = match.capturedStart(1);
    const int end = match.capturedEnd(1);
    const int position = cursor.positionInBlock();

    if (position < start || position > end) {
        return {};
    }

    return match.captured(1).trimmed();
}

class CodeMinimap : public QWidget
{
public:
    explicit CodeMinimap(CodeEditor *editor)
        : QWidget(editor)
        , m_editor(editor)
        , m_dragging(false)
        , m_sourceRefreshTimer(new QTimer(this))
        , m_dragScrollTimer(new QTimer(this))
    {
        setCursor(Qt::PointingHandCursor);
        setMouseTracking(true);
        setAttribute(Qt::WA_OpaquePaintEvent);

        /*
         * Minimap rebuilds are cooperative. Large 100-200 KB sources are walked
         * in small QTextBlock batches with a zero-timeout timer, yielding to Qt
         * between batches so typing/scrolling always wins.
         */
        m_sourceRefreshTimer->setSingleShot(true);
        m_sourceRefreshTimer->setInterval(0);
        connect(m_sourceRefreshTimer, &QTimer::timeout,
                this, [this]() {
                    continueQueuedRefresh();
                });

        /*
         * Mouse-move events can arrive much faster than the editor can repaint.
         * Coalesce minimap dragging to roughly one scroll operation per frame.
         * This is especially important after folding because Qt is also
         * recalculating visible QTextBlock geometry.
         */
        m_dragScrollTimer->setSingleShot(true);
        m_dragScrollTimer->setInterval(16);
        connect(m_dragScrollTimer, &QTimer::timeout,
                this, [this]() {
                    scrollToY(m_pendingScrollY);
                });

        attachDocument(editor->document());

        connect(editor->verticalScrollBar(), &QScrollBar::valueChanged, this, [this]() {
            /*
             * Scrolling still repaints immediately, but paintEvent() uses the
             * cached source lines so it no longer converts the whole document
             * to plain text on every scrollbar movement.
             */
            update();
        });
        connect(editor->verticalScrollBar(), &QScrollBar::rangeChanged, this, [this](int, int) {
            update();
        });
    }

    void attachDocument(QTextDocument *document)
    {
        QObject::disconnect(m_documentChangedConnection);
        Q_UNUSED(document);

        cancelQueuedRefresh();
        m_cachedLines.clear();
        m_sourceLineToVisibleIndex.clear();

        /*
         * Populate immediately for an already-existing shared document.
         */
        rebuildSourceCache();
    }

    void refreshNow()
    {
        /*
         * Explicit folding operations still need an exact cache immediately.
         */
        cancelQueuedRefresh();
        rebuildSourceCache();
    }

    void refreshQueued()
    {
        if (!m_editor || !m_editor->document()) {
            return;
        }

        if (m_sourceRefreshTimer) {
            m_sourceRefreshTimer->stop();
        }

        m_pendingLines.clear();
        m_pendingSourceLineToVisibleIndex.clear();
        m_pendingBlock =
            m_editor->document()->firstBlock();

        if (m_sourceRefreshTimer) {
            m_sourceRefreshTimer->start();
        }
    }

    void cancelQueuedRefresh()
    {
        if (m_sourceRefreshTimer) {
            m_sourceRefreshTimer->stop();
        }

        m_pendingLines.clear();
        m_pendingSourceLineToVisibleIndex.clear();
        m_pendingBlock = QTextBlock();
    }

protected:
    void paintEvent(QPaintEvent *) override
    {
        QPainter painter(this);
        painter.fillRect(rect(), m_editor->theme().minimapBackground);

        if (!m_editor) {
            return;
        }

        const QList<CachedLine> &lines = m_cachedLines;
        const int lineCount = qMax(1, lines.size());
        const qreal usableHeight = qMax(1, height() - 2);
        //const qreal yScale = usableHeight / static_cast<qreal>(lineCount);
        const qreal yScale = qMin<qreal>(
            3.0,
            usableHeight / static_cast<qreal>(lineCount)
            );

        for (int i = 0; i < lines.size(); ++i) {
            const QString &line = lines.at(i).text;
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

        /*
         * Keep the viewport glass in the same coordinate space as the minimap
         * source itself.
         *
         * yScale is capped at 3 px/visible line, so after folding a small file
         * may occupy only the top part of the minimap. The old glass mapping
         * still used the ENTIRE widget height, which made the mouse travel a
         * huge distance while the lens crept slowly through a handful of lines.
         */
        const qreal contentTop = 1.0;
        const qreal contentBottom =
            qMin<qreal>(
                height() - 1.0,
                contentTop
                    + qMax(
                        0,
                        lineCount - 1)
                        * yScale);

        int firstVisibleIndex = 0;

        const int firstVisibleSourceLine =
            m_editor->firstVisibleSourceBlockNumber();

        if (firstVisibleSourceLine >= 0) {
            const auto it =
                m_sourceLineToVisibleIndex.constFind(
                    firstVisibleSourceLine);

            if (it != m_sourceLineToVisibleIndex.constEnd()) {
                firstVisibleIndex = it.value();
            }
        }

        qreal viewTop =
            contentTop
            + firstVisibleIndex * yScale;

        /*
         * QScrollBar::pageStep() is in visual lines for QPlainTextEdit, so it
         * already ignores folded-away blocks. Convert that straight into the
         * same minimap line spacing.
         */
        qreal viewHeight =
            qMax<qreal>(
                12.0,
                qMax(1, bar->pageStep()) * yScale);

        const qreal contentHeight =
            qMax<qreal>(
                1.0,
                contentBottom - contentTop + yScale);

        viewHeight =
            qMin<qreal>(
                viewHeight,
                contentHeight);

        const qreal maxViewTop =
            qMax<qreal>(
                contentTop,
                contentBottom - viewHeight + yScale);

        viewTop =
            qBound<qreal>(
                contentTop,
                viewTop,
                maxViewTop);

        const QRectF viewportRect(
            1.5,
            viewTop + 0.5,
            width() - 2.0,
            qMax<qreal>(1.0, viewHeight - 1.0));
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
                    || diagnostic.line < 0) {
                    continue;
                }

                const auto visibleIt =
                    m_sourceLineToVisibleIndex.constFind(
                        diagnostic.line);

                /*
                 * A diagnostic inside a collapsed region is intentionally not
                 * drawn as a misleading tick on some unrelated visible row.
                 * Expanding the fold restores it immediately.
                 */
                if (visibleIt
                    == m_sourceLineToVisibleIndex.constEnd()) {
                    continue;
                }

                const int visibleLine =
                    visibleIt.value();

                const int y = qBound(
                    0,
                    1 + qRound(visibleLine * yScale) - markerHeight / 2,
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
            queueScrollToY(event->position().y());
            event->accept();
            return;
        }

        QWidget::mousePressEvent(event);
    }

    void mouseMoveEvent(QMouseEvent *event) override
    {
        if (m_dragging
            && (event->buttons() & Qt::LeftButton)) {
            queueScrollToY(event->position().y());
            event->accept();
            return;
        }

        QWidget::mouseMoveEvent(event);
    }

    void mouseReleaseEvent(QMouseEvent *event) override
    {
        if (event->button() == Qt::LeftButton) {
            m_dragging = false;

            /*
             * Apply the last requested position immediately on release so the
             * glass lands exactly where the mouse was let go.
             */
            if (m_dragScrollTimer
                && m_dragScrollTimer->isActive()) {
                m_dragScrollTimer->stop();
                scrollToY(m_pendingScrollY);
            }

            event->accept();
            return;
        }

        QWidget::mouseReleaseEvent(event);
    }

private:
    void continueQueuedRefresh()
    {
        if (!m_editor || !m_editor->document()) {
            cancelQueuedRefresh();
            return;
        }

        /*
         * A fixed block budget is predictable and tiny. Even generated C with
         * thousands of lines yields back to the event loop every 96 blocks.
         */
        int budget = 96;

        while (m_pendingBlock.isValid()
               && budget-- > 0) {
            if (m_pendingBlock.isVisible()) {
                const int visibleIndex =
                    m_pendingLines.size();

                m_pendingLines.append(
                    {m_pendingBlock.text(),
                     m_pendingBlock.blockNumber()});

                m_pendingSourceLineToVisibleIndex.insert(
                    m_pendingBlock.blockNumber(),
                    visibleIndex);
            }

            m_pendingBlock =
                m_pendingBlock.next();
        }

        if (m_pendingBlock.isValid()) {
            m_sourceRefreshTimer->start();
            return;
        }

        m_cachedLines =
            std::move(m_pendingLines);

        m_sourceLineToVisibleIndex =
            std::move(
                m_pendingSourceLineToVisibleIndex);

        update();
    }

    void rebuildSourceCache()
    {
        m_cachedLines.clear();
        m_sourceLineToVisibleIndex.clear();

        if (!m_editor
            || !m_editor->document()) {
            update();
            return;
        }

        /*
         * Cache only visible QTextBlocks. This keeps minimap painting cheap
         * while making the minimap represent the editor exactly as it appears
         * after code folding.
         */
        QTextBlock block =
            m_editor->document()->firstBlock();

        while (block.isValid()) {
            if (block.isVisible()) {
                const int visibleIndex =
                    m_cachedLines.size();

                m_cachedLines.append(
                    {block.text(),
                     block.blockNumber()});

                m_sourceLineToVisibleIndex.insert(
                    block.blockNumber(),
                    visibleIndex);
            }

            block = block.next();
        }

        update();
    }

    bool jumpToDiagnosticAtY(qreal y)
    {
        if (!m_editor || height() <= 1) {
            return false;
        }

        const int lineCount =
            qMax(1, m_cachedLines.size());

        const qreal usableHeight =
            qMax(1, height() - 2);

        const qreal yScale = qMin<qreal>(
            3.0,
            usableHeight / static_cast<qreal>(lineCount));

        int bestLine = -1;
        qreal bestDistance = 1000000.0;

        for (const EditorDiagnostic &diagnostic : m_editor->diagnostics()) {
            if (diagnostic.line < 0) {
                continue;
            }

            const auto visibleIt =
                m_sourceLineToVisibleIndex.constFind(
                    diagnostic.line);

            if (visibleIt
                == m_sourceLineToVisibleIndex.constEnd()) {
                continue;
            }

            const qreal markerY =
                1.0
                + visibleIt.value()
                    * yScale;

            const qreal distance =
                qAbs(markerY - y);

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

    void queueScrollToY(qreal y)
    {
        m_pendingScrollY =
            qBound<qreal>(
                0.0,
                y,
                qMax<qreal>(
                    0.0,
                    height() - 1.0));

        if (m_dragScrollTimer
            && !m_dragScrollTimer->isActive()) {
            m_dragScrollTimer->start();
        }
    }

    void scrollToY(qreal y)
    {
        if (!m_editor
            || !m_editor->document()
            || height() <= 1
            || m_cachedLines.isEmpty()) {
            return;
        }

        const int lineCount =
            qMax(1, m_cachedLines.size());

        const qreal usableHeight =
            qMax(1, height() - 2);

        const qreal yScale =
            qMin<qreal>(
                3.0,
                usableHeight
                    / static_cast<qreal>(
                        lineCount));

        /*
         * The drawn minimap source may occupy less than the full widget after
         * folding because yScale is capped at 3 px/line.
         *
         * Treat only that drawn source range as draggable navigation space:
         *   - inside it, the target follows the mouse directly;
         *   - above/below it, navigation clamps to the first/last visible line.
         */
        const qreal contentTop = 1.0;
        const qreal contentBottom =
            qMin<qreal>(
                height() - 1.0,
                contentTop
                    + qMax(
                        0,
                        lineCount - 1)
                        * yScale);

        const qreal clampedY =
            qBound<qreal>(
                contentTop,
                y,
                contentBottom);

        int visibleIndex = 0;

        if (yScale > 0.0) {
            visibleIndex =
                qBound(
                    0,
                    qRound(
                        (clampedY - contentTop)
                        / yScale),
                    lineCount - 1);
        }

        const int sourceLine =
            m_cachedLines.at(
                visibleIndex).sourceLine;

        const QTextBlock block =
            m_editor->document()
                ->findBlockByNumber(
                    sourceLine);

        if (!block.isValid()
            || !block.isVisible()) {
            return;
        }

        /*
         * A fold/unfold can change the number of visual lines without changing
         * QTextDocument::blockCount(). Make absolutely sure QPlainTextEdit's
         * vertical range matches the current visible blocks before clamping
         * this minimap drag.
         */
        m_editor->recalculateFoldScrollBarRange();

        QScrollBar *bar =
            m_editor->verticalScrollBar();

        if (!bar) {
            return;
        }

        /*
         * m_cachedLines already contains only VISIBLE source blocks, in the
         * same order QPlainTextEdit displays them. Since this editor is NoWrap,
         * visibleIndex is therefore the correct visual-line position.
         *
         * Do not use QTextBlock::firstLineNumber() here. Immediately after
         * expanding folds Qt may not have finished rebuilding every block's
         * internal line-number cache yet, which could make minimap dragging
         * stop short of the newly-restored bottom of the file.
         */
        const int centredValue =
            visibleIndex
            - qMax(
                0,
                bar->pageStep() / 2);

        const int newValue =
            qBound(
                bar->minimum(),
                centredValue,
                bar->maximum());

        if (bar->value() != newValue) {
            bar->setValue(newValue);
        }
    }

    struct CachedLine {
        QString text;
        int sourceLine = -1;
    };

    CodeEditor *m_editor;
    bool m_dragging;
    QTimer *m_sourceRefreshTimer;
    QTimer *m_dragScrollTimer;
    qreal m_pendingScrollY = 0.0;
    QList<CachedLine> m_cachedLines;
    QHash<int, int> m_sourceLineToVisibleIndex;
    QList<CachedLine> m_pendingLines;
    QHash<int, int> m_pendingSourceLineToVisibleIndex;
    QTextBlock m_pendingBlock;
    QMetaObject::Connection m_documentChangedConnection;
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

        void mousePressEvent(QMouseEvent *event) override
        {
            const int x =
                qRound(event->position().x());
            const int y =
                qRound(event->position().y());

            if (event->button() == Qt::RightButton) {
                m_diagnosticPopup->hide();

                QMenu menu(this);

                QAction *collapseAllAction =
                    menu.addAction(
                        tr("Collapse All Foldable Regions"));

                QAction *expandAllAction =
                    menu.addAction(
                        tr("Expand All Foldable Regions"));

                QAction *chosen =
                    menu.exec(
                        event->globalPosition()
                            .toPoint());

                if (chosen == collapseAllAction) {
                    m_editor->collapseAllFolds();
                } else if (chosen == expandAllAction) {
                    m_editor->expandAllFolds();
                }

                event->accept();
                return;
            }

            if (event->button() == Qt::LeftButton
                && x >= FoldMarkerHitLeft
                && x <= FoldMarkerHitRight
                && m_editor->foldMarkerAtY(y)) {
                m_editor->toggleFoldAtY(y);
                event->accept();
                return;
            }

            QWidget::mousePressEvent(event);
        }

        void mouseMoveEvent(QMouseEvent *event) override
        {
            const int x =
                qRound(event->position().x());
            const int y =
                qRound(event->position().y());

            if (x >= FoldMarkerHitLeft
                && x <= FoldMarkerHitRight
                && m_editor->foldMarkerAtY(y)) {
                setCursor(Qt::PointingHandCursor);
                m_diagnosticPopup->hide();
                QWidget::mouseMoveEvent(event);
                return;
            }

            setCursor(Qt::ArrowCursor);

            const QString tip =
                m_editor->diagnosticToolTipAtY(y);

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
    , m_foldScanTimer(new QTimer(this))
    , m_selectedArgument(-1)
{
    const QFont fixedFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    setFont(fixedFont);
    setLineWrapMode(QPlainTextEdit::NoWrap);
    /*
     * Tabs are stored as real '\t' characters, but displayed four columns
     * wide to match the existing Sidbox source style.
     */
    setTabStopDistance(fontMetrics().horizontalAdvance(QLatin1Char(' ')) * 4);
    setMouseTracking(true);
    viewport()->setMouseTracking(true);
    document()->setModified(false);

    /*
     * Whole-document fold/minimap/type discovery is coordinated by MainWindow.
     * Normal typing stays on the lightweight QTextDocument/QSyntaxHighlighter
     * path until navigation occurs or typing has been idle for two seconds.
     */
    attachFoldTracking();

    /*
     * Fold discovery uses the same cooperative idea as the minimap: scan a
     * small number of QTextBlocks, yield, then continue.
     */
    m_foldScanTimer->setSingleShot(true);
    m_foldScanTimer->setInterval(0);
    connect(m_foldScanTimer, &QTimer::timeout,
            this, &CodeEditor::continueQueuedFoldRegionScan);

    connect(this, &CodeEditor::blockCountChanged, this, &CodeEditor::updateLineNumberAreaWidth);
    connect(this, &CodeEditor::updateRequest, this, &CodeEditor::updateLineNumberArea);
    connect(this, &CodeEditor::cursorPositionChanged, this, &CodeEditor::highlightCurrentLine);
    connect(this, &CodeEditor::cursorPositionChanged, this, [this]() {
        if (!m_resourceMode) {
            emit quickTipCandidateChanged(textUnderCursor());
        }
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
    m_projectTypeNames = typeNames;

    if (m_highlighter) {
        m_highlighter->setExternalTypeNames(m_projectTypeNames);
    }
}

void CodeEditor::setApiSyntaxNames(const QStringList &apiNames)
{
    m_apiSyntaxNames = apiNames;

    if (m_highlighter) {
        m_highlighter->setExternalApiNames(m_apiSyntaxNames);
    }
}

void CodeEditor::setResourceMode(bool enabled)
{
    if (m_resourceMode == enabled) {
        return;
    }

    m_resourceMode = enabled;

    if (m_highlighter) {
        m_highlighter->setResourceMode(enabled);
    }

    if (m_resourceMode) {
        m_functionCompletions.clear();
        m_memberCompletionActive = false;
        m_memberCompletionPrefix.clear();
        m_completionModel->setStringList({});
        if (m_completer && m_completer->popup()) {
            m_completer->popup()->hide();
        }
    }

    if (m_minimap) {
        /*
         * Resource files still benefit enormously from minimap navigation,
         * especially when they contain hundreds of kilobytes of generated
         * array data.  The expensive semantic analysis remains disabled;
         * only the visual minimap stays available.
         */
        m_minimap->setVisible(true);
        m_minimap->update();
    }

    updateLineNumberAreaWidth(0);

    if (m_minimap) {
        const QRect view = viewport()->geometry();
        m_minimap->setGeometry(QRect(view.right() + 1, view.top(), CodeMinimapWidth, view.height()));
        m_minimap->raise();
    }

    setTheme(m_theme);
}

bool CodeEditor::isResourceMode() const
{
    return m_resourceMode;
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
    if (m_resourceMode) {
        return;
    }

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

    /*
     * Resource tabs intentionally use a lighter charcoal background so it is
     * immediately obvious that the tab is in lightweight resource mode.
     */
    QColor editorBackground = m_theme.editorBackground;
    if (m_resourceMode) {
        editorBackground = QColor(16, 16, 16);
    }

    p.setColor(QPalette::Base, editorBackground);
    p.setColor(QPalette::Text, m_theme.editorText);
    p.setColor(QPalette::Highlight, m_theme.selectionBackground);
    p.setColor(QPalette::HighlightedText, m_theme.selectionText);
    setPalette(p);

    /*
     * MainWindow has a generic QPlainTextEdit stylesheet, and Qt stylesheets
     * take precedence over QPalette.  That is why resource tabs were still
     * appearing black even though their palette was set to charcoal.
     *
     * Give CodeEditor its own background rule so the selected editor colour
     * wins while the rest of the inherited IDE styling remains intact.
     */
    setStyleSheet(
        QStringLiteral(
            "CodeEditor {"
            " background-color:%1;"
            " color:%2;"
            " selection-background-color:%3;"
            " selection-color:%4;"
            "}")
            .arg(
                ideThemeColorName(editorBackground),
                ideThemeColorName(m_theme.editorText),
                ideThemeColorName(m_theme.selectionBackground),
                ideThemeColorName(m_theme.selectionText)));

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

        block = nextVisibleBlockFast(block);
        top = bottom;
    }

    return {};
}

bool CodeEditor::loadFromFile(
    const QString &path,
    bool deferSyntaxHighlighting)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    /*
     * When opening a new tab, let the plain QTextDocument appear first.
     * QSyntaxHighlighter otherwise processes the document while setPlainText()
     * is still inside the open-file call, which makes the tab itself feel
     * slower than it really is.
     *
     * MainWindow calls enableSyntaxHighlighting() shortly after the tab has
     * been inserted and painted.
     */
    if (deferSyntaxHighlighting && m_highlighter) {
        delete m_highlighter;
        m_highlighter = nullptr;
    }

    QTextStream stream(&file);
    setPlainText(stream.readAll());
    setFilePath(path);
    document()->setModified(false);
    return true;
}

void CodeEditor::enableSyntaxHighlighting()
{
    if (m_highlighter) {
        return;
    }

    /*
     * Reattach normal highlighting after the editor is visible. The current
     * theme and cached project/API names are restored here, so the file first
     * appears immediately as plain text and then gains its syntax colours.
     */
    m_highlighter =
        new CSyntaxHighlighter(document());

    m_highlighter->setResourceMode(m_resourceMode);
    m_highlighter->setTheme(m_theme);

    if (!m_resourceMode) {
        m_highlighter->setExternalTypeNames(
            m_projectTypeNames);
        m_highlighter->setExternalApiNames(
            m_apiSyntaxNames);
    }

    viewport()->update();
}

void CodeEditor::shareDocumentFrom(CodeEditor *sourceEditor)
{
    if (!sourceEditor || sourceEditor == this) {
        return;
    }

    /*
     * The secondary split view must show and edit the exact same QTextDocument
     * as the primary view.  Do NOT give the shared document a second syntax
     * highlighter: highlighting belongs to the document, so the primary
     * editor's highlighter is already visible in both views.
     */
    if (m_highlighter) {
        delete m_highlighter;
        m_highlighter = nullptr;
    }

    QPlainTextEdit::setDocument(sourceEditor->document());

    /*
     * Folding visibility belongs to QTextDocument, so split views naturally
     * see the same collapsed blocks. Copy the already-known region list so the
     * secondary gutter gets its markers immediately, then follow future edits
     * on the newly shared document.
     */
    m_foldRegions = sourceEditor->m_foldRegions;
    attachFoldTracking();

    if (m_minimap) {
        static_cast<CodeMinimap *>(m_minimap)
            ->attachDocument(document());
    }

    m_filePath = sourceEditor->filePath();
    m_resourceMode = sourceEditor->isResourceMode();

    /*
     * shareDocumentFrom() is also used by split views. Copy the already-built
     * completion list from the source editor so opening a split does not need
     * another project-wide scan just to make the second pane useful.
     */
    m_functionCompletions = sourceEditor->m_functionCompletions;
    m_projectTypeNames = sourceEditor->m_projectTypeNames;
    m_apiSyntaxNames = sourceEditor->m_apiSyntaxNames;
    m_memberCompletionActive = false;
    m_memberCompletionPrefix.clear();
    if (m_completionModel) {
        m_completionModel->setStringList(m_functionCompletions);
    }

    setReadOnly(sourceEditor->isReadOnly());
    setTheme(sourceEditor->theme());
    setDiagnostics(sourceEditor->diagnostics());

    if (m_minimap) {
        m_minimap->update();
    }

    updateLineNumberAreaWidth(0);
    viewport()->update();
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

    return FoldGutterWidth
        + 12
        + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;
}

int CodeEditor::firstVisibleSourceBlockNumber() const
{
    const QTextBlock block =
        firstVisibleBlock();

    return block.isValid()
        ? block.blockNumber()
        : -1;
}

void CodeEditor::recalculateFoldScrollBarRange()
{
    if (!document()) {
        return;
    }

    QScrollBar *bar =
        verticalScrollBar();

    if (!bar) {
        return;
    }

    /*
     * Folding changes QTextBlock visibility without changing blockCount().
     * QPlainTextEdit therefore sometimes keeps the old vertical maximum until
     * another larger layout event (such as closing/reopening the tab) occurs.
     *
     * CodeEditor is NoWrap, so every visible QTextBlock is one visual line.
     * Recalculate the range directly from what is ACTUALLY visible now.
     */
    int visibleBlocks = 0;

    QTextBlock block =
        document()->firstBlock();

    while (block.isValid()) {
        if (block.isVisible()) {
            ++visibleBlocks;
        }

        block = block.next();
    }

    const int pageStep =
        qMax(1, bar->pageStep());

    const int expectedMaximum =
        qMax(
            0,
            visibleBlocks - pageStep);

    /*
     * setRange() can cause QPlainTextEdit to move the scrollbar while its
     * internal layout is being rebuilt. Preserve the user's current view
     * explicitly so recalculating fold geometry never means "go to line 1".
     */
    const int oldValue =
        bar->value();

    if (bar->minimum() != 0
        || bar->maximum() != expectedMaximum) {
        bar->setRange(
            0,
            expectedMaximum);
    }

    bar->setValue(
        qBound(
            bar->minimum(),
            oldValue,
            bar->maximum()));
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

            const int foldEnd =
                foldEndForStart(blockNumber);

            if (foldEnd > blockNumber) {
                const bool folded =
                    isFolded(blockNumber);

                const int centreY =
                    top + fontMetrics().height() / 2;

                QPolygon triangle;

                if (folded) {
                    // Right-facing triangle: collapsed.
                    triangle
                        << QPoint(8, centreY - 4)
                        << QPoint(8, centreY + 4)
                        << QPoint(14, centreY);
                } else {
                    // Down-facing triangle: expanded.
                    triangle
                        << QPoint(6, centreY - 3)
                        << QPoint(14, centreY - 3)
                        << QPoint(10, centreY + 3);
                }

                painter.setPen(Qt::NoPen);
                painter.setBrush(m_theme.lineNumber);
                painter.drawPolygon(triangle);
                painter.setBrush(Qt::NoBrush);
            }

            const QString number =
                QString::number(blockNumber + 1);

            painter.setPen(m_theme.lineNumber);

            painter.drawText(
                FoldGutterWidth + 6,
                top,
                m_lineNumberArea->width()
                    - FoldGutterWidth - 12,
                fontMetrics().height(),
                Qt::AlignRight,
                number
                );
        }

        block = nextVisibleBlockFast(block);
        top = bottom;

        if (block.isValid()) {
            blockNumber = block.blockNumber();
            bottom =
                top
                + qRound(
                    blockBoundingRect(block)
                        .height());
        }
    }
}

void CodeEditor::attachFoldTracking()
{
    QObject::disconnect(m_foldDocumentChangedConnection);

    if (!document()) {
        return;
    }

    m_foldDocumentChangedConnection =
        connect(
            document(),
            &QTextDocument::contentsChanged,
            this,
            [this]() {
                /*
                 * Editing invalidates any in-flight cooperative catalogue. Stop
                 * the current batch immediately; the next navigation/idle sync
                 * will restart from the fresh document state.
                 */
                m_deferredEditorStateDirty = true;
                ++m_deferredScanGeneration;

                if (m_foldScanTimer) {
                    m_foldScanTimer->stop();
                }

                if (m_minimap) {
                    static_cast<CodeMinimap *>(m_minimap)
                        ->cancelQueuedRefresh();
                }
            });
}

void CodeEditor::syncDeferredEditorStateNow()
{
    if (!m_deferredEditorStateDirty) {
        return;
    }

    /*
     * IMPORTANT: this function must return almost immediately. Enter/arrows can
     * call it from the input path, so never walk a 100-200 KB document here.
     *
     * Folding and minimap updates are started as cooperative event-loop jobs.
     * Local/project type names are supplied by MainWindow's background semantic
     * catalogue, so there is no second full-file typedef scan here.
     */
    m_deferredEditorStateDirty = false;

    startQueuedFoldRegionScan();

    if (m_minimap) {
        static_cast<CodeMinimap *>(m_minimap)
            ->refreshQueued();
    }
}

void CodeEditor::requestDeferredAnalysisSync()
{
    if (!m_deferredEditorStateDirty) {
        return;
    }

    syncDeferredEditorStateNow();
    emit deferredAnalysisSyncRequested();
}


void CodeEditor::startQueuedFoldRegionScan()
{
    if (!document() || !m_foldScanTimer) {
        return;
    }

    m_foldScanTimer->stop();

    m_pendingFoldRegions.clear();
    m_pendingFoldStack.clear();
    m_foldScanInBlockComment = false;
    m_foldScanPreviousCodeBlock = -1;
    m_foldScanBlock =
        document()->firstBlock();

    m_foldScanRunningGeneration =
        m_deferredScanGeneration;

    m_foldScanTimer->start();
}

void CodeEditor::continueQueuedFoldRegionScan()
{
    if (!document()
        || !m_foldScanTimer
        || m_foldScanRunningGeneration
            != m_deferredScanGeneration) {
        return;
    }

    int budget = 64;

    while (m_foldScanBlock.isValid()
           && budget-- > 0) {
        const int blockNumber =
            m_foldScanBlock.blockNumber();

        const QString line =
            m_foldScanBlock.text();

        bool inDoubleQuote = false;
        bool inSingleQuote = false;
        bool escaped = false;
        bool lineHasCode = false;

        for (int i = 0; i < line.size(); ++i) {
            const QChar ch =
                line.at(i);

            const QChar next =
                i + 1 < line.size()
                    ? line.at(i + 1)
                    : QChar();

            if (m_foldScanInBlockComment) {
                if (ch == QLatin1Char('*')
                    && next == QLatin1Char('/')) {
                    m_foldScanInBlockComment = false;
                    ++i;
                }
                continue;
            }

            if (inDoubleQuote) {
                if (escaped) {
                    escaped = false;
                    continue;
                }

                if (ch == QLatin1Char('\\')) {
                    escaped = true;
                    continue;
                }

                if (ch == QLatin1Char('"')) {
                    inDoubleQuote = false;
                }
                continue;
            }

            if (inSingleQuote) {
                if (escaped) {
                    escaped = false;
                    continue;
                }

                if (ch == QLatin1Char('\\')) {
                    escaped = true;
                    continue;
                }

                if (ch == QLatin1Char('\'')) {
                    inSingleQuote = false;
                }
                continue;
            }

            if (ch == QLatin1Char('/')
                && next == QLatin1Char('/')) {
                break;
            }

            if (ch == QLatin1Char('/')
                && next == QLatin1Char('*')) {
                m_foldScanInBlockComment = true;
                ++i;
                continue;
            }

            if (ch == QLatin1Char('"')) {
                inDoubleQuote = true;
                lineHasCode = true;
                continue;
            }

            if (ch == QLatin1Char('\'')) {
                inSingleQuote = true;
                lineHasCode = true;
                continue;
            }

            if (ch == QLatin1Char('{')) {
                const bool codeBeforeBrace =
                    lineHasCode
                    || !line.left(i)
                            .trimmed()
                            .isEmpty();

                const int anchorBlock =
                    !codeBeforeBrace
                    && m_foldScanPreviousCodeBlock >= 0
                        ? m_foldScanPreviousCodeBlock
                        : blockNumber;

                m_pendingFoldStack.append(
                    qMakePair(
                        blockNumber,
                        anchorBlock));

                lineHasCode = true;
                continue;
            }

            if (ch == QLatin1Char('}')) {
                if (!m_pendingFoldStack.isEmpty()) {
                    const QPair<int, int> open =
                        m_pendingFoldStack.takeLast();

                    if (blockNumber > open.second) {
                        bool merged = false;

                        for (QPair<int, int> &region :
                             m_pendingFoldRegions) {
                            if (region.first
                                == open.second) {
                                region.second =
                                    qMax(
                                        region.second,
                                        blockNumber);
                                merged = true;
                                break;
                            }
                        }

                        if (!merged) {
                            m_pendingFoldRegions.append(
                                qMakePair(
                                    open.second,
                                    blockNumber));
                        }
                    }
                }

                lineHasCode = true;
                continue;
            }

            if (!ch.isSpace()) {
                lineHasCode = true;
            }
        }

        if (lineHasCode) {
            m_foldScanPreviousCodeBlock =
                blockNumber;
        }

        m_foldScanBlock =
            m_foldScanBlock.next();
    }

    if (m_foldScanRunningGeneration
        != m_deferredScanGeneration) {
        return;
    }

    if (m_foldScanBlock.isValid()) {
        m_foldScanTimer->start();
        return;
    }

    finishQueuedFoldRegionScan();
}

void CodeEditor::finishQueuedFoldRegionScan()
{
    if (!document()
        || m_foldScanRunningGeneration
            != m_deferredScanGeneration) {
        return;
    }

    std::sort(
        m_pendingFoldRegions.begin(),
        m_pendingFoldRegions.end(),
        [](const QPair<int, int> &a,
           const QPair<int, int> &b) {
            if (a.first != b.first) {
                return a.first < b.first;
            }

            return a.second > b.second;
        });

    m_foldRegions =
        m_pendingFoldRegions;

    QSet<int> validStarts;

    for (const QPair<int, int> &region :
         std::as_const(m_foldRegions)) {
        validStarts.insert(region.first);
    }

    bool hasFoldedRegion = false;
    bool clearedStaleFold = false;

    QTextBlock block =
        document()->firstBlock();

    while (block.isValid()) {
        if (auto *data =
                foldDataForBlock(block, false)) {
            if (data->folded
                && !validStarts.contains(
                    block.blockNumber())) {
                data->folded = false;
                clearedStaleFold = true;
            }

            if (data->folded) {
                hasFoldedRegion = true;
            }
        }

        block = block.next();
    }

    if (hasFoldedRegion
        || clearedStaleFold) {
        applyFoldVisibility();
    } else if (m_lineNumberArea) {
        m_lineNumberArea->update();
    }

    m_pendingFoldRegions.clear();
    m_pendingFoldStack.clear();
    m_foldScanBlock = QTextBlock();
}


void CodeEditor::rebuildFoldRegions()
{
    if (!document()) {
        m_foldRegions.clear();
        return;
    }

    struct OpenBrace {
        int braceBlock = -1;
        int anchorBlock = -1;
    };

    QList<OpenBrace> stack;
    QList<QPair<int, int>> regions;

    bool inBlockComment = false;
    int previousCodeBlock = -1;

    QTextBlock block =
        document()->firstBlock();

    while (block.isValid()) {
        const int blockNumber =
            block.blockNumber();

        const QString line =
            block.text();

        bool inDoubleQuote = false;
        bool inSingleQuote = false;
        bool escaped = false;
        bool lineHasCode = false;

        for (int i = 0; i < line.size(); ++i) {
            const QChar ch = line.at(i);
            const QChar next =
                i + 1 < line.size()
                    ? line.at(i + 1)
                    : QChar();

            if (inBlockComment) {
                if (ch == QLatin1Char('*')
                    && next == QLatin1Char('/')) {
                    inBlockComment = false;
                    ++i;
                }
                continue;
            }

            if (inDoubleQuote) {
                if (escaped) {
                    escaped = false;
                    continue;
                }

                if (ch == QLatin1Char('\\')) {
                    escaped = true;
                    continue;
                }

                if (ch == QLatin1Char('"')) {
                    inDoubleQuote = false;
                }

                continue;
            }

            if (inSingleQuote) {
                if (escaped) {
                    escaped = false;
                    continue;
                }

                if (ch == QLatin1Char('\\')) {
                    escaped = true;
                    continue;
                }

                if (ch == QLatin1Char('\'')) {
                    inSingleQuote = false;
                }

                continue;
            }

            if (ch == QLatin1Char('/')
                && next == QLatin1Char('/')) {
                // The remainder of this physical line is a C++-style comment.
                break;
            }

            if (ch == QLatin1Char('/')
                && next == QLatin1Char('*')) {
                inBlockComment = true;
                ++i;
                continue;
            }

            if (ch == QLatin1Char('"')) {
                inDoubleQuote = true;
                lineHasCode = true;
                continue;
            }

            if (ch == QLatin1Char('\'')) {
                inSingleQuote = true;
                lineHasCode = true;
                continue;
            }

            if (ch == QLatin1Char('{')) {
                /*
                 * Allman-style C puts the opening brace on the next line:
                 *
                 *     void thing(void)
                 *     {
                 *
                 * Anchor that fold marker to the preceding code line so the
                 * useful declaration/function signature remains visible when
                 * collapsed. Same idea applies beautifully to large arrays.
                 */
                const bool codeBeforeBrace =
                    lineHasCode
                    || !line.left(i).trimmed().isEmpty();

                const int anchorBlock =
                    !codeBeforeBrace
                        && previousCodeBlock >= 0
                        ? previousCodeBlock
                        : blockNumber;

                stack.append(
                    {blockNumber, anchorBlock});

                lineHasCode = true;
                continue;
            }

            if (ch == QLatin1Char('}')) {
                if (!stack.isEmpty()) {
                    const OpenBrace open =
                        stack.takeLast();

                    if (blockNumber > open.anchorBlock) {
                        bool merged = false;

                        /*
                         * More than one opening brace can occur on the same
                         * source line (nested initialisers are the usual case).
                         * A gutter has room for one marker, so let that marker
                         * represent the outermost range from that line.
                         */
                        for (QPair<int, int> &region : regions) {
                            if (region.first
                                == open.anchorBlock) {
                                region.second =
                                    qMax(
                                        region.second,
                                        blockNumber);
                                merged = true;
                                break;
                            }
                        }

                        if (!merged) {
                            regions.append(
                                qMakePair(
                                    open.anchorBlock,
                                    blockNumber));
                        }
                    }
                }

                lineHasCode = true;
                continue;
            }

            if (!ch.isSpace()) {
                lineHasCode = true;
            }
        }

        if (lineHasCode) {
            previousCodeBlock = blockNumber;
        }

        block = block.next();
    }

    std::sort(
        regions.begin(),
        regions.end(),
        [](const QPair<int, int> &a,
           const QPair<int, int> &b) {
            if (a.first != b.first) {
                return a.first < b.first;
            }

            return a.second > b.second;
        });

    m_foldRegions = regions;

    QSet<int> validStarts;
    for (const QPair<int, int> &region
         : std::as_const(m_foldRegions)) {
        validStarts.insert(region.first);
    }

    bool hasFoldedRegion = false;
    bool clearedStaleFold = false;

    /*
     * Fold state is attached to QTextBlocks rather than raw line numbers.
     * QTextBlock user data follows the block when lines are inserted above it,
     * which keeps a collapsed function attached to that function while editing.
     */
    block = document()->firstBlock();
    while (block.isValid()) {
        if (auto *data =
                foldDataForBlock(block, false)) {
            if (data->folded
                && !validStarts.contains(
                    block.blockNumber())) {
                data->folded = false;
                clearedStaleFold = true;
            }

            if (data->folded) {
                hasFoldedRegion = true;
            }
        }

        block = block.next();
    }

    if (hasFoldedRegion || clearedStaleFold) {
        applyFoldVisibility();
    } else if (m_lineNumberArea) {
        m_lineNumberArea->update();
    }
}

int CodeEditor::visibleBlockNumberAtY(int y) const
{
    QTextBlock block =
        firstVisibleBlock();

    int top =
        qRound(
            blockBoundingGeometry(block)
                .translated(contentOffset())
                .top());

    while (block.isValid()) {
        const int height =
            qRound(blockBoundingRect(block).height());

        const int bottom =
            top + height;

        if (block.isVisible()
            && height > 0
            && y >= top
            && y < bottom) {
            return block.blockNumber();
        }

        if (top > y) {
            break;
        }

        block = nextVisibleBlockFast(block);
        top = bottom;
    }

    return -1;
}

int CodeEditor::foldEndForStart(int startBlock) const
{
    for (const QPair<int, int> &region
         : m_foldRegions) {
        if (region.first == startBlock) {
            return region.second;
        }

        if (region.first > startBlock) {
            break;
        }
    }

    return -1;
}

bool CodeEditor::isFolded(int startBlock) const
{
    const QTextBlock block =
        document()
            ? document()->findBlockByNumber(
                  startBlock)
            : QTextBlock();

    if (!block.isValid()) {
        return false;
    }

    const auto *data =
        dynamic_cast<const FoldBlockData *>(
            block.userData());

    return data && data->folded;
}

QTextBlock CodeEditor::nextVisibleBlockFast(
    const QTextBlock &block) const
{
    if (!block.isValid()) {
        return {};
    }

    /*
     * A collapsed fold can hide thousands of QTextBlocks whose layout height
     * is zero. Walking block.next() through all of them on every repaint makes
     * scrolling look like the application has frozen.
     *
     * When the current visible block is a folded anchor, jump directly to the
     * block after that region instead of visiting every hidden block.
     */
    const int startBlock =
        block.blockNumber();

    const int endBlock =
        foldEndForStart(startBlock);

    if (endBlock > startBlock
        && isFolded(startBlock)
        && document()) {
        return document()->findBlockByNumber(
            endBlock + 1);
    }

    QTextBlock next =
        block.next();

    /*
     * Normally the folded-anchor jump above handles every hidden run. This is
     * just a defensive fallback for any transient layout state while Qt is
     * recalculating block visibility.
     */
    while (next.isValid()
           && !next.isVisible()) {
        next = next.next();
    }

    return next;
}

bool CodeEditor::foldMarkerAtY(int y) const
{
    const int blockNumber =
        visibleBlockNumberAtY(y);

    return blockNumber >= 0
        && foldEndForStart(blockNumber)
            > blockNumber;
}

void CodeEditor::toggleFoldAtY(int y)
{
    const int preservedScrollValue =
        verticalScrollBar()
            ? verticalScrollBar()->value()
            : -1;

    const int startBlock =
        visibleBlockNumberAtY(y);

    const int endBlock =
        foldEndForStart(startBlock);

    if (startBlock < 0
        || endBlock <= startBlock) {
        return;
    }

    QTextBlock start =
        document()->findBlockByNumber(
            startBlock);

    if (!start.isValid()) {
        return;
    }

    FoldBlockData *data =
        foldDataForBlock(start, true);

    if (!data) {
        return;
    }

    const bool folding =
        !data->folded;

    data->folded = folding;

    if (folding) {
        const int cursorBlock =
            textCursor().blockNumber();

        if (cursorBlock > startBlock
            && cursorBlock <= endBlock) {
            QTextCursor cursor(start);
            cursor.movePosition(
                QTextCursor::EndOfBlock);
            setTextCursor(cursor);
        }
    }

    applyFoldVisibility(
        preservedScrollValue);
}

void CodeEditor::collapseAllFolds()
{
    if (!document()) {
        return;
    }

    const int preservedScrollValue =
        verticalScrollBar()
            ? verticalScrollBar()->value()
            : -1;

    /*
     * Mark every discovered fold region as collapsed, including nested ones.
     * That means when an outer function/struct is expanded later, any nested
     * regions the user asked to collapse-all remain collapsed too.
     */
    for (const QPair<int, int> &region
         : std::as_const(m_foldRegions)) {
        QTextBlock block =
            document()->findBlockByNumber(
                region.first);

        if (!block.isValid()) {
            continue;
        }

        FoldBlockData *data =
            foldDataForBlock(block, true);

        if (data) {
            data->folded = true;
        }
    }

    /*
     * Do not leave the caret sitting inside a block which is about to become
     * invisible. Move it to the nearest visible fold anchor instead.
     */
    const int cursorBlock =
        textCursor().blockNumber();

    int targetAnchor = -1;

    for (const QPair<int, int> &region
         : std::as_const(m_foldRegions)) {
        if (cursorBlock > region.first
            && cursorBlock <= region.second) {
            targetAnchor =
                targetAnchor < 0
                    ? region.first
                    : qMin(targetAnchor,
                           region.first);
        }
    }

    if (targetAnchor >= 0) {
        const QTextBlock block =
            document()->findBlockByNumber(
                targetAnchor);

        if (block.isValid()) {
            QTextCursor cursor(block);
            cursor.movePosition(
                QTextCursor::EndOfBlock);
            setTextCursor(cursor);
        }
    }

    applyFoldVisibility(
        preservedScrollValue);
}

void CodeEditor::expandAllFolds()
{
    if (!document()) {
        return;
    }

    const int preservedScrollValue =
        verticalScrollBar()
            ? verticalScrollBar()->value()
            : -1;

    /*
     * Clear fold state from every current folding anchor. Hidden QTextBlocks
     * themselves are restored by applyFoldVisibility().
     */
    for (const QPair<int, int> &region
         : std::as_const(m_foldRegions)) {
        QTextBlock block =
            document()->findBlockByNumber(
                region.first);

        if (!block.isValid()) {
            continue;
        }

        if (auto *data =
                foldDataForBlock(block, false)) {
            data->folded = false;
        }
    }

    applyFoldVisibility(
        preservedScrollValue);
}

void CodeEditor::applyFoldVisibility(
    int preferredScrollValue)
{
    if (!document()) {
        return;
    }

    /*
     * Rebuild visibility from fold state each time. This makes nested folding
     * predictable: an inner fold can remain folded while its outer function is
     * collapsed, then reappear still folded when the outer function expands.
     */
    QTextBlock block =
        document()->firstBlock();

    while (block.isValid()) {
        block.setVisible(true);
        block.setLineCount(1);
        block = block.next();
    }

    for (const QPair<int, int> &region
         : std::as_const(m_foldRegions)) {
        if (!isFolded(region.first)) {
            continue;
        }

        QTextBlock hidden =
            document()
                ->findBlockByNumber(
                    region.first)
                .next();

        while (hidden.isValid()
               && hidden.blockNumber()
                   <= region.second) {
            hidden.setVisible(false);
            hidden.setLineCount(0);
            hidden = hidden.next();
        }
    }

    /*
     * Visibility does not alter the source text, but QPlainTextDocumentLayout
     * needs to recalculate block geometry / scrollbar range.
     */
    document()->markContentsDirty(
        0,
        document()->characterCount());

    /*
     * Recalculate the gutter/editor scroll geometry as part of EVERY folding
     * change. This path is shared by:
     *
     *   - clicking one fold triangle
     *   - Collapse All
     *   - Expand All
     *
     * so none of those operations can leave the scrollbar carrying the range
     * from the previous folded state.
     */
    recalculateFoldScrollBarRange();

    if (preferredScrollValue >= 0
        && verticalScrollBar()) {
        QScrollBar *bar =
            verticalScrollBar();

        bar->setValue(
            qBound(
                bar->minimum(),
                preferredScrollValue,
                bar->maximum()));
    }

    updateLineNumberAreaWidth(0);

    if (m_lineNumberArea) {
        m_lineNumberArea->update();
    }

    if (m_minimap) {
        static_cast<CodeMinimap *>(m_minimap)
            ->refreshNow();
    }

    /*
     * Qt may perform its own queued document-layout work after this function
     * returns. Re-assert the correct range after those passes too. The 20 ms
     * refresh was already useful on this setup; the 80 ms pass protects
     * against a later Qt scrollbar/layout update restoring the stale range.
     */
    const auto settleFoldGeometry =
        [this, preferredScrollValue]() {
            recalculateFoldScrollBarRange();

            if (preferredScrollValue >= 0
                && verticalScrollBar()) {
                QScrollBar *bar =
                    verticalScrollBar();

                bar->setValue(
                    qBound(
                        bar->minimum(),
                        preferredScrollValue,
                        bar->maximum()));
            }

            updateLineNumberAreaWidth(0);

            if (m_lineNumberArea) {
                m_lineNumberArea->update();
            }

            if (m_minimap) {
                static_cast<CodeMinimap *>(m_minimap)
                    ->refreshNow();
            }

            viewport()->update();
        };

    QTimer::singleShot(
        0,
        this,
        settleFoldGeometry);

    QTimer::singleShot(
        20,
        this,
        settleFoldGeometry);

    QTimer::singleShot(
        80,
        this,
        settleFoldGeometry);

    viewport()->update();
    updateGeometry();
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
        /*
         * Sidbox sources use real tab characters for indentation. Keep the
         * visual tab width at four columns, but store one '\t' in the file
         * instead of four space characters.
         */
        nextIndent += QLatin1Char('\t');
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
    const QString indent(QLatin1Char('\t'));

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

    const int indentWidth = indentWidthColumns();

    QTextBlock block = firstVisibleBlock();
    int top =
        qRound(
            blockBoundingGeometry(block)
                .translated(contentOffset())
                .top());

    int bottom =
        top + qRound(blockBoundingRect(block).height());

    while (block.isValid()
           && top <= event->rect().bottom()) {

        if (block.isVisible()
            && bottom >= event->rect().top()) {

            const QString text = block.text();
            const QTextLayout *layout = block.layout();

            if (layout && layout->lineCount() > 0) {
                const QTextLine line = layout->lineAt(0);

                const qreal left =
                    blockBoundingGeometry(block)
                        .translated(contentOffset())
                        .left();

                int leadingEnd = 0;
                while (leadingEnd < text.size()) {
                    const QChar ch = text.at(leadingEnd);

                    if (ch == QLatin1Char('\t')
                        || ch == QLatin1Char(' ')) {
                        ++leadingEnd;
                    } else {
                        break;
                    }
                }

                /*
                 * IMPORTANT:
                 *
                 * Do not calculate guide positions as
                 *     4 * widthOf(' ')
                 *
                 * Qt lays out a real tab using QTextLayout's tab stops, and
                 * that rendered distance can differ slightly from four space
                 * glyphs because of font metrics / DPI / fractional widths.
                 *
                 * cursorToX() gives us the EXACT x position Qt used when it
                 * rendered the text. The guide follows the real tab stop,
                 * then moves one physical pixel back into the indentation
                 * whitespace. That lets us paint it above the active-line
                 * background without drawing through the first code glyph.
                 */
                int i = 0;
                int spacesInRun = 0;
                int spaceRunStart = 0;

                while (i < leadingEnd) {
                    const QChar ch = text.at(i);

                    if (ch == QLatin1Char('\t')) {
                        const qreal after =
                            line.cursorToX(i + 1);

                        const int x =
                            qRound(left + after) - 1;

                        if (x >= event->rect().left()
                            && x <= event->rect().right()) {
                            painter.drawLine(
                                x,
                                top,
                                x,
                                bottom);
                        }

                        ++i;
                        spacesInRun = 0;
                        continue;
                    }

                    /*
                     * Keep old files which still contain groups of spaces
                     * looking sensible too. A complete four-space indent is
                     * measured by QTextLayout as well. The same one-pixel
                     * inset keeps legacy space indentation clear of code text.
                     */
                    if (spacesInRun == 0) {
                        spaceRunStart = i;
                    }

                    ++spacesInRun;
                    ++i;

                    if (spacesInRun == indentWidth) {
                        const qreal after =
                            line.cursorToX(i);

                        const int x =
                            qRound(left + after) - 1;

                        if (x >= event->rect().left()
                            && x <= event->rect().right()) {
                            painter.drawLine(
                                x,
                                top,
                                x,
                                bottom);
                        }

                        spacesInRun = 0;
                    }
                }
            }
        }

        block = nextVisibleBlockFast(block);
        top = bottom;

        if (block.isValid()) {
            bottom =
                top
                + qRound(
                    blockBoundingRect(block)
                        .height());
        }
    }
}

void CodeEditor::mousePressEvent(QMouseEvent *event)
{
    if (!m_resourceMode
        && event->button() == Qt::LeftButton
        && (event->modifiers() & Qt::ControlModifier)) {

        QTextCursor cursor =
            cursorForPosition(event->position().toPoint());

        /*
         * #include navigation gets first refusal because include paths can
         * contain '.', '/', '-' and other characters which are not ordinary C
         * identifier characters.
         */
        const QString includeName =
            includePathAtCursor(cursor);

        if (!includeName.isEmpty()) {
            emit includeFileRequested(includeName);
            event->accept();
            return;
        }

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

    const int oldCursorPosition =
        textCursor().position();

    QPlainTextEdit::mousePressEvent(event);

    if (event->button() == Qt::LeftButton
        && textCursor().position()
            != oldCursorPosition) {
        requestDeferredAnalysisSync();
    }
}

void CodeEditor::mouseMoveEvent(QMouseEvent *event)
{
    if (!m_resourceMode
        && (event->modifiers() & Qt::ControlModifier)) {

        QTextCursor cursor =
            cursorForPosition(event->position().toPoint());

        if (!includePathAtCursor(cursor).isEmpty()) {
            viewport()->setCursor(Qt::PointingHandCursor);
        } else {
            cursor.select(QTextCursor::WordUnderCursor);
            const QString symbol =
                cursor.selectedText().trimmed();

            static const QRegularExpression identifierExpression(
                QStringLiteral("^[A-Za-z_][A-Za-z0-9_]*$"));

            viewport()->setCursor(
                identifierExpression.match(symbol).hasMatch()
                    ? Qt::PointingHandCursor
                    : Qt::IBeamCursor);
        }
    } else {
        viewport()->setCursor(Qt::IBeamCursor);
    }

    QPlainTextEdit::mouseMoveEvent(event);
}

void CodeEditor::paintEvent(QPaintEvent *event)
{
    /*
     * Let Qt paint the editor first. This includes the active-line background.
     * Then paint the indentation guides so they remain visible across that
     * highlighted line.
     *
     * drawIndentGuides() keeps each guide one physical pixel inside the
     * indentation whitespace, so although the guides are painted last they do
     * not sit on top of the first code glyph at a tab boundary.
     */
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
        const QString blockText =
            cursor.block().text();

        const int position =
            cursor.positionInBlock();

        if (position < blockText.size()
            && blockText.at(position) == ch) {
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

    const QString blockText =
        cursor.block().text();

    const int position =
        cursor.positionInBlock();

    if (position <= 0
        || position >= blockText.size()) {
        return false;
    }

    const QChar left =
        blockText.at(position - 1);

    const QChar right =
        blockText.at(position);

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
    if (!m_resourceMode && event->key() == Qt::Key_F1) {
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

    /*
     * Structural/source navigation shortcuts.
     *
     * These are intercepted BEFORE QPlainTextEdit gets them, so they never
     * perform the normal Ctrl+arrow scrolling behaviour first.
     */
    const Qt::KeyboardModifiers modifiers =
        event->modifiers();

    const bool controlOnly =
        (modifiers & Qt::ControlModifier)
        && !(modifiers & Qt::ShiftModifier)
        && !(modifiers & Qt::AltModifier)
        && !(modifiers & Qt::MetaModifier);

    if (controlOnly
        && (event->key() == Qt::Key_Up
            || event->key() == Qt::Key_Down)) {

        /*
         * If the document has changed, start the non-blocking catalogue catch-up
         * before navigating. MainWindow deliberately uses the LAST completed
         * catalogue for this keypress, so navigation remains instant.
         */
        requestDeferredAnalysisSync();

        emit structureNavigationRequested(
            event->key() == Qt::Key_Up
                ? -1
                : 1);

        event->accept();
        return;
    }

    if (controlOnly
        && (event->key() == Qt::Key_PageUp
            || event->key() == Qt::Key_PageDown)) {

        QTextCursor cursor =
            textCursor();

        cursor.movePosition(
            event->key() == Qt::Key_PageUp
                ? QTextCursor::Start
                : QTextCursor::End);

        setTextCursor(cursor);
        centerCursor();

        requestDeferredAnalysisSync();

        event->accept();
        return;
    }

    /*
     * Shift+Tab is now Sidbox's editor-tab cycler. Qt commonly reports this as
     * Key_Backtab rather than Key_Tab+Shift, so handle both forms.
     */
    if (event->key() == Qt::Key_Backtab
        || (event->key() == Qt::Key_Tab
            && (modifiers & Qt::ShiftModifier))) {
        emit nextEditorTabRequested();
        event->accept();
        return;
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
                baseIndent + QLatin1Char('\t');

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

        /*
         * Enter is both an edit and a navigation action. It is one of the
         * explicit points where the user wants deferred state caught up now.
         */
        requestDeferredAnalysisSync();

        event->accept();
        return;
    }

    // Tab indents either the selected block or the current cursor position.
    if (event->key() == Qt::Key_Tab && !(event->modifiers() & Qt::ShiftModifier)) {
        QTextCursor cursor = textCursor();

        if (cursor.hasSelection()) {
            indentSelection();
        } else {
            cursor.insertText(QString(QLatin1Char('\t')));
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

    QPlainTextEdit::keyPressEvent(event);

    switch (event->key()) {
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_Home:
    case Qt::Key_End:
    case Qt::Key_PageUp:
    case Qt::Key_PageDown:
        requestDeferredAnalysisSync();
        break;
    default:
        break;
    }

    if (m_resourceMode) {
        if (m_completer && m_completer->popup()) {
            m_completer->popup()->hide();
        }
        return;
    }

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

    /*
     * The minimap lives in the right-hand viewport margin for every editor
     * mode, including lightweight .res resource tabs.
     */
    const QRect view = viewport()->geometry();
    m_minimap->setGeometry(
        QRect(view.right() + 1, view.top(), CodeMinimapWidth, view.height()));
}

void CodeEditor::updateLineNumberAreaWidth(int)
{
    /*
     * Always reserve the normal minimap strip on the right.  Resource mode
     * disables heavyweight semantic analysis, not the minimap itself.
     */
    setViewportMargins(
        lineNumberAreaWidth(),
        0,
        CodeMinimapWidth,
        0);
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
    const QTextCursor cursor =
        textCursor();

    const QString text =
        cursor.block().text();

    int position =
        qBound(
            0,
            cursor.positionInBlock(),
            text.size());

    auto isIdentifierChar = [](QChar ch) {
        return ch.isLetterOrNumber()
            || ch == QLatin1Char('_');
    };

    if (position > 0
        && (position == text.size()
            || !isIdentifierChar(text.at(position)))
        && isIdentifierChar(text.at(position - 1))) {
        --position;
    }

    if (position >= text.size()
        || !isIdentifierChar(text.at(position))) {
        return {};
    }

    int first = position;
    while (first > 0
           && isIdentifierChar(text.at(first - 1))) {
        --first;
    }

    int last = position + 1;
    while (last < text.size()
           && isIdentifierChar(text.at(last))) {
        ++last;
    }

    return text.mid(first, last - first);
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
