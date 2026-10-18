// Stage 3.70: extracted MainWindow implementation (mainwindow_paths.cpp).
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

