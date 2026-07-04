/* Implementacion de Floyd-Warshall. */

#include "caminos_minimos.h"
#include <math.h>

/* Calcula los caminos minimos entre todos los pares de nodos del grafo g
   usando el algoritmo de Floyd-Warshall. Los resultados se almacenan en cm. */
void floyd_warshall(const Grafo *g, CaminosMinimos *cm) {
    int i, j, k;

    cm->n = g->num_nodos;

    /* Inicializa las matrices de distancia y siguiente. */
    for (i = 0; i < cm->n; i++) {
        for (j = 0; j < cm->n; j++) {
            /* Si i y j son el mismo nodo, la distancia es 0 y no hay siguiente. */
            if (i == j) {
                cm->distancia[i][j] = 0.0;
                cm->siguiente[i][j] = -1;
                /* Si hay una arista de i a j, la distancia es el peso de la arista y el siguiente es j. */
            } else if (grafo_existe_arista(g, i, j)) {
                cm->distancia[i][j] = grafo_obtener_peso(g, i, j);
                cm->siguiente[i][j] = j;
                /* Si no hay arista, la distancia es infinita y no hay siguiente. */
            } else {
                cm->distancia[i][j] = INFINITY;
                cm->siguiente[i][j] = -1;
            }
        }
    }

    /* Triple bucle: se intenta mejorar cada par (i,j) pasando
       por k. El orden con k mas externo es esencial para la correctitud. */
    for (k = 0; k < cm->n; k++) {
        for (i = 0; i < cm->n; i++) {
            /* Si la distancia de i a k es infinita, no hay camino a través de k. */
            if (cm->distancia[i][k] == INFINITY) {
                continue;
            }
            /* Si la distancia de k a j es infinita, no hay camino a través de k. */
            for (j = 0; j < cm->n; j++) {
                double distancia_via_k;

                if (cm->distancia[k][j] == INFINITY) {
                    continue;
                }

                distancia_via_k = cm->distancia[i][k] + cm->distancia[k][j];

                /* Si encontramos un camino más corto de i a j pasando por k, actualizamos la distancia y el siguiente nodo. */
                if (distancia_via_k < cm->distancia[i][j]) {
                    cm->distancia[i][j] = distancia_via_k;
                    cm->siguiente[i][j] = cm->siguiente[i][k];
                }
            }
        }
    }
}

/* Reconstruye el camino mínimo desde origen hasta destino usando la matriz siguiente
   generada por Floyd-Warshall. El camino se almacena en camino_salida y la función
   retorna la cantidad de nodos en el camino. Si no hay camino, retorna 0. */
int cm_reconstruir_camino(const CaminosMinimos *cm, int origen, int destino,
                           int *camino_salida) {
    int actual = origen;
    int cantidad = 0;

    /* Si el origen y destino son distintos y la distancia es infinita, no hay camino. */
    if (origen != destino && cm->distancia[origen][destino] == INFINITY) {
        return 0;
    }

    camino_salida[cantidad] = actual;
    cantidad++;

    /* Mientras no hayamos llegado al destino, seguimos el camino usando la matriz siguiente. */
    while (actual != destino) {
        actual = cm->siguiente[actual][destino];
        if (actual == -1) {
            return 0;
        }
        camino_salida[cantidad] = actual;
        cantidad++;
    }

    return cantidad;
}
