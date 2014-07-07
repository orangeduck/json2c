#ifndef WIDGET_H
#define WIDGET_H

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct {
    const char* title;
    const char* name;
    long width;
    long height;
} widgetWidgetWindow;

typedef struct {
    const char* src;
    const char* name;
    long hOffset;
    long vOffset;
    const char* alignment;
} widgetWidgetImage;

typedef struct {
    const char* data;
    long size;
    const char* style;
    const char* name;
    long hOffset;
    long vOffset;
    const char* alignment;
    const char* onMouseUp;
} widgetWidgetText;

typedef struct {
    const char* debug;
    widgetWidgetWindow window;
    widgetWidgetImage image;
    widgetWidgetText text;
} widgetWidget;

typedef struct {
    widgetWidget widget;
} widget;

extern widget widgetObject;

#endif
