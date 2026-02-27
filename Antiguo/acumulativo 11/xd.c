#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILAS 3 
#define COLUMNAS 3
#define MAX_PROFUNDIDAD 31  // Límite de profundidad para DFS

/* FUNCIÓN DE INDEXACIÓN 1D */
int obtener_indice_1d(int i, int r, int c) {    
    return (i * FILAS * COLUMNAS) + (r * COLUMNAS) + c;
}

/* -----------------------------------------------------------------
 * PROTOTIPOS 
 * ----------------------------------------------------------------- */
void leer_datos_puzzle(int [FILAS][COLUMNAS]);
int resolver_puzzle_recursivo(int puzzle[FILAS][COLUMNAS], int objetivo[FILAS][COLUMNAS], 
                             int profundidad, int max_profundidad, int *historia, 
                             int *movimientos, int *ruta_actual, int *encontrado);
void prueba_matriz(int [FILAS][COLUMNAS]); 

/* UTILIDADES */
void copiar_tablero(int origen[FILAS][COLUMNAS], int destino[FILAS][COLUMNAS]);
int son_iguales(int t1[FILAS][COLUMNAS], int t2[FILAS][COLUMNAS]);
void intercambiar(int *a, int *b);
int buscar_0(int tablero[FILAS][COLUMNAS], int *fila, int *col);

int intercambio_horizontal(int tablero[FILAS][COLUMNAS], int r1, int c1, int r2, int c2); 
int intercambio_vertical(int tablero[FILAS][COLUMNAS], int r1, int c1, int r2, int c2); 

/* Utilitarios DFS recursivo */
int ya_visitado_recursivo(int *historia, int tablero[FILAS][COLUMNAS], int estados_visitados);
void imprimir_solucion_recursiva(int *historia, int *movimientos, int profundidad);
void guardar_estado(int *historia, int tablero[FILAS][COLUMNAS], int idx);

/* Direcciones de movimiento para el 0: ARRIBA, ABAJO, IZQUIERDA, DERECHA */
int dir_fila[] = {-1, 1, 0, 0}; 
int dir_col[] = {0, 0, -1, 1};
char *nombre_mov[] = {"ARRIBA", "ABAJO", "IZQUIERDA", "DERECHA"};

int main(){
    int puzzle[FILAS][COLUMNAS];
    int puzzle_resuelto[FILAS][COLUMNAS]={
        {1,2,3},
        {4,5,6},
        {7,8,0}
    };
    
    leer_datos_puzzle(puzzle);
    
    printf("\n--- ESTADO INICIAL ---\n");
    prueba_matriz(puzzle); 
    
    // Preparar estructuras para DFS recursivo
    size_t size_tableros = (MAX_PROFUNDIDAD + 1) * FILAS * COLUMNAS * sizeof(int);
    size_t size_movimientos = (MAX_PROFUNDIDAD + 1) * sizeof(int);
    
    int *historia = (int *)malloc(size_tableros);
    int *movimientos = (int *)malloc(size_movimientos);
    int *ruta_actual = (int *)malloc(size_movimientos);
    int encontrado = 0;
    
    if (!historia || !movimientos || !ruta_actual) {
        printf("ERROR: Fallo al asignar memoria.\n");
        free(historia); free(movimientos); free(ruta_actual);
        return 1;
    }
    
    // Guardar estado inicial
    guardar_estado(historia, puzzle, 0);
    
    printf("--- BUSCANDO SOLUCION (DFS Recursivo) ---\n");
    
    // Llamada recursiva principal
    int resultado = resolver_puzzle_recursivo(puzzle, puzzle_resuelto, 0, 
                                             MAX_PROFUNDIDAD, historia, 
                                             movimientos, ruta_actual, &encontrado);
    
    if (!encontrado) {
        printf("El puzzle no tiene solucion (o se excedio la profundidad maxima de %d).\n", MAX_PROFUNDIDAD);
    }
    
    free(historia);
    free(movimientos);
    free(ruta_actual);
    
    return 0;
}

/* -----------------------------------------------------------------
 * IMPLEMENTACIÓN DEL ALGORITMO DFS RECURSIVO
 * ----------------------------------------------------------------- */

