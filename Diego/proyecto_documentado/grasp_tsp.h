/* GRASP para el TSP: construccion voraz aleatorizada (RCL) + busqueda
 * local 2-opt. El parametro alpha controla cuanta aleatoriedad se admite
 * en la construccion (0 = voraz puro, 1 = aleatorio puro). */

#ifndef GRASP_TSP_H
#define GRASP_TSP_H

#include <stdio.h>
#include "grafo.h"
#include "caminos_minimos.h"

#define MAX_RUTA 100

/* Representa un circuito (recorrido) del TSP: la secuencia de nodos
 * visitados, la cantidad de nodos en la ruta, y la distancia total del
 * circuito (incluyendo el regreso del ultimo nodo al primero). */
typedef struct {
    int ruta[MAX_RUTA];
    int num_nodos;
    double distancia_total;
} Circuito;

/* Ejecuta num_iteraciones de GRASP y retorna el mejor circuito encontrado.
 * El circuito siempre inicia y termina en nodo_inicio. */
Circuito grasp_tsp(const Grafo *g, const CaminosMinimos *cm, int nodo_inicio,
                    int num_iteraciones, double alpha);

/* Imprime la secuencia de nodos del circuito y su distancia total. */
void grasp_imprimir_circuito(const Circuito *c, const Grafo *g,
                              FILE *archivo_salida);

#endif /* GRASP_TSP_H */
