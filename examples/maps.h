#ifndef maps_h
#define maps_h

typedef double json_markers_entry_point[2];

typedef struct {
    const char* markerImage;
    const char* fixture;
    const char* tv;
    json_markers_entry_point point;
    const char* previousScore;
    const char* homeTeam;
    const char* information;
    const char* capacity;
    const char* awayTeam;
} json_markers_entry;

typedef json_markers_entry json_markers[3];

typedef struct {
    json_markers markers;
} json;

extern json maps;

#endif
