#include <stdio.h> // Para funciones de entrada/salida: printf, scanf, fgets, fopen, fclose, fprintf
#include <string.h> // Para funciones de manejo de cadenas: strlen, strchr, strcpy, sprintf

/* --- Prototipos de Funciones Requeridas --- */
void lee_original(char *, int *); /* Se modifica a int * para poder cambiar N */
void inicializa_alfabeto(char *);
void codificar(char *, char *, char *, int);
void graba_mensaje(char *);

/* --- Prototipos de Funciones Adicionales (Necesarias) --- */
void primera_etapa(char *, char *, char *, int); /* Añadido alfabeto */
void segunda_etapa(char *, char *, char *, int); /* Añadido alfabeto */
int buscar_posicion_en_alfabeto(char, char *);
char buscar_caracter_por_posicion(int, char *);

/* Prototipos para Decodificación */
void decodificar(char *, char *, char *);
void primera_etapa_decodificar(char *, char *, char *, int);
void segunda_etapa_decodificar(char *, char *, char *, int);//

/* --- Función Principal --- */
int main() {
    char original[256]; /* Suficientemente grande para el mensaje */
    char alfabeto[50];  /* Para el alfabeto de 47 caracteres + null terminator */
    char codificado[256];
    char decodificado[256]; /* Para almacenar el mensaje decodificado */
    int N; /* La clave N */
    int opcion; /* Para la seleccion de codificar/decodificar */
    
    /* Inicializa el alfabeto una sola vez */
    inicializa_alfabeto(alfabeto);

    printf("Seleccione una opcion:\n");
    printf("1. Codificar un mensaje (desde original.txt)\n");
    printf("2. Decodificar un mensaje (ingresando por teclado)\n");
    printf("Ingrese su opcion (1 o 2): ");
    scanf("%d", &opcion);
    /* Limpia el buffer de entrada para evitar problemas con fgets posteriores */
    while (getchar() != '\n'); 

    if (opcion == 1) {
        /* Lee el mensaje original y la clave N de original.txt */
        /* Se pasa la direccion de N para que la funcion pueda modificarla */
        lee_original(original, &N); 
        
        /* Codifica el mensaje */
        codificar(original, codificado, alfabeto, N);
        printf("Mensaje codificado: %s\n", codificado);
        
        /* Graba el mensaje codificado en codificado.txt */
        graba_mensaje(codificado);
    } else if (opcion == 2) {
        char mensaje_entrada_codificado[256];
        printf("Ingrese el mensaje codificado (ej. 6#BOGIU;L;Y;): ");
        fgets(mensaje_entrada_codificado, sizeof(mensaje_entrada_codificado), stdin);
        
        /* Eliminar el salto de linea si existe */
        if (strlen(mensaje_entrada_codificado) > 0 && mensaje_entrada_codificado[strlen(mensaje_entrada_codificado) - 1] == '\n') {
            mensaje_entrada_codificado[strlen(mensaje_entrada_codificado) - 1] = '\0';
        }

        /* Decodifica el mensaje ingresado */
        decodificar(mensaje_entrada_codificado, decodificado, alfabeto);
        printf("Mensaje decodificado: %s\n", decodificado);
    } else {
        printf("Opcion invalida.\n");
        return 1; /* Indicar error */
    }

    return 0; /* Salida exitosa */
}

/* --- Implementación de Funciones --- */

/* Inicializa el vector del alfabeto */
void inicializa_alfabeto(char *alfabeto) {
    strcpy(alfabeto, "ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789!,.:;?-+*/");
}

/*
 * Lee el mensaje original y la clave N desde "original.txt".
 * Se asume que N es un solo dígito para evitar necesidad de atoi o similar.
 */
