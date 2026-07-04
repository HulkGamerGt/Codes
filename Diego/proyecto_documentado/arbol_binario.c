/* Implementacion del TAD MinHeap. */

#include "arbol_binario.h"

/* Intercambia dos elementos y actualiza sus posiciones en el arreglo. */
static void intercambiar(MinHeap *h, int i, int j) {
    ElementoHeap temporal = h->elementos[i];

    h->elementos[i] = h->elementos[j];
    h->elementos[j] = temporal;

    h->posicion[h->elementos[i].nodo] = i;
    h->posicion[h->elementos[j].nodo] = j;
}

/* Sube el elemento i mientras su prioridad sea menor que la de su padre. */
static void flotar(MinHeap *h, int i) {
    int padre;

    if (i == 0) {
        return;
    }

    /* Calcula el índice del padre en un heap binario. */
    padre = (i - 1) / 2; 

    /* Si la prioridad del elemento actual es menor que la de su padre, intercambiar y continuar flotando. */
    if (h->elementos[i].prioridad < h->elementos[padre].prioridad) {
        intercambiar(h, i, padre);
        flotar(h, padre);
    }
}

/* Baja el elemento i mientras sea mayor que alguno de sus hijos. */
static void hundir(MinHeap *h, int i) {
    int izquierdo = 2 * i + 1;
    int derecho = 2 * i + 2;
    int menor = i;

    /* Compara con el hijo izquierdo si existe y es menor que el elemento actual. */
    if (izquierdo < h->tamano &&
        h->elementos[izquierdo].prioridad < h->elementos[menor].prioridad) {
        menor = izquierdo;
    }

    /* Compara con el hijo derecho si existe y es menor que el hijo izquierdo. */
    if (derecho < h->tamano &&
        h->elementos[derecho].prioridad < h->elementos[menor].prioridad) {
        menor = derecho;
    }

    /* Si el menor no es el elemento actual, intercambiar y continuar hundiendo. */
    if (menor != i) {
        intercambiar(h, i, menor);
        hundir(h, menor);
    }
}

/* Inicializa un MinHeap vacío. */
void heap_inicializar(MinHeap *h) {
    int i;

    h->tamano = 0;
    /* Inicializa todas las posiciones a -1 para indicar que no hay elementos. */
    for (i = 0; i < MAX_HEAP; i++) {
        h->posicion[i] = -1;
    }
}

/* Inserta un nuevo elemento en el MinHeap. */
void heap_insertar(MinHeap *h, int nodo, double prioridad) {
    int posicion_nueva = h->tamano;

    h->elementos[posicion_nueva].nodo = nodo;
    h->elementos[posicion_nueva].prioridad = prioridad;
    h->posicion[nodo] = posicion_nueva;
    h->tamano++;

    /* Hace flotar el nuevo elemento para mantener la propiedad del heap. */
    flotar(h, posicion_nueva);
}

/* Extrae el elemento con menor prioridad del MinHeap. */
ElementoHeap heap_extraer_min(MinHeap *h) {
    ElementoHeap minimo = h->elementos[0];
    int ultimo;

    h->posicion[minimo.nodo] = -1;
    ultimo = h->tamano - 1;

    if (ultimo > 0) {
        h->elementos[0] = h->elementos[ultimo];
        h->posicion[h->elementos[0].nodo] = 0;
    }
    h->tamano--;

    if (h->tamano > 0) {
        hundir(h, 0);
    }

    return minimo;
}
/* Disminuye la prioridad de un elemento en el MinHeap. */
void heap_disminuir_prioridad(MinHeap *h, int nodo, double nueva_prioridad) {
    int pos = h->posicion[nodo];

    if (pos == -1) {
        return;
    }

    h->elementos[pos].prioridad = nueva_prioridad;
    flotar(h, pos);
}

int heap_vacio(const MinHeap *h) {
    return h->tamano == 0;
}

int heap_contiene(const MinHeap *h, int nodo) {
    return h->posicion[nodo] != -1;
}
