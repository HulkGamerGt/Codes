/*
    Autor: Diego M. Solis Rojas
    Fecha : 01 / 12 / 2025
    Descripción: Este programa en C que lee un texto en mayúsculas y cuenta la frecuencia 
                 de cada letra del alfabeto.
    Compatible con el standard C89/90.
*/
#include <stdio.h>

#define tam_letras 26

void lectura(char lectura[]); /* Función para leer el texto */
void contador_letras(char lectura[], char letras[], int contador[]); /* Función para contar las letras */
void frec_calcular_mostrar(char letras[], int contador[]); /* Función para encontrar la letra más frecuente y mostrarla */
/* void verificacion_lectura_y_conteo(int contador[], char letras[]);*/ /*Función para verificar la impresión de resultados */

int main(){
    char lec[101]; /* Almacena el texto ingresado */
    char letras[tam_letras+1] =  /* Almacena las letras del alfabeto */
       {'A','B','C','D','E','F','G',
        'H','I','J','K','L','M',
        'N','O','P','Q','R','S',
        'T','U','V','W','X','Y','Z','\0'
       };

    int contador[tam_letras] = {0}; /* Contador de letras */
    lectura(lec);
    contador_letras(lec, letras, contador);
    /*verificacion_lectura_y_conteo(contador, letras);*/
    frec_calcular_mostrar(letras, contador);
    return 0;
}

/* Función para leer el texto */
void lectura(char lectura[]){
    printf("Ingrese su texto en letra MAYUSCULA: ");
    fgets(lectura, 101, stdin);
}

/* Función para contar las letras */
void contador_letras(char lectura[], char letras[], int contador[]) {
    int i = 0, j = 0;
    /* Contar las letras y guardarlas en un arreglo */
    while(lectura[i] != '\0'){
        for(j = 0; j < tam_letras; j++){
            if(lectura[i] == letras[j]){
                contador[j]++;
            }
        }
        i++;
    }
}

/* Función para encontrar la letra más frecuente y mostrarla */
void frec_calcular_mostrar(char letras[], int contador[]){
    int max_frecuencia = 0;
    int i;
    
    /* 1. Encontrar la frecuencia MÁXIMA */
    for(i = 0; i < tam_letras; i++){
        if(contador[i] > max_frecuencia){
            max_frecuencia = contador[i];
        }
    }
    /* Manejar el caso donde no se ingresa ninguna letra */
    if(max_frecuencia == 0){
        printf("No hay ninguna letra en el texto.\n");
        return;
    }
    /* 2. Recorrer de nuevo e imprimir TODAS las letras con esa frecuencia */
    for(i = 0; i < tam_letras; i++){
        if(contador[i] == max_frecuencia){
            printf("%c %d\n", letras[i], max_frecuencia);
        }
    }
}

/*void verificacion_lectura_y_conteo(int contador[], char letras[]){
    printf("Conteo de letras:\n");
    for(int k = 0; k < 26; k++){
        if(contador[k] > 0){
            printf("%c: %d\n", letras[k], contador[k]);
        }
    }
}*/