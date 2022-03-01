#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include "CPU.h"
#include "Timer.cpp"
#include <cstdint>


class emu {
public:
    SDL_Event event;
    CPU cpu;

    Timer timer = Timer();
    Timer clock = Timer();
    bool running = true;

    SDL_Window* win;
    SDL_Texture *texture;
    SDL_Renderer * renderer;

    uint8_t ram[4096] = {0};
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

    emu(CPU cpu2, char* rom, long rom_size){
        this->cpu = cpu2;
        //this->mem = mem2;
        for (long i = 0; i < rom_size; ++i) {
            ram[i + 0x200] = rom[i];
        }
        for (uint16_t i = 0; i < 80; i++){
            ram[i] = fonts[i];
        }

        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
            printf("error initializing SDL: %s\n", SDL_GetError());
        }

        if (SDL_Init(SDL_INIT_AUDIO) < 0) {
            printf("error initializing SDL: %s\n", SDL_GetError());
        }

        win = SDL_CreateWindow("sdl2 pixel drawing",
                               1000, 500,320, 160, 0);
        renderer = SDL_CreateRenderer(win,-1, SDL_RENDERER_ACCELERATED);
        texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 320, 160);
        SDL_SetRenderTarget(renderer,texture);
    }
    void emu_run();

    void input(CPU *cpu);

    void DrawScreen(int display[32][64]);
};




void emu::emu_run(){
    timer.start();
    clock.start();

    while(running){
        cpu.fetch(ram);
        input(&cpu);

        if(cpu.Drawflag){
            cpu.Drawflag = false;
            DrawScreen(cpu.display);
        }

        if(clock.elapsedTime() < 0.002){
            printf("delay\n");
            SDL_Delay(2-clock.elapsedTime()*1000);
            clock.start();
        }

        if(timer.elapsedTime() > 0.016) {
            if (cpu.delay_timer > 0) cpu.delay_timer--;
            if (cpu.sound_timer > 0) {
                cpu.sound_timer--;
            }
            timer.start();
        }

    }
}

void emu::DrawScreen(int display[32][64]){
    for (int i = 0; i < 64; ++i)
        for (int j = 0; j < 32; j++){
                for(int k=0;k<5;k++){
                    for(int l=0;l<5;l++){
                        if(display[j][i] == 1) {
                            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                            SDL_RenderDrawPoint(this->renderer, i * 5 + k, j * 5 + l);
                        }
                        else {
                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
                            SDL_RenderDrawPoint(this->renderer, i * 5 + k, j * 5 + l);
                        }
                    }

                }

        }
    SDL_RenderPresent(renderer);
}


void emu::input(CPU *cpu) {
    while (SDL_PollEvent(&event)) {

        if (event.type == SDL_QUIT) {
            running = false;
            SDL_DestroyWindow(win);
            break;
        }

        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_1:
                    cpu->keys[0x1] = 1;
                    break;
                case SDLK_2:
                    cpu->keys[0x2] = 1;
                    break;
                case SDLK_3:
                    cpu->keys[0x3] = 1;
                    break;
                case SDLK_4:
                    cpu->keys[0xC] = 1;
                    break;
                case SDLK_q:
                    cpu->keys[0x4] = 1;
                    break;
                case SDLK_w:
                    cpu->keys[0x5] = 1;
                    break;
                case SDLK_e:
                    cpu->keys[0x6] = 1;
                    break;
                case SDLK_r:
                    cpu->keys[0xD] = 1;
                    break;
                case SDLK_a:
                    cpu->keys[0x7] = 1;
                    break;
                case SDLK_s:
                    cpu->keys[0x8] = 1;
                    break;
                case SDLK_d:
                    cpu->keys[0x9] = 1;
                    break;
                case SDLK_f:
                    cpu->keys[0xE] = 1;
                    break;
                case SDLK_z:
                    cpu->keys[0xA] = 1;
                    break;
                case SDLK_x:
                    cpu->keys[0x0] = 1;
                    break;
                case SDLK_c:
                    cpu->keys[0xB] = 1;
                    break;
                case SDLK_v:
                    cpu->keys[0xF] = 1;
                    break;
                case SDLK_ESCAPE:
                    exit(1);
                    break;
            }
        } else if (event.type == SDL_KEYUP) {
            switch (event.key.keysym.sym) {
                case SDLK_1:
                    cpu->keys[0x1] = 0;
                    break;
                case SDLK_2:
                    cpu->keys[0x2] = 0;
                    break;
                case SDLK_3:
                    cpu->keys[0x3] = 0;
                    break;
                case SDLK_4:
                    cpu->keys[0xC] = 0;
                    break;
                case SDLK_q:
                    cpu->keys[0x4] = 0;
                    break;
                case SDLK_w:
                    cpu->keys[0x5] = 0;
                    break;
                case SDLK_e:
                    cpu->keys[0x6] = 0;
                    break;
                case SDLK_r:
                    cpu->keys[0xD] = 0;
                    break;
                case SDLK_a:
                    cpu->keys[0x7] = 0;
                    break;
                case SDLK_s:
                    cpu->keys[0x8] = 0;
                    break;
                case SDLK_d:
                    cpu->keys[0x9] = 0;
                    break;
                case SDLK_f:
                    cpu->keys[0xE] = 0;
                    break;
                case SDLK_z:
                    cpu->keys[0xA] = 0;
                    break;
                case SDLK_x:
                    cpu->keys[0x0] = 0;
                    break;
                case SDLK_c:
                    cpu->keys[0xB] = 0;
                    break;
                case SDLK_v:
                    cpu->keys[0xF] = 0;
                    break;
            }
        }
    }
}


