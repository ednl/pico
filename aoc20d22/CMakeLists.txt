cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(aoc20d22_project)
pico_sdk_init()

add_executable(aoc20d22
    aoc20d22.c
    )

# link pico standard library
target_link_libraries(aoc20d22 pico_stdlib)

# enable usb output, disable uart output
pico_enable_stdio_usb(aoc20d22 1)
pico_enable_stdio_uart(aoc20d22 0)

# create .uf2
pico_add_extra_outputs(aoc20d22)
