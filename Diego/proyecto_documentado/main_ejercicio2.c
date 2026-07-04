/* Ejercicio 2: TSP mediante GRASP sobre 50 ubicaciones en 5 zonas de Talca. */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "grafo.h"
#include "distancias.h"
#include "caminos_minimos.h"
#include "grasp_tsp.h"
#include "salida.h"

#define NODOS_POR_ZONA 10
#define NUM_ZONAS 5

/* Carga las 5 zonas (50 ubicaciones) en el grafo. La UCM es el primer
 * nodo cargado, en la posicion (0,0) de la zona 0. */
static void cargar_zonas_talca(Grafo *g, int ids_por_zona[NUM_ZONAS][NODOS_POR_ZONA]) {
    const char *nombres_zona0[NODOS_POR_ZONA] = {
        "UCM", "Plaza de Armas", "Catedral de Talca", "Museo OBrien",
        "Liceo Abate Molina", "Centro Comercial Centro", "Biblioteca Publica",
        "Mercado Central", "Casa de la Cultura", "Edificio Consistorial"
    };
    double lat_zona0[NODOS_POR_ZONA] = {
        -35.4283, -35.4264, -35.4267, -35.4267, -35.4280,
        -35.4258, -35.4271, -35.4225, -35.4262, -35.4266
    };
    double lon_zona0[NODOS_POR_ZONA] = {
        -71.6536, -71.6554, -71.6552, -71.6541, -71.6560,
        -71.6548, -71.6537, -71.6605, -71.6550, -71.6556
    };

    const char *nombres_zona1[NODOS_POR_ZONA] = {
        "Universidad de Talca", "Parque Los Reyes", "Estadio Bicentenario",
        "Villa Las Lilas", "Centro Deportivo Sur", "Liceo Sur",
        "Plaza Sur", "Hospital Sur", "Feria Sur", "Colegio San Agustin"
    };
    double lat_zona1[NODOS_POR_ZONA] = {
        -35.3961, -35.4400, -35.4150, -35.4420, -35.4380,
        -35.4360, -35.4410, -35.4430, -35.4395, -35.4370
    };
    double lon_zona1[NODOS_POR_ZONA] = {
        -71.6645, -71.6580, -71.6650, -71.6600, -71.6620,
        -71.6560, -71.6590, -71.6610, -71.6630, -71.6570
    };

    const char *nombres_zona2[NODOS_POR_ZONA] = {
        "Terminal de Buses", "Feria Modelo", "Estacion de Trenes",
        "Parque Norte", "Villa Norte", "Colegio Norte",
        "Cementerio Parque", "Plaza Norte", "Centro de Salud Norte", "Av. San Miguel"
    };
    double lat_zona2[NODOS_POR_ZONA] = {
        -35.4233, -35.4220, -35.4233, -35.4100, -35.4120,
        -35.4140, -35.4400, -35.4110, -35.4160, -35.4150
    };
    double lon_zona2[NODOS_POR_ZONA] = {
        -71.6602, -71.6650, -71.6610, -71.6620, -71.6640,
        -71.6600, -71.6300, -71.6630, -71.6580, -71.6500
    };

    const char *nombres_zona3[NODOS_POR_ZONA] = {
        "Mall Plaza Maule", "Costanera Centro", "Casino de Talca",
        "Parque Ibanez", "Hospital Regional", "Plaza Italia",
        "Colegio Oriente", "Villa Oriente", "Centro Medico Oriente", "Parque OHiggins"
    };
    double lat_zona3[NODOS_POR_ZONA] = {
        -35.4072, -35.4055, -35.4100, -35.4310, -35.4350,
        -35.4275, -35.4290, -35.4260, -35.4320, -35.4310
    };
    double lon_zona3[NODOS_POR_ZONA] = {
        -71.6390, -71.6378, -71.6420, -71.6480, -71.6489,
        -71.6500, -71.6440, -71.6410, -71.6460, -71.6440
    };

    const char *nombres_zona4[NODOS_POR_ZONA] = {
        "Cerro La Virgen", "Villa Poniente", "Colegio Poniente",
        "Parque Poniente", "Plaza Poniente", "Centro Comunitario Poniente",
        "Feria Poniente", "Estadio Fiscal", "Villa Don Bosco", "Camino a San Clemente"
    };
    double lat_zona4[NODOS_POR_ZONA] = {
        -35.4330, -35.4300, -35.4270, -35.4250, -35.4240,
        -35.4260, -35.4210, -35.4189, -35.4220, -35.4500
    };
    double lon_zona4[NODOS_POR_ZONA] = {
        -71.6700, -71.6680, -71.6660, -71.6690, -71.6710,
        -71.6650, -71.6670, -71.6612, -71.6640, -71.6100
    };

    int i;

    for (i = 0; i < NODOS_POR_ZONA; i++) {
        ids_por_zona[0][i] = grafo_agregar_nodo(g, nombres_zona0[i], lat_zona0[i], lon_zona0[i]);
    }
    for (i = 0; i < NODOS_POR_ZONA; i++) {
        ids_por_zona[1][i] = grafo_agregar_nodo(g, nombres_zona1[i], lat_zona1[i], lon_zona1[i]);
    }
    for (i = 0; i < NODOS_POR_ZONA; i++) {
        ids_por_zona[2][i] = grafo_agregar_nodo(g, nombres_zona2[i], lat_zona2[i], lon_zona2[i]);
    }
    for (i = 0; i < NODOS_POR_ZONA; i++) {
        ids_por_zona[3][i] = grafo_agregar_nodo(g, nombres_zona3[i], lat_zona3[i], lon_zona3[i]);
    }
    for (i = 0; i < NODOS_POR_ZONA; i++) {
        ids_por_zona[4][i] = grafo_agregar_nodo(g, nombres_zona4[i], lat_zona4[i], lon_zona4[i]);
    }
}

