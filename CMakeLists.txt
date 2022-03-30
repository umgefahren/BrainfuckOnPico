# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(BrainfuckOnPico C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(BrainfuckOnPico BrainfuckOnPico.cpp execute.h execute.cpp parser.h parser.cpp mandelbrot.h)

pico_set_program_name(BrainfuckOnPico "BrainfuckOnPico")
pico_set_program_version(BrainfuckOnPico "0.1")

pico_enable_stdio_uart(BrainfuckOnPico 0)
pico_enable_stdio_usb(BrainfuckOnPico 1)

# Add the standard library to the build
target_link_libraries(BrainfuckOnPico pico_stdlib)

pico_add_extra_outputs(BrainfuckOnPico)

