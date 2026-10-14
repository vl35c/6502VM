#include "../instructions.h"

#define INS_ADC_IM 0x69
#define INS_ADC_ZP 0x65
#define INS_ADC_ZX 0x75
#define INS_ADC_AB 0x6D
#define INS_ADC_AX 0x7D
#define INS_ADC_AY 0x79
#define INS_ADC_IX 0x61
#define INS_ADC_IY 0x71

static void _adc(Byte byte, p6502* proc) {
    // common functionality
    Byte result = add(byte, proc->cpu);                 // add byte to AC
    proc->processor->OF = (result & 0b10000000) > 0;    // check if 8th bit set
    proc->processor->ZF = result == 0;                  // check if result == 0
    proc->processor->NF = (result & 0b1000000) > 0;     // check if 7th bit set (negative check)
    proc->cpu->AC = (Byte)result;
}

void ADC(Byte instruction, p6502* proc, int* cycles) {
    Byte data;
    switch (instruction) {
        case INS_ADC_IM: {
            data = fetch(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_ADC_ZP: {
            data = addr_zero_page(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_ADC_ZX: {
            data = addr_zero_page_x(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_ADC_AB: {
            data = addr_absolute(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_ADC_AX: {
            data = addr_absolute_x(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_ADC_AY: {
            data = addr_absolute_y(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_ADC_IX: {
            data = addr_indirect_x(proc->memory, proc->cpu, cycles);
            break;
        }
        case INS_ADC_IY: {
            data = addr_indirect_y(proc->memory, proc->cpu, cycles);
            break;
        }
    }
    if (data) { _adc(data, proc); }
}