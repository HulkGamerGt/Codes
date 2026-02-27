/* Autor: Diego Solis Rojas
Fecha: 25 / 08 / 2025
Tema:
*/

#include <stdio.h>

#define cant 10

/* Prototipos de funciones */
void Ordenar(int matriz[][cant], int Filas);
void Intercambio(int *v1, int *v2);
void Mostrar(int matriz[][cant], int Filas);

/* Función principal */
int main() {
    int Matriz[cant][cant] = {
        {64, 12, 95, 38, 71, 4, 27, 83, 56, 19},
        {23, 77, 9, 41, 88, 32, 60, 5, 94, 16},
        {45, 2, 67, 91, 10, 53, 78, 29, 86, 37},
        {18, 72, 6, 49, 85, 21, 63, 34, 97, 40},
        {31, 59, 13, 76, 24, 90, 47, 8, 82, 65},
        {54, 1, 79, 35, 92, 26, 68, 43, 15, 87},
        {7, 48, 84, 20, 73, 39, 96, 52, 30, 61},
        {42, 89, 17, 74, 3, 58, 25, 91, 66, 11},
        {80, 33, 69, 14, 55, 22, 75, 46, 98, 28},
        {36, 62, 93, 50, 81, 44, 19, 57, 0, 70}
    };

    Ordenar(Matriz, cant);

    return 0;
}

/* Función para ordenar la matriz */
void Ordenar(int matriz[][cant], int Filas) {
    int a, b, c;

    /* Bucle para iterar a través de cada fila */
    for (a = 0; a < Filas; a++) {
        /* Algoritmo de ordenamiento de burbuja para cada fila */
        for (b = 0; b < cant - 1; b++) {
            for (c = 0; c < cant - 1 - b; c++) {
                if (matriz[a][c] > matriz[a][c + 1]) {
                    Intercambio(&matriz[a][c], &matriz[a][c + 1]);
                }
            }
        }
    }
    Mostrar(matriz, Filas);
}

/* Función para intercambiar dos valores previamente definidos */
void Intercambio(int *v1, int *v2) {
    int temp = *v1;
    *v1 = *v2;
    *v2 = temp;
}

/* Función para mostrar la matriz */
void Mostrar(int matriz[][cant], int Filas) {
    int i, j;
    /* Impresión de la matriz */
    for (i = 0; i < Filas; i++) {
        for (j = 0; j < cant; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}