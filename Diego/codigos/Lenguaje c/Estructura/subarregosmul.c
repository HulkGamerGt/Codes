#include <stdio.h>
#include <stdlib.h>

#define TAM 5
#define MAX_VENTANA 4
#define MIN_VENTANA 1

typedef struct {
    int suma_maxima; // Representará el producto máximo
    int inicio;
    int fin;
    int tamano_sub;
} RESULTADO;

int main() {
    int arr[TAM] = {1, 2, 3, 4, 6};
    
    // Inicializamos con el primer elemento
    RESULTADO mejor = {arr[0], 0, 0, 1};
    
    // 1. Probamos cada tamaño posible (v) de sub-arreglo
    for(int v = MIN_VENTANA; v <= MAX_VENTANA; v++){
        
        // 2. Deslizamos la ventana 'v' a lo largo del arreglo
        for(int i = 0; i <= TAM - v; i++){
            // CAMBIO: Para multiplicación, el acumulador debe empezar en 1
            int producto_actual = 1;

            // 3. Calculamos la MULTIPLICACIÓN del sub-arreglo actual
            for(int k = 0; k < v; k++){
                producto_actual *= arr[i + k]; // Operador de multiplicación
            }

            // 4. Comparación de productos
            if(producto_actual > mejor.suma_maxima){
                mejor.suma_maxima = producto_actual;
                mejor.inicio = i;
                mejor.fin = i + v - 1;
                mejor.tamano_sub = v;
            }
        }
    }

    // Mantenemos tus print originales
    printf("Suma Maxima Encontrada: %d\n", mejor.suma_maxima);
    printf("Tamaño del sub-arreglo: %d\n", mejor.tamano_sub);
    printf("Rango de indices:       [%d] hasta [%d]\n", mejor.inicio, mejor.fin);
    printf("Elementos:              ");
    
    for(int i = mejor.inicio; i <= mejor.fin; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}