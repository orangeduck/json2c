#ifndef MENU_H
#define MENU_H

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct {
    const char* value;
    const char* onclick;
} menu_menu_popup_menuitem_entry;

enum { MENU_MENU_POPUP_MENUITEM_COUNT = 3 };

typedef menu_menu_popup_menuitem_entry menu_menu_popup_menuitem[MENU_MENU_POPUP_MENUITEM_COUNT];

typedef struct {
    menu_menu_popup_menuitem menuitem;
} menu_menu_popup;

typedef struct {
    const char* id;
    const char* value;
    menu_menu_popup popup;
} menu_menu;

typedef struct {
    menu_menu menu;
} menu;

extern menu menu_object;

#endif
