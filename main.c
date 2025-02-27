#include <stdlib.h>

#include "architecture.h"
#include "common.h"
#include "cpu.h"
#include "debug.h"

p6502 proc;

int main(void) {
    system("clear");
    init6502(&proc);

    writeByte(proc.memory, 0xFFFA, 0x91);
    writeByte(proc.memory, 0xFFFB, 0x00);
    writeByte(proc.memory, 0x0000, 0x34);
    writeByte(proc.memory, 0x0001, 0x12);
    proc.cpu->AC = 0xFF;
    proc.cpu->IY = 0x05;

    execute(&proc, 6);

    readByte(proc.memory, 0x1239);

    displayCPUStatus(proc);
    displayProcessorStatus(proc);

    free6502(&proc);

    return 0;
}