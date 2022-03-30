//
// Created by Hannes Furmans on 30.03.22.
//

#include "parser.h"
#include "mandelbrot.h"
#include <stack>
#include <cstdio>
#include "pico/stdlib.h"


unsigned short parse(unsigned char * instructions) {
    std::stack<unsigned short> open_brackets;
    unsigned short instruction_pointer = 0;
    // FILE * file = fopen("../hello.bf", "rb");
    unsigned int instruction_read_pointer = 0;
    while (instruction_pointer < 30000) {
        // int read_char = fgetc(file);
        if (instruction_read_pointer >= mandelbrot_bf_len) break;

        unsigned char read_char = mandelbrot_bf[instruction_read_pointer];

        if (read_char == EOF) break;

        if (read_char == INC_PTR) {
            instructions[instruction_pointer] = INC_PTR_D;
        } else if (read_char == DEC_PTR) {
            instructions[instruction_pointer] = DEC_PTR_D;
        } else if (read_char == INC_VAL) {
            instructions[instruction_pointer] = INC_VAL_D;
        } else if (read_char == DEC_VAL) {
            instructions[instruction_pointer] = DEC_VAL_D;
        } else if (read_char == PUT_CHR) {
            instructions[instruction_pointer] = PUT_CHR_D;
        } else if (read_char == GET_CHR) {
            instructions[instruction_pointer] = GET_CHR_D;
        } else if (read_char == JMP_FOR) {
            open_brackets.push(instruction_pointer);
            instructions[instruction_pointer] = JMP_FOR_D;
            instruction_pointer += 2;
        } else if (read_char == JMP_BCK) {
            unsigned short opening_bracket = open_brackets.top();
            open_brackets.pop();
            instructions[instruction_pointer] = JMP_BCK_D;
            unsigned char higher = (opening_bracket >> 8);
            auto lower = (unsigned char) (opening_bracket & 0xFF);
            unsigned short closing_bracket = instruction_pointer;
            instructions[++instruction_pointer] = higher;
            instructions[++instruction_pointer] = lower;
            unsigned char closing_higher = (closing_bracket >> 8);
            auto closing_lower = (unsigned char) (closing_bracket & 0xFF);
            instructions[opening_bracket + 1] = closing_higher;
            instructions[opening_bracket + 2] = closing_lower;
        } else {
            instructions[instruction_pointer] = COMMENT_D;
        }

        instruction_pointer++;
        instruction_read_pointer++;
    }
    // fclose(file);
    return instruction_pointer;
};