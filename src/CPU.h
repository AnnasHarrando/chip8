//
// Created by annas on 16-02-22.
//

#ifndef CHIP8_CPU_H
#define CHIP8_CPU_H
#include <cstdint>
#include <stack>
#include <array>
#include "Mem.h"

class CPU {
public:

    int pc = 0x200;
    uint8_t I = 0;
    uint8_t regs[16] = {};
    std::stack<uint16_t> stack;
    uint8_t delay_timer = 0;
    uint8_t sound_timer = 0;
    bool keys[16] = {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false};
    int last_key = 16;
    bool display[64*32] = { };
    void GetKey(int key,bool boo);

    void ResetKeys();

    void fetch(Mem mem);
};


#endif //CHIP8_CPU_H
