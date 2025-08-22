#include <stdio.h>

int main() {
    long long int a = 0, b = 1, nextTerm;
    int i = 1;

    printf("Los primeros 50 numeros de la serie de Fibonacci son:\n");

    while (i <= 50) {
        printf("%lld, \n", a);
        nextTerm = a + b;
        a = b;
        b = nextTerm;
        i++;
    }

    return 0;
}