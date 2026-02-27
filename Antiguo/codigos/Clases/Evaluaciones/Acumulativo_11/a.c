/* Bibliotecas */
#include <stdio.h>
#include <stdlib.h> 

/* Constantes del puzzle */
#define FILAS 3 
#define COLUMNAS 3
#define MAX_ESTADOS 950000 

// Función: obtener_indice_1d. Convierte coordenadas 3D (estado, fila, columna) a un índice 1D para malloc.
int obtener_indice_1d(int i, int r, int c);


/* -----------------------------------------------------------------
 * PROTOTIPOS PRINCIPALES
 * ----------------------------------------------------------------- */

// Función: leer_datos_puzzle. Solicita y valida la entrada del puzzle (números 0-8 sin repeticiones).
void leer_datos_puzzle(int [FILAS][COLUMNAS]);

// Función: resolver_puzzle. Implementa el algoritmo BFS (Breadth-First Search) para encontrar la solución.
void resolver_puzzle(int puzzle[FILAS][COLUMNAS], int puzzle_resuelto[FILAS][COLUMNAS]);

// Función: prueba_matriz. Imprime el estado actual de la matriz del puzzle.
void prueba_matriz(int [FILAS][COLUMNAS]); 

/* -----------------------------------------------------------------
 * PROTOTIPOS DE UTILIDADES
 * ----------------------------------------------------------------- */

// Función: copiar_tablero. Copia los elementos de la matriz origen a la matriz destino.
void copiar_tablero(int origen[FILAS][COLUMNAS], int destino[FILAS][COLUMNAS]);

// Función: son_iguales. Compara dos tableros 3x3. Retorna 1 si son iguales, 0 si no.
int son_iguales(int t1[FILAS][COLUMNAS], int t2[FILAS][COLUMNAS]);

// Función: intercambiar. Intercambia los valores de dos punteros enteros.
void intercambiar(int *a, int *b);

// Función: buscar_0. Encuentra la posición (fila, columna) del espacio vacío ('0') en el tablero.
int buscar_0(int tablero[FILAS][COLUMNAS], int *fila, int *col);

// Función: intercambio_horizontal. Intercambia dos posiciones solo si están en la misma fila (Requisito 4).
int intercambio_horizontal(int tablero[FILAS][COLUMNAS], int r1, int c1, int r2, int c2); 

// Función: intercambio_vertical. Intercambia dos posiciones solo si están en la misma columna (Requisito 5).
int intercambio_vertical(int tablero[FILAS][COLUMNAS], int r1, int c1, int r2, int c2); 

/* -----------------------------------------------------------------
 * PROTOTIPOS DE UTILIDADES BFS
 * ----------------------------------------------------------------- */

// Función: ya_visitado_array. Verifica si un tablero ya ha sido generado (búsqueda lineal).
int ya_visitado_array(int *historia, int tablero[FILAS][COLUMNAS], int estados_generados);

// Función: imprimir_solucion_array. Imprime la ruta de solución, mostrando la ficha numerada que se mueve.
void imprimir_solucion_array(int *historia, int *padres, int *movimientos, int idx_solucion);


/* Variables Globales para Movimiento */
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
    
    resolver_puzzle(puzzle, puzzle_resuelto);

    return 0;
}

/* -----------------------------------------------------------------
 * IMPLEMENTACIÓN DE FUNCIONES
 * ----------------------------------------------------------------- */

int obtener_indice_1d(int i, int r, int c) {
    return (i * FILAS * COLUMNAS) + (r * COLUMNAS) + c;
}


