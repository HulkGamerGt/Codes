/*crear un programa que al recibir dos numeros enteros, calcular la suma resta multiplicacion
de dichos*/
#include <stdio.h>

int main(){
    int numero1;
    int numero2;
    int el;
    int suma;
    int resta;
    int multiplicacion;
    int eleccion;
    printf("elige primer numero\n");
    scanf("%d", &numero1);
    printf("elige el segundo numero\n");
    scanf("%d", &numero2);
    printf("elige la operacion\n");
    printf(" 1)suma\n 2)multiplicacion\n 3)resta\n");
    printf("----------------------------------------\n");
    scanf("%d", &el);
    if (el == 1)
    {
        suma = numero1 + numero2;
        printf("el resultado de la suma es: %d", suma);
    }
    if (el == 2)
    {
        multiplicacion = numero1 * numero2;
        printf("el resultado de la multiplicacion es: %d", multiplicacion);
    }
    if (el == 3)
    {
         resta = numero1 - numero2;
        printf("el resultado de la resta es: %d", resta);
    }
return 0;
}