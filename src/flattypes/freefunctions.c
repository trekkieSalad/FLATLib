/* freefunctions.c - Free functions for each type.
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

#define DEFINE_FREE_FUNCTION(TYPE, SUFFIX) \
    static void SUFFIX##_free_function(generic_flat_pointer data) { \
        if (!data) return; \
        free(data); \
    }

//==================================================================//
//              Private functions                                   //
//==================================================================//

DEFINE_FREE_FUNCTION(char, char)
DEFINE_FREE_FUNCTION(unsigned char, uchar)
DEFINE_FREE_FUNCTION(short, short)
DEFINE_FREE_FUNCTION(unsigned short, ushort)
DEFINE_FREE_FUNCTION(int, int)
DEFINE_FREE_FUNCTION(unsigned int, uint)
DEFINE_FREE_FUNCTION(long, long)
DEFINE_FREE_FUNCTION(unsigned long, ulong)
DEFINE_FREE_FUNCTION(long long, longlong)
DEFINE_FREE_FUNCTION(unsigned long long, ulonglong)
DEFINE_FREE_FUNCTION(float, float)
DEFINE_FREE_FUNCTION(double, double)

static void string_free_function(generic_flat_pointer data);
static void set_free_function(generic_flat_pointer data);
static void tuple_free_function(generic_flat_pointer data);

static void (*_free_functions[_TYPE_COUNT])(generic_flat_pointer data) = {
    char_free_function,
    uchar_free_function,
    short_free_function,
    ushort_free_function,
    int_free_function,
    uint_free_function,
    long_free_function,
    ulong_free_function,
    longlong_free_function,
    ulonglong_free_function,
    float_free_function,
    double_free_function,
    string_free_function,
    set_free_function,
    tuple_free_function,
};

static void string_free_function(generic_flat_pointer data) {
    if (!data)
        return;
    char *str = (char *)data;
    free(str);
}

static void set_free_function(generic_flat_pointer data){
    FlatSet set = (FlatSet) data;
    flat_set_destroy(set);
}

static void tuple_free_function(generic_flat_pointer data){
    FlatTuple tuple = (FlatTuple) data;
    flat_tuple_destroy(tuple);
}

//==================================================================//
//              Public functions                                    //
//==================================================================//

FreeFunction get_free_function(FlatType type){
    return _free_functions[type];
}