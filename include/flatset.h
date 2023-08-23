/* flatset.h
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

#ifndef HASH_SET_H
#define HASH_SET_H

#include <flattypes.h>

//==================================================================//
//              Public functions                                    //
//==================================================================//

//      Initialization functions
//      ------------------------

/**
 *   @brief Creates an empty set. This functios is valid only for sets of primitive types, 
 *   strings and FLATlib data structures.
 *   @param type Type of the elements of the set.
 *   @return A pointer to the new set.
 */
FlatSet     flat_set_create                 (FlatType                   type);
/**
 *   @brief Creates a set from a string representation. The string must be in the
 *   format returned by setToString.
 *   @param set Set to be generated in format: \n
 *             {element1, element2, ..., elementN}
 *   @return A pointer to the new set.
 */
FlatSet     flat_set_of_string              (char *                     string, 
                                             FlatType                   type);

//      Destruction functions
//      ---------------------

/**
 *   @brief Destroys a set, freeing all the memory allocated for it.
 *   @param set Set to be destroyed.
 */
void        flat_set_destroy                (FlatSet                    set);

//      Modification functions
//      ----------------------

/**
 *   @brief Adds an element to a initialized set. If the element is already in 
 *   the set, it is not added. Elements must be of the same type as the
 *   set.
 *   @param set Set to be modified.
 *   @param data Element to be added.
 *   @return True if the element was added, false otherwise.
 */
bool        flat_set_add_element            (FlatSet                    set, 
                                             generic_flat_pointer       data);
/**
 *   @brief Removes an element from a initialized set. If the element is not in 
 *   the set, it is not removed. Elements must be of the same type as the
 *   set.
 *   @param set Set to be modified.
 *   @param data Element to be removed.
 *   @return True if the element was removed, false otherwise.
 */
bool        flat_set_remove_element         (FlatSet                    set, 
                                             generic_flat_pointer       data);

//      Query functions
//      ---------------

/**
 *   @brief Returns the number of elements in a initialized set.
 *   @param set Set to be consulted.
 *   @return The number of elements in the set.
 */
size_t      flat_set_cardinality            (const FlatSet              set);
/**
 *   @brief Returns the "sizeof" of a set.
 *   @return The "sizeof" of the set.
 */
size_t      flat_set_type_size              ();

//      Evaluation functions
//      --------------------

/**
 *   @brief Checks if a set contains an element. Elements must be of the same type as the
 *   set. \n
 *        x ∈ A ⇔ x is in A
 *   @param set Set to be consulted.
 *   @param data Element to be checked.
 *   @return True if the element is in the set, false otherwise.
 */
bool        flat_set_contains               (const FlatSet              set, 
                                             const generic_flat_pointer data);
/**
 *   @brief Checks if a set is subset of another set. A set is subset of another set if
 *   all its elements are in the other set. Set and subset must be of the same type. \n
 *        A ⊆ B ⇔ ∀x(x ∈ A → x ∈ B)
 *   @param set Set to be consulted.
 *   @param subset Set to be checked.
 *   @return True if the set is subset of the other set, false otherwise.
 */
bool        flat_set_is_subset_of           (const FlatSet              subset, 
                                             const FlatSet              set);

//      FLAT ADT functions
//      ------------------

/**
 *   @brief Returns the hashcode of a set. 
 * 
 *   The hashcode is calculated using the hashcode of the elements in the set.
 *   @param set Set to calculate the hashcode.
 *   @return The hashcode of the set.
 */
int         flat_set_hashcode               (const FlatSet              set);
/**
 *   @brief Checks if two sets are equal. Two sets are equal if they have the same type
 *   and the same elements. \n
 *        A = B ⇔ ∀x(x ∈ A ⇔ x ∈ B)
 *   @param setA First set to be compared.
 *   @param setB Second set to be compared.
 *   @return True if the sets are equal, false otherwise.
 */
bool        flat_set_equals                 (const FlatSet              setA,   
                                             const FlatSet              setB);
/**
 *   @brief Generates a string representation of a set. 
 *   @param set Set to be represented.
 *   @return A pointer to the string representation of the set.
 */
char *      flat_set_to_string              (const FlatSet              set);
/**
 *  @brief Creates a copy of a set.
 *  @param set Set to be cloned.
 *  @return A pointer to the new set.
 */
FlatSet     flat_set_clone                  (const FlatSet              set);

//      FLATSET functions
//      -----------------

/**
 *   @brief Creates a new set with the union (A ∪ B) of two sets. Sets must be of the same type
 *   and the new set will have the same type as the sets. \n
 *        A ∪ B = {x | x ∈ A ∨ x ∈ B}
 *   @param setA First set to be united.
 *   @param setB Second set to be united.
 *   @return A pointer to the new set.
 */
FlatSet     flat_set_union                  (const FlatSet              setA, 
                                             const FlatSet              setB);
/**
 *   @brief Creates a new set with the intersection (A ∩ B) of two sets. Sets must be of the same type
 *   and the new set will have the same type as the sets. \n
 *        A ∩ B = {x | x ∈ A ∧ x ∈ B}
 *   @param setA First set to be intersected.
 *   @param setB Second set to be intersected.
 *   @return A pointer to the new set.
 */
FlatSet     flat_set_intersection           (const FlatSet              setA, 
                                             const FlatSet              setB);
/**
 *   @brief Creates a new set with the difference (A - B) of two sets. Result set is 
 *   composed by the elements of the first set that are not in the second set.
 *   Sets must be of the same type and the result set will have the same type 
 *   as the sets. \n
 *        A\B = {x ∈ A | x ∉ B} = {x | x ∈ A ∧ x ∉ B}
 */
FlatSet     flat_set_difference             (const FlatSet              setA, 
                                             const FlatSet              setB);
/**
 *   @brief Creates a new set with the symmetric difference (A ∆ B) of two sets. Sets must be of the same type
 *   and the new set will have the same type as the sets. \n
 *        A ∆ B = (A ∪ B) \ (A ∩ B) = (A \ B) ∪ (B \ A) 
 *   @param setA First set to be substracted.
 *   @param setB Second set to be substracted.
 *   @return A pointer to the new set.
 */
FlatSet     flat_set_symmetric_difference   (const FlatSet              setA, 
                                             const FlatSet              setB);
/**
 *   @brief Creates a new set with the cartesian product (A × B) of two sets.
 *           A × B = {(a, b) | a ∈ A ∧ b ∈ B}
 *   @param setA First set to be multiplied.
 *   @param setB Second set to be multiplied.
 *   @return A pointer to the new set.
 */
FlatSet     flat_set_cartesian_product      (const FlatSet              setA, 
                                             const FlatSet              setB);
/**
 *   @brief Creates a new set with the power set (P(A)) of a set. \n
 *           P(A) = {X | X ⊆ A}
 *   @param set Set to calculate the power set.
 *   @return A pointer to the new set.
 */
FlatSet     flat_set_power                  (const FlatSet              set);

#endif // HASH_SET_H