#include <stdio.h>

/* Iterativo
int fibonacci(int n){
    if(n == 0)
        return 0;
    else if(n == 1)
        return 1;
    else 
        return fibonacci(n-1) + fibonacci(n-2);
}*/

int fibonacci(int n){
    int num, i,b, a,nextTerm;
     while (i <= n) {
        printf("%d \n", a);
        nextTerm = a + b;
        a = b;
        b = nextTerm;
        i++;
    }
}

int main(){
    int n;
    printf("Ingrese el valor de n: ");
    scanf("%d", &n);
    printf("Fibonacci de %d = %d\n", n, fibonacci(n));
    return 0;
}