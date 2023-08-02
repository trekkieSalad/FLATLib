#include "types.h"
#include <stdbool.h>

bool intEqualsFunction(const void *data1, const void *data2) {
    int value1 = *(int *)data1;
    int value2 = *(int *)data2;
    return value1 == value2;
}

bool floatEqualsFunction(const void *data1, const void *data2) {
    float value1 = *(float *)data1;
    float value2 = *(float *)data2;
    return value1 == value2;
}

equalsFunction getEqualsFunction(Type type) {
    switch (type) {
        case INT:
            return intEqualsFunction;
        case FLOAT:
            return floatEqualsFunction;
        default:
            return NULL;
    }
}