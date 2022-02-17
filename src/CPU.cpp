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
    uint16_t opcode = mem.ram[pc+1] << 8u | mem.ram[pc] ;
    uint8_t OOON = opcode & 0xF;
    uint8_t OONO = (opcode & 0xFF)>>4;
    uint8_t ONOO = (opcode & 0xFFF)>>8;
    uint8_t NOOO = (opcode & 0xFFFF)>>12;
    uint8_t ONNO = (opcode & 0xFFF)>>4;
    uint16_t NNNO = (opcode & 0x0FFFu);
    uint8_t NNOO = (opcode & 0x00FFu);

    printf("%04X ", opcode);
    printf("%X ",opcode & 0xF);
    printf("%X ",(opcode & 0xFF)>>4);
    printf("%X ",(opcode & 0xFFF)>>8);
    printf("%X ",(opcode & 0xFFFF)>>12);
    printf("%i ", pc);
    printf("%i \n", I);
    printf("0NN0 :%02X ",ONNO);
    printf("0NNN :%03X ",NNNO);
    printf("00NN :%02X \n",NNOO);


    pc += 2;
    int i,j;
    int x = regs[OONO] & 63;
    int y = regs[ONOO] & 31;

    switch(OOON){
        case (0x0):
            if(NOOO == 0) {
                for (i = 0; i < 2048; i++) {
                    display[i] = false;
                }
            }
            else if(NOOO == 0xE) {
                pc = stack.top();
                stack.pop();
            }
            break;
        case (0x1):
            pc = NNNO;
            break;
        case (0x2):
            stack.push(pc);
            pc = NNNO;
            break;
        case (0x3):
            if(regs[OONO] == NNOO) pc += 2;
            break;
        case (0x4):
            if(!(regs[OONO] == NNOO)) pc += 2;
            break;
        case (0x5):
            if(regs[ONOO] == regs[OONO]) pc += 2;
            break;
        case (0x6):
            regs[OONO] = (NNOO);
            break;
        case (0x7):
            regs[OONO] += (NNOO);
            break;
        case (0x8):
            switch (NOOO) {
                case (0x0):
                    regs[OONO] = regs[ONOO];
                    break;
                case (0x1):
                    regs[OONO] = regs[OONO] | regs[OONO];
                    break;
                case (0x2):
                    regs[OONO] = regs[ONOO] & regs[OONO];
                    break;
                case (0x3):
                    regs[OONO] = regs[ONOO] ^ regs[OONO];
                    break;
                case (0x4):
                    if (regs[OONO] + regs[ONOO] > 255) regs[15] = 1;
                    else regs[15] = 0;
                    regs[OONO] = regs[ONOO] + regs[OONO];
                    break;
                case (0x5):
                    if(regs[OONO] > regs[ONOO]) regs[15] = 1;
                    else regs[15] = 0;
                    regs[OONO] = regs[OONO] - regs[ONOO];
                    break;
                case (0x6):
                    regs[15] = regs[OONO] & 0x1;
                    regs[OONO] = regs[OONO]>>1;
                    break;
                case (0x7):
                    if(regs[ONOO] < regs[OONO]) regs[15] = 1;
                    else regs[15] = 0;
                    regs[OONO] = regs[ONOO] - regs[OONO];
                    break;
                case (0xE):
                    regs[15] = regs[OONO] & 0xD0;
                    regs[OONO] = regs[OONO]<<1;
                    break;
                default:
                    break;
            }
        case (0x9):
            if(regs[ONOO] == regs[OONO]) pc += 2;
            break;
        case (0xA):
            I = NNNO;
            break;
        case (0xB):
            pc = NNNO + regs[0];
            break;
        case (0xC):
            srand (time(NULL));
            regs[OONO] = rand() | NNOO;
            break;
        case (0xD):
            regs[15] = 0;
            for(i = 0; i < (NOOO); i++){
                uint8_t sprite = mem.read(I+i);
                for(j = 0; j < 8; j++){
                    if(x+j > 31) goto exit_loop;;
                    uint8_t bit = sprite & 0x1;
                    bit = bit>>1;
                    if(bit){
                        if(display[(x+j)+(y*64)]){
                            display[(x+j)+(y*64)] = false;
                            regs[15] = 1;
                        }
                        else{
                            display[(x+j)+(y*64)] = true;
                            regs[15] = 0;
                        }
                    }
                }
                exit_loop: ;
                y += 1;
                if(y > 31) break;
            }
            break;
        case (0xE):
            if(NOOO == 0x1){
                if(!keys[regs[OONO]]) pc += 2;
            }
            else{
                if(keys[regs[OONO]]) pc += 2;
            }
            break;
        case(0xF):
            switch(NOOO){
                case(0x3):
                    I = (regs[OONO] / 100 << 16) | (regs[OONO] / 10 << 8) | regs[OONO];
                    break;
                case(0x5):
                    if(ONOO == 0x1) delay_timer = regs[OONO];
                    else if (ONOO == 0x5){
                        for(i = 0; i < 16; i++) mem.write(I+i,regs[i]);
                    }
                    else if (ONOO == 0x6){
                        for(i = 0; i < 16; i++) regs[i] = mem.read(I+i);
                    }
                    break;
                case(0x7):
                    regs[OONO] = delay_timer;
                    break;
                case (0x8):
                    sound_timer = regs[OONO];
                    break;
                case (0x9):
                    I = 80 + regs[OONO]*5;
                    break;
                case (0xA):
                    if(last_key < 16){
                        regs[OONO] = last_key;
                    }
                    else pc -= 2;
                    break;
                case (0xE):
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


