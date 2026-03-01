/* Diego Solis R: 2025
   Fecha: 22/05/2025
 Descripcion: ingresa una serie de notas y saca la cantidad de notas validas, promedio de las notas, 
 clasificacion maxima, minima y su desviacion estandar con el metodo de biseccion.
*/

#include <stdio.h>
double raiz(double); 

int main() 
{
  double nota= 0, not=0, prom = 0,  notMax = 0, notMin = 7, dest2 = 0, dest = 0, arreglo[99995]; // Use double por recomendacion del Ayudante Diego Ramírez (22/05/2025), float pero mas preciso.
  int cn = 0,i = 0; 
  while (i < 1)  
  {

      printf("Ingrese una nota (0-7, o 8 para terminar de ingresar notas): ");
      scanf("%lf", &nota); // Se usa %lf porque es un double.
      printf("La nota ingresada es: %lf\n", nota);
      printf("Si desea terminar de ingresar notas, ingrese 8 \n");
      if (nota < notMin) // Saca la nota minima.
     {
        notMin = nota;
     }
      if ((nota !=8 ) && (nota <=7 ) && nota > notMax) // Saca la nota maxima, con esas restricciones.
     {
        notMax = nota;
     }
      not = not + nota;

      arreglo[cn] = nota; // Almacena la nota en el arreglo.
      cn = cn + 1;

      if (nota == 8) 
      {
         not = not - 8;       // Considera a 8 como nota, osea que debemos descontar el 8.
         cn = cn - 1;         // Mismo caso con el 8, solo que ahora con la cantidad de notas.
         prom = not / cn;     // Promedio de notas de datos no agrupados.
         for(int notreal = 0; notreal < cn; notreal++) 
         {
            dest2 = dest2 + ((arreglo[notreal] - prom) * (arreglo[notreal] - prom)); // Formula de la varianza para datos no agrupados, con sumatoria de sus resultados.
         }
         printf("El numero 8 no afecta al resultado\n");
         dest2 = (dest2 / cn); // Resultado final de la varianza para datos no agrupados.
         i++;
         dest = (raiz(dest2)); 
        } // Del if (nota == 8)

      if(nota < 0 || (nota != 8 && nota > 7)) // Si ingresa un numero distinto del rango permitido y distinto de 8 (porque 8 es el dato que usamos para poder sacar los resultados), entonces dice que es erroneo.
      {
        cn = cn - 1;        // Se resta 1 a la cantidad de notas validas, porque no es valida esa nota ingresada.
        not = not - nota;   // Se resta la nota ingresada , porque no es valida al calculo final.
        printf("Error: la nota debe estar entre 0 y 7.\n");
        printf("cantidad de clasificaciones validas: %d\n", cn);
      } // Del if (nota < 0 || (nota != 8 && nota > 7))


  }// Del while i<1
   printf("Cantidad de calificaciones validas %d\n", cn);
   printf("El promedio de las notas es: %.2f\n", prom);
   printf("La nota maxima es: %.2f\n", notMax);
   printf("La nota minima es: %.2f\n", notMin);
   printf("La Desviacion estandar es: %.10f\n", dest);
   return 0;
} // Del int main

double raiz(double num)                 // Número al que calcular la raíz cuadrada, método de bisección.
{
    double bajo = 0, alto;              // Límites del intervalo para la bisección.
    double mid;                         // Punto medio del intervalo.
    double tol = 1e-13;                 // Tolerancia para la convergencia.
    double max_iter = 100000000000;     // Iteraciones máximas.

    if (num > 1.0) 
    {
    alto = num;
    } 
    else 
    {
    alto = 1.0;
    }
    // Bucle de bisección
    for (int i = 0; i < max_iter; i++) 
    {
        mid = (bajo + alto) / 2.0;            // Calcular punto medio.
        float sq = mid * mid;                 // Cuadrado del punto medio.
        if (sq > num) 
        {
            alto = mid;                       // La raíz está en [bajo, mid].
        } 
        else 
        {
            bajo = mid;                       // La raíz está en [mid, alto].
        }
        // Si el intervalo alcanza la tolerancia, salimos.
        if ((alto - bajo) < tol) 
        {
            break;
        }
    }
    // mid es la aproximación de la raíz cuadrada.
    return mid; 

}
