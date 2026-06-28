#include "arbol_binario.h"

static void intercambiar(MinHeap *h, int i, int j) {
    ElementoHeap tmp = h->elementos[i];
    h->elementos[i] = h->elementos[j];
    h->elementos[j] = tmp;
    h->posicion[h->elementos[i].nodo] = i;
    h->posicion[h->elementos[j].nodo] = j;
}

/* Sube el elemento en la posicion i hasta restaurar la propiedad de heap (recursivo) */
static void flotar(MinHeap *h, int i) {
    if (i == 0) return;
    int padre = (i - 1) / 2; /* Calcula la posicion del padre */
    /* Compara la prioridad del elemento con la del padre */
    if (h->elementos[i].prioridad < h->elementos[padre].prioridad) {
        intercambiar(h, i, padre); /* Intercambia el elemento con su padre */
        flotar(h, padre);/* Llama recursivamente a flotar */
    }
}

/* Baja el elemento en la posicion i hasta restaurar la propiedad de heap (recursivo) */
static void hundir(MinHeap *h, int i) {
    int izq = 2 * i + 1, der = 2 * i + 2, menor = i;
    if (izq < h->tamano && h->elementos[izq].prioridad < h->elementos[menor].prioridad) menor = izq;
    if (der < h->tamano && h->elementos[der].prioridad < h->elementos[menor].prioridad) menor = der;
    if (menor != i) {
        intercambiar(h, i, menor);
        hundir(h, menor);
    }
}

void heap_inicializar(MinHeap *h) {
    h->tamano = 0;
    for (int i = 0; i < MAX_HEAP; i++) h->posicion[i] = -1;
}

void heap_insertar(MinHeap *h, int nodo, double prioridad) {
    int i = h->tamano++;
    h->elementos[i].nodo = nodo;
    h->elementos[i].prioridad = prioridad;
    h->posicion[nodo] = i;
    flotar(h, i);
}

ElementoHeap heap_extraer_min(MinHeap *h) {
    ElementoHeap min = h->elementos[0];
    h->posicion[min.nodo] = -1;
    h->tamano--;
    if (h->tamano > 0) {
        h->elementos[0] = h->elementos[h->tamano];
        h->posicion[h->elementos[0].nodo] = 0;
        hundir(h, 0);
    }
    return min;
}

void heap_disminuir_prioridad(MinHeap *h, int nodo, double nueva_prioridad) {
    int i = h->posicion[nodo];
    if (i == -1) return;
    if (nueva_prioridad < h->elementos[i].prioridad) {
        h->elementos[i].prioridad = nueva_prioridad;
        flotar(h, i);
    }
}

int heap_vacio(const MinHeap *h) { return h->tamano == 0; }
int heap_contiene(const MinHeap *h, int nodo) { return h->posicion[nodo] != -1; }