void resolver_puzzle(int inicial[FILAS][COLUMNAS], int objetivo[FILAS][COLUMNAS]){
    
    size_t size_tableros = MAX_ESTADOS * FILAS * COLUMNAS * sizeof(int); 
    size_t size_meta = MAX_ESTADOS * sizeof(int);                       
    
    /* Asignación dinámica en el Heap */
    int *cola_tableros = (int *)malloc(size_tableros);
    int *cola_padres = (int *)malloc(size_meta);
    int *cola_movimientos = (int *)malloc(size_meta);
    int *cola_fila_cero = (int *)malloc(size_meta); 
    int *cola_col_cero = (int *)malloc(size_meta); 

    /* Verificación de asignación */
    if (!cola_tableros || !cola_padres || !cola_movimientos || !cola_fila_cero || !cola_col_cero) {
        printf("ERROR: Fallo al asignar memoria (malloc). Se superó el límite del Heap.\n");
        free(cola_tableros);
        free(cola_padres);
        free(cola_movimientos);
        free(cola_fila_cero);
        free(cola_col_cero);
        return;
    }
    
    int frente = 0; 
    int final = 0;  
    int estados_generados = 0;
    int direccion;
    
    int actual_f_cero, actual_c_cero;
    int tablero_temporal[FILAS][COLUMNAS];

    if (son_iguales(inicial, objetivo)) {
        printf("EL PUZZLE YA ESTA RESUELTO (0 pasos).\n");
        free(cola_tableros); free(cola_padres); free(cola_movimientos); free(cola_fila_cero); free(cola_col_cero);
        return;
    }
    
    /* Inicializar estado inicial y encolar */
    for(int r=0; r<FILAS; r++){
        for(int c=0; c<COLUMNAS; c++){
            cola_tableros[obtener_indice_1d(final, r, c)] = inicial[r][c];
        }
    }
    
    buscar_0(inicial, &actual_f_cero, &actual_c_cero);
    
    cola_padres[final] = -1; 
    cola_movimientos[final] = -1;
    cola_fila_cero[final] = actual_f_cero;
    cola_col_cero[final] = actual_c_cero;
    
    final++;
    estados_generados++;
    
    printf("--- BUSCANDO SOLUCION ---\n");
    
    /* Búsqueda BFS */
    while (frente < final) {
        
        int idx_actual = frente;
        frente++; 
        
        actual_f_cero = cola_fila_cero[idx_actual];
        actual_c_cero = cola_col_cero[idx_actual];
        
        /* Obtener el tablero actual */
        for (int r = 0; r < FILAS; r++) {
            for (int c = 0; c < COLUMNAS; c++) {
                tablero_temporal[r][c] = cola_tableros[obtener_indice_1d(idx_actual, r, c)];
            }
        }
        
        for (direccion = 0; direccion < 4; direccion++) {
            
            int nueva_f = actual_f_cero + dir_fila[direccion];
            int nueva_c = actual_c_cero + dir_col[direccion];

            /* Verificar límites del tablero */
            if (nueva_f < 0 || nueva_f >= FILAS || nueva_c < 0 || nueva_c >= COLUMNAS) {
                continue; 
            }

            /* Crear el nuevo estado */
            copiar_tablero( (int (*)[COLUMNAS])&cola_tableros[obtener_indice_1d(idx_actual, 0, 0)], tablero_temporal);
            
            /* Intercambiar (mover el 0) */
            if (dir_fila[direccion] == 0) { 
                intercambio_horizontal(tablero_temporal, actual_f_cero, actual_c_cero, nueva_f, nueva_c);
            } else { 
                intercambio_vertical(tablero_temporal, actual_f_cero, actual_c_cero, nueva_f, nueva_c);
            }
            
            /* Si es el objetivo, terminar */
            if (son_iguales(tablero_temporal, objetivo)) {
                printf("*** SOLUCION ENCONTRADA! ***\n");
                
                if (estados_generados < MAX_ESTADOS) {
                    /* Guardar estado solución */
                    for(int r=0; r<FILAS; r++){
                        for(int c=0; c<COLUMNAS; c++){
                            cola_tableros[obtener_indice_1d(final, r, c)] = tablero_temporal[r][c];
                        }
                    }
                    cola_padres[final] = idx_actual;
                    cola_movimientos[final] = direccion;
                    
                    imprimir_solucion_array(cola_tableros, cola_padres, cola_movimientos, final);
                }
                /* Liberación de memoria */
                free(cola_tableros); free(cola_padres); free(cola_movimientos); free(cola_fila_cero); free(cola_col_cero);
                return;
            }
            
            /* Si no ha sido visitado y hay espacio, agregar a la cola */
            if (estados_generados < MAX_ESTADOS && !ya_visitado_array(cola_tableros, tablero_temporal, estados_generados)) { 
                /* Encolar: copiar el nuevo estado */
                for(int r=0; r<FILAS; r++){
                    for(int c=0; c<COLUMNAS; c++){
                        cola_tableros[obtener_indice_1d(final, r, c)] = tablero_temporal[r][c];
                    }
                }
                
                cola_padres[final] = idx_actual;
                cola_movimientos[final] = direccion;
                cola_fila_cero[final] = nueva_f;
                cola_col_cero[final] = nueva_c;
                
                final++;
                estados_generados++;
            }
        }
    }
    
    printf("El puzzle no tiene solucion (o se excedió el limite de %d estados).\n", MAX_ESTADOS);
    
    /* Liberación de memoria */
    free(cola_tableros); free(cola_padres); free(cola_movimientos); free(cola_fila_cero); free(cola_col_cero);
}


