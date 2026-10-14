#include "../instructions.h"

#define INS_ORA_IM 0x09
#define INS_ORA_ZP 0x05
#define INS_ORA_ZX 0x15
#define INS_ORA_AB 0x0D
#define INS_ORA_AX 0x1D
#define INS_ORA_AY 0x19
#define INS_ORA_IX 0x01
#define INS_ORA_IY 0x11

static void _ora(Byte data, p6502* proc) {
    Byte result = ora(proc->cpu->AC, data);
    proc->cpu->AC = result;
    proc->processor->ZF = (proc->cpu->AC == 0);
    proc->processor->NF = (proc->cpu->AC & 0b10000000) > 0;
}

void ORA(Byte instruction, p6502* proc, int* cycles) {
    Byte data;
    switch (instruction) {
        case INS_ORA_IM: {
            data = fetch(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_ORA_ZP: {
            data = addr_zero_page(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_ORA_ZX: {
            data = addr_zero_page_x(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_ORA_AB: {
            data = addr_absolute(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_ORA_AX: {
            data = addr_absolute_x(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_ORA_AY: {
            data = addr_absolute_y(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_ORA_IX: {
            data = addr_indirect_x(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_ORA_IY: {
            data = addr_indirect_y(proc->memory, proc->cpu, cycles);
            break;
        }
    }

    if (data) { _ora(data, proc); }
}