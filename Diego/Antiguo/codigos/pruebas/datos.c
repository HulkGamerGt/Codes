/*recibir datos */
#include <stdio.h>

int pregunta();
int caso(int numero1, int numero2);
int suma(int numero1, int numero2);
int resta(int numero1, int numero2);
int multiplicacion(int numero1, int numero2);

int main() {
    int numero1, numero2;
    // Llamada a pregunta, que ahora devuelve los números leídos.
    pregunta(&numero1, &numero2);
    caso(numero1, numero2);
    return 0;
}

// La funcion pregunta ahora pide los números y los asigna a las variables
// pasadas por referencia (con punteros).
int pregunta(int *numero1, int *numero2) {
    printf("Dime 2 numeros enteros \n");

    printf("Dime el numero 1: ");
    scanf("%d", numero1);
    printf("Dime el numero 2: ");
    scanf("%d", numero2);
}

int caso(int numero1, int numero2) {
    int opcion;

    printf("Elige tu opcion :\n");
    printf("1. Sumar\n");
    printf("2. Restar\n");
    printf("3. Multiplicar\n");
    scanf("%d", &opcion);

    if (opcion == 1) {
        suma(numero1, numero2);
    } else if (opcion == 2) {
        resta(numero1, numero2);
    } else if (opcion == 3) {
        multiplicacion(numero1, numero2); // Corregido el nombre de la función
    }
}

int suma(int numero1, int numero2) {
    int resultado;
    resultado = numero1 + numero2;
    printf("Resultado de la suma           : %d\n", resultado);
    return resultado;
}

int resta(int numero1, int numero2) {
    int resultado;
    resultado = numero1 - numero2;
    printf("Resultado de la resta          : %d\n", resultado);
    return resultado;
}

int multiplicacion(int numero1, int numero2) {
    int resultado;
    resultado = numero1 * numero2;
    printf("Resultado de la multiplicacion : %d\n", resultado);
    return resultado;
}