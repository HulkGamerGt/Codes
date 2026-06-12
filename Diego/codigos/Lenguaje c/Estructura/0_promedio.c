#include <stdio.h>
#define TAM 9999

void promedio(int [TAM], int *);

int main(){

    int arr[TAM];
    int prom=0;
    for(int i=0 ; i < TAM ; i++){
        printf("Ingrese un numero de la posicion %d : ", i+1);
        scanf("%d",&arr[i]);
    }

    promedio(arr,&prom);

    printf("El valor promedio es de %d",prom);

    return 0;
}

void promedio(int arr[TAM], int *prom){

    for(int i=0; i < TAM;i++){
        *prom += arr[i];
    }
    *prom = *prom/TAM;
}