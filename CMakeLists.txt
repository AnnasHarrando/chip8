cmake_minimum_required(VERSION 3.21)
project(chip8)

set(CMAKE_CXX_STANDARD 14)

set(SDL2_INCLUDE_DIR "/home/annas/CLionProjects/chip8/sdl2/SDL2-2.0.20/include")
set(SDL2_LIB_DIR "/home/annas/CLionProjects/chip8/sdl2/SDL2-2.0.20/lib/x86")

include_directories( ${SDL2_INCLUDE_DIR} )
link_directories(${SDL2_LIB_DIR})

add_executable(chip8 src/main.cpp)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2)
