/*
 | Identificación del autor: Diego M. Solis Rojas.
 | Curso: PROGRAMACIÓN-S1 [INF123]
 | Fecha: ( 06 / 10 / 2025 )
 | Descripcion: Este programa resuelve el Laberinto encontrado dentro del codigo, haciendo seguimiento atravez de marcas (.) para
 | |||||||||||  no devolverse, en caso de no haber otras opciones devuelve para seguir buscando, encontrando la marca B
 | |||||||||||  que es el punto final del Laberinto.
*/

#include <stdio.h>

// Constantes para las dimensiones del Laberinto.
#define FILAS 10
#define COLUMNAS 10
#define TRUE 1
#define FALSE 0

// Definición del Laberinto.
char Laberinto[FILAS][COLUMNAS] = {
    {'A', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' '},
    {'#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' '},
    {' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' '},
    {' ', '#', '#', ' ', '#', '#', '#', ' ', '#', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' '},
    {'#', '#', '#', '#', '#', ' ', '#', ' ', '#', ' '},
    {' ', ' ', ' ', 'B', '#', ' ', '#', ' ', ' ', ' '},
    {' ', '#', '#', '#', '#', ' ', '#', '#', '#', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' '},
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', ' '}
};

// Prototipos de funciones
void Mostrar_Mapa(char Laberinto[FILAS][COLUMNAS]); // Muestra el Laberinto.
int Es_Movimiento_Valido(int fila, int columna); // Retorna 1 (TRUE) o 0 (FALSE)
int Calcular_(int fila, int columna, char Laberinto[FILAS][COLUMNAS]); // Retorna 1 (TRUE) o 0 (FALSE)
void jugar(); // Llama a funciones para relizar la recursividad

int main() {
    printf("----- BUSCANDO EL CAMINO DEL LABERINTO RECURSIVO -----\n");
    printf("Buscando el camino desde A hasta B \n");
    printf("Laberinto Inicial:\n");
    Mostrar_Mapa(Laberinto);
    
    jugar();
    
    return 0;
}


void Mostrar_Mapa(char Laberinto[FILAS][COLUMNAS]){
    int i,j;
    for(i = 0; i < FILAS; i++){
        for(j = 0; j < COLUMNAS; j++){
            printf("%c ", Laberinto[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int Es_Movimiento_Valido(int fila, int columna) {
    // Verifica si la fila y la columna están dentro del rango.
    return (fila >= 0 && fila < FILAS && columna >= 0 && columna < COLUMNAS);
}


int Calcular_(int fila, int columna, char Laberinto[FILAS][COLUMNAS]) {
    // Arreglos que definen los 4 movimientos posibles (Abajo, Arriba, Derecha, Izquierda).
    const int MOV_FILA[] =    {0, 1, 0, -1};
    const int MOV_COLUMNA[] = {1, 0, -1, 0};
    const int NUM_MOVIMIENTOS = 4;
    int nueva_fila, nueva_columna;
    int i;

    /* 1. Caso Base: Verificar si la posición es válida (límites). */
    if (!Es_Movimiento_Valido(fila, columna)){
        return FALSE;
    }
    /* 2. Caso Base: Se encontró el destino 'B'. */
    if (Laberinto[fila][columna] == 'B') {
        return TRUE;
    }
    /* 
        3. Caso Base: La celda es un muro ('#') o ya fue visitada ('.').
        'A' es el punto de partida y no se debe considerar un obstáculo.
    */
    if (Laberinto[fila][columna] == '#' || Laberinto[fila][columna] == '.') {
        return FALSE;
    }

    /* --- Marcar y seguir buscar --- */
    
    // Marcar la celda actual como parte de la ruta tentativa (si no es 'A').
    if (Laberinto[fila][columna] != 'A') {
        Laberinto[fila][columna] = '.';
    }
    
    // Intenta moverse en las 4 direcciones.
    for (i = 0; i < NUM_MOVIMIENTOS; i++) {
        nueva_fila = fila + MOV_FILA[i];
        nueva_columna = columna + MOV_COLUMNA[i];

        // Si la ruta desde la nueva posición tiene éxito.
        if (Calcular_(nueva_fila, nueva_columna, Laberinto)) {
            return TRUE;
        }
    }
    /*
        Si ninguna dirección lleva a 'B', desmarcar la celda (si no es 'A')
        y retornar FALSE.
    */
    if (Laberinto[fila][columna] != 'A') {
        Laberinto[fila][columna] = ' '; // Restaurar a espacio vacío.
    }

    return FALSE; // No se encontró ruta desde esta posición.
}

void jugar() {
    // La posición inicial es 'A', que está en Laberinto[0][0].
    int inicio_fila = 0;
    int inicio_columna = 0;

    printf("\nIniciando búsqueda de ruta...\n");
    
    // Iniciar la búsqueda recursiva.
    if (Calcular_(inicio_fila, inicio_columna, Laberinto) == TRUE) {
        printf("¡Ruta encontrada!\n");
        printf("Laberinto con la Solución ('.' marca el camino):\n");
        Mostrar_Mapa(Laberinto);
    } else {
        printf("No se encontró ninguna ruta desde A hasta B.\n");
    }
}