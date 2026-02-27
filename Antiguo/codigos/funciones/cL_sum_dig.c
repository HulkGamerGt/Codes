#include <stdio.h>

int pedir_numero(int *n){
    printf("Ingrese el valor de n: ");
    scanf("%d", n);
    return *n;
}
/*// Regresivo
int sum_dig(int n){
    if(n == 0)
        return 0;
    else 
        return (n % 10) + sum_dig(n / 10);
}*/

// Iterativo
int sum_dig(int n){
    int num=0,divisor = n;
    while(divisor != 0){
        num += (divisor % 10);
        divisor = (divisor/10);
    }
    return num;
}
int main(){
    int n;
    printf("Suma de los digitos de %d = %d\n", n, sum_dig(pedir_numero(&n)));
    return 0;
}