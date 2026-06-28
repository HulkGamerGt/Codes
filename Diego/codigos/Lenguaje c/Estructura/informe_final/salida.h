#ifndef SALIDA_H
#define SALIDA_H

#include <stdio.h>

/*
 * Imprime el mismo mensaje por consola (stdout) y, si 'archivo' no es NULL,
 * tambien lo escribe en ese archivo. Se usa en todo el programa para que
 * cada ejecucion quede registrada en un archivo de texto (sirve como
 * evidencia de "prueba de ejecucion" para el informe).
 */
void imprimir_doble(FILE *archivo, const char *formato, ...);

#endif