void lee_original(char *mensaje_original, int *N_ptr) {
    FILE *archivo;
    char linea_completa[256]; /* Buffer para leer la linea completa */
    char *hash_pos; /* Puntero a la posicion del '#' */
    char clave_char; /* Para almacenar el caracter de la clave */
    
    archivo = fopen("original.txt", "r");
    if (archivo == NULL) {
        printf("Error: No se pudo abrir el archivo 'original.txt'. Asegurese de que existe.\n");
        *N_ptr = 0; /* Asignar 0 a N en caso de error */
        strcpy(mensaje_original, ""); /* Vaciar mensaje */
        return;
    }

    /* Lee la linea completa del archivo */
    if (fgets(linea_completa, sizeof(linea_completa), archivo) != NULL) {
        /* Elimina el salto de linea si existe al final de la cadena */
        if (strlen(linea_completa) > 0 && linea_completa[strlen(linea_completa) - 1] == '\n') {
            linea_completa[strlen(linea_completa) - 1] = '\0';
        }

        /* Busca el caracter '#' */
        hash_pos = strchr(linea_completa, '#');

        if (hash_pos != NULL) {
            /* La clave N es el primer caracter antes del '#' */
            clave_char = linea_completa[0]; 
            if (clave_char >= '0' && clave_char <= '9') {
                *N_ptr = clave_char - '0'; /* Convierte el caracter a su valor entero */
            } else {
                printf("Error: La clave N en 'original.txt' no es un digito valido (0-9).\n");
                *N_ptr = 0;
                strcpy(mensaje_original, "");
            }
            /* Copia la parte despues del '#' al mensaje original */
            strcpy(mensaje_original, hash_pos + 1); 
        } else {
            printf("Formato de archivo 'original.txt' incorrecto. Se esperaba clave#mensaje.\n");
            *N_ptr = 0;
            strcpy(mensaje_original, "");
        }
    } else {
        printf("El archivo 'original.txt' esta vacio o no se pudo leer.\n");
        *N_ptr = 0;
        strcpy(mensaje_original, "");
    }
    fclose(archivo);
}

/* Funcion principal para la codificacion */
void codificar(char *mensaje_original, char *mensaje_codificado, char *alfabeto, int N) {
    char mensaje_intermedio[256]; /* Almacena el resultado de la primera etapa */
    char temp_codificado_sin_clave[256]; /* Para construir el mensaje antes de añadir la clave */
    char N_char = N + '0'; /* Convierte N de int a char para sprintf */

    printf("\n--- Proceso de Codificacion ---\n");
    printf("Mensaje Original: %s, Clave N: %d\n", mensaje_original, N);

    /* Ejecuta la primera etapa de codificacion */
    primera_etapa(mensaje_original, mensaje_intermedio, alfabeto, N);
    printf("Mensaje Intermedio (1ra etapa): %s\n", mensaje_intermedio);

    /* Ejecuta la segunda etapa de codificacion */
    segunda_etapa(mensaje_intermedio, temp_codificado_sin_clave, alfabeto, N);
    printf("Mensaje Codificado (2da etapa): %s\n", temp_codificado_sin_clave);

    /* Formatea el mensaje codificado final con la clave y el '#' */
    sprintf(mensaje_codificado, "%c#%s", N_char, temp_codificado_sin_clave);
    printf("Mensaje Final Codificado: %s\n", mensaje_codificado);
}

/*
 * Primera etapa de codificacion: desplazamiento hacia la izquierda (resta N).
 * Circularidad: Si la nueva posicion es negativa, suma la longitud del alfabeto.
 */
void primera_etapa(char *mensaje_original, char *mensaje_intermedio, char *alfabeto, int N) {
    int i;
    int pos_caracter;
    int tam_alfabeto = (int)strlen(alfabeto);
    int nueva_posicion;
    int len_original = (int)strlen(mensaje_original);
    
    for (i = 0; i < len_original; i++) {
        pos_caracter = buscar_posicion_en_alfabeto(mensaje_original[i], alfabeto);
        
        if (pos_caracter != -1) { /* Si el caracter esta en el alfabeto */
            nueva_posicion = (pos_caracter - N); 
            
            /* Asegura que la nueva posicion sea positiva y dentro del rango */
            while (nueva_posicion < 0) {
                nueva_posicion += tam_alfabeto;
            }
            nueva_posicion = nueva_posicion % tam_alfabeto; /* Para circularidad si N es muy grande */
            
            mensaje_intermedio[i] = buscar_caracter_por_posicion(nueva_posicion, alfabeto);
        } else {
            /* Si el caracter no esta en el alfabeto, se mantiene sin cambios */
            mensaje_intermedio[i] = mensaje_original[i];
        }
    }
    mensaje_intermedio[len_original] = '\0'; /* Termina la cadena */
}

