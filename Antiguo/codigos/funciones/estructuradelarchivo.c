/* Autor: Luis Ponce Rosales
Descripción:
Función que crea un archivo vacio llamado "ejemplo.txt" (puntero)
Fecha: 2023-10-05
*/

#include <stdio.h>
#include <string.h>

void xd(FILE * d);
void dx(FILE * fichero);

int main(void) {
    const char *nombre_archivo = "ejemplo.txt";
    const char *modo = "w";  /* Modo escritura (write) */
    FILE *fichero;

    /* Abrir el archivo para escritura */
    fichero = fopen(nombre_archivo, modo);
    /* Verificar si se pudo abrir el archivo */
    if (fichero == NULL) {
        printf("Error al abrir el archivo %s\n", nombre_archivo);
        return 1;
    }
    /* Escribir datos en el archivo */
    xd(fichero);
    dx(fichero);
    /* Cerrar el archivo */
    
    printf("Archivo %s creado exitosamente.\n", nombre_archivo);
    return 0;
}

void xd(FILE *d) {
    fprintf(d, "Este es un ejemplo de archivo.\n");
    fprintf(d, "Creado con el estandar C89/ANSI  C.\n");
    fprintf(d, "Número de ejemplo: %d\n", 52);
}
void dx(FILE *fichero){
    fclose(fichero);
}
