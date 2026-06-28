#include <stdio.h>
#include <stdlib.h>
#include "mst.h"
#include "arbol.h"
#include "arbol_binario.h"
#include "salida.h"

/* ============================ PRIM ============================
 * Usa el arbol binario (min-heap) como cola de prioridad.
 * Complejidad: O(n^2 log n) en esta implementacion basada en matriz.
 * ================================================================ */
ArbolExpansion mst_prim(const Grafo *g, int nodo_inicial) {
    ArbolExpansion resultado;
    resultado.num_aristas = 0;
    resultado.peso_total = 0.0;

    int n = g->num_nodos;
    int en_arbol[MAX_NODOS];
    double clave[MAX_NODOS];
    int padre[MAX_NODOS];
    for (int i = 0; i < n; i++) { en_arbol[i] = 0; clave[i] = 1e18; padre[i] = -1; }

    MinHeap heap;
    heap_inicializar(&heap);
    clave[nodo_inicial] = 0.0;
    for (int i = 0; i < n; i++) heap_insertar(&heap, i, clave[i]);

    while (!heap_vacio(&heap)) {
        ElementoHeap min = heap_extraer_min(&heap);
        int u = min.nodo;
        en_arbol[u] = 1;

        if (padre[u] != -1) {
            resultado.aristas[resultado.num_aristas].origen = padre[u];
            resultado.aristas[resultado.num_aristas].destino = u;
            resultado.aristas[resultado.num_aristas].peso = clave[u];
            resultado.peso_total += clave[u];
            resultado.num_aristas++;
        }

        for (int v = 0; v < n; v++) {
            if (!en_arbol[v] && grafo_existe_arista(g, u, v)) {
                double peso = grafo_obtener_peso(g, u, v);
                if (peso < clave[v]) {
                    clave[v] = peso;
                    padre[v] = u;
                    if (heap_contiene(&heap, v)) heap_disminuir_prioridad(&heap, v, peso);
                }
            }
        }
    }
    return resultado;
}

/* ============================ KRUSKAL ============================
 * Ordena todas las aristas y usa el TAD Arbol (conjuntos disjuntos)
 * para evitar ciclos.
 * ==================================================================== */
typedef struct { int u, v; double peso; } AristaTmp;

static int comparar_aristas(const void *a, const void *b) {
    const AristaTmp *e1 = (const AristaTmp *) a;
    const AristaTmp *e2 = (const AristaTmp *) b;
    if (e1->peso < e2->peso) return -1;
    if (e1->peso > e2->peso) return 1;
    return 0;
}

ArbolExpansion mst_kruskal(const Grafo *g) {
    ArbolExpansion resultado;
    resultado.num_aristas = 0;
    resultado.peso_total = 0.0;

    int n = g->num_nodos;
    AristaTmp *todas = malloc(sizeof(AristaTmp) * n * n);
    int total = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (grafo_existe_arista(g, i, j)) {
                todas[total].u = i;
                todas[total].v = j;
                todas[total].peso = grafo_obtener_peso(g, i, j);
                total++;
            }

    qsort(todas, total, sizeof(AristaTmp), comparar_aristas);

    ConjuntosDisjuntos cd;
    cd_inicializar(&cd, n);

    for (int i = 0; i < total && resultado.num_aristas < n - 1; i++) {
        int u = todas[i].u, v = todas[i].v;
        if (!cd_mismo_conjunto(&cd, u, v)) {
            cd_unir(&cd, u, v);
            resultado.aristas[resultado.num_aristas].origen = u;
            resultado.aristas[resultado.num_aristas].destino = v;
            resultado.aristas[resultado.num_aristas].peso = todas[i].peso;
            resultado.peso_total += todas[i].peso;
            resultado.num_aristas++;
        }
    }
    free(todas);
    return resultado;
}

