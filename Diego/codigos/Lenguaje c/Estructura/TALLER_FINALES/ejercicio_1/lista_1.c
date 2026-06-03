/*
    Nombres : Ruben Sanchez, Diego Solis, Benjamin Vasquez, Joaquin Vasquez
*/
#include <stdio.h>
#include "lista_1.h"

int tamano(Lista l) {
    return l.n;
}

int obtener(Lista l, int pos) {
    return l.datos[pos];
}

void modificar(Lista *l, int pos, int valor) {
    if (pos >= 0 && pos < l->n)
        l->datos[pos] = valor;
}

// Inserta un valor en una posición, desplazando el resto a la derecha
void insertar(Lista *l, int pos, int valor) {
    if (l->n >= MAX || pos < 0 || pos > l->n) return;
    for (int i = l->n; i > pos; i--)
        l->datos[i] = l->datos[i-1];
    l->datos[pos] = valor;
    l->n++;
}

// Elimina el elemento en la posición, desplazando hacia la izquierda
void eliminar(Lista *l, int pos) {
    if (pos < 0 || pos >= l->n) return;
    for (int i = pos; i < l->n - 1; i++)
        l->datos[i] = l->datos[i+1];
    l->n--;
}

void inicializar(Lista *l) {
    l->n = 0;
}