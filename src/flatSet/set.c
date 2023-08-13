#include <set.h>
#include <types.h>
#include <dataStructFunc.h>
#include <prime.h>

#define DEFAULT_LOAD_FACTOR 0.75
#define DEFAULT_SIZE 11

/// @brief Creates a new node with the given data.
/// @param data Data to be stored in the node.
static Node *createNode(generic_flat_pointer data) {
    Node *newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

/// @brief Rehashes the set, doubling its size and reassigning the elements.
/// @param set Set to be rehashed.
static void rehash(Set set) {
    // get next prime size as new size and allocate new buckets
    size_t newSize = nextPrimeSize(set->size);
    Node **newBuckets = calloc(newSize, sizeof(Node *));

    // for each element in the set, reassign it to the new buckets
    for (size_t i = 0; i < set->size; i++) {
        Node *bucket = set->buckets[i];
        while (bucket != NULL) {
            Node *next = bucket->next;
            // reassign the bucket to the new buckets
            size_t newIndex = set->hashFunction(bucket->data, newSize);
            bucket->next = newBuckets[newIndex];
            newBuckets[newIndex] = bucket;
            bucket = next;
        }
    }

    // free old buckets and assign new ones
    free(set->buckets);
    set->buckets = newBuckets;
    set->size = newSize;
}

/// @brief Destroys a bucket, freeing all the memory allocated for it.
/// @param set Set to which the bucket belongs.
/// @param bucket Bucket to be destroyed.
static void destroyBucket(Set set, Node *bucket) {
    if (bucket == NULL) {
        return;
    }
    // destroy the next element in the bucket
    destroyBucket(set, bucket->next);
    // free the data and the bucket
    set->freeFunction(bucket->data);
    free(bucket);
}

// Initialization, modification and destruction operations
Set setCreate(Type type) {

    // allocate memory for the set and initialize it
    Set newSet = malloc(sizeof(struct set));
    newSet->buckets = calloc(DEFAULT_SIZE, sizeof(Node *));
    newSet->size = DEFAULT_SIZE;
    newSet->type = type;
    newSet->hashFunction = getHashFunction(type);
    newSet->equalsFunction = getEqualsFunction(type);
    newSet->toStringFunction = getToStringFunction(type);
    newSet->cloneFunction = getCloneFunction(type);
    newSet->freeFunction = getFreeFunction(type);
    return newSet;
}

void setDestroy(Set set) {
    if (set == NULL) return;

    // destroy each bucket
    for (size_t i = 0; i < set->size; i++) {
        destroyBucket(set, set->buckets[i]);
    }

    // free the buckets and the set
    free(set->buckets);
    free(set);
}

bool setAdd(Set set, generic_flat_pointer data) {
    // if the load factor is greater than the default, rehash the set
    if ((double)setNElements(set) / set->size >= DEFAULT_LOAD_FACTOR)
        rehash(set);

    // calculate the index of the data
    size_t index = set->hashFunction(data, set->size);
    
    // get the bucket and check if the data is already in the set
    Node *bucket = set->buckets[index];
    while (bucket != NULL) {
        if (set->equalsFunction(bucket->data, data)) {
            return false;
        }
        bucket = bucket->next;
    }

    // if the data is not in the set, add it in the last position of the bucket
    Node *newNode = createNode(set->cloneFunction(data));
    newNode->next = set->buckets[index];
    set->buckets[index] = newNode;
    return true;
}

bool setRemove(Set set, generic_flat_pointer data) {
    if (set == NULL || data == NULL) return false;

    // calculate the index of the data
    size_t index = set->hashFunction(data, set->size);

    Node *prev = NULL;
    Node *curr = set->buckets[index];

    // search for the data in the bucket
    while (curr != NULL) {
        // if the data is found, remove it from the bucket
        if (set->equalsFunction(curr->data, data)) {
            // if the data is the first element of the bucket,
            // make the next element the first element
            if (prev == NULL) {
                set->buckets[index] = curr->next;
            } 
            // otherwise, make the previous element point to the next element
            else {
                prev->next = curr->next;
            }
            // free the data and the node
            set->freeFunction(curr->data);
            free(curr);
            return true;
        }
        prev = curr;
        curr = curr->next;
    }
    return false;
}

// Query operations
size_t setNElements(const Set set) {
    size_t elementCounter = 0;

    // for each bucket, count the number of elements
    for (size_t i = 0; i < set->size; i++) {
        Node *current = set->buckets[i];
        // count elements until the end of the bucket
        while (current) {
            elementCounter++;
            current = current->next;
        }
    }
    return elementCounter;
}

char *setToString(const Set set) {
    if (set == NULL) return NULL;

    // calculate the estimated length of the string including the braces {}
    size_t estimatedLength = 2;

    // for each element in the set, calculate the length of its string representation
    for (size_t i = 0; i < set->size; i++) {
        Node *current = set->buckets[i];
        while (current != NULL) {
            // calculate the length of the string representation of the data
            // including the comma and the space
            char *dataString = set->toStringFunction(current->data);
            estimatedLength += strlen(dataString) + 2;
            free(dataString);
            current = current->next;
        }
    }

    // allocate memory for a string of the estimated length
    char *string = malloc(estimatedLength * sizeof(char)+3);
    if (string == NULL) return NULL;

    strcpy(string, "{");

    // for each element in the set, add its string representation to the string
    for (size_t i = 0; i < set->size; i++) {
        Node *current = set->buckets[i];
        while (current != NULL) {
            // get the string representation of the data and add it to the string
            // including the comma and the space
            char *dataString = set->toStringFunction(current->data);
            strcat(string, dataString);
            strcat(string, ", ");
            free(dataString);
            current = current->next;
        }
    }

    // remove the last comma and space and add the closing brace
    size_t len = strlen(string);
    if (len > 1) string[len - 2] = '\0';

    strcat(string, "}");

    return string;
}

// evaluation operations
bool setContains(const Set set, const generic_flat_pointer data) {
    // calculate the index of the data
    unsigned int index = set->hashFunction(data, set->size);
    // search for the data in the bucket
    for (Node *current = set->buckets[index]; current != NULL; current = current->next) {
        if (set->equalsFunction(current->data, data)) {
            return true;
        }
    }
    return false;
}

bool setsEquals(const Set setA, const Set setB){
    // if the sets are not of the same type or have different sizes, 
    // they are not equal
    if (setA->type != setB->type) return false;
    if (setNElements(setA) != setNElements(setB)) return false;

    // for each element in setA, check if it is in setB
    for (size_t i = 0; i < setA->size; i++) {
        Node *current = setA->buckets[i];
        while (current != NULL) {
            if (!setContains(setB, current->data)) return false;
            current = current->next;
        }
    }
    return true;
}

bool setIsSubsetOf(const Set subset, const Set set){
    // if the sets are not of the same type or the subset has more elements 
    // than the set, "subset" is not a subset of the set
    if (subset->type != set->type) return false;
    if (setNElements(subset) > setNElements(set)) return false;

    Node *current = NULL;
    // for each element in the subset, check if it is in the set
    for (size_t i = 0; i < subset->size; i++) {
        current = subset->buckets[i];
        while (current != NULL) {
            if (!setContains(set, current->data)) return false;
            current = current->next;
        }
    }
    return true;
}

// set operations
Set setsUnion(const Set setA, const Set setB) {
    // if any of the sets is NULL or they are not of the same type, return NULL
    if (setA == NULL || setB == NULL) return NULL;
    if (setA->type != setB->type) return NULL;

    // create a new set of the same type as setA and setB
    Set newSet = setCreate(setA->type);

    // add all the elements of setA and setB to the new set
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

Set setsIntersection(const Set setA, const Set setB){
    // if any of the sets is NULL or they are not of the same type, return NULL
    if (setA == NULL || setB == NULL) return NULL;
    if (setA->type != setB->type) return NULL;

    // create a new set of the same type as setA and setB
    Set newSet = setCreate(setA->type);

    // add to the new set all the elements that are in both setA and setB
    for (size_t i = 0; i < setA->size; i++) {
        Node *current = setA->buckets[i];
        while (current != NULL) {
            // if the a-element is in setB, add it to the new set
            if (setContains(setB, current->data)) {
                setAdd(newSet, current->data);
            }
            current = current->next;
        }
    }
    return newSet;
}

Set setsDifference(const Set setA, const Set setB){    
    // if any of the sets is NULL or they are not of the same type, return NULL
    if (setA == NULL || setB == NULL) return NULL;
    if (setA->type != setB->type) return NULL;

    // create a new set of the same type as setA and setB
    Set newSet = setCreate(setA->type);

    // add to the new set all the elements that are in setA but not in setB
    for (size_t i = 0; i < setA->size; i++) {
        Node *current = setA->buckets[i];
        while (current != NULL) {
            // if the a-element is not in setB, add it to the new set
            if (!setContains(setB, current->data)) {
                setAdd(newSet, current->data);
            }
            current = current->next;
        }
    }
    return newSet;
}

Set setsSymmetricDifference(const Set setA, const Set setB){
    // if any of the sets is NULL or they are not of the same type, return NULL
    if (setA == NULL || setB == NULL) return NULL;
    if (setA->type != setB->type) return NULL;

    // create a new set of the same type as setA and setB
    Set newSet = setCreate(setA->type);

    // add to the new set all the elements that are in setA but not in setB
    for (size_t i = 0; i < setA->size; i++) {
        Node *current = setA->buckets[i];
        while (current != NULL) {
            if (!setContains(setB, current->data)) {
                setAdd(newSet, current->data);
            }
            current = current->next;
        }
    }

    // add to the new set all the elements that are in setB but not in setA
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

/// @brief This function adds to the newSet all the subsets of the originalSet 
/// that contain the "subset"
/// @param originalSet set from which the subsets are taken
/// @param newSet set to which the subsets are added (power set)
/// @param subset root subset
void newInset(const Set originalSet, Set newSet, Set subset){
    for (size_t i = 0; i < originalSet->size; i++) {
        Node *current = originalSet->buckets[i];
        while (current != NULL) {
            // if the current element is already in the subset, skip it
            // due to the fact that its supersets are already in the subset
            if (setContains(subset, current->data)){
                current = current->next;
                continue;
            }
            // create a new subset that is the same as the subset and add to it
            // the current element
            Set newSubset = newSet->cloneFunction(subset);
            setAdd(newSubset, current->data);
            // if the new subset is already in the new set, destroy it and
            // continue, due to the fact that its supersets are already in the
            // new set too
            if (setContains(newSet, newSubset)) {
                setDestroy(newSubset);
                current = current->next;
                continue;
            }
            // add the new subset to the new set
            setAdd(newSet, newSubset);
            // recursively call the function to add to the new set all the
            // supersets of the new subset
            newInset(originalSet, newSet, newSubset);
            setDestroy(newSubset);
            current = current->next;
        }
    }
}

Set powerSet(const Set set){
    // if the set is NULL, return NULL
    if (set == NULL) return NULL;

    // create a new set of the same type as set
    Set newSet = setCreate(SET);
    // add the empty set to the new set
    Set auxSet = setCreate(set->type);
    setAdd(newSet, auxSet);
    setDestroy(auxSet);

    // add to the new set all the subsets of set
    for (size_t i = 0; i < set->size; i++) {
        Node *current = set->buckets[i];
        while (current != NULL) {
            auxSet = setCreate(set->type);
            // add the current element to the auxiliar set
            setAdd(auxSet, current->data);
            // add the auxiliar set to the new set (add all subsets with 1 element)
            setAdd(newSet, auxSet);
            // add all supersets of the auxiliar set to the new set
            newInset(set, newSet, auxSet);
            setDestroy(auxSet);
            current = current->next;
        }
    }
    return newSet;
}
