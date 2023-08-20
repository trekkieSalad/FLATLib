/* tostringfunctions.c
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

#define DEFINE_TO_STRING_FUNCTION(TYPE, SUFFIX, FORMAT) \
    char * SUFFIX##_to_string_function(const generic_flat_pointer data) { \
        TYPE value = *(TYPE *)data; \
        char *string = malloc(12 * sizeof(char)); \
        sprintf(string, FORMAT, value); \
        return string; \
    }

DEFINE_TO_STRING_FUNCTION(char, char, "%c")
DEFINE_TO_STRING_FUNCTION(unsigned char, uchar, "%c")
DEFINE_TO_STRING_FUNCTION(short, short, "%d")
DEFINE_TO_STRING_FUNCTION(unsigned short, ushort, "%d")
DEFINE_TO_STRING_FUNCTION(int, int, "%d")
DEFINE_TO_STRING_FUNCTION(unsigned int, uint, "%d")
DEFINE_TO_STRING_FUNCTION(long, long, "%ld")
DEFINE_TO_STRING_FUNCTION(unsigned long, ulong, "%ld")
DEFINE_TO_STRING_FUNCTION(long long, longlong, "%lld")
DEFINE_TO_STRING_FUNCTION(unsigned long long, ulonglong, "%lld")
DEFINE_TO_STRING_FUNCTION(float, float, "%.2f")
DEFINE_TO_STRING_FUNCTION(double, double, "%.4f")
DEFINE_TO_STRING_FUNCTION(long double, longdouble, "%.4Lf")


char * string_to_string_function(const generic_flat_pointer data);
char * set_to_string_function(const generic_flat_pointer data);

char * (*_to_string_functions[_TYPE_COUNT])(const generic_flat_pointer data) = {
    char_to_string_function,
    uchar_to_string_function,
    short_to_string_function,
    ushort_to_string_function,
    int_to_string_function,
    uint_to_string_function,
    long_to_string_function,
    ulong_to_string_function,
    longlong_to_string_function,
    ulonglong_to_string_function,
    float_to_string_function,
    double_to_string_function,
    string_to_string_function,
    set_to_string_function,
    NULL,
};

char * string_to_string_function(const generic_flat_pointer data){
    return get_clone_function(STRING)(data);
}

char * set_to_string_function(const generic_flat_pointer data){
    const FlatSet set = (const FlatSet) data;
    return flat_set_to_string(set);
}

ToStringFunction get_to_string_function(FlatType type){
    return _to_string_functions[type];
}