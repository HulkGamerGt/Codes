#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Para sleep (pausa visual)

typedef struct Nodo {
    int valor;
    struct Nodo* sig;
} Nodo;

// Declaración adelantada de imprimirEstadoMemoria para que imprimir pueda usarla
void imprimirEstadoMemoria(Nodo* matriz[5][5], int colBorrada);

void imprimir(Nodo* matriz[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matriz[i][j] != NULL) {
                printf("[%p] ", (void*)matriz[i][j]); // %p imprime punteros
            } else {
                printf("[ LIBRE ] ");
            }
        }
        printf("\n");
    }
}

void imprimirEstadoMemoria(Nodo* matriz[5][5], int colBorrada) {
    system("clear || cls");
    printf("=== ESTADO DE LA MEMORIA RAM (Simulado) ===\n\n");
    
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (j == colBorrada) {
                printf("[ LIBRE ] "); // Representa memoria devuelta con free()
            } else if (matriz[i][j] != NULL) {
                // Simulamos una dirección de memoria hexadecimal
                printf("[%p] ", (void*)matriz[i][j]);
            } else {
                printf("[ ERROR ] "); // No debería ocurrir, pero por seguridad
            }
        }
        printf("\n");
    }
    printf("\n==========================================\n");
}

int main() {
    // Declarar la matriz como un arreglo de punteros 5x5
    Nodo* matriz[5][5];

    // Simulamos la creación de nodos en el Heap
    printf("Asignando memoria para 25 nodos...\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            matriz[i][j] = (Nodo*)malloc(sizeof(Nodo));
            if (matriz[i][j] == NULL) {
                printf("Error: No se pudo asignar memoria\n");
                // Liberar lo ya asignado
                for (int x = 0; x <= i; x++) {
                    for (int y = 0; y < (x == i ? j : 5); y++) {
                        free(matriz[x][y]);
                    }
                }
                return 1;
            }
            // Inicializar el nodo
            matriz[i][j]->valor = i * 5 + j; // Valor identificativo
            matriz[i][j]->sig = NULL;
        }
    }

    printf("\nEstado inicial de la memoria:\n");
    imprimirEstadoMemoria(matriz, -1);
    printf("\nTodos los nodos ocupan un lugar en la RAM.\n");
    printf("Presiona ENTER para ejecutar free() en la Columna 5...");
    getchar();

    // Simulamos la liberación
    printf("\nLiberando la columna 4 (índices)...\n");
    for (int i = 0; i < 5; i++) {
        free(matriz[i][4]); 
        matriz[i][4] = NULL; // Buena práctica: poner a NULL tras liberar
    }

    imprimirEstadoMemoria(matriz, 4);
    printf("\n¡Memoria liberada! Los bloques [ LIBRE ] ahora pueden ser\n");
    printf("usados para otras variables o procesos.\n");

    printf("\nPresiona ENTER para liberar toda la memoria restante...");
    getchar();

    // Liberar memoria restante (buena práctica)
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matriz[i][j] != NULL) {
                free(matriz[i][j]);
                matriz[i][j] = NULL;
            }
        }
    }
    
    printf("Toda la memoria ha sido liberada. Programa finalizado.\n");
    return 0;
}