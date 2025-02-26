#include "instructions.h"

#define INS_LDY_IM 0xA0
#define INS_LDY_ZP 0xA4
#define INS_LDY_ZX 0xB4
#define INS_LDY_AB 0xAC
#define INS_LDY_AX 0xBC

void LDY(Byte instruction, p6502* proc, int* cycles) {
    switch (instruction) {
        case INS_LDY_IM: {
            Byte data = fetch(proc->memory, proc->cpu, cycles);
            proc->cpu->IY = data;
            proc->processor->ZF = (proc->cpu->IY == 0);
            proc->processor->NF = (proc->cpu->IY & 0b10000000) > 0;
            break;
        }
        case INS_LDY_ZP: {
            Byte address = fetch(proc->memory, proc->cpu, cycles);
            Byte data = read(proc->memory, (__uint16_t)address, cycles);
            proc->cpu->IY = data;
            proc->processor->ZF = (proc->cpu->IY == 0);
            proc->processor->NF = (proc->cpu->IY & 0b10000000) > 0;
            break;
        }
        case INS_LDY_ZX: {
            Byte zpAddress = fetch(proc->memory, proc->cpu, cycles);
            Byte address = addToByte(zpAddress, proc->cpu->IX, cycles);
            Byte data = read(proc->memory, address, cycles);
            proc->cpu->IY = data;
            proc->processor->ZF = (proc->cpu->IY == 0);
            proc->processor->NF = (proc->cpu->IY & 0b10000000) > 0;
            break;
        }
        case INS_LDY_AB: {
            Byte addressLo = fetch(proc->memory, proc->cpu, cycles);
            Byte addressHi = fetch(proc->memory, proc->cpu, cycles);
            __uint16_t address = combineBytes(addressHi, addressLo);
            Byte data = read(proc->memory, address, cycles);
            proc->cpu->IY = data;
            proc->processor->ZF = (proc->cpu->IY == 0);
            proc->processor->NF = (proc->cpu->IY & 0b10000000) > 0;
            break;
        }
        case INS_LDY_AX: {
            Byte addressLo = fetch(proc->memory, proc->cpu, cycles);
            Byte addressHi = fetch(proc->memory, proc->cpu, cycles);
            __uint16_t address = combineBytes(addressHi, addressLo);
            address = addToAddress(address, proc->cpu->IX);
            crossedPage(address, proc->cpu->IX, cycles);
            Byte data = read(proc->memory, address, cycles);
            proc->cpu->IY = data;
            proc->processor->ZF = (proc->cpu->IY == 0);
            proc->processor->NF = (proc->cpu->IY & 0b10000000) > 0;
            break;
        }
    }
}