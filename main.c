#include "architecture.h"
#include "common.h"
#include "cpu.h"
#include "debug.h"

int main(void) {
    p6502 proc;
    init6502(&proc);

    execute(&proc, 2);
    displayCPUStatus(proc);
    displayProcessorStatus(proc);

    free6502(&proc);

    return 0;
}