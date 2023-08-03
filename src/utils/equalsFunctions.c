#include "types.h"
#include <stdbool.h>

#define DEFINE_EQUALS_FUNCTION(TYPE, SUFFIX) \
    bool SUFFIX##EqualsFunction(const void *data1, const void *data2) { \
        TYPE value1 = *(TYPE *)data1; \
        TYPE value2 = *(TYPE *)data2; \
        return value1 == value2; \
    }

DEFINE_EQUALS_FUNCTION(char, char)
DEFINE_EQUALS_FUNCTION(unsigned char, uchar)
DEFINE_EQUALS_FUNCTION(short, short)
DEFINE_EQUALS_FUNCTION(unsigned short, ushort)
DEFINE_EQUALS_FUNCTION(int, int)
DEFINE_EQUALS_FUNCTION(unsigned int, uint)
DEFINE_EQUALS_FUNCTION(long, long)
DEFINE_EQUALS_FUNCTION(unsigned long, ulong)
DEFINE_EQUALS_FUNCTION(long long, longlong)
DEFINE_EQUALS_FUNCTION(unsigned long long, ulonglong)
DEFINE_EQUALS_FUNCTION(float, float)
DEFINE_EQUALS_FUNCTION(double, double)
DEFINE_EQUALS_FUNCTION(long double, longdouble)

bool stringEqualsFunction(const void *data1, const void *data2);

bool (*equalsFunctions[_TYPE_COUNT])(const void *data1, const void *data2) = {
    NULL,
    charEqualsFunction,
    ucharEqualsFunction,
    shortEqualsFunction,
    ushortEqualsFunction,
    intEqualsFunction,
    uintEqualsFunction,
    longEqualsFunction,
    ulongEqualsFunction,
    longlongEqualsFunction,
    ulonglongEqualsFunction,
    floatEqualsFunction,
    doubleEqualsFunction,
    longdoubleEqualsFunction,
    stringEqualsFunction,
    NULL,
};

bool stringEqualsFunction(const void *data1, const void *data2) {
    char *value1 = *(char **)data1;
    char *value2 = *(char **)data2;
    return strcmp(value1, value2) == 0;
}

equalsFunction getEqualsFunction(Type type) {
    return equalsFunctions[type];
}