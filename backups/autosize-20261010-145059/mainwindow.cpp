#include <QScrollArea>
#include "mainwindow.h"

#include "codeeditor.h"
#include "guidesigner.h"
#include "optionsdialog.h"
#include "findreplacedialog.h"
#include "projectsettingsdialog.h"
#include "ui_mainwindow.h"

#include <algorithm>
#include <QSet>
#include <QAction>
#include <QApplication>
#include <QClipboard>
#include <QCloseEvent>
#include <QColor>
#include <QCheckBox>
#include <QComboBox>
#include <QFormLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QSignalBlocker>
#include <QSize>
#include <QSpinBox>
#include <QToolButton>
#include <QAbstractButton>
#include <QAbstractItemView>
#include <QCoreApplication>
#include <QDir>
#include <QDirIterator>
#include <QDrag>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QFile>
#include <QFileSystemWatcher>
#include <QFileDialog>
#include <QFileInfo>
#include <QFrame>
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
#include <QMimeData>
#include <QPlainTextEdit>
#include <QPixmap>
#include <QPainter>
#include <QPushButton>
#include <QPoint>
#include <QProcess>
#include <QProgressBar>
#include <QPointer>
#include <QRegularExpression>
#include <QRunnable>
#include <QThreadPool>
#include <QSaveFile>
#include <QScrollBar>
#include <QSettings>
#include <QSplitter>
#include <QStatusBar>
#include <QTabWidget>
#include <QTabBar>
#include <QTextCharFormat>
#include <QTextBlock>
#include <QTextBrowser>
#include <QTextCursor>
#include <QTextDocument>
#include <QTextStream>
#include <QTimer>
#include <QToolBar>
#include <QVBoxLayout>
#include <QVariant>
#include <QStandardPaths>
#include <QStyle>
#include <functional>
#include <utility>

