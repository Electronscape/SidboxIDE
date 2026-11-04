#include "sidboxvideoconverter.h"

#include <QAbstractItemView>
#include <QCheckBox>
#include <QCollator>
#include <QCloseEvent>
#include <QComboBox>
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFileSystemModel>
#include <QSet>
#include <QHeaderView>
#include <QMouseEvent>
#include <QTimer>
#include <array>
#include <algorithm>
#include <QFileIconProvider>
#include <QFont>
#include <QFileDevice>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QItemSelectionModel>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QProcess>
#include <QProgressBar>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QRegularExpression>
#include <QStandardItemModel>
#include <QTemporaryFile>
#include <QUrl>
#include <QPushButton>
#include <QSettings>
#include <QSortFilterProxyModel>
#include <QSize>
#include <QStringList>
#include <QSplitter>
#include <QStandardPaths>
#include <QToolBar>
#include <QToolButton>
#include <QTreeView>
#include <QUuid>
#include <QVBoxLayout>

// Apply the same natural, case-insensitive, folders-first ordering to local
// QFileSystemModel entries and SMB QStandardItemModel entries.
class SidboxDirectorySortModel final : public QSortFilterProxyModel
{
public:
    explicit SidboxDirectorySortModel(QObject *parent = nullptr)
        : QSortFilterProxyModel(parent)
    {
        m_collator.setCaseSensitivity(Qt::CaseInsensitive);
        m_collator.setNumericMode(true);
        setDynamicSortFilter(true);
    }

protected:
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override
    {
        const QModelIndex leftName = left.siblingAtColumn(0);
        const QModelIndex rightName = right.siblingAtColumn(0);
        const auto *localModel = qobject_cast<const QFileSystemModel *>(sourceModel());
        const bool leftDir = localModel ? localModel->isDir(leftName) :
                             leftName.data(Qt::UserRole + 1).toBool();
        const bool rightDir = localModel ? localModel->isDir(rightName) :
                              rightName.data(Qt::UserRole + 1).toBool();
        if (leftDir != rightDir) return leftDir;
        if (left.column() != 0) return QSortFilterProxyModel::lessThan(left, right);
        const QString first = leftName.data(Qt::DisplayRole).toString();
        const QString second = rightName.data(Qt::DisplayRole).toString();
        const int difference = m_collator.compare(first, second);
        return difference < 0 || (difference == 0 && first < second);
    }

private:
    QCollator m_collator;
};

// Keep each pane's user-sized columns independent of model resets and folder
// changes. QHeaderView can reset its section sizes when QFileSystemModel
// finishes loading a directory, or when the Source pane switches to SMB.
class SidboxPersistentColumnsHeader final : public QHeaderView
{
public:
    explicit SidboxPersistentColumnsHeader(QWidget *parent)
        : QHeaderView(Qt::Horizontal, parent)
    {
        setSectionResizeMode(QHeaderView::Interactive);
        setStretchLastSection(false);
        connect(this, &QHeaderView::sectionResized, this, [this](int, int, int) {
            if (m_restoring || m_userPressed) return;
            // Automatic width changes from model updates must not replace
            // the sizes that the user selected by dragging the header.
            QTimer::singleShot(0, this, [this]() { applyRemembered(); });
        });
    }

    void restoreSavedState(const QByteArray &saved)
    {
        if (!saved.isEmpty() && restoreState(saved)) {
            rememberCurrent();
        } else {
            applyRemembered();
        }
    }

    void applyRemembered()
    {
        if (m_restoring || m_userPressed) return;
        m_restoring = true;
        const int sections = qMin(count(), 4);
        for (int column = 0; column < sections; ++column) {
            if (sectionSize(column) != m_widths[static_cast<std::size_t>(column)])
                resizeSection(column, m_widths[static_cast<std::size_t>(column)]);
        }
        m_restoring = false;
    }

protected:
    void mousePressEvent(QMouseEvent *event) override
    {
        m_userPressed = true;
        QHeaderView::mousePressEvent(event);
    }

    void mouseReleaseEvent(QMouseEvent *event) override
    {
        QHeaderView::mouseReleaseEvent(event);
        if (m_userPressed) rememberCurrent();
        m_userPressed = false;
    }

    void mouseDoubleClickEvent(QMouseEvent *event) override
    {
        QHeaderView::mouseDoubleClickEvent(event);
        // Qt can autosize a section on double-click; preserve that choice.
        QTimer::singleShot(0, this, [this]() { rememberCurrent(); });
    }

private:
    void rememberCurrent()
    {
        const int sections = qMin(count(), 4);
        for (int column = 0; column < sections; ++column) {
            const int width = sectionSize(column);
            if (width > 0) m_widths[static_cast<std::size_t>(column)] = width;
        }
    }

    std::array<int, 4> m_widths{{320, 105, 95, 165}};
    bool m_restoring = false;
    bool m_userPressed = false;
};

