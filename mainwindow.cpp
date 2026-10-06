#include "mainwindow.h"

#include "codeeditor.h"
#include "optionsdialog.h"
#include "projectsettingsdialog.h"
#include "ui_mainwindow.h"

#include <QSet>
#include <QAction>
#include <QApplication>
#include <QColor>
#include <QAbstractButton>
#include <QCoreApplication>
#include <QDir>
#include <QDirIterator>
#include <QDropEvent>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QFontDatabase>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QKeySequence>
#include <QLabel>
#include <QListWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QLineEdit>
#include <QLocale>
#include <QMenu>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QPoint>
#include <QProcess>
#include <QRegularExpression>
#include <QSaveFile>
#include <QSettings>
#include <QSplitter>
#include <QStatusBar>
#include <QTabWidget>
#include <QTextCharFormat>
#include <QTextBlock>
#include <QTextCursor>
#include <QTextDocument>
#include <QToolBar>
#include <QVBoxLayout>
#include <QStandardPaths>
#include <functional>

namespace {
constexpr int ProjectFileVersion = 2;
const QString GuiProjectType = QStringLiteral("gui");
const QString GameProjectType = QStringLiteral("game");


bool isCompilableSource(const QString &filePath)
{
    const QString suffix = QFileInfo(filePath).suffix().toLower();
    return suffix == QStringLiteral("c") || suffix == QStringLiteral("cc") || suffix == QStringLiteral("cpp");
}

bool isProjectExplorerSuffix(const QString &suffix)
{
    const QString lower = suffix.toLower();
    return lower == QStringLiteral("c") || lower == QStringLiteral("h")
        || lower == QStringLiteral("inc") || lower == QStringLiteral("txt")
        || lower == QStringLiteral("md");
}

QString formattedFileSize(qint64 bytes)
{
    if (bytes < 0) {
        return QStringLiteral("0 B");
    }
    if (bytes < 1024) {
        return QStringLiteral("%1 B").arg(QLocale().toString(bytes));
    }

    const double kib = bytes / 1024.0;
    if (kib < 1024.0) {
        return QStringLiteral("%1 KB").arg(QLocale().toString(kib, 'f', 1));
    }

    return QStringLiteral("%1 MB").arg(QLocale().toString(kib / 1024.0, 'f', 1));
}

/*
bool canContainFunctionSignatures(const QString &filePath)
{
    const QString suffix = QFileInfo(filePath).suffix().toLower();
    return suffix == QStringLiteral("c") || suffix == QStringLiteral("h")
        || suffix == QStringLiteral("cc") || suffix == QStringLiteral("cpp")
        || suffix == QStringLiteral("hpp");
}
*/

bool canContainFunctionSignatures(const QString &filePath)
{
    const QString suffix = QFileInfo(filePath).suffix().toLower();
    return !suffix.isEmpty();
}

QString normalizedProjectType(const QString &projectType)
{
    return projectType == GameProjectType ? GameProjectType : GuiProjectType;
}

QString projectTypeLabel(const QString &projectType)
{
    return normalizedProjectType(projectType) == GameProjectType
        ? QStringLiteral("Game")
        : QStringLiteral("GUI");
}

QString hexBytes(int kilobytes)
{
    return QStringLiteral("0x%1").arg(qMax(0, kilobytes) * 1024, 0, 16);
}

bool replaceLinkerAssignment(QString *text, const QString &symbol, const QString &value)
{
    const QRegularExpression expression(QStringLiteral("(^\\s*%1\\s*=\\s*)[^;]+(;)").arg(QRegularExpression::escape(symbol)),
        QRegularExpression::MultilineOption);
    const QRegularExpressionMatch match = expression.match(*text);
    if (!match.hasMatch()) {
        return false;
    }

    text->replace(expression, QStringLiteral("\\1%1\\2").arg(value));
    return true;
}

QStringList splitApiArgumentList(const QString &text)
{
    QStringList arguments;
    QString current;
    int depth = 0;
    for (const QChar ch : text) {
        if (ch == QLatin1Char('(') || ch == QLatin1Char('[')) {
            ++depth;
        } else if ((ch == QLatin1Char(')') || ch == QLatin1Char(']')) && depth > 0) {
            --depth;
        }
        if (ch == QLatin1Char(',') && depth == 0) {
            const QString argument = current.trimmed();
            if (!argument.isEmpty()) {
                arguments.append(argument);
            }
            current.clear();
            continue;
        }
        current.append(ch);
    }
    const QString argument = current.trimmed();
    if (!argument.isEmpty() && argument != QStringLiteral("void")) {
        arguments.append(argument);
    }
    return arguments;
}

QString readableApiArgumentName(const QString &rawArgument, int index)
{
    const QString argument = rawArgument.simplified();
    static const QRegularExpression functionPointerExpression(QStringLiteral("\\(\\s*\\*\\s*([A-Za-z_][A-Za-z0-9_]*)\\s*\\)"));
    const QRegularExpressionMatch functionPointerMatch = functionPointerExpression.match(argument);
    if (functionPointerMatch.hasMatch()) {
        return functionPointerMatch.captured(1);
    }

    static const QRegularExpression identifierExpression(QStringLiteral("([A-Za-z_][A-Za-z0-9_]*)\\s*(?:\\[[^\\]]*\\])?\\s*$"));
    const QRegularExpressionMatch match = identifierExpression.match(argument);
    if (!match.hasMatch()) {
        return QStringLiteral("arg%1").arg(index + 1);
    }

    const QString name = match.captured(1);
    if (name == QStringLiteral("const") || name == QStringLiteral("volatile") || name == QStringLiteral("restrict")) {
        return QStringLiteral("arg%1").arg(index + 1);
    }

    const bool showPointer = argument.contains(QLatin1Char('*'))
        && !argument.contains(QRegularExpression(QStringLiteral("\\bchar\\s*\\*")));
    return showPointer ? QStringLiteral("*%1").arg(name) : name;
}

QString readableApiArguments(const QString &argumentText)
{
    const QStringList arguments = splitApiArgumentList(argumentText);
    QStringList names;
    for (int i = 0; i < arguments.count(); ++i) {
        names.append(readableApiArgumentName(arguments.at(i), i));
    }
    return names.join(QStringLiteral(", "));
}

QString uncommentedApiText(QString text)
{
    text.replace(QRegularExpression(QStringLiteral("/\\*.*?\\*/"), QRegularExpression::DotMatchesEverythingOption), QStringLiteral(" "));
    text.replace(QRegularExpression(QStringLiteral("//[^\\n]*")), QString());
    return text;
}

void collectApiFunctionPointers(const QString &text, QHash<QString, QString> *functionPointers)
{
    static const QRegularExpression pointerExpression(
        QStringLiteral("(?:^|[\\n;{])\\s*[^;{}]*?\\(\\s*\\*\\s*([A-Za-z_][A-Za-z0-9_]*)\\s*\\)\\s*\\(([^;]*)\\)\\s*;"),
        QRegularExpression::MultilineOption);

    QRegularExpressionMatchIterator iterator = pointerExpression.globalMatch(text);
    while (iterator.hasNext()) {
        const QRegularExpressionMatch match = iterator.next();
        functionPointers->insert(match.captured(1).trimmed(), readableApiArguments(match.captured(2)));
    }
}

void collectApiMacros(QString text, const QHash<QString, QString> &functionPointers, QHash<QString, QString> *tips, QStringList *signatures)
{
    text.replace(QRegularExpression(QStringLiteral(R"(\\\s*\r?\n)")), QStringLiteral(" "));
    static const QRegularExpression macroExpression(
        QStringLiteral("^\\s*#\\s*define\\s+([A-Za-z_][A-Za-z0-9_]*)\\s*\\(([^)]*)\\)\\s*([^\\n]*)"),
        QRegularExpression::MultilineOption);
    static const QRegularExpression targetExpression(QStringLiteral("->\\s*([A-Za-z_][A-Za-z0-9_]*)\\s*\\("));

    QRegularExpressionMatchIterator iterator = macroExpression.globalMatch(text);
    while (iterator.hasNext()) {
        const QRegularExpressionMatch match = iterator.next();
        const QString name = match.captured(1).trimmed();
        const QString macroArguments = match.captured(2).trimmed();
        const QString body = match.captured(3);

        QString targetName;
        QRegularExpressionMatchIterator targetIterator = targetExpression.globalMatch(body);
        while (targetIterator.hasNext()) {
            targetName = targetIterator.next().captured(1).trimmed();
        }

        QString displayArguments;
        if (macroArguments == QStringLiteral("...") && !targetName.isEmpty() && functionPointers.contains(targetName)) {
            displayArguments = functionPointers.value(targetName);
        } else {
            QStringList arguments = splitApiArgumentList(macroArguments);
            arguments.removeAll(QStringLiteral("void"));
            displayArguments = arguments.join(QStringLiteral(", "));
        }

        const QString signature = QStringLiteral("%1(%2)").arg(name, displayArguments);
        tips->insert(name, signature);
        signatures->append(signature);
    }
}

QString trimmedApiValue(QString value)
{
    value = value.simplified();
    if (value.length() > 120) {
        value = value.left(117) + QStringLiteral("...");
    }
    return value;
}

void collectApiDefines(QString text, QHash<QString, QString> *tips, QStringList *signatures)
{
    text.replace(QRegularExpression(QStringLiteral(R"(\\\s*\r?\n)")), QStringLiteral(" "));
    static const QRegularExpression defineExpression(
        QStringLiteral("^\\s*#\\s*define\\s+([A-Za-z_][A-Za-z0-9_]*)([^\\n]*)"),
        QRegularExpression::MultilineOption);

    QRegularExpressionMatchIterator iterator = defineExpression.globalMatch(text);
    while (iterator.hasNext()) {
        const QRegularExpressionMatch match = iterator.next();
        const QString name = match.captured(1).trimmed();
        const QString rest = match.captured(2);
        if (name.isEmpty() || rest.startsWith(QLatin1Char('('))) {
            continue;
        }

        const QString value = trimmedApiValue(rest);
        if (value.isEmpty()) {
            continue;
        }
        tips->insert(name, QStringLiteral("#define %1 %2").arg(name, value));
        signatures->append(name);
    }
}

void collectApiTypes(const QString &text, QHash<QString, QString> *tips, QStringList *signatures)
{
    static const QRegularExpression callbackTypedefExpression(
        QStringLiteral("\\btypedef\\s+(.+?)\\(\\s*\\*\\s*([A-Za-z_][A-Za-z0-9_]*)\\s*\\)\\s*\\(([^;]*)\\)\\s*;"),
        QRegularExpression::MultilineOption);
    QRegularExpressionMatchIterator callbackIterator = callbackTypedefExpression.globalMatch(text);
    while (callbackIterator.hasNext()) {
        const QRegularExpressionMatch match = callbackIterator.next();
        const QString returnType = match.captured(1).simplified();
        const QString name = match.captured(2).trimmed();
        const QString arguments = match.captured(3).simplified();
        if (!name.isEmpty()) {
            tips->insert(name, QStringLiteral("typedef %1 (*%2)(%3)").arg(returnType, name, arguments));
            signatures->append(name);
        }
    }

    static const QRegularExpression compoundTypedefExpression(
        QStringLiteral("\\btypedef\\s+(struct|enum)\\s*([A-Za-z_][A-Za-z0-9_]*)?\\s*\\{.*?\\}\\s*([A-Za-z_][A-Za-z0-9_]*)\\s*;"),
        QRegularExpression::DotMatchesEverythingOption);
    QRegularExpressionMatchIterator compoundIterator = compoundTypedefExpression.globalMatch(text);
    while (compoundIterator.hasNext()) {
        const QRegularExpressionMatch match = compoundIterator.next();
        const QString kind = match.captured(1);
        const QString tagName = match.captured(2).trimmed();
        const QString aliasName = match.captured(3).trimmed();
        if (aliasName.isEmpty()) {
            continue;
        }

        const QString tip = tagName.isEmpty()
            ? QStringLiteral("typedef %1 { ... } %2").arg(kind, aliasName)
            : QStringLiteral("typedef %1 %2 { ... } %3").arg(kind, tagName, aliasName);
        tips->insert(aliasName, tip);
        signatures->append(aliasName);
        if (!tagName.isEmpty()) {
            tips->insert(tagName, tip);
            signatures->append(tagName);
        }
    }

    static const QRegularExpression simpleTypedefExpression(
        QStringLiteral("\\btypedef\\s+([^;{}()]+?)\\s+([A-Za-z_][A-Za-z0-9_]*)\\s*;"),
        QRegularExpression::MultilineOption);
    QRegularExpressionMatchIterator simpleIterator = simpleTypedefExpression.globalMatch(text);
    while (simpleIterator.hasNext()) {
        const QRegularExpressionMatch match = simpleIterator.next();
        const QString base = match.captured(1).simplified();
        const QString name = match.captured(2).trimmed();
        if (name.isEmpty() || base.startsWith(QStringLiteral("struct")) || base.startsWith(QStringLiteral("enum"))) {
            continue;
        }

        tips->insert(name, QStringLiteral("typedef %1 %2").arg(base, name));
        signatures->append(name);
    }

    static const QRegularExpression structExpression(
        QStringLiteral("\\b(struct|enum)\\s+([A-Za-z_][A-Za-z0-9_]*)\\s*\\{"),
        QRegularExpression::MultilineOption);
    QRegularExpressionMatchIterator structIterator = structExpression.globalMatch(text);
    while (structIterator.hasNext()) {
        const QRegularExpressionMatch match = structIterator.next();
        const QString kind = match.captured(1);
        const QString name = match.captured(2).trimmed();
        if (!name.isEmpty() && !tips->contains(name)) {
            tips->insert(name, QStringLiteral("%1 %2 { ... }").arg(kind, name));
            signatures->append(name);
        }
    }
}

bool isApiIdentifierChar(QChar ch)
{
    return ch.isLetterOrNumber() || ch == QLatin1Char('_');
}

void collectApiLineSymbols(QString text, QHash<QString, QString> *tips, QStringList *signatures)
{
    text.replace(QRegularExpression(QStringLiteral(R"(\\\s*\r?\n)")), QStringLiteral(" "));

    for (const QString &rawLine : text.split(QLatin1Char('\n'))) {
        const QString line = rawLine.trimmed();
        if (line.startsWith(QStringLiteral("#define "))) {
            const QString rest = line.mid(8).trimmed();
            int nameEnd = 0;
            while (nameEnd < rest.length() && isApiIdentifierChar(rest.at(nameEnd))) {
                ++nameEnd;
            }

            const QString name = rest.left(nameEnd);
            const QString value = trimmedApiValue(rest.mid(nameEnd));
            if (name.isEmpty() || value.isEmpty()) {
                continue;
            }

            if (value.startsWith(QLatin1Char('('))) {
                const int closeIndex = value.indexOf(QLatin1Char(')'));
                if (closeIndex > 0 && !tips->contains(name)) {
                    const QString arguments = value.mid(1, closeIndex - 1).trimmed();
                    const QString signature = QStringLiteral("%1(%2)").arg(name, arguments);
                    tips->insert(name, signature);
                    signatures->append(signature);
                }
            } else if (!tips->contains(name)) {
                tips->insert(name, QStringLiteral("#define %1 %2").arg(name, value));
                signatures->append(name);
            }
            continue;
        }

        if (line.startsWith(QStringLiteral("typedef ")) && line.endsWith(QLatin1Char(';'))
            && !line.contains(QLatin1Char('{')) && !line.contains(QLatin1Char('('))) {
            QString declaration = line;
            declaration.chop(1);
            const int lastSpace = declaration.lastIndexOf(QLatin1Char(' '));
            if (lastSpace <= 8) {
                continue;
            }

            const QString name = declaration.mid(lastSpace + 1).trimmed();
            const QString base = declaration.mid(8, lastSpace - 8).simplified();
            if (!name.isEmpty() && !base.isEmpty() && !tips->contains(name)) {
                tips->insert(name, QStringLiteral("typedef %1 %2").arg(base, name));
                signatures->append(name);
            }
        }
    }
}

class ProjectTreeWidget : public QTreeWidget
{
public:
    explicit ProjectTreeWidget(QWidget *parent = nullptr)
        : QTreeWidget(parent)
    {
        setDragEnabled(true);
        setAcceptDrops(true);
        viewport()->setAcceptDrops(true);
        setDropIndicatorShown(true);
        setDragDropMode(QAbstractItemView::DragDrop);
        setDefaultDropAction(Qt::MoveAction);
    }

