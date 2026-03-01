#include <stdio.h>

#define N 8

int solucionesUnicasGuardadas[12][N][N] = {0};
int contadorSolucionesUnicas = 0;

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

int esSimetrico(int tablero[N][N]) {
    int temp[N][N];
    int simetria[N][N];

    for (int k = 0; k < contadorSolucionesUnicas; k++) {
        copiarTablero(temp, tablero);
        
        for (int s = 0; s < 8; s++) {
            
            if (s > 0 && s < 4) {
                rotar90(temp, simetria);
                copiarTablero(temp, simetria);
            }
            
            else if (s == 4) {
                 reflejarHorizontal(tablero, temp);
                 copiarTablero(simetria, temp);
            }
            
            else if (s > 4) {
                rotar90(temp, simetria);
                copiarTablero(temp, simetria);
            }
            
            else {
                copiarTablero(simetria, tablero); 
            }
            
            int sonIguales = 1;
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    if (simetria[i][j] != solucionesUnicasGuardadas[k][i][j]) {
                        sonIguales = 0;
                        break;
                    }
                }
                if (!sonIguales) break;
            }

            if (sonIguales) {
                return 1;
            }
        }
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


int resolverNReinas(int tablero[N][N]) {
    return resolverNReinasUtil(tablero, 0);
}

int main() {
    int tablero[N][N] = {0};

    printf("Resolviendo el problema de las %d-Reinas y mostrando SOLO las 12 posibles soluciones unicas...\n\n", N);

    resolverNReinas(tablero);

    printf("========================================\n");
    printf("RESUMEN:\n");
    printf("Soluciones unicas (sin simetrias, rotaciones o reflexiones): %d\n", contadorSolucionesUnicas);

    return 0;
}

    for (int fila = 0; fila < N; fila++) {
        if (esSeguro(tablero, fila, columna)) {
            tablero[fila][columna] = 1;

            soluciones_en_este_nodo += resolverNReinasUtil(tablero, columna + 1);

            tablero[fila][columna] = 0;
        }
    }

    return soluciones_en_este_nodo;
}

int resolverNReinas(int tablero[N][N]) {
    return resolverNReinasUtil(tablero, 0);
}

int main() {
    int tablero[N][N] = {0};

    printf("Resolviendo el problema de las %d-Reinas y mostrando SOLO las 12 posibles soluciones unicas...\n\n", N);

    resolverNReinas(tablero);

    printf("========================================\n");
    printf("RESUMEN:\n");
    printf("Soluciones unicas (sin simetrias, rotaciones o reflexiones): %d\n", contadorSolucionesUnicas);

    return 0;
}