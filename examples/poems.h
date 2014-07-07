#ifndef POEMS_H
#define POEMS_H

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct {
    long length;
    const char** values;
} poems_entry_about;

typedef struct {
    const char* id_author;
    long index;
    const char* id_poem;
    double score;
    const char* poem;
    const char* author;
    const char* title;
    long votes;
    poems_entry_about about;
} poems_entry;

enum { POEMS_COUNT = 2 };

typedef poems_entry poems[POEMS_COUNT];

extern poems poems_object;

#endif
