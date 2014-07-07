#ifndef menu_h
#define menu_h

typedef struct {
    const char* value;
    const char* onclick;
} json_menu_popup_menuitem_entry;

typedef json_menu_popup_menuitem_entry json_menu_popup_menuitem[3];

typedef struct {
    json_menu_popup_menuitem menuitem;
} json_menu_popup;

typedef struct {
    const char* id;
    const char* value;
    json_menu_popup popup;
} json_menu;

typedef struct {
    json_menu menu;
} json;

extern json menu;

#endif
