#ifndef viewer_h
#define viewer_h

typedef struct {
    const char* id;
    const char* label;
} json_menu_items_entry_entry;

typedef json_menu_items_entry_entry* json_menu_items[22];

typedef struct {
    const char* header;
    json_menu_items items;
} json_menu;

typedef struct {
    json_menu menu;
} json;

extern json viewer;

#endif
