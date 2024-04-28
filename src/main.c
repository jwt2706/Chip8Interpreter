#include <SDL2/SDL.h>
#include "../include/chip8.h"

int main() {
    // init sdl2
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    
    // create a window
    SDL_Window* window = SDL_CreateWindow(
        "CHIP-8 Interpreter",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640, // height
        320, // width
        SDL_WINDOW_SHOWN,
    );
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // init CHIP-8 (and SDL event)
    struct chip8 chip8;
    initChip8(&chip8);
    SDL_Event event;

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

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}