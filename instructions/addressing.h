#ifndef addressing_h
#define addressing_h

#include "functions.h"
#include "../common.h"
#include "../architecture.h"

Byte addr_immediate(Memory* memory, CPU* cpu, int* cycles);
Byte addr_zero_page(Memory* memory, CPU* cpu, int* cycles);
Byte addr_zero_page_x(Memory* memory, CPU* cpu, int* cycles);
Byte addr_zero_page_y(Memory* memory, CPU* cpu, int* cycles);
Byte addr_absolute(Memory* memory, CPU* cpu, int* cycles);
Byte addr_absolute_x(Memory* memory, CPU* cpu, int* cycles);
Byte addr_absolute_y(Memory* memory, CPU* cpu, int* cycles);
Byte addr_indirect_x(Memory* memory, CPU* cpu, int* cycles);
Byte addr_indirect_y(Memory* memory, CPU* cpu, int* cycles);

#endif