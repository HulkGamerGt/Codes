#include <stdio.h>
int main( ){ 
    int expresion, x = 1; 
    expresion = !((1 == x) && 4);
    if (expresion ){ 
        printf("El resultado de la expresión es verdadero"); 
    } 
    else{ printf("El resultado de la expresion es falso"); } 
    x = 4; 
    for( ; x < 10; x += 3){
        printf("%d", x / 2);
    }
    x = 10; 
    do { printf("%d", x--); 
    } while ( x > 5);  
    return 0; 
} 