/* Funcion de impresion dual: escribe en consola y en archivo.
   El formateo se hace con snprintf antes de llamar a esta funcion. */

#ifndef SALIDA_H
#define SALIDA_H

#include <stdio.h>

/* Escribe mensaje en stdout, y tambien en archivo si este no es NULL. */
void imprimir_doble(FILE *archivo, const char *mensaje);

#endif /* SALIDA_H */
