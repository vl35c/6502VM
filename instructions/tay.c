#include "instructions.h"

#define INS_TAY_IP 0xA8

void TAY(Byte instruction, p6502* proc, int* cycles) {
    switch(instruction) {
        case INS_TAY_IP: {
            copyByte(proc->cpu->AC, &proc->cpu->IY, "cpu.IY");
            proc->processor->ZF = (proc->cpu->IY == 0);
            proc->processor->NF = (proc->cpu->IY & 0b10000000) > 0;
            --*cycles;
            break;
        }
    }
}