#ifndef SDLUTILS_H
#define SDLUTILS_H

#include <SDL2/SDL.h>

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
} SDLComponents;

void initSDL(SDLComponents* components);
void destroySDL(SDLComponents* components);

#endif