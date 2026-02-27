#include <stdio.h>
#include <string.h>

/* Prototipos de Funciones */
void inicializa_alfabeto(char *alfabeto);
void lee_original(char *mensaje, int *N);
void graba_mensaje(char *mensaje_codificado, int N);
void codificar(char *mensaje_original, char *mensaje_codificado, char *alfabeto, int N);
void primera_etapa(char *mensaje_original, char *mensaje_intermedio, char *alfabeto, int N);
void segunda_etapa(char *mensaje_intermedio, char *mensaje_codificado, char *alfabeto, int N);
int buscar_posicion_en_alfabeto(char caracter, char *alfabeto);
char buscar_caracter_por_posicion(int posicion, char *alfabeto);


/* Función Principal */
int main() {
    char original[100];
    char alfabeto[48]; // 47 caracteres + '\0'
    char codificado[100];
    int clave_n;

    inicializa_alfabeto(alfabeto);
    lee_original(original, &clave_n);
    
    if (clave_n > 0 && strlen(original) > 0) { 
        codificar(original, codificado, alfabeto, clave_n);
        graba_mensaje(codificado, clave_n);
    } else {
        printf("No se pudo codificar debido a un error en la lectura del archivo o datos inválidos.\n");
    }

    return 0;
}

/* Inicializa el vector del alfabeto con los caracteres definidos */
void inicializa_alfabeto(char *alfabeto) {
    // A-Z (26) + ' ' (1) + 0-9 (10) + !,.:;?-+*/ (10) = 47 caracteres
    strcpy(alfabeto, "ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789!,.:;?-+*/");
}

/* Busca la posición de un carácter en el alfabeto */
int buscar_posicion_en_alfabeto(char caracter, char *alfabeto) {
    int i;
    for (i = 0; i < strlen(alfabeto); i++) {
        if (alfabeto[i] == caracter) {
            return i;
        }
    }
    return -1; // Retorna -1 si el carácter no se encuentra
}

/* Obtiene el carácter en una posición específica del alfabeto
   Asegura que el índice sea SIEMPRE positivo y dentro del rango. */
char buscar_caracter_por_posicion(int posicion, char *alfabeto) {
    int tamano = strlen(alfabeto);
    int indice_final = posicion % tamano;
    
    // Asegurar que el resultado del módulo sea positivo
    if (indice_final < 0) {
        indice_final += tamano;
    }
    return alfabeto[indice_final];
}

/* Lee el mensaje original y la clave N desde "original.txt" */
void lee_original(char *mensaje, int *N) {
    FILE *archivo;
    char linea[100];
    int i = 0;
    
    archivo = fopen("original.txt", "r");
    if (archivo == NULL) {
        printf("Error: No se pudo abrir 'original.txt'\n");
        *N = 0; // Indica error en N
        mensaje[0] = '\0'; // Vacía el mensaje
        return; 
    }

    if (fgets(linea, sizeof(linea), archivo) == NULL) {
        printf("Error: Archivo vacío o no se pudo leer 'original.txt'\n");
        fclose(archivo);
        *N = 0;
        mensaje[0] = '\0';
        return;
    }

    // Eliminar salto de línea manualmente
    int len_linea = strlen(linea);
    if (len_linea > 0 && linea[len_linea - 1] == '\n') {
        linea[len_linea - 1] = '\0';
    }
    
    /* Convertir la parte numérica antes del # */
    *N = 0;
    while (linea[i] != '\0' && linea[i] != '#') {
        if (linea[i] >= '0' && linea[i] <= '9') {
            *N = *N * 10 + (linea[i] - '0');
            i++;
        } else {
            printf("Error: La clave N debe ser numérica en 'original.txt'\n");
            fclose(archivo);
            *N = 0;
            mensaje[0] = '\0';
            return;
        }
    }

    if (linea[i] != '#') {
        printf("Error: Formato incorrecto en 'original.txt'. Debe ser N#mensaje\n");
        fclose(archivo);
        *N = 0;
        mensaje[0] = '\0';
        return;
    }

    strcpy(mensaje, &linea[i+1]);  /* Copiar el mensaje después del # */
    fclose(archivo);
}

/* Graba el mensaje codificado en "codificado.txt" con el formato N#mensaje */
void graba_mensaje(char *mensaje_codificado, int N) {
    FILE *archivo = fopen("codificado.txt", "w");
    if (archivo == NULL) {
        printf("Error al crear 'codificado.txt'\n");
        return;
    }
    fprintf(archivo, "%d#%s", N, mensaje_codificado);
    fclose(archivo);
}

/* Función principal de codificación */
void codificar(char *mensaje_original, char *mensaje_codificado, char *alfabeto, int N) {
    char intermedio[100];
    
    primera_etapa(mensaje_original, intermedio, alfabeto, N);
    segunda_etapa(intermedio, mensaje_codificado, alfabeto, N);
}

/* Primera etapa: Suma N a la posición de cada carácter */
void primera_etapa(char *mensaje_original, char *mensaje_intermedio, char *alfabeto, int N) {
    int i, pos;
    for (i = 0; mensaje_original[i] != '\0'; i++) {
        pos = buscar_posicion_en_alfabeto(mensaje_original[i], alfabeto);
        if (pos != -1) {
            int nueva_pos = pos + N; 
            mensaje_intermedio[i] = buscar_caracter_por_posicion(nueva_pos, alfabeto);
        } else {
            /*Si el caracter no está en el alfabeto, se mantiene igual*/
            mensaje_intermedio[i] = mensaje_original[i];
        }
    }
    mensaje_intermedio[i] = '\0';
}

/* Segunda etapa: Resta N a caracteres cuya POSICIÓN EN EL ALFABETO es múltiplo de 4 (o 0) */
void segunda_etapa(char *mensaje_intermedio, char *mensaje_codificado, char *alfabeto, int N) {
    int i, pos;
    strcpy(mensaje_codificado, mensaje_intermedio); // Inicializa con el resultado de la primera etapa
    
    for (i = 0; mensaje_codificado[i] != '\0'; i++) {
        pos = buscar_posicion_en_alfabeto(mensaje_codificado[i], alfabeto);
        // La condición es sobre la 'pos' (posición del carácter en el ALFABETO)
        // y 0 es considerado múltiplo de cualquier número.
        if (pos != -1 && pos % 4 == 0) {  
            int nueva_pos = pos - N; 
            mensaje_codificado[i] = buscar_caracter_por_posicion(nueva_pos, alfabeto);
        }
    }
    mensaje_codificado[i] = '\0';
}