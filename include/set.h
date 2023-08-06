#ifndef HASH_SET_H
#define HASH_SET_H

#include <types.h>

typedef struct node {
    void *data;
    struct node *next;
} Node;

typedef struct {
    Node **buckets;
    size_t size;
    Type type;
    long hashcode;
    long nElements;
    hashFunction hashFunction;
    equalsFunction equalsFunction;
    toStringFunction toStringFunction;
    cloneFunction cloneFunction;
    freeFunction freeFunction;
} Set;

// Operaciones de inicialización, destrucción y consulta
Set *setCreate(Type);
size_t setNElements(const Set *);
void setDestroy(Set *);
bool setAdd(Set *, void *);
bool setRemove(Set *, const void *);
char * setToString(const Set *);
Set *setOfString(char *);

// Operaciones de evaluación
bool setContains(const Set *, const void *);
bool setsEquals(const Set *, const Set *);
bool setIsSubsetOf(const Set *, const Set *);

// Operaciones de conjuntos
Set *setsUnion(const Set *, const Set *);
Set *setsIntersection(const Set *, const Set *);
Set *setsDifference(const Set *, const Set *);
Set *setsSymmetricDifference(const Set *, const Set *);
Set *setsCartesianProduct(const Set *, const Set *);
Set *powerSet(const Set *);

#endif // HASH_SET_H