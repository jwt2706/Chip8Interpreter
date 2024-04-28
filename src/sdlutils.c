#include "../include/sdlutils.h"

void initSDL(SDLComponents* components) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    
    // create window
    components->window = SDL_CreateWindow(
        "CHIP-8 Interpreter",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640, // height
        320, // width
        SDL_WINDOW_SHOWN,
    );
    if (components->window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // create renderer
    components->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (components->renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
}

void destroySDL(SDLComponents* components) {
    SDL_DestroyRenderer(components->renderer);
    SDL_DestroyWindow(components->window);
    SDL_Quit();
}
