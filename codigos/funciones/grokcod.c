#include <stdio.h>
#include <string.h>

#define MAX_MSG 100
#define ALFABETO_SIZE 46

void inicializa_alfabeto(char *alfabeto) {
    char *alf = "ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789!,.:;?+-*/";
    strcpy(alfabeto, alf);
    alfabeto[ALFABETO_SIZE] = '\0';
}

int find_position(char c, char *alfabeto) {
    for (int i = 0; i < ALFABETO_SIZE; i++) {
        if (alfabeto[i] == c) return i;
    }
    return -1; // Character not found
}

void primera_etapa(char *original, char *resultado, char *alfabeto, int N) {
    int len = strlen(original);
    for (int i = 0; i < len; i++) {
        int pos = find_position(original[i], alfabeto);
        if (pos != -1) {
            int new_pos = (pos - N) % ALFABETO_SIZE;
            if (new_pos < 0) new_pos += ALFABETO_SIZE;
            resultado[i] = alfabeto[new_pos];
        } else {
            resultado[i] = original[i];
        }
    }
    resultado[len] = '\0';
}

void segunda_etapa(char *primera, char *resultado, char *alfabeto, int N) {
    int len = strlen(primera);
    for (int i = 0; i < len; i++) {
        char c = primera[i];
        if (c >= 'A' && c <= 'Z') {
            int pos = find_position(c, alfabeto);
            if (pos % N == 0) {
                int p = c - 'A';
                int new_p = (p + N) % 26;
                resultado[i] = 'A' + new_p;
            } else {
                resultado[i] = c;
            }
        } else {
            resultado[i] = c;
        }
    }
    resultado[len] = '\0';
}

void codificar(char *original, char *codificado, char *alfabeto, int N) {
    char primera[MAX_MSG];
    primera_etapa(original, primera, alfabeto, N);
    segunda_etapa(primera, codificado, alfabeto, N);
}

void lee_original(char *original, int *N) {
    FILE *file = fopen("original.txt", "r");
    if (!file) {
        printf("Error al abrir original.txt\n");
        return;
    }
    char line[MAX_MSG];
    fgets(line, MAX_MSG, file);
    int i = 0;
    *N = 0;
    while (line[i] >= '0' && line[i] <= '9') {
        *N = *N * 10 + (line[i] - '0');
        i++;
    }
    if (line[i] == '#') {
        strcpy(original, line + i + 1);
    }
    fclose(file);
}

void graba_mensaje(char *codificado) {
    FILE *file = fopen("codiff35.txt", "w");
    if (!file) {
        printf("Error al abrir codiff35.txt\n");
        return;
    }
    int N;
    char original[MAX_MSG];
    lee_original(original, &N);
    fprintf(file, "%d#%s", N, codificado);
    fclose(file);
}

int main() {
    char original[MAX_MSG];
    char alfabeto[ALFABETO_SIZE + 1];
    char codificado[MAX_MSG];
    int N;

    lee_original(original, &N);
    inicializa_alfabeto(alfabeto);
    codificar(original, codificado, alfabeto, N);
    graba_mensaje(codificado);

    return 0;
}