#ifndef CHIP8_CPU_H
#define CHIP8_CPU_H
#include <cstdint>
#include <stack>
#include <array>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

class CPU {
public:

    bool Drawflag = false;
    uint16_t pc = 0x200;
    uint16_t I = 0;
    uint8_t regs[16] = { 0};
    std::stack<uint16_t> stack;
    uint16_t Stack[16]{0};
    uint8_t sp=0;
    uint8_t delay_timer = 0;
    uint8_t sound_timer = 0;
    int keys[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int display[32][64] = {0};

    void fetch(uint8_t *ram);
};


#endif //CHIP8_CPU_H
