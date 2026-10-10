#ifndef SBAPI_DIALOGS_H
#define SBAPI_DIALOGS_H

#include <stdint.h>
#include "window.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MSGBOX_CANCEL   0
#define MSGBOX_OK       1
#define MSGBOX_YES      2
#define MSGBOX_NO       3

typedef enum {
    MSGBOXF_OK          = 0x00,
    MSGBOXF_OKCANCEL    = 0x01,
    MSGBOXF_YESNO       = 0x02,
    MSGBOXF_YESNOCANCEL = 0x03
} MSGBOX_FLAGS;

typedef struct CGFMsgBoxParams {
    const char *title;
    const char *txtMsg;
    void       *user;
    uint8_t     flags;
} CGFMsgBoxParams;

#define INFOBOX_OK     0

typedef enum {
    INFOBOX_OKONLE = 0x00
} INFBOX_FLAGS;

typedef struct CGFInfoBoxParams {
    volatile const char *title;
    volatile const char *txtMsg;
    volatile void       *user;
} CGFInfoBoxParams;

#define MAX_FILERQS             4
#define FILEREQUEST_DEF_WIDTH   290
#define FILEREQUEST_DEF_HEIGHT  320
#define FILERQ_OUTCAP           256

typedef struct CGFileRqParams {
    const char *title;
    const char *initial_dir;
    const char *filter;
    char       *out_path;
    uint32_t    out_cap;
    void       *user;
} CGFileRqParams;

typedef struct API_GUI_DIALOGS {
    CGWindow (*messagebox_ex)        (CGWindow owner_winhnd, const CGFMsgBoxParams *p);
    CGWindow (*messagebox)           (CGWindow owner_winhnd, const char *title, const char *message, uint8_t flags);
    void     (*messagebox_close)     (CGWindow msgbox_winhnd);

    CGWindow (*infobox_ex)           (CGWindow owner_winhnd, const CGFInfoBoxParams *p);
    CGWindow (*infobox)              (CGWindow owner_winhnd, const char *title, const char *message);
    void     (*infobox_close)        (CGWindow infbox_winhnd);

    CGWindow (*filerequest)          (CGWindow owner_winhnd, const char *title, char *initdir);
    CGWindow (*filerequest_filter)   (CGWindow owner_winhnd, const char *title, char *initdir, const char *filter_list);
    void     (*filerequest_close)    (CGWindow filerq_winhnd);
} API_GUI_DIALOGS;

#define SBOS_MessageBoxEx(owner, params) \
    (GUICoderGirl->dialogs->messagebox_ex(owner, params))

#define SBOS_MessageBox(owner, title, message, flags) \
    (GUICoderGirl->dialogs->messagebox(owner, title, message, flags))

#define SBOS_CloseMessageBox(win) \
    (GUICoderGirl->dialogs->messagebox_close(win))

#define SBOS_InfoBoxEx(owner, params) \
    (GUICoderGirl->dialogs->infobox_ex(owner, params))

#define SBOS_InfoBox(owner, title, message) \
    (GUICoderGirl->dialogs->infobox(owner, title, message))

#define SBOS_CloseInfoBox(win) \
    (GUICoderGirl->dialogs->infobox_close(win))

#define SBOS_FileRequest(owner, title, initdir) \
    (GUICoderGirl->dialogs->filerequest(owner, title, initdir))

#define SBOS_FileRequestFilter(owner, title, initdir, filter_list) \
    (GUICoderGirl->dialogs->filerequest_filter(owner, title, initdir, filter_list))

#define SBOS_CloseFileRequester(win) \
    (GUICoderGirl->dialogs->filerequest_close(win))

#ifdef __cplusplus
}
#endif

#endif // SBAPI_DIALOGS_H
