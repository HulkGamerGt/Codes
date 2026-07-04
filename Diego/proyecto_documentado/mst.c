/* Implementacion de Prim, Kruskal y Boruvka para el MST. */

#include "mst.h"
#include "arbol.h"
#include "arbol_binario.h"
#include "salida.h"
#include <stdlib.h>
#include <string.h>

/* Prim: crece un unico arbol agregando, en cada paso, la arista mas
 * barata que conecta el arbol actual con un nodo todavia no incluido. */
ArbolExpansion mst_prim(const Grafo *g, int nodo_inicial) {
    ArbolExpansion resultado;
    MinHeap heap;
    double clave[MAX_NODOS];
    int padre_en_arbol[MAX_NODOS];
    int en_arbol[MAX_NODOS];
    int i;

    resultado.num_aristas = 0;
    resultado.peso_total = 0.0;
    heap_inicializar(&heap);

    for (i = 0; i < g->num_nodos; i++) {
        clave[i] = 1e18;
        padre_en_arbol[i] = -1;
        en_arbol[i] = 0;
    }
    clave[nodo_inicial] = 0.0;

    for (i = 0; i < g->num_nodos; i++) {
        heap_insertar(&heap, i, clave[i]);
    }

    while (!heap_vacio(&heap)) {
        ElementoHeap extraido = heap_extraer_min(&heap);
        int u = extraido.nodo;
        int v;

        en_arbol[u] = 1;

        if (padre_en_arbol[u] != -1) {
            resultado.aristas[resultado.num_aristas].origen = padre_en_arbol[u];
            resultado.aristas[resultado.num_aristas].destino = u;
            resultado.aristas[resultado.num_aristas].peso = clave[u];
            resultado.num_aristas++;
            resultado.peso_total += clave[u];
        }

        for (v = 0; v < g->num_nodos; v++) {
            if (grafo_existe_arista(g, u, v) && !en_arbol[v]) {
                double peso_uv = grafo_obtener_peso(g, u, v);

                if (peso_uv < clave[v]) {
                    clave[v] = peso_uv;
                    padre_en_arbol[v] = u;
                    heap_disminuir_prioridad(&heap, v, peso_uv);
                }
            }
        }
    }

    return resultado;
}

/* Funcion de comparacion para qsort: ordena aristas de forma ascendente
 * segun su peso. Es la base del paso "ordenar aristas" de Kruskal. */
static int comparar_aristas(const void *a, const void *b) {
    const Arista *arista_a = (const Arista *)a;
    const Arista *arista_b = (const Arista *)b;

    if (arista_a->peso < arista_b->peso) return -1;
    if (arista_a->peso > arista_b->peso) return 1;
    return 0;
}

/* Kruskal: ordena todas las aristas por peso y las agrega de menor a
 * mayor, descartando las que formarian un ciclo (mismo conjunto disjunto). */
ArbolExpansion mst_kruskal(const Grafo *g) {
    ArbolExpansion resultado;
    Arista todas_las_aristas[MAX_NODOS * MAX_NODOS];
    int total_aristas = 0;
    ConjuntosDisjuntos cd;
    int i, j;

    resultado.num_aristas = 0;
    resultado.peso_total = 0.0;

    for (i = 0; i < g->num_nodos; i++) {
        for (j = i + 1; j < g->num_nodos; j++) {
            if (grafo_existe_arista(g, i, j)) {
                todas_las_aristas[total_aristas].origen = i;
                todas_las_aristas[total_aristas].destino = j;
                todas_las_aristas[total_aristas].peso = grafo_obtener_peso(g, i, j);
                total_aristas++;
            }
        }
    }

    qsort(todas_las_aristas, (size_t)total_aristas, sizeof(Arista), comparar_aristas);
    cd_inicializar(&cd, g->num_nodos);

    for (i = 0; i < total_aristas && resultado.num_aristas < g->num_nodos - 1; i++) {
        int origen = todas_las_aristas[i].origen;
        int destino = todas_las_aristas[i].destino;

        if (!cd_mismo_conjunto(&cd, origen, destino)) {
            resultado.aristas[resultado.num_aristas] = todas_las_aristas[i];
            resultado.num_aristas++;
            resultado.peso_total += todas_las_aristas[i].peso;
            cd_unir(&cd, origen, destino);
        }
    }

    return resultado;
}

/* Boruvka: por rondas, cada componente busca su arista mas barata hacia
 * otro componente; todas las ganadoras se agregan al mismo tiempo. */
