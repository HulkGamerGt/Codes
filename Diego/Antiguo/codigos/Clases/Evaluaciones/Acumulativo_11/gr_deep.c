#include <stdio.h>
#include <string.h>

#define FILAS 3
#define COLUMNAS 3
#define MAX_MOVIMIENTOS 35
#define MAX_COLA 100000  // Aumentado para puzzles complejos

typedef struct { int celdas[FILAS][COLUMNAS]; } Tablero;
typedef struct { int fila, col; } Pos;

int df[] = { 0, 1, 0, -1};
int dc[] = { 1, 0,-1,  0};
char *dirs[] = {"DERECHA", "ABAJO", "IZQUIERDA", "ARRIBA"};

Tablero cola[MAX_COLA];
int padre[MAX_COLA];
int mov_dir[MAX_COLA];
int num_mov[MAX_COLA];
int frente, fondo;

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

// Verificar si el puzzle tiene solución
int tiene_solucion(Tablero *t) {
    int inversiones = 0;
    int arr[8];
    int k = 0;
    
    // Convertir matriz a array (ignorando el 0)
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (t->celdas[i][j] != 0) {
                arr[k++] = t->celdas[i][j];
            }
        }
    }
    
    // Contar inversiones
    for (int i = 0; i < 8; i++) {
        for (int j = i + 1; j < 8; j++) {
            if (arr[i] > arr[j]) {
                inversiones++;
            }
        }
    }
    
    return (inversiones % 2 == 0);
}

// FUNCIÓN 2: Validación de entrada del usuario
int validar_entrada(char *entrada, Tablero *tablero) {
    int numeros[9] = {0};
    char temp[100];
    char *token;
    int count = 0;
    int i, j;
    
    strcpy(temp, entrada);
    
    if (strlen(temp) == 0) {
        return 0;
    }
    
    token = strtok(temp, "-");
    
    while (token != NULL && count < 9) {
        if (strlen(token) != 1) {
            return 0;
        }
        
        if (token[0] < '0' || token[0] > '8') {
            return 0;
        }
        
        int num = token[0] - '0';
        
        if (numeros[num] == 1) {
            return 0;
        }
        
        numeros[num] = 1;
        
        i = count / 3;
        j = count % 3;
        tablero->celdas[i][j] = num;
        
        count++;
        token = strtok(NULL, "-");
    }
    
    return (count == 9);
}

// FUNCIÓN 3: Mostrar estado de la matriz
void mostrar_tablero(Tablero *t) {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (t->celdas[i][j] == 0) {
                printf("   ");
            } else {
                printf(" %d ", t->celdas[i][j]);
            }
            if (j < COLUMNAS - 1) printf("|");
        }
        printf("\n");
        if (i < FILAS - 1) printf("---+---+---\n");
    }
}

// FUNCIÓN 6: Buscar solución del puzzle
int buscar_solucion(Tablero *inicio, Tablero *objetivo) {
    Tablero visitado[MAX_COLA];
    int n_visitados = 0;

    frente = 0;
    fondo = 0;
    
    copiar(inicio, &cola[fondo]);
    padre[fondo] = -1;
    mov_dir[fondo] = -1;
    num_mov[fondo] = -1;
    fondo++;

    copiar(inicio, &visitado[n_visitados++]);

    int estados_explorados = 0;
    
    while (frente < fondo && fondo < MAX_COLA) {
        Tablero actual = cola[frente];
        int idx_actual = frente;
        estados_explorados++;

        if (estados_explorados % 10000 == 0) {
            printf("Explorando... %d estados analizados\n", estados_explorados);
        }

        if (iguales(&actual, objetivo)) {
            int camino[MAX_MOVIMIENTOS];
            int pasos = 0;
            int i = idx_actual;

            while (i != -1) {
                camino[pasos] = i;
                pasos++;
                i = padre[i];
            }

            printf("\nSOLUCION ENCONTRADA\n");
            printf("Movimientos: %d\n", pasos - 1);
            printf("Estados explorados: %d\n\n", estados_explorados);
            
            for (int k = pasos - 2; k >= 0; k--) {
                int idx = camino[k];
                printf("Paso %d: Mover %d hacia %s\n", 
                       pasos - 1 - k, num_mov[idx], dirs[mov_dir[idx]]);
                mostrar_tablero(&cola[idx]);
                printf("\n");
            }
            return 1;
        }

        Pos v = vacio(&actual);
        for (int d = 0; d < 4; d++) {
            int nf = v.fila + df[d];
            int nc = v.col + dc[d];
            if (nf < 0 || nf >= FILAS || nc < 0 || nc >= COLUMNAS) continue;

            Tablero sig;
            copiar(&actual, &sig);
            int num_que_se_mueve = sig.celdas[nf][nc];
            swap(&sig.celdas[v.fila][v.col], &sig.celdas[nf][nc]);

            int visto = 0;
            for (int j = 0; j < n_visitados; j++) {
                if (iguales(&sig, &visitado[j])) { 
                    visto = 1; 
                    break; 
                }
            }
            if (visto) continue;

            if (fondo < MAX_COLA) {
                copiar(&sig, &cola[fondo]);
                padre[fondo] = idx_actual;
                mov_dir[fondo] = d;
                num_mov[fondo] = num_que_se_mueve;
                fondo++;

                if (n_visitados < MAX_COLA) {
                    copiar(&sig, &visitado[n_visitados]);
                    n_visitados++;
                }
            }
        }
        frente++;
    }
    
    printf("Estados explorados: %d\n", estados_explorados);
    printf("Limite de cola alcanzado: %d\n", fondo);
    return 0;
}

int main() {
    Tablero objetivo = {{{1,2,3}, {4,5,6}, {7,8,0}}};
    Tablero inicial;
    char entrada[100];

    printf("8-PUZZLE SOLVER\n\n");

    printf("Formato de entrada: 1-2-3-4-5-6-7-8-0\n");
    printf("Ingrese configuracion inicial: ");
    
    if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
        printf("Error al leer la entrada.\n");
        return 1;
    }
    
    entrada[strcspn(entrada, "\n")] = 0;

    if (!validar_entrada(entrada, &inicial)) {
        printf("Error: Formato incorrecto. Use numeros del 0-8 sin repeticiones.\n");
        return 1;
    }

    printf("\nMatriz inicial:\n");
    mostrar_tablero(&inicial);

    printf("\nObjetivo:\n");
    mostrar_tablero(&objetivo);

    // Verificar si tiene solución
    if (!tiene_solucion(&inicial)) {
        printf("\n❌ ESTE PUZZLE NO TIENE SOLUCION\n");
        printf("El numero de inversiones es impar, por lo que es imposible resolverlo.\n");
        return 0;
    }

    printf("\nResolviendo... (Este puzzle puede requerir hasta 31 movimientos)\n");
    printf("Paciencia, puede tomar varios segundos...\n\n");
    
    if (!buscar_solucion(&inicial, &objetivo)) {
        printf("\nNO SE ENCONTRO SOLUCION EN EL LIMITE ACTUAL\n");
        printf("Posibles causas:\n");
        printf("- El puzzle requiere mas de %d movimientos\n", MAX_MOVIMIENTOS);
        printf("- Se agoto la memoria (%d estados maximos)\n", MAX_COLA);
        printf("- El puzzle es demasiado complejo\n");
    }

    return 0;
}