#include "cola_3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------- Funciones de cola ----------
ColaImpresion cola_impresion_vacia(void) {
    return NULL;
}

int cola_vacia(ColaImpresion c) {
    return c == NULL;
}

ColaImpresion encolar(ColaImpresion c, Documento doc) {
    Documento *nuevo = (Documento*) malloc(sizeof(Documento));
    if (nuevo == NULL) {
        printf("Error de memoria\n");
        return c;
    }
    *nuevo = doc;
    nuevo->sig = NULL;

    if (c == NULL) {
        return nuevo;
    } else {
        Documento *aux = c;
        while (aux->sig != NULL)
            aux = aux->sig;
        aux->sig = nuevo;
        return c;
    }
}

ColaImpresion desencolar(ColaImpresion c, Documento *atendido) {
    if (c == NULL) {
        printf("La cola de impresión está vacía.\n");
        return NULL;
    }
    *atendido = *c;
    Documento *aux = c->sig;
    free(c);
    return aux;
}

void mostrar_cola(ColaImpresion c) {
    if (c == NULL) {
        printf("No hay documentos pendientes.\n");
        return;
    }
    printf("Documentos pendientes:\n");
    Documento *aux = c;
    while (aux != NULL) {
        printf("  Nombre: %s | Usuario: %s | Páginas: %d | Prioridad: %s\n",
               aux->nombre, aux->usuario, aux->paginas,
               aux->prioridad == NORMAL ? "Normal" : "Urgente");
        aux = aux->sig;
    }
}

int buscar_en_cola(ColaImpresion c, const char *nombre_doc) {
    while (c != NULL) {
        if (strcmp(c->nombre, nombre_doc) == 0)
            return 1;
        c = c->sig;
    }
    return 0;
}

void liberar_cola(ColaImpresion c) {
    Documento *aux;
    while (c != NULL) {
        aux = c->sig;
        free(c);
        c = aux;
    }
}

// ---------- Funciones de pila ----------
PilaHistorial pila_historial_vacia(void) {
    return NULL;
}

int pila_vacia(PilaHistorial p) {
    return p == NULL;
}

PilaHistorial push_historial(PilaHistorial p, Documento doc) {
    Documento *nuevo = (Documento*) malloc(sizeof(Documento));
    if (nuevo == NULL) {
        printf("Error de memoria\n");
        return p;
    }
    *nuevo = doc;
    nuevo->sig = p;
    return nuevo;
}

void mostrar_historial(PilaHistorial p) {
    if (p == NULL) {
        printf("Historial vacío.\n");
        return;
    }
    printf("Historial de impresión (más reciente primero):\n");
    PilaHistorial aux = p;
    while (aux != NULL) {
        printf("  Nombre: %s | Usuario: %s | Páginas: %d | Prioridad: %s\n",
               aux->nombre, aux->usuario, aux->paginas,
               aux->prioridad == NORMAL ? "Normal" : "Urgente");
        aux = aux->sig;
    }
}

int total_paginas_impresas(PilaHistorial p) {
    int total = 0;
    while (p != NULL) {
        total += p->paginas;
        p = p->sig;
    }
    return total;
}

void liberar_pila(PilaHistorial p) {
    Documento *aux;
    while (p != NULL) {
        aux = p->sig;
        free(p);
        p = aux;
    }
}