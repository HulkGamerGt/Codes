#include "cola_3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mostrar_menu();

int main() {
    int opcion, prioridad;
    Documento doc;
    char nombre_doc[50];
    ColaImpresion cola = cola_impresion_vacia();
    PilaHistorial historial = pila_historial_vacia();

    do {
        mostrar_menu();
        scanf("%d", &opcion);
        while (getchar() != '\n');

        switch(opcion) {
            case 1:
                printf("Nombre del documento: ");
                scanf("%49s", doc.nombre);
                printf("Nombre del usuario: ");
                scanf("%49s", doc.usuario);
                printf("Cantidad de páginas: ");
                scanf("%d", &doc.paginas);
                printf("Prioridad (0 = Normal, 1 = Urgente): ");
                scanf("%d", &prioridad);
                doc.prioridad = (prioridad == 1) ? URGENTE : NORMAL;
                cola = encolar(cola, doc);
                printf("Documento agregado a la cola.\n");
                break;

            case 2:
                if (!cola_vacia(cola)) {
                    cola = desencolar(cola, &doc);
                    printf("Imprimiendo: %s de %s (%d páginas)\n",
                           doc.nombre, doc.usuario, doc.paginas);
                    historial = push_historial(historial, doc);
                } else {
                    printf("No hay documentos para imprimir.\n");
                }
                break;

            case 3:
                printf("El historial se actualiza automáticamente al imprimir.\n");
                break;

            case 4:
                mostrar_cola(cola);
                break;

            case 5:
                mostrar_historial(historial);
                break;

            case 6:
                printf("Total de páginas impresas: %d\n", total_paginas_impresas(historial));
                break;

            case 7:
                printf("Nombre del documento a buscar: ");
                scanf("%49s", nombre_doc);
                if (buscar_en_cola(cola, nombre_doc))
                    printf("El documento '%s' está pendiente de impresión.\n", nombre_doc);
                else
                    printf("El documento '%s' NO está en la cola.\n", nombre_doc);
                break;

            case 0:
                liberar_cola(cola);
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
    printf("\n--- SISTEMA DE IMPRESIÓN ---\n");
    printf("1. Agregar documento a la cola de impresión\n");
    printf("2. Imprimir el primer documento de la cola\n");
    printf("3. Guardar cada documento impreso en la pila (automático en opción 2)\n");
    printf("4. Mostrar documentos pendientes\n");
    printf("5. Mostrar historial de impresión\n");
    printf("6. Calcular total de páginas impresas\n");
    printf("7. Buscar si un documento está pendiente\n");
    printf("0. Salir\n");
    printf("Opción: ");
}