#include "scores.h"

#include <stdlib.h>

json scores = {
    {
        .index = 1, 
        .name = "mike", 
        .points = {
            .length = 3, 
            .values = (const char*[]){"blah", NULL, "test"}
        }
    }, 
    {
        .index = 2, 
        .name = "tom", 
        .points = {
            .length = 4, 
            .values = (const char*[]){"one", "two", "three", NULL}
        }
    }, 
    {
        .index = 3, 
        .name = "dan", 
        .points = {
            .length = 2, 
            .values = (const char*[]){"foo", "bar"}
        }
    }
};

