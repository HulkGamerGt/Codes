#include <stdio.h>      // printf, scanf
#include <stdlib.h>     // malloc, free, NULL
#include "cola.h"      // definiciones de Deque y prototipos

void inicializarDeque(Deque* d) {
    d->frente = d->final = NULL;   // deque vacío
    d->tam = 0;
}

int dequeVacio(const Deque* d) {
    return d->frente == NULL;      // sin frente -> vacío
}

int encolarFrente(Deque* d, int m_normal) {
    NodoDeque* n = (NodoDeque*)malloc(sizeof(NodoDeque)); // pedir memoria
    if (!n) { printf("Error de memoria.\n"); return 0; }
    n->m_normal = m_normal;
    n->anterior = NULL;                  // será el nuevo frente
    n->siguiente = d->frente;            // enlazar con el antiguo frente
    if (d->frente) d->frente->anterior = n; // ajustar anterior del antiguo frente
    else d->final = n;                   // si estaba vacío, también es final
    d->frente = n;                       // actualizar frente
    d->tam++;
    return 1;
}

int encolarFinal(Deque* d, int m_normal) {
    NodoDeque* n = (NodoDeque*)malloc(sizeof(NodoDeque));
    if (!n) { printf("Error de memoria.\n"); return 0; }
    n->m_normal = m_normal;
    n->siguiente = NULL;                 // será el nuevo final
    n->anterior = d->final;              // enlazar con el antiguo final
    if (d->final) d->final->siguiente = n; // ajustar siguiente del antiguo final
    else d->frente = n;                  // si estaba vacío, también es frente
    d->final = n;                        // actualizar final
    d->tam++;
    return 1;
}

int desencolarFrente(Deque* d, int* m_normal) {
    if (dequeVacio(d)) { printf("Error: deque vacío.\n"); return 0; }
    NodoDeque* tmp = d->frente;          // nodo a eliminar
    *m_normal = tmp->m_normal;                   // devolver valor
    d->frente = tmp->siguiente;          // avanzar frente
    if (d->frente) d->frente->anterior = NULL; // romper enlace anterior
    else d->final = NULL;                // si quedó vacío, final también NULL
    free(tmp);
    d->tam--;
    return 1;
}

int desencolarFinal(Deque* d, int* m_normal) {
    if (dequeVacio(d)) { printf("Error: deque vacío.\n"); return 0; }
    NodoDeque* tmp = d->final;           // nodo a eliminar
    *m_normal = tmp->m_normal;
    d->final = tmp->anterior;            // retroceder final
    if (d->final) d->final->siguiente = NULL; // romper enlace siguiente
    else d->frente = NULL;               // si quedó vacío, frente también NULL
    free(tmp);
    d->tam--;
    return 1;
}

int verFrente(const Deque* d, int* m_normal) {
    if (dequeVacio(d)) return 0;
    *m_normal = d->frente->m_normal;             // leer m_normal del frente
    return 1;
}

int verFinal(const Deque* d, int* m_normal) {
    if (dequeVacio(d)) return 0;
    *m_normal = d->final->m_normal;              // leer m_normal del final
    return 1;
}

int tamanioDeque(const Deque* d) {
    return d->tam;                       // O(1)
}

void mostrarDeque(const Deque* d) {
    const NodoDeque* p = d->frente;
    printf("Frente -> ");
    while (p) {
        printf("%d ", p->m_normal);          // imprimir cada m_normal
        p = p->siguiente;
    }
    printf("<- Final (tam=%d)\n", d->tam);
}

int buscarEnDeque(const Deque* d, int m_normal) {
    const NodoDeque* p = d->frente;
    while (p) {
        if (p->m_normal == m_normal) return 1;   // encontrado
        p = p->siguiente;
    }
    return 0;                            // no está
}

int copiarDeque(const Deque* origen, Deque* destino) {
    inicializarDeque(destino);           // preparar destino
    const NodoDeque* p = origen->frente;
    while (p) {
        if (!encolarFinal(destino, p->m_normal)) { // copiar al final
            liberarDeque(destino);       // si falla, limpiar
            return 0;
        }
        p = p->siguiente;
    }
    return 1;
}

void invertirDeque(Deque* d) {
    NodoDeque* act = d->frente;
    d->final = d->frente;                // el nuevo final será el antiguo frente
    while (act) {
        NodoDeque* tmp = act->siguiente; // guardar siguiente
        act->siguiente = act->anterior;  // intercambiar enlaces
        act->anterior = tmp;
        act = tmp;                       // avanzar
    }
    if (d->final) {
        d->frente = d->final;            // nuevo frente es el antiguo final
        while (d->frente->anterior)      // buscar el verdadero frente (sin anterior)
            d->frente = d->frente->anterior;
    }
}

void rotarDeque(Deque* d, int n) {
    if (d->tam < 2) return;              // nada que rotar
    n = n % d->tam;                      // normalizar n
    for (int i = 0; i < n; i++) {
        int val;
        if (desencolarFinal(d, &val))    // sacar del final
            encolarFrente(d, val);       // poner al frente
    }
}

void ordenarDeque(Deque* d) {
    if (d->tam < 2) return;              // ya ordenado
    // Selection sort sobre los nodos
    for (NodoDeque* i = d->frente; i->siguiente; i = i->siguiente) {
        NodoDeque* min = i;
        for (NodoDeque* j = i->siguiente; j; j = j->siguiente)
            if (j->m_normal < min->m_normal) min = j; // buscar mínimo
        if (min != i) {
            int tmp = i->m_normal;            // intercambiar valores
            i->m_normal = min->m_normal;
            min->m_normal = tmp;
        }
    }
}

void liberarDeque(Deque* d) {
    while (!dequeVacio(d)) {
        int tmp;
        desencolarFrente(d, &tmp);        // eliminar uno a uno
    }
}