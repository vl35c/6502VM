#include <stdlib.h>

#include "architecture.h"

static void initCPU(p6502* proc) {
    CPU* cpu = (CPU*)malloc(sizeof(CPU));
    proc->cpu = cpu;

    __uint16_t pcValue = 0x1234;
    __uint8_t spValue = 0x00;
    __uint8_t acValue = 0x00;
    __uint8_t ixValue = 0x00;
    __uint8_t iyValue = 0x00;

    proc->cpu->PC = 0x1234;
    proc->cpu->SP = 0x00;
    proc->cpu->AC = 0x00;
    proc->cpu->IX = 0x00;
    proc->cpu->IY = 0x00;
}

static void initProcessor(p6502* proc) {
    Processor p;
    proc->processor = &p;

    proc->processor->CF = 1;
    proc->processor->ZF = 1;
    proc->processor->ID = 1;
    proc->processor->DM = 1;
    proc->processor->BC = 1;
    proc->processor->OF = 1;
    proc->processor->NF = 1;
}

void init6502(p6502* proc) {
    initCPU(proc);
    initProcessor(proc);
}

static void freeCPU(p6502* proc) {
    free(proc->cpu);
}

void free6502(p6502* proc) {
    freeCPU(proc);
}