/* ============================ BORUVKA ============================
 * Tercer metodo (a eleccion del enunciado). En cada ronda, cada
 * componente busca su arista mas barata hacia otra componente;
 * todas esas aristas se agregan simultaneamente. Usa el TAD Arbol
 * (conjuntos disjuntos) igual que Kruskal.
 * ==================================================================== */
ArbolExpansion mst_boruvka(const Grafo *g) {
    ArbolExpansion resultado;
    resultado.num_aristas = 0;
    resultado.peso_total = 0.0;

    int n = g->num_nodos;
    ConjuntosDisjuntos cd;
    cd_inicializar(&cd, n);

    int num_componentes = n;

    while (num_componentes > 1) {
        int mejor_origen[MAX_NODOS], mejor_destino[MAX_NODOS];
        double mejor_peso[MAX_NODOS];
        int tiene_mejor[MAX_NODOS];
        for (int i = 0; i < n; i++) tiene_mejor[i] = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j || !grafo_existe_arista(g, i, j)) continue;
                int ci = cd_encontrar(&cd, i);
                int cj = cd_encontrar(&cd, j);
                if (ci == cj) continue;
                double peso = grafo_obtener_peso(g, i, j);
                if (!tiene_mejor[ci] || peso < mejor_peso[ci]) {
                    tiene_mejor[ci] = 1;
                    mejor_peso[ci] = peso;
                    mejor_origen[ci] = i;
                    mejor_destino[ci] = j;
                }
            }
        }

        int agrego_alguna = 0;
        for (int c = 0; c < n; c++) {
            if (tiene_mejor[c]) {
                int ci = cd_encontrar(&cd, mejor_origen[c]);
                int cj = cd_encontrar(&cd, mejor_destino[c]);
                if (ci != cj) {
                    cd_unir(&cd, ci, cj);
                    resultado.aristas[resultado.num_aristas].origen = mejor_origen[c];
                    resultado.aristas[resultado.num_aristas].destino = mejor_destino[c];
                    resultado.aristas[resultado.num_aristas].peso = mejor_peso[c];
                    resultado.peso_total += mejor_peso[c];
                    resultado.num_aristas++;
                    num_componentes--;
                    agrego_alguna = 1;
                }
            }
        }
        if (!agrego_alguna) break; /* grafo desconectado: no se puede seguir uniendo */
    }
    return resultado;
}

/* ============================ UTILIDADES ============================ */
void mst_imprimir(const ArbolExpansion *arbol, const Grafo *g, const char *nombre_algoritmo, FILE *archivo_salida) {
    imprimir_doble(archivo_salida, "--- Arbol de Expansion Minima (%s) ---\n", nombre_algoritmo);
    for (int i = 0; i < arbol->num_aristas; i++) {
        int o = arbol->aristas[i].origen, d = arbol->aristas[i].destino;
        imprimir_doble(archivo_salida, "  %-30s -- %-30s : %.3f km\n", g->nodos[o].nombre, g->nodos[d].nombre, arbol->aristas[i].peso);
    }
    imprimir_doble(archivo_salida, "  Peso total: %.3f km  (%d aristas)\n", arbol->peso_total, arbol->num_aristas);
}

void mst_comparar3(const ArbolExpansion *prim, const ArbolExpansion *kruskal, const ArbolExpansion *boruvka, FILE *archivo_salida) {
    imprimir_doble(archivo_salida, "  Prim     : %.3f km\n", prim->peso_total);
    imprimir_doble(archivo_salida, "  Kruskal  : %.3f km\n", kruskal->peso_total);
    imprimir_doble(archivo_salida, "  Boruvka  : %.3f km\n", boruvka->peso_total);
    imprimir_doble(archivo_salida, "  (Para un MST correcto sobre un mismo grafo conexo, los tres pesos totales\n");
    imprimir_doble(archivo_salida, "   deben coincidir; diferencias minimas solo ocurren si existen aristas con\n");
    imprimir_doble(archivo_salida, "   pesos empatados y distintos criterios de desempate entre algoritmos.)\n");
}
