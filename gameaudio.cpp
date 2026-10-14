#include "gameaudio.h"

#include <QCheckBox>
#include <QFile>
#include <QFileInfo>
#include <QFont>
#include <QFrame>
#include <QFormLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QSignalBlocker>
#include <QSpinBox>
#include <QUrl>
#include <QVBoxLayout>
#include <QVector>
#include <QtMath>
#ifdef SIDBOX_HAS_QT_MULTIMEDIA
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QMediaDevices>
#include <QAudioDevice>
#endif

namespace {
quint16 le16(const char *p)
{
    return quint16(quint8(p[0])) | (quint16(quint8(p[1])) << 8);
}
quint32 le32(const char *p)
{
    return quint32(quint8(p[0])) | (quint32(quint8(p[1])) << 8)
         | (quint32(quint8(p[2])) << 16) | (quint32(quint8(p[3])) << 24);
}
}

SidboxAudioInfo sidboxInspectAudio(const QString &path)
{
    SidboxAudioInfo info;
    const QFileInfo fi(path);
    if (!fi.isFile()) {
        info.warning = QObject::tr("Missing resource file. The reference is preserved in the design.");
        return info;
    }
    info.fileBytes = quint64(fi.size());
    const QString suffix = fi.suffix().toLower();
    info.isWave = (suffix == QStringLiteral("wav"));
    if (!info.isWave) {
        QFile file(path);
        QByteArray header;
        if (file.open(QIODevice::ReadOnly)) header = file.read(1200);
        QString format = suffix.toUpper();
        if (header.startsWith("Extended Module: ")) format = QStringLiteral("XM module");
        else if (header.size() >= 48 && header.mid(44, 4) == "SCRM") format = QStringLiteral("S3M module");
        else if (header.startsWith("MMD0") || header.startsWith("MMD1") || header.startsWith("MMD2"))
            format = QStringLiteral("MED module");
        else if (header.size() >= 1084 &&
                 (header.mid(1080, 4) == "M.K." || header.mid(1080, 4) == "M!K!" ||
                  header.mid(1080, 4) == "4CHN" || header.mid(1080, 4) == "8CHN"))
            format = QStringLiteral("MOD module");
        info.description = QObject::tr("%1 | %2 bytes | file-backed music reference")
                               .arg(format).arg(qulonglong(info.fileBytes));
        info.warning = QObject::tr("SIDBOX firmware handles game playback. Host preview is optional "
                                    "and requires an FFmpeg backend with a compatible decoder. "
                                    "Call music_update() in the game loop.");
        return info;
    }

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        info.warning = QObject::tr("Cannot read WAV header.");
        return info;
    }
    const QByteArray riff = file.read(12);
    if (riff.size() != 12 || riff.left(4) != "RIFF" || riff.mid(8, 4) != "WAVE") {
        info.warning = QObject::tr("Not a valid RIFF/WAVE file.");
        return info;
    }
    bool hasFmt = false, hasData = false;
    quint16 formatCode = 0, blockAlign = 0;
    quint64 dataBytes = 0;
    qint64 dataOffset = -1;
    // Bounded header traversal: inspect metadata without reading sample data.
    for (int chunk = 0; chunk < 256 && file.pos() + 8 <= file.size(); ++chunk) {
        const QByteArray head = file.read(8);
        if (head.size() != 8) break;
        const quint32 bytes = le32(head.constData() + 4);
        const qint64 contentStart = file.pos();
        if (quint64(bytes) > quint64(file.size() - contentStart)) break;
        if (head.left(4) == "fmt " && bytes >= 16 && !hasFmt) {
            const QByteArray fmt = file.read(16);
            if (fmt.size() == 16) {
                formatCode = le16(fmt.constData());
                info.channels = le16(fmt.constData() + 2);
                info.sampleRate = le32(fmt.constData() + 4);
                blockAlign = le16(fmt.constData() + 12);
                info.bitsPerSample = le16(fmt.constData() + 14);
                hasFmt = true;
            }
        } else if (head.left(4) == "data" && !hasData) {
            hasData = true;
            dataBytes = bytes;
            dataOffset = contentStart;
        }
        // The extra pad byte is mandated for odd-length RIFF chunks.
        const qint64 next = contentStart + qint64(bytes) + (bytes & 1u);
        if (next > file.size() || !file.seek(next)) break;
        if (hasFmt && hasData) break;
    }
    if (!hasFmt || !hasData || !blockAlign || !info.sampleRate) {
        info.warning = QObject::tr("Incomplete WAV: missing usable fmt/data chunks.");
        return info;
    }
    info.frames = dataBytes / blockAlign;
    const double seconds = double(info.frames) / double(info.sampleRate);
    info.description = QObject::tr("PCM %1-bit | %2 channel(s) | %3 Hz | %4 s | %5 bytes")
        .arg(int(info.bitsPerSample)).arg(int(info.channels)).arg(qulonglong(info.sampleRate))
        .arg(seconds, 0, 'f', 2).arg(qulonglong(info.fileBytes));
    // V1 LoadSFX reads a packed 44-byte WAV header then immediately reads the
    // sample payload. More general WAV layouts are valid WAV, but NOT safe for
    // that specific legacy loader without conversion or loader changes.
    info.canonicalV1Wave = formatCode == 1 && info.channels == 1
        && (info.bitsPerSample == 8 || info.bitsPerSample == 16)
        && info.sampleRate <= 65535 && dataOffset == 44
        && le32(riff.constData() + 4) <= quint64(qMax<qint64>(0, file.size() - 8));
    if (!info.canonicalV1Wave) {
        info.warning = QObject::tr("V1 LoadSFX compatibility warning: its current loader assumes "
            "44-byte RIFF PCM with data at byte 44, mono 8/16-bit and sample rate <= 65535. "
            "Convert the WAV before using it on hardware.");
    } else if (info.bitsPerSample == 16) {
        info.warning = QObject::tr("Canonical WAV layout. Match the V1 sound_assign bitsize "
                                   "to 16-bit when generating code (8-bit uses bitsize 0).");
    } else {
        info.warning = QObject::tr("V1 canonical PCM WAV layout detected. Check audio fidelity on hardware.");
    }
    return info;
}

