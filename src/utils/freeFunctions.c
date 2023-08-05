#include "types.h"
#include <set.h>

#define DEFINE_FREE_FUNCTION(TYPE, SUFFIX) \
    void SUFFIX##FreeFunction(void *data) { \
        if (!data) \
            return; \
        free(data); \
    }

DEFINE_FREE_FUNCTION(char, char)
DEFINE_FREE_FUNCTION(unsigned char, uchar)
DEFINE_FREE_FUNCTION(short, short)
DEFINE_FREE_FUNCTION(unsigned short, ushort)
DEFINE_FREE_FUNCTION(int, int)
DEFINE_FREE_FUNCTION(unsigned int, uint)
DEFINE_FREE_FUNCTION(long, long)
DEFINE_FREE_FUNCTION(unsigned long, ulong)
DEFINE_FREE_FUNCTION(long long, longlong)
DEFINE_FREE_FUNCTION(unsigned long long, ulonglong)
DEFINE_FREE_FUNCTION(float, float)
DEFINE_FREE_FUNCTION(double, double)
DEFINE_FREE_FUNCTION(long double, longdouble)

void stringFreeFunction(void *data);
void setFreeFunction(void *data);

void (*FreeFunctions[_TYPE_COUNT])(void *data) = {
    NULL,
    charFreeFunction,
    ucharFreeFunction,
    shortFreeFunction,
    ushortFreeFunction,
    intFreeFunction,
    uintFreeFunction,
    longFreeFunction,
    ulongFreeFunction,
    longlongFreeFunction,
    ulonglongFreeFunction,
    floatFreeFunction,
    doubleFreeFunction,
    longdoubleFreeFunction,
    stringFreeFunction,
    setFreeFunction,
    NULL,
};

void stringFreeFunction(void *data) {
    if (!data)
        return;
    char *str = (char *)data;
    free(str);
}

void setFreeFunction(void *data){
    Set *set = data;

    setDestroy(set);
}

freeFunction getFreeFunction(Type type){
    return FreeFunctions[type];
}