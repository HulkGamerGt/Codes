#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TAM 36
#define TOTAL 9999

void menu(int *);
void option(int, const char *[TAM], char [TAM]);
void mostrar_lista(const char *[TAM], char [TAM]);
void morse_tex(const char *[TAM], char [TAM]);
void tex_morse(const char *[TAM], char [TAM]);
void leer(char *);

int main() {
    int opcion;
    const char *morse[TAM] = {
        ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
        "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
        "..-", "...-", ".--", "-..-", "-.--", "--..", "-----", ".----", "..---",
        "...--", "....-", ".....", "-....", "--...", "---..", "----."
    };
    char letras_morse[TAM] = {
        'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R',
        'S','T','U','V','W','X','Y','Z','0','1','2','3','4','5','6','7','8','9'
    };

    do {
        menu(&opcion);
        option(opcion, morse, letras_morse);
    } while (opcion != 4);

    printf("\nPrograma finalizado.\n");
    return 0;
}

void menu(int *opcion) {
    printf("\n________________________________\n");
    printf("======= Menu =======\n");
    printf("________________________________\n");
    printf("1. Modo Aprendizaje\n");
    printf("2. Texto a Morse\n");
    printf("3. Morse a Texto\n");
    printf("4. Salir\n");
    printf("Elige una opcion [1-4]: ");

    if (scanf("%d", opcion) != 1) {
        printf("Error: Entrada invalida.\n");
        while (getchar() != '\n');
        *opcion = 0;
        return;
    }
    getchar(); // Limpia el \n del scanf
}

void option(int opcion, const char *morse[TAM], char letras_morse[TAM]) {
    switch (opcion) {
        case 1: mostrar_lista(morse, letras_morse); break;
        case 2: tex_morse(morse, letras_morse); break;
        case 3: morse_tex(morse, letras_morse); break;
        case 4: printf("\nSaliendo del programa...\n"); break;
        default: printf("Opcion invalida.\n"); break;
    }
}

void mostrar_lista(const char *morse[TAM], char letras_morse[TAM]) {
    printf("\n=== Tabla de Codigo Morse ===\n");
    for (int i = 0; i < TAM; i++) {
        printf("%c = %s\n", letras_morse[i], morse[i]);
    }
    printf("\n");
}

/* =============== TEXTO → MORSE =============== */
void tex_morse(const char *morse[TAM], char letras_morse[TAM]) {
    char texto[TOTAL];
    leer(texto);
    printf("Traduccion a Morse: ");

    int primera_letra = 1;
    for (int i = 0; texto[i]; i++) {
        char c = toupper(texto[i]);
        
        if (c == ' ') {
            // Espacio entre palabras - se representa con 3 espacios en morse
            if (!primera_letra) {
                printf("  "); // Dos espacios adicionales (total 3 con el espacio que ya hay)
            }
            primera_letra = 1;
            continue;
        }
        
        int encontrado = 0;
        for (int j = 0; j < TAM; j++) {
            if (c == letras_morse[j]) {
                if (!primera_letra) printf(" ");
                printf("%s", morse[j]);
                encontrado = 1;
                primera_letra = 0;
                break;
            }
        }
        if (!encontrado && c != '\n') {
            if (!primera_letra) printf(" ");
            printf("?");
            primera_letra = 0;
        }
    }
    printf("\n");
}

/* =============== MORSE → TEXTO =============== */
void morse_tex(const char *morse[TAM], char letras_morse[TAM]) {
    char entrada[TOTAL];
    char codigo[20];
    int i = 0, j = 0;
    int espacios_seguidos = 0;

    leer(entrada);
    printf("Traduccion a Texto: ");

    while (entrada[i]) {
        char c = entrada[i];

        if (c == '.' || c == '-') {
            if (j < 19) {
                codigo[j++] = c;
            }
            espacios_seguidos = 0;
        }
        else if (c == ' ') {
            if (j > 0) {
                // Procesar código morse completo
                codigo[j] = '\0';
                int encontrado = 0;
                for (int k = 0; k < TAM; k++) {
                    if (strcmp(codigo, morse[k]) == 0) {
                        printf("%c", letras_morse[k]);
                        encontrado = 1;
                        break;
                    }
                }
                if (!encontrado) printf("?");
                j = 0;
            }
            
            espacios_seguidos++;
            
            // Si hay 3 espacios seguidos, es un espacio entre palabras
            if (espacios_seguidos == 3) {
                printf(" ");
                espacios_seguidos = 0;
            }
        }
        else if (c != '\n') {
            // Carácter inválido, ignorar
            espacios_seguidos = 0;
        }
        i++;
    }

    // Procesar último código si queda alguno
    if (j > 0) {
        codigo[j] = '\0';
        int encontrado = 0;
        for (int k = 0; k < TAM; k++) {
            if (strcmp(codigo, morse[k]) == 0) {
                printf("%c", letras_morse[k]);
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) printf("?");
    }
    printf("\n");
}

/* =============== FUNCIÓN LEER =============== */
void leer(char *lectura) {
    printf("\nIntroduce el texto a procesar: ");
    
    if (fgets(lectura, TOTAL, stdin)) {
        // Eliminar el salto de línea al final
        lectura[strcspn(lectura, "\n")] = '\0';
    }
}