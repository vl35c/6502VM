#ifndef lda_h
#define lda_h

#include "../common.h"
#include "../architecture.h"
#include "functions.h"

void LDA(Byte instruction, p6502* proc, int* cycles);
void LDX(Byte instruction, p6502* proc, int* cycles);
void LDY(Byte instruction, p6502* proc, int* cycles);

void STA(Byte instruction, p6502* proc, int* cycles);
void STX(Byte instruction, p6502* proc, int* cycles);
void STY(Byte instruction, p6502* proc, int* cycles);

void TAX(Byte instruction, p6502* proc, int* cycles);
void TAY(Byte instruction, p6502* proc, int* cycles);
void TXA(Byte instruction, p6502* proc, int* cycles);
void TYA(Byte instruction, p6502* proc, int* cycles);

void TSX(Byte instruction, p6502* proc, int* cycles);
void TXS(Byte instruction, p6502* proc, int* cycles);
void PHA(Byte instruction, p6502* proc, int* cycles);
void PHP(Byte instruction, p6502* proc, int* cycles);
void PLA(Byte instruction, p6502* proc, int* cycles);
void PLP(Byte instruction, p6502* proc, int* cycles);

void AND(Byte instruction, p6502* proc, int* cycles);

#endif