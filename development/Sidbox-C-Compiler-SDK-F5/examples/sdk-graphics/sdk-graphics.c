#include "apis.h"

static uint8_t pixels[15360];
static uint8_t under_ball[121];
static int width = 160;
static int height = 96;
static int ball_x = 34;
static int ball_y = 26;
static int vx = 3;
static int vy = 2;
static int timer = CGTIMER_INVALID;
static int running;
static CGWindow window = 0xff;
static CGGadget view;
static CGGadget pause_button;

static void draw_background(void)
{
    int y = 0;
    while (y < height) {
        int x = 0;
        while (x < width) {
            int pen = 19 + (x / 16 + y / 16) % 2;
            if (x % 16 == 0 || y % 16 == 0)
                pen = 23;
            pixels[y * width + x] = pen;
            x = x + 1;
        }
        y = y + 1;
    }
}

static void draw_ball(int erase)
{
    int y = -5;
    while (y <= 5) {
        int x = -5;
        while (x <= 5) {
            int radius_squared = x * x + y * y;
            if (radius_squared <= 25) {
                int at = (ball_y + y) * width + ball_x + x;
                int saved = (y + 5) * 11 + x + 5;
                if (erase) {
                    pixels[at] = under_ball[saved];
                } else {
                    int pen = 29;
                    under_ball[saved] = pixels[at];
                    if (radius_squared > 17)
                        pen = 30;
                    if (x == -2 && y == -2)
                        pen = 2;
                    pixels[at] = pen;
                }
            }
            x = x + 1;
        }
        y = y + 1;
    }
}

static void on_tick(void *user)
{
    draw_ball(1);
    ball_x = ball_x + vx;
    ball_y = ball_y + vy;
    if (ball_x <= 6) {
        ball_x = 6;
        vx = -vx;
    } else if (ball_x >= width - 7) {
        ball_x = width - 7;
        vx = -vx;
    }
    if (ball_y <= 6) {
        ball_y = 6;
        vy = -vy;
    } else if (ball_y >= height - 7) {
        ball_y = height - 7;
        vy = -vy;
    }
    draw_ball(0);
    SBOS_GadgetRepaint(view);
}

static CGWindowProcRes on_window(CGWindow win, const CGMessage_t *m)
{
    if (!m)
        return CGPROC_DEFAULT;

    if (m->mtype == CGMSG_WINDOW && m->eventClass == CGEVT_WIN_CLOSE_REQUEST) {
        SBOS_TimerCancel(timer);
        SBOS_FreeTimer(timer);
        SBOS_CloseWindow(win);
        return CGPROC_HANDLED;
    }

    if ((m->mtype == CGMSG_KEY && m->eventClass == CGEVT_KEY_PRESSED && m->a == ' ') ||
        (m->mtype == CGMSG_GADGET && m->eventClass == CGEVT_GAD_ACTIVATED &&
         m->gadget == pause_button)) {
        if (running) {
            SBOS_TimerCancel(timer);
            running = 0;
            SBOS_ButtonSetText(pause_button, "Resume", -1);
        } else if (SBOS_TimerSet(timer, 66, 66, on_tick, NULL) == 0) {
            running = 1;
            SBOS_ButtonSetText(pause_button, "Pause", -1);
        }
        return CGPROC_HANDLED;
    }
    return CGPROC_DEFAULT;
}

int main(void)
{
    if (SBOS_CreateWindow(&window, 72, 38, 220, 216, "Pixel bounce", SBX_WIN_DEFAULT) == 0xff)
        return 1;

    CGGadget hint = SBOS_CreateLabel(window, 16, 12, 184, 18, "Space toggles pause",
                                      GAD_TOOL_DEFAULT);
    CGGadget frame = SBOS_CreateCanvas(window, 15, 33, 162, 98, CNV_BEVEL, GAD_TOOL_DEFAULT);
    view = SBOS_CreateBitmapView(window, 16, 34, width, height, width, height,
                                 BVF_SRC_ROWMAJOR, GAD_TOOL_NOBORDER);
    pause_button = SBOS_CreateButton(window, 16, 144, 102, 28, "Pause", GAD_TOOL_DEFAULT);
    if (hint == 0 || frame == 0 || view == 0 || pause_button == 0) {
        SBOS_CloseWindow(window);
        return 2;
    }

    draw_background();
    draw_ball(0);
    SBOS_GadgetSetFPen(frame, 9);
    SBOS_GadgetSetBPen(frame, 16);
    SBOS_GadgetRepaint(frame);
    SBOS_BitmapviewSetBitmap(view, pixels);
    SBOS_BitmapviewSetImageSize(view, width, height);

    timer = SBOS_CreateTimer();
    if (timer == CGTIMER_INVALID || SBOS_TimerSet(timer, 66, 66, on_tick, NULL) != 0) {
        if (timer != CGTIMER_INVALID)
            SBOS_FreeTimer(timer);
        SBOS_CloseWindow(window);
        return 3;
    }
    running = 1;
    SBOS_SetWindowProc(window, on_window);
    SBOS_WindowToFront(window);
    SBOS_WindowSetFocus(window);
    return 0;
}
