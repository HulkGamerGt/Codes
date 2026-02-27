#include<stdio.h>
#include<string.h>

void muestra_linea(char []);
void inicializa(int [], int);
void muestra_frec(int [], int);
void analisis(char [], int []);

int main(){
    char linea[50];
    int frec[256];// arreglo de contadores de caracteres
    printf("Texto: ");
    fgets(linea, sizeof(linea), stdin);
    inicializa(frec, 256);
    analisis(linea, frec);
    muestra_frec(frec, 256);
    return 0;
}

void muestra_linea(char linea[]){
    printf("%s\n", linea);
}

void inicializa(int frec[], int cant){
    int i;
    for (i = 0; i < cant; i++){
        frec[i] = 0;
    }
}

void muestra_frec(int frec[], int cant){
    //int new_frec[cant];
    int bidi[cant][2];
    int i;
    //char val_caracter[cant];
    for (i = 32; i < cant; i++){
        if(frec[i] != 0){
            /*new_frec[i] = frec[i];
            val_caracter[i] = (char)i;*/
            bidi[i][0]=(char)i;
            bidi[i][1]= frec[i];

            if(bidi[i][1] > 1){
                printf(" *%c* aparece %d veces en el texto\n", bidi[i][0], bidi[i][1]);
            }
            else{
                printf(" *%c* aparece %d vez en el texto\n", bidi[i][0], bidi[i][1]);
            }
            /*
            if(new_frec[i] > 1){
                printf(" *%c* aparece %d veces en el texto\n", val_caracter[i], new_frec[i]);
            }
            else{
                printf(" *%c* aparece %d vez en el texto\n", val_caracter[i], new_frec[i]);
            }*/
        }
        //j++;
    }
}

void analisis(char linea[], int frec[]){
    int tam,i;
    tam = strlen(linea);
    for (i = 0; i < tam; i++){
        frec[linea[i]] += 1;
    }
}