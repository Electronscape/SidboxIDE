#include "codeeditor.h"

#include "csyntaxhighlighter.h"

#include <QAbstractItemView>
#include <QCompleter>
#include <QFile>
#include <QFocusEvent>
#include <QFont>
#include <QFontDatabase>
#include <QKeyEvent>
#include <QRegularExpression>
#include <QScrollBar>
#include <QStringListModel>
#include <QTextStream>

namespace {
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

    m_completer->setModel(m_completionModel);
    m_completer->setWidget(this);
    m_completer->setCaseSensitivity(Qt::CaseInsensitive);
    m_completer->setCompletionMode(QCompleter::PopupCompletion);
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

void CodeEditor::focusInEvent(QFocusEvent *event)
{
    if (m_completer) {
        m_completer->setWidget(this);
    }

    QPlainTextEdit::focusInEvent(event);
}

void CodeEditor::keyPressEvent(QKeyEvent *event)
{
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

    if (event->key() == Qt::Key_Tab && !m_argumentRanges.isEmpty()) {
        selectArgument(m_selectedArgument + 1);
        event->accept();
        return;
    }

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
    completionRect.setWidth(m_completer->popup()->sizeHintForColumn(0)
                            + m_completer->popup()->verticalScrollBar()->sizeHint().width());
    m_completer->complete(completionRect);
}

QString CodeEditor::textUnderCursor() const
{
    QTextCursor cursor = textCursor();
    cursor.select(QTextCursor::WordUnderCursor);
    return cursor.selectedText();
}

void CodeEditor::insertFunctionCompletion(const QString &signature)
{
    if (signature.isEmpty()) {
        return;
    }

    QTextCursor cursor = textCursor();
    cursor.select(QTextCursor::WordUnderCursor);

    const QString name = functionNameFromSignature(signature);
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
