#include "../instructions.h"

#define INS_STX_IP 0xBA

void TSX(Byte instruction, p6502* proc, int* cycles) {
    switch (instruction) {
        case INS_STX_IP: {
            Byte addressLo = proc->cpu->SP;
            uint16_t address = combineBytes(0x01, addressLo);
            Byte data = read(proc->memory, address, cycles);
            proc->cpu->IX = data;
            proc->processor->ZF = (proc->cpu->IX == 0);
            proc->processor->NF = (proc->cpu->IX & 0b10000000) > 0;
            break;
        }
    }
}