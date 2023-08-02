#include "types.h"

char *intToString(const void *data) {
    int value = *(int *)data;
    char *string = malloc(12 * sizeof(char));
    sprintf(string, "%d", value);
    return string;
}

char *floatToString(const void *data) {
    float value = *(float *)data;
    char *string = malloc(12 * sizeof(char));
    sprintf(string, "%.2f", value);
    return string;
}

toStringFunction getToStringFunction(Type type) {
    switch (type) {
        case INT:
            return intToString;
        case FLOAT:
            return floatToString;
        default:
            return NULL;
    }
}