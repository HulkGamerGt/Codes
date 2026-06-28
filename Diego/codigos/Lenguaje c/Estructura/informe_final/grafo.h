#ifndef GRAFO_H
#define GRAFO_H

#include <stdio.h>

#define MAX_NODOS 100
#define SIN_CONEXION -1.0  /* valor en la matriz de adyacencia cuando NO existe arista */

/* Representa un punto de interes (POI) o ubicacion del grafo */
typedef struct {
    int id;
    char nombre[64];
    double lat;
    double lon;
} Nodo;

/*
 * TAD Grafo: grafo NO dirigido y ponderado, representado mediante
 * matriz de adyacencia (requisito explicito del enunciado: "Genera
 * la matriz de adyacencia correspondiente").
 */
typedef struct {
    int num_nodos;
    Nodo nodos[MAX_NODOS];
    double adyacencia[MAX_NODOS][MAX_NODOS];
} Grafo;

void   grafo_inicializar(Grafo *g);
int    grafo_agregar_nodo(Grafo *g, const char *nombre, double lat, double lon);
void   grafo_agregar_arista(Grafo *g, int origen, int destino, double peso);
int    grafo_existe_arista(const Grafo *g, int origen, int destino);
double grafo_obtener_peso(const Grafo *g, int origen, int destino);
void   grafo_imprimir_nodos(const Grafo *g, FILE *archivo_salida);
void   grafo_imprimir_matriz(const Grafo *g, FILE *archivo_salida);
void   grafo_exportar_csv(const Grafo *g, const char *ruta_archivo);

#endif
