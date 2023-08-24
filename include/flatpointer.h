/* flatpointer.h
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

#ifndef FLAT_POINTER_H
#define FLAT_POINTER_H

#include <flattypes.h>

/**
 * @brief Creates a flat pointer from a primitive type or a string.
 * @param data Data to be converted to a flat pointer.
 * @return A flat pointer with the data as value.
 */
#define FLAT_POINTER_CREATOR(data) _Generic((data), \
    char:               CHAR_FLAT_POINTER,          \
    unsigned char:      UCHAR_FLAT_POINTER,         \
    short:              SHORT_FLAT_POINTER,         \
    unsigned short:     USHORT_FLAT_POINTER,        \
    int:                INT_FLAT_POINTER,           \
    unsigned int:       UINT_FLAT_POINTER,          \
    long:               LONG_FLAT_POINTER,          \
    unsigned long:      ULONG_FLAT_POINTER,         \
    long long:          LONG_LONG_FLAT_POINTER,     \
    unsigned long long: ULONG_LONG_FLAT_POINTER,    \
    float:              FLOAT_FLAT_POINTER,         \
    double:             DOUBLE_FLAT_POINTER,        \
    char *:             STRING_FLAT_POINTER,        \
    FlatSet:            SET_FLAT_POINTER,           \
    FlatTuple:          TUPLE_FLAT_POINTER,         \
    default:            __INVALID_TYPE_ERROR\
)(data)



//==================================================================//
//              Public functions                                    //
//==================================================================//

//      Initialization functions
//      ------------------------
/**
 * This collection of functions creates a flat pointer from a primitive type, a 
 * string or a FLATlib data structure. The type of the flat pointer is the same
 * as the type of the data. For example, if you want to create a flat pointer
 * from an int, you can use INT_FLAT_POINTER(5) or FLAT_POINTER_CREATOR(5).
 */

FlatPointer             CHAR_FLAT_POINTER            (char                   x);
FlatPointer             UCHAR_FLAT_POINTER           (unsigned char          x);
FlatPointer             SHORT_FLAT_POINTER           (short                  x);
FlatPointer             USHORT_FLAT_POINTER          (unsigned short         x);
FlatPointer             INT_FLAT_POINTER             (int                    x);
FlatPointer             UINT_FLAT_POINTER            (unsigned int           x);
FlatPointer             LONG_FLAT_POINTER            (long                   x);
FlatPointer             ULONG_FLAT_POINTER           (unsigned long          x);
FlatPointer             LONG_LONG_FLAT_POINTER       (long long              x);
FlatPointer             ULONG_LONG_FLAT_POINTER      (unsigned long long     x);
FlatPointer             FLOAT_FLAT_POINTER           (float                  x);
FlatPointer             DOUBLE_FLAT_POINTER          (double                 x);
FlatPointer             STRING_FLAT_POINTER          (char *                 x);
FlatPointer             SET_FLAT_POINTER             (FlatSet                x);
FlatPointer             TUPLE_FLAT_POINTER           (FlatTuple              x);

/**
 * This function mustn't be used directly. It is only for internal use.
 */
FlatPointer             __INVALID_TYPE_ERROR        ();

/**
 * @brief Creates a flat pointer from a primitive type, a string or a FLATlib
 * data structure.
 * 
 * @param type Type of the flat pointer.
 * @param value Value of the flat pointer.
 * @return A flat pointer with the type and value specified.
*/
FlatPointer             flat_pointer_create         (FlatType               type, 
                                                     generic_flat_pointer   value);

//      Query functions
//      ---------------
/**
 * This collection of functions returns the value of a flat pointer as a
 * primitive type, a string or a FLATlib data structure. The type of the flat
 * pointer must be the same as the type of the data. For example, if you want to
 * get the value of a flat pointer as an int, you can use
 * FLAT_POINTER_TO_INT(fp).
 */

char                    FLAT_POINTER_TO_CHAR        (FlatPointer            x);
unsigned char           FLAT_POINTER_TO_UCHAR       (FlatPointer            x);
short                   FLAT_POINTER_TO_SHORT       (FlatPointer            x);
unsigned short          FLAT_POINTER_TO_USHORT      (FlatPointer            x);
int                     FLAT_POINTER_TO_INT         (FlatPointer            x);
unsigned int            FLAT_POINTER_TO_UINT        (FlatPointer            x);
long                    FLAT_POINTER_TO_LONG        (FlatPointer            x);
unsigned long           FLAT_POINTER_TO_ULONG       (FlatPointer            x);
long long               FLAT_POINTER_TO_LONG_LONG   (FlatPointer            x);
unsigned long long      FLAT_POINTER_TO_ULONG_LONG  (FlatPointer            x);
float                   FLAT_POINTER_TO_FLOAT       (FlatPointer            x);
double                  FLAT_POINTER_TO_DOUBLE      (FlatPointer            x);
char *                  FLAT_POINTER_TO_STRING      (FlatPointer            x);
FlatSet                 FLAT_POINTER_TO_SET         (FlatPointer            x);
FlatTuple               FLAT_POINTER_TO_TUPLE       (FlatPointer            x);

/**
 * @brief Gets the type of a flat pointer.
 * 
 * @param fp Flat pointer to get the type.
 * @return The type of the flat pointer.
 */
FlatType                flat_pointer_get_type       (FlatPointer            fp);
/**
 * @brief Gets the value of a flat pointer.
 * 
 * @param fp Flat pointer to get the value.
 * @return The value of the flat pointer.
 */
generic_flat_pointer    flat_pointer_get_value      (FlatPointer            fp);
                                            
//      Destruction functions
//      ---------------------

/**
 * @brief Destroys a flat pointer.
 * 
 * Frees the memory allocated by a flat pointer.
 * 
 * @param fp Flat pointer to be destroyed.
 */
void                    flat_pointer_destroy        (FlatPointer            fp);

//      FLAT Type functions
//      -------------------

/**
 * @brief Generates a string representation of a flat pointer value.
 * 
 * @param fp Flat pointer to be represented.
 * @return A string representation of the flat pointer value.
*/
char *                  flat_pointer_to_string      (FlatPointer            fp);

/**
 * @brief Clones a flat pointer.
 * 
 * @param fp Flat pointer to be cloned.
 * @return A pointer to the new flat pointer.
 */
FlatPointer             flat_pointer_clone          (FlatPointer            fp);

/**
 * @brief Checks if two flat pointers are equal.
 * 
 * Two flat pointers are equal if they have the same type and value.
 * 
 * @param fp1 First flat pointer.
 * @param fp2 Second flat pointer.
 * @return True if the flat pointers are equal, false otherwise.
 */
bool                    flat_pointer_equals         (FlatPointer            fp1, 
                                                     FlatPointer            fp2);

/**
 * @brief Returns the hashcode of a flat pointer.
 * 
 * The hashcode is calculated using the hashcode of the value of the flat
 * pointer.
 * 
 * @param fp Flat pointer to calculate the hashcode.
 * @return The hashcode of the flat pointer.
 */
int                     flat_pointer_hashcode       (FlatPointer            fp);

#endif