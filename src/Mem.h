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

    uint8_t ram [4096] = {} ;

    Mem(char* rom, long rom_size){
        memcpy(ram+80, fonts, 80);
        for (int i = 0; i < rom_size; ++i) {
            ram[i + 512] = rom[i];   // Load into memory starting
            // at 0x200 (=512)
        }
    };


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


    void write(uint16_t addr, uint8_t data);
    uint8_t read(uint16_t addr);
};


#endif //CHIP8_MEM_H