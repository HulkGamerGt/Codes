#include <stdio.h> /* Standard input/output library */
#include <string.h> /* String manipulation library */

#define ALPHABET_SIZE 47 

/* Función auxiliar para obtener el índice de un carácter en el alfabeto */
int get_alphabet_index(char c, const char *alfabeto) {
    int j;
    for (j = 0; j < ALPHABET_SIZE; j++) {
        if (alfabeto[j] == c) {
            return j;
        }
    }
    return -1; /* Indica que el carácter no fue encontrado */
}

/* Prototipos de funciones */
void lee_original(char *, int *);
void lee_codificado(char *, int *);
void inicializa_alfabeto(char *);

void primera_etapa(char *, char *, const char *, int);
void segunda_etapa(char *, char *, const char *, int);
void codificar(char *, char *, char *, int);
void graba_mensaje(const char *, int);

void primera_etapa_decodificacion(char *, char *, const char *, int);
void segunda_etapa_decodificacion(char *, char *, const char *, int);
void decodificar(char *, char *, char *, int);
void graba_decodificado(const char *, int);

int main() {
    char original[100];
    char alfabeto[ALPHABET_SIZE + 1]; /* +1 para el terminador nulo */
    char codificado[100];
    char decodificado[100];
    int N;
    int choice;

    inicializa_alfabeto(alfabeto);

    do {
        printf("\n--- Menu de Cifrado/Descifrado ---\n");
        printf("1. Codificar Mensaje\n");
        printf("2. Decodificar Mensaje\n");
        printf("3. Salir\n");
        printf("Ingrese su opcion: ");
        
        /* Manejo de entrada para evitar bucles infinitos en caso de entrada no numérica */
        if (scanf("%d", &choice) != 1) {
            printf("Entrada invalida. Por favor, ingrese un numero.\n");
            while (getchar() != '\n'); /* Limpiar el buffer de entrada */
            continue;
        }
        while (getchar() != '\n'); /* Limpiar el buffer de entrada */

        switch (choice) {
            case 1:
                printf("Realizando codificacion...\n");
                lee_original(original, &N);
                if (N != -1 && original[0] != '\0') {
                    codificar(original, codificado, alfabeto, N);
                    graba_mensaje(codificado, N);
                    printf("Mensaje codificado y guardado en codificado.txt\n");
                    printf("Mensaje codificado resultante para N=%d: %s\n", N, codificado); /* Mostrar el resultado */
                } else {
                    printf("No se pudo realizar la codificacion debido a errores de lectura del archivo.\n");
                }
                break;
            case 2:
                printf("Realizando decodificacion...\n"); 
                lee_codificado(codificado, &N);
                if (N != -1 && codificado[0] != '\0') {
                    decodificar(codificado, decodificado, alfabeto, N);
                    graba_decodificado(decodificado, N);
                    printf("Mensaje decodificado y guardado en decodificado.txt\n");
                    printf("Mensaje decodificado resultante para N=%d: %s\n", N, decodificado); /* Mostrar el resultado sin validación */
                } else {
                    printf("No se pudo realizar la decodificacion debido a errores de lectura del archivo.\n");
                }
                break;
            case 3:
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opcion invalida. Intente de nuevo.\n");
                break;
        }
    } while (choice != 3);

    return 0;
}

/* Lee el mensaje original y el valor N del archivo original.txt */
void lee_original(char *original, int *N_ptr) {
    FILE *file = fopen("original.txt", "r");
    if (file == NULL) {
        printf("Error: No se pudo abrir el archivo original.txt\n");
        *N_ptr = -1; /* Indicar error */
        original[0] = '\0';
        return;
    }

    /* Espera el formato N#MENSAJE */
    if (fscanf(file, "%d#%[^\n]", N_ptr, original) != 2) { 
        printf("Error: Formato incorrecto en original.txt. Esperado N#MENSAJE\n");
        *N_ptr = -1;
        original[0] = '\0';
    }

    fclose(file);
}

/* Inicializa el alfabeto */
void inicializa_alfabeto(char *alfabeto) {
    strcpy(alfabeto, "ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789!.,:;?-+*/");
}

/* Primera etapa de codificación: Restar N a la posición del carácter */
void primera_etapa(char *original_msg, char *first_stage_result, const char *alfabeto, int N) {
    int len = strlen(original_msg);
    int i;
    for (i = 0; i < len; i++) {
        char current_char = original_msg[i];
        int original_idx = get_alphabet_index(current_char, alfabeto);

        if (original_idx != -1) {
            int new_idx = (original_idx - N);
            /* Asegurar que el índice sea positivo y esté dentro del rango del alfabeto */
            new_idx = (new_idx % ALPHABET_SIZE + ALPHABET_SIZE) % ALPHABET_SIZE;
            first_stage_result[i] = alfabeto[new_idx];
        } else {
            first_stage_result[i] = current_char; /* Mantener caracteres no encontrados en el alfabeto */
        }
    }
    first_stage_result[len] = '\0'; /* Asegurar terminador nulo */
}

