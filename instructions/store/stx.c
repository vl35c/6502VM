#include "../instructions.h"

#define INS_STX_ZP 0x86
#define INS_STX_ZY 0x96
#define INS_STX_AB 0x8E

void STX(Byte instruction, p6502* proc, int* cycles) {
    switch (instruction) {
        case INS_STX_ZP: {
            Byte address = fetch(proc->memory, proc->cpu, cycles);
            Byte data = proc->cpu->IX;
            write(proc->memory, (uint16_t)address, data, cycles);
            break;
        }
        case INS_STX_ZY: {
            Byte zpAddress = fetch(proc->memory, proc->cpu, cycles);
            Byte address = addToAddress(zpAddress, proc->cpu->IY);
            Byte data = proc->cpu->IX;
            write(proc->memory, (uint16_t)address, data, cycles);
            break;
        }
        case INS_STX_AB: {
            Byte addressLo = fetch(proc->memory, proc->cpu, cycles);
            Byte addressHi = fetch(proc->memory, proc->cpu, cycles);
            uint16_t address = combineBytes(addressHi, addressLo);
            Byte data = proc->cpu->IX;
            write(proc->memory, address, data, cycles);
            break;
        }
    }
}