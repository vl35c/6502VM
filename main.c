#include "architecture.h"
#include "common.h"
#include "cpu.h"
#include "debug.h"

p6502 proc;

int main(void) {
    init6502(&proc);

    writeByte(proc.memory, 0xFFFA, 0xA1);
    writeByte(proc.memory, 0xFFFB, 0x01);
    writeByte(proc.memory, 0x0000, 0x34);
    writeByte(proc.memory, 0x0001, 0x12);
    writeByte(proc.memory, 0x1234, 0xFF);
    proc.cpu->IX = 0xFF;

    execute(&proc, 6);
    displayCPUStatus(proc);
    displayProcessorStatus(proc);

    free6502(&proc);

    return 0;
}