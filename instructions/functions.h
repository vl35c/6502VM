#ifndef functions_h
#define functions_h

#include "../architecture.h"
#include "../debug.h"

Byte fetch(Memory* memory, CPU* cpu, int* cycles);
Byte read(Memory* memory, Word address, int* cycles);

Byte addToByte(Byte address, Byte indexRegister, int* cycles);
Word addToAddress(Word address, Byte indexRegister);
void crossedPage(Word address, Byte indexRegister, int* cycles);

Word combineBytes(Byte hi, Byte lo);

void write(Memory* memory, Word address, Byte data, int* cycles);
void copyByte(Byte src, Byte* dest, const char* destName);

void pushStack(Memory* memory, CPU* cpu, Byte data, int* cycles);
Byte pullStack(Memory* memory, CPU* cpu, int* cycles);
Byte flagsToByte(Processor p);
void byteToFlags(Byte data, Processor* p);

Byte and(Byte byte1, Byte byte2);
Byte eor(Byte byte1, Byte byte2);
Byte ora(Byte byte1, Byte byte2);

Word add(Byte byte, p6502* proc);
Word sub(Byte byte, p6502* proc);

#endif