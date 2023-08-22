/* flatpointer.c - Implementation of flat pointer functions.
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
#define __STDC_WANT_LIB_EXT2__ 1
#include <flatpointer.h>
#include <flattypes_priv.h>
#include <flatcode.h>
#include <flatset.h>
#include <flattuple.h>
#include <color.h>

//==================================================================//
//              ADT definitions                                     //
//==================================================================//

/**
 * _FlatPointer:
 * 
 * A flat pointer is a data structure that contains a typed value. It is used
 * to store values of different types and let the user retrieve them as the
 * original type. It is used by the FLATlib data structures.
 */

struct _FlatPointer {
    FlatType type;
    generic_flat_pointer value;
};

//==================================================================//
//              MACRO definitions                                   //
//==================================================================//

/*
 * These macros are used to define the make and get functions for each type.
 */

#define DEFINE_MAKE_FUNCTION(TYPE, CTYPE)                                   \
    FlatPointer TYPE##_FLAT_POINTER(CTYPE x) {                              \
        FlatPointer fp = malloc(sizeof(struct _FlatPointer));               \
        fp->type = TYPE;                                                    \
        fp->value = malloc(sizeof(CTYPE));                                  \
        *(CTYPE *)fp->value = x;                                            \
        return fp;                                                          \
    }

#define DEFINE_GET_FUNCTION(TYPE, CTYPE)                                    \
    CTYPE FLAT_POINTER_TO_##TYPE(FlatPointer p) {                           \
        if (p->type != TYPE)                                                \
            CRASH_ON_ERROR("Attempted to get value of flat pointer of"      \
                " type " RED "%s" RESET " as type" GREEN " %s" RESET "\n",  \
                flat_type_to_string(p->type), flat_type_to_string(TYPE));   \
        return *(CTYPE *)p->value;                                          \
    }

//==================================================================//
//              Public functions for internal use                   //
//==================================================================//

FlatPointer __INVALID_TYPE_ERROR(){
    CRASH_ON_ERROR("Attempted to create a flat pointer from an invalid type\n");
    return NULL;
}

//      Flat pointer creation functions
//      -------------------------------

DEFINE_MAKE_FUNCTION(CHAR, char)
DEFINE_MAKE_FUNCTION(UCHAR, unsigned char)
DEFINE_MAKE_FUNCTION(SHORT, short)
DEFINE_MAKE_FUNCTION(USHORT, unsigned short)
DEFINE_MAKE_FUNCTION(INT, int)
DEFINE_MAKE_FUNCTION(UINT, unsigned int)
DEFINE_MAKE_FUNCTION(LONG, long)
DEFINE_MAKE_FUNCTION(ULONG, unsigned long)
DEFINE_MAKE_FUNCTION(LONG_LONG, long long)
DEFINE_MAKE_FUNCTION(ULONG_LONG, unsigned long long)
DEFINE_MAKE_FUNCTION(FLOAT, float)
DEFINE_MAKE_FUNCTION(DOUBLE, double)

FlatPointer STRING_FLAT_POINTER(char *x) {
    FlatPointer fp = malloc(sizeof(struct _FlatPointer));
    fp->type = STRING;
    fp->value = strdup(x);
    return fp;
}

FlatPointer SET_FLAT_POINTER(FlatSet x){
    FlatPointer fp = (FlatPointer) malloc(sizeof(struct _FlatPointer));
    fp->type = SET;
    fp->value = x;
    return fp;
}

FlatPointer TUPLE_FLAT_POINTER(FlatTuple x){
    FlatPointer fp = (FlatPointer) malloc(sizeof(struct _FlatPointer));
    fp->type = TUPLE;
    fp->value = x;
    return fp;
}

//      Flat pointer get functions
//      --------------------------

DEFINE_GET_FUNCTION(CHAR, char)
DEFINE_GET_FUNCTION(UCHAR, unsigned char)
DEFINE_GET_FUNCTION(SHORT, short)
DEFINE_GET_FUNCTION(USHORT, unsigned short)
DEFINE_GET_FUNCTION(INT, int)
DEFINE_GET_FUNCTION(UINT, unsigned int)
DEFINE_GET_FUNCTION(LONG, long)
DEFINE_GET_FUNCTION(ULONG, unsigned long)
DEFINE_GET_FUNCTION(LONG_LONG, long long)
DEFINE_GET_FUNCTION(ULONG_LONG, unsigned long long)
DEFINE_GET_FUNCTION(FLOAT, float)
DEFINE_GET_FUNCTION(DOUBLE, double)

char * FLAT_POINTER_TO_STRING(FlatPointer x){
    if (x->type != STRING)
        CRASH_ON_ERROR("Attempted to get value of flat pointer of"
                " type " RED "%s" RESET " as type" GREEN " %s" RESET "\n",
                flat_type_to_string(x->type), flat_type_to_string(STRING));
    return (char *) x->value;
}

FlatSet FLAT_POINTER_TO_SET(FlatPointer x){
    if (x->type != SET) {
        fprintf(stderr, "Error: Attempted to get value of flat pointer of"
                " type " RED "%s" RESET " as type" GREEN " %s" RESET "\n",
                flat_type_to_string(x->type), flat_type_to_string(SET));
        exit(1);
    }
    return (FlatSet) x->value;
}

FlatTuple FLAT_POINTER_TO_TUPLE(FlatPointer x){
    if (x->type != TUPLE) {
        fprintf(stderr, "Error: Attempted to get value of flat pointer of"
                " type " RED "%s" RESET " as type" GREEN " %s" RESET "\n",
                flat_type_to_string(x->type), flat_type_to_string(TUPLE));
        exit(1);
    }
    return (FlatTuple) x->value;
}

//==================================================================//
//              Public functions                                    //
//==================================================================//

//      Initialization functions
//      ------------------------

FlatPointer flat_pointer_create(FlatType type, generic_flat_pointer value) {
    if (value == NULL) return NULL;
    FlatPointer fp = (FlatPointer) malloc(sizeof(struct _FlatPointer));
    fp->type = type;
    fp->value = value;
    return fp;
}
           
//      Destruction functions
//      ---------------------

void flat_pointer_destroy(FlatPointer fp) {
    if (fp == NULL) return;
    // Free memory depending on the type. For primitive types, just free the
    // memory allocated for the value. For flat data structures, call the
    // corresponding destroy function.
    switch (fp->type) {
    case SET:
        flat_set_destroy((FlatSet) fp->value);
        break;
    case TUPLE:
        flat_tuple_destroy((FlatTuple) fp->value);
        break;
    
    default:
        free(fp->value);
        break;
    }
    free(fp);
}

FlatType flat_pointer_get_type(FlatPointer fp) {
    return fp->type;
}

//      FLAT Type functions
//      -------------------

char *flat_pointer_to_string(FlatPointer fp) {
    if (fp == NULL) return strdup("nil ");
    return get_to_string_function(fp->type)(fp->value);
}

FlatPointer flat_pointer_clone(FlatPointer fp) {
    if (fp == NULL) return NULL;
    return flat_pointer_create(fp->type, get_clone_function(fp->type)(fp->value));
}   

bool flat_pointer_equals(FlatPointer fp1, FlatPointer fp2) {
    if (fp1 == NULL && fp2 == NULL) return true;
    if (fp1 == NULL || fp2 == NULL) return false;
    if (fp1->type != fp2->type) return false;
    return get_equals_function(fp1->type)(fp1->value, fp2->value);
}

int flat_pointer_hashcode(FlatPointer fp) {
    if (fp == NULL) return 0;
    return get_hash_function(fp->type)(fp->value);
}