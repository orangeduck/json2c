#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct {
    const char* streetAddress;
    const char* city;
    const char* state;
    const char* postalCode;
} customerAddress;

typedef struct {
    const char* type;
    const char* number;
} customerPhoneNumberEntry;

enum { CUSTOMERPHONENUMBERCOUNT = 2 };

typedef customerPhoneNumberEntry customerPhoneNumber[CUSTOMERPHONENUMBERCOUNT];

typedef struct {
    const char* firstName;
    const char* lastName;
    long age;
    customerAddress address;
    customerPhoneNumber phoneNumber;
} customer;

extern customer customerObject;

#endif
