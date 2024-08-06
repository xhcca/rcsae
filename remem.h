#ifndef REMEM_H
#define REMEM_H

#define RCSAE_MINIMUM_MEMORY_SIZE 1024lu

#include <stddef.h>
#include <stdint.h>

typedef struct {
    size_t size;
    uint8_t *data;
} remem;

remem *new_remem(size_t);
void free_remem(remem *);

size_t remem_size(remem *);
uint8_t remem_read(remem *, size_t);
void remem_write(remem *, size_t, uint8_t);

#endif
