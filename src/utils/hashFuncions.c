#include "types.h"

unsigned int intHashFunction(const void *data, size_t size) {
    // Convertir el puntero a un entero
    int value = *(int *)data;
    // Usar operaciones bit a bit para obtener el hash
    unsigned int hash = value % size;
    return hash;
}

unsigned int floatHashFunction(const void *data, size_t size) {
    // Convertir el puntero a un entero
    float value = *(float *)data;
    // Usar operaciones bit a bit para obtener el hash
    unsigned int hash = (int)(value * 100) % size;
    return hash;
}

hashFunction getHashFunction(Type type){
    switch (type) {
        case INT:
            return intHashFunction;
        case FLOAT:
            return floatHashFunction;
        default:
            return NULL;
    }
}