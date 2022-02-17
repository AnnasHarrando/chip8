//
// Created by annas on 16-02-22.
//

#ifndef CHIP8_MEM_H
#define CHIP8_MEM_H

#include <cstdint>
#include <array>
#include <cstring>


class Mem {
public:

    uint8_t *ram = new uint8_t[4096];

    uint8_t fonts [5*16] = {0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
                            0x20, 0x60, 0x20, 0x20, 0x70, // 1
                            0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
                            0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
                            0x90, 0x90, 0xF0, 0x10, 0x10, // 4
                            0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
                            0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
                            0xF0, 0x10, 0x20, 0x40, 0x40, // 7
                            0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
                            0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
                            0xF0, 0x90, 0xF0, 0x90, 0x90, // A
                            0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
                            0xF0, 0x80, 0x80, 0x80, 0xF0, // C
                            0xE0, 0x90, 0x90, 0x90, 0xE0, // D
                            0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
                            0xF0, 0x80, 0xF0, 0x80, 0x80};  // F

    Mem(char* rom, long rom_size){
        for (long i = 0; i < rom_size; ++i) {
            ram[i + 0x200] = rom[i];
        }
        for (uint16_t i = 0; i < 80; i++){
            ram[0x50 + i] = fonts[i];
        }
    };

    void write(uint16_t addr, uint8_t data);
    uint8_t read(uint16_t addr);
};


#endif //CHIP8_MEM_H
