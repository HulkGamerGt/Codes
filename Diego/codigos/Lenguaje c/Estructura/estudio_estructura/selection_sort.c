#include <stdio.h>

#define N 8

int main() {
    int arr[N] = {64, 25, 12, 22, 11, 90, 45, 30};
    int min_idx;
    int temp;

    // Imprimir arreglo original
    printf("Arreglo original: ");
    for(int i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    // Selection Sort
    for(int i = 0; i < N-1; i++) {
        min_idx = i;                    // ← Reiniciar en cada pasada

        // Buscar el mínimo en el subarreglo desordenado
        for(int j = i+1; j < N; j++) {
            if(arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }

        // Intercambiar si es necesario
        if(min_idx != i) {
            temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }

    // Imprimir arreglo ordenado
    printf("Arreglo ordenado:  ");
    for(int i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}