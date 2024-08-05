#ifndef RESTOR_H
#define RESTOR_H

#include <stdio.h>
#include <stdint.h>

typedef struct {
    FILE *file;
} restor;

restor *new_restor(FILE *);
void free_restor(restor *);

size_t restor_size(restor *);
uint8_t restor_read(restor *, uintptr_t);
void restor_write(restor *, uintptr_t, uint8_t);

#endif
