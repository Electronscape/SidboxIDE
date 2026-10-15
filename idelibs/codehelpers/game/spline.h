/* CoderGirl V1 - Sprite Spline
 * Follow a smooth path of editable points made in the Game Designer.
 * All timing is in game frames: 50 frames = 1 second at 50 FPS.
 * Call run_spline() once after each VBlank, usually with frame_step=1.
 * This helper DOES NOT wait for VBlank and does not allocate memory.
 *
 *  #include "gamehelpers/gamespline.h"
 *  #include "gamehelpers/splinepaths.h"
 *  static game_spline_t flight = {0};
 *  start_spline(&flight, &enemy, spline_flight_path,
 *               spline_flight_count, 100, 1);
 *  // Within each frame, before drawing the sprite:
 *  run_spline(&flight, 1);
 *
 * loop=1 means the path curves from the final point back to the first.
 * loop=0 means the sprite stays at the final point when finished.
 * Points and example declarations are generated using "Export Spline Paths".
 */
#ifndef CODERGIRL_V1_GAMESPLINE_H
#define CODERGIRL_V1_GAMESPLINE_H

#include "apis.h"
#include <stdint.h>

typedef struct {
    int16_t x;
    int16_t y;
} game_spline_point_t;

typedef struct {
    gfxbob_t *sprite;              /* Existing V1 sprite, never owned here */
    const game_spline_point_t *points; /* Keep this array alive during movement */
    uint16_t point_count;          /* Minimum 2 points */
    uint16_t duration_frames;      /* Whole journey in frames */
    uint16_t elapsed_frames;
    uint8_t loop;
    uint8_t active;
} game_spline_t;

void start_spline(game_spline_t *path, gfxbob_t *sprite,
                  const game_spline_point_t *points, uint16_t point_count,
                  uint16_t duration_frames, uint8_t loop);
void run_spline(game_spline_t *path, uint16_t frame_step);
void stop_spline(game_spline_t *path);

#endif