    std::function<void(const QString &, const QString &)> fileMoveRequested;

protected:
    void startDrag(Qt::DropActions supportedActions) override
    {
        Q_UNUSED(supportedActions);

        QTreeWidgetItem *item = currentItem();
        if (!item) {
            return;
        }

        const bool isFolder = item->data(0, Qt::UserRole + 1).toBool();
        const QString filePath = item->data(0, Qt::UserRole).toString();

        /* Folder items are drop targets only; they can never be dragged. */
        if (isFolder || filePath.isEmpty()) {
            return;
        }

        m_draggedFilePath = QFileInfo(filePath).absoluteFilePath();
        QTreeWidget::startDrag(Qt::MoveAction);
        m_draggedFilePath.clear();
    }

    void dropEvent(QDropEvent *event) override
    {
        if (m_draggedFilePath.isEmpty() || !fileMoveRequested) {
            event->ignore();
            return;
        }

        QString targetDirectory;
        QTreeWidgetItem *targetItem = itemAt(event->position().toPoint());

        if (targetItem) {
            const QString targetPath = targetItem->data(0, Qt::UserRole).toString();
            const bool targetIsFolder = targetItem->data(0, Qt::UserRole + 1).toBool();

            if (!targetPath.isEmpty()) {
                targetDirectory = targetIsFolder
                    ? QFileInfo(targetPath).absoluteFilePath()
                    : QFileInfo(targetPath).absolutePath();
            }
        }

        /*
         * Do not let QTreeWidget perform a cosmetic internal move. MainWindow
         * moves the real file on disk and then rebuilds the tree instead.
         */
        fileMoveRequested(m_draggedFilePath, targetDirectory);
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }

private:
    QString m_draggedFilePath;
};


struct SourceNamedSymbol
{
    QString name;
    int line = -1;
};

struct SourceVariableSymbol
{
    QString name;
    int line = -1;
};

struct SourceFunctionSymbol
{
    QString signature;
    int line = -1;
    QList<SourceVariableSymbol> parameters;
    QList<SourceVariableSymbol> locals;
};

struct SourceSymbolTable
{
    QList<SourceNamedSymbol> defines;
    QList<SourceNamedSymbol> types;
    QList<SourceVariableSymbol> globals;
    QList<SourceFunctionSymbol> functions;
};

QString sanitizedCSource(const QString &source)
{
    QString result = source;
    bool inLineComment = false;
    bool inBlockComment = false;
    bool inString = false;
    bool inChar = false;
    bool escaped = false;

    for (int i = 0; i < source.size(); ++i) {
        const QChar ch = source.at(i);
        const QChar next = i + 1 < source.size() ? source.at(i + 1) : QChar();

        if (inLineComment) {
            if (ch == QLatin1Char('\n')) {
                inLineComment = false;
            } else {
                result[i] = QLatin1Char(' ');
            }
            continue;
        }

        if (inBlockComment) {
            if (ch == QLatin1Char('*') && next == QLatin1Char('/')) {
                result[i] = QLatin1Char(' ');
                if (i + 1 < result.size()) {
                    result[i + 1] = QLatin1Char(' ');
                }
                ++i;
                inBlockComment = false;
            } else if (ch != QLatin1Char('\n')) {
                result[i] = QLatin1Char(' ');
            }
            continue;
        }

        if (inString || inChar) {
            if (ch == QLatin1Char('\n')) {
                inString = false;
                inChar = false;
                escaped = false;
                continue;
            }

            result[i] = QLatin1Char(' ');
            if (escaped) {
                escaped = false;
                continue;
            }
            if (ch == QLatin1Char('\\')) {
                escaped = true;
                continue;
            }
            if ((inString && ch == QLatin1Char('"')) || (inChar && ch == QLatin1Char('\''))) {
                inString = false;
                inChar = false;
            }
            continue;
        }

        if (ch == QLatin1Char('/') && next == QLatin1Char('/')) {
            result[i] = QLatin1Char(' ');
            if (i + 1 < result.size()) {
                result[i + 1] = QLatin1Char(' ');
            }
            ++i;
            inLineComment = true;
            continue;
        }

        if (ch == QLatin1Char('/') && next == QLatin1Char('*')) {
            result[i] = QLatin1Char(' ');
            if (i + 1 < result.size()) {
                result[i + 1] = QLatin1Char(' ');
            }
            ++i;
            inBlockComment = true;
            continue;
        }

        if (ch == QLatin1Char('"')) {
            result[i] = QLatin1Char(' ');
            inString = true;
            escaped = false;
            continue;
        }

        if (ch == QLatin1Char('\'')) {
            result[i] = QLatin1Char(' ');
            inChar = true;
            escaped = false;
            continue;
        }
    }

    return result;
}

int sourceLineForOffset(const QString &source, int offset)
{
    if (offset <= 0) {
        return 0;
    }
    return source.left(qMin(offset, source.size())).count(QLatin1Char('\n'));
}

int matchingBracePosition(const QString &text, int openingBrace)
{
    int depth = 0;
    for (int i = openingBrace; i < text.size(); ++i) {
        if (text.at(i) == QLatin1Char('{')) {
            ++depth;
        } else if (text.at(i) == QLatin1Char('}')) {
            --depth;
            if (depth == 0) {
                return i;
            }
        }
    }
    return -1;
}

QString variableNameFromDeclarator(QString declarator)
{
    int nesting = 0;
    int equals = -1;
    for (int i = 0; i < declarator.size(); ++i) {
        const QChar ch = declarator.at(i);
        if (ch == QLatin1Char('(') || ch == QLatin1Char('[') || ch == QLatin1Char('{')) {
            ++nesting;
        } else if (ch == QLatin1Char(')') || ch == QLatin1Char(']') || ch == QLatin1Char('}')) {
            nesting = qMax(0, nesting - 1);
        } else if (ch == QLatin1Char('=') && nesting == 0) {
            equals = i;
            break;
        }
    }
    if (equals >= 0) {
        declarator = declarator.left(equals);
    }

    declarator.remove(QRegularExpression(QStringLiteral("\\[[^\\]]*\\]")));
    const QRegularExpression nameExpression(QStringLiteral("([A-Za-z_][A-Za-z0-9_]*)\\s*$"));
    const QRegularExpressionMatch match = nameExpression.match(declarator.trimmed());
    return match.hasMatch() ? match.captured(1) : QString();
}

QStringList splitTopLevelCommas(const QString &text)
{
    QStringList parts;
    QString current;
    int depth = 0;
    for (const QChar ch : text) {
        if (ch == QLatin1Char('(') || ch == QLatin1Char('[') || ch == QLatin1Char('{')) {
            ++depth;
        } else if (ch == QLatin1Char(')') || ch == QLatin1Char(']') || ch == QLatin1Char('}')) {
            depth = qMax(0, depth - 1);
        }

        if (ch == QLatin1Char(',') && depth == 0) {
            parts.append(current.trimmed());
            current.clear();
        } else {
            current.append(ch);
        }
    }
    if (!current.trimmed().isEmpty()) {
        parts.append(current.trimmed());
    }
    return parts;
}

QList<SourceVariableSymbol> variableSymbolsFromStatement(const QString &statement,
                                                          int statementOffset,
                                                          const QString &wholeSource)
{
    QList<SourceVariableSymbol> symbols;
    QString text = statement.trimmed();
    if (text.isEmpty() || text.startsWith(QLatin1Char('#')) || text.startsWith(QStringLiteral("typedef "))) {
        return symbols;
    }

    static const QStringList rejectedStarts = {
        QStringLiteral("return"), QStringLiteral("break"), QStringLiteral("continue"),
        QStringLiteral("goto"), QStringLiteral("case"), QStringLiteral("else"),
        QStringLiteral("if"), QStringLiteral("while"), QStringLiteral("switch"),
        QStringLiteral("do")
    };

    const QString firstWord = text.section(QRegularExpression(QStringLiteral("\\s+")), 0, 0);
    if (rejectedStarts.contains(firstWord)) {
        return symbols;
    }

    // A normal variable declaration needs something before its first declarator name
    // (the type/qualifiers). This filters assignments such as "x = 4".
    const QStringList declarators = splitTopLevelCommas(text);
    if (declarators.isEmpty()) {
        return symbols;
    }

    const QString firstName = variableNameFromDeclarator(declarators.first());
    if (firstName.isEmpty()) {
        return symbols;
    }

    QString firstBeforeInitializer = declarators.first();
    const int eq = firstBeforeInitializer.indexOf(QLatin1Char('='));
    if (eq >= 0) {
        firstBeforeInitializer = firstBeforeInitializer.left(eq);
    }
    const int firstNamePos = firstBeforeInitializer.lastIndexOf(QRegularExpression(
        QStringLiteral("\\b%1\\b").arg(QRegularExpression::escape(firstName))));
    if (firstNamePos <= 0 || firstBeforeInitializer.left(firstNamePos).trimmed().isEmpty()) {
        return symbols;
    }

    // Function calls/prototypes are not variables. Function-pointer declarations are
    // intentionally skipped by this light-weight browser rather than guessed wrongly.
    if (text.contains(QLatin1Char('(')) || text.contains(QLatin1Char(')'))) {
        return symbols;
    }

    const int line = sourceLineForOffset(wholeSource, statementOffset);
    for (const QString &declarator : declarators) {
        const QString name = variableNameFromDeclarator(declarator);
        if (!name.isEmpty()) {
            symbols.append({name, line});
        }
    }
    return symbols;
}

QList<SourceVariableSymbol> variableSymbolsInRange(const QString &sanitized,
                                                    const QString &wholeSource,
                                                    int start,
                                                    int end)
{
    QList<SourceVariableSymbol> symbols;
    if (start < 0 || end <= start || start >= sanitized.size()) {
        return symbols;
    }

    const int boundedEnd = qMin(end, sanitized.size());
    const QString region = sanitized.mid(start, boundedEnd - start);

    // Normal one-line declarations ending in ';'. This covers the style used by the
    // Sidbox sources while avoiding most expression statements.
    static const QRegularExpression declarationExpression(
        QStringLiteral("(?:^|[\\n{};])\\s*([^;{}\\n]+)\\s*;"),
        QRegularExpression::MultilineOption);

    QRegularExpressionMatchIterator iterator = declarationExpression.globalMatch(region);
    while (iterator.hasNext()) {
        const QRegularExpressionMatch match = iterator.next();
        const int offset = start + match.capturedStart(1);
        const auto found = variableSymbolsFromStatement(match.captured(1), offset, wholeSource);
        for (const SourceVariableSymbol &symbol : found) {
            bool duplicate = false;
            for (const SourceVariableSymbol &existing : symbols) {
                if (existing.name == symbol.name && existing.line == symbol.line) {
                    duplicate = true;
                    break;
                }
            }
            if (!duplicate) {
                symbols.append(symbol);
            }
        }
    }

    // Also pick up the common C99 form: for (int i = 0; ...)
    static const QRegularExpression forDeclarationExpression(
        QStringLiteral("\\bfor\\s*\\(\\s*([^;]+);"),
        QRegularExpression::MultilineOption);
    iterator = forDeclarationExpression.globalMatch(region);
    while (iterator.hasNext()) {
        const QRegularExpressionMatch match = iterator.next();
        const int offset = start + match.capturedStart(1);
        const auto found = variableSymbolsFromStatement(match.captured(1), offset, wholeSource);
        for (const SourceVariableSymbol &symbol : found) {
            bool duplicate = false;
            for (const SourceVariableSymbol &existing : symbols) {
                if (existing.name == symbol.name && existing.line == symbol.line) {
                    duplicate = true;
                    break;
                }
            }
            if (!duplicate) {
                symbols.append(symbol);
            }
        }
    }

    return symbols;
}

QList<SourceNamedSymbol> defineSymbolsFromSource(const QString &source)
{
    QList<SourceNamedSymbol> symbols;
    const QString sanitized = sanitizedCSource(source);

    static const QRegularExpression defineExpression(
        QStringLiteral(R"((?:^|\n)\s*#\s*define\s+([A-Za-z_][A-Za-z0-9_]*))"),
        QRegularExpression::MultilineOption);

    QRegularExpressionMatchIterator iterator = defineExpression.globalMatch(sanitized);
    while (iterator.hasNext()) {
        const QRegularExpressionMatch match = iterator.next();
        const QString name = match.captured(1).trimmed();
        if (name.isEmpty()) {
            continue;
        }

        const int line = sourceLineForOffset(source, match.capturedStart(1));
        symbols.append({name, line});
    }

    return symbols;
}

QList<SourceNamedSymbol> typeSymbolsFromSource(const QString &source)
{
    QList<SourceNamedSymbol> symbols;
    const QString sanitized = sanitizedCSource(source);

    auto appendUnique = [&symbols](const QString &name, int line) {
        if (name.isEmpty()) {
            return;
        }
        for (const SourceNamedSymbol &existing : std::as_const(symbols)) {
            if (existing.name == name && existing.line == line) {
                return;
            }
        }
        symbols.append({name, line});
    };

    /*
     * Parse typedefs by finding the terminating semicolon at top level rather
     * than with a single regex. A typedef struct contains member semicolons,
     * so a non-greedy regex stops at the first member (for example "int x;")
     * instead of reaching "} Vec3;".
     *
     * This also copes with attributes such as:
     *
     *   typedef struct __attribute__((packed, aligned(4))) {
     *       int16_t x;
     *   } Vec3;
     */
    static const QRegularExpression typedefStartExpression(
        QStringLiteral(R"(\btypedef\b)"));

    int searchFrom = 0;
    while (searchFrom < sanitized.size()) {
        const QRegularExpressionMatch startMatch = typedefStartExpression.match(sanitized, searchFrom);
        if (!startMatch.hasMatch()) {
            break;
        }

        const int typedefStart = startMatch.capturedStart(0);
        int braceDepth = 0;
        int parenDepth = 0;
        int bracketDepth = 0;
        int typedefEnd = -1;

        for (int i = startMatch.capturedEnd(0); i < sanitized.size(); ++i) {
            const QChar ch = sanitized.at(i);

            if (ch == QLatin1Char('{')) {
                ++braceDepth;
            } else if (ch == QLatin1Char('}')) {
                braceDepth = qMax(0, braceDepth - 1);
            } else if (ch == QLatin1Char('(')) {
                ++parenDepth;
            } else if (ch == QLatin1Char(')')) {
                parenDepth = qMax(0, parenDepth - 1);
            } else if (ch == QLatin1Char('[')) {
                ++bracketDepth;
            } else if (ch == QLatin1Char(']')) {
                bracketDepth = qMax(0, bracketDepth - 1);
            } else if (ch == QLatin1Char(';')
                       && braceDepth == 0
                       && parenDepth == 0
                       && bracketDepth == 0) {
                typedefEnd = i;
                break;
            }
        }

        if (typedefEnd < 0) {
            break;
        }

        const QString declaration = sanitized.mid(typedefStart, typedefEnd - typedefStart + 1);

        /*
         * The typedef name is the final identifier before the top-level ';'.
         * For a struct block this is the alias after '}', e.g. Vec3.
         * For an ordinary typedef it is likewise the final identifier.
         */
        static const QRegularExpression aliasExpression(
            QStringLiteral(R"(([A-Za-z_][A-Za-z0-9_]*)\s*;$)"));
        const QRegularExpressionMatch aliasMatch = aliasExpression.match(declaration);
        if (aliasMatch.hasMatch()) {
            const QString alias = aliasMatch.captured(1).trimmed();
            const int aliasOffset = typedefStart + aliasMatch.capturedStart(1);
            appendUnique(alias, sourceLineForOffset(source, aliasOffset));
        }

        searchFrom = typedefEnd + 1;
    }

    // Named struct/enum/union declarations are useful even when they are not typedefs.
    // Allow attributes/qualifiers between the tag name and the opening brace.
    static const QRegularExpression taggedTypeExpression(
        QStringLiteral(
            R"(\b(struct|enum|union)\s+([A-Za-z_][A-Za-z0-9_]*)\s*(?:__attribute__\s*\(\([^\n]*?\)\)\s*)?(?=\{|;))"),
        QRegularExpression::MultilineOption);

    QRegularExpressionMatchIterator taggedIterator = taggedTypeExpression.globalMatch(sanitized);
    while (taggedIterator.hasNext()) {
        const QRegularExpressionMatch match = taggedIterator.next();
        const QString name = match.captured(2).trimmed();
        appendUnique(name, sourceLineForOffset(source, match.capturedStart(2)));
    }

    return symbols;
}

SourceSymbolTable parseSourceSymbols(const QString &source)
{
    SourceSymbolTable table;
    table.defines = defineSymbolsFromSource(source);
    table.types = typeSymbolsFromSource(source);
    const QString sanitized = sanitizedCSource(source);
    QString globalsOnly = sanitized;

    static const QRegularExpression functionExpression(
        QStringLiteral(
            "(?:^|\\n)\\s*"
            "((?:(?:static|inline|extern|const|volatile|unsigned|signed|long|short|struct\\s+[A-Za-z_][A-Za-z0-9_]*|enum\\s+[A-Za-z_][A-Za-z0-9_]*|union\\s+[A-Za-z_][A-Za-z0-9_]*|[A-Za-z_][A-Za-z0-9_]*)\\s+|[*]+\\s*)+)"
            "([A-Za-z_][A-Za-z0-9_]*)\\s*"
            "\\(([^;{}]*)\\)\\s*\\{"),
        QRegularExpression::MultilineOption);

    QRegularExpressionMatchIterator iterator = functionExpression.globalMatch(sanitized);
    while (iterator.hasNext()) {
        const QRegularExpressionMatch match = iterator.next();
        const QString functionName = match.captured(2).trimmed();

        static const QStringList ignoredFunctionNames = {
            QStringLiteral("__attribute__"),
            QStringLiteral("__declspec")
        };
        if (functionName.isEmpty()
            || ignoredFunctionNames.contains(functionName)) {
            continue;
        }

        const int openingBrace = match.capturedEnd(0) - 1;
        const int closingBrace = matchingBracePosition(sanitized, openingBrace);
        if (closingBrace < 0) {
            continue;
        }

        SourceFunctionSymbol function;
        const QString arguments = match.captured(3).simplified();
        function.signature = QStringLiteral("%1(%2)").arg(functionName, arguments);
        function.line = sourceLineForOffset(source, match.capturedStart(2));

        const QStringList parameterParts = splitApiArgumentList(match.captured(3));
        for (const QString &parameter : parameterParts) {
            const QString name = readableApiArgumentName(parameter, function.parameters.size());
            QString cleanName = name;
            cleanName.remove(QLatin1Char('*'));
            cleanName = cleanName.trimmed();
            if (!cleanName.isEmpty()) {
                function.parameters.append({cleanName, function.line});
            }
        }

        function.locals = variableSymbolsInRange(sanitized, source, openingBrace + 1, closingBrace);
        table.functions.append(function);

        // Remove the whole function body from the copy used for global-variable parsing,
        // but preserve newlines so source line numbers stay exact.
        for (int i = match.capturedStart(0); i <= closingBrace && i < globalsOnly.size(); ++i) {
            if (globalsOnly.at(i) != QLatin1Char('\n')) {
                globalsOnly[i] = QLatin1Char(' ');
            }
        }
    }

    table.globals = variableSymbolsInRange(globalsOnly, source, 0, globalsOnly.size());
    return table;
}

class CompilerOutputPane : public QPlainTextEdit
{
public:
    explicit CompilerOutputPane(QWidget *parent = nullptr)
        : QPlainTextEdit(parent)
    {
    }

protected:
    void mousePressEvent(QMouseEvent *event) override
    {
        m_pressedInsideSelection = false;
        if (event->button() == Qt::LeftButton) {
            const QTextCursor cursor = textCursor();
            if (cursor.hasSelection()) {
                const int position = cursorForPosition(event->pos()).position();
                m_pressedInsideSelection = position >= cursor.selectionStart()
                    && position < cursor.selectionEnd();
            }
        }

        QPlainTextEdit::mousePressEvent(event);
    }

