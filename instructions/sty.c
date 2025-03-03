#include "instructions.h"

#define INS_STY_ZP 0x84
#define INS_STY_ZX 0x94

void STY(Byte instruction, p6502* proc, int* cycles) {
    switch(instruction) {
        case INS_STY_ZP: {
            Byte address = fetch(proc->memory, proc->cpu, cycles);
            Byte data = proc->cpu->IY;
            write(proc->memory, (uint16_t)address, data, cycles);
            break;
        }
        case INS_STY_ZX: {
            Byte zpAddress = fetch(proc->memory, proc->cpu, cycles);
            Byte address = addToByte(zpAddress, proc->cpu->IX, cycles);
            Byte data = proc->cpu->IY;
            write(proc->memory, (uint16_t)address, data, cycles);
            break;
        }
    }
}