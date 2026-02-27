#include <stdio.h>

int fib(int);

int main() {
    long long int a = 0, b = 1, nextTerm;
    int i = 1;
    int n; //solo recursivo
    //printf("Los primeros 50 numeros de la serie de Fibonacci son:\n");
    /*
    while (i <= 6) {
        printf("%lld \n", a);
        nextTerm = a + b;
        a = b;
        b = nextTerm;
        i++;
    }*/
    printf("");
    return 0;
}
int fib(int n){
    if (n == 0 || n == 1)
        return n;
    else
        return fib(n - 1) + fib(n - 2);
}