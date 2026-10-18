// Stage 3.70: extracted MainWindow implementation (mainwindow_output.cpp).
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

