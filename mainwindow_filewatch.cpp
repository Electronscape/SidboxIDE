// Stage 3.70: extracted MainWindow implementation (mainwindow_filewatch.cpp).
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

