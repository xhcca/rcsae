#include "remem.h"
#include "reproc.h"
#include "restor.h"

#include <stdio.h>
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
    self->b0 = REPROC_STATE_ON;

    if ((self->psa != NULL) && (restor_size(self->psa) == RCSAE_FP_SIZE)) {
        for (size_t i = 0; i < RCSAE_FP_SIZE; ++i) {
            remem_write(*self->m, i, restor_read(self->psa, i));
        }
    }

    while (self->b0 != REPROC_STATE_OFF) {
        switch (remem_read(*self->m, self->pc++)) {
            case REPROC_CODE_HALT:
                self->b0 = REPROC_STATE_OFF;

                break;
            
            case REPROC_CODE_DEBUG:
                puts("\033[1minfo:\033[0m executed the operation code \033[4m"
                    "DEBUG\033[0m");

                break;
            
            case REPROC_CODE_PASS:
                break;
            
            default:
                self->b0 = REPROC_STATE_UCE;

                break;
        }

        if (self->pc + 1 >= remem_size(*self->m)) {
            self->pc = 0;
        }
    }
}

void reproc_stop(reproc *self) {
    assert(self->b0 == REPROC_STATE_ON);

    self->b0 = REPROC_STATE_OFF;
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
