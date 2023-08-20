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

#include <flatset.h>

/**
 * @brief A flat pointer is a pointer to a typed value.
 * 
 * A flat pointer is a pointer to a typed value. It is used to store values of
 * different types and let the user retrieve them as the original type. It is 
 * used by the FLATlib data structures. * 
 */
typedef struct _flat_pointer    *flat_pointer;

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
    FlatSet:            SET_FLAT_POINTER            \
)(data)

/**
 * @brief Creates a flat pointer from a char.
 * @param x Data to be converted to a flat pointer.
 * @return A flat pointer with the data as value.
 */
flat_pointer        CHAR_FLAT_POINTER           (char x);
/**
 * @brief Creates a flat pointer from an unsigned char.
 * @param x Data to be converted to a flat pointer.
 * @return A flat pointer with the data as value.
 */
flat_pointer        UCHAR_FLAT_POINTER          (unsigned char x);
/**
 * @brief Creates a flat pointer from a short.
 * @param x Data to be converted to a flat pointer.
 * @return A flat pointer with the data as value.
 */
flat_pointer        SHORT_FLAT_POINTER          (short x);
/**
 * @brief Creates a flat pointer from an unsigned short.
 * @param x Data to be converted to a flat pointer.
 * @return A flat pointer with the data as value.
 */
flat_pointer        USHORT_FLAT_POINTER         (unsigned short x);
/**
 * @brief Creates a flat pointer from an int.
 * @param x Data to be converted to a flat pointer.
 * @return A flat pointer with the data as value.
 */
flat_pointer        INT_FLAT_POINTER            (int x);
/**
 * @brief Creates a flat pointer from an unsigned int.
 * @param x Data to be converted to a flat pointer.
 * @return A flat pointer with the data as value.
 */
flat_pointer        UINT_FLAT_POINTER           (unsigned int x);
/**
 * @brief Creates a flat pointer from a long.
 * @param x Data to be converted to a flat pointer.
 * @return A flat pointer with the data as value.
 */
flat_pointer        LONG_FLAT_POINTER           (long x);
/**
 * @brief Creates a flat pointer from an unsigned long.
 * @param x Data to be converted to a flat pointer.
 * @return A flat pointer with the data as value.
 */
flat_pointer        ULONG_FLAT_POINTER          (unsigned long x);
/**
 * @brief Creates a flat pointer from a long long.
 * @param x Data to be converted to a flat pointer.
 * @return A flat pointer with the data as value.
 */
flat_pointer        LONG_LONG_FLAT_POINTER      (long long x);
/**
 * @brief Creates a flat pointer from an unsigned long long.
 * @param x Data to be converted to a flat pointer.
 * @return A flat pointer with the data as value.
 */
flat_pointer        ULONG_LONG_FLAT_POINTER     (unsigned long long x);
/**
 * @brief Creates a flat pointer from a float.
 * @param x Data to be converted to a flat pointer.
 * @return A flat pointer with the data as value.
 */
flat_pointer        FLOAT_FLAT_POINTER          (float x);
/**
 * @brief Creates a flat pointer from a double.
 * @param x Data to be converted to a flat pointer.
 * @return A flat pointer with the data as value.
 */
flat_pointer        DOUBLE_FLAT_POINTER         (double x);
/**
 * @brief Creates a flat pointer from a string.
 * @param x Data to be converted to a flat pointer.
 * @return A flat pointer with the data as value.
 */
flat_pointer        STRING_FLAT_POINTER         (char *x);
/**
 * @brief Creates a flat pointer from a set.
 * @param x Data to be converted to a flat pointer.
 * @return A flat pointer with the data as value.
 */
flat_pointer        SET_FLAT_POINTER            (FlatSet x);

/**
 * @brief Converts a flat pointer to a char.
 * 
 * Converts a flat pointer to a char. If the flat pointer is not a char, one
 * error is printed and the program is aborted.
 * 
 * @param x Flat pointer to be converted.
 * @return The value of the flat pointer as a char.
 */
char                FLAT_POINTER_TO_CHAR        (flat_pointer x);
/**
 * @brief Converts a flat pointer to an unsigned char.
 * 
 * Converts a flat pointer to an unsigned char. If the flat pointer is not an
 * unsigned char, one error is printed and the program is aborted.
 * 
 * @param x Flat pointer to be converted.
 * @return The value of the flat pointer as an unsigned char.
 */
unsigned char       FLAT_POINTER_TO_UCHAR       (flat_pointer x);
/**
 * @brief Converts a flat pointer to a short.
 * 
 * Converts a flat pointer to a short. If the flat pointer is not a short, one
 * error is printed and the program is aborted.
 * 
 * @param x Flat pointer to be converted.
 * @return The value of the flat pointer as a short.
 */
short               FLAT_POINTER_TO_SHORT       (flat_pointer x);
/**
 * @brief Converts a flat pointer to an unsigned short.
 * 
 * Converts a flat pointer to an unsigned short. If the flat pointer is not an
 * unsigned short, one error is printed and the program is aborted.
 * 
 * @param x Flat pointer to be converted.
 * @return The value of the flat pointer as an unsigned short.
 */
