#include "instructions.h"

#define INS_LDX_IM 0xA2
#define INS_LDX_ZP 0xA6
#define INS_LDX_ZY 0xB6
#define INS_LDX_AB 0xAE
#define INS_LDX_AY 0xBE

void LDX(Byte instruction, p6502* proc, int* cycles) {
    switch (instruction) {
        case INS_LDX_IM: {
            Byte data = fetch(proc->memory, proc->cpu, cycles);
            proc->cpu->IX = data;
            proc->processor->ZF = (proc->cpu->IX == 0);
            proc->processor->NF = (proc->cpu->IX & 0b10000000) > 0;
            break;
        }
        case INS_LDX_ZP: {
            Byte address = fetch(proc->memory, proc->cpu, cycles);
            Byte data = read(proc->memory, (__uint16_t)address, cycles);
            proc->cpu->IX = data;
            proc->processor->ZF = (proc->cpu->IX == 0);
            proc->processor->NF = (proc->cpu->IX & 0b10000000) > 0;
            break;
        }
        case INS_LDX_ZY: {
            Byte zpAddress = fetch(proc->memory, proc->cpu, cycles);
            Byte address = addToByte(zpAddress, proc->cpu->IY, cycles);
            Byte data = read(proc->memory, (__uint16_t)address, cycles);
            proc->cpu->IX = data;
            proc->processor->ZF = (proc->cpu->IX == 0);
            proc->processor->NF = (proc->cpu->IX & 0b10000000) > 0;
            break;
        }
        case INS_LDX_AB: {
            Byte addressLo = fetch(proc->memory, proc->cpu, cycles);
            Byte addressHi = fetch(proc->memory, proc->cpu, cycles);
            __uint16_t address = combineBytes(addressHi, addressLo);
            Byte data = read(proc->memory, address, cycles);
            proc->cpu->IX = data;
            proc->processor->ZF = (proc->cpu->IX == 0);
            proc->processor->NF = (proc->cpu->IX & 0b10000000) > 0;
            break;
        }
        case INS_LDX_AY: {
            Byte addressLo = fetch(proc->memory, proc->cpu, cycles);
            Byte addressHi = fetch(proc->memory, proc->cpu, cycles);
            __uint16_t address = combineBytes(addressHi, addressLo);
            address = addToAddress(address, proc->cpu->IY);
            crossedPage(address, proc->cpu->IY, cycles);
            Byte data = read(proc->memory, address, cycles);
            proc->cpu->IX = data;
            proc->processor->ZF = (proc->cpu->IX == 0);
            proc->processor->NF = (proc->cpu->IX & 0b10000000) > 0;
            break;
        }
    }
}