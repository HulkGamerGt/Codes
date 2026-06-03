/*
    Nombres : Ruben Sanchez, Diego Solis, Benjamin Vasquez, Joaquin Vasquez
*/
#include <stdio.h>
#include <stdlib.h>
#include "pilas_colas_listas.h"

// ==================== DEQUE ====================
void inicializarDeque(Deque* d) {
    d->frente = NULL;
    d->final = NULL;
    d->tam = 0;
}

int dequeVacio(const Deque* d) {
    return d->frente == NULL;
}

int encolarFinal(Deque* d, int dato) {
    NodoDeque* nuevo = (NodoDeque*)malloc(sizeof(NodoDeque));
    if (!nuevo) {
        printf("Error de memoria\n");
        return 0;
    }
    nuevo->dato = dato;
    nuevo->siguiente = NULL;
    nuevo->anterior = d->final;

    if (dequeVacio(d)) {
        d->frente = nuevo;
        d->final = nuevo;
    } else {
        d->final->siguiente = nuevo;
        d->final = nuevo;
    }
    d->tam++;
    return 1;
}

int desencolarFrente(Deque* d, int* dato) {
    if (dequeVacio(d)) return 0;
    NodoDeque* aux = d->frente;
    *dato = aux->dato;
    d->frente = aux->siguiente;
    if (d->frente != NULL)
        d->frente->anterior = NULL;
    else
        d->final = NULL;
    free(aux);
    d->tam--;
    return 1;
}

void mostrarDeque(const Deque* d) {
    NodoDeque* aux = d->frente;
    if (aux == NULL) {
        printf("No hay misiones normales.\n");
        return;
    }
    printf("Cola -> ");
    while (aux != NULL) {
        printf("%d ", aux->dato);
        aux = aux->siguiente;
    }
    printf("\n");
}

void liberarDeque(Deque* d) {
    NodoDeque* aux;
    while (d->frente != NULL) {
        aux = d->frente;
        d->frente = d->frente->siguiente;
        free(aux);
    }
    d->final = NULL;
    d->tam = 0;
}

// ==================== PILA ====================
void inicializarPila(Pila* p) {
    p->tope = NULL;
    p->tam = 0;
}

int pilaVacia(const Pila* p) {
    return p->tope == NULL;
}

int apilar(Pila* p, int dato) {
    NodoPila* nuevo = (NodoPila*)malloc(sizeof(NodoPila));
    if (!nuevo) {
        printf("Error de memoria\n");
        return 0;
    }
    nuevo->dato = dato;
    nuevo->siguiente = p->tope;
    p->tope = nuevo;
    p->tam++;
    return 1;
}

int desapilar(Pila* p, int* dato) {
    if (pilaVacia(p)) return 0;
    NodoPila* aux = p->tope;
    *dato = aux->dato;
    p->tope = aux->siguiente;
    free(aux);
    p->tam--;
    return 1;
}

void mostrarPila(const Pila* p) {
    NodoPila* aux = p->tope;
    if (aux == NULL) {
        printf("No hay misiones urgentes.\n");
        return;
    }
    printf("Tope -> ");
    while (aux != NULL) {
        printf("%d ", aux->dato);
        aux = aux->siguiente;
    }
    printf("\n");
}

void liberarPila(Pila* p) {
    NodoPila* aux;
    while (p->tope != NULL) {
        aux = p->tope;
        p->tope = p->tope->siguiente;
        free(aux);
    }
    p->tam = 0;
}

// ==================== LISTA ====================
void inicializar(Lista* l) {
    l->n = 0;
}

void insertarFinal(Lista* l, int dato) {
    if (l->n >= 100) {
        printf("Lista llena, no se puede agregar más recompensas.\n");
        return;
    }
    l->datos[l->n] = dato;
    l->n++;
}

void mostrarLista(Lista* l) {
    if (l->n == 0) {
        printf("No hay recompensas.\n");
        return;
    }
    printf("Recompensas -> ");
    for (int i = 0; i < l->n; i++)
        printf("%d ", l->datos[i]);
    printf("\n");
}

void invertirLista(Lista* l) {
    int i = 0, j = l->n - 1, aux;
    while (i < j) {
        aux = l->datos[i];
        l->datos[i] = l->datos[j];
        l->datos[j] = aux;
        i++;
        j--;
    }
    printf("Lista invertida.\n");
}

void borrarRecompensa(Lista* l, int valor) {
    int pos = -1;
    for (int i = 0; i < l->n; i++) {
        if (l->datos[i] == valor) {
            pos = i;
            break;
        }
    }
    if (pos == -1) {
        printf("Recompensa no encontrada.\n");
        return;
    }
    for (int i = pos; i < l->n - 1; i++)
        l->datos[i] = l->datos[i + 1];
    l->n--;
    printf("Recompensa eliminada.\n");
}