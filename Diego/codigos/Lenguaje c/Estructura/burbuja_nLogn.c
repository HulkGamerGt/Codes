#include <stdio.h>

// Función para ajustar un subárbol con raíz en el índice 'i'
void heapify(int arr[], int n, int i) {
    int largest = i;       // Inicializar el más grande como la raíz
    int left = 2 * i + 1;  // Izquierda = 2*i + 1
    int right = 2 * i + 2; // Derecha = 2*i + 2

    // Si el hijo izquierdo es más grande que la raíz
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // Si el hijo derecho es más grande que el que ahora es el más grande
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // Si el más grande no es la raíz, intercambiar y seguir ajustando
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        // Recursivamente ajustar el subárbol afectado
        heapify(arr, n, largest);
    }
}

// Función principal de Heap Sort
void heapSort(int arr[], int n) {
    // 1. Construir el montículo (reorganizar el arreglo)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // 2. Extraer elementos del montículo uno por uno
    for (int i = n - 1; i > 0; i--) {
        // Mover la raíz actual (el más grande) al final
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // Llamar a heapify en el montículo reducido
        heapify(arr, i, 0);
    }
}

int main() {
    int data[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(data) / sizeof(data[0]);

    heapSort(data, n);

    printf("Arreglo ordenado: \n");
    for (int i = 0; i < n; i++)
        printf("%d ", data[i]);
    printf("\n");

    return 0;
}