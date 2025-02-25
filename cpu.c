#include <stdio.h>

#include "cpu.h"

static Byte fetch(Memory* memory, CPU* cpu, int* cycles) {
    Byte byte = memory->data[cpu->PC];
    cpu->PC++;
    --*cycles;

    return byte;
}

static Byte read(Memory* memory, __uint16_t address, int* cycles) {
    Byte byte = memory->data[address];
    --*cycles;

    return byte;
}

static Byte addToByte(CPU* cpu, Byte address, Byte indexRegister, int* cycles) {
    __uint16_t bytes = address + indexRegister;
    --*cycles;
    return (Byte)bytes;
}

static __uint16_t addToAddress(CPU* cpu, __uint16_t address, Byte indexRegister, int* cycles) {
    if ((Byte)(address + indexRegister) < (Byte)address) {
        --*cycles;
    }
    return address + indexRegister;
}

static __uint16_t combineBytes(Byte hi, Byte lo) {
    return (__uint16_t)((hi << 8) + lo);
}

#define INS_LDA_IM 0xA9
#define INS_LDA_ZP 0xA5
#define INS_LDA_ZX 0xB5
#define INS_LDA_AB 0xAD
#define INS_LDA_AX 0xBD
#define INS_LDA_AY 0xB9

void execute(p6502* proc, int cycles) {
    while (cycles > 0) {
        Byte instruction = fetch(proc->memory, proc->cpu, &cycles);

        switch (instruction) {
            case INS_LDA_IM: {
                Byte data = fetch(proc->memory, proc->cpu, &cycles);
                proc->cpu->AC = data;
                proc->processor->ZF = (proc->cpu->AC == 0);
                proc->processor->NF = (proc->cpu->AC & 0b10000000) > 0;
                break;
            }
            case INS_LDA_ZP: {
                Byte address = fetch(proc->memory, proc->cpu, &cycles);
                Byte data = read(proc->memory, (__uint16_t)address, &cycles);
                proc->cpu->AC = data;
                proc->processor->ZF = (proc->cpu->AC == 0);
                proc->processor->NF = (proc->cpu->AC & 0b10000000) > 0;
                break;
            }
            case INS_LDA_ZX: {
                Byte address = fetch(proc->memory, proc->cpu, &cycles);
                address = addToByte(proc->cpu, address, proc->cpu->IX, &cycles);
                Byte data = read(proc->memory, (__uint16_t)address, &cycles);
                proc->cpu->AC = data;
                proc->processor->ZF = (proc->cpu->AC == 0);
                proc->processor->NF = (proc->cpu->AC & 0b10000000) > 0;
                break;
            }
            case INS_LDA_AB: {
                Byte addressLo = fetch(proc->memory, proc->cpu, &cycles);
                Byte addressHi = fetch(proc->memory, proc->cpu, &cycles);
                __uint16_t address = combineBytes(addressHi, addressLo);
                Byte data = read(proc->memory, address, &cycles);
                proc->cpu->AC = data;
                proc->processor->ZF = (proc->cpu->AC == 0);
                proc->processor->NF = (proc->cpu->AC & 0b10000000) > 0;
                break;
            }
            case INS_LDA_AX: {
                Byte addressLo = fetch(proc->memory, proc->cpu, &cycles);
                Byte addressHi = fetch(proc->memory, proc->cpu, &cycles);
                __uint16_t address = combineBytes(addressHi, addressLo);
                address = addToAddress(proc->cpu, address, proc->cpu->IX, &cycles);
                Byte data = read(proc->memory, address, &cycles);
                proc->cpu->AC = data;
                proc->processor->ZF = (proc->cpu->AC == 0);
                proc->processor->NF = (proc->cpu->AC & 0b10000000) > 0;
                break;
            }
            case INS_LDA_AY: {
                Byte addressLo = fetch(proc->memory, proc->cpu, &cycles);
                Byte addressHi = fetch(proc->memory, proc->cpu, &cycles);
                __uint16_t address = combineBytes(addressHi, addressLo);
                address = addToAddress(proc->cpu, address, proc->cpu->IY, &cycles);
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