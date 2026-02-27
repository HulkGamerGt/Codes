#include <stdio.h>

int main() {
    
    int num = 0;
    int numeros[5];
    int i;
    
    for(i = 0 ; i < 5; i++){
        printf("ingrese numero entero: %d:", i+1);
        scanf("%d",&numeros[i]);
        num = num + numeros[i]; 
    }
    printf("La suma es: %d",num);
    return 0;

}