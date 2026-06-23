/*
    Nombres : Ruben Sanchez, Diego Solis, Benjamin Vasquez, Joaquin Vasquez.
    Docente : Nicolas Reyes Reyes.
    Tema : Arboles - Taller 10/06
    Fecha : 10/06/2026
    Descripcion: Programa principal para el manejo de un árbol binario de búsqueda, 
                 con opciones para insertar valores, realizar diferentes tipos de 
                 recorridos y liberar memoria al finalizar. 
*/

#include "ejercicio_2.h"

int main() {

    Nodo* raiz = NULL; // Inicialización del árbol vacío
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
        while ((c = getchar()) != '\n' && c != EOF); // limpiar buffer

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
                printf("Recorrido Preorden: ");
                preorden(raiz);
                printf("\n");
                break;
                
            case 3:
                if (raiz == NULL) {
                    printf("El arbol esta vacio.\n");
                    break;
                }
                printf("Recorrido Inorden: ");
                inorden(raiz);
                printf("\n");
                break;
            case 4:
                if (raiz == NULL) {
                    printf("El arbol esta vacio.\n");
                    break;
                }
                printf("Recorrido Postorden: ");
                postorden(raiz);
                printf("\n");
                break;

            case 5:
                if (raiz == NULL) {
                    printf("El arbol esta vacio.\n");
                    break;
                }
                printf("Recorrido por Niveles: ");
                recorrido_niveles(raiz);
                printf("\n");
                break;

            case 0:
                printf("Saliendo del programa...\n");
                break;

            default:
                printf("Opcion no valida, intente de nuevo.\n");
        }

    }while(opcion != 0);
    
    liberarArbol(raiz);
    printf("Arbol liberado. Fin.\n");
    return 0;
}