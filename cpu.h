#ifndef cpu_h
#define cpu_h

#include "architecture.h"
#include "common.h"
#include "debug.h"
#include "instructions/lda.h"

void execute(p6502* proc, int cycles);

#endif