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
    SDL_Texture *texture;
    SDL_Renderer * renderer;

    IO(){
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
            printf("error initializing SDL: %s\n", SDL_GetError());
        }

        win = SDL_CreateWindow("sdl2 pixel drawing",
                         1000, 500,64, 32, 0);
        renderer = SDL_CreateRenderer(win,-1, SDL_RENDERER_ACCELERATED);


    };

    void DrawScreen(const bool *display);
};
#endif //CHIP8_IO_H
