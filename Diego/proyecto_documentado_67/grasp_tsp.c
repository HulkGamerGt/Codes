/* Implementacion de GRASP (construccion con RCL + busqueda local 2-opt). */

#include "grasp_tsp.h"
#include "salida.h"
#include <stdlib.h>
#include <string.h>

/* Distancia total del circuito, incluyendo el regreso al nodo inicial. */

/* Calcula la distancia total de un circuito: la suma de las distancias
   entre nodos consecutivos de la ruta, mas la distancia de regreso del
   ultimo nodo al primero (el circuito es cerrado). */
static double calcular_distancia_circuito(const Circuito *c, const CaminosMinimos *cm) {
    double total = 0.0;
    int i;

    for (i = 0; i < c->num_nodos - 1; i++) {
        total += cm->distancia[c->ruta[i]][c->ruta[i + 1]];
    }
    total += cm->distancia[c->ruta[c->num_nodos - 1]][c->ruta[0]];

    return total;
}

/* Fase de construccion: en cada paso se forma una Lista de Candidatos
   Restringida (RCL) con los nodos no visitados cuya distancia al ultimo
   nodo no supera un umbral entre el minimo y el maximo, segun alpha.
   Luego se elige uno de la RCL al azar. */
static void construir_grasp(const Grafo *g, const CaminosMinimos *cm,
                             int nodo_inicio, double alpha, Circuito *c) {
    int visitado[MAX_NODOS];
    int candidatos_rcl[MAX_NODOS];
    int cantidad_rcl;
    int i;

    for (i = 0; i < g->num_nodos; i++) {
        visitado[i] = 0;
    }

    c->num_nodos = 0;
    c->ruta[c->num_nodos] = nodo_inicio;
    c->num_nodos++;
    visitado[nodo_inicio] = 1;

    /* Se agregan nodos a la ruta hasta que se visiten todos. */
    while (c->num_nodos < g->num_nodos) {
        int actual = c->ruta[c->num_nodos - 1];
        double minima = 1e18;
        double maxima = -1e18;
        double umbral;
        int seleccionado;

        for (i = 0; i < g->num_nodos; i++) {
            if (!visitado[i]) {
                double distancia_actual = cm->distancia[actual][i];

                if (distancia_actual < minima) minima = distancia_actual;
                if (distancia_actual > maxima) maxima = distancia_actual;
            }
        }

        /* Se agrega una tolerancia del 1% para que nodos practicamente
           empatados en distancia minima tambien entren a la RCL, incluso
           con alpha = 0. */
        umbral = minima + alpha * (maxima - minima) + 0.01 * minima;

        cantidad_rcl = 0;
        for (i = 0; i < g->num_nodos; i++) {
            if (!visitado[i] && cm->distancia[actual][i] <= umbral) {
                candidatos_rcl[cantidad_rcl] = i;
                cantidad_rcl++;
            }
        }

        seleccionado = candidatos_rcl[rand() % cantidad_rcl];
        c->ruta[c->num_nodos] = seleccionado;
        c->num_nodos++;
        visitado[seleccionado] = 1;
    }

    c->distancia_total = calcular_distancia_circuito(c, cm);
}

/* Busqueda local 2-opt: prueba invertir segmentos de la ruta y conserva
   el cambio si reduce la distancia total. El nodo de inicio (posicion 0)
   se mantiene fijo. Se repite hasta no encontrar mas mejoras. */
static void busqueda_local_2opt(const CaminosMinimos *cm, Circuito *c) {
    int hubo_mejora = 1;

    while (hubo_mejora) {
        int i, j;

        hubo_mejora = 0;
        /* Se prueba invertir segmentos de la ruta. */
        for (i = 1; i < c->num_nodos - 1; i++) {
            for (j = i + 1; j < c->num_nodos; j++) {
                int a = c->ruta[i - 1];
                int b = c->ruta[i];
                int x = c->ruta[j];
                int y = (j + 1 < c->num_nodos) ? c->ruta[j + 1] : c->ruta[0];

                double distancia_actual;
                double distancia_nueva;

                if (a == x) {
                    continue;
                }

                distancia_actual = cm->distancia[a][b] + cm->distancia[x][y];
                distancia_nueva = cm->distancia[a][x] + cm->distancia[b][y];

                if (distancia_nueva < distancia_actual - 1e-9) {
                    int izquierda = i;
                    int derecha = j;

                    while (izquierda < derecha) {
                        int temporal = c->ruta[izquierda];

                        c->ruta[izquierda] = c->ruta[derecha];
                        c->ruta[derecha] = temporal;
                        izquierda++;
                        derecha--;
                    }

                    hubo_mejora = 1;
                }
            }
        }
    }

    c->distancia_total = calcular_distancia_circuito(c, cm);
}

/* Ejecuta num_iteraciones de GRASP: en cada iteracion se construye un
   circuito con construir_grasp y se mejora con busqueda_local_2opt; al
   final se conserva el mejor circuito (menor distancia_total) de todas
   las iteraciones realizadas. */
Circuito grasp_tsp(const Grafo *g, const CaminosMinimos *cm, int nodo_inicio,
                    int num_iteraciones, double alpha) {
    Circuito mejor_circuito;
    Circuito circuito_actual;
    int primera_iteracion = 1;
    int iteracion;

    /* Se inicializa el mejor circuito con una distancia infinita para que
       cualquier circuito valido lo supere en la primera iteracion. */
    for (iteracion = 0; iteracion < num_iteraciones; iteracion++) {
        construir_grasp(g, cm, nodo_inicio, alpha, &circuito_actual);
        busqueda_local_2opt(cm, &circuito_actual);

        if (primera_iteracion || circuito_actual.distancia_total < mejor_circuito.distancia_total) {
            mejor_circuito = circuito_actual;
            primera_iteracion = 0;
        }
    }

    return mejor_circuito;
}

/* Imprime la secuencia de nodos visitados (por nombre) en el orden del
   circuito, agrega el regreso al nodo inicial, y muestra la distancia
   total recorrida. */
void grasp_imprimir_circuito(const Circuito *c, const Grafo *g, FILE *archivo_salida) {
    char buffer[256];
    int i;

    imprimir_doble(archivo_salida, "\n--- Circuito GRASP (TSP) ---\n");

    for (i = 0; i < c->num_nodos; i++) {
        snprintf(buffer, sizeof(buffer), "  %2d. %s\n", i + 1, g->nodos[c->ruta[i]].nombre);
        imprimir_doble(archivo_salida, buffer);
    }

    snprintf(buffer, sizeof(buffer), "  %2d. %s (retorno)\n", c->num_nodos + 1,
              g->nodos[c->ruta[0]].nombre);
    imprimir_doble(archivo_salida, buffer);

    snprintf(buffer, sizeof(buffer), "Distancia total del circuito: %.4f km\n", c->distancia_total);
    imprimir_doble(archivo_salida, buffer);
}
