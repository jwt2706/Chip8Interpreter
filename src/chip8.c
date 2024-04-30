#include <stdio.h>
#include "../include/chip8.h"

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

void initChip8(struct chip8* chip8) {
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
    clearDisplay(chip8);

    // memory
    for (int i = 0; i < 4096; i++) chip8->memory[i] = 0;

    // load the fontset
    for (int i = 0; i < 80; i++) chip8->memory[i] = fontset[i];
}

void clearDisplay(struct chip8* chip8) {
    for (int i = 0; i < 64 * 32; i++) chip8->gfx[i] = 0;
}

void cycle(struct chip8* chip8) {
    // get the opcode
    // since the opcode is 2 bytes long (8-bits * 2 = 16-bits), we need to merge the two bytes into a single 16-bit value
    chip8->opcode = chip8->memory[chip8->pc] << 8 | chip8->memory[chip8->pc + 1];

    // basically just fetching the hex value at wherever the "F" is in the hex code
    // this'll make the case switch a little cleaner
    unsigned short X = (chip8->opcode & 0x0F00) >> 8;   // second hex
    unsigned short Y = (chip8->opcode & 0x00F0) >> 4;   // third hex
    unsigned short N = chip8->opcode & 0x000F;          // fourth hex
    unsigned short NN = chip8->opcode & 0x00FF;         // third and fourth hex
    unsigned short NNN = chip8->opcode & 0x0FFF;        // second, third, and fourth hex

    // decode and execute the opcode
    switch (chip8->opcode & 0xF000) { // compare the first hex, since that's defining the type of instruction
        case 0x0000:
            switch (chip8->opcode & 0x000F) {
                case 0x0000: // 00E0: Clear the display
                    clearDisplay(chip8);
                    break;
                case 0x000E: // 00EE: Returns from a subroutine
                    // TODO
                    break;
            }
            break;
        case 0x1000: // 1NNN: Jumps to address NNN
            chip8->pc = NNN;
            break;
        case 0x2000: // 2NNN: Calls subroutine at NNN
            // TODO
            break;
        case 0x3000: // 3XNN: Skips the next instruction if VX equals NN
            // TODO
            break;
        case 0x4000: // 4XNN: Skips the next instruction if VX doesn't equal NN
            // TODO
            break;
        case 0x5000: // 5XY0: Skips the next instruction if VX equals VY
            // TODO
            break;
        case 0x6000: // 6XNN: Sets VX to NN
            chip8->V[X] = NN;
            chip8->pc += 2;
            break;
        case 0x7000: // 7XNN: Adds NN to VX
            chip8->V[X] += NN;
            chip8->pc += 2;
            break;
        case 0x8000:
            switch (chip8->opcode & 0x000F) {
                case 0x0000: // 8XY0: Sets VX to the value of VY
                    // TODO
                    break;
                case 0x0001: // 8XY1: Sets VX to VX OR VY
                    // TODO
                    break;
                case 0x0002: // 8XY2: Sets VX to VX AND VY
                    // TODO
                    break;
                case 0x0003: // 8XY3: Sets VX to VX XOR VY
                    // TODO
                    break;
                case 0x0004: // 8XY4: Adds VY to VX. VF is set to 1 when there's a carry, and to 0 when there isn't
                    // TODO
                    break;
                case 0x0005: // 8XY5: VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there isn't
                    // TODO
                    break;
                case 0x0006: // 8XY6: Shifts VX right by one. VF is set to the value of the least significant bit of VX before the shift
                    // TODO
                    break;
                case 0x0007: // 8XY7: Sets VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there isn't
                    // TODO
                    break;
                case 0x000E: // 8XYE: Shifts VX left by one. VF is set to the value of the most significant bit of VX before the shift
                    // TODO
                    break;
            }
            break;
        case 0x9000: // 9XY0: Skips the next instruction if VX doesn't equal VY
            // TODO
            break;
        case 0xA000: // ANNN: Sets I to the address NNN
            chip8->I = NNN;
            chip8->pc += 2;
            break;
        case 0xB000: // BNNN: Jumps to the address NNN plus V0
            // TODO
            break;
        case 0xC000: // CXNN: Sets VX to the result of a bitwise AND operation on a random number and NN
            // TODO
            break;
        case 0xD000: // DXYN: Draws a sprite at coordinate (VX, VY) that has a width of 8 pixels and a height of N pixels
            unsigned short x = chip8->V[X];
            unsigned short y = chip8->V[Y];
            unsigned short height = N;
            unsigned short pixel;
\
            chip8->V[0xF] = 0;
            for (int yline = 0; yline < height; yline++) {
                pixel = chip8->memory[chip8->I + yline];
                for (int xline = 0; xline < 8; xline++) {
                    if ((pixel & (0x80 >> xline)) != 0) {
                        if (chip8->gfx[(x + xline + ((y + yline) * 64))] == 1) {
                            chip8->V[0xF] = 1;
                        }
                        chip8->gfx[x + xline + ((y + yline) * 64)] ^= 1;
                    }
                }
            }

            chip8->drawFlag = 1;
            chip8->pc += 2;

            break;
        case 0xE000:
            switch (chip8->opcode & 0x00FF) {
                case 0x009E: // EX9E: Skips the next instruction if the key stored in VX is pressed
                    // TODO
                    break;
                case 0x00A1: // EXA1: Skips the next instruction if the key stored in VX isn't pressed
                    // TODO
                    break;
            }
            break;
        case 0xF000:
            switch (chip8->opcode & 0x00FF) {
                case 0x0007: // FX07: Sets VX to the value of the delay timer
                    // TODO
                    break;
                case 0x000A: // FX0A: A key press is awaited, and then stored in VX
                    // TODO
                    break;
                case 0x0015: // FX15: Sets the delay timer to VX
                    // TODO
                    break;
                case 0x0018: // FX18: Sets the sound timer to VX
                    // TODO
                    break;
                case 0x001E: // FX1E: Adds VX to I
                    // TODO
                    break;
                case 0x0029: // FX29: Sets I to the location of the sprite for the character in VX
                    // TODO
                    break;
                case 0x0033: // FX33: Stores the binary-coded decimal representation of VX at the addresses I, I plus 1, and I plus 2
                    // TODO
                    break;
                case 0x0055: // FX55: Stores V0 to VX (including VX) in memory starting at address I
                    // TODO
                    break;
                case 0x0065: // FX65: Fills V0 to VX (including VX) with values from memory starting at address I
                    // TODO
                    break;
            }
            break;
        default:
            printf("Unknown opcode: 0x%X\n", chip8->opcode);
    }

    // update timers
    if (chip8->delayTimer > 0) {
        chip8->delayTimer--;
    }

    if (chip8->soundTimer > 0) {
        if (chip8->soundTimer == 1) {
            // play a sound
        }
        chip8->soundTimer--;
    }
}

struct chip8 chip8;