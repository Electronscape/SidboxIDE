#include "codeeditor.h"

#include "csyntaxhighlighter.h"

#include <QAbstractItemView>
#include <QCompleter>
#include <QFile>
#include <QFocusEvent>
#include <QFont>
#include <QFontDatabase>
#include <QKeyEvent>
#include <QPainter>
#include <QColor>
#include <QRegularExpression>
#include <QScrollBar>
#include <QStringListModel>
#include <QTextBlock>
#include <QTextEdit>
#include <QTextStream>
#include <QWidget>

namespace {
class LineNumberArea : public QWidget
{
    public:
        explicit LineNumberArea(CodeEditor *editor)
            : QWidget(editor)
            , m_editor(editor)
        {
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

    private:
        CodeEditor *m_editor;
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

CodeEditor::CodeEditor(QWidget *parent)
    : QPlainTextEdit(parent)
    , m_lineNumberArea(new LineNumberArea(this))
    , m_highlighter(new CSyntaxHighlighter(document()))
    , m_completer(new QCompleter(this))
    , m_completionModel(new QStringListModel(this))
    , m_selectedArgument(-1)
{
    const QFont fixedFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    setFont(fixedFont);
    setLineWrapMode(QPlainTextEdit::NoWrap);
    setTabStopDistance(fontMetrics().horizontalAdvance(QLatin1Char(' ')) * 4);
    document()->setModified(false);

    QPalette p = palette();
    p.setColor(QPalette::Base, QColor(0x00, 0x10, 0x20));
    p.setColor(QPalette::Text, QColor(0xd8, 0xe8, 0xd0));
    setPalette(p);

    connect(this, &CodeEditor::blockCountChanged, this, &CodeEditor::updateLineNumberAreaWidth);
    connect(this, &CodeEditor::updateRequest, this, &CodeEditor::updateLineNumberArea);
    connect(this, &CodeEditor::cursorPositionChanged, this, &CodeEditor::highlightCurrentLine);
    connect(this, &CodeEditor::cursorPositionChanged, this, [this]() {
        emit quickTipCandidateChanged(textUnderCursor());
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
        insertFunctionCompletion(completion);
    });
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
    QStringList sortedSignatures = signatures;
    sortedSignatures.removeDuplicates();
    sortedSignatures.sort(Qt::CaseInsensitive);
    m_completionModel->setStringList(sortedSignatures);
}


void CodeEditor::setCompletionFont(const QFont &font)
{
    if (m_completer) {
        m_completer->popup()->setFont(font);
    }
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
    painter.fillRect(event->rect(), QColor(0x00, 0x20, 0x30));

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + qRound(blockBoundingRect(block).height());

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            const QString number = QString::number(blockNumber + 1);
            painter.setPen(QColor(0, 255, 64));
            painter.drawText(0, top, m_lineNumberArea->width() - 6, fontMetrics().height(), Qt::AlignRight, number);
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
    const int spaceWidth = qMax(1, fontMetrics().horizontalAdvance(QLatin1Char(32)));
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
    QPen pen(QColor(0x10, 0x38, 0x38));
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

void CodeEditor::paintEvent(QPaintEvent *event)
{
    QPlainTextEdit::paintEvent(event);
    drawIndentGuides(event);
}

void CodeEditor::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_F1) {
        emit quickTipRequested(textUnderCursor());
        event->accept();
        return;
    }

    if (m_completer && m_completer->popup()->isVisible()) {
        switch (event->key()) {
        case Qt::Key_Tab:
        case Qt::Key_Return:
        case Qt::Key_Enter:
            insertFunctionCompletion(m_completer->currentCompletion());
            m_completer->popup()->hide();
            event->accept();
            return;
        case Qt::Key_Escape:
            m_completer->popup()->hide();
            event->accept();
            return;
        default:
            break;
        }
    }

    /*
    if (event->key() == Qt::Key_Tab && !m_argumentRanges.isEmpty()) {
        selectArgument(m_selectedArgument + 1);
        event->accept();
        return;
    }
    */

    QPlainTextEdit::keyPressEvent(event);

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
    completionRect.setWidth(m_completer->popup()->sizeHintForColumn(0) + m_completer->popup()->verticalScrollBar()->sizeHint().width());
    m_completer->complete(completionRect);
}

void CodeEditor::resizeEvent(QResizeEvent *event){
    QPlainTextEdit::resizeEvent(event);
    const QRect contents = contentsRect();
    m_lineNumberArea->setGeometry(QRect(contents.left(), contents.top(), lineNumberAreaWidth(), contents.height()));
}

void CodeEditor::updateLineNumberAreaWidth(int){
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
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

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;
        selection.format.setBackground(palette().alternateBase().color().lighter(106));
        //selection.format.setBackground(QColor(0,0,0));
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        selections.append(selection);
    }

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
