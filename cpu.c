#include <stdio.h>

#include "cpu.h"

static Byte fetch(Memory* memory, CPU* cpu, int* cycles) {
    Byte byte = memory->data[cpu->PC];
    cpu->PC++;
    --*cycles;

    return byte;
}

#define INS_LDA_IM 0xA9

void execute(p6502* proc, int cycles) {
    while (cycles > 0) {
        Byte instruction = fetch(proc->memory, proc->cpu, &cycles);

        switch (instruction) {
            case INS_LDA_IM: {
                Byte data = fetch(proc->memory, proc->cpu, &cycles);
                proc->cpu->AC = data;
                proc->processor->ZF = (proc->cpu->AC == 0);
                proc->processor->NF = (proc->cpu->AC & 0b10000000) > 0;
                break;
            }
        }
    }
}