#include "../instructions.h"

#define INS_LDY_IM 0xA0
#define INS_LDY_ZP 0xA4
#define INS_LDY_ZX 0xB4
#define INS_LDY_AB 0xAC
#define INS_LDY_AX 0xBC

static void _ldy(Byte data, p6502* proc) {
    proc->cpu->IY = data;
    proc->processor->ZF = (proc->cpu->IY == 0);
    proc->processor->NF = (proc->cpu->IY & 0b10000000) > 0;
}

void LDY(Byte instruction, p6502* proc, int* cycles) {
    Byte data;
    switch (instruction) {
        case INS_LDY_IM: {
            data = fetch(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_LDY_ZP: {
            data = addr_zero_page(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_LDY_ZX: {
            data = addr_zero_page_x(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_LDY_AB: {
            data = addr_absolute(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_LDY_AX: {
            data = addr_absolute_x(proc->memory, proc->cpu, cycles);
            break;
        }
    }

    if (data) { _ldy(data, proc); }
}