#include <stdio.h>

#include "cpu.h"

// opcodes
// LDA
#define INS_LDA_IM 0xA9
#define INS_LDA_ZP 0xA5
#define INS_LDA_ZX 0xB5
#define INS_LDA_AB 0xAD
#define INS_LDA_AX 0xBD
#define INS_LDA_AY 0xB9
#define INS_LDA_IX 0xA1
#define INS_LDA_IY 0xB1
// LDX
#define INS_LDX_IM 0xA2
#define INS_LDX_ZP 0xA6
#define INS_LDX_ZY 0xB6
#define INS_LDX_AB 0xAE
#define INS_LDX_AY 0xBE
// LDY
#define INS_LDY_IM 0xA0
#define INS_LDY_ZP 0xA4
#define INS_LDY_ZX 0xB4
#define INS_LDY_AB 0xAC
#define INS_LDY_AX 0xBC
// STA
#define INS_STA_ZP 0x85
#define INS_STA_ZX 0x95
#define INS_STA_AB 0x8D
#define INS_STA_AX 0x9D
#define INS_STA_AY 0x99
#define INS_STA_IX 0x81
#define INS_STA_IY 0x91
// STX
#define INS_STX_ZP 0x86
#define INS_STX_ZY 0x96
#define INS_STX_AB 0x8E
// TAX
#define INS_TAX_IP 0xAA
// TAY
#define INS_TAY_IP 0xA8
// TXA
#define INS_TXA_IP 0x8A
// TYA
#define INS_TYA_IP 0x98


// main loop
void execute(p6502* proc, int cycles) {
    while (cycles > 0) {
        // gets opcode from memory wherever program counter is pointing
        Byte instruction = fetch(proc->memory, proc->cpu, &cycles);
        
        switch (instruction) {
            case INS_LDA_IM: traceInstructionStart("LDA - Immediate");
            case INS_LDA_ZP: traceInstructionStart("LDA - Zero Page");
            case INS_LDA_ZX: traceInstructionStart("LDA - Zero Page X");
            case INS_LDA_AB: traceInstructionStart("LDA - Absolute");
            case INS_LDA_AX: traceInstructionStart("LDA - Absolute X");
            case INS_LDA_AY: traceInstructionStart("LDA - Absolute Y");
            case INS_LDA_IX: traceInstructionStart("LDA - Indirect X");
            case INS_LDA_IY: traceInstructionStart("LDA - Indirect Y");
                LDA(instruction, proc, &cycles);
                traceInstructionEnd("LDA");
                break;
            case INS_LDX_IM: traceInstructionStart("LDX - Immediate");
            case INS_LDX_ZP: traceInstructionStart("LDX - Zero Page");
            case INS_LDX_ZY: traceInstructionStart("LDX - Zero Page Y");
            case INS_LDX_AB: traceInstructionStart("LDX - Absolute");
            case INS_LDX_AY: traceInstructionStart("LDX - Absolute Y");
                LDX(instruction, proc, &cycles);
                traceInstructionEnd("LDX");
                break;
            case INS_LDY_IM: traceInstructionStart("LDY - Immediate");
            case INS_LDY_ZP: traceInstructionStart("LDY - Zero Page");
            case INS_LDY_ZX: traceInstructionStart("LDY - Zero Page X");
            case INS_LDY_AB: traceInstructionStart("LDY - Absolute");
            case INS_LDY_AX: traceInstructionStart("LDY - Absolute X");
                LDY(instruction, proc, &cycles);
                traceInstructionEnd("LDY");
                break;
            case INS_STA_ZP: traceInstructionStart("STA - Zero Page");
            case INS_STA_ZX: traceInstructionStart("STA - Zero Page X");
            case INS_STA_AB: traceInstructionStart("STA - Absolute");
            case INS_STA_AX: traceInstructionStart("STA - Absolute X"); 
            case INS_STA_AY: traceInstructionStart("STA - Absolute Y");
            case INS_STA_IX: traceInstructionStart("STA - Indirect X");
            case INS_STA_IY: traceInstructionStart("STA - Indirect Y");
                STA(instruction, proc, &cycles);
                traceInstructionEnd("STA");
                break;
            case INS_STX_ZP: traceInstructionStart("STX - Zero Page");
            case INS_STX_ZY: traceInstructionStart("STX - Zero Page Y");
            case INS_STX_AB: traceInstructionStart("STX - Absolute");
                STX(instruction, proc, &cycles);
                traceInstructionEnd("STX");
                break;
            case INS_TAX_IP: traceInstructionStart("TAX - Implicit");
                TAX(instruction, proc, &cycles);
                traceInstructionEnd("TAX");
                break;
            case INS_TAY_IP: traceInstructionStart("TAY - Implicit");
                TAY(instruction, proc, &cycles);
                traceInstructionEnd("TAY");
                break;
            case INS_TXA_IP: traceInstructionStart("TXA - Implicit");
                TXA(instruction, proc, &cycles);
                traceInstructionEnd("TXA");
                break;
            case INS_TYA_IP: traceInstructionStart("TYA - Implicit");
                TYA(instruction, proc, &cycles);
                traceInstructionEnd("TYA");

                break;
        }
    }

    if (cycles < 0) {
        printf("Note: Executed more cycles than requested.\n");
    }
}