#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILAS 3
#define COLUMNAS 3
#define MAX_MOVIMIENTOS 20 
#define MAX_ESTADOS 100000 
#define MAX_VISITADOS 100000 

typedef struct {
    int celdas[FILAS][COLUMNAS];
} TABLERO;

typedef struct {
    int fila;
    int columna;
} POSICION;

typedef struct{
    TABLERO estados[MAX_MOVIMIENTOS + 1];
    int movimientos[MAX_MOVIMIENTOS];
    int numeros_movidos[MAX_MOVIMIENTOS];
    int total_estados;
} SOLUCION;

int mov_fila[] = {-1, 1, 0, 0}; 
int mov_columna[] = {0, 0, -1, 1};
char *nombres_mov[] = {"ARRIBA", "ABAJO", "IZQUIERDA", "DERECHA"};

void leer_tablero(TABLERO *tablero){
    int i, j, leidos, valor, usado[9] = {0};
    int valido = 0;
    
    while(!valido){
        printf("Ingrese el puzzle (ej: 1-2-3-4-5-6-7-8-0): ");
        
        leidos = scanf("%d-%d-%d-%d-%d-%d-%d-%d-%d",
            &tablero->celdas[0][0], &tablero->celdas[0][1], &tablero->celdas[0][2],
            &tablero->celdas[1][0], &tablero->celdas[1][1], &tablero->celdas[1][2],
            &tablero->celdas[2][0], &tablero->celdas[2][1], &tablero->celdas[2][2]);
            
        if(leidos != 9){
            printf("ERROR: Formato incorrecto o falta 'ENTER'. Use: 1-2-3-4-5-6-7-8-0\n");
            while (getchar() != '\n');
            continue; 
        }
        
        for(i = 0; i < 9; i++) usado[i] = 0;
        valido = 1;
        for(i = 0; i < FILAS; i++){
            for(j = 0; j < COLUMNAS; j++){
                valor = tablero->celdas[i][j];
                if(valor < 0 || valor > 8 || usado[valor] > 0){
                    printf("ERROR: Valores inválidos o repetidos.\n");
                    valido = 0; break;
                }
                usado[valor] = 1;
            }
            if(!valido) break;
        }
        if(!valido) while(getchar() != '\n'); 
    }
}

void mostrar_tablero(TABLERO *t){
    int i, j;
    printf("+---+---+---+\n");
    for(i = 0; i < FILAS; i++) {
        printf("|");
        for(j = 0; j < COLUMNAS; j++){
            if(t->celdas[i][j] == 0){
                printf("   |");
            }else{
                printf(" %d |", t->celdas[i][j]);
            }
        }
        printf("\n+---+---+---+\n");
    }
}

int tableros_iguales(TABLERO *a, TABLERO *b){
    return memcmp(a, b, sizeof(TABLERO)) == 0;
}

void copiar_tablero(TABLERO *origen, TABLERO *destino){
    memcpy(destino, origen, sizeof(TABLERO));
}

int encontrar_vacio(TABLERO *t, POSICION *pos){
    int i, j;
    for(i = 0; i < FILAS; i++) {
        for(j = 0; j < COLUMNAS; j++){
            if (t->celdas[i][j] == 0){
                pos->fila = i;
                pos->columna = j;
                return 1;
            }
        }
    }
    return 0;
}

