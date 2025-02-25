#include "architecture.h"
#include "common.h"
#include "cpu.h"
#include "debug.h"

int main(void) {
    p6502 proc;
    init6502(&proc);

    writeByte(proc.memory, 0xFFFA, 0xB9);
    writeByte(proc.memory, 0xFFFB, 0x34);
    writeByte(proc.memory, 0xFFFC, 0x12);
    writeByte(proc.memory, 0x1333, 0xFF);
    proc.cpu->IY = 0xFF;

    execute(&proc, 5);
    displayCPUStatus(proc);
    displayProcessorStatus(proc);

    free6502(&proc);

    return 0;
}