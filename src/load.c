#include <stdio.h>
#include <stdlib.h>
#include "chip8.h"

void loadRom(strcut chip8* chip8, const char* filename) {
    FILE* rom = fopen(filename, "rb");
    if (rom == NULL) {
        printf("Failed to open the ROM file!\n");
        return;
    }

    fseek(rom, 0, SEEK_END);
    long romSize = ftell(rom);
    rewind(rom);

    /*
    if (romSize > 3584) {
        printf("ROM is too large to be loaded!\n");
        return;
    }
    */

    char* buffer = (char*)malloc(sizeof(char) * romSize);
    if (buffer == NULL) {
        printf("Failed to allocate memory for the ROM!\n");
        return;
    }

    size_t result = fread(buffer, sizeof(char), (size_t)romSize, rom);
    if (result != romSize) {
        printf("Failed to read the ROM!\n");
        return;
    }

    // load ROM into CHIP-8 memory
    for (int i = 0; i < romSize; i++) chip8->memory[i + 512] = buffer[i];

    fclose(rom);
    free(buffer);
}