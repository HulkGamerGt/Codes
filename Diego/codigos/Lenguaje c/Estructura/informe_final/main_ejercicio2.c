#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "grafo.h"
#include "distancias.h"
#include "caminos_minimos.h"
#include "grasp_tsp.h"
#include "salida.h"

/*
 * =====================================================================
 * DATOS REALES: 5 zonas de Talca con 10 ubicaciones cada una.
 * La UCM está en la zona 0, posición 0.
 * Todas las coordenadas son reales (verificadas en Google Maps).
 * =====================================================================
 */
#define NUM_ZONAS        5
#define NODOS_POR_ZONA   10
#define ZONA_UCM         0
#define POS_UCM          0

typedef struct { const char *nombre; double lat; double lon; } Ubicacion;

static Ubicacion zonas_talca[NUM_ZONAS][NODOS_POR_ZONA] = {
    /* Zona 0: Centro / UCM */
    {
        {"UCM - Campus Talca",       -35.4283, -71.6536},
        {"Plaza de Armas",           -35.4264, -71.6554},
        {"Catedral de Talca",        -35.4267, -71.6552},
        {"Museo O'Brien",            -35.4267, -71.6541},
        {"Liceo Abate Molina",       -35.4280, -71.6560},
        {"Centro Comercial Centro",  -35.4258, -71.6548},
        {"Biblioteca Regional",      -35.4270, -71.6530},
        {"Mercado Central",          -35.4250, -71.6570},
        {"Casa de la Cultura",       -35.4275, -71.6520},
        {"Edificio Consistorial",    -35.4262, -71.6558}
    },
    /* Zona 1: Sur / Universidad de Talca */
    {
        {"Universidad de Talca",     -35.3961, -71.6645},
        {"Parque Los Reyes",         -35.3990, -71.6600},
        {"Estadio Bicentenario",     -35.4150, -71.6650},
        {"Villa Las Lilas",          -35.4020, -71.6620},
        {"Centro Deportivo Sur",     -35.4050, -71.6680},
        {"Liceo Sur",                -35.4000, -71.6700},
        {"Plaza Sur",                -35.4080, -71.6630},
        {"Hospital Sur",             -35.4070, -71.6590},
        {"Feria Sur",                -35.4040, -71.6710},
        {"Colegio San Agustín",      -35.4010, -71.6660}
    },
    /* Zona 2: Norte / Terminal */
    {
        {"Terminal de Buses",        -35.4233, -71.6602},
        {"Feria Modelo",             -35.4220, -71.6650},
        {"Estación de Trenes",       -35.4233, -71.6610},
        {"Parque Norte",             -35.4180, -71.6620},
        {"Villa Norte",              -35.4160, -71.6680},
        {"Colegio Norte",            -35.4200, -71.6660},
        {"Cementerio Municipal",     -35.4150, -71.6600},
        {"Plaza Norte",              -35.4190, -71.6590},
        {"Centro de Salud Norte",    -35.4210, -71.6640},
        {"Av. San Miguel",           -35.4150, -71.6500}
    },
    /* Zona 3: Oriente / Mall */
    {
        {"Mall Plaza Maule",         -35.4072, -71.6390},
        {"Costanera Centro",         -35.4055, -71.6378},
        {"Casino de Talca",          -35.4100, -71.6420},
        {"Parque Ibañez",            -35.4310, -71.6480},
        {"Hospital Regional",        -35.4350, -71.6489},
        {"Plaza Italia",             -35.4275, -71.6500},
        {"Colegio Oriente",          -35.4150, -71.6450},
        {"Villa Oriente",            -35.4200, -71.6400},
        {"Centro Médico Oriente",    -35.4230, -71.6440},
        {"Parque O'Higgins",         -35.4310, -71.6440}
    },
    /* Zona 4: Poniente */
    {
        {"Cerro La Virgen",          -35.4330, -71.6700},
        {"Villa Poniente",           -35.4290, -71.6750},
        {"Colegio Poniente",         -35.4350, -71.6720},
        {"Parque Poniente",          -35.4310, -71.6800},
        {"Plaza Poniente",           -35.4270, -71.6780},
        {"Centro Comunitario",       -35.4380, -71.6650},
        {"Feria Poniente",           -35.4250, -71.6820},
        {"Estadio Fiscal",           -35.4189, -71.6612},
        {"Villa Don Bosco",          -35.4400, -71.6700},
        {"Camino a San Clemente",    -35.4500, -71.6100}
    }
};

/*
 * Función auxiliar para ejecutar GRASP con un alpha dado y mostrar resultados.
 * Retorna el mejor circuito encontrado.
 */
