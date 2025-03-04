#include "../instructions.h"

#define INS_TAX_IP 0xAA

void TAX(Byte instruction, p6502* proc, int* cycles) {
    switch(instruction) {
        case INS_TAX_IP: {
            copyByte(proc->cpu->AC, &proc->cpu->IX, "cpu.IX");
            proc->processor->ZF = (proc->cpu->IX == 0);
            proc->processor->NF = (proc->cpu->IX & 0b10000000) > 0;
            --*cycles;
            break;
        }
    }
}