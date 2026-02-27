/*
 * Identificación del autor: Diego Solis Rojas
 * Fecha: 20 / 10 / 2025
 * Tema: La funcion principal de este codigo es encontrar puntos de silla en una matriz de M x M, lo cual se podria modificar dependiendo
 *       de la necesidad del usuario, ya que lee el archivo llamado "matriz5x5.txt" y almacena el contenido del archivo dentro de una matriz,
 *       luego procesa la matriz formada para encontrar dichos puntos de silla, en el caso de no encontrar ninguno, se lo notifica al usuario.
 * (pero con el pequeño detalle que no posee llamadas recursivas, si no que utiliza llamadas iterativas).
*/

#include <stdio.h>
#define M 5

void abridor_archivo(int [][M]);
void lector_matrix(int [][M], FILE *);
void procesar_matriz(int [][M]);


int main(){
    int Matriz[M][M];
    abridor_archivo(Matriz);
    return 0;
}

void abridor_archivo(int Matriz[][M]){

    FILE *matrix = fopen("matriz5x5.txt","r");
    if(matrix == NULL){
        printf("Error al leer archivo matrix5x5.txt\n");
        return;
    }
    lector_matrix(Matriz, matrix);
}

void lector_matrix(int Matriz[][M], FILE *matriz){
    int i=0,j=0;
    // Leer Matriz desde el archivo
    while(i < M){
        while(j < M){
            fscanf(matriz,"%d",&Matriz[i][j]);
            j++;
        }
        j=0;
        i++;
    }
    /* para verificar que funciona la matriz 
       despues de leido el archivo
    i=0;
    while(i < M){
        while(j < M){
            printf("%d ",Matriz[i][j]);
            j++;
        }
        printf("\n");
        j=0;
        i++;
    }*/
    fclose(matriz);
    procesar_matriz(Matriz);

}

void procesar_matriz(int Matriz[][M]){
    int min_fila[M];     // minimo de fila
    int max_columna[M];  // maximo de columna
    int i, j;
    int puntos_silla_encontrados = 0;

    // Para encontrar el mínimo en cada fila
    for (i = 0; i < M; i++) {
        min_fila[i] = Matriz[i][0]; 
        // Inicia con el primer elemento de la fila
        for (j = 1; j < M; j++) {
            if (Matriz[i][j] < min_fila[i]) {
                min_fila[i] = Matriz[i][j];
            }
        }
    }

    // Para encontrar el máximo en cada columna
    for (j = 0; j < M; j++) {
        max_columna[j] = Matriz[0][j]; 
        // Inicia con el primer elemento de la columna
        for (i = 1; i < M; i++) {
            if (Matriz[i][j] > max_columna[j]) {
                max_columna[j] = Matriz[i][j];
            }
        }
    }
    printf("\n\n");
    /* Para encontrar el punto de silla */
    // Buscando el valor que es Menor en su Fila y Mayor en su Columna 
    for (i = 0; i < M; i++) {
        for (j = 0; j < M; j++) {
            // Buscando el punto de silla
            if (Matriz[i][j] == min_fila[i] && Matriz[i][j] == max_columna[j]) {
                printf("Punto de Silla encontrado: Valor %d en posicion [%d][%d]\n", Matriz[i][j], i+1, j+1);
                puntos_silla_encontrados++;
            }
        }
    }
    // Si no cumple con ningun punto de silla, entonces
    if (puntos_silla_encontrados == 0) {
        printf("No se encontraron Puntos de Silla.\n");
    }
}