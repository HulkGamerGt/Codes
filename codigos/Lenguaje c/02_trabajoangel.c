#include <stdio.h>
#include <string.h>

void agg_nombre(const char nombre[31]);
void dar_nombre(void);

int main(void)
{
    char continuar;
    char nombre[31];

    do
    {
        printf("Ingrese su nombre: ");
        fgets(nombre, sizeof(nombre), stdin);
        nombre[strcspn(nombre, "\n")] = 0; 
        agg_nombre(nombre);

        do
        {
            printf("¿Desea continuar agregando nombres [S/N]: ");
            scanf(" %c", &continuar);
        } while ((continuar == 'S' || continuar == 's') && (continuar == 'N' || continuar == 'n'));

    } while (continuar == 'S' || continuar == 's');

    dar_nombre();
    return 0;
}

void agg_nombre(const char nombre[31])
{
    FILE *archivo = fopen("nombre.dat", "a");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return;
    }
    fprintf(archivo, "%s\n", nombre); 
    fclose(archivo); 
}

void dar_nombre(void)
{
    char nombre[31];
    int contador = 1;
    FILE *archivo = fopen("nombre.dat", "r");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return;
    }

    printf("Nombres ingresados:\n");
    while (fgets(nombre, sizeof(nombre), archivo) != NULL)
    {
        nombre[strcspn(nombre, "\n")] = 0; 
        printf("%d.- %s %lu\n", contador++, nombre, strlen(nombre));
    }
    fclose(archivo);
}