SidboxVideoConverterDialog::SidboxVideoConverterDialog(QWidget *parent)
    : QDialog(parent, Qt::Window)
{
    setObjectName(QStringLiteral("sidboxVideoConverter"));
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle(tr("SIDBOX Video Converter"));
    setMinimumSize(860, 520);
    resize(1120, 700);

    QSettings settings(QStringLiteral("Sidbox"), QStringLiteral("SidboxIDE"));
    settings.beginGroup(QStringLiteral("tools/videoConverter"));

    auto *root = new QVBoxLayout(this);
    root->setContentsMargins(10, 10, 10, 10);
    root->setSpacing(8);
    auto *bar = new QToolBar(tr("SIDBOX AVI Settings"), this);
    bar->setMovable(false);
    bar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    auto addSetting = [bar](const QString &name, QComboBox *combo) {
        auto *label = new QLabel(name, bar);
        bar->addWidget(label);
        bar->addWidget(combo);
        bar->addSeparator();
    };
    m_resolution = new QComboBox(bar);
    m_resolution->addItem(QStringLiteral("480 × 320"), QSize(480, 320));
    m_resolution->addItem(QStringLiteral("320 × 240"), QSize(320, 240));
    m_resolution->addItem(QStringLiteral("240 × 160"), QSize(240, 160));
    addSetting(tr("Size  "), m_resolution);
    m_fps = new QComboBox(bar);
    for (int fps : {10, 12, 15, 20, 25})
        m_fps->addItem(QStringLiteral("%1 fps").arg(fps), fps);
    addSetting(tr("FPS  "), m_fps);
    m_quality = new QComboBox(bar);
    for (int q : {3, 4, 5, 6, 7, 8, 10, 12})
        m_quality->addItem(QString::number(q), q);
    m_quality->setToolTip(tr("MJPEG quality: lower values produce larger, higher-quality files."));
    addSetting(tr("JPEG Q  "), m_quality);
    m_bitrate = new QComboBox(bar);
    for (int rate : {64, 96, 128})
        m_bitrate->addItem(QStringLiteral("%1k").arg(rate), rate);
    addSetting(tr("MP3  "), m_bitrate);
    m_audioOutput = new QComboBox(bar);
    m_audioOutput->addItem(tr("Off"), 0);
    m_audioOutput->addItem(tr("Mono 44.1 kHz"), 1);
    m_audioOutput->addItem(tr("Stereo 44.1 kHz"), 2);
    m_audioOutput->setToolTip(tr("Audio output: silent AVI, mono MP3 (SIDBOX default), or stereo MP3. "
                                 "The output sample rate is 44.1 kHz."));
    addSetting(tr("Audio  "), m_audioOutput);
    m_audioGain = new QCheckBox(tr("Auto gain"), bar);
    m_audioGain->setToolTip(tr("Automatically normalise audio towards -16 LUFS with a -1.5 dB true-peak limit. "
                                "Applies to single and batch conversions; requires audio enabled."));
    bar->addWidget(m_audioGain);
    connect(m_audioOutput, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int) {
        const bool enabled = m_audioOutput->currentData().toInt() > 0;
        m_audioGain->setEnabled(enabled);
        m_bitrate->setEnabled(enabled);
    });
    bar->addSeparator();
    m_parallel = new QComboBox(bar);
    for (int jobs : {1, 2, 3, 4})
        m_parallel->addItem(tr("%1 concurrent").arg(jobs), jobs);
    m_parallel->setToolTip(tr("Maximum simultaneous FFmpeg conversions (SMB inputs are downloaded first)."));
    addSetting(tr("Batch  "), m_parallel);
    root->addWidget(bar);

    auto restoreCombo = [&settings](QComboBox *combo, const QString &key, int defaultValue) {
        int index = combo->findData(settings.value(key, defaultValue).toInt());
        combo->setCurrentIndex(index < 0 ? 0 : index);
    };
    restoreCombo(m_fps, QStringLiteral("fps"), 15);
    restoreCombo(m_quality, QStringLiteral("quality"), 6);
    restoreCombo(m_bitrate, QStringLiteral("bitrate"), 96);
    restoreCombo(m_parallel, QStringLiteral("parallel"), 2);
    m_resolution->setCurrentIndex(qMax(0, m_resolution->findData(settings.value(
        QStringLiteral("resolution"), QSize(480, 320)).toSize())));
    // Migrate the old mono-audio checkbox: checked -> mono; unchecked -> off.
    const int savedAudioChannels = settings.value(QStringLiteral("audioChannels"),
        settings.value(QStringLiteral("audio"), true).toBool() ? 1 : 0).toInt();
    m_audioOutput->setCurrentIndex(qMax(0, m_audioOutput->findData(savedAudioChannels)));
    m_audioGain->setChecked(settings.value(QStringLiteral("audioGain"), false).toBool());
    const bool audioEnabled = m_audioOutput->currentData().toInt() > 0;
    m_audioGain->setEnabled(audioEnabled);
    m_bitrate->setEnabled(audioEnabled);

    auto *pane = new QWidget(this);
    auto *paneLayout = new QHBoxLayout(pane);
    paneLayout->setContentsMargins(0, 0, 0, 0);
    paneLayout->setSpacing(8);
    m_splitter = new QSplitter(Qt::Horizontal, pane);

    auto *left = new QWidget(m_splitter);
    auto *leftLayout = new QVBoxLayout(left);
    leftLayout->setContentsMargins(0, 0, 0, 0);
    auto *sourceTitle = new QLabel(tr("SOURCE  ·  Ctrl/Shift-click to select videos"), left);
    leftLayout->addWidget(sourceTitle);
    auto *sourceNavigation = new QHBoxLayout;
    auto *sourceUp = new QToolButton(left);
    sourceUp->setText(QStringLiteral("↑"));
    sourceUp->setToolTip(tr("Parent directory"));
    auto *sourceRefresh = new QToolButton(left);
    sourceRefresh->setText(QStringLiteral("↻"));
    sourceRefresh->setToolTip(tr("Refresh source directory"));
    auto *sourceHome = new QToolButton(left);
    sourceHome->setText(QStringLiteral("⌂"));
    sourceHome->setToolTip(tr("Home directory"));
    m_sourcePath = new QLineEdit(left);
    m_sourcePath->setPlaceholderText(tr("Local folder or smb://user@server/Share/Folder/"));
    sourceNavigation->addWidget(sourceUp);
    sourceNavigation->addWidget(sourceHome);
    sourceNavigation->addWidget(sourceRefresh);
    sourceNavigation->addWidget(m_sourcePath, 1);
    leftLayout->addLayout(sourceNavigation);
    m_sourceModel = new QFileSystemModel(this);
    m_sourceModel->setFilter(QDir::AllEntries | QDir::AllDirs | QDir::NoDotAndDotDot);
    m_sourceModel->setNameFilters({QStringLiteral("*.avi"), QStringLiteral("*.mp4"),
        QStringLiteral("*.mkv"), QStringLiteral("*.mov"), QStringLiteral("*.webm"),
        QStringLiteral("*.m4v"), QStringLiteral("*.mpeg"), QStringLiteral("*.mpg"),
        QStringLiteral("*.wmv"), QStringLiteral("*.ts"), QStringLiteral("*.m2ts")});
    // Keep directories and non-video files visible. Unmatched files are greyed
    // out, rather than hiding the folder tree from the Source pane.
    m_sourceModel->setNameFilterDisables(true);
    m_sourceModel->setRootPath(QDir::rootPath());
    m_remoteModel = new QStandardItemModel(this);
    m_remoteModel->setHorizontalHeaderLabels({tr("Name"), tr("Size"), tr("Type"), tr("Date Modified")});
    m_sourceSort = new SidboxDirectorySortModel(this);
    m_sourceSort->setSourceModel(m_sourceModel);
    m_sourceView = new QTreeView(left);
    m_sourceView->setHeader(new SidboxPersistentColumnsHeader(m_sourceView));
    m_sourceView->setModel(m_sourceSort);
    m_sourceView->setRootIsDecorated(false);
    m_sourceView->setItemsExpandable(false);
    m_sourceView->setSortingEnabled(true);
    m_sourceView->sortByColumn(0, Qt::AscendingOrder);
    m_sourceView->header()->setSectionResizeMode(QHeaderView::Interactive);
    m_sourceView->header()->setStretchLastSection(false);
    m_sourceView->setColumnWidth(0, 320);
    m_sourceView->setColumnWidth(1, 105);
    m_sourceView->setColumnWidth(2, 95);
    m_sourceView->setColumnWidth(3, 165);
    m_sourceView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_sourceView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    m_sourceView->setAlternatingRowColors(true);
    // Network listings replace the proxy's source model; local directories
    // can also finish loading after navigation has returned.
    connect(m_sourceSort, &QAbstractItemModel::modelReset, m_sourceView,
            [this]() {
        auto *header = static_cast<SidboxPersistentColumnsHeader *>(m_sourceView->header());
        QTimer::singleShot(0, header, [header]() { header->applyRemembered(); });
    });
    connect(m_sourceModel, &QFileSystemModel::directoryLoaded, m_sourceView,
            [this](const QString &) {
        auto *header = static_cast<SidboxPersistentColumnsHeader *>(m_sourceView->header());
        QTimer::singleShot(0, header, [header]() { header->applyRemembered(); });
    });
    leftLayout->addWidget(m_sourceView, 1);

    auto *right = new QWidget(m_splitter);
    auto *rightLayout = new QVBoxLayout(right);
    rightLayout->setContentsMargins(0, 0, 0, 0);
    rightLayout->addWidget(new QLabel(tr("TARGET  ·  choose output folder"), right));
    auto *targetNavigation = new QHBoxLayout;
    auto *targetUp = new QToolButton(right);
    targetUp->setText(QStringLiteral("↑"));
    targetUp->setToolTip(tr("Parent directory"));
    auto *targetHome = new QToolButton(right);
    targetHome->setText(QStringLiteral("⌂"));
    targetHome->setToolTip(tr("Home directory"));
    m_targetPath = new QLineEdit(right);
    m_targetPath->setPlaceholderText(tr("Output folder"));
    targetNavigation->addWidget(targetUp);
    targetNavigation->addWidget(targetHome);
    targetNavigation->addWidget(m_targetPath, 1);
    rightLayout->addLayout(targetNavigation);
    m_targetModel = new QFileSystemModel(this);
    m_targetModel->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    m_targetModel->setRootPath(QDir::rootPath());
    m_targetSort = new SidboxDirectorySortModel(this);
    m_targetSort->setSourceModel(m_targetModel);
    m_targetView = new QTreeView(right);
    m_targetView->setHeader(new SidboxPersistentColumnsHeader(m_targetView));
    m_targetView->setModel(m_targetSort);
    m_targetView->setRootIsDecorated(false);
    m_targetView->setItemsExpandable(false);
    m_targetView->setSortingEnabled(true);
    m_targetView->sortByColumn(0, Qt::AscendingOrder);
    m_targetView->header()->setSectionResizeMode(QHeaderView::Interactive);
    m_targetView->header()->setStretchLastSection(false);
    m_targetView->setColumnWidth(0, 320);
    m_targetView->setColumnWidth(1, 105);
    m_targetView->setColumnWidth(2, 95);
    m_targetView->setColumnWidth(3, 165);
    m_targetView->setSelectionMode(QAbstractItemView::SingleSelection);
    m_targetView->setAlternatingRowColors(true);
    connect(m_targetSort, &QAbstractItemModel::modelReset, m_targetView,
            [this]() {
        auto *header = static_cast<SidboxPersistentColumnsHeader *>(m_targetView->header());
        QTimer::singleShot(0, header, [header]() { header->applyRemembered(); });
    });
    connect(m_targetModel, &QFileSystemModel::directoryLoaded, m_targetView,
            [this](const QString &) {
        auto *header = static_cast<SidboxPersistentColumnsHeader *>(m_targetView->header());
        QTimer::singleShot(0, header, [header]() { header->applyRemembered(); });
    });
    rightLayout->addWidget(m_targetView, 1);

    m_splitter->addWidget(left);
    m_splitter->addWidget(right);
    m_splitter->setChildrenCollapsible(false);
    m_splitter->setSizes({460, 460});

    auto *middle = new QVBoxLayout;
    middle->addStretch(1);
    m_convert = new QPushButton(QStringLiteral("➜\n") + tr("Convert"), pane);
    m_convert->setMinimumSize(96, 88);
    m_convert->setToolTip(tr("Convert the selected source to an MJPEG + MP3 AVI in the target folder"));
    middle->addWidget(m_convert);
    m_batchConvert = new QPushButton(tr("Batch\nConvert"), pane);
    m_batchConvert->setMinimumSize(96, 66);
    m_batchConvert->setToolTip(tr("Batch highlighted videos (Ctrl/Shift-click); or select one folder / no files to convert the whole folder. Names end in _sb.avi."));
    middle->addWidget(m_batchConvert);
    middle->addStretch(1);
    // The centre arrow is independent of either explorer pane.
    paneLayout->addWidget(m_splitter, 1);
    // Insert centre button between the two file browsers by moving it into
    // the splitter as a non-collapsible narrow widget.
    auto *centre = new QWidget(m_splitter);
    centre->setLayout(middle);
    centre->setMinimumWidth(100);
    centre->setMaximumWidth(112);
    m_splitter->insertWidget(1, centre);
    root->addWidget(pane, 1);

    m_selectedLabel = new QLabel(tr("Choose a video on the left, then press Convert →"), this);
    root->addWidget(m_selectedLabel);
    auto *progressRow = new QHBoxLayout;
    m_progress = new QProgressBar(this);
    m_progress->setRange(0, 100);
    m_progress->setValue(0);
    m_status = new QLabel(tr("Ready"), this);
    m_status->setMinimumWidth(240);
    m_cancel = new QPushButton(tr("Cancel"), this);
    m_cancel->setEnabled(false);
    progressRow->addWidget(m_progress, 1);
    progressRow->addWidget(m_status);
    progressRow->addWidget(m_cancel);
    root->addLayout(progressRow);

    // Keep the explorers large for single-file work. The queue expands only
    // when Batch Folder is used, then remains visible to review results.
    m_batchPanel = new QWidget(this);
    auto *batchLayout = new QVBoxLayout(m_batchPanel);
    batchLayout->setContentsMargins(0, 0, 0, 0);
    batchLayout->setSpacing(4);
    auto *batchHeading = new QHBoxLayout;
    auto *batchTitle = new QLabel(tr("Batch queue"), m_batchPanel);
    QFont batchTitleFont = batchTitle->font();
    batchTitleFont.setBold(true);
    batchTitle->setFont(batchTitleFont);
    batchHeading->addWidget(batchTitle);
    m_batchSummary = new QLabel(m_batchPanel);
    m_batchSummary->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    batchHeading->addWidget(m_batchSummary, 1);
    batchLayout->addLayout(batchHeading);
    m_batchTable = new QTableWidget(0, 4, m_batchPanel);
    m_batchTable->setHorizontalHeaderLabels({tr("Video"), tr("State"),
                                             tr("Progress"), tr("Speed")});
    m_batchTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_batchTable->setSelectionMode(QAbstractItemView::NoSelection);
    m_batchTable->setAlternatingRowColors(true);
    m_batchTable->setShowGrid(false);
    m_batchTable->verticalHeader()->hide();
    m_batchTable->verticalHeader()->setDefaultSectionSize(24);
    m_batchTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    m_batchTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
    m_batchTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
    m_batchTable->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);
    m_batchTable->setColumnWidth(1, 130);
    m_batchTable->setColumnWidth(2, 180);
    m_batchTable->setColumnWidth(3, 78);
    m_batchTable->setMinimumHeight(130);
    m_batchTable->setMaximumHeight(205);
    batchLayout->addWidget(m_batchTable);
    root->addWidget(m_batchPanel);
    m_batchPanel->hide();
    m_batchFeedbackTimer = new QTimer(this);
    m_batchFeedbackTimer->setInterval(500);
    connect(m_batchFeedbackTimer, &QTimer::timeout, this, [this]() {
        if (!m_batchBusy) return;
        // Read the size of an in-progress SMB copy, without blocking the UI.
        for (BatchTask *task : m_batchTasks) {
            if (!task->finished && task->downloading && task->sourceBytes > 0) {
                const qint64 bytes = QFileInfo(task->tempInput).size();
                if (bytes >= 0) {
                    const int percent = qBound(0, int((double(bytes) / double(task->sourceBytes)) * 100.0), 99);
                    task->overallPercent = percent / 5; // Download is first 20% of a remote job.
                    if (task->progressBar) {
                        task->progressBar->setRange(0, 100);
                        task->progressBar->setValue(percent);
                        task->progressBar->setFormat(tr("%p% copied"));
                    }
                }
            }
        }
        updateBatchFeedback();
    });

    m_log = new QPlainTextEdit(this);
    m_log->setReadOnly(true);
    m_log->setMaximumBlockCount(250);
    m_log->setPlaceholderText(tr("FFmpeg conversion messages will appear here."));
    m_log->setMaximumHeight(110);
    root->addWidget(m_log);

    m_ffmpeg = new QProcess(this);
    m_ffmpeg->setProcessChannelMode(QProcess::SeparateChannels);

    connect(sourceUp, &QToolButton::clicked, this, [this]() {
        if (m_sourceDirectory.startsWith(QStringLiteral("smb://"), Qt::CaseInsensitive)) {
            QUrl url(m_sourceDirectory);
            QStringList segments = url.path().split(QLatin1Char('/'), Qt::SkipEmptyParts);
            // Never navigate above the share root; Home returns to local files.
            if (segments.size() > 1) {
                segments.removeLast();
                url.setPath(QStringLiteral("/") + segments.join(QLatin1Char('/')) + QLatin1Char('/'));
                navigateSource(url.toString(QUrl::FullyEncoded));
            }
        } else {
            QDir parent(m_sourceDirectory);
            if (parent.cdUp()) navigateSource(parent.absolutePath());
        }
    });
    connect(sourceHome, &QToolButton::clicked, this, [this]() {
        navigateSource(QDir::homePath());
    });
    connect(sourceRefresh, &QToolButton::clicked, this, [this]() {
        if (m_sourceDirectory.startsWith(QStringLiteral("smb://"), Qt::CaseInsensitive)) {
            navigateSource(m_sourceDirectory);
        } else {
            const QString location = m_sourceDirectory;
            m_sourceModel->setRootPath(QDir::rootPath());
            navigateSource(location);
        }
    });
    connect(m_sourcePath, &QLineEdit::returnPressed, this, [this]() {
        navigateSource(m_sourcePath->text());
    });
    connect(m_sourceView, &QTreeView::doubleClicked, this, [this](const QModelIndex &index) {
        if (m_sourceSort->sourceModel() == m_remoteModel) {
            if (!index.siblingAtColumn(0).data(Qt::UserRole + 1).toBool()) return;
            const QString name = index.siblingAtColumn(0).data(Qt::DisplayRole).toString();
            QUrl url(m_sourceDirectory);
            QString path = url.path();
            if (!path.endsWith(QLatin1Char('/'))) path += QLatin1Char('/');
            url.setPath(path + name + QLatin1Char('/'));
            navigateSource(url.toString(QUrl::FullyEncoded));
        } else {
            const QString path = m_sourceModel->filePath(m_sourceSort->mapToSource(index));
            if (QFileInfo(path).isDir()) navigateSource(path);
        }
    });
    connect(m_sourceView->selectionModel(), &QItemSelectionModel::currentChanged,
            this, [this](const QModelIndex &index) {
        selectSource(index);
        const int count = m_sourceView->selectionModel()->selectedRows(0).size();
        if (count > 1) m_selectedLabel->setText(tr("%1 items selected. Batch converts selected videos.").arg(count));
    });
    connect(m_sourceView->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, [this](const QItemSelection &, const QItemSelection &) {
        const QModelIndexList selected = m_sourceView->selectionModel()->selectedRows(0);
        if (selected.size() > 1) {
            m_selectedLabel->setText(tr("%1 items selected. Batch converts selected videos.").arg(selected.size()));
        } else if (selected.size() == 1) {
            selectSource(selected.first());
        } else {
            m_selectedSource.clear();
            m_selectedLabel->setText(tr("No files selected. Batch converts the current folder."));
        }
    });
    connect(targetUp, &QToolButton::clicked, this, [this]() {
        QDir parent(m_targetDirectory);
        if (parent.cdUp()) navigateTarget(parent.absolutePath());
    });
    connect(targetHome, &QToolButton::clicked, this, [this]() { navigateTarget(QDir::homePath()); });
    connect(m_targetPath, &QLineEdit::returnPressed, this,
            [this]() { navigateTarget(m_targetPath->text()); });
    connect(m_targetView, &QTreeView::doubleClicked, this, [this](const QModelIndex &index) {
        const QString path = m_targetModel->filePath(m_targetSort->mapToSource(index));
        if (QFileInfo(path).isDir()) navigateTarget(path);
    });
    connect(m_targetView->selectionModel(), &QItemSelectionModel::currentChanged,
            this, [this](const QModelIndex &index) {
        const QString path = m_targetModel->filePath(m_targetSort->mapToSource(index));
        if (QFileInfo(path).isDir()) {
            m_targetDirectory = path;
            m_targetPath->setText(QDir::toNativeSeparators(path));
        }
    });
    connect(m_convert, &QPushButton::clicked, this, [this]() {
        // A selected target directory takes precedence over the current pane root.
        const QModelIndex index = m_targetView->currentIndex();
        if (index.isValid()) {
            const QString target = m_targetModel->filePath(m_targetSort->mapToSource(index));
            if (QFileInfo(target).isDir()) m_targetDirectory = target;
        }
        convertSelected();
    });
    connect(m_batchConvert, &QPushButton::clicked, this, [this]() {
        // Convert highlighted videos, or a selected/current folder if no
        // video files are highlighted. Both local and SMB files are supported.
        convertBatchFolder();
    });
    connect(m_cancel, &QPushButton::clicked, this, [this]() {
        if (m_batchBusy || m_batchPreparing) {
            cancelBatch();
            return;
        }
        if (m_smbDownload && m_smbDownload->state() != QProcess::NotRunning) {
            m_remoteCancelled = true;
            m_status->setText(tr("Cancelling network transfer..."));
            m_smbDownload->kill();
        } else if (m_ffmpeg->state() != QProcess::NotRunning) {
            m_status->setText(tr("Cancelling..."));
            m_ffmpeg->kill();
        }
    });
    connect(m_ffmpeg, &QProcess::readyReadStandardOutput, this, [this]() {
        m_progressText += m_ffmpeg->readAllStandardOutput();
        int lineEnd = 0;
        while ((lineEnd = m_progressText.indexOf('\n')) >= 0) {
            const QByteArray line = m_progressText.left(lineEnd).trimmed();
            m_progressText.remove(0, lineEnd + 1);
            if (line.startsWith("out_time=")) {
                const QStringList parts = QString::fromLatin1(line.mid(9)).split(QLatin1Char(':'));
                if (parts.size() == 3) {
                    bool ok = false;
                    const double sec = parts[0].toDouble() * 3600.0 + parts[1].toDouble() * 60.0
                                     + parts[2].toDouble(&ok);
                    if (ok && m_durationSeconds > 0.0) {
                        m_progress->setRange(0, 100);
                        m_progress->setValue(qBound(0, int(sec * 100.0 / m_durationSeconds), 100));
                    }
                    if (ok) m_status->setText(tr("Encoded %1 s").arg(sec, 0, 'f', 1));
                }
            } else if (line == "progress=end") {
                m_progress->setRange(0, 100);
                m_progress->setValue(100);
            }
        }
    });
    connect(m_ffmpeg, &QProcess::readyReadStandardError, this, [this]() {
        m_log->appendPlainText(QString::fromLocal8Bit(m_ffmpeg->readAllStandardError()));
    });
    connect(m_ffmpeg, &QProcess::errorOccurred, this, [this](QProcess::ProcessError error) {
        if (error == QProcess::FailedToStart) {
            m_log->appendPlainText(tr("FFmpeg could not start."));
            m_status->setText(tr("FFmpeg unavailable"));
            m_convert->setEnabled(true);
            m_cancel->setEnabled(false);
            if (!m_tempOutput.isEmpty()) QFile::remove(m_tempOutput);
            if (!m_remoteTempInput.isEmpty()) QFile::remove(m_remoteTempInput);
            m_remoteTempInput.clear();
            m_tempOutput.clear();
            m_finalOutput.clear();
            m_progress->setRange(0, 100);
            m_progress->setValue(0);
        }
    });
    connect(m_ffmpeg, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, [this](int exitCode, QProcess::ExitStatus state) {
        m_convert->setEnabled(true);
        m_cancel->setEnabled(false);
        const bool encoded = state == QProcess::NormalExit && exitCode == 0 &&
                             QFileInfo(m_tempOutput).isFile() && QFileInfo(m_tempOutput).size() > 0;
        if (encoded) {
            // Never put the original source or an existing output at risk until
            // FFmpeg has successfully completed its separate temporary AVI.
            QString backup;
            bool oldMoved = false;
            if (QFile::exists(m_finalOutput)) {
                backup = m_finalOutput + QStringLiteral(".backup-") +
                         QUuid::createUuid().toString(QUuid::WithoutBraces);
                oldMoved = QFile::rename(m_finalOutput, backup);
            }
            const bool canInstall = !QFile::exists(m_finalOutput);
            const bool installed = canInstall && QFile::rename(m_tempOutput, m_finalOutput);
            if (installed) {
                if (oldMoved) QFile::remove(backup);
                m_progress->setRange(0, 100);
                m_progress->setValue(100);
                m_status->setText(tr("Completed"));
                m_log->appendPlainText(tr("Saved: %1").arg(m_finalOutput));
            } else {
                if (oldMoved) QFile::rename(backup, m_finalOutput);
                m_status->setText(tr("Could not save output"));
                m_log->appendPlainText(tr("Output rename failed; temporary AVI: %1").arg(m_tempOutput));
                if (!m_closing) QMessageBox::warning(this, tr("Video Converter"),
                    tr("Conversion finished but the AVI could not be moved to:\n%1\n\n"
                       "The temporary file is:\n%2").arg(m_finalOutput, m_tempOutput));
            }
        } else {
            if (!m_tempOutput.isEmpty()) QFile::remove(m_tempOutput);
            m_status->setText(tr("Conversion cancelled or failed"));
            if (!m_closing) QMessageBox::warning(this, tr("Video Converter"),
                tr("FFmpeg did not finish successfully. See the log for details."));
        }
        m_tempOutput.clear();
        m_finalOutput.clear();
        if (!m_remoteTempInput.isEmpty()) QFile::remove(m_remoteTempInput);
        m_remoteTempInput.clear();
    });

    const QString downloads = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
    const QString defaultDir = QDir(downloads).exists() ? downloads : QDir::homePath();
    navigateSource(settings.value(QStringLiteral("sourceDirectory"), defaultDir).toString());
    navigateTarget(settings.value(QStringLiteral("targetDirectory"), defaultDir).toString());
    const QByteArray splitterGeometry = settings.value(QStringLiteral("splitter")).toByteArray();
    if (!splitterGeometry.isEmpty()) m_splitter->restoreState(splitterGeometry);
    const QByteArray sourceColumns = settings.value(QStringLiteral("sourceColumns")).toByteArray();
    const QByteArray targetColumns = settings.value(QStringLiteral("targetColumns")).toByteArray();
    static_cast<SidboxPersistentColumnsHeader *>(m_sourceView->header())
        ->restoreSavedState(sourceColumns);
    static_cast<SidboxPersistentColumnsHeader *>(m_targetView->header())
        ->restoreSavedState(targetColumns);
    // Regardless of saved header indicators, reopen each pane in natural Name order.
    m_sourceView->sortByColumn(0, Qt::AscendingOrder);
    m_targetView->sortByColumn(0, Qt::AscendingOrder);
    const QByteArray geometry = settings.value(QStringLiteral("geometry")).toByteArray();
    if (!geometry.isEmpty()) restoreGeometry(geometry);
    settings.endGroup();
    if (QStandardPaths::findExecutable(QStringLiteral("ffmpeg")).isEmpty()) {
        m_convert->setEnabled(false);
        m_batchConvert->setEnabled(false);
        m_status->setText(tr("FFmpeg not found in PATH"));
        m_log->appendPlainText(tr("Install FFmpeg and restart the IDE to enable conversion."));
    }
}

