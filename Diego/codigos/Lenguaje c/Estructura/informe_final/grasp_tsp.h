#ifndef GRASP_TSP_H
#define GRASP_TSP_H

#include "grafo.h"
#include "caminos_minimos.h"

#define MAX_RUTA 100

typedef struct {
    int ruta[MAX_RUTA];   /* orden de visita de los nodos (indices del grafo) */
    int num_nodos;
    double distancia_total;
} Circuito;

/*
 * GRASP (Procedimiento de Busqueda Voraz Adaptativo Aleatorizado):
 *  - Fase de construccion: voraz-aleatorizada usando una Lista de
 *    Candidatos Restringida (RCL) controlada por 'alpha'
 *    (alpha=0 -> 100% voraz, alpha=1 -> 100% aleatorio).
 *  - Fase de busqueda local: mejora 2-opt sobre el circuito construido.
 *  - Se repite 'num_iteraciones' veces y se retorna el mejor circuito.
 *
 * 'cm' debe contener las distancias minimas entre TODO par de nodos
 * (calculadas previamente con floyd_warshall), ya que el grafo de
 * zonas no es necesariamente completo.
 */
Circuito grasp_tsp(const Grafo *g, const CaminosMinimos *cm, int nodo_inicio,
                    int num_iteraciones, double alpha);

void grasp_imprimir_circuito(const Circuito *c, const Grafo *g, FILE *archivo_salida);

#endif
