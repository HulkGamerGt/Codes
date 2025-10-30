#include <stdio.h>
#include <string.h>

#define N 3

// ==== FUNCIONES ====

void mostrarMatriz(int matriz[N][N]) {
    printf("\nEstado actual del puzzle:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (matriz[i][j] == 0)
                printf("  _ ");
            else
                printf(" %d ", matriz[i][j]);
        }
        printf("\n");
    }
}

// Valida que el arreglo tenga los números 0 a 8 sin repeticiones
int validarEntrada(int arreglo[9]) {
    int usados[9] = {0};
    for (int i = 0; i < 9; i++) {
        if (arreglo[i] < 0 || arreglo[i] > 8)
            return 0;
        if (usados[arreglo[i]] == 1)
            return 0;
        usados[arreglo[i]] = 1;
    }
    return 1;
}

// Intercambio horizontal en la misma fila
void intercambioHorizontal(int matriz[N][N], int fila, int col1, int col2) {
    if (fila < 0 || fila >= N || col1 < 0 || col1 >= N || col2 < 0 || col2 >= N) {
        printf("Error: coordenadas fuera de rango.\n");
        return;
    }
    int temp = matriz[fila][col1];
    matriz[fila][col1] = matriz[fila][col2];
    matriz[fila][col2] = temp;
}

// Intercambio vertical en la misma columna
void intercambioVertical(int matriz[N][N], int col, int fila1, int fila2) {
    if (col < 0 || col >= N || fila1 < 0 || fila1 >= N || fila2 < 0 || fila2 >= N) {
        printf("Error: coordenadas fuera de rango.\n");
        return;
    }
    int temp = matriz[fila1][col];
    matriz[fila1][col] = matriz[fila2][col];
    matriz[fila2][col] = temp;
}

// Cuenta inversiones para saber si el puzzle tiene solución
int esSolucionable(int arreglo[9]) {
    int inversiones = 0;
    for (int i = 0; i < 9; i++) {
        if (arreglo[i] == 0) continue;
        for (int j = i + 1; j < 9; j++) {
            if (arreglo[j] != 0 && arreglo[i] > arreglo[j])
                inversiones++;
        }
    }
    return (inversiones % 2 == 0);
}

// ==== PROGRAMA PRINCIPAL ====
int main() {
    int entrada[9];
    int matriz[N][N];
    int i, j, k = 0;

    printf("=== Puzzle 3x3 ===\n");
    printf("Ingrese los numeros del 0 al 8 separados por espacio (ejemplo: 1 2 3 4 0 5 7 8 6)\n");

    for (i = 0; i < 9; i++) {
        if (scanf("%d", &entrada[i]) != 1) {
            printf("Error: solo se permiten numeros.\n");
            return 1;
        }
    }

    if (!validarEntrada(entrada)) {
        printf("Error: la secuencia debe contener los numeros del 0 al 8 sin repetir.\n");
        return 1;
    }

    // Cargar a matriz 3x3
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            matriz[i][j] = entrada[k++];
        }
    }

    mostrarMatriz(matriz);

    if (esSolucionable(entrada))
        printf("\nEl puzzle TIENE solucion.\n");
    else
        printf("\nEl puzzle NO tiene solucion.\n");

    // Ejemplo de intercambio horizontal
    printf("\nEjemplo de movimiento horizontal (fila 1, col 1 <-> col 2):\n");
    intercambioHorizontal(matriz, 1, 1, 2);
    mostrarMatriz(matriz);

    // Ejemplo de intercambio vertical
    printf("\nEjemplo de movimiento vertical (col 2, fila 0 <-> fila 1):\n");
    intercambioVertical(matriz, 2, 0, 1);
    mostrarMatriz(matriz);

    return 0;
