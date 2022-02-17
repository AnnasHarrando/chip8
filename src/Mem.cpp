#include "Mem.h"
#include <cstring>

void Mem::write(uint16_t addr, uint8_t data) {
    ram[addr] = data;
}

uint8_t Mem::read(uint16_t addr) {
    return ram[addr];
}
