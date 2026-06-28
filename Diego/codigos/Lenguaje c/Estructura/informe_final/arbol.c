#include "arbol.h"

void cd_inicializar(ConjuntosDisjuntos *cd, int n) {
    cd->n = n;
    for (int i = 0; i < n; i++) {
        cd->padre[i] = i;   /* cada nodo es raiz de su propio arbol */
        cd->rango[i] = 0;
    }
}

int cd_encontrar(ConjuntosDisjuntos *cd, int x) {
    if (cd->padre[x] != x) {
        cd->padre[x] = cd_encontrar(cd, cd->padre[x]); /* recursividad + compresion de camino */
    }
    return cd->padre[x];
}

void cd_unir(ConjuntosDisjuntos *cd, int x, int y) {
    int raiz_x = cd_encontrar(cd, x);
    int raiz_y = cd_encontrar(cd, y);
    if (raiz_x == raiz_y) return;

    /* union por rango: el arbol mas "bajo" cuelga del mas "alto" */
    if (cd->rango[raiz_x] < cd->rango[raiz_y]) {
        cd->padre[raiz_x] = raiz_y;
    } else if (cd->rango[raiz_x] > cd->rango[raiz_y]) {
        cd->padre[raiz_y] = raiz_x;
    } else {
        cd->padre[raiz_y] = raiz_x;
        cd->rango[raiz_x]++;
    }
}

int cd_mismo_conjunto(ConjuntosDisjuntos *cd, int x, int y) {
    return cd_encontrar(cd, x) == cd_encontrar(cd, y);
}
