#ifndef GLOSSARY_H
#define GLOSSARY_H

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

enum { GLOSSARYGLOSSARYGLOSSDIVGLOSSLISTGLOSSENTRYGLOSSDEFGLOSSSEEALSOCOUNT = 2 };

typedef const char* glossaryGlossaryGlossDivGlossListGlossEntryGlossDefGlossSeeAlso[GLOSSARYGLOSSARYGLOSSDIVGLOSSLISTGLOSSENTRYGLOSSDEFGLOSSSEEALSOCOUNT];

typedef struct {
    const char* para;
    glossaryGlossaryGlossDivGlossListGlossEntryGlossDefGlossSeeAlso GlossSeeAlso;
} glossaryGlossaryGlossDivGlossListGlossEntryGlossDef;

typedef struct {
    const char* ID;
    const char* SortAs;
    const char* GlossTerm;
    const char* Acronym;
    const char* Abbrev;
    glossaryGlossaryGlossDivGlossListGlossEntryGlossDef GlossDef;
    const char* GlossSee;
} glossaryGlossaryGlossDivGlossListGlossEntry;

typedef struct {
    glossaryGlossaryGlossDivGlossListGlossEntry GlossEntry;
} glossaryGlossaryGlossDivGlossList;

typedef struct {
    const char* title;
    glossaryGlossaryGlossDivGlossList GlossList;
} glossaryGlossaryGlossDiv;

typedef struct {
    const char* title;
    glossaryGlossaryGlossDiv GlossDiv;
} glossaryGlossary;

typedef struct {
    glossaryGlossary glossary;
} glossary;

extern glossary glossaryObject;

#endif
