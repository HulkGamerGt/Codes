#include <stdio.h>

#define MAX 11
#define m 12

int main(){
    int a[MAX]={1,2,3,4,5,6,7,8,9,10,11};
    int buscando = m, inicio = 0, fin = MAX-1, medio, encontrado = 0;
    medio = (inicio + fin) / 2;
    
    while(inicio != fin+1){
        printf("Inicio: %d, Fin: %d, Medio: %d\n", inicio, fin, medio);
        if(a[medio] == buscando){
            encontrado = 1;
            break;
        }
        if(a[medio] < buscando){
            inicio = medio + 1;
        }else{
            fin = medio - 1;
        }
        medio = (inicio + fin) / 2;
    }
    if(encontrado){
        printf("Elpepe %d\n", a[medio]);
    }else{
        printf("No se ha encontrado\n");
    }
    return 0;
}
/*
if( fin == inicio && a[inicio] == buscando ){

}
printf("Elpepe %d\n", a[inicio]);
¨ */