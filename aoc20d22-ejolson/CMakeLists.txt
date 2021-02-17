cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(aoc20d22-ejolson_project)
pico_sdk_init()

add_executable(aoc20d22-ejolson
    aoc20d22-ejolson.c
    )

# link pico standard library
target_link_libraries(aoc20d22-ejolson pico_stdlib)

# run from SRAM
pico_set_binary_type(aoc20d22-ejolson no_flash)

# enable usb output, disable uart output
pico_enable_stdio_usb(aoc20d22-ejolson 1)
pico_enable_stdio_uart(aoc20d22-ejolson 0)

# create .uf2
pico_add_extra_outputs(aoc20d22-ejolson)
