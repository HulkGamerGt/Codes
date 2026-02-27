#include <stdio.h>
#include <string.h>

#define FIL_COL 5

// Prototipos de funciones
void buscar_palabras(char matriz[FIL_COL][FIL_COL], char *palabras[], int num_palabras);
int buscar_direccion(char matriz[FIL_COL][FIL_COL], int fila, int col, char *palabra);
void mostrar_coordenadas(char *palabra, int fila_inicio, int col_inicio, int dir_fila, int dir_col);

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

    // Mostrar la matriz
    printf("Matriz de letras:\n");
    for (int i = 0; i < FIL_COL; i++) {
        for (int j = 0; j < FIL_COL; j++) {
            printf("%c ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    // Llamar a la función principal de búsqueda
    buscar_palabras(matriz, palabras, num_palabras);

    return 0;
}

// Función que recorre la matriz y las palabras para buscar coincidencias.
void buscar_palabras(char matriz[FIL_COL][FIL_COL], char *palabras[], int num_palabras) {
    int i, j, k;
    for (k = 0; k < num_palabras; k++) {
        char *palabra = palabras[k];
        int longitud = strlen(palabra);
        int encontrada = 0;

        for (i = 0; i < FIL_COL && !encontrada; i++) {
            for (j = 0; j < FIL_COL && !encontrada; j++) {
                if (matriz[i][j] == palabra[0]) {
                    if (buscar_direccion(matriz, i, j, palabra)) {
                        encontrada = 1;
                    }
                }
            }
        }
    }
}

// Función para buscar una palabra en todas las direcciones desde una posición inicial.
int buscar_direccion(char matriz[FIL_COL][FIL_COL], int fila, int col, char *palabra) {
    int d;
    int dir_fila[] = {0, 0, 1, -1, 1, -1, 1, -1};
    int dir_col[] = {1, -1, 0, 0, 1, -1, -1, 1};
    int longitud = strlen(palabra);

    for (d = 0; d < 8; d++) {
        int r = fila + dir_fila[d];
        int c = col + dir_col[d];
        int k;
        
        for (k = 1; k < longitud; k++) {
            if (r < 0 || r >= FIL_COL || c < 0 || c >= FIL_COL || matriz[r][c] != palabra[k]) {
                break;
            }
            r += dir_fila[d];
            c += dir_col[d];
        }

        if (k == longitud) {
            // Palabra encontrada. Llama a la función para mostrar las coordenadas.
            mostrar_coordenadas(palabra, fila, col, dir_fila[d], dir_col[d]);
            return 1;
        }
    }
    return 0; // Palabra no encontrada desde esta posición
}

// Función para mostrar las coordenadas de la palabra encontrada.
void mostrar_coordenadas(char *palabra, int fila_inicio, int col_inicio, int dir_fila, int dir_col) {
    printf("Palabra encontrada: %s\n", palabra);
    int longitud = strlen(palabra);

    for (int i = 0; i < longitud; i++) {
        int fila = fila_inicio + i * dir_fila;
        int col = col_inicio + i * dir_col;
        printf("%c=%d,%d ", palabra[i], fila, col);
    }
    printf("\n\n");
}