#include "CPU.h"
#include "Mem.h"
#include <stack>
#include <iostream>
#include <cstring>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


void CPU::GetKey(int key, bool boo){
    keys[key] = boo;
}

void CPU::ResetKeys(){
    for(int i=0; i < 16;i++){
        keys[i] = false;
    };
}

void CPU::fetch(Mem mem){
    uint16_t opcode = mem.ram[pc] << 8u | mem.ram[pc+1] ;
    uint16_t OOON = opcode & 0xF000;
    uint16_t OONO = (opcode & 0x0F00)>>8;
    uint16_t ONOO = (opcode & 0x00F0)>>4;
    uint16_t NOOO = opcode & 0x000F;
    uint16_t ONNO = opcode & 0x0FF0;
    uint16_t NNNO = opcode & 0x0FFF;
    uint16_t NNOO = opcode & 0x00FF;


   // printf("%04X\n",opcode);

    pc += 2;
    int i,j;
    int x = regs[OONO] & 63;
    int y = regs[ONOO] & 31;

    switch(OOON){
        case (0x0000):
            if(NOOO == 0x0000) {
                for (i = 0; i < 64; i++) {
                    for (j - 0; j < 32;j++){
                        display[j][i] = false;
                    }
                }
            }
            else if(NOOO == 0x000E) {
                pc = stack.top();
                stack.pop();
            }
            break;
        case (0x1000):
            pc = NNNO;
            break;
        case (0x2000):
            stack.push(pc);
            pc = NNNO;
            break;
        case (0x3000):
            if(regs[OONO] == NNOO) pc += 2;
            break;
        case (0x4000):
            if(regs[OONO] != NNOO) pc += 2;
            break;
        case (0x5000):
            if(regs[ONOO] == regs[OONO]) pc += 2;
            break;
        case (0x6000):
            regs[OONO] = (NNOO);
            break;
        case (0x7000):
            regs[OONO] += (NNOO);
            break;
        case (0x8000):
            switch (NOOO) {
                case (0x0000):
                    regs[OONO] = regs[ONOO];
                    break;
                case (0x0001):
                    regs[OONO] = regs[OONO] | regs[ONOO];
                    break;
                case (0x0002):
                    regs[OONO] = regs[OONO] & regs[ONOO];
                    break;
                case (0x0003):
                    regs[OONO] = regs[ONOO] ^ regs[ONOO];
                    break;
                case (0x0004):
                    if (regs[OONO] + regs[ONOO] > 255) regs[15] = 1;
                    else regs[15] = 0;
                    regs[OONO] = regs[ONOO] + regs[OONO];
                    break;
                case (0x0005):
                    if(regs[OONO] > regs[ONOO]) regs[15] = 1;
                    else regs[15] = 0;
                    regs[OONO] = regs[OONO] - regs[ONOO];
                    break;
                case (0x0006):
                    regs[15] = regs[OONO] & 7;
                    regs[OONO] = regs[OONO]>>1;
                    break;
                case (0x0007):
                    if(regs[ONOO] < regs[OONO]) regs[15] = 1;
                    else regs[15] = 0;
                    regs[OONO] = regs[ONOO] - regs[OONO];
                    break;
                case (0x000E):
                    regs[15] = regs[OONO] >> 7;
                    regs[OONO] = regs[OONO]<<1;
                    break;
                default:
                    break;
            }
        case (0x9000):
            if(regs[ONOO] != regs[OONO]) pc += 2;
            break;
        case (0xA000):
            I = NNNO;
            break;
        case (0xB000):
            pc = NNNO + regs[0];
            break;
        case (0xC000):
            srand (time(NULL));
            regs[OONO] = rand() | NNOO;
            break;
        case (0xD000):
            regs[15] = 0;
            for(i = 0; i < (NOOO); i++){
                uint8_t sprite = mem.read(I+i);
                for(j = 0; j < 8; j++){

                    if(sprite & (0x80 >> j)){
                        if(display[y][x+j]){
                            display[y][x+j] = false;
                            regs[15] = 1;
                        }
                        else{
                            display[y][x+j] = true;
                            regs[15] = 0;
                        }
                    }
                }

                y += 1;
            }
            break;
        case (0xE000):
            if(NOOO == 0x0001){
                if(!keys[regs[OONO]]) pc += 2;
            }
            else{
                if(keys[regs[OONO]]) pc += 2;
            }
            break;
        case(0xF000):
            switch(NOOO){
                case(0x0003):
                   // printf("%04X %i %i %i %i %i",opcode, OONO,regs[OONO],regs[OONO] / 100,(regs[OONO] / 10) % 10,regs[OONO] %10);
                    mem.ram[I,(uint8_t)regs[OONO] / 100];
                    mem.ram[I+1,(uint8_t)(regs[OONO] / 10) % 10];
                    mem.ram[I+2,(uint8_t)(regs[OONO]%100) %10];
                    break;
                case(0x0005):
                    if(NNOO == 0x0015) delay_timer = regs[OONO];
                    else if (NNOO == 0x0055){

                        for(i = 0; i <= (int)OONO; i++) {
                            mem.ram[I+i] = regs[i];
                           // printf("%i\n",i);
                        }
                    }
                    else if (NNOO == 0x0065){
                        for(i = 0; i <= (int)OONO; i++) regs[i] = mem.ram[I+i];
                    }
                    break;
                case(0x0007):
                    regs[OONO] = delay_timer;
                    break;
                case (0x0008):
                    sound_timer = regs[OONO];
                    break;
                case (0x0009):
                    I = 80 + regs[OONO]*5;
                    break;
                case (0x000A):
                    if(last_key < 16){
                        regs[OONO] = last_key;
                    }
                    else pc -= 2;
                    break;
                case (0x000E):
                    I += regs[OONO];
                    break;
                default:
                    break;
            }
        break;
        default:
            break;
    }


}


