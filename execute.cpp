//
// Created by Hannes Furmans on 30.03.22.
//

#include "execute.h"
#include "parser.h"
#include <cstdio>
#include <cstdlib>
#include "pico/stdlib.h"

void execute(const unsigned char * instructions, unsigned short instrution_limit) {
    // auto * memory = (unsigned char *) calloc(30000, sizeof(unsigned char));
    unsigned char gpio_value = 1;
    unsigned char memory[30000] = { 0 };

    for (unsigned char & i : memory) {
        i = 0;
    }
    unsigned int ptr = 0;
    unsigned int instruction_ptr = 0;
    while (instruction_ptr <= instrution_limit) {
        unsigned short instruction = instructions[instruction_ptr];
        if (instruction == INC_PTR_D) {
            ptr++;
        } else if (instruction == DEC_PTR_D) {
            ptr--;
        } else if (instruction == INC_VAL_D) {
            memory[ptr]++;
        } else if (instruction == DEC_VAL_D) {
            memory[ptr]--;
        } else if (instruction == PUT_CHR_D) {
            gpio_put(PICO_DEFAULT_LED_PIN, gpio_value);
            gpio_value ^= 1;
            printf("%c", memory[ptr]);
        } else if (instruction == GET_CHR_D) {
            memory[ptr] = getchar();
        } else if (instruction == COMMENT_D) {
        } else if (instruction == JMP_FOR_D) {
            if (memory[ptr] == 0) {
                unsigned short higher = (short)instructions[instruction_ptr + 1] << 8;
                unsigned short lower = instructions[instruction_ptr  + 2];
                unsigned short jump_to = higher + lower;
                instruction_ptr = jump_to;
            }
            instruction_ptr += 2;
        } else if (instruction == JMP_BCK_D) {
            if (memory[ptr] != 0) {
                unsigned short higher = (short)instructions[instruction_ptr + 1] << 8;
                unsigned short lower = instructions[instruction_ptr  + 2];
                unsigned short jump_to = higher + lower;
                instruction_ptr = jump_to;
            }
            instruction_ptr += 2;
        }
        instruction_ptr++;
    }
    // printf("\nstopping after %i instructions moved by\r\n", instruction_ptr);
}