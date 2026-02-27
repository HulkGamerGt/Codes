#include <stdio.h>

int main() {
    
    int num = 0;
    int i ;
    int numeros[10];
    for(i = 0 ; i < 10; i++ ){
        printf("ingrese el numero: ");
        scanf("%d",&numeros[i]);
    }
    printf("Este numero, lo dijiste anteriormente: ");
    scanf("%d",&num);

    for(i = 0 ; i < 10; i++ )
    { 
        if (numeros[i] == num)
        {
            printf("Numero encontrado en la posicion %d\n", i+1);
        } 
    }
    return 0;
}