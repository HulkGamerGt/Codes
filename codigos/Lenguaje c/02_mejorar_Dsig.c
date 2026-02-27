#include <stdio.h>
//Forma menos productiva de recursos. (Hay otra forma de hacerlo, es mas rapido pero mas de pensar, encuentras ahora)

int main (){ 

    int dia = 0, mes = 0, año = 0;
    int i=0,f=0;

    printf("Ingrese dia: ");
    scanf("%d" , &dia);
    printf("Ingrese mes: ");
    scanf("%d" , &mes);
    printf("Ingrese ano :) : ");
    scanf("%d", &año);
    while (i < 1) 
    {
      if (mes >= 1 && mes <= 12)
        {
        if (mes == 11){
            if (dia < 30){
                i++;
                dia++;
                printf("El dia siguiente es: %d / %d / %d", dia, mes, año);
            }
            else{
                dia = 1;
                mes=12;
                printf("El dia siguiente es: %d / %d / %d", dia, mes, año);
                i++;
            }
        }
        if (mes == 10){
            if (dia < 31){
                i++;
                dia++;
                printf("El dia siguiente es: %d / %d / %d", dia, mes, año);
            }
            else{
                dia = 1;
                mes=11;
                printf("El dia siguiente es: %d / %d / %d", dia, mes, año);
                i++;
            }
        }
        if (mes == 9){
            if (dia < 30){
                i++;
                dia++;
                printf("El dia siguiente es: %d / %d / %d", dia, mes, año);
            }
            else{
                dia = 1;
                mes=10;
                printf("El dia siguiente es: %d / %d / %d", dia, mes, año);
                i++;
            }
        }
        if (mes == 8){
            if (dia < 31){
                i++;
                dia++;
                printf("El dia siguiente es: %d / %d / %d", dia, mes, año);
            }
            else{
                dia = 1;
                mes=9;
                printf("El dia siguiente es: %d / %d / %d", dia, mes, año);
                i++;
            }
        }
        if (mes == 7){
            if (dia < 31){
                i++;
                dia++;
                printf("El dia siguiente es: %d / %d / %d", dia, mes, año);
            }
            else{
                dia = 1;
                mes=8;
                printf("El dia siguiente es: %d / %d / %d", dia, mes, año);
                i++;
            }
        }
        if (mes == 6){
            if (dia < 30){
                i++;
                dia++;
                printf("El dia siguiente es: %d / %d / %d", dia, mes, año);
            }
            else{
                dia = 1;
                mes=7;
                printf("El dia siguiente es: %d / %d / %d", dia, mes, año);
                i++;
            }
        }
        if (mes == 5){
            if (dia < 31){
                i++;
                dia++;
                printf("El dia siguiente es: %d / %d / %d", dia, mes, año);
            }
            else{
                dia = 1;
                mes=6;
                printf("El dia siguiente es: %d / %d / %d", dia, mes, año);
                i++;
            }
        }
        if (mes == 4){
            if (dia < 30){
                i++;
                dia++;
                printf("El dia siguiente es: %d / %d / %d", dia, mes, año);
            }
            else{
                dia = 1;
                mes = 5;
                printf("El dia siguiente es: %d / %d / %d", dia, mes, año);
                i++;
            }
        }
        if (mes == 3){
            if (dia < 31){
                i++;
                dia++;
                printf("El dia siguiente es: %d / %d / %d", dia, mes, año);
            }
            else{
                dia = 1;
                mes = 4;
                printf("El dia siguiente es: %d / %d / %d", dia, mes, año);
                i++;
            }
        }
        if (mes == 2){
            printf("El año es bisiesto? 1 para si y 2 para no");
            scanf("%d",&f);
            if (f == 2)
            {
                if (dia < 28)
              {
                i++;
                dia++;
                printf("El dia siguiente es: %d / %d / %d", dia, mes, año);
             }
              else
              {
                dia = 1;
                mes=3;
                printf("El dia siguiente es: %d / %d / %d", dia, mes, año);
                i++;
              }
            } 
            if (f == 1)
            {
                if (dia < 29)
              {
                i++;
                dia++;
                printf("El dia siguiente es: %d / %d / %d", dia, mes, año);
             }
              else
              {
                dia = 1;
                mes=3;
                printf("El dia siguiente es: %d / %d / %d", dia, mes, año);
                i++;
              }
            }
            
        }
        if (mes == 1)
        {
            if (dia < 31)
            {
                i++;
                dia++;
                printf("El dia siguiente es: %d / %d / %d", dia, mes, año);
            }
            else
            {
                dia = 1;
                mes = 2;
                printf("El dia siguiente es: %d / %d / %d", dia, mes, año);
                i++;
            }
        }
        if (mes == 12){
            if (dia < 31){
                i++;
                dia++;
                printf("El dia siguiente es: %d / %d / %d", dia, mes, año);
            }
            else{
                dia = 1;
                mes=1;
                año++;
                printf("El dia siguiente es: %d / %d / %d", dia, mes, año);
                i++;
            }
        }
    }
    else
    {
        printf("El mes no es correcto\n");
        printf("Ingrese un mes correcto: ");
        scanf("%d", &mes);
     }
    }
 return 0;
}
    

