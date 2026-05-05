#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i;
    int *vector_1, *vector_2, *vector_resultante;

    printf("Ingrese el tamaño de los vectores: ");
    scanf("%d", &n);

    vector_1 = (int *)malloc(n * sizeof(int));
    vector_2 = (int *)malloc(n * sizeof(int));
    vector_resultante  = (int *)malloc(n * sizeof(int));

    if (vector_1 == NULL || vector_2 == NULL || vector_resultante == NULL) {
        printf("Error: problema en la memoria.\n");
        return 1;
    }

    printf("\n Ingreso de datos para el Vector 1 \n");
    for (i = 0; i < n; i++) {
        printf("Vector 1 [%d]: ", i);
        scanf("%d", &vector_1[i]);
    }

    printf("\n Ingreso de datos para el Vector 2 \n");
    for (i = 0; i < n; i++) {
        printf("Vector 2 [%d]: ", i);
        scanf("%d", &vector_2[i]);
    }

    for (i = 0; i < n; i++) {
        vector_resultante[i] = vector_1[i] + vector_2[i];
    }

    printf("\n--- Resultados ---\n");
    printf("V1\tV2\tSuma\n");
    printf("--------------------\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\n", vector_1[i], vector_2[i], vector_resultante[i]);
    }

    free(vector_1);
    free(vector_2);
    free(vector_resultante);

    return 0;
}