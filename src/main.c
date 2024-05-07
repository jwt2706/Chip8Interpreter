#include <SDL2/SDL.h>
#include "../include/sdlutils.h"
#include "../include/keyboard.h"
#include "../include/chip8.h"
#include "../include/load.h"

int main(int argc, char *argv[])
{
    // init sdl2
    SDLComponents components;
    if (initSDL(&components) != 0)
        return 1;
    SDL_Event event;

    // init CHIP-8
    struct chip8 chip8;
    initChip8(&chip8);

    // init keymap
    initKeymap();

    // load ROM
    char *romName = "IBMLOGO"; // default
    if (argc >= 2)
        romName = argv[1];
    char rom[265];
    printf(rom, sizeof(rom), "roms/%s", romName);
    loadRom(&chip8, rom);

    // get delay
    int delay = 2;
    if (argc >= 3)
        delay = atoi(argv[2]);

    // main loop
    while (1)
    {
        // handle quitting the program
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                return 0;
            }
            else
            {
                handleKey(&chip8, event.key.keysym.scancode, event.type == SDL_KEYDOWN);
            }
        }
        cycle(&chip8);

        // redraw display if drawFlag is true
        if (chip8.drawFlag)
        {
            redrawDisplay(&components, &chip8);
            chip8.drawFlag = 0;
        }

        SDL_Delay(delay);
    }
    destroySDL(&components);
    return 0;
}
