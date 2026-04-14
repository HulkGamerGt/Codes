#include <stdio.h>

int main(){

    int num;
    int numeros[10] = {23, 45, 12, 67, 89, 34, 56, 78, 91, 11};
    int *p = numeros;
    printf("ingrese un numero a buscar : ");
    scanf("%d",&num);

    for(int i =0; i < 10; i++){

        if(num == *(p+i)){
            printf("Numero encontrado en la posicion %d\n", i);
        }
    }

    return 0;
}
/*
Tenga el siguiente arreglo:
int numeros[10] = {23, 45, 12, 67, 89, 34, 56, 78, 91, 11};
Pida al usuario un número a buscar.
Use búsqueda secuencial y diga:
Si lo encontró → "Encontrado en la posición X"
Si no lo encontró → "No encontrado"
*/