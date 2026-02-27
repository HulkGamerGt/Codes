#include <stdio.h>
#include <string.h>
//Este programa ordena texto desde las letras A a la Z dependiendo del texto que ingrese el usuario, con una funcion que ordena y con otra que el texto se almacena, sin size_t

void Texto(char *texto){

    int len;
    printf("Ingrese un texto: ");
    fgets(texto, 100, stdin);
    // Eliminar el salto de línea al final de la cadena
    len = strlen(texto);
    if (len > 0 && texto[len - 1] == '\n') {
        texto[len - 1] = '\0';
    }
}
void ordenar(char *texto){
    int i, j;
    char temp;

    // Ordenar el texto
    for (i = 0; i < strlen(texto) - 1; i++) {
        for (j = i + 1; j < strlen(texto); j++) {
            if (texto[i] > texto[j]) {
                temp = texto[i];
                texto[i] = texto[j];
                texto[j] = temp;
            }
        }
    }
}

int main() {
    char texto[100];
    Texto(texto);
    ordenar(texto);
    printf("Texto ordenado: %s\n", texto);
    return 0;
}