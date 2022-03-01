#include "Mem.h"
#include <cstring>


void Mem::write(uint16_t addr, uint8_t data) {
    ram[addr] = data;
}

uint8_t Mem::read(uint16_t addr) {
    return ram[addr];
}

Mem::Mem(char *rom, long rom_size) {

    for (long i = 0; i < rom_size; ++i) {
        ram[i + 0x200] = rom[i];
    }
    for (uint16_t i = 0; i < 80; i++){
        ram[0x50 + i] = fonts[i];
    }
}

