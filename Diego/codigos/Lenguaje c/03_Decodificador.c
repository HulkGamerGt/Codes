/*Docentes académicos: Mg. Hugo Araya - Mg. Luis Ponce Rosales.
  Carrera :  Ingeniería Civil Informática.  
  Estudiantes : Escarleth Varela Muñoz / Benjamin Ruz Barde / Diego Solis Rojas.
  Fecha de entrega : 07 / 07 / 2025
  Descripcion del programa : Este programa en lenguaje de programacion C, implementa un sistema de decodificación de 
  mensajes utilizando un cifrado por desplazamiento. 
  El usuario proporciona un mensaje y una clave numérica dentro de un archivo llamado codificado.txt,
  y el programa genera un mensaje decodificado que se almacena en un archivo llamado decodificado.txt.
  Compatible con el estandar C89.
*/

#include <stdio.h>
#include <string.h>

/* Prototipos de Funciones */

void inicializa_alfabeto(char *); /* Inicializa el alfabeto */
int buscar_posicion_en_alfabeto(char, char *); /* Busca la posición de un carácter en el alfabeto */
char buscar_caracter_por_posicion(int, char *); /* Busca un carácter en el alfabeto por su posición */

int lee_codificado(char *, int *); /* Lee el mensaje codificado y la clave N desde "codificado.txt". */
void graba_decodificado(char *); /* Graba el mensaje decodificado en "decodificado.txt". */

void decodificar(char *, char *, char *, int); /* Función principal para la decodificación del mensaje */
void primera_etapa_decodificar(char *, char *, char *, int); /* Deshace la suma N a caracteres cuya posición en el alfabeto es múltiplo de 3. */
void segunda_etapa_decodificar(char *, char *, char *, int); /* Deshace el desplazamiento principal (suma N o el caso especial de +6). */

/* Función Principal del Decodificador */
int main() {
    char alfabeto[48];
    char codificado[100];
    char decodificado[100];
    int  clave_N;
    int  lectura_exitosa; /* Variable para almacenar el resultado de la lectura */

    inicializa_alfabeto(alfabeto);

    lectura_exitosa = lee_codificado(codificado, &clave_N);

    /* Si la lectura no fue exitosa, no se intenta decodificar ni grabar */
    if (!lectura_exitosa) {
        printf("No se pudo decodificar el mensaje debido a un error en 'codificado.txt'.\n");
        return 1; 
    }

    decodificar(codificado, decodificado, alfabeto, clave_N);
    graba_decodificado(decodificado);

    return 0; 
}

/* Inicializa el vector del alfabeto con los caracteres definidos. */
void inicializa_alfabeto(char *alfabeto) {
    strcpy(alfabeto, "ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789!,.:;?-+*/");
}

/* Lee el mensaje codificado y la clave N desde "codificado.txt". */
int lee_codificado(char *mensaje_codificado_con_clave, int *clave_N_codificado) {
    FILE *archivo;
    char Linea_completa[100];
    char *Posicion_gato; 
    char Clave_char;
    int  Longitud_linea;

    archivo = fopen("codificado.txt", "r");
    if (archivo == NULL) {
        printf("Error: No se pudo abrir el archivo 'codificado.txt'. Asegurese de que existe.\n");
        return 0;
    }

    if (fgets(Linea_completa, sizeof(Linea_completa), archivo) != NULL) {
        Longitud_linea = strlen(Linea_completa);

        /* Elimina el salto de línea si existe al final de la cadena */
        if (Longitud_linea > 0 && Linea_completa[Longitud_linea - 1] == '\n') {
            Linea_completa[Longitud_linea - 1] = '\0';
        }
        Posicion_gato = strchr(Linea_completa, '#'); 

        if (Posicion_gato != NULL) {
            Clave_char = Linea_completa[0];
            if (Clave_char >= '0' && Clave_char <= '9') {
                *clave_N_codificado = Clave_char - '0';
            } else {
                printf("Error: La clave N en 'codificado.txt' no es un digito valido. Formato incorrecto.\n");
                fclose(archivo);
                return 0;
            }
            strcpy(mensaje_codificado_con_clave, Linea_completa);
            fclose(archivo);
            return 1;
        } else {
            printf("Formato de archivo 'codificado.txt' es incorrecto. Se esperaba clave#mensaje.\n");
            fclose(archivo);
            return 0;
        }
    } else {
        printf("El archivo 'codificado.txt' está vacio o no se pudo leer.\n");
        fclose(archivo);
        return 0;
    }
}

/* Graba el mensaje decodificado en "decodificado.txt". */
void graba_decodificado(char *mensaje_decodificado) {
    FILE *archivo;

    archivo = fopen("decodificado.txt", "w");
    if (archivo == NULL) {
        printf("Error al crear 'decodificado.txt'.\n");
        return;
    }
    fprintf(archivo, "%s", mensaje_decodificado);
    fclose(archivo);
    printf("Mensaje decodificado guardado en 'decodificado.txt'.\n");
}