/* Segunda etapa de codificación: Sumar N si la posición del carácter resultante de la 1ª etapa en el alfabeto es múltiplo de 3 */
void segunda_etapa(char *first_stage_msg, char *second_stage_result, const char *alfabeto, int N) {
    int len = strlen(first_stage_msg);
    int i;
    for (i = 0; i < len; i++) {
        char current_char = first_stage_msg[i];
        int current_char_idx_in_alphabet = get_alphabet_index(current_char, alfabeto);

        if (current_char_idx_in_alphabet != -1) {
            /* Se aplica la suma si el *índice en el alfabeto del caracter actual* es múltiplo de 3 */
            if (current_char_idx_in_alphabet % 3 == 0) { 
                int new_idx = (current_char_idx_in_alphabet + N) % ALPHABET_SIZE;
                second_stage_result[i] = alfabeto[new_idx];
            } else {
                second_stage_result[i] = current_char; /* Si no es múltiplo de 3, el carácter se mantiene */
            }
        } else {
            second_stage_result[i] = current_char; /* Mantener caracteres no encontrados en el alfabeto */
        }
    }
    second_stage_result[len] = '\0'; /* Asegurar terminador nulo */
}

/* Orquesta las etapas de codificación */
void codificar(char *original, char *codificado, char *alfabeto, int N) {
    char temp_result_first_stage[100]; /* Buffer para el resultado de la primera etapa */
    
    primera_etapa(original, temp_result_first_stage, alfabeto, N);
    
    segunda_etapa(temp_result_first_stage, codificado, alfabeto, N);
}

/* Graba el mensaje codificado en codificado.txt */
void graba_mensaje(const char *codificado, int N) {
    FILE *file = fopen("codificado.txt", "w");
    if (file == NULL) {
        printf("Error: No se pudo crear/abrir el archivo codificado.txt\n");
        return;
    }

    fprintf(file, "%d#%s", N, codificado); /* Escribe N#MENSAJE_CODIFICADO */

    fclose(file);
}

/* Lee el mensaje codificado y N del archivo codificado.txt */
void lee_codificado(char *codificado, int *N_ptr) {
    FILE *file = fopen("codificado.txt", "r");
    if (file == NULL) {
        printf("Error: No se pudo abrir el archivo codificado.txt\n");
        *N_ptr = -1;
        codificado[0] = '\0';
        return;
    }
    /* Espera el formato N#MENSAJE_CODIFICADO */
    if (fscanf(file, "%d#%[^\n]", N_ptr, codificado) != 2) {
        printf("Error: Formato incorrecto en codificado.txt. Esperado N#MENSAJE_CODIFICADO\n");
        *N_ptr = -1;
        codificado[0] = '\0';
    }
    fclose(file);
}

/* Primera etapa de decodificación (invierte la segunda etapa de codificación) */
void primera_etapa_decodificacion(char *message_to_decode, char *temp_result, const char *alfabeto, int N) {
    int len = strlen(message_to_decode);
    int i;
    for (i = 0; i < len; i++) {
        char current_char = message_to_decode[i];
        int current_char_idx_in_alphabet = get_alphabet_index(current_char, alfabeto);

        if (current_char_idx_in_alphabet != -1) {
            /* Si el índice en el alfabeto del caracter actual fue múltiplo de 3 en la codificación, se resta N */
            if (current_char_idx_in_alphabet % 3 == 0) { 
                int new_idx = (current_char_idx_in_alphabet - N);
                new_idx = (new_idx % ALPHABET_SIZE + ALPHABET_SIZE) % ALPHABET_SIZE; /* Asegurar positivo */
                temp_result[i] = alfabeto[new_idx];
            } else {
                temp_result[i] = current_char; 
            }
        } else {
            temp_result[i] = current_char; 
        }
    }
    temp_result[len] = '\0';
}

/* Segunda etapa de decodificación (invierte la primera etapa de codificación) */
void segunda_etapa_decodificacion(char *temp_result_from_first_decode, char *final_decoded_message, const char *alfabeto, int N) {
    int len = strlen(temp_result_from_first_decode);
    int i;
    for (i = 0; i < len; i++) {
        char current_char = temp_result_from_first_decode[i];
        int current_char_idx_in_alphabet = get_alphabet_index(current_char, alfabeto);

        if (current_char_idx_in_alphabet != -1) {
            /* Invertir la resta de N: sumar N */
            int new_idx = (current_char_idx_in_alphabet + N) % ALPHABET_SIZE;
            final_decoded_message[i] = alfabeto[new_idx];
        } else {
            final_decoded_message[i] = current_char; 
        }
    }
    final_decoded_message[len] = '\0';
}

/* Orquesta las etapas de decodificación */
void decodificar(char *codificado, char *decodificado, char *alfabeto, int N) {
    char temp_result_first_decode[100]; /* Buffer para el resultado de la primera etapa de decodificación */
    
    /* Primero, revertir la segunda etapa de codificación */
    primera_etapa_decodificacion(codificado, temp_result_first_decode, alfabeto, N);
    
    /* Luego, revertir la primera etapa de codificación */
    segunda_etapa_decodificacion(temp_result_first_decode, decodificado, alfabeto, N);
}

/* Graba el mensaje decodificado en decodificado.txt */
void graba_decodificado(const char *decodificado, int N) {
    FILE *file = fopen("decodificado.txt", "w");
    if (file == NULL) {
        printf("Error: No se pudo crear/abrir el archivo decodificado.txt\n");
        return;
    }
    /* Escribe solo el mensaje decodificado, sin el N# */
    fprintf(file, "%s", decodificado); 
    fclose(file);
}