#include "instructions.h"

#define INS_TXA_IP 0x8A

void TXA(Byte instruction, p6502* proc, int* cycles) {
    switch(instruction) {
        case INS_TXA_IP: {
            copyByte(proc->cpu->IX, &proc->cpu->AC, "cpu.AC");
            proc->processor->ZF = (proc->cpu->AC == 0);
            proc->processor->NF = (proc->cpu->AC & 0b10000000) > 0;
            --*cycles;
            break;
        }
    }
}