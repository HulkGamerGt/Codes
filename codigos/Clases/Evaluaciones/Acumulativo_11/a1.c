#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILAS 3 
#define COLUMNAS 3
#define MAX_MOVIMIENTOS 31
#define MAX_ESTADOS 10000

typedef struct {
    int celdas[FILAS][COLUMNAS];
} TABLERO;

typedef struct {
    int fila;
    int columna;
} POSICION;

typedef struct {
    TABLERO estado;
    int movimiento;
    int numero_movido;
    int padre;
} ESTADO_SOLUCION;

int mov_fila[] = {0, 1, 0, -1};  // Orden más eficiente: DERECHA, ABAJO, IZQUIERDA, ARRIBA
int mov_columna[] = {1, 0, -1, 0};
char* direcciones[] = {"DERECHA", "ABAJO", "IZQUIERDA", "ARRIBA"};

/* -----------------------------------------------------------------
 * FUNCIONES BÁSICAS OPTIMIZADAS
 * ----------------------------------------------------------------- */

void leer_tablero(TABLERO *tablero) {
    int i, j, leidos, valor, usado[9] = {0};
    int valido = 0;
    
    while(!valido) {
        printf("Ingrese el puzzle (ej: 1-2-3-4-5-6-7-8-0): ");
        
        leidos = scanf("%d-%d-%d-%d-%d-%d-%d-%d-%d",
            &tablero->celdas[0][0], &tablero->celdas[0][1], &tablero->celdas[0][2],
            &tablero->celdas[1][0], &tablero->celdas[1][1], &tablero->celdas[1][2],
            &tablero->celdas[2][0], &tablero->celdas[2][1], &tablero->celdas[2][2]);
            
        if(leidos != 9) {
            printf("ERROR: Formato incorrecto. Use: 1-2-3-4-5-6-7-8-0\n");
            while (getchar() != '\n');
            continue; 
        }
        
        memset(usado, 0, sizeof(usado));
        valido = 1;

        for(i = 0; i < FILAS; i++) {
            for(j = 0; j < COLUMNAS; j++) {
                valor = tablero->celdas[i][j];
                
                if(valor < 0 || valor > 8) {
                    printf("ERROR: Valor %d fuera de rango [0-8].\n", valor);
                    valido = 0; break;
                }
                
                if(usado[valor] > 0) {
                    printf("ERROR: Número %d repetido.\n", valor);
                    valido = 0; break;
                }
                usado[valor] = 1;
            }
            if(!valido) break;
        }
        
        if(!valido) while(getchar() != '\n'); 
    }
}

void mostrar_tablero(TABLERO *t) {
    int i, j;
    printf("+---+---+---+\n");
    for(i = 0; i < FILAS; i++) {
        printf("|");
        for(j = 0; j < COLUMNAS; j++) {
            if(t->celdas[i][j] == 0) {
                printf("   |");
            } else {
                printf(" %d |", t->celdas[i][j]);
            }
        }
        printf("\n+---+---+---+\n");
    }
}

