#include <stdio.h>

int eliminarDuplicados(int *arr, int n);
void mostrarArreglo(int *arr, int n);

int main() {
    int TAM = -1;

    printf("Ingrese la cantidad de elementos: ");
    scanf("%d", &TAM);

    if (TAM <= 0) {
        printf("El tamano del arreglo no es valido\n");
        return 0;
    }

    int arr[TAM];

    for (int i = 0; i < TAM; i++) {
        printf("Ingrese el valor [%d]: ", i + 1);
        scanf("%d", (arr + i));
    }

    int nuevoTAM = eliminarDuplicados(arr, TAM);

    printf("\nArreglo sin duplicados:\n");
    mostrarArreglo(arr, nuevoTAM);

    return 0;
}

int eliminarDuplicados(int *arr, int n) {
    if (n == 0) return 0;

    int nuevoTam = 0;

    for (int i = 0; i < n; i++) {
        int esDuplicado = 0;

        for (int j = 0; j < nuevoTam; j++) {
            if (*(arr + i) == *(arr + j)) {
                esDuplicado = 1;
                break;
            }
        }

        if (!esDuplicado) {
            *(arr + nuevoTam) = *(arr + i);
            nuevoTam++;
        }
    }

    return nuevoTam;
}

void mostrarArreglo(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", *(arr + i));
    }
    printf("\nNuevo tamano: %d\n", n);
}