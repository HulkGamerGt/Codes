#include <stdio.h>
#include <string.h>
#include "grafo.h"
#include "salida.h"

void grafo_inicializar(Grafo *g) {
    g->num_nodos = 0;
    for (int i = 0; i < MAX_NODOS; i++)
        for (int j = 0; j < MAX_NODOS; j++)
            g->adyacencia[i][j] = SIN_CONEXION;
}

int grafo_agregar_nodo(Grafo *g, const char *nombre, double lat, double lon) {
    if (g->num_nodos >= MAX_NODOS) return -1;
    int id = g->num_nodos;
    g->nodos[id].id = id;
    strncpy(g->nodos[id].nombre, nombre, sizeof(g->nodos[id].nombre) - 1);
    g->nodos[id].nombre[sizeof(g->nodos[id].nombre) - 1] = '\0';
    g->nodos[id].lat = lat;
    g->nodos[id].lon = lon;
    g->num_nodos++;
    return id;
}

void grafo_agregar_arista(Grafo *g, int origen, int destino, double peso) {
    if (origen < 0 || destino < 0 || origen >= g->num_nodos || destino >= g->num_nodos) return;
    g->adyacencia[origen][destino] = peso;
    g->adyacencia[destino][origen] = peso; /* grafo no dirigido */
}

int grafo_existe_arista(const Grafo *g, int origen, int destino) {
    if (origen == destino) return 0;
    return g->adyacencia[origen][destino] != SIN_CONEXION;
}

double grafo_obtener_peso(const Grafo *g, int origen, int destino) {
    return g->adyacencia[origen][destino];
}

void grafo_imprimir_nodos(const Grafo *g, FILE *archivo_salida) {
    imprimir_doble(archivo_salida, "ID  Nombre                              Latitud       Longitud\n");
    for (int i = 0; i < g->num_nodos; i++) {
        imprimir_doble(archivo_salida, "%-3d %-35s %-13.6f %-13.6f\n",
               g->nodos[i].id, g->nodos[i].nombre, g->nodos[i].lat, g->nodos[i].lon);
    }
}

void grafo_imprimir_matriz(const Grafo *g, FILE *archivo_salida) {
    imprimir_doble(archivo_salida, "       ");
    for (int j = 0; j < g->num_nodos; j++) imprimir_doble(archivo_salida, "%6d", j);
    imprimir_doble(archivo_salida, "\n");
    for (int i = 0; i < g->num_nodos; i++) {
        imprimir_doble(archivo_salida, "%4d : ", i);
        for (int j = 0; j < g->num_nodos; j++) {
            if (grafo_existe_arista(g, i, j))
                imprimir_doble(archivo_salida, "%6.1f", g->adyacencia[i][j]);
            else
                imprimir_doble(archivo_salida, "%6s", "-");
        }
        imprimir_doble(archivo_salida, "\n");
    }
}

void grafo_exportar_csv(const Grafo *g, const char *ruta_archivo) {
    FILE *f = fopen(ruta_archivo, "w");
    if (!f) { printf("No se pudo crear archivo %s\n", ruta_archivo); return; }
    fprintf(f, "origen,destino,peso\n");
    for (int i = 0; i < g->num_nodos; i++)
        for (int j = i + 1; j < g->num_nodos; j++)
            if (grafo_existe_arista(g, i, j))
                fprintf(f, "%d,%d,%.4f\n", i, j, g->adyacencia[i][j]);
    fclose(f);
}
