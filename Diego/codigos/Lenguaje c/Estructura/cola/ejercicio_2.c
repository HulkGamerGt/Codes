#include "cola_2.h"
#include <stdio.h>

void mostrar_menu();

int main() {
    int opcion, num;
    char nombre[50];
    Cola c = cola_vacia();

    do {
        mostrar_menu();
        scanf("%d", &opcion);
        switch(opcion) {
            case 1:
                printf("Nombre: ");
                scanf("%s", nombre);
                printf("Número de atención: ");
                scanf("%d", &num);
                c = encolar(c, nombre, num);
                break;
            case 2:
                c = desencolar(c);
                break;
            case 3:
                mostrar_proximo(c);
                break;
            case 4:
                mostrar_cola(c);
                break;
            case 5:
                printf("La cola %s vacía\n", es_cola_vacia(c) ? "está" : "no está");
                break;
            case 0:
                liberar_cola(c);
                c = NULL;
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción inválida\n");
        }
    } while(opcion != 0);
    return 0;
}

void mostrar_menu() {
    printf("\n1. Agregar una persona a la cola.\n");
    printf("2. Atender a la primera persona ingresada.\n");
    printf("3. Mostrar la próxima persona a atender.\n");
    printf("4. Mostrar todas las personas en espera.\n");
    printf("5. Indicar si la cola está vacía.\n");
    printf("0. Salida.\n");
    printf("Opción: ");
}