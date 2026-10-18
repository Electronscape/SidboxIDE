// Stage 3.70: extracted MainWindow implementation (mainwindow_preferences.cpp).
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

void MainWindow::applyEditorFont()
{
    QFont font = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    font.setPointSize(m_editorFontPointSize);

    for (int i = 0; i < m_editorTabs->count(); ++i) {
        const QList<CodeEditor *> editors =
            editorsForTab(m_editorTabs->widget(i));

        for (CodeEditor *editor : editors) {
            editor->setFont(font);
            editor->setTabStopDistance(
                editor->fontMetrics().horizontalAdvance(QLatin1Char(' ')) * 4);
            editor->setCompletionFont(font);
            editor->refreshLineNumberAreaWidth();
        }
    }
}

void MainWindow::loadOptions()
{
    QSettings settings(QStringLiteral("Sidbox"), QStringLiteral("SidboxIDE"));

    m_editorFontPointSize =
        qBound(6,
               settings.value(QStringLiteral("editor/fontPointSize"), 10).toInt(),
               36);

    m_theme = defaultIDETheme();

    for (const IDEThemeColorField &field : ideThemeColorFields()) {
        const QString key =
            QStringLiteral("theme/") + QLatin1String(field.key);

        if (!settings.contains(key)) {
            continue;
        }

        const QColor colour(settings.value(key).toString());
        if (colour.isValid()) {
            m_theme.*(field.member) = colour;
        }
    }
}

void MainWindow::saveOptions() const
{
    QSettings settings(QStringLiteral("Sidbox"), QStringLiteral("SidboxIDE"));
    settings.setValue(
        QStringLiteral("editor/fontPointSize"),
        m_editorFontPointSize);

    for (const IDEThemeColorField &field : ideThemeColorFields()) {
        settings.setValue(
            QStringLiteral("theme/") + QLatin1String(field.key),
            ideThemeColorName(m_theme.*(field.member)));
    }
}

