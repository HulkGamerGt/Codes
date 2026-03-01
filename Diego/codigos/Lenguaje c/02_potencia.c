#include <stdio.h>

int potencia();

int main() {
    potencia();
    return 0;
}

int potencia(){
    int num = 0;
    int potencia = 0;
    float resultado = 1;
    int i=0;

    printf("Ingrese un numero: ");
    scanf("%d", &num);
    printf("Ingrese la potencia: ");
    scanf("%d", &potencia);

    for (i = 0; i < potencia; i++)
    {
        resultado = resultado * num;
    }
    printf("El resultado de %d elevado a la potencia %d es: %.2f\n", num, potencia, resultado);
    return 0;
}