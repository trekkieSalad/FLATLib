/* size.c - Size of types
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

//==================================================================//
//              MACRO definitions                                   //
//==================================================================//

#include <datastructfunc.h>
#include <flatset.h>

#define DEFINE_HASH_FUNCTION(TYPE, SUFFIX) \
    size_t SUFFIX##_size() { \
        return sizeof(TYPE); \
    }

//==================================================================//
//              Private functions                                   //
//==================================================================//

DEFINE_HASH_FUNCTION(char, char)
DEFINE_HASH_FUNCTION(unsigned char, uchar)
DEFINE_HASH_FUNCTION(short, short)
DEFINE_HASH_FUNCTION(unsigned short, ushort)
DEFINE_HASH_FUNCTION(int, int)
DEFINE_HASH_FUNCTION(unsigned int, uint)
DEFINE_HASH_FUNCTION(long, long)
DEFINE_HASH_FUNCTION(unsigned long, ulong)
DEFINE_HASH_FUNCTION(long long, longlong)
DEFINE_HASH_FUNCTION(unsigned long long, ulonglong)
DEFINE_HASH_FUNCTION(float, float)
DEFINE_HASH_FUNCTION(double, double)
DEFINE_HASH_FUNCTION(long double, longdouble)

size_t string_size();
size_t set_size();

size_t (*sizes[_TYPE_COUNT])() = {
    char_size,
    uchar_size,
    short_size,
    ushort_size,
    int_size,
    uint_size,
    long_size,
    ulong_size,
    longlong_size,
    ulonglong_size,
    float_size,
    double_size,
    string_size,
    set_size,
    NULL,
};

size_t string_size(){
    return sizeof(char *);
}

size_t set_size(){
    return flat_set_type_size();
}

//==================================================================//
//              Public functions                                    //
//==================================================================//

size_t get_type_size(FlatType type){
    return sizes[type]();
}