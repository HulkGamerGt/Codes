#include <stdio.h>
#include <string.h>

int main(){

    char alfabet[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 
    'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 
    'Y', 'Z', ' ', '0', '1', '2', '3', '4', '5', '6', '7', '8', 
    '9', '!', ',', '.', ':', ';', '?', '-', '+', '*', '/'} ;

    for(int i = 0; i < sizeof(alfabet); i++){
        printf("%d,%c ",i, alfabet[i]);
        printf("\n");
    }
    printf("\n\n");
    char alfabeto[100];
    inicializa_alfabeto(alfabeto);


    return 0;
}
void inicializa_alfabeto(char *alfabeto) {
    strcpy(alfabeto, "ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789!,.:;?-+*/");

    for (int i = 0; i < strlen(alfabeto); i++) {
        printf("%d,%c ",i, alfabeto[i]);
        printf("\n");
    }
}