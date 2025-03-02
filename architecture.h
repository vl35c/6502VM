#ifndef architecture_h
#define architecture_h

#include <stdint.h>

#include "common.h"

#define MAX_MEM 1024 * 64

typedef struct {
    uint8_t CF : 1;   // carry flag
    uint8_t ZF : 1;   // zero flag
    uint8_t ID : 1;   // interrupt disable
    uint8_t DM : 1;   // decimal mode
    uint8_t BC : 1;   // break command
    uint8_t OF : 1;   // overflow flag
    uint8_t NF : 1;   // negative flag
} Processor;

typedef struct {
    uint16_t PC;      // program counter
    Byte SP;            // stack pointer
    Byte AC;            // accumulator
    Byte IX;            // index register x
    Byte IY;            // index register y
} CPU;

typedef struct {
    Byte data[MAX_MEM];
} Memory;

typedef struct {
    Processor* processor;
    CPU* cpu;
    Memory* memory;
} p6502;

void init6502(p6502* proc);
void free6502(p6502* proc);

#endif