#include "../instructions.h"

static void _cpy(Byte data, p6502* proc) {
    Byte y = proc->cpu->IY;
    Byte result = (Byte)(y - data);
    proc->processor->ZF = y == data;
    proc->processor->CF = y >= data;
    proc->processor->NF = (result & 0b10000000) > 0;
}

void CPY(Byte instruction, p6502* proc, int* cycles) {
    Byte data;
    switch (instruction) {
        case INS_CPY_IM: {
            data = fetch(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_CPY_ZP: {
            data = addr_zero_page(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_CPY_AB: {
            data = addr_absolute(proc->memory, proc->cpu, cycles);
            break;
        }
    }

    if (data) { _cpy(data, proc); }
}