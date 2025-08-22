#include <stdio.h> // Para funciones de entrada/salida: printf, fopen, fclose, fprintf, scanf, fgets
#include <string.h> // Para funciones de manejo de cadenas: strlen, strchr, strcpy, sprintf

/* --- Prototipos de Funciones (Declaraciones Adelantadas) --- */

/* Funciones principales del programa */
void seleccionar_opcion_y_ejecutar(char *, char *, char *, char *);

/* Funciones de Cifrado */
void codificar(char *, char *, char *, int);
void primera_etapa(char *, char *, char *, int); 
void segunda_etapa(char *, char *, char *, int); 

/* Funciones de Descifrado */
void decodificar(char *, char *, char *);
void primera_etapa_decodificar(char *, char *, char *, int);
void segunda_etapa_decodificar(char *, char *, char *, int);

/* Funciones de Archivo y Utilidad */
void lee_original(char *, int *); 
void lee_codificado(char *, int *); 
void graba_mensaje(char *); 
void graba_decodificado(char *); 
void inicializa_alfabeto(char *);
int buscar_posicion_en_alfabeto(char, char *);
char buscar_caracter_por_posicion(int, char *);


/* ============================================================= */
/* --- IMPLEMENTACIÓN DE FUNCIONES EN ORDEN LÓGICO DE EJECUCIÓN --- */
/* ============================================================= */


/* --- 1. Función Principal (Punto de Entrada del Programa) --- */
int main() {
    char original[256]; 
    char alfabeto[50];  
    char codificado[256];
    char decodificado[256]; 
    
    // Lo primero es preparar el alfabeto
    inicializa_alfabeto(alfabeto);
    
    // Luego, se presenta el menú y se gestiona la operación
    seleccionar_opcion_y_ejecutar(original, alfabeto, codificado, decodificado);

    return 0; 
}

/* --- 2. Funciones de Interfaz de Usuario y Orquestación --- */

/* Gestiona la selección de opciones del usuario y coordina las operaciones */
void seleccionar_opcion_y_ejecutar(char *original, char *alfabeto, char *codificado, char *decodificado) {
    int opcion;
    int N; // La clave N

    printf("Seleccione una opcion:\n");
    printf("1. Codificar un mensaje (desde original.txt)\n");
    printf("2. Decodificar un mensaje (desde codificado.txt)\n"); 
    printf("Ingrese su opcion (1 o 2): ");
    scanf("%d", &opcion);
    // Limpia el buffer de entrada para evitar problemas con lecturas posteriores
    while (getchar() != '\n'); 

    if (opcion == 1) {
        // Lee el mensaje original y la clave N
        lee_original(original, &N); 
        // Codifica el mensaje
        codificar(original, codificado, alfabeto, N);
        // Graba el mensaje codificado
        graba_mensaje(codificado);
    } else if (opcion == 2) {
        // Lee el mensaje codificado y la clave N
        lee_codificado(codificado, &N);
        // Decodifica el mensaje
        decodificar(codificado, decodificado, alfabeto);
        // Graba el mensaje decodificado
        graba_decodificado(decodificado);
    } else {
        printf("Opcion invalida.\n");
    }
}

/* --- 3. Funciones de Lectura/Escritura de Archivos --- */

/* Inicializa el vector del alfabeto */
void inicializa_alfabeto(char *alfabeto) {
    strcpy(alfabeto, "ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789!,.:;?-+*/");
}

