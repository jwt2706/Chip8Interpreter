#include <SDL2/SDL.h>
#include "../include/chip8.h"
#include "../include/sdlutils.h"

int main() {
    // init sdl2
    SDLComponents components;
    if (initSDL(&components) != 0) return 1;
    SDL_Event event;

    // init CHIP-8
    struct chip8 chip8;
    initChip8(&chip8);

    // main loop
    while (1) {
        // handle quitting the program
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                return 0;
            }
        }
        cycle(&chip8);
    }
    destroySDL(&components);
    return 0;
}