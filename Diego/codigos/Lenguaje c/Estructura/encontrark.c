//este programa busca encontrar la una suma para el valor de k
#include <stdio.h>

#define TAM 20

int main (){
    int k, arr[TAM];

    printf("Ingrese valores para un arreglo de 20 posiciones \n");
    for(int i=0 ; i < TAM ; i++){
        printf("Ingrese el valor para la posicion %d: ", i);
        scanf("%d", &arr[i]);
    }
    printf("Ingrese el valor de k: ");
    scanf("%d",&k);

    for(int j=0;j<TAM;j++){
        for(int i=0;i<TAM;i++){
            if(arr[i]+arr[j] == k){
                printf("La suma de %d y %d es igual a %d\n", arr[i], arr[j], k);
            }
        }
    }

    return 0;
}