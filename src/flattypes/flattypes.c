#include <flattypes_priv.h>

char *flat_type_to_string(FlatType type) {
    char *typeStrings[] = {
        "char",         "unsigned char",        "short",        "unsigned short", 
        "int",          "unsigned int",         "long",         "unsigned long", 
        "long long",    "unsigned long long",   "float",        "double", 
        "char *",       "Set",                  "User Type",    "Unknown Type"
    };

    if (type >= 0 && type < _TYPE_COUNT) {
        return typeStrings[type];
    }
    return typeStrings[_TYPE_COUNT]; // Unknown Type
}