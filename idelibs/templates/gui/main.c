#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "main.h"
#include "apis.h"

#define APP_INVALID_WINDOW ((CGWindow)0xFF)

#define TXTAPP_TITLE    "GUI Test App"
#define TESTAPP_WIN_X    24
#define TESTAPP_WIN_Y    20
#define TESTAPP_WIN_W    300
#define TESTAPP_WIN_H    200

#define SHAPES_PER_TICK 6

#define WIN_DEFAULT     (SBX_WF_VISIBLE    |\
                         SBX_WF_CLOSE      |\
                         SBX_WF_TITLE_BAR  |\
                         SBX_WF_ZORDER     |\
                         SBX_WF_MINIMISE   |\
                         SBX_WF_MOVEABLE   |\
                         SBX_WF_SCREENBOUND)


static CGWindow testapp_win;
static CGTimer draw_timer = CGTIMER_INVALID;
static cg_menu_t demo_menu = CG_MENU_INVALID;
static cg_menuitem_t menu_exit  = CG_MENUITEM_INVALID;

static volatile uint8_t app_running;

static CGWindowProcRes testapp_proc(CGWindow win, const CGMessage_t *m);

static void app_shutdown(void)
{
    if (!app_running) {
        return;
    }

    app_running = 0;

    if (draw_timer != CGTIMER_INVALID) {
        SBOS_FreeTimer(draw_timer);
        draw_timer = CGTIMER_INVALID;
    }

    if (testapp_win) {
        SBOS_CloseWindow(testapp_win);
        testapp_win = 0;
    }

    if (demo_menu != CG_MENU_INVALID) {
        SBOS_DestroyMenu(&demo_menu);
        menu_exit  = CG_MENUITEM_INVALID;
    }

    //printf(TXTAPP_TITLE ": closing\n");
}

static void on_timer_tick(void *user)
{
    (void)user;

    if (!app_running) {
        return;
    }

    //draw_demo_frame(SHAPES_PER_TICK);
    printf("doing something\n");
}

static CGWindowProcRes testapp_proc(CGWindow win, const CGMessage_t *m)
{
    (void)win;

    if (!m) {
        return CGPROC_DEFAULT;
    }

    if (m->mtype == CGMSG_WINDOW) {
        switch (m->eventClass) {
        case CGEVT_WIN_CLOSE_REQUEST:
            app_shutdown();
            return CGPROC_HANDLED;

        case CGEVT_SYS_REPAINT:
            //repaint_bitmapview();
            //set_status();
            return CGPROC_HANDLED;

        default:
            break;
        }
    }

    if (m->mtype == CGMSG_MENU && m->eventClass == CGEVT_MENU_SELECTED) {
        if ((cg_menu_t)m->a != demo_menu) {
            return CGPROC_DEFAULT;
        }

        if ((cg_menuitem_t)m->b == menu_exit) {
            app_shutdown();
            return CGPROC_HANDLED;
        }
    }

    return CGPROC_DEFAULT;
}

static void setup_demo_menu(void)
{
    cg_menuitem_t item;

    if (demo_menu != CG_MENU_INVALID) {
        return;
    }

    demo_menu = SBOS_CreateMenuTitle("Test app|Options|About");
    if (demo_menu == CG_MENU_INVALID) {
        return;
    }

    menu_exit = SBOS_CreateMenuItem(&demo_menu, 0, "Exit"); // handled by CGMSG_MENU in editor_proc()

    //menu_about = SBOS_CreateMenuItem(&demo_menu, 2, "for calling back on menu hit");
    //SBOS_MenuCallBack(menu_about, on_menu_about, NULL);

    SBOS_AttachMenuToWindow(demo_menu, testapp_win);
}

static void build_testapp(void)
{
    SBOS_CreateWindow(&testapp_win, TESTAPP_WIN_X, TESTAPP_WIN_Y, TESTAPP_WIN_W, TESTAPP_WIN_H, TXTAPP_TITLE, WIN_DEFAULT);
    SBOS_SetWindowProc(testapp_win, testapp_proc);
    SetApplicationTitle(testapp_win, "Test blank app!");
    setup_demo_menu();

    draw_timer = SBOS_CreateTimer();
    if (draw_timer != CGTIMER_INVALID) {
        if (SBOS_TimerSet(draw_timer, 1000, 1000, on_timer_tick, NULL) != 0) {
            SBOS_FreeTimer(draw_timer);
            draw_timer = CGTIMER_INVALID;
        }
    }

    SBOS_WindowToFront(testapp_win);
    SBOS_WindowSetFocus(testapp_win);
}

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    app_running = 1;
    build_testapp();

    return 0x00;
}
