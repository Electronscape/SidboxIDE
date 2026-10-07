#include "mainwindow.h"

#include "codeeditor.h"
#include "optionsdialog.h"
#include "findreplacedialog.h"
#include "projectsettingsdialog.h"
#include "ui_mainwindow.h"

#include <algorithm>
#include <QSet>
#include <QAction>
#include <QApplication>
#include <QClipboard>
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
#include <QMetaObject>
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
#include <QTextBrowser>
#include <QTextCursor>
#include <QTextDocument>
#include <QTimer>
#include <QToolBar>
#include <QVBoxLayout>
#include <QStandardPaths>
#include <QStyle>
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


struct SourceVariableSymbol
{
    QString name;
    int line = -1;
    QString typeName;

    /*
     * Display-only array suffix, e.g. "[]", "[256]" or "[16][32]".
     * Keep this separate from name so Ctrl+Click/type/member lookup still uses
     * the real C identifier ("background", not "background[256]").
     */
    QString arraySuffix;

    /*
     * True for declarations such as:
     *
     *     extern const uint8_t background[];
     *
     * Ctrl+Click should prefer the real storage definition in another file
     * rather than stopping on this declaration.
     */
    bool externDeclaration = false;
};

struct SourceNamedSymbol
{
    QString name;
    int line = -1;
    QList<SourceVariableSymbol> members;
};

