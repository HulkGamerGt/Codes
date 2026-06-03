#include <stdio.h>
#include <stdlib.h>
#include "cola.h"

void menu();

int main(){
    int opcion;
    int M_namber;
    Deque* misiones = (Deque*)malloc(sizeof(Deque));
    inicializarDeque(misiones);
    do{
        menu();
        scanf("%d",&opcion);
        switch(opcion){
        case 1:
            printf("Ingrese el numero de la mision normal: ");
            scanf("%d",&M_namber);
            encolarFrente(misiones,M_namber);
            break;
        case 2:
            printf("Ingrese el numero de la mision urgente: ");
            scanf("%d",&M_namber);    
            apilar(misiones, M_namber); 
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            mostrarDeque(misiones);
            break;
        case 6:
            break;
        case 7:
            break;
        case 0:
            printf("Saliendo del programa...\n");
            return 0;
        default:
            printf("Opcion invalida. Intente de nuevo.\n");
            break;
        }
    }while(1);

    return 0;
}

void menu(){
    printf("=== ¿Que Desea Hacer? ===\n\n");
    printf("1.Agregar Mision Normal(MN)\n");
    printf("2.Agregar Mision Urgente(MU)\n");
    printf("3.Resolver Mision(RM)\n");
    printf("4.Invertir lista de recompensas\n");
    printf("5.Mostrar Misiones Normales\n");
    printf("6.Mostrar Misiones Urgentes\n");
    printf("7.Mostrar Recompensas Obtenidas\n");
    printf("0.Salir del programa\n");
    printf("Ingrese su opcion: ");
}