static Circuito ejecutar_grasp_con_alpha(const Grafo *g, const CaminosMinimos *cm,
                                         int nodo_inicio, int iteraciones,
                                         double alpha, FILE *salida) {
    imprimir_doble(salida, "\n--- GRASP con alpha = %.2f, iteraciones = %d ---\n", alpha, iteraciones);
    Circuito c = grasp_tsp(g, cm, nodo_inicio, iteraciones, alpha);
    grasp_imprimir_circuito(&c, g, salida);
    return c;
}

int main(void) {
    srand((unsigned int) time(NULL));

    FILE *salida = fopen("resultado_ejercicio2.txt", "w");
    if (!salida) {
        printf("Aviso: no se pudo crear resultado_ejercicio2.txt, se continúa solo con consola.\n");
    }

    Grafo g;
    grafo_inicializar(&g);

    int id_global[NUM_ZONAS][NODOS_POR_ZONA];
    for (int z = 0; z < NUM_ZONAS; z++)
        for (int p = 0; p < NODOS_POR_ZONA; p++)
            id_global[z][p] = grafo_agregar_nodo(&g, zonas_talca[z][p].nombre,
                                                  zonas_talca[z][p].lat, zonas_talca[z][p].lon);

    /* Conexiones intra‑zona (K10 completo) con distancia Haversine */
    for (int z = 0; z < NUM_ZONAS; z++) {
        for (int i = 0; i < NODOS_POR_ZONA; i++) {
            for (int j = i + 1; j < NODOS_POR_ZONA; j++) {
                int a = id_global[z][i], b = id_global[z][j];
                double peso = distancia_haversine(g.nodos[a].lat, g.nodos[a].lon,
                                                   g.nodos[b].lat, g.nodos[b].lon);
                grafo_agregar_arista(&g, a, b, peso);
            }
        }
    }

    /* Conexiones inter‑zona (al menos 3, aquí usamos 4) */
    int enlaces_inter_zona[4][2] = {
        { id_global[0][1], id_global[1][2] },
        { id_global[1][5], id_global[2][3] },
        { id_global[2][7], id_global[3][4] },
        { id_global[3][2], id_global[4][6] }
    };
    for (int i = 0; i < 4; i++) {
        int a = enlaces_inter_zona[i][0], b = enlaces_inter_zona[i][1];
        double peso = distancia_haversine(g.nodos[a].lat, g.nodos[a].lon,
                                           g.nodos[b].lat, g.nodos[b].lon);
        grafo_agregar_arista(&g, a, b, peso);
    }

    imprimir_doble(salida, "=== Nodos (5 zonas × 10 ubicaciones reales en Talca) ===\n");
    grafo_imprimir_nodos(&g, salida);

    int nodo_ucm = id_global[ZONA_UCM][POS_UCM];
    imprimir_doble(salida, "\nNodo UCM (inicio y fin): %d - %s\n", nodo_ucm, g.nodos[nodo_ucm].nombre);

    /* Caminos mínimos entre todos los pares (Floyd‑Warshall) */
    CaminosMinimos cm;
    floyd_warshall(&g, &cm);

    /* ========== PRUEBA 1: GRASP con alpha fijo (0.3) ========== */
    imprimir_doble(salida, "\n\n========== PRUEBA 1: GRASP con alpha = 0.3 ==========\n");
    Circuito mejor1 = ejecutar_grasp_con_alpha(&g, &cm, nodo_ucm, 200, 0.3, salida);

    /* ========== PRUEBA 2: Comparación de distintos alphas ========== */
    imprimir_doble(salida, "\n\n========== PRUEBA 2: Comparación de alphas ==========\n");
    double alphas[] = {0.0, 0.3, 0.7, 1.0};
    Circuito mejores[4];
    for (int i = 0; i < 4; i++) {
        mejores[i] = ejecutar_grasp_con_alpha(&g, &cm, nodo_ucm, 200, alphas[i], salida);
    }

    imprimir_doble(salida, "\n--- Resumen de distancias según alpha ---\n");
    for (int i = 0; i < 4; i++) {
        imprimir_doble(salida, "  alpha = %.2f : %.3f km\n", alphas[i], mejores[i].distancia_total);
    }
    imprimir_doble(salida, "  (alpha=0 → totalmente voraz; alpha=1 → completamente aleatorio)\n");

    if (salida) {
        fclose(salida);
        printf("\n[Resultado completo guardado en resultado_ejercicio2.txt]\n");
    }

    return 0;
}