#include <flatmem.h>
#include <flatset.h>
#include <flatpointerprivate.h>

void flat_free(flat_pointer p) {
    if (p == NULL) return;
    switch (p->type)
    {
    case SET:
        flat_set_destroy((FlatSet)(p->value));
        break;
    
    default:
        free(p->value);
        break;
    }
    free(p);
}