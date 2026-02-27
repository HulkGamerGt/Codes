/*
 Este programa invierte la primera palabra y mueve el primer
 carácter de la segunda palabra al final para cada par de palabras
 de una oración.
*/

#include <stdio.h>
#include <string.h>

#define TAM_MAX 9999

// Prototipos de funciones
void procesar_oracion(char *oracion);
void invertir_palabra(char *palabra);
void modificar_palabra(char *palabra);
char *obtener_siguiente_palabra(char **str);

int main() {
    char oracion[TAM_MAX];

    printf("Ingrese su texto: ");
    fgets(oracion, TAM_MAX, stdin);

    // Elimina el salto de línea que agrega fgets
    oracion[strcspn(oracion, "\n")] = '\0';

    procesar_oracion(oracion);

    printf("Texto modificado: %s\n", oracion);

    return 0;
}

/*
 Procesa toda la oracion, modificando cada par de palabras.
 oracion La oracion a procesar.
 */
void procesar_oracion(char *oracion) {
    char *palabra1, *palabra2;
    char oracion_temp[TAM_MAX];
    char *p_original = oracion;
    char *p_nueva = oracion_temp;

    // Copia la oracion a un buffer temporal para manipularla de forma segura
    strcpy(oracion_temp, oracion);

    while (1) {
        palabra1 = obtener_siguiente_palabra(&p_original);
        //if (!palabra1) break; // Fin de la oracion

        palabra2 = obtener_siguiente_palabra(&p_original);

        // Si se encuentra una segunda palabra, se aplican las modificaciones
        if (palabra2) {
            invertir_palabra(palabra1);
            modificar_palabra(palabra2);

            // Se reescribe la oracion con las palabras modificadas
            strcpy(p_nueva, palabra1);
            p_nueva += strlen(palabra1);
            *p_nueva++ = ' ';
            strcpy(p_nueva, palabra2);
            p_nueva += strlen(palabra2);
            *p_nueva++ = ' ';
        } else {
            // Si solo queda una palabra, se copia tal como esta
            strcpy(p_nueva, palabra1);
            p_nueva += strlen(palabra1);
            break; // Fin de la oracion
        }
    }

    *p_nueva = '\0';
    strcpy(oracion, oracion_temp);
}

/*
 Invierte los caracteres de una palabra.
 palabra La palabra a invertir.
 */
void invertir_palabra(char *palabra) {
    int i, len;
    char temp;

    len = strlen(palabra);
    for (i = 0; i < len / 2; i++) {
        temp = palabra[i];
        palabra[i] = palabra[len - 1 - i];
        palabra[len - 1 - i] = temp;
    }
}

/*
 Mueve el primer caracter de una palabra al final.
 palabra La palabra a modificar.
 */
void modificar_palabra(char *palabra) {
    int len = strlen(palabra);
    char primer_caracter;

    if (len <= 1) return;

    primer_caracter = palabra[0];
    memmove(palabra, palabra + 1, len - 1);
    palabra[len - 1] = primer_caracter;
    palabra[len] = '\0';
}

/*
   Extrae la siguiente palabra de una cadena, manejando los espacios.
   str Puntero al puntero de la cadena.
   Puntero a la siguiente palabra encontrada.
 */
char *obtener_siguiente_palabra(char **str) {
    char *inicio;

    // Avanza el puntero para saltar espacios iniciales
    while (**str == ' ' && **str != '\0') {
        (*str)++;
    }

    if (**str == '\0') {
        return NULL;
    }

    inicio = *str;

    // Encuentra el final de la palabra (el siguiente espacio o el final de la cadena)
    while (**str != ' ' && **str != '\0') {
        (*str)++;
    }

    // Se "corta" la palabra para tratarla como una cadena separada
    if (**str != '\0') {
        **str = '\0';
        (*str)++;
    }

    return inicio;
}