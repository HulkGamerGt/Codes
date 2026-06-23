#include <stdio.h>
#include <stdlib.h>
#include "Arbol.h"

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

int main() {
    Nodo *raiz = NULL;
    int opcion, valor;
    int c; // para limpiar buffer
    int carga;

    // Preguntar si se desea cargar la secuencia de validación
    printf("¿Desea cargar la secuencia de validacion del ejercicio?\n");
    printf("1: Si, cargar secuencia.\n");
    printf("0: No, comenzar con el arbol vacio.\n");
    printf("Opcion: ");
    scanf("%d", &carga);
    while ((c = getchar()) != '\n' && c != EOF);

    if (carga == 1) {
        cargarSecuenciaValidacion(&raiz);
    } else {
        printf("Arbol vacio inicializado.\n");
    }

    do {
        mostrarMenu();
        scanf("%d", &opcion);
        while ((c = getchar()) != '\n' && c != EOF);

        switch (opcion) {
            case 1:
                printf("Ingrese el valor a insertar: ");
                scanf("%d", &valor);
                while ((c = getchar()) != '\n' && c != EOF);
                raiz = insertar(raiz, valor);
                printf("Valor %d insertado.\n", valor);
                break;

            case 2:
                if (raiz == NULL) {
                    printf("El arbol esta vacio.\n");
                    break;
                }
                printf("Ingrese el valor a buscar: ");
                scanf("%d", &valor);
                while ((c = getchar()) != '\n' && c != EOF);
                if (buscar(raiz, valor) != NULL)
                    printf("Valor %d encontrado en el arbol.\n", valor);
                else
                    printf("Valor %d NO encontrado.\n", valor);
                break;

            case 3:
                if (raiz == NULL)
                    printf("El arbol esta vacio, no hay minimo.\n");
                else
                    printf("Valor minimo: %d\n", minimo(raiz));
                break;

            case 4:
                if (raiz == NULL)
                    printf("El arbol esta vacio, no hay maximo.\n");
                else
                    printf("Valor maximo: %d\n", maximo(raiz));
                break;

            case 5:
                printf("Peso del arbol: %d nodos.\n", peso(raiz));
                break;

            case 6:
                printf("Nodos hoja: %d\n", contarHojas(raiz));
                break;

            case 7:
                if (raiz == NULL)
                    printf("El arbol esta vacio.\n");
                else {
                    printf("Recorrido inorden: ");
                    inorden(raiz);
                    printf("\n");
                }
                break;

            case 0:
                printf("Saliendo del programa...\n");
                break;

            default:
                printf("Opcion no valida, intente de nuevo.\n");
        }
    } while (opcion != 8);

    liberarArbol(raiz);
    printf("Arbol liberado. Fin.\n");
    return 0;
}