ArbolExpansion mst_boruvka(const Grafo *g) {
    ArbolExpansion resultado;
    ConjuntosDisjuntos cd;
    int mejor_destino[MAX_NODOS];
    double mejor_peso[MAX_NODOS];
    int componentes_restantes;
    int i, j;

    resultado.num_aristas = 0;
    resultado.peso_total = 0.0;

    cd_inicializar(&cd, g->num_nodos);
    componentes_restantes = g->num_nodos;

    while (componentes_restantes > 1 && resultado.num_aristas < g->num_nodos - 1) {
        for (i = 0; i < g->num_nodos; i++) {
            mejor_destino[i] = -1;
            mejor_peso[i] = 1e18;
        }

        /* Para cada componente (indexado por su raiz) se busca la arista
         * mas barata que lo conecte con un componente distinto. */
        for (i = 0; i < g->num_nodos; i++) {
            for (j = i + 1; j < g->num_nodos; j++) {
                if (!grafo_existe_arista(g, i, j)) {
                    continue;
                }

                {
                    int raiz_i = cd_encontrar(&cd, i);
                    int raiz_j = cd_encontrar(&cd, j);
                    double peso_ij = grafo_obtener_peso(g, i, j);

                    if (raiz_i == raiz_j) {
                        continue;
                    }
                    if (peso_ij < mejor_peso[raiz_i]) {
                        mejor_peso[raiz_i] = peso_ij;
                        mejor_destino[raiz_i] = j;
                    }
                    if (peso_ij < mejor_peso[raiz_j]) {
                        mejor_peso[raiz_j] = peso_ij;
                        mejor_destino[raiz_j] = i;
                    }
                }
            }
        }

        for (i = 0; i < g->num_nodos; i++) {
            int raiz_i = cd_encontrar(&cd, i);

            if (raiz_i == i && mejor_destino[i] != -1) {
                int destino = mejor_destino[i];
                int raiz_destino = cd_encontrar(&cd, destino);

                if (raiz_i != raiz_destino) {
                    resultado.aristas[resultado.num_aristas].origen = i;
                    resultado.aristas[resultado.num_aristas].destino = destino;
                    resultado.aristas[resultado.num_aristas].peso = mejor_peso[i];
                    resultado.num_aristas++;
                    resultado.peso_total += mejor_peso[i];

                    cd_unir(&cd, i, destino);
                    componentes_restantes--;
                }
            }
        }
    }

    return resultado;
}

/* Imprime cada arista del arbol (nodos origen y destino, con su peso),
 * junto con el numero total de aristas y el peso total del arbol. */
void mst_imprimir(const ArbolExpansion *arbol, const Grafo *g,
                   const char *nombre_algoritmo, FILE *archivo_salida) {
    char buffer[256];
    int i;

    snprintf(buffer, sizeof(buffer), "\n--- Arbol de Expansion Minima (%s) ---\n",
              nombre_algoritmo);
    imprimir_doble(archivo_salida, buffer);

    for (i = 0; i < arbol->num_aristas; i++) {
        int origen = arbol->aristas[i].origen;
        int destino = arbol->aristas[i].destino;

        snprintf(buffer, sizeof(buffer), "  %-30s -- %-30s  peso=%.4f km\n",
                  g->nodos[origen].nombre, g->nodos[destino].nombre,
                  arbol->aristas[i].peso);
        imprimir_doble(archivo_salida, buffer);
    }

    snprintf(buffer, sizeof(buffer), "Numero de aristas: %d\n", arbol->num_aristas);
    imprimir_doble(archivo_salida, buffer);

    snprintf(buffer, sizeof(buffer), "Peso total del MST (%s): %.4f km\n",
              nombre_algoritmo, arbol->peso_total);
    imprimir_doble(archivo_salida, buffer);
}

/* Compara el peso total de tres arboles de expansion (tipicamente el
 * resultado de Prim, Kruskal y Boruvka sobre el mismo grafo) e imprime
 * la diferencia maxima entre ellos, util para verificar que los tres
 * algoritmos convergen al mismo costo minimo. */
void mst_comparar3(const ArbolExpansion *prim, const ArbolExpansion *kruskal,
                    const ArbolExpansion *boruvka, FILE *archivo_salida) {
    char buffer[256];
    double maximo, minimo, diferencia;

    imprimir_doble(archivo_salida, "\n--- Comparacion de pesos totales (Prim vs Kruskal vs Boruvka) ---\n");

    snprintf(buffer, sizeof(buffer), "  Prim:    %.4f km\n", prim->peso_total);
    imprimir_doble(archivo_salida, buffer);
    snprintf(buffer, sizeof(buffer), "  Kruskal: %.4f km\n", kruskal->peso_total);
    imprimir_doble(archivo_salida, buffer);
    snprintf(buffer, sizeof(buffer), "  Boruvka: %.4f km\n", boruvka->peso_total);
    imprimir_doble(archivo_salida, buffer);

    maximo = prim->peso_total;
    if (kruskal->peso_total > maximo) maximo = kruskal->peso_total;
    if (boruvka->peso_total > maximo) maximo = boruvka->peso_total;

    minimo = prim->peso_total;
    if (kruskal->peso_total < minimo) minimo = kruskal->peso_total;
    if (boruvka->peso_total < minimo) minimo = boruvka->peso_total;

    diferencia = maximo - minimo;

    snprintf(buffer, sizeof(buffer), "  Diferencia maxima entre algoritmos: %.6f km\n", diferencia);
    imprimir_doble(archivo_salida, buffer);
}
