#include <stdlib.h>

#include "architecture.h"
#include "common.h"
#include "cpu.h"
#include "debug.h"

p6502 proc;

int main(void) {
    system("clear");
    init6502(&proc);

    writeByte(proc.memory, 0xFFFC, 0xC5);
    writeByte(proc.memory, 0xFFFD, 0x00);
    writeByte(proc.memory, 0x0000, 0xFF);
    proc.cpu->AC = 0xFF;

    execute(&proc, 2);

    displayCPUStatus(proc);
    displayProcessorStatus(proc);

    free6502(&proc);

    return 0;
}