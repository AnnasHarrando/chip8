#include "Mem.h"
#include "IO.h"
#include "CPU.h"

class emu {
public:

    CPU cpu;
    IO io;
    Mem mem;

    emu(IO Io, CPU cpu, Mem mem) : cpu(cpu), mem(mem) {
        this->cpu = cpu;
        this->io = Io;
        this->mem = mem;
    }

    void emu_run();
};




void emu::emu_run(){

    while(io.running){
        io.input(&cpu);
        cpu.fetch(mem);
        SDL_Delay(1000/700);
    }
}


