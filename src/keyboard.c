#include <SDL2/SDL.h>
#include "../include/chip8.h"
#include "../include/keyboard.h"

// lookup table for key mapping
static int keymap[SDL_NUM_SCANCODES];

/*
The keyboard layout is based on the 4x4 hex keyboard from the COSMAC VIP computer.
It is implemented in regular QWERTY layout as follows:

1 2 3 4
Q W E R
A S D F
Z X C V

*/

void initKeymap()
{
    keymap[SDL_SCANCODE_1] = 1;
    keymap[SDL_SCANCODE_2] = 2;
    keymap[SDL_SCANCODE_3] = 3;
    keymap[SDL_SCANCODE_4] = 0xC;
    keymap[SDL_SCANCODE_Q] = 4;
    keymap[SDL_SCANCODE_W] = 5;
    keymap[SDL_SCANCODE_E] = 6;
    keymap[SDL_SCANCODE_R] = 0xD;
    keymap[SDL_SCANCODE_A] = 7;
    keymap[SDL_SCANCODE_S] = 8;
    keymap[SDL_SCANCODE_D] = 9;
    keymap[SDL_SCANCODE_F] = 0xE;
    keymap[SDL_SCANCODE_Z] = 0xA;
    keymap[SDL_SCANCODE_X] = 0;
    keymap[SDL_SCANCODE_C] = 0xB;
    keymap[SDL_SCANCODE_V] = 0xF;
}

void handleKey(struct chip8 *chip8, SDL_KeyCode keycode, int keyState)
{
    int chip8_key = keymap[keycode];
    if (chip8_key >= 0 && chip8_key <= 0xF)
    {
        chip8->keys[chip8_key] = keyState;
    }
}