namespace {
constexpr int ProjectFileVersion = 2;
const QString GuiProjectType = QStringLiteral("gui");
const QString GameProjectType = QStringLiteral("game");

QString normalizedAppOutputName(const QString &name)
{
    QString clean = name.trimmed();
    if (clean.isEmpty()) {
        return {};
    }

    /*
     * This setting is a filename, not an output path. Keeping the generated
     * app beside the project makes builds predictable and prevents accidental
     * path traversal if a project file is edited by hand.
     */
    clean = QFileInfo(clean).fileName();

    if (clean.isEmpty()
        || clean == QStringLiteral(".")
        || clean == QStringLiteral("..")) {
        return {};
    }

    if (!clean.endsWith(QStringLiteral(".app"),
                        Qt::CaseInsensitive)) {
        clean += QStringLiteral(".app");
    }

    return clean;
}


bool isResourceSource(const QString &filePath)
{
    return QFileInfo(filePath).suffix().compare(
               QStringLiteral("res"), Qt::CaseInsensitive) == 0;
}

bool isCompilableSource(const QString &filePath)
{
    const QString suffix = QFileInfo(filePath).suffix().toLower();
    return suffix == QStringLiteral("c")
        || suffix == QStringLiteral("cc")
        || suffix == QStringLiteral("cpp")
        || suffix == QStringLiteral("res");
}

bool isProjectExplorerSuffix(const QString &suffix)
{
    const QString lower = suffix.toLower();
    return lower == QStringLiteral("c") || lower == QStringLiteral("h")
        || lower == QStringLiteral("inc") || lower == QStringLiteral("txt")
        || lower == QStringLiteral("md") || lower == QStringLiteral("res")
        || lower == QStringLiteral("sbui") || lower == QStringLiteral("uis");
}

QIcon editorTabIconForFile(const QString &filePath,
                           int defaultType = 0)
{
    QString suffix = QFileInfo(filePath).suffix().toLower();

    /*
     * Untitled tabs have no file path yet, so use the same defaultType
     * convention as tabTitleForEditor():
     *   0 = C source, 1 = header, 2 = include.
     */
    if (suffix.isEmpty()) {
        if (defaultType == 1) {
            suffix = QStringLiteral("h");
        } else if (defaultType == 2) {
            suffix = QStringLiteral("inc");
        } else {
            suffix = QStringLiteral("c");
        }
    }

    if (suffix == QStringLiteral("c")
        || suffix == QStringLiteral("uis")
        || suffix == QStringLiteral("cc")
        || suffix == QStringLiteral("cpp")) {
        return QIcon(QStringLiteral(":/icons/tree_file_c.png"));
    }

    if (suffix == QStringLiteral("h")
        || suffix == QStringLiteral("hpp")) {
        return QIcon(QStringLiteral(":/icons/tree_file_h.png"));
    }

    if (suffix == QStringLiteral("inc")) {
        return QIcon(QStringLiteral(":/icons/tree_file_inc.png"));
    }

    if (suffix == QStringLiteral("res")) {
        return QIcon(QStringLiteral(":/icons/tree_file_res.png"));
    }

    if (suffix == QStringLiteral("txt")) {
        return QIcon(QStringLiteral(":/icons/tree_file_txt.png"));
    }

    if (suffix == QStringLiteral("sbui")) {
        return QIcon(QStringLiteral(":/icons/tree_guidesigner.png"));
    }

    if (suffix == QStringLiteral("md")) {
        return QIcon(QStringLiteral(":/icons/tree_file_md.png"));
    }

    return QIcon(QStringLiteral(":/icons/tree_file_unknown.png"));
}


QIcon projectFileIconWithErrorBadge(
    const QIcon &baseIcon,
    const QColor &errorColour)
{
    /*
     * Reuse the normal project-file icon and paint a small red diagnostic dot in
     * its lower-right corner. No extra resource image is needed.
     */
    constexpr int IconSize = 20;
    constexpr int BadgeSize = 8;

    QPixmap pixmap =
        baseIcon.pixmap(
            IconSize,
            IconSize);

    if (pixmap.isNull()) {
        pixmap =
            QPixmap(
                IconSize,
                IconSize);

        pixmap.fill(
            Qt::transparent);
    }

    QPainter painter(&pixmap);
    painter.setRenderHint(
        QPainter::Antialiasing,
        true);

    const QRect badgeRect(
        qMax(0, pixmap.width() - BadgeSize - 1),
        qMax(0, pixmap.height() - BadgeSize - 1),
        BadgeSize,
        BadgeSize);

    painter.setPen(
        QColor(
            20,
            20,
            20));

    painter.setBrush(
        errorColour);

    painter.drawEllipse(
        badgeRect);

    return QIcon(pixmap);
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
    if (suffix == QStringLiteral("res")
        || suffix == QStringLiteral("sbui")) {
        return false;
    }
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

    // MEMALIGN4/8/16/32: display metadata, not part of the C identifier.
    bool aligned = false;
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


QVariantList structureNavigationLines(
    const SourceSymbolTable &symbols)
{
    QList<int> lines;

    for (const SourceNamedSymbol &type :
         symbols.types) {
        if (type.line >= 0) {
            lines.append(type.line);
        }
    }

    for (const SourceFunctionSymbol &function :
         symbols.functions) {
        if (function.line >= 0) {
            lines.append(function.line);
        }
    }

    std::sort(
        lines.begin(),
        lines.end());

    lines.erase(
        std::unique(
            lines.begin(),
            lines.end()),
        lines.end());

    QVariantList result;
    result.reserve(lines.size());

    for (int line : std::as_const(lines)) {
        result.append(line);
    }

    return result;
}


void populateSourceSymbolTree(
    QTreeWidget *tree,
    const SourceSymbolTable &symbols)
{
    if (!tree) {
        return;
    }

    tree->setUpdatesEnabled(false);

    const QIcon functionIcon(
        QStringLiteral(
            ":/icons/tree_scope_function.png"));

    const QIcon globalIcon(
        QStringLiteral(
            ":/icons/tree_scope_globals.png"));

    const QIcon typeIcon(
        QStringLiteral(
            ":/icons/tree_scope_types.png"));

    const QIcon defineIcon(
        QStringLiteral(
            ":/icons/tree_scope_defines.png"));

    const QIcon parameterIcon(
        QStringLiteral(
            ":/icons/tree_scope_params.png"));

    const QIcon localIcon(
        QStringLiteral(
            ":/icons/tree_scope_locals.png"));

    auto addNoneItem =
        [](QTreeWidgetItem *parent) {
            auto *noneItem =
                new QTreeWidgetItem(parent);

            noneItem->setText(
                0,
                QObject::tr("(none)"));

            noneItem->setFlags(
                noneItem->flags()
                & ~Qt::ItemIsSelectable);
        };

    auto *definesItem =
        new QTreeWidgetItem(tree);

    definesItem->setText(
        0,
        QObject::tr("Defines"));

    definesItem->setIcon(
        0,
        defineIcon);

    definesItem->setExpanded(false);

    if (symbols.defines.isEmpty()) {
        addNoneItem(definesItem);
    } else {
        for (const SourceNamedSymbol &define :
             symbols.defines) {
            auto *item =
                new QTreeWidgetItem(
                    definesItem);

            item->setText(
                0,
                define.name);

            item->setIcon(
                0,
                defineIcon);

            item->setData(
                0,
                Qt::UserRole,
                define.line);

            item->setToolTip(
                0,
                QObject::tr(
                    "#define — double-click to jump to line %1")
                    .arg(define.line + 1));
        }

        definesItem->setText(
            0,
            QStringLiteral("Defines (%1)")
                .arg(
                    definesItem->childCount()));
    }

    definesItem->setData(
        0,
        Qt::UserRole + 10,
        QStringLiteral("defines"));

    auto *typesItem =
        new QTreeWidgetItem(tree);

    typesItem->setText(
        0,
        QObject::tr("Types"));

    typesItem->setIcon(
        0,
        typeIcon);

    typesItem->setExpanded(false);

    if (symbols.types.isEmpty()) {
        addNoneItem(typesItem);
    } else {
        for (const SourceNamedSymbol &type :
             symbols.types) {
            auto *item =
                new QTreeWidgetItem(
                    typesItem);

            item->setText(
                0,
                type.name);

            item->setIcon(
                0,
                typeIcon);

            item->setData(
                0,
                Qt::UserRole,
                type.line);

            item->setToolTip(
                0,
                QObject::tr(
                    "Type — double-click to jump to line %1")
                    .arg(type.line + 1));

            item->setData(
                0,
                Qt::UserRole + 10,
                QStringLiteral("type:%1")
                    .arg(type.name));

            for (const SourceVariableSymbol &member :
                 type.members) {
                auto *memberItem =
                    new QTreeWidgetItem(item);

                memberItem->setText(
                    0,
                    member.name);

                memberItem->setIcon(
                    0,
                    localIcon);

                memberItem->setData(
                    0,
                    Qt::UserRole,
                    member.line);

                memberItem->setToolTip(
                    0,
                    QObject::tr(
                        "Member — double-click to jump to line %1")
                        .arg(member.line + 1));
            }
        }

        typesItem->setText(
            0,
            QStringLiteral("Types (%1)")
                .arg(
                    typesItem->childCount()));
    }

    typesItem->setData(
        0,
        Qt::UserRole + 10,
        QStringLiteral("types"));

    auto *globalsItem =
        new QTreeWidgetItem(tree);

    globalsItem->setText(
        0,
        QObject::tr("Globals"));

    globalsItem->setIcon(
        0,
        globalIcon);

    globalsItem->setExpanded(false);

    if (symbols.globals.isEmpty()) {
        addNoneItem(globalsItem);
    } else {
        for (const SourceVariableSymbol &global :
             symbols.globals) {
            auto *item =
                new QTreeWidgetItem(
                    globalsItem);

            item->setText(
                0,
                global.name
                    + global.arraySuffix
                    + (global.aligned ? QStringLiteral(" (aligned)") : QString()));

            item->setIcon(
                0,
                globalIcon);

            item->setData(
                0,
                Qt::UserRole,
                global.line);

            item->setToolTip(
                0,
                QObject::tr(
                    "Global — double-click to jump to line %1")
                    .arg(global.line + 1));
        }

        globalsItem->setText(
            0,
            QStringLiteral("Globals (%1)")
                .arg(
                    globalsItem->childCount()));
    }

    globalsItem->setData(
        0,
        Qt::UserRole + 10,
        QStringLiteral("globals"));

    auto *functionsItem =
        new QTreeWidgetItem(tree);

    functionsItem->setText(
        0,
        QObject::tr("Functions"));

    functionsItem->setExpanded(false);

    functionsItem->setIcon(
        0,
        functionIcon);

    functionsItem->setData(
        0,
        Qt::UserRole + 10,
        QStringLiteral("functions"));

    if (symbols.functions.isEmpty()) {
        addNoneItem(functionsItem);
    } else {
        for (const SourceFunctionSymbol &function :
             symbols.functions) {
            auto *functionItem =
                new QTreeWidgetItem(
                    functionsItem);

            functionItem->setText(
                0,
                function.signature);

            functionItem->setIcon(
                0,
                functionIcon);

            functionItem->setData(
                0,
                Qt::UserRole,
                function.line);

            functionItem->setToolTip(
                0,
                QObject::tr(
                    "Function — double-click to jump to line %1")
                    .arg(function.line + 1));

            functionItem->setData(
                0,
                Qt::UserRole + 10,
                QStringLiteral("function:%1")
                    .arg(function.signature));

            if (!function.parameters.isEmpty()) {
                auto *parametersItem =
                    new QTreeWidgetItem(
                        functionItem);

                parametersItem->setText(
                    0,
                    QObject::tr("Parameters"));

                parametersItem->setIcon(
                    0,
                    parameterIcon);

                parametersItem->setExpanded(true);

                for (const SourceVariableSymbol &parameter :
                     function.parameters) {
                    auto *item =
                        new QTreeWidgetItem(
                            parametersItem);

                    item->setText(
                        0,
                        parameter.name
                            + parameter.arraySuffix
                            + (parameter.aligned ? QStringLiteral(" (aligned)") : QString()));

                    item->setIcon(
                        0,
                        parameterIcon);

                    item->setData(
                        0,
                        Qt::UserRole,
                        parameter.line);

                    item->setToolTip(
                        0,
                        QObject::tr(
                            "Parameter — double-click to jump to function"));
                }

                parametersItem->setData(
                    0,
                    Qt::UserRole + 10,
                    QStringLiteral(
                        "function:%1:parameters")
                        .arg(function.signature));
            }

            if (!function.locals.isEmpty()) {
                auto *localsItem =
                    new QTreeWidgetItem(
                        functionItem);

                localsItem->setText(
                    0,
                    QObject::tr("Locals"));

                localsItem->setIcon(
                    0,
                    localIcon);

                localsItem->setExpanded(true);

                for (const SourceVariableSymbol &local :
                     function.locals) {
                    auto *item =
                        new QTreeWidgetItem(
                            localsItem);

                    item->setText(
                        0,
                        local.name
                            + local.arraySuffix
                            + (local.aligned ? QStringLiteral(" (aligned)") : QString()));

                    item->setIcon(
                        0,
                        localIcon);

                    item->setData(
                        0,
                        Qt::UserRole,
                        local.line);

                    item->setToolTip(
                        0,
                        QObject::tr(
                            "Local — double-click to jump to line %1")
                            .arg(local.line + 1));
                }

                localsItem->setData(
                    0,
                    Qt::UserRole + 10,
                    QStringLiteral(
                        "function:%1:locals")
                        .arg(function.signature));
            }
        }

        functionsItem->setText(
            0,
            QStringLiteral("Functions (%1)")
                .arg(
                    functionsItem->childCount()));
    }

    tree->setUpdatesEnabled(true);
    tree->viewport()->update();
}

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

    /*
     * Do not allocate source.left(...) for every symbol. Large generated files
     * may contain thousands of symbols; repeatedly copying prefixes turns a
     * simple line lookup into a surprising amount of memory churn.
     */
    const int limit =
        qMin(offset, source.size());

    int line = 0;

    for (int i = 0; i < limit; ++i) {
        if (source.at(i)
            == QLatin1Char('\n')) {
            ++line;
        }
    }

    return line;
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

    // Alignment macros decorate the variable, they are not its type.
    static const QRegularExpression alignmentExpression(
        QStringLiteral(R"(\bMEMALIGN(?:4|8|16|32)\b)"));
    typePart.remove(alignmentExpression);
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

    static const QRegularExpression alignmentExpression(
        QStringLiteral(R"(\bMEMALIGN(?:4|8|16|32)\b)"));

    for (const QString &declarator : declarators) {
        const QString name = variableNameFromDeclarator(declarator);
        if (!name.isEmpty()) {
            // Look only before the symbol itself: initializer contents must
            // not make an otherwise unaligned variable appear aligned.
            const int namePos = declarator.indexOf(
                QRegularExpression(QStringLiteral(R"(\b%1\b)")
                    .arg(QRegularExpression::escape(name))));
            const bool isAligned = namePos > 0
                && alignmentExpression.match(declarator.left(namePos)).hasMatch();

            symbols.append({
                name,
                line,
                declarationType,
                arraySuffixFromDeclarator(declarator, name),
                isExternDeclaration,
                isAligned
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
            R"((?:^|[\n;{}])\s*((?:(?:const|volatile|static|extern|register)\s+)*(?:(?:struct|union|enum)\s+)?[A-Za-z_][A-Za-z0-9_]*(?:\s*\*)*(?:\s+MEMALIGN(?:4|8|16|32))?\s+[A-Za-z_][A-Za-z0-9_]*\s*(?:\[[^\]]*\]\s*)+\s*=\s*\{))"),
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

QList<SourceNamedSymbol> defineSymbolsFromSource(
    const QString &source,
    const QString &sanitized)
{
    QList<SourceNamedSymbol> symbols;

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

QList<SourceNamedSymbol> typeSymbolsFromSource(
    const QString &source,
    const QString &sanitized)
{
    QList<SourceNamedSymbol> symbols;

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

QStringList functionSignaturesFromSanitizedFast(
    const QString &source,
    const QString &sanitized)
{
    /*
     * Fast completion catalogue: one linear pass, no regex backtracking.
     *
     * We only care about global function declarations/definitions here. The
     * detailed symbol browser still uses parseSourceSymbols(), but it runs in a
     * background worker. This scanner is deliberately tiny and predictable for
     * 100-200 KB generated files.
     */
    QStringList signatures;

    static const QSet<QString> ignoredNames = {
        QStringLiteral("if"),
        QStringLiteral("for"),
        QStringLiteral("while"),
        QStringLiteral("switch"),
        QStringLiteral("return"),
        QStringLiteral("sizeof"),
        QStringLiteral("__attribute__"),
        QStringLiteral("__declspec")
    };

    int braceDepth = 0;

    for (int i = 0; i < sanitized.size(); ++i) {
        const QChar ch =
            sanitized.at(i);

        if (ch == QLatin1Char('{')) {
            ++braceDepth;
            continue;
        }

        if (ch == QLatin1Char('}')) {
            braceDepth =
                qMax(0, braceDepth - 1);
            continue;
        }

        if (braceDepth != 0
            || ch != QLatin1Char('(')) {
            continue;
        }

        int nameEnd = i - 1;

        while (nameEnd >= 0
               && sanitized.at(nameEnd).isSpace()) {
            --nameEnd;
        }

        if (nameEnd < 0
            || !(sanitized.at(nameEnd).isLetterOrNumber()
                 || sanitized.at(nameEnd)
                    == QLatin1Char('_'))) {
            continue;
        }

        int nameStart = nameEnd;

        while (nameStart > 0) {
            const QChar prev =
                sanitized.at(nameStart - 1);

            if (!prev.isLetterOrNumber()
                && prev != QLatin1Char('_')) {
                break;
            }

            --nameStart;
        }

        const QString name =
            sanitized.mid(
                nameStart,
                nameEnd - nameStart + 1);

        if (name.isEmpty()
            || ignoredNames.contains(name)) {
            continue;
        }

        int parenDepth = 1;
        int closeParen = -1;

        for (int j = i + 1;
             j < sanitized.size();
             ++j) {
            const QChar inner =
                sanitized.at(j);

            if (inner == QLatin1Char('(')) {
                ++parenDepth;
            } else if (inner
                       == QLatin1Char(')')) {
                --parenDepth;

                if (parenDepth == 0) {
                    closeParen = j;
                    break;
                }
            }
        }

        if (closeParen < 0) {
            break;
        }

        int after =
            closeParen + 1;

        while (after < sanitized.size()
               && sanitized.at(after).isSpace()) {
            ++after;
        }

        if (after >= sanitized.size()
            || (sanitized.at(after)
                    != QLatin1Char(';')
                && sanitized.at(after)
                    != QLatin1Char('{'))) {
            i = closeParen;
            continue;
        }

        /*
         * A function needs a declaration/type before its name. This rejects
         * macro-ish "(...)" constructs and most accidental expression hits.
         */
        int declarationStart =
            nameStart - 1;

        while (declarationStart >= 0) {
            const QChar before =
                sanitized.at(declarationStart);

            if (before == QLatin1Char(';')
                || before == QLatin1Char('}')
                || before == QLatin1Char('{')) {
                ++declarationStart;
                break;
            }

            --declarationStart;
        }

        declarationStart =
            qMax(0, declarationStart);

        if (sanitized
                .mid(
                    declarationStart,
                    nameStart - declarationStart)
                .trimmed()
                .isEmpty()) {
            i = closeParen;
            continue;
        }

        const QString arguments =
            source.mid(
                      i + 1,
                      closeParen - i - 1)
                .simplified();

        signatures.append(
            QStringLiteral("%1(%2)")
                .arg(
                    name,
                    arguments));

        i = closeParen;
    }

    signatures.removeDuplicates();
    signatures.sort(Qt::CaseInsensitive);
    return signatures;
}


SourceSymbolTable parseSourceSymbolsFromSanitized(
    const QString &source,
    const QString &sanitized,
    const std::function<void(int)> &progress = {})
{
    SourceSymbolTable table;

    if (progress) {
        progress(25);
    }

    table.defines =
        defineSymbolsFromSource(
            source,
            sanitized);

    if (progress) {
        progress(35);
    }

    table.types =
        typeSymbolsFromSource(
            source,
            sanitized);

    if (progress) {
        progress(52);
    }

    QString globalsOnly = sanitized;

    // Struct/typedef members are fields of their type, not globals.
    maskTypeDeclarations(&globalsOnly);

    if (progress) {
        progress(58);
    }

    static const QRegularExpression functionExpression(
        QStringLiteral(
            "(?:^|\\n)\\s*"
            "((?:(?:static|inline|extern|const|volatile|unsigned|signed|long|short|struct\\s+[A-Za-z_][A-Za-z0-9_]*|enum\\s+[A-Za-z_][A-Za-z0-9_]*|union\\s+[A-Za-z_][A-Za-z0-9_]*|[A-Za-z_][A-Za-z0-9_]*)\\s+|[*]+\\s*)+)"
            "([A-Za-z_][A-Za-z0-9_]*)\\s*"
            "\\(([^;{}]*)\\)\\s*\\{"),
        QRegularExpression::MultilineOption);

    QRegularExpressionMatchIterator iterator = functionExpression.globalMatch(sanitized);
    int lastFunctionProgress = 58;

    while (iterator.hasNext()) {
        const QRegularExpressionMatch match = iterator.next();

        if (progress
            && !sanitized.isEmpty()) {
            const int scanProgress =
                58
                + qBound(
                    0,
                    (match.capturedStart(0) * 24)
                        / qMax(
                            1,
                            static_cast<int>(
                                sanitized.size())),
                    24);

            if (scanProgress > lastFunctionProgress) {
                lastFunctionProgress =
                    scanProgress;

                progress(
                    scanProgress);
            }
        }
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

    if (progress) {
        progress(84);
    }

    table.globals =
        variableSymbolsInRange(
            globalsOnly,
            source,
            0,
            globalsOnly.size());

    if (progress) {
        progress(92);
    }

    return table;
}

SourceSymbolTable parseSourceSymbols(
    const QString &source)
{
    const QString sanitized =
        sanitizedCSource(source);

    return parseSourceSymbolsFromSanitized(
        source,
        sanitized);
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
    , m_compileProgressDelayTimer(new QTimer(this))
    , m_fileWatcher(new QFileSystemWatcher(this))
    , m_buildStep(BuildStep::None)
    , m_projectType(GuiProjectType)
    , m_modSizeKb(0)
    , m_appSizeKb(128)
    , m_v2HeapKb(16)
    , m_v2StackKb(8)
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
    /*
     * Ordinary typing only restarts this idle timer. No whole-document semantic,
     * fold, minimap or typedef scan runs while characters are continuously
     * arriving. Two seconds after the LAST edit, synchronise the active tab.
     */
    m_projectAnalysisTimer->setInterval(2000);
    connect(m_projectAnalysisTimer, &QTimer::timeout, this, [this]() {
        CodeEditor *editor = activeEditor();

        if (editor) {
            /*
             * Local fold/minimap catalogues are cooperative event-loop jobs.
             * The semantic/tree catalogue is a background worker.
             */
            editor->syncDeferredEditorStateNow();
        }

        refreshActiveEditorAnalysis();
    });

    /*
     * Reload open files when another editor/tool writes them on disk.
     * A short debounce handles editors which save by writing a temporary file
     * and renaming it over the original.
     */
    connect(m_fileWatcher, &QFileSystemWatcher::fileChanged,
            this, &MainWindow::handleExternalFileChange);

    /*
     * Fast Sidbox builds often finish before a progress indicator is useful.
     * Wait briefly before showing the busy bar so sub-180 ms builds stay
     * visually clean instead of flashing a widget on and off.
     */
    m_compileProgressDelayTimer->setSingleShot(true);
    m_compileProgressDelayTimer->setInterval(180);
    connect(m_compileProgressDelayTimer, &QTimer::timeout, this, [this]() {
        if (m_buildStep != BuildStep::None && m_compileProgressBar) {
            m_compileProgressBar->show();
        }
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
        const QString toolName = m_buildStep == BuildStep::Objcopy ? tr("packer / objcopy") :
            m_buildStep == BuildStep::Linking && m_currentBuildIsV2 ? tr("LLVM linker") : tr("compiler");
        appendOutputLine(tr("Could not start %1. Check that the IDE's bundled toolchain exists.").arg(toolName), OutputKind::Error);
        m_buildStep = BuildStep::None;
        finishCompileProgress();
        statusBar()->showMessage(tr("Compile failed"));
    });
    connect(m_compilerProcess, &QProcess::finished, this, &MainWindow::handleCompilerFinished);

    //createNewSourceFile();
    //createNewHeaderFile();

    //AutoSelectMainC();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::closeEditorTab(int index)
{
    if (!m_editorTabs
        || index < 0
        || index >= m_editorTabs->count()) {
        return false;
    }

    QWidget *widget =
        m_editorTabs->widget(index);

    if (!widget) {
        return false;
    }

    if (auto *designer = dynamic_cast<SidboxGuiDesigner *>(widget)) {
        if (designer->isModified()) {
            QMessageBox box(this);
            box.setIcon(QMessageBox::Warning);
            box.setWindowTitle(tr("Unsaved GUI Design"));
            box.setText(tr("Save changes to %1 before closing?").arg(QFileInfo(designer->filePath()).fileName()));
            QPushButton *saveButton = box.addButton(QMessageBox::Save);
            QPushButton *discardButton = box.addButton(QMessageBox::Discard);
            box.addButton(QMessageBox::Cancel);
            box.setDefaultButton(saveButton);
            box.exec();
            if (box.clickedButton() == saveButton) {
                if (!designer->saveDesignAndGenerate()) return false;
            } else if (box.clickedButton() != discardButton) {
                return false;
            }
        }
        m_editorTabs->removeTab(index);
        widget->deleteLater();
        return true;
    }

    CodeEditor *editor =
        primaryEditorForTab(widget);

    if (editor
        && editor->document()
        && editor->document()->isModified()) {
        const QMessageBox::StandardButton reply =
            QMessageBox::question(
                this,
                tr("Unsaved Changes"),
                tr("You're about to close an unsaved tab, proceed?"),
                QMessageBox::Yes | QMessageBox::No,
                QMessageBox::No);

        if (reply != QMessageBox::Yes) {
            return false;
        }
    }

    if (editor) {
        /*
         * A split pane can temporarily borrow the QTextDocument belonging to
         * another normal tab. If that borrowed tab is being closed, restore
         * the split's secondary pane to its host document before deleting the
         * tab so the split never holds a dangling document pointer.
         */
        QSplitter *splitter =
            editorSplitWidget();

        if (splitter
            && m_editorTabs->widget(index)
                != splitter) {
            CodeEditor *host =
                splitHostEditor(splitter);

            CodeEditor *secondary =
                splitSecondaryEditor(splitter);

            if (host
                && secondary
                && secondary->document()
                    == editor->document()) {
                secondary->setProperty(
                    "sidboxApiReference",
                    host->property(
                        "sidboxApiReference"));

                secondary->shareDocumentFrom(host);
                secondary->setTextCursor(
                    host->textCursor());
                secondary->setDiagnostics(
                    host->diagnostics());

                updateEditorSplitPresentation();
            }
        }

        unwatchEditorFile(editor);
    }

    m_editorTabs->removeTab(index);
    widget->deleteLater();

    /*
     * Closing one or many source tabs can change which in-memory source wins
     * over the on-disk copy. The timer is single-shot, so a bulk close naturally
     * coalesces into one project-analysis refresh after the menu operation.
     */
    m_projectAnalysisTimer->start();

    return true;
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    if (!event) {
        return;
    }

    const auto savePaneLayout = [this]() {
        auto *splitter = findChild<QSplitter *>(QStringLiteral("mainThreePaneSplitter"));
        if (!splitter) return;
        QSettings settings(QStringLiteral("Sidbox"), QStringLiteral("SidboxIDE"));
        settings.setValue(QStringLiteral("layout/projectTreeWidth"),
                          splitter->property("projectTreeWidth").toInt());
        settings.setValue(QStringLiteral("layout/editorRightWidth"),
                          splitter->property("editorRightWidth").toInt());
    };

    QList<SidboxGuiDesigner *> unsavedDesigners;
    for (int i = 0; i < m_editorTabs->count(); ++i) {
        if (auto *designer = dynamic_cast<SidboxGuiDesigner *>(m_editorTabs->widget(i))) {
            if (designer->isModified()) unsavedDesigners.append(designer);
        }
    }

    if (!unsavedDesigners.isEmpty()) {
        QMessageBox box(this);
        box.setIcon(QMessageBox::Warning);
        box.setWindowTitle(tr("Unsaved GUI Designs"));
        box.setText(tr("There are %1 unsaved CoderGirl GUI design(s).").arg(unsavedDesigners.size()));
        box.setInformativeText(tr("Save them and regenerate their .c files before closing Sidbox IDE?"));
        QPushButton *saveButton = box.addButton(QMessageBox::Save);
        QPushButton *discardButton = box.addButton(QMessageBox::Discard);
        box.addButton(QMessageBox::Cancel);
        box.setDefaultButton(saveButton);
        box.exec();
        if (box.clickedButton() == saveButton) {
            for (SidboxGuiDesigner *designer : unsavedDesigners) {
                if (!designer->saveDesignAndGenerate()) { event->ignore(); return; }
            }
        } else if (box.clickedButton() != discardButton) {
            event->ignore();
            return;
        }
    }

    QList<CodeEditor *> unsavedEditors;
    QStringList unsavedNames;

    /*
     * Only inspect each tab's primary editor. Split views can share the same
     * QTextDocument, so walking every CodeEditor widget would report the same
     * modified file twice.
     */
    for (int i = 0;
         i < m_editorTabs->count();
         ++i) {
        CodeEditor *editor =
            primaryEditorForTab(
                m_editorTabs->widget(i));

        if (!editor) {
            continue;
        }

        const bool untitledHasWork =
            editor->filePath().isEmpty()
            && !editor->toPlainText().isEmpty();

        if (!editor->document()->isModified()
            && !untitledHasWork) {
            continue;
        }

        unsavedEditors.append(editor);

        QString name =
            editor->filePath().isEmpty()
                ? tabTitleForEditor(editor)
                      .remove(QLatin1Char('*'))
                : QFileInfo(editor->filePath())
                      .fileName();

        if (name.isEmpty()) {
            name = tr("Untitled source");
        }

        unsavedNames.append(name);
    }

    if (unsavedEditors.isEmpty()) {
        savePaneLayout();
        event->accept();
        return;
    }

    QString details;

    const int shownCount =
        qMin(8, unsavedNames.size());

    for (int i = 0; i < shownCount; ++i) {
        details +=
            QStringLiteral("\n  • %1")
                .arg(unsavedNames.at(i));
    }

    if (unsavedNames.size() > shownCount) {
        details +=
            tr("\n  • ...and %1 more")
                .arg(
                    unsavedNames.size()
                    - shownCount);
    }

    QMessageBox box(this);
    box.setIcon(QMessageBox::Warning);
    box.setWindowTitle(tr("Unsaved Work"));
    box.setText(
        unsavedEditors.size() == 1
            ? tr("There is 1 file with unsaved work.")
            : tr("There are %1 files with unsaved work.")
                  .arg(unsavedEditors.size()));

    box.setInformativeText(
        tr("Save before closing Sidbox IDE?%1")
            .arg(details));

    QPushButton *saveButton =
        box.addButton(
            tr("Save"),
            QMessageBox::AcceptRole);

    QPushButton *discardButton =
        box.addButton(
            tr("Discard"),
            QMessageBox::DestructiveRole);

    QPushButton *cancelButton =
        box.addButton(
            QMessageBox::Cancel);

    box.setDefaultButton(saveButton);
    box.setEscapeButton(cancelButton);
    box.exec();

    QAbstractButton *clicked =
        box.clickedButton();

    if (clicked == cancelButton
        || !clicked) {
        event->ignore();
        return;
    }

    if (clicked == discardButton) {
        savePaneLayout();
        event->accept();
        return;
    }

    if (clicked != saveButton) {
        event->ignore();
        return;
    }

    /*
     * Save only the files that actually need attention. Untitled tabs naturally
     * use the existing Save As dialog through saveEditor(). If the user cancels
     * any Save As, abort the IDE shutdown so nothing is lost accidentally.
     */
    for (CodeEditor *editor :
         std::as_const(unsavedEditors)) {
        if (!editor) {
            continue;
        }

        if (!saveEditor(editor)) {
            event->ignore();
            statusBar()->showMessage(
                tr("Close cancelled — unsaved work remains"),
                3000);
            return;
        }
    }

    /*
     * If this is a normal saved project, persist the tab/project metadata too.
     * Do not force a .proj Save As when the user is simply working from loose
     * files in an empty IDE session.
     */
    if (!m_projectFilePath.isEmpty()) {
        if (!saveProjectFile(
                m_projectFilePath)) {
            event->ignore();
            statusBar()->showMessage(
                tr("Close cancelled — project could not be saved"),
                3000);
            return;
        }
    }

    savePaneLayout();
    event->accept();
}


void MainWindow::showStartupProjectChooser()
{
    /*
     * Do this after the main window has been shown. Starting with an empty IDE
     * is much less confusing than creating untitled editor tabs and then asking
     * the programmer what they actually wanted to do.
     */
    QMessageBox chooser(this);
    chooser.setWindowTitle(tr("Sidbox IDE"));
    chooser.setIcon(QMessageBox::Question);
    chooser.setText(tr("What would you like to do?"));
    chooser.setInformativeText(
        tr("Create a new Sidbox project or load an existing .proj file."));

    QPushButton *newProjectButton =
        chooser.addButton(
            tr("Create New Project"),
            QMessageBox::AcceptRole);

    QPushButton *loadProjectButton =
        chooser.addButton(
            tr("Load Existing Project"),
            QMessageBox::ActionRole);

    QPushButton *emptyButton =
        chooser.addButton(
            tr("Start Empty"),
            QMessageBox::RejectRole);

    chooser.setDefaultButton(loadProjectButton);
    chooser.exec();

    QAbstractButton *clicked = chooser.clickedButton();

    if (clicked == newProjectButton) {
        createNewProject();
        return;
    }

    if (clicked == loadProjectButton) {
        openProject();
        return;
    }

    Q_UNUSED(emptyButton);
    statusBar()->showMessage(
        tr("Ready — create or open a project when you are ready"),
        4000);
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

        QProgressBar {
            background-color: #050505;
            color: #ffffff;
            border: 1px solid #303030;
            border-radius: 0px;
            text-align: center;
        }

        QProgressBar::chunk {
            background-color: #2858A8;
            border-radius: 0px;
            width: 18px;
            margin: 1px;
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

    QAction *newAction = toolBar->addAction(QIcon(":/icons/new_project.png"), tr("New"));
    //auto *newMenu = new QMenu(this);
    //QAction *newProjectAction = newMenu->addAction(tr("New Project"));
    //QAction *newSourceAction = newMenu->addAction(tr("New C Source File"));
    //QAction *newHeaderAction = newMenu->addAction(tr("New H Header File"));
    toolBar->addSeparator();
    //newAction->setMenu(newMenu);

    QAction *openProjectAction = toolBar->addAction(QIcon(":/icons/open_project.png"), tr("Open Project..."));
    QAction *saveProjectAction = toolBar->addAction(QIcon(":/icons/save_project.png"), tr("Save Project..."));
    toolBar->addSeparator();
    QAction *projectSettingsAction = toolBar->addAction(QIcon(":/icons/project_settings.png"), tr("Project Settings"));
    QAction *guiDesignerAction = toolBar->addAction(QIcon(":/icons/toolbar_guidesigner.png"), tr("GUI Designer"));
    guiDesignerAction->setToolTip(tr("Create a visual CoderGirl 480x320 GUI design"));
    QAction *optionsAction = toolBar->addAction(QIcon(":/icons/options.png"), tr("Options"));


    //QIcon findReplaceIcon = QIcon::fromTheme(QStringLiteral("edit-find-replace"));
    //if (findReplaceIcon.isNull()) {
        //findReplaceIcon = QIcon::fromTheme(QStringLiteral("edit-find"));
    //}

    QAction *findReplaceAction = toolBar->addAction(QIcon(":/icons/search_term.png"), tr("Find / Replace"));
    findReplaceAction->setShortcut(QKeySequence(QStringLiteral("Ctrl+Shift+F")));


    QAction *findCurrentWordAction = new QAction(tr("Find Current Word"), this);
    findCurrentWordAction->setShortcuts({
        QKeySequence(QStringLiteral("Ctrl+F")),
        QKeySequence(QStringLiteral("F3"))
    });
    addAction(findCurrentWordAction);

    toolBar->addSeparator();
    QAction *compileAction = toolBar->addAction(QIcon(":/icons/compile.png"), tr("Compile [F5]"));

    toolBar->addSeparator();
    QAction *apiCheatSheetAction = toolBar->addAction(QIcon(":/icons/toolbar_cheatsheet.png"), tr("Cheat Sheet [F8]"));
    apiCheatSheetAction->setShortcut(Qt::Key_F8);
    apiCheatSheetAction->setToolTip(tr("Open the searchable Sidbox API Cheat Sheet"));

    QAction *aboutIdeAction = toolBar->addAction(QIcon(":/icons/ide_icon_32x32.png"), tr("About IDE"));

    newAction->setShortcut(QKeySequence::New);
    openProjectAction->setShortcut(QKeySequence::Open);
    saveProjectAction->setShortcut(QKeySequence::Save);
    compileAction->setShortcut(Qt::Key_F5);

    //connect(newAction, &QAction::triggered, this, [toolBar, newAction, newMenu]() {
        //if (QWidget *button = toolBar->widgetForAction(newAction)) {
            //newMenu->popup(button->mapToGlobal(QPoint(0, button->height())));
        //}
    //});
    connect(newAction, &QAction::triggered, this, &MainWindow::createNewProject);
    //connect(newSourceAction, &QAction::triggered, this, &MainWindow::createNewSourceFile);
    //connect(newHeaderAction, &QAction::triggered, this, &MainWindow::createNewHeaderFile);
    connect(openProjectAction, &QAction::triggered, this, &MainWindow::openProject);
    connect(saveProjectAction, &QAction::triggered, this, &MainWindow::saveProject);
    connect(projectSettingsAction, &QAction::triggered, this, &MainWindow::showProjectSettings);
    connect(guiDesignerAction, &QAction::triggered, this, &MainWindow::createGuiDesigner);
    connect(optionsAction, &QAction::triggered, this, &MainWindow::showOptions);
    connect(aboutIdeAction, &QAction::triggered, this, &MainWindow::showAboutIde);
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
    //auto *addFileButton = new QPushButton(tr("Add"), projectPane);
    //auto *createFileButton = new QPushButton(tr("Create"), projectPane);
    //auto *resourceFileButton = new QPushButton(tr("Add Res"), projectPane);
    //resourceFileButton->setToolTip(tr("Create a lightweight .res C resource file"));
    //auto *rescanFilesButton = new QPushButton(tr("Rescan"), projectPane);
    //rescanFilesButton->setToolTip(tr("Rescan the project directory for supported project files"));
    //auto *removeFileButton = new QPushButton(tr("Remove"), projectPane);
    //projectButtonLayout->addWidget(addFileButton);
    //projectButtonLayout->addWidget(createFileButton);
    //projectButtonLayout->addWidget(resourceFileButton);
    //projectButtonLayout->addWidget(rescanFilesButton);
    //projectButtonLayout->addWidget(removeFileButton);

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
    //connect(addFileButton, &QPushButton::clicked, this, &MainWindow::addExistingProjectFile);
    //connect(createFileButton, &QPushButton::clicked, this, &MainWindow::createProjectFile);
    //connect(resourceFileButton, &QPushButton::clicked, this, &MainWindow::createResourceFile);
    //connect(rescanFilesButton, &QPushButton::clicked, this, &MainWindow::rescanProjectFiles);
    //connect(removeFileButton, &QPushButton::clicked, this, &MainWindow::removeSelectedProjectFile);
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

        menu.addAction(tr("Add Resource"), this, [this, targetDirectory]() {
            createResourceFileInDirectory(targetDirectory);
        });

        menu.addAction(tr("Create Folder"), this, [this, targetDirectory]() {
            createProjectFolderInDirectory(targetDirectory);
        });

        menu.addAction(tr("Create GUI Design"), this, &MainWindow::createGuiDesigner);
        menu.addAction(tr("Add File"), this, &MainWindow::addExistingProjectFile);
        menu.addAction(tr("Rescan Project Files"), this, &MainWindow::rescanProjectFiles);

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

    m_editorTabs->tabBar()->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(
        m_editorTabs->tabBar(),
        &QTabBar::customContextMenuRequested,
        this,
        [this](const QPoint &pos) {
            const int index =
                m_editorTabs->tabBar()->tabAt(pos);

            if (index < 0) {
                return;
            }

            /*
             * Right-clicking a tab makes it the active tab before showing the
             * menu. This also makes "Close Others / Left / Right" unambiguous:
             * they operate relative to the tab the user actually clicked.
             */
            m_editorTabs->setCurrentIndex(index);

            QWidget *tabWidget =
                m_editorTabs->widget(index);

            CodeEditor *editor =
                primaryEditorForTab(tabWidget);

            QMenu menu(this);

            QAction *splitAction = nullptr;

            if (editor) {
                const int splitIndex =
                    editorSplitTabIndex();

                const bool thisIsSplit =
                    splitIndex == index;

                QString splitText;

                if (thisIsSplit) {
                    splitText = tr("Close Split");
                } else if (splitIndex >= 0) {
                    splitText =
                        tr("Open in Existing Split...");
                } else {
                    splitText =
                        tr("Split Editor Left / Right");
                }

                splitAction =
                    menu.addAction(splitText);

                menu.addSeparator();
            }

            QAction *closeAction =
                menu.addAction(tr("Close"));

            QAction *closeOthersAction =
                menu.addAction(tr("Close All Other Tabs"));

            QAction *closeLeftAction =
                menu.addAction(tr("Close Tabs to the Left"));

            QAction *closeRightAction =
                menu.addAction(tr("Close Tabs to the Right"));

            closeOthersAction->setEnabled(
                m_editorTabs->count() > 1);

            closeLeftAction->setEnabled(
                index > 0);

            closeRightAction->setEnabled(
                index < m_editorTabs->count() - 1);

            QAction *chosen =
                menu.exec(
                    m_editorTabs->tabBar()
                        ->mapToGlobal(pos));

            if (!chosen) {
                return;
            }

            if (splitAction
                && chosen == splitAction) {
                const int splitIndex =
                    editorSplitTabIndex();

                const bool thisIsSplit =
                    splitIndex == index;

                if (splitIndex >= 0
                    && !thisIsSplit) {
                    openCurrentTabInExistingSplit();
                } else {
                    toggleCurrentEditorSplit();
                }

                return;
            }

            if (chosen == closeAction) {
                closeEditorTab(index);
                return;
            }

            if (chosen == closeOthersAction) {
                /*
                 * Work from right to left so removing a tab never invalidates
                 * the indexes we still need to visit. If the user keeps an
                 * unsaved tab at its confirmation prompt, that one simply
                 * remains open while the others continue closing.
                 */
                for (int i = m_editorTabs->count() - 1;
                     i >= 0;
                     --i) {
                    if (i != index) {
                        closeEditorTab(i);
                    }
                }
                return;
            }

            if (chosen == closeLeftAction) {
                for (int i = index - 1;
                     i >= 0;
                     --i) {
                    closeEditorTab(i);
                }
                return;
            }

            if (chosen == closeRightAction) {
                for (int i = m_editorTabs->count() - 1;
                     i > index;
                     --i) {
                    closeEditorTab(i);
                }
            }
        });

    connect(
        m_editorTabs,
        &QTabWidget::tabCloseRequested,
        this,
        [this](int index) {
            closeEditorTab(index);
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
        updateCursorPositionStatus();

        if (m_projectAnalysisTimer) {
            m_projectAnalysisTimer->stop();
        }

        /*
         * Changing tabs is an explicit navigation action. Let the tab paint,
         * then catch up any deferred state for the newly active source.
         */
        QTimer::singleShot(0, this, [this]() {
            CodeEditor *editor = activeEditor();

            if (editor) {
                editor->syncDeferredEditorStateNow();
                refreshActiveEditorAnalysis();
            } else if (m_functionvarList) {
                m_functionvarList->clear();
                if (dynamic_cast<SidboxGuiDesigner *>(m_editorTabs->currentWidget())) {
                    auto *item = new QTreeWidgetItem(m_functionvarList);
                    item->setText(0, tr("GUI Designer — visual CoderGirl layout"));
                    item->setFlags(item->flags() & ~Qt::ItemIsSelectable);
                }
            }
        });
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
    workAreaSplitter->setStretchFactor(0, 6);
    workAreaSplitter->setStretchFactor(1, 1);
    workAreaSplitter->setCollapsible(0, false);
    workAreaSplitter->setCollapsible(1, true);

    /*
     * Start with the editor occupying most of the work area. The output pane
     * remains freely resizable afterwards, but it no longer eats most of the
     * screen on launch.
     */
    workAreaSplitter->setSizes({850, 220});

    // Assembly of main horizontal splitter
    mainSplitter->addWidget(projectPane);
    mainSplitter->addWidget(workAreaSplitter);
    mainSplitter->addWidget(rightPane);

    mainSplitter->setStretchFactor(0, 1);
    mainSplitter->setStretchFactor(1, 5);
    mainSplitter->setStretchFactor(2, 1);
    mainSplitter->setSizes({300, 1200, 300});
    mainSplitter->setObjectName(QStringLiteral("mainThreePaneSplitter"));

    // Remember widths rather than restoring the complete splitter state. A
    // hidden right pane must never change the project tree's chosen width.
    QSettings paneSettings(QStringLiteral("Sidbox"), QStringLiteral("SidboxIDE"));
    const int projectWidth = qMax(80, paneSettings.value(
        QStringLiteral("layout/projectTreeWidth"), 300).toInt());
    const int editorRightWidth = qMax(80, paneSettings.value(
        QStringLiteral("layout/editorRightWidth"), 300).toInt());
    mainSplitter->setProperty("projectTreeWidth", projectWidth);
    mainSplitter->setProperty("editorRightWidth", editorRightWidth);
    mainSplitter->setProperty("switchingTabs", false);
    mainSplitter->setStretchFactor(0, 0);
    mainSplitter->setStretchFactor(1, 1);
    mainSplitter->setStretchFactor(2, 0);
    mainSplitter->setSizes({projectWidth, 1200, editorRightWidth});

    // One fixed-by-tab-switch project width; the user can still drag its handle.
    // In designer mode the right pane disappears and the editor fills that space.
    // In code mode the previously chosen right-pane width is restored.
    connect(m_editorTabs, &QTabWidget::currentChanged, this,
            [this, mainSplitter, rightPane](int) {
        const bool designing = dynamic_cast<SidboxGuiDesigner *>(
            m_editorTabs->currentWidget()) != nullptr;
        const int left = mainSplitter->property("projectTreeWidth").toInt();
        const int right = mainSplitter->property("editorRightWidth").toInt();
        mainSplitter->setProperty("switchingTabs", true);
        if (designing) rightPane->hide();
        else rightPane->show();
        const int total = qMax(1, mainSplitter->width());
        if (designing) mainSplitter->setSizes({left, qMax(1, total - left), 0});
        else mainSplitter->setSizes({left, qMax(1, total - left - right), right});
        // Defer until Qt has processed the show/hide layout update.
        QTimer::singleShot(0, mainSplitter, [mainSplitter, rightPane]() {
            const int left = mainSplitter->property("projectTreeWidth").toInt();
            const int right = mainSplitter->property("editorRightWidth").toInt();
            const int total = qMax(1, mainSplitter->width());
            if (rightPane->isHidden())
                mainSplitter->setSizes({left, qMax(1, total - left), 0});
            else
                mainSplitter->setSizes({left, qMax(1, total - left - right), right});
            mainSplitter->setProperty("switchingTabs", false);
        });
    });
    connect(mainSplitter, &QSplitter::splitterMoved, this,
            [mainSplitter, rightPane](int, int) {
        if (mainSplitter->property("switchingTabs").toBool()) return;
        const QList<int> widths = mainSplitter->sizes();
        if (widths.size() != 3) return;
        if (widths[0] >= 80)
            mainSplitter->setProperty("projectTreeWidth", widths[0]);
        if (!rightPane->isHidden() && widths[2] >= 80)
            mainSplitter->setProperty("editorRightWidth", widths[2]);
    });

    // The main window launches maximised. Apply the stored widths after its
    // final geometry has been calculated instead of relying on initial sizes.
    QTimer::singleShot(0, mainSplitter, [mainSplitter, rightPane]() {
        const int left = mainSplitter->property("projectTreeWidth").toInt();
        const int right = mainSplitter->property("editorRightWidth").toInt();
        const int total = qMax(1, mainSplitter->width());
        if (rightPane->isHidden())
            mainSplitter->setSizes({left, qMax(1, total - left), 0});
        else
            mainSplitter->setSizes({left, qMax(1, total - left - right), right});
    });

    setCentralWidget(mainSplitter);
    applyTheme();

    m_compileProgressBar = new QProgressBar(statusBar());
    m_compileProgressBar->setObjectName(QStringLiteral("compileProgress"));
    m_compileProgressBar->setRange(0, 0);
    m_compileProgressBar->setTextVisible(true);
    m_compileProgressBar->setFormat(tr("Compiling..."));
    m_compileProgressBar->setFixedWidth(190);
    m_compileProgressBar->setFixedHeight(16);
    m_compileProgressBar->hide();
    statusBar()->addPermanentWidget(m_compileProgressBar);

    m_cursorPositionLabel = new QLabel(statusBar());
    m_cursorPositionLabel->setObjectName(QStringLiteral("cursorPositionStatus"));
    m_cursorPositionLabel->setMinimumWidth(120);
    m_cursorPositionLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    statusBar()->addPermanentWidget(m_cursorPositionLabel);

    updateCursorPositionStatus();
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

    if (typeBox.exec() == QMessageBox::Cancel || !typeBox.clickedButton()) {
        statusBar()->showMessage(tr("New project cancelled"));
        return;
    }

    m_projectType =
        typeBox.clickedButton() == static_cast<QAbstractButton *>(gameButton)
            ? GameProjectType
            : GuiProjectType;

    Q_UNUSED(guiButton);

    m_modSizeKb = 0;
    m_appSizeKb = 128;
    m_appletFormat = QStringLiteral("v1");
    m_v2HeapKb = 16;
    m_v2StackKb = 8;
    m_outputAppName.clear();
    m_linkerScriptPath.clear();

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

    if (!QDir().mkpath(m_projectPath)) {
        QMessageBox::warning(
            this,
            tr("New Project"),
            tr("Could not create the project directory:\n%1")
                .arg(QDir::toNativeSeparators(m_projectPath)));
        return;
    }

    const QString mainCPath =
        QFileInfo(QDir(m_projectPath).filePath(QStringLiteral("main.c")))
            .absoluteFilePath();

    const QString mainHPath =
        QFileInfo(QDir(m_projectPath).filePath(QStringLiteral("main.h")))
            .absoluteFilePath();

    const QDateTime now = QDateTime::currentDateTime();
    const QString dateStr = now.toString(QStringLiteral("MMM dd yyyy"));
    const QString timeStr = now.toString(QStringLiteral("hh:mm:ss"));

    const QByteArray mainCContents =
        QString(
            "/*\n"
            "   Created file: %1 %2\n"
            "*/\n"
            "#include <stdint.h>\n"
            "#include <stdlib.h>\n\n"
            "#include \"apis.h\"\n"
            "#include \"main.h\"\n\n"
            "int main(void)\n"
            "{\n"
            "    printf(\"Hello world\");\n"
            "    return 0;\n"
            "}\n")
            .arg(timeStr, dateStr)
            .toUtf8();

    const QByteArray mainHContents =
        QString(
            "/*\n"
            "   Created Header file: %1 %2\n"
            "*/\n"
            "#ifndef MAIN_H\n"
            "#define MAIN_H\n\n"
            "\n"
            "#endif // MAIN_H\n")
            .arg(timeStr, dateStr)
            .toUtf8();

    auto writeDefaultFile =
        [this](const QString &path,
               const QByteArray &contents,
               const QString &displayName) -> bool {
            if (QFileInfo::exists(path)) {
                const QMessageBox::StandardButton answer =
                    QMessageBox::warning(
                        this,
                        tr("New Project"),
                        tr("%1 already exists in the selected project directory.\n\n"
                           "Overwrite it with the Sidbox default file?")
                            .arg(displayName),
                        QMessageBox::Yes | QMessageBox::No,
                        QMessageBox::No);

                if (answer != QMessageBox::Yes) {
                    return false;
                }
            }

            QFile file(path);
            if (!file.open(
                    QIODevice::WriteOnly
                    | QIODevice::Text
                    | QIODevice::Truncate)) {
                QMessageBox::warning(
                    this,
                    tr("New Project"),
                    tr("Could not create %1:\n%2")
                        .arg(displayName, QDir::toNativeSeparators(path)));
                return false;
            }

            if (file.write(contents) != contents.size()) {
                file.close();
                QMessageBox::warning(
                    this,
                    tr("New Project"),
                    tr("Could not write the complete %1 file.")
                        .arg(displayName));
                return false;
            }

            file.close();
            return true;
        };

    if (!writeDefaultFile(mainCPath, mainCContents, QStringLiteral("main.c"))
        || !writeDefaultFile(mainHPath, mainHContents, QStringLiteral("main.h"))) {
        statusBar()->showMessage(tr("New project creation cancelled"), 3000);
        return;
    }

    clearEditorTabs();

    addProjectFile(mainCPath);
    addProjectFile(mainHPath);

    refreshProjectFiles();

    openFile(mainCPath);
    openFile(mainHPath);

    saveProjectFile(m_projectFilePath);

    AutoSelectMainC();

    statusBar()->showMessage(
        tr("New %1 project created: %2")
            .arg(projectTypeLabel(m_projectType),
                 QDir::toNativeSeparators(m_projectFilePath)),
        4000);
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
                             "#include <stdint.h>\n"
                             "#include <stdlib.h>\n\n"
                             "#include \"apis.h\"\n\n"
                             "int main(void)\n"
                             "{\n"
                             "    printf(\"Hello world\");\n"
                             "    return 0;\n"
                             "}\n").arg(timeStr, dateStr));

    editor->document()->setModified(false);

    const int index = m_editorTabs->addTab(
        editor,
        editorTabIconForFile(editor->filePath(), 0),
        tabTitleForEditor(editor, 0));
    m_editorTabs->setCurrentIndex(index);
    m_projectAnalysisTimer->start();
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

    const int index = m_editorTabs->addTab(
        editor,
        editorTabIconForFile(editor->filePath(), 1),
        tabTitleForEditor(editor, 1));
    m_editorTabs->setCurrentIndex(index);
    m_projectAnalysisTimer->start();
    statusBar()->showMessage(tr("New H header file created"));
}


void MainWindow::createGuiDesigner()
{
    if (m_projectPath.isEmpty()) {
        QMessageBox::information(
            this,
            tr("GUI Designer"),
            tr("Save or open a project first so the .sbui design and generated .c file have a project folder."));
        return;
    }

    bool accepted = false;
    QString baseName = QInputDialog::getText(
        this,
        tr("New CoderGirl GUI"),
        tr("Design name:"),
        QLineEdit::Normal,
        QStringLiteral("mainwindow"),
        &accepted).trimmed();

    if (!accepted || baseName.isEmpty()) {
        return;
    }

    baseName = QFileInfo(baseName).completeBaseName();
    QString filePath = QDir(m_projectPath).filePath(baseName + QStringLiteral(".sbui"));
    if (QFileInfo::exists(filePath)) {
        QMessageBox::warning(this, tr("GUI Designer"), tr("%1 already exists.").arg(QDir::toNativeSeparators(filePath)));
        return;
    }

    if (!openGuiDesigner(filePath)) {
        return;
    }

    if (auto *designer = dynamic_cast<SidboxGuiDesigner *>(m_editorTabs->currentWidget())) {
        if (designer->saveDesignAndGenerate()) {
            addProjectFile(filePath);
            addProjectFile(QFileInfo(filePath).dir().filePath(QFileInfo(filePath).completeBaseName() + QStringLiteral(".c")));
            refreshProjectFiles();
            if (!m_projectFilePath.isEmpty()) saveProjectFile(m_projectFilePath);
        }
    }
}

bool MainWindow::openGuiDesigner(const QString &filePath)
{
    const QString absolutePath = QFileInfo(filePath).absoluteFilePath();
    for (int i = 0; i < m_editorTabs->count(); ++i) {
        if (auto *designer = dynamic_cast<SidboxGuiDesigner *>(m_editorTabs->widget(i))) {
            if (QFileInfo(designer->filePath()).absoluteFilePath() == absolutePath) {
                m_editorTabs->setCurrentIndex(i);
                return true;
            }
        }
    }

    // Available during the designer constructor, including initial properties.
    m_editorTabs->setProperty("sidboxProjectRoot", m_projectPath);
    auto *designer = createSidboxGuiDesigner(absolutePath, m_editorTabs);
    // Let the designer discover every .sbui in the project, including subfolders.
    designer->setProperty("sidboxProjectRoot", m_projectPath);
    const int index = m_editorTabs->addTab(designer, QIcon(QStringLiteral(":/icons/toolbar_guidesigner.png")), designer->displayName());
    m_editorTabs->setTabToolTip(index, tr("CoderGirl visual design\n%1").arg(QDir::toNativeSeparators(absolutePath)));

    designer->tabTitleChanged = [this, designer]() {
        const int index = m_editorTabs->indexOf(designer);
        if (index >= 0) m_editorTabs->setTabText(index, designer->displayName());
    };
    designer->beforeGenerate = [this](const QString &cPath) {
        const QString absoluteCPath = QFileInfo(cPath).absoluteFilePath();
        for (int i = 0; i < m_editorTabs->count(); ++i) {
            CodeEditor *editor = primaryEditorForTab(m_editorTabs->widget(i));
            if (!editor || editor->filePath().isEmpty()) {
                continue;
            }
            if (QFileInfo(editor->filePath()).absoluteFilePath() == absoluteCPath
                && editor->document()->isModified()) {
                return saveEditor(editor);
            }
        }
        return true;
    };

    designer->generatedFilesChanged = [this](const QString &designPath, const QString &cPath) {
        addProjectFile(designPath);
        addProjectFile(cPath);
        refreshProjectFiles();
        statusBar()->showMessage(tr("GUI generated: %1").arg(displayPath(cPath)), 2500);
    };

    designer->sourceNavigationRequested =
        [this](const QString &cPath,
               const QString &preferredMarker,
               const QString &fallbackMarker) {
            const QString absoluteCPath =
                QFileInfo(cPath).absoluteFilePath();

            if (!openFile(absoluteCPath)) {
                return;
            }

            CodeEditor *editor =
                activeEditor();

            if (!editor
                || QFileInfo(editor->filePath()).absoluteFilePath()
                   != absoluteCPath) {
                return;
            }

            /*
             * Regeneration may replace an already-open .c file. beforeGenerate
             * saved its USER edits first, so reloading here is safe and avoids
             * waiting for the file-watcher debounce before the jump.
             */
            editor->loadFromFile(
                absoluteCPath,
                true);

            editor->enableSyntaxHighlighting();

            QTextCursor target;

            if (!preferredMarker.isEmpty()) {
                target =
                    editor->document()->find(
                        preferredMarker);
            }

            if (target.isNull()
                && !fallbackMarker.isEmpty()) {
                target =
                    editor->document()->find(
                        fallbackMarker);
            }

            if (!target.isNull()) {
                editor->setTextCursor(target);
                editor->centerCursor();
            }

            editor->setFocus();

            statusBar()->showMessage(
                target.isNull()
                    ? tr("Generated GUI source opened")
                    : tr("Jumped to GUI handler"),
                1800);
        };

    addProjectFile(absolutePath);
    m_editorTabs->setCurrentIndex(index);
    designer->setFocus();
    return true;
}

bool MainWindow::saveGuiDesignerTab(QWidget *widget)
{
    auto *designer = dynamic_cast<SidboxGuiDesigner *>(widget);
    return !designer || designer->saveDesignAndGenerate();
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

    /*
     * Save source editors FIRST. A generated GUI .c file may contain programmer
     * edits inside protected USER callback blocks; putting those edits on disk
     * before regeneration lets the designer preserve them safely.
     */
    for (int i = 0; i < m_editorTabs->count(); ++i) {
        auto *editor = primaryEditorForTab(m_editorTabs->widget(i));
        if (!editor) {
            continue;
        }

        // Skip untitled/unsaved tabs so QFileDialog isn't popped up for each one
        if (editor->filePath().isEmpty()) {
            continue;
        }

        allSaved = saveEditor(editor) && allSaved;
    }

    if (allSaved) {
        for (int i = 0; i < m_editorTabs->count(); ++i) {
            if (auto *designer = dynamic_cast<SidboxGuiDesigner *>(m_editorTabs->widget(i))) {
                if (designer->isModified()) {
                    allSaved = designer->saveDesignAndGenerate() && allSaved;
                }
            }
        }
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



void MainWindow::showAboutIde()
{
    if (!m_editorTabs) {
        return;
    }

    // Reuse the existing About tab instead of opening duplicates.
    for (int i = 0; i < m_editorTabs->count(); ++i) {
        QWidget *widget = m_editorTabs->widget(i);
        if (widget && widget->property("sidboxAboutIde").toBool()) {
            m_editorTabs->setCurrentIndex(i);
            return;
        }
    }

    auto *page = new QWidget;
    page->setProperty("sidboxAboutIde", true);

    auto *outerLayout = new QVBoxLayout(page);
    outerLayout->setContentsMargins(24, 24, 24, 24);
    outerLayout->setSpacing(14);

    auto *headerLayout = new QHBoxLayout;
    headerLayout->setSpacing(18);

    auto *logoLabel = new QLabel(page);
    logoLabel->setFixedSize(160, 160);
    logoLabel->setAlignment(Qt::AlignCenter);

    /*
     * ABOUT LOGO PLACEHOLDER
     *
     * Replace :/icons/icon.png below with your final About graphic resource,
     * for example:
     *
     *     QPixmap logo(QStringLiteral(":/icons/about_logo.png"));
     */
    QPixmap logo(QStringLiteral(":/icons/icon.png"));
    if (!logo.isNull()) {
        logoLabel->setPixmap(
            logo.scaled(
                logoLabel->size(),
                Qt::KeepAspectRatio,
                Qt::SmoothTransformation));
    } else {
        logoLabel->setText(tr("SIDBOX IDE"));
    }

    auto *titleArea = new QWidget(page);
    auto *titleLayout = new QVBoxLayout(titleArea);
    titleLayout->setContentsMargins(0, 0, 0, 0);
    titleLayout->setSpacing(5);

    auto *title = new QLabel(tr("Sidbox IDE"), titleArea);
    QFont titleFont = title->font();
    titleFont.setPointSize(titleFont.pointSize() + 8);
    titleFont.setBold(true);
    title->setFont(titleFont);

    auto *subtitle = new QLabel(
        tr("A dedicated C development environment for the Sidbox platform."),
        titleArea);
    subtitle->setWordWrap(true);

    auto *purpose = new QLabel(
        tr("Sidbox IDE was created to make developing Sidbox software quicker, "
           "clearer and more enjoyable. It brings the Sidbox project format, "
           "compiler toolchain, API navigation, diagnostics, source browsing, "
           "minimap, project symbols and searchable API Cheat Sheet together "
           "in one focused development environment."),
        titleArea);
    purpose->setWordWrap(true);

    titleLayout->addWidget(title);
    titleLayout->addWidget(subtitle);
    titleLayout->addSpacing(8);
    titleLayout->addWidget(purpose);
    titleLayout->addStretch(1);

    headerLayout->addWidget(logoLabel, 0, Qt::AlignTop);
    headerLayout->addWidget(titleArea, 1);

    auto *aboutHeading = new QLabel(tr("About the IDE"), page);
    QFont headingFont = aboutHeading->font();
    headingFont.setBold(true);
    aboutHeading->setFont(headingFont);

    auto *aboutText = new QLabel(
        tr("Although it is a capable C/C++ editor at heart, Sidbox IDE was "
           "designed specifically around Sidbox development. Its goal is not "
           "to be a huge general-purpose IDE; it is to provide the tools that "
           "are actually useful when creating Sidbox applications and games."),
        page);
    aboutText->setWordWrap(true);
    aboutText->setTextInteractionFlags(Qt::TextSelectableByMouse);

    auto *featuresHeading = new QLabel(tr("Built for Sidbox"), page);
    featuresHeading->setFont(headingFont);

    auto *features = new QLabel(
        tr("• Sidbox .proj project support\n"
           "• Integrated Sidbox compiler and linker settings\n"
           "• Error and warning diagnostics\n"
           "• API-aware syntax highlighting and completion\n"
           "• Ctrl+Click navigation into project and Sidbox API source\n"
           "• Read-only API source reference tabs\n"
           "• F1 contextual API tips\n"
           "• F8 searchable API Cheat Sheet\n"
           "• Functions / variables browser and minimap navigation\n"
           "• Project-wide find and replace"),
        page);
    features->setWordWrap(true);
    features->setTextInteractionFlags(Qt::TextSelectableByMouse);

    auto *creditsHeading = new QLabel(tr("Credits"), page);
    creditsHeading->setFont(headingFont);

    auto *credits = new QLabel(
        tr("Sidbox IDE was designed and created by Electronscape for the Sidbox platform.\n\n"
           "Qt 6 / C++ implementation assistance, debugging and code review "
           "were carried out with the assistance of ChatGPT by OpenAI."),
        page);
    credits->setWordWrap(true);
    credits->setTextInteractionFlags(Qt::TextSelectableByMouse);

    auto *note = new QLabel(
        tr("Built because Sidbox deserved an IDE of its own. :)"),
        page);
    QFont noteFont = note->font();
    noteFont.setItalic(true);
    note->setFont(noteFont);

    outerLayout->addLayout(headerLayout);
    outerLayout->addSpacing(6);
    outerLayout->addWidget(aboutHeading);
    outerLayout->addWidget(aboutText);
    outerLayout->addSpacing(6);
    outerLayout->addWidget(featuresHeading);
    outerLayout->addWidget(features);
    outerLayout->addSpacing(6);
    outerLayout->addWidget(creditsHeading);
    outerLayout->addWidget(credits);
    outerLayout->addStretch(1);
    outerLayout->addWidget(note);

    auto *scroll = new QScrollArea(m_editorTabs);
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);
    scroll->setWidget(page);
    scroll->setProperty("sidboxAboutIde", true);

    const int index = m_editorTabs->addTab(scroll, tr("About IDE"));
    m_editorTabs->setTabToolTip(index, tr("About Sidbox IDE"));
    m_editorTabs->setCurrentIndex(index);
}

namespace {


QString libraryCheatSheetCategory(const QString &filePath)
{
    const QString baseName = QFileInfo(filePath).completeBaseName();
    return QStringLiteral("Libraries — %1")
        .arg(baseName.isEmpty() ? QStringLiteral("Library") : baseName);
}

QString libraryArchiveForHeader(const QString &libraryRoot,
                                const QString &headerPath)
{
    if (libraryRoot.isEmpty() || headerPath.isEmpty()) {
        return {};
    }

    QString headerBase = QFileInfo(headerPath).completeBaseName();
    if (headerBase.startsWith(QStringLiteral("lib"), Qt::CaseInsensitive)) {
        headerBase.remove(0, 3);
    }

    QDirIterator iterator(
        libraryRoot,
        {QStringLiteral("*.a")},
        QDir::Files,
        QDirIterator::Subdirectories);

    while (iterator.hasNext()) {
        const QString archivePath =
            QFileInfo(iterator.next()).absoluteFilePath();

        QString archiveBase =
            QFileInfo(archivePath).completeBaseName();

        if (archiveBase.startsWith(QStringLiteral("lib"), Qt::CaseInsensitive)) {
            archiveBase.remove(0, 3);
        }

        if (archiveBase.compare(headerBase, Qt::CaseInsensitive) == 0) {
            return archivePath;
        }
    }

    return {};
}

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

    const QString libsRoot = ideLibsPath();
    const QString apiRoot =
        QDir(libsRoot).filePath(QStringLiteral("api"));
    const QString libraryRoot =
        QDir(libsRoot).filePath(QStringLiteral("libraries"));

    if (!QFileInfo::exists(apiRoot)
        && !QFileInfo::exists(libraryRoot)) {
        QMessageBox::information(
            this,
            tr("Cheat Sheet"),
            tr("Neither the Sidbox API nor libraries folder could be found under:\n%1")
                .arg(QDir::toNativeSeparators(libsRoot)));
        return;
    }

    auto *page = new QWidget(m_editorTabs);
    page->setProperty("sidboxApiCheatSheet", true);

    auto *layout = new QVBoxLayout(page);
    layout->setContentsMargins(8, 8, 8, 8);
    layout->setSpacing(6);

    auto *title = new QLabel(
        tr("Sidbox API & Libraries Cheat Sheet"),
        page);

    QFont titleFont = title->font();
    titleFont.setBold(true);
    title->setFont(titleFont);

    auto *search = new QLineEdit(page);
    search->setObjectName(QStringLiteral("apiCheatSearch"));
    search->setPlaceholderText(
        tr("Search API/library functions, constants, types, descriptions..."));
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
        QString libraryArchive;
        bool libraryEntry = false;
        int line = -1;
    };

    QList<ApiEntry> entries;
    const QStringList knownNames = apiSyntaxNames();

    QStringList catalogFiles;

    if (QFileInfo::exists(apiRoot)) {
        QDirIterator apiIterator(
            apiRoot,
            {QStringLiteral("*.h"), QStringLiteral("*.c")},
            QDir::Files,
            QDirIterator::Subdirectories);

        while (apiIterator.hasNext()) {
            catalogFiles.append(
                QFileInfo(apiIterator.next()).absoluteFilePath());
        }
    }

    if (QFileInfo::exists(libraryRoot)) {
        QDirIterator libraryIterator(
            libraryRoot,
            {QStringLiteral("*.h")},
            QDir::Files,
            QDirIterator::Subdirectories);

        while (libraryIterator.hasNext()) {
            catalogFiles.append(
                QFileInfo(libraryIterator.next()).absoluteFilePath());
        }
    }

    /*
     * Headers first: both the core API and static libraries generally expose
     * the public declaration/documentation there. API .c files remain a
     * fallback for wrappers/definitions whose documentation lives in source.
     */
    std::stable_sort(
        catalogFiles.begin(),
        catalogFiles.end(),
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

        for (const QString &filePath : std::as_const(catalogFiles)) {
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

            const QString absoluteLibraryRoot =
                QFileInfo(libraryRoot).absoluteFilePath();
            const QString absoluteFilePath =
                QFileInfo(filePath).absoluteFilePath();

            chosen.libraryEntry =
                QFileInfo::exists(libraryRoot)
                && (absoluteFilePath == absoluteLibraryRoot
                    || absoluteFilePath.startsWith(
                        absoluteLibraryRoot + QDir::separator()));

            if (chosen.libraryEntry) {
                chosen.category =
                    libraryCheatSheetCategory(filePath);
                chosen.libraryArchive =
                    libraryArchiveForHeader(
                        libraryRoot,
                        filePath);
            } else {
                chosen.category =
                    apiCheatSheetCategory(
                        apiRoot,
                        filePath);
            }

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
                chosen.libraryEntry
                    ? tr("No description is written in this library header yet. "
                         "Add a /* @brief ... */ comment above the declaration "
                         "to document it in the Cheat Sheet.")
                    : tr("No description is written in the API source yet. "
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
        item->setData(0, Qt::UserRole + 6, entry.libraryArchive);
        item->setData(0, Qt::UserRole + 7, entry.libraryEntry);
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

        const bool libraryEntry =
            item->data(
                0,
                Qt::UserRole + 7).toBool();

        const QString libraryArchive =
            item->data(
                0,
                Qt::UserRole + 6).toString();

        if (libraryEntry) {
            const QString archiveText =
                libraryArchive.isEmpty()
                    ? tr("(matching .a archive not found)")
                    : QFileInfo(libraryArchive).fileName();

            sourceLabel->setText(
                tr("Library: %1\nHeader: %2:%3")
                    .arg(
                        archiveText,
                        QDir(libsRoot).relativeFilePath(filePath))
                    .arg(line + 1));
        } else {
            sourceLabel->setText(
                tr("Source: %1:%2")
                    .arg(
                        QDir(libsRoot).relativeFilePath(filePath))
                    .arg(line + 1));
        }

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
        tr("F8 — searchable Sidbox API & Libraries Cheat Sheet"));

    m_editorTabs->setCurrentIndex(index);

    tree->collapseAll();

    const bool selected =
        selectCheatSheetSymbol(page);

    if (!selected) {
        search->setFocus();
    }

    statusBar()->showMessage(
        tr("Sidbox API & Libraries Cheat Sheet ready — %1 items")
            .arg(entries.size()),
        3000);
}

void MainWindow::showProjectSettings()
{
    ProjectSettingsDialog dialog(this);
    dialog.setProjectType(m_projectType);
    dialog.setAppletFormat(m_appletFormat);
    dialog.setModSizeKb(m_modSizeKb);
    dialog.setAppSizeKb(m_appSizeKb);
    dialog.setV2HeapKb(m_v2HeapKb);
    dialog.setV2StackKb(m_v2StackKb);
    dialog.setOutputAppName(m_outputAppName);
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
    m_appletFormat = (m_projectType == GuiProjectType) ? dialog.appletFormat() : QStringLiteral("v1");
    m_modSizeKb = dialog.modSizeKb();
    m_appSizeKb = dialog.appSizeKb();
    m_v2HeapKb = dialog.v2HeapKb();
    m_v2StackKb = dialog.v2StackKb();
    m_outputAppName =
        normalizedAppOutputName(dialog.outputAppName());
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
    /*
     * F5 is a PROJECT build action, not a source-tab action. GUI Designer tabs
     * are first-class project documents, so compiling from one must save source
     * editors, save/regenerate visual designs, then build the project normally.
     */
    if (m_projectFilePath.isEmpty()) {
        QMessageBox::information(this, tr("Compile"), tr("Save the project before compiling so build outputs can sit beside the .proj file."));
        return;
    }

    /*
     * Save C/C++/resource editors first so protected callback USER blocks in a
     * generated GUI .c are safely on disk before any designer regeneration.
     */
    for (int i = 0; i < m_editorTabs->count(); ++i) {
        auto *openEditor =
            primaryEditorForTab(
                m_editorTabs->widget(i));

        if (openEditor
            && !saveEditor(openEditor)) {
            QMessageBox::warning(
                this,
                tr("Compile"),
                tr("Save all project files before compiling."));
            return;
        }
    }

    /*
     * Then save/regenerate every visual design. This makes F5 work identically
     * from a .c tab, a .h tab, a .res tab, or the GUI Designer itself.
     */
    for (int i = 0; i < m_editorTabs->count(); ++i) {
        if (auto *designer =
                dynamic_cast<SidboxGuiDesigner *>(
                    m_editorTabs->widget(i))) {
            if (!designer->saveDesignAndGenerate()) {
                QMessageBox::warning(
                    this,
                    tr("Compile"),
                    tr("Could not save/regenerate a GUI design before compiling."));
                return;
            }
        }
    }

    if (m_compilerProcess->state() != QProcess::NotRunning) {
        QMessageBox::information(this, tr("Compile"), tr("A compile is already running."));
        return;
    }

    const QStringList sourceFiles = projectFilesForCompile();
    if (sourceFiles.isEmpty()) {
        QMessageBox::information(this, tr("Compile"), tr("Add at least one .c, .cc, .cpp, or .res file to the project before compiling."));
        return;
    }

    /*
     * Preflight only what is knowable without running the linker: generated
     * embedded PCM bytes.  Compiler code, BSS, alignment, and stack are NOT
     * included in this estimate.  The linked ELF remains authoritative.
     */
    qint64 embeddedSfxBytes = 0;
    int embeddedSfxCount = 0;
    {
        QSet<QString> compiledFiles;
        for (const QString &source : sourceFiles) {
            compiledFiles.insert(QFileInfo(source).absoluteFilePath());
        }

        QDirIterator designs(m_projectPath, QStringList{QStringLiteral("*.sbui")},
                             QDir::Files, QDirIterator::Subdirectories);
        while (designs.hasNext()) {
            const QString designPath = designs.next();
            const QFileInfo designInfo(designPath);
            const QString assetSource = designInfo.dir().absoluteFilePath(
                designInfo.completeBaseName() + QStringLiteral("res/media_sfx.c"));
            const QString legacySource = designInfo.dir().absoluteFilePath(
                designInfo.completeBaseName() + QStringLiteral("_sfx.c"));
            if (!compiledFiles.contains(QFileInfo(assetSource).absoluteFilePath())
                && !compiledFiles.contains(QFileInfo(legacySource).absoluteFilePath())) {
                continue;
            }

            QFile designFile(designPath);
            if (!designFile.open(QIODevice::ReadOnly)) {
                continue;
            }
            const QJsonDocument document =
                QJsonDocument::fromJson(designFile.readAll());
            for (const QJsonValue &value :
                 document.object().value(QStringLiteral("gadgets")).toArray()) {
                const QJsonObject gadget = value.toObject();
                if (gadget.value(QStringLiteral("type")).toString() != QStringLiteral("Media")
                    || gadget.value(QStringLiteral("mediaMode")).toString() != QStringLiteral("SFX")
                    || !gadget.value(QStringLiteral("mediaEmbedSfx")).toBool()) {
                    continue;
                }
                const QByteArray pcm = QByteArray::fromBase64(
                    gadget.value(QStringLiteral("mediaEmbeddedPcmBase64"))
                        .toString().toLatin1());
                if (!pcm.isEmpty()) {
                    // Generated arrays use MEMALIGN32, plus a length constant.
                    embeddedSfxBytes += (pcm.size() + 31LL) & ~31LL;
                    embeddedSfxBytes += 4;
                    ++embeddedSfxCount;
                }
            }
        }
    }

    const qint64 reservedBytes = qint64(m_appSizeKb) * 1024;
    if (m_linkerScriptPath.isEmpty() && embeddedSfxBytes > 0 && reservedBytes > 0
        && embeddedSfxBytes * 100 >= reservedBytes * 70) {
        QMessageBox warning(this);
        warning.setIcon(QMessageBox::Warning);
        warning.setWindowTitle(tr("Applet memory preflight"));
        warning.setText(tr("Embedded sound data is using much of the applet allowance."));
        warning.setInformativeText(
            tr("%1 embedded SFX sample(s) account for approximately %2 of the "
               "configured %3 KB applet allowance.\n\n"
               "This does NOT include program code, other data, BSS or stack. "
               "Only the linker can calculate final RAM usage. Increasing the "
               "limit also changes the applet's memory reservation, so check "
               "your SIDBOX memory layout first.")
                .arg(embeddedSfxCount)
                .arg(formattedFileSize(embeddedSfxBytes))
                .arg(m_appSizeKb));
        QPushButton *settingsButton = warning.addButton(
            tr("Project Settings..."), QMessageBox::ActionRole);
        QPushButton *continueButton = warning.addButton(
            tr("Compile Anyway"), QMessageBox::AcceptRole);
        warning.addButton(QMessageBox::Cancel);
        warning.setDefaultButton(continueButton);
        warning.exec();
        if (warning.clickedButton() == settingsButton) {
            showProjectSettings();
            return; // Run Compile again after reviewing the new size.
        }
        if (warning.clickedButton() != continueButton) {
            return;
        }
    }

    const bool v2Build = normalizedProjectType(m_projectType) == GuiProjectType &&
        m_appletFormat == QStringLiteral("v2");
    if (v2Build && !m_linkerScriptPath.isEmpty()) {
        QMessageBox::warning(this, tr("V2 build"),
            tr("Experimental V2 requires its dedicated gui_v2.ld template. "
               "Set the Linker script field to Default, or select V1 for your custom script."));
        return;
    }
    if (v2Build && (m_v2HeapKb < 4 || (m_v2HeapKb * 1024) % 32 != 0)) {
        QMessageBox::warning(this, tr("V2 build"),
            tr("GUI V2 requires at least 4 KB of heap, aligned to 32 bytes."));
        return;
    }
    if (v2Build && (m_v2StackKb < 4 || m_v2StackKb > 128 ||
                    (m_v2StackKb * 1024) % 32 != 0)) {
        QMessageBox::warning(this, tr("V2 build"),
            tr("Stage 6C private callback stacks must be 4–128 KB and 32-byte aligned."));
        return;
    }
    if (v2Build && m_appSizeKb > 512) {
        QMessageBox::warning(this, tr("V2 build"),
            tr("The experimental firmware loader currently accepts at most 512 KB "
               "per V2 applet. Reduce the applet allowance or build V1."));
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
    QStringList apiSourceFiles = sidboxApiSourceFiles();
    const QStringList libraryFiles = sidboxLibraryFiles();
    if (v2Build) {
        // V2 uses its versioned ELF header; never link the V1 startup marker.
        apiSourceFiles.removeAll(
            QDir(apiDir.absolutePath()).filePath(QStringLiteral("applet.s"))
        );

        // CGARM: Automatically discover all runtime C sources.
        // V1 and Gaming remain unchanged.
        const QDir cgarmLibcDir(
            QDir(libsPath).filePath(QStringLiteral("tools/cgarm/libc"))
        );

        if (!cgarmLibcDir.exists()) {
            QMessageBox::warning(this, tr("CGARM build"),
                tr("CGARM library directory not found:\n%1")
                    .arg(cgarmLibcDir.absolutePath()));
            return;
        }

        const QFileInfoList cgarmSources = cgarmLibcDir.entryInfoList(
            QStringList{QStringLiteral("*.c")},
            QDir::Files | QDir::Readable | QDir::NoSymLinks,
            QDir::Name
        );

        if (cgarmSources.isEmpty()) {
            QMessageBox::warning(this, tr("CGARM build"),
                tr("No CGARM C source files found:\n%1")
                    .arg(cgarmLibcDir.absolutePath()));
            return;
        }

        for (const QFileInfo &source : cgarmSources) {
            apiSourceFiles.append(source.absoluteFilePath());
        }
    }

    if (!QFileInfo::exists(selectedCompiler)) {
        QMessageBox::warning(this, tr("Compile"), tr("The bundled Sidbox compiler was not found:\n%1").arg(QDir::toNativeSeparators(selectedCompiler)));
        return;
    }

    if (!v2Build && !QFileInfo::exists(selectedObjcopy)) {
        QMessageBox::warning(this, tr("Compile"), tr("The bundled Sidbox objcopy was not found:\n%1").arg(QDir::toNativeSeparators(selectedObjcopy)));
        return;
    }

    if (!QFileInfo::exists(selectedLinkerScript)) {
        QMessageBox::warning(this, tr("Compile"), tr("The selected linker script does not exist:\n%1").arg(QDir::toNativeSeparators(selectedLinkerScript)));
        return;
    }

    // PIE-capable LLVM LLD is required for V2. Prefer a bundled executable
    // (tools/bin/ld.lld) so released IDEs do not depend on the host PATH.
    // Fedora's installed ld.lld is a development fallback only.
    QString v2LldPath;
    if (v2Build) {
        for (const QString &candidate : {
                 QDir(libsPath).filePath(QStringLiteral("tools/bin/ld.lld")),
                 QDir(libsPath).filePath(QStringLiteral("tools/ld.lld")),
                 QStandardPaths::findExecutable(QStringLiteral("ld.lld"))}) {
            if (!candidate.isEmpty() && QFileInfo(candidate).isExecutable()) {
                v2LldPath = candidate;
                break;
            }
        }
        if (v2LldPath.isEmpty()) {
            QMessageBox::warning(this, tr("V2 linker missing"),
                tr("GUI V2 requires LLVM's ld.lld for a genuine ARM ET_DYN ELF.\n\n"
                   "Install the LLD tool for development, or place its executable at\n"
                   "%1\n\n"
                   "V1 and gaming mode are unaffected.")
                    .arg(QDir(libsPath).filePath(QStringLiteral("tools/bin/ld.lld"))));
            return;
        }
    }

    if (apiSourceFiles.isEmpty()) {
        QMessageBox::warning(this, tr("Compile"), tr("The IDE API sources were not found under idelibs/api."));
        return;
    }

    const QString outputBaseName =
        QFileInfo(m_projectFilePath).completeBaseName();

    const QString appFileName =
        m_outputAppName.isEmpty()
            ? outputBaseName + QStringLiteral(".app")
            : normalizedAppOutputName(m_outputAppName);

    const QString buildPath =
        QDir(m_projectPath).filePath(QStringLiteral("build"));
    if (!QDir().mkpath(buildPath)) {
        QMessageBox::warning(this, tr("Compile"), tr("Could not create build folder:\n%1").arg(QDir::toNativeSeparators(buildPath)));
        return;
    }

    const QString outputPath = QDir(buildPath).filePath(outputBaseName + QStringLiteral(".elf"));
    const QString appOutputPath = QDir(m_projectPath).filePath(appFileName);
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
    };
    if (v2Build) {
        arguments << QStringLiteral("-DSIDBOX_V2_HEAP_BYTES=%1").arg(m_v2HeapKb * 1024)
                  << QStringLiteral("-DSIDBOX_APPLET_V2")
                  << QStringLiteral("-fPIE") << QStringLiteral("-fPIC")
                  << QStringLiteral("-fno-plt")
                  << QStringLiteral("-fvisibility=hidden")
                  << QStringLiteral("-ffreestanding") << QStringLiteral("-fno-builtin");
    }
    arguments << QStringList{
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

    if (v2Build) {
        arguments << QStringLiteral("-I")
                  << QDir(libsPath).filePath(QStringLiteral("tools/cgarm/include"));
    }

    // Capture compiler-only options before project and SDK inputs or linker
    // flags are appended. V2 compiles each source to a separate PIC object.
    const QStringList v2CompileFlags = arguments;

    /*
     * .res is a Sidbox IDE resource-source extension. GCC does not infer C
     * from that suffix, so explicitly select C for that input and immediately
     * restore extension-based language detection for the files which follow.
     */
    for (const QString &sourceFile : sourceFiles) {
        if (isResourceSource(sourceFile)) {
            arguments << QStringLiteral("-x")
                      << QStringLiteral("c")
                      << sourceFile
                      << QStringLiteral("-x")
                      << QStringLiteral("none");
        } else {
            arguments << sourceFile;
        }
    }

    arguments << apiSourceFiles;
    arguments << libraryFiles;
    arguments << QStringLiteral("-T") << selectedLinkerScript;
    arguments << QStringLiteral("-Wl,-Map=%1").arg(mapOutputPath);
    arguments << QStringLiteral("-Wl,--gc-sections");
    if (v2Build) {
        // V2 never uses the GCC driver's final link. Its objects will be
        // linked explicitly by ld.lld -pie below. Never relabel ET_EXEC.

    } else {
        arguments << QStringLiteral("-static");
    }
    arguments << QStringLiteral("--specs=nosys.specs");

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
    appendOutputLine(v2Build
        ? tr("Applet format: V2 (EXPERIMENTAL PIE; unsupported relocations are rejected)")
        : tr("Applet format: V1 (legacy fixed-address)"), OutputKind::Header);
    if (v2Build) {
        appendOutputLine(tr("V2 heap: %1 KB bounded; private callback PSP stack: %2 KB (Stage 6C firmware)")
            .arg(m_v2HeapKb).arg(m_v2StackKb), OutputKind::Header);
        appendOutputLine(tr("V2 still enters on MSP; window/timer callbacks use PSP. "
                            "Non-PIC GNU/Newlib archives may be rejected by the linker. "
                            "Build a test copy first."), OutputKind::Warning);
    }
    appendOutputLine(tr("Project: %1").arg(QDir::toNativeSeparators(m_projectFilePath)), OutputKind::Path);
    appendOutputLine(tr("Build folder: %1").arg(QDir::toNativeSeparators(buildPath)), OutputKind::Path);
    appendOutputLine(tr("ELF: %1").arg(QDir::toNativeSeparators(outputPath)), OutputKind::Path);
    appendOutputLine(tr("APP: %1").arg(QDir::toNativeSeparators(appOutputPath)), OutputKind::Path);
    appendOutputLine(tr("Map: %1").arg(QDir::toNativeSeparators(mapOutputPath)), OutputKind::Path);
    appendOutputLine(tr("Asm: %1").arg(QDir::toNativeSeparators(asmOutputPath)), OutputKind::Path);
    appendOutputLine(tr("Linker script: %1").arg(QDir::toNativeSeparators(selectedLinkerScript)), OutputKind::Path);
    appendOutputLine(
        tr("Applet size: %1 KB").arg(m_appSizeKb),
        OutputKind::Header);
    if (embeddedSfxBytes > 0) {
        appendOutputLine(
            tr("Embedded SFX: %1 sample(s), approximately %2 RAM before "
               "code, BSS and stack")
                .arg(embeddedSfxCount)
                .arg(formattedFileSize(embeddedSfxBytes)),
            OutputKind::Muted);
    }
    appendOutputLine(
        tr("Optimisation: %1").arg(m_compilerOptimization),
        OutputKind::Header);

    int resourceCount = 0;
    for (const QString &sourceFile : sourceFiles) {
        if (isResourceSource(sourceFile)) {
            ++resourceCount;
        }
    }
    if (resourceCount > 0) {
        appendOutputLine(
            tr("Resource sources: %1 (.res compiled as C, IDE analysis disabled)")
                .arg(resourceCount),
            OutputKind::Muted);
    }

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

    m_buildLinkSizeOverflow = false;
    m_currentBuildIsV2 = v2Build;
    m_pendingElfPath = outputPath;
    m_pendingAppPath = appOutputPath;
    m_pendingAsmPath = asmOutputPath;
    m_compilerProcess->setWorkingDirectory(buildPath);

    if (v2Build) {
        // Unlike bare-metal GCC's final link (which produced ET_EXEC on the
        // tested GCC 9.3.1 toolchain), LLVM LLD explicitly produces ET_DYN.
        // Use GCC only for compiling, preserving the bundled toolchain's
        // system headers and C language compatibility.
        m_v2CompilerPath = selectedCompiler;
        m_v2LinkerPath = v2LldPath;
        m_v2BuildDirectory = buildPath;
        m_v2CompileFlags = v2CompileFlags;
        m_v2CompileSources = sourceFiles;
        m_v2CompileSources.append(apiSourceFiles);
        m_v2CompileSources.removeDuplicates();
        m_v2CompiledObjects.clear();
        for (int i = 0; i < m_v2CompileSources.size(); ++i) {
            m_v2CompiledObjects.append(QDir(buildPath).filePath(
                QStringLiteral("v2_unit_%1.o").arg(i, 3, 10, QLatin1Char('0'))));
        }
        m_v2LinkArguments = {
            QStringLiteral("-pie"),
            QStringLiteral("-Bsymbolic"),
            QStringLiteral("--no-undefined"),
            QStringLiteral("--nostdlib"),
            QStringLiteral("--gc-sections"),
            QStringLiteral("--entry=applet_entry"),
            QStringLiteral("-T"), selectedLinkerScript,
            QStringLiteral("-Map=%1").arg(mapOutputPath)
        };
        m_v2LinkArguments.append(m_v2CompiledObjects);
        if (!libraryFiles.isEmpty()) {
            // Existing static archives may not be PIC! LLD will reject unsafe
            // relocations; never quietly link GNU/Newlib's non-PIC libraries.
            m_v2LinkArguments << QStringLiteral("--start-group");
            m_v2LinkArguments.append(libraryFiles);
            m_v2LinkArguments << QStringLiteral("--end-group");
        }
        m_v2LinkArguments << QStringLiteral("-o") << outputPath;
        m_v2CompileIndex = 0;
        if (m_v2CompileSources.isEmpty()) {
            appendOutputLine(tr("V2 has no C sources to compile."), OutputKind::Error);
            finishCompileProgress();
            statusBar()->showMessage(tr("Compile failed"));
            return;
        }
        m_buildStep = BuildStep::V2Compiling;
        appendOutputLine(tr("V2 linker: %1 (LLVM LLD, true ET_DYN)")
            .arg(QDir::toNativeSeparators(v2LldPath)), OutputKind::Path);
        appendOutputLine(tr("CGARM runtime: freestanding PIC libc; GNU/Newlib libc is NOT linked. "
                            "Unsupported dependencies will produce a linker error."), OutputKind::Warning);
        setCompileProgressStage(tr("Compiling V2 PIC objects..."));
        QStringList compileArgs = m_v2CompileFlags;
        if (isResourceSource(m_v2CompileSources.first())) {
            compileArgs << QStringLiteral("-x") << QStringLiteral("c");
        }
        compileArgs << QStringLiteral("-c") << m_v2CompileSources.first()
                    << QStringLiteral("-o") << m_v2CompiledObjects.first();
        m_compilerProcess->start(m_v2CompilerPath, compileArgs);
    } else {
        m_buildStep = BuildStep::Linking;
        setCompileProgressStage(tr("Compiling & linking..."));
        m_compilerProcess->start(selectedCompiler, arguments);
    }
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
        auto *editor = primaryEditorForTab(m_editorTabs->widget(i));
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
        tr("Project files (*.c *.h *.inc *.res *.txt *.md);;All files (*)"));

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
        QMessageBox::warning(this, tr("Create File"), tr("Use one of these extensions: .c, .h, .inc, .res, .txt, .md"));
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

void MainWindow::createResourceFile()
{
    createResourceFileInDirectory(m_projectPath);
}

void MainWindow::createResourceFileInDirectory(const QString &directoryPath)
{
    if (m_projectPath.isEmpty()) {
        QMessageBox::information(
            this,
            tr("Create Resource"),
            tr("Save or create a project first so the IDE knows which folder to use."));
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
        QMessageBox::warning(
            this, tr("Create Resource"), tr("The selected project folder no longer exists."));
        return;
    }

    bool accepted = false;
    QString fileName = QInputDialog::getText(
        this,
        tr("Create Resource"),
        tr("Resource file name:"),
        QLineEdit::Normal,
        QStringLiteral("resource.res"),
        &accepted).trimmed();

    if (!accepted || fileName.isEmpty()) {
        return;
    }

    if (QFileInfo(fileName).suffix().isEmpty()) {
        fileName.append(QStringLiteral(".res"));
    }

    if (QFileInfo(fileName).suffix().compare(
            QStringLiteral("res"), Qt::CaseInsensitive) != 0) {
        QMessageBox::warning(
            this, tr("Create Resource"), tr("Sidbox resource source files use the .res extension."));
        return;
    }

    if (QFileInfo(fileName).fileName() != fileName) {
        QMessageBox::warning(this, tr("Create Resource"), tr("Enter a file name, not a path."));
        return;
    }

    const QString filePath =
        QFileInfo(QDir(targetDirectory).filePath(fileName)).absoluteFilePath();

    if (QFileInfo::exists(filePath)) {
        QMessageBox::warning(this, tr("Create Resource"), tr("That resource file already exists."));
        return;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(
            this,
            tr("Create Resource"),
            tr("Could not create %1.").arg(QDir::toNativeSeparators(filePath)));
        return;
    }

    const QByteArray header =
        "/*\n"
        " * SIDBOX RESOURCE SOURCE\n"
        " *\n"
        " * This file contains C resource data. Sidbox IDE compiles .res\n"
        " * files as C, but deliberately excludes them from IntelliSense,\n"
        " * project symbol analysis and heavyweight syntax analysis.\n"
        " */\n\n";

    file.write(header);
    file.close();

    addProjectFile(filePath);
    refreshProjectFiles();
    openFile(filePath);

    if (!m_projectFilePath.isEmpty()) {
        saveProjectFile(m_projectFilePath);
    }

    statusBar()->showMessage(
        tr("Resource created: %1").arg(displayPath(filePath)),
        4000);
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
        QWidget *widget = m_editorTabs->widget(i);
        if (auto *designer = dynamic_cast<SidboxGuiDesigner *>(widget)) {
            if (QFileInfo(designer->filePath()).absoluteFilePath() == QFileInfo(filePath).absoluteFilePath()) {
                m_editorTabs->removeTab(i);
                widget->deleteLater();
                continue;
            }
        }
        auto *editor = primaryEditorForTab(widget);
        if (editor && QFileInfo(editor->filePath()).absoluteFilePath() == QFileInfo(filePath).absoluteFilePath()) {
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
        QMessageBox::warning(this, tr("Rename File"), tr("Use one of these extensions: .c, .h, .inc, .res, .txt, .md, .sbui, .uis"));
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

    for (int i = m_editorTabs->count() - 1; i >= 0; --i) {
        QWidget *tab = m_editorTabs->widget(i);
        if (auto *designer = dynamic_cast<SidboxGuiDesigner *>(tab)) {
            if (QFileInfo(designer->filePath()).absoluteFilePath() == oldInfo.absoluteFilePath()) {
                m_editorTabs->removeTab(i);
                tab->deleteLater();
                openGuiDesigner(newPath);
                continue;
            }
        }
        auto *editor = primaryEditorForTab(tab);
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

void MainWindow::setCompileProgressStage(const QString &text)
{
    /*
     * The status message changes immediately so even lightning-fast builds
     * have useful feedback. The animated bar itself is delayed to avoid a
     * distracting flash when the whole build completes almost instantly.
     */
    statusBar()->showMessage(text);

    if (m_compileProgressBar) {
        m_compileProgressBar->setFormat(text);

        if (m_compileProgressBar->isVisible()) {
            return;
        }
    }

    if (m_compileProgressDelayTimer
        && !m_compileProgressDelayTimer->isActive()) {
        m_compileProgressDelayTimer->start();
    }
}

void MainWindow::finishCompileProgress()
{
    if (m_compileProgressDelayTimer) {
        m_compileProgressDelayTimer->stop();
    }

    if (m_compileProgressBar) {
        m_compileProgressBar->hide();
        m_compileProgressBar->setFormat(tr("Compiling..."));
    }
}

void MainWindow::handleCompilerFinished(int exitCode)
{
    if ((m_buildStep == BuildStep::Linking || m_buildStep == BuildStep::V2Compiling)
        && !m_compilerStderrBuffer.isEmpty()) {
        const QString finalLine = m_compilerStderrBuffer.toLower();
        if (finalLine.contains(QStringLiteral("applet image exceeds selected app size"))
            || (finalLine.contains(QStringLiteral("applet"))
                && finalLine.contains(QStringLiteral("region"))
                && (finalLine.contains(QStringLiteral("overflowed"))
                    || finalLine.contains(QStringLiteral("will not fit"))))) {
            m_buildLinkSizeOverflow = true;
        }
        appendOutputLine(
            m_compilerStderrBuffer,
            compilerOutputKindForLine(m_compilerStderrBuffer));
        processCompilerDiagnosticLine(m_compilerStderrBuffer);
        m_compilerStderrBuffer.clear();
    }

    if (m_buildStep == BuildStep::V2Compiling) {
        if (exitCode != 0) {
            appendOutputLine(tr("V2 PIC compilation failed for %1 (exit %2).")
                .arg(QDir::toNativeSeparators(m_v2CompileSources.value(m_v2CompileIndex)))
                .arg(exitCode), OutputKind::Error);
            m_buildStep = BuildStep::None;
            finishCompileProgress();
            statusBar()->showMessage(tr("Compile failed"));
            return;
        }
        ++m_v2CompileIndex;
        if (m_v2CompileIndex < m_v2CompileSources.size()) {
            QStringList compileArgs = m_v2CompileFlags;
            if (isResourceSource(m_v2CompileSources.at(m_v2CompileIndex))) {
                compileArgs << QStringLiteral("-x") << QStringLiteral("c");
            }
            compileArgs << QStringLiteral("-c")
                        << m_v2CompileSources.at(m_v2CompileIndex)
                        << QStringLiteral("-o")
                        << m_v2CompiledObjects.at(m_v2CompileIndex);
            m_compilerProcess->start(m_v2CompilerPath, compileArgs);
            return;
        }
        appendOutputLine(tr("V2 PIC objects compiled: %1")
            .arg(m_v2CompiledObjects.size()), OutputKind::Success);
        appendOutputLine(tr("Linking with LLVM LLD in PIE mode..."), OutputKind::Header);
        m_buildStep = BuildStep::Linking;
        setCompileProgressStage(tr("Linking V2 PIE..."));
        m_compilerProcess->start(m_v2LinkerPath, m_v2LinkArguments);
        return;
    }

    if (m_buildStep == BuildStep::Linking) {
        if (exitCode != 0) {
            appendOutputLine(tr("Link failed with exit code %1.").arg(exitCode), OutputKind::Error);
            m_buildStep = BuildStep::None;
            finishCompileProgress();
            statusBar()->showMessage(tr("Compile failed"));
            if (m_buildLinkSizeOverflow) {
                QMessageBox memoryWarning(this);
                memoryWarning.setIcon(QMessageBox::Warning);
                memoryWarning.setWindowTitle(tr("Applet memory limit exceeded"));
                memoryWarning.setText(
                    tr("The linker could not fit the applet into its allocated RAM."));
                memoryWarning.setInformativeText(
                    tr("Current applet allowance: %1 KB. The limit includes code, "
                       "embedded sounds, data, BSS and stack.\n\n"
                       "You can review Applet size in Project Settings. "
                       "Don't increase it beyond your reserved SDRAM layout.\n\n"
                       "The full linker error remains in the Build Output.")
                        .arg(m_appSizeKb));
                QPushButton *settingsButton = memoryWarning.addButton(
                    tr("Project Settings..."), QMessageBox::ActionRole);
                memoryWarning.addButton(QMessageBox::Close);
                memoryWarning.exec();
                if (memoryWarning.clickedButton() == settingsButton) {
                    showProjectSettings();
                }
            }
            return;
        }

        appendOutputLine(tr("Link finished successfully."), OutputKind::Success);

        // Validate the GCC-linked ELF *before* disassembly/packing.  A linker
        // that ignored PIE can emit ET_EXEC even when -fPIC compiled cleanly;
        // the V2 packer correctly refuses to reinterpret that file as ET_DYN.
        if (m_currentBuildIsV2) {
            QFile elf(m_pendingElfPath);
            if (!elf.open(QIODevice::ReadOnly)) {
                appendOutputLine(tr("V2 ELF check: cannot read the linked file: %1")
                    .arg(QDir::toNativeSeparators(m_pendingElfPath)), OutputKind::Error);
                m_buildStep = BuildStep::None;
                finishCompileProgress();
                statusBar()->showMessage(tr("Compile failed"));
                return;
            }
            const QByteArray header = elf.read(20);
            if (header.size() != 20 || !header.startsWith("\x7f" "ELF") ||
                quint8(header.at(4)) != 1 || quint8(header.at(5)) != 1) {
                appendOutputLine(tr("V2 ELF check: expected little-endian ELF32."), OutputKind::Error);
                m_buildStep = BuildStep::None;
                finishCompileProgress();
                statusBar()->showMessage(tr("Compile failed"));
                return;
            }
            const quint16 elfType = quint8(header.at(16)) |
                (quint16(quint8(header.at(17))) << 8);
            const quint16 elfMachine = quint8(header.at(18)) |
                (quint16(quint8(header.at(19))) << 8);
            const QString typeName = elfType == 3 ? QStringLiteral("ET_DYN") :
                elfType == 2 ? QStringLiteral("ET_EXEC") :
                QStringLiteral("other");
            appendOutputLine(tr("V2 ELF check: %1 (type %2), machine %3")
                .arg(typeName).arg(elfType).arg(elfMachine),
                elfType == 3 && elfMachine == 40 ? OutputKind::Success : OutputKind::Error);
            if (elfType != 3 || elfMachine != 40) {
                appendOutputLine(tr("V2 requires ARM ET_DYN. This build's linker produced "
                                    "an incompatible ELF despite the PIE request. No .app "
                                    "will be generated. The linker/toolchain configuration "
                                    "must be corrected; do not bypass the V2 packer check."),
                                 OutputKind::Error);
                m_buildStep = BuildStep::None;
                finishCompileProgress();
                statusBar()->showMessage(tr("Compile failed"));
                return;
            }
        }

        // Use linked symbols, not the on-disk .app size.  __stack_end__
        // includes the reserved stack; .app binary file size does not.
        QString nmExecutable = compilerPath();
        if (nmExecutable.endsWith(QStringLiteral("gcc"))) {
            nmExecutable.chop(3);
            nmExecutable += QStringLiteral("nm");
        } else if (nmExecutable.endsWith(QStringLiteral("gcc.exe"))) {
            nmExecutable.chop(7);
            nmExecutable += QStringLiteral("nm.exe");
        }
        if (QFileInfo::exists(nmExecutable)) {
            QProcess nm;
            nm.start(nmExecutable, {QStringLiteral("-n"), m_pendingElfPath});
            if (nm.waitForFinished(3000) && nm.exitStatus() == QProcess::NormalExit
                && nm.exitCode() == 0) {
                const QString symbols = QString::fromLocal8Bit(nm.readAllStandardOutput());
                const QRegularExpression entry(
                    QStringLiteral(R"(^([0-9a-fA-F]+)\s+[A-Za-z]\s+(_appstart|__stack_end__)\s*$)"),
                    QRegularExpression::MultilineOption);
                quint64 start = 0;
                quint64 end = 0;
                bool foundStart = false;
                bool foundEnd = false;
                auto matches = entry.globalMatch(symbols);
                while (matches.hasNext()) {
                    const QRegularExpressionMatch match = matches.next();
                    bool ok = false;
                    const quint64 address = match.captured(1).toULongLong(&ok, 16);
                    if (!ok) continue;
                    if (match.captured(2) == QStringLiteral("_appstart")) {
                        start = address;
                        foundStart = true;
                    } else {
                        end = address;
                        foundEnd = true;
                    }
                }
                if (foundStart && foundEnd && end >= start) {
                    // V2: the ELF includes reserved .stack, but the heap is an
                    // additional uninitialised allocation appended by the packer.
                    const qint64 used = qint64(end - start) +
                        (m_currentBuildIsV2 ? qint64(m_v2HeapKb) * 1024 : 0);
                    if (!m_linkerScriptPath.isEmpty()) {
                        appendOutputLine(
                            tr("Applet RAM used: %1 (including stack; custom linker controls the limit)")
                                .arg(formattedFileSize(used)),
                            OutputKind::Header);
                    } else {
                        const qint64 allowance = qint64(m_appSizeKb) * 1024;
                        appendOutputLine(
                            tr("Applet RAM: %1 / %2 used (%3%); %4 free (includes stack reserve%5)")
                                .arg(formattedFileSize(used))
                                .arg(formattedFileSize(allowance))
                                .arg(allowance > 0 ? qRound(100.0 * used / allowance) : 0)
                                .arg(formattedFileSize(qMax(qint64(0), allowance - used)))
                                .arg(m_currentBuildIsV2 ? tr(" and bounded heap") : QString()),
                            allowance > 0 && used * 100 >= allowance * 90
                                ? OutputKind::Warning : OutputKind::Success);
                    }
                }
            }
        }

        appendOutputLine(tr("Generating .asm output..."), OutputKind::Header);

        QString objdumpExec = objcopyPath();
        objdumpExec.replace(QStringLiteral("objcopy"), QStringLiteral("objdump"));

        m_buildStep = BuildStep::Asm;
        setCompileProgressStage(tr("Generating assembly..."));
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
            finishCompileProgress();
            statusBar()->showMessage(tr("Compile failed"));
            return;
        }

        const qint64 asmSize = QFileInfo(m_pendingAsmPath).size();
        appendOutputLine(tr("ASM generated: %1").arg(QDir::toNativeSeparators(m_pendingAsmPath)), OutputKind::Success);
        if (asmSize >= 0) {
            appendOutputLine(tr("ASM size: %1 bytes").arg(QLocale().toString(asmSize)), OutputKind::Success);
        }

        m_buildStep = BuildStep::Objcopy;
        setCompileProgressStage(tr("Creating applet..."));
        m_compilerProcess->setWorkingDirectory(m_projectPath);
        if (m_currentBuildIsV2) {
            appendOutputLine(tr("Packing and validating relocatable V2 ELF..."), OutputKind::Header);
            // Built from v2_packer.cpp at the IDE source root, but deployed
            // together with the other build tools under idelibs/tools/.
            // Never fall back to Python or to the legacy V1 objcopy path.
            const QString packerName =
#ifdef Q_OS_WIN
                QStringLiteral("sidbox-v2-packer.exe");
#else
                QStringLiteral("sidbox-v2-packer");
#endif
            const QString packerPath = QDir(ideLibsPath()).filePath(
                QStringLiteral("tools/") + packerName);
            const QFileInfo packerInfo(packerPath);
            if (!packerInfo.isFile() || !packerInfo.isExecutable()) {
                appendOutputLine(tr("Native V2 packer missing or not executable: %1. "
                                    "Rebuild SidboxIDE to stage it in idelibs/tools.")
                    .arg(QDir::toNativeSeparators(packerPath)), OutputKind::Error);
                m_buildStep = BuildStep::None;
                finishCompileProgress();
                statusBar()->showMessage(tr("Compile failed"));
                return;
            }
            // Passing --stack tells the Stage 6C loader to use its private
            // PSP bridge for window/timer callbacks.  The native packer checks
            // the ELF .stack reservation before marking the applet.
            m_compilerProcess->start(packerPath, {
                m_pendingElfPath, m_pendingAppPath,
                QStringLiteral("--heap"), QString::number(m_v2HeapKb * 1024),
                QStringLiteral("--stack"), QString::number(m_v2StackKb * 1024)
            });
        } else {
            appendOutputLine(tr("Generating legacy V1 .app binary..."), OutputKind::Header);
            m_compilerProcess->start(objcopyPath(), {
                QStringLiteral("-O"), QStringLiteral("binary"),
                m_pendingElfPath, m_pendingAppPath
            });
        }
        return;
    }

    if (m_buildStep == BuildStep::Objcopy) {
        if (exitCode != 0) {
            appendOutputLine(m_currentBuildIsV2
                ? tr("V2 packer rejected this ELF (exit %1). Inspect relocation errors; V1 remains available.").arg(exitCode)
                : tr("Objcopy failed with exit code %1.").arg(exitCode), OutputKind::Error);
            // Keep any previously working .app; the packer only publishes on success.
            // Do not leave an incomplete or mislabelled V2 image behind.
            m_buildStep = BuildStep::None;
            finishCompileProgress();
            statusBar()->showMessage(tr("Compile failed"));
            return;
        }

        const qint64 appSize = QFileInfo(m_pendingAppPath).size();
        appendOutputLine(tr("%1 APP generated: %2")
            .arg(m_currentBuildIsV2 ? QStringLiteral("V2") : QStringLiteral("V1"),
                 QDir::toNativeSeparators(m_pendingAppPath)), OutputKind::Success);
        if (appSize >= 0) {
            appendOutputLine(tr("APP size: %1 bytes").arg(QLocale().toString(appSize)), OutputKind::Success);
        }


        appendOutputLine(tr("Compile finished successfully."), OutputKind::Success);
        m_buildStep = BuildStep::None;
        finishCompileProgress();
        statusBar()->showMessage(tr("Compile successful"));
        return;
    }

    m_buildStep = BuildStep::None;
    finishCompileProgress();
}

QList<CodeEditor *> MainWindow::editorsForTab(QWidget *tabWidget) const
{
    QList<CodeEditor *> editors;

    if (!tabWidget) {
        return editors;
    }

    if (auto *editor = qobject_cast<CodeEditor *>(tabWidget)) {
        editors.append(editor);
        return editors;
    }

    if (auto *splitter = qobject_cast<QSplitter *>(tabWidget)) {
        for (int i = 0; i < splitter->count(); ++i) {
            if (auto *editor =
                    qobject_cast<CodeEditor *>(splitter->widget(i))) {
                editors.append(editor);
            }
        }
    }

    return editors;
}

CodeEditor *MainWindow::primaryEditorForTab(QWidget *tabWidget) const
{
    const QList<CodeEditor *> editors = editorsForTab(tabWidget);
    return editors.isEmpty() ? nullptr : editors.first();
}

int MainWindow::tabIndexForEditor(CodeEditor *editor) const
{
    if (!editor || !m_editorTabs) {
        return -1;
    }

    for (int i = 0; i < m_editorTabs->count(); ++i) {
        const QList<CodeEditor *> editors =
            editorsForTab(m_editorTabs->widget(i));

        if (editors.contains(editor)) {
            return i;
        }
    }

    return -1;
}

CodeEditor *MainWindow::activeEditor() const
{
    if (!m_editorTabs) {
        return nullptr;
    }

    QWidget *tabWidget = m_editorTabs->currentWidget();
    const QList<CodeEditor *> editors = editorsForTab(tabWidget);

    if (editors.isEmpty()) {
        return nullptr;
    }

    /*
     * In a split tab the editor which currently owns keyboard focus is the
     * active side.  This keeps line/column, Ctrl+Click, search jumps and other
     * editor actions naturally attached to the pane the programmer is using.
     */
    for (CodeEditor *editor : editors) {
        if (editor->hasFocus()
            || (editor->viewport() && editor->viewport()->hasFocus())) {
            return editor;
        }
    }

    return editors.first();
}

int MainWindow::editorSplitTabIndex() const
{
    if (!m_editorTabs) {
        return -1;
    }

    for (int i = 0; i < m_editorTabs->count(); ++i) {
        auto *splitter =
            qobject_cast<QSplitter *>(m_editorTabs->widget(i));

        if (splitter
            && splitter->objectName()
                == QStringLiteral("editorSplitView")) {
            return i;
        }
    }

    return -1;
}

QSplitter *MainWindow::editorSplitWidget() const
{
    const int index = editorSplitTabIndex();
    if (index < 0) {
        return nullptr;
    }

    return qobject_cast<QSplitter *>(
        m_editorTabs->widget(index));
}

CodeEditor *MainWindow::splitHostEditor(
    QSplitter *splitter) const
{
    if (!splitter) {
        return nullptr;
    }

    const QList<CodeEditor *> editors =
        editorsForTab(splitter);

    for (CodeEditor *editor : editors) {
        if (editor->property(
                "sidboxSplitHostEditor").toBool()) {
            return editor;
        }
    }

    return editors.isEmpty()
        ? nullptr
        : editors.first();
}

CodeEditor *MainWindow::splitSecondaryEditor(
    QSplitter *splitter) const
{
    if (!splitter) {
        return nullptr;
    }

    const QList<CodeEditor *> editors =
        editorsForTab(splitter);
    CodeEditor *host =
        splitHostEditor(splitter);

    for (CodeEditor *editor : editors) {
        if (editor != host) {
            return editor;
        }
    }

    return nullptr;
}

void MainWindow::updateEditorSplitPresentation()
{
    const int index = editorSplitTabIndex();
    QSplitter *splitter = editorSplitWidget();

    if (index < 0 || !splitter) {
        return;
    }

    CodeEditor *host = splitHostEditor(splitter);
    CodeEditor *secondary =
        splitSecondaryEditor(splitter);

    if (!host) {
        return;
    }

    QString title = tabTitleForEditor(host);
    QString tooltip = host->filePath();

    if (secondary
        && secondary->document() != host->document()) {
        title += QStringLiteral("  |  ");
        title += tabTitleForEditor(secondary);

        tooltip =
            tr("Split view:\n%1\n%2")
                .arg(
                    QDir::toNativeSeparators(
                        host->filePath()),
                    QDir::toNativeSeparators(
                        secondary->filePath()));
    }

    m_editorTabs->setTabText(index, title);
    m_editorTabs->setTabIcon(
        index,
        editorTabIconForFile(host->filePath()));
    m_editorTabs->setTabToolTip(index, tooltip);
}

void MainWindow::openCurrentTabInExistingSplit()
{
    const int splitIndex = editorSplitTabIndex();
    QSplitter *splitter = editorSplitWidget();

    if (splitIndex < 0 || !splitter) {
        toggleCurrentEditorSplit();
        return;
    }

    const int sourceTabIndex =
        m_editorTabs->currentIndex();

    if (sourceTabIndex < 0
        || sourceTabIndex == splitIndex) {
        return;
    }

    CodeEditor *sourceEditor =
        primaryEditorForTab(
            m_editorTabs->widget(sourceTabIndex));

    CodeEditor *host =
        splitHostEditor(splitter);
    CodeEditor *secondary =
        splitSecondaryEditor(splitter);

    if (!sourceEditor || !host || !secondary) {
        return;
    }

    QMessageBox sideBox(this);
    sideBox.setWindowTitle(tr("Open in Split"));
    sideBox.setText(
        tr("Which side should show %1?")
            .arg(
                QFileInfo(sourceEditor->filePath())
                    .fileName()));
    sideBox.setInformativeText(
        tr("The other side will keep %1.")
            .arg(
                QFileInfo(host->filePath())
                    .fileName()));

    QPushButton *leftButton =
        sideBox.addButton(
            tr("Left"),
            QMessageBox::AcceptRole);

    QPushButton *rightButton =
        sideBox.addButton(
            tr("Right"),
            QMessageBox::AcceptRole);

    sideBox.addButton(QMessageBox::Cancel);

    if (sideBox.exec() == QMessageBox::Cancel
        || !sideBox.clickedButton()) {
        return;
    }

    const bool sourceOnLeft =
        sideBox.clickedButton()
        == static_cast<QAbstractButton *>(
            leftButton);

    Q_UNUSED(rightButton);

    secondary->setProperty(
        "sidboxApiReference",
        sourceEditor->property(
            "sidboxApiReference"));
    secondary->shareDocumentFrom(sourceEditor);
    secondary->setTextCursor(
        sourceEditor->textCursor());
    secondary->verticalScrollBar()->setValue(
        sourceEditor->verticalScrollBar()->value());
    secondary->horizontalScrollBar()->setValue(
        sourceEditor->horizontalScrollBar()->value());
    secondary->setDiagnostics(
        sourceEditor->diagnostics());

    /*
     * Keep the split host's own live document on the opposite side.
     * The selected tab's live document is borrowed by the reusable secondary
     * view, so there is still only one document/save state for each file.
     */
    if (sourceOnLeft) {
        splitter->insertWidget(0, secondary);
    } else {
        splitter->insertWidget(1, secondary);
    }

    const int available =
        qMax(
            240,
            splitter->width()
                - splitter->handleWidth());

    splitter->setSizes(
        {
            available / 2,
            available - (available / 2)
        });

    m_editorTabs->setCurrentIndex(splitIndex);
    updateEditorSplitPresentation();

    secondary->setFocus();
    updateCursorPositionStatus();

    statusBar()->showMessage(
        tr("%1 opened in the %2 split")
            .arg(
                QFileInfo(sourceEditor->filePath())
                    .fileName(),
                sourceOnLeft
                    ? tr("left")
                    : tr("right")),
        3000);
}

void MainWindow::toggleCurrentEditorSplit()
{
    if (!m_editorTabs
        || m_editorTabs->currentIndex() < 0) {
        return;
    }

    const int index =
        m_editorTabs->currentIndex();

    QWidget *tabWidget =
        m_editorTabs->widget(index);

    QList<CodeEditor *> editors =
        editorsForTab(tabWidget);

    if (editors.isEmpty()) {
        statusBar()->showMessage(
            tr("This tab cannot be split"),
            2500);
        return;
    }

    const int existingSplitIndex =
        editorSplitTabIndex();

    if (existingSplitIndex >= 0
        && existingSplitIndex != index) {
        openCurrentTabInExistingSplit();
        return;
    }

    const QString tabText =
        m_editorTabs->tabText(index);
    const QIcon tabIcon =
        m_editorTabs->tabIcon(index);
    const QString tabToolTip =
        m_editorTabs->tabToolTip(index);

    if (auto *splitter =
            qobject_cast<QSplitter *>(tabWidget)) {
        CodeEditor *primary =
            splitHostEditor(splitter);
        CodeEditor *secondary =
            splitSecondaryEditor(splitter);

        if (!primary) {
            return;
        }

        if (secondary
            && activeEditor() == secondary
            && secondary->document()
                == primary->document()) {
            primary->setTextCursor(
                secondary->textCursor());
            primary->verticalScrollBar()->setValue(
                secondary->verticalScrollBar()->value());
            primary->horizontalScrollBar()->setValue(
                secondary->horizontalScrollBar()->value());
        }

        m_editorTabs->removeTab(index);
        primary->setParent(m_editorTabs);
        primary->setProperty(
            "sidboxSplitHostEditor",
            false);

        if (secondary) {
            secondary->deleteLater();
        }

        splitter->deleteLater();

        m_editorTabs->insertTab(
            index,
            primary,
            editorTabIconForFile(
                primary->filePath()),
            tabTitleForEditor(primary));

        m_editorTabs->setTabToolTip(
            index,
            primary->filePath());

        m_editorTabs->setCurrentIndex(index);

        primary->setFocus();
        updateCursorPositionStatus();

        statusBar()->showMessage(
            tr("Editor split closed"),
            2000);
        return;
    }

    CodeEditor *primary = editors.first();
    if (!primary) {
        return;
    }

    auto *splitter =
        new QSplitter(
            Qt::Horizontal,
            m_editorTabs);

    splitter->setObjectName(
        QStringLiteral("editorSplitView"));
    splitter->setChildrenCollapsible(false);
    splitter->setHandleWidth(4);

    primary->setProperty(
        "sidboxSplitHostEditor",
        true);

    m_editorTabs->removeTab(index);
    splitter->addWidget(primary);

    CodeEditor *secondary =
        createEditor(primary->filePath());

    secondary->setProperty(
        "sidboxApiReference",
        primary->property(
            "sidboxApiReference"));

    secondary->setProperty(
        "sidboxSplitHostEditor",
        false);

    secondary->shareDocumentFrom(primary);
    secondary->setTextCursor(
        primary->textCursor());
    secondary->verticalScrollBar()->setValue(
        primary->verticalScrollBar()->value());
    secondary->horizontalScrollBar()->setValue(
        primary->horizontalScrollBar()->value());

    splitter->addWidget(secondary);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 1);

    m_editorTabs->insertTab(
        index,
        splitter,
        tabIcon,
        tabText);

    m_editorTabs->setTabToolTip(
        index,
        tabToolTip);

    m_editorTabs->setCurrentIndex(index);

    splitter->show();
    primary->show();
    secondary->show();

    QTimer::singleShot(
        0,
        splitter,
        [splitter, primary, secondary]() {
            const int available =
                qMax(
                    240,
                    splitter->width()
                        - splitter->handleWidth());

            const int left = available / 2;
            const int right = available - left;

            primary->setMinimumWidth(120);
            secondary->setMinimumWidth(120);
            splitter->setSizes({left, right});
        });

    updateEditorSplitPresentation();

    primary->setFocus();
    updateCursorPositionStatus();

    statusBar()->showMessage(
        tr("Split active — select another tab and choose Open in Existing Split"),
        4500);
}

void MainWindow::updateCursorPositionStatus()
{
    if (!m_cursorPositionLabel) {
        return;
    }

    CodeEditor *editor = activeEditor();
    if (!editor) {
        m_cursorPositionLabel->clear();
        return;
    }

    const QTextCursor cursor = editor->textCursor();
    m_cursorPositionLabel->setText(
        tr("[ Ln %1, Col %2 ]  ")
            .arg(cursor.blockNumber() + 1)
            .arg(cursor.positionInBlock() + 1));
}

void MainWindow::watchEditorFile(CodeEditor *editor)
{
    if (!editor || !m_fileWatcher) {
        return;
    }

    const QString path =
        QFileInfo(editor->filePath()).absoluteFilePath();

    if (path.isEmpty() || !QFileInfo::exists(path)) {
        return;
    }

    if (!m_fileWatcher->files().contains(path)) {
        m_fileWatcher->addPath(path);
    }
}

void MainWindow::unwatchEditorFile(CodeEditor *editor)
{
    if (!editor || !m_fileWatcher) {
        return;
    }

    const QString path =
        QFileInfo(editor->filePath()).absoluteFilePath();

    if (!path.isEmpty() && m_fileWatcher->files().contains(path)) {
        m_fileWatcher->removePath(path);
    }

    m_pendingExternalReloads.remove(path);
}

void MainWindow::handleExternalFileChange(const QString &filePath)
{
    if (!m_fileWatcher || filePath.isEmpty()) {
        return;
    }

    const QString path = QFileInfo(filePath).absoluteFilePath();

    /*
     * One external save can produce several filesystem events. Coalesce them
     * into one reload after the writer has finished replacing the file.
     */
    if (m_pendingExternalReloads.contains(path)) {
        return;
    }

    m_pendingExternalReloads.insert(path);

    QTimer::singleShot(180, this, [this, path]() {
        m_pendingExternalReloads.remove(path);

        CodeEditor *editor = nullptr;
        for (int i = 0; i < m_editorTabs->count(); ++i) {
            auto *candidate =
                primaryEditorForTab(m_editorTabs->widget(i));

            if (candidate
                && QFileInfo(candidate->filePath()).absoluteFilePath() == path) {
                editor = candidate;
                break;
            }
        }

        /*
         * The tab may have been closed while the debounce timer was waiting.
         * In that case there is nothing left to watch.
         */
        if (!editor) {
            if (m_fileWatcher->files().contains(path)) {
                m_fileWatcher->removePath(path);
            }
            return;
        }

        /*
         * QFileSystemWatcher can drop a watched path when an editor performs
         * an atomic replace. By now the replacement should normally exist.
         */
        if (!QFileInfo::exists(path)) {
            statusBar()->showMessage(
                tr("%1 no longer exists on disk")
                    .arg(QFileInfo(path).fileName()),
                4000);
            return;
        }

        bool reload = true;

        if (editor->document()->isModified()) {
            const QMessageBox::StandardButton answer =
                QMessageBox::warning(
                    this,
                    tr("File Changed Outside Sidbox IDE"),
                    tr("%1 was changed outside Sidbox IDE, but this tab also "
                       "contains unsaved changes.\n\n"
                       "Reload the file and discard the unsaved IDE changes?")
                        .arg(QFileInfo(path).fileName()),
                    QMessageBox::Yes | QMessageBox::No,
                    QMessageBox::No);

            reload = (answer == QMessageBox::Yes);
        }

        if (reload) {
            reloadEditorFromDisk(editor);
        }

        /*
         * Re-arm after every external event. This is essential for applications
         * which save by replacing the file rather than modifying it in place.
         */
        watchEditorFile(editor);
    });
}

bool MainWindow::reloadEditorFromDisk(CodeEditor *editor)
{
    if (!editor || editor->filePath().isEmpty()) {
        return false;
    }

    const QString path =
        QFileInfo(editor->filePath()).absoluteFilePath();

    if (!QFileInfo::exists(path)) {
        return false;
    }

    const QTextCursor oldCursor = editor->textCursor();
    const int oldLine = oldCursor.blockNumber();
    const int oldColumn = oldCursor.positionInBlock();
    const int oldVerticalScroll = editor->verticalScrollBar()->value();
    const int oldHorizontalScroll = editor->horizontalScrollBar()->value();

    if (!editor->loadFromFile(path)) {
        statusBar()->showMessage(
            tr("Could not reload %1")
                .arg(QFileInfo(path).fileName()),
            4000);
        return false;
    }

    const QTextBlock block =
        editor->document()->findBlockByNumber(
            qBound(0, oldLine, qMax(0, editor->blockCount() - 1)));

    if (block.isValid()) {
        QTextCursor cursor(block);
        const int maxColumn = qMax(0, block.length() - 1);
        cursor.setPosition(
            block.position() + qMin(oldColumn, maxColumn));
        editor->setTextCursor(cursor);
    }

    editor->verticalScrollBar()->setValue(oldVerticalScroll);
    editor->horizontalScrollBar()->setValue(oldHorizontalScroll);
    editor->document()->setModified(false);
    updateTabTitle(editor);
    updateCursorPositionStatus();

    statusBar()->showMessage(
        tr("Reloaded %1 — changed outside Sidbox IDE")
            .arg(QFileInfo(path).fileName()),
        3000);

    return true;
}



void MainWindow::navigateEditorStructure(
    CodeEditor *editor,
    int direction)
{
    if (!editor
        || editor != activeEditor()) {
        return;
    }

    const QVariantList storedLines =
        editor->property(
            "sidboxStructureLines")
            .toList();

    QList<int> lines;
    lines.reserve(
        storedLines.size());

    for (const QVariant &value :
         storedLines) {
        const int line =
            value.toInt();

        if (line >= 0) {
            lines.append(line);
        }
    }

    std::sort(
        lines.begin(),
        lines.end());

    lines.erase(
        std::unique(
            lines.begin(),
            lines.end()),
        lines.end());

    if (lines.isEmpty()) {
        /*
         * The first catalogue for a freshly-opened/edited source may still be
         * running. Ask for it without blocking this shortcut.
         */
        if (editor->property(
                "sidboxAnalysisDirty")
                .toBool()
            || editor->property(
                "sidboxAnalysisWorkerRunning")
                .toBool()) {

            refreshActiveEditorAnalysis();

            statusBar()->showMessage(
                tr("Rebuilding catalogue: %1%")
                    .arg(
                        editor->property(
                            "sidboxCatalogueProgress")
                            .toInt()),
                1200);
        } else {
            statusBar()->showMessage(
                tr("No functions or typedef/struct types in this file"),
                1800);
        }

        return;
    }

    const int currentLine =
        editor->textCursor()
            .blockNumber();

    int targetLine = -1;

    if (direction < 0) {
        for (auto it = lines.crbegin();
             it != lines.crend();
             ++it) {
            if (*it < currentLine) {
                targetLine = *it;
                break;
            }
        }
    } else {
        for (int line :
             std::as_const(lines)) {
            if (line > currentLine) {
                targetLine = line;
                break;
            }
        }
    }

    if (targetLine < 0) {
        statusBar()->showMessage(
            direction < 0
                ? tr("Already at the first function/type")
                : tr("Already at the last function/type"),
            1200);
        return;
    }

    const QTextBlock block =
        editor->document()
            ->findBlockByNumber(
                targetLine);

    if (!block.isValid()) {
        return;
    }

    QTextCursor cursor(block);
    editor->setTextCursor(cursor);
    editor->centerCursor();
    editor->setFocus();

    updateCursorPositionStatus();
}


void MainWindow::selectNextEditorTab()
{
    if (!m_editorTabs
        || m_editorTabs->count() <= 0) {
        return;
    }

    const int current =
        m_editorTabs->currentIndex();

    const int next =
        current < 0
            ? 0
            : (current + 1)
                % m_editorTabs->count();

    m_editorTabs->setCurrentIndex(next);

    if (CodeEditor *editor =
            activeEditor()) {
        editor->setFocus();
    }
}


void MainWindow::showCatalogueProgress(
    CodeEditor *editor,
    int percent)
{
    if (!editor) {
        return;
    }

    const int boundedPercent =
        qBound(
            0,
            percent,
            100);

    editor->setProperty(
        "sidboxCatalogueProgress",
        boundedPercent);

    if (editor != activeEditor()) {
        return;
    }

    statusBar()->showMessage(
        tr("Rebuilding catalogue: %1%")
            .arg(boundedPercent),
        boundedPercent >= 100
            ? 1100
            : 0);
}


CodeEditor *MainWindow::createEditor(const QString &filePath)
{
    auto *editor = new CodeEditor(m_editorTabs);
    editor->setFilePath(filePath);

    editor->setProperty(
        "sidboxAnalysisDirty",
        true);

    editor->setProperty(
        "sidboxCatalogueProgress",
        0);

    editor->setProperty(
        "sidboxStructureLines",
        QVariantList());

    const bool resourceMode = isResourceSource(filePath);
    editor->setResourceMode(resourceMode);
    editor->setTheme(m_theme);

    if (!resourceMode) {
        ensureApiCatalog();

        /*
         * Keep tab creation cheap. projectFunctionSignatures() and
         * projectTypeNames() both scan the project and used to run here before
         * the new tab could even appear. The existing project-analysis timer
         * fills those project-wide lists shortly after the UI has updated.
         *
         * API completions are already cached by refreshApiCatalog(), so they
         * are safe to install immediately.
         */
        editor->setFunctionCompletions(m_apiSignatures);
        editor->setProjectTypeNames({});
        editor->setApiSyntaxNames(apiSyntaxNames());
    } else {
        editor->setFunctionCompletions({});
        editor->setProjectTypeNames({});
        editor->setApiSyntaxNames({});
    }
    applyCompilerDiagnostics(editor);

    QFont font = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    font.setPointSize(m_editorFontPointSize);
    editor->setFont(font);
    editor->setCompletionFont(font);
    editor->refreshLineNumberAreaWidth();

    connect(editor, &QPlainTextEdit::cursorPositionChanged,
            this, [this, editor]() {
                if (editor == activeEditor()) {
                    updateCursorPositionStatus();
                }
            });

    connect(editor->document(), &QTextDocument::modificationChanged, this, [this, editor]() {
        updateTabTitle(editor);
    });
    connect(editor->document(), &QTextDocument::contentsChanged,
            this, [this, editor]() {
        /*
         * Every edit invalidates any worker result already in flight. The worker
         * is not force-killed (it is off the UI thread anyway); its stale result
         * is simply discarded when it finishes.
         */
        const int generation =
            editor->property(
                "sidboxAnalysisGeneration")
                .toInt()
            + 1;

        editor->setProperty(
            "sidboxAnalysisGeneration",
            generation);

        editor->setProperty(
            "sidboxAnalysisDirty",
            true);

        /*
         * Normal typing only pushes the guaranteed catch-up pass two seconds
         * into the future.
         */
        if (!editor->isResourceMode()
            && editor == activeEditor()
            && tabIndexForEditor(editor) >= 0) {
            m_projectAnalysisTimer->start();
        }
    });

    connect(editor, &CodeEditor::deferredAnalysisSyncRequested,
            this, [this, editor]() {
        if (editor != activeEditor()) {
            return;
        }

        /*
         * Arrow/Home/End/Page keys, Enter, and mouse caret movement are explicit
         * sync points. Cancel the pending idle timer and refresh the active tab
         * immediately. CodeEditor only emits this when edits are actually dirty,
         * so repeatedly pressing arrows does not repeatedly rescan unchanged code.
         */
        if (m_projectAnalysisTimer) {
            m_projectAnalysisTimer->stop();
        }

        /*
         * This returns immediately: heavy semantic parsing now runs in the
         * thread pool, while fold/minimap work is sliced across event-loop turns.
         */
        refreshActiveEditorAnalysis();
    });

    connect(editor, &CodeEditor::structureNavigationRequested,
            this, [this, editor](int direction) {
        navigateEditorStructure(
            editor,
            direction);
    });

    connect(editor, &CodeEditor::nextEditorTabRequested,
            this, [this]() {
        selectNextEditorTab();
    });

    connect(editor, &CodeEditor::quickTipRequested, this, &MainWindow::showQuickTip);
    connect(editor, &CodeEditor::quickTipCandidateChanged, this, &MainWindow::showPassiveQuickTip);
    connect(editor, &CodeEditor::definitionRequested,
            this, [this, editor](const QString &symbol, int sourceLine) {
                goToDefinition(editor, symbol, sourceLine);
            });
    connect(editor, &CodeEditor::includeFileRequested,
            this, [this, editor](const QString &includeName) {
                openIncludedFile(editor, includeName);
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
        auto *editor = primaryEditorForTab(m_editorTabs->widget(i));
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
    if (QFileInfo(filePath).suffix().compare(QStringLiteral("sbui"), Qt::CaseInsensitive) == 0) {
        return openGuiDesigner(filePath);
    }

    for (int i = 0; i < m_editorTabs->count(); ++i) {
        //auto *editor = qobject_cast(m_editorTabs->widget(i));
        auto *editor = primaryEditorForTab(m_editorTabs->widget(i));
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
    const qint64 largeSourceThreshold = 2048LL * 1024LL;
    const qint64 veryLargeSourceThreshold = 4096LL * 1024LL;
    const QString suffix = openingFileInfo.suffix().toLower();

    const bool isSourceLike =
        suffix == QStringLiteral("c")
        || suffix == QStringLiteral("h")
        || suffix == QStringLiteral("cc")
        || suffix == QStringLiteral("cpp")
        || suffix == QStringLiteral("hpp")
        || suffix == QStringLiteral("inc")
        || suffix == QStringLiteral("uis");

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
    if (!editor->loadFromFile(filePath, true)) {
        editor->deleteLater();
        QMessageBox::warning(this, tr("Open File"), tr("Could not open %1.").arg(QDir::toNativeSeparators(filePath)));
        return false;
    }

    const int index = m_editorTabs->addTab(
        editor,
        editorTabIconForFile(filePath),
        tabTitleForEditor(editor));
    m_editorTabs->setCurrentIndex(index);

    /*
     * Give Qt one paint opportunity before asking QSyntaxHighlighter to walk
     * the document. Twenty milliseconds is visually instant, but it lets the
     * user see the file/tab immediately while the IDE prepares colouring and
     * the later project catalogue refresh.
     */
    QTimer::singleShot(20, editor, [editor]() {
        editor->enableSyntaxHighlighting();
    });

    watchEditorFile(editor);

    const QString absoluteProjectFile =
        QFileInfo(filePath).absoluteFilePath();
    const bool projectListChanged =
        !m_projectFilesInProject.contains(absoluteProjectFile);

    addProjectFile(filePath);

    /*
     * Merely opening an existing project file does not change the file tree.
     * Avoid recursively rebuilding that tree on every tab open.
     */
    if (projectListChanged) {
        refreshProjectFiles();
    }

    m_projectAnalysisTimer->start();
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
            primaryEditorForTab(m_editorTabs->widget(i));

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

        if (!editor->loadFromFile(absolutePath, true)) {
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
                editorTabIconForFile(absolutePath),
                tabTitleForEditor(editor));

        m_editorTabs->setTabToolTip(
            index,
            tr("Read-only Sidbox API source\n%1")
                .arg(QDir::toNativeSeparators(absolutePath)));

        m_editorTabs->setCurrentIndex(index);

        QTimer::singleShot(20, editor, [editor]() {
            editor->enableSyntaxHighlighting();
        });

        watchEditorFile(editor);
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
    const QString oldPath =
        QFileInfo(editor->filePath()).absoluteFilePath();

    /*
     * Do not treat Sidbox IDE's own save as an external edit.
     * Temporarily remove the file from QFileSystemWatcher and re-arm it after
     * the save completes.
     */
    if (!oldPath.isEmpty()
        && m_fileWatcher
        && m_fileWatcher->files().contains(oldPath)) {
        m_fileWatcher->removePath(oldPath);
    }
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
            watchEditorFile(editor);
            return false;
        }
    } else if (!editor->save()) {
        QMessageBox::warning(this, tr("Save File"), tr("Could not save %1.").arg(QDir::toNativeSeparators(editor->filePath())));
        watchEditorFile(editor);
        return false;
    }

    watchEditorFile(editor);

    const QString newPath =
        QFileInfo(editor->filePath()).absoluteFilePath();

    if (!oldPath.isEmpty()
        && oldPath != newPath) {
        m_cachedFileFunctionSignatures.remove(
            oldPath);
        m_cachedFileTypeNames.remove(
            oldPath);
    }

    const bool projectListChanged =
        !m_projectFilesInProject.contains(newPath);

    addProjectFile(editor->filePath());
    updateTabTitle(editor);

    if (wasUntitled
        || projectListChanged
        || (!oldPath.isEmpty() && oldPath != newPath)) {
        refreshProjectFiles();
    }

    m_projectAnalysisTimer->start();
    return true;
}


bool MainWindow::saveModifiedWorkBeforeNewProject()
{
    bool hasUnsavedWork = m_projectFilePath.isEmpty() && m_editorTabs->count() > 0;
    for (int i = 0; i < m_editorTabs->count(); ++i) {
        QWidget *tab = m_editorTabs->widget(i);
        if (auto *designer = dynamic_cast<SidboxGuiDesigner *>(tab)) {
            if (designer->isModified()) {
                hasUnsavedWork = true;
                break;
            }
        }
        auto *editor = primaryEditorForTab(tab);
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
        m_outputAppName.clear();
        m_modSizeKb = 0;
        m_projectType = GuiProjectType;
        m_appletFormat = QStringLiteral("v1");
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
    m_appletFormat = (m_projectType == GuiProjectType &&
        root.value(QStringLiteral("appletFormat")).toString() == QStringLiteral("v2"))
        ? QStringLiteral("v2") : QStringLiteral("v1");
    m_modSizeKb = root.value(QStringLiteral("modSizeKb")).toInt(0);
    m_appSizeKb = root.value(QStringLiteral("appSizeKb")).toInt(128);
    m_v2HeapKb = qBound(0, root.value(QStringLiteral("v2HeapKb")).toInt(16), 512);
    m_v2StackKb = qBound(1, root.value(QStringLiteral("v2StackKb")).toInt(8), 128);
    m_outputAppName =
        normalizedAppOutputName(
            root.value(QStringLiteral("outputAppName")).toString());
    if (m_appSizeKb < 16) {
        m_appSizeKb = 128;
    }

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

    /*
     * Project load is a project-level event, so build the per-file caches once.
     * Normal typing after this point only refreshes the active tab.
     */
    refreshFunctionCompletions();
    refreshSymbolTree();

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
        QWidget *tab = m_editorTabs->widget(i);
        if (auto *designer = dynamic_cast<SidboxGuiDesigner *>(tab)) {
            if (!designer->filePath().isEmpty()) {
                openTabsArray.append(toProjectRelativePath(designer->filePath()));
            }
            continue;
        }
        auto *editor = primaryEditorForTab(tab);
        if (editor && !editor->filePath().isEmpty()) {
            openTabsArray.append(toProjectRelativePath(editor->filePath()));
        }
    }

    QJsonObject root;
    root.insert(QStringLiteral("version"), ProjectFileVersion);
    root.insert(QStringLiteral("projectType"), normalizedProjectType(m_projectType));
    root.insert(QStringLiteral("appletFormat"),
                m_projectType == GameProjectType ? QStringLiteral("v1") : m_appletFormat);
    root.insert(QStringLiteral("files"), files);
    root.insert(QStringLiteral("openTabs"), openTabsArray);
    root.insert(QStringLiteral("linkerScript"), m_linkerScriptPath.isEmpty() ? QString() : toProjectRelativePath(m_linkerScriptPath));
    root.insert(QStringLiteral("modSizeKb"), m_modSizeKb);
    root.insert(QStringLiteral("appSizeKb"), m_appSizeKb);
    root.insert(QStringLiteral("v2HeapKb"), m_v2HeapKb);
    root.insert(QStringLiteral("v2StackKb"), m_v2StackKb);
    root.insert(QStringLiteral("outputAppName"), m_outputAppName);

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
    if (m_fileWatcher) {
        const QStringList watchedFiles = m_fileWatcher->files();
        if (!watchedFiles.isEmpty()) {
            m_fileWatcher->removePaths(watchedFiles);
        }
    }
    m_pendingExternalReloads.clear();
    m_cachedFileFunctionSignatures.clear();
    m_cachedFileTypeNames.clear();

    while (m_editorTabs->count() > 0) {
        QWidget *widget = m_editorTabs->widget(0);
        m_editorTabs->removeTab(0);
        widget->deleteLater();
    }
}

void MainWindow::rescanProjectFiles()
{
    if (m_projectPath.isEmpty()
        || !QFileInfo(m_projectPath).isDir()) {
        statusBar()->showMessage(
            tr("No project directory to rescan"),
            3000);
        return;
    }

    /*
     * projectFolderSourceFiles() is deliberately the single source of truth
     * for what belongs in the Files in Project tree.  At present that means:
     *
     *   .c  .h  .inc  .res  .txt  .md
     *
     * It scans subdirectories recursively and skips the generated build/
     * directory.  Linker scripts (.ld) stay out of the file tree because they
     * are managed separately in Project Settings.
     */
    const QStringList discoveredFiles =
        projectFolderSourceFiles();

    int addedCount = 0;

    for (const QString &filePath : discoveredFiles) {
        const QString absolutePath =
            QFileInfo(filePath).absoluteFilePath();

        if (!m_projectFilesInProject.contains(absolutePath)) {
            m_projectFilesInProject.append(absolutePath);
            ++addedCount;
        }
    }

    m_projectFilesInProject.removeDuplicates();
    m_projectFilesInProject.sort(Qt::CaseInsensitive);

    refreshProjectFiles();
    refreshFunctionCompletions();
    refreshSymbolTree();

    /*
     * Persist the newly discovered file list immediately when a real .proj
     * file is already open. This keeps Rescan behaving like "add these files
     * to my project", not merely "show them until I restart".
     */
    if (!m_projectFilePath.isEmpty()) {
        saveProjectFile(m_projectFilePath);
    }

    statusBar()->showMessage(
        addedCount == 1
            ? tr("Rescan complete — 1 new project file added")
            : tr("Rescan complete — %1 new project files added")
                  .arg(addedCount),
        3500);
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
        } else if (suffix == QStringLiteral("res")) {
            fileIcon = QIcon(QStringLiteral(":/icons/tree_file_res.png"));
        } else if (suffix == QStringLiteral("txt")) {
            fileIcon = QIcon(QStringLiteral(":/icons/tree_file_txt.png"));
        } else if (suffix == QStringLiteral("uis")) {
            fileIcon = QIcon(QStringLiteral(":/icons/tree_file_c.png"));
        } else if (suffix == QStringLiteral("sbui")) {
            fileIcon = QIcon(QStringLiteral(":/icons/tree_guidesigner.png"));
        } else if (suffix == QStringLiteral("md")) {
            fileIcon = QIcon(QStringLiteral(":/icons/tree_file_md.png"));
        } else {
            fileIcon = QIcon(QStringLiteral(":/icons/tree_file_unknown.png"));
        }

        const QString absoluteFilePath =
            fileInfo.absoluteFilePath();

        bool hasCompilerError = false;

        const auto diagnosticIt =
            m_compilerDiagnostics.constFind(
                absoluteFilePath);

        if (diagnosticIt
            != m_compilerDiagnostics.constEnd()) {
            for (const EditorDiagnostic &diagnostic :
                 diagnosticIt.value()) {
                if (diagnostic.severity
                    == EditorDiagnostic::Severity::Error) {
                    hasCompilerError = true;
                    break;
                }
            }
        }

        if (hasCompilerError) {
            fileIcon =
                projectFileIconWithErrorBadge(
                    fileIcon,
                    m_theme.diagnosticError);
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


void MainWindow::updateProjectDiagnosticMarkers()
{
    if (!m_projectFiles) {
        return;
    }

    auto fileHasError =
        [this](const QString &path) {
            const QString absolutePath =
                QFileInfo(path)
                    .absoluteFilePath();

            const auto it =
                m_compilerDiagnostics
                    .constFind(
                        absolutePath);

            if (it
                == m_compilerDiagnostics
                       .constEnd()) {
                return false;
            }

            for (const EditorDiagnostic &diagnostic :
                 it.value()) {
                if (diagnostic.severity
                    == EditorDiagnostic::Severity::Error) {
                    return true;
                }
            }

            return false;
        };

    std::function<void(QTreeWidgetItem *)>
        updateItem;

    updateItem =
        [this,
         &fileHasError,
         &updateItem](QTreeWidgetItem *item) {
            if (!item) {
                return;
            }

            const bool isFolder =
                item->data(
                        0,
                        Qt::UserRole + 1)
                    .toBool();

            if (!isFolder) {
                const QString filePath =
                    item->data(
                            0,
                            Qt::UserRole)
                        .toString();

                if (!filePath.isEmpty()) {
                    QIcon icon =
                        editorTabIconForFile(
                            filePath);

                    const bool hasError =
                        fileHasError(
                            filePath);

                    if (hasError) {
                        icon =
                            projectFileIconWithErrorBadge(
                                icon,
                                m_theme.diagnosticError);
                    }

                    item->setIcon(
                        0,
                        icon);

                    QString tooltip =
                        QDir::toNativeSeparators(
                            QFileInfo(filePath)
                                .absoluteFilePath());

                    if (hasError) {
                        tooltip +=
                            tr("\nCompiler error in this file");
                    }

                    item->setToolTip(
                        0,
                        tooltip);
                }
            }

            for (int i = 0;
                 i < item->childCount();
                 ++i) {
                updateItem(
                    item->child(i));
            }
        };

    for (int i = 0;
         i < m_projectFiles
                 ->topLevelItemCount();
         ++i) {
        updateItem(
            m_projectFiles
                ->topLevelItem(i));
    }
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

    if (m_symbolTreeEditor) {
        saveSymbolTreeExpansionState(
            m_symbolTreeEditor);
    }

    CodeEditor *editor =
        activeEditor();

    m_functionvarList->clear();

    if (!editor) {
        m_symbolTreeEditor = nullptr;
        return;
    }

    if (editor->isResourceMode()) {
        auto *resourceItem =
            new QTreeWidgetItem(
                m_functionvarList);

        resourceItem->setText(
            0,
            tr("Resource file — analysis disabled"));

        resourceItem->setFlags(
            resourceItem->flags()
            & ~Qt::ItemIsSelectable);

        m_symbolTreeEditor = editor;
        return;
    }

    /*
     * This synchronous version is retained for explicit project-level actions.
     * Normal editing uses refreshActiveEditorAnalysis(), which parses off the UI
     * thread and feeds the resulting table straight into this same tree builder.
     */
    const SourceSymbolTable symbols =
        parseSourceSymbols(
            editor->toPlainText());

    populateSourceSymbolTree(
        m_functionvarList,
        symbols);

    editor->setProperty(
        "sidboxStructureLines",
        structureNavigationLines(
            symbols));

    restoreSymbolTreeExpansionState(
        editor);

    m_symbolTreeEditor =
        editor;
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
            primaryEditorForTab(m_editorTabs->widget(i));

        if (!editor || editor == sourceEditor || editor->isResourceMode()) {
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


void MainWindow::openIncludedFile(
    CodeEditor *sourceEditor,
    const QString &includeName)
{
    if (!sourceEditor || includeName.trimmed().isEmpty()) {
        return;
    }

    const QString cleanInclude =
        QDir::cleanPath(includeName.trimmed());

    QStringList candidates;

    auto addCandidate =
        [&candidates](const QString &path) {
            if (path.isEmpty()) {
                return;
            }

            const QString absolute =
                QFileInfo(path).absoluteFilePath();

            if (!candidates.contains(absolute)) {
                candidates.append(absolute);
            }
        };

    /*
     * Match the same practical search order a C programmer expects:
     * current source directory first, then project root, then the Sidbox API
     * and library include roots.
     */
    const QFileInfo includeInfo(cleanInclude);
    if (includeInfo.isAbsolute()) {
        addCandidate(cleanInclude);
    } else {
        if (!sourceEditor->filePath().isEmpty()) {
            addCandidate(
                QDir(QFileInfo(sourceEditor->filePath()).absolutePath())
                    .filePath(cleanInclude));
        }

        if (!m_projectPath.isEmpty()) {
            addCandidate(
                QDir(m_projectPath)
                    .filePath(cleanInclude));
        }

        const QString libsRoot = ideLibsPath();
        addCandidate(
            QDir(QDir(libsRoot).filePath(QStringLiteral("api")))
                .filePath(cleanInclude));
        addCandidate(
            QDir(QDir(libsRoot).filePath(QStringLiteral("libraries")))
                .filePath(cleanInclude));
    }

    /*
     * Also consider known project files by relative path or basename. This is
     * useful for older projects whose file list contains a header outside the
     * immediate source directory.
     */
    QStringList projectFiles = m_projectFilesInProject;
    projectFiles.append(projectFolderSourceFiles());
    projectFiles.removeDuplicates();

    for (const QString &projectFile : std::as_const(projectFiles)) {
        const QFileInfo info(projectFile);

        if (info.fileName().compare(
                QFileInfo(cleanInclude).fileName(),
                Qt::CaseInsensitive) == 0) {
            addCandidate(info.absoluteFilePath());
        }

        if (!m_projectPath.isEmpty()) {
            const QString relative =
                QDir(m_projectPath)
                    .relativeFilePath(info.absoluteFilePath());

            if (QDir::cleanPath(relative).compare(
                    cleanInclude,
                    Qt::CaseInsensitive) == 0) {
                addCandidate(info.absoluteFilePath());
            }
        }
    }

    QString resolvedPath;
    for (const QString &candidate : std::as_const(candidates)) {
        const QFileInfo info(candidate);
        if (info.exists() && info.isFile()) {
            resolvedPath = info.absoluteFilePath();
            break;
        }
    }

    if (resolvedPath.isEmpty()) {
        statusBar()->showMessage(
            tr("Include not found: %1").arg(cleanInclude),
            3000);
        return;
    }

    /*
     * Sidbox's own API/library headers are references supplied by the IDE, so
     * keep those read-only. Project/local headers open as normal editable tabs.
     */
    const QString libsRoot =
        QFileInfo(ideLibsPath()).absoluteFilePath();

    const QString relativeToLibs =
        QDir(libsRoot).relativeFilePath(resolvedPath);

    const bool isIdeLibraryFile =
        !relativeToLibs.startsWith(QStringLiteral("../"))
        && relativeToLibs != QStringLiteral("..")
        && !QDir::isAbsolutePath(relativeToLibs);

    const bool opened =
        isIdeLibraryFile
            ? openApiReference(resolvedPath, 0)
            : openFile(resolvedPath);

    if (opened) {
        statusBar()->showMessage(
            tr("Opened include: %1")
                .arg(QDir::toNativeSeparators(resolvedPath)),
            2500);
    }
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

        const int tabIndex = tabIndexForEditor(editor);
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
        auto *editor = primaryEditorForTab(m_editorTabs->widget(i));
        if (!editor || editor == sourceEditor || editor->isResourceMode()) {
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
        const QString libsRoot = ideLibsPath();
        const QString apiPath =
            QDir(libsRoot).filePath(QStringLiteral("api"));
        const QString libraryPath =
            QDir(libsRoot).filePath(QStringLiteral("libraries"));

        QStringList apiSourceFiles;
        QStringList apiHeaderFiles;
        QStringList libraryHeaderFiles;

        if (QFileInfo::exists(apiPath)) {
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
        }

        if (QFileInfo::exists(libraryPath)) {
            QDirIterator libraryIterator(
                libraryPath,
                {QStringLiteral("*.h")},
                QDir::Files,
                QDirIterator::Subdirectories);

            while (libraryIterator.hasNext()) {
                libraryHeaderFiles.append(
                    QFileInfo(
                        libraryIterator.next())
                        .absoluteFilePath());
            }
        }

        /*
         * Prefer API .c implementations first, then API headers, then static
         * library headers. A .a archive is binary, so its accompanying .h is
         * the useful read-only reference target for Ctrl+Click.
         */
        apiSourceFiles.sort(Qt::CaseInsensitive);
        apiHeaderFiles.sort(Qt::CaseInsensitive);
        libraryHeaderFiles.sort(Qt::CaseInsensitive);

        QStringList sdkFiles = apiSourceFiles;
        sdkFiles.append(apiHeaderFiles);
        sdkFiles.append(libraryHeaderFiles);

        for (const QString &apiFilePath : std::as_const(sdkFiles)) {
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
                const QString absoluteLibraryRoot =
                    QFileInfo(libraryPath).absoluteFilePath();
                const QString absoluteReferencePath =
                    QFileInfo(apiFilePath).absoluteFilePath();

                const bool libraryReference =
                    QFileInfo::exists(libraryPath)
                    && absoluteReferencePath.startsWith(
                        absoluteLibraryRoot + QDir::separator());

                statusBar()->showMessage(
                    libraryReference
                        ? tr("%1 — Sidbox library header in %2:%3 (read-only)")
                              .arg(
                                  symbol,
                                  QFileInfo(apiFilePath).fileName())
                              .arg(apiLine + 1)
                        : tr("%1 — Sidbox API source in %2:%3 (read-only)")
                              .arg(
                                  symbol,
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

    m_cachedFileFunctionSignatures.clear();
    m_cachedFileTypeNames.clear();

    QHash<QString, CodeEditor *> openEditors;

    /*
     * Open tabs win over disk so a deliberate full refresh still sees unsaved
     * source correctly. Build a path -> editor map once rather than walking all
     * tabs repeatedly for every project file.
     */
    for (int i = 0; i < m_editorTabs->count(); ++i) {
        CodeEditor *editor =
            primaryEditorForTab(
                m_editorTabs->widget(i));

        if (!editor
            || editor->isResourceMode()
            || editor->filePath().isEmpty()) {
            continue;
        }

        const QString path =
            QFileInfo(editor->filePath())
                .absoluteFilePath();

        openEditors.insert(path, editor);
    }

    QStringList projectFiles =
        m_projectFilesInProject;

    projectFiles.append(
        projectFolderSourceFiles());

    for (auto it = openEditors.constBegin();
         it != openEditors.constEnd();
         ++it) {
        if (!projectFiles.contains(it.key())) {
            projectFiles.append(it.key());
        }
    }

    projectFiles.removeDuplicates();

    for (const QString &rawPath :
         std::as_const(projectFiles)) {
        const QString path =
            QFileInfo(rawPath)
                .absoluteFilePath();

        if (path.isEmpty()
            || !canContainFunctionSignatures(path)) {
            continue;
        }

        QString source;

        if (CodeEditor *editor =
                openEditors.value(path, nullptr)) {
            source = editor->toPlainText();
        } else {
            QFile file(path);

            if (!file.exists()
                || !file.open(
                    QIODevice::ReadOnly
                    | QIODevice::Text)) {
                continue;
            }

            source =
                QString::fromUtf8(
                    file.readAll());
        }

        const QString sanitized =
            sanitizedCSource(source);

        QStringList functions =
            functionSignaturesFromSanitizedFast(
                source,
                sanitized);

        QStringList types;

        const SourceSymbolTable symbols =
            parseSourceSymbolsFromSanitized(
                source,
                sanitized);

        for (const SourceNamedSymbol &type :
             symbols.types) {
            if (!type.name.isEmpty()) {
                types.append(type.name);
            }
        }

        functions.removeDuplicates();
        types.removeDuplicates();

        m_cachedFileFunctionSignatures.insert(
            path,
            functions);

        m_cachedFileTypeNames.insert(
            path,
            types);
    }

    QStringList completions =
        m_apiSignatures;

    QStringList typeNames;

    for (auto it =
             m_cachedFileFunctionSignatures.constBegin();
         it !=
             m_cachedFileFunctionSignatures.constEnd();
         ++it) {
        completions.append(it.value());
    }

    for (auto it =
             m_cachedFileTypeNames.constBegin();
         it !=
             m_cachedFileTypeNames.constEnd();
         ++it) {
        typeNames.append(it.value());
    }

    typeNames.removeDuplicates();
    typeNames.sort(Qt::CaseInsensitive);

    completions.append(typeNames);
    completions.removeDuplicates();
    completions.sort(Qt::CaseInsensitive);

    const QStringList apiNames =
        apiSyntaxNames();

    for (int i = 0;
         i < m_editorTabs->count();
         ++i) {
        const QList<CodeEditor *> editors =
            editorsForTab(
                m_editorTabs->widget(i));

        for (CodeEditor *editor :
             editors) {
            if (!editor) {
                continue;
            }

            if (editor->isResourceMode()) {
                editor->setFunctionCompletions({});
                editor->setProjectTypeNames({});
                editor->setApiSyntaxNames({});
                continue;
            }

            editor->setFunctionCompletions(
                completions);

            editor->setProjectTypeNames(
                typeNames);

            editor->setApiSyntaxNames(
                apiNames);
        }
    }
}


void MainWindow::refreshActiveEditorAnalysis()
{
    CodeEditor *editor =
        activeEditor();

    if (!editor) {
        return;
    }

    if (editor->isResourceMode()) {
        editor->setFunctionCompletions({});
        editor->setProjectTypeNames({});
        editor->setApiSyntaxNames({});
        return;
    }

    ensureApiCatalog();

    /*
     * If a worker is already cataloguing this tab, do not queue an army of
     * expensive copies/parses behind it. Remember that another pass is wanted;
     * the completed worker will either apply its still-current result or launch
     * one fresh pass if edits made it stale.
     */
    if (editor->property(
            "sidboxAnalysisWorkerRunning")
            .toBool()) {
        editor->setProperty(
            "sidboxAnalysisRerun",
            true);

        showCatalogueProgress(
            editor,
            editor->property(
                "sidboxCatalogueProgress")
                .toInt());

        return;
    }

    /*
     * Copying ~100-200 KB once is cheap compared with parsing it repeatedly on
     * the GUI thread. From this point onward the heavy work happens in a
     * QThreadPool worker.
     */
    const QString source =
        editor->toPlainText();

    const int generation =
        editor->property(
            "sidboxAnalysisGeneration")
            .toInt();

    const QString editorPath =
        editor->filePath().isEmpty()
            ? QString()
            : QFileInfo(editor->filePath())
                  .absoluteFilePath();

    editor->setProperty(
        "sidboxAnalysisWorkerRunning",
        true);

    editor->setProperty(
        "sidboxAnalysisRerun",
        false);

    showCatalogueProgress(
        editor,
        0);

    QPointer<MainWindow> self(this);
    QPointer<CodeEditor> guardedEditor(editor);

    QThreadPool::globalInstance()->start(
        QRunnable::create(
            [self,
             guardedEditor,
             source,
             generation,
             editorPath]() mutable {

                int lastProgress = 0;

                auto reportProgress =
                    [self,
                     guardedEditor,
                     generation,
                     &lastProgress](int percent) {
                        if (!self
                            || !guardedEditor) {
                            return;
                        }

                        const int bounded =
                            qBound(
                                0,
                                percent,
                                100);

                        /*
                         * Avoid filling the GUI event queue with duplicate
                         * percentages when a source contains many functions.
                         */
                        if (bounded <= lastProgress) {
                            return;
                        }

                        lastProgress =
                            bounded;

                        QMetaObject::invokeMethod(
                            self.data(),
                            [self,
                             guardedEditor,
                             generation,
                             bounded]() {
                                if (!self
                                    || !guardedEditor) {
                                    return;
                                }

                                CodeEditor *editor =
                                    guardedEditor.data();

                                if (self->activeEditor()
                                        != editor
                                    || editor->property(
                                           "sidboxAnalysisGeneration")
                                           .toInt()
                                           != generation) {
                                    return;
                                }

                                self->showCatalogueProgress(
                                    editor,
                                    bounded);
                            },
                            Qt::QueuedConnection);
                    };

                /*
                 * Sanitize ONCE, then reuse that copy for both the detailed
                 * symbol catalogue and the ultra-light function signature pass.
                 */
                const QString sanitized =
                    sanitizedCSource(source);

                reportProgress(18);

                SourceSymbolTable symbols =
                    parseSourceSymbolsFromSanitized(
                        source,
                        sanitized,
                        reportProgress);

                QStringList localFunctions =
                    functionSignaturesFromSanitizedFast(
                        source,
                        sanitized);

                reportProgress(96);

                QStringList localTypes;

                for (const SourceNamedSymbol &type :
                     symbols.types) {
                    if (!type.name.isEmpty()) {
                        localTypes.append(
                            type.name);
                    }
                }

                localFunctions.removeDuplicates();
                localTypes.removeDuplicates();

                QVariantList structureLines =
                    structureNavigationLines(
                        symbols);

                if (!self) {
                    return;
                }

                QMetaObject::invokeMethod(
                    self.data(),
                    [self,
                     guardedEditor,
                     generation,
                     editorPath,
                     symbols = std::move(symbols),
                     localFunctions =
                         std::move(localFunctions),
                     localTypes =
                         std::move(localTypes),
                     structureLines =
                         std::move(structureLines)]() mutable {

                        if (!self
                            || !guardedEditor) {
                            return;
                        }

                        CodeEditor *editor =
                            guardedEditor.data();

                        editor->setProperty(
                            "sidboxAnalysisWorkerRunning",
                            false);

                        const bool rerunRequested =
                            editor->property(
                                "sidboxAnalysisRerun")
                                .toBool();

                        editor->setProperty(
                            "sidboxAnalysisRerun",
                            false);

                        /*
                         * Any edit increments the generation. A stale worker is
                         * simply ignored — no half-old catalogue is ever applied.
                         */
                        const bool stillCurrent =
                            editor->property(
                                "sidboxAnalysisGeneration")
                                .toInt()
                                == generation;

                        if (!stillCurrent
                            || self->activeEditor()
                                != editor) {

                            if (self->activeEditor()
                                    == editor) {
                                self->statusBar()
                                    ->showMessage(
                                        self->tr(
                                            "Catalogue changed — waiting for the next sync"),
                                        900);
                            }

                            if (rerunRequested
                                && self->activeEditor()
                                    == editor) {
                                QTimer::singleShot(
                                    0,
                                    self.data(),
                                    [self]() {
                                        if (self) {
                                            self
                                                ->refreshActiveEditorAnalysis();
                                        }
                                    });
                            }

                            return;
                        }

                        if (!editorPath.isEmpty()) {
                            self
                                ->m_cachedFileFunctionSignatures
                                .insert(
                                    editorPath,
                                    localFunctions);

                            self
                                ->m_cachedFileTypeNames
                                .insert(
                                    editorPath,
                                    localTypes);
                        }

                        QStringList completions =
                            self->m_apiSignatures;

                        QStringList typeNames;

                        for (auto it =
                                 self
                                     ->m_cachedFileFunctionSignatures
                                     .constBegin();
                             it !=
                                 self
                                     ->m_cachedFileFunctionSignatures
                                     .constEnd();
                             ++it) {
                            completions.append(
                                it.value());
                        }

                        for (auto it =
                                 self
                                     ->m_cachedFileTypeNames
                                     .constBegin();
                             it !=
                                 self
                                     ->m_cachedFileTypeNames
                                     .constEnd();
                             ++it) {
                            typeNames.append(
                                it.value());
                        }

                        if (editorPath.isEmpty()) {
                            completions.append(
                                localFunctions);

                            typeNames.append(
                                localTypes);
                        }

                        typeNames.removeDuplicates();
                        typeNames.sort(
                            Qt::CaseInsensitive);

                        completions.append(
                            typeNames);

                        completions.removeDuplicates();
                        completions.sort(
                            Qt::CaseInsensitive);

                        const QStringList apiNames =
                            self->apiSyntaxNames();

                        QWidget *currentTab =
                            self->m_editorTabs
                                ? self
                                      ->m_editorTabs
                                      ->currentWidget()
                                : nullptr;

                        if (currentTab) {
                            const QList<CodeEditor *>
                                currentEditors =
                                    self->editorsForTab(
                                        currentTab);

                            for (CodeEditor *current :
                                 currentEditors) {
                                if (!current
                                    || current
                                        ->isResourceMode()) {
                                    continue;
                                }

                                current
                                    ->setFunctionCompletions(
                                        completions);

                                current
                                    ->setProjectTypeNames(
                                        typeNames);

                                current
                                    ->setApiSyntaxNames(
                                        apiNames);
                            }
                        }

                        editor->setProperty(
                            "sidboxStructureLines",
                            structureLines);

                        /*
                         * Reuse the already-parsed worker result for the tree.
                         * Previously the tree called parseSourceSymbols() AGAIN
                         * immediately after active-tab completion analysis.
                         */
                        if (self->m_functionvarList) {
                            if (self
                                    ->m_symbolTreeEditor) {
                                self
                                    ->saveSymbolTreeExpansionState(
                                        self
                                            ->m_symbolTreeEditor);
                            }

                            self
                                ->m_functionvarList
                                ->clear();

                            populateSourceSymbolTree(
                                self
                                    ->m_functionvarList,
                                symbols);

                            self
                                ->restoreSymbolTreeExpansionState(
                                    editor);

                            self->m_symbolTreeEditor =
                                editor;
                        }

                        editor->setProperty(
                            "sidboxAnalysisDirty",
                            false);

                        self->showCatalogueProgress(
                            editor,
                            100);

                        /*
                         * A navigation event may have requested one newer pass
                         * while this worker was running. Do that pass now, but
                         * still off the UI thread.
                         */
                        if (rerunRequested) {
                            QTimer::singleShot(
                                0,
                                self.data(),
                                [self]() {
                                    if (self) {
                                        self
                                            ->refreshActiveEditorAnalysis();
                                    }
                                });
                        }
                    },
                    Qt::QueuedConnection);
            }));
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

    const QString libsRoot = ideLibsPath();
    const QString apiPath =
        QDir(libsRoot).filePath(QStringLiteral("api"));
    const QString libraryPath =
        QDir(libsRoot).filePath(QStringLiteral("libraries"));

    QStringList catalogTexts;
    int scannedFileCount = 0;

    auto appendCatalogFiles =
        [&catalogTexts, &scannedFileCount](
            const QString &rootPath,
            const QStringList &filters) {
            if (!QFileInfo::exists(rootPath)) {
                return;
            }

            QDirIterator iterator(
                rootPath,
                filters,
                QDir::Files,
                QDirIterator::Subdirectories);

            while (iterator.hasNext()) {
                QFile file(iterator.next());
                if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                    continue;
                }

                catalogTexts.append(
                    uncommentedApiText(
                        QString::fromUtf8(file.readAll())));
                ++scannedFileCount;
            }
        };

    // Core Sidbox API: declarations plus source-side wrappers/types.
    appendCatalogFiles(
        apiPath,
        {QStringLiteral("*.h"), QStringLiteral("*.c")});

    /*
     * Static libraries expose their public interface through the accompanying
     * headers.  The .a archive itself is binary and cannot be meaningfully
     * parsed for Cheat Sheet descriptions/signatures, so catalogue the .h
     * files and let the build system continue linking every .a as before.
     */
    appendCatalogFiles(
        libraryPath,
        {QStringLiteral("*.h")});

    if (catalogTexts.isEmpty()) {
        if (m_quickTipLabel) {
            m_quickTipLabel->setText(
                tr("F1: API/library catalogue not found under %1")
                    .arg(QDir::toNativeSeparators(libsRoot)));
        }
        return;
    }

    QHash<QString, QString> functionPointers;
    for (const QString &text : std::as_const(catalogTexts)) {
        collectApiFunctionPointers(text, &functionPointers);
    }

    for (const QString &text : std::as_const(catalogTexts)) {
        collectApiMacros(
            text,
            functionPointers,
            &m_apiTips,
            &m_apiSignatures);
        collectApiDefines(
            text,
            &m_apiTips,
            &m_apiSignatures);
        collectApiTypes(
            text,
            &m_apiTips,
            &m_apiSignatures);
        collectApiLineSymbols(
            text,
            &m_apiTips,
            &m_apiSignatures);
        m_apiSignatures.append(
            functionSignaturesFromText(text));
    }

    m_apiSignatures.removeDuplicates();
    m_apiSignatures.sort(Qt::CaseInsensitive);

    if (m_quickTipLabel) {
        m_quickTipLabel->setText(
            tr("F1: SDK ready: %1 tips from %2 API/library files")
                .arg(m_apiTips.count())
                .arg(scannedFileCount));
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

    /*
     * This function is used by passive cursor tips. Cursor movement happens on
     * normal typing too, so never launch a whole-project scan here.
     */
    for (auto it =
             m_cachedFileFunctionSignatures.constBegin();
         it !=
             m_cachedFileFunctionSignatures.constEnd();
         ++it) {
        for (const QString &signature : it.value()) {
            const int parenIndex =
                signature.indexOf(QLatin1Char('('));

            const QString functionName =
                parenIndex > 0
                    ? signature.left(parenIndex)
                    : signature;

            if (functionName.compare(
                    name,
                    Qt::CaseInsensitive) == 0) {
                return signature;
            }
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
    const int index = tabIndexForEditor(editor);
    if (index >= 0) {
        m_editorTabs->setTabText(
            index,
            tabTitleForEditor(editor));

        m_editorTabs->setTabIcon(
            index,
            editorTabIconForFile(
                editor->filePath()));
    }

    updateEditorSplitPresentation();
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
        QStringLiteral("*.res"), QStringLiteral("*.txt"), QStringLiteral("*.md"),
        QStringLiteral("*.sbui"), QStringLiteral("*.uis")
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
        QWidget *tab = m_editorTabs->widget(i);
        if (auto *designer = dynamic_cast<SidboxGuiDesigner *>(tab)) {
            const QString designPath = QFileInfo(designer->filePath()).absoluteFilePath();
            if (!designPath.isEmpty() && !files.contains(designPath)) files.append(designPath);
            const QString cPath = QFileInfo(designPath).dir().filePath(QFileInfo(designPath).completeBaseName() + QStringLiteral(".c"));
            if (QFileInfo::exists(cPath) && !files.contains(QFileInfo(cPath).absoluteFilePath())) files.append(QFileInfo(cPath).absoluteFilePath());
            continue;
        }
        auto *editor = primaryEditorForTab(tab);
        if (!editor || editor->filePath().isEmpty()) continue;
        const QString filePath = QFileInfo(editor->filePath()).absoluteFilePath();
        if (!files.contains(filePath)) files.append(filePath);
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
        auto *editor = primaryEditorForTab(m_editorTabs->widget(i));
        if (!editor || editor->isResourceMode()) {
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
        auto *editor = primaryEditorForTab(m_editorTabs->widget(i));
        if (!editor || editor->isResourceMode()) {
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

QStringList MainWindow::functionSignaturesFromText(
    const QString &text) const
{
    /*
     * The old implementation used a global QRegularExpression over the whole
     * file. For Sidbox's catalogue use-case a tiny linear C scanner is both
     * cheaper and more predictable on 100-200 KB sources.
     */
    const QString sanitized =
        sanitizedCSource(text);

    return functionSignaturesFromSanitizedFast(
        text,
        sanitized);
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
            primaryEditorForTab(m_editorTabs->widget(i));

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
            primaryEditorForTab(m_editorTabs->widget(i));

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

    const QString sourcePath = (normalizedProjectType(m_projectType) == GuiProjectType &&
        m_appletFormat == QStringLiteral("v2"))
        ? QDir(ideLibsPath()).filePath(QStringLiteral("gui_v2.ld"))
        : defaultLinkerScriptPath();
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

    const bool linkerV2 = normalizedProjectType(m_projectType) == GuiProjectType &&
        m_appletFormat == QStringLiteral("v2");
    const bool linkedSettingsOk = linkerV2
        ? (replaceLinkerAssignment(&scriptText, QStringLiteral("_v2_app_limit"), hexBytes(m_appSizeKb))
           && replaceLinkerAssignment(&scriptText, QStringLiteral("_v2_stack_bytes"), hexBytes(m_v2StackKb))
           && replaceLinkerAssignment(&scriptText, QStringLiteral("_v2_heap_bytes"), hexBytes(m_v2HeapKb)))
        : (replaceLinkerAssignment(&scriptText, QStringLiteral("_profile_is_desktop"), profileValue)
           && replaceLinkerAssignment(&scriptText, QStringLiteral("_requested_app_size"), hexBytes(m_appSizeKb))
           && replaceLinkerAssignment(&scriptText, QStringLiteral("_largest_modfile"), hexBytes(m_modSizeKb)));
    if (!linkedSettingsOk) {
        if (errorMessage) {
            *errorMessage = tr("The template linker script is missing an expected Sidbox setting.");
        }
        return false;
    }

    /*
     * The template's wizard comment contains the template app-size value.
     * Keep that human-readable line synchronized too, otherwise somebody can
     * quite reasonably see one value in Project Settings and another in the
     * generated .ld even though the assignment itself is correct.
     */
    const QString appSizeHex = hexBytes(m_appSizeKb);
    scriptText.replace(
        QRegularExpression(
            QStringLiteral(
                R"((Applet allowance:\s*)\d+\s*KB\s*/\s*0x[0-9A-Fa-f]+)")),
        QStringLiteral("\\1%1 KB / %2")
            .arg(m_appSizeKb)
            .arg(appSizeHex));

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
        const QList<CodeEditor *> editors =
            editorsForTab(m_editorTabs->widget(i));

        for (CodeEditor *editor : editors) {
            editor->setFont(font);
            editor->setTabStopDistance(
                editor->fontMetrics().horizontalAdvance(QLatin1Char(' ')) * 4);
            editor->setCompletionFont(font);
            editor->refreshLineNumberAreaWidth();
        }
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
        "QProgressBar { background-color:%7; color:%3; border:1px solid %6; "
        " border-radius:0px; text-align:center; }"
        "QProgressBar::chunk { background-color:%5; border-radius:0px; "
        " width:18px; margin:1px; }"
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
            const QList<CodeEditor *> editors =
                editorsForTab(m_editorTabs->widget(i));
            for (CodeEditor *editor : editors) {
                editor->setTheme(m_theme);
            }
        }
    }
}

void MainWindow::clearCompilerDiagnostics()
{
    m_compilerStderrBuffer.clear();
    m_compilerDiagnostics.clear();

    updateProjectDiagnosticMarkers();

    if (!m_editorTabs) {
        return;
    }

    for (int i = 0; i < m_editorTabs->count(); ++i) {
        const QList<CodeEditor *> editors =
            editorsForTab(m_editorTabs->widget(i));

        for (CodeEditor *editor : editors) {
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

        const QString lowerLine = line.toLower();
        if (m_buildStep == BuildStep::Linking
            && (lowerLine.contains(QStringLiteral("applet image exceeds selected app size"))
                || ((lowerLine.contains(QStringLiteral("region"))
                     && lowerLine.contains(QStringLiteral("applet")))
                    && (lowerLine.contains(QStringLiteral("overflowed"))
                        || lowerLine.contains(QStringLiteral("will not fit")))))) {
            m_buildLinkSizeOverflow = true;
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
            auto *editor = primaryEditorForTab(m_editorTabs->widget(i));
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
                auto *editor = primaryEditorForTab(m_editorTabs->widget(i));
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

    if (severity
        == EditorDiagnostic::Severity::Error) {
        updateProjectDiagnosticMarkers();
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

    const QString path =
        QFileInfo(editor->filePath()).absoluteFilePath();
    const QList<EditorDiagnostic> diagnostics =
        m_compilerDiagnostics.value(path);

    const int tabIndex = tabIndexForEditor(editor);
    if (tabIndex >= 0) {
        const QList<CodeEditor *> editors =
            editorsForTab(m_editorTabs->widget(tabIndex));
        for (CodeEditor *view : editors) {
            view->setDiagnostics(diagnostics);
        }
        return;
    }

    editor->setDiagnostics(diagnostics);
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
