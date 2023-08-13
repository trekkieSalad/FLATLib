#include <dataStructFunc.h>
#include <set.h>

#define DEFINE_TO_STRING_FUNCTION(TYPE, SUFFIX, FORMAT) \
    char * SUFFIX##ToStringFunction(const generic_flat_pointer data) { \
        TYPE value = *(TYPE *)data; \
        char *string = malloc(12 * sizeof(char)); \
        sprintf(string, FORMAT, value); \
        return string; \
    }

DEFINE_TO_STRING_FUNCTION(char, char, "%c")
DEFINE_TO_STRING_FUNCTION(unsigned char, uchar, "%c")
DEFINE_TO_STRING_FUNCTION(short, short, "%d")
DEFINE_TO_STRING_FUNCTION(unsigned short, ushort, "%d")
DEFINE_TO_STRING_FUNCTION(int, int, "%d")
DEFINE_TO_STRING_FUNCTION(unsigned int, uint, "%d")
DEFINE_TO_STRING_FUNCTION(long, long, "%ld")
DEFINE_TO_STRING_FUNCTION(unsigned long, ulong, "%ld")
DEFINE_TO_STRING_FUNCTION(long long, longlong, "%lld")
DEFINE_TO_STRING_FUNCTION(unsigned long long, ulonglong, "%lld")
DEFINE_TO_STRING_FUNCTION(float, float, "%.2f")
DEFINE_TO_STRING_FUNCTION(double, double, "%.4f")
DEFINE_TO_STRING_FUNCTION(long double, longdouble, "%.4Lf")


char * stringToStringFunction(const generic_flat_pointer data);
char * setToStringFunction(const generic_flat_pointer data);

char * (*ToStringFunctions[_TYPE_COUNT])(const generic_flat_pointer data) = {
    charToStringFunction,
    ucharToStringFunction,
    shortToStringFunction,
    ushortToStringFunction,
    intToStringFunction,
    uintToStringFunction,
    longToStringFunction,
    ulongToStringFunction,
    longlongToStringFunction,
    ulonglongToStringFunction,
    floatToStringFunction,
    doubleToStringFunction,
    stringToStringFunction,
    setToStringFunction,
    NULL,
};

char * stringToStringFunction(const generic_flat_pointer data){
    char *value = *(char **)data;
    char *string = malloc((strlen(value) + 1) * sizeof(char));
    strcpy(string, value);
    return string;
}

char * setToStringFunction(const generic_flat_pointer data){
    const Set set = (const Set) data;
    return setToString(set);
}

toStringFunction getToStringFunction(Type type){
    return ToStringFunctions[type];
}