/* Diego Solis R: 2025
   Fecha: 09/05/2025
 Descripcion: Programa que calcula el area de un rectangulo y de un cubo
*/

#include <stdio.h>

int main() {
    float L1r = 0, L2r = 0, L1c = 0;
    float areaRectangulo = 0, areaCubo = 0;

    printf("Este programa calcula el area de un rectangulo y de un cubo\n");

    printf("Ingrese el lado 1 del rectangulo: \n");
    scanf("%f", &L1r);                               
    
    printf("Ingrese el lado 2 del rectangulo: \n");
    scanf("%f", &L2r);
    
    printf("Ingrese el lado 1 del cubo: \n");
    scanf("%f", &L1c);
    
    if (L1r < 0 || L2r < 0 || L1c < 0) {
        printf("Error: Los lados no pueden ser negativos.\n");
        return 0;
    }
    
    if (L1r > 0 && L2r > 0) {
        areaRectangulo = L1r * L2r; 
    }

    if (L1c > 0) {
        areaCubo = 6 * (L1c * L1c);  
    }

    printf("El area del rectangulo es: %.2f\n", areaRectangulo); 
    printf("El area del cubo es: %.2f\n", areaCubo); 

    return 0;
}