SidboxGameAudioPanel::SidboxGameAudioPanel(QWidget *parent) : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 4, 0, 4);
    layout->setSpacing(5);
    auto *heading = new QLabel(tr("AUDIO SETTINGS  |  V1"), this);
    QFont f = heading->font(); f.setBold(true); heading->setFont(f);
    layout->addWidget(heading);
    m_info = new QLabel(this);
    m_info->setWordWrap(true);
    m_info->setTextInteractionFlags(Qt::TextSelectableByMouse);
    layout->addWidget(m_info);
    m_warning = new QLabel(this);
    m_warning->setWordWrap(true);
    m_warning->setTextInteractionFlags(Qt::TextSelectableByMouse);
    layout->addWidget(m_warning);

    auto *form = new QFormLayout;
    m_form = form;
    m_channel = new QSpinBox(this); m_channel->setRange(0, 7);
    m_frequency = new QSpinBox(this); m_frequency->setRange(0, 65535);
    m_frequency->setSpecialValueText(tr("WAV rate"));
    m_volume = new QSpinBox(this); m_volume->setRange(0, 1024); // V1 examples deliberately use >255 overdrive
    m_pan = new QSpinBox(this); m_pan->setRange(-127, 127);
    m_loop = new QCheckBox(tr("Loop sample"), this);
    m_loopStart = new QSpinBox(this); m_loopStart->setRange(0, 2147483647);
    m_loopLength = new QSpinBox(this); m_loopLength->setRange(0, 2147483647);
    m_loopLength->setSpecialValueText(tr("Remaining"));
    m_subsong = new QSpinBox(this); m_subsong->setRange(0, 255);
    form->addRow(tr("Channel"), m_channel);
    form->addRow(tr("Playback Hz"), m_frequency);
    form->addRow(tr("Volume"), m_volume);
    form->addRow(tr("Panning"), m_pan);
    form->addRow(QString(), m_loop);
    form->addRow(tr("Loop start"), m_loopStart);
    form->addRow(tr("Loop length"), m_loopLength);
    form->addRow(tr("Subsong"), m_subsong);
    layout->addLayout(form);
    m_hint = new QLabel(this);
    m_hint->setWordWrap(true);
    layout->addWidget(m_hint);

    auto *previewRow = new QHBoxLayout;
    m_preview = new QPushButton(tr("Preview audio"), this);
    m_stop = new QPushButton(tr("Stop"), this);
    previewRow->addWidget(m_preview);
    previewRow->addWidget(m_stop);
    layout->addLayout(previewRow);
    m_previewStatus = new QLabel(this);
    m_previewStatus->setWordWrap(true);
    m_previewStatus->setTextInteractionFlags(Qt::TextSelectableByMouse);
    layout->addWidget(m_previewStatus);
