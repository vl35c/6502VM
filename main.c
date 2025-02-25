#include "architecture.h"
#include "debug.h"

int main(void) {
    p6502 proc;
    init6502(&proc);

    displayCPUStatus(proc);
    displayProcessorStatus(proc);

    free6502(&proc);

    return 0;
}