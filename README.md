json2c
======

Convert JSON to C data literals.

For example this...

```javascript
{
     "firstName": "John",
     "lastName": "Smith",
     "age": 25,
     "address":
     {
         "streetAddress": "21 2nd Street",
         "city": "New York",
         "state": "NY",
         "postalCode": "10021"
     },
     "phoneNumber":
     [
         {
           "type": "home",
           "number": "212 555-1234"
         },
         {
           "type": "fax",
           "number": "646 555-4567"
         }
     ]
}
```

becomes this...

```c
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
```

and this...

```c
customer customerObject = {
    .firstName = "John", 
    .lastName = "Smith", 
    .age = 25, 
    .address = {
        .streetAddress = "21 2nd Street", 
        .city = "New York", 
        .state = "NY", 
        .postalCode = "10021"
    }, 
    .phoneNumber = {
        {
            .type = "home", 
            .number = "212 555-1234"
        }, 
        {
            .type = "fax", 
            .number = "646 555-4567"
        }
    }
};
```

Why?
----

Generating data literals in C is useful for embedding configuration, mark up, or even whole databases into C programs. It has several advantages over loading the data at runtime - it doesn't require a parser, gives lightning fast access, and uses minimal memory. This is because the whole thing is stripped of meta-data such as field names, there is no hashing required, and all access patterns are resolved at compile-time.

Converting from JSON is a natural choice because of the abundance of tools that can generate and edit it, and its ease of construction by hand.

An example application for this tool might be in the construction of an RPG. If you have a large amount of data to enter such as weapon and item details you could do the data entry in JSON and then use this tool to embed it directly at compile time.


Usage
-----

Simply run the script on some JSON file to create a header and source file as output in the same directory.

```
pip install json2c
json2c customer.json
```

Run with `--help` to see the full list of options. This includes lots of options for changing the style and conventions of the generated C code.


How Does it Work?
-----------------

The basic process of `json2c` is simple. JSON literals such as `str`, `int`, and `bool`, can be converted directly to C types. Even hashes are easily converted to C structs, with a type definition to go with them. The trouble comes with trying to convert lists, as C does not support heterogeneous lists.

But while JSON has heterogeneous lists, most JSON data you encounter in the wild tends to use lists somewhat homogeneously. So if it encounters a list of data `json2c` attempts to _unify_ all the types within the list into a single matching type. It does this using a number of heuristics. For example it can unify `null` with various types using pointers and other tricks. It can add missing entries into hashes, or convert two arrays of different fixed sizes into variable length arrays. It can also automatically promote basic types together, such as converting `int` to `float` or `bool` to `int`.

This has proven fairly effective for almost all example JSON data I've found - and while some of the heuristics don't always make sense, `json2c` is almost always capable of producing something.



