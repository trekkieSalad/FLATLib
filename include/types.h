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
    LONG_DOUBLE,
    STRING,
    SET,
    USER_DEFINED,
    _TYPE_COUNT,
}Type;


typedef unsigned int (*hashFunction)(const void *data, size_t size);
typedef bool (*equalsFunction)(const void *a, const void *b);
typedef char * (*toStringFunction)(const void *data);
typedef void * (*cloneFunction)(const void *data);
typedef void (*freeFunction)(void *data);

hashFunction getHashFunction(Type);
equalsFunction getEqualsFunction(Type);
toStringFunction getToStringFunction(Type);
cloneFunction getCloneFunction(Type);
freeFunction getFreeFunction(Type);
size_t getTypeSize(Type);

#endif // TYPES_H