#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILAS 3 
#define COLUMNAS 3
#define MAX_PROFUNDIDAD 31
#define HASH_SIZE 1000000

/* Estructuras para organizar los datos */
typedef struct {
    int tablero[FILAS][COLUMNAS];
} ESTADOTABLERO;

typedef struct {
    int fila;
    int columna;
} POSICION;

typedef struct {
    ESTADOTABLERO estado;
    int movimiento_realizado;
    int numero_movido;
    int profundidad_actual;
} NodoBusqueda;

typedef struct {
    int *datos_tableros;
    int *secuencia_movimientos;
    int *numeros_desplazados;
    int capacidad_almacenamiento;
} ALMCENAMIENTOSOLUCION;

/* FUNCIÓN DE INDEXACIÓN 1D */
int calcular_indice_almacenamiento(int indice_estado, int fila, int columna) {    
    return (indice_estado * FILAS * COLUMNAS) + (fila * COLUMNAS) + columna;
}

/* -----------------------------------------------------------------
 * PROTOTIPOS 
 * ----------------------------------------------------------------- */
void leer_configuracion_puzzle(int configuracion[FILAS][COLUMNAS]);
int buscar_solucion_iddfs(ESTADOTABLERO estado_inicial, ESTADOTABLERO estado_objetivo, 
                         ALMCENAMIENTOSOLUCION *almacen_solucion);
int buscar_profundidad_limitada(ESTADOTABLERO estado_actual, ESTADOTABLERO estado_objetivo, 
                               int profundidad_actual, int limite_profundidad, 
                               ALMCENAMIENTOSOLUCION *almacen_solucion, 
                               int *solucion_encontrada, int *tabla_hash_estados);
void mostrar_tablero_estado(ESTADOTABLERO tablero); 
void mostrar_tablero_formateado(int configuracion[FILAS][COLUMNAS]);

/* UTILIDADES */
void copiar_estado_tablero(ESTADOTABLERO origen, ESTADOTABLERO *destino);
int comparar_estados_tablero(ESTADOTABLERO estado1, ESTADOTABLERO estado2);
void intercambiar_valores(int *valor_a, int *valor_b);
int encontrar_posicion_vacia(ESTADOTABLERO tablero, POSICION *pos_vacia);

int realizar_intercambio_horizontal(ESTADOTABLERO *tablero, POSICION pos1, POSICION pos2); 
int realizar_intercambio_vertical(ESTADOTABLERO *tablero, POSICION pos1, POSICION pos2); 

/* Utilitarios */
void mostrar_secuencia_solucion(ALMCENAMIENTOSOLUCION *almacen_solucion, int total_pasos);
void guardar_estado_actual(ALMCENAMIENTOSOLUCION *almacen_solucion, ESTADOTABLERO estado, int indice);
char* determinar_direccion_movimiento(int direccion_espacio_vacio);

/* Funciones de optimización */
unsigned long calcular_hash_estado(ESTADOTABLERO estado);
int verificar_estado_visitado(int *tabla_hash_estados, ESTADOTABLERO estado);
void marcar_estado_visitado(int *tabla_hash_estados, ESTADOTABLERO estado);
int calcular_heuristica_manhattan(ESTADOTABLERO estado_actual, ESTADOTABLERO estado_objetivo);
void ordenar_movimientos_prioridad(int movimientos_posibles[4], ESTADOTABLERO estado_actual, ESTADOTABLERO estado_objetivo);

/* Direcciones de movimiento DEL ESPACIO VACIO */
int desplazamiento_fila[] = {-1, 1, 0, 0}; 
int desplazamiento_columna[] = {0, 0, -1, 1};
char *nombres_direcciones[] = {"ARRIBA", "ABAJO", "IZQUIERDA", "DERECHA"};

