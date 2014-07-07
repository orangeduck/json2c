#ifndef twitter_h
#define twitter_h

typedef struct {
    const char* result_type;
    long recent_retweets;
} json_results_entry_metadata;

typedef struct {
    const char* text;
    long to_user_id;
    const char* to_user;
    const char* from_user;
    json_results_entry_metadata metadata;
    long id;
    long from_user_id;
    const char* iso_language_code;
    const char* source;
    const char* profile_image_url;
    const char* created_at;
} json_results_entry;

typedef json_results_entry json_results[1];

typedef struct {
    json_results results;
    long since_id;
    long max_id;
    const char* refresh_url;
    long results_per_page;
    const char* next_page;
    double completed_in;
    long page;
    const char* query;
} json;

extern json twitter;

#endif
