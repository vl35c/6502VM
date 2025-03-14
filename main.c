#include <stdlib.h>

#include "architecture.h"
#include "common.h"
#include "cpu.h"
#include "debug.h"

p6502 proc;

int main(void) {
    system("clear");
    init6502(&proc);

    writeByte(proc.memory, 0xFFFA, 0x2C);
    writeByte(proc.memory, 0xFFFB, 0x34);
    writeByte(proc.memory, 0xFFFC, 0x12);
    writeByte(proc.memory, 0x1234, 0xFF);
    proc.cpu->AC = 0xFF;

    execute(&proc, 4);

    displayCPUStatus(proc);
    displayProcessorStatus(proc);

    free6502(&proc);

    return 0;
}