int resolver_puzzle_recursivo(int actual[FILAS][COLUMNAS], int objetivo[FILAS][COLUMNAS], 
                             int profundidad, int max_profundidad, int *historia, 
                             int *movimientos, int *ruta_actual, int *encontrado) {
    
    // Caso base: solución encontrada
    if (son_iguales(actual, objetivo)) {
        printf("*** SOLUCION ENCONTRADA! ***\n");
        *encontrado = 1;
        imprimir_solucion_recursiva(historia, ruta_actual, profundidad);
        return 1;
    }
    
    // Caso base: profundidad máxima alcanzada
    if (profundidad >= max_profundidad) {
        return 0;
    }
    
    int fila_cero, col_cero;
    buscar_0(actual, &fila_cero, &col_cero);
    
    int nuevo_tablero[FILAS][COLUMNAS];
    int direccion;
    
    // Probar todas las direcciones posibles
    for (direccion = 0; direccion < 4; direccion++) {
        int nueva_f = fila_cero + dir_fila[direccion];
        int nueva_c = col_cero + dir_col[direccion];
        
        // Verificar movimiento válido
        if (nueva_f < 0 || nueva_f >= FILAS || nueva_c < 0 || nueva_c >= COLUMNAS) {
            continue;
        }
        
        // Crear nuevo estado
        copiar_tablero(actual, nuevo_tablero);
        
        // Realizar movimiento
        if (dir_fila[direccion] == 0) {
            intercambio_horizontal(nuevo_tablero, fila_cero, col_cero, nueva_f, nueva_c);
        } else {
            intercambio_vertical(nuevo_tablero, fila_cero, col_cero, nueva_f, nueva_c);
        }
        
        // Verificar si ya fue visitado (evitar ciclos)
        if (ya_visitado_recursivo(historia, nuevo_tablero, profundidad + 1)) {
            continue;
        }
        
        // Guardar estado y movimiento actual
        guardar_estado(historia, nuevo_tablero, profundidad + 1);
        ruta_actual[profundidad] = direccion;
        
        // Llamada recursiva
        if (resolver_puzzle_recursivo(nuevo_tablero, objetivo, profundidad + 1, 
                                     max_profundidad, historia, movimientos, 
                                     ruta_actual, encontrado)) {
            return 1; // Solución encontrada, propagar hacia arriba
        }
        
        // Backtracking implícito: no necesitamos "deshacer" porque usamos copias
    }
    
    return 0; // No se encontró solución en esta rama
}

/**
 * Imprime la solución encontrada recursivamente
 */
