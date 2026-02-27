#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <stdio.h>
#include <string.h>

#define TAM 36
#define TOTAL 9999

// Tablas globales para testing
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

// Función auxiliar para simular tex_morse
void simular_tex_morse(const char* texto, char* resultado) {
    int primera_letra = 1;
    int pos = 0, c;
    
    for (int i = 0; texto[i]; i++) {
        
        if (c == ' ') {
            resultado[pos++] = ' ';
            primera_letra = 1;
            continue;
        }
        
        int encontrado = 0;
        for (int j = 0; j < TAM; j++) {
            if (c == letras_morse[j]) {
                if (!primera_letra) {
                    resultado[pos++] = ' ';
                }
                const char* codigo = morse[j];
                for (int k = 0; codigo[k]; k++) {
                    resultado[pos++] = codigo[k];
                }
                encontrado = 1;
                primera_letra = 0;
                break;
            }
        }
        if (!encontrado && c != '\n') {
            if (!primera_letra) {
                resultado[pos++] = ' ';
            }
            resultado[pos++] = '?';
            primera_letra = 0;
        }
    }
    resultado[pos] = '\0';
}

// Función auxiliar para simular morse_tex
void simular_morse_tex(const char* entrada, char* resultado) {
    char codigo[20];
    int i = 0, j = 0;
    int pos = 0;
    int hay_espacio = 0;
    
    while (entrada[i]) {
        char c = entrada[i];
        
        if (c == '.' || c == '-') {
            if (j < 19) {
                codigo[j++] = c;
            }
            hay_espacio = 0;
        }
        else if (c == ' ') {
            if (j > 0) {
                codigo[j] = '\0';
                int encontrado = 0;
                for (int k = 0; k < TAM; k++) {
                    if (strcmp(codigo, morse[k]) == 0) {
                        resultado[pos++] = letras_morse[k];
                        encontrado = 1;
                        break;
                    }
                }
                if (!encontrado) resultado[pos++] = '?';
                j = 0;
            }
            
            if (hay_espacio) {
                resultado[pos++] = ' ';
                hay_espacio = 0;
            } else {
                hay_espacio = 1;
            }
        }
        i++;
    }
    
    if (j > 0) {
        codigo[j] = '\0';
        int encontrado = 0;
        for (int k = 0; k < TAM; k++) {
            if (strcmp(codigo, morse[k]) == 0) {
                resultado[pos++] = letras_morse[k];
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) resultado[pos++] = '?';
    }
    resultado[pos] = '\0';
}

TEST_CASE("Texto a Morse simple") {
    char resultado[100];
    simular_tex_morse("HOLA", resultado);
    REQUIRE(strcmp(resultado, ".... --- .-.. .-") == 0);
}

TEST_CASE("Morse a Texto simple") {
    char resultado[100];
    simular_morse_tex(".... --- .-.. .-", resultado);
    REQUIRE(strcmp(resultado, "HOLA") == 0);
}

TEST_CASE("Texto con espacios") {
    char resultado[100];
    simular_tex_morse("HOLA MUNDO", resultado);
    REQUIRE(strcmp(resultado, ".... --- .-.. .- -- ..- -. -.. ---") == 0);
}

TEST_CASE("Morse con espacios") {
    char resultado[100];
    simular_morse_tex(".... --- .-.. .-  -- ..- -. -.. ---", resultado);
    REQUIRE(strcmp(resultado, "HOLA MUNDO") == 0);
}

TEST_CASE("Caracteres no validos") {
    char resultado[100];
    simular_tex_morse("HOLA!", resultado);
    REQUIRE(strcmp(resultado, ".... --- .-.. .- ?") == 0);
}

TEST_CASE("Numeros a Morse") {
    char resultado[100];
    simular_tex_morse("123", resultado);
    REQUIRE(strcmp(resultado, ".---- ..--- ...--") == 0);
}

TEST_CASE("Morse a numeros") {
    char resultado[100];
    simular_morse_tex(".---- ..--- ...--", resultado);
    REQUIRE(strcmp(resultado, "123") == 0);
}