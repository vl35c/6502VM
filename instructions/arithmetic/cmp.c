#include "../instructions.h"

static void _cmp(Byte data, p6502* proc) {
    Byte ac = proc->cpu->AC;
    Byte result = (Byte)(ac - data);
    proc->processor->ZF = ac == data;
    proc->processor->CF = ac >= data;
    proc->processor->NF = (result & 0b10000000) > 0;
}

void CMP(Byte instruction, p6502* proc, int* cycles) {
    Byte data;
    switch (instruction) {
        case INS_CMP_IM: {
            data = fetch(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_CMP_ZP: {
            data = addr_zero_page(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_CMP_ZX: {
            data = addr_zero_page_x(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_CMP_AB: {
            data = addr_absolute(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_CMP_AX: {
            data = addr_absolute_x(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_CMP_AY: {
            data = addr_absolute_y(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_CMP_IX: {
            data = addr_indirect_x(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_CMP_IY: {
            data = addr_indirect_y(proc->memory, proc->cpu, cycles);
            break;
        }
    }

    if (data) { _cmp(data, proc); }
}