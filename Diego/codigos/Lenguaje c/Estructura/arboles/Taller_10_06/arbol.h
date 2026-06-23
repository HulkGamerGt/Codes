#ifndef ARBOL_H
#define ARBOL_H

#include <stdio.h>
#include <stdlib.h>

/*
 * Estructura que representa un nodo de un árbol binario.
 * Contiene un valor entero y dos punteros: izquierda y derecha.
 */
typedef struct Nodo {
    int dato;                 /* Valor almacenado en el nodo */
    struct Nodo* izquierda;   /* Apunta al hijo izquierdo (valores menores en un BST) */
    struct Nodo* derecha;     /* Apunta al hijo derecho (valores mayores en un BST) */
} Nodo;

/* --------------------------------------------------------------------------
 * FUNCIONES BÁSICAS
 * -------------------------------------------------------------------------- */

/*
 * Crea un nuevo nodo con el valor dado.
 * Devuelve el puntero al nodo creado o NULL si falla la reserva de memoria.
 */
Nodo* crearNodo(int valor);

/*
 * Inserta un valor en el árbol binario de búsqueda (BST).
 * Si el valor ya existe no lo duplica.
 * Retorna la nueva raíz (por si cambia).
 * Parámetros:
 *   raiz  - puntero a la raíz actual del árbol
 *   valor - entero a insertar
 */
Nodo* insertar(Nodo* raiz, int valor);

/*
 * Busca un valor en el árbol.
 * Devuelve el puntero al nodo que contiene el valor, o NULL si no existe.
 */
Nodo* buscar(Nodo* raiz, int valor);

/*
 * Encuentra el nodo con el valor mínimo en un subárbol.
 * Se recorre siempre hacia la izquierda hasta llegar a NULL.
 * Devuelve el puntero al nodo mínimo.
 */
Nodo* minimo(Nodo* nodo);

/*
 * Elimina el nodo que contiene el valor dado del árbol.
 * Maneja los tres casos: sin hijos, un hijo, dos hijos.
 * Devuelve la nueva raíz después de la eliminación.
 */
Nodo* eliminar(Nodo* raiz, int valor);

/*
 * Recorridos profundos del árbol:
 * inorden   : izquierda → raíz → derecha   (muestra los valores ordenados)
 * preorden  : raíz → izquierda → derecha
 * postorden : izquierda → derecha → raíz
 */
void inorden(Nodo* raiz);
void preorden(Nodo* raiz);
void postorden(Nodo* raiz);

/* --------------------------------------------------------------------------
 * FUNCIONES AVANZADAS
 * -------------------------------------------------------------------------- */

/*
 * Calcula la altura del árbol (cantidad de niveles desde la raíz).
 * La altura de un árbol vacío es 0.
 */
int altura(Nodo* raiz);

/*
 * Cuenta el número total de nodos del árbol.
 */
int contarNodos(Nodo* raiz);

/*
 * Cuenta cuántos nodos son hojas (sin hijos).
 */
int contarHojas(Nodo* raiz);

/*
 * Invierte el árbol (espejo): intercambia el hijo izquierdo y el derecho,
 * y aplica recursivamente lo mismo a los subárboles.
 */
void espejo(Nodo* raiz);

/*
 * Recorrido por niveles (anchura / BFS).
 * Usa una cola interna para visitar los nodos nivel por nivel.
 */
void nivelOrden(Nodo* raiz);

/*
 * Encuentra el ancestro común más bajo (LCA) en un BST.
 * Dados dos valores v1 y v2, retorna el nodo más profundo que es ancestro de ambos.
 * Si alguno no está en el árbol, devuelve NULL.
 */
Nodo* ancestroComun(Nodo* raiz, int v1, int v2);

/*
 * Obtiene el k-ésimo elemento más pequeño (según orden inorden).
 * k se considera 1-indexado (1 = menor de todos).
 * Devuelve el valor correspondiente, o -1 si k es inválido.
 */
int kEsimoMenor(Nodo* raiz, int k);

/*
 * Verifica si el árbol está balanceado:
 * un árbol está balanceado si, para cada nodo, la diferencia de alturas
 * entre sus subárboles izquierdo y derecho es como máximo 1.
 * Devuelve 1 si está balanceado, 0 en caso contrario.
 */
int esBalanceado(Nodo* raiz);

/*
 * Comprueba si el árbol es un BST válido (árbol binario de búsqueda).
 * Para ello se verifica que todos los nodos estén dentro del rango permitido.
 * Devuelve 1 si es BST, 0 si no lo es.
 */
int esBST(Nodo* raiz);

/*
 * Imprime el árbol de forma visual, girado 90° antihorario.
 * El parámetro 'espacio' debe iniciarse en 0; se usa para la sangría.
 */
void imprimirArbol(Nodo* raiz, int espacio);

/*
 * Libera toda la memoria ocupada por el árbol.
 * Recorre en postorden para liberar los hijos antes que el padre.
 */
void liberarArbol(Nodo* raiz);

/*
 * Obtiene el nodo con el valor máximo del árbol.
 * Se recorre siempre hacia la derecha.
 * Devuelve el puntero al nodo máximo o NULL si el árbol está vacío.
 */
Nodo* maximo(Nodo* raiz);

/*
 * Encuentra el predecesor y sucesor inorden de un valor dado.
 * El valor debe existir en el árbol.
 * predecesor: número inmediatamente menor en inorden.
 * sucesor   : número inmediatamente mayor en inorden.
 * Si no existe predecesor o sucesor, se almacena -1.
 * Parámetros:
 *   raiz       - raíz del árbol
 *   valor      - valor de referencia
 *   predecesor - puntero donde guardar el predecesor
 *   sucesor    - puntero donde guardar el sucesor
 */
void sucesorPredecesor(Nodo* raiz, int valor, int* predecesor, int* sucesor);

#endif