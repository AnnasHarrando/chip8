#include "CPU.cpp"
#include "emu.cpp"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{

    std::ifstream file("/home/annas/CLionProjects/chip8/src/roms/invaders.ch8", std::ios::binary | std::ios::ate);

    if (file.is_open())
    {
        // Get size of file and allocate a buffer to hold the contents
        std::streampos size = file.tellg();
        char* buffer = new char[size];

        // Go back to the beginning of the file and fill the buffer
        file.seekg(0, std::ios::beg);
        file.read(buffer, size);
        file.close();

        //Mem memory = Mem(buffer, size);

        emu test = emu(CPU(), buffer, size);
        test.emu_run();

        delete[] buffer;
    }

    return 0;
}