#include <stdio.h>
#include <string.h>

#define MAX_LONGITUD 32

int obtenerValorHex(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return 10 + c - 'A';
    if (c >= 'a' && c <= 'f') return 10 + c - 'a';
    return -1;
}

int hexAEnteroIterativo(const char *hex) {
    int decimal = 0;
    int longitud = strlen(hex);
    int potencia = 1;
    int valor,i;
    for (i = longitud - 1; i >= 0; i--) {
        valor = obtenerValorHex(hex[i]);
        if (valor == -1) return -1;
        decimal += valor * potencia;
        potencia *= 16;
    }
    return decimal;
}

int hexAEnteroRecursivo(const char *hex) {
    int longitud,valor,resto,potencia,i;

    longitud = strlen(hex);
    if (longitud == 0) return 0;
    valor = obtenerValorHex(hex[0]);
    if (valor == -1) return -1;
    resto = hexAEnteroRecursivo(hex + 1);
    if (resto == -1) return -1;
    potencia = 1;
    for (i = 0; i < longitud - 1; i++) {
        potencia *= 16;
    }
    return valor * potencia + resto;
}

int main() {
    char hex[MAX_LONGITUD + 1];
    int opcion;
    int resultado;

    printf("CONVERSOR HEXADECIMAL a ENTERO\n");
    printf("Ingrese el número hexadecimal (máx %d caracteres): ", MAX_LONGITUD);
    if (scanf("%32s", hex) != 1) {
        printf("Error de lectura.\n");
        return 1;
    }

    printf("\nSeleccione el método de conversión:\n");
    printf("1. Método Iterativo\n");
    printf("2. Método Recursivo\n");
    printf("Opción: ");
    if (scanf("%d", &opcion) != 1) {
        printf("Opción inválida.\n");
        return 1;
    }

    switch (opcion) {
        case 1:
            resultado = hexAEnteroIterativo(hex);
            break;
        case 2:
            resultado = hexAEnteroRecursivo(hex);
            break;
        default:
            printf("Opción no reconocida.\n");
            return 1;
    }

    printf("Resultado: ");
    if (resultado == -1) {
        printf("Error: La cadena contiene caracteres no hexadecimales.\n");
    } else {
        printf("%d\n", resultado);
    }

    return 0;
}