#include <stdio.h>
#include <string.h>

// Definiciones de constantes
#define FILAS 100 // Número máximo de secuencias
#define COLUMNAS 30 // La longitud máxima de la secuencia (ej. 10) + 1 para '\0'
#define LONGITUD_MAX_SECUENCIA (COLUMNAS - 1) // 29

// Estructura (se mantiene)
typedef struct {
    char name[50];
    int age;
} GENOMA;

// Prototipos de funciones
void abridor_archivo_gestor_funciones(int *n, char matriz_genoma[][COLUMNAS]);
void leer_num_genoma(int *n, FILE *archivo);
void leer_letras_genoma(int *n, FILE *archivo, char matriz_genoma[][COLUMNAS]);
void leer_secuencia_recursiva(int *n, FILE *archivo, char matriz_genoma[][COLUMNAS], int indice_actual, int limite_filas);
void analizador_genoma(int n, char matriz_genoma[][COLUMNAS], char new_genoma[][COLUMNAS], char temp_genoma[][COLUMNAS]);

// ---------------------------------------------------------------------
// FUNCIÓN PRINCIPAL
// ---------------------------------------------------------------------

int main() {
    int n = 0; // Número de filas (secuencias) esperado del archivo
    
    char genoma_matriz[FILAS][COLUMNAS]; 
    char temp_genoma[FILAS][COLUMNAS]; 
    char new_genoma[FILAS][COLUMNAS];

    abridor_archivo_gestor_funciones(&n, genoma_matriz);
    
    // n ahora contiene el número real de secuencias cargadas.
    if (n > 0) {
        analizador_genoma(n, genoma_matriz, new_genoma, temp_genoma);
    }
    
    return 0;
}

// ---------------------------------------------------------------------
// GESTIÓN DE ARCHIVOS Y NÚMEROS
// ---------------------------------------------------------------------

void abridor_archivo_gestor_funciones(int *n, char matriz_genoma[][COLUMNAS]) {
    FILE *archivo = fopen("genoma.txt", "r");
    
    if (archivo == NULL) {
        printf("Error: No se pudo abrir el archivo genoma.txt\n");
        return;
    }
    
    leer_num_genoma(n, archivo);
    
    if (*n > 0 && *n < FILAS) {
        // Llama al wrapper de la función recursiva
        leer_letras_genoma(n, archivo, matriz_genoma);
    }
    
    fclose(archivo);
}

void leer_num_genoma(int *n, FILE *archivo) {
    if (fscanf(archivo, "%d", n) == 1) {
        if (*n >= 1 && *n < FILAS) {
            printf("El numero de genoma que hay es: %d\n", *n); 
            fgetc(archivo); // Consumir el carácter de salto de línea (\n)
        } else {
            printf("Rango de numeros no compatible o excede el límite de FILAS (%d).\n", FILAS);
            *n = 0; 
        }
    } else {
        printf("No hay num, solo caracteres o error de lectura.\n");
        *n = 0;
    }
}

// ---------------------------------------------------------------------
// LECTURA RECURSIVA (WRAPPER)
// ---------------------------------------------------------------------

void leer_letras_genoma(int *n, FILE *archivo, char matriz_genoma[][COLUMNAS]) {
    if (archivo == NULL || *n <= 0) {
        return;
    }

    int n_esperado = *n;
    // Implementación de la solicitud: leer *n + 1 (donde 'a' = 1)
    int limite_recursivo = n_esperado + 1; 

    printf("\n------ Leyendo recursivamente hasta %d secuencias (n+1) ------\n", limite_recursivo);
    
    // Llamada a la función recursiva
    leer_secuencia_recursiva(n, archivo, matriz_genoma, 0, limite_recursivo);
    
    // El valor de *n se actualiza en la recursión al número real de secuencias cargadas.
}

// ---------------------------------------------------------------------
// FUNCIÓN RECURSIVA PRINCIPAL
// ---------------------------------------------------------------------

void leer_secuencia_recursiva(int *n, FILE *archivo, char matriz_genoma[][COLUMNAS], int indice_actual, int limite_filas) {
    
    // 1. Caso Base 1: Detener la recursión si se alcanzó el límite de filas solicitado (*n + 1)
    if (indice_actual >= limite_filas || indice_actual >= FILAS) {
        *n = indice_actual; // El número final de filas leídas (si no hay EOF)
        return;
    }

    char buffer_linea[COLUMNAS];
    int longitud;

    // 2. Condición de Parada (Caso Base 2): No hay más líneas en el archivo (EOF)
    if (fgets(buffer_linea, sizeof(buffer_linea), archivo) == NULL) {
        *n = indice_actual; // Actualiza n al número real de filas leídas (i)
        printf("Advertencia: Se leyeron solo %d secuencias antes del fin de archivo.\n", indice_actual);
        return; 
    }

    // 3. Procesamiento de la Línea (Igual que en el caso iterativo)
    longitud = strlen(buffer_linea);
    
    // Elimina el '\n' y '\r'
    if (longitud > 0 && buffer_linea[longitud - 1] == '\n') {
        buffer_linea[longitud - 1] = '\0';
        longitud--;
    }
    if (longitud > 0 && buffer_linea[longitud - 1] == '\r') {
        buffer_linea[longitud - 1] = '\0';
        longitud--;
    }

    // 4. Carga de la Matriz
    if (longitud > 0 && longitud <= LONGITUD_MAX_SECUENCIA) { 
        strcpy(matriz_genoma[indice_actual], buffer_linea);
        printf("Leído y cargado (Fila %d): %s\n", indice_actual, matriz_genoma[indice_actual]);
    } else if (longitud > 0) {
         printf("Error: Secuencia de la fila %d excede la longitud máxima o está vacía. Omitiendo.\n", indice_actual);
         // Aunque se omite, se sigue la recursión para el siguiente índice si no se alcanza el límite.
    }

    // 5. Llamada Recursiva: Avanzar al siguiente índice
    leer_secuencia_recursiva(n, archivo, matriz_genoma, indice_actual + 1, limite_filas);
}

// ---------------------------------------------------------------------
// ANÁLISIS (Sin Cambios)
// ---------------------------------------------------------------------

void analizador_genoma(int n, char matriz_genoma[][COLUMNAS], char new_genoma[][COLUMNAS], char temp_genoma[][COLUMNAS]) {
    
    FILE *Salida = fopen("salida.txt", "w");
    if (Salida == NULL) {
        printf("ERROR al abrir el archivo de salida.\n");
        return;
    }

    printf("\n------ Analizando y Escribiendo a salida.txt ------\n");

    for (int i = 0; i < n; i++) {
        
        strcpy(temp_genoma[i], matriz_genoma[i]); 
        strcpy(new_genoma[i], temp_genoma[i]); 
        
        // Escribir la secuencia al archivo de salida
        printf("Escribiendo: %s\n", new_genoma[i]);
        if (fputs(new_genoma[i], Salida) == EOF || fputc('\n', Salida) == EOF) {
             printf("Error al escribir en el archivo de salida.\n");
             break;
        }
    }

    printf("Análisis completado y guardado en salida.txt.\n");
    fclose(Salida);
}