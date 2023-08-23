/* datastructfunc.h - Defines the functions that are used to manage the data 
 * structures of the library.
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

#ifndef DATA_STRUCT_FUNC_H
#define DATA_STRUCT_FUNC_H

#include <flattypes.h>
#include <flatset.h>
#include <flattuple.h>

//==================================================================//
//              Type definitions                                    //
//==================================================================//

typedef unsigned int            (*HashFunction)     (const generic_flat_pointer data);
typedef bool                    (*EqualsFunction)   (const generic_flat_pointer setA, 
                                                     const generic_flat_pointer setB);
typedef char *                  (*ToStringFunction) (const generic_flat_pointer data);
typedef generic_flat_pointer    (*CloneFunction)    (const generic_flat_pointer data);
typedef void                    (*FreeFunction)     (generic_flat_pointer       data);

//==================================================================//
//              Public functions                                    //
//==================================================================//

HashFunction        get_hash_function       (FlatType);
EqualsFunction      get_equals_function     (FlatType);
ToStringFunction    get_to_string_function  (FlatType);
CloneFunction       get_clone_function      (FlatType);
FreeFunction        get_free_function       (FlatType);
size_t              get_type_size           (FlatType);

#endif // DATA_STRUCT_FUNC_H