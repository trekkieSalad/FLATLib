/* flatset.c - Implementation of the FlatSet data structure.
 *
 *  FLATLib - Library of formal languages and automata theory.
 *  Copyright (C) 2023  Daniel José García Paz
 * 
 *      SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License as published by the Free Software Foundation; either
 *    version 2.1 of the License, or (at your option) any later version.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
 *    USA or see <https://www.gnu.org/licenses/>.
 * 
 *  Author: Daniel José García Paz <daniel.garcia.paz@udc.es>
 */

#include <flatset.h>
#include <flattypes.h>
#include <datastructfunc.h>
#include <prime.h>

#define DEFAULT_LOAD_FACTOR 0.75
#define DEFAULT_SIZE 11

struct _Node {
    generic_flat_pointer data;
    struct _Node *next;
};

typedef struct _Node Node;

struct _FlatSet {
    Node **buckets;
    size_t size;
    FlatType type;
    HashFunction hashFunction;
    EqualsFunction equalsFunction;
    ToStringFunction toStringFunction;
    CloneFunction cloneFunction;
    FreeFunction freeFunction;
};

/**
 * @brief Creates a new node with the given data.
 * @param data Data to be stored in the node.
 * @return New node with the given data.
 */
static Node *create_node(generic_flat_pointer data) {
    Node *newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

/**
 * @brief Rehashes the set, doubling its size and reassigning the elements.
 * @param set Set to be rehashed.
 */
static void rehash(FlatSet set) {
    // get next prime size as new size and allocate new buckets
    size_t newSize = next_prime_size(set->size);
    Node **newBuckets = calloc(newSize, sizeof(Node *));

    // for each element in the set, reassign it to the new buckets
    for (size_t i = 0; i < set->size; i++) {
        Node *bucket = set->buckets[i];
        while (bucket != NULL) {
            Node *next = bucket->next;
            // reassign the bucket to the new buckets
            size_t newIndex = set->hashFunction(bucket->data) % newSize;
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

/**
 * @brief Destroys a bucket, freeing all the memory allocated for it.
 * @param set Set to which the bucket belongs.
 * @param bucket Bucket to be destroyed.
 */
static void destroy_bucket(FlatSet set, Node *bucket) {
    if (bucket == NULL) {
        return;
    }
    // destroy the next element in the bucket
    destroy_bucket(set, bucket->next);
    // free the data and the bucket
    set->freeFunction(bucket->data);
    free(bucket);
}

// Initialization, modification and destruction operations
FlatSet flat_set_create(FlatType type) {

    // allocate memory for the set and initialize it
    FlatSet newSet = malloc(sizeof(struct _FlatSet));
    newSet->buckets = calloc(DEFAULT_SIZE, sizeof(Node *));
    newSet->size = DEFAULT_SIZE;
    newSet->type = type;
    newSet->hashFunction = get_hash_function(type);
    newSet->equalsFunction = get_equals_function(type);
    newSet->toStringFunction = get_to_string_function(type);
    newSet->cloneFunction = get_clone_function(type);
    newSet->freeFunction = get_free_function(type);
    return newSet;
}

FlatSet flat_set_clone(const FlatSet set){
    if (set == NULL) return NULL;
    FlatSet copy = flat_set_create(set->type);

    for (size_t i = 0; i < set->size; i++) {
        Node *current = set->buckets[i];
        while (current != NULL) {
            generic_flat_pointer dataClone = set->cloneFunction(current->data);
            flat_set_add_element(copy, dataClone);
            free(dataClone);
            current = current->next;
        }
    }

    return copy;
}

void flat_set_destroy(FlatSet set) {
    if (set == NULL) return;

    // destroy each bucket
    for (size_t i = 0; i < set->size; i++) {
        destroy_bucket(set, set->buckets[i]);
    }

    // free the buckets and the set
    free(set->buckets);
    free(set);
}

bool flat_set_add_element(FlatSet set, generic_flat_pointer data) {
    // if the load factor is greater than the default, rehash the set
    if ((double)flat_set_cardinality(set) / set->size >= DEFAULT_LOAD_FACTOR)
        rehash(set);

    // calculate the index of the data
    size_t index = set->hashFunction(data) % set->size;
    
    // get the bucket and check if the data is already in the set
    Node *bucket = set->buckets[index];
    while (bucket != NULL) {
        if (set->equalsFunction(bucket->data, data)) {
            return false;
        }
        bucket = bucket->next;
    }

    // if the data is not in the set, add it in the last position of the bucket
    Node *newNode = create_node(set->cloneFunction(data));
    newNode->next = set->buckets[index];
    set->buckets[index] = newNode;
    return true;
}

bool flat_set_remove_element(FlatSet set, generic_flat_pointer data) {
    if (set == NULL || data == NULL) return false;

    // calculate the index of the data
    size_t index = set->hashFunction(data) % set->size;

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
size_t flat_set_cardinality(const FlatSet set) {
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

int flat_set_hashcode(const FlatSet set) {
    long hash = 0;

    // for each element in the set, calculate its hash and add it to the set hash
    for (size_t i = 0; i < set->size; i++) {
        Node *current = set->buckets[i];
        while (current != NULL) {
            hash += set->hashFunction(current->data) % set->size;
            current = current->next;
        }
    }
    return hash;
}

size_t flat_set_type_size() {
    return sizeof(struct _FlatSet);
}

char *flat_set_to_string(const FlatSet set) {
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
bool flat_set_contains(const FlatSet set, const generic_flat_pointer data) {
    // calculate the index of the data
    unsigned int index = set->hashFunction(data) % set->size;
    // search for the data in the bucket
    for (Node *current = set->buckets[index]; current != NULL; current = current->next) {
        if (set->equalsFunction(current->data, data)) {
            return true;
        }
    }
    return false;
}

bool flat_set_equals(const FlatSet setA, const FlatSet setB){
    // if the sets are not of the same type or have different sizes, 
    // they are not equal
    if (setA->type != setB->type) return false;
    if (flat_set_cardinality(setA) != flat_set_cardinality(setB)) return false;

    // for each element in setA, check if it is in setB
    for (size_t i = 0; i < setA->size; i++) {
        Node *current = setA->buckets[i];
        while (current != NULL) {
            if (!flat_set_contains(setB, current->data)) return false;
            current = current->next;
        }
    }
    return true;
}

bool flat_set_is_subset_of(const FlatSet subset, const FlatSet set){
    // if the sets are not of the same type or the subset has more elements 
    // than the set, "subset" is not a subset of the set
    if (subset->type != set->type) return false;
    if (flat_set_cardinality(subset) > flat_set_cardinality(set)) return false;

    Node *current = NULL;
    // for each element in the subset, check if it is in the set
    for (size_t i = 0; i < subset->size; i++) {
        current = subset->buckets[i];
        while (current != NULL) {
            if (!flat_set_contains(set, current->data)) return false;
            current = current->next;
        }
    }
    return true;
}

// set operations
FlatSet flat_set_union(const FlatSet setA, const FlatSet setB) {
    // if any of the sets is NULL or they are not of the same type, return NULL
    if (setA == NULL || setB == NULL) return NULL;
    if (setA->type != setB->type) return NULL;

    // create a new set of the same type as setA and setB
    FlatSet newSet = flat_set_create(setA->type);

    // add all the elements of setA and setB to the new set
    for (size_t i = 0; i < setA->size; i++) {
        Node *current = setA->buckets[i];
        while (current != NULL) {
            flat_set_add_element(newSet, current->data);
            current = current->next;
        }
    }
    for (size_t i = 0; i < setB->size; i++) {
        Node *current = setB->buckets[i];
        while (current != NULL) {
            flat_set_add_element(newSet, current->data);
            current = current->next;
        }
    }
    return newSet;
}

FlatSet flat_set_intersection(const FlatSet setA, const FlatSet setB){
    // if any of the sets is NULL or they are not of the same type, return NULL
    if (setA == NULL || setB == NULL) return NULL;
    if (setA->type != setB->type) return NULL;

    // create a new set of the same type as setA and setB
    FlatSet newSet = flat_set_create(setA->type);

    // add to the new set all the elements that are in both setA and setB
    for (size_t i = 0; i < setA->size; i++) {
        Node *current = setA->buckets[i];
        while (current != NULL) {
            // if the a-element is in setB, add it to the new set
            if (flat_set_contains(setB, current->data)) {
                flat_set_add_element(newSet, current->data);
            }
            current = current->next;
        }
    }
    return newSet;
}

FlatSet flat_set_difference(const FlatSet setA, const FlatSet setB){    
    // if any of the sets is NULL or they are not of the same type, return NULL
    if (setA == NULL || setB == NULL) return NULL;
    if (setA->type != setB->type) return NULL;

    // create a new set of the same type as setA and setB
    FlatSet newSet = flat_set_create(setA->type);

    // add to the new set all the elements that are in setA but not in setB
    for (size_t i = 0; i < setA->size; i++) {
        Node *current = setA->buckets[i];
        while (current != NULL) {
            // if the a-element is not in setB, add it to the new set
            if (!flat_set_contains(setB, current->data)) {
                flat_set_add_element(newSet, current->data);
            }
            current = current->next;
        }
    }
    return newSet;
}

FlatSet flat_set_symmetric_difference(const FlatSet setA, const FlatSet setB){
    // if any of the sets is NULL or they are not of the same type, return NULL
    if (setA == NULL || setB == NULL) return NULL;
    if (setA->type != setB->type) return NULL;

    // create a new set of the same type as setA and setB
    FlatSet newSet = flat_set_create(setA->type);

    // add to the new set all the elements that are in setA but not in setB
    for (size_t i = 0; i < setA->size; i++) {
        Node *current = setA->buckets[i];
        while (current != NULL) {
            if (!flat_set_contains(setB, current->data)) {
                flat_set_add_element(newSet, current->data);
            }
            current = current->next;
        }
    }

    // add to the new set all the elements that are in setB but not in setA
    for (size_t i = 0; i < setB->size; i++) {
        Node *current = setB->buckets[i];
        while (current != NULL) {
            if (!flat_set_contains(setA, current->data)) {
                flat_set_add_element(newSet, current->data);
            }
            current = current->next;
        }
    }
    return newSet;
}

/**
 * @brief This function adds to the newSet all the subsets of the originalSet 
 * that contain the "subset"
 * @param originalSet set from which the subsets are taken
 * @param newSet set to which the subsets are added (power set)
 * @param subset root subset
 */
void new_inset(const FlatSet originalSet, FlatSet newSet, FlatSet subset){
    for (size_t i = 0; i < originalSet->size; i++) {
        Node *current = originalSet->buckets[i];
        while (current != NULL) {
            // if the current element is already in the subset, skip it
            // due to the fact that its supersets are already in the subset
            if (flat_set_contains(subset, current->data)){
                current = current->next;
                continue;
            }
            // create a new subset that is the same as the subset and add to it
            // the current element
            FlatSet newSubset = newSet->cloneFunction(subset);
            flat_set_add_element(newSubset, current->data);
            // if the new subset is already in the new set, destroy it and
            // continue, due to the fact that its supersets are already in the
            // new set too
            if (flat_set_contains(newSet, newSubset)) {
                flat_set_destroy(newSubset);
                current = current->next;
                continue;
            }
            // add the new subset to the new set
            flat_set_add_element(newSet, newSubset);
            // recursively call the function to add to the new set all the
            // supersets of the new subset
            new_inset(originalSet, newSet, newSubset);
            flat_set_destroy(newSubset);
            current = current->next;
        }
    }
}

FlatSet flat_set_power(const FlatSet set){
    // if the set is NULL, return NULL
    if (set == NULL) return NULL;

    // create a new set of the same type as set
    FlatSet newSet = flat_set_create(SET);
    // add the empty set to the new set
    FlatSet auxSet = flat_set_create(set->type);
    flat_set_add_element(newSet, auxSet);
    flat_set_destroy(auxSet);

    // add to the new set all the subsets of set
    for (size_t i = 0; i < set->size; i++) {
        Node *current = set->buckets[i];
        while (current != NULL) {
            auxSet = flat_set_create(set->type);
            // add the current element to the auxiliar set
            flat_set_add_element(auxSet, current->data);
            // add the auxiliar set to the new set (add all subsets with 1 element)
            flat_set_add_element(newSet, auxSet);
            // add all supersets of the auxiliar set to the new set
            new_inset(set, newSet, auxSet);
            flat_set_destroy(auxSet);
            current = current->next;
        }
    }
    return newSet;
}
