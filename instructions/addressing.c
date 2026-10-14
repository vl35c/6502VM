#include "addressing.h"

Byte addr_immediate(Memory* memory, CPU* cpu, int* cycles) {
    // immediate fetches next byte as data
    return fetch(memory, cpu, cycles);
}

Byte addr_zero_page(Memory* memory, CPU* cpu, int* cycles) {
    // zero page addressing takes the next byte and uses that as the least significant byte
    // {00 -> 0x0000, ..., FF -> 0x00FF}
    Byte zpAddress = fetch(memory, cpu, cycles);
    return read(memory, (Word)zpAddress, cycles); // cast to word to pad 0s
}

Byte addr_zero_page_x(Memory* memory, CPU* cpu, int* cycles) {
    // zero page addressing with IX register added
    // wraps around -> 0xFF + 0x01 = 0x00 -> 0x0000
    Byte zpAddress = fetch(memory, cpu, cycles);
    Byte address = addToByte(zpAddress, cpu->IX, cycles);
    return read(memory, (Word)address, cycles);
}

Byte addr_zero_page_y(Memory* memory, CPU* cpu, int* cycles) {
    // zero page addressing with IY register added
    // no wrap around !
    Byte zpAddress = fetch(memory, cpu, cycles);
    Byte address = addToAddress(zpAddress, cpu->IY);
    return read(memory, (Word)address, cycles);
}

static Word _absolute(Memory* memory, CPU* cpu, int* cycles) {
    Byte addressLo = fetch(memory, cpu, cycles);
    Byte addressHi = fetch(memory, cpu, cycles);
    return combineBytes(addressHi, addressLo);
}

Byte addr_absolute(Memory* memory, CPU* cpu, int* cycles) {
    // takes 2 bytes and combines them for address
    // low byte first -> 0x34, 0x12 -> 0x1234
    Word address = _absolute(memory, cpu, cycles);
    return read(memory, address, cycles);
}

Byte addr_absolute_x(Memory* memory, CPU* cpu, int* cycles) {
    Word address = _absolute(memory, cpu, cycles);
    address = addToAddress(address, cpu->IX);
    crossedPage(address, cpu->IX, cycles);  // page crossed = extra cycle
    return read(memory, address, cycles);
}

Byte addr_absolute_y(Memory* memory, CPU* cpu, int* cycles) {
    Word address = _absolute(memory, cpu, cycles);
    address = addToAddress(address, cpu->IY);
    crossedPage(address, cpu->IY, cycles);  // page crossed = extra cycle
    return read(memory, address, cycles);
}

Byte addr_indirect_x(Memory* memory, CPU* cpu, int* cycles) {
    Byte zpAddress = fetch(memory, cpu, cycles);
    zpAddress = addToByte(zpAddress, cpu->IX, cycles);
    Byte addressLo = read(memory, (Word)((Byte)(zpAddress + 0)), cycles);
    Byte addressHi = read(memory, (Word)((Byte)(zpAddress + 1)), cycles);
    Word address = combineBytes(addressHi, addressLo);
    return read(memory, address, cycles);
}

Byte addr_indirect_y(Memory* memory, CPU* cpu, int* cycles) {
    Byte zpAddress = fetch(memory, cpu, cycles);
    Byte addressLo = read(memory, (Word)((Byte)(zpAddress + 0)), cycles);
    Byte addressHi = read(memory, (Word)((Byte)(zpAddress + 1)), cycles);
    Word address = combineBytes(addressHi, addressLo);
    address = addToAddress(address, cpu->IY);
    crossedPage(address, cpu->IY, cycles);  // page crossed = extra cycle
    return read(memory, address, cycles);
}