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

    //bubble sort
    for(int i = 0; i < N-1; i++){
        for(int j = 0; j < N-i-1; j++){  
            if(arr[j] > arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
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