#include <stdio.h>
#include <stdlib.h>
#include "estudiante.h"

void menu();

int main() {
    int opcion;
    Estudiante *lista_estudiantes = NULL;

    do {
        menu();
        if (scanf("%d", &opcion) != 1) {
            while(getchar() != '\n');
            opcion = -1;
        }

        switch(opcion) {
            case 1:
                lista_estudiantes = leer_archivo(lista_estudiantes);
                break;
            case 2:
                mostrar_lista(lista_estudiantes);
                break;
            case 3:
                calcular_promedio(lista_estudiantes);
                break;
            case 4:
                guardar_aprobados(lista_estudiantes);
                break;
            case 0:
                liberar_lista(lista_estudiantes);
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
    printf("\n       GESTION DE ESTUDIANTES");
    printf("\n====================================");
    printf("\n1. Cargar datos desde archivo");
    printf("\n2. Mostrar lista de estudiantes");
    printf("\n3. Calcular promedio general");
    printf("\n4. Guardar aprobados (nota >= 4.0)");
    printf("\n0. Salir");
    printf("\nSeleccione una opcion: ");
}