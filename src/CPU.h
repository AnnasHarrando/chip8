//
// Created by annas on 16-02-22.
//

#ifndef CHIP8_CPU_H
#define CHIP8_CPU_H
#include <cstdint>
#include <stack>
#include <array>
//#include "Mem.h"
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


    uint8_t keymap[16] = {
            SDLK_x,
            SDLK_1,
            SDLK_2,
            SDLK_3,
            SDLK_q,
            SDLK_w,
            SDLK_e,
            SDLK_a,
            SDLK_s,
            SDLK_d,
            SDLK_z,
            SDLK_c,
            SDLK_4,
            SDLK_r,
            SDLK_f,
            SDLK_v,
    };

    void fetch(uint8_t *ram);
};


#endif //CHIP8_CPU_H
