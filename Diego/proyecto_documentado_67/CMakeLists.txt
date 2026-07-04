cmake_minimum_required(VERSION 3.10)
project(TSP_MST_Talca C)

# El codigo usa funciones de C99 (snprintf, INFINITY, declaraciones
# mixtas en algunos puntos), por lo que se exige ese estandar.
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra)
endif()

# Los ejecutables abren sus archivos de resultados con la ruta relativa
# "../resultados/...", asumiendo que se ejecutan desde dentro de la
# carpeta de build (p.ej. build/ai junto a resultados/ en la raiz del
# proyecto). Esta linea crea esa carpeta automaticamente si no existe.
file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/resultados")

# Biblioteca matematica (sqrt, sin, cos, asin, INFINITY), necesaria en
# sistemas tipo Unix; en otros (p.ej. MSVC) no suele requerirse.
find_library(MATH_LIBRARY m)

# Fuentes compartidas por ambos ejercicios (TADs y algoritmos).
set(FUENTES_COMUNES
    grafo.c
    distancias.c
    salida.c
    arbol.c
    arbol_binario.c
    mst.c
    caminos_minimos.c
    grasp_tsp.c
)

# Ejercicio 1: MST (Prim, Kruskal, Boruvka) sobre los POIs de Talca.
add_executable(ejercicio1
    main_ejercicio1.c
    ${FUENTES_COMUNES}
)

# Ejercicio 2: TSP mediante GRASP sobre las 5 zonas de Talca.
add_executable(ejercicio2
    main_ejercicio2.c
    ${FUENTES_COMUNES}
)

if(MATH_LIBRARY)
    target_link_libraries(ejercicio1 PRIVATE ${MATH_LIBRARY})
    target_link_libraries(ejercicio2 PRIVATE ${MATH_LIBRARY})
endif()