void imprimir_solucion_recursiva(int *historia, int *movimientos, int profundidad) {
    printf("Respuesta: %d pasos\n", profundidad);
    printf("\n--- SECUENCIA DE MOVIMIENTOS ---\n");
    
    // Reconstruir y mostrar el camino
    int tablero_actual[FILAS][COLUMNAS];
    
    // Mostrar estado inicial
    printf("Estado Inicial:\n");
    for(int r=0; r<FILAS; r++){
        for(int c=0; c<COLUMNAS; c++){
            tablero_actual[r][c] = historia[obtener_indice_1d(0, r, c)];
            printf("%2d ", tablero_actual[r][c]);
        }
        printf("\n");
    }
    printf("\n");
    
    // Mostrar cada movimiento
    for (int i = 0; i < profundidad; i++) {
        printf("Paso %d: Mover el 0 hacia %s\n", i + 1, nombre_mov[movimientos[i]]);
        
        // Mostrar estado después del movimiento
        printf("Estado despues del movimiento:\n");
        for(int r=0; r<FILAS; r++){
            for(int c=0; c<COLUMNAS; c++){
                tablero_actual[r][c] = historia[obtener_indice_1d(i + 1, r, c)];
                printf("%2d ", tablero_actual[r][c]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

/**
 * Guarda un estado en el historial
 */
void guardar_estado(int *historia, int tablero[FILAS][COLUMNAS], int idx) {
    for(int r=0; r<FILAS; r++){
        for(int c=0; c<COLUMNAS; c++){
            historia[obtener_indice_1d(idx, r, c)] = tablero[r][c];
        }
    }
}

/**
 * Verifica si un estado ya fue visitado en el camino actual
 */
int ya_visitado_recursivo(int *historia, int tablero[FILAS][COLUMNAS], int estados_visitados) {
    for (int i = 0; i < estados_visitados; i++) {
        int iguales = 1;
        for(int r=0; r<FILAS; r++){
            for(int c=0; c<COLUMNAS; c++){
                if(tablero[r][c] != historia[obtener_indice_1d(i, r, c)]){
                    iguales = 0;
                    break;
                }
            }
            if (!iguales) break;
        }
        if (iguales) return 1;
    }
    return 0;
}

/* -----------------------------------------------------------------
 * IMPLEMENTACIÓN DE UTILIDADES (MISMAS FUNCIONES)
 * ----------------------------------------------------------------- */

void leer_datos_puzzle(int puzzle[FILAS][COLUMNAS]){
    int i, j, leidos, valor, contador[9] = {0};
    int valido = 0;
    
    while (!valido) {
        printf("Ingrese el puzzle (ej: 1-2-3-4-5-6-7-8-0): ");
        
        leidos = scanf("%d-%d-%d-%d-%d-%d-%d-%d-%d", 
            &puzzle[0][0], &puzzle[0][1], &puzzle[0][2], 
            &puzzle[1][0], &puzzle[1][1], &puzzle[1][2], 
            &puzzle[2][0], &puzzle[2][1], &puzzle[2][2]);
            
        if (leidos != 9) {
            printf("ERROR: Formato incorrecto o incompleto. Intente de nuevo.\n");
            while (getchar() != '\n'); continue; 
        }
        for(i=0;i<9;i++) contador[i]=0;
        valido = 1;

        for(i = 0; i < FILAS; i++) {
            for(j = 0; j < COLUMNAS; j++) {
                valor = puzzle[i][j];
                
                if (valor < 0 || valor > 8) {
                    printf("ERROR: El valor %d está fuera del rango [0-8]. Intente de nuevo.\n", valor);
                    valido = 0; break;
                }
                
                if (contador[valor] > 0) {
                    printf("ERROR: El número %d está repetido. Intente de nuevo.\n", valor);
                    valido = 0; break;
                }
                contador[valor] = 1;
            }
            if (!valido) break;
        }
        
        if (!valido) { while (getchar() != '\n'); }
    }
}

void prueba_matriz(int puzzle[FILAS][COLUMNAS]){ 
    int i,j;
    for(i=0;i<FILAS;i++){
        for(j=0;j<COLUMNAS;j++){
            printf("%2d ", puzzle[i][j]);
        }
        printf("\n");
    }
}

void copiar_tablero(int origen[FILAS][COLUMNAS], int destino[FILAS][COLUMNAS]) {
    int i, j;
    for (i = 0; i < FILAS; i++)
        for (j = 0; j < COLUMNAS; j++)
            destino[i][j] = origen[i][j];
}

int son_iguales(int t1[FILAS][COLUMNAS], int t2[FILAS][COLUMNAS]) {
    int i, j;
    for (i = 0; i < FILAS; i++)
        for (j = 0; j < COLUMNAS; j++)
            if (t1[i][j] != t2[i][j])
                return 0;
    return 1;
}

void intercambiar(int *a, int *b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

int buscar_0(int tablero[FILAS][COLUMNAS], int *fila_cero, int *col_cero){
    int i,j,cero=0;
    for(i=0 ; i< FILAS; i++){
        for(j=0;j< COLUMNAS;j++){
            if(tablero[i][j] == cero ){
                *fila_cero = i;
                *col_cero = j;
                return 1;
            }
        }
    }
    *fila_cero = -1;
    *col_cero = -1;
    return -1; 
}

int intercambio_horizontal(int tablero[FILAS][COLUMNAS], int r1, int c1, int r2, int c2) {
    if (r1 == r2) {
        intercambiar(&tablero[r1][c1], &tablero[r2][c2]);
        return 1;
    }
    return 0;
}

int intercambio_vertical(int tablero[FILAS][COLUMNAS], int r1, int c1, int r2, int c2) {
    if (c1 == c2) {
        intercambiar(&tablero[r1][c1], &tablero[r2][c2]);
        return 1;
    }
    return 0;
}