#include <stdint.h>
#include "apis.h"

/*

    BASIC USE OF LOADING A SOUND

    uint8_t MEMALIGN32 *sndTestSound;

    uint32_t samplelen;
    samplelen = LoadSFX("sdcard:/soundwave.wav", &sndTestSound);    // recommend 8bit unsigned audio. 
    sound_assign(0, sndTestSound, samplelen, 0);    // sound in channel 0
    sound_setfrequency(0, 22080);   // for a 44khz file, setting frequencie at 22khz slows it by half.
    sound_setvolume(0, 840);    // channel 0, volume OVER volume is allowed, not recommended, max 255
    sound_setpanning(0, 0);     // channel 0, center pan (-127 = full left, 127 = full right)
    sound_setloop(0, 200, 4433);    // channel 0, set sample loop position, loop length
    sound_enableloop(0, 0);         // channel 0, sample loop off


    sound_stop(0);  // use this to reset the sample
    sound_play(0);  // play the sample


*/

uint32_t LoadSFX(char *filename, uint8_t **snddata){
    FRESULT res;
    uint32_t uread;
    wav_t head;

    res = sfopen(0, filename, SD_READ);
    if (res != F_OK) {
        sfclose(0);
        return 0;
    }

    sfread(0, &head, sizeof(wav_t), &uread);

    if (memcmp(head.chunk_id, "RIFF", 4) != 0 ||
        memcmp(head.format, "WAVE", 4) != 0 ||
        head.audio_format != 1) {
        sfclose(0);
        return 0;
    }

    *snddata = malloc(head.subchunk2_size);
    if (!*snddata) {
        sfclose(0);
        return 0;
    }

    sfread(0, *snddata, head.subchunk2_size, &uread);

    sfclose(0);
    return head.subchunk2_size;
}

void freeSFX(uint8_t **snddata){
    free(*snddata);
}