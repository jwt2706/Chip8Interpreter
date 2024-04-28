#include "chip8.h"

unsigned char fontset[80] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

void initialize(struct chip8* chip8) {
    // init/reset everything
    chip8->pc = 0x200;
    chip8->opcode = 0;
    chip8->I = 0;
    chip8->sp = 0;
    chip8->delayTimer = 0;
    chip8->soundTimer = 0;

    // stack and registers
    for (int i = 0; i < 16; i++) {
        chip8->stack[i] = 0;
        chip8->V[i] = 0;
    }

    // display
    for (int i = 0; i < 64 * 32; i++) chip8->gfx[i] = 0;

    // memory
    for (int i = 0; i < 4096; i++) chip8->memory[i] = 0;

    // load the fontset
    for (int i = 0; i < 80; i++) chip8->memory[i] = fontset[i];
}

void cycle(struct chip8* chip8) {
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
    if (chip8.delayTimer > 0) {
        chip8.delayTimer--;
    }

    if (chip8.soundTimer > 0) {
        if (chip8.soundTimer == 1) {
            // play a sound
        }
        chip8.soundTimer--;
    }
}

struct chip8 chip8;