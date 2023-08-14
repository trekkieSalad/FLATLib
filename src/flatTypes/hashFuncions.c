#include <dataStructFunc.h>
#include <set.h>

#define DEFINE_HASH_FUNCTION(TYPE, SUFFIX, MULTIPLIER) \
    unsigned int SUFFIX##HashFunction(const generic_flat_pointer data, size_t size) { \
        const TYPE value = *(const TYPE *)data; \
        return (unsigned int) (value * MULTIPLIER) % size; \
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

unsigned int stringHashFunction(const generic_flat_pointer data, size_t size);
unsigned int setHashFunction(const generic_flat_pointer data, size_t size);

unsigned int (*hashFunctions[_TYPE_COUNT])(const generic_flat_pointer data, size_t size) = {
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
    stringHashFunction,
    setHashFunction,
    NULL,
};

unsigned int stringHashFunction(const generic_flat_pointer data, size_t size){
    const char *value = (const char *) data;
    unsigned int hash = 0;
    for (size_t i = 0; i < strlen(value); i++){
        hash += value[i];
    }
    return hash % size;
}

unsigned int setHashFunction(const generic_flat_pointer data, size_t size){
    const Set value = (const Set) data;
    return setHashcode(value) % size;
}

hashFunction getHashFunction(Type type){
    return hashFunctions[type];
}