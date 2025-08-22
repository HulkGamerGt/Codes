/* Autor : [Diego Solis Rojas]
   Fecha : [12/06/2025]
   Fecha y hora de termino : [  /06/2025 00:00]
   Descripcion : [nose xdd]
*/

#include <stdio.h>

int main (void)
{
    int j=0;
    int n;
    printf("Dime el valor de n (que sea entero): ");
    scanf("%d", &n);
    do{
        printf("Valor do while j: %d\n",j);
        j++;
    }
    while (j < n);
    printf("funcion do while %d\n", j);
    j=0;
    for(j=0;j<n;j++)
    {
        printf("Valor for j: %d\n",j);
    }
    printf("funcion for %d\n", j);
    j=0;
    while (j < n){
        printf("Valor while j: %d\n",j);
        j++;
    }
    printf("funcion while %d\n", j);
    return 0; 
}