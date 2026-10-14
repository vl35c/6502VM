#include "../instructions.h"

void PHA(Byte instruction, p6502* proc, int* cycles) {
    switch (instruction) {
        case INS_PHA_IP: {
            Byte data = proc->cpu->AC;
            pushStack(proc->memory, proc->cpu, data, cycles);
            break;
        }
    }
}