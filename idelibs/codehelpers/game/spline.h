/* CoderGirl V1 - Sprite Spline
 * Follow a smooth path of editable points made in the Game Designer.
 * All timing is in game frames: 50 frames = 1 second at 50 FPS.
 * Call run_spline() once after each VBlank, usually with frame_step=1.
 * This helper DOES NOT wait for VBlank and does not allocate memory.
 *
 * Copyable examples: gamehelpers/gamespline.txt.
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
    int32_t offset_x, offset_y;    /* World relocation via set_spline_pos(). */
    int32_t view_x, view_y;        /* Absolute drawing/camera offset. */
    uint16_t duration_frames;      /* Whole journey in frames */
    uint16_t elapsed_frames;
    uint8_t loop;
    uint8_t active;
} game_spline_t;

void start_spline(game_spline_t *path, gfxbob_t *sprite,
                  const game_spline_point_t *points, uint16_t point_count,
                  uint16_t duration_frames, uint8_t loop);
void run_spline(game_spline_t *path, uint16_t frame_step);
/* Shift the path so its FIRST world control point becomes (x,y).
   Calling while moving preserves elapsed frames and looping. */
void set_spline_pos(game_spline_t *path, int16_t x, int16_t y);
/* Set an ABSOLUTE drawing offset from the world path (not an increment).
   E.g. offset_spline(&flight, -camera_x, -camera_y) EVERY frame.
   This preserves any world relocation made using set_spline_pos().
   The sprite follows camera motion, without accumulation or timer resets. */
void offset_spline(game_spline_t *path, int32_t x, int32_t y);
void stop_spline(game_spline_t *path);

#endif
