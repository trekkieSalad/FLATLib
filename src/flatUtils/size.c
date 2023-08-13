#include <dataStructFunc.h>
#include <set.h>

#define DEFINE_HASH_FUNCTION(TYPE, SUFFIX) \
    size_t SUFFIX##Size() { \
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

size_t stringSize();
size_t setSize();

size_t (*Sizes[_TYPE_COUNT])() = {
    charSize,
    ucharSize,
    shortSize,
    ushortSize,
    intSize,
    uintSize,
    longSize,
    ulongSize,
    longlongSize,
    ulonglongSize,
    floatSize,
    doubleSize,
    stringSize,
    setSize,
    NULL,
};

size_t stringSize(){
    return sizeof(char *);
}

size_t setSize(){
    return sizeof(struct set);
}

size_t getTypeSize(Type type){
    return Sizes[type]();
}