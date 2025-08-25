#include <stdio.h>
#include <string.h>

int pregunta(char *);
void Frecuencia(char *, int);

int main(){
    int Longitud;
    char texto[2000];
    Longitud = pregunta(texto);
    Frecuencia(texto, Longitud);
    return 0;
}

int pregunta(char *texto){

    int Longitud;
    printf("Ingrese un texto de maximo 2000 caracteres: ");
    fgets(texto, 2000, stdin);
    Longitud = strlen(texto);
    return Longitud;
}

void Frecuencia(char *texto, int Longitud){
    int i, j=0;
    char caracter;
    printf("Indique el caracter a investigar: ");
    scanf("%c", &caracter);

    for(i = 0; i < Longitud; i++){
        if(texto[i] == caracter){
            j++;
        }
    }
    printf("En el texto %c, la letra %c aparece %d veces.\n", texto[0], caracter, j);
}