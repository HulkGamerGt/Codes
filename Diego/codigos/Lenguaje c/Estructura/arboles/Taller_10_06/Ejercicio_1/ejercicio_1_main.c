/*
    Nombres : Ruben Sanchez, Diego Solis, Benjamin Vasquez, Joaquin Vasquez.
    Docente : Nicolas Reyes Reyes.
    Tema : Arboles - Taller 10/06
    Fecha : 10/06/2026
    Descripcion: Programa principal para el manejo de un árbol binario de búsqueda, 
                 con opciones para insertar valores, buscar nodo especifico, busacar 
                 valor maximo y minimo, calcular peso del arbol, contar las hojas 
                 del arbol y liberar memoria al finalizar.
*/
    
#include "ejercicio_1.h"

int main() {
    Nodo *raiz = NULL;
    int opcion, valor;
    int c; // para limpiar buffer
    int carga;

    // Preguntar si se desea cargar la secuencia de validación
    
    scanf("%d", &carga);
    printf("¿Desea cargar la secuencia de validacion del ejercicio?\n");
    printf("1: Si, cargar secuencia.\n");
    printf("0: No, comenzar con el arbol vacio.\n");
    printf("Opcion: ");
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
    } while (opcion != 0);

    liberarArbol(raiz);
    printf("Arbol liberado. Fin.\n");
    return 0;
}