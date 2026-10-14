#include "../instructions.h"

static void _inc(Word address, p6502* proc, int* cycles) {
    Byte data = read(proc->memory, address, cycles);
    Byte new_data = (Byte)(data + 1);
    write(proc->memory, address, new_data, cycles);
} 

void INC(Byte instruction, p6502* proc, int* cycles) {
    Word address;
    switch (instruction) {
        case INS_INC_ZP: {
            Byte zpAddress = fetch(proc->memory, proc->cpu, cycles);
            address = (Word)zpAddress;
            break;
        }
        case INS_INC_ZX: {
            Byte zpAddress = fetch(proc->memory, proc->cpu, cycles);
            zpAddress = addToByte(zpAddress, proc->cpu->IX, cycles);
            address = (Word)zpAddress;
            break;
        }
        case INS_INC_AB: {
            Byte addressLo = fetch(proc->memory, proc->cpu, cycles);
            Byte addressHi = fetch(proc->memory, proc->cpu, cycles);
            address = combineBytes(addressHi, addressLo);
            break;
        }
        case INS_INC_AX: {
            Byte addressLo = fetch(proc->memory, proc->cpu, cycles);
            Byte addressHi = fetch(proc->memory, proc->cpu, cycles);
            address = combineBytes(addressHi, addressLo);
            address = addToAddress(address, proc->cpu->IX);
            break;
        }
    }

    if (address) { _inc(address, proc, cycles); }
}