SidboxVideoConverterDialog::~SidboxVideoConverterDialog()
{
    m_closing = true;
    if (m_batchListing) {
        disconnect(m_batchListing, nullptr, this, nullptr);
        m_batchListing->kill();
        m_batchListing->waitForFinished(1000);
    }
    for (BatchTask *task : m_batchTasks) {
        if (task->process) {
            disconnect(task->process, nullptr, this, nullptr);
            task->process->kill();
            task->process->waitForFinished(1000);
        }
        if (!task->tempInput.isEmpty()) QFile::remove(task->tempInput);
        if (!task->tempOutput.isEmpty()) QFile::remove(task->tempOutput);
        delete task;
    }
    m_batchTasks.clear();
    if (m_ffmpeg && m_ffmpeg->state() != QProcess::NotRunning) {
        m_ffmpeg->kill();
        m_ffmpeg->waitForFinished(2000);
    }
    if (!m_tempOutput.isEmpty()) QFile::remove(m_tempOutput);
    if (!m_remoteTempInput.isEmpty()) QFile::remove(m_remoteTempInput);
    if (m_smbListing && m_smbListing->state() != QProcess::NotRunning) {
        m_smbListing->kill();
        m_smbListing->waitForFinished(1000);
    }
    if (m_smbDownload && m_smbDownload->state() != QProcess::NotRunning) {
        m_smbDownload->kill();
        m_smbDownload->waitForFinished(1000);
    }
    delete m_smbCredentials;
}

