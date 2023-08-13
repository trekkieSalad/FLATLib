#ifndef DATA_STRUCT_FUNC_H
#define DATA_STRUCT_FUNC_H

#include <types.h>
#include <stdbool.h>
#include <stddef.h>

typedef unsigned int    (*hashFunction)     (const generic_flat_pointer data, 
                                             size_t                     size);
typedef bool            (*equalsFunction)   (const generic_flat_pointer setA, 
                                             const generic_flat_pointer setB);
typedef char *          (*toStringFunction) (const generic_flat_pointer data);
typedef void *          (*cloneFunction)    (const generic_flat_pointer data);
typedef void            (*freeFunction)     (generic_flat_pointer       data);


hashFunction        getHashFunction         (Type);
equalsFunction      getEqualsFunction       (Type);
toStringFunction    getToStringFunction     (Type);
cloneFunction       getCloneFunction        (Type);
freeFunction        getFreeFunction         (Type);
size_t              getTypeSize             (Type);

#endif // DATA_STRUCT_FUNC_H