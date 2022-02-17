
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

int main(int argc, char *argv[])
{

    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }

    SDL_Window* win = SDL_CreateWindow("GAME", // creates a window
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       1000, 1000, 0);

    int close = 0;

    // animation loop
    while (!close) {
        SDL_Event event;
        // Events management
        while (SDL_PollEvent(&event)) {

            switch (event.type) {

                case SDL_QUIT:
                    // handling of close button
                    close = 1;
                    break;

                case SDL_KEYDOWN:

                    // keyboard API for key pressedhhhhhhhhhhhhhhh
                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_W:
                        case SDL_SCANCODE_UP:
                            printf("up");
                            break;
                        case SDL_SCANCODE_A:
                        case SDL_SCANCODE_LEFT:
                            printf("left");
                            break;
                        case SDL_SCANCODE_S:
                        case SDL_SCANCODE_DOWN:
                            printf("down");
                            break;
                        case SDL_SCANCODE_D:
                        case SDL_SCANCODE_RIGHT:
                            printf("right");
                            break;
                        default:
                            break;
                    }
            }
        }



        // calculates to 60 fps
        SDL_Delay(1000 / 60);
    }

    // destroy texture

    // close SDL
    SDL_Quit();

    return 0;
}