void SidboxVideoConverterDialog::navigateSource(const QString &directory)
{
    const QString entered = directory.trimmed();
    if (entered.startsWith(QStringLiteral("smb://"), Qt::CaseInsensitive)) {
        QUrl url(entered, QUrl::TolerantMode);
        // Authentication is collected in a masked dialog, not stored in a URL
        // or QSettings. Do not accept an embedded password.
        if (!url.password().isEmpty()) {
            QMessageBox::warning(this, tr("Network source"),
                tr("Enter the SMB password when prompted, not in the URL."));
            m_sourcePath->setText(m_sourceDirectory);
            return;
        }
        if (url.scheme().compare(QStringLiteral("smb"), Qt::CaseInsensitive) != 0 ||
            url.host().isEmpty() || url.path().split(QLatin1Char('/'), Qt::SkipEmptyParts).isEmpty()) {
            QMessageBox::warning(this, tr("Network source"),
                tr("Use an SMB share URL such as smb://user@server/Share/Folder/"));
            m_sourcePath->setText(m_sourceDirectory);
            return;
        }
        if (QStandardPaths::findExecutable(QStringLiteral("smbclient")).isEmpty()) {
            QMessageBox::warning(this, tr("SMB support"),
                tr("SMB browsing requires the Samba client. On Fedora, install it with:\n"
                   "sudo dnf install samba-client"));
            m_sourcePath->setText(m_sourceDirectory);
            return;
        }
        url.setPassword(QString());
        startRemoteListing(url);
        return;
    }

    const QFileInfo info(QDir::fromNativeSeparators(entered));
    if (!info.isDir()) {
        m_sourcePath->setText(m_sourceDirectory);
        return;
    }
    m_pendingRemoteLocation.clear();
    if (m_smbListing) {
        QProcess *previous = m_smbListing;
        m_smbListing = nullptr;
        if (previous->state() != QProcess::NotRunning) previous->kill();
        previous->deleteLater();
    }
    if (m_sourceSort->sourceModel() != m_sourceModel) {
        m_sourceSort->setSourceModel(m_sourceModel);
    }
    m_sourceDirectory = info.absoluteFilePath();
    m_sourcePath->setText(QDir::toNativeSeparators(m_sourceDirectory));
    m_sourceView->setRootIndex(m_sourceSort->mapFromSource(m_sourceModel->index(m_sourceDirectory)));
    m_sourceView->sortByColumn(0, Qt::AscendingOrder);
    auto *header = static_cast<SidboxPersistentColumnsHeader *>(m_sourceView->header());
    header->applyRemembered();
    QTimer::singleShot(0, header, [header]() { header->applyRemembered(); });
    m_selectedSource.clear();
    m_selectedLabel->setText(tr("Choose a video on the left, then press Convert →"));
}

void SidboxVideoConverterDialog::selectSource(const QModelIndex &index)
{
    QString file;
    QString name;
    if (index.isValid() && m_sourceSort->sourceModel() == m_remoteModel) {
        const QModelIndex first = index.siblingAtColumn(0);
        if (!first.data(Qt::UserRole + 1).toBool()) {
            file = first.data(Qt::UserRole).toString();
            name = first.data(Qt::DisplayRole).toString();
        }
    } else if (index.isValid() && m_sourceSort->sourceModel() == m_sourceModel) {
        const QString path = m_sourceModel->filePath(m_sourceSort->mapToSource(index));
        if (QFileInfo(path).isFile()) {
            file = path;
            name = QFileInfo(path).fileName();
        }
    }
    static const QStringList supported = {
        QStringLiteral("avi"), QStringLiteral("mp4"), QStringLiteral("mkv"),
        QStringLiteral("mov"), QStringLiteral("webm"), QStringLiteral("m4v"),
        QStringLiteral("mpeg"), QStringLiteral("mpg"), QStringLiteral("wmv"),
        QStringLiteral("ts"), QStringLiteral("m2ts"), QStringLiteral("mts"),
        QStringLiteral("flv")
    };
    if (!supported.contains(QFileInfo(name).suffix().toLower())) file.clear();
    m_selectedSource = file;
    m_durationSeconds = 0.0;
    m_selectedLabel->setText(file.isEmpty()
        ? tr("Choose a video on the left, then press Convert →")
        : tr("Source: %1").arg(name));
    if (!file.isEmpty() && !remoteSourceSelected()) probeDuration(file);
}

void SidboxVideoConverterDialog::probeDuration(const QString &source)
{
    const QString probeExe = QStandardPaths::findExecutable(QStringLiteral("ffprobe"));
    if (probeExe.isEmpty()) return;
    auto *probe = new QProcess(this);
    connect(probe, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, [this, probe, source](int code, QProcess::ExitStatus state) {
        if (state == QProcess::NormalExit && code == 0 &&
            (m_selectedSource == source || source == m_remoteTempInput)) {
            bool ok = false;
            const double seconds = QString::fromUtf8(probe->readAllStandardOutput()).trimmed().toDouble(&ok);
            if (ok && seconds > 0.0) m_durationSeconds = seconds;
        }
        probe->deleteLater();
    });
    connect(probe, &QProcess::errorOccurred, probe, [probe]() {
        if (probe->state() == QProcess::NotRunning) probe->deleteLater();
    });
    probe->start(probeExe, {QStringLiteral("-v"), QStringLiteral("error"),
        QStringLiteral("-show_entries"), QStringLiteral("format=duration"),
        QStringLiteral("-of"), QStringLiteral("default=noprint_wrappers=1:nokey=1"), source});
}

bool SidboxVideoConverterDialog::remoteSourceSelected() const
{
    return m_selectedSource.startsWith(QStringLiteral("smb://"), Qt::CaseInsensitive);
}

QStringList SidboxVideoConverterDialog::smbArguments(const QUrl &url, const QString &command) const
{
    const QStringList pieces = url.path().split(QLatin1Char('/'), Qt::SkipEmptyParts);
    if (url.host().isEmpty() || pieces.isEmpty()) return {};
    // Do not pass -E: smbclient redirects even `ls` output to stderr with it.
    // Directory parsing below intentionally reads standard output.
    QStringList args = {QStringLiteral("//") + url.host() + QLatin1Char('/') + pieces.first(),
                        QStringLiteral("-d"), QStringLiteral("0"),
                        QStringLiteral("-q")};
    if (url.port() > 0) args << QStringLiteral("-p") << QString::number(url.port());
    if (!url.userName().isEmpty()) args << QStringLiteral("-U") << url.userName();
    const QString identity = url.userName() + QLatin1Char('@') + url.host() +
                             QLatin1Char(':') + QString::number(url.port(445));
    if (m_smbCredentials && m_smbCredentialIdentity == identity)
        args << QStringLiteral("-A") << m_smbCredentials->fileName();
    else
        args << QStringLiteral("-N");
    if (pieces.size() > 1)
        args << QStringLiteral("-D") << pieces.mid(1).join(QLatin1Char('/'));
    args << QStringLiteral("-c") << command;
    return args;
}

void SidboxVideoConverterDialog::startRemoteListing(const QUrl &url)
{
    const QString location = url.toString(QUrl::FullyEncoded);
    if (m_pendingRemoteLocation != location) m_smbPasswordPrompted = false;
    m_pendingRemoteLocation = location;
    m_selectedSource.clear();
    m_selectedLabel->setText(tr("Choose a video on the left, then press Convert →"));
    if (m_smbListing && m_smbListing->state() != QProcess::NotRunning)
        m_smbListing->kill();
    auto *process = new QProcess(this);
    m_smbListing = process;
    process->setProcessChannelMode(QProcess::SeparateChannels);
    m_status->setText(tr("Opening SMB folder..."));
    m_sourcePath->setText(url.toDisplayString(QUrl::RemovePassword));
    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this,
            [this, process, url, location](int code, QProcess::ExitStatus state) {
        const bool current = !m_closing && m_smbListing == process &&
                             m_pendingRemoteLocation == location;
        const QString output = QString::fromLocal8Bit(process->readAllStandardOutput());
        const QString errors = QString::fromLocal8Bit(process->readAllStandardError());
        process->deleteLater();
        if (!current) return;
        m_smbListing = nullptr;
        const bool smbError = output.contains(QStringLiteral("NT_STATUS_")) ||
                              errors.contains(QStringLiteral("NT_STATUS_"));
        if (state != QProcess::NormalExit || code != 0 || smbError) {
            const bool authFailure = errors.contains(QStringLiteral("LOGON_FAILURE"), Qt::CaseInsensitive) ||
                                     errors.contains(QStringLiteral("ACCESS_DENIED"), Qt::CaseInsensitive) ||
                                     output.contains(QStringLiteral("LOGON_FAILURE"), Qt::CaseInsensitive) ||
                                     output.contains(QStringLiteral("ACCESS_DENIED"), Qt::CaseInsensitive);
            if (authFailure && !m_smbPasswordPrompted) {
                m_smbPasswordPrompted = true;
                bool accepted = false;
                const QString password = QInputDialog::getText(this, tr("SMB Login"),
                    tr("Password for %1 on %2:").arg(url.userName().isEmpty()
                        ? QStringLiteral("guest") : url.userName(), url.host()),
                    QLineEdit::Password, QString(), &accepted);
                if (accepted && !password.contains(QLatin1Char('\n')) &&
                    !password.contains(QLatin1Char('\r'))) {
                    delete m_smbCredentials;
                    m_smbCredentials = new QTemporaryFile(QDir::tempPath() +
                        QStringLiteral("/sidbox-smb-auth-XXXXXX"), this);
                    if (m_smbCredentials->open()) {
                        m_smbCredentials->setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner);
                        const QByteArray credentials = QStringLiteral("username = %1\npassword = %2\n")
                            .arg(url.userName(), password).toUtf8();
                        if (m_smbCredentials->write(credentials) == credentials.size()) {
                            m_smbCredentials->flush();
                            m_smbCredentialIdentity = url.userName() + QLatin1Char('@') +
                                url.host() + QLatin1Char(':') + QString::number(url.port(445));
                            startRemoteListing(url);
                            return;
                        }
                    }
                }
            }
            m_smbPasswordPrompted = false; // Allow another attempt after a bad password.
            m_sourcePath->setText(m_sourceDirectory);
            m_status->setText(tr("SMB folder unavailable"));
            QMessageBox::warning(this, tr("SMB folder"),
                tr("Could not list %1\n\n%2").arg(location,
                    errors.trimmed().isEmpty() ? output.trimmed() : errors.trimmed()));
            return;
        }
        // smbclient `ls` normally prints: name, attribute letters, byte size,
        // timestamp. Permit all uppercase attributes, not just a small subset.
        const QRegularExpression entry(QStringLiteral(
            R"(^\s*(.*?)\s+([A-Z]+)\s+(\d+)\s+(.+?)\s*$)"));
        // A successful smbclient exit with zero parseable entries must not
        // silently display a blank folder. A truly empty folder usually still
        // includes the dot entries, which count as valid listing records.
        int parsedRecords = 0;
        for (const QString &line : output.split(QLatin1Char('\n'))) {
            if (entry.match(line).hasMatch()) ++parsedRecords;
        }
        if (!parsedRecords) {
            m_sourcePath->setText(m_sourceDirectory);
            m_status->setText(tr("SMB listing format not recognised"));
            QMessageBox::warning(this, tr("SMB folder"),
                tr("Connected to the SMB share, but could not read its directory listing.\n\n%1")
                    .arg((output.trimmed().isEmpty() ? errors : output).trimmed().left(1000)));
            return;
        }
        showRemoteDirectory(url);
        QFileIconProvider provider;
        for (const QString &line : output.split(QLatin1Char('\n'))) {
            const auto match = entry.match(line);
            if (!match.hasMatch()) continue;
            const QString name = match.captured(1).trimmed();
            if (name.isEmpty() || name == QStringLiteral(".") || name == QStringLiteral("..")) continue;
            const bool isDir = match.captured(2).contains(QLatin1Char('D'));
            bool sizeOk = false;
            const qint64 size = match.captured(3).toLongLong(&sizeOk);
            if (!sizeOk) continue;
            QUrl item = url;
            QString path = item.path();
            if (!path.endsWith(QLatin1Char('/'))) path += QLatin1Char('/');
            item.setPath(path + name + (isDir ? QStringLiteral("/") : QString()));
            auto *nameItem = new QStandardItem(provider.icon(isDir ? QFileIconProvider::Folder :
                QFileIconProvider::File), name);
            nameItem->setData(item.toString(QUrl::FullyEncoded), Qt::UserRole);
            nameItem->setData(isDir, Qt::UserRole + 1);
            nameItem->setData(size, Qt::UserRole + 2); // Exact bytes for selected-file batch download progress.
            nameItem->setEditable(false);
            auto *sizeItem = new QStandardItem(isDir ? QString() :
                QStringLiteral("%1 MiB").arg(double(size) / (1024.0 * 1024.0), 0, 'f', 2));
            auto *typeItem = new QStandardItem(isDir ? tr("Folder") : tr("File"));
            auto *dateItem = new QStandardItem(match.captured(4).trimmed());
            sizeItem->setEditable(false);
            typeItem->setEditable(false);
            dateItem->setEditable(false);
            m_remoteModel->appendRow({nameItem, sizeItem, typeItem, dateItem});
        }
        m_status->setText(tr("SMB folder ready (%1 items)").arg(m_remoteModel->rowCount()));
    });
    connect(process, &QProcess::errorOccurred, this, [this, process](QProcess::ProcessError error) {
        if (error == QProcess::FailedToStart && process == m_smbListing) {
            m_smbListing = nullptr;
            m_sourcePath->setText(m_sourceDirectory);
            m_status->setText(tr("smbclient failed to start"));
            process->deleteLater();
        }
    });
    process->start(QStandardPaths::findExecutable(QStringLiteral("smbclient")),
                   smbArguments(url, QStringLiteral("ls")));
}

