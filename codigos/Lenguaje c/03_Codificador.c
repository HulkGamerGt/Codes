/*Docentes académicos: Mg. Hugo Araya - Mg. Luis Ponce Rosales.
  Carrera :  Ingeniería Civil Informática.  
  Estudiantes : Escarleth Varela Muñoz / Benjamin Ruz Barde / Diego Solis Rojas.
  Fecha de entrega : 07 / 07 / 2025
  Descripcion del programa : Este programa en lenguaje de programacion C, implementa un sistema de codificación de 
  mensajes utilizando un cifrado por desplazamiento. 
  El usuario proporciona un mensaje y una clave numérica dentro de un archivo llamado original.txt,
  y el programa genera un mensaje codificado que se almacena en un archivo llamado codificado.txt.
  Compatible con el estandar C89.
*/

#include <stdio.h>
#include <string.h>

/* Prototipos de Funciones */

void inicializa_alfabeto(char *); /* Inicializa el alfabeto */
int  buscar_posicion_en_alfabeto(char, char *); /* Busca la posición de un carácter en el alfabeto */
char buscar_caracter_por_posicion(int, char *); /* Busca un carácter en el alfabeto por su posición */

int  lee_original(char *, int *); /* Lee el mensaje original y la clave N desde "original.txt". */
void graba_mensaje(char *); /* Graba el mensaje codificado en "codificado.txt". */

void codificar(char *, char *, char *, int); /* Función principal para la codificación del mensaje. */
void primera_etapa(char *, char *, char *, int); /* Primera etapa de codificación: Desplaza caracteres a la izquierda (resta N). */
void segunda_etapa(char *, char *, char *, int); /* Segunda etapa de codificación: Desplaza caracteres a la derecha (suma N). */

/* Función Principal del Codificador */
int main() {
    char original[100];
    char alfabeto[48];
    char codificado[100];
    int  clave_n;
    int  lectura_exitosa;

    inicializa_alfabeto(alfabeto);

    lectura_exitosa = lee_original(original, &clave_n);

    if (!lectura_exitosa) {
        printf("No se pudo codificar el mensaje debido a un error en 'original.txt'.\n");
        return 1; 
    }

    codificar(original, codificado, alfabeto, clave_n);
    graba_mensaje(codificado);

    return 0;
}

/* Inicializa el vector del alfabeto con los caracteres definidos para el cifrado. */
void inicializa_alfabeto(char *alfabeto) {
    strcpy(alfabeto, "ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789!,.:;?-+*/");
}

/* Lee el mensaje original y la clave N desde "original.txt".
   Retorna 0 si hay un error en la lectura o formato, 1 si es exitosa. */
int lee_original(char *mensaje_original, int *N) {
    FILE *archivo;
    char Linea_completa[100];
    int  Buscar_caracter_gato;
    int  Almacenar_gato = -1;
    char Clave;
    int  Longitud_linea_real;

    archivo = fopen("original.txt", "r");
    if (archivo == NULL) {
        printf("Error: No se pudo abrir el archivo 'original.txt'. Asegurese de que existe.\n");
        return 0;
    }

    if (fgets(Linea_completa, sizeof(Linea_completa), archivo) != NULL) {
        Longitud_linea_real = strlen(Linea_completa);
        /* Elimina el salto de línea si existe al final de la cadena */ 
        if (Longitud_linea_real > 0 && Linea_completa[Longitud_linea_real - 1] == '\n') {
            Linea_completa[Longitud_linea_real - 1] = '\0';
            Longitud_linea_real--;
        }

        /* Busca el caracter '#' que separa la clave del mensaje */
        for (Buscar_caracter_gato = 0; Buscar_caracter_gato < Longitud_linea_real; Buscar_caracter_gato++) {
            if (Linea_completa[Buscar_caracter_gato] == '#') {
                Almacenar_gato = Buscar_caracter_gato;
                break;
            }
        }

        if (Almacenar_gato != -1) { /* Si se encontró el '#' */
            Clave = Linea_completa[0];

            /* Valida que la clave sea un dígito numérico */
            if (Clave >= '0' && Clave <= '9') {
                *N = Clave - '0'; /* Convierte el carácter a su valor numérico */
            } else {
                printf("Error: La clave N en 'original.txt' no es un dígito valido. Formato incorrecto.\n");
                fclose(archivo);
                return 0;
            }
            /* Copia el mensaje que sigue después del '#' */
            strcpy(mensaje_original, Linea_completa + Almacenar_gato + 1);
            fclose(archivo);
            return 1;
        } else {
            printf("Formato de archivo 'original.txt' incorrecto. Se esperaba clave#mensaje.\n");
            fclose(archivo);
            return 0;
        }
    } else {
        printf("El archivo 'original.txt' está vacio o no se pudo leer.\n");
        fclose(archivo);
        return 0;
    }
}

/* Graba el mensaje codificado en "codificado.txt". */
void graba_mensaje(char *mensaje_codificado) {
    FILE *Guardar_mensaje_codificado;

    Guardar_mensaje_codificado = fopen("codificado.txt", "w");
    if (Guardar_mensaje_codificado == NULL) {
        printf("Error al crear 'codificado.txt'.\n");
        return;
    }
    fprintf(Guardar_mensaje_codificado, "%s", mensaje_codificado);
    fclose(Guardar_mensaje_codificado);
    printf("Mensaje codificado guardado en 'codificado.txt'.\n\n");
}

