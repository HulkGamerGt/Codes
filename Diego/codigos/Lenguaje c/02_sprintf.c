#include <stdio.h>
#include <string.h>

int main() {
    char nombre_completo[50];
    char nombre[] = "Gandalf";
    char apellido[] = "el Gris";
    sprintf(nombre_completo, "%s %s", nombre, apellido);/*INTERESANTE i i*/
    printf("El nombre completo es: %s.\n", nombre_completo);
    
    return 0;
}
    
