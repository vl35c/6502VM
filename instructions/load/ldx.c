#include "../instructions.h"

#define INS_LDX_IM 0xA2
#define INS_LDX_ZP 0xA6
#define INS_LDX_ZY 0xB6
#define INS_LDX_AB 0xAE
#define INS_LDX_AY 0xBE

static void _ldx(Byte data, p6502* proc) {
    proc->cpu->IX = data;
    proc->processor->ZF = (proc->cpu->IX == 0);
    proc->processor->NF = (proc->cpu->IX & 0b10000000) > 0;
}

void LDX(Byte instruction, p6502* proc, int* cycles) {
    Byte data;
    switch (instruction) {
        case INS_LDX_IM: {
            data = fetch(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_LDX_ZP: {
            data = addr_zero_page(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_LDX_ZY: {
            data = addr_zero_page_y(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_LDX_AB: {
            data = addr_absolute(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_LDX_AY: {
            data = addr_absolute_y(proc->memory, proc->cpu, cycles);
            break;
        }
    }
    if (data) { _ldx(data, proc); }
}