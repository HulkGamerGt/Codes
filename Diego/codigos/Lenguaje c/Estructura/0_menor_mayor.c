#include <stdio.h>
#define TAM 5

void ordenamiento(int *);
void arr_ordenado(int *);

int main() {
    int arr[TAM];

    for (int i = 0; i < TAM; i++) {
        printf("Ingrese un numero de la posicion %d: ", i + 1);
        scanf("%d", (arr + i));
    }

    ordenamiento(arr);
    
    printf("\nArreglo ordenado: ");
    arr_ordenado(arr);
    printf("\n");

    return 0;
}

void ordenamiento(int *arr){
    for(int i = 0; i < TAM - 1; i++){
        for(int j = i + 1; j < TAM; j++){
            if(*(arr + i) > *(arr + j)){
                int temp = *(arr + i);
                *(arr + i) = *(arr + j);
                *(arr + j) = temp;
            }
        }
    }
}

void arr_ordenado(int *arr){
    for(int i = 0; i < TAM; i++){
        
        printf("%d ", *(arr + i));
    }
}