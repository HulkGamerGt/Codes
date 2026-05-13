#include <stdio.h>
#include <stdlib.h>
#include "historial.h"

void menu();

int main() {
    int opcion;

    do {
        menu();
        if (scanf("%d", &opcion) != 1) {
            while(getchar() != '\n');
            opcion = -1;
        }
        printf("\n==================================== \n");

        switch(opcion) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 0:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion invalida, intente nuevamente.\n");
        }
    } while(opcion != 0);

    return 0;
}

void menu() {
    printf("\n====================================");
    printf("\n       HISTORIAL DE ACCIONES           ");
    printf("\n1. Leer todas las acciones.");
    printf("\n2. Insertar cada acción en una pila.");
    printf("\n3. Mostrar las acciones en orden inverso al que fueron realizadas");
    printf("\n4. Operación deshacer (eliminar la última acción realizada)");
    printf("\n5. Guardar acciones");
    printf("\n0. Salir");
    printf("\nSeleccione una opcion: ");
}