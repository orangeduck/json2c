#ifndef PRODUCT_H
#define PRODUCT_H

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct {
    const char* type;
    const char* description;
    bool required;
} product_properties_id;

typedef struct {
    const char* description;
    const char* type;
    bool required;
} product_properties_name;

typedef struct {
    const char* type;
    long minimum;
    bool required;
} product_properties_price;

typedef struct {
    const char* type;
} product_properties_tags_items;

typedef struct {
    const char* type;
    product_properties_tags_items items;
} product_properties_tags;

typedef struct {
    product_properties_id id;
    product_properties_name name;
    product_properties_price price;
    product_properties_tags tags;
} product_properties;

typedef struct {
    const char* name;
    product_properties properties;
} product;

extern product product_object;

#endif
