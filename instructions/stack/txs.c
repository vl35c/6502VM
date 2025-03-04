#include "../instructions.h"

#define INS_TXS_IP 0x9A

void TXS(Byte instruction, p6502* proc, int* cycles) {
    switch (instruction) {
        case INS_TXS_IP: {
            Byte data = proc->cpu->IX;
            Byte addressLo = proc->cpu->SP;
            uint16_t address = combineBytes(0x01, addressLo);
            write(proc->memory, address, data, cycles);
            break;
        }
    }
}