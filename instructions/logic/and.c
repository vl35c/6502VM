#include "../instructions.h"

#define INS_AND_IM 0x29
#define INS_AND_ZP 0x25
#define INS_AND_ZX 0x35
#define INS_AND_AB 0x2D
#define INS_AND_AX 0x3D
#define INS_AND_AY 0x39
#define INS_AND_IX 0x21
#define INS_AND_IY 0x31

void AND(Byte instruction, p6502* proc, int* cycles) {
    switch (instruction) {
        case INS_AND_IM: {
            Byte andend = fetch(proc->memory, proc->cpu, cycles);
            Byte sum = and(proc->cpu->AC, andend);
            proc->cpu->AC = sum;
            proc->processor->ZF = (proc->cpu->AC == 0);
            proc->processor->NF = (proc->cpu->AC & 0b10000000) > 0;
            break;
        }
        case INS_AND_ZP: {
            Byte address = fetch(proc->memory, proc->cpu, cycles);
            Byte andend = read(proc->memory, (uint16_t)address, cycles);
            Byte sum = and(proc->cpu->AC, andend);
            proc->cpu->AC = sum;
            proc->processor->ZF = (proc->cpu->AC == 0);
            proc->processor->NF = (proc->cpu->AC & 0b10000000) > 0;
            break;
        }
        case INS_AND_ZX: {
            Byte zpAddress = fetch(proc->memory, proc->cpu, cycles);
            uint16_t address = addToByte(zpAddress, proc->cpu->IX, cycles);
            Byte andend = read(proc->memory, (uint16_t)address, cycles);
            Byte sum = and(proc->cpu->AC, andend);
            proc->cpu->AC = sum;
            proc->processor->ZF = (proc->cpu->AC == 0);
            proc->processor->NF = (proc->cpu->AC & 0b10000000) > 0;
            break;
        }
        case INS_AND_AB: {
            Byte addressLo = fetch(proc->memory, proc->cpu, cycles);
            Byte addressHi = fetch(proc->memory, proc->cpu, cycles);
            uint16_t address = combineBytes(addressHi, addressLo);
            Byte andend = read(proc->memory, address, cycles);
            Byte sum = and(proc->cpu->AC, andend);
            proc->cpu->AC = sum;
            proc->processor->ZF = (proc->cpu->AC == 0);
            proc->processor->NF = (proc->cpu->AC & 0b10000000) > 0;
            break;
        }
        case INS_AND_AX: {
            Byte addressLo = fetch(proc->memory, proc->cpu, cycles);
            Byte addressHi = fetch(proc->memory, proc->cpu, cycles);
            uint16_t address = combineBytes(addressHi, addressLo);
            crossedPage(address, proc->cpu->IX, cycles);
            address = addToAddress(address, proc->cpu->IX);
            Byte andend = read(proc->memory, address, cycles);
            Byte sum = and(proc->cpu->AC, andend);
            proc->cpu->AC = sum;
            proc->processor->ZF = (proc->cpu->AC == 0);
            proc->processor->NF = (proc->cpu->AC & 0b10000000) > 0;
            break;
        }
        case INS_AND_AY: {
            Byte addressLo = fetch(proc->memory, proc->cpu, cycles);
            Byte addressHi = fetch(proc->memory, proc->cpu, cycles);
            uint16_t address = combineBytes(addressHi, addressLo);
            crossedPage(address, proc->cpu->IY, cycles);
            address = addToAddress(address, proc->cpu->IY);
            Byte andend = read(proc->memory, address, cycles);
            Byte sum = and(proc->cpu->AC, andend);
            proc->cpu->AC = sum;
            proc->processor->ZF = (proc->cpu->AC == 0);
            proc->processor->NF = (proc->cpu->AC & 0b10000000) > 0;
            break;
        }
        case INS_AND_IX: {
            Byte zpAddress = fetch(proc->memory, proc->cpu, cycles);
            zpAddress = addToByte(zpAddress, proc->cpu->IX, cycles);
            Byte addressLo = read(proc->memory, (uint16_t)((Byte)(zpAddress + 0)), cycles);
            Byte addressHi = read(proc->memory, (uint16_t)((Byte)(zpAddress + 1)), cycles);
            uint16_t address = combineBytes(addressHi, addressLo);
            Byte andend = read(proc->memory, address, cycles);
            Byte sum = and(proc->cpu->AC, andend);
            proc->cpu->AC = sum;
            proc->processor->ZF = (proc->cpu->AC == 0);
            proc->processor->NF = (proc->cpu->AC & 0b10000000) > 0;
            break;
        }
        case INS_AND_IY: {
            Byte zpByte = fetch(proc->memory, proc->cpu, cycles);
            crossedPage(zpByte, proc->cpu->IY + 0, cycles);
            crossedPage(zpByte, proc->cpu->IY + 1, cycles);
            uint16_t zpAddress = addToAddress((uint16_t)zpByte, proc->cpu->IY);
            Byte addressLo = read(proc->memory, zpAddress + 0, cycles);
            Byte addressHi = read(proc->memory, zpAddress + 1, cycles);
            uint16_t address = combineBytes(addressHi, addressLo);
            Byte andend = read(proc->memory, address, cycles);
            Byte sum = and(proc->cpu->AC, andend);
            proc->cpu->AC = sum;
            proc->processor->ZF = (proc->cpu->AC == 0);
            proc->processor->NF = (proc->cpu->AC & 0b10000000) > 0;
            break;
        }
    }
}