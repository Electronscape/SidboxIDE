#ifndef MUSIC_API_H
#define MUSIC_API_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


#pragma pack(push, 1)

typedef struct {
    char     chunk_id[4];     // "RIFF"
    uint32_t chunk_size;      // 36 + data_size (for PCM)
    char     format[4];       // "WAVE"

    // fmt chunk
    char     subchunk1_id[4]; // "fmt "
    uint32_t subchunk1_size;  // 16 for PCM
    uint16_t audio_format;    // 1 = PCM
    uint16_t num_channels;    // 1=mono, 2=stereo
    uint32_t sample_rate;     // e.g. 11025, 22050, 44100
    uint32_t byte_rate;       // sample_rate * num_channels * bits_per_sample/8
    uint16_t block_align;     // num_channels * bits_per_sample/8
    uint16_t bits_per_sample; // 8 or 16 typically

    // data chunk header (note: some WAVs have extra chunks before "data")
    char     subchunk2_id[4]; // "data"
    uint32_t subchunk2_size;  // PCM bytes count
} wav_t;

#pragma pack(pop)



typedef struct {
    void (*setbuffsize) (uint32_t size);
    uint8_t *musicdmaenable;
    void (*dmadisable) (void);
    void (*dmaenable)  (void);
    uint8_t (*dmabufferview)(const uint16_t **left, const uint16_t **right, uint32_t *frames, uint32_t *play_cursor);
    int (*midi_out)     (const uint8_t *buffer, uint16_t count);

    // Live Sid Interface
    void (*startsidlive) (void);
    void (*sidpoke)    (uint8_t chip, uint8_t reg, uint8_t v);
} API_AUDIO_HARDWARE;


typedef struct  {
    void (*play)            (char *file, uint8_t subsong);
    void (*CallMusicRoutine)(void);     // call this every frame (or every other frame, but often enough to keep music playing)
    int  (*modfromMem) (const uint8_t *src, uint32_t dataLen);
    void (*stop)            (void);
    // some other functions like set sub track, rewind, set position, channel masking, 

} API_MUSIC;


typedef uint8_t SampleFmt;
#define SAMP_S8  0
#define SAMP_S16 1

typedef struct {
    void (*loadsfx)       (void);
    void (*playsample)    (uint8_t channel);
    void (*stopsample)    (uint8_t channel);
    void (*assignsample)  (uint8_t channel, void *sample, uint32_t samples, uint8_t bitsize);   // 0 = 8bits, 1 = 16bits
    void (*setsamplefreq) (uint8_t channel, uint16_t hz);
    void (*setsamplevol)  (uint8_t channel, uint16_t vol);
    void (*setsamplepan)  (uint8_t channel, int8_t pan); // -127 to 127
    void (*setsampleloop) (uint8_t channel, uint32_t from, uint32_t length);
    void (*setloopenable) (uint8_t channel, uint8_t enable);
} API_SOUND;


typedef struct  {
    int      (*start)              (uint8_t route_mask);
    uint8_t  (*isready)            (void);
    void     (*set_routes)         (uint8_t route_mask);
    void     (*set_input_channel)  (uint8_t channel);
    void     (*set_voice)          (uint8_t voice);
    void     (*set_percussion_ch)  (uint8_t channel);
    void     (*note_on)            (uint8_t route_mask, uint8_t channel, uint8_t note, uint8_t velocity);
    void     (*note_off)           (uint8_t route_mask, uint8_t channel, uint8_t note, uint8_t velocity);
    void     (*control)            (uint8_t route_mask, uint8_t channel, uint8_t controller, uint8_t value);
    void     (*program)            (uint8_t route_mask, uint8_t channel, uint8_t program);
    void     (*pitch_bend)         (uint8_t route_mask, uint8_t channel, int16_t bend);
    void     (*all_notes_off)      (uint8_t route_mask);
    
    void     (*sid_voice_reset)    (void);
    uint8_t  (*sid_voice_get)      (uint8_t program, uint8_t *wave, uint8_t *ad, uint8_t *sr, uint16_t *pulse, int16_t *tune_cents);
    uint8_t  (*sid_voice_set)      (uint8_t program, uint8_t wave, uint8_t ad, uint8_t sr, uint16_t pulse, int16_t tune_cents);
} API_AUDIO_MIDI;




uint32_t LoadSFX(char *filename, uint8_t **snddata);



///////////-------------- HELPERS -----------------//////
/////////////////// hardware level stuff ################
#define AUDIOBase       (API->audio)
#define AUDIOMUSIC      (AUDIOBase->music)
#define AUDIOSound      (AUDIOBase->sound)
/////////////////////////////////////////////////////////

// AUDIO HARDWARE SETUP //
#define set_audio_dma(size)  (AUDIOBase->audhl->setbuffsize(size))
#define set_music_dma (*(AUDIOBase->audhl->musicdmaenable))
#define audio_dma_disable() (AUDIOBase->audhl->dmadisable())
#define audio_dma_enable()  (AUDIOBase->audhl->dmaenable())
#define disable_audio_dma() audio_dma_disable()
#define enable_audio_dma()  audio_dma_enable()
#define audio_dma_buffer_view(left, right, frames, play_cursor)  (AUDIOBase->audhl->dmabufferview(left, right, frames, play_cursor))

// MIDI INTERFACING //
#define midi_out(packetBuffer, packetSize) (AUDIOBase->audhl->midi_out(packetBuffer, packetSize))

// opens a music file and begins playing
#define music_play(filename, subsong) (AUDIOMUSIC->play(filename, subsong))
#define music_stop()                  (AUDIOMUSIC->stop())
#define music_mod_from_ram_play(src, len) (AUDIOMUSIC->modfromMem(src, len))

// update music routine and timers, recommend using this on each frame, or every other frame
#define music_update() (AUDIOMUSIC->CallMusicRoutine())

// SOUND INTERFACING //
#define sound_assign(chan, data, samples, bitsize)  (AUDIOSound->assignsample(chan, data, samples, bitsize))    // void (*assignsample)  (uint8_t channel, void *sample, uint32_t samples, uint8_t bitsize);   // 0 = 8bits, 1 = 16bits
#define sound_play(chan)              (AUDIOSound->playsample    (chan))
#define sound_stop(chan)              (AUDIOSound->stopsample    (chan))
#define sound_setfrequency(chan, hz)  (AUDIOSound->setsamplefreq (chan, hz)) 
#define sound_setvolume(chan, vol)    (AUDIOSound->setsamplevol  (chan, vol))  // 0 to 255
#define sound_setpanning(chan, pan)   (AUDIOSound->setsamplepan  (chan, pan))  // -127 to 127
#define sound_setloop(chan, from, to) (AUDIOSound->setsampleloop (chan, from, to))   // set both to 0 to stop loop
#define sound_enableloop(chan, en)    (AUDIOSound->setloopenable (chan, en))



// direct sid interface
#define audio_livesid()               (AUDIOBase->audhl->startsidlive())
#define audio_sidpoke(chip, reg, val) (AUDIOBase->audhl->sidpoke(chip, reg, val))




#ifdef __cplusplus
}
#endif
#endif
