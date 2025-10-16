/*  Identificación del autor
    Nombre: Diego Solis Rojas
    Fecha: 13/10/2025
    tema: busca las posibles soluciones del problema de las 8 reinas, 12 soluciones encontradas
*/

#include <stdio.h>

#define N 8

/*variables globales*/
int solucionesGuardadas[12][N][N] = {0};
int contadorUnicas = 0;

void imprimirTablero(int tablero[N][N]) {
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (tablero[i][j] == 1) {
                printf(" Q ");
            } else {
                printf(" - ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void copiarTablero(int destino[N][N], int origen[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            destino[i][j] = origen[i][j];
        }
    }
}

void rotar90(int tablero[N][N], int nuevo[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            nuevo[j][N - 1 - i] = tablero[i][j];
        }
    }
}

void reflejarHorizontal(int tablero[N][N], int nuevo[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            nuevo[i][N - 1 - j] = tablero[i][j];
        }
    }
}

int comparar(int tableroA[N][N], int tableroB[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (tableroA[i][j] != tableroB[i][j]) {
                return 0; 
            }
        }
    }
    return 1;
}

int esSimetrico(int tablero[N][N]) {
    int transformado[N][N];
    int temporal[N][N];
    int esIgual;

    for (int k = 0; k < contadorUnicas; k++) {
        
        // 1. ORIGINAL
        copiarTablero(transformado, tablero);
        if (comparar(transformado, solucionesGuardadas[k])) return 1;

        // 2. ROTACION 90
        rotar90(transformado, temporal);
        copiarTablero(transformado, temporal);
        if (comparar(transformado, solucionesGuardadas[k])) return 1;

        // 3. ROTACION 180
        rotar90(transformado, temporal);
        copiarTablero(transformado, temporal);
        if (comparar(transformado, solucionesGuardadas[k])) return 1;

        // 4. ROTACION 270
        rotar90(transformado, temporal);
        copiarTablero(transformado, temporal);
        if (comparar(transformado, solucionesGuardadas[k])) return 1;
        
        // 5. REFLEJADO HORIZONTALMENTE
        reflejarHorizontal(tablero, transformado);
        if (comparar(transformado, solucionesGuardadas[k])) return 1;
        
        // 6. REFLEJADO + ROTACION 90
        rotar90(transformado, temporal);
        copiarTablero(transformado, temporal);
        if (comparar(transformado, solucionesGuardadas[k])) return 1;
        
        // 7. REFLEJADO + ROTACION 180
        rotar90(transformado, temporal);
        copiarTablero(transformado, temporal);
        if (comparar(transformado, solucionesGuardadas[k])) return 1;

        // 8. REFLEJADO + ROTACION 270
        rotar90(transformado, temporal);
        copiarTablero(transformado, temporal);
        if (comparar(transformado, solucionesGuardadas[k])) return 1;
    }

    return 0;
}

int esSeguro(int tablero[N][N], int fila, int columna) {
    int i, j;

    for (i = 0; i < columna; i++) {
        if (tablero[fila][i]) return 0;
    }

    for (i = fila, j = columna; i >= 0 && j >= 0; i--, j--) {
        if (tablero[i][j]) return 0;
    }

    for (i = fila, j = columna; j >= 0 && i < N; i++, j--) {
        if (tablero[i][j]) return 0;
    }

    return 1;
}

int resolverNReinasUtil(int tablero[N][N], int columna) {
    if (columna >= N) {
        
        if (!esSimetrico(tablero) && contadorUnicas < 12) {
            
            copiarTablero(solucionesGuardadas[contadorUnicas], tablero);
            printf("----------------------------------------\n");
            printf("SOLUCION UNICA #%d ENCONTRADA:\n", contadorUnicas + 1);
            imprimirTablero(tablero);
            contadorUnicas++;
        }
        
        return 1;
    }
    
    int solucionesNodo = 0;
    
    for (int fila = 0; fila < N; fila++) {
        if (esSeguro(tablero, fila, columna)) {
            tablero[fila][columna] = 1;

            solucionesNodo += resolverNReinasUtil(tablero, columna + 1);

            tablero[fila][columna] = 0;
        }
    }

    return solucionesNodo;
}

int resolverNReinas(int tablero[N][N]) {
    return resolverNReinasUtil(tablero, 0);
}

int main() {
    int tablero[N][N];
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            tablero[i][j] = 0;
        }
    }
    
    printf("Resolviendo el problema de las %d-Reinas y mostrando SOLO las 12 soluciones unicas...\n\n", N);

    resolverNReinas(tablero);

    printf("-------------------------------------------\n");
    printf("Soluciones unicas encontradas: %d\n", contadorUnicas);

    return 0;
}