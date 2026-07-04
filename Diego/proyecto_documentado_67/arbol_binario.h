/* TAD MinHeap (cola de prioridad), representado en arreglo. Usado por
 * Prim para extraer eficientemente el nodo de menor distancia. */

#ifndef ARBOL_BINARIO_H
#define ARBOL_BINARIO_H

#define MAX_HEAP 100

/* Estructura que representa un elemento del MinHeap. */
typedef struct {
    int nodo;
    double prioridad;
} ElementoHeap;

/* Estructura que representa un MinHeap. */
typedef struct {
    ElementoHeap elementos[MAX_HEAP];
    int posicion[MAX_HEAP];   /* posicion[nodo] = indice en elementos, o -1 */
    int tamano;
} MinHeap;

/* Inicializa un heap vacio. */
void heap_inicializar(MinHeap *h);

/* Inserta un nodo con una prioridad dada. */
void heap_insertar(MinHeap *h, int nodo, double prioridad);

/* Extrae y retorna el elemento de menor prioridad. */
ElementoHeap heap_extraer_min(MinHeap *h);

/* Disminuye la prioridad de un nodo ya presente en el heap. */
void heap_disminuir_prioridad(MinHeap *h, int nodo, double nueva_prioridad);

/* Indica si el heap esta vacio. */
int heap_vacio(const MinHeap *h);

/* Indica si un nodo esta presente en el heap. */
int heap_contiene(const MinHeap *h, int nodo);

#endif /* ARBOL_BINARIO_H */