int main()
{
    ESTADOTABLERO estado_inicial;
    ESTADOTABLERO estado_objetivo = {
        {{1,2,3},
         {4,5,6},
         {7,8,0}}
    };
    ALMCENAMIENTOSOLUCION almacen_solucion;
    size_t tamano_almacenamiento;
    size_t tamano_secuencias;
    int pasos_solucion;
    
    leer_configuracion_puzzle(estado_inicial.tablero);
    
    printf("\n--- ESTADO INICIAL ---\n");
    mostrar_tablero_estado(estado_inicial); 
    
    /* Preparar estructuras de almacenamiento */
    tamano_almacenamiento = (MAX_PROFUNDIDAD + 1) * FILAS * COLUMNAS * sizeof(int);
    tamano_secuencias = (MAX_PROFUNDIDAD + 1) * sizeof(int);
    
    almacen_solucion.datos_tableros = (int *)malloc(tamano_almacenamiento);
    almacen_solucion.secuencia_movimientos = (int *)malloc(tamano_secuencias);
    almacen_solucion.numeros_desplazados = (int *)malloc(tamano_secuencias);
    almacen_solucion.capacidad_almacenamiento = MAX_PROFUNDIDAD + 1;
    
    if (!almacen_solucion.datos_tableros || !almacen_solucion.secuencia_movimientos || 
        !almacen_solucion.numeros_desplazados) {
        printf("ERROR: Fallo al asignar memoria.\n");
        if (almacen_solucion.datos_tableros) free(almacen_solucion.datos_tableros);
        if (almacen_solucion.secuencia_movimientos) free(almacen_solucion.secuencia_movimientos);
        if (almacen_solucion.numeros_desplazados) free(almacen_solucion.numeros_desplazados);
        return 1;
    }
    
    /* Guardar estado inicial */
    guardar_estado_actual(&almacen_solucion, estado_inicial, 0);
    
    printf("--- BUSCANDO SOLUCION (IDDFS Optimizado) ---\n");
    
    /* Usar Iterative Deepening DFS para encontrar la solución óptima */
    pasos_solucion = buscar_solucion_iddfs(estado_inicial, estado_objetivo, &almacen_solucion);
    
    if (pasos_solucion == -1) {
        printf("El puzzle no tiene solucion (o se excedio la profundidad maxima de %d).\n", MAX_PROFUNDIDAD);
    }
    
    free(almacen_solucion.datos_tableros);
    free(almacen_solucion.secuencia_movimientos);
    free(almacen_solucion.numeros_desplazados);
    
    return 0;
}

/* -----------------------------------------------------------------
 * IMPLEMENTACIÓN DE ITERATIVE DEEPENING DFS (IDDFS) OPTIMIZADO
 * ----------------------------------------------------------------- */

int buscar_solucion_iddfs(ESTADOTABLERO estado_inicial, ESTADOTABLERO estado_objetivo, 
                         ALMCENAMIENTOSOLUCION *almacen_solucion)
{
    int limite_profundidad;
    int profundidad_minima_estimada;
    int *tabla_hash_estados;
    int solucion_encontrada;
    
    if (comparar_estados_tablero(estado_inicial, estado_objetivo)) {
        printf("*** EL PUZZLE YA ESTA RESUELTO ***\n");
        mostrar_secuencia_solucion(almacen_solucion, 0);
        return 0;
    }
    
    /* Calcular profundidad mínima usando heurística Manhattan */
    profundidad_minima_estimada = calcular_heuristica_manhattan(estado_inicial, estado_objetivo);
    printf("Profundidad minima estimada: %d\n", profundidad_minima_estimada);
    
    /* Búsqueda iterativa empezando desde la profundidad mínima */
    for (limite_profundidad = profundidad_minima_estimada; limite_profundidad <= MAX_PROFUNDIDAD; limite_profundidad++) {
        printf("Buscando con profundidad limite: %d\n", limite_profundidad);
        
        /* Crear nueva tabla hash para cada iteración */
        tabla_hash_estados = (int *)calloc(HASH_SIZE, sizeof(int));
        if (!tabla_hash_estados) {
            printf("ERROR: No se pudo asignar memoria para tabla hash\n");
            continue;
        }
        
        solucion_encontrada = 0;
        
        if (buscar_profundidad_limitada(estado_inicial, estado_objetivo, 0, limite_profundidad, 
                                       almacen_solucion, &solucion_encontrada, tabla_hash_estados)) {
            free(tabla_hash_estados);
            return limite_profundidad;
        }
        
        free(tabla_hash_estados);
    }
    
    return -1;
}

