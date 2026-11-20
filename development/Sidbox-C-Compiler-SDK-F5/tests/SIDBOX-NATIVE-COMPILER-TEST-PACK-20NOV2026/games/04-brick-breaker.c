/* PLAYABLE: brick-breaker, physics, collision tests, paddle joystick.
 * LEFT/RIGHT move. FIRE restarts once you miss the ball.
 */
#include "apis.h"
#define W 240
#define H 144
static CGWindow win;
static CGGadget view;
static CGGadget hud;
static uint8_t timer;
static uint8_t pixels[34560];
static int blocks[40];
static int bx = 120;
static int by = 100;
static int vx = 2;
static int vy = -2;
static int paddle = 120;
static int missed;
static int broken;

static void tick(void *unused)
{
    int joy = API.hwl->getjoyport();
    int x; int y; int i; int row; int col; int left; int top;
    if (joy & 0x10) paddle -= 5;
    if (joy & 0x20) paddle += 5;
    if (paddle < 24) paddle = 24;
    if (paddle > W - 24) paddle = W - 24;
    if (missed && (joy & 1)) {
        bx = 120; by = 100; vx = 2; vy = -2; missed = 0;
        API.gui->gadgets->label_set_text(hud, "Keep the ball in play!");
    }
    if (!missed) {
        bx += vx; by += vy;
        if (bx < 3) { bx = 3; vx = -vx; }
        if (bx >= W - 3) { bx = W - 4; vx = -vx; }
        if (by < 3) { by = 3; vy = -vy; }
        if (by > H - 6) {
            missed = 1;
            API.gui->gadgets->label_set_text(hud, "Missed! Press FIRE to restart");
        }
        if (by >= 128 && by <= 133 && bx >= paddle - 24 && bx <= paddle + 24 && vy > 0) {
            vy = -vy;
            if (bx < paddle - 8) vx = -3;
            else if (bx > paddle + 8) vx = 3;
        }
        for (i = 0; i < 40; i++) {
            if (!blocks[i]) continue;
            row = i / 10; col = i % 10;
            left = 5 + col * 23;
            top = 8 + row * 12;
            if (bx >= left && bx <= left + 19 && by >= top && by <= top + 8) {
                blocks[i] = 0; broken++; vy = -vy;
                if (broken == 40) {
                    API.gui->gadgets->label_set_text(hud, "ALL BRICKS GONE! Close to finish");
                    missed = 1;
                }
                break;
            }
        }
    }
    for (i = 0; i < W * H; i++) pixels[i] = 0;
    for (i = 0; i < 40; i++) {
        if (!blocks[i]) continue;
        row = i / 10; col = i % 10;
        left = 5 + col * 23; top = 8 + row * 12;
        for (y = top; y < top + 9; y++) {
            for (x = left; x < left + 20; x++) pixels[y * W + x] = 4 + row * 3;
        }
    }
    for (y = 135; y < 139; y++) {
        for (x = paddle - 24; x <= paddle + 24; x++) pixels[y * W + x] = 15;
    }
    if (!missed) {
        for (y = by - 2; y <= by + 2; y++) {
            if (y < 0 || y >= H) continue;
            for (x = bx - 2; x <= bx + 2; x++) {
                if (x >= 0 && x < W) pixels[y * W + x] = 14;
            }
        }
    }
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
    for (i = 0; i < 40; i++) blocks[i] = 1;
    win = API.gui->windows->window_create(&win, 35, 18, 290, 232,
                                         "Brick Breaker", SBX_WIN_DEFAULT);
    if (!win) return 1;
    API.gui->windows->set_proc(win, window_proc);
    view = API.gui->gadgets->bitmapview_create(win, 10, 10, W, H, W, H,
                 BVF_SRC_ROWMAJOR | BVF_PERSISTANT, GAD_TOOL_DEFAULT);
    hud = API.gui->gadgets->label_create(win, 10, 165, 265, 22,
                                         "Keep the ball in play!", GAD_TOOL_DEFAULT);
    API.gui->gadgets->bitmapview_set_bitmap(view, pixels);
    timer = API.gui->timers->create();
    if (timer == CGTIMER_INVALID) { API.gui->windows->window_close(win); return 2; }
    /* Timer-set return-code convention is not assumed by this test. */
    API.gui->timers->set(timer, 50, 50, tick, NULL);
    return 0;
}
