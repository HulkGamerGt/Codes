#include <stdio.h>

int main(){
    int nota1=0,nota2=0,nota3=0, prom=0;
    printf("Ingrese la primera nota: ");
    scanf("%d", &nota1);
    printf("Ingrese la segunda nota: ");
    scanf("%d", &nota2);
    printf("Ingrese la tercera nota: ");
    scanf("%d", &nota3);
    prom = nota1 + nota2 + nota3/3;
    printf("El promedio es: %d\n", prom);
    return 0;
}