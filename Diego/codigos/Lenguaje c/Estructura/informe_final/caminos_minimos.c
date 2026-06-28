#include <math.h>
#include "caminos_minimos.h"

void floyd_warshall(const Grafo *g, CaminosMinimos *cm) {
    int n = g->num_nodos;
    cm->n = n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                cm->distancia[i][j] = 0.0;
                cm->siguiente[i][j] = -1;
            } else if (grafo_existe_arista(g, i, j)) {
                cm->distancia[i][j] = grafo_obtener_peso(g, i, j);
                cm->siguiente[i][j] = j;
            } else {
                cm->distancia[i][j] = INFINITY;
                cm->siguiente[i][j] = -1;
            }
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (cm->distancia[i][k] + cm->distancia[k][j] < cm->distancia[i][j]) {
                    cm->distancia[i][j] = cm->distancia[i][k] + cm->distancia[k][j];
                    cm->siguiente[i][j] = cm->siguiente[i][k];
                }
            }
        }
    }
}

int cm_reconstruir_camino(const CaminosMinimos *cm, int origen, int destino, int *camino_salida) {
    if (origen != destino && cm->siguiente[origen][destino] == -1) return 0;
    int actual = origen;
    int idx = 0;
    camino_salida[idx++] = actual;
    while (actual != destino) {
        actual = cm->siguiente[actual][destino];
        camino_salida[idx++] = actual;
    }
    return idx;
}
