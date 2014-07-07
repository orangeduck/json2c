#ifndef MAPS_H
#define MAPS_H

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

enum { MAPSMARKERSENTRYPOINTCOUNT = 2 };

typedef double mapsMarkersEntryPoint[MAPSMARKERSENTRYPOINTCOUNT];

typedef struct {
    mapsMarkersEntryPoint point;
    const char* homeTeam;
    const char* awayTeam;
    const char* markerImage;
    const char* information;
    const char* fixture;
    const char* capacity;
    const char* previousScore;
    const char* tv;
} mapsMarkersEntry;

enum { MAPSMARKERSCOUNT = 3 };

typedef mapsMarkersEntry mapsMarkers[MAPSMARKERSCOUNT];

typedef struct {
    mapsMarkers markers;
} maps;

extern maps mapsObject;

#endif
