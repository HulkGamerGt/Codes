/*
    Nombres : Ruben Sanchez, Diego Solis, Benjamin Vasquez, Joaquin Vasquez.
    Docente : Nicolas Reyes Reyes.
    Tema : Arboles - Taller 10/06
    Fecha : 10/06/2026
    Descripcion: En este programa se implementas las operaciones requeridas para 
                 el manejo de un árbol binario de búsqueda. 
*/

#ifndef EJERCICIO_1_H
#define EJERCICIO_1_H

#include <stdio.h>
#include <stdlib.h>

/* Estructura del nodo del árbol binario */
typedef struct Nodo {
    int dato;
    struct Nodo *izq;
    struct Nodo *der;
} Nodo;

/* Prototipos de funciones */

/* Inserta un valor en el árbol de forma ordenada (ABB)*/
Nodo* insertar(Nodo *raiz, int valor);

/*Busca un valor específico en el árbol.*/
Nodo* buscar(Nodo *raiz, int valor);

/*Encuentra el valor mínimo del árbol.*/
int minimo(Nodo *raiz);

/*Encuentra el valor máximo del árbol.*/
int maximo(Nodo *raiz);

/*Calcula el peso del árbol (cantidad total de nodos).*/
int peso(Nodo *raiz);

/*Cuenta los nodos hoja del árbol (sin hijos).*/
int contarHojas(Nodo *raiz);

/*Libera toda la memoria ocupada por el árbol.*/
void liberarArbol(Nodo *raiz);

/*Recorrido inorden (para verificación visual).*/
void inorden(Nodo *raiz);

void mostrarMenu(); /* Muestra el menú de opciones */

#endif /* EJERCICIO_1_H */