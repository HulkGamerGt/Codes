#include <stdio.h>
#define CANT 3


int main(){
    int i=0, suma=0;
    int array[CANT];
    for(i = 0; i < CANT; i++){
        array[i] = 0;
    }
    for(i=0; i < CANT; i++ ){
        printf("Ingrese el valor de la posicion [%d]: ",i);
        scanf("%d",&array[i]);
    }
    while(i < CANT){
        suma = suma + array[i];
        i++;
    }
    printf("La suma total es: %d",suma);
    return 0;
}