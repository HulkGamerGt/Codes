#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <string.h>

#define TAM 36

/* Copiamos las tablas del código original */
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

/* Función simplificada de texto a morse para la prueba unitaria */
void tex_morse_test(const char* texto, char* resultado){
    const char* codigo;
    int pos = 0,i,j,k, encontrado;
    char c;
    
    for(i = 0; texto[i]; i++){
        c = texto[i];
        
        if(c == ' '){
            resultado[pos++] = ' ';
            continue;
        }
        
        encontrado = 0;
        for(j = 0; j < TAM; j++){
            if(c == letras_morse[j]){
                if(pos > 0 && resultado[pos-1] != ' '){
                    resultado[pos++] = ' ';
                }
                codigo = morse[j];
                for(k = 0; codigo[k]; k++){
                    resultado[pos++] = codigo[k];
                }
                encontrado = 1;
                break;
            }
        }
        if(!encontrado && c != '\n'){
            if(pos > 0 && resultado[pos-1] != ' '){
                resultado[pos++] = ' ';
            }
            resultado[pos++] = '?';
        }
    }
    resultado[pos] = '\0';
}

/* Función simplificada de morse a texto para la prueba unitaria */
void morse_tex_test(const char* entrada, char* resultado){
    char codigo[20],c;
    int i = 0, j = 0;
    int pos = 0;
    int hay_espacio = 0, encontrado,k;
    
    while(entrada[i]){
        c = entrada[i];
        
        if(c == '.' || c == '-'){
            if(j < 19){
                codigo[j++] = c;
            }
            hay_espacio = 0;
        }
        else if(c == ' '){
            if(j > 0){
                codigo[j] = '\0';
                encontrado = 0;
                for(k = 0; k < TAM; k++){
                    if(strcmp(codigo, morse[k]) == 0){
                        resultado[pos++] = letras_morse[k];
                        encontrado = 1;
                        break;
                    }
                }
                if(!encontrado) resultado[pos++] = '?';
                j = 0;
            }
            
            if(hay_espacio){
                resultado[pos++] = ' ';
                hay_espacio = 0;
            }else{
                hay_espacio = 1;
            }
        }
        i++;
    }
    
    if(j > 0){
        codigo[j] = '\0';
        encontrado = 0;
        for(k = 0; k < TAM; k++){
            if(strcmp(codigo, morse[k]) == 0){
                resultado[pos++] = letras_morse[k];
                encontrado = 1;
                break;
            }
        }
        if(!encontrado) resultado[pos++] = '?';
    }
    resultado[pos] = '\0';
}

TEST_CASE("Texto a Morse - HOLA"){
    char resultado[100];
    tex_morse_test("HOLA", resultado);
    REQUIRE(strcmp(resultado, ".... --- .-.. .-") == 0);
}

TEST_CASE("Morse a Texto - HOLA"){
    char resultado[100];
    morse_tex_test(".... --- .-.. .-", resultado);
    REQUIRE(strcmp(resultado, "HOLA") == 0);
}

TEST_CASE("Texto a Morse - ABC"){
    char resultado[100];
    tex_morse_test("ABC", resultado);
    REQUIRE(strcmp(resultado, ".- -... -.-.") == 0);
}

TEST_CASE("Morse a Texto - ABC"){
    char resultado[100];
    morse_tex_test(".- -... -.-.", resultado);
    REQUIRE(strcmp(resultado, "ABC") == 0);
}

TEST_CASE("Texto con espacios"){
    char resultado[100];
    tex_morse_test("A B", resultado);
    REQUIRE(strcmp(resultado, ".- -...") == 0);
}

TEST_CASE("Morse con espacios"){
    char resultado[100];
    morse_tex_test(".- -...", resultado);
    REQUIRE(strcmp(resultado, "AB") == 0);
}

TEST_CASE("Numeros a Morse"){
    char resultado[100];
    tex_morse_test("123", resultado);
    REQUIRE(strcmp(resultado, ".---- ..--- ...--") == 0);
}

TEST_CASE("Morse a Numeros"){
    char resultado[100];
    morse_tex_test(".---- ..--- ...--", resultado);
    REQUIRE(strcmp(resultado, "123") == 0);
}

TEST_CASE("Caracter invalido"){
    char resultado[100];
    tex_morse_test("A!", resultado);
    REQUIRE(strcmp(resultado, ".- ?") == 0);
}

TEST_CASE("Texto a Morse - Falla por Minúsculas") {
    char resultado[100];
    tex_morse_test("hola", resultado);
    REQUIRE(strcmp(resultado, ".... --- .-.. .-") == 0);
}

TEST_CASE("Texto a Morse - Falla por Doble Espacio") {
    char resultado[100];
    tex_morse_test("A  B", resultado);
    REQUIRE(strcmp(resultado, ".-  -...") == 0);
}

TEST_CASE("Texto a Morse - Falla por Caracteres no Imprimibles (Tab)") {
    char resultado[100];
    tex_morse_test("A\tB", resultado);
    REQUIRE(strcmp(resultado, ".- -...") == 0);
}

TEST_CASE("Texto a Morse - Falla por Desbordamiento de Buffer (Overflow)") {
    char resultado[100];
    const char* texto_largo = "ZZZZZZZZZZZZZZZZZZZZZZZZZ";
    tex_morse_test(texto_largo, resultado);
    REQUIRE(strlen(resultado) > 99);
}

TEST_CASE("Morse a Texto - Falla por código demasiado largo") {
    char resultado[100];
    morse_tex_test("....................", resultado);
    REQUIRE(strcmp(resultado, "?") == 0);
}

TEST_CASE("Morse a Texto - Falla por un solo espacio (debería ser espacio de palabra)") {
    char resultado[100];
    morse_tex_test(".- .--", resultado);
    REQUIRE(strcmp(resultado, "A W") == 0);
}

TEST_CASE("Morse a Texto - Falla por Caracteres no Morse (Ignorados)") {
    char resultado[100];
    morse_tex_test(".-, .--", resultado);
    REQUIRE(strcmp(resultado, "A?W") == 0);
}