    void mouseMoveEvent(QMouseEvent *event) override
    {
        if (m_pressedInsideSelection && (event->buttons() & Qt::LeftButton)) {
            event->accept();
            return;
        }

        QPlainTextEdit::mouseMoveEvent(event);
    }

    void mouseReleaseEvent(QMouseEvent *event) override
    {
        QPlainTextEdit::mouseReleaseEvent(event);
        m_pressedInsideSelection = false;
    }

private:
    bool m_pressedInsideSelection = false;
};
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_projectFiles(nullptr)
    , m_editorTabs(nullptr)
    , m_quickTipLabel(nullptr)
    , m_outputPane(nullptr)
    , m_outputToolBar(nullptr)
    , m_compilerProcess(new QProcess(this))
    , m_buildStep(BuildStep::None)
    , m_projectType(GuiProjectType)
    , m_modSizeKb(0)
    , m_editorFontPointSize(10)
{
    ui->setupUi(this);
    loadOptions();
    setupInterface();
    refreshApiCatalog();




    connect(m_compilerProcess, &QProcess::readyReadStandardOutput, this, [this]() {
        appendOutputText(QString::fromLocal8Bit(m_compilerProcess->readAllStandardOutput()), OutputKind::Normal);
    });
    connect(m_compilerProcess, &QProcess::readyReadStandardError, this, [this]() {
        appendOutputText(QString::fromLocal8Bit(m_compilerProcess->readAllStandardError()), OutputKind::Error);
    });
    connect(m_compilerProcess, &QProcess::errorOccurred, this, [this](QProcess::ProcessError) {
        const QString toolName = m_buildStep == BuildStep::Objcopy ? tr("objcopy") : tr("compiler");
        appendOutputLine(tr("Could not start %1. Check that the IDE's bundled toolchain exists.").arg(toolName), OutputKind::Error);
        m_buildStep = BuildStep::None;
        statusBar()->showMessage(tr("Compile failed"));
    });
    connect(m_compilerProcess, &QProcess::finished, this, &MainWindow::handleCompilerFinished);

    createNewSourceFile();
    createNewHeaderFile();

    AutoSelectMainC();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AutoSelectMainC(){
    for (int i = 0; i < m_editorTabs->count(); ++i) {
        if (m_editorTabs->tabText(i) == "main.c" || m_editorTabs->tabText(i) == "untitled.c") { // Or tabToolTip(i) / filename check
            m_editorTabs->setCurrentIndex(i);
            break;
        }
    }
}

void MainWindow::setupInterface()
{
    setWindowTitle(tr("Sidbox IDE"));
    QIcon icon = QApplication::windowIcon().isNull() ? QIcon(":/icons/icon.png") : QApplication::windowIcon();
    setWindowIcon(icon);
    //resize(1600, 880);
    //maximumSize();
    showMaximized();


    setStyleSheet(R"(
        QMainWindow {
            background-color: #101010;
            color: #ffffff;
        }

        QWidget {
            background-color: #101010;
            color: #d8d8d8;
        }

        QLabel {
            background-color: #101010;
            color: #ffffff;
            border: none;
        }

        QToolBar {
            background-color: #101010;
            border: none;
            spacing: 1px;
            padding: 1px;
        }

        QToolButton {
            background-color: #101010;
            color: #ffffff;
            border: none;
            border-radius: 0px;
            padding: 3px;
        }

        QToolButton:hover {
            background-color: #202020;
        }

        QToolButton:pressed {
            background-color: #2858A8;
        }

        QPushButton {
            background-color: #101010;
            color: #dddddd;
            border: 1px solid #303030;
            border-radius: 0px;
            padding: 4px 8px;
        }

        QPushButton:hover {
            background-color: #202020;
            border: 1px solid #506090;
        }

        QPushButton:pressed {
            background-color: #2858A8;
            color: #ffffff;
        }

        QTreeWidget {
            background-color: #050505;
            color: #dddddd;
            border: 1px solid #202840;
            border-radius: 0px;
            alternate-background-color: #0b0b0b;
        }

        QTreeWidget::item {
            border-radius: 0px;
            padding: 1px;
        }

        QTreeWidget::item:selected {
            background-color: #2858A8;
            color: #ffffff;
        }

        QTreeWidget::item:hover {
            background-color: #161616;
        }

        QTabWidget::pane {
            background-color: #101010;
            border: 1px solid #202840;
            border-radius: 0px;
        }

        QTabBar::tab {
            background-color: #101010;
            color: #aaaaaa;
            border: 1px solid #282828;
            border-bottom: none;
            border-radius: 0px;
            padding: 5px 10px;
        }

        QTabBar::tab:selected {
            background-color: #2858A8;
            color: #ffffff;
        }

        QTabBar::tab:hover:!selected {
            background-color: #202020;
        }

        QStatusBar {
            background-color: #101010;
            color: #b0b0b0;
            border-top: 1px solid #202020;
        }

        QSplitter::handle {
            background-color: #202020;
        }

        QSplitter::handle:hover {
            background-color: #2858A8;
        }

        QMenu {
            background-color: #080808;
            color: #dddddd;
            border: 1px solid #303030;
        }

        QMenu::item {
            padding: 5px 24px 5px 8px;
        }

        QMenu::item:selected {
            background-color: #2858A8;
            color: #ffffff;
        }

        QScrollBar:vertical {
            background: #080808;
            width: 12px;
            margin: 0px;
        }

        QScrollBar::handle:vertical {
            background: #303030;
            min-height: 20px;
            border-radius: 0px;
        }

        QScrollBar::handle:vertical:hover {
            background: #505050;
        }

        QScrollBar:add-line:vertical,
        QScrollBar:sub-line:vertical {
            height: 0px;
        }

        QScrollBar:horizontal {
            background: #080808;
            height: 12px;
            margin: 0px;
        }

        QScrollBar::handle:horizontal {
            background: #303030;
            min-width: 20px;
            border-radius: 0px;
        }

        QScrollBar::handle:horizontal:hover {
            background: #505050;
        }

        QScrollBar:add-line:horizontal,
        QScrollBar:sub-line:horizontal {
            width: 0px;
        }

        QLineEdit,
        QPlainTextEdit {
            background-color: #050505;
            color: #dddddd;
            border: 1px solid #303030;
            border-radius: 0px;
            selection-background-color: #2858A8;
            selection-color: #ffffff;
        }

        QToolTip {
            background-color: #101010;
            color: #ffffff;
            border: 1px solid #505050;
        }
    )");


    auto *toolBar = addToolBar(tr("Project"));
    toolBar->setMovable(false);
    toolBar->setIconSize(QSize(32, 32));
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);    //
/*
    toolBar->setStyleSheet(R"(
        QToolBar {
            background-color: #000000;
            spacing: 1px;
            padding: 1px;
            margin: 0px;
            border: none;
        }
        QToolButton {
            background-color: #000000;
            color: #FF9A00;
            padding: 2px;
            margin: 0px;
            border: none;
            border-radius: 0px;
        }
        QToolButton:hover {
            background-color: rgba(255, 255, 255, 25);
            border-radius: 0px;
        }
        QToolButton:pressed {
            background-color: rgba(255, 255, 255, 40);
        }
         QToolBar::separator {
                background: #333333;
                width: 1px;
                margin: 4px;
            }
    )");
*/
    QAction *newAction = toolBar->addAction(QIcon(":/icons/new_project.png"), tr("|   New   |"));
    auto *newMenu = new QMenu(this);
    QAction *newProjectAction = newMenu->addAction(tr("New Project"));
    //QAction *newSourceAction = newMenu->addAction(tr("New C Source File"));
    //QAction *newHeaderAction = newMenu->addAction(tr("New H Header File"));
    newAction->setMenu(newMenu);

    QAction *openProjectAction = toolBar->addAction(QIcon(":/icons/open_project.png"), tr("Open Project..."));
    QAction *saveProjectAction = toolBar->addAction(QIcon(":/icons/save_project.png"), tr("Save Project..."));
    QAction *projectSettingsAction = toolBar->addAction(QIcon(":/icons/project_settings.png"), tr("Project Settings"));
    QAction *optionsAction = toolBar->addAction(QIcon(":/icons/options.png"), tr("Options"));
    toolBar->addSeparator();
    QAction *compileAction = toolBar->addAction(QIcon(":/icons/compile.png"), tr("Compile [F5]"));



    newAction->setShortcut(QKeySequence::New);
    openProjectAction->setShortcut(QKeySequence::Open);
    saveProjectAction->setShortcut(QKeySequence::Save);
    compileAction->setShortcut(Qt::Key_F5);

    connect(newAction, &QAction::triggered, this, [toolBar, newAction, newMenu]() {
        if (QWidget *button = toolBar->widgetForAction(newAction)) {
            newMenu->popup(button->mapToGlobal(QPoint(0, button->height())));
        }
    });
    connect(newProjectAction, &QAction::triggered, this, &MainWindow::createNewProject);
    //connect(newSourceAction, &QAction::triggered, this, &MainWindow::createNewSourceFile);
    //connect(newHeaderAction, &QAction::triggered, this, &MainWindow::createNewHeaderFile);
    connect(openProjectAction, &QAction::triggered, this, &MainWindow::openProject);
    connect(saveProjectAction, &QAction::triggered, this, &MainWindow::saveProject);
    connect(projectSettingsAction, &QAction::triggered, this, &MainWindow::showProjectSettings);
    connect(optionsAction, &QAction::triggered, this, &MainWindow::showOptions);
    connect(compileAction, &QAction::triggered, this, &MainWindow::compileActiveFile);

    auto *mainSplitter = new QSplitter(Qt::Horizontal, this);



    // --- Left Project Panel ---
    auto *projectPane = new QWidget(mainSplitter);
    projectPane->setMinimumWidth(300); // Prevents resizing the left panel smaller than 300px

    auto *projectLayout = new QVBoxLayout(projectPane);
    projectLayout->setContentsMargins(8, 8, 8, 8);
    projectLayout->setSpacing(6);

    auto *projectLabel = new QLabel(tr("Files in Project"), projectPane);

    auto *projectTree = new ProjectTreeWidget(projectPane);
    m_projectFiles = projectTree;
    m_projectFiles->setHeaderHidden(true);
    m_projectFiles->setRootIsDecorated(true);
    m_projectFiles->setItemsExpandable(true);
    m_projectFiles->setAnimated(false);

    projectTree->fileMoveRequested = [this](const QString &sourceFilePath, const QString &targetDirectory) {
        moveProjectFile(sourceFilePath, targetDirectory);
    };

    m_projectFiles->setStyleSheet(QStringLiteral(
        "QTreeWidget {"
        "   border: 1px solid #102048;"
        "   border-radius: 0px;"
        "}"
        "QTreeWidget::item {"
        "   border-radius: 0px;"
        "}"
        "QTreeWidget::item:selected {"
        "   background-color: #2858A8;"
        "   color: #ffffff;"
        "}"
        "QTreeWidget::item:selected:hover {"
        "   border: 1px solid #6C80AA;"
        "   background-color: #2858A8;"
        "}"
        ));

    m_projectFiles->setContextMenuPolicy(Qt::CustomContextMenu);
    auto *projectButtonLayout = new QHBoxLayout();
    projectButtonLayout->setContentsMargins(0, 0, 0, 0);
    projectButtonLayout->setSpacing(4);
    auto *addFileButton = new QPushButton(tr("Add"), projectPane);
    auto *createFileButton = new QPushButton(tr("Create"), projectPane);
    auto *removeFileButton = new QPushButton(tr("Remove"), projectPane);
    projectButtonLayout->addWidget(addFileButton);
    projectButtonLayout->addWidget(createFileButton);
    projectButtonLayout->addWidget(removeFileButton);

    auto *renameFileAction = new QAction(tr("Rename"), m_projectFiles);
    renameFileAction->setShortcut(Qt::Key_F2);
    renameFileAction->setShortcutContext(Qt::WidgetWithChildrenShortcut);
    m_projectFiles->addAction(renameFileAction);
    m_projectFiles->setAlternatingRowColors(true);
    projectLayout->addWidget(projectLabel);
    projectLayout->addLayout(projectButtonLayout);
    projectLayout->addWidget(m_projectFiles, 1);

    connect(m_projectFiles, &QTreeWidget::itemDoubleClicked, this, &MainWindow::openProjectFile);
    connect(m_projectFiles, &QTreeWidget::itemActivated, this, &MainWindow::openProjectFile);
    connect(addFileButton, &QPushButton::clicked, this, &MainWindow::addExistingProjectFile);
    connect(createFileButton, &QPushButton::clicked, this, &MainWindow::createProjectFile);
    connect(removeFileButton, &QPushButton::clicked, this, &MainWindow::removeSelectedProjectFile);
    connect(renameFileAction, &QAction::triggered, this, &MainWindow::renameSelectedProjectFile);
    connect(m_projectFiles, &QTreeWidget::customContextMenuRequested, this, [this](const QPoint &pos) {
        QTreeWidgetItem *item = m_projectFiles->itemAt(pos);

        if (item) {
            m_projectFiles->setCurrentItem(item);
        } else {
            m_projectFiles->clearSelection();
        }

        const QString targetDirectory = projectContextDirectory(item);

        QMenu menu(this);

        menu.addAction(tr("Create File"), this, [this, targetDirectory]() {
            createProjectFileInDirectory(targetDirectory);
        });

        menu.addAction(tr("Create Folder"), this, [this, targetDirectory]() {
            createProjectFolderInDirectory(targetDirectory);
        });

        menu.addAction(tr("Add File"), this, &MainWindow::addExistingProjectFile);

        /*
         * Rename / Remove currently apply to files only.
         * Folder rename/delete can be added separately later.
         */
        if (item && !item->data(0, Qt::UserRole + 1).toBool()) {
            menu.addSeparator();
            menu.addAction(tr("Rename"), this, &MainWindow::renameSelectedProjectFile);
            menu.addAction(tr("Remove"), this, &MainWindow::removeSelectedProjectFile);
        }

        menu.exec(m_projectFiles->viewport()->mapToGlobal(pos));
    });

    // --- Center Work Area ---
    auto *workAreaSplitter = new QSplitter(Qt::Vertical, mainSplitter);
    m_editorTabs = new QTabWidget(workAreaSplitter);
    m_editorTabs->setDocumentMode(true);
    m_editorTabs->setTabsClosable(true);
    m_editorTabs->setMovable(true);
    m_editorTabs->setStyleSheet(R"(
        QTabWidget::pane {
            border: 1px solid #102048;
            border-radius: 0px;
        }
        QTabBar::tab {
            background: #1a1a2e;
            color: #c0c0c0;
            border: 1px solid #102048;
            border-bottom: none;
            border-radius: 0px;
            padding: 6px 12px;
            margin-right: -6px;
        }
        QTabBar::tab:selected {
            background: #2858A8;
            color: #ffffff;
            border-radius: 0px;
        }
        QTabBar::tab:hover:!selected {
            background: #2a2a4a;
            border-radius: 0px;
        }
        QTabBar::close-button {
                image: url(:/icons/close_tab.png);   /* optional – only if you have a custom icon */
                border-radius: 0px;
                subcontrol-position: right;
                subcontrol-origin: padding;
                width: 14px;
                height: 14px;
                background: transparent;
            }
            QTabBar::close-button:hover {
                background: #ff5555;
                border-radius: 0px;
            }
    )");

    connect(m_editorTabs, &QTabWidget::tabCloseRequested, this, [this](int index) {
        QWidget *widget = m_editorTabs->widget(index);
        auto *editor = qobject_cast<QPlainTextEdit *>(widget);
        if (editor && editor->document()->isModified())
        {
            QMessageBox::StandardButton reply = QMessageBox::question(
                this,
                tr("Unsaved Changes"),
                tr("You're about to close an unsaved tab, proceed?"),
                QMessageBox::Yes | QMessageBox::No,
                QMessageBox::No);

            if (reply != QMessageBox::Yes) {
                return;
            }
        }



        m_editorTabs->removeTab(index);
        widget->deleteLater();
        refreshFunctionCompletions();
    });

    // --- Right Panel (Functions/Variables) ---
    auto *rightPane = new QWidget(mainSplitter);
    rightPane->setMinimumWidth(300);

    auto *rightLayout = new QVBoxLayout(rightPane);
    rightLayout->setContentsMargins(8, 8, 8, 8);
    rightLayout->setSpacing(6);

    auto *functionLabel = new QLabel(tr("Functions & Variables"), rightPane);
    m_functionvarList = new QTreeWidget(rightPane);
    m_functionvarList->setHeaderHidden(true);
    m_functionvarList->setRootIsDecorated(true);
    m_functionvarList->setItemsExpandable(true);
    m_functionvarList->setExpandsOnDoubleClick(false);
    m_functionvarList->setAnimated(false);
    m_functionvarList->setStyleSheet(QStringLiteral(
        "QTreeWidget {"
        "   border: 1px solid #102048;"
        "   border-radius: 0px;"
        "}"
        "QTreeWidget::item {"
        "   border-radius: 0px;"
        "}"
        "QTreeWidget::item:selected {"
        "   background-color: #2858A8;"
        "   color: #ffffff;"
        "}"
        "QTreeWidget::item:selected:hover {"
        "   border: 1px solid #6C80AA;"
        "   background-color: #2858A8;"
        "}"
        ));

    connect(m_editorTabs, &QTabWidget::currentChanged, this, [this](int) {
        refreshSymbolTree();
    });
    connect(m_functionvarList, &QTreeWidget::itemDoubleClicked,
            this, &MainWindow::jumpToSymbol);

    rightLayout->addWidget(functionLabel);
    rightLayout->addWidget(m_functionvarList, 1);

    // --- Bottom Output Panel ---
    auto *outputPanel = new QWidget(workAreaSplitter);
    auto *outputLayout = new QVBoxLayout(outputPanel);
    outputLayout->setContentsMargins(0, 0, 0, 0);
    outputLayout->setSpacing(0);

    m_quickTipLabel = new QLabel(tr("F1: quick API tip"), outputPanel);
    m_quickTipLabel->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));
    m_quickTipLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    m_quickTipLabel->setStyleSheet(QStringLiteral(
        "QLabel { background: #020402; color: #66ff8a; border-top: 1px solid #15351a; "
        "border-bottom: 1px solid #15351a; padding: 3px 6px; }"));

    m_outputToolBar = new QToolBar(tr("Compiler Output"), outputPanel);
    m_outputToolBar->setMovable(false);
    QAction *clearOutputAction = m_outputToolBar->addAction(tr("Clear"));
    connect(clearOutputAction, &QAction::triggered, this, [this]() {
        m_outputPane->clear();
    });

    m_outputPane = new CompilerOutputPane(outputPanel);
    m_outputPane->setReadOnly(true);
    m_outputPane->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
    m_outputPane->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));
    m_outputPane->setStyleSheet(QStringLiteral(
        "QPlainTextEdit { background: #000000; color: #d8e8d0; "
        "selection-background-color: #265c32; selection-color: #ffffff; }"));
    m_outputPane->setAcceptDrops(false);
    m_outputPane->viewport()->setAcceptDrops(false);
    m_outputPane->setPlaceholderText(tr("Compiler output"));
    m_outputPane->setMaximumBlockCount(1000);

    outputLayout->addWidget(m_quickTipLabel);
    outputLayout->addWidget(m_outputToolBar);
    outputLayout->addWidget(m_outputPane, 1);

    workAreaSplitter->addWidget(m_editorTabs);
    workAreaSplitter->addWidget(outputPanel);
    workAreaSplitter->setStretchFactor(0, 4);
    workAreaSplitter->setStretchFactor(1, 1);

    // Assembly of main horizontal splitter
    mainSplitter->addWidget(projectPane);
    mainSplitter->addWidget(workAreaSplitter);
    mainSplitter->addWidget(rightPane);

    mainSplitter->setStretchFactor(0, 1);
    mainSplitter->setStretchFactor(1, 5);
    mainSplitter->setStretchFactor(2, 1);
    mainSplitter->setSizes({300, 1200, 300});



    setCentralWidget(mainSplitter);
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::createNewProject()
{
    if (!saveModifiedWorkBeforeNewProject()) {
        statusBar()->showMessage(tr("New project cancelled"));
        return;
    }

    QString projectFilePath = QFileDialog::getSaveFileName(
        this,
        tr("New Project"),
        QDir::home().filePath(QStringLiteral("project.proj")),
        tr("Sidbox projects (*.proj);;All files (*)"));

    if (projectFilePath.isEmpty()) {
        statusBar()->showMessage(tr("New project cancelled"));
        return;
    }

    if (QFileInfo(projectFilePath).suffix().isEmpty()) {
        projectFilePath.append(QStringLiteral(".proj"));
    }

    QMessageBox typeBox(this);
    typeBox.setWindowTitle(tr("Project Type"));
    typeBox.setText(tr("What type of Sidbox project is this?"));
    QPushButton *guiButton = typeBox.addButton(tr("GUI"), QMessageBox::AcceptRole);
    QPushButton *gameButton = typeBox.addButton(tr("Game"), QMessageBox::AcceptRole);
    typeBox.addButton(QMessageBox::Cancel);
    //typeBox.exec();

    //if (typeBox.clickedButton() == nullptr || typeBox.standardButton(typeBox.clickedButton()) == QMessageBox::Cancel) {
    //if (typeBox.standardButton(typeBox.clickedButton()) == QMessageBox::Cancel) {
    if (typeBox.exec() == QMessageBox::Cancel || !typeBox.clickedButton()) {
        statusBar()->showMessage(tr("New project cancelled"));
        return;
    }


    m_projectType = typeBox.clickedButton() == static_cast<QAbstractButton *>(gameButton) ? GameProjectType : GuiProjectType;
    Q_UNUSED(guiButton);
    m_modSizeKb = 0;
    m_linkerScriptPath.clear();
    m_projectFilePath = QFileInfo(projectFilePath).absoluteFilePath();
    m_projectPath = QFileInfo(m_projectFilePath).absolutePath();
    m_projectFilesInProject.clear();

    clearEditorTabs();
    refreshProjectFiles();
    createNewSourceFile();
    createNewHeaderFile();
    saveProjectFile(m_projectFilePath);

    statusBar()->showMessage(tr("New %1 project created: %2")
        .arg(projectTypeLabel(m_projectType), QDir::toNativeSeparators(m_projectFilePath)));


    AutoSelectMainC();
}


