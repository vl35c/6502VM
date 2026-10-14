#include "../instructions.h"

#define INS_SBC_IM 0xE9
#define INS_SBC_ZP 0xE5
#define INS_SBC_ZX 0xF5
#define INS_SBC_AB 0xED
#define INS_SBC_AX 0xFD
#define INS_SBC_AY 0xF9
#define INS_SBC_IX 0xE1
#define INS_SBC_IY 0xF1

static void _sbc(Byte data, p6502* proc) {
    Word result = sub(data, proc);                                  // subtract byte from AC
    if ((result & 0b100000000) > 0) { proc->processor->OF = 0; }    // clear OF if overflow in bit 8
    proc->processor->NF = (result & 0b10000000) > 0;                // set NF if bit 7 is set
    proc->processor->ZF = result == 0;                              // set ZF if result == 0
    proc->cpu->AC = (Byte)result;                                   // store result in AC
}

void SBC(Byte instruction, p6502* proc, int* cycles) {
    Byte data;
    switch (instruction) {
        case INS_SBC_IM: {
            data = fetch(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_SBC_ZP: {
            data = addr_zero_page(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_SBC_ZX: {
            data = addr_zero_page_x(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_SBC_AB: {
            data = addr_absolute(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_SBC_AX: {
            data = addr_absolute_x(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_SBC_AY: {
            data = addr_absolute_y(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_SBC_IX: {
            data = addr_indirect_x(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_SBC_IY: {
            data = addr_indirect_y(proc->memory, proc->cpu, cycles);
            break;
        }
    }

    if (data) { _sbc(data, proc); }
}