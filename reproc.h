#ifndef REPROC_H
#define REPROC_H

#define RCSAE_DEFAULT_PORT_PATH "/tmp/rcsae-ports"

#include "remem.h"
#include "restor.h"

#include <stdint.h>

enum {
    REPROC_ON = 0x00,
    REPROC_OFF = 0x01,
};

typedef struct {
    remem **m;
    restor *psa;
    restor *psb;
    restor *psc;
    restor *pioa;
    restor *piob;
    restor *pioc;

    uint64_t pc;

    uint8_t b0;
    uint8_t b1;
    uint8_t b2;
    uint8_t b3;
    uint8_t b4;
    uint8_t b5;
    uint8_t b6;
    uint8_t b7;
    uint8_t b8;
    uint8_t b9;
    uint8_t b10;
    uint8_t b11;
    uint8_t b12;
    uint8_t b13;
    uint8_t b14;
    uint8_t b15;

    uint16_t sr0;
    uint16_t sr1;
    uint16_t sr2;
    uint16_t sr3;
    uint16_t sr4;
    uint16_t sr5;
    uint16_t sr6;
    uint16_t sr7;
    uint16_t sr8;
    uint16_t sr9;
    uint16_t sr10;
    uint16_t sr11;
    uint16_t sr12;
    uint16_t sr13;
    uint16_t sr14;
    uint16_t sr15;

    uint32_t r0;
    uint32_t r1;
    uint32_t r2;
    uint32_t r3;
    uint32_t r4;
    uint32_t r5;
    uint32_t r6;
    uint32_t r7;
    uint32_t r8;
    uint32_t r9;
    uint32_t r10;
    uint32_t r11;
    uint32_t r12;
    uint32_t r13;
    uint32_t r14;
    uint32_t r15;

    uint64_t lr0;
    uint64_t lr1;
    uint64_t lr2;
    uint64_t lr3;
    uint64_t lr4;
    uint64_t lr5;
    uint64_t lr6;
    uint64_t lr7;
    uint64_t lr8;
    uint64_t lr9;
    uint64_t lr10;
    uint64_t lr11;
    uint64_t lr12;
    uint64_t lr13;
    uint64_t lr14;
    uint64_t lr15;
} reproc;

reproc *new_reproc(remem **);
void free_reproc(reproc *);

void reproc_start(reproc *);
void reproc_stop(reproc *);

#endif
