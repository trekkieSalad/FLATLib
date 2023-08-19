/* flattuple.c - Implementation of the FlatTuple data structure.
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

#include <flatpointer.h>
#include <flatcode.h>
#include <flattypes_priv.h>
#include <flattuple.h>
#include <stdarg.h>

//==================================================================//
//              Opaque data structure definition                    //
//==================================================================//

struct _FlatTuple {
    flat_pointer *elements;
    FlatType *types;
    size_t size;
    int fill;
};


//==================================================================//
//              Public functions for internal use                   //
//==================================================================//

FlatTuple _flat_tuple_create(flat_pointer fp, ...) {
    FlatTuple tuple = malloc(sizeof(struct _FlatTuple));
    tuple->fill = 1;
    tuple->size = 0;
    tuple->elements = NULL;
    tuple->types = NULL;
    
    va_list args;
    va_start(args, fp);
    flat_pointer current = fp;
    size_t size = 0;
    while (current != END_OF_TUPLE)
    {
        size_t newSize = (size + 1);
        flat_pointer *newElements = realloc(tuple->elements, sizeof(flat_pointer) * newSize);
        FlatType *newTypes = realloc(tuple->types, sizeof(FlatType) * newSize);
        if (newElements == NULL || newTypes == NULL) {
            // Manejar error de asignación de memoria
            free(newElements);
            free(newTypes);
            free(tuple);
            return NULL;
        }
        tuple->elements = newElements;
        tuple->types = newTypes;
        tuple->elements[size] = current;
        tuple->types[size] = flat_pointer_get_type(current);
        current = va_arg(args, flat_pointer);
        size++;
    }
    tuple->size = size;    
    va_end(args);
    return tuple;
}

FlatTuple _flat_tuple_define(FlatType type, ...) {
    FlatTuple tuple = malloc(sizeof(struct _FlatTuple));
    tuple->fill = 0;
    tuple->size = 0;
    tuple->elements = NULL;
    tuple->types = NULL;
    
    va_list args;
    va_start(args, type);
    FlatType current = type;
    size_t size = 0;
    while (current != END_OF_TUPLE)
    {
        size_t newSize = (size + 1);
        FlatType *newTypes = realloc(tuple->types, sizeof(FlatType) * newSize);
        tuple->types = newTypes;
        tuple->types[size] = current;
        current = va_arg(args, FlatType);
        size++;
    }
    tuple->size = size;    
    va_end(args);
    return tuple;
}

void _flat_tuple_filler(FlatTuple tuple, flat_pointer   fp, ...) {
    if (tuple->fill)
        CRASH_ON_ERROR("tuple is already filled\n");

    va_list args;
    va_start(args, fp);
    size_t size = 0;
    flat_pointer current = fp;
    tuple->elements = malloc(sizeof(flat_pointer) * tuple->size);
    for (size_t i = 0; i < tuple->size; i++)
    {
        if (current == END_OF_TUPLE)
            CRASH_ON_ERROR("tuple has more elements than arguments\n");

        if (flat_pointer_get_type(current) != tuple->types[i])
            CRASH_ON_ERROR(
                "argument %lu has type %s, but tuple has type %s\n", i, 
                flat_type_to_string(flat_pointer_get_type(current)), 
                flat_type_to_string(tuple->types[i])
                );

        size++;
        tuple->elements[i] = current;
        current = va_arg(args, flat_pointer);
    }
    va_end(args);
    tuple->fill = 1;
}

//==================================================================//
//              Public functions                                    //
//==================================================================//

//      Initialization functions
//      ------------------------

FlatTuple flat_tuple_define_from_array(FlatType *types, size_t size) {
    FlatTuple tuple = malloc(sizeof(struct _FlatTuple));
    tuple->types = malloc(sizeof(FlatType) * size);
    for (size_t i = 0; i < size; i++)
    {
        tuple->types[i] = types[i];
    }
    tuple->size = size;
    tuple->fill = 0;
    return tuple;
}

FlatTuple flat_tuple_create_from_array(flat_pointer *array, size_t size) {

    FlatTuple tuple = malloc(sizeof(struct _FlatTuple));
    tuple->elements = array;
    tuple->size = size;
    tuple->fill = 1;
    tuple->types = malloc(sizeof(FlatType) * size);
    for (size_t i = 0; i < size; i++)
    {
        if (array[i] == NULL)
            CRASH_ON_ERROR("Error: flat_tuple_create_from_array: NULL pointer found at position %lu\n", i);
        tuple->types[i] = flat_pointer_get_type(array[i]);
        
    }
    return tuple;
}

void flat_tuple_fill_from_array(FlatTuple tuple, flat_pointer *array, size_t size) {
    if (tuple->fill)
        CRASH_ON_ERROR("tuple is already filled\n");

    if (size != tuple->size)
        CRASH_ON_ERROR("tuple has size %lu, but array has size %lu\n", tuple->size, size);

    for (size_t i = 0; i < size; i++)
    {
        if (array[i] == NULL)
            CRASH_ON_ERROR("Error: flat_tuple_fill_from_array: NULL pointer found at position %lu\n", i);
        if (flat_pointer_get_type(array[i]) != tuple->types[i])
            CRASH_ON_ERROR(
                "argument %lu has type %s, but tuple has type %s\n", i, 
                flat_type_to_string(flat_pointer_get_type(array[i])), 
                flat_type_to_string(tuple->types[i])
                );
    }
    tuple->elements = array;
    tuple->fill = 1;
}

//      Destruction functions
//      ---------------------

void flat_tuple_destroy(FlatTuple tuple) {

    for (size_t i = 0; i < tuple->size; i++)
        flat_pointer_destroy(tuple->elements[i]);

    free(tuple->elements);
    free(tuple->types);
    free(tuple);
}

//      Query functions
//      ---------------

char * flat_tuple_definition_to_string(FlatTuple tuple){
    if (tuple == NULL) CRASH_ON_ERROR("tuple is not defined\n");
    char *str = malloc(sizeof(char) * 2);
    str[0] = '(';
    str[1] = '\0';
    for (size_t i = 0; i < tuple->size; i++)
    {
        char *aux = flat_type_to_string(tuple->types[i]);
        str = realloc(str, sizeof(char) * (strlen(str) + strlen(aux) + 3));
        strcat(str, aux);
        strcat(str, ", ");
    }
    str[strlen(str) - 2] = ')';
    str[strlen(str) - 1] = '\0';
    return str;

}

FlatType *flat_tuple_get_definition(FlatTuple      tuple){
    if (tuple == NULL) CRASH_ON_ERROR("tuple is not defined\n");
    FlatType *types = malloc(sizeof(FlatType) * tuple->size);
    for (size_t i = 0; i < tuple->size; i++)
        types[i] = tuple->types[i];
    return types;
}

flat_pointer flat_tuple_get_element(FlatTuple tuple, size_t index) {
    if (index >= tuple->size)
        CRASH_ON_ERROR("index %lu out of bounds\n", index);
    return tuple->elements[index];
}

char * flat_tuple_to_string(FlatTuple tuple) {
    if (!tuple->fill) CRASH_ON_ERROR("tuple has not elements\n");
    
    char *str = malloc(sizeof(char) * 2);
    str[0] = '(';
    str[1] = '\0';
    for (size_t i = 0; i < tuple->size; i++)
    {
        char *aux = flat_pointer_to_string(tuple->elements[i]);
        str = realloc(str, sizeof(char) * (strlen(str) + strlen(aux) + 3));
        strcat(str, aux);
        strcat(str, ", ");
        free(aux);
    }
    str[strlen(str) - 2] = ')';
    str[strlen(str) - 1] = '\0';
    return str;
}

size_t flat_tuple_length(FlatTuple tuple){
    return tuple->size;
}