#include <stdio.h>
#include <string.h>

int main(){
    char cadena[]="El puerto paralelo del PC";
    char *p;
    int espacios = 0, letras_e = 0, letras_a = 0;

    p = cadena;

    while (*p != '\0') {
        if (*p == ' ') espacios++;
        if (*p == 'e' || *p == 'E') letras_e++;
        if (*p == 'a') letras_a++;
        p++;
    }
    printf( "En la cadena \"%s\" hay:\n", cadena );
    printf( " %i espacios\n", espacios );
    printf( " %i letras e\n", letras_e );
    printf( " %i letras a\n", letras_a );
    return 0;
}
