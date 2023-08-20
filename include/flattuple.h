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

typedef struct _FlatTuple * FlatTuple;


#define flat_tuple_create(...) _flat_tuple_create(__VA_ARGS__, END_OF_TUPLE)
#define flat_tuple_define(...) _flat_tuple_define(__VA_ARGS__, END_OF_TUPLE)
#define flat_tuple_filler(...) _flat_tuple_filler(__VA_ARGS__, END_OF_TUPLE)
#define flat_tuple_verify_definition(tuple, definition) _flat_tuple_verify_definition(tuple, definition, sizeof(definition)/sizeof(FlatType))

//==================================================================//
//              Public functions for internal use                   //
//==================================================================//

FlatTuple       _flat_tuple_create                  (flat_pointer   fp,     ...);
FlatTuple       _flat_tuple_define                  (FlatType       type,   ...);
void            _flat_tuple_filler                  (FlatTuple      tuple, 
                                                     flat_pointer   fp,     ...);
bool            _flat_tuple_verify_definition       (FlatTuple      tuple, 
                                                     FlatType *     definition,
                                                     size_t         size);

//==================================================================//
//              Public functions                                    //
//==================================================================//

//      Initialization functions
//      ------------------------
FlatTuple       flat_tuple_create_from_array        (flat_pointer * array, 
                                                     size_t         size);
FlatTuple       flat_tuple_define_from_array        (FlatType *     types, 
                                                     size_t         size);
void            flat_tuple_filler_from_array        (FlatTuple      tuple,
                                                     flat_pointer * array, 
                                                     size_t         size);
                                            
//      Destruction functions
//      ---------------------

void            flat_tuple_destroy                  (FlatTuple      tuple);

//      Query functions
//      ---------------

char *          flat_tuple_definition_to_string     (FlatTuple      tuple);
FlatType *      flat_tuple_get_definition           (FlatTuple      tuple);
flat_pointer *  flat_tuple_to_array                 (FlatTuple      tuple);
flat_pointer    flat_tuple_get_element              (FlatTuple      tuple, 
                                                     size_t         index);
size_t          flat_tuple_length                   (FlatTuple      tuple);
bool            flat_tuple_contains                 (FlatTuple      tuple1,
                                                     flat_pointer   fp);
size_t          flat_tuple_count_elements           (FlatTuple      tuple, 
                                                     flat_pointer   fp);
size_t          flat_tuple_index_of_element         (FlatTuple      tuple, 
                                                     flat_pointer   fp);

//      FLAT ADT functions
//      ------------------

char *          flat_tuple_to_string                (FlatTuple      tuple);
bool            flat_tuple_equals                   (FlatTuple      tuple1, 
                                                     FlatTuple      tuple2);

//      Tuple functions
//      ---------------

FlatTuple       flat_tuple_slice                    (FlatTuple      tuple, 
                                                     size_t         start, 
                                                     size_t         end);
FlatTuple       flat_tuple_concat                   (FlatTuple      tuple1,
                                                     FlatTuple      tuple2);
#endif