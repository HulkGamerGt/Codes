#include <stdio.h>
#include <string.h>

int main() {
    char nombre1[] = "Gandalf";
    char nombre2[] = "Frodo";
    printf("Comparación con strcmp: %i\n", strcmp(nombre1, nombre2));
    return 0;
}
