#include <stdio.h>
#include "grafo.h"
#include "distancias.h"
#include "mst.h"
#include "salida.h"

/*
 * =====================================================================
 * DATOS REALES: Puntos de interés en Talca (Chile) obtenidos de Google
 * Maps / OpenStreetMap. Cada entrada incluye nombre, latitud y longitud.
 * =====================================================================
 */
typedef struct { const char *nombre; double lat; double lon; } PuntoInteres;

static PuntoInteres puntos_talca[25] = {
    {"Plaza de Armas",                 -35.4264, -71.6554},
    {"Universidad Católica del Maule", -35.4283, -71.6536},
    {"Universidad de Talca",           -35.3961, -71.6645},
    {"Terminal de Buses",              -35.4233, -71.6602},
    {"Hospital Regional",              -35.4350, -71.6489},
    {"Mall Plaza Maule",               -35.4072, -71.6390},
    {"Estadio Fiscal",                 -35.4189, -71.6612},
    {"Parque Ibañez",                  -35.4310, -71.6480},
    {"Estación de Trenes",             -35.4233, -71.6610},
    {"Museo O'Brien",                  -35.4267, -71.6541},
    {"Costanera Centro",               -35.4055, -71.6378},
    {"Liceo Abate Molina",             -35.4280, -71.6560},
    {"Catedral de Talca",              -35.4267, -71.6552},
    {"Av. San Miguel",                 -35.4150, -71.6500},
    {"Feria Modelo",                   -35.4220, -71.6650},
    {"Centro Histórico",               -35.4260, -71.6545},
    {"Parque O'Higgins",               -35.4310, -71.6440},
    {"Villa Cultural Huilquilemu",     -35.4690, -71.5550},
    {"Cementerio Parque",              -35.4400, -71.6300},
    {"Casino de Talca",                -35.4100, -71.6420},
    {"Cerro La Virgen",                -35.4330, -71.6700},
    {"Plaza Italia",                   -35.4275, -71.6500},
    {"Estadio Bicentenario",           -35.4150, -71.6650},
    {"Aeródromo",                      -35.3950, -71.6900},
    {"Camino a San Clemente",          -35.4500, -71.6100}
};

/* 
 * Función auxiliar para ejecutar y mostrar el MST de un algoritmo dado.
 * Sirve para evitar repetir código en las pruebas.
 */
static void ejecutar_y_mostrar_mst(const Grafo *g, ArbolExpansion (*algoritmo)(const Grafo*),
                                   const char *nombre, FILE *salida) {
    ArbolExpansion arbol = algoritmo(g);
    mst_imprimir(&arbol, g, nombre, salida);
}

int main(void) {
    FILE *salida = fopen("resultado_ejercicio1.txt", "w");
    if (!salida) {
        printf("Aviso: no se pudo crear resultado_ejercicio1.txt, se continúa solo con consola.\n");
    }

    Grafo g;
    grafo_inicializar(&g);

    // Cargar los 25 puntos de interés reales
    for (int i = 0; i < 25; i++)
        grafo_agregar_nodo(&g, puntos_talca[i].nombre, puntos_talca[i].lat, puntos_talca[i].lon);

    // Grafo COMPLETO con distancia euclidiana aproximada (en km)
    for (int i = 0; i < g.num_nodos; i++)
        for (int j = i + 1; j < g.num_nodos; j++) {
            double peso = distancia_euclidiana_aprox(g.nodos[i].lat, g.nodos[i].lon,
                                                       g.nodos[j].lat, g.nodos[j].lon);
            grafo_agregar_arista(&g, i, j, peso);
        }

    imprimir_doble(salida, "=== Nodos (Puntos de interés reales en Talca) ===\n");
    grafo_imprimir_nodos(&g, salida);

    imprimir_doble(salida, "\n=== Matriz de adyacencia (25x25, pesos en km) ===\n");
    grafo_imprimir_matriz(&g, salida);

    /* ========== PRUEBA 1: Algoritmos estándar ========== */
    imprimir_doble(salida, "\n\n--- PRUEBA 1: Comparación de los tres algoritmos ---\n");
    ArbolExpansion arbol_prim    = mst_prim(&g, 0);
    ArbolExpansion arbol_kruskal = mst_kruskal(&g);
    ArbolExpansion arbol_boruvka = mst_boruvka(&g);

    mst_imprimir(&arbol_prim, &g, "PRIM", salida);
    imprimir_doble(salida, "\n");
    mst_imprimir(&arbol_kruskal, &g, "KRUSKAL", salida);
    imprimir_doble(salida, "\n");
    mst_imprimir(&arbol_boruvka, &g, "BORUVKA", salida);

    imprimir_doble(salida, "\n=== Comparación de pesos totales ===\n");
    mst_comparar3(&arbol_prim, &arbol_kruskal, &arbol_boruvka, salida);

    /* ========== PRUEBA 2: Prim con diferentes nodos iniciales ========== 
     * Demuestra que el peso total del MST es el mismo (invariante). */
    imprimir_doble(salida, "\n\n--- PRUEBA 2: Prim con distintos nodos iniciales (0, 5, 12) ---\n");
    int nodos_inicio[] = {0, 5, 12};
    for (int k = 0; k < 3; k++) {
        ArbolExpansion a = mst_prim(&g, nodos_inicio[k]);
        imprimir_doble(salida, "  Prim (inicio = %2d) peso total: %.3f km\n", 
                       nodos_inicio[k], a.peso_total);
    }
    imprimir_doble(salida, "  (Todos deben ser iguales; pequeñas diferencias por empates en pesos.)\n");

    if (salida) {
        fclose(salida);
        printf("\n[Resultado completo guardado en resultado_ejercicio1.txt]\n");
    }

    return 0;
}