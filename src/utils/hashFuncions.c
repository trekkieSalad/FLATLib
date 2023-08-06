#include "types.h"
#include <set.h>

#define DEFINE_HASH_FUNCTION(TYPE, SUFFIX, MULTIPLIER) \
    unsigned int SUFFIX##HashFunction(const void *data, size_t size) { \
        TYPE value = *(TYPE *)data; \
        return (int) (value * MULTIPLIER) % size; \
    }

DEFINE_HASH_FUNCTION(char, char, 1)
DEFINE_HASH_FUNCTION(unsigned char, uchar, 1)
DEFINE_HASH_FUNCTION(short, short, 1)
DEFINE_HASH_FUNCTION(unsigned short, ushort, 1)
DEFINE_HASH_FUNCTION(int, int, 1)
DEFINE_HASH_FUNCTION(unsigned int, uint, 1)
DEFINE_HASH_FUNCTION(long, long, 1)
DEFINE_HASH_FUNCTION(unsigned long, ulong, 1)
DEFINE_HASH_FUNCTION(long long, longlong, 1)
DEFINE_HASH_FUNCTION(unsigned long long, ulonglong, 1)
DEFINE_HASH_FUNCTION(float, float, 1000)
DEFINE_HASH_FUNCTION(double, double, 1000)
DEFINE_HASH_FUNCTION(long double, longdouble, 1000)

unsigned int stringHashFunction(const void *data, size_t size);
unsigned int setHashFunction(const void *data, size_t size);

unsigned int (*hashFunctions[_TYPE_COUNT])(const void *data, size_t size) = {
    NULL,
    charHashFunction,
    ucharHashFunction,
    shortHashFunction,
    ushortHashFunction,
    intHashFunction,
    uintHashFunction,
    longHashFunction,
    ulongHashFunction,
    longlongHashFunction,
    ulonglongHashFunction,
    floatHashFunction,
    doubleHashFunction,
    longdoubleHashFunction,
    stringHashFunction,
    setHashFunction,
    NULL,
};

unsigned int stringHashFunction(const void *data, size_t size){
    char *value = (char *) data;
    unsigned int hash = 0;
    for (size_t i = 0; i < strlen(value); i++){
        hash += value[i];
    }
    return hash % size;
}

unsigned int setHashFunction(const void *data, size_t size){
    Set *value = *(Set **)data;
    return value->hashcode % size;
}

hashFunction getHashFunction(Type type){
    return hashFunctions[type];
}