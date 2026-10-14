#include "../instructions.h"

static void _and(Byte data, p6502* proc) {
    Byte sum = and(proc->cpu->AC, data);
    proc->cpu->AC = sum;
    proc->processor->ZF = (proc->cpu->AC == 0);
    proc->processor->NF = (proc->cpu->AC & 0b10000000) > 0;
}

void AND(Byte instruction, p6502* proc, int* cycles) {
    Byte data;
    switch (instruction) {
        case INS_AND_IM: {
            data = fetch(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_AND_ZP: {
            data = addr_zero_page(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_AND_ZX: {
            data = addr_zero_page_x(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_AND_AB: {
            data = addr_absolute(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_AND_AX: {
            data = addr_absolute_x(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_AND_AY: {
            data = addr_absolute_y(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_AND_IX: {
            data = addr_indirect_x(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_AND_IY: {
            data = addr_indirect_y(proc->memory, proc->cpu, cycles);
            break;
        }
    }

    if (data) { _and(data, proc); }
}