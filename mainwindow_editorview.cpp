// Stage 3.70: extracted MainWindow implementation (mainwindow_editorview.cpp).
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

QList<CodeEditor *> MainWindow::editorsForTab(QWidget *tabWidget) const
{
    QList<CodeEditor *> editors;

    if (!tabWidget) {
        return editors;
    }

    if (auto *editor = qobject_cast<CodeEditor *>(tabWidget)) {
        editors.append(editor);
        return editors;
    }

    if (auto *splitter = qobject_cast<QSplitter *>(tabWidget)) {
        for (int i = 0; i < splitter->count(); ++i) {
            if (auto *editor =
                    qobject_cast<CodeEditor *>(splitter->widget(i))) {
                editors.append(editor);
            }
        }
    }

    return editors;
}

CodeEditor *MainWindow::primaryEditorForTab(QWidget *tabWidget) const
{
    const QList<CodeEditor *> editors = editorsForTab(tabWidget);
    return editors.isEmpty() ? nullptr : editors.first();
}

int MainWindow::tabIndexForEditor(CodeEditor *editor) const
{
    if (!editor || !m_editorTabs) {
        return -1;
    }

    for (int i = 0; i < m_editorTabs->count(); ++i) {
        const QList<CodeEditor *> editors =
            editorsForTab(m_editorTabs->widget(i));

        if (editors.contains(editor)) {
            return i;
        }
    }

    return -1;
}

CodeEditor *MainWindow::activeEditor() const
{
    if (!m_editorTabs) {
        return nullptr;
    }

    QWidget *tabWidget = m_editorTabs->currentWidget();
    const QList<CodeEditor *> editors = editorsForTab(tabWidget);

    if (editors.isEmpty()) {
        return nullptr;
    }

    /*
     * In a split tab the editor which currently owns keyboard focus is the
     * active side.  This keeps line/column, Ctrl+Click, search jumps and other
     * editor actions naturally attached to the pane the programmer is using.
     */
    for (CodeEditor *editor : editors) {
        if (editor->hasFocus()
            || (editor->viewport() && editor->viewport()->hasFocus())) {
            return editor;
        }
    }

    return editors.first();
}

int MainWindow::editorSplitTabIndex() const
{
    if (!m_editorTabs) {
        return -1;
    }

    for (int i = 0; i < m_editorTabs->count(); ++i) {
        auto *splitter =
            qobject_cast<QSplitter *>(m_editorTabs->widget(i));

        if (splitter
            && splitter->objectName()
                == QStringLiteral("editorSplitView")) {
            return i;
        }
    }

    return -1;
}

QSplitter *MainWindow::editorSplitWidget() const
{
    const int index = editorSplitTabIndex();
    if (index < 0) {
        return nullptr;
    }

    return qobject_cast<QSplitter *>(
        m_editorTabs->widget(index));
}

CodeEditor *MainWindow::splitHostEditor(
    QSplitter *splitter) const
{
    if (!splitter) {
        return nullptr;
    }

    const QList<CodeEditor *> editors =
        editorsForTab(splitter);

    for (CodeEditor *editor : editors) {
        if (editor->property(
                "sidboxSplitHostEditor").toBool()) {
            return editor;
        }
    }

    return editors.isEmpty()
        ? nullptr
        : editors.first();
}

CodeEditor *MainWindow::splitSecondaryEditor(
    QSplitter *splitter) const
{
    if (!splitter) {
        return nullptr;
    }

    const QList<CodeEditor *> editors =
        editorsForTab(splitter);
    CodeEditor *host =
        splitHostEditor(splitter);

    for (CodeEditor *editor : editors) {
        if (editor != host) {
            return editor;
        }
    }

    return nullptr;
}

void MainWindow::updateEditorSplitPresentation()
{
    const int index = editorSplitTabIndex();
    QSplitter *splitter = editorSplitWidget();

    if (index < 0 || !splitter) {
        return;
    }

    CodeEditor *host = splitHostEditor(splitter);
    CodeEditor *secondary =
        splitSecondaryEditor(splitter);

    if (!host) {
        return;
    }

    QString title = tabTitleForEditor(host);
    QString tooltip = host->filePath();

    if (secondary
        && secondary->document() != host->document()) {
        title += QStringLiteral("  |  ");
        title += tabTitleForEditor(secondary);

        tooltip =
            tr("Split view:\n%1\n%2")
                .arg(
                    QDir::toNativeSeparators(
                        host->filePath()),
                    QDir::toNativeSeparators(
                        secondary->filePath()));
    }

    m_editorTabs->setTabText(index, title);
    m_editorTabs->setTabIcon(
        index,
        editorTabIconForFile(host->filePath()));
    m_editorTabs->setTabToolTip(index, tooltip);
}

