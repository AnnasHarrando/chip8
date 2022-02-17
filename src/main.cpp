#include "CPU.cpp"
#include "Mem.cpp"
#include "emu.cpp"
#include "IO.cpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#include <iostream>     // std::cout
#include <fstream>



using namespace std;

int main(int argc, char *argv[])
{
    int speed = 700;

    FILE* rom = fopen("/home/annas/CLionProjects/chip8/src/roms/PONG.ch8", "rb");
    if (rom == NULL) {
        std::cerr << "Failed to open ROM" << std::endl;
        return -1;
    }

    fseek(rom, 0, SEEK_END);
    long rom_size = ftell(rom);
    rewind(rom);

    char *buffer = new char[rom_size];

    size_t result = fread(buffer, sizeof(char), (size_t)rom_size, rom);
    if (result != rom_size) {
        std::cerr << "Failed to read ROM" << std::endl;
        return false;
    }


    emu test = emu(IO(), CPU(), Mem(buffer, rom_size));
    fclose(rom);
    free(buffer);

    test.emu_run();



    return 0;
}