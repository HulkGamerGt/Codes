/* Ejercicio 1: MST (Prim, Kruskal, Boruvka) sobre 25 POIs reales de Talca. */

#include <stdio.h>
#include "grafo.h"
#include "distancias.h"
#include "mst.h"
#include "salida.h"

/* Carga los 25 puntos de interes de Talca en el grafo. */
static void cargar_pois_talca(Grafo *g) {
    grafo_agregar_nodo(g, "Plaza de Armas", -35.4264, -71.6554);
    grafo_agregar_nodo(g, "Universidad Catolica del Maule", -35.4283, -71.6536);
    grafo_agregar_nodo(g, "Universidad de Talca", -35.3961, -71.6645);
    grafo_agregar_nodo(g, "Terminal de Buses", -35.4233, -71.6602);
    grafo_agregar_nodo(g, "Hospital Regional", -35.4350, -71.6489);
    grafo_agregar_nodo(g, "Mall Plaza Maule", -35.4072, -71.6390);
    grafo_agregar_nodo(g, "Estadio Fiscal", -35.4189, -71.6612);
    grafo_agregar_nodo(g, "Parque Ibanez", -35.4310, -71.6480);
    grafo_agregar_nodo(g, "Estacion de Trenes", -35.4233, -71.6610);
    grafo_agregar_nodo(g, "Museo OBrien", -35.4267, -71.6541);
    grafo_agregar_nodo(g, "Costanera Centro", -35.4055, -71.6378);
    grafo_agregar_nodo(g, "Liceo Abate Molina", -35.4280, -71.6560);
    grafo_agregar_nodo(g, "Catedral de Talca", -35.4267, -71.6552);
    grafo_agregar_nodo(g, "Av. San Miguel", -35.4150, -71.6500);
    grafo_agregar_nodo(g, "Feria Modelo", -35.4220, -71.6650);
    grafo_agregar_nodo(g, "Centro Historico", -35.4260, -71.6545);
    grafo_agregar_nodo(g, "Parque OHiggins", -35.4310, -71.6440);
    grafo_agregar_nodo(g, "Villa Cultural Huilquilemu", -35.4690, -71.5550);
    grafo_agregar_nodo(g, "Cementerio Parque", -35.4400, -71.6300);
    grafo_agregar_nodo(g, "Casino de Talca", -35.4100, -71.6420);
    grafo_agregar_nodo(g, "Cerro La Virgen", -35.4330, -71.6700);
    grafo_agregar_nodo(g, "Plaza Italia", -35.4275, -71.6500);
    grafo_agregar_nodo(g, "Estadio Bicentenario", -35.4150, -71.6650);
    grafo_agregar_nodo(g, "Aerodromo", -35.3950, -71.6900);
    grafo_agregar_nodo(g, "Camino a San Clemente", -35.4500, -71.6100);
}

/* Conecta todos los nodos entre si (grafo completo), con peso =
 * distancia euclidiana aproximada. */
static void construir_grafo_completo(Grafo *g) {
    int i, j;

    for (i = 0; i < g->num_nodos; i++) {
        for (j = i + 1; j < g->num_nodos; j++) {
            double peso = distancia_euclidiana_aprox(
                g->nodos[i].lat, g->nodos[i].lon,
                g->nodos[j].lat, g->nodos[j].lon);

            grafo_agregar_arista(g, i, j, peso);
        }
    }
}

/* Punto de entrada del Ejercicio 1: construye el grafo completo de los
 * 25 POIs de Talca, ejecuta y compara los tres algoritmos de MST (Prim,
 * Kruskal y Boruvka), y ademas evalua Prim desde distintos nodos
 * iniciales para verificar que el peso total del MST no depende del
 * nodo de inicio. Los resultados se escriben en pantalla y en el
 * archivo ../resultados/resultado_ejercicio1.txt. */