int buscar_profundidad_limitada(ESTADOTABLERO estado_actual, ESTADOTABLERO estado_objetivo, 
                               int profundidad_actual, int limite_profundidad, 
                               ALMCENAMIENTOSOLUCION *almacen_solucion, 
                               int *solucion_encontrada, int *tabla_hash_estados)
{
    POSICION pos_vacia;
    ESTADOTABLERO nuevo_estado;
    int movimientos_posibles[4] = {0, 1, 2, 3};
    int indice_movimiento;
    int direccion_actual;
    POSICION nueva_posicion;
    int numero_a_mover;
    
    if (comparar_estados_tablero(estado_actual, estado_objetivo)) {
        printf("*** SOLUCION ENCONTRADA! ***\n");
        *solucion_encontrada = 1;
        mostrar_secuencia_solucion(almacen_solucion, profundidad_actual);
        return 1;
    }
    
    /* PODA CRÍTICA: Si profundidad + heurística > límite, cortar rama */
    if (profundidad_actual + calcular_heuristica_manhattan(estado_actual, estado_objetivo) > limite_profundidad) {
        return 0;
    }
    
    /* Marcar estado actual como visitado */
    marcar_estado_visitado(tabla_hash_estados, estado_actual);
    
    encontrar_posicion_vacia(estado_actual, &pos_vacia);
    
    /* Ordenar movimientos por prioridad (los más prometedores primero) */
    ordenar_movimientos_prioridad(movimientos_posibles, estado_actual, estado_objetivo);
    
    for (indice_movimiento = 0; indice_movimiento < 4; indice_movimiento++) {
        direccion_actual = movimientos_posibles[indice_movimiento];
        nueva_posicion.fila = pos_vacia.fila + desplazamiento_fila[direccion_actual];
        nueva_posicion.columna = pos_vacia.columna + desplazamiento_columna[direccion_actual];
        
        if (nueva_posicion.fila < 0 || nueva_posicion.fila >= FILAS || 
            nueva_posicion.columna < 0 || nueva_posicion.columna >= COLUMNAS) {
            continue;
        }
        
        copiar_estado_tablero(estado_actual, &nuevo_estado);
        
        numero_a_mover = nuevo_estado.tablero[nueva_posicion.fila][nueva_posicion.columna];
        
        if (desplazamiento_fila[direccion_actual] == 0) {
            realizar_intercambio_horizontal(&nuevo_estado, pos_vacia, nueva_posicion);
        } else {
            realizar_intercambio_vertical(&nuevo_estado, pos_vacia, nueva_posicion);
        }
        
        /* Verificar si ya fue visitado usando tabla hash */
        if (verificar_estado_visitado(tabla_hash_estados, nuevo_estado)) {
            continue;
        }
        
        guardar_estado_actual(almacen_solucion, nuevo_estado, profundidad_actual + 1);
        almacen_solucion->secuencia_movimientos[profundidad_actual] = direccion_actual;
        almacen_solucion->numeros_desplazados[profundidad_actual] = numero_a_mover;
        
        if (buscar_profundidad_limitada(nuevo_estado, estado_objetivo, profundidad_actual + 1, limite_profundidad, 
                                       almacen_solucion, solucion_encontrada, tabla_hash_estados)) {
            return 1;
        }
    }
    
    return 0;
}

/* -----------------------------------------------------------------
 * FUNCIONES DE OPTIMIZACIÓN
 * ----------------------------------------------------------------- */

