/* Implementacion del TAD Conjuntos Disjuntos (Union-Find). */

#include "arbol.h"

/* Cada elemento comienza siendo su propia raiz, con rango 0. */
void cd_inicializar(ConjuntosDisjuntos *cd, int n) {
    int i;

    cd->n = n;
    for (i = 0; i < n; i++) {
        cd->padre[i] = i;
        cd->rango[i] = 0;
    }
}

/* Busqueda recursiva de la raiz, comprimiendo el camino al volver:
  cada nodo visitado queda apuntando directo a la raiz encontrada. */
int cd_encontrar(ConjuntosDisjuntos *cd, int x) {
    if (cd->padre[x] == x) {
        return x;
    }
    cd->padre[x] = cd_encontrar(cd, cd->padre[x]);
    return cd->padre[x];
}

/* Une por rango: la raiz de menor rango cuelga bajo la de mayor rango. */
void cd_unir(ConjuntosDisjuntos *cd, int x, int y) {
    int raiz_x = cd_encontrar(cd, x);
    int raiz_y = cd_encontrar(cd, y);

    if (raiz_x == raiz_y) {
        return;
    }

    /* Une por rango: la raiz de menor rango cuelga bajo la de mayor rango. */
    if (cd->rango[raiz_x] < cd->rango[raiz_y]) {
        cd->padre[raiz_x] = raiz_y;
    } else if (cd->rango[raiz_x] > cd->rango[raiz_y]) {
        cd->padre[raiz_y] = raiz_x;
    } else {
        /* Mismo rango: se elige raiz_x y su rango aumenta en 1. */
        cd->padre[raiz_y] = raiz_x;
        cd->rango[raiz_x]++;
    }
}

int cd_mismo_conjunto(ConjuntosDisjuntos *cd, int x, int y) {
    return cd_encontrar(cd, x) == cd_encontrar(cd, y);
}
