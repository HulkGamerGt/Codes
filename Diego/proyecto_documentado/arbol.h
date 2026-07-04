/* TAD Conjuntos Disjuntos (Union-Find), con union por rango y compresion
 * de camino. Se usa en Kruskal y Boruvka para detectar ciclos. */

#ifndef ARBOL_H
#define ARBOL_H

#define MAX_ELEMENTOS 100

/* Estructura que representa un conjunto disjunto. */
typedef struct {
    int padre[MAX_ELEMENTOS];
    int rango[MAX_ELEMENTOS];
    int n;
} ConjuntosDisjuntos;

/* Inicializa n conjuntos, cada uno con un solo elemento. */
void cd_inicializar(ConjuntosDisjuntos *cd, int n);

/* Retorna la raiz (representante) del conjunto de x, comprimiendo camino. */
int cd_encontrar(ConjuntosDisjuntos *cd, int x);

/* Une los conjuntos de x e y usando union por rango. */
void cd_unir(ConjuntosDisjuntos *cd, int x, int y);

/* Indica si x e y pertenecen al mismo conjunto. */
int cd_mismo_conjunto(ConjuntosDisjuntos *cd, int x, int y);

#endif /* ARBOL_H */
