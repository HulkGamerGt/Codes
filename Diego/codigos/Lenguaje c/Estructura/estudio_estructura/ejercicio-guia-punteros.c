/*3. Punteros y Strings:
Escriba una función en C llamada contarVocales(char *s) que reciba un puntero a
una cadena de texto y devuelva la can�dad de vocales minúsculas que con�ene,
u�lizando solo aritmé�ca de punteros (sin usar [ ] ).
*/

#include <stdio.h>
#include <string.h>

int contarVocales(char *s);

int main(){

    char arr[] ={"pendejo"};
    int vocales;
    vocales = contarVocales(arr);

    printf("La cantidad de vocales es de : %d ", vocales);

    return 0;
}

int contarVocales(char *s){

    int contador = 0;
    while(*s !='\0'){
        if(strchr("aeiouAEIOU", *s) != NULL){
            contador++;
        }
        s++;
    }
    return contador;
}