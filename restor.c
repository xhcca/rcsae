#include "restor.h"

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

restor *new_restor(FILE *file) {
    restor *self = (restor *) calloc(1, sizeof(restor));

    self->file = file;

    return self;
}

void free_restor(restor *self) {
    fclose(self->file);
    free(self);
}

void free_restor_only(restor *self) {
    free(self);
}

size_t restor_size(restor *self) {
    size_t op = ftell(self->file);

    fseek(self->file, 0, SEEK_END);

    size_t fs = ftell(self->file);

    fseek(self->file, op, SEEK_SET);

    return fs;
}

uint8_t restor_read(restor *self, size_t addr) {
    if (addr >= restor_size(self)) {
        return restor_read(self, addr - restor_size(self));
    } else {
        fseek(self->file, addr, SEEK_SET);

        uint8_t r;

        fread(&r, sizeof(uint8_t), 1, self->file);

        return r;
    }
}

void restor_write(restor *self, size_t addr, uint8_t byte) {
    if (addr >= restor_size(self)) {
        restor_write(self, addr - restor_size(self), byte);
    } else {
        fseek(self->file, addr, SEEK_SET);
        fwrite(&byte, sizeof(uint8_t), 1, self->file);
    }
}