void intercambiar(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int estado_ya_visitado(TABLERO *tablero, TABLERO *visitados, int total_visitados){
    int i;
    for(i = 0; i < total_visitados; i++){
        if(tableros_iguales(tablero, &visitados[i])) return 1;
    }
    return 0;
}

void agregar_estado_visitado(TABLERO *tablero, TABLERO *visitados, int *total_visitados){
    if(*total_visitados < MAX_VISITADOS){
        copiar_tablero(tablero, &visitados[*total_visitados]);
        (*total_visitados)++;
    }
}

int buscar_solucion_bfs(TABLERO *inicial, TABLERO *objetivo, SOLUCION *sol) {
    TABLERO cola[MAX_ESTADOS];
    int padres[MAX_ESTADOS];
    int movimientos_ruta[MAX_ESTADOS];
    int numeros_ruta[MAX_ESTADOS];
    TABLERO visitados[MAX_VISITADOS];
    int total_visitados = 0;
    int frente = 0, final = 0;
    int resultado = 0;
    
    copiar_tablero(inicial, &cola[final]);
    padres[final] = -1;
    movimientos_ruta[final] = -1;
    numeros_ruta[final] = -1;
    final++;
    
    agregar_estado_visitado(inicial, visitados, &total_visitados);
    
    while (frente < final && final < MAX_ESTADOS) {
        TABLERO actual = cola[frente];
        int indice_actual = frente;
        
        if (tableros_iguales(&actual, objetivo)) {
            resultado = 1;
            break;
        }
        
        POSICION vacio, nueva_pos;
        encontrar_vacio(&actual, &vacio);
        
        for (int dir = 0; dir < 4; dir++) {
            nueva_pos.fila = vacio.fila + mov_fila[dir];
            nueva_pos.columna = vacio.columna + mov_columna[dir];
            
            if (nueva_pos.fila < 0 || nueva_pos.fila >= FILAS || 
                nueva_pos.columna < 0 || nueva_pos.columna >= COLUMNAS) {
                continue;
            }
            
            TABLERO siguiente;
            copiar_tablero(&actual, &siguiente);
            int numero_movido = siguiente.celdas[nueva_pos.fila][nueva_pos.columna];
            intercambiar(&siguiente.celdas[vacio.fila][vacio.columna], 
                        &siguiente.celdas[nueva_pos.fila][nueva_pos.columna]);
            
            if (!estado_ya_visitado(&siguiente, visitados, total_visitados)) {
                if (final < MAX_ESTADOS) {
                    copiar_tablero(&siguiente, &cola[final]);
                    padres[final] = indice_actual;
                    movimientos_ruta[final] = dir;
                    numeros_ruta[final] = numero_movido;
                    final++;
                    
                    agregar_estado_visitado(&siguiente, visitados, &total_visitados);
                }
            }
        }
        frente++;
    }
    
    if (resultado) {
        int pasos = 0;
        int camino_indices[MAX_MOVIMIENTOS + 1];
        int indice = frente;
        
        while (indice != -1) {
            if (pasos >= MAX_MOVIMIENTOS + 1) {
                return 0;
            }
            camino_indices[pasos] = indice;
            pasos++;
            indice = padres[indice];
        }
        
        sol->total_estados = pasos;
        for (int i = 0; i < pasos; i++) {
            int idx = camino_indices[pasos - 1 - i]; 
            copiar_tablero(&cola[idx], &sol->estados[i]);
            if (i > 0) {
                sol->movimientos[i-1] = movimientos_ruta[idx];
                sol->numeros_movidos[i-1] = numeros_ruta[idx];
            }
        }
    }
    
    return resultado;
}

void mostrar_solucion(SOLUCION *sol, TABLERO *inicial){
    int i;
    
    printf("\n*** SOLUCIÓN ENCONTRADA! ***\n");
    printf("Total de movimientos: %d\n\n", sol->total_estados - 1);
    
    printf("Estado inicial:\n");
    mostrar_tablero(inicial);
    printf("\n");
    
    for(i = 0; i < sol->total_estados - 1; i++){
        printf("--- Paso %d ---\n", i + 1);
        printf("Movimiento: Mover número %d hacia %s\n", 
               sol->numeros_movidos[i], nombres_mov[sol->movimientos[i]]);
        
        printf("Estado resultante:\n");
        mostrar_tablero(&sol->estados[i + 1]);
        printf("\n");
    }
    
    printf("*** SOLUCIÓN COMPLETADA ***\n");
}

int main(){
    TABLERO inicial, objetivo = {
        {{1, 2, 3},
         {4, 5, 6},
         {7, 8, 0}}
    };
    SOLUCION solucion;
    int resultado;
    
    printf("=== RESOLVEDOR DE 8-PUZZLE (BFS) ===\n\n");
    
    leer_tablero(&inicial);
    
    printf("\n--- ESTADO INICIAL ---\n");
    mostrar_tablero(&inicial);
    
    printf("\n--- BUSCANDO SOLUCIÓN ÓPTIMA ---\n");
    printf("Límite de movimientos para mostrar: %d\n", MAX_MOVIMIENTOS);
    printf("Calculando...\n");
    
    resultado = buscar_solucion_bfs(&inicial, &objetivo, &solucion);

    if(resultado){
        mostrar_solucion(&solucion, &inicial);
    }else{
        printf("\nNO SE ENCONTRÓ SOLUCIÓN en el rango de búsqueda (MAX_ESTADOS).\n");
        printf("El problema requiere más de %d movimientos o el espacio de búsqueda se excedió.\n", MAX_MOVIMIENTOS);
    }
    
    return 0;
}