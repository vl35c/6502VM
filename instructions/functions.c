#include "functions.h"

// fetch retrieves byte from memory and increases program counter
Byte fetch(Memory* memory, CPU* cpu, int* cycles) {
#ifdef DEBUG_TRACE
    traceProcessor(TRACE_FETCH);
#endif
    Byte byte = memory->data[cpu->PC];
    cpu->PC++;
    --*cycles;

    return byte;
}

// read retrieves byte from memory without increasing program counter
Byte read(Memory* memory, uint16_t address, int* cycles) {
#ifdef DEBUG_TRACE
    traceProcessor(TRACE_READ, address);
#endif
    Byte byte = memory->data[address];
    --*cycles;

    return byte;
}

// addToByte takes an address and a register and combines the two, constraining the result to a uint8
Byte addToByte(Byte address, Byte indexRegister, int* cycles) {
#ifdef DEBUG_TRACE
    traceProcessor(TRACE_ADD_BYTE, address, indexRegister);
#endif
    uint16_t bytes = address + indexRegister;
    --*cycles;
    return (Byte)bytes;
}

// addToAddress take an address and a register and combines the two, constraining the result to a uint16
uint16_t addToAddress(uint16_t address, Byte indexRegister) {
#ifdef DEBUG_TRACE
    traceProcessor(TRACE_ADD_ADDRESS, address, indexRegister);
#endif
    return address + indexRegister;
}

// crossedPage checks if an address and register when combined change the page, i.e. the first byte of an address [0x!!]
void crossedPage(uint16_t address, Byte indexRegister, int* cycles) {
    if ((Byte)(address + indexRegister) < (Byte)address) {
        --*cycles;
    }
}

// combine bytes takes two bytes and returns them as an address (uint16)
uint16_t combineBytes(Byte hi, Byte lo) {
#ifdef DEBUG_TRACE
    traceProcessor(TRACE_COMBINE, hi, lo);
#endif
    return (uint16_t)((hi << 8) + lo);
}

void write(Memory* memory, uint16_t address, Byte data, int* cycles) {
#ifdef DEBUG_TRACE
    traceProcessor(TRACE_WRITE, address, data);
#endif
    memory->data[address] = data;
    --*cycles;
}

void copyByte(Byte src, Byte dest) {
#ifdef DEBUG_TRACE
    traceProcessor(TRACE_COPY, src, "cpu->IX");
#endif
}