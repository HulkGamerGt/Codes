#include "pila_1.h"
#include <stdio.h>
#include <stdlib.h>

void mostrar_menu();

int main(){
    int opcion, n;
    Pila p = pila_vacia();

    do {
        mostrar_menu();
        scanf("%d", &opcion);
        switch(opcion) {
            case 1:
                printf("Ingrese un valor: ");
                scanf("%d", &n);
                p = push(p, n);
                mostrar_pila(p);
                break;
            case 2:
                if (!es_pila_vacia(p)) {
                    printf("Eliminando %d\n", cima(p));
                    p = pop(p);
                } else
                    printf("Pila vacía\n");
                mostrar_pila(p);
                break;
            case 3:
                if (!es_pila_vacia(p))
                    printf("Cima: %d\n", cima(p));
                else
                    printf("Pila vacía\n");
                break;
            case 4:
                mostrar_pila(p);
                break;
            case 5:
                printf("La pila %s vacía\n", es_pila_vacia(p) ? "está" : "no está");
                break;
            case 0:
                liberar_pila(p);
                p = NULL;
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción inválida\n");
        }
    } while(opcion != 0);
    return 0;
}

void mostrar_menu(){
    printf("\nSeleccione una opción:\n");
    printf("1. Insertar un número en la pila.\n");
    printf("2. Eliminar el último número ingresado.\n");
    printf("3. Mostrar el número que está en la cima.\n");
    printf("4. Mostrar todos los números almacenados.\n");
    printf("5. Indicar si la pila está vacía.\n");
    printf("0. Salida.\n");
    printf("Opción a elegir: ");
}