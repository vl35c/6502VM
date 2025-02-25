#ifndef debug_h
#define debug_h

#include "architecture.h"
#include "common.h"

void displayProcessorStatus(p6502 proc);
void displayCPUStatus(p6502 proc);
void writeByte(Memory* memory, __uint16_t address, Byte data);

#endif