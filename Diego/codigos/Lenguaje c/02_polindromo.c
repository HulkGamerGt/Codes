#include <stdio.h>
#include <string.h>

int es_polindromo(char *cadena) {
    int longitud = strlen(cadena);
    for (int i = 0; i < longitud / 2; i++) {
        if (  cadena[longitud - i - 1]) {
            return 0;  
        }
    }
    return 1;
}

int main() {
    char cadena[100];
    printf("Ingrese una cadena: ");
    fgets(cadena, sizeof(cadena), stdin);

    cadena[strcspn(cadena, "\n")] = 0;

    if (es_polindromo(cadena)) {
        printf("La cadena es un palindromo.\n");
    } else {
        printf("La cadena no es un palindromo.\n");
    }
    return 0;
}