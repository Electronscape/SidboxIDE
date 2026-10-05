#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHash>
#include <QString>
#include <QStringList>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class CodeEditor;
class QLabel;
class QListWidget;
class QListWidgetItem;
class QPlainTextEdit;
class QToolBar;
class QProcess;
class QTabWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    void setupInterface();
    void createNewProject();
    void createNewSourceFile();
    void createNewHeaderFile();
    void openProject();
    bool saveProject();
    void showOptions();
    void showProjectSettings();
    void compileActiveFile();
    void openProjectFile(QListWidgetItem *item);
    void addExistingProjectFile();
    void createProjectFile();
    void removeSelectedProjectFile();
    void renameSelectedProjectFile();
    void handleCompilerFinished(int exitCode);

    CodeEditor *activeEditor() const;
    CodeEditor *createEditor(const QString &filePath = QString());
    bool openFile(const QString &filePath);
    bool saveEditor(CodeEditor *editor);
    bool saveModifiedWorkBeforeNewProject();
    bool loadProjectFile(const QString &filePath);
    bool saveProjectFile(const QString &filePath);
    void addProjectFile(const QString &filePath);
    void clearEditorTabs();
    void refreshProjectFiles();
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
    QStringList functionSignaturesFromText(const QString &text) const;
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
    void appendOutputText(const QString &text, OutputKind kind);
    void appendOutputLine(const QString &text, OutputKind kind);
    void loadOptions();
    void saveOptions() const;

    enum class BuildStep {
        None,
        Linking,
        Asm,
        Objcopy
    };

    Ui::MainWindow *ui;
    QListWidget *m_projectFiles;
    QTabWidget *m_editorTabs;
    QLabel *m_quickTipLabel;
    QPlainTextEdit *m_outputPane;
    QToolBar *m_outputToolBar;
    QProcess *m_compilerProcess;
    BuildStep m_buildStep;
    QString m_pendingElfPath;
    QString m_pendingAsmPath;
    QString m_pendingAppPath;
    QString m_projectPath;
    QString m_projectFilePath;
    QStringList m_projectFilesInProject;
    QHash<QString, QString> m_apiTips;
    QStringList m_apiSignatures;
    QString m_linkerScriptPath;
    QString m_projectType;
    int m_modSizeKb;
    int m_editorFontPointSize;
};
#endif // MAINWINDOW_H
