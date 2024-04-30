#include <stdio.h>
#include <stdlib.h>
#include "../include/chip8.h"

int loadRom(struct chip8 *chip8, const char *filename)
{
    FILE *rom = fopen(filename, "rb");
    if (rom == NULL)
    {
        printf("Failed to open the ROM file!\n");
        return 1;
    }

    if (fseek(rom, 0, SEEK_END) != 0)
    {
        printf("Failed to seek to the end of the ROM file!\n");
        return 1;
    }

    long romSize = ftell(rom);
    if (romSize == -1)
    {
        printf("Failed to get the size of the ROM file!\n");
        return 1;
    }

    if (romSize > 3584)
    { // not 4096 because the first 512 bytes are reserved for the interpreter
        printf("ROM is too large to be loaded!\n");
        return 1;
    }

    if (romSize < 2)
    {
        printf("ROM is too small! This is not a valid program.\n");
        return 1;
    }

    rewind(rom);

    char *buffer = (char *)malloc(sizeof(char) * romSize);
    if (buffer == NULL)
    {
        printf("Failed to allocate memory for the ROM!\n");
        return 1;
    }

    size_t result = fread(buffer, sizeof(char), (size_t)romSize, rom);
    if (result != romSize)
    {
        printf("Failed to read the ROM!\n");
        return 1;
    }

    // load ROM into CHIP-8 memory
    for (int i = 0; i < romSize; i++)
        chip8->memory[i + 512] = buffer[i];

    fclose(rom);
    free(buffer);

    return 0;
}