/**
 * Calcula la distancia Manhattan (heurística admisible)
 */
int calcular_heuristica_manhattan(ESTADOTABLERO estado_actual, ESTADOTABLERO estado_objetivo)
{
    int distancia_total = 0;
    int numero_actual;
    int fila_actual, columna_actual;
    int fila_objetivo, columna_objetivo;
    int i, j;
    
    for (numero_actual = 1; numero_actual <= 8; numero_actual++) {
        fila_actual = -1;
        columna_actual = -1;
        fila_objetivo = -1;
        columna_objetivo = -1;
        
        /* Encontrar posición actual del número */
        for (i = 0; i < FILAS; i++) {
            for (j = 0; j < COLUMNAS; j++) {
                if (estado_actual.tablero[i][j] == numero_actual) {
                    fila_actual = i;
                    columna_actual = j;
                }
                if (estado_objetivo.tablero[i][j] == numero_actual) {
                    fila_objetivo = i;
                    columna_objetivo = j;
                }
            }
        }
        
        if (fila_actual != -1 && fila_objetivo != -1) {
            distancia_total += abs(fila_actual - fila_objetivo) + abs(columna_actual - columna_objetivo);
        }
    }
    
    return distancia_total;
}

/**
 * Ordena movimientos por mejor heurística primero
 */
void ordenar_movimientos_prioridad(int movimientos_posibles[4], ESTADOTABLERO estado_actual, ESTADOTABLERO estado_objetivo)
{
    POSICION pos_vacia;
    int prioridades_movimientos[4];
    int i, j;
    POSICION nueva_posicion;
    ESTADOTABLERO estado_temporal;
    int heuristica_actual, heuristica_nueva;
    int movimiento_temporal;
    
    encontrar_posicion_vacia(estado_actual, &pos_vacia);
    
    for (i = 0; i < 4; i++) {
        nueva_posicion.fila = pos_vacia.fila + desplazamiento_fila[i];
        nueva_posicion.columna = pos_vacia.columna + desplazamiento_columna[i];
        
        if (nueva_posicion.fila < 0 || nueva_posicion.fila >= FILAS || 
            nueva_posicion.columna < 0 || nueva_posicion.columna >= COLUMNAS) {
            prioridades_movimientos[i] = -1000; /* Movimiento inválido */
            continue;
        }
        
        /* Calcular mejora en heurística */
        copiar_estado_tablero(estado_actual, &estado_temporal);
        
        if (desplazamiento_fila[i] == 0) {
            realizar_intercambio_horizontal(&estado_temporal, pos_vacia, nueva_posicion);
        } else {
            realizar_intercambio_vertical(&estado_temporal, pos_vacia, nueva_posicion);
        }
        
        heuristica_actual = calcular_heuristica_manhattan(estado_actual, estado_objetivo);
        heuristica_nueva = calcular_heuristica_manhattan(estado_temporal, estado_objetivo);
        prioridades_movimientos[i] = heuristica_actual - heuristica_nueva; /* Positivo si mejora */
    }
    
    /* Ordenar movimientos por prioridad (bubble sort simple) */
    for (i = 0; i < 4; i++) {
        for (j = i + 1; j < 4; j++) {
            if (prioridades_movimientos[movimientos_posibles[j]] > prioridades_movimientos[movimientos_posibles[i]]) {
                movimiento_temporal = movimientos_posibles[i];
                movimientos_posibles[i] = movimientos_posibles[j];
                movimientos_posibles[j] = movimiento_temporal;
            }
        }
    }
}

/**
 * Función hash simple pero efectiva
 */
unsigned long calcular_hash_estado(ESTADOTABLERO estado)
{
    unsigned long valor_hash = 0;
    int i, j;
    
    for (i = 0; i < FILAS; i++) {
        for (j = 0; j < COLUMNAS; j++) {
            valor_hash = valor_hash * 31 + estado.tablero[i][j] + 1; /* +1 para evitar ceros */
        }
    }
    return valor_hash % HASH_SIZE;
}

