#include <stdio.h>
#include <string.h>

#define TAM 36
#define TOTAL 9999

void menu(int *); /* Muestra el menú principal y captura la opción del usuario */
void option(int, const char *[TAM], char [TAM]); /* Ejecuta la opción seleccionada del menú */
void mostrar_lista(const char *[TAM], char [TAM]); /* Muestra la tabla completa de código Morse */
void morse_tex(const char *[TAM], char [TAM]); /* Convierte código Morse a texto */
void tex_morse(const char *[TAM], char [TAM]); /* Convierte texto a código Morse */
void leer(char *); /* Lee texto ingresado por el usuario */
void instructivo(); /* Muestra instrucciones de uso del programa */

/* Función principal que inicializa el programa y controla el bucle principal */
int main(){
    int opcion;
    const char *morse[TAM] ={
        ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
        "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
        "..-", "...-", ".--", "-..-", "-.--", "--..", "-----", ".----", "..---",
        "...--", "....-", ".....", "-....", "--...", "---..", "----."};
    char letras_morse[TAM] ={
        'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R',
        'S','T','U','V','W','X','Y','Z','0','1','2','3','4','5','6','7','8','9'};

    instructivo();
    do{
        menu(&opcion);
        option(opcion, morse, letras_morse);
    }while(opcion != 4);

    printf("\nPrograma finalizado.\n");
    return 0;
}

/* Muestra el menú de opciones y valida la entrada del usuario */
void menu(int *opcion){
    printf("\n________________________\n");
    printf("=========  Menu  =========\n");
    printf("__________________________\n");
    printf("1. Modo Aprendizaje\n");
    printf("2. Texto a Morse\n");
    printf("3. Morse a Texto\n");
    printf("4. Salir\n");
    printf("Elige una opcion [1-4]: ");

    if(scanf("%d", opcion) != 1){
        printf("Error: Entrada invalida.\n");
        while (getchar() != '\n');
        *opcion = 0;
        return;
    }
    getchar(); /* Limpia el buffer de entrada */
}

/* Ejecuta la función correspondiente según la opción seleccionada */
void option(int opcion, const char *morse[TAM], char letras_morse[TAM]){
    switch(opcion){
        case 1: mostrar_lista(morse, letras_morse); break; /* Muestra tabla Morse */
        case 2: tex_morse(morse, letras_morse); break;     /* Convierte texto a Morse */
        case 3: morse_tex(morse, letras_morse); break;     /* Convierte Morse a texto */
        case 4: printf("\nSaliendo del programa...\n"); break; /* Sale del programa */
        default: printf("Opcion invalida.\n"); break;      /* Opción no válida */
    }
}

/* Muestra la tabla completa con todas las letras y números en Morse */
void mostrar_lista(const char *morse[TAM], char letras_morse[TAM]){
    int i;
    printf("\n=== Tabla de Codigo Morse ===\n");
    for(i = 0; i < TAM; i++){
        printf("%c = %s\n", letras_morse[i], morse[i]);
    }
    printf("\n");
}

/* Convierte texto ingresado por el usuario a código Morse */
void tex_morse(const char *morse[TAM], char letras_morse[TAM]){
    char texto[TOTAL];
    int primera_letra;
    int i, j;
    char c;
    int encontrado;
    
    leer(texto);
    printf("Traduccion a Morse: ");

    primera_letra = 1; /* Controla si es el primer carácter para no poner espacio al inicio */
    for(i = 0; texto[i]; i++){ /* Recorre cada carácter del texto */
        c = texto[i];
        
        if(c == ' '){ /* Si es espacio, lo imprime directamente */
            printf(" ");
            primera_letra = 1;
            continue;
        }
        
        encontrado = 0;
        for(j = 0; j < TAM; j++){ /* Busca el carácter en la tabla Morse */
            if(c == letras_morse[j]){
                if(!primera_letra) printf(" "); /* Agrega espacio entre códigos Morse */
                printf("%s", morse[j]);
                encontrado = 1;
                primera_letra = 0;
                break;
            }
        }
        if(!encontrado && c != '\n'){ /* Si no encuentra el carácter, muestra ? */
            if (!primera_letra) printf(" "); /* Agrega espacio antes del ? si no es el primero */
            printf("?");
            primera_letra = 0;
        }
    }
    printf("\n");
}

