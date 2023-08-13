#include <dataStructFunc.h>
#include <set.h>

#define DEFINE_EQUALS_FUNCTION(TYPE, SUFFIX) \
    bool SUFFIX##EqualsFunction(const generic_flat_pointer data1, const generic_flat_pointer data2) { \
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

bool stringEqualsFunction(const generic_flat_pointer data1, const generic_flat_pointer data2);
bool setEqualsFunction(const generic_flat_pointer data1, const generic_flat_pointer data2);

bool (*equalsFunctions[_TYPE_COUNT])(const generic_flat_pointer data1, const generic_flat_pointer data2) = {
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
    stringEqualsFunction,
    setEqualsFunction,
    NULL,
};

bool stringEqualsFunction(const generic_flat_pointer data1, const generic_flat_pointer data2) {
    char *value1 = (char *)data1;
    char *value2 = (char *)data2;

    return strcmp(value1, value2) == 0;
}

bool setEqualsFunction(const generic_flat_pointer data1, const generic_flat_pointer data2) {
    const Set value1 = (const Set)data1;
    const Set value2 = (const Set)data2;
    return setsEquals(value1, value2);
}

equalsFunction getEqualsFunction(Type type) {
    return equalsFunctions[type];
}