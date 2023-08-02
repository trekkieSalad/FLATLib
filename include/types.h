#ifndef SET_TYPES_H
#define SET_TYPES_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef enum {
    _NUL, // placeholder prevents type null-checking false alarms on CHAR
    CHAR,
    UCHAR,
    SHORT,
    USHORT,
    INT,
    UINT,
    LONG,
    ULONG,
    LONG_LONG,
    ULONG_LONG,
    FLOAT,
    DOUBLE,
    UDOUBLE,
    LONG_DOUBLE,
    STRING,
    USER_DEFINED,
}Type;


typedef unsigned int (*hashFunction)(const void *data, size_t size);
typedef bool (*equalsFunction)(const void *a, const void *b);
typedef char * (*toStringFunction)(const void *data);

hashFunction getHashFunction(Type);
equalsFunction getEqualsFunction(Type);
toStringFunction getToStringFunction(Type);

#endif // TYPES_H