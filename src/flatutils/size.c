#include <datastructfunc.h>
#include <flatset.h>

#define DEFINE_HASH_FUNCTION(TYPE, SUFFIX) \
    size_t SUFFIX##_size() { \
        return sizeof(TYPE); \
    }

DEFINE_HASH_FUNCTION(char, char)
DEFINE_HASH_FUNCTION(unsigned char, uchar)
DEFINE_HASH_FUNCTION(short, short)
DEFINE_HASH_FUNCTION(unsigned short, ushort)
DEFINE_HASH_FUNCTION(int, int)
DEFINE_HASH_FUNCTION(unsigned int, uint)
DEFINE_HASH_FUNCTION(long, long)
DEFINE_HASH_FUNCTION(unsigned long, ulong)
DEFINE_HASH_FUNCTION(long long, longlong)
DEFINE_HASH_FUNCTION(unsigned long long, ulonglong)
DEFINE_HASH_FUNCTION(float, float)
DEFINE_HASH_FUNCTION(double, double)
DEFINE_HASH_FUNCTION(long double, longdouble)

size_t string_size();
size_t set_size();

size_t (*sizes[_TYPE_COUNT])() = {
    char_size,
    uchar_size,
    short_size,
    ushort_size,
    int_size,
    uint_size,
    long_size,
    ulong_size,
    longlong_size,
    ulonglong_size,
    float_size,
    double_size,
    string_size,
    set_size,
    NULL,
};

size_t string_size(){
    return sizeof(char *);
}

size_t set_size(){
    return flat_set_type_size();
}

size_t get_type_size(FlatType type){
    return sizes[type]();
}