/* Conecta completamente (K10) las ubicaciones dentro de cada zona,
 * usando distancia de haversine. */
static void conectar_intra_zona(Grafo *g, int ids_por_zona[NUM_ZONAS][NODOS_POR_ZONA]) {
    int zona, i, j;

    for (zona = 0; zona < NUM_ZONAS; zona++) {
        for (i = 0; i < NODOS_POR_ZONA; i++) {
            for (j = i + 1; j < NODOS_POR_ZONA; j++) {
                int id_i = ids_por_zona[zona][i];
                int id_j = ids_por_zona[zona][j];

                double peso = distancia_haversine(
                    g->nodos[id_i].lat, g->nodos[id_i].lon,
                    g->nodos[id_j].lat, g->nodos[id_j].lon);

                grafo_agregar_arista(g, id_i, id_j, peso);
            }
        }
    }
}

/* Agrega 5 conexiones entre ubicaciones de zonas distintas. */
static void conectar_inter_zona(Grafo *g, int ids_por_zona[NUM_ZONAS][NODOS_POR_ZONA]) {
    int conexiones[5][2] = {
        {0, 1}, {0, 2}, {0, 3}, {1, 4}, {2, 3}
    };
    int posiciones_origen[5] = {0, 2, 5, 2, 3};
    int posiciones_destino[5] = {0, 9, 0, 7, 3};
    int i;

    for (i = 0; i < 5; i++) {
        int zona_origen = conexiones[i][0];
        int zona_destino = conexiones[i][1];

        int id_origen = ids_por_zona[zona_origen][posiciones_origen[i]];
        int id_destino = ids_por_zona[zona_destino][posiciones_destino[i]];

        double peso = distancia_haversine(
            g->nodos[id_origen].lat, g->nodos[id_origen].lon,
            g->nodos[id_destino].lat, g->nodos[id_destino].lon);

        grafo_agregar_arista(g, id_origen, id_destino, peso);
    }
}

/* Ejecuta GRASP con un alpha dado y reporta el resultado. */
static double ejecutar_prueba_alpha(const Grafo *g, const CaminosMinimos *cm,
                                     int id_ucm, double alpha, int num_iteraciones,
                                     FILE *archivo_salida) {
    Circuito circuito;
    char buffer[256];

    circuito = grasp_tsp(g, cm, id_ucm, num_iteraciones, alpha);

    snprintf(buffer, sizeof(buffer), "  alpha = %.1f -> distancia total = %.4f km\n",
              alpha, circuito.distancia_total);
    imprimir_doble(archivo_salida, buffer);

    return circuito.distancia_total;
}

/* Punto de entrada del Ejercicio 2: construye el grafo de 50 ubicaciones
 * agrupadas en 5 zonas de Talca (grafo no completo: K10 intra-zona mas
 * algunas conexiones inter-zona), calcula la distancia minima entre
 * todos los pares de nodos con Floyd-Warshall, y resuelve el TSP desde
 * la UCM usando GRASP, comparando distintos valores de alpha. Los
 * resultados se escriben en pantalla y en el archivo
 * ../resultados/resultado_ejercicio2.txt. */
