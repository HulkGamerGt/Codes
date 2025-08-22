/*
* Ejemplo de uso de do while
* Autor: Luis Ponce Rosales 
Escribir un programa que lea sucesivamente números desde el teclado, hasta que
aparezca un número comprendido entre 1 y 5. Desarrollar el algoritmo usando las
funciones:
a) getchar( )
b) scanf ( )

*/
#include <stdio.h>

void limpiar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        
    }
}   
int main() {

int n = 0;
 
    do
    {
       printf("Ingrese un número entre 1 y 5: \n");
       scanf("%d", &n);
       limpiar_buffer(); 
     
    } while (n <= 1 ||  n >= 5);
    printf("Número válido ingresado: %d\n", n); 
    printf("Fin del programa.\n");
 return 0;
}