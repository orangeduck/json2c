#ifndef glossary_h
#define glossary_h

typedef const char* json_glossary_GlossDiv_GlossList_GlossEntry_GlossDef_GlossSeeAlso[2];

typedef struct {
    const char* para;
    json_glossary_GlossDiv_GlossList_GlossEntry_GlossDef_GlossSeeAlso GlossSeeAlso;
} json_glossary_GlossDiv_GlossList_GlossEntry_GlossDef;

typedef struct {
    const char* ID;
    const char* SortAs;
    const char* GlossTerm;
    const char* Acronym;
    const char* Abbrev;
    json_glossary_GlossDiv_GlossList_GlossEntry_GlossDef GlossDef;
    const char* GlossSee;
} json_glossary_GlossDiv_GlossList_GlossEntry;

typedef struct {
    json_glossary_GlossDiv_GlossList_GlossEntry GlossEntry;
} json_glossary_GlossDiv_GlossList;

typedef struct {
    const char* title;
    json_glossary_GlossDiv_GlossList GlossList;
} json_glossary_GlossDiv;

typedef struct {
    const char* title;
    json_glossary_GlossDiv GlossDiv;
} json_glossary;

typedef struct {
    json_glossary glossary;
} json;

extern json glossary;

#endif
