#ifndef YOUTUBE_H
#define YOUTUBE_H

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

enum { YOUTUBEDATAITEMSENTRYTAGSCOUNT = 3 };

typedef const char* youtubeDataItemsEntryTags[YOUTUBEDATAITEMSENTRYTAGSCOUNT];

typedef struct {
    const char* _default;
    const char* hqDefault;
} youtubeDataItemsEntryThumbnail;

typedef struct {
    const char* _default;
} youtubeDataItemsEntryPlayer;

typedef struct {
    const char* _1;
    const char* _5;
    const char* _6;
} youtubeDataItemsEntryContent;

typedef struct {
    const char* value;
    const char* reason;
} youtubeDataItemsEntryStatus;

typedef struct {
    const char* syndicate;
    const char* commentVote;
    const char* rate;
    const char* list;
    const char* comment;
    const char* embed;
    const char* videoRespond;
} youtubeDataItemsEntryAccessControl;

typedef struct {
    const char* id;
    const char* uploaded;
    const char* updated;
    const char* uploader;
    const char* category;
    const char* title;
    const char* description;
    youtubeDataItemsEntryTags tags;
    youtubeDataItemsEntryThumbnail thumbnail;
    youtubeDataItemsEntryPlayer player;
    youtubeDataItemsEntryContent content;
    long duration;
    const char* aspectRatio;
    double rating;
    long ratingCount;
    long viewCount;
    long favoriteCount;
    long commentCount;
    youtubeDataItemsEntryStatus status;
    youtubeDataItemsEntryAccessControl accessControl;
} youtubeDataItemsEntry;

enum { YOUTUBEDATAITEMSCOUNT = 1 };

typedef youtubeDataItemsEntry youtubeDataItems[YOUTUBEDATAITEMSCOUNT];

typedef struct {
    const char* updated;
    long totalItems;
    long startIndex;
    long itemsPerPage;
    youtubeDataItems items;
} youtubeData;

typedef struct {
    const char* apiVersion;
    youtubeData data;
} youtube;

extern youtube youtubeObject;

#endif
