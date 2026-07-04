/* Implementacion del TAD Grafo (no dirigido, ponderado, matriz de adyacencia). */

#include "grafo.h"
#include "salida.h"
#include <string.h>
#include <stdio.h>

void grafo_inicializar(Grafo *g) {
    int i, j;

    g->num_nodos = 0;
    for (i = 0; i < MAX_NODOS; i++) {
        for (j = 0; j < MAX_NODOS; j++) {
            g->adyacencia[i][j] = SIN_CONEXION;
        }
    }
}

int grafo_agregar_nodo(Grafo *g, const char *nombre, double lat, double lon) {
    int nuevo_id = g->num_nodos;

    g->nodos[nuevo_id].id = nuevo_id;

    strncpy(g->nodos[nuevo_id].nombre, nombre, sizeof(g->nodos[nuevo_id].nombre) - 1);
    g->nodos[nuevo_id].nombre[sizeof(g->nodos[nuevo_id].nombre) - 1] = '\0';

    g->nodos[nuevo_id].lat = lat;
    g->nodos[nuevo_id].lon = lon;
    g->num_nodos++;

    return nuevo_id;
}

/* Grafo no dirigido: el peso se guarda en ambas direcciones de la matriz. */
void grafo_agregar_arista(Grafo *g, int origen, int destino, double peso) {
    g->adyacencia[origen][destino] = peso;
    g->adyacencia[destino][origen] = peso;
}

int grafo_existe_arista(const Grafo *g, int origen, int destino) {
    return g->adyacencia[origen][destino] != SIN_CONEXION;
}

double grafo_obtener_peso(const Grafo *g, int origen, int destino) {
    return g->adyacencia[origen][destino];
}

void grafo_imprimir_nodos(const Grafo *g, FILE *archivo_salida) {
    char buffer[256];
    int i;

    imprimir_doble(archivo_salida, "Lista de nodos (id, nombre, lat, lon):\n");

    for (i = 0; i < g->num_nodos; i++) {
        snprintf(buffer, sizeof(buffer), "  [%2d] %-30s lat=%.6f lon=%.6f\n",
                 g->nodos[i].id, g->nodos[i].nombre, g->nodos[i].lat, g->nodos[i].lon);
        imprimir_doble(archivo_salida, buffer);
    }
}

void grafo_imprimir_matriz(const Grafo *g, FILE *archivo_salida) {
    char buffer[64];
    char linea[2048];
    int i, j;

    imprimir_doble(archivo_salida, "Matriz de adyacencia:\n");

    for (i = 0; i < g->num_nodos; i++) {
        linea[0] = '\0';
        for (j = 0; j < g->num_nodos; j++) {
            snprintf(buffer, sizeof(buffer), "%8.2f", g->adyacencia[i][j]);
            strncat(linea, buffer, sizeof(linea) - strlen(linea) - 1);
        }
        strncat(linea, "\n", sizeof(linea) - strlen(linea) - 1);
        imprimir_doble(archivo_salida, linea);
    }
}

void grafo_exportar_csv(const Grafo *g, const char *ruta_archivo) {
    FILE *csv;
    char buffer[256];
    int i, j;

    csv = fopen(ruta_archivo, "w");
    if (csv == NULL) {
        return;
    }

    fputs("id,nombre,lat,lon\n", csv);
    for (i = 0; i < g->num_nodos; i++) {
        snprintf(buffer, sizeof(buffer), "%d,%s,%.6f,%.6f\n",
                 g->nodos[i].id, g->nodos[i].nombre, g->nodos[i].lat, g->nodos[i].lon);
        fputs(buffer, csv);
    }

    fputs("\n", csv);
    fputs("matriz_adyacencia\n", csv);
    for (i = 0; i < g->num_nodos; i++) {
        for (j = 0; j < g->num_nodos; j++) {
            snprintf(buffer, sizeof(buffer), "%.4f", g->adyacencia[i][j]);
            fputs(buffer, csv);
            if (j < g->num_nodos - 1) {
                fputs(",", csv);
            }
        }
        fputs("\n", csv);
    }

    fclose(csv);
}
