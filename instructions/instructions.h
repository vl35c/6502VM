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

void TAX(Byte instruction, p6502* proc, int* cycles);
void TAY(Byte instruction, p6502* proc, int* cycles);
void TXA(Byte instruction, p6502* proc, int* cycles);
void TYA(Byte instruction, p6502* proc, int* cycles);

#endif