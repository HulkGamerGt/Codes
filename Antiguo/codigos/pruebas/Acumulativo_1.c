#include <stdio.h>
#include <string.h>

/*Funciones prototipos*/
void invertir_cadena(char *cadena);
void vocales(char *cadena);
void es_polindromo(char *cadena);

int main() {
    char texto[30];

    printf("Ingrese una cadena de texto (Max 30 caracteres): ");
    fgets(texto, sizeof(texto), stdin); /* Leer la cadena de texto */
    vocales(texto);
    es_polindromo(texto);
    return 0;
}

/* Función para contar vocales */
void vocales(char *cadena) {
    char vocales[] = "aeiouAEIOU";
    int contador = 0;
    int i, j;

    for (i = 0; cadena[i] != '\0'; i++) {     
        for (j = 0; vocales[j] != '\0'; j++) {
            if (cadena[i] == vocales[j]) {
                contador++;
            }
        }
    }
    printf("Numero de vocales: %d\n", contador);
}

/* Función para verificar si una cadena es un palíndromo */
void es_polindromo(char *cadena){
    char invertida[30];
    
    if (cadena[strlen(cadena) - 1] == '\n') {
        cadena[strlen(cadena) - 1] = '\0';// Eliminar el salto de línea
    }
    strcpy(invertida, cadena);
    invertir_cadena(invertida);
    if (strncmp(cadena, invertida, 30) == 0) {
        printf("La cadena es un palindromo.\n");
    }else{
        printf("La cadena no es un palindromo.\n");
    }
}

/*Funcion para invertir cadena*/
void invertir_cadena(char *cadena){
    int longitud = strlen(cadena);
    int i;
    char temp;

    for (i = 0; i < longitud / 2; i++) {
        temp = cadena[i];// Guardar el caracter actual
        cadena[i] = cadena[longitud - i - 1];// Guardar el caracter de la posicion opuesta
        cadena[longitud - i - 1] = temp;// Intercambiar los caracteres
    }
    printf("La cadena invertida es: %s\n", cadena);
}