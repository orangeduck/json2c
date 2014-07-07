#ifndef scores_h
#define scores_h

typedef struct {
    long length;
    const char** values;
} json_entry_points;

typedef struct {
    long index;
    const char* name;
    json_entry_points points;
} json_entry;

typedef json_entry json[3];

extern json scores;

#endif
