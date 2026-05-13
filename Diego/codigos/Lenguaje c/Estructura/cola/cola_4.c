#include "cola_4.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------- Cola de caja ----------
ColaCaja cola_vacia(void) {
    return NULL;
}

int es_cola_vacia(ColaCaja c) {
    return c == NULL;
}

ColaCaja encolar_cliente(ColaCaja c, Cliente cl) {
    Cliente *nuevo = (Cliente*) malloc(sizeof(Cliente));
    if (nuevo == NULL) {
        printf("Error de memoria\n");
        return c;
    }
    *nuevo = cl;
    nuevo->sig = NULL;
    if (c == NULL) {
        return nuevo;
    } else {
        Cliente *aux = c;
        while (aux->sig != NULL)
            aux = aux->sig;
        aux->sig = nuevo;
        return c;
    }
}

ColaCaja desencolar_cliente(ColaCaja c, Cliente *atendido) {
    if (c == NULL) {
        printf("La cola está vacía.\n");
        return NULL;
    }
    *atendido = *c;
    Cliente *aux = c->sig;
    free(c);
    return aux;
}

void mostrar_cola_caja(ColaCaja c, int num_caja) {
    printf("Caja %d: ", num_caja);
    if (c == NULL) {
        printf("sin clientes en espera.\n");
        return;
    }
    printf("\n");
    Cliente *aux = c;
    while (aux != NULL) {
        printf("  %s | Productos: %d | Monto: $%.2f\n",
               aux->nombre, aux->cant_productos, aux->monto_total);
        aux = aux->sig;
    }
}

int clientes_en_espera(ColaCaja c) {
    int cont = 0;
    while (c != NULL) {
        cont++;
        c = c->sig;
    }
    return cont;
}

void liberar_cola(ColaCaja c) {
    Cliente *aux;
    while (c != NULL) {
        aux = c->sig;
        free(c);
        c = aux;
    }
}

// ---------- Pila de historial ----------
PilaHistorial pila_vacia(void) {
    return NULL;
}

int es_pila_vacia(PilaHistorial p) {
    return p == NULL;
}

PilaHistorial push_historial(PilaHistorial p, Cliente cl) {
    Cliente *nuevo = (Cliente*) malloc(sizeof(Cliente));
    if (nuevo == NULL) {
        printf("Error de memoria\n");
        return p;
    }
    *nuevo = cl;
    nuevo->sig = p;
    return nuevo;
}

void mostrar_historial(PilaHistorial p) {
    if (p == NULL) {
        printf("Historial vacío.\n");
        return;
    }
    printf("Historial de clientes atendidos (más reciente primero):\n");
    PilaHistorial aux = p;
    while (aux != NULL) {
        printf("  %s | Caja: %d | Productos: %d | Monto: $%.2f\n",
               aux->nombre, aux->caja, aux->cant_productos, aux->monto_total);
        aux = aux->sig;
    }
}

float total_vendido_caja(PilaHistorial p, int caja) {
    float total = 0.0f;
    while (p != NULL) {
        if (p->caja == caja)
            total += p->monto_total;
        p = p->sig;
    }
    return total;
}

void liberar_pila(PilaHistorial p) {
    Cliente *aux;
    while (p != NULL) {
        aux = p->sig;
        free(p);
        p = aux;
    }
}