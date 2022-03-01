#include "CPU.h"
//#include "Mem.h"
#include <stack>
#include <iostream>
#include <cstring>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <sstream>

using namespace std;

void CPU::fetch(uint8_t *ram){
    uint16_t opcode = ram[pc] << 8u | ram[pc+1] ;
    uint16_t OOON = opcode & 0xF000;
    uint16_t OONO = (opcode & 0x0F00)>>8;
    uint16_t ONOO = (opcode & 0x00F0)>>4;
    uint16_t NOOO = opcode & 0x000F;
    uint16_t NNNO = opcode & 0x0FFF;
    uint16_t NNOO = opcode & 0x00FF;


    printf("%04X\n",opcode);
    //printf("%i\n",regs[0xF]);
    //printf("%i\n",regs[OONO]);

    pc += 2;
    int i,j;
    int x = regs[OONO] & 63;
    int y = regs[ONOO] & 31;

    switch(OOON){
        case (0x0000):
            if(NOOO == 0x0000) {
                for (i = 0; i < 64; i++) {
                    for (j = 0; j < 32;j++){
                        display[j][i] = 0;
                    }
                }
                Drawflag = true;
            }
            else if(NOOO == 0x000E) {
                pc = stack.top();
                stack.pop();
            }
            else {
                printf("unknown opcode %04X",opcode);
                exit(3);
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
            regs[OONO] = NNOO;
            break;
        case (0x7000):
            regs[OONO] += NNOO;
            break;
        case (0x8000):
            switch (NOOO) {
                case (0x0000):
                    regs[OONO] = regs[ONOO];
                    break;
                case (0x0001):
                    regs[OONO] |= regs[ONOO];
                    break;
                case (0x0002):
                    regs[OONO] &= regs[ONOO];
                    break;
                case (0x0003):
                    printf("test\n");
                    regs[OONO] ^= regs[ONOO];
                    break;
                case (0x0004):
                    //printf("%i\n",regs[OONO]+regs[ONOO]);
                {
                    int temp = regs[OONO] + regs[ONOO];
                    if (temp > 255) {
                        regs[0xF] = 1;
                    } else {
                        regs[0xF] = 0;
                    }
                    regs[OONO] = temp & 0xFF;
                }
                    break;
                case (0x0005):

                    if(regs[OONO] < regs[ONOO]) regs[0xF] = 0;
                    else regs[0xF] = 1;
                    regs[OONO] -= regs[ONOO];

                    break;
                case (0x0006):
                    regs[0xF] = regs[OONO] & 0x1;
                    regs[OONO] = regs[OONO]>>1;
                    break;
                case (0x0007):

                    if(regs[ONOO] < regs[OONO]) regs[0xF] = 0;
                    else regs[0xF] = 1;
                    regs[OONO] = regs[ONOO] - regs[OONO];

                    break;
                case (0x000E):
                    regs[0xF] = regs[OONO] >> 7;
                    regs[OONO] = regs[OONO]<<1;
                    break;
                default:
                    printf("unknown opcode %04X",opcode);
                    exit(3);
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
            regs[OONO] = (rand() % (0xFF +1)) & NNOO;
            break;
        case (0xD000):
            regs[0xF] = 0;

            for(i = 0; i < (NOOO); i++){
                uint8_t sprite = ram[I+i];
                for(j = 0; j < 8; j++){

                    if((sprite & (0x80 >> j)) != 0){
                        if(display[y+i][x+j] == 1){
                            regs[0xF] = 1;
                        }
                        display[y+i][x+j] ^= 1;
                    }
                }

            }
            Drawflag = true;
            break;
        case (0xE000):
            if(NOOO == 0x0001){
                if(!keys[regs[OONO]]) pc += 2;
            }
            else if (NOOO == 0x000E){
                if(keys[regs[OONO]]) pc += 2;
            }
            else {
            printf("unknown opcode %04X",opcode);
            exit(3);
            }
            break;
        case(0xF000):
            switch(NNOO){
                case(0x0033):
                    ram[I] = regs[OONO] / 100;
                    ram[I+1] = (regs[OONO] / 10) % 10;
                    ram[I+2] = regs[OONO] % 10;
                    break;
                case(0x0015):
                    delay_timer = regs[OONO];
                    break;
                case(0x0055):
                    for(i = 0; i <= ((opcode & 0x0F00) >> 8); i++) {
                        ram[I+i] = regs[i];
                        //printf("%i\n",i);
                    }
                    break;
                case(0x0065):
                    for(i = 0; i <= ((opcode & 0x0F00) >> 8); i++) {
                        regs[i] = ram[I+i];
                    }
                    break;
                case(0x0007):
                    regs[OONO] = delay_timer;
                    break;
                case (0x0018):
                    sound_timer = regs[OONO];
                    break;
                case (0x0029):
                    I = regs[OONO]*0x5;
                    break;
                case (0x000A):
                    for (int i=0; i < 16; ++i) {
                        if (keys[i] != 0) {
                            regs[OONO] = i;
                            pc += 2;
                            break;
                        }
                    }
                    pc -= 2;
                    break;
                case (0x001E):
                    if(I+regs[OONO] > 0xFFF){
                        regs[0xF] = 1;
                    }
                    else {
                        regs[0xF] = 0;
                    }
                    I += regs[OONO];
                    break;
                default:
                    printf("unknown opcode %04X",opcode);
                    exit(3);
                    break;
            }
        break;
        default:
            printf("unknown opcode %04X",opcode);
            exit(3);
            break;
    }



}


