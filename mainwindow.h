#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QStringList>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class CodeEditor;
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
    void createNewSourceFile();
    void openProject();
    void saveProject();
    void showOptions();
    void compileActiveFile();
    void openProjectFile(QListWidgetItem *item);
    void handleCompilerFinished(int exitCode);

    CodeEditor *activeEditor() const;
    CodeEditor *createEditor(const QString &filePath = QString());
    bool openFile(const QString &filePath);
    bool saveEditor(CodeEditor *editor);
    bool loadProjectFile(const QString &filePath);
    bool saveProjectFile(const QString &filePath);
    void addProjectFile(const QString &filePath);
    void clearEditorTabs();
    void refreshProjectFiles();
    void refreshFunctionCompletions();
    void updateTabTitle(CodeEditor *editor);
    QString tabTitleForEditor(CodeEditor *editor) const;
    QString displayPath(const QString &filePath) const;
    QStringList collectOpenProjectFiles() const;
    QStringList projectFilesForCompile() const;
    QStringList projectFunctionSignatures() const;
    QStringList functionSignaturesFromText(const QString &text) const;
    QString toProjectRelativePath(const QString &filePath) const;
    QString fromProjectRelativePath(const QString &filePath) const;
    void loadOptions();
    void saveOptions() const;

    Ui::MainWindow *ui;
    QListWidget *m_projectFiles;
    QTabWidget *m_editorTabs;
    QPlainTextEdit *m_outputPane;
    QToolBar *m_outputToolBar;
    QProcess *m_compilerProcess;
    QString m_projectPath;
    QString m_projectFilePath;
    QStringList m_projectFilesInProject;
    QString m_linkerScriptPath;
    int m_modSizeKb;
};
#endif // MAINWINDOW_H
