/*Nombre : Diego Solis Rojas
 Fecha : 29 / 05 / 2025
 Descripcion : Este programa calcula el DV del rut (Chileno), con una formula y despues lo comparara con el DV ingresado*/
#include <stdio.h>
//ESTA A MEDIAS, FALTA EL K ARREGLAR

int main (void){

    int f=0, h=0, num = 0, n=0,i = 0; 
    int multis[8] = {2,3,4,5,6,7,2,3};
    int rut, g[8]; 
    char dv;
    printf("Ingrese su DV: ");
    scanf("%c", &dv);
    printf("Ingrese su rut uno por uno sin DV ni guion\n");
    scanf("%d", &rut);

    for(i = 0 ; i < 8 ; i++ )
    {
        g[i] = rut % 10;
        rut /= 10;
    }
    for (i = 0; i < 8; i++)
    {
        num = ((multis[i] * g[i]) + num);
    }

    f = num % 11; 
    h = 11 - f;
    if (h == 11)
    printf("El digito verificador es 0\n");
    if (h == 10)
    printf("El digito verificador es k\n");
    if (h < 10)
    { 
        printf("El digito verificador es %d\n", h);
    }
    else 
    {
        printf("Ingrese un rut valido\n");
    }
    if (dv == 'k' || dv == 'K')
    {
    dv = 10;
    }
    if(dv != 'k' && dv != 'K')
    {
        if(dv < 10)
        {
            printf("El rut es valido\n");
        }
        else
        {
            printf("El rut no es valido\n");
        }
    }
}