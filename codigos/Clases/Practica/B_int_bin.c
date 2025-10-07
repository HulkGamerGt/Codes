#include <stdio.h>
#include <string.h>

#define MAX_LONGITUD 32

char* convertirABinarioIterativo(unsigned int decimal, char *binario) {
    int i = 0, len, j;
    char temp;
    if (decimal == 0) {
        strcpy(binario, "0");
        return binario;
    }
    
    while (decimal > 0) {
        if (i >= MAX_LONGITUD) {
            return NULL; // Número demasiado grande
        }
        binario[i++] = '0' + (decimal % 2);
        decimal /= 2;
    }
    
    binario[i] = '\0';
    
    // Invertir la cadena
    len = strlen(binario);
    for (j = 0; j < len / 2; j++) {
        temp = binario[j];
        binario[j] = binario[len - 1 - j];
        binario[len - 1 - j] = temp;
    }
    
    return binario;
}

void convertirABinarioRecursivoAux(unsigned int decimal, char *binario) {
    int len, resto;
    if (decimal > 0) {
        convertirABinarioRecursivoAux(decimal / 2, binario);
        len = strlen(binario);
        if (len >= MAX_LONGITUD) {
            return; // Ignorar, pero en práctica asumir que cabe
        }
        binario[len] = '0' + (decimal % 2);
        binario[len + 1] = '\0';
    }
}

char* convertirABinarioRecursivo(unsigned int decimal, char *binario) {
    binario[0] = '\0';
    
    if (decimal == 0) {
        strcpy(binario, "0");
        return binario;
    }
    
    convertirABinarioRecursivoAux(decimal, binario);
    return binario;
}

int main() {
    unsigned int decimal;
    int opcion;
    char binario[MAX_LONGITUD + 1];
    char *resultado;

    printf("CONVERSOR ENTERO a BINARIO\n");
    printf("Ingrese el número entero: ");
    
    if (scanf("%d", &decimal) != 1) {
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
            resultado = convertirABinarioIterativo(decimal, binario);
            break;
        case 2:
            resultado = convertirABinarioRecursivo(decimal, binario);
            break;
        default:
            printf("Opción no reconocida.\n");
            return 1;
    }

    printf("Resultado: ");
    if (resultado == NULL) {
        printf("Error: El número es demasiado grande o inválido.\n");
    } else {
        printf("%s\n", resultado);
    }

    return 0;
}