/*
    Nombres : Ruben Sanchez, Diego Solis, Benjamin Vasquez, Joaquin Vasquez.
    Docente : Nicolas Reyes Reyes.
    Tema : Arboles - Taller 10/06
    Fecha : 10/06/2026
    Descripcion: En este programa se muestran los portotipos de las funciones necesarias
                 para el manejo de un árbol binario segun lo requierido en el taller.
*/

#ifndef EJERCICIO_2_H
#define EJERCICIO_2_H

#include <stdio.h>
#include <stdlib.h>

// 1. Estructura base del Nodo
typedef struct nodo {
    int dato;           // Valor almacenado en el nodo
    struct nodo* izq;   // Puntero al subárbol izquierdo
    struct nodo* der;   // Puntero al subárbol derecho
} Nodo;

Nodo* nuevoNodo(int valor);                  /* Crea un nuevo nodo de árbol */
Nodo* liberarArbol(Nodo* raiz);              /* Libera la memoria del árbol */
Nodo* insertar(Nodo* raiz, int valor);       /* Inserta un valor en el árbol manteniendo la propiedad del ABB */
void inorden(Nodo* raiz);                    /* Recorrido inorden */
void preorden(Nodo* raiz);                   /* Recorrido preorden */
void postorden(Nodo* raiz);                  /* Recorrido postorden */
void recorrido_niveles(Nodo* raiz);          /* Recorrido por niveles */
void mostrarMenu();                          /* Muestra el menú de opciones */
void cargarSecuenciaValidacion(Nodo** raiz); /* Carga una secuencia de validación predefinida (en la pauta) */


#endif /* EJERCICIO_2_H */