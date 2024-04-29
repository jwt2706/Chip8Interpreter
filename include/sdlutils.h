#ifndef SDLUTILS_H
#define SDLUTILS_H

#include <SDL2/SDL.h>

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
} SDLComponents;

void initSDL(SDLComponents* components);
void redrawDisplay(SDLComponents* components, struct chip8* chip8);
void destroySDL(SDLComponents* components);

#endif