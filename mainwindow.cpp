#include "mainwindow.h"

#include "codeeditor.h"
#include "optionsdialog.h"
#include "projectsettingsdialog.h"
#include "ui_mainwindow.h"

#include <QAction>
#include <QApplication>
#include <QColor>
#include <QAbstractButton>
#include <QCoreApplication>
#include <QDir>
#include <QDirIterator>
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
#include <QTextCursor>
#include <QTextDocument>
#include <QToolBar>
#include <QVBoxLayout>
#include <QStandardPaths>

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
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setupInterface()
{
    setWindowTitle(tr("Sidbox IDE"));
    QIcon icon = QApplication::windowIcon().isNull() ? QIcon(":/icons/icon.png") : QApplication::windowIcon();
    setWindowIcon(icon);
    resize(1600, 880);


    auto *toolBar = addToolBar(tr("Project"));
    toolBar->setMovable(false);

    QAction *newAction = toolBar->addAction(tr("New"));
    auto *newMenu = new QMenu(this);
    QAction *newProjectAction = newMenu->addAction(tr("New Project"));
    QAction *newSourceAction = newMenu->addAction(tr("New C Source File"));
    QAction *newHeaderAction = newMenu->addAction(tr("New H Header File"));
    newAction->setMenu(newMenu);

    QAction *openProjectAction = toolBar->addAction(tr("Open Project [CTRL+O]"));
    QAction *saveProjectAction = toolBar->addAction(tr("Save Project [CTRL+S]"));
    QAction *projectSettingsAction = toolBar->addAction(tr("Project Settings"));
    QAction *optionsAction = toolBar->addAction(tr("Options"));
    toolBar->addSeparator();
    QAction *compileAction = toolBar->addAction(tr("Compile [F5]"));

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
    connect(newSourceAction, &QAction::triggered, this, &MainWindow::createNewSourceFile);
    connect(newHeaderAction, &QAction::triggered, this, &MainWindow::createNewHeaderFile);
    connect(openProjectAction, &QAction::triggered, this, &MainWindow::openProject);
    connect(saveProjectAction, &QAction::triggered, this, &MainWindow::saveProject);
    connect(projectSettingsAction, &QAction::triggered, this, &MainWindow::showProjectSettings);
    connect(optionsAction, &QAction::triggered, this, &MainWindow::showOptions);
    connect(compileAction, &QAction::triggered, this, &MainWindow::compileActiveFile);

    auto *mainSplitter = new QSplitter(Qt::Horizontal, this);



    auto *projectPane = new QWidget(mainSplitter);
    projectPane->setMinimumWidth(200); // Prevents resizing the left panel smaller than 200px

    auto *projectLayout = new QVBoxLayout(projectPane);
    projectLayout->setContentsMargins(8, 8, 8, 8);
    projectLayout->setSpacing(6);

    auto *projectLabel = new QLabel(tr("Files in Project"), projectPane);
    m_projectFiles = new QListWidget(projectPane);
    m_projectFiles->setStyleSheet(QStringLiteral(
        "QListWidget {"
        "   border: 1px solid #102048;"
        "   border-radius: 0px;"
        "}"
        "QListWidget::item {"
        "   border-radius: 0px;"
        "}"
        "QListWidget::item:selected {"
        "   background-color: #2858A8;"
        "   color: #ffffff;"
        "}"
        "QListWidget::item:selected:hover {"
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

    connect(m_projectFiles, &QListWidget::itemDoubleClicked, this, &MainWindow::openProjectFile);
    connect(m_projectFiles, &QListWidget::itemActivated, this, &MainWindow::openProjectFile);
    connect(addFileButton, &QPushButton::clicked, this, &MainWindow::addExistingProjectFile);
    connect(createFileButton, &QPushButton::clicked, this, &MainWindow::createProjectFile);
    connect(removeFileButton, &QPushButton::clicked, this, &MainWindow::removeSelectedProjectFile);
    connect(renameFileAction, &QAction::triggered, this, &MainWindow::renameSelectedProjectFile);
    connect(m_projectFiles, &QListWidget::customContextMenuRequested, this, [this](const QPoint &pos) {
        QMenu menu(this);
        menu.addAction(tr("Add File"), this, &MainWindow::addExistingProjectFile);
        menu.addAction(tr("Create File"), this, &MainWindow::createProjectFile);
        menu.addSeparator();
        menu.addAction(tr("Rename"), this, &MainWindow::renameSelectedProjectFile);
        menu.addAction(tr("Remove"), this, &MainWindow::removeSelectedProjectFile);
        menu.exec(m_projectFiles->viewport()->mapToGlobal(pos));
    });

    auto *workAreaSplitter = new QSplitter(Qt::Vertical, mainSplitter);
    m_editorTabs = new QTabWidget(workAreaSplitter);
    m_editorTabs->setDocumentMode(true);
    m_editorTabs->setTabsClosable(true);
    m_editorTabs->setMovable(true);

    connect(m_editorTabs, &QTabWidget::tabCloseRequested, this, [this](int index) {
        QWidget *widget = m_editorTabs->widget(index);
        m_editorTabs->removeTab(index);
        widget->deleteLater();
        refreshFunctionCompletions();
    });

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

    mainSplitter->addWidget(projectPane);
    mainSplitter->addWidget(workAreaSplitter);
    mainSplitter->setStretchFactor(0, 1);
    mainSplitter->setStretchFactor(1, 5);
    mainSplitter->setSizes({100, 1600});



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
    typeBox.exec();

    if (typeBox.clickedButton() == nullptr || typeBox.standardButton(typeBox.clickedButton()) == QMessageBox::Cancel) {
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
}

bool MainWindow::saveProject()
{
    bool allSaved = true;

    for (int i = 0; i < m_editorTabs->count(); ++i) {
        auto *editor = qobject_cast<CodeEditor *>(m_editorTabs->widget(i));
        if (!editor) {
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




void MainWindow::openProjectFile(QListWidgetItem *item)
{
    if (!item) {
        return;
    }

    openFile(item->data(Qt::UserRole).toString());
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
    if (m_projectPath.isEmpty()) {
        QMessageBox::information(this, tr("Create File"), tr("Save or create a project first so the IDE knows which folder to use."));
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

    const QString filePath = QFileInfo(QDir(m_projectPath).filePath(fileName)).absoluteFilePath();
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

void MainWindow::removeSelectedProjectFile()
{
    QListWidgetItem *item = m_projectFiles->currentItem();
    if (!item) {
        return;
    }

    const QString filePath = item->data(Qt::UserRole).toString();
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
    QListWidgetItem *item = m_projectFiles->currentItem();
    if (!item) {
        return;
    }

    const QString oldPath = item->data(Qt::UserRole).toString();
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
    connect(editor->document(), &QTextDocument::contentsChanged, this, [this]() {
        refreshFunctionCompletions();
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
        QMessageBox::Save | QMessageBox::Cancel,
        QMessageBox::Save);

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

    for (const QString &projectFile : std::as_const(m_projectFilesInProject)) {
        openFile(projectFile);
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

    QJsonObject root;
    root.insert(QStringLiteral("version"), ProjectFileVersion);
    root.insert(QStringLiteral("projectType"), normalizedProjectType(m_projectType));
    root.insert(QStringLiteral("files"), files);
    root.insert(QStringLiteral("linkerScript"), m_linkerScriptPath.isEmpty() ? QString() : toProjectRelativePath(m_linkerScriptPath));
    root.insert(QStringLiteral("modSizeKb"), m_modSizeKb);

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

        auto *item = new QListWidgetItem(projectFileDisplayText(filePath), m_projectFiles);
        item->setData(Qt::UserRole, QFileInfo(filePath).absoluteFilePath());
        item->setToolTip(QDir::toNativeSeparators(QFileInfo(filePath).absoluteFilePath()));
    }
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
