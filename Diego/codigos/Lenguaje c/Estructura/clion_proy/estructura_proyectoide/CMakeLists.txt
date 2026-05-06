cmake_minimum_required(VERSION 4.1)
project(ListasAplicacion C)

set(CMAKE_C_STANDARD 11)

add_executable(ListasAplicacion main.c
        include/lista.h
        src/lista.c)