/*
 * Segunda etapa de codificacion: Suma N a caracteres cuya POSICION en el ALFABETO es multiplo de 3.
 * Circularidad: Si la nueva posicion excede el tam_alfabeto, usa modulo.
 */
void segunda_etapa(char *mensaje_intermedio, char *mensaje_codificado, char *alfabeto, int N) {
    int i;
    int pos_caracter;
    int tam_alfabeto = (int)strlen(alfabeto);
    int nueva_posicion;
    int len_intermedio = (int)strlen(mensaje_intermedio);

    /* Copia el mensaje intermedio al codificado para trabajar sobre el */
    strcpy(mensaje_codificado, mensaje_intermedio); 

    for (i = 0; i < len_intermedio; i++) {
        pos_caracter = buscar_posicion_en_alfabeto(mensaje_codificado[i], alfabeto);
        
        if (pos_caracter != -1) { /* Si el caracter esta en el alfabeto */
            /* Verifica si la POSICION del caracter en el alfabeto es multiplo de 3 */
            if (pos_caracter % 3 == 0) { /* Incluye el 0 */
                nueva_posicion = (pos_caracter + N); 
                nueva_posicion = nueva_posicion % tam_alfabeto; /* Para circularidad */
                mensaje_codificado[i] = buscar_caracter_por_posicion(nueva_posicion, alfabeto);
            }
            /* Si no es multiplo de 3, el caracter se mantiene sin cambios */
        }
        /* Si el caracter no esta en el alfabeto, ya se mantuvo sin cambios desde el strcpy */
    }
    mensaje_codificado[len_intermedio] = '\0'; /* Termina la cadena */
}

/* Graba el mensaje codificado en "codificado.txt" */
void graba_mensaje(char *mensaje_codificado) {
    FILE *archivo;
    archivo = fopen("codificado.txt", "w");
    if (archivo == NULL) {
        printf("Error: No se pudo abrir o crear el archivo 'codificado.txt'\n");
        return;
    }
    fprintf(archivo, "%s", mensaje_codificado);
    fclose(archivo);
    printf("Mensaje codificado guardado en 'codificado.txt'\n");
}

/* Busca la posicion de un caracter dado en el alfabeto */
int buscar_posicion_en_alfabeto(char caracter, char *alfabeto) {
    int i;
    for (i = 0; i < (int)strlen(alfabeto); i++) {
        if (alfabeto[i] == caracter) {
            return i;
        }
    }
    return -1; /* Retorna -1 si el caracter no se encuentra */
}

/* Busca el caracter en una posicion dada del alfabeto */
char buscar_caracter_por_posicion(int posicion, char *alfabeto) {
    return alfabeto[posicion];
}

/* --- Funciones de Decodificación --- */

/*
 * Funcion principal para la decodificacion.
 * Extrae la clave N y el mensaje codificado para luego aplicar las etapas inversas.
 */
