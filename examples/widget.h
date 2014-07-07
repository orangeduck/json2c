#ifndef widget_h
#define widget_h

typedef struct {
    const char* title;
    const char* name;
    long width;
    long height;
} json_widget_window;

typedef struct {
    const char* src;
    const char* name;
    long hOffset;
    long vOffset;
    const char* alignment;
} json_widget_image;

typedef struct {
    const char* data;
    long size;
    const char* style;
    const char* name;
    long hOffset;
    long vOffset;
    const char* alignment;
    const char* onMouseUp;
} json_widget_text;

typedef struct {
    const char* debug;
    json_widget_window window;
    json_widget_image image;
    json_widget_text text;
} json_widget;

typedef struct {
    json_widget widget;
} json;

extern json widget;

#endif
