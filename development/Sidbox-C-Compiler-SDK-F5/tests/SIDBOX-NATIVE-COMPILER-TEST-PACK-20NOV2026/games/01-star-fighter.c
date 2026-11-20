/* PLAYABLE: indexed 240x160 software framebuffer + real joystick input.
 * Joystick LEFT/RIGHT (0x10/0x20), FIRE (0x01). GUI window owns drawing.
 */
#include "apis.h"
#define W 240
#define H 160
static CGWindow win;
static CGGadget view;
static CGGadget score_gad;
static uint8_t timer;
static uint8_t pixels[38400];
static uint8_t score_text[12];
static int ship_x = 120;
static int shot_x;
static int shot_y = -1;
static int rock_x[8];
static int rock_y[8];
static int frame;
static int score;

static void tick(void *user)
{
    int key = API.hwl->getjoyport();
    int x; int y; int i; int a; int b;
    if ((key & 0x10) && ship_x > 9) ship_x -= 4;
    if ((key & 0x20) && ship_x < W - 10) ship_x += 4;
    if ((key & 1) && shot_y < 0) { shot_x = ship_x; shot_y = 133; }
    if (shot_y >= 0) shot_y -= 7;
    frame++;
    for (i = 0; i < W * H; i++) pixels[i] = 0;
    for (i = 0; i < 65; i++) {
        x = (i * 73 + frame * (i % 3 + 1)) % W;
        y = (i * 53 + frame * (i % 4 + 1)) % H;
        pixels[y * W + x] = 7;
    }
    for (i = 0; i < 8; i++) {
        rock_y[i] += 1 + (i % 3);
        if (rock_y[i] >= H + 8) {
            rock_y[i] = -12 - i * 10;
            rock_x[i] = (i * 57 + frame * 9) % (W - 12) + 6;
        }
        if (shot_y >= 0 && shot_y > rock_y[i] - 6 &&
            shot_y < rock_y[i] + 6 && shot_x > rock_x[i] - 7 &&
            shot_x < rock_x[i] + 7) {
            rock_y[i] = -25;
            shot_y = -1;
            score++;
            if (score > 9999) score = 0;
            score_text[7] = '0' + score / 1000;
            score_text[8] = '0' + (score / 100) % 10;
            score_text[9] = '0' + (score / 10) % 10;
            score_text[10] = '0' + score % 10;
            API.gui->gadgets->label_set_text(score_gad, score_text);
        }
        for (b = -4; b <= 4; b++) {
            y = rock_y[i] + b;
            if (y < 0 || y >= H) continue;
            for (a = -4; a <= 4; a++) {
                x = rock_x[i] + a;
                if (x < 0 || x >= W) continue;
                if (a*a + b*b <= 20) pixels[y * W + x] = 4 + (i & 3);
            }
        }
    }
    if (shot_y >= 1 && shot_y < H - 5) {
        for (y = shot_y; y < shot_y + 6; y++) pixels[y * W + shot_x] = 15;
    }
    for (b = -7; b <= 7; b++) {
        if (b < 0) y = 144 - (7 + b) / 2;
        else y = 144 - (7 - b) / 2;
        x = ship_x + b;
        if (x >= 0 && x < W && y >= 0 && y < H) {
            pixels[y * W + x] = 15;
            pixels[(y + 1) * W + x] = 12;
        }
    }
    for (y = 133; y < 146; y++) pixels[y * W + ship_x] = 10;
    API.gui->gadgets->repaint(view);
}

static CGWindowProcRes window_proc(CGWindow w, const CGMessage_t *m)
{
    if (m->mtype == CGMSG_WINDOW && m->eventClass == CGEVT_WIN_CLOSE_REQUEST) {
        API.gui->timers->cancel(timer);
        API.gui->timers->free(timer);
        API.gui->windows->window_close(w);
        return CGPROC_HANDLED;
    }
    return CGPROC_DEFAULT;
}
int main(void)
{
    int i;
    score_text[0] = 'S'; score_text[1] = 'C'; score_text[2] = 'O';
    score_text[3] = 'R'; score_text[4] = 'E'; score_text[5] = ':';
    score_text[6] = ' '; score_text[7] = '0'; score_text[8] = '0';
    score_text[9] = '0'; score_text[10] = '0'; score_text[11] = 0;
    for (i = 0; i < 8; i++) { rock_x[i] = (i * 41) % 220 + 10; rock_y[i] = -i * 25; }
    win = API.gui->windows->window_create(&win, 35, 15, 290, 244,
                                         "Star Fighter: joystick + FIRE", SBX_WIN_DEFAULT);
    if (!win) return 1;
    API.gui->windows->set_proc(win, window_proc);
    view = API.gui->gadgets->bitmapview_create(win, 12, 12, W, H, W, H,
                   BVF_SRC_ROWMAJOR | BVF_PERSISTANT, GAD_TOOL_DEFAULT);
    score_gad = API.gui->gadgets->label_create(win, 12, 180, 225, 20,
                                               score_text, GAD_TOOL_DEFAULT);
    API.gui->gadgets->bitmapview_set_bitmap(view, pixels);
    timer = API.gui->timers->create();
    if (timer == CGTIMER_INVALID) { API.gui->windows->window_close(win); return 2; }
    /* Timer-set return-code convention is not assumed by this test. */
    API.gui->timers->set(timer, 50, 50, tick, NULL);
    return 0;
}
