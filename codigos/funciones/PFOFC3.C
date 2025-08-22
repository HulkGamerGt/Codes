/*Docentes académicos: Mg. Hugo Araya - Mg. Luis Ponce Rosales.
  Carrera  Ingeniería Civil Informáca.  
  Estudiantes : Benjamin Ruz Barde / Escarleth Varela Muñoz / Diego Solis Rojas.
  Fecha de entrega : 07 / 07 / 2025
  Descripcion del programa :  El mensaje se codifica en dos etapas, la primera es utilizando un método ampliamente 
difundido, el cual corresponde a un sistema por sustitución simple basado en una 
manipulación aritmética sobre la posición que ocupa el carácter en el “alfabeto”. Esta 
manipulación aritmética es la misma para todos los caracteres de los mensajes y consiste 
en restar un determinado número entero positivo (lo llamaremos N) a la posición del 
carácter en estudio y reemplazarlo por el que se encuentra en la posición indicada por la 
resta.   
Una vez realizado este reemplazo, se ejecuta la segunda etapa y consiste en reemplazar 
los caracteres de la siguiente forma: a los caracteres que se encuentren en una posición 
múltiplo de 3 se le debe sumar el número antes indicado (N) a su posición y sustituirlo por 
el carácter correspondiente del “alfabeto”. NOTA: Consideraremos que el número cero es 
múltiplo de cualquier número. 
Con el mensaje así codificado, se genera un archivo de texto el que es enviado al espía 
junto a un número N que corresponde a la clave numérica que  posibilita  la decodificación 
(este número corresponde al desplazamiento en el alfabeto que dio inicio a la 
codificación).  
compatible con C89
*/
#include <stdio.h> 
#include <string.h> 

/*Prototipos de funciones*/ 
void lee_original(char *mensaje_original , int *N);

void codificar(char *mensaje_original, char *mensaje_codificado, char *alfabeto, int N);

void primera_etapa(char *mensaje_original, char *mensaje_intermedio, int N);

void segunda_etapa(char *mensaje_intermedio, char *mensaje_codificado, int N);

void graba_mensaje(char *mensaje_codificado, int N);

void inicializa_alfabeto(char *alfabeto); 
/* Esta funcion   */


int main(){ 
  char original[100]; 
  char alfabeto[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S'
                      ,'T','U','V','W','X','Y','Z',' ','0','1','2','3','4','5','6','7','8','9'
                      ,',','!','.',':',';','?','-','+','*','/'}; 
  const int tam_alfabeto = sizeof(alfabeto) - 1; /*Longitud del alfabeto*/ 
  char codificado[100]; 
  int N; 
  printf("%d",tam_alfabeto);
  lee_original(original, &N); 
  inicializa_alfabeto(alfabeto); 
  codificar(original, codificado, alfabeto, N); 
  graba_mensaje(codificado, N); 
  return 0; 
}

void lee_original(char *mensaje_original, int *N){
  printf("Ingrese el mensaje original: ");
  fgets(mensaje_original, 100, stdin);
  *N = strlen(mensaje_original);
  if (mensaje_original[*N - 1] == '\n') {
    mensaje_original[*N - 1] = '\0';
    (*N)--;
  }
}

void codificar(char *mensaje_original, char *mensaje_codificado, char *alfabeto, int N){
  primera_etapa(mensaje_original, mensaje_codificado, N);
  segunda_etapa(mensaje_codificado, mensaje_codificado, N);
}

void primera_etapa(char *mensaje_original, char *mensaje_intermedio, int N){
  for (int i = 0; i < N; i++) {
    mensaje_intermedio[i] = alfabeto[(find_position(mensaje_original[i], alfabeto) - N + ALFABETO_SIZE) % ALFABETO_SIZE];
  }
}

void segunda_etapa(char *mensaje_intermedio, char *mensaje_codificado, int N){
  for (int i = 0; i < N; i++) {
    if (i % 3 == 0) {
      mensaje_codificado[i] = alfabeto[(find_position(mensaje_intermedio[i], alfabeto) + N) % ALFABETO_SIZE];
    } else {
      mensaje_codificado[i] = mensaje_intermedio[i];
    }
  }
}

void graba_mensaje(char *mensaje_codificado, int N){
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
  for (int i = 0; i < ALFABETO_SIZE; i++) {
    alfabeto[i] = i + 32;  // Inicializa el alfabeto con caracteres ASCII
  }
}
