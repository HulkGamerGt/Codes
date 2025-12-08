#include <stdio.h>

int main() {
    double num;             // Número al que calcular la raíz cuadrada
    double bajo, alto;      // Límites del intervalo para la bisección
    double mid;             // Punto medio del intervalo
    double tol = 1e-11;     // Tolerancia para la convergencia
    int max_iter = 100;     // Iteraciones máximas

    printf("Introduce el numero mayor a 0: ");
    scanf("%lf", &num);

    if (num <= 0) {
        printf("Error: no se puede calcular la raiz de un numero negativo o cero.\n");
        return 1;
    }
 printf("%f\n", mid);
    if (num > 1.0) 
    {
    alto = num;
    } 
    else 
    {
    alto = 1.0;
    }
    printf("%f\n", mid);
    // Bucle de bisección
    for (int i = 0; i < max_iter; i++) {
        mid = (bajo + alto) / 2.0;            // Calcular punto medio
        double sq = mid * mid;               // Cuadrado del punto medio

        if (sq > num) 
        {
            alto = mid;                      // La raíz está en [bajo, mid]
        } 
        else 
        {
            bajo = mid;                      // La raíz está en [mid, alto]
        }
        printf("%f\n", mid);
        // Si el intervalo alcanza la tolerancia, salimos
        if ((alto - bajo) < tol) 
        {
            break;
        }
    }printf("%f\n", mid);
    // mid es la aproximación de la raíz cuadrada
    printf("La raiz cuadrada aproximada de %f es %.10f\n", num, mid);
    return mid;
}

