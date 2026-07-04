/* TAD Grafo no dirigido y ponderado, representado con matriz de adyacencia. */

#ifndef GRAFO_H
#define GRAFO_H

#include <stdio.h>

#define MAX_NODOS 100
#define SIN_CONEXION (-1.0)

typedef struct {
    int id;
    char nombre[64];
    double lat;
    double lon;
} Nodo;

typedef struct {
    int num_nodos;
    Nodo nodos[MAX_NODOS];
    double adyacencia[MAX_NODOS][MAX_NODOS];
} Grafo;

/* Inicializa un grafo vacio (sin nodos ni aristas). */
void grafo_inicializar(Grafo *g);

/* Agrega un nodo y retorna el id asignado. */
int grafo_agregar_nodo(Grafo *g, const char *nombre, double lat, double lon);

/* Agrega una arista no dirigida entre origen y destino. */
void grafo_agregar_arista(Grafo *g, int origen, int destino, double peso);

/* Indica si existe arista directa entre dos nodos. */
int grafo_existe_arista(const Grafo *g, int origen, int destino);

/* Retorna el peso de la arista entre dos nodos, o SIN_CONEXION. */
double grafo_obtener_peso(const Grafo *g, int origen, int destino);

/* Imprime la lista de nodos (id, nombre, coordenadas). */
void grafo_imprimir_nodos(const Grafo *g, FILE *archivo_salida);

/* Imprime la matriz de adyacencia completa. */
void grafo_imprimir_matriz(const Grafo *g, FILE *archivo_salida);

/* Exporta nodos y matriz de adyacencia a un archivo CSV. */
void grafo_exportar_csv(const Grafo *g, const char *ruta_archivo);

#endif /* GRAFO_H */
