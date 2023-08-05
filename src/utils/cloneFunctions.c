#include "types.h"
#include <set.h>

#define DEFINE_CLONE_FUNCTION(TYPE, SUFFIX) \
    void * SUFFIX##CloneFunction(const void *data) { \
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


void * stringCloneFunction(const void *data);
void * setCloneFunction(const void *data);

void * (*CloneFunctions[_TYPE_COUNT])(const void *data) = {
    NULL,
    charCloneFunction,
    ucharCloneFunction,
    shortCloneFunction,
    ushortCloneFunction,
    intCloneFunction,
    uintCloneFunction,
    longCloneFunction,
    ulongCloneFunction,
    longlongCloneFunction,
    ulonglongCloneFunction,
    floatCloneFunction,
    doubleCloneFunction,
    longdoubleCloneFunction,
    stringCloneFunction,
    setCloneFunction,
    NULL,
};

void *stringCloneFunction(const void *data) {
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

void * setCloneFunction(const void *data){
    if (!data)
        return NULL;
    const Set *set = data;
    Set *copy = setCreate(set->type);

    copy->hashcode = set->hashcode;

    for (size_t i = 0; i < set->size; i++) {
        Node *current = set->buckets[i];
        while (current != NULL) {
            void * dataClone = set->cloneFunction(current->data);
            setAdd(copy, dataClone);
            free(dataClone);
            current = current->next;
        }
    }

    return copy;
}

cloneFunction getCloneFunction(Type type){
    return CloneFunctions[type];
}