/*
    Invierte la primera palabra y mueve el primer
    carácter de la segunda palabra al final.
*/

#include <stdio.h>
#include <string.h>

#define TAM 9999

// Prototipos de funciones
void inicializacion(char []);
void obtener_texto(char []);
void procesar_texto(char []);
void invertir_palabra(char [], char [], int);
void modificar_palabra(char [], char []);
void reconstruir_oracion(char [], char [], char [], char []);

int main() {
    char pig[TAM];

    inicializacion(pig);
    obtener_texto(pig);
    procesar_texto(pig);

    return 0;
}

// Inicializa el array con ceros para asegurar que no haya basura.
void inicializacion(char pig[]) {
    memset(pig, 0, TAM); // Llena el array con ceros
}

// Solicita al usuario que ingrese texto y lo limpia.
void obtener_texto(char pig[]) {
    int tamano;

    printf("Ingrese su texto: ");
    fgets(pig, TAM, stdin); // Lee el texto ingresado por el usuario

    // Elimina el salto de línea que agrega fgets
    tamano = strlen(pig);
    if (pig[tamano - 1] == '\n') { // Elimina el salto de línea
        pig[tamano - 1] = '\0';
    }
}

// Analiza el texto y coordina las modificaciones.
void procesar_texto(char pig[]) {
    int i, j;
    int inicioPrimera, finPrimera;
    int inicioSegunda, finSegunda;
    int tamano;
    
    char primeraPalabra[TAM];
    char palabraInvertida[TAM];
    char segundaPalabra[TAM];
    char palabraModificada[TAM];
    char oracionFinal[TAM];
    
    tamano = strlen(pig);
    inicioPrimera = 0;
    finPrimera = 0;
    
    // Encuentra el final de la primera palabra (el primer espacio)
    for (i = 0; i < tamano; i++) { 
        if (pig[i] == ' ') {
            finPrimera = i;
            break;
        }
    }

    // Si no se encuentra un espacio, no hay segunda palabra.
    if (i == tamano) {
        printf("El texto no tiene dos palabras: %s\n", pig);
        return;
    }

    // Encuentra el inicio y fin de la segunda palabra
    inicioSegunda = i + 1;
    finSegunda = tamano;
    for (j = inicioSegunda; j < tamano; j++) {
        if (pig[j] == ' ') {
            finSegunda = j;
            break;
        }
    }

    // Copia y procesa la primera palabra
    strncpy(primeraPalabra, pig, finPrimera);
    primeraPalabra[finPrimera] = '\0';// Termina la cadena
    invertir_palabra(primeraPalabra, palabraInvertida, finPrimera);// Invierte la primera palabra

    // Copia y procesa la segunda palabra
    strncpy(segundaPalabra, pig + inicioSegunda, finSegunda - inicioSegunda);
    segundaPalabra[finSegunda - inicioSegunda] = '\0';// Termina la cadena
    modificar_palabra(segundaPalabra, palabraModificada);
    
    // Reconstruye la oración completa
    reconstruir_oracion(oracionFinal, palabraInvertida, palabraModificada, pig + finSegunda);

    printf("Texto original: %s\n", pig);
    printf("Texto modificado: %s\n", oracionFinal);
}

// Invierte una palabra.
void invertir_palabra(char original[], char invertida[], int largo) {
    int i;
    for (i = 0; i < largo; i++) {
        invertida[i] = original[largo - 1 - i];
    }
    invertida[largo] = '\0';
}

// Mueve el primer carácter de una palabra al final.
void modificar_palabra(char original[], char modificada[]) {
    char primerChar;
    int tamanoModificada;

    primerChar = original[0];
    strcpy(modificada, original + 1);// Copia la parte de la cadena sin el primer carácter

    tamanoModificada = strlen(modificada);
    modificada[tamanoModificada] = primerChar;
    modificada[tamanoModificada + 1] = '\0';
}

// Reconstruye la oración con las palabras modificadas
void reconstruir_oracion(char destino[], char primera[], char segunda[], char resto[]) {
    strcpy(destino, primera);
    strcat(destino, " ");
    strcat(destino, segunda);

    if (strlen(resto) > 0) {// Agrega el resto de la oración si existe
        strcat(destino, resto);
    }
}