#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Se añade para sscanf y atoi, esenciales para la validación robusta

#define FILAS 3
#define COLUMNAS 3
#define MAX_MOVIMIENTOS 20
#define MAX_COLA 50000 // Máximo de estados a explorar

// Definiciones de estructuras
typedef struct { int celdas[FILAS][COLUMNAS]; } Tablero;
typedef struct { int fila, col; } Pos;

// Definiciones de movimientos
// df y dc representan el cambio en la posición (d=dirección)
int df[] = { 0, 1, 0, -1}; // Cambios de fila: Derecha, Abajo, Izquierda, Arriba
int dc[] = { 1, 0,-1,  0}; // Cambios de columna: Derecha, Abajo, Izquierda, Arriba
// Estos nombres corresponden a la dirección en la que se mueve la BALDOSA BLANCA (0)
char *dirs[] = {"DERECHA", "ABAJO", "IZQUIERDA", "ARRIBA"}; 

// Variables globales para la BFS
Tablero cola[MAX_COLA];
int padre[MAX_COLA];
int mov_dir[MAX_COLA];
int num_mov[MAX_COLA];
int profundidad[MAX_COLA];
int frente, fondo;

/* -----------------------------------------------------------------
 * FUNCIONES UTILITARIAS BÁSICAS
 * ----------------------------------------------------------------- */

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

/* -----------------------------------------------------------------
 * 3. FUNCIÓN PARA MOSTRAR EL ESTADO DE LA MATRIZ (REQUERIMIENTO)
 * ----------------------------------------------------------------- */

void mostrar_tablero(Tablero *t, char *titulo) {
    printf("\n=== %s ===\n", titulo);
    printf("+---+---+---+\n");
    for(int i = 0; i < FILAS; i++) {
        printf("|");
        for(int j = 0; j < COLUMNAS; j++){
            if(t->celdas[i][j] == 0){
                printf("   |");
            }else{
                printf(" %d |", t->celdas[i][j]);
            }
        }
        printf("\n+---+---+---+\n");
    }
}

/* -----------------------------------------------------------------
 * 2. FUNCIÓN DE ENTRADA Y VALIDACIÓN DE DATOS (REQUERIMIENTO)
 * ----------------------------------------------------------------- */

void leer_tablero_usuario(Tablero *t) {
    int valido = 0;
    int nums[9];
    char buffer[100];
    
    while(!valido) {
        printf("Ingrese el puzzle (ej: 7-3-5-8-0-2-1-4-6): ");
        
        // Leer la línea completa. Necesario para manejar errores de entrada no numérica.
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("ERROR: Lectura fallida. Intente de nuevo.\n");
            continue;
        }
        
        // Intentar parsear los 9 números separados por '-'
        int leidos = sscanf(buffer, "%d-%d-%d-%d-%d-%d-%d-%d-%d",
            &nums[0], &nums[1], &nums[2], &nums[3], &nums[4],
            &nums[5], &nums[6], &nums[7], &nums[8]);
        
        if(leidos != 9) {
            printf("ERROR: El formato es incorrecto. Debe ingresar exactamente 9 números separados por '-'.\n");
            continue; 
        }
        
        // Validar: Solo números del 0 al 8 sin repeticiones
        int usado[9] = {0};
        valido = 1;
        for(int i = 0; i < 9; i++) {
            int valor = nums[i];
            if (valor < 0 || valor > 8) {
                printf("ERROR: Valor fuera del rango (0-8).\n");
                valido = 0; break;
            }
            if (usado[valor] > 0) {
                printf("ERROR: Número %d repetido.\n", valor);
                valido = 0; break;
            }
            usado[valor] = 1;
        }
        
        if(valido) {
            // Copiar los números validados al tablero 3x3
            for(int i = 0; i < 9; i++) {
                t->celdas[i/COLUMNAS][i%COLUMNAS] = nums[i];
            }
        }
    }
}

/* -----------------------------------------------------------------
 * 4. FUNCIÓN PARA INTERCAMBIO HORIZONTAL (REQUERIMIENTO)
 * ----------------------------------------------------------------- */

void intercambiar_horizontal(Tablero *t, int f1, int c1, int f2, int c2) {
    printf("\n--- Intercambio de Posiciones ---\n");
    // Coordenadas válidas: 0-2
    if (f1 < 0 || f1 >= FILAS || c1 < 0 || c1 >= COLUMNAS ||
        f2 < 0 || f2 >= FILAS || c2 < 0 || c2 >= COLUMNAS) {
        printf("ERROR: Coordenadas fuera de rango (0-2).\n");
        return;
    }
    
    // Validar que sea un intercambio HORIZONTAL (misma fila, distinta columna)
    if (f1 != f2) {
        printf("ERROR: Las coordenadas deben estar en la misma fila (intercambio NO horizontal).\n");
        return;
    }
    
    printf("Permutando valores en (Fila %d, Columna %d): %d \n\t con (Fila %d, Columna %d): %d\n", 
           f1, c1, t->celdas[f1][c1], f2, c2, t->celdas[f2][c2]);
    
    swap(&t->celdas[f1][c1], &t->celdas[f2][c2]);
    printf("¡Permuta realizada con éxito!\n");
}


/* -----------------------------------------------------------------
 * BÚSQUEDA POR ANCHURA (BFS)
 * ----------------------------------------------------------------- */

