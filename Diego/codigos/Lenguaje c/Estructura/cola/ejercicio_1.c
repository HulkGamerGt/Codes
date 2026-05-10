#include "cola_1.h"
#include <stdio.h>
#include <stdlib.h>

void mostrar_menu();

int main(){
    int opcion;
    int n;

    TipoCola l;

    l = NULL;

    do{
        mostrar_menu();
        scanf("%d",&opcion);
        switch(opcion){
        case 1:
            printf("ingrese un valor");
            scanf("%d",&n);
            l = inserta_por_cola(l,n);
            muestra_cola(l);
            break;
        case 2:
            /* code */
            break;
        case 3:
            /* code */
            break;
        case 4:
            /* code */
            break;
        case 5:
            /* code */
            break;
        case 0:
            /* code */
            break;
        
        default:
            break;
        }
    }while(opcion!=0);

    return 0;
}

void mostrar_menu(){
    printf("Seleccione una opcion : ");
    printf("\n1. Insertar un número en la pila.\n2. Eliminar el último número ingresado.\n3. Mostrar el número que está en la cima.\n4. Mostrar todos los números almacenados.\n5. Indicar si la pila está vacía.\n0.Salida..");
    printf("\nOpcion a elegir: ");
}