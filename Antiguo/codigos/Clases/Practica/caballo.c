#include <stdio.h>
#include <string.h>
#include <stdlib.h> // ¡CORRECCIÓN CRÍTICA! Necesario para la función abs()

#define N_KNIGHT 5 // Tablero 5x5 para encontrar solucion rapida
#define N_QUEENS 8 // Tamano clasico: 8x8

// Arreglos Globales
int board_knight[N_KNIGHT][N_KNIGHT];
int move_x[] = {2, 1, -1, -2, -2, -1, 1, 2};
int move_y[] = {1, 2, 2, 1, -1, -2, -2, -1};

int board_queens[N_QUEENS];
int solution_count = 0;

// =======================
// PROTOTIPOS DE FUNCIONES
// =======================

// Funciones del Salto del Caballo
void print_solution_knight();
int is_safe_knight(int x, int y);
int solve_knight_tour(int x, int y, int move_count);
void knight_tour_main();

// Funciones de las N-Damas
void print_queens_solution();
int is_safe_queens(int row, int col);
void solve_n_queens(int row);
void n_queens_main();

// ==================
// FUNCIÓN PRINCIPAL
// ==================

int main(){
    int op;
    do{
        printf("Caballo 1, Damas 2\n");
        printf("Ingrese el que quiera: ");
        scanf("%d", &op);
        if (op == 1)
            // 1. Ejecutar el Salto del Caballo (5x5)
            knight_tour_main();
        else if (op == 2)
            // 2. Ejecutar el Problema de las N-Damas (8x8)
            n_queens_main();

        printf("\n======================================================\n");
    }while(1);
    return 0;
}

// ================================
// IMPLEMENTACIÓN DEL SALTO DEL CABALLO
// ================================

void print_solution_knight()
{
    printf("\n--- Solucion del Salto del Caballo (%dx%d) ---\n", N_KNIGHT, N_KNIGHT);
    for (int i = 0; i < N_KNIGHT; i++)
    {
        for (int j = 0; j < N_KNIGHT; j++)
        {
            printf("%3d ", board_knight[i][j]);
        }
        printf("\n");
    }
}

int is_safe_knight(int x, int y)
{
    // 1. Dentro de limites 2. No visitado (valor 0)
    return (x >= 0 && x < N_KNIGHT && y >= 0 && y < N_KNIGHT && board_knight[x][y] == 0);
}

int solve_knight_tour(int x, int y, int move_count)
{
    // Caso base: todas las casillas cubiertas
    if (move_count == N_KNIGHT * N_KNIGHT + 1)
    {
        return 1;
    }

    for (int k = 0; k < 8; k++)
    {
        int next_x = x + move_x[k];
        int next_y = y + move_y[k];

        if (is_safe_knight(next_x, next_y))
        {
            // Elegir: Marcar el movimiento
            board_knight[next_x][next_y] = move_count;

            // Explorar: Llamada recursiva
            if (solve_knight_tour(next_x, next_y, move_count + 1) == 1)
            {
                return 1;
            }

            // Vuelta Atrás: Deshacer el movimiento
            board_knight[next_x][next_y] = 0;
        }
    }
    return 0;
}

void knight_tour_main()
{
    printf("Iniciando busqueda del Salto del Caballo (%dx%d)...\n", N_KNIGHT, N_KNIGHT);

    // Inicializacion forzada a 0 (No visitado)
    for (int i = 0; i < N_KNIGHT; i++)
    {
        for (int j = 0; j < N_KNIGHT; j++)
        {
            board_knight[i][j] = 0;
        }
    }

    // Empezar en (0, 0)
    board_knight[0][0] = 1;

    if (solve_knight_tour(0, 0, 2) == 1)
    {
        print_solution_knight();
    }
    else
    {
        printf("No se pudo encontrar una solucion que cubra todo el tablero %dx%d.\n", N_KNIGHT, N_KNIGHT);
    }
}

// ================================
// IMPLEMENTACIÓN DE LAS N-DAMAS
// ================================

void print_queens_solution()
{
    solution_count++;
    printf("\n--- Solucion #%d ---\n", solution_count);

    for (int i = 0; i < N_QUEENS; i++)
    {
        for (int j = 0; j < N_QUEENS; j++)
        {
            if (board_queens[i] == j)
            {
                printf(" Q ");
            }
            else
            {
                printf(" - ");
            }
        }
        printf("\n");
    }
}

int is_safe_queens(int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        // 1. Verificacion de Columna (Vertical)
        if (board_queens[i] == col)
        {
            return 0;
        }

        // 2. Verificacion de Diagonales: Si las diferencias son iguales, estan en diagonal
        if (abs(board_queens[i] - col) == abs(i - row))
        {
            return 0;
        }
    }
    return 1;
}

void solve_n_queens(int row)
{
    // Caso base: Si todas las damas fueron colocadas
    if (row == N_QUEENS)
    {
        print_queens_solution();
        return;
    }

    // Intentar cada columna
    for (int col = 0; col < N_QUEENS; col++)
    {
        if (is_safe_queens(row, col))
        {
            // Elegir: Colocar la dama
            board_queens[row] = col;

            // Explorar: Pasar a la siguiente fila
            solve_n_queens(row + 1);
        }
    }
}

void n_queens_main()
{
    // Inicializar el arreglo de columnas de forma segura (indicando que no hay dama en esa fila)
    for (int i = 0; i < N_QUEENS; i++)
    {
        board_queens[i] = -1;
    }
    solution_count = 0; // Resetear el contador antes de buscar nuevas soluciones

    printf("\nIniciando busqueda de soluciones para el Problema de las %d Damas...\n", N_QUEENS);

    solve_n_queens(0);

    if (solution_count == 0)
    {
        printf("No se encontraron soluciones.\n");
    }
    else
    {
        printf("\nBusqueda finalizada. Total de soluciones encontradas: %d\n", solution_count);
    }
}