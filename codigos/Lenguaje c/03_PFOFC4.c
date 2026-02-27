/*Docentes académicos: Mg. Hugo Araya - Mg. Luis Ponce Rosales.
  Carrera  Ingeniería Civil Informáca.  
  Estudiantes : Benjamin Ruz Barde / Escarleth Varela Muñoz / Diego Solis Rojas.
  Fecha de entrega : 07 / 07 / 2025
  Descripcion del programa :  codifica un programa que permita a los espías cifrar los mensajes que la agencia 
envía a sus colaboradores a través de Internet usando todas las funciones que están en el programa, para  guardar la informacion
crea un archivo llamado original.txt, que guarda el mensaje original, y otro llamado codificado.txt, que guarda el mensaje codificado.
  El mensaje original se lee desde la entrada estándar y se guarda en un archivo llamado original.txt. 
  El mensaje codificado se genera a partir del mensaje original y se guarda en un archivo llamado codificado.txt.
  El alfabeto utilizado para la codificación es un arreglo de caracteres que incluye letras mayúsculas, números y algunos signos de puntuación.

*/
#include <stdio.h>
#include <string.h>

/* Prototipos de funciones */
void lee_original(char *mensaje_original, int *N);

void codificar(char *mensaje_original, char *mensaje_codificado, char *alfabeto, int N, int tam_alfabeto);

void primera_etapa(char *mensaje_original, char *mensaje_intermedio, int N);

void segunda_etapa(char *mensaje_intermedio, char *mensaje_codificado, int N);

void graba_mensaje(char *mensaje_codificado, int N);

void inicializa_alfabeto(char *alfabeto);


int main() {
  char original[100];
  char alfabeto[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' ', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ',', '!', '.', ':', ';', '?', '-', '+', '*', '/'};
  int tam_alfabeto = sizeof(alfabeto) - 1;
  char codificado[100];
  int N;

  printf("%d\n", tam_alfabeto);
  lee_original(original, &N);
  inicializa_alfabeto(alfabeto);
  codificar(original, codificado, alfabeto, N, tam_alfabeto);
  graba_mensaje(codificado, N);
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
  /*Dar vuelta el mensaje codificado*/
  strrev(mensaje_codificado);
  printf("mensaje codificado: %s\n", mensaje_codificado);
}

void primera_etapa(char *mensaje_original, char *mensaje_intermedio, int N) {

 
}

void segunda_etapa(char *mensaje_intermedio, char *mensaje_codificado, int N) {


}

void graba_mensaje(char *mensaje_codificado, int N) {
  
}

void inicializa_alfabeto(char *alfabeto) {

}
