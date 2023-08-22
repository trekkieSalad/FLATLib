/* flattuple.h
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
#ifndef FLATTUPLE_H
#define FLATTUPLE_H

#include <flatpointer.h>

#define END_OF_TUPLE 0

/**
 * @typedef FlatTuple
 * 
 * @brief   A FlatTuple is a pointer to a tuple of FlatPointers. A tuple is a 
 * finite ordered and inmutable list of elements. The elements of a tuple can 
 * be of any primitive type, string or FlatLib data structure and are 
 * represented by FlatPointers.
 */
typedef struct _FlatTuple * FlatTuple;

/**
 * @brief Creates a new FlatTuple from an indefinite number of FlatPointers.
 * 
 * @param flatpointers  The FlatPointers to be stored in the tuple.
 * @return              The new FlatTuple.
 */
#define flat_tuple_create(...) _flat_tuple_create(__VA_ARGS__, END_OF_TUPLE)
/**
 * @brief Creates and defines the types of a new empty FlatTuple from an 
 * indefinite number of FlatTypes. The FlatTuple will be empty, but the types
 * will be defined. The FlatTuple can be filled later with the function
 * flat_tuple_filler.
 * 
 * @param types         The types of the FlatTuple.
 * @return              The new empty FlatTuple.
 */
#define flat_tuple_define(...) _flat_tuple_define(__VA_ARGS__, END_OF_TUPLE)
/**
 * @brief Fills a FlatTuple with an indefinite number of FlatPointers. The
 * FlatTuple must be previously defined with the function flat_tuple_define. If
 * the FlatTuple is already filled, the function will fail. If the size of the
 * FlatTuple is different from the number of FlatPointers, the function will
 * fail.
 * 
 * @param tuple         The FlatTuple to be filled.
 * @param flatpointers  The FlatPointers to be stored in the tuple.
 */
#define flat_tuple_filler(...) _flat_tuple_filler(__VA_ARGS__, END_OF_TUPLE)
/**
 * @brief Verifies if a FlatTuple has the same definition as an indefinite
 * number of FlatTypes.
 * 
 * @param tuple         The FlatTuple to be verified.
 * @param definition    An array of FlatTypes with the definition to be
 *                      verified.
 * @return              True if the FlatTuple has the same definition as the
 *                      FlatTypes, false otherwise.
 */
#define flat_tuple_verify_definition(tuple, definition)                     \
            _flat_tuple_verify_definition(tuple, definition,                \
                                        sizeof(definition)/sizeof(FlatType))

//==================================================================//
//              Public functions for internal use                   //
//==================================================================//
/**
 * This functions are for internal use only. They are used by the macros
 * flat_tuple_create, flat_tuple_define, flat_tuple_filler and
 * flat_tuple_verify_definition.
 * 
 * In the case of use some of this functions, the user must be sure that the
 * last argument is END_OF_TUPLE.
 * 
 * @warning Users must not use this functions directly.
 */

/**
 * @warning Users must not use this functions directly.
 */
FlatTuple       _flat_tuple_create                  (FlatPointer    fp,     ...);
/**
 * @warning Users must not use this functions directly.
 */
FlatTuple       _flat_tuple_define                  (FlatType       type,   ...);
/**
 * @warning Users must not use this functions directly.
 */
void            _flat_tuple_filler                  (FlatTuple      tuple, 
                                                     FlatPointer    fp,     ...);
/**
 * @warning Users must not use this functions directly.
 */
bool            _flat_tuple_verify_definition       (FlatTuple      tuple, 
                                                     FlatType *     definition,
                                                     size_t         size);

//==================================================================//
//              Public functions                                    //
//==================================================================//

//      Initialization functions
//      ------------------------
/**
 * @brief Creates a new FlatTuple from an array of FlatPointers.
 * 
 * @param array         The array of FlatPointers to be stored in the tuple.
 * @param size          The size of the array.
 */
FlatTuple       flat_tuple_create_from_array        (FlatPointer *  array, 
                                                     size_t         size);
/**
 * @brief Creates and defines the types of a new empty FlatTuple from an array
 * of FlatTypes. The FlatTuple will be empty, but the types will be defined.
 * 
 * @param types         The types of the FlatTuple.
 * @param size          The size of the array.
 * @return              The new empty FlatTuple.
 */
FlatTuple       flat_tuple_define_from_array        (FlatType *     types, 
                                                     size_t         size);
/**
 * @brief Fills a FlatTuple with an array of FlatPointers. The FlatTuple must
 * be previously defined with the function flat_tuple_define.
 * @warning If the FlatTuple is already filled, the function will fail.
 * @warning If the size of the FlatTuple is different from the size of the
 * array, the function will fail.
 * 
 * @param tuple         The FlatTuple to be filled.
 * @param array         The array of FlatPointers to be stored in the tuple.
 * @param size          The size of the array.
 */
void            flat_tuple_filler_from_array        (FlatTuple      tuple,
                                                     FlatPointer *  array, 
                                                     size_t         size);
                                            
