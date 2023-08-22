/* clonefunctions.c - Implementation of clone functions for each type.
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

#include <datastructfunc.h>
#include <flatset.h>
#include <flattuple.h>

//==================================================================//
//              MACRO definitions                                   //
//==================================================================//

#define DEFINE_CLONE_FUNCTION(TYPE, SUFFIX) \
    static generic_flat_pointer  SUFFIX##_clone_function(const generic_flat_pointer data) { \
        if (!data) \
            return NULL; \
        TYPE *value = (TYPE *)data; \
        TYPE *clone = (TYPE *)malloc(sizeof(TYPE)); \
        *clone = *value; \
        return clone; \
    }

//==================================================================//
//              Private functions                                   //
//==================================================================//

DEFINE_CLONE_FUNCTION(char, char)
DEFINE_CLONE_FUNCTION(unsigned char, uchar)
DEFINE_CLONE_FUNCTION(short, short)
DEFINE_CLONE_FUNCTION(unsigned short, ushort)
DEFINE_CLONE_FUNCTION(int, int)
DEFINE_CLONE_FUNCTION(unsigned int, uint)
DEFINE_CLONE_FUNCTION(long, long)
DEFINE_CLONE_FUNCTION(unsigned long, ulong)
DEFINE_CLONE_FUNCTION(long long, longlong)
DEFINE_CLONE_FUNCTION(unsigned long long, ulonglong)
DEFINE_CLONE_FUNCTION(float, float)
DEFINE_CLONE_FUNCTION(double, double)


static generic_flat_pointer  string_clone_function(const generic_flat_pointer data);
static generic_flat_pointer  set_clone_function(const generic_flat_pointer data);
static generic_flat_pointer  tuple_clone_function(const generic_flat_pointer data);

static generic_flat_pointer  (*_clone_functions[_TYPE_COUNT])(const generic_flat_pointer data) = {
    char_clone_function,
    uchar_clone_function,
    short_clone_function,
    ushort_clone_function,
    int_clone_function,
    uint_clone_function,
    long_clone_function,
    ulong_clone_function,
    longlong_clone_function,
    ulonglong_clone_function,
    float_clone_function,
    double_clone_function,
    string_clone_function,
    set_clone_function,
    tuple_clone_function
};

static generic_flat_pointer string_clone_function(const generic_flat_pointer data) {
    if (!data)
        return NULL;

    const char *str = (const char *)data;
    size_t len = strlen(str);

    char *copy = (char *)malloc((len + 1) * sizeof(char)); // +1 for null terminator
    if (copy) {
        strcpy(copy, str);
    }
    return copy;
}

static generic_flat_pointer  set_clone_function(const generic_flat_pointer data){
    if (!data)
        return NULL;
    const FlatSet set = (const FlatSet) data;
    FlatSet copy = flat_set_clone(set);
    return copy;
}

static generic_flat_pointer  tuple_clone_function(const generic_flat_pointer data){
    if (!data)
        return NULL;
    const FlatTuple tuple = (const FlatTuple) data;
    FlatTuple copy = flat_tuple_clone(tuple);
    return copy;
}

//==================================================================//
//              Public functions                                    //
//==================================================================//

CloneFunction get_clone_function(FlatType type){
    return _clone_functions[type];
}