void MainWindow::openCurrentTabInExistingSplit()
{
    const int splitIndex = editorSplitTabIndex();
    QSplitter *splitter = editorSplitWidget();

    if (splitIndex < 0 || !splitter) {
        toggleCurrentEditorSplit();
        return;
    }

    const int sourceTabIndex =
        m_editorTabs->currentIndex();

    if (sourceTabIndex < 0
        || sourceTabIndex == splitIndex) {
        return;
    }

    CodeEditor *sourceEditor =
        primaryEditorForTab(
            m_editorTabs->widget(sourceTabIndex));

    CodeEditor *host =
        splitHostEditor(splitter);
    CodeEditor *secondary =
        splitSecondaryEditor(splitter);

    if (!sourceEditor || !host || !secondary) {
        return;
    }

    QMessageBox sideBox(this);
    sideBox.setWindowTitle(tr("Open in Split"));
    sideBox.setText(
        tr("Which side should show %1?")
            .arg(
                QFileInfo(sourceEditor->filePath())
                    .fileName()));
    sideBox.setInformativeText(
        tr("The other side will keep %1.")
            .arg(
                QFileInfo(host->filePath())
                    .fileName()));

    QPushButton *leftButton =
        sideBox.addButton(
            tr("Left"),
            QMessageBox::AcceptRole);

    QPushButton *rightButton =
        sideBox.addButton(
            tr("Right"),
            QMessageBox::AcceptRole);

    sideBox.addButton(QMessageBox::Cancel);

    if (sideBox.exec() == QMessageBox::Cancel
        || !sideBox.clickedButton()) {
        return;
    }

    const bool sourceOnLeft =
        sideBox.clickedButton()
        == static_cast<QAbstractButton *>(
            leftButton);

    Q_UNUSED(rightButton);

    secondary->setProperty(
        "sidboxApiReference",
        sourceEditor->property(
            "sidboxApiReference"));
    secondary->shareDocumentFrom(sourceEditor);
    secondary->setTextCursor(
        sourceEditor->textCursor());
    secondary->verticalScrollBar()->setValue(
        sourceEditor->verticalScrollBar()->value());
    secondary->horizontalScrollBar()->setValue(
        sourceEditor->horizontalScrollBar()->value());
    secondary->setDiagnostics(
        sourceEditor->diagnostics());

    /*
     * Keep the split host's own live document on the opposite side.
     * The selected tab's live document is borrowed by the reusable secondary
     * view, so there is still only one document/save state for each file.
     */
    if (sourceOnLeft) {
        splitter->insertWidget(0, secondary);
    } else {
        splitter->insertWidget(1, secondary);
    }

    const int available =
        qMax(
            240,
            splitter->width()
                - splitter->handleWidth());

    splitter->setSizes(
        {
            available / 2,
            available - (available / 2)
        });

    m_editorTabs->setCurrentIndex(splitIndex);
    updateEditorSplitPresentation();

    secondary->setFocus();
    updateCursorPositionStatus();

    statusBar()->showMessage(
        tr("%1 opened in the %2 split")
            .arg(
                QFileInfo(sourceEditor->filePath())
                    .fileName(),
                sourceOnLeft
                    ? tr("left")
                    : tr("right")),
        3000);
}