void imprimir_solucion_array(int *historia, int *padres, int *movimientos, int idx_solucion){
    int ruta_movimientos_indices[MAX_ESTADOS];
    int ruta_indices_tableros[MAX_ESTADOS]; 
    int i, num_movimientos = 0;
    int actual_idx = idx_solucion;
    
    /* Recorrer hacia atrás para obtener la ruta */
    while (actual_idx != -1) {
        if (padres[actual_idx] != -1) { 
            ruta_movimientos_indices[num_movimientos] = movimientos[actual_idx];
        }
        ruta_indices_tableros[num_movimientos] = actual_idx;
        num_movimientos++;
        actual_idx = padres[actual_idx];
    }
    
    printf("Respuesta: %d pasos\n", num_movimientos - 1); 
    printf("\n--- SECUENCIA DE MOVIMIENTOS ---\n");
    
    int tablero_actual[FILAS][COLUMNAS];
    int indice_actual;
    int numero_movido;

    /* Iterar la ruta al derecho */
    for (i = (num_movimientos - 2); i >= 0; i--) { 

        indice_actual = ruta_indices_tableros[i];     
        int direccion_mov_0 = ruta_movimientos_indices[i];
        
        /* Cargar el estado actual */
        for(int r=0; r<FILAS; r++){
            for(int c=0; c<COLUMNAS; c++){
                tablero_actual[r][c] = historia[obtener_indice_1d(indice_actual, r, c)];
            }
        }
        
        /* Calcular la posición donde se movió el número */
        int r_cero_act, c_cero_act;
        buscar_0(tablero_actual, &r_cero_act, &c_cero_act);
        
        /* Posición que ocupaba el 0 en el estado anterior */
        int r_cero_ant = r_cero_act - dir_fila[direccion_mov_0];
        int c_cero_ant = c_cero_act - dir_col[direccion_mov_0];
        
        /* El número movido es el que ocupa esa posición en el estado actual */
        numero_movido = tablero_actual[r_cero_ant][c_cero_ant];


        printf("Paso %d: Mover el %d hacia %s\n", 
               (num_movimientos - 1 - i), 
               numero_movido, 
               nombre_mov[direccion_mov_0]);
    }
    
    printf("\n--- ESTADO FINAL (OBJETIVO) ---\n");
    
    /* Cargar e imprimir el estado final */
    int tablero_final[FILAS][COLUMNAS];
    for(int r=0; r<FILAS; r++){
        for(int c=0; c<COLUMNAS; c++){
            tablero_final[r][c] = historia[obtener_indice_1d(idx_solucion, r, c)];
        }
    }
    prueba_matriz(tablero_final);
}


int ya_visitado_array(int *historia, int tablero[FILAS][COLUMNAS], int estados_generados)
{
    int i, r, c;
    for (i = 0; i < estados_generados; i++) {
        int iguales = 1;
        
        for(r=0; r<FILAS; r++){
            for(c=0; c<COLUMNAS; c++){
                if(tablero[r][c] != historia[obtener_indice_1d(i, r, c)]){
                    iguales = 0;
                    break;
                }
            }
            if (!iguales) break;
        }

        if (iguales)
            return 1;
    }
    return 0;
}


void leer_datos_puzzle(int puzzle[FILAS][COLUMNAS]){
    int i, j, leidos;
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

        int contador[9] = {0};
        valido = 1;

        for(i = 0; i < FILAS; i++) {
            for(j = 0; j < COLUMNAS; j++) {
                int valor = puzzle[i][j];
                
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

void copiar_tablero(int origen[FILAS][COLUMNAS], int destino[FILAS][COLUMNAS])
{
    int i, j;
    for (i = 0; i < FILAS; i++)
        for (j = 0; j < COLUMNAS; j++)
            destino[i][j] = origen[i][j];
}

int son_iguales(int t1[FILAS][COLUMNAS], int t2[FILAS][COLUMNAS])
{
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