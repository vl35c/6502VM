#include <stdbool.h>
#include <stdio.h>

#include "cpu.h"

// fetch retrieves byte from memory and increases program counter
static Byte fetch(Memory* memory, CPU* cpu, int* cycles) {
    Byte byte = memory->data[cpu->PC];
    cpu->PC++;
    --*cycles;

    return byte;
}

// read retrieves byte from memory without increasing program counter
static Byte read(Memory* memory, __uint16_t address, int* cycles) {
    Byte byte = memory->data[address];
    --*cycles;

    return byte;
}

// addToByte takes an address and a register and combines the two, constraining the result to a uint8
static Byte addToByte(Byte address, Byte indexRegister, int* cycles) {
    __uint16_t bytes = address + indexRegister;
    --*cycles;
    return (Byte)bytes;
}

// addToAddress take an address and a register and combines the two, constraining the result to a uint16
static __uint16_t addToAddress(__uint16_t address, Byte indexRegister, int* cycles) {
    return address + indexRegister;
}

// crossedPage checks if an address and register when combine change the page, i.e. the first byte of an address [0x!!__]
static void crossedPage(__uint16_t address, Byte indexRegister, int* cycles) {
    if ((Byte)(address + indexRegister) < (Byte)address) {
        --*cycles;
    }
}

// combine bytes takes two bytes and returns them as an address (uint16)
static __uint16_t combineBytes(Byte hi, Byte lo) {
    return (__uint16_t)((hi << 8) + lo);
}

// opcode definitions
#define INS_LDA_IM 0xA9
#define INS_LDA_ZP 0xA5
#define INS_LDA_ZX 0xB5
#define INS_LDA_AB 0xAD
#define INS_LDA_AX 0xBD
#define INS_LDA_AY 0xB9
#define INS_LDA_IX 0xA1
#define INS_LDA_IY 0xB1

