#include "../instructions.h"

static void _eor(Byte data, p6502* proc) {
    Byte result = eor(proc->cpu->AC, data);
    proc->cpu->AC = result;
    proc->processor->ZF = (proc->cpu->AC == 0);
    proc->processor->NF = (proc->cpu->AC & 0b10000000) > 0;
}

void EOR(Byte instruction, p6502* proc, int* cycles) {
    Byte data;
    switch (instruction) {
        case INS_EOR_IM: {
            data = fetch(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_EOR_ZP: {
            data = addr_zero_page(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_EOR_ZX: {
            data = addr_zero_page_x(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_EOR_AB: {
            data = addr_absolute(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_EOR_AX: {
            data = addr_absolute_x(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_EOR_AY: {
            data = addr_absolute_y(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_EOR_IX: {
            data = addr_indirect_x(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_EOR_IY: {
            data = addr_indirect_y(proc->memory, proc->cpu, cycles);
            break;
        }
    }

    if (data) { _eor(data, proc); }
}