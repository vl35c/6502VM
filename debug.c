#include <memory.h>
#include <stdio.h>

#include "debug.h"

void displayProcessorStatus(p6502 proc) {
    printf("________\n");
    printf("|CF | %d|\n", proc.processor->CF);
    printf("|ZF | %d|\n", proc.processor->ZF);
    printf("|ID | %d|\n", proc.processor->ID);
    printf("|DM | %d|\n", proc.processor->DM);
    printf("|BC | %d|\n", proc.processor->BC);
    printf("|OF | %d|\n", proc.processor->OF);
    printf("|NF | %d|\n", proc.processor->NF);
    printf("‾‾‾‾‾‾‾‾\n");
}

// little endian, so offset of 1 to [0x1234] gives [0x12]
static Byte getByte(__uint16_t bytes, int offset) {
    return (Byte)(bytes >> (8 * offset));
}

void displayCPUStatus(p6502 proc) {
    Byte pcByte1 = getByte(proc.cpu->PC, 0);
    Byte pcByte2 = getByte(proc.cpu->PC, 1);
    printf("PC | [0x%02x] [0x%02x]\n", pcByte1, pcByte2);
    printf("SP | [0x%02x]\n", proc.cpu->SP);
    printf("AC | [0x%02x] (%d)\n", proc.cpu->AC, proc.cpu->AC);
    printf("IX | [0x%02x]\n", proc.cpu->IX);
    printf("IY | [0x%02x]\n", proc.cpu->IY);
}

void writeByte(Memory* memory, __uint16_t address, Byte data) {
    memory->data[address] = data;
}