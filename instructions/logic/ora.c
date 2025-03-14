#include "../instructions.h"

#define INS_ORA_IM 0x09
#define INS_ORA_ZP 0x05
#define INS_ORA_ZX 0x15
#define INS_ORA_AB 0x0D
#define INS_ORA_AX 0x1D
#define INS_ORA_AY 0x19
#define INS_ORA_IX 0x01
#define INS_ORA_IY 0x11

void ORA(Byte instruction, p6502* proc, int* cycles) {
    switch (instruction) {
        case INS_ORA_IM: {
            // name orend - as in addend, but for a byte to be "or'd"
            Byte orend = fetch(proc->memory, proc->cpu, cycles);
            Byte result = ora(proc->cpu->AC, orend);
            proc->cpu->AC = result;
            proc->processor->ZF = (proc->cpu->AC == 0);
            proc->processor->NF = (proc->cpu->AC & 0b10000000) > 0;
            break;
        }
        case INS_ORA_ZP: {
            Byte zpAddress = fetch(proc->memory, proc->cpu, cycles);
            Byte orend = read(proc->memory, (uint16_t)zpAddress, cycles);
            Byte result = ora(proc->cpu->AC, orend);
            proc->cpu->AC = result;
            proc->processor->ZF = (proc->cpu->AC == 0);
            proc->processor->NF = (proc->cpu->AC & 0b10000000) > 0;
            break;
        }
        case INS_ORA_ZX: {
            Byte zpByte = fetch(proc->memory, proc->cpu, cycles);
            Byte zpAddress = addToByte(zpByte, proc->cpu->IX, cycles);
            Byte orend = read(proc->memory, (uint16_t)zpAddress, cycles);
            Byte result = ora(proc->cpu->AC, orend);
            proc->cpu->AC = result;
            proc->processor->ZF = (proc->cpu->AC == 0);
            proc->processor->NF = (proc->cpu->AC & 0b10000000) > 0;
            break;
        }
        case INS_ORA_AB: {
            Byte addressLo = fetch(proc->memory, proc->cpu, cycles);
            Byte addressHi = fetch(proc->memory, proc->cpu, cycles);
            uint16_t address = combineBytes(addressHi, addressLo);
            Byte orend = read(proc->memory, address, cycles);
            Byte result = ora(proc->cpu->AC, orend);
            proc->cpu->AC = result;
            proc->processor->ZF = (proc->cpu->AC == 0);
            proc->processor->NF = (proc->cpu->AC & 0b10000000) > 0;
            break;
        }
        case INS_ORA_AX: {
            Byte addressLo = fetch(proc->memory, proc->cpu, cycles);
            Byte addressHi = fetch(proc->memory, proc->cpu, cycles);
            uint16_t address = combineBytes(addressHi, addressLo);
            crossedPage(address, proc->cpu->IX, cycles);
            address = addToAddress(address, proc->cpu->IX);
            Byte orend = read(proc->memory, address, cycles);
            Byte result = ora(proc->cpu->AC, orend);
            proc->cpu->AC = result;
            proc->processor->ZF = (proc->cpu->AC == 0);
            proc->processor->NF = (proc->cpu->AC & 0b10000000) > 0;
            break;
        }
        case INS_ORA_AY: {
            Byte addressLo = fetch(proc->memory, proc->cpu, cycles);
            Byte addressHi = fetch(proc->memory, proc->cpu, cycles);
            uint16_t address = combineBytes(addressHi, addressLo);
            crossedPage(address, proc->cpu->IY, cycles);
            address = addToAddress(address, proc->cpu->IY);
            Byte orend = read(proc->memory, address, cycles);
            Byte result = ora(proc->cpu->AC, orend);
            proc->cpu->AC = result;
            proc->processor->ZF = (proc->cpu->AC == 0);
            proc->processor->NF = (proc->cpu->AC & 0b10000000) > 0;
            break;
        }
        case INS_ORA_IX: {
            Byte zpByte = fetch(proc->memory, proc->cpu, cycles);
            Byte zpAddress = addToByte(zpByte, proc->cpu->IX, cycles);
            Byte addressLo = read(proc->memory, (uint16_t)((Byte)(zpAddress + 0)), cycles);
            Byte addressHi = read(proc->memory, (uint16_t)((Byte)(zpAddress + 1)), cycles);
            uint16_t address = combineBytes(addressHi, addressLo);
            Byte orend = read(proc->memory, address, cycles);
            Byte result = ora(proc->cpu->AC, orend);
            proc->cpu->AC = result;
            proc->processor->ZF = (proc->cpu->AC == 0);
            proc->processor->NF = (proc->cpu->AC & 0b10000000) > 0;
            break;
        }
        case INS_ORA_IY: {
            Byte zpByte = fetch(proc->memory, proc->cpu, cycles);
            crossedPage(zpByte + 0, proc->cpu->IY, cycles);
            crossedPage(zpByte + 1, proc->cpu->IY, cycles);
            uint16_t zpAddress = addToAddress(zpByte, proc->cpu->IY);
            Byte addressLo = read(proc->memory, zpAddress + 0, cycles);
            Byte addressHi = read(proc->memory, zpAddress + 1, cycles);
            uint16_t address = combineBytes(addressHi, addressLo);
            Byte orend = read(proc->memory, address, cycles);
            Byte result = ora(proc->cpu->AC, orend);
            proc->cpu->AC = result;
            proc->processor->ZF = (proc->cpu->AC == 0);
            proc->processor->NF = (proc->cpu->AC & 0b10000000) > 0;
            break;
        }
    }
}