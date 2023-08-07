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
    hashFunction hashFunction;
    equalsFunction equalsFunction;
    toStringFunction toStringFunction;
    cloneFunction cloneFunction;
    freeFunction freeFunction;
} Set;

// Operaciones de inicialización, modificacion, destrucción y consulta

/// @brief Creates an empty set. This functios is valid only for sets of primitive types, 
/// strings and FLATlib data structures.
/// @param type Type of the elements of the set.
/// @return A pointer to the new set.
Set *setCreate(Type type);
/// @brief Returns the number of elements in a initialized set.
/// @param set Set to be consulted.
/// @return The number of elements in the set.
size_t setNElements(const Set * set);
/// @brief Destroys a set, freeing all the memory allocated for it.
/// @param set Set to be destroyed.
void setDestroy(Set * set);
/// @brief Adds an element to a initialized set. If the element is already in 
/// the set, it is not added. Elements must be of the same type as the
/// set.
/// @param set Set to be modified.
/// @param data Element to be added.
/// @return True if the element was added, false otherwise.
bool setAdd(Set * set, void * data);
/// @brief Removes an element from a initialized set. If the element is not in 
/// the set, it is not removed. Elements must be of the same type as the
/// set.
/// @param set Set to be modified.
/// @param data Element to be removed.
/// @return True if the element was removed, false otherwise.
bool setRemove(Set * set, void * data);
/// @brief Generates a string representation of a set. 
/// @param set Set to be represented.
/// @return A pointer to the string representation of the set.
char * setToString(const Set * set);
/// @brief Creates a set from a string representation. The string must be in the
/// format returned by setToString.
/// @param set Set to be generated in format: \n
///           {element1, element2, ..., elementN}
/// @return A pointer to the new set.
Set *setOfString(char * string, Type type);

// Operaciones de evaluación

/// @brief Checks if a set contains an element. Elements must be of the same type as the
/// set. \n
///      x ∈ A ⇔ x is in A
/// @param set Set to be consulted.
/// @param data Element to be checked.
/// @return True if the element is in the set, false otherwise.
bool setContains(const Set * set, const void * data);
/// @brief Checks if two sets are equal. Two sets are equal if they have the same type
/// and the same elements. \n
///      A = B ⇔ ∀x(x ∈ A ⇔ x ∈ B)
/// @param setA First set to be compared.
/// @param setB Second set to be compared.
/// @return True if the sets are equal, false otherwise.
bool setsEquals(const Set * setA, const Set * setB);
/// @brief Checks if a set is subset of another set. A set is subset of another set if
/// all its elements are in the other set. Set and subset must be of the same type. \n
///      A ⊆ B ⇔ ∀x(x ∈ A → x ∈ B)
/// @param set Set to be consulted.
/// @param subset Set to be checked.
/// @return True if the set is subset of the other set, false otherwise.
bool setIsSubsetOf(const Set * subset, const Set * set);

// Operaciones de conjuntos

/// @brief Creates a new set with the union (A ∪ B) of two sets. Sets must be of the same type
/// and the new set will have the same type as the sets. \n
///      A ∪ B = {x | x ∈ A ∨ x ∈ B}
/// @param setA First set to be united.
/// @param setB Second set to be united.
/// @return A pointer to the new set.
Set *setsUnion(const Set * setA, const Set * setB);
/// @brief Creates a new set with the intersection (A ∩ B) of two sets. Sets must be of the same type
/// and the new set will have the same type as the sets. \n
///      A ∩ B = {x | x ∈ A ∧ x ∈ B}
/// @param setA First set to be intersected.
/// @param setB Second set to be intersected.
/// @return A pointer to the new set.
Set *setsIntersection(const Set * setA, const Set * setB);
/// @brief Creates a new set with the difference (A - B) of two sets. Result set is 
/// composed by the elements of the first set that are not in the second set.
/// Sets must be of the same type and the result set will have the same type 
/// as the sets. \n
///      A\B = {x ∈ A | x ∉ B} = {x | x ∈ A ∧ x ∉ B}
Set *setsDifference(const Set * setA, const Set * setB);
/// @brief Creates a new set with the symmetric difference (A ∆ B) of two sets. Sets must be of the same type
/// and the new set will have the same type as the sets. \n
///      A ∆ B = (A ∪ B) \ (A ∩ B) = (A \ B) ∪ (B \ A) 
/// @param setA First set to be substracted.
/// @param setB Second set to be substracted.
/// @return A pointer to the new set.
Set *setsSymmetricDifference(const Set * setA, const Set * setB);
/// @brief Creates a new set with the cartesian product (A × B) of two sets.
///         A × B = {(a, b) | a ∈ A ∧ b ∈ B}
/// @param setA First set to be multiplied.
/// @param setB Second set to be multiplied.
/// @return A pointer to the new set.
Set *setsCartesianProduct(const Set * setA, const Set * setB);
/// @brief Creates a new set with the power set (P(A)) of a set. \n
///         P(A) = {X | X ⊆ A}
Set *powerSet(const Set * set);

#endif // HASH_SET_H