void SidboxVideoConverterDialog::showRemoteDirectory(const QUrl &url)
{
    const QString location = url.toString(QUrl::FullyEncoded);
    m_remoteModel->clear();
    m_remoteModel->setHorizontalHeaderLabels({tr("Name"), tr("Size"), tr("Type"), tr("Date Modified")});
    if (m_sourceSort->sourceModel() != m_remoteModel) {
        m_sourceSort->setSourceModel(m_remoteModel);
    }
    m_sourceView->setRootIndex(QModelIndex());
    m_sourceView->sortByColumn(0, Qt::AscendingOrder);
    auto *header = static_cast<SidboxPersistentColumnsHeader *>(m_sourceView->header());
    header->applyRemembered();
    QTimer::singleShot(0, header, [header]() { header->applyRemembered(); });
    m_sourceDirectory = location;
    m_sourcePath->setText(url.toDisplayString(QUrl::RemovePassword));
    m_selectedSource.clear();
    m_selectedLabel->setText(tr("Choose a video on the left, then press Convert →"));
}

void SidboxVideoConverterDialog::navigateTarget(const QString &directory)
{
    const QFileInfo info(QDir::fromNativeSeparators(directory.trimmed()));
    if (!info.isDir()) {
        m_targetPath->setText(m_targetDirectory);
        return;
    }
    m_targetDirectory = info.absoluteFilePath();
    m_targetPath->setText(QDir::toNativeSeparators(m_targetDirectory));
    m_targetView->setRootIndex(m_targetSort->mapFromSource(m_targetModel->index(m_targetDirectory)));
    m_targetView->sortByColumn(0, Qt::AscendingOrder);
    auto *header = static_cast<SidboxPersistentColumnsHeader *>(m_targetView->header());
    header->applyRemembered();
    QTimer::singleShot(0, header, [header]() { header->applyRemembered(); });
}

void SidboxVideoConverterDialog::convertSelected()
{
    if (m_ffmpeg->state() != QProcess::NotRunning ||
        (m_smbDownload && m_smbDownload->state() != QProcess::NotRunning)) return;
    const bool remote = remoteSourceSelected();
    if (m_selectedSource.isEmpty() || (!remote && !QFileInfo(m_selectedSource).isFile())) {
        QMessageBox::information(this, tr("Video Converter"), tr("Select a source video file first."));
        return;
    }
    // The target address bar is editable; accept a local directory entered there.
    const QFileInfo typedTarget(QDir::fromNativeSeparators(m_targetPath->text().trimmed()));
    if (typedTarget.isDir()) m_targetDirectory = typedTarget.absoluteFilePath();
    if (!QFileInfo(m_targetDirectory).isDir()) {
        QMessageBox::warning(this, tr("Video Converter"), tr("Choose an existing local target directory."));
        return;
    }
    const QString sourceName = remote
        ? QFileInfo(QUrl(m_selectedSource).path()).fileName()
        : QFileInfo(m_selectedSource).fileName();
    const QString proposed = QFileInfo(sourceName).completeBaseName() + QStringLiteral(".avi");
    bool accepted = false;
    QString filename = QInputDialog::getText(this, tr("Output AVI Name"),
        tr("Save converted video as:"), QLineEdit::Normal, proposed, &accepted).trimmed();
    if (!accepted) return;
    if (filename.isEmpty() || filename.contains(QLatin1Char('/')) ||
        filename.contains(QLatin1Char('\\')) || filename == "." || filename == "..") {
        QMessageBox::warning(this, tr("Video Converter"), tr("Please enter a filename, not a path."));
        return;
    }
    filename = QFileInfo(filename).completeBaseName() + QStringLiteral(".avi");
    if (filename == QStringLiteral(".avi")) return;
    m_finalOutput = QDir(m_targetDirectory).absoluteFilePath(filename);
    if (!remote && QFileInfo(m_selectedSource).absoluteFilePath() ==
                   QFileInfo(m_finalOutput).absoluteFilePath()) {
        QMessageBox::warning(this, tr("Video Converter"),
            tr("The output must not overwrite the source AVI. Choose another name or folder."));
        return;
    }
    if (QFile::exists(m_finalOutput) && QMessageBox::question(this,
            tr("Replace existing AVI?"), tr("Replace %1 after conversion succeeds?").arg(filename),
            QMessageBox::Yes | QMessageBox::No, QMessageBox::No) != QMessageBox::Yes)
        return;
    if (QStandardPaths::findExecutable(QStringLiteral("ffmpeg")).isEmpty()) {
        QMessageBox::warning(this, tr("FFmpeg missing"), tr("FFmpeg was not found in PATH."));
        return;
    }
    // Both temporary files are on the target volume to avoid /tmp running out
    // of space when the remote input is a long TV episode.
    const QString id = QUuid::createUuid().toString(QUuid::WithoutBraces);
    m_tempOutput = QDir(m_targetDirectory).absoluteFilePath(
        QStringLiteral(".sidbox-converting-%1.avi").arg(id));
    m_remoteTempInput.clear();
    m_log->clear();
    m_log->appendPlainText(tr("Input: %1\nOutput: %2").arg(m_selectedSource, m_finalOutput));
    m_progressText.clear();
    m_convert->setEnabled(false);
    m_cancel->setEnabled(true);
    savePreferences();
    if (remote) {
        m_remoteTempInput = QDir(m_targetDirectory).absoluteFilePath(
            QStringLiteral(".sidbox-network-input-%1.%2")
                .arg(id, QFileInfo(sourceName).suffix().toLower()));
        startRemoteDownload();
    } else {
        beginFFmpeg(m_selectedSource);
    }
}

void SidboxVideoConverterDialog::startRemoteDownload()
{
    const QUrl url(m_selectedSource);
    const QString filename = QFileInfo(url.path()).fileName();
    // smbclient -c accepts semicolon-delimited commands. Reject control or
    // quoting characters before passing an untrusted remote filename into it.
    if (filename.isEmpty() || filename.contains(QLatin1Char('"')) ||
        filename.contains(QLatin1Char('\\')) || filename.contains(QLatin1Char(';')) ||
        filename.contains(QLatin1Char('\t')) || filename.contains(QLatin1Char('\r')) ||
        filename.contains(QLatin1Char('\n'))) {
        m_status->setText(tr("Unsupported SMB filename"));
        m_convert->setEnabled(true);
        m_cancel->setEnabled(false);
        m_tempOutput.clear();
        m_finalOutput.clear();
        m_remoteTempInput.clear();
        return;
    }
    auto *process = new QProcess(this);
    m_smbDownload = process;
    m_remoteCancelled = false;
    m_status->setText(tr("Downloading video from SMB..."));
    m_progress->setRange(0, 0);
    m_log->appendPlainText(tr("Copying network source to temporary input..."));
    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this,
            [this, process](int code, QProcess::ExitStatus state) {
        const bool current = !m_closing && process == m_smbDownload;
        const bool success = state == QProcess::NormalExit && code == 0 &&
                             QFileInfo(m_remoteTempInput).isFile() &&
                             QFileInfo(m_remoteTempInput).size() > 0;
        const QString errors = QString::fromLocal8Bit(process->readAllStandardError());
        process->deleteLater();
        if (!current) return;
        m_smbDownload = nullptr;
        if (success && !m_remoteCancelled) {
            m_durationSeconds = 0.0;
            probeDuration(m_remoteTempInput);
            beginFFmpeg(m_remoteTempInput);
            return;
        }
        QFile::remove(m_remoteTempInput);
        m_remoteTempInput.clear();
        m_tempOutput.clear();
        m_finalOutput.clear();
        m_progress->setRange(0, 100);
        m_progress->setValue(0);
        m_convert->setEnabled(true);
        m_cancel->setEnabled(false);
        m_status->setText(m_remoteCancelled ? tr("Network transfer cancelled") :
                                            tr("SMB download failed"));
        if (!m_remoteCancelled) {
            m_log->appendPlainText(errors);
            QMessageBox::warning(this, tr("Network source"),
                tr("Could not download the source video.\n\n%1").arg(errors.trimmed()));
        }
    });
    connect(process, &QProcess::errorOccurred, this,
            [this, process](QProcess::ProcessError error) {
        if (error == QProcess::FailedToStart && m_smbDownload == process) {
            m_smbDownload = nullptr;
            process->deleteLater();
            QFile::remove(m_remoteTempInput);
            m_remoteTempInput.clear();
            m_tempOutput.clear();
            m_finalOutput.clear();
            m_progress->setRange(0, 100);
            m_progress->setValue(0);
            m_convert->setEnabled(true);
            m_cancel->setEnabled(false);
            m_status->setText(tr("smbclient could not start"));
        }
    });
    // smbclient understands double-quoted filenames with spaces. QProcess
    // passes each option as an argument, never through a shell.
    const QString command = QStringLiteral("get \"%1\" \"%2\"")
        .arg(filename, QFileInfo(m_remoteTempInput).fileName());
    process->setWorkingDirectory(m_targetDirectory);
    // The selected URL is a FILE. smbclient -D must point to its PARENT
    // directory, otherwise the server tries to cd into the movie filename.
    QUrl parent = url;
    const QString remotePath = parent.path();
    parent.setPath(remotePath.left(remotePath.lastIndexOf(QLatin1Char('/'))) +
                   QLatin1Char('/'));
    process->start(QStandardPaths::findExecutable(QStringLiteral("smbclient")),
                   smbArguments(parent, command));
}

