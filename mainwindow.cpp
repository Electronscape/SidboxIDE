#include "mainwindow.h"

#include "codeeditor.h"
#include "optionsdialog.h"
#include "ui_mainwindow.h"

#include <QAction>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QKeySequence>
#include <QLabel>
#include <QListWidget>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QProcess>
#include <QRegularExpression>
#include <QSettings>
#include <QSplitter>
#include <QStatusBar>
#include <QTabWidget>
#include <QTextDocument>
#include <QToolBar>
#include <QVBoxLayout>

namespace {
constexpr int ProjectFileVersion = 1;

bool isCompilableSource(const QString &filePath)
{
    const QString suffix = QFileInfo(filePath).suffix().toLower();
    return suffix == QStringLiteral("c") || suffix == QStringLiteral("cc") || suffix == QStringLiteral("cpp");
}

bool canContainFunctionSignatures(const QString &filePath)
{
    const QString suffix = QFileInfo(filePath).suffix().toLower();
    return suffix == QStringLiteral("c") || suffix == QStringLiteral("h")
        || suffix == QStringLiteral("cc") || suffix == QStringLiteral("cpp")
        || suffix == QStringLiteral("hpp");
}
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_projectFiles(nullptr)
    , m_editorTabs(nullptr)
    , m_outputPane(nullptr)
    , m_outputToolBar(nullptr)
    , m_compilerProcess(new QProcess(this))
    , m_modSizeKb(0)
{
    ui->setupUi(this);
    loadOptions();
    setupInterface();

    connect(m_compilerProcess, &QProcess::readyReadStandardOutput, this, [this]() {
        m_outputPane->appendPlainText(QString::fromLocal8Bit(m_compilerProcess->readAllStandardOutput()));
    });
    connect(m_compilerProcess, &QProcess::readyReadStandardError, this, [this]() {
        m_outputPane->appendPlainText(QString::fromLocal8Bit(m_compilerProcess->readAllStandardError()));
    });
    connect(m_compilerProcess, &QProcess::errorOccurred, this, [this](QProcess::ProcessError) {
        m_outputPane->appendPlainText(tr("Could not start compiler. Make sure gcc is installed and on PATH."));
        statusBar()->showMessage(tr("Compile failed"));
    });
    connect(m_compilerProcess, &QProcess::finished, this, &MainWindow::handleCompilerFinished);

    createNewSourceFile();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupInterface()
{
    setWindowTitle(tr("Sidbox IDE"));
    resize(1100, 720);

    auto *toolBar = addToolBar(tr("Project"));
    toolBar->setMovable(false);

    QAction *newAction = toolBar->addAction(tr("New"));
    QAction *openProjectAction = toolBar->addAction(tr("Open Project"));
    QAction *saveProjectAction = toolBar->addAction(tr("Save Project"));
    QAction *optionsAction = toolBar->addAction(tr("Options"));
    toolBar->addSeparator();
    QAction *compileAction = toolBar->addAction(tr("Compile"));

    newAction->setShortcut(QKeySequence::New);
    openProjectAction->setShortcut(QKeySequence::Open);
    saveProjectAction->setShortcut(QKeySequence::Save);
    compileAction->setShortcut(Qt::Key_F5);

    connect(newAction, &QAction::triggered, this, &MainWindow::createNewSourceFile);
    connect(openProjectAction, &QAction::triggered, this, &MainWindow::openProject);
    connect(saveProjectAction, &QAction::triggered, this, &MainWindow::saveProject);
    connect(optionsAction, &QAction::triggered, this, &MainWindow::showOptions);
    connect(compileAction, &QAction::triggered, this, &MainWindow::compileActiveFile);

    auto *mainSplitter = new QSplitter(Qt::Horizontal, this);

    auto *projectPane = new QWidget(mainSplitter);
    auto *projectLayout = new QVBoxLayout(projectPane);
    projectLayout->setContentsMargins(8, 8, 8, 8);
    projectLayout->setSpacing(6);

    auto *projectLabel = new QLabel(tr("Files in Project"), projectPane);
    m_projectFiles = new QListWidget(projectPane);
    m_projectFiles->setAlternatingRowColors(true);
    projectLayout->addWidget(projectLabel);
    projectLayout->addWidget(m_projectFiles, 1);

    connect(m_projectFiles, &QListWidget::itemDoubleClicked, this, &MainWindow::openProjectFile);
    connect(m_projectFiles, &QListWidget::itemActivated, this, &MainWindow::openProjectFile);

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

    m_outputToolBar = new QToolBar(tr("Compiler Output"), outputPanel);
    m_outputToolBar->setMovable(false);
    QAction *clearOutputAction = m_outputToolBar->addAction(tr("Clear"));
    connect(clearOutputAction, &QAction::triggered, this, [this]() {
        m_outputPane->clear();
    });

    m_outputPane = new QPlainTextEdit(outputPanel);
    m_outputPane->setReadOnly(true);
    m_outputPane->setTextInteractionFlags(Qt::NoTextInteraction);
    m_outputPane->setAcceptDrops(false);
    m_outputPane->viewport()->setAcceptDrops(false);
    m_outputPane->setPlaceholderText(tr("Compiler output"));
    m_outputPane->setMaximumBlockCount(1000);

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
    mainSplitter->setSizes({220, 880});

    setCentralWidget(mainSplitter);
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::createNewSourceFile()
{
    CodeEditor *editor = createEditor();
    editor->setPlainText(QStringLiteral("#include <stdio.h>\n\nint main(void)\n{\n    printf(\"Hello, Sidbox!\\n\");\n    return 0;\n}\n"));
    editor->document()->setModified(false);

    const int index = m_editorTabs->addTab(editor, tabTitleForEditor(editor));
    m_editorTabs->setCurrentIndex(index);
    refreshFunctionCompletions();
    statusBar()->showMessage(tr("New C source file created"));
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

void MainWindow::saveProject()
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
        return;
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
            return;
        }

        if (QFileInfo(projectFilePath).suffix().isEmpty()) {
            projectFilePath.append(QStringLiteral(".proj"));
        }
    }

    if (saveProjectFile(projectFilePath)) {
        refreshProjectFiles();
        statusBar()->showMessage(tr("Project saved: %1").arg(QDir::toNativeSeparators(m_projectFilePath)));
    }
}

void MainWindow::showOptions()
{
    OptionsDialog dialog(this);
    dialog.setLinkerScriptPath(m_linkerScriptPath);
    dialog.setModSizeKb(m_modSizeKb);

    if (dialog.exec() != QDialog::Accepted) {
        return;
    }

    m_linkerScriptPath = dialog.linkerScriptPath();
    m_modSizeKb = dialog.modSizeKb();
    saveOptions();

    statusBar()->showMessage(tr("Options saved"));
}

void MainWindow::compileActiveFile()
{
    CodeEditor *editor = activeEditor();
    if (!editor) {
        QMessageBox::information(this, tr("Compile"), tr("Open a project source file before compiling."));
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

    const QString filePath = editor->filePath();
    const QFileInfo sourceInfo(filePath);
    const QStringList sourceFiles = projectFilesForCompile();

    if (sourceFiles.isEmpty()) {
        QMessageBox::information(this, tr("Compile"), tr("Add at least one .c, .cc, or .cpp file to the project before compiling."));
        return;
    }

    const QString workingDirectory = m_projectPath.isEmpty() ? sourceInfo.absolutePath() : m_projectPath;
    const QString outputDirectory = QDir(workingDirectory).filePath(QStringLiteral(".sidbox-build"));

    QDir().mkpath(outputDirectory);

    const QString outputName = m_projectFilePath.isEmpty()
        ? sourceInfo.completeBaseName()
        : QFileInfo(m_projectFilePath).completeBaseName();
    const QString outputPath = QDir(outputDirectory).filePath(outputName);
    QStringList arguments = {QStringLiteral("-Wall"), QStringLiteral("-Wextra")};
    arguments << sourceFiles << QStringLiteral("-o") << outputPath;

    if (!m_linkerScriptPath.isEmpty()) {
        const QFileInfo linkerInfo(m_linkerScriptPath);
        if (!linkerInfo.exists()) {
            QMessageBox::warning(this, tr("Compile"), tr("The selected linker script does not exist."));
            return;
        }

        arguments << QStringLiteral("-T") << m_linkerScriptPath;
    }

    if (m_modSizeKb > 0) {
        arguments << QStringLiteral("-Wl,--defsym=MOD_SIZE=%1").arg(m_modSizeKb * 1024);
    }

    m_outputPane->clear();
    m_outputPane->appendPlainText(tr("Compiling project sources:"));
    for (const QString &sourceFile : sourceFiles) {
        m_outputPane->appendPlainText(tr("  %1").arg(displayPath(sourceFile)));
    }
    m_outputPane->appendPlainText(tr("Output: %1").arg(QDir::toNativeSeparators(outputPath)));
    if (!m_projectFilePath.isEmpty()) {
        m_outputPane->appendPlainText(tr("Project: %1").arg(QDir::toNativeSeparators(m_projectFilePath)));
    }
    if (!m_linkerScriptPath.isEmpty()) {
        m_outputPane->appendPlainText(tr("Linker script: %1").arg(QDir::toNativeSeparators(m_linkerScriptPath)));
    }
    if (m_modSizeKb > 0) {
        m_outputPane->appendPlainText(tr("MOD size: %1 KB").arg(m_modSizeKb));
    }

    m_compilerProcess->setWorkingDirectory(workingDirectory);
    m_compilerProcess->start(QStringLiteral("gcc"), arguments);

    statusBar()->showMessage(tr("Compile started"));
}

void MainWindow::openProjectFile(QListWidgetItem *item)
{
    if (!item) {
        return;
    }

    openFile(item->data(Qt::UserRole).toString());
}

void MainWindow::handleCompilerFinished(int exitCode)
{
    if (exitCode == 0) {
        m_outputPane->appendPlainText(tr("Compile finished successfully."));
        statusBar()->showMessage(tr("Compile successful"));
    } else {
        m_outputPane->appendPlainText(tr("Compile failed with exit code %1.").arg(exitCode));
        statusBar()->showMessage(tr("Compile failed"));
    }
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

    connect(editor->document(), &QTextDocument::modificationChanged, this, [this, editor]() {
        updateTabTitle(editor);
    });
    connect(editor->document(), &QTextDocument::contentsChanged, this, [this]() {
        refreshFunctionCompletions();
    });

    return editor;
}

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

bool MainWindow::saveEditor(CodeEditor *editor)
{
    if (!editor) {
        return false;
    }

    const bool wasUntitled = editor->filePath().isEmpty();
    if (wasUntitled) {
        const QString baseDirectory = m_projectPath.isEmpty() ? QDir::homePath() : m_projectPath;
        const QString filePath = QFileDialog::getSaveFileName(
            this,
            tr("Save Source File"),
            QDir(baseDirectory).filePath(QStringLiteral("main.c")),
            tr("C source/header files (*.c *.h *.cc *.cpp *.hpp);;All files (*)"));

        if (filePath.isEmpty()) {
            return false;
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

    const QString linkerScript = root.value(QStringLiteral("linkerScript")).toString();
    if (!linkerScript.isEmpty()) {
        m_linkerScriptPath = fromProjectRelativePath(linkerScript);
    }
    m_modSizeKb = root.value(QStringLiteral("modSizeKb")).toInt(m_modSizeKb);
    saveOptions();

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
    m_projectFilesInProject = collectOpenProjectFiles();

    QJsonArray files;
    for (const QString &projectFile : std::as_const(m_projectFilesInProject)) {
        files.append(toProjectRelativePath(projectFile));
    }

    QJsonObject root;
    root.insert(QStringLiteral("version"), ProjectFileVersion);
    root.insert(QStringLiteral("files"), files);
    root.insert(QStringLiteral("linkerScript"), toProjectRelativePath(m_linkerScriptPath));
    root.insert(QStringLiteral("modSizeKb"), m_modSizeKb);

    QFile file(m_projectFilePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(this, tr("Save Project"), tr("Could not save %1.").arg(QDir::toNativeSeparators(m_projectFilePath)));
        return false;
    }

    file.write(QJsonDocument(root).toJson(QJsonDocument::Indented));
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

    for (const QString &filePath : std::as_const(m_projectFilesInProject)) {
        auto *item = new QListWidgetItem(displayPath(filePath), m_projectFiles);
        item->setData(Qt::UserRole, filePath);
    }
}

void MainWindow::refreshFunctionCompletions()
{
    const QStringList signatures = projectFunctionSignatures();
    for (int i = 0; i < m_editorTabs->count(); ++i) {
        auto *editor = qobject_cast<CodeEditor *>(m_editorTabs->widget(i));
        if (editor) {
            editor->setFunctionCompletions(signatures);
        }
    }
}

void MainWindow::updateTabTitle(CodeEditor *editor)
{
    const int index = m_editorTabs->indexOf(editor);
    if (index >= 0) {
        m_editorTabs->setTabText(index, tabTitleForEditor(editor));
    }
}

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

QString MainWindow::displayPath(const QString &filePath) const
{
    if (m_projectPath.isEmpty()) {
        return QFileInfo(filePath).fileName();
    }

    return QDir(m_projectPath).relativeFilePath(filePath);
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
    for (const QString &filePath : m_projectFilesInProject) {
        if (isCompilableSource(filePath)) {
            files.append(filePath);
        }
    }
    return files;
}

QStringList MainWindow::projectFunctionSignatures() const
{
    QStringList signatures;
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

void MainWindow::loadOptions()
{
    QSettings settings(QStringLiteral("Sidbox"), QStringLiteral("SidboxIDE"));
    m_linkerScriptPath = settings.value(QStringLiteral("compiler/linkerScript")).toString();
    m_modSizeKb = settings.value(QStringLiteral("compiler/modSizeKb"), 0).toInt();
}

void MainWindow::saveOptions() const
{
    QSettings settings(QStringLiteral("Sidbox"), QStringLiteral("SidboxIDE"));
    settings.setValue(QStringLiteral("compiler/linkerScript"), m_linkerScriptPath);
    settings.setValue(QStringLiteral("compiler/modSizeKb"), m_modSizeKb);
}
