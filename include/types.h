#ifndef SET_TYPES_H
#define SET_TYPES_H

typedef enum {
    CHAR,
    UCHAR,
    SHORT,
    USHORT,
    INT,
    UINT,
    LONG,
    ULONG,
    LONG_LONG,
    ULONG_LONG,
    FLOAT,
    DOUBLE,
    STRING,
    SET,
    USER_DEFINED,
    _TYPE_COUNT,
}Type;

typedef     void *              generic_flat_pointer;
typedef     char                flatchar;
typedef     unsigned char       flatuchar;
typedef     short               flatshort;
typedef     unsigned short      flatushort;
typedef     int                 flatint;
typedef     unsigned int        flatuint;
typedef     long                flatlong;
typedef     unsigned long       flatulong;
typedef     long long           flatlonglong;
typedef     unsigned long long  flatulonglong;
typedef     float               flatfloat;
typedef     double              flatdouble;
typedef     char *              flatstring;

#endif // TYPES_H