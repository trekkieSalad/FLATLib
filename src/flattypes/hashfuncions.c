/* hashfunctions.c - Hash functions for the different types of data.
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

#define DEFINE_HASH_FUNCTION(TYPE, SUFFIX, MULTIPLIER) \
    unsigned int SUFFIX##_hash_function(const generic_flat_pointer data) { \
        const TYPE value = *(const TYPE *)data; \
        return (unsigned int) (value * MULTIPLIER); \
    }

DEFINE_HASH_FUNCTION(char, char, 1)
DEFINE_HASH_FUNCTION(unsigned char, uchar, 1)
DEFINE_HASH_FUNCTION(short, short, 1)
DEFINE_HASH_FUNCTION(unsigned short, ushort, 1)
DEFINE_HASH_FUNCTION(int, int, 1)
DEFINE_HASH_FUNCTION(unsigned int, uint, 1)
DEFINE_HASH_FUNCTION(long, long, 1)
DEFINE_HASH_FUNCTION(unsigned long, ulong, 1)
DEFINE_HASH_FUNCTION(long long, longlong, 1)
DEFINE_HASH_FUNCTION(unsigned long long, ulonglong, 1)
DEFINE_HASH_FUNCTION(float, float, 1000)
DEFINE_HASH_FUNCTION(double, double, 1000)

unsigned int string_hash_function(const generic_flat_pointer data);
unsigned int set_hash_function(const generic_flat_pointer data);
unsigned int tuple_hash_function(const generic_flat_pointer data);


unsigned int (*_hash_functions[_TYPE_COUNT])(const generic_flat_pointer data) = {
    char_hash_function,
    uchar_hash_function,
    short_hash_function,
    ushort_hash_function,
    int_hash_function,
    uint_hash_function,
    long_hash_function,
    ulong_hash_function,
    longlong_hash_function,
    ulonglong_hash_function,
    float_hash_function,
    double_hash_function,
    string_hash_function,
    set_hash_function,
    tuple_hash_function,
};

unsigned int string_hash_function(const generic_flat_pointer data){
    const char *value = (const char *) data;
    unsigned int hash = 0;
    for (size_t i = 0; i < strlen(value); i++){
        hash += value[i];
    }
    return hash;
}

unsigned int set_hash_function(const generic_flat_pointer data){
    const FlatSet value = (const FlatSet) data;
    return flat_set_hashcode(value);
}

unsigned int tuple_hash_function(const generic_flat_pointer data){
    const FlatTuple value = (const FlatTuple) data;
    return flat_tuple_hashcode(value);
}

HashFunction get_hash_function(FlatType type){
    return _hash_functions[type];
}