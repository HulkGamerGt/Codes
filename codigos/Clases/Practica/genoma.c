#include <stdio.h>
#include <string.h>
#define 

char leer_archivo(int , char *);

int main(){
    int n;
    char *genoma;
    leer_archivo(&n, genoma);

    return 0;
}
char leer_archivo(int n, char *genoma){
    FILE *archivo = fopen("genoma.txt","r");
    if(archivo != NULL){
        printf("Error al abrir el archivo");
    }

    if(fgets(,,))
    fclose(archivo);
    return ;
}