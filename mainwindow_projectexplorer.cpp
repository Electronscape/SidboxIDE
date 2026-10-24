// Stage 3.70: extracted MainWindow implementation (mainwindow_projectexplorer.cpp).
#include <QScrollArea>
#include "mainwindow.h"

#include "codeeditor.h"
#include "guidesigner.h"
#include "gamedesigner.h"
#include "gamemainownership.h"
#include "optionsdialog.h"
#include "findreplacedialog.h"
#include "projectsettingsdialog.h"
#include "ui_mainwindow.h"

#include <algorithm>
#include <cmath>
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
#include <QHeaderView>
#include <QGroupBox>
#include <QSignalBlocker>
#include <QSizePolicy>
#include <QSize>
#include <QSpinBox>
#include <QToolButton>
#include <QAbstractButton>
#include <QAbstractItemView>
#include <QCoreApplication>
#include <QDir>
#include <QDirIterator>
#include <QDateTime>
#include <QDialog>
#include <QDialogButtonBox>
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
#include <QCryptographicHash>
#include <QLockFile>
#include <QUuid>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QKeySequence>
#include <QLabel>
#include <QListWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QTreeWidgetItemIterator>
#include <QLineEdit>
#include <QLayoutItem>
#include <QLocale>
#include <QMenu>
#include <QMessageBox>
#include <QMetaObject>
#include <QMouseEvent>
#include <QMimeData>
#include <QUrl>
#include <QPlainTextEdit>
#include <QPixmap>
#include <QGraphicsEffect>
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
#include <QTemporaryDir>
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
#include <QVector>
#include <QTextEdit>
#include <QStandardPaths>
#include <QStyle>
#include <functional>
#include <memory>
#include <limits>
#include <utility>
#include <zlib.h> // RFC 1952 gzip history snapshots


#include "mainwindow_uiicons.h"

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

    /*
     * A .sbui is not a CodeEditor tab. Moving it without updating the live
     * designer leaves m_filePath pointing at the old location; saving then
     * recreates the old design and triggers duplicate-window diagnostics.
     */
    for (int i = 0; i < m_editorTabs->count(); ++i) {
        QWidget *tab = m_editorTabs->widget(i);
        if (auto *game = dynamic_cast<SidboxGameDesigner *>(tab)) {
            if (QFileInfo(game->filePath()).absoluteFilePath() == sourcePath) {
                game->setFilePath(destinationPath);
                m_editorTabs->setTabToolTip(i, tr("V1 Game design\n%1").arg(QDir::toNativeSeparators(destinationPath)));
            }
            continue;
        }
        if (auto *designer = dynamic_cast<SidboxGuiDesigner *>(tab)) {
            if (QFileInfo(designer->filePath()).absoluteFilePath() == sourcePath) {
                designer->setFilePath(destinationPath);
                m_editorTabs->setTabToolTip(i,
                    tr("CoderGirl visual design\n%1")
                        .arg(QDir::toNativeSeparators(destinationPath)));
            }
            continue;
        }

        auto *editor = primaryEditorForTab(tab);
        if (editor
            && !editor->filePath().isEmpty()
            && QFileInfo(editor->filePath()).absoluteFilePath() == sourcePath) {
            unwatchEditorFile(editor);
            editor->setFilePath(destinationPath);
            watchEditorFile(editor);
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
        tr("Project files (*.c *.h *.inc *.cc *.cpp *.hpp *.res *.txt *.md *.sbui *.sbgm *.sbpi *.uis *.ppb *.pal *.act *.map *.png *.bmp *.jpg *.jpeg *.gif *.wav *.mod *.s3m *.xm *.med *.tfmx *.sid *.sba *.spc *.mp3);;"
           "Audio files (*.wav *.mod *.s3m *.xm *.med *.tfmx *.sid *.sba *.spc *.mp3);;"
           "Source files (*.c *.h *.inc *.cc *.cpp *.hpp *.res *.txt *.md);;All files (*)"));

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
        if (auto *game = dynamic_cast<SidboxGameDesigner *>(widget)) {
            if (QFileInfo(game->filePath()).absoluteFilePath() == QFileInfo(filePath).absoluteFilePath()) {
                m_editorTabs->removeTab(i); widget->deleteLater(); continue;
            }
        }
        if (auto *designer = dynamic_cast<SidboxGuiDesigner *>(widget)) {
            if (QFileInfo(designer->filePath()).absoluteFilePath() == QFileInfo(filePath).absoluteFilePath()) {
                m_editorTabs->removeTab(i);
                widget->deleteLater();
                continue;
            }
        }
        auto *editor = primaryEditorForTab(widget);
        if (editor && !editor->filePath().isEmpty()
            && QFileInfo(editor->filePath()).absoluteFilePath() == QFileInfo(filePath).absoluteFilePath()) {
            unwatchEditorFile(editor);
            m_editorTabs->removeTab(i);
            widget->deleteLater();
        }
    }

    // Remove can be triggered from a QMenu::exec() on the project tree.
    // Rebuilding that tree synchronously destroys the selected item while
    // QMenu/Qt may still be dispatching the originating QAction event.
    // Finish project-bookkeeping first, then rebuild after the menu unwinds.
    if (!m_projectFilePath.isEmpty()) {
        saveProjectFile(m_projectFilePath);
    }
    QTimer::singleShot(0, this, [this]() {
        refreshProjectFiles();
    });
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
        QMessageBox::warning(this, tr("Rename File"), tr("Use one of these extensions: .c, .h, .inc, .res, .txt, .md, .sbui, .sbgm, .uis"));
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
        if (auto *game = dynamic_cast<SidboxGameDesigner *>(tab)) {
            if (QFileInfo(game->filePath()).absoluteFilePath() == oldInfo.absoluteFilePath()) {
                game->setFilePath(newPath);
                m_editorTabs->setTabToolTip(i, tr("V1 Game design\n%1").arg(QDir::toNativeSeparators(newPath)));
            }
            continue;
        }
        if (auto *designer = dynamic_cast<SidboxGuiDesigner *>(tab)) {
            if (QFileInfo(designer->filePath()).absoluteFilePath() == oldInfo.absoluteFilePath()) {
                designer->setFilePath(newPath);
                m_editorTabs->setTabToolTip(i,
                    tr("CoderGirl visual design\n%1")
                        .arg(QDir::toNativeSeparators(newPath)));
                continue;
            }
        }
        auto *editor = primaryEditorForTab(tab);
        if (editor && !editor->filePath().isEmpty()
            && QFileInfo(editor->filePath()).absoluteFilePath() == oldInfo.absoluteFilePath()) {
            unwatchEditorFile(editor);
            editor->setFilePath(newPath);
            watchEditorFile(editor);
            updateTabTitle(editor);
        }
    }

    refreshProjectFiles();
    if (!m_projectFilePath.isEmpty()) {
        saveProjectFile(m_projectFilePath);
    }
    statusBar()->showMessage(tr("File renamed: %1").arg(displayPath(newPath)));
}

