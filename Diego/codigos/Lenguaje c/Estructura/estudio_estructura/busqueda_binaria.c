#include <stdio.h>

int main() {
    int a[11] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    int buscando;
    int inicio = 0;
    int fin = 10;           // MAX-1
    int medio;
    int encontrado = 0;

    printf("Ingrese numero a buscar del 1 al 11: ");
    scanf("%d", &buscando);

    while(inicio <= fin) {
        medio = (inicio + fin) / 2;
        printf("Inicio: %d, Fin: %d, Medio: %d\n", inicio, fin, medio);

        if(a[medio] == buscando) {
            encontrado = 1;
            break;
        }
        else if(a[medio] < buscando) {
            inicio = medio + 1;
        }
        else {
            fin = medio - 1;
        }
    }

    if(encontrado) {
        printf("Numero %d encontrado en la posicion %d\n", buscando, medio);
    } else {
        printf("No se ha encontrado\n");
    }

    return 0;
}