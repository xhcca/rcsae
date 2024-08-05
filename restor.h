#ifndef RESTOR_H
#define RESTOR_H

#include <stdio.h>
#include <stdint.h>

typedef struct {
    FILE *file;
} restor;

restor *new_restor(FILE *);
void free_restor(restor *);
void free_restor_only(restor *);

size_t restor_size(restor *);
uint8_t restor_read(restor *, size_t);
void restor_write(restor *, size_t, uint8_t);

#endif
