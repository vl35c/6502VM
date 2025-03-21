#include <memory.h>
#include <stdarg.h>
#include <stdio.h>

#include "debug.h"

bool instructionInProgress = false;

void displayProcessorStatus(p6502 proc) {
    printf("\n________\n");
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
static Byte getByte(uint16_t bytes, int offset) {
    return (Byte)(bytes >> (8 * offset));
}

void displayCPUStatus(p6502 proc) {
    Byte pcByte1 = getByte(proc.cpu->PC, 0);
    Byte pcByte2 = getByte(proc.cpu->PC, 1);
    printf("\nPC | [0x%02x] [0x%02x]\n", pcByte1, pcByte2);
    printf("SP | [0x%02x]\n", proc.cpu->SP);
    printf("AC | [0x%02x] (%d)\n", proc.cpu->AC, proc.cpu->AC);
    printf("IX | [0x%02x] (%d)\n", proc.cpu->IX, proc.cpu->IX);
    printf("IY | [0x%02x] (%d)\n", proc.cpu->IY, proc.cpu->IY);
}

void writeByte(Memory* memory, uint16_t address, Byte data) {
    memory->data[address] = data;
}

void readByte(Memory* memory, uint16_t address) {
    printf("read_byte : 0x%04x -> 0x%02x\n", address, memory->data[address]);
}

static void fetchMemory(const char* code, Memory* memory, CPU* cpu) {
    printf("%-12s 0x%04x -> 0x%02x\n  PC -> 0x%04x\n", code, cpu->PC, memory->data[cpu->PC], cpu->PC + 1);
}

static void readMemory(const char* code, Memory* memory, uint16_t address) {
    printf("%-12s 0x%04x -> 0x%02x\n", code, address, memory->data[address]);
}

static void writeMemory(const char* code, Byte data, uint16_t address) {
    printf("%-12s 0x%04x -> 0x%02x\n", code, address, data);
}

static void addByte(const char* code, Byte byte1, Byte byte2) {
    printf("%-12s 0x%02x +  0x%02x = 0x%02x (ZP)\n", code, byte1, byte2, byte1 + byte2);
}

static void addAddress(const char* code, Byte add, uint16_t address) {
    printf("%-12s 0x%04x +  0x%02x = 0x%04x\n", code, address, add, address + add);
}

static void combineBytes(const char* code, Byte byte2, Byte byte1) {
    printf("%-12s 0x%02x, 0x%02x -> 0x%04x\n", code, byte1, byte2, (byte1 << 8) + byte2);
}

static void copyBytes(const char* code, const char* dest, Byte byte1) {
    printf("%-12s 0x%02x -> %s\n", code, byte1, dest);
}

static void pushStack(const char* code, Byte data, Byte stackPointer) {
    printf("%-12s stack[0x%02x] = 0x%02x\n  SP -> 0x%02x\n", code, stackPointer, data, stackPointer - 1);
}

static void and(const char* code, Byte byte2, Byte byte1) {
    printf("%-12s 0x%02x & 0x%02x = 0x%02x\n", code, byte1, byte2, byte1 & byte2);
}

static void eor(const char* code, Byte byte2, Byte byte1) {
    printf("%-12s 0x%02x ^ 0x%02x = 0x%02x\n", code, byte1, byte2, byte1 ^ byte2);
}

static void ora(const char* code, Byte byte2, Byte byte1) {
    printf("%-12s 0x%02x | 0x%02x = 0x%02x\n", code, byte1, byte2, byte1 | byte2);
}

void traceInstructionStart(const char* name) {
    if (instructionInProgress) { return; }
    instructionInProgress = true;

#ifdef DEBUG_TRACE
    printf("-=-=-= START: %s =-=-=-\n", name);
#endif
}

void traceInstructionEnd(const char* name) {
    instructionInProgress = false;

#ifdef DEBUG_TRACE
    printf("-=-=-= END: %s =-=-=-\n", name);
#endif
}

void traceProcessor(TraceCode code, ...) {
    switch (code) {
        case TRACE_FETCH: fetchMemory("FETCH", proc.memory, proc.cpu); break;
        case TRACE_READ: {
            va_list args;
            va_start(args, code);
            readMemory("READ", proc.memory, va_arg(args, int));
            va_end(args);
            break;
        }
        case TRACE_WRITE: {
            va_list args;
            va_start(args, code);
            writeMemory("WRITE", va_arg(args, int), va_arg(args, int));
            va_end(args);
            break;
        }
        case TRACE_ADD_BYTE: {
            va_list args;
            va_start(args, code);
            addByte("ADD", va_arg(args, int), va_arg(args, int));
            va_end(args);
            break;
        }
        case TRACE_ADD_ADDRESS: {
            va_list args;
            va_start(args, code);
            addAddress("ADD", va_arg(args, int), va_arg(args, int));
            va_end(args);
            break;
        }
        case TRACE_COMBINE: {
            va_list args;
            va_start(args, code);
            combineBytes("COMBINE", va_arg(args, int), va_arg(args, int));
            va_end(args);
            break;
        }
        case TRACE_COPY: {
            va_list args;
            va_start(args, code);
            copyBytes("COPY", va_arg(args, char*), va_arg(args, int));
            va_end(args);
            break;
        }
        case TRACE_PUSH: {
            va_list args;
            va_start(args, code);
            pushStack("PUSH STACK", va_arg(args, int), va_arg(args, int));
            va_end(args);
            break;
        }
        case TRACE_PULL: {
            printf("PULL STACK:\n");
            break;
        }
        case TRACE_AND: {
            va_list args;
            va_start(args, code);
            and("AND", va_arg(args, int), va_arg(args, int));
            va_end(args);
            break;
        }
        case TRACE_EOR: {
            va_list args;
            va_start(args, code);
            eor("XOR", va_arg(args, int), va_arg(args, int));
            va_end(args);
            break;
        }
        case TRACE_ORA: {
            va_list args;
            va_start(args, code);
            ora("OR", va_arg(args, int), va_arg(args, int));
            va_end(args);
            break;
        }
        default:
            return;
    }
}