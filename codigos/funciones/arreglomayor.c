#include <stdio.h>
/*crear una funcion que se pueda ingresar valores qeu el usuario a un arreglo y devuelva el numeor mayor de ese arreglo*/
int encontrarMayor(int arreglo[], int tam) {
    int mayor = arreglo[0];
    int i;
    for (i = 1; i < tam; i++) {
        if (arreglo[i] > mayor) {
            mayor = arreglo[i];
        }
    }
    return mayor;
}
int main() {
    int arreglo = 0;
    int i;
    printf("ingrese la cantidad del arreglo ");
    scanf("%d", &arreglo);
    int numeros[arreglo];
    for (i = 0; i < arreglo; i++) {
        printf("Ingrese un numero: ");
        scanf("%d", &numeros[i]);
    }
    int mayor = encontrarMayor(numeros, arreglo);
    printf("El numero mayor es: %d\n", mayor);
    return 0;
}
