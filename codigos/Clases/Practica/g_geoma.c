#include <stdio.h>
#include <string.h>
#define M 100 // Máximo de caracteres para el genoma

// Prototipos de funciones
void abridor_archivo_gestor_funciones(int *, char []);
void leer_num_genoma(int *, FILE * );
void leer_letras_genoma(int *, FILE *, char []);

// Función principal
int main(){
    int n;
    char genoma[M]; // Array para almacenar las letras
    abridor_archivo_gestor_funciones(&n, genoma);
    
    printf("\nEl numero de filas (n) es: %d\n", n);
    
    // Imprimir el genoma leido
    printf("Genoma leido:\n");
    for(int i = 0; i < n * 10; i++) { // n filas * 10 letras por fila
        printf("%c", genoma[i]);
        // Añadir un salto de línea para formatear la salida como en el archivo original
        if ((i + 1) % 10 == 0 && i < n * 10 - 1) {
            printf("\n");
        }
    }
    printf("\n");
    
    return 0;
}

// -----------------------------------------------------------

void abridor_archivo_gestor_funciones(int *n, char genoma[]){
    FILE *archivo = fopen("genoma.txt","r");
    
    if(archivo == NULL){
        printf("Error al abrir el archivo");
        return; // Salir si hay error
    }
    
    leer_num_genoma(n, archivo);
    
    // Consumir el carácter de nueva línea que queda después de fscanf(%d)
    //fgetc(archivo); 
    
    leer_letras_genoma(n, archivo, genoma);
    
    fclose(archivo);
}

// -----------------------------------------------------------

void leer_num_genoma(int *n, FILE *archivo){
    if(fscanf(archivo,"%d",n) == 1){
        if(*n >= 1 && *n < 100 ){
            printf("El numero de genoma que hay es: %d\n",*n); 
        } else {
            printf("Rango de numeros no compatible.\n");
            *n = 0; // Invalidar n
        }
    } else {
        printf("Error: No hay numero, solo caracteres.\n");
        *n = 0; // Invalidar n
    }
}

// -----------------------------------------------------------

void leer_letras_genoma(int *n, FILE *archivo, char genoma[]){
    if (*n == 0) return; // No leer si n es inválido

    int i = 0;
    int max_chars = *n * 10; // 6 filas * 10 letras = 60 caracteres

    // Bucle para leer *todos* los caracteres
    while (i < max_chars && fscanf(archivo, " %c", &genoma[i]) == 1) {
        // La expresión " %c" ignora automáticamente los espacios en blanco 
        // (incluidos saltos de línea) antes del siguiente carácter.
        i++;
    }
    
    // Asegurarse de que el array finaliza correctamente si se usa como cadena
    if (i < M) {
        genoma[i] = '\0';
    }
    
    printf("Se leyeron %d letras.\n", i);
}