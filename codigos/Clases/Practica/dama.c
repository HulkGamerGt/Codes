#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Necesario para la funcion abs()

#define N_QUEENS 8 // Tamano clasico: 8x8
int board_queens[N_QUEENS];
int solution_count = 0;

void print_queens_solution() {
    solution_count++;
    printf("\n--- Solucion #%d ---\n", solution_count);
    
    for (int i = 0; i < N_QUEENS; i++) {
        for (int j = 0; j < N_QUEENS; j++) {
            if (board_queens[i] == j) {
                printf(" Q ");
            } else {
                printf(" - ");
            }
        }
        printf("\n");
    }
}

int is_safe_queens(int row, int col) {
    for (int i = 0; i < row; i++) {
        // 1. Verificacion de Columna (Vertical)
        if (board_queens[i] == col) {
            return 0;
        }

        // 2. Verificacion de Diagonales: Si las diferencias son iguales, estan en diagonal
        if (abs(board_queens[i] - col) == abs(i - row)) {
            return 0;
        }
    }
    return 1;
}

void solve_n_queens(int row) {
    // Caso base: Si todas las damas fueron colocadas
    if (row == N_QUEENS) {
        print_queens_solution();
        return; 
    }

    // Intentar cada columna
    for (int col = 0; col < N_QUEENS; col++) {
        if (is_safe_queens(row, col)) {
            // Elegir: Colocar la dama
            board_queens[row] = col;

            // Explorar: Pasar a la siguiente fila
            solve_n_queens(row + 1);

            // No es estrictamente necesaria la "Vuelta Atrás" si la proxima iteracion
            // sobrescribe board_queens[row], pero se puede añadir si fuera necesario:
            // board_queens[row] = -1;
        }
    }
}

void n_queens_main() {
    // Inicializar el arreglo de columnas de forma segura (indicando que no hay dama en esa fila)
    for (int i = 0; i < N_QUEENS; i++) {
        board_queens[i] = -1; 
    }

    printf("\nIniciando busqueda de soluciones para el Problema de las %d Damas...\n", N_QUEENS);
    
    solve_n_queens(0);

    if (solution_count == 0) {
        printf("No se encontraron soluciones.\n");
    } else {
        printf("\nBusqueda finalizada. Total de soluciones encontradas: %d\n", solution_count);
    }
}