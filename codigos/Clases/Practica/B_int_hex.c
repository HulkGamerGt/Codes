#include <stdio.h>
#include <string.h>

#define MAX_LONGITUD 32

char* enteroAHexIterativo(unsigned int decimal, char *hex) {
    int i = 0,resto,len,j;
    char temp;
    if (decimal == 0) {
        strcpy(hex, "0");
        return hex;
    }
    while (decimal > 0) {
        if (i >= MAX_LONGITUD) return NULL;
        resto = decimal % 16;
        hex[i++] = (resto < 10) ? '0' + resto : 'A' + (resto - 10);
        decimal /= 16;
    }
    hex[i] = '\0';
    // Invertir la cadena
    len = strlen(hex);
    for (j = 0; j < len / 2; j++) {
        temp = hex[j];
        hex[j] = hex[len - 1 - j];
        hex[len - 1 - j] = temp;
    }
    return hex;
}

void enteroAHexRecursivoAux(unsigned int decimal, char *hex) {
    int len, resto;
    if (decimal > 0) {
        enteroAHexRecursivoAux(decimal / 16, hex);
        len = strlen(hex);
        if (len >= MAX_LONGITUD) return;
        resto = decimal % 16;
        hex[len] = (resto < 10) ? '0' + resto : 'A' + (resto - 10);
        hex[len + 1] = '\0';
    }
}

char* enteroAHexRecursivo(unsigned int decimal, char *hex) {
    hex[0] = '\0';
    if (decimal == 0) {
        strcpy(hex, "0");
        return hex;
    }
    enteroAHexRecursivoAux(decimal, hex);
    return hex;
}

int main() {
    unsigned int decimal;
    int opcion;
    char hex[MAX_LONGITUD + 1];
    char *resultado;

    printf("CONVERSOR ENTERO a HEXADECIMAL\n");
    printf("Ingrese el número entero (positivo, máx %u): ", (unsigned int)-1 >> 1);
    if (scanf("%u", &decimal) != 1) {
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
            resultado = enteroAHexIterativo(decimal, hex);
            break;
        case 2:
            resultado = enteroAHexRecursivo(decimal, hex);
            break;
        default:
            printf("Opción no reconocida.\n");
            return 1;
    }

    printf("Resultado: ");
    if (resultado == NULL) {
        printf("Error: El número es demasiado grande.\n");
    } else {
        printf("%s\n", resultado);
    }

    return 0;
}