int main(void) {
    Grafo g;
    FILE *archivo_resultados;
    char buffer[256];

    ArbolExpansion resultado_prim;
    ArbolExpansion resultado_kruskal;
    ArbolExpansion resultado_boruvka;

    ArbolExpansion prim_nodo0;
    ArbolExpansion prim_nodo5;
    ArbolExpansion prim_nodo12;

    archivo_resultados = fopen("../resultados/resultado_ejercicio1.txt", "w");

    imprimir_doble(archivo_resultados,
        "=================================================\n"
        " EJERCICIO 1: ARBOL DE EXPANSION MINIMA (MST)\n"
        " 25 Puntos de Interes de Talca, Chile\n"
        "=================================================\n\n");

    grafo_inicializar(&g);
    cargar_pois_talca(&g);
    construir_grafo_completo(&g);

    grafo_imprimir_nodos(&g, archivo_resultados);
    imprimir_doble(archivo_resultados, "\n");
    grafo_imprimir_matriz(&g, archivo_resultados);
    grafo_exportar_csv(&g, "../resultados/grafo_ejercicio1.csv");

    /* Prueba 1: comparacion de los tres algoritmos de MST. */
    imprimir_doble(archivo_resultados,
        "\n=================================================\n"
        " PRUEBA 1: Prim vs Kruskal vs Boruvka (nodo inicial = 0)\n"
        "=================================================\n");

    resultado_prim = mst_prim(&g, 0);
    mst_imprimir(&resultado_prim, &g, "Prim", archivo_resultados);

    resultado_kruskal = mst_kruskal(&g);
    mst_imprimir(&resultado_kruskal, &g, "Kruskal", archivo_resultados);

    resultado_boruvka = mst_boruvka(&g);
    mst_imprimir(&resultado_boruvka, &g, "Boruvka", archivo_resultados);

    mst_comparar3(&resultado_prim, &resultado_kruskal, &resultado_boruvka, archivo_resultados);

    /* Prueba 2: Prim desde distintos nodos iniciales. */
    imprimir_doble(archivo_resultados,
        "\n=================================================\n"
        " PRUEBA 2: Prim desde distintos nodos iniciales (0, 5, 12)\n"
        "=================================================\n");

    prim_nodo0 = mst_prim(&g, 0);
    prim_nodo5 = mst_prim(&g, 5);
    prim_nodo12 = mst_prim(&g, 12);

    snprintf(buffer, sizeof(buffer), "  Peso total Prim (inicio en nodo %2d - %s): %.4f km\n",
              0, g.nodos[0].nombre, prim_nodo0.peso_total);
    imprimir_doble(archivo_resultados, buffer);

    snprintf(buffer, sizeof(buffer), "  Peso total Prim (inicio en nodo %2d - %s): %.4f km\n",
              5, g.nodos[5].nombre, prim_nodo5.peso_total);
    imprimir_doble(archivo_resultados, buffer);

    snprintf(buffer, sizeof(buffer), "  Peso total Prim (inicio en nodo %2d - %s): %.4f km\n",
              12, g.nodos[12].nombre, prim_nodo12.peso_total);
    imprimir_doble(archivo_resultados, buffer);

    {
        double maximo = prim_nodo0.peso_total;
        double minimo = prim_nodo0.peso_total;
        double diferencia;

        if (prim_nodo5.peso_total > maximo) maximo = prim_nodo5.peso_total;
        if (prim_nodo12.peso_total > maximo) maximo = prim_nodo12.peso_total;
        if (prim_nodo5.peso_total < minimo) minimo = prim_nodo5.peso_total;
        if (prim_nodo12.peso_total < minimo) minimo = prim_nodo12.peso_total;

        diferencia = maximo - minimo;

        snprintf(buffer, sizeof(buffer), "  Diferencia maxima entre los 3 nodos de inicio: %.6f km\n",
                  diferencia);
        imprimir_doble(archivo_resultados, buffer);
    }

    imprimir_doble(archivo_resultados,
        "\n=================================================\n"
        " FIN DE LA EJECUCION - EJERCICIO 1\n"
        "=================================================\n");

    if (archivo_resultados != NULL) {
        fclose(archivo_resultados);
        fputs("\nResultados guardados en ../resultados/resultado_ejercicio1.txt\n", stdout);
    } else {
        fputs("\nAdvertencia: no se pudo crear el archivo de resultados.\n", stdout);
    }

    return 0;
}
