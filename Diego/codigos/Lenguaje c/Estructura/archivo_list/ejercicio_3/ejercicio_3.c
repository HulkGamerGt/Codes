#include <stdio.h>
#include <stdlib.h>
#include "at_clientes.h"

void menu();

int main() {
    int opcion;
    CLIENTE *cola = NULL;

    do {
        menu();
        if (scanf("%d", &opcion) != 1) {
            while(getchar() != '\n');
            opcion = -1;
        }
        printf("\n====================================\n");

        switch(opcion) {
            case 1:
                // Clientes en espera (cargar desde clientes.txt)
                cola = cargar_clientes_desde_archivo(cola, "clientes.txt");
                break;
            case 2:
                // Ingresar último cliente (interactivo)
                {
                    int num;
                    char nombre[50], tramite[50];
                    printf("Ingrese numero: ");
                    scanf("%d", &num);
                    printf("Ingrese nombre: ");
                    scanf("%s", nombre);
                    printf("Ingrese tramite: ");
                    scanf("%s", tramite);
                    cola = encolar(cola, num, nombre, tramite);
                    printf("Cliente agregado al final de la cola.\n");
                }
                break;
            case 3:
                // Mostrar cola de espera
                mostrar_cola(cola);
                break;
            case 4:
                // Atención al primer cliente
                {
                    int num;
                    char nombre[50], tramite[50];
                    cola = desencolar(cola, &num, nombre, tramite);
                    if (num != -1)
                        printf("Atendiendo a: %d - %s (%s)\n", num, nombre, tramite);
                    else
                        printf("No hay clientes en espera.\n");
                }
                break;
            case 5:
                // Mostrar cola actualizada
                mostrar_cola(cola);
                break;
            case 6:
                // Guardar clientes pendientes
                guardar_pendientes(cola, "clientes_pendientes.txt");
                break;
            case 0:
                liberar_cola(cola);
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
    printf("\n       ATENCION CLIENTES\n");
    printf("1. Clientes en espera.\n");
    printf("2. Ingresar ultimo cliente.\n");
    printf("3. Mostrar cola de espera.\n");
    printf("4. Atencion al 1er cliente en espera.\n");
    printf("5. Mostrar cola actualizada.\n");
    printf("6. Guardar clientes pendientes.\n");
    printf("0. Salir\n");
    printf("Seleccione una opcion: ");
}
