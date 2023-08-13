#include <dataStructFunc.h>
#include <set.h>


#define DEFINE_CLONE_FUNCTION(TYPE, SUFFIX) \
    generic_flat_pointer  SUFFIX##CloneFunction(const generic_flat_pointer data) { \
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


generic_flat_pointer  stringCloneFunction(const generic_flat_pointer data);
generic_flat_pointer  setCloneFunction(const generic_flat_pointer data);

generic_flat_pointer  (*CloneFunctions[_TYPE_COUNT])(const generic_flat_pointer data) = {
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
    stringCloneFunction,
    setCloneFunction,
    NULL,
};

generic_flat_pointer stringCloneFunction(const generic_flat_pointer data) {
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

generic_flat_pointer  setCloneFunction(const generic_flat_pointer data){
    if (!data)
        return NULL;
    const Set set = (const Set) data;
    Set copy = setCreate(set->type);

    for (size_t i = 0; i < set->size; i++) {
        Node *current = set->buckets[i];
        while (current != NULL) {
            generic_flat_pointer dataClone = set->cloneFunction(current->data);
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