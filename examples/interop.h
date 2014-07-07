#ifndef INTEROP_H
#define INTEROP_H

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct {
    const char* Url;
    const char* Height;
    const char* Width;
} interopResultSetResultEntryThumbnail;

typedef struct {
    const char* Title;
    const char* Summary;
    const char* Url;
    const char* ClickUrl;
    const char* RefererUrl;
    long FileSize;
    const char* FileFormat;
    const char* Height;
    const char* Width;
    interopResultSetResultEntryThumbnail Thumbnail;
} interopResultSetResultEntry;

enum { INTEROPRESULTSETRESULTCOUNT = 2 };

typedef interopResultSetResultEntry interopResultSetResult[INTEROPRESULTSETRESULTCOUNT];

typedef struct {
    const char* totalResultsAvailable;
    long totalResultsReturned;
    long firstResultPosition;
    interopResultSetResult Result;
} interopResultSet;

typedef struct {
    interopResultSet ResultSet;
} interop;

extern interop interopObject;

#endif
