#include <stdio.h>
#include <string.h>

#define FILAS 3
#define COLUMNAS 3
#define MAX_MOVIMIENTOS 20
#define MAX_COLA 50000

typedef struct { 
    int celdas[FILAS][COLUMNAS]; 
} Tablero;

typedef struct { 
    int fila, columna; 
} Posicion;

/* Direcciones de movimiento: cuando el espacio vacio se mueve, el numero se mueve en direccion opuesta */
int desplazamiento_fila[] = { 0, 1, 0, -1};
int desplazamiento_columna[] = { 1, 0,-1,  0};
char *nombres_direcciones[] = {"IZQUIERDA", "ARRIBA", "DERECHA", "ABAJO"};

/* Variables para la busqueda por anchura (BFS) */
Tablero estados_cola[MAX_COLA];
int indice_padre[MAX_COLA];
int direccion_movimiento[MAX_COLA];
int numero_movido[MAX_COLA];
int nivel_profundidad[MAX_COLA];
int indice_frente, indice_final;

void copiar_tablero(Tablero *origen, Tablero *destino) 
{ 
    memcpy(destino, origen, sizeof(Tablero)); 
}

int comparar_tableros(Tablero *tablero1, Tablero *tablero2) 
{ 
    return memcmp(tablero1, tablero2, sizeof(Tablero)) == 0; 
}

void intercambiar_numeros(int *numero1, int *numero2) 
{ 
    int temporal = *numero1; 
    *numero1 = *numero2; 
    *numero2 = temporal; 
}

Posicion buscar_espacio_vacio(Tablero *tablero) 
{
    Posicion posicion;
    int fila, columna;
    
    for (fila = 0; fila < FILAS; fila++) {
        for (columna = 0; columna < COLUMNAS; columna++) {
            if (tablero->celdas[fila][columna] == 0) { 
                posicion.fila = fila; 
                posicion.columna = columna; 
                return posicion; 
            }
        }
    }
    posicion.fila = -1;
    posicion.columna = -1; 
    return posicion;
}

void solicitar_tablero_usuario(Tablero *tablero) 
{
    int valor, numeros_usados[9] = {0}, entrada_valida = 0;
    int fila, columna, valores_leidos;
    
    while(!entrada_valida) {
        printf("Ingrese el puzzle (ej: 1-2-3-4-5-6-7-8-0): ");
        
        valores_leidos = scanf("%d-%d-%d-%d-%d-%d-%d-%d-%d",
            &tablero->celdas[0][0], &tablero->celdas[0][1], &tablero->celdas[0][2],
            &tablero->celdas[1][0], &tablero->celdas[1][1], &tablero->celdas[1][2],
            &tablero->celdas[2][0], &tablero->celdas[2][1], &tablero->celdas[2][2]);
            
        if(valores_leidos != 9) {
            printf("Formato incorrecto. Use: 1-2-3-4-5-6-7-8-0\n");
            while(getchar() != '\n'); 
            continue; 
        }

        entrada_valida = 1;
        memset(numeros_usados, 0, sizeof(numeros_usados));
        
        for (fila = 0; fila < FILAS && entrada_valida; fila++) {
            for (columna = 0; columna < COLUMNAS; columna++) {
                valor = tablero->celdas[fila][columna];
                if (valor < 0 || valor > 8 || numeros_usados[valor]++) {
                    printf("Error: valores invalidos o repetidos.\n");
                    entrada_valida = 0; 
                    break;
                }
            }
        }
        while(getchar() != '\n');
    }
}

void mostrar_estado_tablero(Tablero *tablero) 
{
    int fila, columna;
    
    printf("+---+---+---+\n");
    for (fila = 0; fila < FILAS; fila++) {
        printf("|");
        for (columna = 0; columna < COLUMNAS; columna++) {
            if (tablero->celdas[fila][columna] == 0) {
                printf("   |");
            } else {
                printf(" %d |", tablero->celdas[fila][columna]);
            }
        }
        printf("\n+---+---+---+\n");
    }
}