void SidboxVideoConverterDialog::beginFFmpeg(const QString &inputFile)
{
    const QString executable = QStandardPaths::findExecutable(QStringLiteral("ffmpeg"));
    if (executable.isEmpty()) {
        m_status->setText(tr("FFmpeg unavailable"));
        m_convert->setEnabled(true);
        m_cancel->setEnabled(false);
        if (!m_remoteTempInput.isEmpty()) QFile::remove(m_remoteTempInput);
        m_remoteTempInput.clear();
        m_tempOutput.clear();
        m_finalOutput.clear();
        return;
    }
    const QSize size = m_resolution->currentData().toSize();
    const int fps = m_fps->currentData().toInt();
    const int quality = m_quality->currentData().toInt();
    const int bitrate = m_bitrate->currentData().toInt();
    const int audioChannels = m_audioOutput->currentData().toInt();
    const QString scale = QStringLiteral("fps=%1,scale=%2:%3:force_original_aspect_ratio=decrease,"
        "pad=%2:%3:(ow-iw)/2:(oh-ih)/2").arg(fps).arg(size.width()).arg(size.height());
    QStringList args = {QStringLiteral("-hide_banner"), QStringLiteral("-nostdin"),
        QStringLiteral("-y"), QStringLiteral("-i"), inputFile,
        QStringLiteral("-vf"), scale, QStringLiteral("-c:v"), QStringLiteral("mjpeg"),
        QStringLiteral("-q:v"), QString::number(quality),
        QStringLiteral("-pix_fmt"), QStringLiteral("yuvj420p")};
    if (audioChannels > 0) {
        if (m_audioGain->isChecked())
            args << QStringLiteral("-af") << QStringLiteral("loudnorm=I=-16:TP=-1.5:LRA=11");
        args << QStringLiteral("-c:a") << QStringLiteral("libmp3lame")
             << QStringLiteral("-b:a") << QStringLiteral("%1k").arg(bitrate)
             << QStringLiteral("-ar") << QStringLiteral("44100")
             << QStringLiteral("-ac") << QString::number(audioChannels);
    } else {
        args << QStringLiteral("-an");
    }
    args << QStringLiteral("-f") << QStringLiteral("avi")
         << QStringLiteral("-progress") << QStringLiteral("pipe:1")
         << QStringLiteral("-nostats") << m_tempOutput;
    m_log->appendPlainText(tr("Settings: %1×%2, %3 fps, MJPEG Q%4, MP3 %5%6")
        .arg(size.width()).arg(size.height()).arg(fps).arg(quality)
        .arg(audioChannels > 0 ? QStringLiteral("%1k %2, 44.1 kHz").arg(bitrate)
            .arg(audioChannels == 1 ? tr("mono") : tr("stereo")) : tr("off"))
        .arg(audioChannels > 0 && m_audioGain->isChecked()
            ? QStringLiteral(" (auto gain -16 LUFS)") : QString()));
    m_progressText.clear();
    m_progress->setRange(0, m_durationSeconds > 0.0 ? 100 : 0);
    m_progress->setValue(0);
    m_status->setText(tr("Starting FFmpeg..."));
    m_ffmpeg->start(executable, args);
}

void SidboxVideoConverterDialog::convertBatchFolder()
{
    if (m_batchBusy || m_batchPreparing || m_ffmpeg->state() != QProcess::NotRunning ||
        (m_smbDownload && m_smbDownload->state() != QProcess::NotRunning)) return;

    // Respect an output path typed into the Target address bar.
    const QFileInfo typedTarget(QDir::fromNativeSeparators(m_targetPath->text().trimmed()));
    if (typedTarget.isDir()) m_targetDirectory = typedTarget.absoluteFilePath();
    if (!QFileInfo(m_targetDirectory).isDir()) {
        QMessageBox::warning(this, tr("Batch Convert"), tr("Choose a valid local destination folder."));
        return;
    }
    if (QStandardPaths::findExecutable(QStringLiteral("ffmpeg")).isEmpty()) {
        QMessageBox::warning(this, tr("Batch Convert"), tr("FFmpeg was not found in PATH."));
        return;
    }

    // selectedRows(0) returns one proxy index per highlighted file, not all
    // four columns. Always map through the proxy before accessing local files;
    // for SMB, use the URL stored on each item (not a rebuilt filename).
    const QModelIndexList selected = m_sourceView->selectionModel()->selectedRows(0);
    static const QSet<QString> supported = {
        QStringLiteral("avi"), QStringLiteral("mp4"), QStringLiteral("mkv"),
        QStringLiteral("mov"), QStringLiteral("webm"), QStringLiteral("m4v"),
        QStringLiteral("mpeg"), QStringLiteral("mpg"), QStringLiteral("wmv"),
        QStringLiteral("ts"), QStringLiteral("m2ts"), QStringLiteral("mts"),
        QStringLiteral("flv")
    };
    const bool remote = m_sourceSort->sourceModel() == m_remoteModel;
    QString folder = m_sourceDirectory;
    bool singleFolderSelected = false;
    QVector<BatchFile> chosenFiles;
    for (const QModelIndex &proxyIndex : selected) {
        const QModelIndex index = m_sourceSort->mapToSource(proxyIndex);
        if (!index.isValid()) continue;
        bool isDir = false;
        QString source;
        QString name;
        qint64 bytes = 0;
        if (remote) {
            isDir = index.data(Qt::UserRole + 1).toBool();
            source = index.data(Qt::UserRole).toString();
            name = index.data(Qt::DisplayRole).toString();
            bytes = index.data(Qt::UserRole + 2).toLongLong();
        } else {
            const QFileInfo info(m_sourceModel->filePath(index));
            isDir = info.isDir();
            if (!isDir && (!info.isFile() || !info.isReadable())) continue;
            source = info.absoluteFilePath();
            name = info.fileName();
            bytes = info.size();
        }
        if (isDir) {
            if (selected.size() == 1) {
                folder = source;
                singleFolderSelected = true;
            }
            continue;
        }
        if (source.isEmpty() || name.isEmpty() ||
            !supported.contains(QFileInfo(name).suffix().toLower()) ||
            name.endsWith(QStringLiteral("_sb.avi"), Qt::CaseInsensitive)) continue;
        chosenFiles.append({source, name, bytes});
    }

    if (!chosenFiles.isEmpty()) {
        QCollator natural;
        natural.setNumericMode(true);
        natural.setCaseSensitivity(Qt::CaseInsensitive);
        std::sort(chosenFiles.begin(), chosenFiles.end(), [&natural](const BatchFile &a, const BatchFile &b) {
            return natural.compare(a.name, b.name) < 0;
        });
        // Only the highlighted video files enter the queue. Any highlighted
        // folders or unsupported files are ignored, never traversed.
        beginBatch(chosenFiles, m_sourceDirectory, true);
        return;
    }
    if (!selected.isEmpty() && !singleFolderSelected) {
        QMessageBox::information(this, tr("Batch Convert"),
            tr("Select supported video files (Ctrl/Shift-click), or select one folder to convert all videos inside it. Already-converted *_sb.avi files are excluded."));
        return;
    }
    prepareBatch(folder);
}

void SidboxVideoConverterDialog::prepareBatch(const QString &folder)
{
    static const QSet<QString> supported = {
        QStringLiteral("avi"), QStringLiteral("mp4"), QStringLiteral("mkv"),
        QStringLiteral("mov"), QStringLiteral("webm"), QStringLiteral("m4v"),
        QStringLiteral("mpeg"), QStringLiteral("mpg"), QStringLiteral("wmv"),
        QStringLiteral("ts"), QStringLiteral("m2ts"), QStringLiteral("mts"),
        QStringLiteral("flv")
    };
    if (!folder.startsWith(QStringLiteral("smb://"), Qt::CaseInsensitive)) {
        const QDir dir(folder);
        if (!dir.exists()) return;
        QVector<BatchFile> files;
        const QFileInfoList entries = dir.entryInfoList(QDir::Files | QDir::Readable | QDir::NoDotAndDotDot,
                                                         QDir::Name | QDir::IgnoreCase);
        for (const QFileInfo &entry : entries)
            if (supported.contains(entry.suffix().toLower()) &&
                !entry.fileName().endsWith(QStringLiteral("_sb.avi"), Qt::CaseInsensitive))
                files.append({entry.absoluteFilePath(), entry.fileName(), entry.size()});
        QCollator natural;
        natural.setNumericMode(true);
        natural.setCaseSensitivity(Qt::CaseInsensitive);
        std::sort(files.begin(), files.end(), [&natural](const BatchFile &a, const BatchFile &b) {
            return natural.compare(a.name, b.name) < 0;
        });
        beginBatch(files, folder);
        return;
    }
    const QUrl url(folder, QUrl::TolerantMode);
    const QString executable = QStandardPaths::findExecutable(QStringLiteral("smbclient"));
    if (executable.isEmpty()) {
        QMessageBox::warning(this, tr("Batch Convert"), tr("smbclient is not installed."));
        return;
    }
    m_batchPreparing = true;
    m_batchCancelled = false;
    m_sourceView->parentWidget()->setEnabled(false);
    m_targetView->parentWidget()->setEnabled(false);
    m_batchConvert->setEnabled(false);
    m_convert->setEnabled(false);
    m_cancel->setEnabled(true);
    m_progress->setRange(0, 0);
    m_status->setText(tr("Listing SMB batch folder..."));
    auto *proc = new QProcess(this);
    m_batchListing = proc;
    connect(proc, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, [this, proc, url, folder](int code, QProcess::ExitStatus state) {
        const bool current = (m_batchListing == proc);
        const QString output = QString::fromLocal8Bit(proc->readAllStandardOutput());
        const QString errors = QString::fromLocal8Bit(proc->readAllStandardError());
        proc->deleteLater();
        if (!current || m_closing) return;
        m_batchListing = nullptr;
        m_batchPreparing = false;
        if (m_batchCancelled) {
            endBatch();
            return;
        }
        if (code != 0 || state != QProcess::NormalExit ||
            errors.contains(QStringLiteral("NT_STATUS_")) ||
            output.contains(QStringLiteral("NT_STATUS_"))) {
            endBatch();
            QMessageBox::warning(this, tr("Batch Convert"),
                tr("Unable to list SMB folder:\n%1").arg(errors.trimmed().isEmpty()
                    ? output.trimmed() : errors.trimmed()));
            return;
        }
        const QRegularExpression entry(QStringLiteral(
            R"(^\s*(.*?)\s+([A-Z]+)\s+(\d+)\s+(.+?)\s*$)"));
        QVector<BatchFile> files;
        int parsed = 0;
        for (const QString &line : output.split(QLatin1Char('\n'))) {
            const auto match = entry.match(line);
            if (!match.hasMatch()) continue;
            ++parsed;
            const QString name = match.captured(1).trimmed();
            if (name.isEmpty() || name == QStringLiteral(".") || name == QStringLiteral("..") ||
                match.captured(2).contains(QLatin1Char('D')) ||
                !supported.contains(QFileInfo(name).suffix().toLower()) ||
                name.endsWith(QStringLiteral("_sb.avi"), Qt::CaseInsensitive)) continue;
            QUrl item = url;
            QString path = item.path();
            if (!path.endsWith(QLatin1Char('/'))) path += QLatin1Char('/');
            item.setPath(path + name);
            files.append({item.toString(QUrl::FullyEncoded), name,
                          match.captured(3).toLongLong()});
        }
        if (!parsed) {
            endBatch();
            QMessageBox::warning(this, tr("Batch Convert"), tr("SMB listing format not recognised."));
            return;
        }
        QCollator natural;
        natural.setNumericMode(true);
        natural.setCaseSensitivity(Qt::CaseInsensitive);
        std::sort(files.begin(), files.end(), [&natural](const BatchFile &a, const BatchFile &b) {
            return natural.compare(a.name, b.name) < 0;
        });
        beginBatch(files, folder);
    });
    connect(proc, &QProcess::errorOccurred, this, [this, proc](QProcess::ProcessError error) {
        if (error == QProcess::FailedToStart && proc == m_batchListing) {
            m_batchListing = nullptr;
            m_batchPreparing = false;
            proc->deleteLater();
            endBatch();
            QMessageBox::warning(this, tr("Batch Convert"), tr("Could not start smbclient."));
        }
    });
    proc->start(executable, smbArguments(url, QStringLiteral("ls")));
}

