#include <stdlib.h>

#include "architecture.h"

static void initCPU(p6502* proc) {
    CPU* cpu = (CPU*)malloc(sizeof(CPU));
    proc->cpu = cpu;

    __uint16_t pcValue = 0x1234;
    Byte spValue = 0x00;
    Byte acValue = 0x00;
    Byte ixValue = 0x00;
    Byte iyValue = 0x00;

    proc->cpu->PC = 0xFFFA;
    proc->cpu->SP = 0x00;
    proc->cpu->AC = 0x00;
    proc->cpu->IX = 0x00;
    proc->cpu->IY = 0x00;
}

static void initProcessor(p6502* proc) {
    Processor* p = (Processor*)malloc(sizeof(Processor));
    proc->processor = p;

    proc->processor->CF = 0;
    proc->processor->ZF = 0;
    proc->processor->ID = 0;
    proc->processor->DM = 0;
    proc->processor->BC = 0;
    proc->processor->OF = 0;
    proc->processor->NF = 0;
}

static void initMemory(p6502* proc) {
    Memory* memory = (Memory*)malloc(sizeof(Memory));
    proc->memory = memory;

    for (int i = 0; i < MAX_MEM; i++) {
        memory->data[i] = 0x00;
    }

    memory->data[0xFFFA] = 0xA9;
    memory->data[0xFFFB] = 0x00;
}

void init6502(p6502* proc) {
    initCPU(proc);
    initProcessor(proc);
    initMemory(proc);
}

static void freeCPU(p6502* proc) {
    free(proc->cpu);
}

static void freeProcessor(p6502* proc) {
    free(proc->processor);
}

static void freeMemory(p6502* proc) {
    free(proc->memory);
}

void free6502(p6502* proc) {
    freeCPU(proc);
    freeProcessor(proc);
    freeMemory(proc);
}