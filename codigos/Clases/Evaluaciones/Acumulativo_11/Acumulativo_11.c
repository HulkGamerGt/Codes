// revisar y cambiar nombres, entender logica y crear la documentacion, tecnica, guia de uso 
//y comentarios en el codigo

#include <stdio.h>
#include <stdlib.h> // LIBRERÍA NECESARIA para malloc/free

#define FILAS 3 
#define COLUMNAS 3
#define MAX_ESTADOS 950000 // Límite máximo de estados a generar

/* FUNCIÓN DE INDEXACIÓN 1D (Reemplaza la macro) */
// Calcula la posición exacta en el puntero 1D
int obtener_indice_1d(int i, int r, int c) {    
    // i: número de estado (tablero)           
    // r: fila                                 
    // c: columna
    return (i * FILAS * COLUMNAS) + (r * COLUMNAS) + c;
}


/* -----------------------------------------------------------------
 * PROTOTIPOS 
 * ----------------------------------------------------------------- */
void leer_datos_puzzle(int [FILAS][COLUMNAS]);
void resolver_puzzle(int puzzle[FILAS][COLUMNAS], int puzzle_resuelto[FILAS][COLUMNAS]);
void prueba_matriz(int [FILAS][COLUMNAS]); 

/* UTILIDADES */
void copiar_tablero(int origen[FILAS][COLUMNAS], int destino[FILAS][COLUMNAS]);
int son_iguales(int t1[FILAS][COLUMNAS], int t2[FILAS][COLUMNAS]);
void intercambiar(int *a, int *b);
int buscar_0(int tablero[FILAS][COLUMNAS], int *fila, int *col);


int intercambio_horizontal(int tablero[FILAS][COLUMNAS], int r1, int c1, int r2, int c2); 
int intercambio_vertical(int tablero[FILAS][COLUMNAS], int r1, int c1, int r2, int c2); 

/* Utilitarios de BFS (usando punteros dinámicos) */
int ya_visitado_array(int *historia, int tablero[FILAS][COLUMNAS], int estados_generados);
void imprimir_solucion_array(int *historia, int *padres, int *movimientos, int idx_solucion);


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
    
    resolver_puzzle(puzzle, puzzle_resuelto);

    return 0;
}

/* -----------------------------------------------------------------
 * IMPLEMENTACIÓN DEL ALGORITMO BFS (REQUISITO 6)
 * ----------------------------------------------------------------- */

