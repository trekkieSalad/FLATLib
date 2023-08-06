#include <stdio.h>

#define typename(x) _Generic((x), \
    int:     "int", \
    float:   "float", \
    default: "other")

int main() {
    int a = 42;
    float b = 3.14;
    char c = 'A';
    double d = 2.718;

    printf("a es de tipo %s\n", typename(a));
    printf("b es de tipo %s\n", typename(b));
    printf("c es de tipo %s\n", typename(c));
    printf("d es de tipo %s\n", typename(d));

    return 0;
}
