#include <stdio.h>
#include <string.h>

int main() {
    char cadena1[50] = "Hola";
    char cadena2[] = " Mundo";
    char cadena_origen[] = "programacion";
    char cadena_destino[20];
    char cadena_a[] = "abc";
    char cadena_b[] = "abd";

    // strcpy: Copia una cadena a otra.
    strcpy(cadena_destino, cadena_origen); // Ahora, cadena_destino es "programacion"

    // strcat: Concatena dos cadenas.
    strcat(cadena1, cadena2); // Ahora, cadena1 es "Hola Mundo"

    // strcmp: Compara dos cadenas.
    int resultado_comparacion = strcmp(cadena_a, cadena_b); // resultado_comparacion es < 0 porque 'c' < 'd'

    // strlen: Devuelve la longitud de una cadena.
    size_t longitud = strlen(cadena_origen); // longitud es 12

    // strncpy: Copia N caracteres de una cadena.
    strncpy(cadena_destino, cadena_origen, 4); // cadena_destino es "prog" (sin el terminador nulo)

    // strncat: Concatena N caracteres de una cadena.
    strncat(cadena1, " en C", 2); // cadena1 es "Hola Mundo e"

    // strncmp: Compara N caracteres de dos cadenas.
    int resultado_n_comparacion = strncmp(cadena_a, cadena_b, 2); // resultado_n_comparacion es 0 porque 'ab' == 'ab'

    // strchr: Busca un carácter en una cadena.
    char *puntero_a_m = strchr(cadena_origen, 'm'); // puntero_a_m apunta al primer 'm' en "programacion"

    // strstr: Busca una subcadena dentro de una cadena.
    char *puntero_a_prog = strstr(cadena_origen, "gram"); // puntero_a_prog apunta a "gramacion"

    printf("Cadena destino: %s\n", cadena_destino);
    printf("Cadena concatenada: %s\n", cadena1);
    printf("Resultado de comparacion: %d\n", resultado_n_comparacion);
    printf("Longitud de cadena origen: %zu\n", longitud);
    printf("Cadena destino despues de strncpy: %s\n", cadena_destino);
    return 0;
}