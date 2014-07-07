#ifndef COLORS_H
#define COLORS_H

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct {
    const char* colorName;
    const char* hexValue;
} colorsColorsArrayEntry;

enum { COLORSCOLORSARRAYCOUNT = 7 };

typedef colorsColorsArrayEntry colorsColorsArray[COLORSCOLORSARRAYCOUNT];

typedef struct {
    colorsColorsArray colorsArray;
} colors;

extern colors colorsObject;

#endif
