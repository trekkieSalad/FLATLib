#include <set.h>
#include <prime.h>
#include <time.h>

#define DEFAULT_LOAD_FACTOR 0.75
#define DEFAULT_SIZE 11

// Operaciones privadas
static Node *createNode(void *data) {
    Node *newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

/*static Node *createNode(void *data, size_t dataSize) {
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        // Manejo del error en caso de fallo en la asignación de memoria
        return NULL;
    }

    // Asignar memoria para copiar los datos
    newNode->data = malloc(dataSize);
    if (newNode->data == NULL) {
        // Manejo del error en caso de fallo en la asignación de memoria
        free(newNode);
        return NULL;
    }

    // Copiar los datos en la nueva ubicación de memoria
    memcpy(newNode->data, data, dataSize);

    newNode->next = NULL;
    return newNode;
}*/



static void rehash(Set *set) {
    size_t newSize = nextPrimeSize(set->size);
    Node **newBuckets = calloc(newSize, sizeof(Node *));
    for (size_t i = 0; i < set->size; i++) {
        Node *bucket = set->buckets[i];
        while (bucket != NULL) {
            Node *next = bucket->next;
            size_t newIndex = set->hashFunction(bucket->data, newSize);
            bucket->next = newBuckets[newIndex];
            newBuckets[newIndex] = bucket;
            bucket = next;
        }
    }
    free(set->buckets);
    set->buckets = newBuckets;
    set->size = newSize;
}

static void destroyBucket(Set *set, Node *bucket) {
    if (bucket == NULL) {
        return;
    }
    destroyBucket(set, bucket->next);
    set->freeFunction(bucket->data);
    free(bucket);
}

// Operaciones públicas
// Operaciones de inicialización y destrucción
Set *setCreate(Type type) {
    srand(time(NULL));
    long hash = rand() * rand();

    Set *newSet = malloc(sizeof(Set));
    newSet->buckets = calloc(DEFAULT_SIZE, sizeof(Node *));
    newSet->size = DEFAULT_SIZE;
    newSet->type = type;
    newSet->hashcode = hash;
    newSet->nElements = 0;
    newSet->hashFunction = getHashFunction(type);
    newSet->equalsFunction = getEqualsFunction(type);
    newSet->toStringFunction = getToStringFunction(type);
    newSet->cloneFunction = getCloneFunction(type);
    newSet->freeFunction = getFreeFunction(type);
    return newSet;
}

size_t setNElements(const Set *set) {
    size_t size = 0;
    for (size_t i = 0; i < set->size; i++) {
        Node *current = set->buckets[i];
        while (current) {
            size++;
            current = current->next;
        }
    }
    return size;
    //return set->nElements;
}

void setDestroy(Set *set) {
    for (size_t i = 0; i < set->size; i++) {
        destroyBucket(set, set->buckets[i]);
    }
    free(set->buckets);
    free(set);
}

bool setAdd(Set *set, void *data) {
    if (set->size == 0) return false;
    if ((double)setNElements(set) / set->size >= DEFAULT_LOAD_FACTOR)
        rehash(set);
    size_t index = set->hashFunction(data, set->size);
    
    Node *bucket = set->buckets[index];
    while (bucket != NULL) {
        if (set->equalsFunction(bucket->data, data)) {
            return false;
        }
        bucket = bucket->next;
    }
    Node *newNode = createNode(set->cloneFunction(data));
    newNode->next = set->buckets[index];
    set->buckets[index] = newNode;
    set->nElements++;
    return true;
}

bool setRemove(Set *set, const void *data) {
    if (set->size == 0) {
        return false;
    }
    size_t index = set->hashFunction(data, set->size);
    Node *prev = NULL;
    Node *curr = set->buckets[index];
    while (curr != NULL) {
        if (set->equalsFunction(curr->data, data)) {
            if (prev == NULL) {
                set->buckets[index] = curr->next;
            } else {
                prev->next = curr->next;
            }
            set->freeFunction(curr->data);
            free(curr);
            set->nElements--;
            return true;
        }
        prev = curr;
        curr = curr->next;
    }
    return false;
}

char *setToString(const Set *set) {
    if (set == NULL) return NULL;

    // Estimamos el tamaño inicial de la cadena
    size_t estimatedLength = 2; // Incluyendo los corchetes {}
    for (size_t i = 0; i < set->size; i++) {
        Node *current = set->buckets[i];
        while (current != NULL) {
            char *dataString = set->toStringFunction(current->data);
            estimatedLength += strlen(dataString) + 2; // Incluyendo la coma y el espacio
            free(dataString); // Liberamos memoria asignada en toStringFunction
            current = current->next;
        }
    }

    char *string = malloc(estimatedLength * sizeof(char));
    if (string == NULL) return NULL;

    strcpy(string, "{");

    for (size_t i = 0; i < set->size; i++) {
        Node *current = set->buckets[i];
        while (current != NULL) {
            char *dataString = set->toStringFunction(current->data);
            strcat(string, dataString);
            strcat(string, ", ");
            free(dataString); // Liberamos memoria asignada en toStringFunction
            current = current->next;
        }
    }
    size_t len = strlen(string);
    if (len > 1) string[len - 2] = '\0';

    strcat(string, "}");

    return string;
}

// Operaciones de evaluación
bool setContains(const Set *set, const void *data) {
    unsigned int index = set->hashFunction(data, set->size);
    for (Node *current = set->buckets[index]; current != NULL; current = current->next) {
        if (set->equalsFunction(current->data, data)) {
            return true;
        }
    }
    return false;
}

bool setsEquals(const Set *setA, const Set *setB){
    if (setA->type != setB->type) return false;
    if (setNElements(setA) != setNElements(setB)) return false;
    for (size_t i = 0; i < setA->size; i++) {
        Node *current = setA->buckets[i];
        while (current != NULL) {
            if (!setContains(setB, current->data)) return false;
            current = current->next;
        }
    }
    return true;
}

bool setIsSubsetOf(const Set *subset, const Set *set){
    if (subset->type != set->type) return false;
    if (setNElements(subset) > setNElements(set)) return false;

    Node *current = NULL;
    for (size_t i = 0; i < subset->size; i++) {
        current = subset->buckets[i];
        while (current != NULL) {
            if (!setContains(set, current->data)) return false;
            current = current->next;
        }
    }
    return true;
}


Set *setsUnion(const Set *setA, const Set *setB) {
    if (setA == NULL || setB == NULL) return NULL;
    if (setA->type != setB->type) return NULL;

    Set *newSet = setCreate(setA->type);
    for (size_t i = 0; i < setA->size; i++) {
        Node *current = setA->buckets[i];
        while (current != NULL) {
            setAdd(newSet, current->data);
            current = current->next;
        }
    }
    for (size_t i = 0; i < setB->size; i++) {
        Node *current = setB->buckets[i];
        while (current != NULL) {
            setAdd(newSet, current->data);
            current = current->next;
        }
    }
    return newSet;
}

Set *setsIntersection(const Set *setA, const Set *setB){
    if (setA == NULL || setB == NULL) return NULL;
    if (setA->type != setB->type) return NULL;

    Set *newSet = setCreate(setA->type);
    for (size_t i = 0; i < setA->size; i++) {
        Node *current = setA->buckets[i];
        while (current != NULL) {
            if (setContains(setB, current->data)) {
                setAdd(newSet, current->data);
            }
            current = current->next;
        }
    }
    return newSet;
}

Set *setsDifference(const Set *setA, const Set *setB){
    if (setA == NULL || setB == NULL) return NULL;
    if (setA->type != setB->type) return NULL;

    Set *newSet = setCreate(setA->type);
    for (size_t i = 0; i < setA->size; i++) {
        Node *current = setA->buckets[i];
        while (current != NULL) {
            if (!setContains(setB, current->data)) {
                setAdd(newSet, current->data);
            }
            current = current->next;
        }
    }
    return newSet;
}

Set *setsSymmetricDifference(const Set *setA, const Set *setB){
    if (setA == NULL || setB == NULL) return NULL;
    if (setA->type != setB->type) return NULL;

    Set *newSet = setCreate(setA->type);
    for (size_t i = 0; i < setA->size; i++) {
        Node *current = setA->buckets[i];
        while (current != NULL) {
            if (!setContains(setB, current->data)) {
                setAdd(newSet, current->data);
            }
            current = current->next;
        }
    }
    for (size_t i = 0; i < setB->size; i++) {
        Node *current = setB->buckets[i];
        while (current != NULL) {
            if (!setContains(setA, current->data)) {
                setAdd(newSet, current->data);
            }
            current = current->next;
        }
    }
    return newSet;
}