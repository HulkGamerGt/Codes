#include <stdio.h>

int main() {
    int arr[8] = {64, 25, 12, 22, 11, 90, 45, 30};
    int j;
    // 1. Imprimir antes
    printf("Antes: ");
    for(int i=0 ; i < 8 ; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");

    // 2. Insertion Sort
    for(int i = 1; i < 8; i++) {
        int clave = arr[i];
        j = i - 1;

        while(j >= 0 && arr[j] > clave) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = clave;
    }

    // 3. Imprimir después
    printf("Después: ");
    for(int i=0 ;i < 8; i++){
        printf("%d ", arr[i]);
    }

    return 0;
}