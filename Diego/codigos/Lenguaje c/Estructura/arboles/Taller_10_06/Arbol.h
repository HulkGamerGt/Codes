#ifndef ARBOL_H
#define ARBOL_H

/* Estructura del nodo del árbol binario */
typedef struct Nodo {
    int dato;
    struct Nodo *izq;
    struct Nodo *der;
} Nodo;

/* Prototipos de funciones */

/**
 * Inserta un valor en el árbol de forma ordenada (ABB).
 * @param raiz Puntero a la raíz del árbol.
 * @param valor Valor entero a insertar.
 * @return Puntero a la raíz actualizada.
 */
Nodo* insertar(Nodo *raiz, int valor);

/**
 * Busca un valor específico en el árbol.
 * @param raiz Puntero a la raíz del árbol.
 * @param valor Valor a buscar.
 * @return Puntero al nodo encontrado, o NULL si no existe.
 */
Nodo* buscar(Nodo *raiz, int valor);

/**
 * Encuentra el valor mínimo del árbol.
 * @param raiz Puntero a la raíz del árbol (no debe ser NULL).
 * @return El menor valor almacenado.
 */
int minimo(Nodo *raiz);

/**
 * Encuentra el valor máximo del árbol.
 * @param raiz Puntero a la raíz del árbol (no debe ser NULL).
 * @return El mayor valor almacenado.
 */
int maximo(Nodo *raiz);

/**
 * Calcula el peso del árbol (cantidad total de nodos).
 * @param raiz Puntero a la raíz del árbol.
 * @return Número de nodos.
 */
int peso(Nodo *raiz);

/**
 * Cuenta los nodos hoja del árbol (sin hijos).
 * @param raiz Puntero a la raíz del árbol.
 * @return Número de hojas.
 */
int contarHojas(Nodo *raiz);

/**
 * Libera toda la memoria ocupada por el árbol.
 * @param raiz Puntero a la raíz del árbol.
 */
void liberarArbol(Nodo *raiz);

/**
 * Recorrido inorden (para verificación visual).
 * @param raiz Puntero a la raíz del árbol.
 */
void inorden(Nodo *raiz);

#endif // ARBOL_H