void MainWindow::createNewSourceFile()
{
    CodeEditor *editor = createEditor();

    const QDateTime now = QDateTime::currentDateTime();
    const QString dateStr = now.toString(QStringLiteral("MMM dd yyyy"));
    const QString timeStr = now.toString(QStringLiteral("hh:mm:ss"));

    editor->setPlainText(QString(
                             "/*\n"
                             "   Created file: %1 %2\n"
                             "*/\n"
                             "#include \"apis.h\"\n\n"
                             "int main(void)\n"
                             "{\n"
                             "    printf(\"Hello world\");\n"
                             "    return 0;\n"
                             "}\n").arg(timeStr, dateStr));

    editor->document()->setModified(false);

    const int index = m_editorTabs->addTab(editor, tabTitleForEditor(editor, 0));
    m_editorTabs->setCurrentIndex(index);
    refreshFunctionCompletions();
    statusBar()->showMessage(tr("New C source file created"));
}

void MainWindow::createNewHeaderFile(){
    CodeEditor *editor = createEditor();

    const QDateTime now = QDateTime::currentDateTime();
    const QString dateStr = now.toString(QStringLiteral("MMM dd yyyy"));
    const QString timeStr = now.toString(QStringLiteral("hh:mm:ss"));

    editor->setPlainText(QString(
                             "/*\n"
                             "   Created Header file: %1 %2\n"
                             "*/\n"
                             "\n").arg(timeStr, dateStr));

    editor->document()->setModified(false);

    const int index = m_editorTabs->addTab(editor, tabTitleForEditor(editor, 1));
    m_editorTabs->setCurrentIndex(index);
    refreshFunctionCompletions();
    statusBar()->showMessage(tr("New H header file created"));
}

void MainWindow::openProject()
{
    const QString projectFilePath = QFileDialog::getOpenFileName(
        this,
        tr("Open Project"),
        m_projectPath.isEmpty() ? QDir::homePath() : m_projectPath,
        tr("Sidbox projects (*.proj);;All files (*)"));

    if (projectFilePath.isEmpty()) {
        return;
    }

    if (loadProjectFile(projectFilePath)) {
        statusBar()->showMessage(tr("Project opened: %1").arg(QDir::toNativeSeparators(m_projectFilePath)));
    }

    AutoSelectMainC();
}

bool MainWindow::saveProject()
{
    bool allSaved = true;

    for (int i = 0; i < m_editorTabs->count(); ++i) {
        auto *editor = qobject_cast<CodeEditor *>(m_editorTabs->widget(i));
        if (!editor) {
            continue;
        }

        // Skip untitled/unsaved tabs so QFileDialog isn't popped up for each one
        if (editor->filePath().isEmpty()) {
            continue;
        }

        allSaved = saveEditor(editor) && allSaved;
    }

    if (!allSaved) {
        statusBar()->showMessage(tr("Project save cancelled"));
        return false;
    }

    QString projectFilePath = m_projectFilePath;
    if (projectFilePath.isEmpty()) {
        projectFilePath = QFileDialog::getSaveFileName(
            this,
            tr("Save Project"),
            QDir(m_projectPath.isEmpty() ? QDir::homePath() : m_projectPath).filePath(QStringLiteral("project.proj")),
            tr("Sidbox projects (*.proj);;All files (*)"));

        if (projectFilePath.isEmpty()) {
            statusBar()->showMessage(tr("Project save cancelled"));
            return false;
        }

        if (QFileInfo(projectFilePath).suffix().isEmpty()) {
            projectFilePath.append(QStringLiteral(".proj"));
        }
    }

    if (saveProjectFile(projectFilePath)) {
        refreshProjectFiles();
        statusBar()->showMessage(tr("Project saved: %1").arg(QDir::toNativeSeparators(m_projectFilePath)));
        return true;
    }

    return false;
}

void MainWindow::showOptions()
{
    OptionsDialog dialog(this);
    dialog.setEditorFontPointSize(m_editorFontPointSize);

    if (dialog.exec() != QDialog::Accepted) {
        return;
    }

    m_editorFontPointSize = dialog.editorFontPointSize();
    saveOptions();
    applyEditorFont();

    statusBar()->showMessage(tr("Options saved"));
}

void MainWindow::showProjectSettings()
{
    ProjectSettingsDialog dialog(this);
    dialog.setProjectType(m_projectType);
    dialog.setModSizeKb(m_modSizeKb);
    dialog.setCustomLinkerScriptPath(m_linkerScriptPath);
    dialog.setDefaultLinkerScriptPaths(defaultLinkerScriptPath(GuiProjectType), defaultLinkerScriptPath(GameProjectType));

    if (dialog.exec() != QDialog::Accepted) {
        return;
    }

    m_projectType = normalizedProjectType(dialog.projectType());
    m_modSizeKb = dialog.modSizeKb();
    m_linkerScriptPath = dialog.customLinkerScriptPath();

    if (!m_projectFilePath.isEmpty()) {
        saveProjectFile(m_projectFilePath);
    }

    statusBar()->showMessage(tr("Project settings saved"));
}

