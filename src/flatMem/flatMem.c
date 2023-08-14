#include <flatMem.h>
#include <set.h>
#include <flatPointerPrivate.h>

void flat_free(flat_pointer p) {
    if (p == NULL) return;
    switch (p->type)
    {
    case SET:
        setDestroy((Set)(p->value));
        break;
    
    default:
        free(p->value);
        break;
    }
    free(p);
}