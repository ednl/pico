cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(Day24)
pico_sdk_init()

add_executable(Day24
    day24.c
    )

# Diable Flash use, run from SRAM
pico_set_binary_type(Day24 no_flash)

# link pico standard library
target_link_libraries(Day24 pico_stdlib)

# enable usb output, disable uart output
pico_enable_stdio_usb(Day24 1)
pico_enable_stdio_uart(Day24 0)

# create .uf2
pico_add_extra_outputs(Day24)
