#include "reproc.h"
#include "restor.h"

#include <stdlib.h>

#include <assert.h>
#include <unistd.h>

reproc *new_reproc(remem **memory) {
    reproc *self = (reproc *) calloc(1, sizeof(reproc));

    self->m = memory;
    self->pc = 0;

    reproc_read_ports(self);

    return self;
}

void free_reproc(reproc *self) {
    if (self->psa != NULL) free_restor(self->psa);
    if (self->psb != NULL) free_restor(self->psb);
    if (self->psc != NULL) free_restor(self->psc);

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

void reproc_read_ports(reproc *self) {
    if (access(RCSAE_DEFAULT_PORT_PATH "/psa", F_OK) == 0) {
        self->psa = new_restor(fopen(RCSAE_DEFAULT_PORT_PATH "/psa", "rb"));
    } else if (self->psa != NULL) {
        free_restor(self->psa);
    }

    if (access(RCSAE_DEFAULT_PORT_PATH "/psb", F_OK) == 0) {
        self->psb = new_restor(fopen(RCSAE_DEFAULT_PORT_PATH "/psb", "rb"));
    } else if (self->psb != NULL) {
        free_restor(self->psb);
    }

    if (access(RCSAE_DEFAULT_PORT_PATH "/psc", F_OK) == 0) {
        self->psc = new_restor(fopen(RCSAE_DEFAULT_PORT_PATH "/psc", "rb"));
    } else if (self->psc != NULL) {
        free_restor(self->psc);
    }
}
