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
    uint16_t opcode =  (mem.read(pc) << 8) | mem.read(pc+1) ;
    printf("%X\n",opcode);

    pc += 2;

    int i,j;
    int x = regs[opcode & 0xF0] & 63;
    int y = regs[opcode & 0xF00] & 31;
    switch(opcode & 0xF){
        case (0x0):
            if((opcode & 0xF000) == 0) {
                for (i = 0; i < 2048; i++) {
                    display[i] = false;
                }
            }
            else{
                pc = stack.top();
                stack.pop();
            }

            break;
        case (0x1):
            pc = opcode & 0xFFF;
            break;
        case (0x2):
            stack.push(pc);
            pc = opcode & 0xFFF;
            break;
        case (0x3):
            if(regs[opcode & 0xF00] == (opcode & 0xFF00)) pc += 2;
            break;
        case (0x4):
            if(!regs[opcode & 0xF00] == (opcode & 0xFF00)) pc += 2;
            break;
        case (0x5):
            if(regs[opcode & 0xF0] == regs[opcode & 0xF00]) pc += 2;
            break;
        case (0x6):
            regs[opcode & 0xF0] = (opcode & 0xFF00);
            break;
        case (0x7):
            regs[opcode & 0xF0] += (opcode & 0xFF00);
            break;
        case (0x8):
            switch (opcode & 0xF000) {
                case (0x0):
                    regs[opcode & 0xF0] = regs[opcode & 0xF00];
                    break;
                case (0x1):
                    regs[opcode & 0xF0] = regs[opcode & 0xF0] | regs[opcode & 0xF00];
                    break;
                case (0x2):
                    regs[opcode & 0xF0] = regs[opcode & 0xF0] & regs[opcode & 0xF00];
                    break;
                case (0x3):
                    regs[opcode & 0xF0] = regs[opcode & 0xF0] ^ regs[opcode & 0xF00];
                    break;
                case (0x4):
                    if (regs[opcode & 0xF0] + regs[opcode & 0xF00] > 255) regs[15] = 1;
                    else regs[15] = 0;
                    regs[opcode & 0xF0] = regs[opcode & 0xF0] + regs[opcode & 0xF00];
                    break;
                case (0x5):
                    if(regs[opcode & 0xF0] > regs[opcode & 0xF00]) regs[15] = 1;
                    else regs[15] = 0;
                    regs[opcode & 0xF0] = regs[opcode & 0xF0] - regs[opcode & 0xF00];
                    break;
                case (0x6):
                    regs[15] = regs[opcode & 0xF0] & 0x1;
                    regs[opcode & 0xF0] = regs[opcode & 0xF0]>>1;
                    break;
                case (0x7):
                    if(regs[opcode & 0xF0] < regs[opcode & 0xF00]) regs[15] = 1;
                    else regs[15] = 0;
                    regs[opcode & 0xF0] = regs[opcode & 0xF00] - regs[opcode & 0xF0];
                    break;
                case (0xE):
                    regs[15] = regs[opcode & 0xF0] & 0xD0;
                    regs[opcode & 0xF0] = regs[opcode & 0xF0]<<1;
                    break;
                default:
                    printf("opcode not implemented\n");
                    printf("%X",opcode);
                    exit(-1);
            }
        case (0x9):
            if(regs[opcode & 0xF0] == regs[opcode & 0xF00]) pc += 2;
            break;
        case (0xA):
            I = opcode & 0xFFF0;
            break;
        case (0xB):
            pc = (opcode & 0xFFF0) + regs[0];
            break;
        case (0xC):
            srand (time(NULL));
            regs[opcode & 0xF0] = rand() | (opcode & 0xFF00);
            break;
        case (0xD):
            regs[15] = 0;
            for(i = 0; i < (opcode & 0xF000); i++){
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
            if((opcode & 0xF000) == 0x1){
                if(!keys[regs[opcode & 0xF0]]) pc += 2;
            }
            else{
                if(keys[regs[opcode & 0xF0]]) pc += 2;
            }
            break;
        case(0xF):
            switch(opcode & 0xF000){
                case(0x3):
                    I = (regs[opcode & 0xF0] / 100 << 16) | (regs[opcode & 0xF0] / 10 << 8) | regs[opcode & 0xF0];
                    break;
                case(0x5):
                    if((opcode & 0xF00) == 0x1) delay_timer = regs[opcode & 0xF0];
                    else if ((opcode & 0xF00) == 0x5){
                        for(i = 0; i < 16; i++) mem.write(I+i,regs[i]);
                    }
                    else if ((opcode & 0xF00) == 0x6){
                        for(i = 0; i < 16; i++) regs[i] = mem.read(I+i);
                    }
                    else{
                        printf("opcode not implemented\n");
                        printf("%X",opcode);
                        exit(-1);
                    }
                    break;
                case(0x7):
                    regs[opcode & 0xF0] = delay_timer;
                    break;
                case (0x8):
                    sound_timer = regs[opcode & 0xF0];
                    break;
                case (0x9):
                    I = 80 + regs[opcode & 0xF0]*5;
                    break;
                case (0xA):
                    if(last_key < 16){
                        regs[opcode & 0xF0] = last_key;
                    }
                    else pc -= 2;
                    break;
                case (0xE):
                    I += regs[opcode & 0xF0];
                    break;
            }
        break;
        default:
            printf("opcode not implemented\n");
            printf("%X",opcode);
            exit(-1);
    }


}


