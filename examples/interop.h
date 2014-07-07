#ifndef interop_h
#define interop_h

typedef struct {
    const char* Url;
    const char* Height;
    const char* Width;
} json_ResultSet_Result_entry_Thumbnail;

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
    json_ResultSet_Result_entry_Thumbnail Thumbnail;
} json_ResultSet_Result_entry;

typedef json_ResultSet_Result_entry json_ResultSet_Result[2];

typedef struct {
    const char* totalResultsAvailable;
    long totalResultsReturned;
    long firstResultPosition;
    json_ResultSet_Result Result;
} json_ResultSet;

typedef struct {
    json_ResultSet ResultSet;
} json;

extern json interop;

#endif
