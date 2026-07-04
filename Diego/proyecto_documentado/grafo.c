/* Implementacion del TAD Grafo (no dirigido, ponderado, matriz de adyacencia). */

#include "grafo.h"
#include "salida.h"
#include <string.h>
#include <stdio.h>

/* Inicializa un grafo vacio: sin nodos, y con todas las posiciones de la
 * matriz de adyacencia marcadas como SIN_CONEXION. */
void grafo_inicializar(Grafo *g) {
    int i, j;

    g->num_nodos = 0;
    for (i = 0; i < MAX_NODOS; i++) {
        for (j = 0; j < MAX_NODOS; j++) {
            g->adyacencia[i][j] = SIN_CONEXION;
        }
    }
}

/* Agrega un nuevo nodo al grafo con el nombre y coordenadas indicadas.
 * El id se asigna de forma secuencial (0, 1, 2, ...) segun el orden de
 * insercion, y se retorna para que el llamador pueda referenciarlo. */
int grafo_agregar_nodo(Grafo *g, const char *nombre, double lat, double lon) {
    int nuevo_id = g->num_nodos;

    g->nodos[nuevo_id].id = nuevo_id;

    /* Se copia con strncpy y se fuerza el caracter nulo final, para
     * evitar desbordes si "nombre" es mas largo que el buffer destino. */
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

/* Indica si existe una arista directa entre origen y destino, comparando
 * el valor de la matriz de adyacencia contra el centinela SIN_CONEXION. */
int grafo_existe_arista(const Grafo *g, int origen, int destino) {
    return g->adyacencia[origen][destino] != SIN_CONEXION;
}

/* Retorna el peso almacenado en la matriz de adyacencia para la arista
 * (origen, destino). Si no existe arista, retorna SIN_CONEXION. */
double grafo_obtener_peso(const Grafo *g, int origen, int destino) {
    return g->adyacencia[origen][destino];
}

/* Imprime, para cada nodo del grafo, su id, nombre y coordenadas
 * (lat, lon), usando imprimir_doble (consola + archivo). */
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

/* Imprime la matriz de adyacencia completa, fila por fila, con los
 * pesos formateados a dos decimales (SIN_CONEXION aparece como -1.00). */
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

/* Exporta el grafo a un archivo CSV con dos secciones: primero la lista
 * de nodos (id, nombre, lat, lon) y luego la matriz de adyacencia
 * completa, separadas por una linea en blanco. */
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
