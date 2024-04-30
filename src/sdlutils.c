#include "../include/sdlutils.h"
#include "../include/chip8.h"

int initSDL(SDLComponents *components)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
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
        SDL_WINDOW_SHOWN);
    if (components->window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // create renderer
    components->renderer = SDL_CreateRenderer(components->window, -1, SDL_RENDERER_ACCELERATED);
    if (components->renderer == NULL)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    return 0;
}

void redrawDisplay(SDLComponents *components, struct chip8 *chip8)
{
    SDL_SetRenderDrawColor(components->renderer, 0, 0, 0, 255); // black
    SDL_RenderClear(components->renderer);

    SDL_SetRenderDrawColor(components->renderer, 255, 255, 255, 255); // white
    for (int y = 0; y < 32; y++)
    { // rows of the screen
        for (int x = 0; x < 64; x++)
        { // columns of the screen
            if (chip8->gfx[(y * 64) + x] == 1)
            {
                SDL_Rect pixel = {x * 10, y * 10, 10, 10};        // pixel position and size
                SDL_RenderFillRect(components->renderer, &pixel); // draw pixel
            }
        }
    }

    SDL_RenderPresent(components->renderer);
}

void destroySDL(SDLComponents *components)
{
    SDL_DestroyRenderer(components->renderer);
    SDL_DestroyWindow(components->window);
    SDL_Quit();
}
