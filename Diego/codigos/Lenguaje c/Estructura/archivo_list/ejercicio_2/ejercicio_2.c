#include <stdio.h>
#include <stdlib.h>
#include "historial.h"

void menu();

int main() {
    int opcion;
    PilaNode *pila = NULL;

    do {
        menu();
        if (scanf("%d", &opcion) != 1) {
            while(getchar() != '\n');
            opcion = -1;
        }
        printf("\n====================================\n");

        switch(opcion) {
            case 1:
                // Leer todas las acciones desde "acciones.txt" y apilarlas
                pila = cargar_acciones_a_pila(pila, "acciones.txt");
                break;
            case 2:
                // Insertar cada acción en una pila (ya se hizo en opción 1)
                printf("Las acciones ya estan en la pila (use opcion 1 para recargar).\n");
                break;
            case 3:
                // Mostrar acciones en orden inverso
                mostrar_pila(pila);
                break;
            case 4:
                // Deshacer (eliminar última acción)
                {
                    char accion_eliminada[100];
                    pila = pop(pila, accion_eliminada);
                    if (strlen(accion_eliminada) > 0)
                        printf("Accion deshecha: %s\n", accion_eliminada);
                    else
                        printf("No hay acciones para deshacer.\n");
                }
                break;
            case 5:
                // Guardar acciones restantes en "historial_final.txt"
                guardar_pila_en_archivo(pila, "historial_final.txt");
                break;
            case 0:
                liberar_pila(pila);
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
    printf("\n       HISTORIAL DE ACCIONES\n");
    printf("1. Leer todas las acciones.\n");
    printf("2. Insertar cada accion en una pila.\n");
    printf("3. Mostrar las acciones en orden inverso.\n");
    printf("4. Operacion deshacer (eliminar la ultima accion).\n");
    printf("5. Guardar acciones.\n");
    printf("0. Salir\n");
    printf("Seleccione una opcion: ");
}
