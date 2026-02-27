#include <stdio.h>


void verificar_si_es_primo();

int main()
{
    verificar_si_es_primo();
    return 0;
}

void verificar_si_es_primo()
{
    int i=0;
    int num=0;
    int nume=1;
    int nel=0;
    printf("Ingrese un numero positivo: ");
    scanf("%d", &num);

    for (i = 0; i < num ; i++)
    {
        if (num % i == 1)
        {
            printf("El numero es primo");
        }
    }
    for(i = 0 ;i < nume ; i++)
    {
        nel = (nume % i == 1);
        printf("%d", nel);
    
    }    
}