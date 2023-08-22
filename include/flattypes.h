/* flattypes.h
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
/**
 * @file flattypes.h
 * 
 * @brief This file contains the definition of the flat types and the generic
 * flat pointer. These types are used to store and manipulate values of different
 * types in the same data structure and have a typed context to retrieve them.
 */

#ifndef SET_TYPES_H
#define SET_TYPES_H

#include <stdbool.h>

/**
 * @typedef FlatType
 * 
 * @brief A flat type is a type that can be stored in a flat pointer. It is used
 * to store and reference values of different types in the same data structure.
 * 
 * The flat types are the primitive types, strings, sets, tuples and user 
 * defined types.
 */
typedef enum {
    CHAR,
    UCHAR,
    SHORT,
    USHORT,
    INT,
    UINT,
    LONG,
    ULONG,
    LONG_LONG,
    ULONG_LONG,
    FLOAT,
    DOUBLE,
    STRING,
    SET,
    TUPLE,
    USER_DEFINED,
    _TYPE_COUNT,
}FlatType;

/**
 * @typedef generic_flat_pointer
 * @brief A flat pointer is an alias for a void pointer.
 */
typedef     void *              generic_flat_pointer;
typedef     char                flatchar;
typedef     unsigned char       flatuchar;
typedef     short               flatshort;
typedef     unsigned short      flatushort;
typedef     int                 flatint;
typedef     unsigned int        flatuint;
typedef     long                flatlong;
typedef     unsigned long       flatulong;
typedef     long long           flatlonglong;
typedef     unsigned long long  flatulonglong;
typedef     float               flatfloat;
typedef     double              flatdouble;
typedef     char *              flatstring;

#endif // TYPES_H