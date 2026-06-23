/*
    Nombres : Ruben Sanchez, Diego Solis, Benjamin Vasquez, Joaquin Vasquez.
    Docente : Nicolas Reyes Reyes.
    Tema : Arboles - Taller 10/06
    Fecha : 10/06/2026
    Descripcion: En este programa se muestran las operaciones requeridas para 
                 el manejo de un árbol binario de búsqueda, describiendo su funcionamiento. 
*/
#include "ejercicio_1.h"

/* ---------- Implementación de funciones ---------- */

Nodo* insertar(Nodo *raiz, int valor) {
    if (raiz == NULL) {
        Nodo *nuevo = (Nodo*) malloc(sizeof(Nodo));
        if (nuevo == NULL) {
            printf("Error: no se pudo asignar memoria.\n");
            exit(EXIT_FAILURE);
        }
        nuevo->dato = valor;
        nuevo->izq = NULL;
        nuevo->der = NULL;
        return nuevo;
    }

    if (valor < raiz->dato)
        raiz->izq = insertar(raiz->izq, valor);
    else if (valor > raiz->dato)
        raiz->der = insertar(raiz->der, valor);
    // Valores iguales se ignoran (árbol sin duplicados)

    return raiz;
}

Nodo* buscar(Nodo *raiz, int valor) {
    if (raiz == NULL)
        return NULL;

    if (valor == raiz->dato)
        return raiz;
    else if (valor < raiz->dato)
        return buscar(raiz->izq, valor);
    else
        return buscar(raiz->der, valor);
}

int minimo(Nodo *raiz) {
    // Se asume que el árbol NO está vacío (se verifica en el menú)
    while (raiz->izq != NULL)
        raiz = raiz->izq;
    return raiz->dato;
}

int maximo(Nodo *raiz) {
    while (raiz->der != NULL)
        raiz = raiz->der;
    return raiz->dato;
}

int peso(Nodo *raiz) {
    if (raiz == NULL)
        return 0;
    return 1 + peso(raiz->izq) + peso(raiz->der);
}

int contarHojas(Nodo *raiz) {
    if (raiz == NULL)
        return 0;
    if (raiz->izq == NULL && raiz->der == NULL)
        return 1;
    return contarHojas(raiz->izq) + contarHojas(raiz->der);
}

void liberarArbol(Nodo *raiz) {
    if (raiz == NULL) return;
    liberarArbol(raiz->izq);
    liberarArbol(raiz->der);
    free(raiz);
}

void inorden(Nodo *raiz) {
    if (raiz != NULL) {
        inorden(raiz->izq);
        printf("%d ", raiz->dato);
        inorden(raiz->der);
    }
}

/* ----- Función para cargar la secuencia de validación ----- */
void cargarSecuenciaValidacion(Nodo **raiz) {
    int valores[] = {23, 45, 1, 3, 7, 36, 8, 9, 30, 24,
                     33, 77, 42, 34, 67, 98, 100, 11, 14, 81};
    int n = sizeof(valores) / sizeof(valores[0]);
    for (int i = 0; i < n; i++) {
        *raiz = insertar(*raiz, valores[i]);
    }
    printf("Secuencia de validación cargada.\n");
}

/* ----- Menú interactivo ----- */
void mostrarMenu() {
    printf("\n===== MENU ARBOL BINARIO =====\n");
    printf("1. Insertar un valor\n");
    printf("2. Buscar un valor\n");
    printf("3. Valor minimo\n");
    printf("4. Valor maximo\n");
    printf("5. Peso del arbol (total nodos)\n");
    printf("6. Contar nodos hoja\n");
    printf("7. Mostrar recorrido inorden\n");
    printf("0. Salir\n");
    printf("Seleccione una opcion: ");
}