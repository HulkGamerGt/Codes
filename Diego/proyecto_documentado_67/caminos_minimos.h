/* Algoritmo de Floyd-Warshall: caminos minimos entre todos los pares de nodos. */

#ifndef CAMINOS_MINIMOS_H
#define CAMINOS_MINIMOS_H

#include "grafo.h"

/* Estructura que representa los caminos minimos entre todos los pares de nodos. */
typedef struct {
    int n;
    double distancia[MAX_NODOS][MAX_NODOS];
    int siguiente[MAX_NODOS][MAX_NODOS];
} CaminosMinimos;

/* Calcula la distancia minima entre cada par de nodos del grafo. */
void floyd_warshall(const Grafo *g, CaminosMinimos *cm);

/* Reconstruye el camino minimo entre origen y destino. Retorna la
 * cantidad de nodos en camino_salida, o 0 si no existe camino. */
int cm_reconstruir_camino(const CaminosMinimos *cm, int origen, int destino,
                           int *camino_salida);

#endif /* CAMINOS_MINIMOS_H */
