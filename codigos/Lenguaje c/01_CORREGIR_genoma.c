#include <stdio.h>
#include <string.h>
#define M 100

//LOS GENOMAS USAR STRUCTUR AL FINALIZAR EL CODIGO MODIFICARLO

typedef struct genoma {
    char name[50];
    int age;
}GENOMA;

void abridor_archivo_gestor_funciones(int *, char []);
void leer_num_genoma(int *, FILE * );
void leer_letras_genoma(int *, FILE *, char []);
void analizador_genoma(int , char [], char [][M], int [][M]);
//void mostrador_new_genoma(char []);

void abridor_archivo_gestor_funciones(int *n,char genoma[]){
    FILE *archivo = fopen("genoma.txt","r");
    if(archivo == NULL){
        printf("Error al abrir el archivo");
    }
    leer_num_genoma(n,archivo);
    leer_letras_genoma(n,archivo,genoma);
    fclose(archivo);
}
int main(){
    int n;
    char genoma[M];
    int temp_genoma[M][M];
    char new_genoma[M][M];
    abridor_archivo_gestor_funciones(&n, genoma);
    analizador_genoma(n, genoma, new_genoma, temp_genoma);
    //mostrador_new_genoma(new_genoma);
    return 0;
}
void leer_num_genoma(int *n,FILE *archivo){
    if(fscanf(archivo,"%d",n) == 1){
        if(*n >= 1 && *n < 100 ){
            printf("El numero de genoma que hay es: %d\n",*n); 
            fgetc(archivo);
        }
        else printf("Rango de numeros no compatible.\n");
    }else
        printf("No hay num, solo caracteres");
}

void leer_letras_genoma(int *n, FILE *archivo, char genoma[]){
    int i=0, j=0;
    if(*n == 0) return;
    while(fscanf(archivo,"%c",&genoma[i]) == 1){
        i++;
    }
    printf("------ Este es el conjunto de genomas ------");
    while(j < i){
        printf("%c",genoma[j]);
        j++;
    }
}

void analizador_genoma(int n, char genoma[], char new_genoma[][M], int temp_genoma[M][M]){
    int i=0, j=10;
    int letras;
    FILE *Salida = fopen("salida.txt","w");
    if(Salida == NULL) printf("ERROR");

    while(fprintf(Salida,&genoma[i]) == 1){
        i++;
    }

    for(i =0; i < n; i++ ){
        (sscanf(genoma[i], "%d", &letras) == 1);
        while(letras != 0){
            temp_genoma[i][j] = letras % 100;
            letras = (letras/100);
            j--;
        }
        
    }

    // longitud = 0;

    // Recorrer el arreglo desde el índice 0 hasta longitud - 1
    // e imprimir cada caracter seguido de un espacio.
    /*for (int i = 0; i < longitud; i++) {
        longitud = strlen(genoma[i]);
        for(int k=0; k < longitud){
            printf("%c ", new_genoma[i][k]);
        }
        
    }*/

    /*
    char temp[MAX_NOMBRES];
    strcpy(temp, genoma[i]);
    strcpy(genoma[i], genoma[i+1]);
    strcpy(genoma[i+1], temp);
    */
/*
    */
    fclose(Salida);
}
/*
void mostrador_new_genoma(char new_genoma []){

}*/