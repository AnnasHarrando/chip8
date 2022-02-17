#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <iostream>
#include "CPU.h"


void IO::input(CPU *cpu){
    SDL_Event event;
    cpu->ResetKeys();
    // Events management
    while (SDL_PollEvent(&event)) {

        if (event.type == SDL_QUIT) {
            running = false;
            SDL_DestroyWindow(win);
            break;
        }

        const uint8_t* state = SDL_GetKeyboardState(NULL);

        cpu->last_key = 16;
        if(state[SDL_SCANCODE_1]) {
            cpu->GetKey(1,true);
            cpu->last_key = 1;
        }
        if(state[SDL_SCANCODE_2]){
            cpu->GetKey(2,true);
            cpu->last_key = 2;
        }
        if(state[SDL_SCANCODE_3]) {
            cpu->GetKey(3,true);
            cpu->last_key = 3;
        }
        if(state[SDL_SCANCODE_4]) {
            cpu->GetKey(13,true);
            cpu->last_key = 13;
        }
        if(state[SDL_SCANCODE_Q]) {
            cpu->GetKey(4,true);
            cpu->last_key = 4;
        }
        if(state[SDL_SCANCODE_W]) {
            cpu->GetKey(5,true);
            cpu->last_key = 5;
        }
        if(state[SDL_SCANCODE_E]) {
            cpu->GetKey(6,true);
            cpu->last_key = 6;
        }
        if(state[SDL_SCANCODE_R]) {
            cpu->GetKey(14,true);
            cpu->last_key = 14;
        }
        if(state[SDL_SCANCODE_A]) {
            cpu->GetKey(7,true);
            cpu->last_key = 7;
        }
        if(state[SDL_SCANCODE_S]) {
            cpu->GetKey(8,true);
            cpu->last_key = 8;
        }
        if(state[SDL_SCANCODE_D]) {
            cpu->GetKey(9,true);
            cpu->last_key = 9;
        }
        if(state[SDL_SCANCODE_F]) {
            cpu->GetKey(14,true);
            cpu->last_key = 14;
        }
        if(state[SDL_SCANCODE_Z]) {
            cpu->GetKey(10,true);
            cpu->last_key = 10;
        }
        if(state[SDL_SCANCODE_X]) {
            cpu->GetKey(0,true);
            cpu->last_key = 0;
        }
        if(state[SDL_SCANCODE_C]) {
            cpu->GetKey(11,true);
            cpu->last_key = 11;
        }
        if(state[SDL_SCANCODE_V]) {
            cpu->GetKey(15,true);
            cpu->last_key = 15;
        }

    }
}

void IO::DrawScreen(const bool *display){
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 64, 32);
    SDL_SetRenderTarget(renderer,texture);
    for (int i = 0; i < 64; ++i)
        for (int j = 0; j < 32; j++){
            if(display[i+(j*64)]){
                SDL_RenderDrawPoint(this->renderer, i, j);
            }
        }
    SDL_RenderPresent(renderer);
}
