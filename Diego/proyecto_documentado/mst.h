/* Algoritmos de Arbol de Expansion Minima: Prim, Kruskal y Boruvka. */

#ifndef MST_H
#define MST_H

#include <stdio.h>
#include "grafo.h"

/* Representa una arista del arbol de expansion: el par de nodos que
 * conecta y el peso (distancia) asociado. */
typedef struct {
    int origen;
    int destino;
    double peso;
} Arista;

/* Representa un arbol de expansion: el arreglo de aristas que lo forman,
 * la cantidad de aristas usadas y la suma de sus pesos. */
typedef struct {
    Arista aristas[MAX_NODOS];
    int num_aristas;
    double peso_total;
} ArbolExpansion;

/* MST mediante Prim, usando MinHeap, partiendo de nodo_inicial. */
ArbolExpansion mst_prim(const Grafo *g, int nodo_inicial);

/* MST mediante Kruskal, ordenando aristas y usando conjuntos disjuntos. */
ArbolExpansion mst_kruskal(const Grafo *g);

/* MST mediante Boruvka, por rondas de fusion de componentes. */
ArbolExpansion mst_boruvka(const Grafo *g);

/* Imprime las aristas del arbol y su peso total. */
void mst_imprimir(const ArbolExpansion *arbol, const Grafo *g,
                   const char *nombre_algoritmo, FILE *archivo_salida);

/* Compara el peso total de tres arboles de expansion. */
void mst_comparar3(const ArbolExpansion *prim, const ArbolExpansion *kruskal,
                    const ArbolExpansion *boruvka, FILE *archivo_salida);

#endif /* MST_H */
