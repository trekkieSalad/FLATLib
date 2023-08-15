#include <flatpointer.h>
#include <flatpointerprivate.h>
#include <flatset.h>
#include <color.h>
#include <stdio.h>

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

const char *flat_type_to_string(FlatType type);

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

const char *flat_type_to_string(FlatType type) {
    static const char *typeStrings[] = {
        "char", "unsigned char", "short", "unsigned short", "int",
        "unsigned int", "long", "unsigned long", "long long", "unsigned long long",
        "float", "double", "char *", "Set", "User Defined Type", "Unknown Type"
    };

    if (type >= 0 && type < _TYPE_COUNT) {
        return typeStrings[type];
    }
    return typeStrings[_TYPE_COUNT]; // Unknown Type
}

/*flat_pointer flat_pointer_create(Type type, generic_flat_pointer value) {
    flat_pointer fp = (flat_pointer) malloc(sizeof(struct _flat_pointer));
    fp->type = type;
    fp->value = value;
    return fp;
}

void setValue(flat_pointer fp, generic_flat_pointer value) {
    fp->value = value;
}

void setType(flat_pointer fp, Type type) {
    fp->type = type;
}*/


flat_pointer SET_FLAT_POINTER(FlatSet x){
    flat_pointer fp = (flat_pointer) malloc(sizeof(struct _flat_pointer));
    fp->type = SET;
    fp->value = x;
    return fp;
}

FlatSet FLAT_POINTER_TO_SET(flat_pointer x){
    if (x->type != SET) {
        fprintf(stderr, "Error: Attempted to get value of flat pointer of"
                " type " RED "%s" RESET " as type" GREEN " %s" RESET "\n",
                flat_type_to_string(x->type), flat_type_to_string(SET));
        exit(1);
    }
    return (FlatSet) x->value;
}