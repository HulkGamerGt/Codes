/* Autor: [Tu nombre] */                           

#include <stdio.h>

void leer_numeros(int arreglo[], int tamaño);
void ordenar(int arreglo[], int tamaño);
void mostrar(int arreglo[], int tamaño);

int main() {
    int cantidad;
    printf("Ingrese la cantidad de números: ");
    scanf("%d", &cantidad);
    int arreglo[cantidad];
    leer_numeros(arreglo, cantidad);
    ordenar(arreglo, cantidad);
    mostrar(arreglo, cantidad);
    return 0;
}

void leer_numeros(int arreglo[], int tamaño) {
    for (int i = 0; i < tamaño; i++) {
        printf("Ingrese el número %d: ", i + 1);
        scanf("%d", &arreglo[i]);
    }
}

void ordenar(int arreglo[], int tamaño) {
    int i = 0;
    int j = 0;
    for (i = 0; i < tamaño - 1; i++) {
        for (j = 0; j < tamaño - i - 1; j++) {
            if (arreglo[j] > arreglo[j + 1]) {
                int temp = arreglo[j];
                arreglo[j] = arreglo[j + 1];
                arreglo[j + 1] = temp;
            }
        }
    }
}

void mostrar(int arreglo[], int tamaño) {
    int i = 0;
    printf("Números ordenados:\n");
    for (i = 0; i < tamaño; i++) {
        printf("%d ", arreglo[i]);
    }
    printf("\n");
}