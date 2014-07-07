#ifndef facebook_h
#define facebook_h

typedef struct {
    const char* name;
    const char* id;
} json_data_entry_from;

typedef struct {
    const char* name;
    const char* link;
} json_data_entry_actions_entry;

typedef json_data_entry_actions_entry json_data_entry_actions[2];

typedef struct {
    const char* id;
    json_data_entry_from from;
    const char* message;
    json_data_entry_actions actions;
    const char* type;
    const char* created_time;
    const char* updated_time;
} json_data_entry;

typedef json_data_entry json_data[2];

typedef struct {
    json_data data;
} json;

extern json facebook;

#endif
