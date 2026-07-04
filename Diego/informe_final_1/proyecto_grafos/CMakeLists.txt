cmake_minimum_required(VERSION 3.20)
project(proyecto_grafos)

set(CMAKE_C_STANDARD 99)

include_directories(src)

add_executable(ejercicio1 src/main_ejercicio1.c src/grafo.c src/distancias.c src/mst.c src/arbol.c src/arbol_binario.c src/salida.c)
add_executable(ejercicio2 src/main_ejercicio2.c src/grafo.c src/distancias.c src/caminos_minimos.c src/grasp_tsp.c src/arbol.c src/arbol_binario.c src/salida.c)