#ifdef SIDBOX_HAS_QT_MULTIMEDIA
    // QMediaPlayer can decode common WAV variants which QSoundEffect rejects.
    // Modules are a best-effort host preview, depending on local FFmpeg codecs.
    m_player = new QMediaPlayer(this);
    m_audioOutput = new QAudioOutput(this);
    m_player->setAudioOutput(m_audioOutput);
    connect(m_preview, &QPushButton::clicked, this, [this]() {
        if (m_currentPath.isEmpty() || !QFileInfo(m_currentPath).isFile()) return;
        if (QMediaDevices::defaultAudioOutput().isNull()) {
            m_previewStatus->setText(tr("No default audio output device. Check PipeWire / Windows sound settings."));
            return;
        }
        m_player->stop();
        m_audioOutput->setVolume(qBound(0.0, double(m_volume->value()) / 255.0, 1.0));
        m_player->setSource(QUrl::fromLocalFile(m_currentPath));
        m_player->setPlaybackRate(1.0);
        m_previewRateDescription = tr("original playback rate");
        // This is a host PREVIEW only. Qt's playbackRate adjusts speed and may
        // preserve pitch depending on backend; it is not a SIDBOX DAC emulation.
        if (m_currentKind == QStringLiteral("sound")) {
            const SidboxAudioInfo info = sidboxInspectAudio(m_currentPath);
            if (info.isWave && info.sampleRate && m_frequency->value() > 0) {
                const double speed = double(m_frequency->value()) / double(info.sampleRate);
                m_player->setPlaybackRate(speed);
                m_previewRateDescription = tr("requested %1 Hz / WAV %2 Hz ≈ %3× speed (host approximation)")
                    .arg(m_frequency->value()).arg(info.sampleRate).arg(speed, 0, 'f', 3);
            }
        }
        m_previewStatus->setText(tr("Opening audio preview... %1").arg(m_previewRateDescription));
        m_player->play();
    });
    connect(m_player, &QMediaPlayer::errorOccurred, this,
        [this](QMediaPlayer::Error, const QString &message) {
            m_previewStatus->setText(tr("Preview unavailable: %1").arg(message));
        });
    connect(m_player, &QMediaPlayer::playbackStateChanged, this,
        [this](QMediaPlayer::PlaybackState state) {
            if (state == QMediaPlayer::PlayingState)
                m_previewStatus->setText(tr("Playing through host audio output: %1")
                    .arg(m_previewRateDescription));
            else if (state == QMediaPlayer::StoppedState && m_player->error() == QMediaPlayer::NoError)
                m_previewStatus->setText(tr("Stopped"));
        });
    connect(m_stop, &QPushButton::clicked, m_player, &QMediaPlayer::stop);
#else
    m_preview->setToolTip(tr("Audio preview requires optional Qt6 Multimedia at build time."));
    m_stop->setToolTip(m_preview->toolTip());
#endif
    for (QSpinBox *spin : {m_channel, m_frequency, m_volume, m_pan,
                           m_loopStart, m_loopLength, m_subsong})
        connect(spin, qOverload<int>(&QSpinBox::valueChanged), this,
                [this](int) { emitSettings(); });
    connect(m_loop, &QCheckBox::toggled, this, [this](bool value) {
        m_loopStart->setEnabled(value);
        m_loopLength->setEnabled(value);
        emitSettings();
    });
    clearAudio();
}

SidboxGameAudioPanel::~SidboxGameAudioPanel() = default;

SidboxAudioSettings SidboxGameAudioPanel::settings() const
{
    SidboxAudioSettings s;
    s.channel = m_channel->value();
    s.frequency = m_frequency->value();
    s.volume = m_volume->value();
    s.pan = m_pan->value();
    s.loop = m_loop->isChecked();
    s.loopStart = m_loopStart->value();
    s.loopLength = m_loopLength->value();
    s.subsong = m_subsong->value();
    return s;
}

