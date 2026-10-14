#include "../instructions.h"

static void _lda(Byte data, p6502* proc) {
    proc->cpu->AC = data;
    proc->processor->ZF = (proc->cpu->AC == 0);
    proc->processor->NF = (proc->cpu->AC & 0b10000000) > 0;
}

void LDA(Byte instruction, p6502* proc, int* cycles) {
    Byte data;
    switch (instruction) {
        case INS_LDA_IM: {
            data = fetch(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_LDA_ZP: {
            data = addr_zero_page_x(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_LDA_ZX: {
            data = addr_zero_page_x(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_LDA_AB: {
            data = addr_absolute(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_LDA_AX: {
            data = addr_absolute_x(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_LDA_AY: {
            data = addr_absolute_y(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_LDA_IX: {
            data = addr_indirect_x(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_LDA_IY: {
            data = addr_indirect_y(proc->memory, proc->cpu, cycles);
            break;
        }
    }

    if (data) { _lda(data, proc); }
}