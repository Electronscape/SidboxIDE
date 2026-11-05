#ifndef SIDBOXVIDEOCONVERTER_H
#define SIDBOXVIDEOCONVERTER_H

#include <QDialog>
#include <QByteArray>
#include <QString>
#include <QStringList>
#include <QSize>
#include <QVector>
#include <QUrl>

class QCheckBox;
class QComboBox;
class QFileSystemModel;
class QLabel;
class QPlainTextEdit;
class QProcess;
class QProgressBar;
class QTableWidget;
class QTimer;
class QPushButton;
class QSplitter;
class QTreeView;
class QStandardItemModel;
class QSortFilterProxyModel;
class QTemporaryFile;
class QModelIndex;
class QCloseEvent;

// Standalone desktop tool. No project or game-designer dependencies.
class SidboxVideoConverterDialog final : public QDialog
{
public:
    explicit SidboxVideoConverterDialog(QWidget *parent = nullptr);
    ~SidboxVideoConverterDialog() override;

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    void navigateSource(const QString &directory);
    void selectSource(const QModelIndex &index);
    void showRemoteDirectory(const QUrl &url);
    void startRemoteListing(const QUrl &url);
    QStringList smbArguments(const QUrl &url, const QString &command) const;
    void beginFFmpeg(const QString &inputFile);
    void probeDuration(const QString &source);
    void startRemoteDownload();
    bool remoteSourceSelected() const;
    void navigateTarget(const QString &directory);
    void convertSelected();
    void savePreferences();
    struct BatchFile {
        QString source;
        QString name;
        qint64 sourceBytes = 0;
    };
    struct BatchTask {
        QString source;
        QString name;
        QString output;
        QString tempOutput;
        QString tempInput;
        QProcess *process = nullptr;
        QString errorTail;
        QByteArray progressText;
        QString speed;
        QString stage;
        qint64 sourceBytes = 0;
        double durationSeconds = 0.0;
        double encodedSeconds = 0.0;
        int percent = 0;
        int overallPercent = 0;
        int row = -1;
        bool finished = false;
        bool downloading = false;
        QProgressBar *progressBar = nullptr;
    };
    void convertBatchFolder();
    void prepareBatch(const QString &folder);
    void beginBatch(const QVector<BatchFile> &files, const QString &folder, bool selectedFiles = false);
    void pumpBatch();
    void startBatchTask(BatchTask *task);
    void encodeBatchTask(BatchTask *task, const QString &input);
    void finishBatchTask(BatchTask *task, bool success, const QString &detail);
    void endBatch();
    void cancelBatch();
    void updateBatchFeedback();

    QFileSystemModel *m_sourceModel = nullptr;
    QSortFilterProxyModel *m_sourceSort = nullptr;
    QStandardItemModel *m_remoteModel = nullptr;
    QProcess *m_smbListing = nullptr;
    QProcess *m_smbDownload = nullptr;
    QTemporaryFile *m_smbCredentials = nullptr;
    QString m_smbCredentialIdentity;
    QString m_remoteTempInput;
    QString m_pendingRemoteLocation;
    bool m_smbPasswordPrompted = false;
    bool m_remoteCancelled = false;
    QFileSystemModel *m_targetModel = nullptr;
    QSortFilterProxyModel *m_targetSort = nullptr;
    QTreeView *m_sourceView = nullptr;
    QTreeView *m_targetView = nullptr;
    QComboBox *m_sourcePath = nullptr;
    QComboBox *m_targetPath = nullptr;
    QLabel *m_selectedLabel = nullptr;
    QLabel *m_status = nullptr;
    QComboBox *m_resolution = nullptr;
    QComboBox *m_fps = nullptr;
    QComboBox *m_quality = nullptr;
    QComboBox *m_bitrate = nullptr;
    QComboBox *m_audioOutput = nullptr;
    QCheckBox *m_audioGain = nullptr;
    QSplitter *m_splitter = nullptr;
    QPushButton *m_convert = nullptr;
    QPushButton *m_batchConvert = nullptr;
    QComboBox *m_parallel = nullptr;
    QProcess *m_batchListing = nullptr;
    QWidget *m_batchPanel = nullptr;
    QTableWidget *m_batchTable = nullptr;
    QLabel *m_batchSummary = nullptr;
    QTimer *m_batchFeedbackTimer = nullptr;
    QVector<BatchTask *> m_batchTasks;
    int m_batchNext = 0;
    int m_batchActive = 0;
    int m_batchDone = 0;
    int m_batchSucceeded = 0;
    int m_batchSkipped = 0;
    int m_batchFailed = 0;
    int m_batchParallel = 2;
    int m_batchFps = 15;
    int m_batchQuality = 6;
    int m_batchBitrate = 96;
    QSize m_batchSize;
    int m_batchAudioChannels = 1;
    bool m_batchGain = false;
    bool m_batchBusy = false;
    bool m_batchPreparing = false;
    bool m_batchCancelled = false;
    QPushButton *m_cancel = nullptr;
    QProgressBar *m_progress = nullptr;
    QPlainTextEdit *m_log = nullptr;
    QProcess *m_ffmpeg = nullptr;
    QString m_sourceDirectory;
    QString m_targetDirectory;
    QString m_selectedSource;
    QString m_tempOutput;
    QString m_finalOutput;
    QByteArray m_progressText;
    double m_durationSeconds = 0.0;
    bool m_closing = false;
};

#endif
