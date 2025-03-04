#include "../instructions.h"

#define INS_TYA_IP 0x98

void TYA(Byte instruction, p6502* proc, int* cycles) {
    switch(instruction) {
        case INS_TYA_IP: {
            copyByte(proc->cpu->IY, &proc->cpu->AC, "cpu.AC");
            proc->processor->ZF = (proc->cpu->AC == 0);
            proc->processor->NF = (proc->cpu->AC & 0b10000000) > 0;
            --*cycles;
            break;
        }
    }
}