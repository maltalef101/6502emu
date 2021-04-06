cmake_minimum_required(VERSION 3.5)

if(${CMAKE_VERSION} VERSION_LESS 3.5)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(6502emu  VERSION 1.0
    DESCRIPTION "A very basic 6502 emulator."
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main src/main.cpp)
add_library(cpu STATIC src/cpu/cpu.cpp)
add_library(mem STATIC src/mem/mem.cpp)
