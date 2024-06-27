cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(test_project C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Oz)
#add_compile_options(-flto)
add_compile_options(-fomit-frame-pointer)
add_compile_options(-DNDEBUG)

pico_sdk_init()

add_executable(
  main
  main.c
)

target_link_libraries(main pico_stdlib hardware_i2c)

#generates test.hex file
pico_add_extra_outputs(main)

# Enable usb output, disable uart output
pico_enable_stdio_usb(main 1)
pico_enable_stdio_uart(main 0)