void SidboxVideoConverterDialog::beginBatch(const QVector<BatchFile> &files,
                                             const QString &folder, bool selectedFiles)
{
    if (m_closing) return;
    if (files.isEmpty()) {
        endBatch();
        m_status->setText(tr("No convertible videos in the selected folder"));
        return;
    }
    const int parallel = m_parallel->currentData().toInt();
    if (QMessageBox::question(this, tr("Batch Convert"),
        tr("Convert %1 %2 from:\n%3\n\nTo:\n%4\n\n"
           "Names: filename_sb.avi\nParallel conversions: %5\n"
           "Existing output files will be skipped. Subfolders are not included.\n\nStart?")
        .arg(files.size()).arg(selectedFiles ? tr("selected videos") : tr("videos"))
        .arg(folder, m_targetDirectory).arg(parallel),
        QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) != QMessageBox::Yes) {
        endBatch();
        return;
    }
    for (BatchTask *task : m_batchTasks) delete task;
    m_batchTasks.clear();
    m_batchNext = m_batchDone = m_batchActive = 0;
    m_batchSucceeded = m_batchSkipped = m_batchFailed = 0;
    m_batchParallel = qBound(1, parallel, 4);
    m_batchSize = m_resolution->currentData().toSize();
    m_batchFps = m_fps->currentData().toInt();
    m_batchQuality = m_quality->currentData().toInt();
    m_batchBitrate = m_bitrate->currentData().toInt();
    m_batchAudioChannels = m_audioOutput->currentData().toInt();
    m_batchGain = m_audioGain->isChecked();
    m_batchCancelled = false;
    m_batchBusy = true;
    m_batchPanel->show();
    m_batchTable->setRowCount(0);
    m_log->clear();
    m_log->appendPlainText(tr("Batch %1: %2\nDestination: %3\nParallel: %4")
                            .arg(selectedFiles ? tr("selection") : tr("folder"))
                            .arg(folder, m_targetDirectory).arg(m_batchParallel));
    QSet<QString> planned;
    for (const BatchFile &file : files) {
        const QString base = QFileInfo(file.name).completeBaseName();
        if (base.isEmpty()) continue;
        const QString output = QDir(m_targetDirectory).absoluteFilePath(base + QStringLiteral("_sb.avi"));
        if (QFile::exists(output) || planned.contains(output.toCaseFolded()) ||
            (!file.source.startsWith(QStringLiteral("smb://"), Qt::CaseInsensitive) &&
             QFileInfo(file.source).absoluteFilePath() == output)) {
            ++m_batchSkipped;
            const int row = m_batchTable->rowCount();
            m_batchTable->insertRow(row);
            m_batchTable->setItem(row, 0, new QTableWidgetItem(file.name));
            m_batchTable->setItem(row, 1, new QTableWidgetItem(tr("Skipped")));
            m_batchTable->setItem(row, 2, new QTableWidgetItem(tr("Already exists")));
            m_batchTable->setItem(row, 3, new QTableWidgetItem(QStringLiteral("—")));
            m_log->appendPlainText(tr("Skipped existing: %1").arg(output));
            continue;
        }
        planned.insert(output.toCaseFolded());
        auto *task = new BatchTask;
        task->name = file.name;
        task->source = file.source;
        task->output = output;
        task->sourceBytes = file.sourceBytes;
        task->row = m_batchTable->rowCount();
        m_batchTable->insertRow(task->row);
        auto *nameItem = new QTableWidgetItem(file.name);
        nameItem->setToolTip(file.source);
        m_batchTable->setItem(task->row, 0, nameItem);
        m_batchTable->setItem(task->row, 1, new QTableWidgetItem(tr("Queued")));
        m_batchTable->setItem(task->row, 3, new QTableWidgetItem(QStringLiteral("—")));
        task->progressBar = new QProgressBar(m_batchTable);
        task->progressBar->setRange(0, 100);
        task->progressBar->setValue(0);
        task->progressBar->setFormat(QStringLiteral("0%"));
        task->progressBar->setTextVisible(true);
        m_batchTable->setCellWidget(task->row, 2, task->progressBar);
        const QString token = QUuid::createUuid().toString(QUuid::WithoutBraces);
        task->tempOutput = QDir(m_targetDirectory).absoluteFilePath(
            QStringLiteral(".sidbox-batch-%1.avi").arg(token));
        if (file.source.startsWith(QStringLiteral("smb://"), Qt::CaseInsensitive)) {
            task->tempInput = QDir(m_targetDirectory).absoluteFilePath(
                QStringLiteral(".sidbox-batch-input-%1.%2")
                    .arg(token, QFileInfo(file.name).suffix().toLower()));
        }
        m_batchTasks.append(task);
    }
    m_convert->setEnabled(false);
    m_batchConvert->setEnabled(false);
    m_cancel->setEnabled(true);
    m_sourceView->parentWidget()->setEnabled(false);
    m_targetView->parentWidget()->setEnabled(false);
    m_parallel->setEnabled(false);
    m_resolution->setEnabled(false);
    m_fps->setEnabled(false);
    m_quality->setEnabled(false);
    m_bitrate->setEnabled(false);
    m_audioOutput->setEnabled(false);
    m_audioGain->setEnabled(false);
    m_progress->setRange(0, qMax(1, m_batchTasks.size() + m_batchSkipped) * 100);
    m_progress->setFormat(tr("Batch %p%"));
    m_progress->setValue(m_batchSkipped * 100);
    m_batchFeedbackTimer->start();
    updateBatchFeedback();
    savePreferences();
    if (m_batchTasks.isEmpty()) {
        endBatch();
        return;
    }
    pumpBatch();
}

void SidboxVideoConverterDialog::pumpBatch()
{
    if (!m_batchBusy || m_batchCancelled || m_closing) return;
    while (m_batchActive < m_batchParallel && m_batchNext < m_batchTasks.size()) {
        BatchTask *task = m_batchTasks.at(m_batchNext++);
        ++m_batchActive;
        startBatchTask(task);
    }
    updateBatchFeedback();
    if (m_batchActive == 0 && m_batchNext == m_batchTasks.size()) endBatch();
}

void SidboxVideoConverterDialog::startBatchTask(BatchTask *task)
{
    if (task->tempInput.isEmpty()) {
        encodeBatchTask(task, task->source);
        return;
    }
    const QUrl url(task->source);
    const QString filename = QFileInfo(url.path()).fileName();
    if (filename.isEmpty() || filename.contains(QLatin1Char('"')) ||
        filename.contains(QLatin1Char('\\')) || filename.contains(QLatin1Char(';')) ||
        filename.contains(QLatin1Char('\n')) || filename.contains(QLatin1Char('\r'))) {
        finishBatchTask(task, false, tr("Unsupported SMB filename"));
        return;
    }
    task->downloading = true;
    task->stage = tr("Downloading");
    task->overallPercent = 0;
    m_batchTable->item(task->row, 1)->setText(task->stage);
    if (task->sourceBytes > 0) {
        task->progressBar->setRange(0, 100);
        task->progressBar->setValue(0);
        task->progressBar->setFormat(tr("0% copied"));
    } else {
        task->progressBar->setRange(0, 0);
        task->progressBar->setFormat(tr("Downloading..."));
    }
    updateBatchFeedback();
    auto *proc = new QProcess(this);
    task->process = proc;
    proc->setWorkingDirectory(QFileInfo(task->tempInput).absolutePath());
    connect(proc, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, [this, task, proc](int code, QProcess::ExitStatus state) {
        if (task->process != proc || m_closing) return;
        task->process = nullptr;
        const QString err = QString::fromLocal8Bit(proc->readAllStandardError()).right(1200);
        proc->deleteLater();
        if (!m_batchCancelled && state == QProcess::NormalExit && code == 0 &&
            QFileInfo(task->tempInput).size() > 0) {
            encodeBatchTask(task, task->tempInput);
        } else {
            finishBatchTask(task, false, m_batchCancelled ? tr("Cancelled") :
                            tr("SMB download failed: %1").arg(err.trimmed()));
        }
    });
    connect(proc, &QProcess::errorOccurred, this, [this, task, proc](QProcess::ProcessError error) {
        if (error == QProcess::FailedToStart && task->process == proc) {
            task->process = nullptr;
            proc->deleteLater();
            finishBatchTask(task, false, tr("Unable to start smbclient"));
        }
    });
    QUrl parent = url;
    const QString remotePath = parent.path();
    parent.setPath(remotePath.left(remotePath.lastIndexOf(QLatin1Char('/'))) + QLatin1Char('/'));
    proc->start(QStandardPaths::findExecutable(QStringLiteral("smbclient")),
        smbArguments(parent, QStringLiteral("get \"%1\" \"%2\"")
            .arg(filename, QFileInfo(task->tempInput).fileName())));
}

void SidboxVideoConverterDialog::encodeBatchTask(BatchTask *task, const QString &input)
{
    if (m_batchCancelled) {
        finishBatchTask(task, false, tr("Cancelled"));
        return;
    }
    task->downloading = false;
    task->stage = tr("Converting");
    task->speed.clear();
    task->percent = 0;
    task->overallPercent = task->tempInput.isEmpty() ? 0 : 20;
    task->progressBar->setRange(0, 0); // Until FFmpeg reports input duration.
    task->progressBar->setFormat(tr("Starting..."));
    m_batchTable->item(task->row, 1)->setText(task->stage);
    m_batchTable->item(task->row, 3)->setText(QStringLiteral("—"));
    updateBatchFeedback();
    auto *proc = new QProcess(this);
    task->process = proc;
    const QString scale = QStringLiteral("fps=%1,scale=%2:%3:force_original_aspect_ratio=decrease,"
        "pad=%2:%3:(ow-iw)/2:(oh-ih)/2")
        .arg(m_batchFps).arg(m_batchSize.width()).arg(m_batchSize.height());
    QStringList args = {QStringLiteral("-hide_banner"), QStringLiteral("-nostdin"),
        QStringLiteral("-y"), QStringLiteral("-i"), input,
        QStringLiteral("-vf"), scale, QStringLiteral("-c:v"), QStringLiteral("mjpeg"),
        QStringLiteral("-q:v"), QString::number(m_batchQuality),
        QStringLiteral("-pix_fmt"), QStringLiteral("yuvj420p")};
    if (m_batchAudioChannels > 0) {
        if (m_batchGain)
            args << QStringLiteral("-af") << QStringLiteral("loudnorm=I=-16:TP=-1.5:LRA=11");
        args << QStringLiteral("-c:a") << QStringLiteral("libmp3lame")
             << QStringLiteral("-b:a") << QStringLiteral("%1k").arg(m_batchBitrate)
             << QStringLiteral("-ar") << QStringLiteral("44100")
             << QStringLiteral("-ac") << QString::number(m_batchAudioChannels);
    } else {
        args << QStringLiteral("-an");
    }
    args << QStringLiteral("-f") << QStringLiteral("avi")
         << QStringLiteral("-nostats")
         << QStringLiteral("-progress") << QStringLiteral("pipe:1")
         << task->tempOutput;
    m_log->appendPlainText(tr("Converting: %1%2")
        .arg(task->name, m_batchAudioChannels > 0 && m_batchGain
            ? QStringLiteral(" [auto gain -16 LUFS]") : QString()));
    connect(proc, &QProcess::readyReadStandardError, this, [this, task, proc]() {
        task->errorTail += QString::fromLocal8Bit(proc->readAllStandardError());
        if (task->durationSeconds <= 0.0) {
            static const QRegularExpression durationRe(
                QStringLiteral(R"(Duration:\s*(\d+):(\d+):(\d+(?:\.\d+)?))"));
            const auto match = durationRe.match(task->errorTail);
            if (match.hasMatch()) {
                task->durationSeconds = match.captured(1).toDouble() * 3600.0 +
                                        match.captured(2).toDouble() * 60.0 +
                                        match.captured(3).toDouble();
                if (task->durationSeconds > 0.0) {
                    task->progressBar->setRange(0, 100);
                    task->progressBar->setValue(0);
                    task->progressBar->setFormat(QStringLiteral("%p%"));
                }
            }
        }
        if (task->errorTail.size() > 2000) task->errorTail = task->errorTail.right(2000);
        updateBatchFeedback();
    });
    connect(proc, &QProcess::readyReadStandardOutput, this, [this, task, proc]() {
        task->progressText += proc->readAllStandardOutput();
        int end = -1;
        while ((end = task->progressText.indexOf('\n')) >= 0) {
            const QByteArray line = task->progressText.left(end).trimmed();
            task->progressText.remove(0, end + 1);
            const int separator = line.indexOf('=');
            if (separator < 0) continue;
            const QByteArray key = line.left(separator);
            const QByteArray value = line.mid(separator + 1);
            if (key == "out_time") {
                const QList<QByteArray> parts = value.split(':');
                if (parts.size() == 3) {
                    bool ok = false;
                    const double seconds = parts.at(0).toDouble() * 3600.0 +
                                           parts.at(1).toDouble() * 60.0 +
                                           parts.at(2).toDouble(&ok);
                    if (ok) task->encodedSeconds = qMax(0.0, seconds);
                }
            } else if (key == "speed") {
                task->speed = QString::fromLatin1(value);
            } else if (key == "progress" && value == "end") {
                task->encodedSeconds = task->durationSeconds;
            }
        }
        updateBatchFeedback();
    });
    connect(proc, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, [this, task, proc](int code, QProcess::ExitStatus state) {
        if (task->process != proc || m_closing) return;
        task->process = nullptr;
        proc->deleteLater();
        bool success = state == QProcess::NormalExit && code == 0 && !m_batchCancelled &&
                       QFileInfo(task->tempOutput).size() > 0;
        QString message;
        if (success) {
            if (QFile::exists(task->output)) {
                success = false;
                message = tr("Skipped: target appeared during conversion");
            } else if (!QFile::rename(task->tempOutput, task->output)) {
                success = false;
                message = tr("Could not install AVI in target folder");
            } else {
                message = tr("Saved: %1").arg(task->output);
            }
        } else {
            message = m_batchCancelled ? tr("Cancelled") :
                      tr("FFmpeg failed: %1").arg(task->errorTail.trimmed().right(400));
        }
        finishBatchTask(task, success, message);
    });
    connect(proc, &QProcess::errorOccurred, this, [this, task, proc](QProcess::ProcessError error) {
        if (error == QProcess::FailedToStart && task->process == proc) {
            task->process = nullptr;
            proc->deleteLater();
            finishBatchTask(task, false, tr("Unable to start FFmpeg"));
        }
    });
    proc->start(QStandardPaths::findExecutable(QStringLiteral("ffmpeg")), args);
}

