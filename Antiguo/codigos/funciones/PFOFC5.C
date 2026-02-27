/*Docentes académicos: Mg. Hugo Araya - Mg. Luis Ponce Rosales.
  Carrera  Ingeniería Civil Informáca.  
  Estudiantes : Benjamin Ruz Barde / Escarleth Varela Muñoz / Diego Solis Rojas.
  Fecha de entrega : 07 / 07 / 2025
  Descripcion del programa :  codifica un programa que permita a los espías cifrar los mensajes que la agencia 
envía a sus colaboradores a través de Internet. 

*/
#include <stdio.h>
#include <string.h>

/* Prototipos de funciones */
void lee_original(char *mensaje_original, int *N);

void codificar(char *mensaje_original, char *mensaje_codificado, char *alfabeto, int N, int tam_alfabeto);

void primera_etapa(char *str,int N);

void segunda_etapa(char *mensaje_intermedio, char *mensaje_codificado, int N);

void graba_mensaje(char *mensaje_codificado);

void inicializa_alfabeto(char *alfabeto);


int main() {
  char original[100];
  char alfabeto[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' ', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ',', '!', '.', ':', ';', '?', '-', '+', '*', '/'};
  int tam_alfabeto = sizeof(alfabeto) - 1;
  char codificado[100];
  int N;

  printf("%d\n", tam_alfabeto);
  lee_original(original, &N);
  /* inicializa_alfabeto(alfabeto); // Esta función está vacía y no es necesaria si el alfabeto se inicializa directamente */
  codificar(original, codificado, alfabeto, N, tam_alfabeto);
  graba_mensaje(codificado);
  return 0;
}

void lee_original(char *mensaje_original, int *N) {
  printf("ingrese el mensaje original:");
  fgets(mensaje_original, 100, stdin);
  *N = strlen(mensaje_original);    /* Obtener la longitud del mensaje original */
  if (mensaje_original[*N - 1] == '\n') {
    mensaje_original[*N - 1] = '\0';
    (*N)--;
  }
}

void codificar(char *mensaje_original, char *mensaje_codificado, char *alfabeto, int N, int tam_alfabeto) {
  int i = 0;
  int desplazamiento = 3;
  int j;
  int encontrado; /* Bandera para saber si el caracter se encontró en el alfabeto */

  for (i = 0; i < N; i++) {
    encontrado = 0;
    for (j = 0; j < tam_alfabeto; j++) {
      if (mensaje_original[i] == alfabeto[j]) {
        /* Calcula el nuevo índice con el desplazamiento y el módulo */
        mensaje_codificado[i] = alfabeto[(j + desplazamiento) % tam_alfabeto];
        encontrado = 1;
        break; /* Sale del bucle interno una vez que se encuentra el caracter */
      }
    }
    if (!encontrado) {
      /* Si el caracter no está en el alfabeto, se mantiene igual */
      mensaje_codificado[i] = mensaje_original[i];
    }
  }
  mensaje_codificado[N] = '\0';
  /*DAR VUELTA EL MENSAJE CODIFICADO*/
  strrev(mensaje_codificado);
  printf("mensaje codificado: %s\n", mensaje_codificado);
}
void primera_etapa(char *str, int N) {
  int left = 0;
  int right = N - 1;
  while (left < right) {
     char temp = str[left];
      str[left] = str[right];
      str[right] = temp;
      left++;
      right--;
    
  }
}
void segunda_etapa(char *mensaje_intermedio, char *mensaje_codificado, int N) {
 int i;
    for (i = 0; i < N; i++) {
        switch (mensaje_intermedio[i]) { 
            case 'A': mensaje_codificado[i] = '@'; break;
            case 'E': mensaje_codificado[i] = '3'; break;
            case 'I': mensaje_codificado[i] = '1'; break;
            case 'O': mensaje_codificado[i] = '0'; break;
            case 'S': mensaje_codificado[i] = '9'; break;
            default: mensaje_codificado[i] = mensaje_intermedio[i]; break;
        }
    } 
    mensaje_codificado[N] = '\0';
}

void graba_mensaje(char *mensaje_codificado) {
  printf("mensaje codificado:%s\n", mensaje_codificado);
}



