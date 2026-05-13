#include <stdio.h>
#include <stdlib.h>
#include "pila_1.h"

Pila pila_vacia(void) { return NULL; }

int es_pila_vacia(Pila p) { return p == NULL; }

Pila push(Pila p, int valor) {
    struct Nodo *nuevo = malloc(sizeof(struct Nodo));
    nuevo->info = valor;
    nuevo->sig = p;
    return nuevo;
}

Pila pop(Pila p) {
    if (!es_pila_vacia(p)) {
        struct Nodo *aux = p->sig;
        free(p);
        return aux;
    }
    return NULL;
}

int cima(Pila p) {
    if (!es_pila_vacia(p))
        return p->info;
    printf("Error: pila vacía\n");
    return -1; // valor centinela
}

void mostrar_pila(Pila p) {
    struct Nodo *aux;
    printf("->");
    for (aux = p; aux != NULL; aux = aux->sig)
        printf("[%d]->", aux->info);
    printf("|\n");
}

void liberar_pila(Pila p) {
    struct Nodo *aux;
    while (p != NULL) {
        aux = p->sig;
        free(p);
        p = aux;
    }
}