void SidboxVideoConverterDialog::finishBatchTask(BatchTask *task, bool success,
                                                  const QString &detail)
{
    if (!task->tempInput.isEmpty()) QFile::remove(task->tempInput);
    if (!task->tempOutput.isEmpty()) QFile::remove(task->tempOutput);
    task->finished = true;
    task->downloading = false;
    task->overallPercent = 100;
    task->stage = success ? tr("Saved") : (m_batchCancelled ? tr("Cancelled") : tr("Failed"));
    m_batchTable->item(task->row, 1)->setText(task->stage);
    m_batchTable->item(task->row, 1)->setToolTip(detail);
    task->progressBar->setRange(0, 100);
    task->progressBar->setValue(success ? 100 : task->percent);
    task->progressBar->setFormat(success ? tr("Done") : task->stage);
    m_log->appendPlainText(QStringLiteral("%1: %2 - %3")
        .arg(success ? tr("OK") : tr("FAILED"), task->name, detail));
    ++m_batchDone;
    if (success) ++m_batchSucceeded;
    else if (!m_batchCancelled) ++m_batchFailed;
    if (m_batchActive > 0) --m_batchActive;
    updateBatchFeedback();
    if (m_batchCancelled) {
        if (m_batchActive == 0) endBatch();
    } else {
        QTimer::singleShot(0, this, [this]() { pumpBatch(); });
    }
}

void SidboxVideoConverterDialog::endBatch()
{
    m_batchFeedbackTimer->stop();
    const bool hadActiveQueue = m_batchBusy;
    m_batchBusy = false;
    m_batchPreparing = false;
    m_convert->setEnabled(true);
    m_batchConvert->setEnabled(true);
    m_cancel->setEnabled(false);
    m_sourceView->parentWidget()->setEnabled(true);
    m_targetView->parentWidget()->setEnabled(true);
    m_parallel->setEnabled(true);
    m_resolution->setEnabled(true);
    m_fps->setEnabled(true);
    m_quality->setEnabled(true);
    m_audioOutput->setEnabled(true);
    const bool audioEnabled = m_audioOutput->currentData().toInt() > 0;
    m_bitrate->setEnabled(audioEnabled);
    m_audioGain->setEnabled(audioEnabled);
    if (!hadActiveQueue) {
        m_progress->setRange(0, 100);
        m_progress->setValue(0);
        m_status->setText(m_batchCancelled ? tr("Batch cancelled") : tr("Ready"));
        return;
    }
    updateBatchFeedback();
    if (!m_batchCancelled) m_progress->setValue(m_progress->maximum());
    m_status->setText(m_batchCancelled ? tr("Batch cancelled: %1 saved").arg(m_batchSucceeded) :
        tr("Batch complete: %1 saved, %2 skipped, %3 failed")
            .arg(m_batchSucceeded).arg(m_batchSkipped).arg(m_batchFailed));
    // Keep completed job metadata until the next batch, but do not retain any
    // process handles, input copies or AVI temporary files.
}

void SidboxVideoConverterDialog::updateBatchFeedback()
{
    if (!m_batchPanel->isVisible()) return;
    const int total = m_batchTasks.size() + m_batchSkipped;
    int work = (m_batchSkipped + m_batchDone) * 100;
    for (BatchTask *task : m_batchTasks) {
        if (task->finished) continue;
        if (!task->downloading && task->durationSeconds > 0.0) {
            task->percent = qBound(0, int(task->encodedSeconds * 100.0 /
                                             task->durationSeconds), 99);
            task->overallPercent = task->tempInput.isEmpty() ? task->percent :
                                   20 + (task->percent * 80 / 100);
            task->progressBar->setRange(0, 100);
            task->progressBar->setValue(task->percent);
            task->progressBar->setFormat(QStringLiteral("%p%"));
        } else if (!task->downloading && task->encodedSeconds > 0.0) {
            task->progressBar->setFormat(tr("%1 s encoded").arg(
                task->encodedSeconds, 0, 'f', 0));
        }
        if (!task->speed.isEmpty())
            m_batchTable->item(task->row, 3)->setText(task->speed);
        work += task->overallPercent;
    }
    m_progress->setRange(0, qMax(1, total) * 100);
    m_progress->setValue(qBound(0, work, m_progress->maximum()));
    m_batchSummary->setText(tr("%1/%2 finished  |  %3 active  |  %4 saved  |  %5 skipped  |  %6 failed")
        .arg(m_batchDone + m_batchSkipped).arg(total).arg(m_batchActive)
        .arg(m_batchSucceeded).arg(m_batchSkipped).arg(m_batchFailed));
    if (m_batchBusy && !m_batchCancelled)
        m_status->setText(tr("%1/%2 complete").arg(m_batchDone + m_batchSkipped).arg(total));
}

void SidboxVideoConverterDialog::cancelBatch()
{
    m_batchCancelled = true;
    m_status->setText(tr("Cancelling batch..."));
    for (int i = m_batchNext; i < m_batchTasks.size(); ++i)
        m_batchTable->item(m_batchTasks.at(i)->row, 1)->setText(tr("Not started"));
    if (m_batchListing) {
        m_batchListing->kill();
        return;
    }
    if (!m_batchBusy) return;
    for (int i = 0; i < m_batchNext; ++i) {
        BatchTask *task = m_batchTasks.at(i);
        if (!task->process) continue;
        if (task->process->state() != QProcess::NotRunning) {
            task->process->kill();
        } else {
            QProcess *process = task->process;
            task->process = nullptr;
            process->deleteLater();
            finishBatchTask(task, false, tr("Cancelled"));
        }
    }
    if (!m_batchActive) endBatch();
}

void SidboxVideoConverterDialog::savePreferences()
{
    QSettings settings(QStringLiteral("Sidbox"), QStringLiteral("SidboxIDE"));
    settings.beginGroup(QStringLiteral("tools/videoConverter"));
    settings.setValue(QStringLiteral("sourceDirectory"), m_sourceDirectory);
    settings.setValue(QStringLiteral("targetDirectory"), m_targetDirectory);
    settings.setValue(QStringLiteral("resolution"), m_resolution->currentData().toSize());
    settings.setValue(QStringLiteral("fps"), m_fps->currentData().toInt());
    settings.setValue(QStringLiteral("quality"), m_quality->currentData().toInt());
    settings.setValue(QStringLiteral("bitrate"), m_bitrate->currentData().toInt());
    settings.setValue(QStringLiteral("audioChannels"), m_audioOutput->currentData().toInt());
    // Keep the old key for compatibility with older IDE builds.
    settings.setValue(QStringLiteral("audio"), m_audioOutput->currentData().toInt() > 0);
    settings.setValue(QStringLiteral("audioGain"), m_audioGain->isChecked());
    settings.setValue(QStringLiteral("parallel"), m_parallel->currentData().toInt());
    settings.setValue(QStringLiteral("splitter"), m_splitter->saveState());
    static_cast<SidboxPersistentColumnsHeader *>(m_sourceView->header())->applyRemembered();
    static_cast<SidboxPersistentColumnsHeader *>(m_targetView->header())->applyRemembered();
    settings.setValue(QStringLiteral("sourceColumns"), m_sourceView->header()->saveState());
    settings.setValue(QStringLiteral("targetColumns"), m_targetView->header()->saveState());
    settings.setValue(QStringLiteral("geometry"), saveGeometry());
    settings.endGroup();
}

void SidboxVideoConverterDialog::closeEvent(QCloseEvent *event)
{
    if ((m_batchBusy || m_batchPreparing ||
        m_ffmpeg->state() != QProcess::NotRunning ||
        (m_smbDownload && m_smbDownload->state() != QProcess::NotRunning)) &&
        QMessageBox::question(this, tr("Cancel conversion?"),
            tr("A transfer or conversion is still running. Cancel and close?"),
            QMessageBox::Yes | QMessageBox::No, QMessageBox::No) != QMessageBox::Yes) {
        event->ignore();
        return;
    }
    m_closing = true;
    if (m_batchListing) {
        disconnect(m_batchListing, nullptr, this, nullptr);
        m_batchListing->kill();
        m_batchListing->waitForFinished(1000);
        m_batchListing->deleteLater();
        m_batchListing = nullptr;
    }
    for (BatchTask *task : m_batchTasks) {
        if (task->process) {
            disconnect(task->process, nullptr, this, nullptr);
            task->process->kill();
            task->process->waitForFinished(1000);
            task->process->deleteLater();
            task->process = nullptr;
        }
        if (!task->tempInput.isEmpty()) QFile::remove(task->tempInput);
        if (!task->tempOutput.isEmpty()) QFile::remove(task->tempOutput);
        delete task;
    }
    m_batchTasks.clear();
    m_batchBusy = false;
    m_batchPreparing = false;
    if (m_ffmpeg->state() != QProcess::NotRunning) {
        m_ffmpeg->kill();
        m_ffmpeg->waitForFinished(2000);
    }
    if (m_smbDownload && m_smbDownload->state() != QProcess::NotRunning) {
        m_smbDownload->kill();
        m_smbDownload->waitForFinished(2000);
    }
    if (m_smbListing && m_smbListing->state() != QProcess::NotRunning) {
        m_smbListing->kill();
        m_smbListing->waitForFinished(2000);
    }
    if (!m_tempOutput.isEmpty()) QFile::remove(m_tempOutput);
    if (!m_remoteTempInput.isEmpty()) QFile::remove(m_remoteTempInput);
    savePreferences();
    QDialog::closeEvent(event);
}
