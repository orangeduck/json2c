#ifndef product_h
#define product_h

#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    const char* type;
    const char* description;
    bool required;
} customer_properties_id;

typedef struct {
    const char* description;
    const char* type;
    bool required;
} customer_properties_name;

typedef struct {
    const char* type;
    long minimum;
    bool required;
} customer_properties_price;

typedef struct {
    const char* type;
} customer_properties_tags_items;

typedef struct {
    const char* type;
    customer_properties_tags_items items;
} customer_properties_tags;

typedef struct {
    customer_properties_id id;
    customer_properties_name name;
    customer_properties_price price;
    customer_properties_tags tags;
} customer_properties;

typedef struct {
    const char* name;
    customer_properties properties;
} customer;

extern customer object;

#endif
