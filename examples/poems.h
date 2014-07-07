#ifndef poems_h
#define poems_h

typedef struct {
    long length;
    const char** values;
} json_entry_about;

typedef struct {
    const char* id_author;
    long index;
    const char* id_poem;
    double score;
    const char* poem;
    const char* author;
    const char* title;
    long votes;
    json_entry_about about;
} json_entry;

typedef json_entry json[2];

extern json poems;

#endif
