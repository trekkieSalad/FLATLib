/* flattypes.h
 *
 * FLATLib - Library of formal languages and automata theory algorithms.
 * Copyright (C) 2023  Daniel José García Paz
 * 
 * SPDX-License-Identifier: LGPL-2.1-or-later
 *
 * This library  is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 * 
 * Author: Daniel José García Paz <daniel.garcia.paz@udc.es>
 */

#ifndef SET_TYPES_H
#define SET_TYPES_H

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
    USER_DEFINED,
    _TYPE_COUNT,
}Type;

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