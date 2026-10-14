#include "../instructions.h"

static void _adc(Byte byte, p6502* proc) {
    Word result = add(byte, proc);                                  // add byte to AC
    if ((result & 0b100000000) > 0) { proc->processor->OF = 1; }    // check if bit 8 set
    proc->processor->ZF = result == 0;                              // check if result == 0
    proc->processor->NF = (result & 0b10000000) > 0;                // check if bit 7 set (negative check)
    proc->cpu->AC = (Byte)result;                                   // store result in AC
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