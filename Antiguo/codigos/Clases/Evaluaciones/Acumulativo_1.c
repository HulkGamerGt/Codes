#include <stdio.h>
#include <string.h>

void invertir_cadena(char *cadena);
void mostrar_longitud_cadena(char *cadena); 
int es_polindromo(char *cadena);
void limpiar_buffer();

int main() {

    char texto[] = "Este es un texto de entrenamiento";
    es_polindromo(texto);
    limpiar_buffer();
    mostrar_longitud_cadena(texto);
    limpiar_buffer();
    invertir_cadena(texto);

    return 0;
}
void limpiar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}   

void mostrar_longitud_cadena(char *cadena) {
    int longitud;
    longitud = strlen(cadena);
    printf("La cadena \"%s\" tiene %i caracteres.\n", cadena, longitud);
}

void invertir_cadena(char *cadena){

    int longitud = strlen(cadena);
    int i;
    char temp;
    for (i = 0; i < longitud / 2; i++) {
        temp = cadena[i];
        cadena[i] = cadena[longitud - i - 1];
        cadena[longitud - i - 1] = temp;
    }
    printf("La cadena invertida es: %s\n", cadena);
}

int es_polindromo(char *cadena){
    int longitud = strlen(cadena);
    int i=0;
    for (i = 0; i < longitud / 2; i++) {
        if (cadena[i] != cadena[longitud - i - 1]) {
            return 0;  
        }
    }
    return 1;
    cadena[strcspn(cadena, "\n")] = 0;

    if (es_polindromo(cadena)) {
        printf("La cadena es un palíndromo.\n");
    } else {
        printf("La cadena no es un palíndromo.\n");
    }
    return 0;
}
