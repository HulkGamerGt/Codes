
#include <stdio.h>

int factorial();

int main()
{

    factorial();
    return 0;
}
int factorial() {
    int num = 0;
    int factorial = 1;

    printf("Ingrese un numero: ");
    scanf("%d", &num);

    while (num > 0) {
        factorial = factorial * num;
        num--;
    }
    printf("El factorial es: %d\n", factorial);
    return 0;
}
    