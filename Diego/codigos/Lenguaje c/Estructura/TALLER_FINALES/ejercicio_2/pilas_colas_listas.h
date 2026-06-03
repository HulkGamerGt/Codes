/*
    Nombres : Ruben Sanchez, Diego Solis, Benjamin Vasquez, Joaquin Vasquez
*/
#ifndef PILAS_COLAS_LISTAS_H
#define PILAS_COLAS_LISTAS_H

#include <stdio.h>
#include <stdlib.h>

// Nodo para Deque (cola doble)
typedef struct NodoDeque {
    int dato;
    struct NodoDeque* anterior;
    struct NodoDeque* siguiente;
} NodoDeque;

// Deque (cola)
typedef struct {
    NodoDeque* frente;
    NodoDeque* final;
    int tam;
} Deque;

extern void inicializarDeque(Deque* d);
extern int dequeVacio(const Deque* d);
extern int encolarFinal(Deque* d, int dato);
extern int desencolarFrente(Deque* d, int* dato);
extern void mostrarDeque(const Deque* d);
extern void liberarDeque(Deque* d);

// Pila
typedef struct NodoPila {
    int dato;
    struct NodoPila* siguiente;
} NodoPila;

typedef struct {
    NodoPila* tope;
    int tam;
} Pila;

extern void inicializarPila(Pila* p);
extern int pilaVacia(const Pila* p);
extern int apilar(Pila* p, int dato);
extern int desapilar(Pila* p, int* dato);
extern void mostrarPila(const Pila* p);
extern void liberarPila(Pila* p);

// Lista estática
typedef struct {
    int datos[100];
    int n;
} Lista;

extern void inicializar(Lista* l);
extern void insertarFinal(Lista* l, int dato);
extern void mostrarLista(Lista* l);
extern void invertirLista(Lista* l);
extern void borrarRecompensa(Lista* l, int valor);

#endif