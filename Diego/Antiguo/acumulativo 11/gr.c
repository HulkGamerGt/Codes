#include <stdio.h>
#include <string.h>

#define FILAS 3
#define COLUMNAS 3
#define MAX_MOVIMIENTOS 20
#define MAX_COLA 50000

typedef struct { int celdas[FILAS][COLUMNAS]; } Tablero;
typedef struct { int fila, col; } Pos;

int df[] = { 0, 1, 0, -1};
int dc[] = { 1, 0,-1,  0};
// Direcciones CORREGIDAS: cuando el vacío se mueve en una dirección, el número se mueve en la opuesta
char *dirs[] = {"IZQUIERDA", "ARRIBA", "DERECHA", "ABAJO"};

Tablero cola[MAX_COLA];
int padre[MAX_COLA];
int mov_dir[MAX_COLA];
int num_mov[MAX_COLA];
int profundidad[MAX_COLA];
int frente = 0, fondo = 0;

void copiar(Tablero *a, Tablero *b) { memcpy(b, a, sizeof(Tablero)); }
int iguales(Tablero *a, Tablero *b) { return memcmp(a, b, sizeof(Tablero)) == 0; }
void swap(int *a, int *b) { int t = *a; *a = *b; *b = t; }

Pos vacio(Tablero *t) {
    Pos p;
    for (int i = 0; i < FILAS; i++)
        for (int j = 0; j < COLUMNAS; j++)
            if (t->celdas[i][j] == 0) { p.fila = i; p.col = j; return p; }
    p.fila = p.col = -1; return p;
}

void leer(Tablero *t) {
    int v, usado[9] = {0}, ok;
    do {
        printf("Ingrese el puzzle (ej: 1-2-3-4-5-6-7-8-0): ");
        ok = scanf("%d-%d-%d-%d-%d-%d-%d-%d-%d",
            &t->celdas[0][0], &t->celdas[0][1], &t->celdas[0][2],
            &t->celdas[1][0], &t->celdas[1][1], &t->celdas[1][2],
            &t->celdas[2][0], &t->celdas[2][1], &t->celdas[2][2]) == 9;

        if (!ok) { 
            printf("Formato incorrecto. Use: 1-2-3-4-5-6-7-8-0\n");
            while(getchar() != '\n'); 
            continue; 
        }

        ok = 1;
        memset(usado, 0, sizeof(usado));
        for (int i = 0; i < FILAS && ok; i++)
            for (int j = 0; j < COLUMNAS; j++) {
                v = t->celdas[i][j];
                if (v < 0 || v > 8 || usado[v]++) ok = 0;
            }
        if (!ok) printf("Error: valores inválidos o repetidos.\n");
        while(getchar() != '\n');
    } while (!ok);
}

void mostrar(Tablero *t) {
    printf("+---+---+---+\n");
    for (int i = 0; i < FILAS; i++) {
        printf("|");
        for (int j = 0; j < COLUMNAS; j++) {
            if (t->celdas[i][j] == 0) {
                printf("   |");
            } else {
                printf(" %d |", t->celdas[i][j]);
            }
        }
        printf("\n+---+---+---+\n");
    }
}

