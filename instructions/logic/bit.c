#include "../functions.h"

#define INS_BIT_ZP 0x24
#define INS_BIT_AB 0x2C

void BIT(Byte instruction, p6502* proc, int* cycles) {
    switch (instruction) {
        case INS_BIT_ZP: {
            Byte zpAddress = fetch(proc->memory, proc->cpu, cycles);
            Byte data = read(proc->memory, (uint16_t)zpAddress, cycles);
            Byte result = and(proc->cpu->AC, data);
            proc->processor->ZF = result == 0;
            proc->processor->OF = result >> 5;
            proc->processor->NF = result >> 6;
            break;
        }
        case INS_BIT_AB: {
            Byte addressLo = fetch(proc->memory, proc->cpu, cycles);
            Byte addressHi = fetch(proc->memory, proc->cpu, cycles);
            uint16_t address = combineBytes(addressHi, addressLo);
            Byte data = read(proc->memory, address, cycles);
            Byte result = and(proc->cpu->AC, data);
            proc->processor->ZF = result == 0;
            proc->processor->OF = result >> 5;
            proc->processor->NF = result >> 6;
            break;
        }
    }
}