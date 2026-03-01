#include <stdio.h>

void encontrarMayor(int arreglo[], int tam) {

    for (int i = tam; i > 0 ; i--) {

        printf("Invertido : %d\n",arreglo[i-1]);
        
    }

}
int main() {
    int n;
    printf("ingrese la cantidad del arreglo ");
    scanf("%d", &n);
    int numeros[n];
    for (int i = 0; i < n; i++) {
        printf("Ingrese un numero: ");
        scanf("%d", &numeros[i]);
    }
    encontrarMayor(numeros, n);

    return 0;
}