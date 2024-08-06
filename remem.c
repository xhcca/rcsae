#include "remem.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include <assert.h>

remem *new_remem(size_t size) {
    assert(size >= RCSAE_MINIMUM_MEMORY_SIZE);

    remem *self = (remem *) calloc(1, sizeof(remem));

    self->size = size;
    self->data = (uint8_t *) calloc(self->size, sizeof(uint8_t));

    return self;
}

void free_remem(remem *self) {
    free(self->data);
    free(self);
}

size_t remem_size(remem *self) {
    return self->size;
}

uint8_t remem_read(remem *self, size_t addr) {
    if (addr >= self->size) {
        return remem_read(self, addr - self->size);
    } else {
        return self->data[addr];
    }
}

void remem_write(remem *self, size_t addr, uint8_t byte) {
    if (addr >= self->size) {
        remem_write(self, addr - self->size, byte);
    } else {
        self->data[addr] = byte;
    }
}
