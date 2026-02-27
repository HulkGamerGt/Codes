#include <stdio.h>
#include <string.h>

#define ALFABETO_SIZE 44

void inicializa_alfabeto(char *alfabeto) {
    int i = 0;
    for (char c = 'A'; c <= 'Z'; c++) alfabeto[i++] = c;
    alfabHosts[i++] = ' ';
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

void lee_codificado(char *codificado, int *N) {
    FILE *fp = fopen("codificado.txt", "r");
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
            strcpy(codificado, hash_pos + 1);
            hash_pos = strchr(codificado, '\n');
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

void decodificar(char *codificado, char *original, char *alfabeto, int N) {
    int len = strlen(codificado);
    char intermediate[100];
    int i, P, new_P;
    strcpy(intermediate, codificado);
    for (i = 0; i < len; i += 3) {
        P = find_position(intermediate[i], alfabeto);
        new_P = (P - N) % ALFABETO_SIZE;
        if (new_P < 0) new_P += ALFABETO_SIZE;
        intermediate[i] = alfabeto[new_P];
    }
    for (i = 0; i < len; i++) {
        P = find_position(intermediate[i], alfabeto);
        new_P = (P + N) % ALFABETO_SIZE;
        original[i] = alfabeto[new_P];
    }
    original[len] = '\0';
}

void graba_original(char *original) {
    FILE *fp = fopen("decodificado.txt", "w");
    if (fp == NULL) {
        printf("Error abriendo archivo\n");
        exit(1);
    }
    fprintf(fp, "%s", original);
    fclose(fp);
}

int main() {
    char codificado[100];
    char alfabeto[100];
    char original[100];
    int N;
    lee_codificado(codificado, &N);
    inicializa_alfabeto(alfabeto);
    decodificar(codificado, original, alfabeto, N);
    graba_original(original);
    return 0;
}