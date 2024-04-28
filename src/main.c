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

    SDL_Event event;
    while (1) {
        // handle quitting the program
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                return 0;
            }
        }

        // get the opcode
        // since the opcode is 2 bytes long (8-bits * 2 = 16-bits), we need to merge the two bytes into a single 16-bit value
        chip8.opcode = chip8.memory[chip8.pc] << 8 | chip8.memory[chip8.pc + 1];

        // extract X, Y, N, and NN from the opcode
        /*unsigned short X = (chip8.opcode & 0x0F00) >> 8;
        unsigned short Y = (chip8.opcode & 0x00F0) >> 4;
        unsigned short N = chip8.opcode & 0x000F;
        unsigned short NN = chip8.opcode & 0x00FF;
        unsigned short NNN = chip8.opcode & 0x0FFF;*/

        // decode and execute the opcode
        switch (chip8.opcode & 0xF000) {
            // ...
        }

        // update timers
        if (chip8.delay_timer > 0) {
            chip8.delay_timer--;
        }

        if (chip8.sound_timer > 0) {
            if (chip8.sound_timer == 1) {
                // play a sound
            }
            chip8.sound_timer--;
        }

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}