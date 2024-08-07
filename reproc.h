#ifndef REPROC_H
#define REPROC_H

#define RCSAE_FP_SIZE 64lu
#define RCSAE_DEFAULT_PORT_PATH "/tmp/rcsae-ports"

#include "remem.h"
#include "restor.h"

#include <stdint.h>

typedef enum {
    REPROC_STATE_ON = 0x00,
    REPROC_STATE_OFF = 0x01,
    REPROC_STATE_UCE = 0x02,    // Stands for "unknown code error."
} reproc_state_t;

typedef enum {
    REPROC_CODE_PASS = 0x00,
    REPROC_CODE_DEBUG = 0x01,   // This is obviously non-existent in the actual
                                // architecture.
    REPROC_CODE_HALT = 0x02,
} reproc_code_t;

typedef enum {
    REPROC_REGID_PC = 0,
    REPROC_REGID_B0 = 1,
    REPROC_REGID_B1 = 2,
    REPROC_REGID_B2 = 3,
    REPROC_REGID_B3 = 4,
    REPROC_REGID_B4 = 5,
    REPROC_REGID_B5 = 6,
    REPROC_REGID_B6 = 7,
    REPROC_REGID_B7 = 8,
    REPROC_REGID_B8 = 9,
    REPROC_REGID_B9 = 10,
    REPROC_REGID_B10 = 11,
    REPROC_REGID_B11 = 12,
    REPROC_REGID_B12 = 13,
    REPROC_REGID_B13 = 14,
    REPROC_REGID_B14 = 15,
    REPROC_REGID_B15 = 16,
    REPROC_REGID_SR0 = 17,
    REPROC_REGID_SR1 = 18,
    REPROC_REGID_SR2 = 19,
    REPROC_REGID_SR3 = 20,
    REPROC_REGID_SR4 = 21,
    REPROC_REGID_SR5 = 22,
    REPROC_REGID_SR6 = 23,
    REPROC_REGID_SR7 = 24,
    REPROC_REGID_SR8 = 25,
    REPROC_REGID_SR9 = 26,
    REPROC_REGID_SR10 = 27,
    REPROC_REGID_SR11 = 28,
    REPROC_REGID_SR12 = 29,
    REPROC_REGID_SR13 = 30,
    REPROC_REGID_SR14 = 31,
    REPROC_REGID_SR15 = 32,
    REPROC_REGID_R0 = 33,
    REPROC_REGID_R1 = 34,
    REPROC_REGID_R2 = 35,
    REPROC_REGID_R3 = 36,
    REPROC_REGID_R4 = 37,
    REPROC_REGID_R5 = 38,
    REPROC_REGID_R6 = 39,
    REPROC_REGID_R7 = 40,
    REPROC_REGID_R8 = 41,
    REPROC_REGID_R9 = 42,
    REPROC_REGID_R10 = 43,
    REPROC_REGID_R11 = 44,
    REPROC_REGID_R12 = 45,
    REPROC_REGID_R13 = 46,
    REPROC_REGID_R14 = 47,
    REPROC_REGID_R15 = 48,
    REPROC_REGID_LR0 = 49,
    REPROC_REGID_LR1 = 50,
    REPROC_REGID_LR2 = 51,
    REPROC_REGID_LR3 = 52,
    REPROC_REGID_LR4 = 53,
    REPROC_REGID_LR5 = 54,
    REPROC_REGID_LR6 = 55,
    REPROC_REGID_LR7 = 56,
    REPROC_REGID_LR8 = 57,
    REPROC_REGID_LR9 = 58,
    REPROC_REGID_LR10 = 59,
    REPROC_REGID_LR11 = 60,
    REPROC_REGID_LR12 = 61,
    REPROC_REGID_LR13 = 62,
    REPROC_REGID_LR14 = 63,
    REPROC_REGID_LR15 = 64,
} reproc_regid_t;

typedef struct {
    remem **m;
    restor *psa;
    restor *psb;
    restor *psc;

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
