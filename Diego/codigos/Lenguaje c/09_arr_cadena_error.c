#include <stdio.h>
#include <string.h>
int error( int num_err ){
char *errores[] = {
    "No se ha producido ningún error",
    "No hay suficiente memoria",
    "No hay espacio en disco",
    "Me he cansado de trabajar"
};
printf( "Error número %i: %s.\n", num_err,errores[num_err]);
exit( -1 );
}
int main(){
error( 2 );
}