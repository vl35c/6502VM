#include "../instructions.h"

void LDA(Byte instruction, p6502* proc, int* cycles) {
    #define INS_LDA_IM 0xA9
    #define INS_LDA_ZP 0xA5
    #define INS_LDA_ZX 0xB5
    #define INS_LDA_AB 0xAD
    #define INS_LDA_AX 0xBD
    #define INS_LDA_AY 0xB9
    #define INS_LDA_IX 0xA1
    #define INS_LDA_IY 0xB1

    switch (instruction) {
        // LDA Immediate
        case INS_LDA_IM: {
            // fetchs byte and loads straight into AC
            Byte data = fetch(proc->memory, proc->cpu, cycles);
            proc->cpu->AC = data;
            // flag checking
            proc->processor->ZF = (proc->cpu->AC == 0);
            proc->processor->NF = (proc->cpu->AC & 0b10000000) > 0;
            break;
        }
        // LDA Zero Page
        case INS_LDA_ZP: {
            // fetchs byte to be the low byte of a zero page address i.e. 0x12 -> 0x0012
            Byte address = fetch(proc->memory, proc->cpu, cycles);
            // reads data from zero page and loads into AC
            Byte data = read(proc->memory, (uint16_t)address, cycles);
            proc->cpu->AC = data;
            proc->processor->ZF = (proc->cpu->AC == 0);
            proc->processor->NF = (proc->cpu->AC & 0b10000000) > 0;
            break;
        }
        // LDA Zero Page X
        case INS_LDA_ZX: {
            // fetchs byte to be the low byte of a zero page address
            Byte address = fetch(proc->memory, proc->cpu, cycles);
            // adds the index register X to the byte, with wraparound i.e. 0xFF + 0x01 = 0x00
            address = addToByte(address, proc->cpu->IX, cycles);
            // reads data from zero page and loads into AC
            Byte data = read(proc->memory, (uint16_t)address, cycles);
            proc->cpu->AC = data;
            proc->processor->ZF = (proc->cpu->AC == 0);
            proc->processor->NF = (proc->cpu->AC & 0b10000000) > 0;
            break;
        }
        // LDA Absolute
        case INS_LDA_AB: {
            // fetchs byte to be low byte of an address
            Byte addressLo = fetch(proc->memory, proc->cpu, cycles);
            // fetchs byte to be high byte of an address
            Byte addressHi = fetch(proc->memory, proc->cpu, cycles);
            // combines bytes into a 2 byte address
            uint16_t address = combineBytes(addressHi, addressLo);
            // reads data from the calculated address and loads into AC
            Byte data = read(proc->memory, address, cycles);
            proc->cpu->AC = data;
            proc->processor->ZF = (proc->cpu->AC == 0);
            proc->processor->NF = (proc->cpu->AC & 0b10000000) > 0;
            break;
        }
        // LDS Absolute X
        case INS_LDA_AX: {
            // fetchs byte to be low byte of an address
            Byte addressLo = fetch(proc->memory, proc->cpu, cycles);
            // fetchs byte to be high byte of an address
            Byte addressHi = fetch(proc->memory, proc->cpu, cycles);
            // combines bytes into a 2 byte address
            uint16_t address = combineBytes(addressHi, addressLo);
            // checks if the addition crossed a page, which uses an extra cycle
            crossedPage(address, proc->cpu->IX, cycles);
            // adds address and Index Register X together
            address = addToAddress(address, proc->cpu->IX);
            // reads data from the calculated address and loads into AC
            Byte data = read(proc->memory, address, cycles);
            proc->cpu->AC = data;
            proc->processor->ZF = (proc->cpu->AC == 0);
            proc->processor->NF = (proc->cpu->AC & 0b10000000) > 0;
            break;
        }
        // LDA Absolute Y
        // same as above, but with Index Register Y instead of X
        case INS_LDA_AY: {
            Byte addressLo = fetch(proc->memory, proc->cpu, cycles);
            Byte addressHi = fetch(proc->memory, proc->cpu, cycles);
            uint16_t address = combineBytes(addressHi, addressLo);
            crossedPage(address, proc->cpu->IY, cycles);
            address = addToAddress(address, proc->cpu->IY);
            Byte data = read(proc->memory, address, cycles);
            proc->cpu->AC = data;
            proc->processor->ZF = (proc->cpu->AC == 0);
            proc->processor->NF = (proc->cpu->AC & 0b10000000) > 0;
            break;
        }
        // LDA Indirect X
        case INS_LDA_IX: {
            // fetchs byte from memory to be low byte of a zero page address
            Byte zpAddress = fetch(proc->memory, proc->cpu, cycles);
            // adds Index Register X to the address and uses wraparound to keep it on the zero page
            zpAddress = addToByte(zpAddress, proc->cpu->IX, cycles);
            // reads byte to be low byte of address from zero page
            Byte addressLo = read(proc->memory, (uint16_t)zpAddress, cycles);
            // reads next byte to be high byte of address from zero page
            Byte addressHi = read(proc->memory, (uint16_t)((Byte)(zpAddress + 1)), cycles);
            // combines bytes to find address
            uint16_t address = combineBytes(addressHi, addressLo);
            // reads data from calculated address and stores in AC
            Byte data = read(proc->memory, address, cycles);
            proc->cpu->AC = data;
            proc->processor->ZF = (proc->cpu->AC == 0);
            proc->processor->NF = (proc->cpu->AC & 0b10000000) > 0;
            break;
        }
        // LDA Indirect Y
        case INS_LDA_IY: {
            // fetchs byte to be low byte of a zero page address
            Byte zpByte = fetch(proc->memory, proc->cpu, cycles);
            // checks if either new address or next address has crossed page, if so uses an extra cycle
            crossedPage(zpByte, proc->cpu->IY + 0, cycles);
            crossedPage(zpByte, proc->cpu->IY + 1, cycles);
            // adds Index Register Y to byte WITHOUT wraparound
            uint16_t zpAddress = addToAddress((uint16_t)zpByte, proc->cpu->IY);
            // reads byte to be low byte of address
            Byte addressLo = read(proc->memory, zpAddress, cycles);
            // reads byte to be high byte of address
            Byte addressHi = read(proc->memory, zpAddress + 1, cycles);
            // combines bytes into readable address
            uint16_t address = combineBytes(addressHi, addressLo);
            // reads data from calculated address and stores in AC
            Byte data = read(proc->memory, address, cycles);
            proc->cpu->AC = data;
            proc->processor->ZF = (proc->cpu->AC == 0);
            proc->processor->NF = (proc->cpu->AC & 0b10000000) > 0;
            break;
        }
    }
}