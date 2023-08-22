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
    FlatPointer *elements;
    FlatType *types;
    size_t size;
    int fill;
};


//==================================================================//
//              Public functions for internal use                   //
//==================================================================//

FlatTuple _flat_tuple_create(FlatPointer fp, ...) {
    FlatTuple tuple = malloc(sizeof(struct _FlatTuple));
    // initialize tuple with 0 elements
    tuple->fill = 1;
    tuple->size = 0;
    tuple->elements = NULL;
    tuple->types = NULL;
    
    va_list args;
    va_start(args, fp);
    FlatPointer current = fp;
    size_t size = 0;
    // Insert elements until END_OF_TUPLE is found
    while (current != END_OF_TUPLE)
    {
        size_t newSize = (size + 1);
        // Reallocate memory for new element
        FlatPointer *newElements = realloc(tuple->elements, sizeof(FlatPointer) * newSize);
        FlatType *newTypes = realloc(tuple->types, sizeof(FlatType) * newSize);
        // Check if memory allocation was successful
        if (newElements == NULL || newTypes == NULL) {
            // Manejar error de asignación de memoria
            free(newElements);
            free(newTypes);
            free(tuple);
            return NULL;
        }
        // Update tuple
        tuple->elements = newElements;
        tuple->types = newTypes;
        tuple->elements[size] = current;
        tuple->types[size] = flat_pointer_get_type(current);

        // Get next element
        current = va_arg(args, FlatPointer);
        size++;
    }
    tuple->size = size;    
    va_end(args);
    return tuple;
}

FlatTuple _flat_tuple_define(FlatType type, ...) {
    FlatTuple tuple = malloc(sizeof(struct _FlatTuple));
    // initialize tuple with 0 elements
    tuple->fill = 0;
    tuple->size = 0;
    tuple->elements = NULL;
    tuple->types = NULL;
    
    va_list args;
    va_start(args, type);
    FlatType current = type;
    size_t size = 0;
    // Insert types until END_OF_TUPLE is found
    while (current != END_OF_TUPLE)
    {
        size_t newSize = (size + 1);
        // Reallocate memory for new type
        FlatType *newTypes = realloc(tuple->types, sizeof(FlatType) * newSize);
        // Add new type to tuple definition
        tuple->types = newTypes;
        tuple->types[size] = current;
        current = va_arg(args, FlatType);
        size++;
    }
    tuple->size = size;    
    va_end(args);
    return tuple;
}

void _flat_tuple_filler(FlatTuple tuple, FlatPointer fp, ...) {
    // Check if tuple is already filled
    if (tuple->fill)
        CRASH_ON_ERROR("tuple is already filled\n");

    va_list args;
    va_start(args, fp);
    size_t size = 0;
    FlatPointer current = fp;
    tuple->elements = malloc(sizeof(FlatPointer) * tuple->size);
    // Insert elements until END_OF_TUPLE is found
    for (size_t i = 0; i < tuple->size; i++)
    {
        // Check if tuple has more elements than arguments passed
        if (current == END_OF_TUPLE)
            CRASH_ON_ERROR("tuple has more elements than arguments passed\n");

        // Check if argument has the correct type
        if (flat_pointer_get_type(current) != tuple->types[i])
            CRASH_ON_ERROR(
                "argument %lu has type %s, but tuple has type %s\n", i, 
                flat_type_to_string(flat_pointer_get_type(current)), 
                flat_type_to_string(tuple->types[i])
                );

        size++;
        // Check if tuple has less elements than arguments passed
        if (size > tuple->size)
            CRASH_ON_ERROR("tuple has less elements than arguments passed\n");
        tuple->elements[i] = current;
        current = va_arg(args, FlatPointer);
    }
    va_end(args);
    tuple->fill = 1;
}

bool _flat_tuple_verify_definition(FlatTuple tuple, 
        FlatType *definition, size_t size){
    if (tuple == NULL) CRASH_ON_ERROR("tuple is not defined\n");
    // Check if size of array is the same as tuple size
    if (tuple->size != size) return false;
    // Check if types are the same
    for (size_t i = 0; i < tuple->size; i++)
        if (tuple->types[i] != definition[i])
            return false;
    return true;
}

//      Initialization functions
//      ------------------------

FlatTuple flat_tuple_define_from_array(FlatType *types, size_t size) {
    // Check if types is NULL
    if (types == NULL) CRASH_ON_ERROR("types array is not defined\n");
    // Allocate memory for tuple
    FlatTuple tuple = malloc(sizeof(struct _FlatTuple));
    tuple->types = malloc(sizeof(FlatType) * size);
    // Copy types to tuple
    for (size_t i = 0; i < size; i++) tuple->types[i] = types[i];
    tuple->size = size;
    tuple->fill = 0;
    return tuple;
}

