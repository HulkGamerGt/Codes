#include <stdio.h>
int main() {    
    FILE *archivo = fopen("ejemplo.txt", "w");
    if (archivo == NULL) {
    printf("Error al crear el archivo.\n");
        return 1;
    }
    fprintf(archivo, "¡Hola, mundo!\n");
    fclose(archivo);
    printf("Archivo creado exitosamente.\n");
    return 0;
}