void MainWindow::toggleCurrentEditorSplit()
{
    if (!m_editorTabs
        || m_editorTabs->currentIndex() < 0) {
        return;
    }

    const int index =
        m_editorTabs->currentIndex();

    QWidget *tabWidget =
        m_editorTabs->widget(index);

    QList<CodeEditor *> editors =
        editorsForTab(tabWidget);

    if (editors.isEmpty()) {
        statusBar()->showMessage(
            tr("This tab cannot be split"),
            2500);
        return;
    }

    const int existingSplitIndex =
        editorSplitTabIndex();

    if (existingSplitIndex >= 0
        && existingSplitIndex != index) {
        openCurrentTabInExistingSplit();
        return;
    }

    const QString tabText =
        m_editorTabs->tabText(index);
    const QIcon tabIcon =
        m_editorTabs->tabIcon(index);
    const QString tabToolTip =
        m_editorTabs->tabToolTip(index);

    if (auto *splitter =
            qobject_cast<QSplitter *>(tabWidget)) {
        CodeEditor *primary =
            splitHostEditor(splitter);
        CodeEditor *secondary =
            splitSecondaryEditor(splitter);

        if (!primary) {
            return;
        }

        if (secondary
            && activeEditor() == secondary
            && secondary->document()
                == primary->document()) {
            primary->setTextCursor(
                secondary->textCursor());
            primary->verticalScrollBar()->setValue(
                secondary->verticalScrollBar()->value());
            primary->horizontalScrollBar()->setValue(
                secondary->horizontalScrollBar()->value());
        }

        m_editorTabs->removeTab(index);
        primary->setParent(m_editorTabs);
        primary->setProperty(
            "sidboxSplitHostEditor",
            false);

        if (secondary) {
            secondary->deleteLater();
        }

        splitter->deleteLater();

        m_editorTabs->insertTab(
            index,
            primary,
            editorTabIconForFile(
                primary->filePath()),
            tabTitleForEditor(primary));

        m_editorTabs->setTabToolTip(
            index,
            primary->filePath());

        m_editorTabs->setCurrentIndex(index);

        primary->setFocus();
        updateCursorPositionStatus();

        statusBar()->showMessage(
            tr("Editor split closed"),
            2000);
        return;
    }

    CodeEditor *primary = editors.first();
    if (!primary) {
        return;
    }

    auto *splitter =
        new QSplitter(
            Qt::Horizontal,
            m_editorTabs);

    splitter->setObjectName(
        QStringLiteral("editorSplitView"));
    splitter->setChildrenCollapsible(false);
    splitter->setHandleWidth(4);

    primary->setProperty(
        "sidboxSplitHostEditor",
        true);

    m_editorTabs->removeTab(index);
    splitter->addWidget(primary);

    CodeEditor *secondary =
        createEditor(primary->filePath());

    secondary->setProperty(
        "sidboxApiReference",
        primary->property(
            "sidboxApiReference"));

    secondary->setProperty(
        "sidboxSplitHostEditor",
        false);

    secondary->shareDocumentFrom(primary);
    secondary->setTextCursor(
        primary->textCursor());
    secondary->verticalScrollBar()->setValue(
        primary->verticalScrollBar()->value());
    secondary->horizontalScrollBar()->setValue(
        primary->horizontalScrollBar()->value());

    splitter->addWidget(secondary);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 1);

    m_editorTabs->insertTab(
        index,
        splitter,
        tabIcon,
        tabText);

    m_editorTabs->setTabToolTip(
        index,
        tabToolTip);

    m_editorTabs->setCurrentIndex(index);

    splitter->show();
    primary->show();
    secondary->show();

    QTimer::singleShot(
        0,
        splitter,
        [splitter, primary, secondary]() {
            const int available =
                qMax(
                    240,
                    splitter->width()
                        - splitter->handleWidth());

            const int left = available / 2;
            const int right = available - left;

            primary->setMinimumWidth(120);
            secondary->setMinimumWidth(120);
            splitter->setSizes({left, right});
        });

    updateEditorSplitPresentation();

    primary->setFocus();
    updateCursorPositionStatus();

    statusBar()->showMessage(
        tr("Split active — select another tab and choose Open in Existing Split"),
        4500);
}

void MainWindow::updateCursorPositionStatus()
{
    if (!m_cursorPositionLabel) {
        return;
    }

    CodeEditor *editor = activeEditor();
    if (!editor) {
        m_cursorPositionLabel->clear();
        return;
    }

    const QTextCursor cursor = editor->textCursor();
    m_cursorPositionLabel->setText(
        tr("[ Ln %1, Col %2 ]  ")
            .arg(cursor.blockNumber() + 1)
            .arg(cursor.positionInBlock() + 1));
}

