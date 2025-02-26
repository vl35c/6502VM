#include <stdio.h>

#include "cpu.h"

// opcodes
//lda
#define INS_LDA_IM 0xA9
#define INS_LDA_ZP 0xA5
#define INS_LDA_ZX 0xB5
#define INS_LDA_AB 0xAD
#define INS_LDA_AX 0xBD
#define INS_LDA_AY 0xB9
#define INS_LDA_IX 0xA1
#define INS_LDA_IY 0xB1

#define INS_LDX_IM 0xA2
#define INS_LDX_ZP 0xA6
#define INS_LDX_ZY 0xB6
#define INS_LDX_AB 0xAE
#define INS_LDX_AY 0xBE

// main loop
void execute(p6502* proc, int cycles) {
    while (cycles > 0) {
        // gets opcode from memory wherever program counter is pointing
        Byte instruction = fetch(proc->memory, proc->cpu, &cycles);
        
        switch (instruction) {
            case INS_LDA_IM:
            case INS_LDA_ZP:
            case INS_LDA_ZX:
            case INS_LDA_AB:
            case INS_LDA_AX:
            case INS_LDA_AY:
            case INS_LDA_IX:
            case INS_LDA_IY:
                LDA(instruction, proc, &cycles);
            case INS_LDX_IM:
            case INS_LDX_ZP:
            case INS_LDX_ZY:
            case INS_LDX_AB:
            case INS_LDX_AY:
                LDX(instruction, proc, &cycles);
        }
    }

    if (cycles < 0) {
        printf("Note: Executed more cycles than requested.\n");
    }
}