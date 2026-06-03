/*
    Nombres : Ruben Sanchez, Diego Solis, Benjamin Vasquez, Joaquin Vasquez
*/
#ifndef LISTA_1_H
#define LISTA_1_H

#define MAX 100

typedef struct {
    int datos[MAX];
    int n;          // cantidad actual de elementos
} Lista;

// Operaciones básicas (prototipos con extern)
extern int tamano(Lista l);
extern int obtener(Lista l, int pos);
extern void modificar(Lista *l, int pos, int valor);
extern void insertar(Lista *l, int pos, int valor);
extern void eliminar(Lista *l, int pos);
extern void inicializar(Lista *l);

#endif