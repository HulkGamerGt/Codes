/* Implementacion de la impresion dual (consola + archivo). */

#include "salida.h"

/* Escribe mensaje en stdout y, si archivo no es NULL, tambien lo
   escribe ahi. Permite que toda la salida del programa quede registrada
   simultaneamente en la consola y en el archivo de resultados. */
void imprimir_doble(FILE *archivo, const char *mensaje) {
    if (archivo != NULL) {
        fputs(mensaje, archivo);
    }
    fputs(mensaje, stdout);
}
