#ifndef ARBOL_H
#define ARBOL_H

#define MAX_ELEMENTOS 100

/*
 * TAD Arbol (bosque de arboles) representado en memoria mediante un
 * arreglo de punteros a padre ("representacion de arboles en memoria").
 * Cada elemento es la raiz de su propio arbol al inicio; al unir dos
 * conjuntos, un arbol pasa a ser subarbol del otro. Se usa para
 * detectar ciclos en tiempo casi-constante dentro de Kruskal y Boruvka.
 */
typedef struct {
    int padre[MAX_ELEMENTOS];
    int rango[MAX_ELEMENTOS];
    int n;
} ConjuntosDisjuntos;

void cd_inicializar(ConjuntosDisjuntos *cd, int n);
int  cd_encontrar(ConjuntosDisjuntos *cd, int x);      /* recursivo, con compresion de camino */
void cd_unir(ConjuntosDisjuntos *cd, int x, int y);     /* union por rango */
int  cd_mismo_conjunto(ConjuntosDisjuntos *cd, int x, int y);

#endif
