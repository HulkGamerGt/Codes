#include <stdio.h>
#include <string.h>

#define ALFABETO_SIZE 44

void inicializa_alfabeto(char *alfabeto) {
    int i = 0;
    for (char c = 'A'; c <= 'Z'; c++) alfabeto[i++] = c;
    alfabeto[i++] = ' ';
    for (char c = '0'; c <= '9'; c++) alfabeto[i++] = c;
    alfabeto[i++] = '!';
    alfabeto[i++] = ':';
    alfabeto[i++] = ';';
    alfabeto[i++] = '?';
    alfabeto[i++] = '+';
    alfabeto[i++] = '*';
    alfabeto[i++] = '/';
    alfabeto[i] = '\0';
}

int find_position(char c, char *alfabeto) {
    int i;
    for (i = 0; i < ALFABETO_SIZE; i++) {
        if (alfabeto[i] == c) return i;
    }
    return -1;
}

void lee_original(char *original, int *N) {
    FILE *fp = fopen("original.txt", "w");
    char line[256];
    char *hash_pos;
    if (fp == NULL) {
        printf("Error abriendo archivo\n");
        exit(1);
    }
    if (fgets(line, sizeof(line), fp) != NULL) {
        hash_pos = strchr(line, '#');
        if (hash_pos != NULL) {
            *hash_pos = '\0';
            *N = atoi(line);
            strcpy(original, hash_pos + 1);
            hash_pos = strchr(original, '\n');
            if (hash_pos) *hash_pos = '\0';
        } else {
            printf("Formato invalido\n");
            exit(1);
        }
    } else {
        printf("Archivo vacio\n");
        exit(1);
    }
    fclose(fp);
}

void primera_etapa(char *original, char *resultado, char *alfabeto, int N) {
    int len = strlen(original);
    int i, P, new_P;
    for (i = 0; i < len; i++) {
        P = find_position(original[i], alfabeto);
        new_P = (P - N) % ALFABETO_SIZE;
        if (new_P < 0) new_P += ALFABETO_SIZE;
        resultado[i] = alfabeto[new_P];
    }
    resultado[len] = '\0';
}

void segunda_etapa(char *entrada, char *resultado, char *alfabeto, int N) {
    int len = strlen(entrada);
    int i, P, new_P;
    strcpy(resultado, entrada);
    for (i = 0; i < len; i += 3) {
        P = find_position(resultado[i], alfabeto);
        new_P = (P + N) % ALFABETO_SIZE;
        resultado[i] = alfabeto[new_P];
    }
}

void codificar(char *original, char *codificado, char *alfabeto, int N) {
    char intermediate[100];
    primera_etapa(original, intermediate, alfabeto, N);
    segunda_etapa(intermediate, codificado, alfabeto, N);
}

void graba_Mensaje(char *codificado, int N) {
    FILE *fp = fopen("codificado.txt", "w");
    if (fp == NULL) {
        printf("Error abriendo archivo\n");
        exit(1);
    }
    fprintf(fp, "%d#%s", N, codificado);
    fclose(fp);
}

int main() {
    char original[100];
    char alfabeto[100];
    char codificado[100];
    int N;
    lee_original(original, &N);
    inicializa_alfabeto(alfabeto);
    codificar(original, codificado, alfabeto, N);
    graba_Mensaje(codificado, N);
    return 0;
}