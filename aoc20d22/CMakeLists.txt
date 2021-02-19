cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(Day22)
pico_sdk_init()

add_executable(Day22
    day22.c
    )

# link pico standard library
target_link_libraries(Day22 pico_stdlib)

# enable usb output, disable uart output
pico_enable_stdio_usb(Day22 1)
pico_enable_stdio_uart(Day22 0)

# create .uf2
pico_add_extra_outputs(Day22)