void SidboxGameAudioPanel::emitSettings()
{
    if (!m_updating && settingsChanged) settingsChanged(settings());
}

void SidboxGameAudioPanel::clearAudio()
{
    m_updating = true;
#ifdef SIDBOX_HAS_QT_MULTIMEDIA
    if (m_player) m_player->stop();
#endif
    m_currentPath.clear(); m_currentKind.clear(); m_previewRateDescription.clear();
    m_info->clear(); m_warning->clear(); m_hint->clear(); m_previewStatus->clear();
    m_preview->setEnabled(false); m_stop->setEnabled(false);
    m_updating = false;
    hide();
}

void SidboxGameAudioPanel::showAudio(const QString &kind, const QString &path,
                                    const SidboxAudioSettings &settings)
{
    m_updating = true;
#ifdef SIDBOX_HAS_QT_MULTIMEDIA
    if (m_player && (m_currentPath != path || m_currentKind != kind)) m_player->stop();
#endif
    m_currentPath = path; m_currentKind = kind;
    m_previewStatus->clear();
    const bool sound = kind == QStringLiteral("sound");
    m_channel->setValue(qBound(0, settings.channel, 7));
    m_frequency->setValue(qBound(0, settings.frequency, 65535));
    m_volume->setValue(qBound(0, settings.volume, 1024));
    m_pan->setValue(qBound(-127, settings.pan, 127));
    m_loop->setChecked(settings.loop);
    m_loopStart->setValue(qBound(0, settings.loopStart, 2147483647));
    m_loopLength->setValue(qBound(0, settings.loopLength, 2147483647));
    m_subsong->setValue(qBound(0, settings.subsong, 255));
    // QFormLayout owns a separate label for each row. Hide labels too or
    // switching between Sound and Music leaves orphaned captions behind.
    const auto showRow = [this](QWidget *field, bool visible) {
        field->setVisible(visible);
        if (auto *label = m_form->labelForField(field)) label->setVisible(visible);
    };
    for (QWidget *w : {static_cast<QWidget *>(m_channel), static_cast<QWidget *>(m_frequency),
                      static_cast<QWidget *>(m_volume), static_cast<QWidget *>(m_pan),
                      static_cast<QWidget *>(m_loop), static_cast<QWidget *>(m_loopStart),
                      static_cast<QWidget *>(m_loopLength)}) showRow(w, sound);
    m_loopStart->setEnabled(sound && settings.loop);
    m_loopLength->setEnabled(sound && settings.loop);
    showRow(m_subsong, !sound);
    const SidboxAudioInfo info = sidboxInspectAudio(path);
    m_info->setText(info.description.isEmpty() ? tr("No readable audio metadata") : info.description);
    m_warning->setText(info.warning);
    m_hint->setText(sound
        ? tr("Settings are saved in the design only; V1 SFX loading/assignment code comes in Stage 55. "
             "Channel and panning match the V1 API; loop offsets use PCM frames. "
             "Volumes above 255 are overdrive and may clip.")
        : tr("Subsong is passed to music_play(filename, subsong). "
             "Remember music_update() in your game loop. Host module preview depends on FFmpeg codec support; "
             "it is NOT the SIDBOX mixer."));
#ifdef SIDBOX_HAS_QT_MULTIMEDIA
    const QString suffix = QFileInfo(path).suffix().toLower();
    const bool previewEnabled = QFileInfo(path).isFile() && (info.isWave ||
        QStringList{QStringLiteral("mod"), QStringLiteral("xm"), QStringLiteral("s3m"),
            QStringLiteral("med"),QStringLiteral("tfmx")}.contains(suffix));
#else
    const bool previewEnabled = false;
#endif
    m_preview->setVisible(true);
    m_stop->setVisible(true);
    m_preview->setEnabled(previewEnabled);
    m_previewStatus->setText(previewEnabled ? tr("Host preview (best effort)")
        : tr("Preview unavailable for this format or build."));
    m_stop->setEnabled(previewEnabled);
    m_updating = false;
    show();
}
