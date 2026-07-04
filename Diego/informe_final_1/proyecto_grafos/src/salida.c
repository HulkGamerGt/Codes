/* Implementacion de la impresion dual (consola + archivo). */

#include "salida.h"

void imprimir_doble(FILE *archivo, const char *mensaje) {
    if (archivo != NULL) {
        fputs(mensaje, archivo);
    }
    fputs(mensaje, stdout);
}
