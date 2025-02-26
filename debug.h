#ifndef debug_h
#define debug_h

#include "architecture.h"
#include "common.h"

typedef enum {
    TRACE_FETCH,
    TRACE_READ,
    TRACE_ADD_BYTE,
    TRACE_ADD_ADDRESS,
    TRACE_COMBINE
} TraceCode;

extern p6502 proc;

void displayProcessorStatus(p6502 proc);
void displayCPUStatus(p6502 proc);
void writeByte(Memory* memory, __uint16_t address, Byte data);
void traceProcessor(TraceCode code, ...);

#endif