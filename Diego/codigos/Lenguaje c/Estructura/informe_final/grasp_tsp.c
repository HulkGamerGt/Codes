#include <stdio.h>
#include <stdlib.h>
#include "grasp_tsp.h"
#include "salida.h"

/* ---------- Fase de construccion voraz-aleatorizada (RCL) ---------- */
static void construir_grasp(const CaminosMinimos *cm, int n, int nodo_inicio,
                             double alpha, int *ruta_salida) {
    int visitado[MAX_NODOS] = {0};
    int actual = nodo_inicio;
    visitado[actual] = 1;
    ruta_salida[0] = actual;
    int contador = 1;

    while (contador < n) {
        int candidatos[MAX_NODOS];
        double distancias[MAX_NODOS];
        int num_cand = 0;
        double dmin = 1e18, dmax = -1e18;

        for (int j = 0; j < n; j++) {
            if (!visitado[j]) {
                double d = cm->distancia[actual][j];
                candidatos[num_cand] = j;
                distancias[num_cand] = d;
                if (d < dmin) dmin = d;
                if (d > dmax) dmax = d;
                num_cand++;
            }
        }

        /* Lista de Candidatos Restringida (RCL) */
        double umbral = dmin + alpha * (dmax - dmin);
        int rcl[MAX_NODOS];
        int num_rcl = 0;
        for (int k = 0; k < num_cand; k++) {
            if (distancias[k] <= umbral) rcl[num_rcl++] = candidatos[k];
        }

        int elegido = rcl[rand() % num_rcl]; /* seleccion aleatoria dentro de la RCL */
        visitado[elegido] = 1;
        ruta_salida[contador++] = elegido;
        actual = elegido;
    }
}

static double calcular_distancia_circuito(const CaminosMinimos *cm, const int *ruta, int n) {
    double total = 0.0;
    for (int i = 0; i < n - 1; i++) total += cm->distancia[ruta[i]][ruta[i + 1]];
    total += cm->distancia[ruta[n - 1]][ruta[0]]; /* cierre del circuito */
    return total;
}

/* ---------- Fase de busqueda local: mejora 2-opt ----------
 * El nodo en la posicion 0 (UCM) nunca se mueve, porque toda
 * inversion de segmento comienza en i+1 (i parte desde 0). */
static void busqueda_local_2opt(const CaminosMinimos *cm, int *ruta, int n) {
    int mejora = 1;
    while (mejora) {
        mejora = 0;
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                int a = ruta[i], b = ruta[(i + 1) % n];
                int c = ruta[j], d = ruta[(j + 1) % n];
                if (a == c || b == d) continue;

                double actual = cm->distancia[a][b] + cm->distancia[c][d];
                double nueva = cm->distancia[a][c] + cm->distancia[b][d];

                if (nueva < actual - 1e-9) {
                    int izq = i + 1, der = j;
                    while (izq < der) {
                        int tmp = ruta[izq];
                        ruta[izq] = ruta[der];
                        ruta[der] = tmp;
                        izq++;
                        der--;
                    }
                    mejora = 1;
                }
            }
        }
    }
}

Circuito grasp_tsp(const Grafo *g, const CaminosMinimos *cm, int nodo_inicio,
                    int num_iteraciones, double alpha) {
    int n = g->num_nodos;
    Circuito mejor;
    mejor.distancia_total = 1e18;
    mejor.num_nodos = n;

    for (int it = 0; it < num_iteraciones; it++) {
        int ruta[MAX_RUTA];
        construir_grasp(cm, n, nodo_inicio, alpha, ruta);
        busqueda_local_2opt(cm, ruta, n);
        double dist = calcular_distancia_circuito(cm, ruta, n);
        if (dist < mejor.distancia_total) {
            mejor.distancia_total = dist;
            for (int i = 0; i < n; i++) mejor.ruta[i] = ruta[i];
        }
    }
    return mejor;
}

void grasp_imprimir_circuito(const Circuito *c, const Grafo *g, FILE *archivo_salida) {
    imprimir_doble(archivo_salida, "Orden de visita:\n");
    for (int i = 0; i < c->num_nodos; i++) {
        imprimir_doble(archivo_salida, "  %2d. %s\n", i + 1, g->nodos[c->ruta[i]].nombre);
    }
    imprimir_doble(archivo_salida, "  %2d. %s (retorno)\n", c->num_nodos + 1, g->nodos[c->ruta[0]].nombre);
    imprimir_doble(archivo_salida, "Distancia total del circuito: %.3f km\n", c->distancia_total);
}