void MainWindow::compileActiveFile()
{
    CodeEditor *editor = activeEditor();
    if (!editor) {
        QMessageBox::information(this, tr("Compile"), tr("Open a project source file before compiling."));
        return;
    }

    if (m_projectFilePath.isEmpty()) {
        QMessageBox::information(this, tr("Compile"), tr("Save the project before compiling so build outputs can sit beside the .proj file."));
        return;
    }

    for (int i = 0; i < m_editorTabs->count(); ++i) {
        auto *openEditor = qobject_cast<CodeEditor *>(m_editorTabs->widget(i));
        if (openEditor && !saveEditor(openEditor)) {
            QMessageBox::warning(this, tr("Compile"), tr("Save all project files before compiling."));
            return;
        }
    }

    if (m_compilerProcess->state() != QProcess::NotRunning) {
        QMessageBox::information(this, tr("Compile"), tr("A compile is already running."));
        return;
    }

    const QStringList sourceFiles = projectFilesForCompile();
    if (sourceFiles.isEmpty()) {
        QMessageBox::information(this, tr("Compile"), tr("Add at least one .c, .cc, or .cpp file to the project before compiling."));
        return;
    }

    QString linkerError;
    if (m_linkerScriptPath.isEmpty() && !updateProjectLinkerScript(&linkerError)) {
        QMessageBox::warning(this, tr("Compile"), tr("Could not prepare the project linker script:\n%1").arg(linkerError));
        return;
    }

    const QString libsPath = ideLibsPath();
    const QDir apiDir(QDir(libsPath).filePath(QStringLiteral("api")));
    const QString selectedLinkerScript = effectiveLinkerScriptPath();
    const QString selectedCompiler = compilerPath();
    const QString selectedObjcopy = objcopyPath();
    const QStringList apiSourceFiles = sidboxApiSourceFiles();
    const QStringList libraryFiles = sidboxLibraryFiles();

    if (!QFileInfo::exists(selectedCompiler)) {
        QMessageBox::warning(this, tr("Compile"), tr("The bundled Sidbox compiler was not found:\n%1").arg(QDir::toNativeSeparators(selectedCompiler)));
        return;
    }

    if (!QFileInfo::exists(selectedObjcopy)) {
        QMessageBox::warning(this, tr("Compile"), tr("The bundled Sidbox objcopy was not found:\n%1").arg(QDir::toNativeSeparators(selectedObjcopy)));
        return;
    }

    if (!QFileInfo::exists(selectedLinkerScript)) {
        QMessageBox::warning(this, tr("Compile"), tr("The selected linker script does not exist:\n%1").arg(QDir::toNativeSeparators(selectedLinkerScript)));
        return;
    }

    if (apiSourceFiles.isEmpty()) {
        QMessageBox::warning(this, tr("Compile"), tr("The IDE API sources were not found under idelibs/api."));
        return;
    }

    const QString outputBaseName = QFileInfo(m_projectFilePath).completeBaseName();
    const QString buildPath = QDir(m_projectPath).filePath(QStringLiteral("build"));
    if (!QDir().mkpath(buildPath)) {
        QMessageBox::warning(this, tr("Compile"), tr("Could not create build folder:\n%1").arg(QDir::toNativeSeparators(buildPath)));
        return;
    }

    const QString outputPath = QDir(buildPath).filePath(outputBaseName + QStringLiteral(".elf"));
    const QString appOutputPath = QDir(m_projectPath).filePath(outputBaseName + QStringLiteral(".app"));
    const QString mapOutputPath = QDir(buildPath).filePath(outputBaseName + QStringLiteral(".map"));
    const QString asmOutputPath = QDir(buildPath).filePath(outputBaseName + QStringLiteral(".asm"));

    QStringList arguments = {
        QStringLiteral("-mcpu=cortex-m7"),
        QStringLiteral("-mthumb"),
        QStringLiteral("-mfpu=fpv5-d16"),
        QStringLiteral("-mfloat-abi=hard"),
        QStringLiteral("-std=gnu99"),
        QStringLiteral("-Ofast"),
        QStringLiteral("-ffunction-sections"),
        QStringLiteral("-fdata-sections"),
        QStringLiteral("-fstack-usage"),
        QStringLiteral("--specs=nano.specs"),
        QStringLiteral("-mno-unaligned-access"),
        QStringLiteral("-w"),
        QStringLiteral("-DSIDBOX_STARTUP_HEADER_IN_ASM"),
        QStringLiteral("-I"), apiDir.absolutePath(),
        QStringLiteral("-I"), QDir(libsPath).filePath(QStringLiteral("libraries")),
    };

    arguments << sourceFiles;
    arguments << apiSourceFiles;
    arguments << libraryFiles;
    arguments << QStringLiteral("-T") << selectedLinkerScript;
    arguments << QStringLiteral("-Wl,-Map=%1").arg(mapOutputPath);
    arguments << QStringLiteral("-Wl,--gc-sections")
              << QStringLiteral("-static")
              << QStringLiteral("--specs=nosys.specs");

    arguments << QStringLiteral("-Wl,--start-group")
              << QStringLiteral("-lc")
              << QStringLiteral("-lm")
              << QStringLiteral("-Wl,--end-group")
              << QStringLiteral("-o")
              << outputPath;

    m_outputPane->clear();
    appendOutputLine(tr("Compiler: %1").arg(QDir::toNativeSeparators(selectedCompiler)), OutputKind::Path);
    appendOutputLine(tr("Objcopy: %1").arg(QDir::toNativeSeparators(selectedObjcopy)), OutputKind::Path);
    appendOutputLine(tr("Project type: %1").arg(projectTypeLabel(m_projectType)), OutputKind::Header);
    appendOutputLine(tr("Project: %1").arg(QDir::toNativeSeparators(m_projectFilePath)), OutputKind::Path);
    appendOutputLine(tr("Build folder: %1").arg(QDir::toNativeSeparators(buildPath)), OutputKind::Path);
    appendOutputLine(tr("ELF: %1").arg(QDir::toNativeSeparators(outputPath)), OutputKind::Path);
    appendOutputLine(tr("APP: %1").arg(QDir::toNativeSeparators(appOutputPath)), OutputKind::Path);
    appendOutputLine(tr("Map: %1").arg(QDir::toNativeSeparators(mapOutputPath)), OutputKind::Path);
    appendOutputLine(tr("Asm: %1").arg(QDir::toNativeSeparators(asmOutputPath)), OutputKind::Path);
    appendOutputLine(tr("Linker script: %1").arg(QDir::toNativeSeparators(selectedLinkerScript)), OutputKind::Path);
    if (m_modSizeKb > 0) {
        appendOutputLine(tr("MOD size: %1 KB").arg(m_modSizeKb), OutputKind::Warning);
    }
    appendOutputLine(tr("Project sources:"), OutputKind::Header);
    for (const QString &sourceFile : sourceFiles) {
        appendOutputLine(tr("  %1").arg(displayPath(sourceFile)), OutputKind::Muted);
    }
    appendOutputLine(tr("IDE API sources:"), OutputKind::Header);
    for (const QString &apiSource : apiSourceFiles) {
        appendOutputLine(tr("  %1").arg(QDir(libsPath).relativeFilePath(apiSource)), OutputKind::Muted);
    }

    m_pendingElfPath = outputPath;
    m_pendingAppPath = appOutputPath;
    m_pendingAsmPath = asmOutputPath;
    m_buildStep = BuildStep::Linking;
    m_compilerProcess->setWorkingDirectory(buildPath);
    m_compilerProcess->start(selectedCompiler, arguments);

    statusBar()->showMessage(tr("Compile started"));
}




void MainWindow::openProjectFile(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);

    if (!item) {
        return;
    }

    const bool isFolder = item->data(0, Qt::UserRole + 1).toBool();
    const QString itemPath = item->data(0, Qt::UserRole).toString();

    if (isFolder) {
        item->setExpanded(!item->isExpanded());
        return;
    }

    if (!itemPath.isEmpty()) {
        openFile(itemPath);
    }
}

QString MainWindow::projectContextDirectory(QTreeWidgetItem *item) const
{
    if (m_projectPath.isEmpty()) {
        return {};
    }

    const QString projectRoot = QFileInfo(m_projectPath).absoluteFilePath();

    if (!item) {
        return projectRoot;
    }

    const QString itemPath = item->data(0, Qt::UserRole).toString();
    const bool isFolder = item->data(0, Qt::UserRole + 1).toBool();

    if (itemPath.isEmpty()) {
        return projectRoot;
    }

    QString directoryPath = isFolder
        ? QFileInfo(itemPath).absoluteFilePath()
        : QFileInfo(itemPath).absolutePath();

    /*
     * Files which live outside the project can appear as top-level items.
     * Do not create new project files beside those external files.
     */
    if (directoryPath != projectRoot
        && !directoryPath.startsWith(projectRoot + QDir::separator())) {
        directoryPath = projectRoot;
    }

    return directoryPath;
}

void MainWindow::moveProjectFile(const QString &sourceFilePath, const QString &targetDirectory)
{
    if (m_projectPath.isEmpty() || sourceFilePath.isEmpty()) {
        return;
    }

    const QString projectRoot = QFileInfo(m_projectPath).absoluteFilePath();
    const QString sourcePath = QFileInfo(sourceFilePath).absoluteFilePath();

    /*
     * External files may appear in the project tree, but dragging should never
     * silently relocate files from elsewhere on the machine.
     */
    if (sourcePath != projectRoot
        && !sourcePath.startsWith(projectRoot + QDir::separator())) {
        QMessageBox::information(
            this,
            tr("Move File"),
            tr("Only files inside the project folder can be moved by drag and drop."));
        refreshProjectFiles();
        return;
    }

    QString destinationDirectory = targetDirectory.isEmpty()
        ? projectRoot
        : QFileInfo(targetDirectory).absoluteFilePath();

    if (destinationDirectory != projectRoot
        && !destinationDirectory.startsWith(projectRoot + QDir::separator())) {
        destinationDirectory = projectRoot;
    }

    if (!QFileInfo(destinationDirectory).isDir()) {
        QMessageBox::warning(
            this,
            tr("Move File"),
            tr("The destination folder no longer exists."));
        refreshProjectFiles();
        return;
    }

    const QFileInfo sourceInfo(sourcePath);
    const QString destinationPath =
        QFileInfo(QDir(destinationDirectory).filePath(sourceInfo.fileName())).absoluteFilePath();

    /* Dropping onto the current folder is simply a no-op. */
    if (destinationPath == sourcePath) {
        refreshProjectFiles();
        return;
    }

    if (QFileInfo::exists(destinationPath)) {
        QMessageBox::warning(
            this,
            tr("Move File"),
            tr("A file named %1 already exists in that folder.").arg(sourceInfo.fileName()));
        refreshProjectFiles();
        return;
    }

    if (!QFile::rename(sourcePath, destinationPath)) {
        QMessageBox::warning(
            this,
            tr("Move File"),
            tr("Could not move %1 to %2.")
                .arg(QDir::toNativeSeparators(sourcePath),
                     QDir::toNativeSeparators(destinationDirectory)));
        refreshProjectFiles();
        return;
    }

    /* Update the explicit project-file list, if this file is stored there. */
    m_projectFilesInProject.removeAll(sourcePath);
    addProjectFile(destinationPath);

    /* Keep already-open editor tabs pointing at the file's new location. */
    for (int i = 0; i < m_editorTabs->count(); ++i) {
        auto *editor = qobject_cast<CodeEditor *>(m_editorTabs->widget(i));
        if (editor
            && QFileInfo(editor->filePath()).absoluteFilePath() == sourcePath) {
            editor->setFilePath(destinationPath);
            updateTabTitle(editor);
        }
    }

    refreshProjectFiles();
    refreshFunctionCompletions();

    if (!m_projectFilePath.isEmpty()) {
        saveProjectFile(m_projectFilePath);
    }

    statusBar()->showMessage(
        tr("File moved: %1").arg(displayPath(destinationPath)),
        4000);
}

void MainWindow::addExistingProjectFile()
{
    const QString baseDirectory = m_projectPath.isEmpty() ? QDir::homePath() : m_projectPath;
    const QStringList filePaths = QFileDialog::getOpenFileNames(
        this,
        tr("Add File"),
        baseDirectory,
        tr("Project files (*.c *.h *.inc *.txt *.md);;All files (*)"));

    if (filePaths.isEmpty()) {
        return;
    }

    for (const QString &filePath : filePaths) {
        addProjectFile(filePath);
    }

    refreshProjectFiles();
    if (!m_projectFilePath.isEmpty()) {
        saveProjectFile(m_projectFilePath);
    }
    statusBar()->showMessage(tr("File added to project"));
}

void MainWindow::createProjectFile()
{
    createProjectFileInDirectory(m_projectPath);
}

void MainWindow::createProjectFileInDirectory(const QString &directoryPath)
{
    if (m_projectPath.isEmpty()) {
        QMessageBox::information(this, tr("Create File"), tr("Save or create a project first so the IDE knows which folder to use."));
        return;
    }

    QString targetDirectory = directoryPath.isEmpty()
        ? QFileInfo(m_projectPath).absoluteFilePath()
        : QFileInfo(directoryPath).absoluteFilePath();

    const QString projectRoot = QFileInfo(m_projectPath).absoluteFilePath();
    if (targetDirectory != projectRoot
        && !targetDirectory.startsWith(projectRoot + QDir::separator())) {
        targetDirectory = projectRoot;
    }

    if (!QFileInfo(targetDirectory).isDir()) {
        QMessageBox::warning(this, tr("Create File"), tr("The selected project folder no longer exists."));
        return;
    }

    bool accepted = false;
    QString fileName = QInputDialog::getText(
        this,
        tr("Create File"),
        tr("File name:"),
        QLineEdit::Normal,
        QStringLiteral("newfile.c"),
        &accepted).trimmed();

    if (!accepted || fileName.isEmpty()) {
        return;
    }

    if (QFileInfo(fileName).suffix().isEmpty()) {
        fileName.append(QStringLiteral(".c"));
    }

    if (QFileInfo(fileName).fileName() != fileName) {
        QMessageBox::warning(this, tr("Create File"), tr("Enter a file name, not a path."));
        return;
    }

    const QString filePath = QFileInfo(QDir(targetDirectory).filePath(fileName)).absoluteFilePath();

    if (!isProjectExplorerFile(filePath)) {
        QMessageBox::warning(this, tr("Create File"), tr("Use one of these extensions: .c, .h, .inc, .txt, .md"));
        return;
    }

    if (QFileInfo::exists(filePath)) {
        QMessageBox::warning(this, tr("Create File"), tr("That file already exists."));
        return;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Create File"), tr("Could not create %1.").arg(QDir::toNativeSeparators(filePath)));
        return;
    }
    file.close();

    addProjectFile(filePath);
    refreshProjectFiles();
    openFile(filePath);

    if (!m_projectFilePath.isEmpty()) {
        saveProjectFile(m_projectFilePath);
    }

    statusBar()->showMessage(tr("File created: %1").arg(displayPath(filePath)));
}

void MainWindow::createProjectFolderInDirectory(const QString &directoryPath)
{
    if (m_projectPath.isEmpty()) {
        QMessageBox::information(this, tr("Create Folder"), tr("Save or create a project first so the IDE knows which folder to use."));
        return;
    }

    QString targetDirectory = directoryPath.isEmpty()
        ? QFileInfo(m_projectPath).absoluteFilePath()
        : QFileInfo(directoryPath).absoluteFilePath();

    const QString projectRoot = QFileInfo(m_projectPath).absoluteFilePath();
    if (targetDirectory != projectRoot
        && !targetDirectory.startsWith(projectRoot + QDir::separator())) {
        targetDirectory = projectRoot;
    }

    if (!QFileInfo(targetDirectory).isDir()) {
        QMessageBox::warning(this, tr("Create Folder"), tr("The selected project folder no longer exists."));
        return;
    }

    bool accepted = false;
    const QString folderName = QInputDialog::getText(
        this,
        tr("Create Folder"),
        tr("Folder name:"),
        QLineEdit::Normal,
        QStringLiteral("NewFolder"),
        &accepted).trimmed();

    if (!accepted || folderName.isEmpty()) {
        return;
    }

    if (folderName == QStringLiteral(".")
        || folderName == QStringLiteral("..")
        || QFileInfo(folderName).fileName() != folderName) {
        QMessageBox::warning(this, tr("Create Folder"), tr("Enter a folder name, not a path."));
        return;
    }

    const QString folderPath = QFileInfo(QDir(targetDirectory).filePath(folderName)).absoluteFilePath();

    if (QFileInfo::exists(folderPath)) {
        QMessageBox::warning(this, tr("Create Folder"), tr("That folder already exists."));
        return;
    }

    QDir parentDirectory(targetDirectory);
    if (!parentDirectory.mkdir(folderName)) {
        QMessageBox::warning(this, tr("Create Folder"), tr("Could not create %1.").arg(QDir::toNativeSeparators(folderPath)));
        return;
    }

    refreshProjectFiles();
    statusBar()->showMessage(tr("Folder created: %1").arg(displayPath(folderPath)));
}

void MainWindow::removeSelectedProjectFile()
{
    QTreeWidgetItem *item = m_projectFiles->currentItem();
    if (!item) {
        return;
    }

    if (item->data(0, Qt::UserRole + 1).toBool()) {
        return;
    }

    const QString filePath = item->data(0, Qt::UserRole).toString();
    if (filePath.isEmpty()) {
        return;
    }

    const bool inProjectFolder = !m_projectPath.isEmpty()
        && QFileInfo(filePath).absoluteFilePath().startsWith(QFileInfo(m_projectPath).absoluteFilePath() + QDir::separator());

    QMessageBox box(this);
    box.setWindowTitle(tr("Remove File"));
    box.setText(tr("Remove %1?").arg(displayPath(filePath)));
    QPushButton *removeButton = box.addButton(inProjectFolder ? tr("Delete File") : tr("Remove From Project"), QMessageBox::DestructiveRole);
    box.addButton(QMessageBox::Cancel);
    box.exec();

    if (box.clickedButton() != removeButton) {
        return;
    }

    if (inProjectFolder && QFileInfo::exists(filePath) && !QFile::remove(filePath)) {
        QMessageBox::warning(this, tr("Remove File"), tr("Could not delete %1.").arg(QDir::toNativeSeparators(filePath)));
        return;
    }

    m_projectFilesInProject.removeAll(QFileInfo(filePath).absoluteFilePath());
    for (int i = m_editorTabs->count() - 1; i >= 0; --i) {
        auto *editor = qobject_cast<CodeEditor *>(m_editorTabs->widget(i));
        if (editor && QFileInfo(editor->filePath()).absoluteFilePath() == QFileInfo(filePath).absoluteFilePath()) {
            QWidget *widget = m_editorTabs->widget(i);
            m_editorTabs->removeTab(i);
            widget->deleteLater();
        }
    }

    refreshProjectFiles();
    if (!m_projectFilePath.isEmpty()) {
        saveProjectFile(m_projectFilePath);
    }
    statusBar()->showMessage(tr("File removed"));
}

