/*
Diego Solis R: 2025
Fecha: 14/05/2025
Descripcion: Este programa saca el perimetro de un cuadrado (idea de mi hermano, 11 años)

*/

#include<stdio.h>

int main() {

    float PeCua=0, AreCua=0;
    float LaCua=0;

    printf("Este programa saca el area y perimetro de un cuadrado\n");
    printf("ingrese el lado del cuadrado en centimetros: ");
    scanf("%f", &LaCua);

    if (LaCua <= 0){

        printf("Un lado no puede ser negativo o cero, prueba con un valo positivo");
        return 0;
    }
    if (LaCua > 0){

        AreCua = LaCua * LaCua;
        PeCua = 4 * LaCua;
    }
    printf("El area del cuadrado es : %f centimetros cuadrados\n", AreCua);
    printf("El perimetro del cuadrado es : %f centimetros\n", PeCua);
    return 0;
}