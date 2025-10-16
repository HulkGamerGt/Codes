#include <stdio.h>
#include <string.h>
#define M 100

void abridor_archivo_gestor_funciones(int *, char []);
void leer_num_genoma(int *, FILE * );
void leer_letras_genoma(int *, FILE *, char []);

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
    abridor_archivo_gestor_funciones(&n, genoma);
    printf("%d",n);
    return 0;
}
void leer_num_genoma(int *n,FILE *archivo){
    if(fscanf(archivo,"%d",n) == 1){
        if(*n >= 1 && *n < 100 )
            printf("El numero de genoma que hay es: %d\n",*n);    
        else printf("Rango de numeros no compatible.\n");
    }else
        printf("No hay num, solo caracteres");
}

void leer_letras_genoma(int *n, FILE *archivo, char genoma[]){

    for(int i=0; i < *n; i++){
        for(int m=0; m < *n; m++){
            fgets(((genoma + m)+i),*n,archivo);
        }
    }
    for(int j=0; j < *n; j++){
        for(int k=0; k < *n; k++){
            printf("%c", *(((genoma + k)+j))+);
        }
    }
}