// main loop
void execute(p6502* proc, int cycles) {
    while (cycles > 0) {
        // gets opcode from memory wherever program counter is pointing
        Byte instruction = fetch(proc->memory, proc->cpu, &cycles);

        switch (instruction) {
            // LDA Immediate
            case INS_LDA_IM: {
                // fetchs byte and loads straight into AC
                Byte data = fetch(proc->memory, proc->cpu, &cycles);
                proc->cpu->AC = data;
                // flag checking
                proc->processor->ZF = (proc->cpu->AC == 0);
                proc->processor->NF = (proc->cpu->AC & 0b10000000) > 0;
                break;
            }
            // LDA Zero Page
            case INS_LDA_ZP: {
                // fetchs byte to be the low byte of a zero page address i.e. 0x12 -> 0x0012
                Byte address = fetch(proc->memory, proc->cpu, &cycles);
                // reads data from zero page and loads into AC
                Byte data = read(proc->memory, (__uint16_t)address, &cycles);
                proc->cpu->AC = data;
                proc->processor->ZF = (proc->cpu->AC == 0);
                proc->processor->NF = (proc->cpu->AC & 0b10000000) > 0;
                break;
            }
            // LDA Zero Page X
            case INS_LDA_ZX: {
                // fetchs byte to be the low byte of a zero page address
                Byte address = fetch(proc->memory, proc->cpu, &cycles);
                // adds the index register X to the byte, with wraparound i.e. 0xFF + 0x01 = 0x00
                address = addToByte(address, proc->cpu->IX, &cycles);
                // reads data from zero page and loads into AC
                Byte data = read(proc->memory, (__uint16_t)address, &cycles);
                proc->cpu->AC = data;
                proc->processor->ZF = (proc->cpu->AC == 0);
                proc->processor->NF = (proc->cpu->AC & 0b10000000) > 0;
                break;
            }
            // LDA Absolute
            case INS_LDA_AB: {
                // fetchs byte to be low byte of an address
                Byte addressLo = fetch(proc->memory, proc->cpu, &cycles);
                // fetchs byte to be high byte of an address
                Byte addressHi = fetch(proc->memory, proc->cpu, &cycles);
                // combines bytes into a 2 byte address
                __uint16_t address = combineBytes(addressHi, addressLo);
                // reads data from the calculated address and loads into AC
                Byte data = read(proc->memory, address, &cycles);
                proc->cpu->AC = data;
                proc->processor->ZF = (proc->cpu->AC == 0);
                proc->processor->NF = (proc->cpu->AC & 0b10000000) > 0;
                break;
            }
            // LDS Absolute X
            case INS_LDA_AX: {
                // fetchs byte to be low byte of an address
                Byte addressLo = fetch(proc->memory, proc->cpu, &cycles);
                // fetchs byte to be high byte of an address
                Byte addressHi = fetch(proc->memory, proc->cpu, &cycles);
                // combines bytes into a 2 byte address
                __uint16_t address = combineBytes(addressHi, addressLo);
                // adds address and Index Register X together
                address = addToAddress(address, proc->cpu->IX, &cycles);
                // checks if the addition crossed a page, which uses an extra cycle
                crossedPage(address, proc->cpu->IX, &cycles);
                // reads data from the calculated address and loads into AC
                Byte data = read(proc->memory, address, &cycles);
                proc->cpu->AC = data;
                proc->processor->ZF = (proc->cpu->AC == 0);
                proc->processor->NF = (proc->cpu->AC & 0b10000000) > 0;
                break;
            }
            // LDA Absolute Y
            // same as above, but with Index Register Y instead of X
            case INS_LDA_AY: {
                Byte addressLo = fetch(proc->memory, proc->cpu, &cycles);
                Byte addressHi = fetch(proc->memory, proc->cpu, &cycles);
                __uint16_t address = combineBytes(addressHi, addressLo);
                address = addToAddress(address, proc->cpu->IY, &cycles);
                crossedPage(address, proc->cpu->IY, &cycles);
                Byte data = read(proc->memory, address, &cycles);
                proc->cpu->AC = data;
                proc->processor->ZF = (proc->cpu->AC == 0);
                proc->processor->NF = (proc->cpu->AC & 0b10000000) > 0;
                break;
            }
            // LDA Indirect X
            case INS_LDA_IX: {
                // fetchs byte from memory to be low byte of a zero page address
                Byte zpAddress = fetch(proc->memory, proc->cpu, &cycles);
                // adds Index Register X to the address and uses wraparound to keep it on the zero page
                zpAddress = addToByte(zpAddress, proc->cpu->IX, &cycles);
                // reads byte to be low byte of address from zero page
                Byte addressLo = read(proc->memory, (__uint16_t)zpAddress, &cycles);
                // reads next byte to be high byte of address from zero page
                Byte addressHi = read(proc->memory, (__uint16_t)((Byte)(zpAddress + 1)), &cycles);
                // combines bytes to find address
                __uint16_t address = combineBytes(addressHi, addressLo);
                // reads data from calculated address and stores in AC
                Byte data = read(proc->memory, address, &cycles);
                proc->cpu->AC = data;
                proc->processor->ZF = (proc->cpu->AC == 0);
                proc->processor->NF = (proc->cpu->AC & 0b10000000) > 0;
                break;
            }
            // LDA Indirect Y
            case INS_LDA_IY: {
                // fetchs byte to be low byte of a zero page address
                Byte zpByte = fetch(proc->memory, proc->cpu, &cycles);
                // adds Index Register Y to byte WITHOUT wraparound
                __uint16_t zpAddress = addToAddress((__uint16_t)zpByte, proc->cpu->IY, &cycles);
                // checks if either new address or next address has crossed page, if so uses an extra cycle
                crossedPage(zpAddress, proc->cpu->IY + 0, &cycles);
                crossedPage(zpAddress, proc->cpu->IY + 1, &cycles);
                // reads byte to be low byte of address
                Byte addressLo = read(proc->memory, zpAddress, &cycles);
                // reads byte to be high byte of address
                Byte addressHi = read(proc->memory, zpAddress + 1, &cycles);
                // combines bytes into readable address
                __uint16_t address = combineBytes(addressHi, addressLo);
                // reads data from calculated address and stores in AC
                Byte data = read(proc->memory, address, &cycles);
                proc->cpu->AC = data;
                proc->processor->ZF = (proc->cpu->AC == 0);
                proc->processor->NF = (proc->cpu->AC & 0b10000000) > 0;
                break;
            }
        }
    }

    if (cycles < 0) {
        printf("Note: Executed more cycles than requested.\n");
    }
}