#include <stdio.h>

int main(){
    int arreglo[9999999999999];
    arreglo[0] = 1;
    arreglo[1] = 2;
    arreglo[2] = 3;

    for(int i = 0; i < 3; i++){
        printf(" %d", arreglo[i]);

    }
    return 0;
}