#include "../instructions.h"

#define INS_PLA_IP 0x68

void PLA(Byte instruction, p6502* proc, int* cycles) {
    switch (instruction) {
        case INS_PLA_IP: {
            proc->cpu->SP++;
            Byte data = pullStack(proc->memory, proc->cpu, cycles);
            --*cycles;
            proc->cpu->AC = data;
            proc->processor->ZF = (proc->cpu->AC == 0);
            proc->processor->NF = (proc->cpu->AC & 0b10000000) > 0;
            break;
        }
    }
}