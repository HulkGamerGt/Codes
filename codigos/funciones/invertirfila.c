/* NO COMPATIBLE CON ANSI C */

#include <stdio.h>

#define TAMANO 3

void transponer(int original[TAMANO][TAMANO], int transpuesta[TAMANO][TAMANO]);
void mostrar(int matriz[TAMANO][TAMANO]);

int main() {
    int original[TAMANO][TAMANO];
    int transpuesta[TAMANO][TAMANO];
    
    // Leer la matriz original
    for (int i = 0; i < TAMANO; i++) {
        for (int j = 0; j < TAMANO; j++) {
            printf("Elemento [%d][%d]: ", i, j);
            scanf("%d", &original[i][j]);
        }
    }

    transponer(original, transpuesta);
  
    mostrar(transpuesta);
    mostrar(original);

    return 0;
}

void transponer(int original[TAMANO][TAMANO], int transpuesta[TAMANO][TAMANO]) {
    for (int i = 0; i < TAMANO; i++) {
        for (int j = 0; j < TAMANO; j++) {
            transpuesta[j][i] = original[i][j];
        }
    }
}

void mostrar(int matriz[TAMANO][TAMANO]) {
    printf("Matriz:\n");
    for (int i = 0; i < TAMANO; i++) {
        for (int j = 0; j < TAMANO; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}