void MainWindow::renameSelectedProjectFile()
{
    QTreeWidgetItem *item = m_projectFiles->currentItem();
    if (!item) {
        return;
    }

    if (item->data(0, Qt::UserRole + 1).toBool()) {
        return;
    }

    const QString oldPath = item->data(0, Qt::UserRole).toString();
    const QFileInfo oldInfo(oldPath);
    if (!oldInfo.exists()) {
        return;
    }

    bool accepted = false;
    const QString newName = QInputDialog::getText(
        this,
        tr("Rename File"),
        tr("New name:"),
        QLineEdit::Normal,
        oldInfo.fileName(),
        &accepted).trimmed();

    if (!accepted || newName.isEmpty() || newName == oldInfo.fileName()) {
        return;
    }

    if (QFileInfo(newName).fileName() != newName) {
        QMessageBox::warning(this, tr("Rename File"), tr("Enter a file name, not a path."));
        return;
    }

    const QString newPath = QFileInfo(oldInfo.dir().filePath(newName)).absoluteFilePath();
    if (!isProjectExplorerFile(newPath)) {
        QMessageBox::warning(this, tr("Rename File"), tr("Use one of these extensions: .c, .h, .inc, .txt, .md"));
        return;
    }

    if (QFileInfo::exists(newPath)) {
        QMessageBox::warning(this, tr("Rename File"), tr("A file with that name already exists."));
        return;
    }

    if (!QFile::rename(oldPath, newPath)) {
        QMessageBox::warning(this, tr("Rename File"), tr("Could not rename %1.").arg(QDir::toNativeSeparators(oldPath)));
        return;
    }

    m_projectFilesInProject.removeAll(oldInfo.absoluteFilePath());
    addProjectFile(newPath);

    for (int i = 0; i < m_editorTabs->count(); ++i) {
        auto *editor = qobject_cast<CodeEditor *>(m_editorTabs->widget(i));
        if (editor && QFileInfo(editor->filePath()).absoluteFilePath() == oldInfo.absoluteFilePath()) {
            editor->setFilePath(newPath);
            updateTabTitle(editor);
        }
    }

    refreshProjectFiles();
    if (!m_projectFilePath.isEmpty()) {
        saveProjectFile(m_projectFilePath);
    }
    statusBar()->showMessage(tr("File renamed: %1").arg(displayPath(newPath)));
}

void MainWindow::handleCompilerFinished(int exitCode)
{
    if (m_buildStep == BuildStep::Linking) {
        if (exitCode != 0) {
            appendOutputLine(tr("Link failed with exit code %1.").arg(exitCode), OutputKind::Error);
            m_buildStep = BuildStep::None;
            statusBar()->showMessage(tr("Compile failed"));
            return;
        }

        appendOutputLine(tr("Link finished successfully."), OutputKind::Success);
        appendOutputLine(tr("Generating .asm output..."), OutputKind::Header);

        QString objdumpExec = objcopyPath();
        objdumpExec.replace(QStringLiteral("objcopy"), QStringLiteral("objdump"));

        m_buildStep = BuildStep::Asm;
        m_compilerProcess->setWorkingDirectory(m_projectPath);
        m_compilerProcess->setStandardOutputFile(m_pendingAsmPath);
        m_compilerProcess->start(objdumpExec, {
                                                  QStringLiteral("-d"),
                                                  QStringLiteral("-S"),
                                                  m_pendingElfPath
                                              });
        return;
    }

    if (m_buildStep == BuildStep::Asm) {
        m_compilerProcess->setStandardOutputFile(QString());

        if (exitCode != 0) {
            appendOutputLine(tr("ASM generation failed with exit code %1.").arg(exitCode), OutputKind::Error);
            m_buildStep = BuildStep::None;
            statusBar()->showMessage(tr("Compile failed"));
            return;
        }

        const qint64 asmSize = QFileInfo(m_pendingAsmPath).size();
        appendOutputLine(tr("ASM generated: %1").arg(QDir::toNativeSeparators(m_pendingAsmPath)), OutputKind::Success);
        if (asmSize >= 0) {
            appendOutputLine(tr("ASM size: %1 bytes").arg(QLocale().toString(asmSize)), OutputKind::Success);
        }

        appendOutputLine(tr("Generating .app binary..."), OutputKind::Header);

        m_buildStep = BuildStep::Objcopy;
        m_compilerProcess->setWorkingDirectory(m_projectPath);
        m_compilerProcess->start(objcopyPath(), {
                                                    QStringLiteral("-O"),
                                                    QStringLiteral("binary"),
                                                    m_pendingElfPath,
                                                    m_pendingAppPath
                                                });
        return;
    }

    if (m_buildStep == BuildStep::Objcopy) {
        if (exitCode != 0) {
            appendOutputLine(tr("Objcopy failed with exit code %1.").arg(exitCode), OutputKind::Error);
            m_buildStep = BuildStep::None;
            statusBar()->showMessage(tr("Compile failed"));
            return;
        }

        const qint64 appSize = QFileInfo(m_pendingAppPath).size();
        appendOutputLine(tr("APP generated: %1").arg(QDir::toNativeSeparators(m_pendingAppPath)), OutputKind::Success);
        if (appSize >= 0) {
            appendOutputLine(tr("APP size: %1 bytes").arg(QLocale().toString(appSize)), OutputKind::Success);
        }


        appendOutputLine(tr("Compile finished successfully."), OutputKind::Success);
        m_buildStep = BuildStep::None;
        statusBar()->showMessage(tr("Compile successful"));
        return;
    }

    m_buildStep = BuildStep::None;
}

CodeEditor *MainWindow::activeEditor() const
{
    return qobject_cast<CodeEditor *>(m_editorTabs->currentWidget());
}

CodeEditor *MainWindow::createEditor(const QString &filePath)
{
    auto *editor = new CodeEditor(m_editorTabs);
    editor->setFilePath(filePath);
    editor->setFunctionCompletions(projectFunctionSignatures());

    QFont font = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    font.setPointSize(m_editorFontPointSize);
    editor->setFont(font);
    editor->setCompletionFont(font);
    editor->refreshLineNumberAreaWidth();

    connect(editor->document(), &QTextDocument::modificationChanged, this, [this, editor]() {
        updateTabTitle(editor);
    });
    connect(editor->document(), &QTextDocument::contentsChanged, this, [this, editor]() {
        refreshFunctionCompletions();
        if (editor == activeEditor()) {
            refreshSymbolTree();
        }
    });

    connect(editor, &CodeEditor::quickTipRequested, this, &MainWindow::showQuickTip);
    connect(editor, &CodeEditor::quickTipCandidateChanged, this, &MainWindow::showPassiveQuickTip);
    return editor;
}


/*
bool MainWindow::openFile(const QString &filePath)
{
    for (int i = 0; i < m_editorTabs->count(); ++i) {
        auto *editor = qobject_cast<CodeEditor *>(m_editorTabs->widget(i));
        if (editor && QFileInfo(editor->filePath()).absoluteFilePath() == QFileInfo(filePath).absoluteFilePath()) {
            m_editorTabs->setCurrentIndex(i);
            return true;
        }
    }

    CodeEditor *editor = createEditor(filePath);
    if (!editor->loadFromFile(filePath)) {
        editor->deleteLater();
        QMessageBox::warning(this, tr("Open File"), tr("Could not open %1.").arg(QDir::toNativeSeparators(filePath)));
        return false;
    }

    const int index = m_editorTabs->addTab(editor, tabTitleForEditor(editor));
    m_editorTabs->setCurrentIndex(index);
    refreshFunctionCompletions();
    return true;
}

*/

bool MainWindow::openFile(const QString &filePath)
{
    for (int i = 0; i < m_editorTabs->count(); ++i) {
        //auto *editor = qobject_cast(m_editorTabs->widget(i));
        auto *editor = qobject_cast<CodeEditor *>(m_editorTabs->widget(i));
        if (editor && QFileInfo(editor->filePath()).absoluteFilePath() == QFileInfo(filePath).absoluteFilePath()) {
            m_editorTabs->setCurrentIndex(i);
            return true;
        }
    }

    CodeEditor *editor = createEditor(filePath);
    if (!editor->loadFromFile(filePath)) {
        editor->deleteLater();
        QMessageBox::warning(this, tr("Open File"), tr("Could not open %1.").arg(QDir::toNativeSeparators(filePath)));
        return false;
    }

    const int index = m_editorTabs->addTab(editor, tabTitleForEditor(editor));
    m_editorTabs->setCurrentIndex(index);
    addProjectFile(filePath);
    refreshProjectFiles();
    refreshFunctionCompletions();
    return true;
}




/*

bool MainWindow::saveEditor(CodeEditor *editor)
{
    if (!editor) {
        return false;
    }

    const bool wasUntitled = editor->filePath().isEmpty();
    if (wasUntitled) {
        const QString baseDirectory = m_projectPath.isEmpty() ? QDir::homePath() : m_projectPath;
        QString filePath = QFileDialog::getSaveFileName(
            this,
            tr("Save Source File"),
            QDir(baseDirectory).filePath(QStringLiteral("main.c")),
            tr("C source/header files (*.c *.h *.cc *.cpp *.hpp);;All files (*)"));

        if (filePath.isEmpty()) {
            return false;
        }

        if (QFileInfo(filePath).suffix().isEmpty()) {
            filePath.append(QStringLiteral(".c"));
        }

        if (!editor->saveAs(filePath)) {
            QMessageBox::warning(this, tr("Save File"), tr("Could not save %1.").arg(QDir::toNativeSeparators(filePath)));
            return false;
        }
    } else if (!editor->save()) {
        QMessageBox::warning(this, tr("Save File"), tr("Could not save %1.").arg(QDir::toNativeSeparators(editor->filePath())));
        return false;
    }

    addProjectFile(editor->filePath());
    updateTabTitle(editor);
    refreshProjectFiles();
    refreshFunctionCompletions();
    return true;
}

*/

bool MainWindow::saveEditor(CodeEditor *editor)
{
    if (!editor) {
        return false;
    }

    const bool wasUntitled = editor->filePath().isEmpty();
    if (wasUntitled) {
        const QString baseDirectory = m_projectPath.isEmpty() ? QDir::homePath() : m_projectPath;
        QString filePath = QFileDialog::getSaveFileName(
            this,
            tr("Save Source File"),
            QDir(baseDirectory).filePath(tabTitleForEditor(editor).remove(QLatin1Char('*'))),
            tr("Source files (*.c *.h *.inc *.cc *.cpp *.hpp);;All files (*)"));

        if (filePath.isEmpty()) {
            return false;
        }

        if (QFileInfo(filePath).suffix().isEmpty()) {
            filePath.append(QStringLiteral(".c"));
        }

        if (!editor->saveAs(filePath)) {
            QMessageBox::warning(this, tr("Save File"), tr("Could not save %1.").arg(QDir::toNativeSeparators(filePath)));
            return false;
        }
    } else if (!editor->save()) {
        QMessageBox::warning(this, tr("Save File"), tr("Could not save %1.").arg(QDir::toNativeSeparators(editor->filePath())));
        return false;
    }

    addProjectFile(editor->filePath());
    updateTabTitle(editor);
    refreshProjectFiles();
    refreshFunctionCompletions();
    return true;
}


bool MainWindow::saveModifiedWorkBeforeNewProject()
{
    bool hasUnsavedWork = m_projectFilePath.isEmpty() && m_editorTabs->count() > 0;
    for (int i = 0; i < m_editorTabs->count(); ++i) {
        auto *editor = qobject_cast<CodeEditor *>(m_editorTabs->widget(i));
        if (editor && editor->document()->isModified()) {
            hasUnsavedWork = true;
            break;
        }
    }

    if (!hasUnsavedWork) {
        return true;
    }

    const QMessageBox::StandardButton answer = QMessageBox::warning(
        this,
        tr("New Project"),
        tr("Save the current project and source files before creating a new project?"),
        QMessageBox::Save | QMessageBox::Cancel | QMessageBox::Discard,
        QMessageBox::Save);


    if (answer == QMessageBox::Discard) {
        // Throw away current work and reset to the exact same clean state as startup
        m_projectFilePath.clear();
        m_projectPath.clear();
        m_projectFilesInProject.clear();
        m_linkerScriptPath.clear();
        m_modSizeKb = 0;
        m_projectType = GuiProjectType;
        clearEditorTabs();
        refreshProjectFiles();
        createNewSourceFile();
        createNewHeaderFile();
        setWindowTitle(tr("Sidbox IDE"));
        statusBar()->showMessage(tr("New project started (unsaved)"));
        return false;   // stop createNewProject — we already did the reset
    }

    if (answer != QMessageBox::Save) {
        return false;
    }


    return saveProject();
}

bool MainWindow::loadProjectFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Open Project"), tr("Could not open %1.").arg(QDir::toNativeSeparators(filePath)));
        return false;
    }

    QJsonParseError parseError;
    const QJsonDocument document = QJsonDocument::fromJson(file.readAll(), &parseError);
    if (parseError.error != QJsonParseError::NoError || !document.isObject()) {
        QMessageBox::warning(this, tr("Open Project"), tr("The project file is not valid JSON."));
        return false;
    }

    const QJsonObject root = document.object();
    const QJsonArray files = root.value(QStringLiteral("files")).toArray();

    m_projectFilePath = QFileInfo(filePath).absoluteFilePath();
    m_projectPath = QFileInfo(m_projectFilePath).absolutePath();
    m_projectFilesInProject.clear();
    m_projectType = normalizedProjectType(root.value(QStringLiteral("projectType")).toString(GuiProjectType));
    m_modSizeKb = root.value(QStringLiteral("modSizeKb")).toInt(0);
    m_appSizeKb = root.value(QStringLiteral("appSizeKb")).toInt(0);

    const QString linkerScript = root.value(QStringLiteral("linkerScript")).toString();
    m_linkerScriptPath = linkerScript.isEmpty() ? QString() : fromProjectRelativePath(linkerScript);

    for (const QJsonValue &value : files) {
        const QString projectFile = fromProjectRelativePath(value.toString());
        if (!projectFile.isEmpty()) {
            addProjectFile(projectFile);
        }
    }

    clearEditorTabs();
    refreshProjectFiles();

    const QJsonArray openTabsArray = root.value(QStringLiteral("openTabs")).toArray();
    for (const QJsonValue &val : openTabsArray) {
        const QString tabPath = fromProjectRelativePath(val.toString());
        if (!tabPath.isEmpty() && QFileInfo::exists(tabPath)) {
            openFile(tabPath);
        }
    }

    /*
    for (const QString &projectFile : std::as_const(m_projectFilesInProject)) {
        // open initially the main.c only
        //openFile(projectFile);
        if (projectFile.endsWith(QStringLiteral("/main.c"), Qt::CaseInsensitive) || projectFile == QStringLiteral("main.c")) {
            openFile(projectFile);
            break; // Stop looping once main.c is found and opened
        }
    }
    */

    if (m_editorTabs->count() == 0) {
        for (const QString &projectFile : std::as_const(m_projectFilesInProject)) {
            if (projectFile.endsWith(QStringLiteral("/main.c"), Qt::CaseInsensitive) || projectFile == QStringLiteral("main.c")) {
                openFile(projectFile);
                break;
            }
        }
    }

    if (m_editorTabs->count() == 0) {
        createNewSourceFile();
    }

    refreshFunctionCompletions();
    setWindowTitle(tr("Sidbox IDE - %1").arg(QFileInfo(m_projectFilePath).fileName()));
    return true;
}

bool MainWindow::saveProjectFile(const QString &filePath)
{
    m_projectFilePath = QFileInfo(filePath).absoluteFilePath();
    m_projectPath = QFileInfo(m_projectFilePath).absolutePath();
    for (const QString &projectFile : collectOpenProjectFiles()) {
        addProjectFile(projectFile);
    }

    QJsonArray files;
    for (const QString &projectFile : std::as_const(m_projectFilesInProject)) {
        files.append(toProjectRelativePath(projectFile));
    }

    QJsonArray openTabsArray;
    for (int i = 0; i < m_editorTabs->count(); ++i) {
        auto *editor = qobject_cast<CodeEditor *>(m_editorTabs->widget(i));
        if (editor && !editor->filePath().isEmpty()) {
            openTabsArray.append(toProjectRelativePath(editor->filePath()));
        }
    }

    QJsonObject root;
    root.insert(QStringLiteral("version"), ProjectFileVersion);
    root.insert(QStringLiteral("projectType"), normalizedProjectType(m_projectType));
    root.insert(QStringLiteral("files"), files);
    root.insert(QStringLiteral("openTabs"), openTabsArray);
    root.insert(QStringLiteral("linkerScript"), m_linkerScriptPath.isEmpty() ? QString() : toProjectRelativePath(m_linkerScriptPath));
    root.insert(QStringLiteral("modSizeKb"), m_modSizeKb);
    root.insert(QStringLiteral("appSizeKb"), m_appSizeKb);

    QFile file(m_projectFilePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(this, tr("Save Project"), tr("Could not save %1.").arg(QDir::toNativeSeparators(m_projectFilePath)));
        return false;
    }

    file.write(QJsonDocument(root).toJson(QJsonDocument::Indented));
    file.close();

    if (m_linkerScriptPath.isEmpty()) {
        QString linkerError;
        if (!updateProjectLinkerScript(&linkerError)) {
            QMessageBox::warning(this, tr("Save Project"), tr("Project saved, but the linker script could not be prepared:\n%1").arg(linkerError));
            return false;
        }
    }

    refreshFunctionCompletions();
    setWindowTitle(tr("Sidbox IDE - %1").arg(QFileInfo(m_projectFilePath).fileName()));
    return true;
}

void MainWindow::addProjectFile(const QString &filePath)
{
    if (filePath.isEmpty()) {
        return;
    }

    const QString absolutePath = QFileInfo(filePath).absoluteFilePath();
    if (!m_projectFilesInProject.contains(absolutePath)) {
        m_projectFilesInProject.append(absolutePath);
        m_projectFilesInProject.sort(Qt::CaseInsensitive);
    }
}

