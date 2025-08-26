#include <stdio.h>
#include <string.h>

#define MAX_MSG 100
#define ALFABETO_SIZE 46

void inicializa_alfabeto(char *alfabeto) {
    const char *alf = "ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789!,.:;?+-*/";
    strcpy(alfabeto, alf);
    alfabeto[ALFABETO_SIZE] = '\0';
}

int find_position(char c, const char *alfabeto) {
    for (int i = 0; i < ALFABETO_SIZE; i++) {
        if (alfabeto[i] == c) return i;
    }
    return -1;
}

void inversa_segunda_etapa(char *codificado, char *resultado, int N) {
    int len = strlen(codificado);
    for (int i = 0; i < len; i++) {
        char c = codificado[i];
        if (c >= 'A' && c <= 'Z') {
            int p = c - 'A';
            int q = ((p - N) % 26 + 26) % 26;
            if (q % N == 0) {
                resultado[i] = 'A' + q;
            } else {
                resultado[i] = c;
            }
        } else {
            resultado[i] = c;
        }
    }
    resultado[len] = '\0';
}

void inversa_primera_etapa(char *segunda, char *resultado, const char *alfabeto, int N) {
    int len = strlen(segunda);
    for (int i = 0; i < len; i++) {
        int pos = find_position(segunda[i], alfabeto);
        if (pos != -1) {
            int new_pos = (pos + N) % ALFABETO_SIZE;
            resultado[i] = alfabeto[new_pos];
        } else {
            resultado[i] = segunda[i];
        }
    }
    resultado[len] = '\0';
}

void decodificar(char *codificado, char *decodificado, char *alfabeto, int N) {
    char segunda[MAX_MSG];
    inversa_segunda_etapa(codificado, segunda, N);
    inversa_primera_etapa(segunda, decodificado, alfabeto, N);
}

void lee_codificado(char *codificado, int *N) {
    FILE *file = fopen("codificado.txt", "r");
    if (!file) {
        printf("Error al abrir codificado.txt\n");
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
        strcpy(codificado, line + i + 1);
    }
    fclose(file);
}

void graba_decodificado(char *decodificado) {
    FILE *file = fopen("decodificado.txt", "w");
    if (!file) {
        printf("Error al abrir decodificado.txt\n");
        return;
    }
    int N;
    char codificado[MAX_MSG];
    lee_codificado(codificado, &N);
    fprintf(file, "%d#%s", N, decodificado);
    fclose(file);
}

int main() {
    char codificado[MAX_MSG];
    char alfabeto[ALFABETO_SIZE + 1];
    char decodificado[MAX_MSG];
    int N;

    lee_codificado(codificado, &N);
    inicializa_alfabeto(alfabeto);
    decodificar(codificado, decodificado, alfabeto, N);
    graba_decodificado(decodificado);

    return 0;
}