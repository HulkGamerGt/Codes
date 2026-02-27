#include <stdio.h>
#include <string.h>

#define ALFABETO_SIZE 47
#define MAX_MENSAJE 100

void inicializa_alfabeto(char *alfabeto) {
    char temp[ALFABETO_SIZE] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
        ' ', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        '!', ',', '.', ':', ';', '?', '-', '+', '*', '/'
    };
    int i;
    for (i = 0; i < ALFABETO_SIZE; i++) {
        alfabeto[i] = temp[i];
    }
}

void lee_original(char *mensaje, int *N) {
    FILE *archivo = fopen("original.txt", "r");
    if (archivo == NULL) {
        printf("Error al abrir original.txt\n");
        return;
    }
    fscanf(archivo, "%d#", N);
    int i = 0;
    char c;
    while ((c = fgetc(archivo)) != EOF && i < MAX_MENSAJE - 1) {
        mensaje[i++] = c;
    }
    mensaje[i] = '\0';
    fclose(archivo);
}

int encuentra_posicion(char c, char *alfabeto) {
    int i;
    for (i = 0; i < ALFABETO_SIZE; i++) {
        if (alfabeto[i] == c) return i;
    }
    return -1;
}

void primera_etapa(char *original, char *resultado, char *alfabeto, int N) {
    int i = 0;
    while (original[i] != '\0') {
        int pos = encuentra_posicion(original[i], alfabeto);
        if (pos != -1) {
            int nueva_pos = ((pos - N) % ALFABETO_SIZE + ALFABETO_SIZE) % ALFABETO_SIZE;
            resultado[i] = alfabeto[nueva_pos];
        } else {
            resultado[i] = original[i];
        }
        i++;
    }
    resultado[i] = '\0';
}

void segunda_etapa(char *intermedio, char *resultado, char *alfabeto, int N) {
    int i = 0;
    while (intermedio[i] != '\0') {
        if (i % 3 == 0) {
            int pos = encuentra_posicion(intermedio[i], alfabeto);
            if (pos != -1) {
                int nueva_pos = ((pos + N) % ALFABETO_SIZE + ALFABETO_SIZE) % ALFABETO_SIZE;
                resultado[i] = alfabeto[nueva_pos];
            } else {
                resultado[i] = intermedio[i];
            }
        } else {
            resultado[i] = intermedio[i];
        }
        i++;
    }
    resultado[i] = '\0';
}

void codificar(char *original, char *codificado, char *alfabeto, int N) {
    char intermedio[MAX_MENSAJE];
    primera_etapa(original, intermedio, alfabeto, N);
    segunda_etapa(intermedio, codificado, alfabeto, N);
}

void graba_mensaje(char *codificado, int N) {
    FILE *archivo = fopen("codificado.txt", "w");
    if (archivo == NULL) {
        printf("Error al abrir codificado.txt\n");
        return;
    }
    fprintf(archivo, "%d#%s", N, codificado);
    fclose(archivo);
}

int main() {
    char original[MAX_MENSAJE];
    char alfabeto[ALFABETO_SIZE];
    char codificado[MAX_MENSAJE];
    int N;
    lee_original(original, &N);
    inicializa_alfabeto(alfabeto);
    codificar(original, codificado, alfabeto, N);
    graba_mensaje(codificado, N);
    return 0;
}