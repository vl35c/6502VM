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
//STY
#define INS_STY_ZP 0x84
#define INS_STY_ZX 0x94
#define INS_STY_AB 0x8C
// Transfers
#define INS_TAX_IP 0xAA
#define INS_TAY_IP 0xA8
#define INS_TXA_IP 0x8A
#define INS_TYA_IP 0x98
// Stack Operations
#define INS_TSX_IP 0xBA
#define INS_TXS_IP 0x9A
#define INS_PHA_IP 0x48
#define INS_PHP_IP 0x08
#define INS_PLA_IP 0x68
#define INS_PLP_IP 0x28
// AND
#define INS_AND_IM 0x29
#define INS_AND_ZP 0x25
#define INS_AND_ZX 0x35
#define INS_AND_AB 0x2D
#define INS_AND_AX 0x3D
#define INS_AND_AY 0x39
#define INS_AND_IX 0x21
#define INS_AND_IY 0x31
// EOR
#define INS_EOR_IM 0x49
#define INS_EOR_ZP 0x45
#define INS_EOR_ZX 0x55
#define INS_EOR_AB 0x4D
#define INS_EOR_AX 0x5D
#define INS_EOR_AY 0x59
#define INS_EOR_IX 0x41
#define INS_EOR_IY 0x51
// ORA
#define INS_ORA_IM 0x09
#define INS_ORA_ZP 0x05
#define INS_ORA_ZX 0x15
#define INS_ORA_AB 0x0D
#define INS_ORA_AX 0x1D
#define INS_ORA_AY 0x19
#define INS_ORA_IX 0x01
#define INS_ORA_IY 0x11
// BIT
#define INS_BIT_ZP 0x24
#define INS_BIT_AB 0x2C

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
            case INS_STY_ZP: traceInstructionStart("STY - Zero Page");
            case INS_STY_ZX: traceInstructionStart("STY - Zero Page X");
            case INS_STY_AB: traceInstructionStart("STY - Absolute");
                STY(instruction, proc, &cycles);
                traceInstructionEnd("STY");
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
            case INS_TSX_IP: traceInstructionStart("TSX - Implicit");
                TSX(instruction, proc, &cycles);
                traceInstructionEnd("TSX");
                break;
            case INS_TXS_IP: traceInstructionStart("TXS - Implicit");
                TXS(instruction, proc, &cycles);
                traceInstructionEnd("TXS");
                break;
            case INS_PHA_IP: traceInstructionStart("PHA - Implicit");
                PHA(instruction, proc, &cycles);
                traceInstructionEnd("PHA");
                break;
            case INS_PHP_IP: traceInstructionStart("PHP - Implicit");
                PHP(instruction, proc, &cycles);
                traceInstructionEnd("PHP");
                break;
            case INS_PLA_IP: traceInstructionStart("PLA - Implicit");
                PLA(instruction, proc, &cycles);
                traceInstructionEnd("PLA");
                break;
            case INS_PLP_IP: traceInstructionStart("PLP - Implicit");
                PLP(instruction, proc, &cycles);
                traceInstructionEnd("PLP");
                break;
            case INS_AND_IM: traceInstructionStart("AND - Immediate");
            case INS_AND_ZP: traceInstructionStart("AND - Zero Page");
            case INS_AND_ZX: traceInstructionStart("AND - Zero Page X");
            case INS_AND_AB: traceInstructionStart("AND - Absolute");
            case INS_AND_AX: traceInstructionStart("AND - Absolute X");
            case INS_AND_AY: traceInstructionStart("AND - Absolute Y");
            case INS_AND_IX: traceInstructionStart("AND - Indirect X");
            case INS_AND_IY: traceInstructionStart("AND - Absolute Y");
                AND(instruction, proc, &cycles);
                traceInstructionEnd("AND");
                break;
            case INS_EOR_IM: traceInstructionStart("EOR - Immediate");
            case INS_EOR_ZP: traceInstructionStart("EOR - Zero Page");
            case INS_EOR_ZX: traceInstructionStart("EOR - Zero Page X");
            case INS_EOR_AB: traceInstructionStart("EOR - Absolute");
            case INS_EOR_AX: traceInstructionStart("EOR - Absolute X");
            case INS_EOR_AY: traceInstructionStart("EOR - Absolute Y");
            case INS_EOR_IX: traceInstructionStart("EOR - Indirect X");
            case INS_EOR_IY: traceInstructionStart("EOR - Indirect Y");
                EOR(instruction, proc, &cycles);
                traceInstructionEnd("EOR");
                break;
            case INS_ORA_IM: traceInstructionStart("ORA - Immediate");
            case INS_ORA_ZP: traceInstructionStart("ORA - Zero Page");
            case INS_ORA_ZX: traceInstructionStart("ORA - Zero Page X");
            case INS_ORA_AB: traceInstructionStart("ORA - Absolute");
            case INS_ORA_AX: traceInstructionStart("ORA - Absolute X");
            case INS_ORA_AY: traceInstructionStart("ORA - Absolute Y");
            case INS_ORA_IX: traceInstructionStart("ORA - Indirect X");
            case INS_ORA_IY: traceInstructionStart("ORA - Indirect Y");
                ORA(instruction, proc, &cycles);
                traceInstructionEnd("ORA");
                break;
            case INS_BIT_ZP: traceInstructionStart("BIT - Zero Page");
            case INS_BIT_AB: traceInstructionStart("BIT - Absolute");
                BIT(instruction, proc, &cycles);
                traceInstructionEnd("BIT");
                break;
            default:
                printf("UNKNOWN OPCODE\n");
        }
    }

    if (cycles < 0) {
        printf("Note: Executed more cycles than requested.\n");
    }
}