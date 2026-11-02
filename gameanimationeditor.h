#ifndef SIDBOX_GAMEANIMATIONEDITOR_H
#define SIDBOX_GAMEANIMATIONEDITOR_H

#include <QDialog>
#include <QImage>
#include <QMap>
#include <QJsonArray>
#include <QJsonObject>
#include <QStringList>
#include <QVector>
#include "idetheme.h"
#include <functional>

class QListWidget;
class QComboBox;
class QButtonGroup;
class QSpinBox;
class QScrollArea;
class QCheckBox;
class QLabel;
class QPushButton;
class QTimer;
class QWidget;

// Design-time V1 sprite-atlas animation editor. The .sbanim file contains
// frame INDEXES, not bitmaps. It never touches the original PNG/PPB.
class SidboxPlayerAnimationEditor final : public QDialog
{
public:
    SidboxPlayerAnimationEditor(const QString &atlasFile,
                               const QString &animationFile,
                               const QString &defaultHeaderFile,
                               int cellWidth, int cellHeight,
                               QWidget *parent = nullptr,
                               const IDETheme &theme = defaultIDETheme(),
                               const QJsonObject &playerProfile = QJsonObject(),
                               int worldTileSize = 16,
                               const QString &worldName = QString());
    ~SidboxPlayerAnimationEditor() override;
    QString animationFile() const { return m_file; }
    bool isUsable() const { return !m_atlas.isNull(); }
    int cellWidth() const { return m_cellW; }
    int cellHeight() const { return m_cellH; }

private:
    struct Clip {
        QVector<int> frames;
        QVector<int> frameMs; // Per-position millisecond duration; paired with frames.
        int durationMs = 100; // Five 50 Hz VBlanks
        bool loop = true;
    };
    IDETheme m_theme;
    QString m_file;
    QString m_defaultHeaderFile;
    QString m_atlasFile;
    QImage m_atlas;
    QStringList m_states;
    QMap<QString, Clip> m_clips;
    int m_cellW = 32, m_cellH = 32;
    int m_mode = 2;
    bool m_mirror = true;
    bool m_autoState = true;
    bool m_refreshing = false;
    int m_savedFootX = -1, m_savedFootY = -1;
    int m_savedBoxX = 0, m_savedBoxY = 0, m_savedBoxW = -1, m_savedBoxH = -1;
    bool m_savedShowFoot = true, m_savedShowBox = true;
    int m_selectedAtlasFrame = -1;
    int m_previewPosition = 0;
    int m_previewElapsed = 0; // Milliseconds carried between 50 Hz preview ticks
    int m_previewSpeedPercent = 100; // Preview only: 100 = normal 50 Hz timing.
    int m_previewSpeedAccumulator = 0; // Fixed-point real ticks -> preview ticks.
    bool m_playing = true;
    // Design-time flat-floor preview only. World game physics are not modified.
    QJsonArray m_previewPhysicsProfiles;
    QString m_previewWorldName;
    int m_worldTileSize = 16;
    int m_startPhysicsId = 0;
    int m_floorTravel100 = 0; // World pixel distance, 100 = 1 pixel
    int m_iceVelocity100 = 0;
    int m_iceRemainder100 = 0;
    bool m_previewFloorEnabled = true;
    bool m_gameScaleWalkingFloor = true; // 1:1 game pixels when the moving floor is visible.
    QColor m_paletteZeroBackground;
    bool m_hasPaletteZeroBackground = false;
    QColor m_customPreviewBackground = QColor(145, 150, 160);
    int m_previewBackgroundMode = 0; // 0: palette 0, 1: theme, 2: custom

    QListWidget *m_stateList = nullptr;
    QComboBox *m_directions = nullptr;
    QButtonGroup *m_directionModeButtons = nullptr;
    QListWidget *m_timeline = nullptr;
    QSpinBox *m_width = nullptr, *m_height = nullptr, *m_zoom = nullptr, *m_defaultDuration = nullptr;
    QSpinBox *m_previewZoom = nullptr; // Display-only magnification, not physics scale.
    QSpinBox *m_frameDuration = nullptr;
    QSpinBox *m_footX = nullptr, *m_footY = nullptr;
    QSpinBox *m_boxX = nullptr, *m_boxY = nullptr, *m_boxW = nullptr, *m_boxH = nullptr;
    QCheckBox *m_loop = nullptr, *m_mirrorCheck = nullptr, *m_autoCheck = nullptr;
    QCheckBox *m_showFoot = nullptr, *m_showBox = nullptr, *m_walkingFloor = nullptr, *m_gameScaleCheck = nullptr;
    QLabel *m_preview = nullptr, *m_status = nullptr, *m_atlasInfo = nullptr, *m_floorInfo = nullptr;
    QScrollArea *m_previewScroll = nullptr;
    QPushButton *m_play = nullptr, *m_previewColourButton = nullptr, *m_setAllFrameDurations = nullptr;
    QComboBox *m_previewBackgroundChoice = nullptr, *m_previewPhysics = nullptr;
    QWidget *m_atlasView = nullptr;
    QTimer *m_timer = nullptr;

    QString currentState() const;
    QString currentDirection() const;
    QString clipKey(const QString &state, const QString &direction) const;
    QString mirroredSourceDirection(const QString &direction) const;
    const Clip *effectiveClip(bool *flipped = nullptr) const;
    void createUi();
    void rebuildStateList(int selected = 0);
    void rebuildDirections(const QString &keep = QString());
    void refreshAll();
    void refreshTimeline();
    void refreshPreview();
    void updateWalkingPreviewControls();
    void updateAtlas();
    void appendFrame(int index, bool range);
    void removeFrame();
    void moveFrame(int delta);
    void saveClipSettings();
    void saveSelectedFrameDuration();
    void updateSelectedFrameDuration();
    void readDocument();
    bool writeDocument();
    void exportHeader();
    bool saveHeader(const QString &path);
    bool offerHeaderUpdate();
    QString generateHeader(const QString &prefix, QString *error = nullptr) const;
};

#endif