void MainWindow::clearEditorTabs()
{
    while (m_editorTabs->count() > 0) {
        QWidget *widget = m_editorTabs->widget(0);
        m_editorTabs->removeTab(0);
        widget->deleteLater();
    }
}

void MainWindow::refreshProjectFiles()
{
    m_projectFiles->clear();

    QHash<QString, QTreeWidgetItem *> folderItems;

    /*
     * Create / find a folder item from a path relative to the project root.
     * Folder items store their real directory path in Qt::UserRole and are
     * marked as folders in Qt::UserRole + 1.
     */
    auto ensureFolderItem = [this, &folderItems](const QString &relativeFolderPath) -> QTreeWidgetItem * {
        const QString cleanPath = QDir::cleanPath(relativeFolderPath);
        if (cleanPath.isEmpty() || cleanPath == QStringLiteral(".")) {
            return nullptr;
        }

        const QStringList parts = cleanPath.split(QLatin1Char('/'), Qt::SkipEmptyParts);
        QTreeWidgetItem *parentItem = nullptr;
        QString currentFolder;

        for (const QString &part : parts) {
            if (!currentFolder.isEmpty()) {
                currentFolder += QLatin1Char('/');
            }
            currentFolder += part;

            QTreeWidgetItem *folderItem = folderItems.value(currentFolder, nullptr);
            if (!folderItem) {
                folderItem = new QTreeWidgetItem();
                folderItem->setText(0, part);
                folderItem->setIcon(0, QIcon(QStringLiteral(":/icons/tree_folder.png")));

                const QString absoluteFolderPath =
                    QFileInfo(QDir(m_projectPath).filePath(currentFolder)).absoluteFilePath();

                folderItem->setData(0, Qt::UserRole, absoluteFolderPath);
                folderItem->setData(0, Qt::UserRole + 1, true);
                folderItem->setToolTip(0, QDir::toNativeSeparators(absoluteFolderPath));

                if (parentItem) {
                    parentItem->addChild(folderItem);
                } else {
                    m_projectFiles->addTopLevelItem(folderItem);
                }

                folderItems.insert(currentFolder, folderItem);
            }

            parentItem = folderItem;
        }

        return parentItem;
    };

    /*
     * Add actual project directories first so empty folders are visible too.
     * The generated build folder stays hidden from the project explorer.
     */
    if (!m_projectPath.isEmpty() && QFileInfo(m_projectPath).isDir()) {
        QDirIterator directoryIterator(
            m_projectPath,
            QDir::Dirs | QDir::NoDotAndDotDot,
            QDirIterator::Subdirectories);

        while (directoryIterator.hasNext()) {
            const QString absoluteFolderPath =
                QFileInfo(directoryIterator.next()).absoluteFilePath();
            const QString relativeFolderPath =
                QDir(m_projectPath).relativeFilePath(absoluteFolderPath);

            if (relativeFolderPath == QStringLiteral("build")
                || relativeFolderPath.startsWith(QStringLiteral("build/"))) {
                continue;
            }

            ensureFolderItem(relativeFolderPath);
        }
    }

    QStringList files = m_projectFilesInProject;

    for (const QString &projectFile : projectFolderSourceFiles()) {
        const QString absolutePath = QFileInfo(projectFile).absoluteFilePath();
        if (!files.contains(absolutePath)) {
            files.append(absolutePath);
        }
    }

    files.removeDuplicates();
    files.sort(Qt::CaseInsensitive);

    for (const QString &filePath : std::as_const(files)) {
        if (!isProjectExplorerFile(filePath) || !QFileInfo::exists(filePath)) {
            continue;
        }

        const QFileInfo fileInfo(filePath);
        QString relativePath;

        if (!m_projectPath.isEmpty()) {
            relativePath = QDir(m_projectPath).relativeFilePath(fileInfo.absoluteFilePath());
        } else {
            relativePath = fileInfo.fileName();
        }

        relativePath = QDir::cleanPath(relativePath);

        QIcon fileIcon;
        const QString suffix = fileInfo.suffix().toLower();

        if (suffix == QStringLiteral("c")) {
            fileIcon = QIcon(QStringLiteral(":/icons/tree_file_c.png"));
        } else if (suffix == QStringLiteral("h")) {
            fileIcon = QIcon(QStringLiteral(":/icons/tree_file_h.png"));
        } else if (suffix == QStringLiteral("inc")) {
            fileIcon = QIcon(QStringLiteral(":/icons/tree_file_inc.png"));
        } else if (suffix == QStringLiteral("txt")) {
            fileIcon = QIcon(QStringLiteral(":/icons/tree_file_txt.png"));
        } else if (suffix == QStringLiteral("md")) {
            fileIcon = QIcon(QStringLiteral(":/icons/tree_file_md.png"));
        } else {
            fileIcon = QIcon(QStringLiteral(":/icons/tree_file_unknown.png"));
        }

        /* Files outside the project directory remain top-level entries. */
        if (relativePath == QStringLiteral("..")
            || relativePath.startsWith(QStringLiteral("../"))) {

            auto *fileItem = new QTreeWidgetItem(m_projectFiles);
            fileItem->setText(0, projectFileDisplayText(filePath));
            fileItem->setIcon(0, fileIcon);
            fileItem->setData(0, Qt::UserRole, fileInfo.absoluteFilePath());
            fileItem->setData(0, Qt::UserRole + 1, false);
            fileItem->setToolTip(0, QDir::toNativeSeparators(fileInfo.absoluteFilePath()));
            continue;
        }

        const QString parentFolderPath = QFileInfo(relativePath).path();
        QTreeWidgetItem *parentItem = nullptr;

        if (!parentFolderPath.isEmpty() && parentFolderPath != QStringLiteral(".")) {
            parentItem = ensureFolderItem(parentFolderPath);
        }

        auto *fileItem = new QTreeWidgetItem();
        fileItem->setText(0, QStringLiteral("%1 (%2)")
                                 .arg(fileInfo.fileName(), formattedFileSize(fileInfo.size())));
        fileItem->setIcon(0, fileIcon);
        fileItem->setData(0, Qt::UserRole, fileInfo.absoluteFilePath());
        fileItem->setData(0, Qt::UserRole + 1, false);
        fileItem->setToolTip(0, QDir::toNativeSeparators(fileInfo.absoluteFilePath()));

        if (parentItem) {
            parentItem->addChild(fileItem);
        } else {
            m_projectFiles->addTopLevelItem(fileItem);
        }
    }

    m_projectFiles->expandAll();
}

void MainWindow::saveSymbolTreeExpansionState(CodeEditor *editor)
{
    if (!editor || !m_functionvarList) {
        return;
    }

    QSet<QString> expanded;

    std::function<void(QTreeWidgetItem *)> scan;
    scan = [&](QTreeWidgetItem *item) {
        if (!item) {
            return;
        }

        const QString key = item->data(0, Qt::UserRole + 10).toString();

        if (!key.isEmpty() && item->isExpanded()) {
            expanded.insert(key);
        }

        for (int i = 0; i < item->childCount(); ++i) {
            scan(item->child(i));
        }
    };

    for (int i = 0; i < m_functionvarList->topLevelItemCount(); ++i) {
        scan(m_functionvarList->topLevelItem(i));
    }

    m_symbolTreeExpanded[editor] = expanded;
}

void MainWindow::restoreSymbolTreeExpansionState(CodeEditor *editor)
{
    if (!editor || !m_functionvarList) {
        return;
    }

    const QSet<QString> expanded = m_symbolTreeExpanded.value(editor);

    std::function<void(QTreeWidgetItem *)> restore;
    restore = [&](QTreeWidgetItem *item) {
        if (!item) {
            return;
        }

        const QString key = item->data(0, Qt::UserRole + 10).toString();

        if (!key.isEmpty()) {
            item->setExpanded(expanded.contains(key));
        }

        for (int i = 0; i < item->childCount(); ++i) {
            restore(item->child(i));
        }
    };

    for (int i = 0; i < m_functionvarList->topLevelItemCount(); ++i) {
        restore(m_functionvarList->topLevelItem(i));
    }
}


void MainWindow::refreshSymbolTree()
{
    if (!m_functionvarList) {
        return;
    }

    // Save the tree state belonging to the editor
    // that is CURRENTLY represented by the tree.
    if (m_symbolTreeEditor) {
        saveSymbolTreeExpansionState(m_symbolTreeEditor);
    }

    CodeEditor *editor = activeEditor();

    m_functionvarList->clear();

    if (!editor) {
        m_symbolTreeEditor = nullptr;
        return;
    }

    const SourceSymbolTable symbols =
        parseSourceSymbols(editor->toPlainText());


    const QIcon functionIcon(QStringLiteral(":/icons/tree_scope_function.png"));
    const QIcon globalIcon(QStringLiteral(":/icons/tree_scope_globals.png"));
    const QIcon typeIcon(QStringLiteral(":/icons/tree_scope_types.png"));
    const QIcon defineIcon(QStringLiteral(":/icons/tree_scope_defines.png"));
    const QIcon parameterIcon(QStringLiteral(":/icons/tree_scope_params.png"));

    const QIcon localIcon(QStringLiteral(":/icons/tree_scope_locals.png"));

    auto addNoneItem = [](QTreeWidgetItem *parent) {
        auto *noneItem = new QTreeWidgetItem(parent);
        noneItem->setText(0, QObject::tr("(none)"));
        noneItem->setFlags(noneItem->flags() & ~Qt::ItemIsSelectable);
    };

    auto *definesItem = new QTreeWidgetItem(m_functionvarList);
    definesItem->setText(0, tr("Defines"));

    definesItem->setIcon(0, defineIcon);
    definesItem->setExpanded(false);

    if (symbols.defines.isEmpty()) {
        addNoneItem(definesItem);
    } else {
        for (const SourceNamedSymbol &define : symbols.defines) {
            auto *item = new QTreeWidgetItem(definesItem);
            item->setText(0, define.name);
            item->setIcon(0, defineIcon);
            item->setData(0, Qt::UserRole, define.line);
            item->setToolTip(0, tr("#define — double-click to jump to line %1").arg(define.line + 1));
        }
        definesItem->setText(0,
            QStringLiteral("Defines (%1)")
                .arg(definesItem->childCount())
            );
    }
    definesItem->setData(
        0,
        Qt::UserRole + 10,
        QStringLiteral("defines")
        );


    auto *typesItem = new QTreeWidgetItem(m_functionvarList);
    typesItem->setText(0, tr("Types"));
    typesItem->setIcon(0, typeIcon);
    typesItem->setExpanded(false);

    if (symbols.types.isEmpty()) {
        addNoneItem(typesItem);
    } else {
        for (const SourceNamedSymbol &type : symbols.types) {
            auto *item = new QTreeWidgetItem(typesItem);
            item->setText(0, type.name);
            item->setIcon(0, typeIcon);
            item->setData(0, Qt::UserRole, type.line);
            item->setToolTip(0, tr("Type — double-click to jump to line %1").arg(type.line + 1));
        }
        typesItem->setText(0,
            QStringLiteral("Types (%1)")
                .arg(typesItem->childCount())
            );
    }
    typesItem->setData(
        0,
        Qt::UserRole + 10,
        QStringLiteral("types")
        );

    auto *globalsItem = new QTreeWidgetItem(m_functionvarList);
    globalsItem->setText(0, tr("Globals"));
    globalsItem->setIcon(0, globalIcon);
    globalsItem->setExpanded(false);

    if (symbols.globals.isEmpty()) {
        addNoneItem(globalsItem);
    } else {
        for (const SourceVariableSymbol &global : symbols.globals) {
            auto *item = new QTreeWidgetItem(globalsItem);
            item->setText(0, global.name);
            item->setIcon(0, globalIcon);
            item->setData(0, Qt::UserRole, global.line);
            item->setToolTip(0, tr("Global — double-click to jump to line %1").arg(global.line + 1));
        }
        globalsItem->setText(0,
            QStringLiteral("Globals (%1)")
                .arg(globalsItem->childCount())
            );
    }
    globalsItem->setData(
        0,
        Qt::UserRole + 10,
        QStringLiteral("globals")
        );

    auto *functionsItem = new QTreeWidgetItem(m_functionvarList);
    functionsItem->setText(0, tr("Functions"));
    functionsItem->setExpanded(false);
    functionsItem->setIcon(0, functionIcon);
    functionsItem->setData(
        0,
        Qt::UserRole + 10,
        QStringLiteral("functions")
        );

    if (symbols.functions.isEmpty()) {
        addNoneItem(functionsItem);
    } else {
        for (const SourceFunctionSymbol &function : symbols.functions) {
            auto *functionItem = new QTreeWidgetItem(functionsItem);
            functionItem->setText(0, function.signature);
            functionItem->setIcon(0, functionIcon);
            functionItem->setData(0, Qt::UserRole, function.line);
            functionItem->setToolTip(0, tr("Function — double-click to jump to line %1").arg(function.line + 1));
            functionItem->setData(
                0,
                Qt::UserRole + 10,
                QStringLiteral("function:%1").arg(function.signature)
                );

            if (!function.parameters.isEmpty()) {
                auto *parametersItem = new QTreeWidgetItem(functionItem);
                parametersItem->setText(0, tr("Parameters"));
                parametersItem->setIcon(0, parameterIcon);
                parametersItem->setExpanded(true);
                for (const SourceVariableSymbol &parameter : function.parameters) {
                    auto *item = new QTreeWidgetItem(parametersItem);
                    item->setText(0, parameter.name);
                    item->setIcon(0, parameterIcon);
                    item->setData(0, Qt::UserRole, parameter.line);
                    item->setToolTip(0, tr("Parameter — double-click to jump to function"));
                }
                parametersItem->setData(
                    0,
                    Qt::UserRole + 10,
                    QStringLiteral("function:%1:parameters").arg(function.signature)
                    );
            }

            if (!function.locals.isEmpty()) {
                auto *localsItem = new QTreeWidgetItem(functionItem);
                localsItem->setText(0, tr("Locals"));
                localsItem->setIcon(0, localIcon);
                localsItem->setExpanded(true);
                for (const SourceVariableSymbol &local : function.locals) {
                    auto *item = new QTreeWidgetItem(localsItem);
                    item->setText(0, local.name);
                    item->setIcon(0, localIcon);
                    item->setData(0, Qt::UserRole, local.line);
                    item->setToolTip(0, tr("Local — double-click to jump to line %1").arg(local.line + 1));
                }
                localsItem->setData(
                    0,
                    Qt::UserRole + 10,
                    QStringLiteral("function:%1:locals").arg(function.signature)
                    );
            }

        }
        functionsItem->setText(
            0,
            QStringLiteral("Functions (%1)")
                .arg(functionsItem->childCount())
            );
    }



    restoreSymbolTreeExpansionState(editor);

    m_symbolTreeEditor = editor;
}

void MainWindow::jumpToSymbol(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);

    if (!item) {
        return;
    }

    bool ok = false;
    const int line = item->data(0, Qt::UserRole).toInt(&ok);
    if (!ok || line < 0) {
        return;
    }

    CodeEditor *editor = activeEditor();
    if (!editor) {
        return;
    }

    const QTextBlock block = editor->document()->findBlockByNumber(line);
    if (!block.isValid()) {
        return;
    }

    QTextCursor cursor(block);
    editor->setTextCursor(cursor);
    editor->centerCursor();
    editor->setFocus();
}

void MainWindow::refreshFunctionCompletions()
{
    ensureApiCatalog();
    const QStringList signatures = projectFunctionSignatures();
    for (int i = 0; i < m_editorTabs->count(); ++i) {
        auto *editor = qobject_cast<CodeEditor *>(m_editorTabs->widget(i));
        if (editor) {
            editor->setFunctionCompletions(signatures);
        }
    }
}

void MainWindow::ensureApiCatalog()
{
    if (m_apiTips.isEmpty() || m_apiSignatures.isEmpty()) {
        refreshApiCatalog();
    }
}


