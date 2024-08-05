#include "reproc.h"

#include <stdlib.h>

#include <assert.h>

void _reproc_advance(reproc *); 

reproc *new_reproc(remem **memory) {
    reproc *self = (reproc *) calloc(1, sizeof(reproc));

    self->m = memory;

    self->pc = 0;

    return self;
}

void free_reproc(reproc *self) {
    free(self);
}

void reproc_start(reproc *self) {
    self->b0 = REPROC_ON;

    while (self->b0 == REPROC_ON) {
        
    } 
}

void reproc_stop(reproc *self) {
    assert(self->b0 == REPROC_ON);

    self->b0 = REPROC_OFF;
}
