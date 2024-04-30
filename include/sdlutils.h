#ifndef SDLUTILS_H
#define SDLUTILS_H

#include <SDL2/SDL.h>
#include "chip8.h"

typedef struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_AudioDeviceID audio;
} SDLComponents;

int initSDL(SDLComponents *components);
void redrawDisplay(SDLComponents *components, struct chip8 *chip8);
void destroySDL(SDLComponents *components);
void playSound();

#endif