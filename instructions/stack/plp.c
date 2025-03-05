#include "../instructions.h"

#define INS_PLP_IP 0x28

void PLP(Byte instruction, p6502* proc, int* cycles) {
    switch (instruction) {
        case INS_PLP_IP: {
            proc->cpu->SP++;
            Byte addressLo = proc->cpu->SP;
            uint16_t address = combineBytes(0x01, addressLo);
            Byte data = read(proc->memory, address, cycles);
            byteToFlags(data, proc->processor);
            write(proc->memory, address, 0x00, cycles);
            --*cycles;
            break;
        }
    }
}