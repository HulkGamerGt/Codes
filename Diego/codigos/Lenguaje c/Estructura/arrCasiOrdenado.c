#include <stdio.h>

#define TAM 4

int main(){

    int arr[TAM]={4,1,2,3};
    int temp;
    
    for(int i= 0; i < TAM-1; i++){
        temp = arr[i+1];
        arr[i+1]=arr[i];
        arr[i]= temp;
    }
    for(int i= 0; i < TAM; i++){
        printf("%d",arr[i]);
    }


    return 0;
}