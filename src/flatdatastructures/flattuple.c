#include <stdio.h>
#include <stdint.h>
#define GINT_TO_POINTER(i) ((void *)((intptr_t)(i)))
#define GPOINTER_TO_INT(p) ((int)((intptr_t)(p)))

/*#define g_pointer(value) _Generic((value), \
    short: &value, \
    unsigned short: &value, \
    int: &value, \
    unsigned int: &value, \
    long: &value, \
    unsigned long: &value, \
    long long: &value, \
    unsigned long long: &value, \
    float: &value, \
    double: &value \
)


int main() {
    int x = 5;
    void *y = g_pointer(x);
    void * z = GINT_TO_POINTER(x);
    printf("%d\n", GPOINTER_TO_INT(y));
    printf("%d\n", GPOINTER_TO_INT(z));
    return 0;
}*/