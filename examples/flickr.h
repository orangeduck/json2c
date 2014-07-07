#ifndef flickr_h
#define flickr_h

typedef struct {
    const char* m;
} json_items_entry_media;

typedef struct {
    const char* title;
    const char* link;
    json_items_entry_media media;
    const char* date_taken;
    const char* description;
    const char* published;
    const char* author;
    const char* author_id;
    const char* tags;
} json_items_entry;

typedef json_items_entry json_items[1];

typedef struct {
    const char* title;
    const char* link;
    const char* description;
    const char* modified;
    const char* generator;
    json_items items;
} json;

extern json flickr;

#endif