int buscar(Tablero *inicio, Tablero *fin, Tablero *solucion_estados, int *solucion_movimientos, int *solucion_numeros, int *total_pasos) {
    Tablero visitado[MAX_COLA];
    int n_visitados = 0;

    frente = fondo = 0;
    copiar(inicio, &cola[fondo]);
    padre[fondo] = -1;
    mov_dir[fondo] = num_mov[fondo] = -1;
    profundidad[fondo] = 0;
    fondo++;

    copiar(inicio, &visitado[n_visitados++]);

    while (frente < fondo) {
        Tablero actual = cola[frente];
        int idx_actual = frente;
        int nivel = profundidad[frente];

        if (nivel > MAX_MOVIMIENTOS) {
            frente++;
            continue;
        }

        if (iguales(&actual, fin)) {
            int camino[MAX_COLA];
            int pasos = 0;
            int i = idx_actual;

            while (i != -1) {
                camino[pasos++] = i;
                i = padre[i];
            }

            *total_pasos = pasos;
            
            for (int k = 0; k < pasos; k++) {
                int idx = camino[pasos - 1 - k];
                copiar(&cola[idx], &solucion_estados[k]);
                if (k > 0) {
                    solucion_movimientos[k-1] = mov_dir[idx];
                    solucion_numeros[k-1] = num_mov[idx];
                }
            }
            return 1;
        }

        Pos v = vacio(&actual);
        for (int d = 0; d < 4; d++) {
            int nf = v.fila + df[d];
            int nc = v.col + dc[d];
            if (nf < 0 || nf >= FILAS || nc < 0 || nc >= COLUMNAS) continue;

            Tablero sig = actual;
            int num_que_se_mueve = sig.celdas[nf][nc];
            swap(&sig.celdas[v.fila][v.col], &sig.celdas[nf][nc]);

            int visto = 0;
            for (int j = 0; j < n_visitados; j++)
                if (iguales(&sig, &visitado[j])) { visto = 1; break; }
            if (visto) continue;

            if (fondo >= MAX_COLA) {
                printf("Error: no hay suficiente memoria para continuar.\n");
                return 0;
            }

            copiar(&sig, &cola[fondo]);
            padre[fondo] = idx_actual;
            mov_dir[fondo] = d;
            num_mov[fondo] = num_que_se_mueve;
            profundidad[fondo] = nivel + 1;
            fondo++;

            copiar(&sig, &visitado[n_visitados++]);
        }
        frente++;
    }
    return 0;
}

void mostrar_solucion_completa(Tablero *solucion_estados, int *solucion_movimientos, int *solucion_numeros, int total_pasos, Tablero *inicio) {
    printf("\n=========================================\n");
    printf("SOLUCION ENCONTRADA!\n");
    printf("Total de movimientos: %d\n", total_pasos - 1);
    printf("=========================================\n\n");

    printf("Estado inicial:\n");
    mostrar(inicio);
    printf("\n");

    for (int i = 1; i < total_pasos; i++) {
        printf("--- Paso %d ---\n", i);
        printf("Movimiento: Mover numero %d hacia %s\n", solucion_numeros[i-1], dirs[solucion_movimientos[i-1]]);
        printf("Estado resultante:\n");
        mostrar(&solucion_estados[i]);
        printf("\n");
    }

    printf("=========================================\n");
    printf("SOLUCION COMPLETADA!\n");
    printf("=========================================\n");
}

int main() {
    Tablero inicio, objetivo = {{
        {1,2,3},
        {4,5,6},
        {7,8,0}
    }};
    
    Tablero solucion_estados[MAX_MOVIMIENTOS + 1];
    int solucion_movimientos[MAX_MOVIMIENTOS];
    int solucion_numeros[MAX_MOVIMIENTOS];
    int total_pasos;
    int resultado;

    printf("RESOLVEDOR DE 8-PUZZLE\n");
    printf("Maximo de movimientos: %d\n\n", MAX_MOVIMIENTOS);

    leer(&inicio);
    
    printf("\nEstado inicial del puzzle:\n");
    mostrar(&inicio);

    printf("\nBuscando solucion...\n\n");

    resultado = buscar(&inicio, &objetivo, solucion_estados, solucion_movimientos, solucion_numeros, &total_pasos);

    if (resultado) {
        mostrar_solucion_completa(solucion_estados, solucion_movimientos, solucion_numeros, total_pasos, &inicio);
    } else {
        printf("\n=========================================\n");
        printf("NO SE ENCONTRO SOLUCION en %d movimientos\n", MAX_MOVIMIENTOS);
        printf("=========================================\n");
    }

    return 0;
}