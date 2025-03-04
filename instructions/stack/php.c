#include "../instructions.h"

#define INS_PHP_IP 0x08

void PHP(Byte instruction, p6502* proc, int* cycles) {
    switch (instruction) {
        case INS_PHP_IP: {
            Byte data = flagsToByte(*proc->processor);
            pushStack(proc->memory, proc->cpu, data, cycles);
            break;
        }
    }
}