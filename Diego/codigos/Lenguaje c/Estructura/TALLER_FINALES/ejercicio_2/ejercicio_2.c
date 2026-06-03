/*
    Nombres : Ruben Sanchez, Diego Solis, Benjamin Vasquez, Joaquin Vasquez
*/
#include <stdio.h>
#include <stdlib.h>
#include "pilas_colas_listas.h"

void menu() {
    printf("\n=== SISTEMA DE MISIONES ===\n");
    printf("1. Agregar mision normal (cola)\n");
    printf("2. Agregar mision urgente (pila)\n");
    printf("3. Resolver mision (prioridad: urgente primero)\n");
    printf("4. Invertir lista de recompensas\n");
    printf("5. Mostrar misiones normales\n");
    printf("6. Mostrar misiones urgentes\n");
    printf("7. Mostrar recompensas\n");
    printf("8. Eliminar recompensa especifica\n");
    printf("0. Salir\n");
    printf("Opción: ");
}

int main() {
    Deque cola;
    Pila pila;
    Lista lista;
    int opcion, id, resuelta;

    inicializarDeque(&cola);
    inicializarPila(&pila);
    inicializar(&lista);

    do {
        menu();
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Ingrese ID de misión normal: ");
                scanf("%d", &id);
                if (!encolarFinal(&cola, id))
                    printf("Error al agregar misión normal.\n");
                break;

            case 2:
                printf("Ingrese ID de misión urgente: ");
                scanf("%d", &id);
                if (!apilar(&pila, id))
                    printf("Error al agregar misión urgente.\n");
                break;

            case 3:
                if (!pilaVacia(&pila)) {
                    desapilar(&pila, &resuelta);
                    printf("Se resolvió misión urgente %d\n", resuelta);
                    insertarFinal(&lista, resuelta);
                } else if (!dequeVacio(&cola)) {
                    desencolarFrente(&cola, &resuelta);
                    printf("Se resolvió misión normal %d\n", resuelta);
                    insertarFinal(&lista, resuelta);
                } else {
                    printf("No hay misiones pendientes.\n");
                }
                break;

            case 4:
                invertirLista(&lista);
                break;

            case 5:
                mostrarDeque(&cola);
                break;

            case 6:
                mostrarPila(&pila);
                break;

            case 7:
                mostrarLista(&lista);
                break;

            case 8:
                printf("Ingrese recompensa a eliminar: ");
                scanf("%d", &id);
                borrarRecompensa(&lista, id);
                break;

            case 0:
                printf("Saliendo del programa...\n");
                break;

            default:
                printf("Opción inválida.\n");
        }
    }while(opcion != 0);

    liberarDeque(&cola);
    liberarPila(&pila);
    return 0;
}