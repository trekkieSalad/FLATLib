#include <datastructfunc.h>
#include <flatset.h>

#define DEFINE_TO_STRING_FUNCTION(TYPE, SUFFIX, FORMAT) \
    char * SUFFIX##_to_string_function(const generic_flat_pointer data) { \
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


char * string_to_string_function(const generic_flat_pointer data);
char * set_to_string_function(const generic_flat_pointer data);

char * (*_to_string_functions[_TYPE_COUNT])(const generic_flat_pointer data) = {
    char_to_string_function,
    uchar_to_string_function,
    short_to_string_function,
    ushort_to_string_function,
    int_to_string_function,
    uint_to_string_function,
    long_to_string_function,
    ulong_to_string_function,
    longlong_to_string_function,
    ulonglong_to_string_function,
    float_to_string_function,
    double_to_string_function,
    string_to_string_function,
    set_to_string_function,
    NULL,
};

char * string_to_string_function(const generic_flat_pointer data){
    char *value = *(char **)data;
    char *string = malloc((strlen(value) + 1) * sizeof(char));
    strcpy(string, value);
    return string;
}

char * set_to_string_function(const generic_flat_pointer data){
    const FlatSet set = (const FlatSet) data;
    return flat_set_to_string(set);
}

ToStringFunction get_to_string_function(FlatType type){
    return _to_string_functions[type];
}