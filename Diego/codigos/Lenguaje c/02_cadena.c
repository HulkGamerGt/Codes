/*Nombre: Diego Solis Rojas
  Fecha: 13 / 06 / 2025
  Descripcion: Ejemplo de manejo de cadenas en C
*/

#include <stdio.h>


int main() {
  char nombre[20];
  printf("Introduzca su nombre (20 letras máximo): ");
  scanf("%s", nombre);
  printf("\nEl nombre que ha escrito es: %s\n", nombre);
  return 0;
}
