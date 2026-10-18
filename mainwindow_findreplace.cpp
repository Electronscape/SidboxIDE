// Stage 3.70: extracted MainWindow implementation (mainwindow_findreplace.cpp).
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