/* Lee el mensaje original y la clave N desde "original.txt" */
void lee_original(char *mensaje_original, int *N_ptr) {
    FILE *archivo;
    char linea_completa[256]; 
    char *hash_pos; 
    char clave_char; 
    
    archivo = fopen("original.txt", "r");
    if (archivo == NULL) {
        printf("Error: No se pudo abrir el archivo 'original.txt'.\n");
        *N_ptr = 0; 
        strcpy(mensaje_original, ""); 
        return;
    }

    if (fgets(linea_completa, sizeof(linea_completa), archivo) != NULL) {
        // Elimina el salto de linea si existe
        if (strlen(linea_completa) > 0 && linea_completa[strlen(linea_completa) - 1] == '\n') {
            linea_completa[strlen(linea_completa) - 1] = '\0';
        }
        hash_pos = strchr(linea_completa, '#');

        if (hash_pos != NULL) {
            clave_char = linea_completa[0]; 
            if (clave_char >= '0' && clave_char <= '9') {
                *N_ptr = clave_char - '0'; 
            } else {
                printf("Error: La clave N en 'original.txt' no es un digito valido.\n");
                *N_ptr = 0;
                strcpy(mensaje_original, "");
            }
            strcpy(mensaje_original, hash_pos + 1); 
        } else {
            printf("Formato de archivo 'original.txt' incorrecto.\n");
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

/* Graba el mensaje codificado en "codificado.txt" */
void graba_mensaje(char *mensaje_codificado) {
    FILE *archivo;
    archivo = fopen("codificado.txt", "w");
    if (archivo == NULL) {
        printf("Error al crear 'codificado.txt'\n");
        return;
    }
    fprintf(archivo, "%s", mensaje_codificado);
    fclose(archivo);
    printf("Mensaje codificado guardado en 'codificado.txt'.\n");
}

/* Lee el mensaje codificado y la clave N desde "codificado.txt" */
void lee_codificado(char *mensaje_codificado_con_clave, int *N_ptr) {
    FILE *archivo;
    char linea_completa[256];
    char *hash_pos;
    char clave_char;
    
    archivo = fopen("codificado.txt", "r");
    if (archivo == NULL) {
        printf("Error: No se pudo abrir el archivo 'codificado.txt'.\n");
        *N_ptr = 0;
        strcpy(mensaje_codificado_con_clave, "");
        return 0; // Indicar fallo
    }

    if (fgets(linea_completa, sizeof(linea_completa), archivo) != NULL) {
        if (strlen(linea_completa) > 0 && linea_completa[strlen(linea_completa) - 1] == '\n') {
            linea_completa[strlen(linea_completa) - 1] = '\0';
        }
        hash_pos = strchr(linea_completa, '#');

        if (hash_pos != NULL) {
            clave_char = linea_completa[0]; 
            if (clave_char >= '0' && clave_char <= '9') {
                *N_ptr = clave_char - '0'; 
            } else {
                printf("Error: La clave N en 'codificado.txt' no es un digito valido.\n");
                *N_ptr = 0;
                strcpy(mensaje_codificado_con_clave, "");
                fclose(archivo);
                return 0;
            }
            strcpy(mensaje_codificado_con_clave, linea_completa); // Copia la linea completa
            fclose(archivo);
            return 1; // Indicar exito
        } else {
            printf("Formato de archivo 'codificado.txt' incorrecto.\n");
            *N_ptr = 0;
            strcpy(mensaje_codificado_con_clave, "");
            fclose(archivo);
            return 0;
        }
    } else {
        printf("El archivo 'codificado.txt' esta vacio o no se pudo leer.\n");
        *N_ptr = 0;
        strcpy(mensaje_codificado_con_clave, "");
        fclose(archivo);
        return 0;
    }
}

/* Graba el mensaje decodificado en "decodificado.txt" */
void graba_decodificado(char *mensaje_decodificado) {
    FILE *archivo;
    archivo = fopen("decodificado.txt", "w");
    if (archivo == NULL) {
        printf("Error al crear 'decodificado.txt'\n");
        return;
    }
    fprintf(archivo, "%s", mensaje_decodificado);
    fclose(archivo);
    printf("Mensaje decodificado guardado en 'decodificado.txt'.\n");
}


/* --- 4. Funciones de Cifrado (Codificación) --- */

/* Función principal para la codificación */
void codificar(char *mensaje_original, char *mensaje_codificado, char *alfabeto, int N) {
    char mensaje_intermedio[256]; 
    char temp_codificado_sin_clave[256]; 
    char N_char = N + '0'; // Convierte N de int a char
    
    // Primera etapa de codificación
    primera_etapa(mensaje_original, mensaje_intermedio, alfabeto, N);
    // Segunda etapa de codificación
    segunda_etapa(mensaje_intermedio, temp_codificado_sin_clave, alfabeto, N);

    // Formatea el mensaje final con la clave y el '#'
    sprintf(mensaje_codificado, "%c#%s", N_char, temp_codificado_sin_clave);
}

/* Primera etapa de codificación: desplazamiento hacia la izquierda (resta N) */
void primera_etapa(char *mensaje_original, char *mensaje_intermedio, char *alfabeto, int N) {
    int i;
    int pos_caracter;
    int tam_alfabeto = (int)strlen(alfabeto);
    int nueva_posicion;
    int len_original = (int)strlen(mensaje_original);
    
    for (i = 0; i < len_original; i++) {
        pos_caracter = buscar_posicion_en_alfabeto(mensaje_original[i], alfabeto);
        
        if (pos_caracter != -1) { // Si el caracter está en el alfabeto
            nueva_posicion = (pos_caracter - N); 
            
            // Asegura que la nueva posición sea positiva y dentro del rango (circularidad)
            while (nueva_posicion < 0) {
                nueva_posicion += tam_alfabeto;
            }
            nueva_posicion = nueva_posicion % tam_alfabeto; // Para circularidad si N es muy grande
            
            mensaje_intermedio[i] = buscar_caracter_por_posicion(nueva_posicion, alfabeto);
        } else {
            // Si el caracter no está en el alfabeto, se mantiene sin cambios
            mensaje_intermedio[i] = mensaje_original[i];
        }
    }
    mensaje_intermedio[len_original] = '\0'; // Termina la cadena
}

/* Segunda etapa de codificación: Suma N a caracteres cuya POSICIÓN en el ALFABETO es múltiplo de 3 */
void segunda_etapa(char *mensaje_intermedio, char *mensaje_codificado, char *alfabeto, int N) {
    int i;
    int pos_caracter;
    int tam_alfabeto = (int)strlen(alfabeto);
    int nueva_posicion;
    int len_intermedio = (int)strlen(mensaje_intermedio);

    // Copia el mensaje intermedio al codificado para trabajar sobre él
    strcpy(mensaje_codificado, mensaje_intermedio); 

    for (i = 0; i < len_intermedio; i++) {
        pos_caracter = buscar_posicion_en_alfabeto(mensaje_codificado[i], alfabeto);
        
        if (pos_caracter != -1) { // Si el caracter está en el alfabeto
            // Verifica si la POSICIÓN del caracter en el alfabeto es múltiplo de 3 (incluye el 0)
            if (pos_caracter % 3 == 0) { 
                nueva_posicion = (pos_caracter + N); 
                nueva_posicion = nueva_posicion % tam_alfabeto; // Para circularidad
                mensaje_codificado[i] = buscar_caracter_por_posicion(nueva_posicion, alfabeto);
            }
            // Si no es múltiplo de 3, el caracter se mantiene sin cambios
        }
        // Si el caracter no está en el alfabeto, ya se mantuvo sin cambios desde el strcpy
    }
    mensaje_codificado[len_intermedio] = '\0'; // Termina la cadena
}


/* --- 5. Funciones de Descifrado (Decodificación) --- */

/* Función principal para la decodificación */
void decodificar(char *mensaje_codificado_con_clave, char *mensaje_decodificado, char *alfabeto) {
    char *hash_pos; 
    int N_clave; 
    char mensaje_solo_codificado[256]; 
    char mensaje_intermedio_decodificado[256]; 
    
    // Extraer la clave y el mensaje codificado del string
    hash_pos = strchr(mensaje_codificado_con_clave, '#');
    // Asumimos que hash_pos no es NULL porque ya fue verificado en lee_codificado
    N_clave = mensaje_codificado_con_clave[0] - '0'; 
    strcpy(mensaje_solo_codificado, hash_pos + 1);

    // Primera etapa de decodificación: deshace la segunda etapa de codificación
    primera_etapa_decodificar(mensaje_solo_codificado, mensaje_intermedio_decodificado, alfabeto, N_clave);
    // Segunda etapa de decodificación: deshace la primera etapa de codificación
    segunda_etapa_decodificar(mensaje_intermedio_decodificado, mensaje_decodificado, alfabeto, N_clave);
}

/* Primera etapa de decodificación: deshace la segunda etapa de codificación */
void primera_etapa_decodificar(char *mensaje_codificado, char *mensaje_intermedio_decodificado, char *alfabeto, int N) {
    int i;
    int pos_caracter;
    int tam_alfabeto = (int)strlen(alfabeto);
    int nueva_posicion;
    int len_codificado = (int)strlen(mensaje_codificado);

    strcpy(mensaje_intermedio_decodificado, mensaje_codificado); // Copia para trabajar sobre él

    for (i = 0; i < len_codificado; i++) {
        pos_caracter = buscar_posicion_en_alfabeto(mensaje_intermedio_decodificado[i], alfabeto);
        
        if (pos_caracter != -1) { 
            if (pos_caracter % 3 == 0) { 
                nueva_posicion = (pos_caracter - N); 
                while (nueva_posicion < 0) {
                    nueva_posicion += tam_alfabeto;
                }
                nueva_posicion = nueva_posicion % tam_alfabeto;
                mensaje_intermedio_decodificado[i] = buscar_caracter_por_posicion(nueva_posicion, alfabeto);
            }
        }
    }
    mensaje_intermedio_decodificado[len_codificado] = '\0'; 
}

/* Segunda etapa de decodificación: deshace la primera etapa de codificación */
void segunda_etapa_decodificar(char *mensaje_intermedio, char *mensaje_decodificado, char *alfabeto, int N) {
    int i;
    int pos_caracter;
    int tam_alfabeto = (int)strlen(alfabeto);
    int nueva_posicion;
    int len_intermedio = (int)strlen(mensaje_intermedio);

    for (i = 0; i < len_intermedio; i++) {
        pos_caracter = buscar_posicion_en_alfabeto(mensaje_intermedio[i], alfabeto);
        
        if (pos_caracter != -1) { 
            nueva_posicion = (pos_caracter + N); 
            nueva_posicion = nueva_posicion % tam_alfabeto; 
            mensaje_decodificado[i] = buscar_caracter_por_posicion(nueva_posicion, alfabeto);
        } else {
            mensaje_decodificado[i] = mensaje_intermedio[i];
        }
    }
    mensaje_decodificado[len_intermedio] = '\0'; 
}

/* --- 6. Funciones Auxiliares Generales --- */

/* Busca la posición de un caracter dado en el alfabeto */
int buscar_posicion_en_alfabeto(char caracter, char *alfabeto) {
    int i;
    for (i = 0; i < (int)strlen(alfabeto); i++) {
        if (alfabeto[i] == caracter) {
            return i;
        }
    }
    return -1; // Retorna -1 si el caracter no se encuentra
}

/* Busca el caracter en una posición dada del alfabeto */
char buscar_caracter_por_posicion(int posicion, char *alfabeto) {
    return alfabeto[posicion];
}