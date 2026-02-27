#include <stdio.h>
#include <string.h>

int main(){
    char destino[50]="Éste no es un curso de HTML, sino de C.";
    printf( "%s\n", destino );
    strcpy( destino, "Éste es un curso de C." );
    printf( "%s\n", destino );
    return 0;
}