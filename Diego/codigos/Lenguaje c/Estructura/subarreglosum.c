#include <stdio.h>
#include <stdlib.h>

#define TAM 5

//int num_random(int *);

typedef struct {
    int suma_maxima;
    int inicio;
    int fin;
} RESULTADO;

int main() {
    int arr[TAM] = {-1, 3, -2, 0, 4};

    //num_random(arr);
    int suma_actual = arr[0];
    int inicio_temporal = 0;

    RESULTADO mejor;
    mejor.suma_maxima = arr[0];
    mejor.inicio = 0;
    mejor.fin = 0;

    for(int i = 1; i < TAM; i++){
        if(arr[i] > suma_actual + arr[i]){
            suma_actual = arr[i];
            inicio_temporal = i;
        }else{
            suma_actual += arr[i];
        }

        if(suma_actual > mejor.suma_maxima){
            mejor.suma_maxima = suma_actual;
            mejor.inicio = inicio_temporal;
            mejor.fin = i;
        }
    }

    printf("Suma Maxima Encontrada: %d\n", mejor.suma_maxima);
    printf("Rango de indices:       [%d] hasta [%d]\n", mejor.inicio, mejor.fin);
    printf("Elementos:              ");
    
    for(int i = mejor.inicio; i <= mejor.fin; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
/*
int num_random(int arr[TAM]){
    for(int i = 0; i < TAM; i++){
        if(i%2 == 0)
            arr[i] = rand() % 1000;
        else
            arr[i] = -(rand() % 1000);
    }
    return arr;        
}
*/