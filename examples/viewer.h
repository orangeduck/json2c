#ifndef viewer_h
#define viewer_h

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct {
    const char* id;
    const char* label;
} viewer_menu_items_entry;

enum { viewer_menu_items_count = 22 };

typedef viewer_menu_items_entry* viewer_menu_items[viewer_menu_items_count];

typedef struct {
    const char* header;
    viewer_menu_items items;
} viewer_menu;

typedef struct {
    viewer_menu menu;
} viewer;

extern viewer viewer_object;

#endif
