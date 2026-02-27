

#include <stdio.h>


int consulta ();
int numero_dentro();
int al_revez();
int main ()
{
    consulta();

    printf("El programa ha finalizado\n");
    return 0;
}

int consulta()
{
    int cantidad;
    int cantidad2;
    printf("Indique las cantidades del arreglo bidimensional:\n");
    scanf("%d", &cantidad);
    scanf("%d", &cantidad2);
    int arreglo[cantidad][cantidad2];

    numero_dentro(cantidad, cantidad2, arreglo);
}

int numero_dentro(int a, int b, int arreglo[a][b])
{
    int i=0;
    int j=0;
    for (i=0; i< a; i++)
    {
        for (j=0; j< b; j++)
        {
            printf("Ingrese un numero al arreglo[%d][%d]: ", i, j);
            scanf("%d", &arreglo[i][j]);
        }
    }
    printf("Los numeros ingresados son:\n");
    al_revez(a, b, arreglo);

}

int al_revez(int a, int b, int arreglo[a][b])
{// imprime el arreglo al reves
    int i=0;
    int j=0;
    for (i=a-1; i>=0; i--)
    {
        for (j=b-1; j>=0; j--)
        {
            printf("arreglo[%d][%d] = %d\n", i, j, arreglo[i][j]);
        }
        printf("\n");
    }
    return 0;
}