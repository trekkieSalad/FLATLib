#include <datastructfunc.h>
#include <flatset.h>

#define DEFINE_HASH_FUNCTION(TYPE, SUFFIX, MULTIPLIER) \
    unsigned int SUFFIX##_hash_function(const generic_flat_pointer data, size_t size) { \
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

unsigned int string_hash_function(const generic_flat_pointer data, size_t size);
unsigned int set_hash_function(const generic_flat_pointer data, size_t size);

unsigned int (*_hash_functions[_TYPE_COUNT])(const generic_flat_pointer data, size_t size) = {
    char_hash_function,
    uchar_hash_function,
    short_hash_function,
    ushort_hash_function,
    int_hash_function,
    uint_hash_function,
    long_hash_function,
    ulong_hash_function,
    longlong_hash_function,
    ulonglong_hash_function,
    float_hash_function,
    double_hash_function,
    string_hash_function,
    set_hash_function,
    NULL,
};

unsigned int string_hash_function(const generic_flat_pointer data, size_t size){
    const char *value = (const char *) data;
    unsigned int hash = 0;
    for (size_t i = 0; i < strlen(value); i++){
        hash += value[i];
    }
    return hash % size;
}

unsigned int set_hash_function(const generic_flat_pointer data, size_t size){
    const FlatSet value = (const FlatSet) data;
    return flat_set_hashcode(value) % size;
}

HashFunction get_hash_function(FlatType type){
    return _hash_functions[type];
}