int buscar_solucion_optima(Tablero *estado_inicial, Tablero *estado_objetivo, 
                          Tablero *camino_solucion, int *direcciones_solucion, 
                          int *numeros_solucion, int *total_estados_solucion) 
{
    Tablero estados_visitados[MAX_COLA];
    int total_estados_visitados = 0;
    int indice, paso, indice_camino, direccion, nivel, indice_actual;
    int nueva_fila, nueva_columna, numero_a_mover, estado_ya_visitado, contador;
    int ruta_camino[MAX_MOVIMIENTOS + 10];
    int total_pasos_ruta;
    Posicion posicion_vacia;
    Tablero estado_actual, estado_siguiente;

    /* Inicializar busqueda por anchura */
    indice_frente = 0;
    indice_final = 0;
    
    copiar_tablero(estado_inicial, &estados_cola[indice_final]);
    indice_padre[indice_final] = -1;
    direccion_movimiento[indice_final] = -1;
    numero_movido[indice_final] = -1;
    nivel_profundidad[indice_final] = 0;
    indice_final++;

    copiar_tablero(estado_inicial, &estados_visitados[total_estados_visitados]);
    total_estados_visitados++;

    /* Ejecutar busqueda BFS */
    while (indice_frente < indice_final && indice_final < MAX_COLA) {
        copiar_tablero(&estados_cola[indice_frente], &estado_actual);
        indice_actual = indice_frente;
        nivel = nivel_profundidad[indice_frente];

        /* Verificar si se encontro el estado objetivo */
        if (comparar_tableros(&estado_actual, estado_objetivo)) {
            total_pasos_ruta = 0;
            indice = indice_actual;

            /* Reconstruir la ruta de la solucion desde el final hasta el inicio */
            while (indice != -1) {
                ruta_camino[total_pasos_ruta] = indice;
                total_pasos_ruta++;
                indice = indice_padre[indice];
            }

            *total_estados_solucion = total_pasos_ruta;
            
            /* Almacenar la solucion completa en orden correcto */
            for (paso = 0; paso < total_pasos_ruta; paso++) {
                indice_camino = ruta_camino[total_pasos_ruta - 1 - paso];
                copiar_tablero(&estados_cola[indice_camino], &camino_solucion[paso]);
                if (paso > 0) {
                    direcciones_solucion[paso-1] = direccion_movimiento[indice_camino];
                    numeros_solucion[paso-1] = numero_movido[indice_camino];
                }
            }
            return 1;
        }

        /* Generar todos los movimientos posibles desde el estado actual */
        posicion_vacia = buscar_espacio_vacio(&estado_actual);
        
        for (direccion = 0; direccion < 4; direccion++) {
            nueva_fila = posicion_vacia.fila + desplazamiento_fila[direccion];
            nueva_columna = posicion_vacia.columna + desplazamiento_columna[direccion];
            
            if (nueva_fila < 0 || nueva_fila >= FILAS || 
                nueva_columna < 0 || nueva_columna >= COLUMNAS) {
                continue;
            }

            copiar_tablero(&estado_actual, &estado_siguiente);
            numero_a_mover = estado_siguiente.celdas[nueva_fila][nueva_columna];
            intercambiar_numeros(&estado_siguiente.celdas[posicion_vacia.fila][posicion_vacia.columna], 
                        &estado_siguiente.celdas[nueva_fila][nueva_columna]);

            /* Verificar si este estado ya fue visitado */
            estado_ya_visitado = 0;
            for (contador = 0; contador < total_estados_visitados; contador++) {
                if (comparar_tableros(&estado_siguiente, &estados_visitados[contador])) { 
                    estado_ya_visitado = 1; 
                    break; 
                }
            }
            if (estado_ya_visitado) continue;

            /* Agregar el nuevo estado a la cola de busqueda */
            copiar_tablero(&estado_siguiente, &estados_cola[indice_final]);
            indice_padre[indice_final] = indice_actual;
            direccion_movimiento[indice_final] = direccion;
            numero_movido[indice_final] = numero_a_mover;
            nivel_profundidad[indice_final] = nivel + 1;
            indice_final++;

            /* Registrar el estado como visitado */
            if (total_estados_visitados < MAX_COLA) {
                copiar_tablero(&estado_siguiente, &estados_visitados[total_estados_visitados]);
                total_estados_visitados++;
            }
        }
        indice_frente++;
    }
    
    return 0;
}

void mostrar_solucion_completa(Tablero *estados_solucion, int *direcciones_movimientos, 
                              int *numeros_movidos, int total_estados, Tablero *estado_inicial) 
{
    int paso;
    
    printf("\n=========================================\n");
    printf("           SOLUCION ENCONTRADA\n");
    printf("=========================================\n");
    printf("Total de movimientos: %d\n\n", total_estados - 1);

    printf("Estado inicial:\n");
    mostrar_estado_tablero(estado_inicial);
    printf("\n");

    /* Mostrar cada paso de la solucion */
    for (paso = 1; paso < total_estados; paso++) {
        printf("--- Paso %d ---\n", paso);
        printf("Movimiento: Mover numero %d hacia %s\n", 
               numeros_movidos[paso-1], nombres_direcciones[direcciones_movimientos[paso-1]]);
        printf("Estado resultante:\n");
        mostrar_estado_tablero(&estados_solucion[paso]);
        printf("\n");
    }

    printf("=========================================\n");
    printf("          SOLUCION COMPLETADA\n");
    printf("=========================================\n");
}

int main() 
{
    Tablero estado_inicial, estado_objetivo = {
        {{1, 2, 3},
         {4, 5, 6},
         {7, 8, 0}}
    };
    
    Tablero estados_solucion[MAX_MOVIMIENTOS + 1];
    int direcciones_solucion[MAX_MOVIMIENTOS];
    int numeros_solucion[MAX_MOVIMIENTOS];
    int total_estados_solucion;
    int solucion_encontrada;

    printf("RESOLVEDOR DE 8-PUZZLE\n");
    printf("Maximo de movimientos: %d\n\n", MAX_MOVIMIENTOS);

    solicitar_tablero_usuario(&estado_inicial);
    
    printf("\nEstado inicial del puzzle:\n");
    mostrar_estado_tablero(&estado_inicial);

    printf("\nBuscando solucion optima...\n");

    solucion_encontrada = buscar_solucion_optima(&estado_inicial, &estado_objetivo, estados_solucion, direcciones_solucion, numeros_solucion, &total_estados_solucion);

    if (solucion_encontrada) {
        mostrar_solucion_completa(estados_solucion, direcciones_solucion, numeros_solucion, total_estados_solucion, &estado_inicial);
    } else {
        printf("\n-------------------------------------\n");
        printf("  No se encontro solucion en %d movimientos\n", MAX_MOVIMIENTOS);
        printf("-------------------------------------\n");
    }

    return 0;
}