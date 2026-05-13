#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cola_2.h"

Cola cola_vacia(void) { return NULL; }

int es_cola_vacia(Cola c) { return c == NULL; }

Cola encolar(Cola c, char *nombre, int num) {
    Persona *nuevo = malloc(sizeof(Persona));
    strncpy(nuevo->nombre, nombre, 49);
    nuevo->nombre[49] = '\0';
    nuevo->num_atencion = num;
    nuevo->sig = NULL;

    if (c == NULL) {
        return nuevo;
    } else {
        Persona *aux = c;
        while (aux->sig != NULL)
            aux = aux->sig;
        aux->sig = nuevo;
        return c;
    }
}

Cola desencolar(Cola c) {
    if (!es_cola_vacia(c)) {
        Persona *aux = c->sig;
        printf("Atendiendo a %s (nro %d)\n", c->nombre, c->num_atencion);
        free(c);
        return aux;
    }
    printf("Cola vacía\n");
    return NULL;
}

void mostrar_proximo(Cola c) {
    if (!es_cola_vacia(c))
        printf("Próximo: %s (nro %d)\n", c->nombre, c->num_atencion);
    else
        printf("Cola vacía\n");
}

void mostrar_cola(Cola c) {
    Persona *aux = c;
    printf("Cola: ");
    while (aux != NULL) {
        printf("[%s(%d)] -> ", aux->nombre, aux->num_atencion);
        aux = aux->sig;
    }
    printf("|\n");
}

void liberar_cola(Cola c) {
    Persona *aux;
    while (c != NULL) {
        aux = c->sig;
        free(c);
        c = aux;
    }
}