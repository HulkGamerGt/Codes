#include <stdio.h>
#include <stdlib.h>
#include "at_clientes.h"

void menu();

int main() {
    int opcion;
    CLIENTE *lista_clientes = NULL;
    do {
        menu();
        if (scanf("%d", &opcion) != 1) {
            while(getchar() != '\n');
            opcion = -1;
        }
        printf("\n==================================== \n");

        switch(opcion) {
            case 1:
            lista_clientes = leer_archivo(lista_clientes);
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
    printf("\n       ATENCION CLIENTES           ");
    printf("\n1. Clientes en espera.");
    printf("\n2. Ingresar ultimo cliente.");
    printf("\n3. Mostrar cola de espera");
    printf("\n4. Atencion al 1er cliente en espera");
    printf("\n5. Mostrar cola acrualizada");
    printf("\n6. Guardar clientes pendientes");
    printf("\n0. Salir");
    printf("\nSeleccione una opcion: ");
}