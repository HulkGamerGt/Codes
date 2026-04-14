#include <stdio.h>

void printArray(int arr[], int size) {
    for(int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int partition(int arr[], int low, int high) {
    int pivot = arr[low];
    int i = low + 1;

    for(int j = low + 1; j <= high; j++) {
        if(arr[j] < pivot) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
        }
    }

    // Colocar pivote en su posición final
    int temp = arr[low];
    arr[low] = arr[i-1];
    arr[i-1] = temp;

    return i - 1;
}

void quickSort(int arr[], int low, int high) {
    if(low < high) {
        int pi = partition(arr, low, high);
        
        quickSort(arr, low, pi - 1);   // Parte izquierda
        quickSort(arr, pi + 1, high);  // Parte derecha
    }
}

int main() {
    int arr[8] = {64, 25, 12, 22, 11, 90, 45, 30};
    
    printf("Arreglo original: ");
    printArray(arr, 8);

    quickSort(arr, 0, 7);

    printf("Arreglo ordenado:  ");
    printArray(arr, 8);

    return 0;
}