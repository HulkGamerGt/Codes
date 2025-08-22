#include <stdio.h>
#include <string.h>

int main() {
    char texto[] = "Éste es un curso de C.";
    char destino[50];
    strcpy(destino, texto);
    printf("Valor final: %s\n", destino);
    return 0;
}