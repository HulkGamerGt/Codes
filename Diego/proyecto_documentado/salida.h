/* Funcion de impresion dual: escribe en consola y, opcionalmente, en archivo.
 * No usa printf ni argumentos variables (stdarg.h); el formateo se hace
 * con snprintf antes de llamar a esta funcion. */

#ifndef SALIDA_H
#define SALIDA_H

#include <stdio.h>

/* Escribe mensaje en stdout, y tambien en archivo si este no es NULL. */
void imprimir_doble(FILE *archivo, const char *mensaje);

#endif /* SALIDA_H */
