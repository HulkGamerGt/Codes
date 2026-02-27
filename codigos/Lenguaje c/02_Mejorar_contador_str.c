#include <stdio.h>
#include <string.h>
//TA RARO XDDD NO SE QUE LE FALTA
int main(){
    char texto[20];
    int longitud;
    printf("Dime un nombre: ");
    scanf("%s", texto);
    longitud = strlen(texto);
    printf("%d",longitud);
    return 0;
}