/* Función principal para la decodificación del mensaje. */
void decodificar(char *mensaje_codificado_con_clave, char *mensaje_decodificado, char *alfabeto, int N) {
    char *Almacenar_gato;
    char Mensaje_solo_codificado[100];
    char Mensaje_intermedio_decodificado[100];

    /*Extrae el mensaje codificado (lo que viene después del '#')*/ 
    Almacenar_gato = strchr(mensaje_codificado_con_clave, '#');
    strcpy(Mensaje_solo_codificado, Almacenar_gato + 1);

    primera_etapa_decodificar(Mensaje_solo_codificado, Mensaje_intermedio_decodificado, alfabeto, N);
    segunda_etapa_decodificar(Mensaje_intermedio_decodificado, mensaje_decodificado, alfabeto, N);
}

/*Deshace la suma N a caracteres cuya posición en el alfabeto es múltiplo de 3. */
void primera_etapa_decodificar(char *mensaje_codificado, char *mensaje_intermedio_decodificado, char *alfabeto, int N) {
    int Pri_etapa_decodificar;
    int Posicion_caracter;
    int Tamano_alfabeto;
    int Nueva_posicion;
    int Longitud_codificado;

    Tamano_alfabeto = strlen(alfabeto);
    Longitud_codificado = strlen(mensaje_codificado);

    strcpy(mensaje_intermedio_decodificado, mensaje_codificado);

    for (Pri_etapa_decodificar = 0; Pri_etapa_decodificar < Longitud_codificado; Pri_etapa_decodificar++) {
        Posicion_caracter = buscar_posicion_en_alfabeto(mensaje_intermedio_decodificado[Pri_etapa_decodificar], alfabeto);

        if (Posicion_caracter != -1) {
            if (Posicion_caracter % 3 == 0) {
                Nueva_posicion = (Posicion_caracter - N);
                while (Nueva_posicion < 0) {
                    Nueva_posicion = Nueva_posicion + Tamano_alfabeto;
                }
                Nueva_posicion = Nueva_posicion % Tamano_alfabeto;
                mensaje_intermedio_decodificado[Pri_etapa_decodificar] = buscar_caracter_por_posicion(Nueva_posicion, alfabeto);
            }
        }
    }
    mensaje_intermedio_decodificado[Longitud_codificado] = '\0';
}

/* Segunda etapa de decodificación: Deshace el desplazamiento principal (suma N o el caso especial de +6). */
void segunda_etapa_decodificar(char *mensaje_intermedio, char *mensaje_decodificado, char *alfabeto, int N) {
    int Segu_etapa_decodificar;
    int Posicion_caracter;
    int Tamano_alfabeto;
    int Nueva_posicion;
    int Longitud_mensaje_intermedio;

    Tamano_alfabeto = strlen(alfabeto);
    Longitud_mensaje_intermedio = strlen(mensaje_intermedio);

    /* Caso especial de decodificación. Si el mensaje tiene un solo carácter después de # */ 
    if (Longitud_mensaje_intermedio == 1) {
        Posicion_caracter = buscar_posicion_en_alfabeto(mensaje_intermedio[0], alfabeto);
        if (Posicion_caracter != -1) {
            Nueva_posicion = (Posicion_caracter + 6);  
            Nueva_posicion = Nueva_posicion % Tamano_alfabeto;
            mensaje_decodificado[0] = buscar_caracter_por_posicion(Nueva_posicion, alfabeto);
            mensaje_decodificado[1] = '\0';
            return;
        }
    }

    /* Caso normal para mensajes con más de un carácter */
    for (Segu_etapa_decodificar = 0; Segu_etapa_decodificar < Longitud_mensaje_intermedio; Segu_etapa_decodificar++) {
        Posicion_caracter = buscar_posicion_en_alfabeto(mensaje_intermedio[Segu_etapa_decodificar], alfabeto);

        if (Posicion_caracter != -1) {
            Nueva_posicion = (Posicion_caracter + N); 
            Nueva_posicion = Nueva_posicion % Tamano_alfabeto;
            mensaje_decodificado[Segu_etapa_decodificar] = buscar_caracter_por_posicion(Nueva_posicion, alfabeto);
        } else {
            mensaje_decodificado[Segu_etapa_decodificar] = mensaje_intermedio[Segu_etapa_decodificar]; 
        }
    }
    mensaje_decodificado[Longitud_mensaje_intermedio] = '\0';
}

/* Busca la posición de un carácter dado en el alfabeto. Retorna -1 si no lo encuentra. */
int buscar_posicion_en_alfabeto(char caracter, char *alfabeto) {
    int buscar_posicion_alfabeto;
    int Tamano_alfabeto;

    Tamano_alfabeto = strlen(alfabeto);
    for (buscar_posicion_alfabeto = 0; buscar_posicion_alfabeto < Tamano_alfabeto; buscar_posicion_alfabeto++) {
        if (alfabeto[buscar_posicion_alfabeto] == caracter) {
            return buscar_posicion_alfabeto;
        }
    }
    return -1;
}

/* Busca el carácter en una posición dada del alfabeto. */
char buscar_caracter_por_posicion(int posicion, char *alfabeto) {
    return alfabeto[posicion];
}