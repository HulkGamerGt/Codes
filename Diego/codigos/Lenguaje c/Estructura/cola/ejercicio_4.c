#include "cola_4.h"
#include <stdio.h>
#include <stdlib.h>

#define NUM_CAJAS 3

void mostrar_menu();

int main() {
    int opcion, caja_sel;
    Cliente cl;
    ColaCaja cajas[NUM_CAJAS] = {NULL, NULL, NULL};
    PilaHistorial historial = pila_vacia();
    int i;

    do {
        mostrar_menu();
        scanf("%d", &opcion);
        while (getchar() != '\n');

        switch(opcion) {
            case 1:
                printf("Nombre del cliente: ");
                scanf("%49s", cl.nombre);
                printf("Cantidad de productos: ");
                scanf("%d", &cl.cant_productos);
                printf("Monto total de compra: ");
                scanf("%f", &cl.monto_total);
                printf("Asignar a caja (1, 2 o 3): ");
                scanf("%d", &cl.caja);
                if (cl.caja < 1 || cl.caja > NUM_CAJAS) {
                    printf("Caja no válida. Se asignará a la caja 1.\n");
                    cl.caja = 1;
                }
                cajas[cl.caja - 1] = encolar_cliente(cajas[cl.caja - 1], cl);
                printf("Cliente agregado a la caja %d.\n", cl.caja);
                break;

            case 2:
                printf("Seleccione la caja a atender (1, 2 o 3): ");
                scanf("%d", &caja_sel);
                if (caja_sel < 1 || caja_sel > NUM_CAJAS) {
                    printf("Caja inválida.\n");
                    break;
                }
                if (!es_cola_vacia(cajas[caja_sel - 1])) {
                    cajas[caja_sel - 1] = desencolar_cliente(cajas[caja_sel - 1], &cl);
                    printf("Atendiendo a %s (Caja %d). Monto: $%.2f\n",
                           cl.nombre, cl.caja, cl.monto_total);
                    historial = push_historial(historial, cl);
                } else {
                    printf("La caja %d no tiene clientes en espera.\n", caja_sel);
                }
                break;

            case 3:
                printf("El cliente atendido se guarda automáticamente en el historial (opción 2).\n");
                break;

            case 4:
                for (i = 0; i < NUM_CAJAS; i++) {
                    mostrar_cola_caja(cajas[i], i + 1);
                }
                break;

            case 5:
                mostrar_historial(historial);
                break;

            case 6:
                for (i = 0; i < NUM_CAJAS; i++) {
                    float total = total_vendido_caja(historial, i + 1);
                    printf("Total vendido en caja %d: $%.2f\n", i + 1, total);
                }
                break;

            case 7: {
                int max_clientes = -1, caja_max = -1;
                for (i = 0; i < NUM_CAJAS; i++) {
                    int en_espera = clientes_en_espera(cajas[i]);
                    printf("Caja %d: %d clientes en espera.\n", i + 1, en_espera);
                    if (en_espera > max_clientes) {
                        max_clientes = en_espera;
                        caja_max = i + 1;
                    }
                }
                if (max_clientes > 0)
                    printf("La caja con más clientes en espera es la %d (%d clientes).\n",
                           caja_max, max_clientes);
                else
                    printf("Todas las cajas están vacías.\n");
                break;
            }

            case 0:
                for (i = 0; i < NUM_CAJAS; i++)
                    liberar_cola(cajas[i]);
                liberar_pila(historial);
                printf("Memoria liberada. Saliendo...\n");
                break;

            default:
                printf("Opción no válida.\n");
        }
    } while (opcion != 0);

    return 0;
}

void mostrar_menu() {
    printf("\n--- SUPERMERCADO ---\n");
    printf("1. Agregar cliente a una caja\n");
    printf("2. Atender primer cliente de una caja\n");
    printf("3. Guardar cliente atendido en historial (automático en 2)\n");
    printf("4. Mostrar clientes en espera por caja\n");
    printf("5. Mostrar historial de clientes atendidos\n");
    printf("6. Calcular total vendido por cada caja\n");
    printf("7. Determinar caja con más clientes en espera\n");
    printf("0. Salir\n");
    printf("Opción: ");
}