struct SourceFunctionSymbol
{
    QString signature;
    int line = -1;
    int endLine = -1;
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

int inferredBraceArrayElementCount(const QString &declarator)
{
    /*
     * Count elements in the outermost brace initializer only.
     *
     * Examples:
     *   { 1, 2, 3 }                  -> 3
     *   { {1,2}, {3,4} }            -> 2
     *
     * The parser calls this with sanitized C source, so comments and quoted
     * strings have already been blanked and commas inside them cannot confuse
     * the count.
     */
    const int equals = declarator.indexOf(QLatin1Char('='));
    if (equals < 0) {
        return -1;
    }

    const int openBrace = declarator.indexOf(QLatin1Char('{'), equals + 1);
    if (openBrace < 0) {
        return -1;
    }

    int depth = 0;
    int elementCount = 0;
    bool elementHasContent = false;

    for (int i = openBrace + 1; i < declarator.size(); ++i) {
        const QChar ch = declarator.at(i);

        if (ch == QLatin1Char('{')) {
            ++depth;
            elementHasContent = true;
            continue;
        }

        if (ch == QLatin1Char('}')) {
            if (depth > 0) {
                --depth;
                elementHasContent = true;
                continue;
            }

            // Closing brace of the outer initializer.
            if (elementHasContent) {
                ++elementCount;
            }
            return elementCount;
        }

        if (ch == QLatin1Char(',')
            && depth == 0) {
            if (elementHasContent) {
                ++elementCount;
                elementHasContent = false;
            }
            continue;
        }

        if (!ch.isSpace()) {
            elementHasContent = true;
        }
    }

    return -1;
}

QString arraySuffixFromDeclarator(const QString &declarator,
                                  const QString &variableName)
{
    if (variableName.isEmpty()) {
        return {};
    }

    QString beforeInitializer = declarator;

    /*
     * Find '=' only at top level. An array bound may itself contain
     * parentheses/brackets, so do not simply use indexOf('=').
     */
    int nesting = 0;
    int equals = -1;
    for (int i = 0; i < beforeInitializer.size(); ++i) {
        const QChar ch = beforeInitializer.at(i);

        if (ch == QLatin1Char('(') || ch == QLatin1Char('[')) {
            ++nesting;
        } else if (ch == QLatin1Char(')') || ch == QLatin1Char(']')) {
            nesting = qMax(0, nesting - 1);
        } else if (ch == QLatin1Char('=') && nesting == 0) {
            equals = i;
            break;
        }
    }

    if (equals >= 0) {
        beforeInitializer = beforeInitializer.left(equals);
    }

    const QRegularExpression arrayExpression(
        QStringLiteral(
            R"(\b%1\b\s*((?:\[[^\]]*\]\s*)+)$)")
            .arg(QRegularExpression::escape(variableName)));

    const QRegularExpressionMatch match =
        arrayExpression.match(beforeInitializer.trimmed());

    if (!match.hasMatch()) {
        return {};
    }

    QString suffix = match.captured(1);
    suffix.remove(QRegularExpression(QStringLiteral("\\s+")));

    /*
     * If the first dimension was left empty and this declaration has a brace
     * initializer, show the element count that C would infer.
     *
     *     const int8_t background[] = { 10, 20, 30 };
     *                               -> background[3]
     *
     * For multidimensional arrays only the first unsized dimension is inferred:
     *
     *     int map[][2] = {{1,2}, {3,4}};
     *                  -> map[2][2]
     */
    if (suffix.startsWith(QStringLiteral("[]"))) {
        const int inferredCount =
            inferredBraceArrayElementCount(declarator);

        if (inferredCount > 0) {
            suffix.replace(
                0,
                2,
                QStringLiteral("[%1]").arg(inferredCount));
        }
    }

    return suffix;
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

QString typeNameFromDeclaration(const QString &statement,
                                const QString &variableName)
{
    if (variableName.isEmpty()) {
        return {};
    }

    QString beforeInitializer = statement;
    const int equals = beforeInitializer.indexOf(QLatin1Char('='));
    if (equals >= 0) {
        beforeInitializer = beforeInitializer.left(equals);
    }

    const QRegularExpression variableExpression(
        QStringLiteral("\\b%1\\b")
            .arg(QRegularExpression::escape(variableName)));

    const int variablePos =
        beforeInitializer.indexOf(variableExpression);

    if (variablePos <= 0) {
        return {};
    }

    QString typePart =
        beforeInitializer.left(variablePos).trimmed();

    // Remove pointer stars and common declaration qualifiers/storage classes.
    typePart.remove(QLatin1Char('*'));

    static const QRegularExpression qualifierExpression(
        QStringLiteral(
            R"(\b(?:const|volatile|restrict|static|extern|register|auto|signed|unsigned|long|short)\b)"));

    typePart.remove(qualifierExpression);
    typePart = typePart.simplified();

    // "struct Foo", "union Foo" and "enum Foo" should resolve to Foo.
    static const QRegularExpression taggedTypeExpression(
        QStringLiteral(R"(^(?:struct|union|enum)\s+([A-Za-z_][A-Za-z0-9_]*)$)"));

    const QRegularExpressionMatch taggedMatch =
        taggedTypeExpression.match(typePart);

    if (taggedMatch.hasMatch()) {
        return taggedMatch.captured(1);
    }

    // For a typedef alias (Vec3, Face, etc.) the final identifier is the type.
    static const QRegularExpression finalIdentifierExpression(
        QStringLiteral(R"(([A-Za-z_][A-Za-z0-9_]*)\s*$)"));

    const QRegularExpressionMatch finalMatch =
        finalIdentifierExpression.match(typePart);

    return finalMatch.hasMatch()
        ? finalMatch.captured(1)
        : QString();
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

    /*
     * Member assignments are expressions, not declarations:
     *
     *     fish.y = 3;
     *     fish->y = 3;
     *
     * Without this check the lightweight declaration parser sees the final
     * member name (y) and mistakes the object name (fish) for a type.
     */
    const QString declarationPrefix =
        firstBeforeInitializer.left(firstNamePos).trimmed();

    if (declarationPrefix.contains(QLatin1Char('.'))
        || declarationPrefix.contains(QStringLiteral("->"))) {
        return symbols;
    }

    // Function calls/prototypes are not variables. Function-pointer declarations are
    // intentionally skipped by this light-weight browser rather than guessed wrongly.
    if (text.contains(QLatin1Char('(')) || text.contains(QLatin1Char(')'))) {
        return symbols;
    }

    const int line = sourceLineForOffset(wholeSource, statementOffset);
    const QString declarationType =
        typeNameFromDeclaration(text, firstName);

    // If there is no identifiable type before the variable name, this was an
    // expression (for example *ptr = value), not a declaration.
    if (declarationType.isEmpty()) {
        return symbols;
    }

    const bool isExternDeclaration =
        QRegularExpression(QStringLiteral(R"(\bextern\b)"))
            .match(text)
            .hasMatch();

    for (const QString &declarator : declarators) {
        const QString name = variableNameFromDeclarator(declarator);
        if (!name.isEmpty()) {
            symbols.append({
                name,
                line,
                declarationType,
                arraySuffixFromDeclarator(declarator, name),
                isExternDeclaration
            });
        }
    }
    return symbols;
}

/*
 * Find C array declarations which use brace initialisers, for example:
 *
 *     const int8_t background[] = {
 *         1, 2, 3, 4
 *     };
 *
 * The normal lightweight declaration regexp deliberately stops at braces, so
 * these declarations used to disappear from the Globals/Locals tree. Scan
 * them separately and feed the complete declaration through the same
 * variable/type parser used for ordinary declarations.
 */
QList<SourceVariableSymbol> braceInitialisedArraySymbolsInRange(
    const QString &sanitized,
    const QString &wholeSource,
    int start,
    int end)
{
    QList<SourceVariableSymbol> symbols;

    if (start < 0 || end <= start || start >= sanitized.size()) {
        return symbols;
    }

    const int boundedEnd = qMin(end, sanitized.size());

    static const QRegularExpression arrayStartExpression(
        QStringLiteral(
            R"((?:^|[\n;{}])\s*((?:(?:const|volatile|static|extern|register)\s+)*(?:(?:struct|union|enum)\s+)?[A-Za-z_][A-Za-z0-9_]*(?:\s*\*)*\s+[A-Za-z_][A-Za-z0-9_]*\s*\[[^\]]*\]\s*=\s*\{))"),
        QRegularExpression::MultilineOption);

    int searchFrom = start;

    while (searchFrom < boundedEnd) {
        const QRegularExpressionMatch match =
            arrayStartExpression.match(
                sanitized,
                searchFrom,
                QRegularExpression::NormalMatch,
                QRegularExpression::NoMatchOption);

        if (!match.hasMatch() || match.capturedStart(1) >= boundedEnd) {
            break;
        }

        const int declarationStart = match.capturedStart(1);
        const int openBrace =
            sanitized.indexOf(QLatin1Char('{'), match.capturedStart(1));

        if (openBrace < 0 || openBrace >= boundedEnd) {
            break;
        }

        const int closeBrace = matchingBracePosition(sanitized, openBrace);
        if (closeBrace < 0 || closeBrace >= boundedEnd) {
            break;
        }

        int semicolon = closeBrace + 1;
        while (semicolon < boundedEnd
               && sanitized.at(semicolon).isSpace()) {
            ++semicolon;
        }

        if (semicolon >= boundedEnd
            || sanitized.at(semicolon) != QLatin1Char(';')) {
            searchFrom = closeBrace + 1;
            continue;
        }

        const QString declaration =
            sanitized.mid(
                declarationStart,
                semicolon - declarationStart);

        const auto found =
            variableSymbolsFromStatement(
                declaration,
                declarationStart,
                wholeSource);

        for (const SourceVariableSymbol &symbol : found) {
            bool duplicate = false;
            for (const SourceVariableSymbol &existing : symbols) {
                if (existing.name == symbol.name
                    && existing.line == symbol.line) {
                    duplicate = true;
                    break;
                }
            }

            if (!duplicate) {
                symbols.append(symbol);
            }
        }

        searchFrom = semicolon + 1;
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

    /*
     * Brace-initialised arrays need a separate pass because the ordinary
     * declaration regexp above intentionally excludes braces.
     */
    const auto arraySymbols =
        braceInitialisedArraySymbolsInRange(
            sanitized,
            wholeSource,
            start,
            boundedEnd);

    for (const SourceVariableSymbol &symbol : arraySymbols) {
        bool duplicate = false;
        for (const SourceVariableSymbol &existing : symbols) {
            if (existing.name == symbol.name
                && existing.line == symbol.line) {
                duplicate = true;
                break;
            }
        }

        if (!duplicate) {
            symbols.append(symbol);
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

    auto appendUnique = [&symbols](const QString &name,
                                   int line,
                                   const QList<SourceVariableSymbol> &members = {}) {
        if (name.isEmpty()) {
            return;
        }

        for (SourceNamedSymbol &existing : symbols) {
            if (existing.name == name && existing.line == line) {
                if (existing.members.isEmpty() && !members.isEmpty()) {
                    existing.members = members;
                }
                return;
            }
        }

        symbols.append({name, line, members});
    };

    static const QRegularExpression typedefStartExpression(
        QStringLiteral(R"(\btypedef\b)"));

    int searchFrom = 0;
    while (searchFrom < sanitized.size()) {
        const QRegularExpressionMatch startMatch =
            typedefStartExpression.match(sanitized, searchFrom);

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

        const QString declaration =
            sanitized.mid(typedefStart, typedefEnd - typedefStart + 1);

        QList<SourceVariableSymbol> members;
        const int relativeOpenBrace = declaration.indexOf(QLatin1Char('{'));
        if (relativeOpenBrace >= 0) {
            const int openBrace = typedefStart + relativeOpenBrace;
            const int closeBrace = matchingBracePosition(sanitized, openBrace);

            if (closeBrace > openBrace && closeBrace <= typedefEnd) {
                members = variableSymbolsInRange(
                    sanitized,
                    source,
                    openBrace + 1,
                    closeBrace);
            }
        }

        static const QRegularExpression aliasExpression(
            QStringLiteral(R"(([A-Za-z_][A-Za-z0-9_]*)\s*;$)"));

        const QRegularExpressionMatch aliasMatch =
            aliasExpression.match(declaration);

        if (aliasMatch.hasMatch()) {
            const QString alias = aliasMatch.captured(1).trimmed();
            const int aliasOffset =
                typedefStart + aliasMatch.capturedStart(1);

            appendUnique(
                alias,
                sourceLineForOffset(source, aliasOffset),
                members);
        }

        searchFrom = typedefEnd + 1;
    }

    // Named struct / enum / union types, including non-typedef declarations.
    static const QRegularExpression taggedTypeExpression(
        QStringLiteral(
            R"(\b(struct|enum|union)\s+([A-Za-z_][A-Za-z0-9_]*)\s*(?:__attribute__\s*\(\([^\n]*?\)\)\s*)?(?=\{|;))"),
        QRegularExpression::MultilineOption);

    QRegularExpressionMatchIterator taggedIterator =
        taggedTypeExpression.globalMatch(sanitized);

    while (taggedIterator.hasNext()) {
        const QRegularExpressionMatch match = taggedIterator.next();
        const QString name = match.captured(2).trimmed();

        QList<SourceVariableSymbol> members;
        const int openBrace = sanitized.indexOf(
            QLatin1Char('{'),
            match.capturedEnd(0));

        if (openBrace >= 0) {
            // Do not accidentally attach a later unrelated brace to a
            // forward declaration such as "struct Foo;".
            const int semicolon = sanitized.indexOf(
                QLatin1Char(';'),
                match.capturedEnd(0));

            if (semicolon < 0 || openBrace < semicolon) {
                const int closeBrace =
                    matchingBracePosition(sanitized, openBrace);

                if (closeBrace > openBrace) {
                    members = variableSymbolsInRange(
                        sanitized,
                        source,
                        openBrace + 1,
                        closeBrace);
                }
            }
        }

        appendUnique(
            name,
            sourceLineForOffset(source, match.capturedStart(2)),
            members);
    }

    return symbols;
}

void maskTypeDeclarations(QString *text)
{
    if (!text) {
        return;
    }

    auto blankRange = [text](int start, int end) {
        if (start < 0 || end < start) {
            return;
        }

        const int boundedEnd = qMin(end, text->size() - 1);
        for (int i = start; i <= boundedEnd; ++i) {
            if (text->at(i) != QLatin1Char('\n')) {
                (*text)[i] = QLatin1Char(' ');
            }
        }
    };

    // Mask complete typedef declarations, respecting braces/parentheses so
    // member semicolons inside a struct do not terminate the declaration.
    static const QRegularExpression typedefStartExpression(
        QStringLiteral(R"(\btypedef\b)"));

    int searchFrom = 0;
    while (searchFrom < text->size()) {
        const QRegularExpressionMatch match =
            typedefStartExpression.match(*text, searchFrom);

        if (!match.hasMatch()) {
            break;
        }

        int braces = 0;
        int parens = 0;
        int brackets = 0;
        int end = -1;

        for (int i = match.capturedEnd(); i < text->size(); ++i) {
            const QChar ch = text->at(i);

            if (ch == QLatin1Char('{')) {
                ++braces;
            } else if (ch == QLatin1Char('}')) {
                braces = qMax(0, braces - 1);
            } else if (ch == QLatin1Char('(')) {
                ++parens;
            } else if (ch == QLatin1Char(')')) {
                parens = qMax(0, parens - 1);
            } else if (ch == QLatin1Char('[')) {
                ++brackets;
            } else if (ch == QLatin1Char(']')) {
                brackets = qMax(0, brackets - 1);
            } else if (ch == QLatin1Char(';')
                       && braces == 0
                       && parens == 0
                       && brackets == 0) {
                end = i;
                break;
            }
        }

        if (end < 0) {
            break;
        }

        blankRange(match.capturedStart(), end);
        searchFrom = end + 1;
    }

    // Also mask standalone named struct/enum/union bodies:
    //     struct Foo { int x; };
    static const QRegularExpression taggedBodyExpression(
        QStringLiteral(R"(\b(struct|enum|union)\s+[A-Za-z_][A-Za-z0-9_]*[^\n;{]*\{)"),
        QRegularExpression::MultilineOption);

    searchFrom = 0;
    while (searchFrom < text->size()) {
        const QRegularExpressionMatch match =
            taggedBodyExpression.match(*text, searchFrom);

        if (!match.hasMatch()) {
            break;
        }

        const int openBrace =
            text->indexOf(QLatin1Char('{'), match.capturedStart());

        if (openBrace < 0) {
            break;
        }

        const int closeBrace =
            matchingBracePosition(*text, openBrace);

        if (closeBrace < 0) {
            break;
        }

        int end = closeBrace;
        const int semicolon =
            text->indexOf(QLatin1Char(';'), closeBrace + 1);

        if (semicolon >= 0) {
            end = semicolon;
        }

        blankRange(match.capturedStart(), end);
        searchFrom = end + 1;
    }
}

SourceSymbolTable parseSourceSymbols(const QString &source)
{
    SourceSymbolTable table;
    table.defines = defineSymbolsFromSource(source);
    table.types = typeSymbolsFromSource(source);
    const QString sanitized = sanitizedCSource(source);
    QString globalsOnly = sanitized;

    // Struct/typedef members are fields of their type, not globals.
    maskTypeDeclarations(&globalsOnly);

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
        function.endLine = sourceLineForOffset(source, closingBrace);

        const QStringList parameterParts = splitApiArgumentList(match.captured(3));
        for (const QString &parameter : parameterParts) {
            const QString name = readableApiArgumentName(parameter, function.parameters.size());
            QString cleanName = name;
            cleanName.remove(QLatin1Char('*'));
            cleanName = cleanName.trimmed();
            if (!cleanName.isEmpty()) {
                function.parameters.append({
                    cleanName,
                    function.line,
                    typeNameFromDeclaration(parameter, cleanName),
                    arraySuffixFromDeclarator(parameter, cleanName)
                });
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

QString variableTypeInTable(const SourceSymbolTable &table,
                            const QString &variableName,
                            int usageLine,
                            bool includeLocalScope)
{
    if (includeLocalScope && usageLine >= 0) {
        for (const SourceFunctionSymbol &function : table.functions) {
            if (usageLine < function.line
                || (function.endLine >= 0 && usageLine > function.endLine)) {
                continue;
            }

            // Prefer the nearest local declaration visible before this use.
            int bestLine = -1;
            QString bestType;

            for (const SourceVariableSymbol &local : function.locals) {
                if (local.name == variableName
                    && local.line <= usageLine
                    && local.line > bestLine) {
                    bestLine = local.line;
                    bestType = local.typeName;
                }
            }

            if (!bestType.isEmpty()) {
                return bestType;
            }

            for (const SourceVariableSymbol &parameter : function.parameters) {
                if (parameter.name == variableName) {
                    return parameter.typeName;
                }
            }

            break;
        }
    }

    for (const SourceVariableSymbol &global : table.globals) {
        if (global.name == variableName) {
            return global.typeName;
        }
    }

    return {};
}

QStringList membersForTypeInTable(const SourceSymbolTable &table,
                                  const QString &typeName)
{
    for (const SourceNamedSymbol &type : table.types) {
        if (type.name != typeName) {
            continue;
        }

        QStringList members;
        for (const SourceVariableSymbol &member : type.members) {
            if (!member.name.isEmpty()) {
                members.append(member.name);
            }
        }

        members.removeDuplicates();
        members.sort(Qt::CaseInsensitive);
        return members;
    }

    return {};
}

QString sourceFunctionName(const QString &signature)
{
    const int paren = signature.indexOf(QLatin1Char('('));
    return paren >= 0 ? signature.left(paren).trimmed() : signature.trimmed();
}

int definitionLineInTable(const SourceSymbolTable &table,
                          const QString &symbol,
                          int usageLine,
                          bool includeLocalScope,
                          bool includeExternGlobals = true)
{
    if (includeLocalScope && usageLine >= 0) {
        for (const SourceFunctionSymbol &function : table.functions) {
            if (usageLine < function.line
                || (function.endLine >= 0 && usageLine > function.endLine)) {
                continue;
            }

            // A local variable is the most specific definition. Prefer the
            // nearest declaration at or before the clicked use.
            int bestLocalLine = -1;
            for (const SourceVariableSymbol &local : function.locals) {
                if (local.name == symbol
                    && local.line <= usageLine
                    && local.line > bestLocalLine) {
                    bestLocalLine = local.line;
                }
            }
            if (bestLocalLine >= 0) {
                return bestLocalLine;
            }

            for (const SourceVariableSymbol &parameter : function.parameters) {
                if (parameter.name == symbol) {
                    return parameter.line;
                }
            }
            break;
        }
    }

    // Types first makes "struct Foo" / typedef aliases particularly useful.
    for (const SourceNamedSymbol &type : table.types) {
        if (type.name == symbol) {
            return type.line;
        }
    }

    for (const SourceFunctionSymbol &function : table.functions) {
        if (sourceFunctionName(function.signature) == symbol) {
            return function.line;
        }
    }

    for (const SourceVariableSymbol &global : table.globals) {
        if (global.name == symbol
            && (includeExternGlobals || !global.externDeclaration)) {
            return global.line;
        }
    }

    for (const SourceNamedSymbol &define : table.defines) {
        if (define.name == symbol) {
            return define.line;
        }
    }

    return -1;
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
    , m_findReplaceDialog(nullptr)
    , m_compilerProcess(new QProcess(this))
    , m_projectAnalysisTimer(new QTimer(this))
    , m_buildStep(BuildStep::None)
    , m_projectType(GuiProjectType)
    , m_modSizeKb(0)
    , m_editorFontPointSize(10)
    , m_compilerOptimization(QStringLiteral("-Ofast"))
    , m_compilerSuppressWarnings(true)
    , m_compilerWall(false)
    , m_compilerWextra(false)
    , m_compilerFunctionSections(true)
    , m_compilerDataSections(true)
    , m_compilerStackUsage(true)
    , m_theme(defaultIDETheme())
{
    ui->setupUi(this);
    loadOptions();
    setupInterface();
    refreshApiCatalog();

    /*
     * Project-wide function/type discovery scans multiple source files.
     * Running it on every single keystroke makes large resource-heavy projects
     * feel frozen. Coalesce bursts of edits into one refresh shortly after the
     * user stops typing.
     */
    m_projectAnalysisTimer->setSingleShot(true);
    m_projectAnalysisTimer->setInterval(140);
    connect(m_projectAnalysisTimer, &QTimer::timeout, this, [this]() {
        refreshFunctionCompletions();
        refreshSymbolTree();
    });

    connect(m_compilerProcess, &QProcess::readyReadStandardOutput, this, [this]() {
        appendOutputText(QString::fromLocal8Bit(m_compilerProcess->readAllStandardOutput()), OutputKind::Normal);
    });
    connect(m_compilerProcess, &QProcess::readyReadStandardError, this, [this]() {
        const QString text =
            QString::fromLocal8Bit(m_compilerProcess->readAllStandardError());

        processCompilerStderrChunk(text);
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
            background-color: #07090d;
            color: #f2f2f2;
            border: 2px solid #2858A8;
            padding: 5px 5px;
            font-size: 12px;
            font-weight: 500;
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

    //QIcon findReplaceIcon = QIcon::fromTheme(QStringLiteral("edit-find-replace"));
    //if (findReplaceIcon.isNull()) {
        //findReplaceIcon = QIcon::fromTheme(QStringLiteral("edit-find"));
    //}

    QAction *findReplaceAction = toolBar->addAction(QIcon(":/icons/search_term.png"), tr("Find / Replace"));
    findReplaceAction->setShortcut(QKeySequence(QStringLiteral("Ctrl+Shift+F")));

    QAction *apiCheatSheetAction =
        toolBar->addAction(tr("Cheat Sheet [F8]"));
    apiCheatSheetAction->setShortcut(Qt::Key_F8);
    apiCheatSheetAction->setToolTip(
        tr("Open the searchable Sidbox API Cheat Sheet"));

    QAction *findCurrentWordAction = new QAction(tr("Find Current Word"), this);
    findCurrentWordAction->setShortcuts({
        QKeySequence(QStringLiteral("Ctrl+F")),
        QKeySequence(QStringLiteral("F3"))
    });
    addAction(findCurrentWordAction);

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
    connect(findReplaceAction, &QAction::triggered, this, &MainWindow::showFindReplace);
    connect(apiCheatSheetAction, &QAction::triggered,
            this, &MainWindow::showApiCheatSheet);
    connect(findCurrentWordAction, &QAction::triggered,
            this, &MainWindow::showFindReplaceForCurrentWord);
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
    applyTheme();
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

    // Compiler defaults for a brand-new project.
    m_compilerOptimization = QStringLiteral("-Ofast");
    m_compilerSuppressWarnings = true;
    m_compilerWall = false;
    m_compilerWextra = false;
    m_compilerFunctionSections = true;
    m_compilerDataSections = true;
    m_compilerStackUsage = true;
    m_extraCompilerFlags.clear();
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
    int newFontPointSize = m_editorFontPointSize;
    IDETheme newTheme = m_theme;

    /*
     * Keep the dialog in its own scope so it and all of its colour-picker /
     * tab children are destroyed before we replace the MainWindow stylesheet.
     */
    {
        OptionsDialog dialog(this);
        dialog.setEditorFontPointSize(m_editorFontPointSize);
        dialog.setTheme(m_theme);

        if (dialog.exec() != QDialog::Accepted) {
            return;
        }

        newFontPointSize = dialog.editorFontPointSize();
        newTheme = dialog.theme();
    }

    m_editorFontPointSize = newFontPointSize;
    m_theme = newTheme;

    saveOptions();
    applyTheme();
    applyEditorFont();

    statusBar()->showMessage(tr("Options saved"), 3000);
}

void MainWindow::showFindReplace()
{
    if (!m_findReplaceDialog) {
        m_findReplaceDialog = new FindReplaceDialog(this);
        m_findReplaceDialog->setAttribute(Qt::WA_DeleteOnClose, true);

        connect(m_findReplaceDialog, &QObject::destroyed,
                this, [this]() {
                    m_findReplaceDialog = nullptr;
                });

        connect(m_findReplaceDialog, &FindReplaceDialog::findAllRequested,
                this, [this]() {
                    if (!m_findReplaceDialog) {
                        return;
                    }

                    const QList<ProjectSearchResult> results =
                        findInProject(
                            m_findReplaceDialog->findText(),
                            m_findReplaceDialog->matchCase(),
                            m_findReplaceDialog->wholeWord());

                    m_findReplaceDialog->setResults(results);

                    statusBar()->showMessage(
                        tr("%1 match(es) found")
                            .arg(results.size()),
                        3000);
                });

        connect(m_findReplaceDialog, &FindReplaceDialog::resultActivated,
                this, [this](int index) {
                    if (!m_findReplaceDialog
                        || index < 0
                        || index >= m_findReplaceDialog->results().size()) {
                        return;
                    }

                    jumpToProjectSearchResult(
                        m_findReplaceDialog->results().at(index));
                });

        connect(m_findReplaceDialog, &FindReplaceDialog::replaceSelectedRequested,
                this, [this]() {
                    if (!m_findReplaceDialog) {
                        return;
                    }

                    QList<ProjectSearchResult> selected;
                    for (const int index :
                         m_findReplaceDialog->selectedResultIndexes()) {
                        if (index >= 0
                            && index < m_findReplaceDialog->results().size()) {
                            selected.append(
                                m_findReplaceDialog->results().at(index));
                        }
                    }

                    if (selected.isEmpty()) {
                        return;
                    }

                    if (!replaceProjectResults(
                            selected,
                            m_findReplaceDialog->replaceText())) {
                        return;
                    }

                    const QList<ProjectSearchResult> refreshed =
                        findInProject(
                            m_findReplaceDialog->findText(),
                            m_findReplaceDialog->matchCase(),
                            m_findReplaceDialog->wholeWord());

                    m_findReplaceDialog->setResults(refreshed);

                    statusBar()->showMessage(
                        tr("%1 selected replacement(s) made")
                            .arg(selected.size()),
                        3000);
                });

        connect(m_findReplaceDialog, &FindReplaceDialog::replaceAllRequested,
                this, [this]() {
                    if (!m_findReplaceDialog
                        || m_findReplaceDialog->results().isEmpty()) {
                        return;
                    }

                    const QList<ProjectSearchResult> allResults =
                        m_findReplaceDialog->results();

                    QSet<QString> files;
                    for (const ProjectSearchResult &result : allResults) {
                        files.insert(QFileInfo(result.filePath).absoluteFilePath());
                    }

                    const QMessageBox::StandardButton answer =
                        QMessageBox::question(
                            this,
                            tr("Replace All"),
                            tr("Replace %1 occurrence(s) in %2 file(s)?\n\n"
                               "Open files will remain as unsaved editor changes. "
                               "Files which are not open will be written to disk.")
                                .arg(allResults.size())
                                .arg(files.size()),
                            QMessageBox::Yes | QMessageBox::Cancel,
                            QMessageBox::Cancel);

                    if (answer != QMessageBox::Yes) {
                        return;
                    }

                    if (!replaceProjectResults(
                            allResults,
                            m_findReplaceDialog->replaceText())) {
                        return;
                    }

                    const QList<ProjectSearchResult> refreshed =
                        findInProject(
                            m_findReplaceDialog->findText(),
                            m_findReplaceDialog->matchCase(),
                            m_findReplaceDialog->wholeWord());

                    m_findReplaceDialog->setResults(refreshed);

                    statusBar()->showMessage(
                        tr("%1 replacement(s) made")
                            .arg(allResults.size()),
                        4000);
                });
    }

    m_findReplaceDialog->show();
    m_findReplaceDialog->raise();
    m_findReplaceDialog->activateWindow();
}

void MainWindow::showFindReplaceForCurrentWord()
{
    QString word;

    if (CodeEditor *editor = activeEditor()) {
        QTextCursor cursor = editor->textCursor();

        if (cursor.hasSelection()) {
            word = cursor.selectedText().trimmed();
        } else {
            cursor.select(QTextCursor::WordUnderCursor);
            word = cursor.selectedText().trimmed();
        }
    }

    showFindReplace();

    if (!m_findReplaceDialog) {
        return;
    }

    if (!word.isEmpty()) {
        m_findReplaceDialog->setFindText(word);
    } else {
        m_findReplaceDialog->focusFindText();
    }
}


namespace {

QString apiCheatSheetCategory(const QString &apiRoot,
                              const QString &filePath)
{
    QString relative =
        QDir(apiRoot).relativeFilePath(filePath);

    relative = QDir::fromNativeSeparators(relative);

    const int slash = relative.indexOf(QLatin1Char('/'));
    QString category =
        slash >= 0
            ? relative.left(slash)
            : QFileInfo(relative).completeBaseName();

    if (category.compare(QStringLiteral("apis"), Qt::CaseInsensitive) == 0
        || category.compare(QStringLiteral("syscalls"), Qt::CaseInsensitive) == 0
        || category.compare(QStringLiteral("applet"), Qt::CaseInsensitive) == 0) {
        category = QStringLiteral("Core");
    }

    if (!category.isEmpty()) {
        category[0] = category.at(0).toUpper();
    }

    return category.isEmpty() ? QStringLiteral("Other") : category;
}

QString cleanApiComment(QString comment)
{
    comment.replace(QStringLiteral("/**"), QString());
    comment.replace(QStringLiteral("/*"), QString());
    comment.replace(QStringLiteral("*/"), QString());

    QStringList cleaned;
    const QStringList lines = comment.split(QLatin1Char('\n'));

    for (QString line : lines) {
        line = line.trimmed();

        if (line.startsWith(QLatin1Char('*'))) {
            line.remove(0, 1);
            line = line.trimmed();
        }
        if (line.startsWith(QStringLiteral("//"))) {
            line.remove(0, 2);
            line = line.trimmed();
        }

        if (line.startsWith(QStringLiteral("@brief"))) {
            line.remove(0, 6);
            line = line.trimmed();
        }

        /*
         * Keep useful prose, but skip documentation tags that are better
         * represented by the function signature itself.
         */
        if (line.startsWith(QLatin1Char('@'))) {
            continue;
        }

        if (!line.isEmpty()) {
            cleaned.append(line);
        }
    }

    return cleaned.join(QLatin1Char(' ')).simplified();
}

QString apiCommentBeforeLine(const QString &source, int zeroBasedLine)
{
    if (zeroBasedLine < 0) {
        return {};
    }

    const QStringList lines = source.split(QLatin1Char('\n'));
    if (zeroBasedLine >= lines.size()) {
        return {};
    }

    int i = zeroBasedLine - 1;

    while (i >= 0 && lines.at(i).trimmed().isEmpty()) {
        --i;
    }

    if (i < 0) {
        return {};
    }

    QStringList commentLines;

    // Consecutive // comments directly above the declaration.
    if (lines.at(i).trimmed().startsWith(QStringLiteral("//"))) {
        while (i >= 0
               && lines.at(i).trimmed().startsWith(QStringLiteral("//"))) {
            commentLines.prepend(lines.at(i));
            --i;
        }
        return cleanApiComment(commentLines.join(QLatin1Char('\n')));
    }

    // /* ... */ or /** ... */ block immediately above the declaration.
    if (lines.at(i).contains(QStringLiteral("*/"))) {
        while (i >= 0) {
            commentLines.prepend(lines.at(i));

            if (lines.at(i).contains(QStringLiteral("/*"))) {
                break;
            }
            --i;
        }

        if (!commentLines.isEmpty()
            && commentLines.first().contains(QStringLiteral("/*"))) {
            return cleanApiComment(commentLines.join(QLatin1Char('\n')));
        }
    }

    return {};
}

QString firstDeclarationLineContaining(const QString &source,
                                       const QString &symbol,
                                       int *lineOut)
{
    if (lineOut) {
        *lineOut = -1;
    }

    const QRegularExpression symbolExpression(
        QStringLiteral(R"(\b%1\b)")
            .arg(QRegularExpression::escape(symbol)));

    const QStringList lines = source.split(QLatin1Char('\n'));

    for (int i = 0; i < lines.size(); ++i) {
        const QString trimmed = lines.at(i).trimmed();

        if (trimmed.startsWith(QStringLiteral("//"))
            || trimmed.startsWith(QLatin1Char('*'))
            || trimmed.startsWith(QStringLiteral("/*"))) {
            continue;
        }

        if (!symbolExpression.match(lines.at(i)).hasMatch()) {
            continue;
        }

        if (lineOut) {
            *lineOut = i;
        }

        /*
         * Gather a short multi-line declaration/prototype, stopping at ';' or
         * '{'. This keeps the Cheat Sheet useful for wrapped API prototypes.
         */
        QString declaration = trimmed;

        for (int j = i + 1;
             j < lines.size()
             && j <= i + 6
             && !declaration.contains(QLatin1Char(';'))
             && !declaration.contains(QLatin1Char('{'));
             ++j) {
            declaration += QLatin1Char(' ');
            declaration += lines.at(j).trimmed();
        }

        return declaration.simplified();
    }

    return {};
}

}

void MainWindow::showApiCheatSheet()
{
    if (!m_editorTabs) {
        return;
    }

    /*
     * F8 is context-sensitive: if the caret is sitting on a known Sidbox API
     * identifier, remember it before switching away from the source editor.
     */
    QString requestedSymbol;

    ensureApiCatalog();

    if (auto *editor = activeEditor()) {
        QTextCursor cursor = editor->textCursor();
        cursor.select(QTextCursor::WordUnderCursor);

        const QString candidate = cursor.selectedText().trimmed();
        if (!candidate.isEmpty()
            && apiSyntaxNames().contains(candidate)) {
            requestedSymbol = candidate;
        }
    }

    auto selectCheatSheetSymbol =
        [requestedSymbol](QWidget *page) -> bool {
            if (!page || requestedSymbol.isEmpty()) {
                return false;
            }

            auto *tree =
                page->findChild<QTreeWidget *>(
                    QStringLiteral("apiCheatTree"));
            auto *search =
                page->findChild<QLineEdit *>(
                    QStringLiteral("apiCheatSearch"));

            if (!tree) {
                return false;
            }

            /*
             * A previous search may have hidden the requested symbol. Clear it
             * before selecting the exact API entry.
             */
            if (search && !search->text().isEmpty()) {
                search->clear();
            }

            const QList<QTreeWidgetItem *> matches =
                tree->findItems(
                    requestedSymbol,
                    Qt::MatchExactly | Qt::MatchRecursive,
                    0);

            for (QTreeWidgetItem *item : matches) {
                if (!item || item->childCount() > 0) {
                    continue;
                }

                /*
                 * Keep the tree collapsed by default. Only expand the category
                 * which contains the API symbol requested by F8.
                 */
                tree->collapseAll();

                if (item->parent()) {
                    item->parent()->setExpanded(true);
                }

                tree->setCurrentItem(item);
                tree->scrollToItem(
                    item,
                    QAbstractItemView::PositionAtCenter);
                return true;
            }

            return false;
        };

    /*
     * Reuse the existing Cheat Sheet tab instead of opening duplicates.
     */
    for (int i = 0; i < m_editorTabs->count(); ++i) {
        QWidget *widget = m_editorTabs->widget(i);
        if (widget
            && widget->property("sidboxApiCheatSheet").toBool()) {
            m_editorTabs->setCurrentIndex(i);

            const bool selected =
                selectCheatSheetSymbol(widget);

            if (!selected) {
                if (QLineEdit *search =
                        widget->findChild<QLineEdit *>(
                            QStringLiteral("apiCheatSearch"))) {
                    search->setFocus();
                    search->selectAll();
                }
            }
            return;
        }
    }

    const QString apiRoot =
        QDir(ideLibsPath()).filePath(QStringLiteral("api"));

    if (!QFileInfo::exists(apiRoot)) {
        QMessageBox::information(
            this,
            tr("Cheat Sheet"),
            tr("The Sidbox API folder could not be found:\n%1")
                .arg(QDir::toNativeSeparators(apiRoot)));
        return;
    }

    auto *page = new QWidget(m_editorTabs);
    page->setProperty("sidboxApiCheatSheet", true);

    auto *layout = new QVBoxLayout(page);
    layout->setContentsMargins(8, 8, 8, 8);
    layout->setSpacing(6);

    auto *title = new QLabel(
        tr("Sidbox API Cheat Sheet"),
        page);

    QFont titleFont = title->font();
    titleFont.setBold(true);
    title->setFont(titleFont);

    auto *search = new QLineEdit(page);
    search->setObjectName(QStringLiteral("apiCheatSearch"));
    search->setPlaceholderText(
        tr("Search functions, constants, types, descriptions..."));
    search->setClearButtonEnabled(true);

    auto *splitter = new QSplitter(Qt::Horizontal, page);

    auto *tree = new QTreeWidget(splitter);
    tree->setObjectName(QStringLiteral("apiCheatTree"));
    tree->setHeaderHidden(true);
    tree->setRootIsDecorated(true);
    tree->setAlternatingRowColors(true);
    tree->setMinimumWidth(300);

    auto *detailPane = new QWidget(splitter);
    auto *detailLayout = new QVBoxLayout(detailPane);
    detailLayout->setContentsMargins(8, 0, 0, 0);
    detailLayout->setSpacing(6);

    auto *symbolLabel = new QLabel(tr("Select an API item"), detailPane);
    QFont symbolFont = symbolLabel->font();
    symbolFont.setBold(true);
    symbolLabel->setFont(symbolFont);
    symbolLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);

    auto *signatureLabel = new QLabel(detailPane);
    signatureLabel->setWordWrap(true);
    signatureLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    signatureLabel->setFont(
        QFontDatabase::systemFont(QFontDatabase::FixedFont));

    auto *description = new QTextBrowser(detailPane);
    description->setOpenExternalLinks(false);
    description->setPlaceholderText(
        tr("No API item selected."));
    description->setMinimumHeight(160);

    auto *sourceLabel = new QLabel(detailPane);
    sourceLabel->setWordWrap(true);
    sourceLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);

    auto *buttonRow = new QHBoxLayout;
    auto *openSourceButton =
        new QPushButton(tr("Open Source"), detailPane);
    auto *copyPrototypeButton =
        new QPushButton(tr("Copy Prototype"), detailPane);

    openSourceButton->setEnabled(false);
    copyPrototypeButton->setEnabled(false);

    buttonRow->addWidget(openSourceButton);
    buttonRow->addWidget(copyPrototypeButton);
    buttonRow->addStretch(1);

    detailLayout->addWidget(symbolLabel);
    detailLayout->addWidget(signatureLabel);
    detailLayout->addWidget(description, 1);
    detailLayout->addWidget(sourceLabel);
    detailLayout->addLayout(buttonRow);

    splitter->addWidget(tree);
    splitter->addWidget(detailPane);
    splitter->setStretchFactor(0, 2);
    splitter->setStretchFactor(1, 3);

    layout->addWidget(title);
    layout->addWidget(search);
    layout->addWidget(splitter, 1);

    struct ApiEntry {
        QString name;
        QString signature;
        QString description;
        QString filePath;
        QString category;
        int line = -1;
    };

    QList<ApiEntry> entries;
    const QStringList knownNames = apiSyntaxNames();

    QStringList apiFiles;
    QDirIterator iterator(
        apiRoot,
        {QStringLiteral("*.h"), QStringLiteral("*.c")},
        QDir::Files,
        QDirIterator::Subdirectories);

    while (iterator.hasNext()) {
        apiFiles.append(
            QFileInfo(iterator.next()).absoluteFilePath());
    }

    /*
     * Headers first: they generally contain the public declaration and the
     * documentation comment a Sidbox programmer actually wants to read.
     * Source files still fill gaps and give us something useful for APIs that
     * are only declared/implemented there.
     */
    std::stable_sort(
        apiFiles.begin(),
        apiFiles.end(),
        [](const QString &a, const QString &b) {
            const bool aHeader =
                QFileInfo(a).suffix().compare(
                    QStringLiteral("h"),
                    Qt::CaseInsensitive) == 0;
            const bool bHeader =
                QFileInfo(b).suffix().compare(
                    QStringLiteral("h"),
                    Qt::CaseInsensitive) == 0;

            if (aHeader != bHeader) {
                return aHeader;
            }
            return a.compare(b, Qt::CaseInsensitive) < 0;
        });

    QSet<QString> addedNames;

    for (const QString &name : knownNames) {
        ApiEntry chosen;
        chosen.name = name;

        for (const QString &filePath : std::as_const(apiFiles)) {
            QFile file(filePath);
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                continue;
            }

            const QString source =
                QString::fromUtf8(file.readAll());

            int line = -1;
            const QString declaration =
                firstDeclarationLineContaining(
                    source,
                    name,
                    &line);

            if (line < 0) {
                continue;
            }

            chosen.filePath = filePath;
            chosen.line = line;
            chosen.category =
                apiCheatSheetCategory(apiRoot, filePath);

            const QString catalogTip =
                quickTipForSymbol(name);

            chosen.signature =
                !catalogTip.isEmpty()
                    ? catalogTip
                    : declaration;

            chosen.description =
                apiCommentBeforeLine(source, line);

            /*
             * Prefer a documented match. If the first header declaration has
             * no prose, keep looking for a source definition with a useful
             * comment before accepting the plain declaration.
             */
            if (!chosen.description.isEmpty()) {
                break;
            }
        }

        if (chosen.filePath.isEmpty()) {
            continue;
        }

        if (chosen.description.isEmpty()) {
            chosen.description =
                tr("No description is written in the API source yet. "
                   "Use the prototype and Open Source button to inspect how it works.");
        }

        entries.append(chosen);
        addedNames.insert(name);
    }

    std::sort(
        entries.begin(),
        entries.end(),
        [](const ApiEntry &a, const ApiEntry &b) {
            const int categoryCompare =
                a.category.compare(
                    b.category,
                    Qt::CaseInsensitive);

            if (categoryCompare != 0) {
                return categoryCompare < 0;
            }

            return a.name.compare(
                       b.name,
                       Qt::CaseInsensitive) < 0;
        });

    QHash<QString, QTreeWidgetItem *> categoryItems;

    for (const ApiEntry &entry : std::as_const(entries)) {
        QTreeWidgetItem *category =
            categoryItems.value(entry.category, nullptr);

        if (!category) {
            category = new QTreeWidgetItem(tree);
            category->setText(0, entry.category);
            category->setExpanded(false);
            category->setData(
                0,
                Qt::UserRole + 20,
                QStringLiteral("category"));
            categoryItems.insert(entry.category, category);
        }

        auto *item = new QTreeWidgetItem(category);
        item->setText(0, entry.name);
        item->setToolTip(0, entry.signature);

        item->setData(0, Qt::UserRole, entry.filePath);
        item->setData(0, Qt::UserRole + 1, entry.line);
        item->setData(0, Qt::UserRole + 2, entry.signature);
        item->setData(0, Qt::UserRole + 3, entry.description);
        item->setData(0, Qt::UserRole + 4, entry.category);
        item->setData(0, Qt::UserRole + 5, entry.name);
    }

    auto showItem = [=](QTreeWidgetItem *item) {
        if (!item || item->childCount() > 0) {
            return;
        }

        const QString name =
            item->data(0, Qt::UserRole + 5).toString();
        const QString signature =
            item->data(0, Qt::UserRole + 2).toString();
        const QString explanation =
            item->data(0, Qt::UserRole + 3).toString();
        const QString filePath =
            item->data(0, Qt::UserRole).toString();
        const int line =
            item->data(0, Qt::UserRole + 1).toInt();

        symbolLabel->setText(name);
        signatureLabel->setText(signature);
        description->setPlainText(explanation);

        sourceLabel->setText(
            tr("Source: %1:%2")
                .arg(
                    QDir(apiRoot).relativeFilePath(filePath))
                .arg(line + 1));

        openSourceButton->setProperty(
            "apiFilePath",
            filePath);
        openSourceButton->setProperty(
            "apiLine",
            line);
        copyPrototypeButton->setProperty(
            "apiPrototype",
            signature);

        openSourceButton->setEnabled(
            !filePath.isEmpty() && line >= 0);
        copyPrototypeButton->setEnabled(
            !signature.isEmpty());
    };

    connect(tree, &QTreeWidget::currentItemChanged,
            page,
            [showItem](QTreeWidgetItem *current,
                       QTreeWidgetItem *) {
                showItem(current);
            });

    connect(tree, &QTreeWidget::itemDoubleClicked,
            page,
            [this](QTreeWidgetItem *item, int) {
                if (!item || item->childCount() > 0) {
                    return;
                }

                const QString filePath =
                    item->data(
                        0,
                        Qt::UserRole).toString();
                const int line =
                    item->data(
                        0,
                        Qt::UserRole + 1).toInt();

                openApiReference(filePath, line);
            });

    connect(openSourceButton, &QPushButton::clicked,
            page,
            [this, openSourceButton]() {
                const QString filePath =
                    openSourceButton
                        ->property("apiFilePath")
                        .toString();
                const int line =
                    openSourceButton
                        ->property("apiLine")
                        .toInt();

                if (!filePath.isEmpty()) {
                    openApiReference(filePath, line);
                }
            });

    connect(copyPrototypeButton, &QPushButton::clicked,
            page,
            [copyPrototypeButton]() {
                const QString prototype =
                    copyPrototypeButton
                        ->property("apiPrototype")
                        .toString();

                if (!prototype.isEmpty()) {
                    QApplication::clipboard()
                        ->setText(prototype);
                }
            });

    connect(search, &QLineEdit::textChanged,
            page,
            [tree](const QString &text) {
                const QString needle =
                    text.trimmed();

                for (int i = 0;
                     i < tree->topLevelItemCount();
                     ++i) {
                    QTreeWidgetItem *category =
                        tree->topLevelItem(i);

                    bool categoryHasMatch = false;

                    for (int j = 0;
                         j < category->childCount();
                         ++j) {
                        QTreeWidgetItem *item =
                            category->child(j);

                        const QString searchable =
                            item->text(0)
                            + QLatin1Char(' ')
                            + item->data(
                                  0,
                                  Qt::UserRole + 2).toString()
                            + QLatin1Char(' ')
                            + item->data(
                                  0,
                                  Qt::UserRole + 3).toString()
                            + QLatin1Char(' ')
                            + item->data(
                                  0,
                                  Qt::UserRole + 4).toString();

                        const bool match =
                            needle.isEmpty()
                            || searchable.contains(
                                needle,
                                Qt::CaseInsensitive);

                        item->setHidden(!match);

                        if (match) {
                            categoryHasMatch = true;
                        }
                    }

                    category->setHidden(
                        !categoryHasMatch);

                    if (!needle.isEmpty()) {
                        category->setExpanded(true);
                    } else {
                        category->setExpanded(false);
                    }
                }
            });

    const int index =
        m_editorTabs->addTab(
            page,
            tr("Cheat Sheet"));

    m_editorTabs->setTabToolTip(
        index,
        tr("F8 — searchable Sidbox API Cheat Sheet"));

    m_editorTabs->setCurrentIndex(index);

    tree->collapseAll();

    const bool selected =
        selectCheatSheetSymbol(page);

    if (!selected) {
        search->setFocus();
    }

    statusBar()->showMessage(
        tr("Sidbox API Cheat Sheet ready — %1 items")
            .arg(entries.size()),
        3000);
}

void MainWindow::showProjectSettings()
{
    ProjectSettingsDialog dialog(this);
    dialog.setProjectType(m_projectType);
    dialog.setModSizeKb(m_modSizeKb);
    dialog.setCustomLinkerScriptPath(m_linkerScriptPath);
    dialog.setDefaultLinkerScriptPaths(
        defaultLinkerScriptPath(GuiProjectType),
        defaultLinkerScriptPath(GameProjectType));

    dialog.setOptimizationFlag(m_compilerOptimization);
    dialog.setSuppressWarnings(m_compilerSuppressWarnings);
    dialog.setWallEnabled(m_compilerWall);
    dialog.setWextraEnabled(m_compilerWextra);
    dialog.setFunctionSectionsEnabled(m_compilerFunctionSections);
    dialog.setDataSectionsEnabled(m_compilerDataSections);
    dialog.setStackUsageEnabled(m_compilerStackUsage);
    dialog.setExtraCompilerFlags(m_extraCompilerFlags);

    if (dialog.exec() != QDialog::Accepted) {
        return;
    }

    m_projectType = normalizedProjectType(dialog.projectType());
    m_modSizeKb = dialog.modSizeKb();
    m_linkerScriptPath = dialog.customLinkerScriptPath();

    m_compilerOptimization = dialog.optimizationFlag();
    m_compilerSuppressWarnings = dialog.suppressWarnings();
    m_compilerWall = dialog.wallEnabled();
    m_compilerWextra = dialog.wextraEnabled();
    m_compilerFunctionSections = dialog.functionSectionsEnabled();
    m_compilerDataSections = dialog.dataSectionsEnabled();
    m_compilerStackUsage = dialog.stackUsageEnabled();
    m_extraCompilerFlags = dialog.extraCompilerFlags();

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
        m_compilerOptimization,
        QStringLiteral("--specs=nano.specs"),
        QStringLiteral("-mno-unaligned-access"),
        QStringLiteral("-DSIDBOX_STARTUP_HEADER_IN_ASM"),
        QStringLiteral("-I"), apiDir.absolutePath(),
        QStringLiteral("-I"), QDir(libsPath).filePath(QStringLiteral("libraries")),
    };

    if (m_compilerFunctionSections) {
        arguments << QStringLiteral("-ffunction-sections");
    }
    if (m_compilerDataSections) {
        arguments << QStringLiteral("-fdata-sections");
    }
    if (m_compilerStackUsage) {
        arguments << QStringLiteral("-fstack-usage");
    }

    if (m_compilerSuppressWarnings) {
        arguments << QStringLiteral("-w");
    } else {
        if (m_compilerWall) {
            arguments << QStringLiteral("-Wall");
        }
        if (m_compilerWextra) {
            arguments << QStringLiteral("-Wextra");
        }
    }

    if (!m_extraCompilerFlags.trimmed().isEmpty()) {
        arguments << QProcess::splitCommand(m_extraCompilerFlags);
    }

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

    clearCompilerDiagnostics();
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
    appendOutputLine(
        tr("Optimisation: %1").arg(m_compilerOptimization),
        OutputKind::Header);

    QStringList enabledCompilerOptions;
    if (m_compilerFunctionSections) enabledCompilerOptions << QStringLiteral("-ffunction-sections");
    if (m_compilerDataSections) enabledCompilerOptions << QStringLiteral("-fdata-sections");
    if (m_compilerStackUsage) enabledCompilerOptions << QStringLiteral("-fstack-usage");
    if (m_compilerSuppressWarnings) {
        enabledCompilerOptions << QStringLiteral("-w");
    } else {
        if (m_compilerWall) enabledCompilerOptions << QStringLiteral("-Wall");
        if (m_compilerWextra) enabledCompilerOptions << QStringLiteral("-Wextra");
    }
    if (!m_extraCompilerFlags.trimmed().isEmpty()) {
        enabledCompilerOptions << m_extraCompilerFlags.trimmed();
    }

    appendOutputLine(
        tr("Compiler options: %1")
            .arg(enabledCompilerOptions.isEmpty()
                     ? tr("(none)")
                     : enabledCompilerOptions.join(QLatin1Char(' '))),
        OutputKind::Muted);

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
    if (m_buildStep == BuildStep::Linking && !m_compilerStderrBuffer.isEmpty()) {
        appendOutputLine(
            m_compilerStderrBuffer,
            compilerOutputKindForLine(m_compilerStderrBuffer));
        processCompilerDiagnosticLine(m_compilerStderrBuffer);
        m_compilerStderrBuffer.clear();
    }

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
    editor->setTheme(m_theme);
    editor->setFilePath(filePath);

    ensureApiCatalog();

    QStringList initialCompletions = projectFunctionSignatures();
    const QStringList initialTypeNames = projectTypeNames();
    initialCompletions.append(initialTypeNames);
    initialCompletions.removeDuplicates();
    initialCompletions.sort(Qt::CaseInsensitive);

    editor->setFunctionCompletions(initialCompletions);
    editor->setProjectTypeNames(initialTypeNames);
    editor->setApiSyntaxNames(apiSyntaxNames());
    applyCompilerDiagnostics(editor);

    QFont font = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    font.setPointSize(m_editorFontPointSize);
    editor->setFont(font);
    editor->setCompletionFont(font);
    editor->refreshLineNumberAreaWidth();

    connect(editor->document(), &QTextDocument::modificationChanged, this, [this, editor]() {
        updateTabTitle(editor);
    });
    connect(editor->document(), &QTextDocument::contentsChanged, this, [this, editor]() {
        /*
         * loadFromFile() calls setPlainText() before the editor is inserted
         * into the tab widget. Do not perform a project-wide parse in the
         * middle of that initial load; openFile() performs the normal refresh
         * after the tab is installed.
         */
        if (m_editorTabs->indexOf(editor) >= 0) {
            m_projectAnalysisTimer->start();
        }

        /*
         * Struct/member completion itself is cheap unless the caret is
         * actually after '.' or '->', so keep this responsive.
         */
        QMetaObject::invokeMethod(
            editor,
            [editor]() {
                editor->refreshMemberCompletion();
            },
            Qt::QueuedConnection);
    });

    connect(editor, &CodeEditor::quickTipRequested, this, &MainWindow::showQuickTip);
    connect(editor, &CodeEditor::quickTipCandidateChanged, this, &MainWindow::showPassiveQuickTip);
    connect(editor, &CodeEditor::definitionRequested,
            this, [this, editor](const QString &symbol, int sourceLine) {
                goToDefinition(editor, symbol, sourceLine);
            });
    connect(editor, &CodeEditor::memberCompletionRequested,
            this, [this, editor](const QString &objectName,
                                int sourceLine,
                                const QString &prefix) {
                completeStructMembers(editor, objectName, sourceLine, prefix);
            });
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

    /*
     * Sidbox IDE deliberately performs syntax highlighting, symbol discovery
     * and project IntelliSense on source files. That is useful for normal code,
     * but very large generated/resource files can still take a moment to open.
     *
     * Warn rather than silently disabling features: the user keeps full IDE
     * behaviour if they choose Open Anyway.
     */
    const QFileInfo openingFileInfo(filePath);
    const qint64 largeSourceThreshold = 200LL * 1024LL;
    const qint64 veryLargeSourceThreshold = 1024LL * 1024LL;
    const QString suffix = openingFileInfo.suffix().toLower();

    const bool isSourceLike =
        suffix == QStringLiteral("c")
        || suffix == QStringLiteral("h")
        || suffix == QStringLiteral("cc")
        || suffix == QStringLiteral("cpp")
        || suffix == QStringLiteral("hpp")
        || suffix == QStringLiteral("inc");

    if (isSourceLike
        && openingFileInfo.exists()
        && openingFileInfo.size() >= largeSourceThreshold) {

        QMessageBox warning(this);
        warning.setIcon(QMessageBox::Warning);
        warning.setWindowTitle(
            openingFileInfo.size() >= veryLargeSourceThreshold
                ? tr("Very Large Source File")
                : tr("Large Source File"));

        warning.setText(
            tr("%1 is %2.")
                .arg(openingFileInfo.fileName(),
                     formattedFileSize(openingFileInfo.size())));

        warning.setInformativeText(
            openingFileInfo.size() >= veryLargeSourceThreshold
                ? tr("This is a very large source file. Syntax analysis and IntelliSense "
                     "may take a few seconds. Generated/resource data is usually easier "
                     "for the IDE to handle when split across smaller source files.")
                : tr("Large source files may take a moment to open while syntax analysis "
                     "and IntelliSense are prepared. If this is generated/resource data, "
                     "consider splitting it across smaller source files."));

        QPushButton *openAnywayButton =
            warning.addButton(tr("Open Anyway"), QMessageBox::AcceptRole);
        warning.addButton(QMessageBox::Cancel);
        warning.setDefaultButton(openAnywayButton);

        warning.exec();

        if (warning.clickedButton() != openAnywayButton) {
            return false;
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


bool MainWindow::openApiReference(const QString &filePath, int line)
{
    const QString absolutePath = QFileInfo(filePath).absoluteFilePath();
    if (absolutePath.isEmpty() || !QFileInfo::exists(absolutePath)) {
        return false;
    }

    /*
     * Reuse an already-open tab for the same file. If it is a project tab,
     * leave its editability alone; if it was opened by API navigation it is
     * already read-only.
     */
    CodeEditor *editor = nullptr;

    for (int i = 0; i < m_editorTabs->count(); ++i) {
        auto *candidate =
            qobject_cast<CodeEditor *>(m_editorTabs->widget(i));

        if (!candidate || candidate->filePath().isEmpty()) {
            continue;
        }

        if (QFileInfo(candidate->filePath()).absoluteFilePath()
            == absolutePath) {
            editor = candidate;
            m_editorTabs->setCurrentIndex(i);
            break;
        }
    }

    if (!editor) {
        editor = createEditor(absolutePath);

        if (!editor->loadFromFile(absolutePath)) {
            editor->deleteLater();
            QMessageBox::warning(
                this,
                tr("Open API Source"),
                tr("Could not open %1.")
                    .arg(QDir::toNativeSeparators(absolutePath)));
            return false;
        }

        editor->setReadOnly(true);
        editor->setProperty("sidboxApiReference", true);

        const int index =
            m_editorTabs->addTab(
                editor,
                tabTitleForEditor(editor));

        m_editorTabs->setTabToolTip(
            index,
            tr("Read-only Sidbox API source\n%1")
                .arg(QDir::toNativeSeparators(absolutePath)));

        m_editorTabs->setCurrentIndex(index);
    }

    if (line >= 0) {
        const QTextBlock block =
            editor->document()->findBlockByNumber(line);

        if (block.isValid()) {
            QTextCursor cursor(block);
            editor->setTextCursor(cursor);
            editor->centerCursor();
        }
    }

    editor->setFocus();
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
        m_compilerOptimization = QStringLiteral("-Ofast");
        m_compilerSuppressWarnings = true;
        m_compilerWall = false;
        m_compilerWextra = false;
        m_compilerFunctionSections = true;
        m_compilerDataSections = true;
        m_compilerStackUsage = true;
        m_extraCompilerFlags.clear();
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

    const QJsonObject compiler =
        root.value(QStringLiteral("compiler")).toObject();

    m_compilerOptimization =
        compiler.value(QStringLiteral("optimization"))
            .toString(QStringLiteral("-Ofast"));

    const QStringList validOptimizations = {
        QStringLiteral("-O0"),
        QStringLiteral("-Og"),
        QStringLiteral("-O1"),
        QStringLiteral("-O2"),
        QStringLiteral("-O3"),
        QStringLiteral("-Os"),
        QStringLiteral("-Ofast")
    };
    if (!validOptimizations.contains(m_compilerOptimization)) {
        m_compilerOptimization = QStringLiteral("-Ofast");
    }

    m_compilerSuppressWarnings =
        compiler.value(QStringLiteral("suppressWarnings")).toBool(true);
    m_compilerWall =
        compiler.value(QStringLiteral("wall")).toBool(false);
    m_compilerWextra =
        compiler.value(QStringLiteral("wextra")).toBool(false);
    m_compilerFunctionSections =
        compiler.value(QStringLiteral("functionSections")).toBool(true);
    m_compilerDataSections =
        compiler.value(QStringLiteral("dataSections")).toBool(true);
    m_compilerStackUsage =
        compiler.value(QStringLiteral("stackUsage")).toBool(true);
    m_extraCompilerFlags =
        compiler.value(QStringLiteral("extraFlags")).toString();

    /*
     * -w means warnings are suppressed, so warning-enabling switches have no
     * effect. Keep the stored state internally consistent for older/hand-edited
     * project files.
     */
    if (m_compilerSuppressWarnings) {
        m_compilerWall = false;
        m_compilerWextra = false;
    }

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

    QJsonObject compiler;
    compiler.insert(QStringLiteral("optimization"), m_compilerOptimization);
    compiler.insert(QStringLiteral("suppressWarnings"), m_compilerSuppressWarnings);
    compiler.insert(QStringLiteral("wall"), m_compilerWall);
    compiler.insert(QStringLiteral("wextra"), m_compilerWextra);
    compiler.insert(QStringLiteral("functionSections"), m_compilerFunctionSections);
    compiler.insert(QStringLiteral("dataSections"), m_compilerDataSections);
    compiler.insert(QStringLiteral("stackUsage"), m_compilerStackUsage);
    compiler.insert(QStringLiteral("extraFlags"), m_extraCompilerFlags);
    root.insert(QStringLiteral("compiler"), compiler);

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
            item->setData(
                0,
                Qt::UserRole + 10,
                QStringLiteral("type:%1").arg(type.name));

            for (const SourceVariableSymbol &member : type.members) {
                auto *memberItem = new QTreeWidgetItem(item);
                memberItem->setText(0, member.name);
                memberItem->setIcon(0, localIcon);
                memberItem->setData(0, Qt::UserRole, member.line);
                memberItem->setToolTip(
                    0,
                    tr("Member — double-click to jump to line %1")
                        .arg(member.line + 1));
            }
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
            item->setText(0, global.name + global.arraySuffix);
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
                    item->setText(0, parameter.name + parameter.arraySuffix);
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
                    item->setText(0, local.name + local.arraySuffix);
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

void MainWindow::completeStructMembers(CodeEditor *sourceEditor,
                                       const QString &objectName,
                                       int sourceLine,
                                       const QString &prefix)
{
    if (!sourceEditor || objectName.isEmpty()) {
        return;
    }

    const SourceSymbolTable currentSymbols =
        parseSourceSymbols(sourceEditor->toPlainText());

    const QString typeName =
        variableTypeInTable(
            currentSymbols,
            objectName,
            sourceLine,
            true);

    if (typeName.isEmpty()) {
        sourceEditor->showMemberCompletions({}, prefix);
        return;
    }

    // The type may be declared in the same file.
    QStringList members =
        membersForTypeInTable(currentSymbols, typeName);

    if (!members.isEmpty()) {
        sourceEditor->showMemberCompletions(members, prefix);
        return;
    }

    const QString sourcePath =
        sourceEditor->filePath().isEmpty()
            ? QString()
            : QFileInfo(sourceEditor->filePath()).absoluteFilePath();

    QSet<QString> scannedPaths;
    if (!sourcePath.isEmpty()) {
        scannedPaths.insert(sourcePath);
    }

    // Then search other open tabs, using their unsaved in-memory text.
    for (int i = 0; i < m_editorTabs->count(); ++i) {
        auto *editor =
            qobject_cast<CodeEditor *>(m_editorTabs->widget(i));

        if (!editor || editor == sourceEditor) {
            continue;
        }

        if (!editor->filePath().isEmpty()) {
            scannedPaths.insert(
                QFileInfo(editor->filePath()).absoluteFilePath());
        }

        const SourceSymbolTable table =
            parseSourceSymbols(editor->toPlainText());

        members = membersForTypeInTable(table, typeName);
        if (!members.isEmpty()) {
            sourceEditor->showMemberCompletions(members, prefix);
            return;
        }
    }

    // Finally search the remaining project files on disk.
    QStringList projectFiles = m_projectFilesInProject;
    projectFiles.append(projectFolderSourceFiles());
    projectFiles.removeDuplicates();

    for (const QString &filePath : std::as_const(projectFiles)) {
        const QString absolutePath =
            QFileInfo(filePath).absoluteFilePath();

        if (absolutePath.isEmpty()
            || scannedPaths.contains(absolutePath)
            || !QFileInfo::exists(absolutePath)
            || !canContainFunctionSignatures(absolutePath)) {
            continue;
        }

        QFile file(absolutePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            continue;
        }

        const SourceSymbolTable table =
            parseSourceSymbols(QString::fromUtf8(file.readAll()));

        members = membersForTypeInTable(table, typeName);
        if (!members.isEmpty()) {
            sourceEditor->showMemberCompletions(members, prefix);
            return;
        }
    }

    sourceEditor->showMemberCompletions({}, prefix);
}


void MainWindow::goToDefinition(CodeEditor *sourceEditor,
                                const QString &symbol,
                                int sourceLine)
{
    if (!sourceEditor || symbol.isEmpty()) {
        return;
    }

    auto jumpToLine = [this](CodeEditor *editor, int line) {
        if (!editor || line < 0) {
            return false;
        }

        const QTextBlock block = editor->document()->findBlockByNumber(line);
        if (!block.isValid()) {
            return false;
        }

        const int tabIndex = m_editorTabs->indexOf(editor);
        if (tabIndex >= 0) {
            m_editorTabs->setCurrentIndex(tabIndex);
        }

        QTextCursor cursor(block);
        editor->setTextCursor(cursor);
        editor->centerCursor();
        editor->setFocus();
        return true;
    };

    /*
     * Keep the first extern declaration as a fallback. We search every open
     * tab/project file for a real definition first. If none exists, Ctrl+Click
     * can still take the user to the declaration rather than doing nothing.
     */
    CodeEditor *externFallbackEditor = nullptr;
    int externFallbackLine = -1;
    QString externFallbackPath;

    // 1. Current file first. This also resolves locals and parameters using
    //    the function containing the Ctrl+Clicked use.
    const SourceSymbolTable currentSymbols =
        parseSourceSymbols(sourceEditor->toPlainText());

    for (const SourceVariableSymbol &global : currentSymbols.globals) {
        if (global.name == symbol && global.externDeclaration) {
            externFallbackEditor = sourceEditor;
            externFallbackLine = global.line;
            externFallbackPath = sourceEditor->filePath();
            break;
        }
    }

    const int currentLine =
        definitionLineInTable(currentSymbols, symbol, sourceLine, true, false);

    if (currentLine >= 0) {
        jumpToLine(sourceEditor, currentLine);
        statusBar()->showMessage(
            tr("%1 — definition in %2:%3")
                .arg(symbol,
                     sourceEditor->filePath().isEmpty()
                         ? tr("current tab")
                         : QFileInfo(sourceEditor->filePath()).fileName())
                .arg(currentLine + 1),
            2500);
        return;
    }

    const QString sourcePath = sourceEditor->filePath().isEmpty()
        ? QString()
        : QFileInfo(sourceEditor->filePath()).absoluteFilePath();

    QSet<QString> scannedPaths;
    if (!sourcePath.isEmpty()) {
        scannedPaths.insert(sourcePath);
    }

    // 2. Other open tabs. Use their in-memory contents so unsaved edits still
    //    participate in Ctrl+Click navigation.
    for (int i = 0; i < m_editorTabs->count(); ++i) {
        auto *editor = qobject_cast<CodeEditor *>(m_editorTabs->widget(i));
        if (!editor || editor == sourceEditor) {
            continue;
        }

        const QString editorPath = editor->filePath().isEmpty()
            ? QString()
            : QFileInfo(editor->filePath()).absoluteFilePath();

        if (!editorPath.isEmpty()) {
            scannedPaths.insert(editorPath);
        }

        const SourceSymbolTable symbols =
            parseSourceSymbols(editor->toPlainText());

        if (externFallbackLine < 0) {
            for (const SourceVariableSymbol &global : symbols.globals) {
                if (global.name == symbol && global.externDeclaration) {
                    externFallbackEditor = editor;
                    externFallbackLine = global.line;
                    externFallbackPath = editorPath;
                    break;
                }
            }
        }

        const int line = definitionLineInTable(symbols, symbol, -1, false, false);
        if (line >= 0) {
            jumpToLine(editor, line);
            statusBar()->showMessage(
                tr("%1 — definition in %2:%3")
                    .arg(symbol,
                         editorPath.isEmpty()
                             ? tr("open tab")
                             : QFileInfo(editorPath).fileName())
                    .arg(line + 1),
                2500);
            return;
        }
    }

    // 3. Remaining files in the project. This includes headers and .inc files,
    //    not just compilable .c/.cpp sources.
    QStringList projectFiles = m_projectFilesInProject;
    projectFiles.append(projectFolderSourceFiles());
    projectFiles.removeDuplicates();

    for (const QString &filePath : std::as_const(projectFiles)) {
        const QString absolutePath = QFileInfo(filePath).absoluteFilePath();

        if (absolutePath.isEmpty()
            || scannedPaths.contains(absolutePath)
            || !QFileInfo::exists(absolutePath)
            || !canContainFunctionSignatures(absolutePath)) {
            continue;
        }

        QFile file(absolutePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            continue;
        }

        const QString source = QString::fromUtf8(file.readAll());
        const SourceSymbolTable symbols = parseSourceSymbols(source);

        if (externFallbackLine < 0) {
            for (const SourceVariableSymbol &global : symbols.globals) {
                if (global.name == symbol && global.externDeclaration) {
                    externFallbackEditor = nullptr;
                    externFallbackLine = global.line;
                    externFallbackPath = absolutePath;
                    break;
                }
            }
        }

        const int line = definitionLineInTable(symbols, symbol, -1, false, false);

        if (line < 0) {
            continue;
        }

        if (!openFile(absolutePath)) {
            return;
        }

        CodeEditor *targetEditor = activeEditor();
        if (targetEditor && jumpToLine(targetEditor, line)) {
            statusBar()->showMessage(
                tr("%1 — definition in %2:%3")
                    .arg(symbol, QFileInfo(absolutePath).fileName())
                    .arg(line + 1),
                2500);
        }
        return;
    }

    /*
     * 4. Sidbox API source/header lookup.
     *
     * Only do this for names that are actually in the API catalogue, so a
     * failed Ctrl+Click on an ordinary project identifier does not recursively
     * scan the SDK.
     */
    ensureApiCatalog();

    const QStringList knownApiNames = apiSyntaxNames();
    if (knownApiNames.contains(symbol)) {
        const QString apiPath =
            QDir(ideLibsPath()).filePath(QStringLiteral("api"));

        QStringList apiSourceFiles;
        QStringList apiHeaderFiles;

        QDirIterator apiIterator(
            apiPath,
            {QStringLiteral("*.c"), QStringLiteral("*.h")},
            QDir::Files,
            QDirIterator::Subdirectories);

        while (apiIterator.hasNext()) {
            const QString path =
                QFileInfo(apiIterator.next()).absoluteFilePath();

            if (QFileInfo(path).suffix().compare(
                    QStringLiteral("c"),
                    Qt::CaseInsensitive) == 0) {
                apiSourceFiles.append(path);
            } else {
                apiHeaderFiles.append(path);
            }
        }

        /*
         * Prefer .c first: for an API function/global this normally lands on
         * the real implementation/storage. Headers are the fallback for
         * macros, typedefs, enums, structs and header-only declarations.
         */
        apiSourceFiles.sort(Qt::CaseInsensitive);
        apiHeaderFiles.sort(Qt::CaseInsensitive);

        QStringList apiFiles = apiSourceFiles;
        apiFiles.append(apiHeaderFiles);

        for (const QString &apiFilePath : std::as_const(apiFiles)) {
            QFile apiFile(apiFilePath);
            if (!apiFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
                continue;
            }

            const QString apiSource =
                QString::fromUtf8(apiFile.readAll());

            const SourceSymbolTable apiSymbols =
                parseSourceSymbols(apiSource);

            const int apiLine =
                definitionLineInTable(
                    apiSymbols,
                    symbol,
                    -1,
                    false,
                    false);

            if (apiLine < 0) {
                continue;
            }

            if (openApiReference(apiFilePath, apiLine)) {
                statusBar()->showMessage(
                    tr("%1 — Sidbox API source in %2:%3 (read-only)")
                        .arg(symbol,
                             QFileInfo(apiFilePath).fileName())
                        .arg(apiLine + 1),
                    3500);
            }
            return;
        }
    }

    /*
     * No storage definition was found. Fall back to the extern declaration,
     * if there was one.
     */
    if (externFallbackLine >= 0) {
        if (externFallbackEditor) {
            jumpToLine(externFallbackEditor, externFallbackLine);
            statusBar()->showMessage(
                tr("%1 — extern declaration in %2:%3")
                    .arg(symbol,
                         externFallbackPath.isEmpty()
                             ? tr("open tab")
                             : QFileInfo(externFallbackPath).fileName())
                    .arg(externFallbackLine + 1),
                2500);
            return;
        }

        if (!externFallbackPath.isEmpty()
            && openFile(externFallbackPath)) {
            CodeEditor *targetEditor = activeEditor();
            if (targetEditor
                && jumpToLine(targetEditor, externFallbackLine)) {
                statusBar()->showMessage(
                    tr("%1 — extern declaration in %2:%3")
                        .arg(symbol,
                             QFileInfo(externFallbackPath).fileName())
                        .arg(externFallbackLine + 1),
                    2500);
            }
            return;
        }
    }

    statusBar()->showMessage(
        tr("No definition found for %1").arg(symbol),
        3000);
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

QStringList MainWindow::apiSyntaxNames() const
{
    QStringList names = m_apiTips.keys();

    /*
     * Some functions are discovered as signatures without a separate quick-tip
     * entry. Pull their identifier out as well so every catalogued API symbol
     * receives the API syntax colour.
     */
    for (const QString &signature : m_apiSignatures) {
        const int paren = signature.indexOf(QLatin1Char('('));
        const QString name =
            (paren >= 0 ? signature.left(paren) : signature).trimmed();

        if (!name.isEmpty()) {
            names.append(name);
        }
    }

    names.removeDuplicates();
    names.sort(Qt::CaseSensitive);
    return names;
}

void MainWindow::refreshFunctionCompletions()
{
    ensureApiCatalog();

    QStringList completions = projectFunctionSignatures();
    const QStringList typeNames = projectTypeNames();
    const QStringList apiNames = apiSyntaxNames();

    // Type names without "(...)" are handled by CodeEditor's existing
    // completion insertion path as plain identifiers.
    completions.append(typeNames);
    completions.removeDuplicates();
    completions.sort(Qt::CaseInsensitive);

    for (int i = 0; i < m_editorTabs->count(); ++i) {
        auto *editor = qobject_cast<CodeEditor *>(m_editorTabs->widget(i));
        if (!editor) {
            continue;
        }

        editor->setFunctionCompletions(completions);
        editor->setProjectTypeNames(typeNames);
        editor->setApiSyntaxNames(apiNames);
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
    QDirIterator iterator(apiPath,
                          {QStringLiteral("*.h"), QStringLiteral("*.c")},
                          QDir::Files,
                          QDirIterator::Subdirectories);
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

        if (editor->property("sidboxApiReference").toBool()) {
            title += tr(" [API]");
        }
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

    QStringList projectFiles = m_projectFilesInProject;
    projectFiles.append(projectFolderSourceFiles());
    projectFiles.removeDuplicates();

    for (const QString &filePath : std::as_const(projectFiles)) {
        const QString absolutePath = QFileInfo(filePath).absoluteFilePath();
        if (scannedOpenFiles.contains(absolutePath)
            || !QFileInfo::exists(absolutePath)
            || !canContainFunctionSignatures(absolutePath)) {
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

QStringList MainWindow::projectTypeNames() const
{
    QStringList names;
    QSet<QString> scannedPaths;

    auto appendTypes = [&names](const QString &source) {
        const SourceSymbolTable symbols = parseSourceSymbols(source);

        for (const SourceNamedSymbol &type : symbols.types) {
            if (!type.name.isEmpty()) {
                names.append(type.name);
            }
        }
    };

    // Open tabs win: use the live in-memory text, including unsaved changes.
    for (int i = 0; i < m_editorTabs->count(); ++i) {
        auto *editor = qobject_cast<CodeEditor *>(m_editorTabs->widget(i));
        if (!editor) {
            continue;
        }

        appendTypes(editor->toPlainText());

        if (!editor->filePath().isEmpty()) {
            scannedPaths.insert(
                QFileInfo(editor->filePath()).absoluteFilePath());
        }
    }

    // Then scan all remaining project files on disk, including subfolders,
    // headers and .inc files.
    QStringList projectFiles = m_projectFilesInProject;
    projectFiles.append(projectFolderSourceFiles());
    projectFiles.removeDuplicates();

    for (const QString &filePath : std::as_const(projectFiles)) {
        const QString absolutePath =
            QFileInfo(filePath).absoluteFilePath();

        if (absolutePath.isEmpty()
            || scannedPaths.contains(absolutePath)
            || !QFileInfo::exists(absolutePath)
            || !canContainFunctionSignatures(absolutePath)) {
            continue;
        }

        QFile file(absolutePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            continue;
        }

        appendTypes(QString::fromUtf8(file.readAll()));
    }

    names.removeDuplicates();
    names.sort(Qt::CaseInsensitive);
    return names;
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

QList<ProjectSearchResult> MainWindow::findInProject(
    const QString &needle,
    bool matchCase,
    bool wholeWord) const
{
    QList<ProjectSearchResult> results;

    if (needle.isEmpty()) {
        return results;
    }

    /*
     * Build one list of project files. An open editor always wins over the
     * on-disk copy so unsaved edits are searched live.
     */
    QStringList candidates = m_projectFilesInProject;
    candidates.append(projectFolderSourceFiles());

    QHash<QString, CodeEditor *> openEditors;

    for (int i = 0; i < m_editorTabs->count(); ++i) {
        auto *editor =
            qobject_cast<CodeEditor *>(m_editorTabs->widget(i));

        if (!editor || editor->filePath().isEmpty()) {
            continue;
        }

        const QString path =
            QFileInfo(editor->filePath()).absoluteFilePath();

        openEditors.insert(path, editor);

        if (!candidates.contains(path)) {
            candidates.append(path);
        }
    }

    candidates.removeDuplicates();
    candidates.sort(Qt::CaseInsensitive);

    const Qt::CaseSensitivity sensitivity =
        matchCase ? Qt::CaseSensitive : Qt::CaseInsensitive;

    QRegularExpression wholeWordExpression;

    if (wholeWord) {
        QRegularExpression::PatternOptions options =
            QRegularExpression::NoPatternOption;

        if (!matchCase) {
            options |= QRegularExpression::CaseInsensitiveOption;
        }

        wholeWordExpression =
            QRegularExpression(
                QStringLiteral("\\b%1\\b")
                    .arg(QRegularExpression::escape(needle)),
                options);
    }

    for (const QString &rawPath : std::as_const(candidates)) {
        const QString filePath =
            QFileInfo(rawPath).absoluteFilePath();

        QString text;

        if (CodeEditor *editor =
                openEditors.value(filePath, nullptr)) {
            text = editor->toPlainText();
        } else {
            QFile file(filePath);

            if (!file.open(
                    QIODevice::ReadOnly | QIODevice::Text)) {
                continue;
            }

            text = QString::fromUtf8(file.readAll());
        }

        QList<QPair<int, int>> matches;

        if (wholeWord) {
            QRegularExpressionMatchIterator iterator =
                wholeWordExpression.globalMatch(text);

            while (iterator.hasNext()) {
                const QRegularExpressionMatch match = iterator.next();

                if (match.capturedLength() > 0) {
                    matches.append({
                        match.capturedStart(),
                        match.capturedLength()
                    });
                }
            }
        } else {
            int from = 0;

            while (from <= text.size()) {
                const int found =
                    text.indexOf(needle, from, sensitivity);

                if (found < 0) {
                    break;
                }

                matches.append({found, needle.size()});
                from = found + qMax(1, needle.size());
            }
        }

        for (const auto &match : matches) {
            const int start = match.first;
            const int length = match.second;

            const int line =
                text.left(start).count(QLatin1Char('\n'));

            const int lineStart =
                text.lastIndexOf(QLatin1Char('\n'), start - 1) + 1;

            int lineEnd =
                text.indexOf(QLatin1Char('\n'), start);

            if (lineEnd < 0) {
                lineEnd = text.size();
            }

            const int column = start - lineStart;

            QString preview =
                text.mid(lineStart, lineEnd - lineStart).trimmed();

            if (preview.size() > 180) {
                preview = preview.left(177)
                    + QStringLiteral("...");
            }

            results.append({
                filePath,
                line,
                column,
                start,
                length,
                preview
            });
        }
    }

    return results;
}

bool MainWindow::replaceProjectResults(
    const QList<ProjectSearchResult> &results,
    const QString &replacement)
{
    if (results.isEmpty()) {
        return true;
    }

    QHash<QString, QList<ProjectSearchResult>> byFile;

    for (const ProjectSearchResult &result : results) {
        if (result.filePath.isEmpty()
            || result.start < 0
            || result.length < 0) {
            continue;
        }

        byFile[QFileInfo(result.filePath).absoluteFilePath()]
            .append(result);
    }

    for (auto it = byFile.begin();
         it != byFile.end();
         ++it) {

        QList<ProjectSearchResult> fileResults = it.value();

        std::sort(
            fileResults.begin(),
            fileResults.end(),
            [](const ProjectSearchResult &a,
               const ProjectSearchResult &b) {
                return a.start > b.start;
            });

        CodeEditor *openEditor = nullptr;

        for (int i = 0; i < m_editorTabs->count(); ++i) {
            auto *editor =
                qobject_cast<CodeEditor *>(
                    m_editorTabs->widget(i));

            if (editor
                && !editor->filePath().isEmpty()
                && QFileInfo(editor->filePath()).absoluteFilePath()
                    == it.key()) {
                openEditor = editor;
                break;
            }
        }

        if (openEditor) {
            QTextCursor cursor(openEditor->document());
            cursor.beginEditBlock();

            for (const ProjectSearchResult &result :
                 fileResults) {
                if (result.start + result.length
                    > openEditor->document()->characterCount()) {
                    continue;
                }

                cursor.setPosition(result.start);
                cursor.setPosition(
                    result.start + result.length,
                    QTextCursor::KeepAnchor);
                cursor.insertText(replacement);
            }

            cursor.endEditBlock();

            openEditor->document()->setModified(true);
            updateTabTitle(openEditor);
            continue;
        }

        QFile file(it.key());

        if (!file.open(
                QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(
                this,
                tr("Replace"),
                tr("Could not read %1.")
                    .arg(QDir::toNativeSeparators(it.key())));
            return false;
        }

        QString text = QString::fromUtf8(file.readAll());
        file.close();

        for (const ProjectSearchResult &result :
             fileResults) {
            if (result.start < 0
                || result.start + result.length > text.size()) {
                continue;
            }

            text.replace(
                result.start,
                result.length,
                replacement);
        }

        QSaveFile output(it.key());

        if (!output.open(
                QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(
                this,
                tr("Replace"),
                tr("Could not write %1.")
                    .arg(QDir::toNativeSeparators(it.key())));
            return false;
        }

        output.write(text.toUtf8());

        if (!output.commit()) {
            QMessageBox::warning(
                this,
                tr("Replace"),
                tr("Could not finish writing %1.")
                    .arg(QDir::toNativeSeparators(it.key())));
            return false;
        }
    }

    refreshFunctionCompletions();
    refreshSymbolTree();
    return true;
}

void MainWindow::jumpToProjectSearchResult(
    const ProjectSearchResult &result)
{
    if (result.filePath.isEmpty()) {
        return;
    }

    CodeEditor *editor = nullptr;
    const QString target =
        QFileInfo(result.filePath).absoluteFilePath();

    for (int i = 0; i < m_editorTabs->count(); ++i) {
        auto *candidate =
            qobject_cast<CodeEditor *>(m_editorTabs->widget(i));

        if (candidate
            && !candidate->filePath().isEmpty()
            && QFileInfo(candidate->filePath()).absoluteFilePath()
                == target) {
            editor = candidate;
            m_editorTabs->setCurrentIndex(i);
            break;
        }
    }

    if (!editor) {
        if (!openFile(target)) {
            return;
        }

        editor = activeEditor();
    }

    if (!editor) {
        return;
    }

    QTextBlock block =
        editor->document()->findBlockByNumber(
            qMax(0, result.line));

    if (!block.isValid()) {
        return;
    }

    QTextCursor cursor(block);

    if (result.column > 0) {
        cursor.movePosition(
            QTextCursor::NextCharacter,
            QTextCursor::MoveAnchor,
            result.column);
    }

    if (result.length > 0) {
        cursor.movePosition(
            QTextCursor::NextCharacter,
            QTextCursor::KeepAnchor,
            result.length);
    }

    editor->setTextCursor(cursor);
    editor->centerCursor();
    editor->setFocus();
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

void MainWindow::applyTheme()
{
    const auto C = [](const QColor &colour) {
        return ideThemeColorName(colour);
    };

    setStyleSheet(QStringLiteral(
        "QMainWindow, QWidget { background-color:%1; color:%2; }"
        "QLabel { background-color:%1; color:%3; border:none; }"

        "QToolBar { background-color:%1; border:none; spacing:1px; padding:1px; }"
        "QToolButton { background-color:%1; color:%3; border:none; border-radius:0px; padding:3px; }"
        "QToolButton:hover { background-color:%4; }"
        "QToolButton:pressed { background-color:%5; }"

        "QPushButton { background-color:%1; color:%2; border:1px solid %6; border-radius:0px; padding:4px 8px; }"
        "QPushButton:hover { background-color:%4; border:1px solid %5; }"
        "QPushButton:pressed { background-color:%5; color:%3; }"

        "QTreeWidget { background-color:%7; color:%2; border:1px solid %8; "
        " alternate-background-color:%9; border-radius:0px; }"
        "QTreeWidget::item { border-radius:0px; padding:1px; }"
        "QTreeWidget::item:selected { background-color:%5; color:%3; }"
        "QTreeWidget::item:hover { background-color:%4; }"

        "QTabWidget::pane { background-color:%1; border:1px solid %8; border-radius:0px; }"
        "QTabBar::tab { background-color:%1; color:%10; border:1px solid %6; "
        " border-bottom:none; border-radius:0px; padding:5px 10px; }"
        "QTabBar::tab:selected { background-color:%5; color:%3; }"
        "QTabBar::tab:hover:!selected { background-color:%4; }"

        "QStatusBar { background-color:%1; color:%10; border-top:1px solid %6; }"
        "QSplitter::handle { background-color:%4; }"
        "QSplitter::handle:hover { background-color:%5; }"

        "QMenu { background-color:%11; color:%2; border:1px solid %6; }"
        "QMenu::item { padding:5px 24px 5px 8px; }"
        "QMenu::item:selected { background-color:%5; color:%3; }"

        "QScrollBar:vertical { background:%11; width:12px; margin:0px; }"
        "QScrollBar:horizontal { background:%11; height:12px; margin:0px; }"
        "QScrollBar::handle:vertical { background:%12; min-height:20px; border-radius:0px; }"
        "QScrollBar::handle:horizontal { background:%12; min-width:20px; border-radius:0px; }"
        "QScrollBar::handle:vertical:hover, QScrollBar::handle:horizontal:hover { background:%13; }"
        "QScrollBar:add-line, QScrollBar:sub-line { width:0px; height:0px; }"

        "QLineEdit, QPlainTextEdit, QSpinBox { background-color:%7; color:%2; "
        " border:1px solid %6; border-radius:0px; "
        " selection-background-color:%5; selection-color:%3; }"

        "QToolTip { background-color:%14; color:%15; border:2px solid %5; "
        " padding:5px 5px; font-size:12px; font-weight:500; }")
        .arg(C(m_theme.windowBackground))      // 1
        .arg(C(m_theme.text))                  // 2
        .arg(C(m_theme.brightText))            // 3
        .arg(C(m_theme.hover))                 // 4
        .arg(C(m_theme.accent))                // 5
        .arg(C(m_theme.border))                // 6
        .arg(C(m_theme.inputBackground))       // 7
        .arg(C(m_theme.treeBorder))            // 8
        .arg(C(m_theme.alternateBackground))   // 9
        .arg(C(m_theme.mutedText))             // 10
        .arg(C(m_theme.menuBackground))        // 11
        .arg(C(m_theme.scrollHandle))          // 12
        .arg(C(m_theme.scrollHandleHover))     // 13
        .arg(C(m_theme.tooltipBackground))     // 14
        .arg(C(m_theme.tooltipText)));         // 15

    if (m_projectFiles) {
        m_projectFiles->setStyleSheet(QStringLiteral(
            "QTreeWidget { border:1px solid %1; border-radius:0px; }"
            "QTreeWidget::item { border-radius:0px; }"
            "QTreeWidget::item:selected { background-color:%2; color:%3; }"
            "QTreeWidget::item:selected:hover { border:1px solid %4; background-color:%2; }")
            .arg(C(m_theme.treeBorder),
                 C(m_theme.accent),
                 C(m_theme.brightText),
                 C(m_theme.border)));
    }

    if (m_functionvarList) {
        m_functionvarList->setStyleSheet(QStringLiteral(
            "QTreeWidget { border:1px solid %1; border-radius:0px; }"
            "QTreeWidget::item { border-radius:0px; }"
            "QTreeWidget::item:selected { background-color:%2; color:%3; }"
            "QTreeWidget::item:selected:hover { border:1px solid %4; background-color:%2; }")
            .arg(C(m_theme.treeBorder),
                 C(m_theme.accent),
                 C(m_theme.brightText),
                 C(m_theme.border)));
    }

    if (m_editorTabs) {
        m_editorTabs->setStyleSheet(QStringLiteral(
            "QTabWidget::pane { border:1px solid %1; border-radius:0px; }"
            "QTabBar::tab { background:%2; color:%3; border:1px solid %1; "
            " border-bottom:none; border-radius:0px; padding:6px 12px; margin-right:-6px; }"
            "QTabBar::tab:selected { background:%4; color:%5; border-radius:0px; }"
            "QTabBar::tab:hover:!selected { background:%6; border-radius:0px; }"
            "QTabBar::close-button { image:url(:/icons/close_tab.png); border-radius:0px; "
            " subcontrol-position:right; subcontrol-origin:padding; width:14px; height:14px; background:transparent; }"
            "QTabBar::close-button:hover { background:%7; border-radius:0px; }")
            .arg(C(m_theme.treeBorder),
                 C(m_theme.panelBackground),
                 C(m_theme.mutedText),
                 C(m_theme.accent),
                 C(m_theme.brightText),
                 C(m_theme.hover),
                 C(m_theme.outputError)));
    }

    if (m_quickTipLabel) {
        m_quickTipLabel->setStyleSheet(QStringLiteral(
            "QLabel { background:%1; color:%2; border-top:1px solid %3; "
            " border-bottom:1px solid %3; padding:3px 6px; }")
            .arg(C(m_theme.quickTipBackground),
                 C(m_theme.quickTipText),
                 C(m_theme.quickTipBorder)));
    }

    if (m_outputPane) {
        m_outputPane->setStyleSheet(QStringLiteral(
            "QPlainTextEdit { background:%1; color:%2; "
            " selection-background-color:%3; selection-color:%4; }")
            .arg(C(m_theme.outputBackground),
                 C(m_theme.outputNormal),
                 C(m_theme.selectionBackground),
                 C(m_theme.selectionText)));
    }

    if (m_editorTabs) {
        for (int i = 0; i < m_editorTabs->count(); ++i) {
            auto *editor = qobject_cast<CodeEditor *>(m_editorTabs->widget(i));
            if (editor) {
                editor->setTheme(m_theme);
            }
        }
    }
}

void MainWindow::clearCompilerDiagnostics()
{
    m_compilerStderrBuffer.clear();
    m_compilerDiagnostics.clear();

    if (!m_editorTabs) {
        return;
    }

    for (int i = 0; i < m_editorTabs->count(); ++i) {
        auto *editor = qobject_cast<CodeEditor *>(m_editorTabs->widget(i));
        if (editor) {
            editor->clearDiagnostics();
        }
    }
}

QString MainWindow::normalizedDiagnosticPath(const QString &compilerPath) const
{
    QString path = compilerPath.trimmed();
    if (path.isEmpty()) {
        return {};
    }

    QFileInfo info(path);
    if (info.isAbsolute()) {
        return info.absoluteFilePath();
    }

    if (m_compilerProcess && !m_compilerProcess->workingDirectory().isEmpty()) {
        const QString fromWorkingDirectory =
            QFileInfo(QDir(m_compilerProcess->workingDirectory()).filePath(path))
                .absoluteFilePath();

        if (QFileInfo::exists(fromWorkingDirectory)) {
            return fromWorkingDirectory;
        }
    }

    if (!m_projectPath.isEmpty()) {
        const QString fromProject =
            QFileInfo(QDir(m_projectPath).filePath(path)).absoluteFilePath();

        if (QFileInfo::exists(fromProject)) {
            return fromProject;
        }
    }

    return QFileInfo(path).absoluteFilePath();
}

MainWindow::OutputKind MainWindow::compilerOutputKindForLine(
    const QString &line) const
{
    const QString lower = line.toLower();

    if (lower.contains(QStringLiteral("warning:"))) {
        return OutputKind::Warning;
    }

    if (lower.contains(QStringLiteral("fatal error:"))
        || lower.contains(QStringLiteral("error:"))
        || lower.contains(QStringLiteral("undefined reference"))
        || lower.contains(QStringLiteral("ld returned"))) {
        return OutputKind::Error;
    }

    return OutputKind::Normal;
}

void MainWindow::processCompilerStderrChunk(const QString &text)
{
    if (text.isEmpty()) {
        return;
    }

    m_compilerStderrBuffer += text;

    int newlineIndex = -1;
    while ((newlineIndex = m_compilerStderrBuffer.indexOf(QLatin1Char('\n'))) >= 0) {
        QString line = m_compilerStderrBuffer.left(newlineIndex);
        m_compilerStderrBuffer.remove(0, newlineIndex + 1);

        if (line.endsWith(QLatin1Char('\r'))) {
            line.chop(1);
        }

        appendOutputLine(line, compilerOutputKindForLine(line));
        processCompilerDiagnosticLine(line);
    }
}

void MainWindow::processCompilerDiagnosticLine(const QString &line)
{
    static const QRegularExpression diagnosticExpression(
        QStringLiteral(R"(^(.+?):(\d+)(?::(\d+))?:\s*(fatal error|error|warning):\s*(.*)$)"),
        QRegularExpression::CaseInsensitiveOption);

    const QRegularExpressionMatch match = diagnosticExpression.match(line);
    if (!match.hasMatch()) {
        return;
    }

    QString filePath = normalizedDiagnosticPath(match.captured(1));

    bool lineOk = false;
    const int oneBasedLine = match.captured(2).toInt(&lineOk);
    if (!lineOk || oneBasedLine <= 0 || filePath.isEmpty()) {
        return;
    }

    bool columnOk = false;
    const int oneBasedColumn = match.captured(3).toInt(&columnOk);

    const QString severityText = match.captured(4).toLower();
    const EditorDiagnostic::Severity severity =
        severityText == QStringLiteral("warning")
            ? EditorDiagnostic::Severity::Warning
            : EditorDiagnostic::Severity::Error;

    EditorDiagnostic diagnostic;
    diagnostic.line = oneBasedLine - 1;
    diagnostic.column = columnOk && oneBasedColumn > 0 ? oneBasedColumn - 1 : -1;
    diagnostic.severity = severity;
    diagnostic.message = match.captured(5).trimmed();

    CodeEditor *matchedEditor = nullptr;

    if (m_editorTabs) {
        // Prefer an exact absolute-path match.
        for (int i = 0; i < m_editorTabs->count(); ++i) {
            auto *editor = qobject_cast<CodeEditor *>(m_editorTabs->widget(i));
            if (!editor || editor->filePath().isEmpty()) {
                continue;
            }

            const QString editorPath =
                QFileInfo(editor->filePath()).absoluteFilePath();

            if (editorPath == filePath) {
                matchedEditor = editor;
                filePath = editorPath;
                break;
            }
        }

        // Some toolchains print only a bare file name. Fall back only when
        // that name uniquely identifies one open editor.
        if (!matchedEditor) {
            const QString diagnosticName = QFileInfo(filePath).fileName();
            CodeEditor *nameMatch = nullptr;

            for (int i = 0; i < m_editorTabs->count(); ++i) {
                auto *editor = qobject_cast<CodeEditor *>(m_editorTabs->widget(i));
                if (!editor || editor->filePath().isEmpty()) {
                    continue;
                }

                if (QFileInfo(editor->filePath()).fileName() == diagnosticName) {
                    if (nameMatch) {
                        nameMatch = nullptr; // ambiguous
                        break;
                    }
                    nameMatch = editor;
                }
            }

            if (nameMatch) {
                matchedEditor = nameMatch;
                filePath = QFileInfo(nameMatch->filePath()).absoluteFilePath();
            }
        }
    }

    QList<EditorDiagnostic> &diagnostics = m_compilerDiagnostics[filePath];

    const bool duplicate = std::any_of(
        diagnostics.cbegin(),
        diagnostics.cend(),
        [&](const EditorDiagnostic &existing) {
            return existing.line == diagnostic.line
                && existing.column == diagnostic.column
                && existing.severity == diagnostic.severity
                && existing.message == diagnostic.message;
        });

    if (!duplicate) {
        diagnostics.append(diagnostic);
    }

    if (matchedEditor) {
        applyCompilerDiagnostics(matchedEditor);
    }
}

void MainWindow::applyCompilerDiagnostics(CodeEditor *editor)
{
    if (!editor || editor->filePath().isEmpty()) {
        return;
    }

    const QString path = QFileInfo(editor->filePath()).absoluteFilePath();
    editor->setDiagnostics(m_compilerDiagnostics.value(path));
}

void MainWindow::appendOutputText(const QString &text, OutputKind kind)
{
    if (!m_outputPane || text.isEmpty()) {
        return;
    }

    QColor color;
    switch (kind) {
    case OutputKind::Header:
        color = m_theme.outputHeader;
        break;
    case OutputKind::Path:
        color = m_theme.outputPath;
        break;
    case OutputKind::Success:
        color = m_theme.outputSuccess;
        break;
    case OutputKind::Error:
        color = m_theme.outputError;
        break;
    case OutputKind::Warning:
        color = m_theme.outputWarning;
        break;
    case OutputKind::Muted:
        color = m_theme.outputMuted;
        break;
    case OutputKind::Normal:
        color = m_theme.outputNormal;
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

    m_editorFontPointSize =
        qBound(6,
               settings.value(QStringLiteral("editor/fontPointSize"), 10).toInt(),
               36);

    m_theme = defaultIDETheme();

    for (const IDEThemeColorField &field : ideThemeColorFields()) {
        const QString key =
            QStringLiteral("theme/") + QLatin1String(field.key);

        if (!settings.contains(key)) {
            continue;
        }

        const QColor colour(settings.value(key).toString());
        if (colour.isValid()) {
            m_theme.*(field.member) = colour;
        }
    }
}

void MainWindow::saveOptions() const
{
    QSettings settings(QStringLiteral("Sidbox"), QStringLiteral("SidboxIDE"));
    settings.setValue(
        QStringLiteral("editor/fontPointSize"),
        m_editorFontPointSize);

    for (const IDEThemeColorField &field : ideThemeColorFields()) {
        settings.setValue(
            QStringLiteral("theme/") + QLatin1String(field.key),
            ideThemeColorName(m_theme.*(field.member)));
    }
}
