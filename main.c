#include <stdlib.h>

#include "architecture.h"
#include "common.h"
#include "cpu.h"
#include "debug.h"

p6502 proc;

int main(void) {
    system("clear");
    init6502(&proc);

    writeByte(proc.memory, 0xFFFA, 0x11);
    writeByte(proc.memory, 0xFFFB, 0x34);
    writeByte(proc.memory, 0x0034, 0x34);
    writeByte(proc.memory, 0x0035, 0x12);
    writeByte(proc.memory, 0x1234, 0x45);
    proc.cpu->AC = 0x23;

    execute(&proc, 5);

    displayCPUStatus(proc);
    displayProcessorStatus(proc);

    free6502(&proc);

    return 0;
}