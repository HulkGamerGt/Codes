/*
 * Identificación del autor: Diego Solis Rojas
 * Fecha: 01 / 09 / 2025
 * Tema: Escanea un archivo llamado "Matrix.txt" en el cual contiene una sopa de letras, siendo 
 * asi que se busca palabras en dicha sopa y la salida se muestra en un archivo de texto llamado "Salida.txt".
*/
 
#include <stdio.h>
#include <string.h>

#define FIL_COL 5

/* Declarar prototipos de funciones */
void procesar_archivo(FILE *);
void buscar_palabras(char matriz[FIL_COL][FIL_COL], char *palabras[], int num_palabras);
int buscar_direccion(char matriz[FIL_COL][FIL_COL], int fila, int col, char *palabra);
void mostrar_coordenadas(char *palabra, int fila_inicio, int col_inicio, int dir_fila, int dir_col);

int main() {
    FILE *archivo;
    archivo = fopen("Matrix.txt","r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }
    procesar_archivo(archivo);
    fclose(archivo);
    return 0;
}

void procesar_archivo(FILE *archivo) {
    char *palabras[] = {"CASA", "RATOS", "CALAS", "LOSA", "RATON", "SOLO", "SALA"};
    char matriz[FIL_COL][FIL_COL];

    for (int i = 0; i < FIL_COL; i++) {
        for (int j = 0; j < FIL_COL; j++) {
            fscanf(archivo, " %c", &matriz[i][j]);// Lee cada carácter, ignorando espacios
        }
    }
    int num_palabras = sizeof(palabras) / sizeof(palabras[0]); // Calcula el número de palabras
    
    buscar_palabras(matriz, palabras, num_palabras);
    fclose(archivo);
}

// Lógica de búsqueda principal. Itera a través de cada palabra y cada celda de la matriz.
void buscar_palabras(char matriz[FIL_COL][FIL_COL], char *palabras[], int num_palabras) {
    for (int i = 0; i < num_palabras; i++) {
        char *palabra = palabras[i];
        int encontrada = 0;
        
        // Itera a través de cada celda de la matriz para encontrar la primera letra
        for (int f = 0; f < FIL_COL; f++) {
            for (int c = 0; c < FIL_COL; c++) {
                if (matriz[f][c] == palabra[0]) {
                    // Si la primera letra coincide, llama a buscar_direccion
                    if (buscar_direccion(matriz, f, c, palabra)) {
                        encontrada = 1; // Marca que la palabra fue encontrada
                    }
                }
            }
        }

        if (!encontrada) {
            printf("Palabra no encontrada: %s\n\n", palabra);
        }
    }
}

// Búsqueda en 8 direcciones desde una posición inicial.
int buscar_direccion(char matriz[FIL_COL][FIL_COL], int fila, int col, char *palabra) {
    int dir_fila[] = {0, 0, 1, -1, 1, -1, 1, -1}; // Direcciones: derecha, izquierda, abajo, arriba, diagonales
    int dir_col[] = {1, -1, 0, 0, 1, -1, -1, 1};
    int longitud = strlen(palabra);

    for (int d = 0; d < 8; d++) {
        int r = fila;
        int c = col;
        int k;

        // Verifica si la palabra cabe en la dirección actual
        for (k = 0; k < longitud; k++) {
            // Comprueba límites antes de acceder a la matriz
            if (r < 0 || r >= FIL_COL || c < 0 || c >= FIL_COL) {
                break; // Fuera de los límites, termina esta dirección
            }
            if (matriz[r][c] != palabra[k]) {
                break; // Letra no coincide, termina esta dirección
            }
            r += dir_fila[d];
            c += dir_col[d];
        }

        if (k == longitud) {
            mostrar_coordenadas(palabra, fila, col, dir_fila[d], dir_col[d]);
            return 1; // Palabra encontrada en esta dirección
        }
    }

    return 0; // Palabra no encontrada en ninguna dirección
}

// Función que muestra las coordenadas de una palabra.
void mostrar_coordenadas(char *palabra, int fila_inicio, int col_inicio, int dir_fila, int dir_col) {
    FILE *Salida;
    Salida = fopen("Salida.txt","a");
    if (Salida == NULL) {
        printf("Error al abrir el archivo de salida.\n");
        return;
    }
    fprintf(Salida, "Palabra encontrada: %s\n", palabra);
    int longitud = strlen(palabra);
    
    for (int i = 0; i < longitud; i++) {
        int fila = fila_inicio + i * dir_fila;
        int col = col_inicio + i * dir_col;
        fprintf(Salida, "%c = (%d, %d) ", palabra[i], fila, col);
    }
    fprintf(Salida, "\n\n");
    fclose(Salida);
}
/*
    for(int i=0;imput[i]!=\0;i++){
        if(imput[i] != ' '){
            output[j++]=imput[i];  
        }
    }
*/
    /*Muestra la matriz
    printf("Matriz de letras:\n");
    for (int i = 0; i < FIL_COL; i++) {
        for (int j = 0; j < FIL_COL; j++) {
            fprintf(archivo, "%c  ", matriz[i][j]);
        }
        fprintf(archivo, "\n");
    }
    fprintf(archivo, "\n");*/

    