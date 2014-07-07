#ifndef FLICKR_H
#define FLICKR_H

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct {
    const char* m;
} flickr_items_entry_media;

typedef struct {
    const char* title;
    const char* link;
    flickr_items_entry_media media;
    const char* date_taken;
    const char* description;
    const char* published;
    const char* author;
    const char* author_id;
    const char* tags;
} flickr_items_entry;

enum { FLICKR_ITEMS_COUNT = 1 };

typedef flickr_items_entry flickr_items[FLICKR_ITEMS_COUNT];

typedef struct {
    const char* title;
    const char* link;
    const char* description;
    const char* modified;
    const char* generator;
    flickr_items items;
} flickr;

extern flickr flickr_object;

#endif
