#ifndef FACEBOOK_H
#define FACEBOOK_H

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct {
    const char* name;
    const char* id;
} facebook_data_entry_from;

typedef struct {
    const char* name;
    const char* link;
} facebook_data_entry_actions_entry;

enum { FACEBOOK_DATA_ENTRY_ACTIONS_COUNT = 2 };

typedef facebook_data_entry_actions_entry facebook_data_entry_actions[FACEBOOK_DATA_ENTRY_ACTIONS_COUNT];

typedef struct {
    const char* id;
    facebook_data_entry_from from;
    const char* message;
    facebook_data_entry_actions actions;
    const char* type;
    const char* created_time;
    const char* updated_time;
} facebook_data_entry;

enum { FACEBOOK_DATA_COUNT = 2 };

typedef facebook_data_entry facebook_data[FACEBOOK_DATA_COUNT];

typedef struct {
    facebook_data data;
} facebook;

extern facebook facebook_object;

#endif
