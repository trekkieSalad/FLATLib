#include <flatPointer.h>
#include <set.h>
#include <color.h>
#include <stdio.h>

struct _flat_pointer {
    Type type;
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
                    typeToString(p->type), typeToString(TYPE)); \
            exit(1); \
        } \
        return *(CTYPE *)p->value; \
    }

const char *typeToString(Type type);

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

void flat_free(flat_pointer p) {
    if (p == NULL) return;
    free(p->value);
    free(p);
}

const char *typeToString(Type type) {
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


flat_pointer SET_FLAT_POINTER(Set x){
    flat_pointer fp = (flat_pointer) malloc(sizeof(struct _flat_pointer));
    fp->type = SET;
    fp->value = x;
    return fp;
}

Set FLAT_POINTER_TO_SET(flat_pointer x){
    if (x->type != SET) {
        fprintf(stderr, "Error: Attempted to get value of flat pointer of"
                " type " RED "%s" RESET " as type" GREEN " %s" RESET "\n",
                typeToString(x->type), typeToString(SET));
        exit(1);
    }
    return (Set) x->value;
}