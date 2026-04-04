#include <stdio.h>
#define N 8
int main(){
    int arr[N] = {10,9,2,5,3,7,101,18};
    int lista[N] = {1};
    int guardar[N] = {0};
    int max_lista = 0;
    int max_index = -1;
    
    for(int i = 0; i < N; i++){

        for(int j = 0; j < i; j++){
            if(arr[i] > arr[j] && lista[i] < lista[j] + 1){
                lista[i] = lista[j] + 1;
            }
        }

        if(lista[i] > max_lista){
            max_lista = lista[i];
            max_index = i;
        }
    }

    int buscar = max_lista; 
    printf("Longitud: %d\n", max_lista);
    printf("Secuencia: ");

    int j = N - 1;

    for(int i = max_index; i >= 0 ; i--){
        if(lista[i] == buscar){
            guardar[j] = arr[i];
            buscar--;
        }
        j--;
    }
    for(int i=0 ; i < N; i++){
        if(guardar[i] != 0){
            printf("%d ",guardar[i]);
        }
    }

    return 0;
}