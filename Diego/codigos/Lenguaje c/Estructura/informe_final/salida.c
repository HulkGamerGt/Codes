#include <stdarg.h>
#include "salida.h"

void imprimir_doble(FILE *archivo, const char *formato, ...) {
    va_list args_consola, args_archivo;
    va_start(args_consola, formato);
    va_copy(args_archivo, args_consola);

    vprintf(formato, args_consola);
    if (archivo != NULL) {
        vfprintf(archivo, formato, args_archivo);
    }

    va_end(args_consola);
    va_end(args_archivo);
}