unsigned short      FLAT_POINTER_TO_USHORT      (flat_pointer x);
/**
 * @brief Converts a flat pointer to an int.
 * 
 * Converts a flat pointer to an int. If the flat pointer is not an int, one
 * error is printed and the program is aborted.
 * 
 * @param x Flat pointer to be converted.
 * @return The value of the flat pointer as an int.
 */
int                 FLAT_POINTER_TO_INT         (flat_pointer x);
/**
 * @brief Converts a flat pointer to an unsigned int.
 * 
 * Converts a flat pointer to an unsigned int. If the flat pointer is not an
 * unsigned int, one error is printed and the program is aborted.
 * 
 * @param x Flat pointer to be converted.
 * @return The value of the flat pointer as an unsigned int.
 */
unsigned int        FLAT_POINTER_TO_UINT        (flat_pointer x);
/**
 * @brief Converts a flat pointer to a long.
 * 
 * Converts a flat pointer to a long. If the flat pointer is not a long, one
 * error is printed and the program is aborted.
 * 
 * @param x Flat pointer to be converted.
 * @return The value of the flat pointer as a long.
 */
long                FLAT_POINTER_TO_LONG        (flat_pointer x);
/**
 * @brief Converts a flat pointer to an unsigned long.
 * 
 * Converts a flat pointer to an unsigned long. If the flat pointer is not an
 * unsigned long, one error is printed and the program is aborted.
 * 
 * @param x Flat pointer to be converted.
 * @return The value of the flat pointer as an unsigned long.
 */
unsigned long       FLAT_POINTER_TO_ULONG       (flat_pointer x);
/**
 * @brief Converts a flat pointer to a long long.
 * 
 * Converts a flat pointer to a long long. If the flat pointer is not a long long,
 * one error is printed and the program is aborted.
 * 
 * @param x Flat pointer to be converted.
 * @return The value of the flat pointer as a long long.
 */
long long           FLAT_POINTER_TO_LONG_LONG   (flat_pointer x);
/**
 * @brief Converts a flat pointer to an unsigned long long.
 * 
 * Converts a flat pointer to an unsigned long long. If the flat pointer is not 
 * an unsigned long long, one error is printed and the program is aborted.
 * 
 * @param x Flat pointer to be converted.
 * @return The value of the flat pointer as an unsigned long long.
 */
unsigned long long  FLAT_POINTER_TO_ULONG_LONG  (flat_pointer x);
/**
 * @brief Converts a flat pointer to a float.
 * 
 * Converts a flat pointer to a float. If the flat pointer is not a float, one
 * error is printed and the program is aborted.
 * 
 * @param x Flat pointer to be converted.
 * @return The value of the flat pointer as a float.
 */
float               FLAT_POINTER_TO_FLOAT       (flat_pointer x);
/**
 * @brief Converts a flat pointer to a double.
 * 
 * Converts a flat pointer to a double. If the flat pointer is not a double, one
 * error is printed and the program is aborted.
 * 
 * @param x Flat pointer to be converted.
 * @return The value of the flat pointer as a double.
 */
double              FLAT_POINTER_TO_DOUBLE      (flat_pointer x);
/**
 * @brief Converts a flat pointer to a string.
 * 
 * Converts a flat pointer to a string. If the flat pointer is not a string, one
 * error is printed and the program is aborted.
 * 
 * @param x Flat pointer to be converted.
 * @return The value of the flat pointer as a string.
 */
char *              FLAT_POINTER_TO_STRING      (flat_pointer x);
/**
 * @brief Converts a flat pointer to a flat set.
 * 
 * Converts a flat pointer to a set. If the flat pointer is not a flat set, one
 * error is printed and the program is aborted.
 * 
 * @param x Flat pointer to be converted.
 * @return The value of the flat pointer as a set.
 */
FlatSet             FLAT_POINTER_TO_SET         (flat_pointer x);

/**
 * @brief Creates a flat pointer from a generic flat pointer (void *). 
 * 
 * @param type Type of the flat pointer.
 * @param value Generic flat pointer to the value.
 * @return A flat pointer with the data as value.
 */
flat_pointer    flat_pointer_create     (FlatType               type, 
                                         generic_flat_pointer   value);
/**
 * @brief Destroys a flat pointer.
 * 
 * Frees the memory allocated by a flat pointer.
 * 
 * @param fp Flat pointer to be destroyed.
 */
void            flat_pointer_destroy    (flat_pointer           fp);
/**
 * @brief Gets the type of a flat pointer.
 * 
 * @param fp Flat pointer to get the type.
 * @return The type of the flat pointer.
 */
FlatType        flat_pointer_get_type   (flat_pointer           fp);
/**
 * @brief Generates a string representation of a flat pointer value.
 * @param fp Flat pointer to be represented.
 * @return A string representation of the flat pointer value.
*/
char * flat_pointer_to_string(flat_pointer fp);

flat_pointer flat_pointer_clone(flat_pointer fp);

bool    flat_pointer_equals     (flat_pointer fp1, flat_pointer fp2);

int     flat_pointer_hashcode   (flat_pointer fp);

#endif