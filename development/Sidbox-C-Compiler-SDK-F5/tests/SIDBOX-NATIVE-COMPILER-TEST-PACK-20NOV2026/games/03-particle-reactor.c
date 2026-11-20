/* LIVE GRAPHICS: 140 independently moving particles, software pixels.
 * Joystick moves the reactor; every particle orbits/moves toward it.
 */
#include "apis.h"
#define W 240
#define H 150
static CGWindow win;
static CGGadget view;
static uint8_t timer;
static uint8_t pixels[36000];
static int posx[140];
static int posy[140];
static int velx[140];
static int vely[140];
static int core_x = 120;
static int core_y = 75;
static int frame;

static void tick(void *unused)
{
    int joy = API.hwl->getjoyport();
    int i; int x; int y; int dx; int dy;
    if ((joy & 0x10) && core_x > 15) core_x -= 3;
    if ((joy & 0x20) && core_x < W - 15) core_x += 3;
    if ((joy & 0x04) && core_y > 15) core_y -= 3;
    if ((joy & 0x08) && core_y < H - 15) core_y += 3;
    for (i = 0; i < W * H; i++) {
        if (pixels[i] > 0) pixels[i] -= 1;
    }
    frame++;
    for (i = 0; i < 140; i++) {
        dx = core_x - posx[i];
        dy = core_y - posy[i];
        if (dx > 18) velx[i] += 1;
        if (dx < -18) velx[i] -= 1;
        if (dy > 18) vely[i] += 1;
        if (dy < -18) vely[i] -= 1;
        if (velx[i] > 3) velx[i] = 3;
        if (velx[i] < -3) velx[i] = -3;
        if (vely[i] > 3) vely[i] = 3;
        if (vely[i] < -3) vely[i] = -3;
        posx[i] += velx[i];
        posy[i] += vely[i];
        if (posx[i] < 3) { posx[i] = 3; velx[i] = -velx[i]; }
        if (posx[i] >= W - 3) { posx[i] = W - 4; velx[i] = -velx[i]; }
        if (posy[i] < 3) { posy[i] = 3; vely[i] = -vely[i]; }
        if (posy[i] >= H - 3) { posy[i] = H - 4; vely[i] = -vely[i]; }
        x = posx[i]; y = posy[i];
        pixels[y * W + x] = 15;
        pixels[(y - 1) * W + x] = 10;
        pixels[(y + 1) * W + x] = 10;
        pixels[y * W + x - 1] = 7;
        pixels[y * W + x + 1] = 7;
    }
    for (y = core_y - 5; y <= core_y + 5; y++) {
        for (x = core_x - 5; x <= core_x + 5; x++) {
            dx = x - core_x; dy = y - core_y;
            if (dx*dx + dy*dy < 26) pixels[y * W + x] = 14;
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
    CGGadget status;
    for (i = 0; i < 140; i++) {
        posx[i] = (i * 43 + 11) % (W - 7) + 3;
        posy[i] = (i * 71 + 9) % (H - 7) + 3;
        velx[i] = (i % 5) - 2;
        vely[i] = (i % 7) - 3;
    }
    win = API.gui->windows->window_create(&win, 35, 15, 290, 244,
                                         "Particle Reactor", SBX_WIN_DEFAULT);
    if (!win) return 1;
    API.gui->windows->set_proc(win, window_proc);
    view = API.gui->gadgets->bitmapview_create(win, 10, 10, W, H, W, H,
               BVF_SRC_ROWMAJOR | BVF_PERSISTANT, GAD_TOOL_DEFAULT);
    status = API.gui->gadgets->label_create(win, 10, 170, 245, 20,
                       "Joystick moves the particle attractor", GAD_TOOL_DEFAULT);
    API.gui->gadgets->bitmapview_set_bitmap(view, pixels);
    timer = API.gui->timers->create();
    if (timer == CGTIMER_INVALID) { API.gui->windows->window_close(win); return 2; }
    /* Timer-set return-code convention is not assumed by this test. */
    API.gui->timers->set(timer, 45, 45, tick, NULL);
    return 0;
}
