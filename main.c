#include <stdlib.h>

#include "architecture.h"
#include "common.h"
#include "cpu.h"
#include "debug.h"

p6502 proc;

int main(void) {
    system("clear");
    init6502(&proc);

    writeByte(proc.memory, 0xFFFC, 0xE6);
    writeByte(proc.memory, 0xFFFD, 0x00);
    writeByte(proc.memory, 0x0000, 0x01);
    writeByte(proc.memory, 0xFFFE, 0xA5);
    writeByte(proc.memory, 0xFFFF, 0x00);

    execute(&proc, 6);

    displayCPUStatus(proc);
    displayProcessorStatus(proc);

    free6502(&proc);

    return 0;
}