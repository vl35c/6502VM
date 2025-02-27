#include "instructions.h"

#define INS_STA_ZP 0x85
#define INS_STA_ZX 0x95
#define INS_STA_AB 0x8D
#define INS_STA_AX 0x9D
#define INS_STA_AY 0x99
#define INS_STA_IX 0x81
#define INS_STA_IY 0x91

void STA(Byte instruction, p6502* proc, int* cycles) {
    switch (instruction) {
        case INS_STA_ZP: {
            Byte address = fetch(proc->memory, proc->cpu, cycles);
            Byte data = proc->cpu->AC;
            write(proc->memory, address, data, cycles);
            break;
        }
        case INS_STA_ZX: {
            Byte zpAddress = fetch(proc->memory, proc->cpu, cycles);
            Byte address = addToByte(zpAddress, proc->cpu->IX, cycles);
            Byte data = proc->cpu->AC;
            write(proc->memory, (__uint16_t)address, data, cycles);
            break;
        }
        case INS_STA_AB: {
            Byte addressLo = fetch(proc->memory, proc->cpu, cycles);
            Byte addressHi = fetch(proc->memory, proc->cpu, cycles);
            __uint16_t address = combineBytes(addressHi, addressLo);
            Byte data = proc->cpu->AC;
            write(proc->memory, address, data, cycles);
            break;
        }
        case INS_STA_AX: {
            Byte addressLo = fetch(proc->memory, proc->cpu, cycles);
            Byte addressHi = fetch(proc->memory, proc->cpu, cycles);
            __uint16_t address = combineBytes(addressHi, addressLo);
            address = addToAddress(address, proc->cpu->IX);
            --*cycles;
            Byte data = proc->cpu->AC;
            write(proc->memory, address, data, cycles);
            break;
        }
        case INS_STA_AY: {
            Byte addressLo = fetch(proc->memory, proc->cpu, cycles);
            Byte addressHi = fetch(proc->memory, proc->cpu, cycles);
            __uint16_t address = combineBytes(addressHi, addressLo);
            address = addToAddress(address, proc->cpu->IY);
            --*cycles;
            Byte data = proc->cpu->AC;
            write(proc->memory, address, data, cycles);
            break;
        }
        case INS_STA_IX: {
            Byte zpAddress = fetch(proc->memory, proc->cpu, cycles);
            Byte addressLo = read(proc->memory, (__uint16_t)(zpAddress + 0), cycles);
            Byte addressHi = read(proc->memory, (__uint16_t)((Byte)(zpAddress + 1)), cycles);
            __uint16_t address = combineBytes(addressHi, addressLo);
            address = addToAddress(address, proc->cpu->IX);
            --*cycles;
            Byte data = proc->cpu->AC;
            write(proc->memory, address, data, cycles);
        }
        case INS_STA_IY: {
            Byte zpAddress = fetch(proc->memory, proc->cpu, cycles);
            Byte addressLo = read(proc->memory, (__uint16_t)(zpAddress + 0), cycles);
            Byte addressHi = read(proc->memory, (__uint16_t)(zpAddress + 1), cycles);
            __uint16_t address = combineBytes(addressHi, addressLo);
            address = addToAddress(address, proc->cpu->IY);
            --*cycles;
            Byte data = proc->cpu->AC;
            write(proc->memory, address, data, cycles);
        }
    }
}