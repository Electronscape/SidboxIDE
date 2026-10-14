#ifndef SIDBOX_GAMEAUDIO_H
#define SIDBOX_GAMEAUDIO_H

#include <QWidget>
#include <QString>
#include <QtGlobal>
#include <functional>

class QCheckBox;
class QComboBox;
class QFormLayout;
class QLabel;
class QPushButton;
class QSpinBox;
#ifdef SIDBOX_HAS_QT_MULTIMEDIA
class QMediaPlayer;
class QAudioOutput;
#endif

// Host-side resource metadata only. No hardware API is called here.
// The design document stores settings; V1 code generation is a later stage.
struct SidboxAudioSettings {
    int channel = 0;        // sound channel 0..7 (SIDBOX V1 examples)
    int frequency = 22050;  // new SFX: 22050 Hz; 0 = WAV source rate
    int volume = 255;       // V1 normal range 0..255, up to 1024 for overdrive
    int pan = 0;            // -127 (left) .. +127 (right)
    bool loop = false;
    int loopStart = 0;      // sample frames, not arbitrary bytes
    int loopLength = 0;     // sample frames, 0 = use remaining when generating
    int subsong = 0;        // music_play(path, uint8_t subsong)
};

struct SidboxAudioInfo {
    QString description;
    QString warning;
    bool isWave = false;
    bool canonicalV1Wave = false;
    quint32 sampleRate = 0;
    quint16 channels = 0;
    quint16 bitsPerSample = 0;
    quint64 frames = 0;
    quint64 fileBytes = 0;
};

// Reads only small headers; does not decode or load full music/audio assets.
SidboxAudioInfo sidboxInspectAudio(const QString &path);

// Self-contained, theme-inheriting editor used by Game Designer's properties pane.
class SidboxGameAudioPanel final : public QWidget
{
public:
    explicit SidboxGameAudioPanel(QWidget *parent = nullptr);
    ~SidboxGameAudioPanel() override;

    std::function<void(const SidboxAudioSettings &)> settingsChanged;
    void showAudio(const QString &kind, const QString &absolutePath,
                   const SidboxAudioSettings &settings);
    void clearAudio();

private:
    SidboxAudioSettings settings() const;
    void emitSettings();
    QFormLayout *m_form = nullptr;
    QSpinBox *m_channel = nullptr;
    QSpinBox *m_frequency = nullptr;
    QSpinBox *m_volume = nullptr;
    QSpinBox *m_pan = nullptr;
    QSpinBox *m_loopStart = nullptr;
    QSpinBox *m_loopLength = nullptr;
    QSpinBox *m_subsong = nullptr;
    QCheckBox *m_loop = nullptr;
    QLabel *m_info = nullptr;
    QLabel *m_warning = nullptr;
    QLabel *m_hint = nullptr;
    QLabel *m_previewStatus = nullptr;
    QPushButton *m_preview = nullptr;
    QPushButton *m_stop = nullptr;
    bool m_updating = false;
    QString m_currentPath;
    QString m_currentKind;
    QString m_previewRateDescription;
#ifdef SIDBOX_HAS_QT_MULTIMEDIA
    QMediaPlayer *m_player = nullptr;
    QAudioOutput *m_audioOutput = nullptr;
#endif
};

#endif // SIDBOX_GAMEAUDIO_H
