#include <stdio.h>

 int main () {

    int i;
    int num = 5;
    int numeros[100];

    num = 34;
    numeros[6] = num;
    
    for(int i = 0 ; i < 100; i++){

        numeros[i]= num;
        printf("%d\n",numeros[i]);
        
    }
    return 0;

 }

