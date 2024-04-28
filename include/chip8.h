#ifndef CHIP8_H
#define CHIP8_H

// CHIP-8 system variables
// (NOTE: chars are 8-bits, shorts are 16-bits)
struct chip8 {
    unsigned short opcode; // current operation code
    unsigned char memory[4096]; // the CHIP-8 system has 4KB of memory
    unsigned char V[16]; // 16 general purpose 8-bit registers
    unsigned short I; // memory address
    unsigned short pc; // program counter
    unsigned char gfx[64 * 32]; // for the monochrome display (size of 64 * 32 pixels)
    unsigned char delayTimer; // self explanatory
    unsigned char soundTimer; // also self explanatory
    unsigned short stack[16]; // stack with 16 levels
    unsigned short sp; // stack pointer
    unsigned char key[16]; // keypad
};

void initialize(struct chip8* chip8);
void cycle(struct chip8* chip8);

#endif