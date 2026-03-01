/*construye un programa que al recibir como datos 
el costo de un articulo vendido y la cantidad de
 vuelto que tiene que recibir y calcule*/ 
#include <stdio.h>

int main(){
    int plata;
    int articulo;
    int cantidad;
    int vuelto;
    int mayo;
    int ketchu;
    printf("¿ cual articulo vas a comprar ?\n");
    printf(" 1)mayo\n 2)ketchu\n");
    scanf("%d", &articulo);
    
    if (articulo == 1)
    {
        mayo = 300;
        articulo = mayo;
    }
    if (articulo == 2)
    {
        ketchu = 500;
        articulo = ketchu;
    }
    printf("¿cuantos productos lleva?: ");
    scanf("%d", &cantidad);

    articulo = articulo * cantidad;

    printf("¿ ingresa cuanto dinero tienes ?\n");
    scanf("%d", &plata);
    if (plata < articulo)
    {
        printf("dinero insuficiente");
    }
    else
    {
        vuelto = plata - articulo;
        printf("el vuelto es de: %d", vuelto);
    }

return 0;  
}