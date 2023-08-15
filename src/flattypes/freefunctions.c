#include <datastructfunc.h>
#include <flatset.h>

#define DEFINE_FREE_FUNCTION(TYPE, SUFFIX) \
    void SUFFIX##_free_function(generic_flat_pointer data) { \
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

void string_free_function(generic_flat_pointer data);
void set_free_function(generic_flat_pointer data);

void (*_free_functions[_TYPE_COUNT])(generic_flat_pointer data) = {
    char_free_function,
    uchar_free_function,
    short_free_function,
    ushort_free_function,
    int_free_function,
    uint_free_function,
    long_free_function,
    ulong_free_function,
    longlong_free_function,
    ulonglong_free_function,
    float_free_function,
    double_free_function,
    string_free_function,
    set_free_function,
    NULL,
};

void string_free_function(generic_flat_pointer data) {
    if (!data)
        return;
    char *str = (char *)data;
    free(str);
}

void set_free_function(generic_flat_pointer data){
    FlatSet set = (FlatSet) data;

    flat_set_destroy(set);
}

FreeFunction get_free_function(FlatType type){
    return _free_functions[type];
}