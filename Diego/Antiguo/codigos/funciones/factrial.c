#include <stdio.h>

long factorial(long );
int main(){

    long n;
    long resultado;
    n = 4;
    resultado = factorial(n);
    printf("El factorial de %ld es %ld\n", n, resultado);
    return 0;
}

long factorial(long n){
    printf("%ld\n", n);
    if(n==0)
        return 1;
    else
        return n * factorial(n-1);
}
