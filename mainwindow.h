#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "codeeditor.h"
#include "idetheme.h"
#include "findreplacedialog.h"
#include <QMainWindow>
#include <QSet>
#include <QHash>
#include <QList>
#include <QString>
#include <QStringList>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class QLabel;
class QListWidget;
class QTreeWidget;
class QTreeWidgetItem;
class QPlainTextEdit;
class QToolBar;
class QProcess;
class QProgressBar;
class QTabWidget;
class QSplitter;
class QTimer;
class QFileSystemWatcher;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    void showStartupProjectChooser();

private:

    QHash<CodeEditor *, QSet<QString>> m_symbolTreeExpanded;
    CodeEditor *m_symbolTreeEditor = nullptr;
    void setupInterface();
    void createNewProject();
    void createNewSourceFile();
    void createNewHeaderFile();
    void openProject();
    bool saveProject();
    void showOptions();
    void showFindReplace();
    void showFindReplaceForCurrentWord();
    void showProjectSettings();
    void showApiCheatSheet();
    void showAboutIde();
    void compileActiveFile();
    void openProjectFile(QTreeWidgetItem *item, int column);
    void addExistingProjectFile();
    void createProjectFile();
    void createProjectFileInDirectory(const QString &directoryPath);
    void createResourceFile();
    void createResourceFileInDirectory(const QString &directoryPath);
    void createProjectFolderInDirectory(const QString &directoryPath);
    QString projectContextDirectory(QTreeWidgetItem *item) const;
    void moveProjectFile(const QString &sourceFilePath, const QString &targetDirectory);
    void removeSelectedProjectFile();
    void renameSelectedProjectFile();
    void handleCompilerFinished(int exitCode);
    void setCompileProgressStage(const QString &text);
    void finishCompileProgress();
    bool closeEditorTab(int index);

    CodeEditor *activeEditor() const;
    CodeEditor *primaryEditorForTab(QWidget *tabWidget) const;
    QList<CodeEditor *> editorsForTab(QWidget *tabWidget) const;
    int tabIndexForEditor(CodeEditor *editor) const;
    int editorSplitTabIndex() const;
    QSplitter *editorSplitWidget() const;
    CodeEditor *splitHostEditor(QSplitter *splitter) const;
    CodeEditor *splitSecondaryEditor(QSplitter *splitter) const;
    void updateEditorSplitPresentation();
    void openCurrentTabInExistingSplit();
    void toggleCurrentEditorSplit();
    void updateCursorPositionStatus();
    CodeEditor *createEditor(const QString &filePath = QString());
    void watchEditorFile(CodeEditor *editor);
    void unwatchEditorFile(CodeEditor *editor);
    void handleExternalFileChange(const QString &filePath);
    bool reloadEditorFromDisk(CodeEditor *editor);
    bool openFile(const QString &filePath);
    bool openApiReference(const QString &filePath, int line);
    bool saveEditor(CodeEditor *editor);
    bool saveModifiedWorkBeforeNewProject();
    bool loadProjectFile(const QString &filePath);
    bool saveProjectFile(const QString &filePath);
    void addProjectFile(const QString &filePath);
    void clearEditorTabs();
    void refreshProjectFiles();
    void rescanProjectFiles();
    void refreshSymbolTree();
    void jumpToSymbol(QTreeWidgetItem *item, int column);
    void goToDefinition(CodeEditor *sourceEditor, const QString &symbol, int sourceLine);
    void openIncludedFile(CodeEditor *sourceEditor, const QString &includeName);
    void completeStructMembers(CodeEditor *sourceEditor,
                               const QString &objectName,
                               int sourceLine,
                               const QString &prefix);

    void saveSymbolTreeExpansionState(CodeEditor *editor);
    void restoreSymbolTreeExpansionState(CodeEditor *editor);

    void refreshFunctionCompletions();
    void ensureApiCatalog();
    void refreshApiCatalog();
    void showPassiveQuickTip(const QString &symbol);
    void showQuickTip(const QString &symbol);
    QString quickTipForSymbol(const QString &symbol) const;
    void updateTabTitle(CodeEditor *editor);
    QString tabTitleForEditor(CodeEditor *editor, int type = 0) const;
    QString displayPath(const QString &filePath) const;
    QString projectFileDisplayText(const QString &filePath) const;
    QStringList projectFolderSourceFiles() const;
    bool isProjectExplorerFile(const QString &filePath) const;
    QStringList collectOpenProjectFiles() const;
    QStringList projectFilesForCompile() const;
    QStringList projectFunctionSignatures() const;
    QStringList projectTypeNames() const;
    QStringList apiSyntaxNames() const;
    QStringList functionSignaturesFromText(const QString &text) const;

    QList<ProjectSearchResult> findInProject(
        const QString &needle,
        bool matchCase,
        bool wholeWord) const;
    bool replaceProjectResults(
        const QList<ProjectSearchResult> &results,
        const QString &replacement);
    void jumpToProjectSearchResult(const ProjectSearchResult &result);
    QString toProjectRelativePath(const QString &filePath) const;
    QString fromProjectRelativePath(const QString &filePath) const;
    QString ideLibsPath() const;
    QString defaultLinkerScriptPath(const QString &projectType = QString()) const;
    QString projectLinkerScriptPath() const;
    QString effectiveLinkerScriptPath() const;
    bool updateProjectLinkerScript(QString *errorMessage = nullptr) const;
    QString compilerPath() const;
    QString objcopyPath() const;
    QStringList sidboxApiSourceFiles() const;
    QStringList sidboxLibraryFiles() const;
    enum class OutputKind {
        Normal,
        Header,
        Path,
        Success,
        Error,
        Warning,
        Muted
    };

    void applyEditorFont();
    void applyTheme();
    void appendOutputText(const QString &text, OutputKind kind);
    void appendOutputLine(const QString &text, OutputKind kind);

    void clearCompilerDiagnostics();
    void processCompilerStderrChunk(const QString &text);
    OutputKind compilerOutputKindForLine(const QString &line) const;
    void processCompilerDiagnosticLine(const QString &line);
    void applyCompilerDiagnostics(CodeEditor *editor);
    QString normalizedDiagnosticPath(const QString &compilerPath) const;

    void loadOptions();
    void saveOptions() const;
    void AutoSelectMainC();

    enum class BuildStep {
        None,
        Linking,
        Asm,
        Objcopy
    };

    Ui::MainWindow *ui;
    QTreeWidget *m_projectFiles;
    QTabWidget *m_editorTabs;
    QTreeWidget *m_functionvarList;
    QLabel *m_quickTipLabel;
    QLabel *m_cursorPositionLabel = nullptr;
    QProgressBar *m_compileProgressBar = nullptr;
    QPlainTextEdit *m_outputPane;
    QToolBar *m_outputToolBar;
    FindReplaceDialog *m_findReplaceDialog;
    QProcess *m_compilerProcess;
    QTimer *m_projectAnalysisTimer;
    QTimer *m_compileProgressDelayTimer;
    QFileSystemWatcher *m_fileWatcher;
    QSet<QString> m_pendingExternalReloads;
    BuildStep m_buildStep;
    QString m_pendingElfPath;
    QString m_pendingAsmPath;
    QString m_pendingAppPath;
    QString m_projectPath;
    QString m_projectFilePath;
    QStringList m_projectFilesInProject;
    QHash<QString, QString> m_apiTips;
    QStringList m_apiSignatures;

    QString m_compilerStderrBuffer;
    QHash<QString, QList<EditorDiagnostic>> m_compilerDiagnostics;
    QString m_linkerScriptPath;
    QString m_outputAppName;
    QString m_projectType;
    int m_modSizeKb;
    int m_appSizeKb;
    int m_editorFontPointSize;
    QString m_compilerOptimization;
    QString m_extraCompilerFlags;
    bool m_compilerSuppressWarnings;
    bool m_compilerWall;
    bool m_compilerWextra;
    bool m_compilerFunctionSections;
    bool m_compilerDataSections;
    bool m_compilerStackUsage;
    IDETheme m_theme;
};
#endif // MAINWINDOW_H