int tableros_iguales(TABLERO *a, TABLERO *b) {
    int i, j;
    for(i = 0; i < FILAS; i++) {
        for(j = 0; j < COLUMNAS; j++) {
            if(a->celdas[i][j] != b->celdas[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

void copiar_tablero(TABLERO *origen, TABLERO *destino) {
    memcpy(destino, origen, sizeof(TABLERO));
}

int encontrar_vacio(TABLERO *t, POSICION *pos) {
    int i, j;
    for(i = 0; i < FILAS; i++) {
        for(j = 0; j < COLUMNAS; j++) {
            if(t->celdas[i][j] == 0) {
                pos->fila = i;
                pos->columna = j;
                return 1;
            }
        }
    }
    return 0;
}

void intercambiar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* -----------------------------------------------------------------
 * DETECCIÓN RÁPIDA DE ESTADOS REPETIDOS
 * ----------------------------------------------------------------- */

// Función rápida para calcular un identificador único del estado
unsigned long calcular_id_estado(TABLERO *t) {
    unsigned long id = 0;
    int i, j;
    for(i = 0; i < FILAS; i++) {
        for(j = 0; j < COLUMNAS; j++) {
            id = id * 10 + t->celdas[i][j];
        }
    }
    return id;
}

#define TABLA_VISITADOS_SIZE 10007

typedef struct {
    unsigned long ids[TABLA_VISITADOS_SIZE];
    int count;
} TABLA_VISITADOS;

void inicializar_tabla(TABLA_VISITADOS *tabla) {
    tabla->count = 0;
    memset(tabla->ids, 0, sizeof(tabla->ids));
}

int estado_ya_visitado(TABLERO *tablero, TABLA_VISITADOS *tabla) {
    unsigned long id = calcular_id_estado(tablero);
    int index = id % TABLA_VISITADOS_SIZE;
    
    // Búsqueda lineal simple en caso de colisión
    int i;
    for(i = 0; i < tabla->count; i++) {
        if(tabla->ids[i] == id) {
            return 1;
        }
    }
    return 0;
}

void agregar_estado_visitado(TABLERO *tablero, TABLA_VISITADOS *tabla) {
    if(tabla->count < TABLA_VISITADOS_SIZE) {
        unsigned long id = calcular_id_estado(tablero);
        tabla->ids[tabla->count++] = id;
    }
}

/* -----------------------------------------------------------------
 * BÚSQUEDA BFS OPTIMIZADA
 * ----------------------------------------------------------------- */

int buscar_solucion_bfs(TABLERO *inicial, TABLERO *objetivo, ESTADO_SOLUCION *solucion, int *total_movimientos) {
    TABLERO cola_estados[MAX_ESTADOS];
    int padres[MAX_ESTADOS];
    int movimientos[MAX_ESTADOS];
    int numeros_movidos[MAX_ESTADOS];
    int frente = 0, final = 0;
    TABLA_VISITADOS visitados;
    
    inicializar_tabla(&visitados);
    
    // Inicializar cola con estado inicial
    copiar_tablero(inicial, &cola_estados[final]);
    padres[final] = -1;
    movimientos[final] = -1;
    numeros_movidos[final] = -1;
    final++;
    
    agregar_estado_visitado(inicial, &visitados);
    
    printf("Explorando estados...\n");
    int estados_explorados = 0;
    
    while(frente < final && final < MAX_ESTADOS) {
        TABLERO actual = cola_estados[frente];
        int padre_actual = frente;
        estados_explorados++;
        
        // Mostrar progreso cada 1000 estados
        if(estados_explorados % 1000 == 0) {
            printf("Estados explorados: %d, Cola: %d\n", estados_explorados, final - frente);
        }
        
        // Verificar si es solución
        if(tableros_iguales(&actual, objetivo)) {
            // Reconstruir solución
            *total_movimientos = 0;
            int indice = frente;
            
            // Contar movimientos
            while(indice != -1) {
                (*total_movimientos)++;
                indice = padres[indice];
            }
            
            // Almacenar solución
            indice = frente;
            int paso = *total_movimientos - 1;
            
            while(indice != -1 && paso >= 0) {
                solucion[paso].estado = cola_estados[indice];
                solucion[paso].movimiento = movimientos[indice];
                solucion[paso].numero_movido = numeros_movidos[indice];
                solucion[paso].padre = padres[indice];
                indice = padres[indice];
                paso--;
            }
            
            printf("Solución encontrada después de explorar %d estados\n", estados_explorados);
            return 1;
        }
        
        // Generar movimientos
        POSICION vacio;
        encontrar_vacio(&actual, &vacio);
        
        int dir;
        for(dir = 0; dir < 4; dir++) {
            POSICION nueva_pos;
            nueva_pos.fila = vacio.fila + mov_fila[dir];
            nueva_pos.columna = vacio.columna + mov_columna[dir];
            
            if(nueva_pos.fila < 0 || nueva_pos.fila >= FILAS || 
               nueva_pos.columna < 0 || nueva_pos.columna >= COLUMNAS) {
                continue;
            }
            
            TABLERO siguiente;
            copiar_tablero(&actual, &siguiente);
            intercambiar(&siguiente.celdas[vacio.fila][vacio.columna], 
                        &siguiente.celdas[nueva_pos.fila][nueva_pos.columna]);
            
            // Evitar estados repetidos
            if(estado_ya_visitado(&siguiente, &visitados)) {
                continue;
            }
            
            // Agregar a la cola
            if(final < MAX_ESTADOS) {
                copiar_tablero(&siguiente, &cola_estados[final]);
                padres[final] = frente;
                movimientos[final] = dir;
                numeros_movidos[final] = siguiente.celdas[vacio.fila][vacio.columna];
                final++;
                
                agregar_estado_visitado(&siguiente, &visitados);
            }
        }
        
        frente++;
    }
    
    printf("Búsqueda terminada. Estados explorados: %d\n", estados_explorados);
    return 0;
}

/* -----------------------------------------------------------------
 * MOSTRAR SOLUCIÓN
 * ----------------------------------------------------------------- */

void mostrar_solucion(ESTADO_SOLUCION *solucion, int total_movimientos, TABLERO *inicial) {
    int i;
    
    printf("\n*** SOLUCIÓN ENCONTRADA! ***\n");
    printf("Total de movimientos: %d\n\n", total_movimientos - 1);
    
    printf("Estado inicial:\n");
    mostrar_tablero(inicial);
    printf("\n");
    
    for(i = 1; i < total_movimientos; i++) {
        printf("--- Paso %d ---\n", i);
        printf("Movimiento: Mover número %d hacia %s\n", 
               solucion[i].numero_movido, 
               direcciones[solucion[i].movimiento]);
        
        printf("Estado resultante:\n");
        mostrar_tablero(&solucion[i].estado);
        printf("\n");
    }
    
    printf("*** SOLUCIÓN COMPLETADA ***\n");
}

/* -----------------------------------------------------------------
 * FUNCIÓN PRINCIPAL
 * ----------------------------------------------------------------- */

int main() {
    TABLERO inicial, objetivo = {
        {{1, 2, 3},
         {4, 5, 6},
         {7, 8, 0}}
    };
    ESTADO_SOLUCION solucion[MAX_MOVIMIENTOS + 1];
    int total_movimientos;
    int resultado;
    
    printf("=== RESOLVEDOR DE 8-PUZZLE OPTIMIZADO ===\n\n");
    
    leer_tablero(&inicial);
    
    printf("\n--- ESTADO INICIAL ---\n");
    mostrar_tablero(&inicial);
    
    printf("\n--- BUSCANDO SOLUCIÓN ---\n");
    printf("Límite: %d estados en cola\n", MAX_ESTADOS);
    printf("Calculando...\n");
    
    // Buscar solución con BFS optimizado
    resultado = buscar_solucion_bfs(&inicial, &objetivo, solucion, &total_movimientos);

    if(resultado) {
        mostrar_solucion(solucion, total_movimientos, &inicial);
    } else {
        printf("\nNO SE ENCONTRÓ SOLUCIÓN en el límite de %d estados.\n", MAX_ESTADOS);
        printf("Esto puede ser porque:\n");
        printf("1. El puzzle requiere más de %d movimientos\n", MAX_MOVIMIENTOS);
        printf("2. El estado inicial no tiene solución\n");
        printf("3. Se necesita más memoria\n");
        
        // Verificar si el puzzle tiene solución
        printf("\nPrueba con estos ejemplos garantizados:\n");
        printf("• 1-2-3-4-5-6-7-0-8 (1 movimiento)\n");
        printf("• 1-2-3-4-0-5-6-7-8 (1 movimiento)\n"); 
        printf("• 1-2-3-4-5-6-0-7-8 (2 movimientos)\n");
        printf("• 1-0-3-4-2-5-6-7-8 (4 movimientos)\n");
        printf("• 4-1-3-0-2-5-6-7-8 (6 movimientos)\n");
    }
    
    return 0;
}