FlatTuple flat_tuple_create_from_array(FlatPointer *array, size_t size) {
    // Check if array is NULL
    if (array == NULL) CRASH_ON_ERROR("flat pointer array is not defined\n");
    // initialize tuple with 0 elements
    FlatTuple tuple = malloc(sizeof(struct _FlatTuple));
    tuple->elements = array;
    tuple->size = size;
    tuple->fill = 1;
    tuple->types = malloc(sizeof(FlatType) * size);
    // Copy types to tuple
    for (size_t i = 0; i < size; i++)
        if (array[i] == NULL)
            CRASH_ON_ERROR("NULL pointer found at position %lu\n", i);
        else
            tuple->types[i] = flat_pointer_get_type(array[i]);
        
    return tuple;
}

void flat_tuple_fill_from_array(FlatTuple tuple, FlatPointer *array, size_t size) {
    // Check if array or tuple are NULL
    if (array == NULL) CRASH_ON_ERROR("flat pointer array is not defined\n");
    if (tuple == NULL) CRASH_ON_ERROR("tuple is not defined\n");
    // Check if tuple is already filled
    if (tuple->fill)
        CRASH_ON_ERROR("tuple is already filled\n");
    // Check if size of array is the same as tuple size
    if (size != tuple->size)
        CRASH_ON_ERROR("tuple has size %lu, but array has size %lu\n", tuple->size, size);

    for (size_t i = 0; i < size; i++)
    {
        // Check if array has NULL pointers
        if (array[i] == NULL)
            CRASH_ON_ERROR("Error: flat_tuple_fill_from_array: NULL pointer found at position %lu\n", i);
        // Check if types are the same
        if (flat_pointer_get_type(array[i]) != tuple->types[i])
            CRASH_ON_ERROR(
                "argument %lu has type %s, but tuple has type %s\n", i, 
                flat_type_to_string(flat_pointer_get_type(array[i])), 
                flat_type_to_string(tuple->types[i])
                );
    }
    // Fill tuple
    tuple->elements = array;
    tuple->fill = 1;
}

//      Destruction functions
//      ---------------------

void flat_tuple_destroy(FlatTuple tuple) {
    if (tuple == NULL) CRASH_ON_ERROR("tuple is not defined\n");
    // Destroy each flat pointer of the elements of the tuple
    for (size_t i = 0; i < tuple->size; i++)
        flat_pointer_destroy(tuple->elements[i]);

    // Free memory allocated for the tuple
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
    // For each type in the tuple, add it representation to the string
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
    // For each type in the tuple, add it to the final array
    for (size_t i = 0; i < tuple->size; i++)
        types[i] = tuple->types[i];
    return types;
}

FlatPointer * flat_tuple_to_array(FlatTuple tuple){
    if (tuple == NULL) CRASH_ON_ERROR("tuple is not defined\n");
    if (tuple->fill == 0) CRASH_ON_ERROR("tuple is not filled\n");
    // Allocate memory for the array
    FlatPointer *array = malloc(sizeof(FlatPointer) * tuple->size);
    // For each element in the tuple, add it to the final array
    for (size_t i = 0; i < tuple->size; i++)
        array[i] = flat_pointer_clone(tuple->elements[i]);
    return array;
}

FlatPointer flat_tuple_get_element(FlatTuple tuple, size_t index) {
    if (tuple == NULL) CRASH_ON_ERROR("tuple is not defined\n");
    if (tuple->fill == 0) CRASH_ON_ERROR("tuple is not filled\n");
    // Check if index is out of bounds
    if (index >= tuple->size)
        CRASH_ON_ERROR("index %lu out of bounds\n", index);
    // Return element
    return tuple->elements[index];
}

size_t flat_tuple_length(FlatTuple tuple){
    if (tuple == NULL) CRASH_ON_ERROR("tuple is not defined\n");
    return tuple->size;
}

bool flat_tuple_contains(FlatTuple tuple, FlatPointer element) {
    if (tuple == NULL) CRASH_ON_ERROR("tuple is not defined\n");
    if (tuple->fill == 0) CRASH_ON_ERROR("tuple is not filled\n");
    // For each element in the tuple, check if it is equal to the element
    for (size_t i = 0; i < tuple->size; i++)
        if (flat_pointer_equals(tuple->elements[i], element))
            return true;
    return false;
}

size_t flat_tuple_count_elements(FlatTuple tuple, FlatPointer element) {
    if (tuple == NULL) CRASH_ON_ERROR("tuple is not defined\n");
    if (element == NULL) CRASH_ON_ERROR("element is not defined\n");
    if (tuple->fill == 0) CRASH_ON_ERROR("tuple is not filled\n");
    size_t count = 0;
    // For each element in the tuple, check if it is equal to the element
    for (size_t i = 0; i < tuple->size; i++)
        count += flat_pointer_equals(tuple->elements[i], element);
    return count;
}

