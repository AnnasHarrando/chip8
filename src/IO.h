#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <iostream>

#ifndef CHIP8_IO_H
#define CHIP8_IO_H
class IO {
public:
    bool running = true;
    void input(CPU *cpu);
    SDL_Window* win;

    IO(){
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
            printf("error initializing SDL: %s\n", SDL_GetError());
        }

        win = SDL_CreateWindow("GAME", // creates a window
                                           SDL_WINDOWPOS_CENTERED,
                                           SDL_WINDOWPOS_CENTERED,
                                           1000, 1000, 0);

    };
};
#endif //CHIP8_IO_H
