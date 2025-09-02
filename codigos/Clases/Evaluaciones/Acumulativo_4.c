/*
 * Identificación del autor: Diego Solis Rojas
 * Fecha: 01 / 09 / 2025
 * Tema: Búsqueda de palabras en una matriz, con un pequeño error en la lógica final.
*/

#include <stdio.h>
#include <string.h>

#define FIL_COL 5

/* declarar prototipos de funciones*/

// Prototipo para la función principal de búsqueda
void buscar_palabras(char matriz[FIL_COL][FIL_COL], char *palabras[], int num_palabras);

// Prototipo para la función que buscará en las 8 direcciones
int buscar_direccion(char matriz[FIL_COL][FIL_COL], int fila, int col, const char *palabra);

// Prototipo para la función que mostrará las coordenadas
void mostrar_coordenadas(const char *palabra, int fila_inicio, int col_inicio, int dir_fila, int dir_col);


int main() {
    char matriz[FIL_COL][FIL_COL] = {
        {'C', 'R', 'O', 'N', 'O'},
        {'A', 'A', 'S', 'O', 'L'},
        {'S', 'T', 'L', 'T', 'A'},
        {'A', 'O', 'L', 'A', 'R'},
        {'S', 'S', 'E', 'R', 'S'}
    };
    char *palabras[] = {"CASA", "RATOS", "CALAS", "LOSA", "RATON", "SOLO", "SALA"};
    
    int num_palabras = sizeof(palabras) / sizeof(palabras[0]);

    // Muestra la matriz
    printf("Matriz de letras:\n");
    for (int i = 0; i < FIL_COL; i++) {
        for (int j = 0; j < FIL_COL; j++) {
            printf("%c ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    buscar_palabras(matriz, palabras, num_palabras);
    
    return 0;
}

// Lógica de búsqueda principal. Itera a través de cada palabra y cada celda de la matriz.
void buscar_palabras(char matriz[FIL_COL][FIL_COL], char *palabras[], int num_palabras) {
    for (int i = 0; i < num_palabras; i++) {
        const char *palabra = palabras[i];
        int encontrada = 0;
        
        // Itera a través de cada celda de la matriz para encontrar la primera letra
        for (int f = 0; f < FIL_COL; f++) {
            for (int c = 0; c < FIL_COL; c++) {
                if (matriz[f][c] == palabra[0]) {
                    // Si la primera letra coincide, llama a buscar_direccion
                    if (buscar_direccion(matriz, f, c, palabra)) {
                        encontrada = 1;
                        break; // Sale del bucle interior si encuentra la palabra
                    }
                }
            }
            if (encontrada) break; // Sale del bucle exterior
        }

        if (!encontrada) {
            printf("Palabra no encontrada: %s\n\n", palabra);
        }
    }
}

// Búsqueda en 8 direcciones desde una posición inicial.
int buscar_direccion(char matriz[FIL_COL][FIL_COL], int fila, int col, const char *palabra) {
    int dir_fila[] = {0, 0, 1, -1, 1, -1, 1, -1};
    int dir_col[] = {1, -1, 0, 0, 1, -1, -1, 1};
    int longitud = strlen(palabra);
    int r, c, k;

    for (int d = 0; d < 8; d++) {
        r = fila;
        c = col;
        
        for (k = 0; k < longitud; k++) {
            if (r >= 0 && r < FIL_COL && c >= 0 && c < FIL_COL && matriz[r][c] == palabra[k]) {
                r += dir_fila[d];
                c += dir_col[d];
            } else {
                break;
            }
        }

        if (k == longitud) {
            mostrar_coordenadas(palabra, fila, col, dir_fila[d], dir_col[d]);
            return 1;
        }
    }

    return 0;
}

// Función que muestra las coordenadas de una palabra.
void mostrar_coordenadas(const char *palabra, int fila_inicio, int col_inicio, int dir_fila, int dir_col) {
    printf("Palabra encontrada: %s\n", palabra);
    int longitud = strlen(palabra);
    
    for (int i = 0; i < longitud; i++) {
        int fila = fila_inicio + i * dir_fila;
        int col = col_inicio + i * dir_col;
        printf("%c = (%d , %d) ", palabra[i], fila, col);
    }
    printf("\n\n");
}