#ifndef SBAPI_MENUS_H
#define SBAPI_MENUS_H

#include <stdint.h>
#include "window.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef uint32_t cg_menu_t;
typedef uint32_t cg_menuitem_t;
typedef struct ItemLists_t ItemLists_t;
typedef void (*SBOS_MenuCallback)(cg_menu_t menu, cg_menuitem_t item, void *userdata);

#define CG_MENU_INVALID         ((cg_menu_t)0u)
#define CG_MENUITEM_INVALID     ((cg_menuitem_t)0u)
#define CG_MENU_BAR_H           22
#define CG_MENUITEMF_SEPARATOR  0x02u
#define CG_MENUITEMF_TICKED     0x04u
#define CG_MENUITEMF_TICKABLE   0x08u
#define CG_MENUITEMF_CHECKBOX   CG_MENUITEMF_TICKABLE
#define CG_MENU_IMAGE_NONE      0xffu

typedef struct API_GUI_MENUS {
    cg_menu_t     (*create_title)           (const char *titlestring);
    cg_menuitem_t (*create_item)            (cg_menu_t *menuid, uint8_t menutitleindex, const char *itemstring);
    void          (*destroy)                (cg_menu_t *menuid);
    void          (*attach_to_window)       (cg_menu_t menuid, CGWindow windowid);
    int16_t       (*attach_images_itemlist) (cg_menu_t *menuid, ItemLists_t *imageitemlist);
    void          (*set_callback)           (cg_menuitem_t menuitemid, SBOS_MenuCallback callback, void *userdata);
    void          (*set_flags)              (const cg_menuitem_t *menuitemid, uint32_t clearflags, uint32_t setflags);
    uint32_t      (*get_flags)              (const cg_menuitem_t *menuitemid);
    void          (*set_item_image)         (const cg_menuitem_t *menuitemid, uint8_t imageindex);
    uint8_t       (*active)                 (void);
    void          (*close)                  (void);
} API_GUI_MENUS;

typedef API_GUI_MENUS API_GUI_Menus;

#ifndef GUICoderGirl
#define GUICoderGirl (API->gui)
#endif

/* @brief Creates a menu and its title, returning the menu handle. */
#define SBOS_CreateMenuTitle(titlestring) \
    (GUICoderGirl->menus->create_title(titlestring))

/* @brief Adds an item to a menu title and returns its menu-item handle. */
#define SBOS_CreateMenuItem(menuid, menutitleindex, itemstring) \
    (GUICoderGirl->menus->create_item(menuid, menutitleindex, itemstring))

/* @brief Destroys a menu and releases its menu resources. */
#define SBOS_DestroyMenu(menuid) \
    (GUICoderGirl->menus->destroy(menuid))

/* @brief Attaches a menu bar/menu to a GUI window. */
#define SBOS_AttachMenuToWindow(menuid, windowid) \
    (GUICoderGirl->menus->attach_to_window(menuid, windowid))

/* @brief Associates an image item-list with a menu. */
#define SBOS_MenuAttachImagesItemlist(menuid, imageitemlist) \
    (GUICoderGirl->menus->attach_images_itemlist(menuid, imageitemlist))

/* @brief Assigns a callback and user pointer to a menu item. */
#define SBOS_MenuCallBack(menuitemid, callback, userdata) \
    (GUICoderGirl->menus->set_callback(menuitemid, callback, userdata))

/* @brief Clears/sets menu-item state flags. */
#define SBOS_MenuSetFlags(menuitemid, clearflags, setflags) \
    (GUICoderGirl->menus->set_flags(menuitemid, clearflags, setflags))

/* @brief Returns the current flags for a menu item. */
#define SBOS_MenuGetFlags(menuitemid) \
    (GUICoderGirl->menus->get_flags(menuitemid))

/* @brief Sets the image index used by a menu item. */
#define SBOS_SetMenuItemImage(menuitemid, imageindex) \
    (GUICoderGirl->menus->set_item_image(menuitemid, imageindex))

/* @brief Returns whether the menu system currently has an active/open menu. */
#define SBOS_MenuActive() \
    (GUICoderGirl->menus->active())

/* @brief Closes the currently active menu. */
#define SBOS_MenuClose() \
    (GUICoderGirl->menus->close())

#ifdef __cplusplus
}
#endif

#endif // SBAPI_MENUS_H
