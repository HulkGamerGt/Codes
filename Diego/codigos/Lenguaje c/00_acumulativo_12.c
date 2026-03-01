#include <stdio.h>
#include <string.h>

#define TAM 36
#define TOTAL 9999

void menu(int *);
void option(int , const char *[TAM], char [TAM]); 
void mostrar_lista(const char *[TAM], char [TAM]);
void morse_tex(const char *[TAM], char [TAM]); 
void tex_morse(const char *[TAM], char [TAM]); 
void leer(char *); 

void mostrar_lista(const char* morse[TAM], char letras_morse[TAM]){
    int i;
    for(i=0; i < TAM ; i++){
        printf("%c = %s\n", letras_morse[i], morse[i]);
    }
}

void menu(int *opcion){

    printf("________________________________\n");
    printf("======= Menu =======\n");
    printf("________________________________\n");
    printf("1. Modo Aprendizaje (Este modo solo debe mostrar el alfabeto)\n");
    printf("2. Traducir Texto a Morse\n");
    printf("3. Traducir de Morse a Texto.\n");
    printf("4. Salir \nElige una opción [1-4]: ");

    if (scanf("%d",opcion) != 1) {
        printf("\n Error: Entrada no válida. (Use 'ENTER' para continuar)\n");
        while (getchar() != '\n'); 
        *opcion = 0;
        return;
    }
    /* Limpieza del buffer después de scanf */
    while (getchar() != '\n'); 
}    

int main(){
    int opcion;
    const char* morse[TAM] = { 
    ".-","-...","-.-.", "-..", ".", "..-.", 
    "--.","....", "..",".---", "-.-",".-..", 
    "--","-.","---",".--.","--.-",".-.",  
    "...","-","..-","...-",".--","-..-","-.--",  
    "--..", "-----",".----","..---", "...--", 
    "....-",".....", "-....", "--...", "---..", "----." };

    char letras_morse[TAM] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R',
                                 'S','T','U','V','W','X','Y','Z','0','1','2','3','4','5','6','7','8','9'};

    do{
        menu(&opcion);
        option(opcion, morse, letras_morse); 
    }while(opcion != 4);

    printf("\nPrograma finalizado.\n");
    return 0;
}

void option(int opcion, const char *morse[TAM], char letras_morse[TAM]){
    switch(opcion){
        case 1:
            mostrar_lista(morse, letras_morse);
            break;
        case 2:
            tex_morse(morse,letras_morse); 
            break;
        case 3:
            morse_tex(morse,letras_morse);
            break;
        case 4:
            printf("\nSaliendo del programa...\n");
            break;
        default:
            printf("\n Error: Opción no reconocida. \n");
            break;
    }
}    


void tex_morse(const char *morse[TAM], char letras_morse[TAM]){
    char tex_mo[TOTAL];
    int i;
    int j;
    int tam_temp;
    char caracter_actual;
    
    leer(tex_mo);
    tam_temp = strlen(tex_mo);
    printf("Traduccion a Morse: ");

    for(i = 0; i < tam_temp; i++){
        caracter_actual = tex_mo[i];

        if (caracter_actual == ' ') {
            printf("/ "); /* Espacio entre palabras */
            continue;
        }

        for(j=0; j < TAM; j++ ){
            if(caracter_actual == letras_morse[j]){
                printf("%s ", morse[j]);
                break; /* Salimos del for interno al encontrar la letra */
            }
        }
    }
    printf("\n");
}

void morse_tex(const char *morse[TAM], char letras_morse[TAM]){
    char mo_tex[TOTAL];
    char codigo_actual[10]; // Para almacenar cada código morse
    int i = 0;
    int j = 0;
    int k;
    
    leer(mo_tex);
    printf("Traduccion a Texto: ");

    // Procesamos cada carácter de la entrada
    while(mo_tex[i] != '\0') {
        // Si encontramos un espacio o el final, procesamos el código acumulado
        if(mo_tex[i] == ' ' || mo_tex[i+1] == '\0') {
            // Si es el último carácter y no es espacio, lo agregamos
            if(mo_tex[i+1] == '\0' && mo_tex[i] != ' ') {
                codigo_actual[j] = mo_tex[i];
                j++;
            }
            
            // Terminamos el string del código actual
            codigo_actual[j] = '\0';
            
            // Buscamos el código en nuestra tabla
            if(j > 0) {
                int encontrado = 0;
                for(k = 0; k < TAM; k++) {
                    if(strcmp(codigo_actual, morse[k]) == 0) {
                        printf("%c", letras_morse[k]);
                        encontrado = 1;
                        break;
                    }
                }
                if(!encontrado && strcmp(codigo_actual, "/") == 0) {
                    printf(" "); // El "/" representa un espacio entre palabras
                } else if(!encontrado) {
                    printf("?"); // Código no reconocido
                }
            }
            
            j = 0; // Reseteamos para el próximo código
        } else {
            // Seguimos acumulando caracteres para el código actual
            codigo_actual[j] = mo_tex[i];
            j++;
        }
        i++;
    }
    printf("\n");
}

void leer(char *lectura){
    printf("\nIntroduce el texto a procesar: ");

    if (fgets(lectura, TOTAL, stdin) == NULL) {
        return;
    }
    lectura[strcspn(lectura, "\n")] = 0;
}

/* demostrar que lee e imprime bien 
    printf("Texto leído: ");
    for(i = 0; tex_mo[i] != '\0' ; i++){
        printf("%c",tex_mo[i]);
    }
    printf("\n");
    
    
    */