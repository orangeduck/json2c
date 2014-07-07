#ifndef TWITTER_H
#define TWITTER_H

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct {
    const char* result_type;
    long recent_retweets;
} twitter_results_entry_metadata;

typedef struct {
    const char* text;
    long to_user_id;
    const char* to_user;
    const char* from_user;
    twitter_results_entry_metadata metadata;
    long id;
    long from_user_id;
    const char* iso_language_code;
    const char* source;
    const char* profile_image_url;
    const char* created_at;
} twitter_results_entry;

enum { TWITTER_RESULTS_COUNT = 1 };

typedef twitter_results_entry twitter_results[TWITTER_RESULTS_COUNT];

typedef struct {
    twitter_results results;
    long since_id;
    long max_id;
    const char* refresh_url;
    long results_per_page;
    const char* next_page;
    double completed_in;
    long page;
    const char* query;
} twitter;

extern twitter twitter_object;

#endif
