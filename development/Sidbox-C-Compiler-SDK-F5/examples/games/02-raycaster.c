/* PLAYABLE: raycast 3D maze, no float/libm. 240x144 software frame.
 * Joystick UP/DOWN moves; LEFT/RIGHT turns. Uses real getjoyport().
 * Each ray is integer-stepped across a 16x16 map.
 */
#include "apis.h"
#define W 240
#define H 144
static CGWindow win;
static CGGadget view;
static uint8_t timer;
static uint8_t pixels[34560];
static int px = 8 * 256;
static int py = 8 * 256;
static int direction = 0;
static int sine[64] = {
    0,100,200,297,392,483,569,650,724,792,851,903,946,980,1004,1019,
    1024,1019,1004,980,946,903,851,792,724,650,569,483,392,297,200,100,
    0,-100,-200,-297,-392,-483,-569,-650,-724,-792,-851,-903,-946,-980,-1004,-1019,
    -1024,-1019,-1004,-980,-946,-903,-851,-792,-724,-650,-569,-483,-392,-297,-200,-100
};
static uint8_t level[257];
/* Map is filled as 16 rows in main, to avoid unsupported file-scope char strings. */
/* original literals replaced below */


static void tick(void *user)
{
    int key = API.hwl->getjoyport();
    int new_x; int new_y; int x; int y; int ray; int step; int rx; int ry; int dx; int dy; int mx; int my; int height;
    int colour; int top; int bot;
    if (key & 0x10) direction = (direction + 63) & 63;
    if (key & 0x20) direction = (direction + 1) & 63;
    new_x = px;
    new_y = py;
    if (key & 0x04) {
        new_x += sine[(direction + 16) & 63] / 24;
        new_y += sine[direction] / 24;
    }
    if (key & 0x08) {
        new_x -= sine[(direction + 16) & 63] / 24;
        new_y -= sine[direction] / 24;
    }
    mx = new_x >> 8;
    my = new_y >> 8;
    if (mx > 0 && mx < 15 && my > 0 && my < 15 && level[my * 16 + mx] != '#') {
        px = new_x; py = new_y;
    }
    for (y = 0; y < H; y++) {
        if (y < H / 2) colour = 9;
        else colour = 3;
        for (x = 0; x < W; x++) pixels[y * W + x] = colour;
    }
    for (ray = 0; ray < W; ray += 4) {
        int angle = (direction + ((ray - W / 2) / 13) + 64) & 63;
        dx = sine[(angle + 16) & 63] / 8;
        dy = sine[angle] / 8;
        rx = px; ry = py;
        for (step = 1; step < 110; step++) {
            rx += dx; ry += dy;
            mx = rx >> 8; my = ry >> 8;
            if (mx < 0 || mx > 15 || my < 0 || my > 15) break;
            if (level[my * 16 + mx] == '#') break;
        }
        height = 850 / (step + 2);
        if (height > H) height = H;
        top = (H - height) / 2;
        bot = top + height;
        if (step < 10) colour = 15;
        else if (step < 20) colour = 11;
        else if (step < 35) colour = 7;
        else colour = 5;
        for (y = top; y < bot; y++) {
            pixels[y * W + ray] = colour;
            pixels[y * W + ray + 1] = colour;
            pixels[y * W + ray + 2] = colour;
            pixels[y * W + ray + 3] = colour;
        }
    }
    /* Tiny aiming crosshair. */
    for (x = 115; x <= 125; x++) pixels[72 * W + x] = 15;
    for (y = 67; y <= 77; y++) pixels[y * W + 120] = 15;
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
    CGGadget label;
    int mi;
    for (mi = 0; mi < 256; mi++) level[mi] = '.';
    level[0] = '#';
    level[1] = '#';
    level[2] = '#';
    level[3] = '#';
    level[4] = '#';
    level[5] = '#';
    level[6] = '#';
    level[7] = '#';
    level[8] = '#';
    level[9] = '#';
    level[10] = '#';
    level[11] = '#';
    level[12] = '#';
    level[13] = '#';
    level[14] = '#';
    level[15] = '#';
    level[16] = '#';
    level[23] = '#';
    level[31] = '#';
    level[32] = '#';
    level[39] = '#';
    level[42] = '#';
    level[43] = '#';
    level[47] = '#';
    level[48] = '#';
    level[55] = '#';
    level[63] = '#';
    level[64] = '#';
    level[79] = '#';
    level[80] = '#';
    level[81] = '#';
    level[82] = '#';
    level[86] = '#';
    level[87] = '#';
    level[88] = '#';
    level[95] = '#';
    level[96] = '#';
    level[111] = '#';
    level[112] = '#';
    level[115] = '#';
    level[119] = '#';
    level[120] = '#';
    level[123] = '#';
    level[127] = '#';
    level[128] = '#';
    level[131] = '#';
    level[143] = '#';
    level[144] = '#';
    level[147] = '#';
    level[159] = '#';
    level[160] = '#';
    level[163] = '#';
    level[164] = '#';
    level[165] = '#';
    level[175] = '#';
    level[176] = '#';
    level[191] = '#';
    level[192] = '#';
    level[198] = '#';
    level[199] = '#';
    level[200] = '#';
    level[207] = '#';
    level[208] = '#';
    level[223] = '#';
    level[224] = '#';
    level[239] = '#';
    level[240] = '#';
    level[241] = '#';
    level[242] = '#';
    level[243] = '#';
    level[244] = '#';
    level[245] = '#';
    level[246] = '#';
    level[247] = '#';
    level[248] = '#';
    level[249] = '#';
    level[250] = '#';
    level[251] = '#';
    level[252] = '#';
    level[253] = '#';
    level[254] = '#';
    level[255] = '#';
    win = API.gui->windows->window_create(&win, 35, 18, 290, 235,
                                         "3D Maze: integer raycaster", SBX_WIN_DEFAULT);
    if (!win) return 1;
    API.gui->windows->set_proc(win, window_proc);
    view = API.gui->gadgets->bitmapview_create(win, 10, 10, W, H, W, H,
                   BVF_SRC_ROWMAJOR | BVF_PERSISTANT, GAD_TOOL_DEFAULT);
    label = API.gui->gadgets->label_create(win, 10, 167, 260, 20,
                                          "UP/DOWN move, LEFT/RIGHT turn", GAD_TOOL_DEFAULT);
    API.gui->gadgets->bitmapview_set_bitmap(view, pixels);
    timer = API.gui->timers->create();
    if (timer == CGTIMER_INVALID) { API.gui->windows->window_close(win); return 2; }
    /* Timer-set return-code convention is not assumed by this test. */
    API.gui->timers->set(timer, 60, 60, tick, NULL);
    return 0;
}
