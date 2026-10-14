#include "../instructions.h"

#define INS_BIT_ZP 0x24
#define INS_BIT_AB 0x2C

static void _bit(Byte data, p6502* proc) {
    Byte result = and(proc->cpu->AC, data);
    proc->processor->ZF = result == 0;
    proc->processor->OF = result >> 5;
    proc->processor->NF = result >> 6;
}

void BIT(Byte instruction, p6502* proc, int* cycles) {
    Byte data;
    switch (instruction) {
        case INS_BIT_ZP: {
            data = addr_zero_page(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_BIT_AB: {
            data = addr_absolute(proc->memory, proc->cpu, cycles);
            break;
        }
    }

    if (data) { _bit(data, proc); }
}