/* Convierte código Morse ingresado por el usuario a texto */
void morse_tex(const char *morse[TAM], char letras_morse[TAM]){
    char entrada[TOTAL];
    char codigo[20];
    int i, j, k;
    int hay_espacio;
    int encontrado;
    char c;
    
    leer(entrada);
    printf("Traduccion a Texto: ");

    i = 0;
    j = 0;
    hay_espacio = 0;
    
    while(entrada[i]){ /* Recorre cada carácter de la entrada Morse */
        c = entrada[i];
        
        if(c == '.' || c == '-'){ /* Si es punto o raya, lo agrega al código actual */
            if(j < 19){ /* Verifica límite del buffer del código */
                codigo[j++] = c;
            }
            hay_espacio = 0;
        }
        else if(c == ' '){ /* Si es espacio, procesa el código completo */
            if(j > 0){ /* Si hay un código almacenado, lo procesa */
                codigo[j] = '\0';
                encontrado = 0;
                for(k = 0; k < TAM; k++){ /* Busca el código en la tabla Morse */
                    if(strcmp(codigo, morse[k]) == 0){
                        printf("%c", letras_morse[k]);
                        encontrado = 1;
                        break;
                    }
                }
                if(!encontrado) printf("?"); /* Si no encuentra el código, muestra ? */
                j = 0;
            }
            
            if(hay_espacio){ /* Si ya había un espacio, es espacio entre palabras */
                printf(" ");
                hay_espacio = 0;
            }else{
                hay_espacio = 1; /* Marca que hubo un espacio */
            }
        }
        i++;
    }
    
    if(j > 0){ /* Procesa el último código si queda alguno */
        codigo[j] = '\0';
        encontrado = 0;
        for(k = 0; k < TAM; k++){ /* Busca el código en la tabla Morse */
            if(strcmp(codigo, morse[k]) == 0){
                printf("%c", letras_morse[k]);
                encontrado = 1;
                break;
            }
        }
        if(!encontrado) printf("?"); /* Si no encuentra el código, muestra ? */
    }
    printf("\n");
}

/* Lee texto del usuario y elimina el salto de línea */
void leer(char *lectura){
    printf("\nIntroduce el texto a procesar: ");
    
    if(fgets(lectura, TOTAL, stdin)){
        lectura[strcspn(lectura, "\n")] = '\0'; /* Elimina el salto de línea */
    }
}

/* Muestra las instrucciones de uso del programa */
void instructivo(){
    printf("\n--- OPCIONES DEL MENU ---\n");
    printf("[1] MODO APRENDIZAJE: Muestra tabla completa Morse\n");
    printf("    Ejemplo: A = .- , B = -... , 1 = .----\n");
    printf("\n[2] TEXTO A MORSE: Convierte texto a morse\n");
    printf("    Ejemplo: HOLA = .... --- .-.. .-\n");
    printf("    Ejemplo: HOLA MUNDO = .... --- .-.. .-  -- ..- -. -.. ---\n");
    printf("\n[3] MORSE A TEXTO: Convierte de morse a texto\n");
    printf("    Ejemplo: .... --- .-.. .- = HOLA\n");
    printf("    SEPARE EL MORSE CON ESPACIOS: .- -... en vez de .--...\n");
    printf("    Con 1 solo espacio para separar letras y 2 para palabras");
    printf("\n[4] SALIR: Finaliza el programa\n");
    printf("\n--- FORMATOS ACEPTADOS ---\n");
    printf("• Letras: A-Z (MAYUSCULAS)\n");
    printf("• Numeros: 0-9\n");
    printf("• Espacios: Separan palabras en morse\n");
    printf("• Caracteres no validos: Se muestran como ?\n");
    printf("\n========================================\n");
}
