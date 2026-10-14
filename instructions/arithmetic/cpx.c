#include "../instructions.h"

static void _cpx(Byte data, p6502* proc) {
    Byte x = proc->cpu->IX;
    Byte result = (Byte)(x - data);
    proc->processor->ZF = x == data;
    proc->processor->CF = x >= data;
    proc->processor->NF = (result & 0b10000000) > 0;
}

void CPX(Byte instruction, p6502* proc, int* cycles) {
    Byte data;
    switch (instruction) {
        case INS_CPX_IM: {
            data = fetch(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_CPX_ZP: {
            data = addr_zero_page(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_CPX_AB: {
            data = addr_absolute(proc->memory, proc->cpu, cycles);
            break;
        }
    }

    if (data) { _cpx(data, proc); }
}