void decodificar(char *mensaje_codificado_con_clave, char *mensaje_decodificado, char *alfabeto) {
    char *hash_pos; /* Puntero a la posicion del '#' */
    char clave_char; /* Para almacenar el caracter de la clave */
    int N_clave; /* La clave numerica N */
    char mensaje_solo_codificado[256]; /* Almacena solo la parte del mensaje */
    char mensaje_intermedio_decodificado[256]; /* Resultado despues de la 1ra etapa de decodificacion */
    
    printf("\n--- Proceso de Decodificacion ---\n");
    printf("Mensaje Codificado de Entrada: %s\n", mensaje_codificado_con_clave);

    /* Extraer la clave y el mensaje codificado de la cadena de entrada */
    hash_pos = strchr(mensaje_codificado_con_clave, '#');
    if (hash_pos != NULL) {
        /* La clave es el primer caracter antes del '#' (asumimos un solo digito) */
        clave_char = mensaje_codificado_con_clave[0]; 
        if (clave_char >= '0' && clave_char <= '9') {
            N_clave = clave_char - '0'; /* Convierte el caracter a su valor entero */
        } else {
            printf("Error: La clave N en el mensaje codificado no es un digito valido (0-9).\n");
            strcpy(mensaje_decodificado, "ERROR");
            return;
        }
        /* Copia la parte despues del '#' al mensaje solo codificado */
        strcpy(mensaje_solo_codificado, hash_pos + 1);
    } else {
        printf("Formato de mensaje codificado incorrecto. Se esperaba clave#mensaje.\n");
        strcpy(mensaje_decodificado, "ERROR");
        return;
    }
    printf("Clave N extraida: %d, Mensaje Solo Codificado: %s\n", N_clave, mensaje_solo_codificado);

    /*
     * Primera etapa de decodificacion: Inverso de la segunda etapa de codificacion.
     * Resta N a caracteres cuya POSICION en el ALFABETO es multiplo de 3.
     */
    primera_etapa_decodificar(mensaje_solo_codificado, mensaje_intermedio_decodificado, alfabeto, N_clave);
    printf("Mensaje Intermedio Decodificado (1ra etapa dec.): %s\n", mensaje_intermedio_decodificado);
    
    /*
     * Segunda etapa de decodificacion: Inverso de la primera etapa de codificacion.
     * Suma N a cada caracter.
     */
    segunda_etapa_decodificar(mensaje_intermedio_decodificado, mensaje_decodificado, alfabeto, N_clave);
    printf("Mensaje Final Decodificado: %s\n", mensaje_decodificado);
}

/*
 * Primera etapa de decodificacion: deshace la segunda etapa de codificacion.
 * Resta N a caracteres cuya POSICION en el ALFABETO es multiplo de 3.
 */
void primera_etapa_decodificar(char *mensaje_codificado, char *mensaje_intermedio_decodificado, char *alfabeto, int N) {
    int i;
    int pos_caracter;
    int tam_alfabeto = (int)strlen(alfabeto);
    int nueva_posicion;
    int len_codificado = (int)strlen(mensaje_codificado);

    strcpy(mensaje_intermedio_decodificado, mensaje_codificado); /* Copia para trabajar sobre el */

    for (i = 0; i < len_codificado; i++) {
        pos_caracter = buscar_posicion_en_alfabeto(mensaje_intermedio_decodificado[i], alfabeto);
        
        if (pos_caracter != -1) { /* Si el caracter esta en el alfabeto */
            /* Verifica si la POSICION del caracter en el alfabeto es multiplo de 3 */
            if (pos_caracter % 3 == 0) { /* Incluye el 0 */
                nueva_posicion = (pos_caracter - N); 
                /* Asegura que la nueva posicion sea positiva y dentro del rango */
                while (nueva_posicion < 0) {
                    nueva_posicion += tam_alfabeto;
                }
                nueva_posicion = nueva_posicion % tam_alfabeto;
                mensaje_intermedio_decodificado[i] = buscar_caracter_por_posicion(nueva_posicion, alfabeto);
            }
            /* Si no es multiplo de 3, el caracter se mantiene sin cambios */
        }
    }
    mensaje_intermedio_decodificado[len_codificado] = '\0'; /* Termina la cadena */
}

/*
 * Segunda etapa de decodificacion: deshace la primera etapa de codificacion.
 * Suma N a cada caracter.
 */
void segunda_etapa_decodificar(char *mensaje_intermedio, char *mensaje_decodificado, char *alfabeto, int N) {
    int i;
    int pos_caracter;
    int tam_alfabeto = (int)strlen(alfabeto);
    int nueva_posicion;
    int len_intermedio = (int)strlen(mensaje_intermedio);

    for (i = 0; i < len_intermedio; i++) {
        pos_caracter = buscar_posicion_en_alfabeto(mensaje_intermedio[i], alfabeto);
        
        if (pos_caracter != -1) { /* Si el caracter esta en el alfabeto */
            nueva_posicion = (pos_caracter + N); 
            nueva_posicion = nueva_posicion % tam_alfabeto; /* Para circularidad */
            mensaje_decodificado[i] = buscar_caracter_por_posicion(nueva_posicion, alfabeto);
        } else {
            /* Si el caracter no esta en el alfabeto, se mantiene sin cambios */
            mensaje_decodificado[i] = mensaje_intermedio[i];
        }
    }
    mensaje_decodificado[len_intermedio] = '\0'; /* Termina la cadena */
}