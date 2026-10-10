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
class QCloseEvent;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    void showStartupProjectChooser();

protected:
    void closeEvent(QCloseEvent *event) override;

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
    void createGuiDesigner();
    bool openGuiDesigner(const QString &filePath);
    bool saveGuiDesignerTab(QWidget *widget);
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
    void navigateEditorStructure(CodeEditor *editor, int direction);
    void selectNextEditorTab();
    void showCatalogueProgress(CodeEditor *editor, int percent);
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
    void refreshActiveEditorAnalysis();
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
    void updateProjectDiagnosticMarkers();
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
        V2Compiling, // Legacy fallback; new CGARM builds use cgarm-build.
        V2CliBuilding, // Independent CGARM V2 compiler, linker and packer.
        V2CliProbe, // Re-link same PIC objects against 512 KiB for RAM sizing.
        V2CliRelink, // Re-link and pack with the accepted new RAM allowance.
        V2CliAsm, // Generate disassembly after CLI has finished packing.
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
    QString m_v2CliPath; // Bundled standalone cgarm-build frontend.
    // Asynchronous two-stage V2 path: bundled GCC -c -> LLVM LLD -pie.
    // Legacy V1 and gaming still use the existing GCC link command.
    QString m_v2CompilerPath;
    QString m_v2LinkerPath;
    QString m_v2BuildDirectory;
    QStringList m_v2CompileFlags;
    QStringList m_v2CompileSources;
    QStringList m_v2CompiledObjects;
    QStringList m_v2LinkArguments;
    int m_v2CompileIndex = 0;
    QString m_projectPath;
    QString m_projectFilePath;
    QStringList m_projectFilesInProject;
    QHash<QString, QString> m_apiTips;
    QStringList m_apiSignatures;

    /*
     * Per-file semantic caches let normal typing refresh only the active tab.
     * A full project scan rebuilds these on project load/rescan/save.
     */
    QHash<QString, QStringList> m_cachedFileFunctionSignatures;
    QHash<QString, QStringList> m_cachedFileTypeNames;

    QString m_compilerStderrBuffer;
    bool m_buildLinkSizeOverflow = false;
    bool m_v2AutoResizeRetried = false;
    QHash<QString, QList<EditorDiagnostic>> m_compilerDiagnostics;
    QString m_linkerScriptPath;
    QString m_outputAppName;
    QString m_projectType;
    QString m_appletFormat = QStringLiteral("v1");
    bool m_currentBuildIsV2 = false;
    int m_modSizeKb;
    int m_appSizeKb;
    int m_v2HeapKb; // bounded allocation in experimental v2 only
    int m_v2StackKb; // private PSP for V2 window/timer callbacks (entry remains MSP)
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