void resolver_puzzle(int inicial[FILAS][COLUMNAS], int objetivo[FILAS][COLUMNAS]){
    
    // Calcular tamaños en bytes para malloc
    size_t size_tableros = MAX_ESTADOS * FILAS * COLUMNAS * sizeof(int); 
    size_t size_meta = MAX_ESTADOS * sizeof(int);                       
    
    // ASIGNACIÓN DE MEMORIA EN EL HEAP (Montículo)
    int *cola_tableros = (int *)malloc(size_tableros);
    int *cola_padres = (int *)malloc(size_meta);
    int *cola_movimientos = (int *)malloc(size_meta);
    int *cola_fila_cero = (int *)malloc(size_meta); 
    int *cola_col_cero = (int *)malloc(size_meta); 

    // Verificar si la asignación falló
    if (!cola_tableros || !cola_padres || !cola_movimientos || !cola_fila_cero || !cola_col_cero) {
        printf("ERROR: Fallo al asignar memoria (malloc). Se superó el límite del Heap.\n");
        // Limpiar la memoria antes de salir (solo lo que se logró asignar)
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
        // Asegurarse de liberar memoria incluso si se sale temprano
        free(cola_tableros); free(cola_padres); free(cola_movimientos); free(cola_fila_cero); free(cola_col_cero);
        return;
    }
    
    // 1. Inicializar estado inicial y encolar
    // Copiar el tablero inicial a la posición 0 de la cola_tableros (usando función)
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
    
    // 2. BFS: Explorar
    while (frente < final) {

        int idx_actual = frente;// Índice del estado actual
        frente++;

        actual_f_cero = cola_fila_cero[idx_actual];
        actual_c_cero = cola_col_cero[idx_actual];
        
        // Obtener el tablero actual de la cola y copiarlo a tablero_temporal
        for (int r = 0; r < FILAS; r++) {
            for (int c = 0; c < COLUMNAS; c++) {
                // ACCESO CON LA FUNCIÓN
                tablero_temporal[r][c] = cola_tableros[obtener_indice_1d(idx_actual, r, c)];
            }
        }
        
        for (direccion = 0; direccion < 4; direccion++) {
            
            int nueva_f = actual_f_cero + dir_fila[direccion];
            int nueva_c = actual_c_cero + dir_col[direccion];

            if (nueva_f < 0 || nueva_f >= FILAS || nueva_c < 0 || nueva_c >= COLUMNAS) {
                continue; 
            }

            // 2b. Crear el nuevo estado (copiando del tablero actual a temp)
            copiar_tablero( (int (*)[COLUMNAS])&cola_tableros[obtener_indice_1d(idx_actual, 0, 0)], tablero_temporal);
            
            // Usar R4 o R5
            if (dir_fila[direccion] == 0) { 
                intercambio_horizontal(tablero_temporal, actual_f_cero, actual_c_cero, nueva_f, nueva_c);
            } else { 
                intercambio_vertical(tablero_temporal, actual_f_cero, actual_c_cero, nueva_f, nueva_c);
            }
            
            // 2c. Si es el objetivo, terminar
            if (son_iguales(tablero_temporal, objetivo)) {
                printf("*** SOLUCION ENCONTRADA! ***\n");
                
                if (estados_generados < MAX_ESTADOS) {
                    // Copiar el tablero final a la última posición de la cola_tableros (usando función)
                    for(int r=0; r<FILAS; r++){
                        for(int c=0; c<COLUMNAS; c++){
                            cola_tableros[obtener_indice_1d(final, r, c)] = tablero_temporal[r][c];
                        }
                    }
                    cola_padres[final] = idx_actual;
                    cola_movimientos[final] = direccion;
                    
                    imprimir_solucion_array(cola_tableros, cola_padres, cola_movimientos, final);
                }
                // LIBERACIÓN DE MEMORIA
                free(cola_tableros); free(cola_padres); free(cola_movimientos); free(cola_fila_cero); free(cola_col_cero);
                return;
            }
            
            // 2d. Si no ha sido visitado y hay espacio, agregar a la cola
            if (estados_generados < MAX_ESTADOS && !ya_visitado_array(cola_tableros, tablero_temporal, estados_generados)) { 
                // Encolar: copiar el nuevo estado (usando función)
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
    
    // LIBERACIÓN DE MEMORIA
    free(cola_tableros); free(cola_padres); free(cola_movimientos); free(cola_fila_cero); free(cola_col_cero);
}

/**
 * Requisito 6: Muestra la secuencia de movimientos y el tablero final
 */
void imprimir_solucion_array(int *historia, int *padres, int *movimientos, int idx_solucion){
    int ruta_movimientos_indices[MAX_ESTADOS];
    int i, num_movimientos = 0;
    int actual_idx = idx_solucion;
    
    // 1. Recorrer hacia atrás, guardando los movimientos
    while (padres[actual_idx] != -1) {
        ruta_movimientos_indices[num_movimientos++] = movimientos[actual_idx];
        actual_idx = padres[actual_idx];
    }
    
    // 2. Imprimir el resultado
    printf("Respuesta: %d pasos\n", num_movimientos);
    printf("\n--- SECUENCIA DE MOVIMIENTOS ---\n");
    for (i = num_movimientos - 1; i >= 0; i--) {
        printf("Paso %d: Mover el 0 hacia %s\n", 
               (num_movimientos - i), nombre_mov[ruta_movimientos_indices[i]]);
    }
    
    printf("\n--- ESTADO FINAL (OBJETIVO) ---\n");
    
    // Crear un tablero temporal para imprimir el estado final (usando la función)
    int tablero_final[FILAS][COLUMNAS];
    for(int r=0; r<FILAS; r++){
        for(int c=0; c<COLUMNAS; c++){
            tablero_final[r][c] = historia[obtener_indice_1d(idx_solucion, r, c)];
        }
    }
    prueba_matriz(tablero_final);
}


/* -----------------------------------------------------------------
 * IMPLEMENTACIÓN DE UTILIDADES
 * ----------------------------------------------------------------- */

/**
 * Verifica si un estado ya fue generado y guardado en la historia.
 */
int ya_visitado_array(int *historia, int tablero[FILAS][COLUMNAS], int estados_generados)
{
    int i, r, c;
    for (i = 0; i < estados_generados; i++) {
        int iguales = 1;
        // Comparar tablero con historia[i] (usando función)
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


/**
 * Requisito 2: Lee y valida la entrada (0-8 sin repeticiones).
 */
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

/**
 * Requisito 3: Muestra el estado de la matriz.
 */
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

/**
 * Requisito 4: Intercambio Horizontal (Solo si es misma fila).
 */
int intercambio_horizontal(int tablero[FILAS][COLUMNAS], int r1, int c1, int r2, int c2) {
    if (r1 == r2) {
        intercambiar(&tablero[r1][c1], &tablero[r2][c2]);
        return 1;
    }
    return 0;
}

/**
 * Requisito 5: Intercambio Vertical (Solo si es misma columna).
 */
int intercambio_vertical(int tablero[FILAS][COLUMNAS], int r1, int c1, int r2, int c2) {
    if (c1 == c2) {
        intercambiar(&tablero[r1][c1], &tablero[r2][c2]);
        return 1;
    }
    return 0;
}