int verificar_estado_visitado(int *tabla_hash_estados, ESTADOTABLERO estado)
{
    unsigned long valor_hash = calcular_hash_estado(estado);
    return tabla_hash_estados[valor_hash] == 1;
}

void marcar_estado_visitado(int *tabla_hash_estados, ESTADOTABLERO estado)
{
    unsigned long valor_hash = calcular_hash_estado(estado);
    tabla_hash_estados[valor_hash] = 1;
}

/* -----------------------------------------------------------------
 * FUNCIONES RESTANTES
 * ----------------------------------------------------------------- */

char* determinar_direccion_movimiento(int direccion_espacio_vacio)
{
    switch(direccion_espacio_vacio) {
        case 0: return "ABAJO";
        case 1: return "ARRIBA";
        case 2: return "DERECHA";
        case 3: return "IZQUIERDA";
        default: return "DESCONOCIDO";
    }
}

void mostrar_secuencia_solucion(ALMCENAMIENTOSOLUCION *almacen_solucion, int total_pasos)
{
    int paso_actual;
    int fila, columna;
    ESTADOTABLERO estado_actual;
    ESTADOTABLERO estado_siguiente;
    char* direccion_movimiento;
    
    if (total_pasos == 0) {
        printf("El puzzle ya estaba resuelto.\n");
        return;
    }
    
    printf("Respuesta: %d pasos\n", total_pasos);
    printf("\n--- SECUENCIA DE MOVIMIENTOS ---\n");
    
    printf("Estado Inicial:\n");
    for (fila = 0; fila < FILAS; fila++) {
        for (columna = 0; columna < COLUMNAS; columna++) {
            estado_actual.tablero[fila][columna] = almacen_solucion->datos_tableros[calcular_indice_almacenamiento(0, fila, columna)];
        }
    }
    mostrar_tablero_estado(estado_actual);
    printf("\n");
    
    for (paso_actual = 0; paso_actual < total_pasos; paso_actual++) {
        for (fila = 0; fila < FILAS; fila++) {
            for (columna = 0; columna < COLUMNAS; columna++) {
                estado_siguiente.tablero[fila][columna] = almacen_solucion->datos_tableros[calcular_indice_almacenamiento(paso_actual + 1, fila, columna)];
            }
        }
        
        direccion_movimiento = determinar_direccion_movimiento(almacen_solucion->secuencia_movimientos[paso_actual]);
        
        printf("Paso %d: Mover el numero %d hacia %s\n", 
               paso_actual + 1, almacen_solucion->numeros_desplazados[paso_actual], direccion_movimiento);
        
        printf("Estado despues del movimiento:\n");
        mostrar_tablero_estado(estado_siguiente);
        printf("\n");
    }
}

void mostrar_tablero_estado(ESTADOTABLERO tablero)
{
    mostrar_tablero_formateado(tablero.tablero);
}

void mostrar_tablero_formateado(int configuracion[FILAS][COLUMNAS])
{
    int i, j;
    
    printf("+---+---+---+\n");
    for (i = 0; i < FILAS; i++) {
        printf("|");
        for (j = 0; j < COLUMNAS; j++) {
            if (configuracion[i][j] == 0) {
                printf("   |");
            } else {
                printf(" %d |", configuracion[i][j]);
            }
        }
        printf("\n+---+---+---+\n");
    }
}

void prueba_matriz(int configuracion[FILAS][COLUMNAS])
{ 
    mostrar_tablero_formateado(configuracion);
}

void guardar_estado_actual(ALMCENAMIENTOSOLUCION *almacen_solucion, ESTADOTABLERO estado, int indice)
{
    int fila, columna;
    
    for (fila = 0; fila < FILAS; fila++) {
        for (columna = 0; columna < COLUMNAS; columna++) {
            almacen_solucion->datos_tableros[calcular_indice_almacenamiento(indice, fila, columna)] = estado.tablero[fila][columna];
        }
    }
}

