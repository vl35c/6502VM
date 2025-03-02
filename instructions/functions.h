#ifndef functions_h
#define functions_h

#include "../architecture.h"
#include "../debug.h"

Byte fetch(Memory* memory, CPU* cpu, int* cycles);
Byte read(Memory* memory, uint16_t address, int* cycles);
Byte addToByte(Byte address, Byte indexRegister, int* cycles);
uint16_t addToAddress(uint16_t address, Byte indexRegister);
void crossedPage(uint16_t address, Byte indexRegister, int* cycles);
uint16_t combineBytes(Byte hi, Byte lo);
void write(Memory* memory, uint16_t address, Byte data, int* cycles);

#endif