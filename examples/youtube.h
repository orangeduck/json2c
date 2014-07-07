#ifndef youtube_h
#define youtube_h

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

enum { YOUTUBE_DATA_ITEMS_ENTRY_TAGS_COUNT = 3 };

typedef const char* youtube_data_items_entry_tags[YOUTUBE_DATA_ITEMS_ENTRY_TAGS_COUNT];

typedef struct {
    const char* _default;
    const char* hqDefault;
} youtube_data_items_entry_thumbnail;

typedef struct {
    const char* _default;
} youtube_data_items_entry_player;

typedef struct {
    const char* _1;
    const char* _5;
    const char* _6;
} youtube_data_items_entry_content;

typedef struct {
    const char* value;
    const char* reason;
} youtube_data_items_entry_status;

typedef struct {
    const char* syndicate;
    const char* commentVote;
    const char* rate;
    const char* list;
    const char* comment;
    const char* embed;
    const char* videoRespond;
} youtube_data_items_entry_accessControl;

typedef struct {
    const char* id;
    const char* uploaded;
    const char* updated;
    const char* uploader;
    const char* category;
    const char* title;
    const char* description;
    youtube_data_items_entry_tags tags;
    youtube_data_items_entry_thumbnail thumbnail;
    youtube_data_items_entry_player player;
    youtube_data_items_entry_content content;
    long duration;
    const char* aspectRatio;
    double rating;
    long ratingCount;
    long viewCount;
    long favoriteCount;
    long commentCount;
    youtube_data_items_entry_status status;
    youtube_data_items_entry_accessControl accessControl;
} youtube_data_items_entry;

enum { YOUTUBE_DATA_ITEMS_COUNT = 1 };

typedef youtube_data_items_entry youtube_data_items[YOUTUBE_DATA_ITEMS_COUNT];

typedef struct {
    const char* updated;
    long totalItems;
    long startIndex;
    long itemsPerPage;
    youtube_data_items items;
} youtube_data;

typedef struct {
    const char* apiVersion;
    youtube_data data;
} youtube;

extern youtube youtube_object;

#endif