size_t flat_tuple_index_of_element(FlatTuple tuple, FlatPointer element) {
    if (tuple == NULL) CRASH_ON_ERROR("tuple is not defined\n");
    if (element == NULL) CRASH_ON_ERROR("element is not defined\n");
    if (tuple->fill == 0) CRASH_ON_ERROR("tuple is not filled\n");
    // For each element in the tuple, check if it is equal to the element
    for (size_t i = 0; i < tuple->size; i++)
        if (flat_pointer_equals(tuple->elements[i], element))
            return i;
    return -1;
}

//      FLAT ADT functions
//      ------------------

char * flat_tuple_to_string(FlatTuple tuple) {
    if (!tuple->fill) CRASH_ON_ERROR("tuple has not elements\n");
    // Allocate memory for the string representation of the tuple
    char *str = malloc(sizeof(char) * 2);
    str[0] = '(';
    str[1] = '\0';
    // For each element in the tuple, add it representation to the string
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

bool flat_tuple_equals(FlatTuple tuple1, FlatTuple tuple2){
    if (tuple1->size != tuple2->size) return false;
    if (tuple1->fill != tuple2->fill) return false;
    if (!tuple1->fill || !tuple2->fill) CRASH_ON_ERROR("tuple is not filled\n");
    // For each element in the tuple, check if it is equal to the element
    for (size_t i = 0; i < tuple1->size; i++)
        if (!flat_pointer_equals(tuple1->elements[i], tuple2->elements[i]))
            return false;
    return true;
}

int flat_tuple_hashcode(FlatTuple tuple) {
    if (tuple == NULL) CRASH_ON_ERROR("tuple is not defined\n");
    int hash = 0;
    // Calculate hashcode as the sum of the hashcodes of each element
    for (size_t i = 0; i < tuple->size; i++)
        hash += flat_pointer_hashcode(tuple->elements[i]);
    return hash;
}

FlatTuple flat_tuple_clone(FlatTuple tuple) {
    if (tuple == NULL) CRASH_ON_ERROR("tuple is not defined\n");
    // Allocate memory for the new tuple
    FlatTuple newTuple = malloc(sizeof(struct _FlatTuple));
    // Copy tuple data to new tuple
    newTuple->size = tuple->size;
    newTuple->fill = tuple->fill;
    newTuple->elements = malloc(sizeof(FlatPointer) * newTuple->size);
    newTuple->types = malloc(sizeof(FlatType) * newTuple->size);
    // To copy the elements, clone each element and copy its type
    for (size_t i = 0; i < newTuple->size; i++)
    {
        newTuple->elements[i] = flat_pointer_clone(tuple->elements[i]);
        newTuple->types[i] = tuple->types[i];
    }
    return newTuple;
}

//      Tuple functions
//      ---------------

FlatTuple flat_tuple_slice(FlatTuple tuple, size_t start, size_t end) {
    // Check if tuple is already filled
    if (!tuple->fill) CRASH_ON_ERROR("tuple is not filled\n");
    // Check if start and end are out of bounds
    if (start > end) 
        CRASH_ON_ERROR("start index %lu is greater than end index %lu\n", 
                        start, end);
    if (end > tuple->size) 
        CRASH_ON_ERROR("end index %lu is out of bounds\n", end);

    // Create new tuple
    FlatTuple newTuple = malloc(sizeof(struct _FlatTuple));
    // Calculate new tuple size as the difference between end and start
    newTuple->size = end - start;
    newTuple->fill = 1;
    // Allocate memory for the elements and types of the new tuple
    newTuple->elements = malloc(sizeof(FlatPointer) * newTuple->size);
    newTuple->types = malloc(sizeof(FlatType) * newTuple->size);
    // Copy elements and types from the original tuple
    for (size_t i = 0; i < newTuple->size; i++)
    {
        newTuple->elements[i] = flat_pointer_clone(tuple->elements[start + i]);
        newTuple->types[i] = tuple->types[start + i];
    }
    return newTuple;
}

FlatTuple flat_tuple_concat(FlatTuple tuple1, FlatTuple tuple2) {
    // Check if each tuple is already filled
    if (!tuple1->fill || !tuple2->fill) CRASH_ON_ERROR("tuple is not filled\n");
    // Create new tuple
    FlatTuple newTuple = malloc(sizeof(struct _FlatTuple));
    newTuple->size = tuple1->size + tuple2->size;
    newTuple->fill = 1;
    // Allocate memory for the elements and types of the new tuple
    newTuple->elements = malloc(sizeof(FlatPointer) * newTuple->size);
    newTuple->types = malloc(sizeof(FlatType) * newTuple->size);
    // Copy elements and types from the original tuples
    for (size_t i = 0; i < tuple1->size; i++)
    {
        newTuple->elements[i] = flat_pointer_clone(tuple1->elements[i]);
        newTuple->types[i] = tuple1->types[i];
    }
    for (size_t i = 0; i < tuple2->size; i++)
    {
        newTuple->elements[tuple1->size + i] = flat_pointer_clone(tuple2->elements[i]);
        newTuple->types[tuple1->size + i] = tuple2->types[i];
    }
    return newTuple;
}