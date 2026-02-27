/*Docentes académicos: Mg. Hugo Araya - Mg. Luis Ponce Rosales.
  Carrera  Ingeniería Civil Informática.
  Estudiantes : Benjamin Ruz Barde / Escarleth Varela Muñoz / Diego Solis Rojas.
  Fecha de entrega : 07 / 07 / 2025
  Descripcion del programa :   
  
*/
#include <stdio.h>
#include <string.h>

/* Prototipos de funciones */
void lee_original(char *mensaje_original, int *N);
void codificar(char *mensaje_original, char *mensaje_codificado, char *alfabeto, int N);
void primera_etapa(char *mensaje_original, char *mensaje_intermedio, int N);
void segunda_etapa(char *mensaje_intermedio, char *mensaje_codificado, int N);
void graba_mensaje(char *mensaje_codificado, int N);
void inicializa_alfabeto(char *alfabeto);
void decodificar(char *mensaje_codificado, char *mensaje_decodificado, int N);
void primera_etapa_decodificar(char *mensaje_intermedio, char *mensaje_decodificado, int N);
void segunda_etapa_decodificar(char *mensaje_codificado, char *mensaje_intermedio, int N);

int main() {
  char original[100];
  char alfabeto[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789,!.:;?-+*/";
  const int tam_alfabeto = sizeof(alfabeto) - 1; /* Longitud del alfabeto */
  char codificado[100];
  char decodificado[100];
  int N;
  int opcion;

  printf("Seleccione una opcion:\n");
  printf("1. Codificar un mensaje\n");
  printf("2. Decodificar un mensaje\n");
  printf("Ingrese su opcion (1 o 2): ");
  scanf("%d", &opcion);
  getchar(); /* Consumir el salto de linea despues de scanf */

  if (opcion == 1) {
    lee_original(original, &N);
    codificar(original, codificado, alfabeto, N);
    printf("Mensaje codificado: %s\n", codificado);
    graba_mensaje(codificado, N);
  } else if (opcion == 2) {
    printf("Ingrese el mensaje codificado: ");
    fgets(codificado, 100, stdin);
    N = strlen(codificado);
    if (codificado[N - 1] == '\n') 
    {
      codificado[N - 1] = '\0';
       N--;
    }
    decodificar(codificado, decodificado, N);
    printf("Mensaje decodificado: %s\n", decodificado);
  } else {
    printf("Opcion invalida.\n");
    return 1;
  }

  return 0;
}

void lee_original(char *mensaje_original, int *N) {
  printf("Ingrese el mensaje original: ");
  fgets(mensaje_original, 100, stdin);
  *N = strlen(mensaje_original);
  if (mensaje_original[*N - 1] == '\n') {
    mensaje_original[*N - 1] = '\0';
    (*N)--;
  }
}

void codificar(char *mensaje_original, char *mensaje_codificado, char *alfabeto, int N) {
  char mensaje_intermedio[100]; /* Buffer para el mensaje intermedio */
  primera_etapa(mensaje_original, mensaje_intermedio, N);
  segunda_etapa(mensaje_intermedio, mensaje_codificado, N);
}

void primera_etapa(char *mensaje_original, char *mensaje_intermedio, int N) {
  int i;
  for (i = 0; i < N; i++) {
    mensaje_intermedio[i] = mensaje_original[i] + 3;  /* Cifrado simple */
  }
}

void segunda_etapa(char *mensaje_intermedio, char *mensaje_codificado, int N) {
  int i;
  for (i = 0; i < N; i++) {
    mensaje_codificado[i] = mensaje_intermedio[N - 1 - i];
  }
}

void graba_mensaje(char *mensaje_codificado, int N) {
  FILE *archivo;
  archivo = fopen("mensaje_codificado.txt", "w");
  if (archivo == NULL) {
    printf("Error al abrir el archivo\n");
    return;
  }
  fwrite(mensaje_codificado, sizeof(char), N, archivo);
  fclose(archivo);
  printf("Mensaje codificado guardado en 'mensaje_codificado.txt'\n");
}

void inicializa_alfabeto(char *alfabeto) {
  const char *caracteres = "ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789,!.:;?-+*/";
  int i;
  for (i = 0; i < strlen(caracteres); i++) {
    alfabeto[i] = caracteres[i];
  }
  alfabeto[strlen(caracteres)] = '\0'; /* Asegura que el alfabeto sea una cadena valida */
}

void decodificar(char *mensaje_codificado, char *mensaje_decodificado, int N) {
  char mensaje_intermedio[100]; /* Buffer para el mensaje intermedio */
  segunda_etapa_decodificar(mensaje_codificado, mensaje_intermedio, N);
  primera_etapa_decodificar(mensaje_intermedio, mensaje_decodificado, N);
}

void segunda_etapa_decodificar(char *mensaje_codificado, char *mensaje_intermedio, int N) {
  int i;
  for (i = 0; i < N; i++) {
    mensaje_intermedio[i] = mensaje_codificado[N - 1 - i]; /* Invierte el orden */
  }
}

void primera_etapa_decodificar(char *mensaje_intermedio, char *mensaje_decodificado, int N) {
  int i;
  for (i = 0; i < N; i++) {
    mensaje_decodificado[i] = mensaje_intermedio[i] - 3;  /* Descifrado simple */
  }
  mensaje_decodificado[N] = '\0'; /* Asegura que el mensaje decodificado sea una cadena valida */
}