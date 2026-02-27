// no se como se hace

#include <stdio.h>

void darvuelta();
/*void limpiar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        
    }
}   */

int main ()
{
    darvuelta();
}
void darvuelta()
{
    char cad1[ ] = "reconocer"; 
    printf("%s\n", strrev(cad1)); 

}