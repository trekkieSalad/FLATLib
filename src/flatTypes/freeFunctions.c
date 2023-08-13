#include <dataStructFunc.h>
#include <set.h>

#define DEFINE_FREE_FUNCTION(TYPE, SUFFIX) \
    void SUFFIX##FreeFunction(generic_flat_pointer data) { \
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

void stringFreeFunction(generic_flat_pointer data);
void setFreeFunction(generic_flat_pointer data);

void (*FreeFunctions[_TYPE_COUNT])(generic_flat_pointer data) = {
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
    stringFreeFunction,
    setFreeFunction,
    NULL,
};

void stringFreeFunction(generic_flat_pointer data) {
    if (!data)
        return;
    char *str = (char *)data;
    free(str);
}

void setFreeFunction(generic_flat_pointer data){
    Set set = (const Set) data;

    setDestroy(set);
}

freeFunction getFreeFunction(Type type){
    return FreeFunctions[type];
}