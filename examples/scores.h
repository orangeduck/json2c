#ifndef SCORES_H
#define SCORES_H

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct {
    long length;
    const char** values;
} scores_entry_points;

typedef struct {
    long index;
    const char* name;
    scores_entry_points points;
} scores_entry;

enum { SCORES_COUNT = 3 };

typedef scores_entry scores[SCORES_COUNT];

extern scores scores_object;

#endif
