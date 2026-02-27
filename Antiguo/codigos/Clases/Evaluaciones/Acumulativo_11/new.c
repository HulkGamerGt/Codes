#include <stdio.h>
#include <string.h>

#define FILAS 3
#define COLUMNAS 3
#define MAX_MOV 15
#define MAX_ESTADOS 10000

int mov_fila[] = {0, 1, 0, -1};
int mov_col[] = {1, 0, -1, 0};
char *nombres_dir[] = {"IZQUIERDA", "ARRIBA", "DERECHA", "ABAJO"};

void copiar_tablero(int destino[FILAS][COLUMNAS], int origen[FILAS][COLUMNAS]) 
{
    int i, j;
    for (i = 0; i < FILAS; i++) 
    {
        for (j = 0; j < COLUMNAS; j++) 
        {
            destino[i][j] = origen[i][j];
        }
    }
}

int tableros_iguales(int tab1[FILAS][COLUMNAS], int tab2[FILAS][COLUMNAS]) 
{
    int i, j;
    for (i = 0; i < FILAS; i++) 
    {
        for (j = 0; j < COLUMNAS; j++) 
        {
            if (tab1[i][j] != tab2[i][j]) 
            {
                return 0;
            }
        }
    }
    return 1;
}

void intercambiar(int *a, int *b) 
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void leer_tablero(int tablero[FILAS][COLUMNAS]) 
{
    int valido, i, j, leidos;
    
    valido = 0;
    while(valido == 0) 
    {
        printf("Ingrese el puzzle (1-2-3-4-5-6-7-8-0): ");
        
        leidos = scanf("%d-%d-%d-%d-%d-%d-%d-%d-%d",
            &tablero[0][0], &tablero[0][1], &tablero[0][2],
            &tablero[1][0], &tablero[1][1], &tablero[1][2],
            &tablero[2][0], &tablero[2][1], &tablero[2][2]);
            
        if(leidos == 9) 
        {
            valido = 1;
        }
        else
        {
            printf("Formato incorrecto.\n");
        }
        while(getchar() != '\n');
    }
}

void mostrar_tablero(int tablero[FILAS][COLUMNAS]) 
{
    int i, j;
    printf("+---+---+---+\n");
    for (i = 0; i < FILAS; i++) 
    {
        printf("|");
        for (j = 0; j < COLUMNAS; j++) 
        {
            if (tablero[i][j] == 0) 
            {
                printf("   |");
            } 
            else 
            {
                printf(" %d |", tablero[i][j]);
            }
        }
        printf("\n+---+---+---+\n");
    }
}

int resolver_puzzle(int inicio[FILAS][COLUMNAS], int objetivo[FILAS][COLUMNAS]) 
{
    int cola[MAX_ESTADOS][FILAS][COLUMNAS];
    int dirs[MAX_ESTADOS];
    int nums[MAX_ESTADOS];
    int previo[MAX_ESTADOS];
    int visitados[MAX_ESTADOS][FILAS][COLUMNAS];
    int total_visitados, frente, final;
    int i, j, dir, fila_v, col_v, nueva_f, nueva_c, num, visto;
    int camino[MAX_MOV+1];
    int pasos, indice;
    int actual[FILAS][COLUMNAS];
    int siguiente[FILAS][COLUMNAS];

    frente = 0;
    final = 0;
    total_visitados = 0;
    
    copiar_tablero(cola[final], inicio);
    dirs[final] = -1;
    nums[final] = -1;
    previo[final] = -1;
    final++;

    copiar_tablero(visitados[total_visitados], inicio);
    total_visitados++;

    while (frente < final && final < MAX_ESTADOS) 
    {
        copiar_tablero(actual, cola[frente]);
        indice = frente;

        if (tableros_iguales(actual, objetivo) == 1) 
        {
            pasos = 0;
            i = indice;

            while (i != -1) 
            {
                camino[pasos] = i;
                pasos++;
                i = previo[i];
            }

            printf("\nSOLUCION ENCONTRADA\n");
            printf("Movimientos: %d\n\n", pasos - 1);
            printf("Estado inicial:\n");
            mostrar_tablero(inicio);

            for (i = 1; i < pasos; i++) 
            {
                int pos = camino[pasos - 1 - i];
                printf("\nPaso %d:\n", i);
                printf("Mover %d hacia %s\n", nums[pos], nombres_dir[dirs[pos]]);
                printf("Estado:\n");
                mostrar_tablero(cola[pos]);
            }
            return 1;
        }

        for (fila_v = 0; fila_v < FILAS; fila_v++) 
        {
            for (col_v = 0; col_v < COLUMNAS; col_v++) 
            {
                if (actual[fila_v][col_v] == 0) break;
            }
            if (col_v < COLUMNAS && actual[fila_v][col_v] == 0) break;
        }
        
        for (dir = 0; dir < 4; dir++) 
        {
            nueva_f = fila_v + mov_fila[dir];
            nueva_c = col_v + mov_col[dir];
            
            if (nueva_f < 0) continue;
            if (nueva_f >= FILAS) continue;
            if (nueva_c < 0) continue;
            if (nueva_c >= COLUMNAS) continue;

            copiar_tablero(siguiente, actual);
            num = siguiente[nueva_f][nueva_c];
            intercambiar(&siguiente[fila_v][col_v], &siguiente[nueva_f][nueva_c]);

            visto = 0;
            for (j = 0; j < total_visitados; j++) 
            {
                if (tableros_iguales(siguiente, visitados[j]) == 1) 
                { 
                    visto = 1;
                    break;
                }
            }
            if (visto == 1) continue;

            copiar_tablero(cola[final], siguiente);
            dirs[final] = dir;
            nums[final] = num;
            previo[final] = indice;
            final++;

            copiar_tablero(visitados[total_visitados], siguiente);
            total_visitados++;
        }
        frente++;
    }
    
    return 0;
}

int main() 
{
    int inicio[FILAS][COLUMNAS];
    int objetivo[FILAS][COLUMNAS] = {{1,2,3}, {4,5,6}, {7,8,0}};

    printf("RESUELVE 8-PUZZLE\n");
    printf("Maximo: %d movimientos\n\n", MAX_MOV);

    leer_tablero(inicio);
    
    printf("\nEstado inicial:\n");
    mostrar_tablero(inicio);

    printf("\nBuscando solucion...\n");

    if (resolver_puzzle(inicio, objetivo) == 0) 
    {
        printf("\nNo hay solucion en %d movimientos\n", MAX_MOV);
    }

    return 0;
}