//      Destruction functions
//      ---------------------
/**
 * @brief Destroys a FlatTuple and frees the memory.
 * 
 * @param tuple         The FlatTuple to be destroyed.
 */
void            flat_tuple_destroy                  (FlatTuple      tuple);

//      Query functions
//      ---------------
/**
 * @brief Returns the definition of a FlatTuple as a string.
 * 
 * @param tuple         The FlatTuple to get the definition.
 * @return              The definition of the FlatTuple as a string.
 */
char *          flat_tuple_definition_to_string     (FlatTuple      tuple);
/**
 * @brief Returns the definition of a FlatTuple.
 * 
 * @param tuple         The FlatTuple to get the definition.
 * @return              The definition of the FlatTuple as an array of FlatTypes.
 */
FlatType *      flat_tuple_get_definition           (FlatTuple      tuple);
/**
 * @brief Converts a FlatTuple to an array of FlatPointers.
 * 
 * @param tuple         The FlatTuple to be converted.
 * @return              The array of FlatPointers with the elements of the
 *                      FlatTuple.
 */
FlatPointer *   flat_tuple_to_array                 (FlatTuple      tuple);
/**
 * @brief Returns the element of a FlatTuple at a given index.
 * 
 * @param tuple         The FlatTuple to get the element.
 * @param index         The index of the element in the FlatTuple.
 * @return              The element of the FlatTuple at the given index.
 */
FlatPointer     flat_tuple_get_element              (FlatTuple      tuple, 
                                                     size_t         index);
/**
 * @brief Returns the size of a FlatTuple.
 * 
 * @param tuple         The FlatTuple to get the size.
 * @return              The size of the FlatTuple.
 */
size_t          flat_tuple_length                   (FlatTuple      tuple);
/**
 * @brief Checks if a FlatTuple contains a given FlatPointer.
 * 
 * @param tuple         The FlatTuple to be checked.
 * @param fp            The FlatPointer to be checked.
 * @return              True if the FlatTuple contains the FlatPointer, false
 *                      otherwise.
*/
bool            flat_tuple_contains                 (FlatTuple      tuple1,
                                                     FlatPointer    fp);
/**
 * @brief Returns the number of times a FlatPointer appears in a FlatTuple.
 * 
 * @param tuple         The FlatTuple to be checked.
 * @param fp            The FlatPointer to be checked.
 * @return              The number of times the FlatPointer appears in the
 *                      FlatTuple.
 */
size_t          flat_tuple_count_elements           (FlatTuple      tuple, 
                                                     FlatPointer    fp);
/**
 * @brief Returns the index of the first appearance of a FlatPointer in a
 * FlatTuple.
 * 
 * @param tuple         The FlatTuple to be checked.
 * @param fp            The FlatPointer to be checked.
 * @return              The index of the first appearance of the FlatPointer
 *                      in the FlatTuple.
 */
size_t          flat_tuple_index_of_element         (FlatTuple      tuple, 
                                                     FlatPointer    fp);

//      FLAT Type functions
//      -------------------
/**
 * @brief Returns a string representation of a FlatTuple.
 * 
 * @param tuple         The FlatTuple to be converted.
 * @return              The string representation of the FlatTuple.
 */
char *          flat_tuple_to_string                (FlatTuple      tuple);
/**
 * @brief Checks if two FlatTuples are equal.
 * 
 * @param tuple1        The first FlatTuple to be compared.
 * @param tuple2        The second FlatTuple to be compared.
 * @return              True if the FlatTuples are equal, false otherwise.
 */
bool            flat_tuple_equals                   (FlatTuple      tuple1, 
                                                     FlatTuple      tuple2);
/**
 * @brief Returns the hashcode of a FlatTuple.
 * 
 * @param tuple         The FlatTuple to get the hashcode.
 * @return              The hashcode of the FlatTuple.
 */
int             flat_tuple_hashcode                 (FlatTuple      tuple);
/**
 * @brief Clones a FlatTuple.
 * 
 * @param tuple         The FlatTuple to be cloned.
 * @return              The clone of the FlatTuple.
 * 
 * @warning The clone of a FlatTuple is a new FlatTuple with the same
 * definition and elements, but it is not the same FlatTuple.
 */
FlatTuple       flat_tuple_clone                    (FlatTuple      tuple);

//      Tuple functions
//      ---------------
/**
 * @brief Returns a slice of a FlatTuple from a start index to an end index.
 * 
 * @param tuple         The FlatTuple to be sliced.
 * @param start         The start index of the slice.
 * @param end           The end index of the slice.
 * @return              The slice of the FlatTuple.
 */
FlatTuple       flat_tuple_slice                    (FlatTuple      tuple, 
                                                     size_t         start, 
                                                     size_t         end);
/**
 * @brief Returns a new FlatTuple with the elements of two FlatTuples.
 * 
 * @param tuple1        The first FlatTuple.
 * @param tuple2        The second FlatTuple.
 * @return              The concatenation of the two FlatTuples.
 */
FlatTuple       flat_tuple_concat                   (FlatTuple      tuple1,
                                                     FlatTuple      tuple2);
#endif