#ifndef MST_H
#define MST_H

#include "grafo.h"

typedef struct {
    int origen;
    int destino;
    double peso;
} Arista;

/* Arbol de expansion (resultado de cualquiera de los 3 algoritmos) */
typedef struct {
    Arista aristas[MAX_NODOS];
    int num_aristas;
    double peso_total;
} ArbolExpansion;

ArbolExpansion mst_prim(const Grafo *g, int nodo_inicial);
ArbolExpansion mst_kruskal(const Grafo *g);
ArbolExpansion mst_boruvka(const Grafo *g);

void mst_imprimir(const ArbolExpansion *arbol, const Grafo *g, const char *nombre_algoritmo, FILE *archivo_salida);
void mst_comparar3(const ArbolExpansion *prim, const ArbolExpansion *kruskal, const ArbolExpansion *boruvka, FILE *archivo_salida);

#endif
