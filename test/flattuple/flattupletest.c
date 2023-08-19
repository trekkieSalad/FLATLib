#include <flatlib.h>
#include <stdarg.h>

#include <stdlib.h>
#include <stdio.h>


int main(){
    FlatTuple tuple = flat_tuple_create(
        FLAT_POINTER_CREATOR(1), 
        FLAT_POINTER_CREATOR("hola"), 
        FLAT_POINTER_CREATOR("hola")
        );
    char *str = flat_tuple_to_string(tuple);
    char *def = flat_tuple_definition_to_string(tuple);
    printf("%s\n", str);
    printf("%s\n", def);
    free(str);
    free(def);
    flat_tuple_destroy(tuple);

    FlatType types[3] = {INT, STRING, INT};
    tuple = flat_tuple_define_from_array(types, 3);
    flat_tuple_filler(tuple, FLAT_POINTER_CREATOR(1), FLAT_POINTER_CREATOR("hola"), FLAT_POINTER_CREATOR(1));
    str = flat_tuple_to_string(tuple);
    printf("%s\n", str);
    def = flat_tuple_definition_to_string(tuple);
    printf("%s\n", def);

    free(str);
    free(def);
    flat_tuple_destroy(tuple);


}