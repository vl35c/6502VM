#include "../instructions.h"

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
            write(proc->memory, (Word)address, data, cycles);
            break;
        }
        case INS_STA_AB: {
            Byte addressLo = fetch(proc->memory, proc->cpu, cycles);
            Byte addressHi = fetch(proc->memory, proc->cpu, cycles);
            Word address = combineBytes(addressHi, addressLo);
            Byte data = proc->cpu->AC;
            write(proc->memory, address, data, cycles);
            break;
        }
        case INS_STA_AX: {
            Byte addressLo = fetch(proc->memory, proc->cpu, cycles);
            Byte addressHi = fetch(proc->memory, proc->cpu, cycles);
            Word address = combineBytes(addressHi, addressLo);
            address = addToAddress(address, proc->cpu->IX);
            --*cycles;
            Byte data = proc->cpu->AC;
            write(proc->memory, address, data, cycles);
            break;
        }
        case INS_STA_AY: {
            Byte addressLo = fetch(proc->memory, proc->cpu, cycles);
            Byte addressHi = fetch(proc->memory, proc->cpu, cycles);
            Word address = combineBytes(addressHi, addressLo);
            address = addToAddress(address, proc->cpu->IY);
            --*cycles;
            Byte data = proc->cpu->AC;
            write(proc->memory, address, data, cycles);
            break;
        }
        case INS_STA_IX: {
            Byte zpAddress = fetch(proc->memory, proc->cpu, cycles);
            Byte addressLo = read(proc->memory, (Word)(zpAddress + 0), cycles);
            Byte addressHi = read(proc->memory, (Word)((Byte)(zpAddress + 1)), cycles);
            Word address = combineBytes(addressHi, addressLo);
            address = addToAddress(address, proc->cpu->IX);
            --*cycles;
            Byte data = proc->cpu->AC;
            write(proc->memory, address, data, cycles);
        }
        case INS_STA_IY: {
            Byte zpAddress = fetch(proc->memory, proc->cpu, cycles);
            Byte addressLo = read(proc->memory, (Word)(zpAddress + 0), cycles);
            Byte addressHi = read(proc->memory, (Word)(zpAddress + 1), cycles);
            Word address = combineBytes(addressHi, addressLo);
            address = addToAddress(address, proc->cpu->IY);
            --*cycles;
            Byte data = proc->cpu->AC;
            write(proc->memory, address, data, cycles);
        }
    }
}