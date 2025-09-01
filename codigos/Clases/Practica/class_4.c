#include<stdio.h>
#include<string.h>

//mejorar a 2 arregos, uno para letras y otro para la frecuencia
// o dejarlo en uno bidimensional

void muestra_linea(char []);
void inicializa(int [], int);
void muestra_frec(int [], int);
void analisis(char [], int [], int);

int main(){
    char linea[50];
    int frec[256];// arreglo de contadores de caracteres
    printf("Texto: ");
    fgets(linea, sizeof(linea), stdin);
    inicializa(frec, 256);
    analisis(linea, frec, 256);
    muestra_frec(frec, 256);
    return 0;
}

void muestra_linea(char linea[]){
    printf("%s\n", linea);
}

void inicializa(int frec[], int cant){
    for (int i = 0; i < cant; i++){
        frec[i] = 0;
    }
}

void muestra_frec(int frec[], int cant){
    int new_frec[cant];
    char val_caracter[cant];
    for (int i = 0; i < cant; i++){
        if(frec[i] != 0 && i > 31){
            new_frec[i] = frec[i];
            val_caracter[i] = (char)i;
            if(new_frec[i] > 1){
                printf(" *%c* aparece %d veces en el texto\n", val_caracter[i], new_frec[i]);
            }
            else{
                printf(" *%c* aparece %d vez en el texto\n", val_caracter[i], new_frec[i]);
            }
        }
    }
}

void analisis(char linea[], int frec[], int cant){
    int tam;
    tam = strlen(linea);
    for (int i = 0; i < tam; i++){
        frec[linea[i]] += 1;
    }
}