#ifndef debug_h
#define debug_h

#include <stdbool.h>

#include "architecture.h"
#include "common.h"

typedef enum {
    TRACE_FETCH,
    TRACE_READ,
    TRACE_WRITE,
    TRACE_ADD_BYTE,
    TRACE_ADD_ADDRESS,
    TRACE_COMBINE,
    TRACE_COPY,
    TRACE_PUSH
} TraceCode;

extern p6502 proc;

void displayProcessorStatus(p6502 proc);
void displayCPUStatus(p6502 proc);
void writeByte(Memory* memory, uint16_t address, Byte data);
void readByte(Memory* memory, uint16_t address);
void traceInstructionStart(const char* name);
void traceInstructionEnd(const char* name);
void traceProcessor(TraceCode code, ...);

#endif