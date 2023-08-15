#ifndef DATA_STRUCT_FUNC_H
#define DATA_STRUCT_FUNC_H

#include <flattypes.h>
#include <stdbool.h>
#include <stddef.h>

typedef unsigned int            (*HashFunction)     (const generic_flat_pointer data, 
                                                     size_t                     size);
typedef bool                    (*EqualsFunction)   (const generic_flat_pointer setA, 
                                                     const generic_flat_pointer setB);
typedef char *                  (*ToStringFunction) (const generic_flat_pointer data);
typedef generic_flat_pointer    (*CloneFunction)    (const generic_flat_pointer data);
typedef void                    (*FreeFunction)     (generic_flat_pointer       data);


HashFunction        get_hash_function       (FlatType);
EqualsFunction      get_equals_function     (FlatType);
ToStringFunction    get_to_string_function  (FlatType);
CloneFunction       get_clone_function      (FlatType);
FreeFunction        get_free_function       (FlatType);
size_t              get_type_size           (FlatType);

#endif // DATA_STRUCT_FUNC_H