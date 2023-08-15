#include <datastructfunc.h>
#include <flatset.h>


#define DEFINE_CLONE_FUNCTION(TYPE, SUFFIX) \
    generic_flat_pointer  SUFFIX##_clone_function(const generic_flat_pointer data) { \
        if (!data) \
            return NULL; \
        TYPE *value = (TYPE *)data; \
        TYPE *clone = (TYPE *)malloc(sizeof(TYPE)); \
        *clone = *value; \
        return clone; \
    }

DEFINE_CLONE_FUNCTION(char, char)
DEFINE_CLONE_FUNCTION(unsigned char, uchar)
DEFINE_CLONE_FUNCTION(short, short)
DEFINE_CLONE_FUNCTION(unsigned short, ushort)
DEFINE_CLONE_FUNCTION(int, int)
DEFINE_CLONE_FUNCTION(unsigned int, uint)
DEFINE_CLONE_FUNCTION(long, long)
DEFINE_CLONE_FUNCTION(unsigned long, ulong)
DEFINE_CLONE_FUNCTION(long long, longlong)
DEFINE_CLONE_FUNCTION(unsigned long long, ulonglong)
DEFINE_CLONE_FUNCTION(float, float)
DEFINE_CLONE_FUNCTION(double, double)
DEFINE_CLONE_FUNCTION(long double, longdouble)


generic_flat_pointer  string_clone_function(const generic_flat_pointer data);
generic_flat_pointer  set_clone_function(const generic_flat_pointer data);

generic_flat_pointer  (*_clone_functions[_TYPE_COUNT])(const generic_flat_pointer data) = {
    char_clone_function,
    uchar_clone_function,
    short_clone_function,
    ushort_clone_function,
    int_clone_function,
    uint_clone_function,
    long_clone_function,
    ulong_clone_function,
    longlong_clone_function,
    ulonglong_clone_function,
    float_clone_function,
    double_clone_function,
    string_clone_function,
    set_clone_function,
    NULL,
};

generic_flat_pointer string_clone_function(const generic_flat_pointer data) {
    if (!data)
        return NULL;

    const char *str = (const char *)data;
    size_t len = strlen(str);

    char *copy = (char *)malloc((len + 1) * sizeof(char)); // +1 for null terminator
    if (copy) {
        strcpy(copy, str);
    }
    return copy;
}

generic_flat_pointer  set_clone_function(const generic_flat_pointer data){
    if (!data)
        return NULL;
    const FlatSet set = (const FlatSet) data;
    FlatSet copy = flat_set_clone(set);
    return copy;
}

CloneFunction get_clone_function(FlatType type){
    return _clone_functions[type];
}