void MainWindow::refreshApiCatalog()
{
    m_apiTips.clear();
    m_apiSignatures.clear();

    const QString apiPath = QDir(ideLibsPath()).filePath(QStringLiteral("api"));
    if (!QFileInfo::exists(apiPath)) {
        if (m_quickTipLabel) {
            m_quickTipLabel->setText(tr("F1: API folder not found: %1").arg(QDir::toNativeSeparators(apiPath)));
        }
        return;
    }

    QStringList apiTexts;
    QDirIterator iterator(apiPath, {QStringLiteral("*.h")}, QDir::Files, QDirIterator::Subdirectories);
    while (iterator.hasNext()) {
        QFile file(iterator.next());
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            continue;
        }

        apiTexts.append(uncommentedApiText(QString::fromUtf8(file.readAll())));
    }

    QHash<QString, QString> functionPointers;
    for (const QString &text : std::as_const(apiTexts)) {
        collectApiFunctionPointers(text, &functionPointers);
    }

    for (const QString &text : std::as_const(apiTexts)) {
        collectApiMacros(text, functionPointers, &m_apiTips, &m_apiSignatures);
        collectApiDefines(text, &m_apiTips, &m_apiSignatures);
        collectApiTypes(text, &m_apiTips, &m_apiSignatures);
        collectApiLineSymbols(text, &m_apiTips, &m_apiSignatures);
        m_apiSignatures.append(functionSignaturesFromText(text));
    }

    m_apiSignatures.removeDuplicates();
    m_apiSignatures.sort(Qt::CaseInsensitive);

    if (m_quickTipLabel) {
        m_quickTipLabel->setText(tr("F1: API ready: %1 tips from %2").arg(m_apiTips.count()).arg(QDir::toNativeSeparators(apiPath)));
    }
}

QString MainWindow::quickTipForSymbol(const QString &symbol) const
{
    const QString name = symbol.trimmed();
    if (name.isEmpty()) {
        return {};
    }

    const auto exactMatch = m_apiTips.constFind(name);
    if (exactMatch != m_apiTips.constEnd()) {
        return exactMatch.value();
    }

    for (auto it = m_apiTips.constBegin(); it != m_apiTips.constEnd(); ++it) {
        if (it.key().compare(name, Qt::CaseInsensitive) == 0) {
            return it.value();
        }
    }

    const QStringList signatures = projectFunctionSignatures();
    for (const QString &signature : signatures) {
        const int parenIndex = signature.indexOf(QLatin1Char('('));
        if (parenIndex > 0 && signature.left(parenIndex).compare(name, Qt::CaseInsensitive) == 0) {
            return signature;
        }
    }

    return {};
}

void MainWindow::showPassiveQuickTip(const QString &symbol)
{
    if (!m_quickTipLabel) {
        return;
    }

    ensureApiCatalog();
    const QString tip = quickTipForSymbol(symbol);
    if (!tip.isEmpty()) {
        m_quickTipLabel->setText(tip);
    }
}


void MainWindow::showQuickTip(const QString &symbol)
{
    if (!m_quickTipLabel) {
        return;
    }

    ensureApiCatalog();
    const QString name = symbol.trimmed();
    if (name.isEmpty()) {
        m_quickTipLabel->setText(tr("F1: move the cursor onto an API call first"));
        return;
    }

    const QString tip = quickTipForSymbol(name);
    if (tip.isEmpty()) {
        m_quickTipLabel->setText(tr("F1: no API tip for %1").arg(name));
        return;
    }

    m_quickTipLabel->setText(tip);
    statusBar()->showMessage(tip, 4000);
}


void MainWindow::updateTabTitle(CodeEditor *editor)
{
    const int index = m_editorTabs->indexOf(editor);
    if (index >= 0) {
        m_editorTabs->setTabText(index, tabTitleForEditor(editor));
    }
}

/*
QString MainWindow::tabTitleForEditor(CodeEditor *editor) const
{
    QString title = editor->filePath().isEmpty()
        ? tr("untitled.c")
        : QFileInfo(editor->filePath()).fileName();

    if (editor->document()->isModified()) {
        title.prepend(QLatin1Char('*'));
    }

    return title;
}
*/

QString MainWindow::tabTitleForEditor(CodeEditor *editor, int defaultType) const
{
    QString title;
    if (editor->filePath().isEmpty()) {
        if (defaultType == 1) {
            title = tr("untitled.h");
        } else if (defaultType == 2) {
            title = tr("untitled.inc");
        } else {
            title = tr("untitled.c");
        }
    } else {
        title = QFileInfo(editor->filePath()).fileName();
    }

    if (editor->document()->isModified()) {
        title.prepend(QLatin1Char('*'));
    }

    return title;
}

QString MainWindow::displayPath(const QString &filePath) const
{
    if (m_projectPath.isEmpty()) {
        return QFileInfo(filePath).fileName();
    }

    return QDir(m_projectPath).relativeFilePath(filePath);
}

QString MainWindow::projectFileDisplayText(const QString &filePath) const
{
    const QFileInfo info(filePath);
    return QStringLiteral("%1 (%2)").arg(displayPath(filePath), formattedFileSize(info.size()));
}

QStringList MainWindow::projectFolderSourceFiles() const
{
    QStringList files;
    if (m_projectPath.isEmpty() || !QFileInfo::exists(m_projectPath)) {
        return files;
    }

    const QStringList filters = {
        QStringLiteral("*.c"), QStringLiteral("*.h"), QStringLiteral("*.inc"),
        QStringLiteral("*.txt"), QStringLiteral("*.md")
    };

    QDirIterator iterator(m_projectPath, filters, QDir::Files, QDirIterator::Subdirectories);
    while (iterator.hasNext()) {
        const QString filePath = QFileInfo(iterator.next()).absoluteFilePath();
        const QString relativePath = QDir(m_projectPath).relativeFilePath(filePath);
        if (relativePath.startsWith(QStringLiteral("build/")) || relativePath == QStringLiteral("build")) {
            continue;
        }
        files.append(filePath);
    }

    files.removeDuplicates();
    files.sort(Qt::CaseInsensitive);
    return files;
}

bool MainWindow::isProjectExplorerFile(const QString &filePath) const
{
    return isProjectExplorerSuffix(QFileInfo(filePath).suffix());
}

QStringList MainWindow::collectOpenProjectFiles() const
{
    QStringList files;
    for (int i = 0; i < m_editorTabs->count(); ++i) {
        auto *editor = qobject_cast<CodeEditor *>(m_editorTabs->widget(i));
        if (!editor || editor->filePath().isEmpty()) {
            continue;
        }

        const QString filePath = QFileInfo(editor->filePath()).absoluteFilePath();
        if (!files.contains(filePath)) {
            files.append(filePath);
        }
    }

    files.sort(Qt::CaseInsensitive);
    return files;
}

QStringList MainWindow::projectFilesForCompile() const
{
    QStringList files;
    QStringList candidates = m_projectFilesInProject;
    candidates.append(projectFolderSourceFiles());
    candidates.removeDuplicates();

    for (const QString &filePath : std::as_const(candidates)) {
        if (isCompilableSource(filePath)) {
            files.append(filePath);
        }
    }
    files.removeDuplicates();
    files.sort(Qt::CaseInsensitive);
    return files;
}

QStringList MainWindow::projectFunctionSignatures() const
{
    QStringList signatures;
    signatures.append(m_apiSignatures);
    QStringList scannedOpenFiles;

    for (int i = 0; i < m_editorTabs->count(); ++i) {
        auto *editor = qobject_cast<CodeEditor *>(m_editorTabs->widget(i));
        if (!editor) {
            continue;
        }

        signatures.append(functionSignaturesFromText(editor->toPlainText()));
        if (!editor->filePath().isEmpty()) {
            scannedOpenFiles.append(QFileInfo(editor->filePath()).absoluteFilePath());
        }
    }

    for (const QString &filePath : m_projectFilesInProject) {
        const QString absolutePath = QFileInfo(filePath).absoluteFilePath();
        if (scannedOpenFiles.contains(absolutePath) || !canContainFunctionSignatures(absolutePath)) {
            continue;
        }

        QFile file(absolutePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            continue;
        }

        signatures.append(functionSignaturesFromText(QString::fromUtf8(file.readAll())));
    }

    signatures.removeDuplicates();
    signatures.sort(Qt::CaseInsensitive);
    return signatures;
}

QStringList MainWindow::functionSignaturesFromText(const QString &text) const
{
    static const QStringList ignoredNames = {
        QStringLiteral("if"), QStringLiteral("for"), QStringLiteral("while"),
        QStringLiteral("switch"), QStringLiteral("return"), QStringLiteral("sizeof")
    };
    static const QRegularExpression functionExpression(
        QStringLiteral("(?:^|[\\n;{}])\\s*(?:[A-Za-z_][A-Za-z0-9_]*\\s+|[*]\\s*)+([A-Za-z_][A-Za-z0-9_]*)\\s*\\(([^;{}()]*)\\)\\s*(?=[;{])"),
        QRegularExpression::MultilineOption);

    QStringList signatures;
    QRegularExpressionMatchIterator iterator = functionExpression.globalMatch(text);
    while (iterator.hasNext()) {
        const QRegularExpressionMatch match = iterator.next();
        const QString name = match.captured(1).trimmed();
        const QString arguments = match.captured(2).simplified();
        if (!name.isEmpty() && !ignoredNames.contains(name)) {
            signatures.append(QStringLiteral("%1(%2)").arg(name, arguments));
        }
    }

    signatures.removeDuplicates();
    return signatures;
}

QString MainWindow::toProjectRelativePath(const QString &filePath) const
{
    if (filePath.isEmpty() || m_projectPath.isEmpty()) {
        return filePath;
    }

    return QDir(m_projectPath).relativeFilePath(filePath);
}

QString MainWindow::fromProjectRelativePath(const QString &filePath) const
{
    if (filePath.isEmpty()) {
        return {};
    }

    QFileInfo info(filePath);
    if (info.isAbsolute()) {
        return info.absoluteFilePath();
    }

    return QFileInfo(QDir(m_projectPath).filePath(filePath)).absoluteFilePath();
}

QString MainWindow::ideLibsPath() const
{
    const QDir appDir(QCoreApplication::applicationDirPath());
    const QStringList candidates = {
        appDir.filePath(QStringLiteral("idelibs")),
        appDir.filePath(QStringLiteral("../idelibs")),
        appDir.filePath(QStringLiteral("../../idelibs")),
        appDir.filePath(QStringLiteral("../SidboxIDE/idelibs")),
        QDir::current().filePath(QStringLiteral("idelibs")),
        QDir::current().filePath(QStringLiteral("SidboxIDE/idelibs"))
    };

    for (const QString &candidate : candidates) {
        const QFileInfo info(candidate);
        if (info.exists() && info.isDir()) {
            return info.absoluteFilePath();
        }
    }

    return QFileInfo(appDir.filePath(QStringLiteral("../../idelibs"))).absoluteFilePath();
}

QString MainWindow::defaultLinkerScriptPath(const QString &projectType) const
{
    const QString type = normalizedProjectType(projectType.isEmpty() ? m_projectType : projectType);
    return QDir(ideLibsPath()).filePath(type == GameProjectType ? QStringLiteral("gaming.ld") : QStringLiteral("gui.ld"));
}

QString MainWindow::projectLinkerScriptPath() const
{
    if (m_projectFilePath.isEmpty()) {
        return {};
    }

    const QString fileName = QFileInfo(m_projectFilePath).completeBaseName() + QStringLiteral(".ld");
    return QDir(m_projectPath).filePath(fileName);
}

QString MainWindow::effectiveLinkerScriptPath() const
{
    if (!m_linkerScriptPath.isEmpty()) {
        return m_linkerScriptPath;
    }

    const QString projectLinker = projectLinkerScriptPath();
    return projectLinker.isEmpty() ? defaultLinkerScriptPath() : projectLinker;
}

bool MainWindow::updateProjectLinkerScript(QString *errorMessage) const
{
    if (m_projectFilePath.isEmpty() || m_projectPath.isEmpty()) {
        if (errorMessage) {
            *errorMessage = tr("Save the project first so the linker script has a project folder.");
        }
        return false;
    }

    const QString sourcePath = defaultLinkerScriptPath();
    QFile sourceFile(sourcePath);
    if (!sourceFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        if (errorMessage) {
            *errorMessage = tr("Could not read %1.").arg(QDir::toNativeSeparators(sourcePath));
        }
        return false;
    }

    QString scriptText = QString::fromUtf8(sourceFile.readAll());
    const QString profileValue = normalizedProjectType(m_projectType) == GameProjectType
        ? QStringLiteral("0")
        : QStringLiteral("1");

    if (!replaceLinkerAssignment(&scriptText, QStringLiteral("_profile_is_desktop"), profileValue)
        || !replaceLinkerAssignment(&scriptText, QStringLiteral("_largest_modfile"), hexBytes(m_modSizeKb))) {
        if (errorMessage) {
            *errorMessage = tr("The template linker script is missing an expected Sidbox setting.");
        }
        return false;
    }

    scriptText.prepend(tr("/* Generated by Sidbox IDE from %1. Edit the project settings to regenerate. */\n")
        .arg(QDir::toNativeSeparators(sourcePath)));

    const QString destinationPath = projectLinkerScriptPath();
    QSaveFile destinationFile(destinationPath);
    if (!destinationFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        if (errorMessage) {
            *errorMessage = tr("Could not write %1.").arg(QDir::toNativeSeparators(destinationPath));
        }
        return false;
    }

    destinationFile.write(scriptText.toUtf8());
    if (!destinationFile.commit()) {
        if (errorMessage) {
            *errorMessage = tr("Could not finish writing %1.").arg(QDir::toNativeSeparators(destinationPath));
        }
        return false;
    }

    return true;
}

QString MainWindow::compilerPath() const
{
    return QDir(ideLibsPath()).filePath(QStringLiteral("tools/bin/arm-none-eabi-gcc"));
}

QString MainWindow::objcopyPath() const
{
    return QDir(ideLibsPath()).filePath(QStringLiteral("tools/bin/arm-none-eabi-objcopy"));
}

QStringList MainWindow::sidboxApiSourceFiles() const
{
    // realistically this should scan the folders, and search for the .c / .h for function calls, type defs
    const QDir apiDir(QDir(ideLibsPath()).filePath(QStringLiteral("api")));
    const QStringList relativePaths = {
        QStringLiteral("applet.s"),
        QStringLiteral("apis.c"),
        QStringLiteral("syscalls.c"),
        QStringLiteral("crt/crt.c"),
        QStringLiteral("graphics/graphics.c"),
        QStringLiteral("audio/audio.c"),
        QStringLiteral("touch/touch.c")
    };

    QStringList files;
    for (const QString &relativePath : relativePaths) {
        const QString absolutePath = apiDir.filePath(relativePath);
        if (QFileInfo::exists(absolutePath)) {
            files.append(absolutePath);
        }
    }
    return files;
}

QStringList MainWindow::sidboxLibraryFiles() const
{
    QStringList files;
    const QString libraryPath = QDir(ideLibsPath()).filePath(QStringLiteral("libraries"));
    if (!QFileInfo::exists(libraryPath)) {
        return files;
    }

    QDirIterator iterator(libraryPath, {QStringLiteral("*.a")}, QDir::Files, QDirIterator::Subdirectories);
    while (iterator.hasNext()) {
        files.append(iterator.next());
    }
    return files;
}

void MainWindow::applyEditorFont()
{
    QFont font = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    font.setPointSize(m_editorFontPointSize);

    for (int i = 0; i < m_editorTabs->count(); ++i) {
        auto *editor = qobject_cast<CodeEditor *>(m_editorTabs->widget(i));
        if (!editor) {
            continue;
        }

        editor->setFont(font);
        editor->setTabStopDistance(editor->fontMetrics().horizontalAdvance(QLatin1Char(' ')) * 4);
        editor->setCompletionFont(font);
        editor->refreshLineNumberAreaWidth();
    }
}

void MainWindow::appendOutputText(const QString &text, OutputKind kind)
{
    if (!m_outputPane || text.isEmpty()) {
        return;
    }

    QColor color;
    switch (kind) {
    case OutputKind::Header:
        color = QColor(120, 220, 255);
        break;
    case OutputKind::Path:
        color = QColor(170, 205, 255);
        break;
    case OutputKind::Success:
        color = QColor(80, 255, 120);
        break;
    case OutputKind::Error:
        color = QColor(255, 90, 90);
        break;
    case OutputKind::Warning:
        color = QColor(255, 210, 90);
        break;
    case OutputKind::Muted:
        color = QColor(150, 165, 150);
        break;
    case OutputKind::Normal:
        color = QColor(220, 235, 210);
        break;
    }

    QTextCharFormat format;
    format.setForeground(color);

    QTextCursor cursor = m_outputPane->textCursor();
    cursor.movePosition(QTextCursor::End);
    cursor.insertText(text, format);
    m_outputPane->setTextCursor(cursor);
    m_outputPane->ensureCursorVisible();
}

void MainWindow::appendOutputLine(const QString &text, OutputKind kind)
{
    appendOutputText(text + QLatin1Char('\n'), kind);
}

void MainWindow::loadOptions()
{
    QSettings settings(QStringLiteral("Sidbox"), QStringLiteral("SidboxIDE"));
    m_editorFontPointSize = settings.value(QStringLiteral("editor/fontPointSize"), 10).toInt();
}

void MainWindow::saveOptions() const
{
    QSettings settings(QStringLiteral("Sidbox"), QStringLiteral("SidboxIDE"));
    settings.setValue(QStringLiteral("editor/fontPointSize"), m_editorFontPointSize);
}
