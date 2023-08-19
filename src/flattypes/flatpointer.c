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
#include <flatset.h>
#include <color.h>
#include <stdio.h>


struct _flat_pointer {
    FlatType type;
    generic_flat_pointer value;
};

#define DEFINE_MAKE_FUNCTION(TYPE, CTYPE) \
    flat_pointer TYPE##_FLAT_POINTER(CTYPE x) { \
        flat_pointer fp = malloc(sizeof(struct _flat_pointer)); \
        fp->type = TYPE; \
        fp->value = malloc(sizeof(CTYPE)); \
        *(CTYPE *)fp->value = x; \
        return fp; \
    }

#define DEFINE_GET_FUNCTION(TYPE, CTYPE) \
    CTYPE FLAT_POINTER_TO_##TYPE(flat_pointer p) { \
        if (p->type != TYPE) { \
            fprintf(stderr, "Error: Attempted to get value of flat pointer of" \
                    " type " RED "%s" RESET " as type" GREEN " %s" RESET "\n", \
                    flat_type_to_string(p->type), flat_type_to_string(TYPE)); \
            exit(1); \
        } \
        return *(CTYPE *)p->value; \
    }

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
DEFINE_MAKE_FUNCTION(STRING, char *)

flat_pointer SET_FLAT_POINTER(FlatSet x){
    flat_pointer fp = (flat_pointer) malloc(sizeof(struct _flat_pointer));
    fp->type = SET;
    fp->value = x;
    return fp;
}

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
DEFINE_GET_FUNCTION(STRING, char *)


FlatSet FLAT_POINTER_TO_SET(flat_pointer x){
    if (x->type != SET) {
        fprintf(stderr, "Error: Attempted to get value of flat pointer of"
                " type " RED "%s" RESET " as type" GREEN " %s" RESET "\n",
                flat_type_to_string(x->type), flat_type_to_string(SET));
        exit(1);
    }
    return (FlatSet) x->value;
}

flat_pointer flat_pointer_create(FlatType type, generic_flat_pointer value) {
    if (value == NULL) return NULL;
    flat_pointer fp = (flat_pointer) malloc(sizeof(struct _flat_pointer));
    fp->type = type;
    fp->value = value;
    return fp;
}

void flat_pointer_destroy(flat_pointer fp) {
    if (fp == NULL) return;
    switch (fp->type) {
    case SET:
        flat_set_destroy((FlatSet) fp->value);
        break;
    
    default:
        free(fp->value);
        break;
    }
    free(fp);
}

FlatType flat_pointer_get_type(flat_pointer fp) {
    return fp->type;
}

char *flat_pointer_to_string(flat_pointer fp) {
    if (fp == NULL) return strdup("nil ");
    return get_to_string_function(fp->type)(fp->value);
}

flat_pointer flat_pointer_clone(flat_pointer fp) {
    if (fp == NULL) return NULL;
    return flat_pointer_create(fp->type, get_clone_function(fp->type)(fp->value));
}   
