#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <SDL2/SDL.h>
#include "../include/chip8.h"

void initKeymap();
void handleKey(struct chip8 *chip8, SDL_KeyCode keycode, int keyState);

#endif