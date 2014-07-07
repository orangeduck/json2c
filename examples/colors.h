#ifndef colors_h
#define colors_h

typedef struct {
    const char* colorName;
    const char* hexValue;
} json_colorsArray_entry;

typedef json_colorsArray_entry json_colorsArray[7];

typedef struct {
    json_colorsArray colorsArray;
} json;

extern json colors;

#endif