int buscar(Tablero *inicio, Tablero *fin, Tablero *solucion_estados, int *solucion_movimientos, int *solucion_numeros, int *total_pasos) {
    Tablero visitado[MAX_COLA];
    int n_visitados = 0; // Se mantiene la búsqueda lineal lenta del original

    frente = 0;
    fondo = 0;
    
    // Inicializar la cola con el estado inicial
    copiar(inicio, &cola[fondo]);
    padre[fondo] = -1;
    mov_dir[fondo] = -1;
    num_mov[fondo] = -1;
    profundidad[fondo] = 0;
    fondo++;

    // Marcar el estado inicial como visitado
    copiar(inicio, &visitado[n_visitados++]);

    while (frente < fondo && fondo < MAX_COLA) {
        Tablero actual = cola[frente];
        int idx_actual = frente;
        int nivel = profundidad[frente];

        // Si la solución es encontrada
        if (iguales(&actual, fin)) {
            // Reconstrucción del camino
            int camino[MAX_MOVIMIENTOS + 1];
            int pasos = 0;
            int i = idx_actual;

            while (i != -1 && pasos <= MAX_MOVIMIENTOS) {
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

        // Generar los estados sucesores
        Pos v = vacio(&actual);
        for (int d = 0; d < 4; d++) {
            int nf = v.fila - df[d]; // NOTA: Aquí invertí la lógica del movimiento
            int nc = v.col - dc[d]; // para que df/dc representen el movimiento del hueco
            // El original tenía un error en df/dc y dirs, lo he corregido indirectamente
            // para que dirs coincida con el movimiento de la baldosa.
            // La baldosa se mueve hacia (df[d], dc[d]) y el hueco (v) va en dirección opuesta.

            // Chequeo de límites (baldosa que se mueve)
            if (nf < 0 || nf >= FILAS || nc < 0 || nc >= COLUMNAS) continue;

            Tablero sig;
            copiar(&actual, &sig);
            // El número que se mueve es el que está en la posición nf, nc
            int num_que_se_mueve = sig.celdas[nf][nc]; 
            swap(&sig.celdas[v.fila][v.col], &sig.celdas[nf][nc]);

            // Chequeo de estado visitado (lento O(N))
            int visto = 0;
            for (int j = 0; j < n_visitados; j++) {
                if (iguales(&sig, &visitado[j])) { 
                    visto = 1; 
                    break; 
                }
            }
            if (visto) continue;

            // Añadir a la cola y a visitados
            if (fondo < MAX_COLA && n_visitados < MAX_COLA) {
                copiar(&sig, &cola[fondo]);
                padre[fondo] = idx_actual;
                mov_dir[fondo] = d;
                num_mov[fondo] = num_que_se_mueve;
                profundidad[fondo] = nivel + 1;
                fondo++;

                copiar(&sig, &visitado[n_visitados]);
                n_visitados++;
            }
        }
        frente++;
    }
    return 0;
}

void mostrar_solucion(Tablero *inicio, Tablero *solucion_estados, int *solucion_movimientos, int *solucion_numeros, int total_pasos) {
    int movimientos_real = total_pasos - 1;

    printf("\n*** SOLUCIÓN ENCONTRADA ***\n");
    printf("Total de movimientos óptimos (BFS): %d\n", movimientos_real);

    mostrar_tablero(inicio, "0. ESTADO INICIAL");

    for (int i = 0; i < movimientos_real; i++) {
        printf("--- Paso %d ---\n", i + 1);
        printf("Movimiento: Mover número %d hacia %s\n", 
            solucion_numeros[i], dirs[solucion_movimientos[i]]);
        
        mostrar_tablero(&solucion_estados[i + 1], "Estado Resultante");
    }
}

/* -----------------------------------------------------------------
 * FUNCIÓN PRINCIPAL
 * ----------------------------------------------------------------- */

int main() {
    Tablero inicial, objetivo = {{{1,2,3}, {4,5,6}, {7,8,0}}};
    Tablero solucion_estados[MAX_MOVIMIENTOS + 1];
    int solucion_movimientos[MAX_MOVIMIENTOS];
    int solucion_numeros[MAX_MOVIMIENTOS];
    int total_pasos;
    int resultado;

    printf("=== RESOLVEDOR DE 8-PUZZLE (BFS) ===\n");
    printf("Maximo de estados a visitar: %d\n", MAX_COLA);
    
    // 2. Lectura y validación del usuario
    leer_tablero_usuario(&inicial);
    
    // 3. Mostrar estado inicial
    mostrar_tablero(&inicial, "ESTADO INICIAL SELECCIONADO");

    // 4. Demostración de Intercambio Horizontal
    printf("\n--- DEMOSTRACIÓN DE LA FUNCIÓN INTERCAMBIAR_HORIZONTAL ---\n");
    Tablero temp;
    copiar(&inicial, &temp);
    // Intenta permutar las celdas (Fila 2, Columna 0) y (Fila 2, Columna 2)
    intercambiar_horizontal(&temp, 2, 0, 2, 2); 
    mostrar_tablero(&temp, "Tablero Después de Permutar (2,0) y (2,2)");
    printf("-------------------------------------------------------------------\n");
    

    printf("\n--- INICIO DE LA BÚSQUEDA ÓPTIMA ---\n");
    
    resultado = buscar(&inicial, &objetivo, solucion_estados, solucion_movimientos, solucion_numeros, &total_pasos);

    if(resultado){
        mostrar_solucion(&inicial, solucion_estados, solucion_movimientos, solucion_numeros, total_pasos);
    }else{
        printf("\n✗ NO SE ENCONTRÓ SOLUCIÓN en el límite de %d estados (MAX_COLA).\n", MAX_COLA);
    }
    
    return 0;
}