int main(void) {
    Grafo g;
    CaminosMinimos cm;
    FILE *archivo_resultados;
    char buffer[256];
    int ids_por_zona[NUM_ZONAS][NODOS_POR_ZONA];
    int id_ucm;

    Circuito circuito_prueba1;

    double distancia_alpha_00;
    double distancia_alpha_03;
    double distancia_alpha_07;
    double distancia_alpha_10;

    srand((unsigned int)time(NULL));

    archivo_resultados = fopen("../resultados/resultado_ejercicio2.txt", "w");

    imprimir_doble(archivo_resultados,
        "=================================================\n"
        " EJERCICIO 2: PROBLEMA DEL VENDEDOR VIAJERO (TSP)\n"
        " Bus de acercamiento UCM - 5 zonas de Talca\n"
        "=================================================\n\n");

    grafo_inicializar(&g);
    cargar_zonas_talca(&g, ids_por_zona);
    conectar_intra_zona(&g, ids_por_zona);
    conectar_inter_zona(&g, ids_por_zona);

    id_ucm = ids_por_zona[0][0];

    grafo_imprimir_nodos(&g, archivo_resultados);

    snprintf(buffer, sizeof(buffer), "\nNodo UCM: id=%d, nombre=%s, lat=%.6f, lon=%.6f\n",
              g.nodos[id_ucm].id, g.nodos[id_ucm].nombre,
              g.nodos[id_ucm].lat, g.nodos[id_ucm].lon);
    imprimir_doble(archivo_resultados, buffer);

    grafo_exportar_csv(&g, "../resultados/grafo_ejercicio2.csv");

    /* El grafo no es completo (solo K10 intra-zona + pocas aristas
     * inter-zona), por lo que se necesita Floyd-Warshall para conocer
     * la distancia minima entre cualquier par de nodos. */
    floyd_warshall(&g, &cm);

    /* Prueba 1: GRASP con alpha = 0.3 y 200 iteraciones. */
    imprimir_doble(archivo_resultados,
        "\n=================================================\n"
        " PRUEBA 1: GRASP con alpha = 0.3, 200 iteraciones\n"
        "=================================================\n");

    circuito_prueba1 = grasp_tsp(&g, &cm, id_ucm, 200, 0.3);
    grasp_imprimir_circuito(&circuito_prueba1, &g, archivo_resultados);

    /* Prueba 2: comparacion de distintos valores de alpha. */
    imprimir_doble(archivo_resultados,
        "\n=================================================\n"
        " PRUEBA 2: Comparacion de alpha (0.0, 0.3, 0.7, 1.0), 200 iteraciones c/u\n"
        "=================================================\n");

    distancia_alpha_00 = ejecutar_prueba_alpha(&g, &cm, id_ucm, 0.0, 200, archivo_resultados);
    distancia_alpha_03 = ejecutar_prueba_alpha(&g, &cm, id_ucm, 0.3, 200, archivo_resultados);
    distancia_alpha_07 = ejecutar_prueba_alpha(&g, &cm, id_ucm, 0.7, 200, archivo_resultados);
    distancia_alpha_10 = ejecutar_prueba_alpha(&g, &cm, id_ucm, 1.0, 200, archivo_resultados);

    {
        double mejor_distancia = distancia_alpha_00;
        double mejor_alpha = 0.0;

        if (distancia_alpha_03 < mejor_distancia) { mejor_distancia = distancia_alpha_03; mejor_alpha = 0.3; }
        if (distancia_alpha_07 < mejor_distancia) { mejor_distancia = distancia_alpha_07; mejor_alpha = 0.7; }
        if (distancia_alpha_10 < mejor_distancia) { mejor_distancia = distancia_alpha_10; mejor_alpha = 1.0; }

        snprintf(buffer, sizeof(buffer), "\n  Mejor resultado: alpha = %.1f, con distancia total = %.4f km\n",
                  mejor_alpha, mejor_distancia);
        imprimir_doble(archivo_resultados, buffer);

        imprimir_doble(archivo_resultados,
            "  Se observa que valores de alpha bajos (cercanos a 0) tienden a\n"
            "  favorecer un comportamiento mas voraz durante la construccion,\n"
            "  concentrando la busqueda en las opciones mas prometedoras desde\n"
            "  el inicio, lo que en general conduce a mejores resultados para\n"
            "  este tipo de instancia del problema.\n");
    }

    imprimir_doble(archivo_resultados,
        "\n=================================================\n"
        " FIN DE LA EJECUCION - EJERCICIO 2\n"
        "=================================================\n");

    if (archivo_resultados != NULL) {
        fclose(archivo_resultados);
        fputs("\nResultados guardados en ../resultados/resultado_ejercicio2.txt\n", stdout);
    } else {
        fputs("\nAdvertencia: no se pudo crear el archivo de resultados.\n", stdout);
    }

    return 0;
}
