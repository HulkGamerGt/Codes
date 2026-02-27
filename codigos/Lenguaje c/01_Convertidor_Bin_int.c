#include <stdio.h>
#include <string.h>

#define MAX_LONGITUD 32

int obtener_valor_bit(char c) {
    if (c == '1') return 1;
    if (c == '0') return 0;
    return -1;
}

int convertir_Entero_Iterativo(const char *binario) {
    int decimal = 0;
    int longitud = strlen(binario);
    int valor,i;
    int potencia_de_dos = 1;

    for (i = longitud - 1; i >= 0; i--) {
        valor = obtener_valor_bit(binario[i]);

        if (valor == -1) {
            return -1;
        }
        
        if (valor == 1) {
            decimal += potencia_de_dos;
        }
        
        potencia_de_dos *= 2;
    }

    return decimal;
}

int convertir_Entero_Recursivo(const char *binario) {
    int longitud, bit_actual, resultado_restante,i, potencia;
    longitud = strlen(binario);
    
    // Caso Base 1: Cadena vacía
    if (longitud == 0) {
        return 0;
    }

    bit_actual = obtener_valor_bit(binario[0]);

    // Caso Base 2: Error
    if (bit_actual == -1) {
        return -1;
    }

    // Llama recursivamente al resto de la cadena (binario + 1)
    resultado_restante = convertir_Entero_Recursivo(binario + 1);

    // Si hubo un error en las llamadas anidadas, propaga el error
    if (resultado_restante == -1) {
        return -1;
    }

    // Calcula la contribución del bit actual: bit * 2^(posición)
    // El bit actual está en la posición (longitud - 1)
    potencia = 1;
    for (i = 0; i < longitud - 1; i++) {
        potencia *= 2;
    }

    return resultado_restante + bit_actual * potencia;
}

int main() {
    char binario[MAX_LONGITUD + 1];
    int opcion;
    int resultado;

    printf("CONVERSOR BINARIO a ENTERO\n");
    printf("Ingrese el número binario (máx %d bits): ", MAX_LONGITUD);
    
    if (scanf("%32s", binario) != 1) {
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
            resultado = convertir_Entero_Iterativo(binario);
            break;
        case 2:
            resultado = convertir_Entero_Recursivo(binario);
            break;
        default:
            printf("Opción no reconocida.\n");
            return 1;
    }

    printf("Resultado: ");
    if (resultado == -1) {
        printf("Error: La cadena contiene caracteres no binarios o es inválida.\n");
    } else {
        printf("%d\n", resultado);
    }

    return 0;
}