/* Función principal para la codificación del mensaje. */
void codificar(char *mensaje_original, char *mensaje_codificado, char *alfabeto, int N) {
    char Mensaje_intermedio[100];
    char Temp_codificado_sin_clave[100]; /* Buffer para el mensaje codificado sin la clave */
    char N_tipo_str[2];

    sprintf(N_tipo_str, "%d", N); /*Convierte el entero N a un string*/

    primera_etapa(mensaje_original, Mensaje_intermedio, alfabeto, N);
    segunda_etapa(Mensaje_intermedio, Temp_codificado_sin_clave, alfabeto, N);

    /* Une la clave N, el separador '#' y el mensaje codificado final */
    strcpy(mensaje_codificado, N_tipo_str);
    strcat(mensaje_codificado, "#");
    strcat(mensaje_codificado, Temp_codificado_sin_clave);
}

/* Primera etapa de codificación: Desplaza caracteres a la izquierda (resta N). */
/* Maneja un caso especial para mensajes de un solo carácter. */
void primera_etapa(char *mensaje_original, char *mensaje_intermedio, char *alfabeto, int N) {
    int Primera_etapa;
    int Posicion_caracter;
    int Tamano_alfabeto;
    int Nueva_posicion;
    int Largo_original;

    Tamano_alfabeto = strlen(alfabeto);
    Largo_original = strlen(mensaje_original);

    /* Caso especial: Si el mensaje original tiene un solo carácter, desplazarlo 6 posiciones a la izquierda */
    if (Largo_original == 1) {
        Posicion_caracter = buscar_posicion_en_alfabeto(mensaje_original[0], alfabeto);
        if (Posicion_caracter != -1) {
            Nueva_posicion = (Posicion_caracter - 6); 
            while (Nueva_posicion < 0) {
                Nueva_posicion = Nueva_posicion + Tamano_alfabeto;
            }
            Nueva_posicion = Nueva_posicion % Tamano_alfabeto;
            mensaje_intermedio[0] = buscar_caracter_por_posicion(Nueva_posicion, alfabeto);
            mensaje_intermedio[1] = '\0';
            return;
        }
    }

    /* Lógica normal para mensajes con más de un carácter */
    for (Primera_etapa = 0; Primera_etapa < Largo_original; Primera_etapa++) {
        Posicion_caracter = buscar_posicion_en_alfabeto(mensaje_original[Primera_etapa], alfabeto);

        if (Posicion_caracter != -1) {
            Nueva_posicion = (Posicion_caracter - N);
            while (Nueva_posicion < 0) {
                Nueva_posicion = Nueva_posicion + Tamano_alfabeto;
            }
            Nueva_posicion = Nueva_posicion % Tamano_alfabeto;
            mensaje_intermedio[Primera_etapa] = buscar_caracter_por_posicion(Nueva_posicion, alfabeto);
        } else {
            mensaje_intermedio[Primera_etapa] = mensaje_original[Primera_etapa]; /* Mantiene caracteres no encontrados */
        }
    }
    mensaje_intermedio[Largo_original] = '\0';
}

/* Segunda etapa de codificación: Suma N a caracteres cuya posición en el alfabeto es múltiplo de 3. */
void segunda_etapa(char *mensaje_intermedio, char *mensaje_codificado, char *alfabeto, int N) {
    int Segunda_etapa; 
    int Posicion_caracter_en_alfabeto;
    int Tamano_alfabeto;
    int Nueva_posicion;
    int Longitud_mensaje_intermedio;

    Tamano_alfabeto = strlen(alfabeto);
    Longitud_mensaje_intermedio = strlen(mensaje_intermedio);

    strcpy(mensaje_codificado, mensaje_intermedio); /* Copia el mensaje intermedio para modificarlo */

    for (Segunda_etapa = 0; Segunda_etapa < Longitud_mensaje_intermedio; Segunda_etapa++) {
        Posicion_caracter_en_alfabeto = buscar_posicion_en_alfabeto(mensaje_codificado[Segunda_etapa], alfabeto);

        if (Posicion_caracter_en_alfabeto != -1) {
            if (Posicion_caracter_en_alfabeto % 3 == 0) {  /* Aplica el desplazamiento solo si es múltiplo de 3 */
                Nueva_posicion = (Posicion_caracter_en_alfabeto + N);
                Nueva_posicion = Nueva_posicion % Tamano_alfabeto; /* fetseseswesese */
                mensaje_codificado[Segunda_etapa] = buscar_caracter_por_posicion(Nueva_posicion, alfabeto);
            }
        }
    } 
    mensaje_codificado[Longitud_mensaje_intermedio] = '\0';
}

/* Busca la posición de un carácter dado en el alfabeto. Retorna -1 si no lo encuentra. */
int buscar_posicion_en_alfabeto(char caracter, char *alfabeto) {
    int Bus_pos_alfabeto;
    int Tamano_alfabeto;

    Tamano_alfabeto = strlen(alfabeto); 
    for (Bus_pos_alfabeto = 0; Bus_pos_alfabeto < Tamano_alfabeto; Bus_pos_alfabeto++) {
        if (alfabeto[Bus_pos_alfabeto] == caracter) {
            return Bus_pos_alfabeto;
        }
    }
    return -1;
}

/* Busca el carácter en una posición dada del alfabeto. */
char buscar_caracter_por_posicion(int posicion, char *alfabeto) {
    return alfabeto[posicion];
}