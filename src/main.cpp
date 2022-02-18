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

    std::ifstream file("/home/annas/CLionProjects/chip8/src/roms/test_opcode.ch8", std::ios::binary | std::ios::ate);

    if (file.is_open())
    {
        // Get size of file and allocate a buffer to hold the contents
        std::streampos size = file.tellg();
        char* buffer = new char[size];

        // Go back to the beginning of the file and fill the buffer
        file.seekg(0, std::ios::beg);
        file.read(buffer, size);
        file.close();

        emu test = emu(CPU(), Mem(buffer, size));
        printf("%i\n",size);
        test.emu_run();

        delete[] buffer;
    }

    return 0;
}