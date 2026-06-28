#ifndef CAMINOS_MINIMOS_H
#define CAMINOS_MINIMOS_H

#include "grafo.h"

/*
 * El grafo del Ejercicio 2 NO es completo (las zonas solo se conectan
 * por unos pocos enlaces inter-zona), por lo que para resolver el TSP
 * se necesita la distancia MAS CORTA entre cada par de ubicaciones
 * (pudiendo pasar por nodos intermedios). Floyd-Warshall calcula esa
 * matriz completa de distancias antes de aplicar GRASP.
 */
typedef struct {
    int n;
    double distancia[MAX_NODOS][MAX_NODOS]; /* distancia minima entre cada par */
    int siguiente[MAX_NODOS][MAX_NODOS];     /* siguiente nodo en el camino, -1 si no hay */
} CaminosMinimos;

void floyd_warshall(const Grafo *g, CaminosMinimos *cm);

/* Reconstruye el camino real (con nodos intermedios) entre origen y destino.
 * Escribe los nodos en camino_salida y retorna la cantidad de nodos escritos. */
int cm_reconstruir_camino(const CaminosMinimos *cm, int origen, int destino, int *camino_salida);

#endif
