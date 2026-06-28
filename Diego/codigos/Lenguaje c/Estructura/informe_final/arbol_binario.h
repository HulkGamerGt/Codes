#ifndef ARBOL_BINARIO_H
#define ARBOL_BINARIO_H

#define MAX_HEAP 100

/*
 * TAD Arbol binario completo (min-heap), representado en memoria
 * mediante un arreglo (representacion implicita de arbol binario:
 * hijos de la posicion i estan en 2i+1 y 2i+2). Se usa como cola
 * de prioridad dentro del algoritmo de Prim.
 */
typedef struct {
    int nodo;          /* id del nodo del grafo */
    double prioridad;  /* peso/distancia asociada */
} ElementoHeap;

typedef struct {
    ElementoHeap elementos[MAX_HEAP];
    int posicion[MAX_HEAP]; /* posicion de cada nodo dentro del heap, -1 si no esta */
    int tamano;
} MinHeap;

void heap_inicializar(MinHeap *h);
void heap_insertar(MinHeap *h, int nodo, double prioridad);
ElementoHeap heap_extraer_min(MinHeap *h);
void heap_disminuir_prioridad(MinHeap *h, int nodo, double nueva_prioridad);
int  heap_vacio(const MinHeap *h);
int  heap_contiene(const MinHeap *h, int nodo);

#endif