void leer_configuracion_puzzle(int configuracion[FILAS][COLUMNAS])
{
    int i, j, valores_leidos, valor_actual, contador_numeros[9];
    int configuracion_valida = 0;
    
    while (!configuracion_valida) {
        printf("Ingrese el puzzle (ej: 1-2-3-4-5-6-7-8-0): ");
        
        valores_leidos = scanf("%d-%d-%d-%d-%d-%d-%d-%d-%d", 
            &configuracion[0][0], &configuracion[0][1], &configuracion[0][2], 
            &configuracion[1][0], &configuracion[1][1], &configuracion[1][2], 
            &configuracion[2][0], &configuracion[2][1], &configuracion[2][2]);
            
        if (valores_leidos != 9) {
            printf("ERROR: Formato incorrecto o incompleto. Intente de nuevo.\n");
            while (getchar() != '\n'); 
            continue; 
        }
        
        for (i = 0; i < 9; i++) {
            contador_numeros[i] = 0;
        }
        configuracion_valida = 1;

        for (i = 0; i < FILAS; i++) {
            for (j = 0; j < COLUMNAS; j++) {
                valor_actual = configuracion[i][j];
                
                if (valor_actual < 0 || valor_actual > 8) {
                    printf("ERROR: El valor %d está fuera del rango [0-8]. Intente de nuevo.\n", valor_actual);
                    configuracion_valida = 0; 
                    break;
                }
                
                if (contador_numeros[valor_actual] > 0) {
                    printf("ERROR: El número %d está repetido. Intente de nuevo.\n", valor_actual);
                    configuracion_valida = 0; 
                    break;
                }
                contador_numeros[valor_actual] = 1;
            }
            if (!configuracion_valida) break;
        }
        
        if (!configuracion_valida) { 
            while (getchar() != '\n'); 
        }
    }
}

void copiar_estado_tablero(ESTADOTABLERO origen, ESTADOTABLERO *destino)
{
    int i, j;
    for (i = 0; i < FILAS; i++) {
        for (j = 0; j < COLUMNAS; j++) {
            destino->tablero[i][j] = origen.tablero[i][j];
        }
    }
}

int comparar_estados_tablero(ESTADOTABLERO estado1, ESTADOTABLERO estado2)
{
    int i, j;
    for (i = 0; i < FILAS; i++) {
        for (j = 0; j < COLUMNAS; j++) {
            if (estado1.tablero[i][j] != estado2.tablero[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

void intercambiar_valores(int *valor_a, int *valor_b)
{
    int valor_temporal;
    valor_temporal = *valor_a;
    *valor_a = *valor_b;
    *valor_b = valor_temporal;
}

int encontrar_posicion_vacia(ESTADOTABLERO tablero, POSICION *pos_vacia)
{
    int i, j;
    for (i = 0; i < FILAS; i++) {
        for (j = 0; j < COLUMNAS; j++) {
            if (tablero.tablero[i][j] == 0) {
                pos_vacia->fila = i;
                pos_vacia->columna = j;
                return 1;
            }
        }
    }
    pos_vacia->fila = -1;
    pos_vacia->columna = -1;
    return -1; 
}

int realizar_intercambio_horizontal(ESTADOTABLERO *tablero, POSICION pos1, POSICION pos2)
{
    if (pos1.fila == pos2.fila) {
        intercambiar_valores(&tablero->tablero[pos1.fila][pos1.columna], &tablero->tablero[pos2.fila][pos2.columna]);
        return 1;
    }
    return 0;
}

int realizar_intercambio_vertical(ESTADOTABLERO *tablero, POSICION pos1, POSICION pos2)
{
    if (pos1.columna == pos2.columna) {
        intercambiar_valores(&tablero->tablero[pos1.fila][pos1.columna], &tablero->tablero[pos2.fila][pos2.columna]);
        return 1;
    }
    return 0;
}