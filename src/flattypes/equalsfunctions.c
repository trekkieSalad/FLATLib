/* equalsfunctions.c - Implementation of equals functions for each type.
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
#include <stdlib.h>
#include <string.h>

#include <datastructfunc.h>

//==================================================================//
//              MACRO definitions                                   //
//==================================================================//

#define DEFINE_EQUALS_FUNCTION(TYPE, SUFFIX) \
    static bool SUFFIX##_equals_function(const generic_flat_pointer data1, const generic_flat_pointer data2) { \
        TYPE value1 = *(TYPE *)data1; \
        TYPE value2 = *(TYPE *)data2; \
        return value1 == value2; \
    }

//==================================================================//
//              Private functions                                   //
//==================================================================//

DEFINE_EQUALS_FUNCTION(char, char)
DEFINE_EQUALS_FUNCTION(unsigned char, uchar)
DEFINE_EQUALS_FUNCTION(short, short)
DEFINE_EQUALS_FUNCTION(unsigned short, ushort)
DEFINE_EQUALS_FUNCTION(int, int)
DEFINE_EQUALS_FUNCTION(unsigned int, uint)
DEFINE_EQUALS_FUNCTION(long, long)
DEFINE_EQUALS_FUNCTION(unsigned long, ulong)
DEFINE_EQUALS_FUNCTION(long long, longlong)
DEFINE_EQUALS_FUNCTION(unsigned long long, ulonglong)
DEFINE_EQUALS_FUNCTION(float, float)
DEFINE_EQUALS_FUNCTION(double, double)

static bool string_equals_function(const generic_flat_pointer data1, const generic_flat_pointer data2);
static bool set_equals_function(const generic_flat_pointer data1, const generic_flat_pointer data2);
static bool tuple_equals_function(const generic_flat_pointer data1, const generic_flat_pointer data2);

static bool (*_equals_functions[_TYPE_COUNT])(const generic_flat_pointer data1, const generic_flat_pointer data2) = {
    char_equals_function,
    uchar_equals_function,
    short_equals_function,
    ushort_equals_function,
    int_equals_function,
    uint_equals_function,
    long_equals_function,
    ulong_equals_function,
    longlong_equals_function,
    ulonglong_equals_function,
    float_equals_function,
    double_equals_function,
    string_equals_function,
    set_equals_function,
    tuple_equals_function,
};

static bool string_equals_function(const generic_flat_pointer data1, const generic_flat_pointer data2) {
    char *value1 = (char *)data1;
    char *value2 = (char *)data2;

    return strcmp(value1, value2) == 0;
}

static bool set_equals_function(const generic_flat_pointer data1, const generic_flat_pointer data2) {
    const FlatSet value1 = (const FlatSet)data1;
    const FlatSet value2 = (const FlatSet)data2;
    return flat_set_equals(value1, value2);
}

static bool tuple_equals_function(const generic_flat_pointer data1, const generic_flat_pointer data2) {
    const FlatTuple value1 = (const FlatTuple)data1;
    const FlatTuple value2 = (const FlatTuple)data2;
    return flat_tuple_equals(value1, value2);
}

//==================================================================//
//              Public functions                                    //
//==================================================================//

EqualsFunction get_equals_function(FlatType type) {
    return _equals_functions[type];
}