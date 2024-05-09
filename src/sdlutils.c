#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include <stdio.h>
#include <math.h>
#include "../include/sdlutils.h"
#include "../include/chip8.h"

static SDL_AudioDeviceID *audioPointer;

int initSDL(SDLComponents *components)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
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

    // setup audio
    SDL_AudioSpec want, have;
    SDL_zero(want);
    want.freq = 44100;
    want.format = AUDIO_S16SYS;
    want.channels = 1;
    want.samples = 2048;
    want.callback = NULL;

    // open audio
    components->audio = SDL_OpenAudioDevice(NULL, 0, &want, &have, 0);
    if (components->audio == 0)
    {
        printf("Failed to open audio device! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    audioPointer = &components->audio;

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

void playSound()
{
    // params
    int freq = 440;          // frequency
    int samples = 2048;      // number of samples to generate
    int sample_rate = 44100; // sample rate

    // sound generation
    int16_t *sound = malloc(samples * sizeof(int16_t));
    for (int i = 0; i < samples; i++)
    {
        sound[i] = 32767.0 * sin(2.0 * M_PI * freq * i / sample_rate);
    }

    // play the sound
    SDL_QueueAudio(*audioPointer, sound, samples * sizeof(int16_t));
    SDL_PauseAudioDevice(*audioPointer, 0);

    // wait for the sound to finish playing
    SDL_Delay(samples * 1000 / sample_rate);

    // free the sound
    free(sound);
}