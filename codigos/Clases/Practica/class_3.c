#include <stdio.h>
#define N 3

/* Prototipos de funciones */
void lectura_matriz(int [][N], int);
/* void imprime_matriz(int [][N], int);*/
void imprime_matriz_2(int [][N], int);
void proceso(int [][N], int, int *);
void resultado(int [][N], int, int);
int obtener_suma_magica(int [][N], int);
int suma_filas(int [][N], int, int);
int suma_columnas(int [][N], int, int);
int suma_diagonales(int [][N], int, int);

int main(){
    int matriz[N][N];
    int status; // 0 es Falso y 1 Es Verdadero
    lectura_matriz(matriz, N);
    /*imprime_matriz(matriz, N);*/
    imprime_matriz_2(matriz, N);
    proceso(matriz, N, &status);
    resultado(matriz, N, status);
    return 0;
}

/* Funcion para leer la matriz */
void lectura_matriz(int matriz[][N], int n){
    int i, j;
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            printf("Numero [%d][%d]: ", i, j);
            scanf("%d", &matriz[i][j]);
        }
    }
}

/* Funcion para obtener la suma magica */
int obtener_suma_magica(int matriz[][N], int n){
    int suma = 0, j;
    for (j = 0; j < n; j++){
        suma += matriz[0][j];
    }
    return suma;
}

/* Funcion para sumar las filas */
int suma_filas(int matriz[][N], int n, int suma_referencia){
    int suma, i, j;
    for (i = 0; i < n; i++){
        suma = 0;
        for (j = 0; j < n; j++){
            suma += matriz[i][j];
        }
        if (suma != suma_referencia){
            return 0;
        }
    }
    return 1;
}

/* Funcion para sumar las columnas */
int suma_columnas(int matriz[][N], int n, int suma_referencia){
    int suma, i, j;
    for (j = 0; j < n; j++){
        suma = 0;
        for (i = 0; i < n; i++){
            suma += matriz[i][j];
        }
        if (suma != suma_referencia){
            return 0;
        }
    }
    return 1;
}

/* Funcion para sumar las diagonales */
int suma_diagonales(int matriz[][N], int n, int suma_referencia){
    int suma1 = 0, suma2 = 0, i;
    for (i = 0; i < n; i++){
        suma1 += matriz[i][i];
        suma2 += matriz[i][n-i-1];
    }
    if (suma1 != suma_referencia || suma2 != suma_referencia){
        return 0;
    }
    return 1;
}

/* Funcion para procesar la matriz */
void proceso(int matriz[][N], int n, int *status){
    int st1, st2, st3;
    int suma_referencia = obtener_suma_magica(matriz, n);
    st1 = suma_filas(matriz, n, suma_referencia); // devuelve 0 falso 1 verdadero
    st2 = suma_columnas(matriz, n, suma_referencia); // devuelve 0 falso 1 verdadero
    st3 = suma_diagonales(matriz, n, suma_referencia); // devuelve 0 falso 1 verdadero
    if ((st1 + st2 + st3)!=3){
        *status = 0;
    }
    else{
        *status = 1;
    }
}

/* Funcion para mostrar el resultado */
void resultado(int matriz[][N], int n, int status){
    int i, j;
    if (status == 1){
        printf("La matriz es un cuadrado magico:\n");
        for (i = 0; i < n; i++){
            for (j = 0; j < n; j++){
                printf("%3d ", matriz[i][j]);
            }
            printf("\n");
        }
    }
    else{
        printf("La matriz no es un cuadrado magico.\n");
    }
}

/* Funcion para imprimir la matriz */
/*void imprime_matriz(int matriz[][N], int n){
    int i, j;
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            printf("Matriz[%d][%d]: %d\n", i, j, matriz[i][j]);
        }
    }
}*/

/* Funcion para imprimir la matriz */
void imprime_matriz_2(int matriz[][N], int n){
    int i, j, l;

    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            printf("Matriz[%d][%d] ", i, j);
        }
        printf("\n");
        for(l = 0; l < 3; l++){
            printf("      %d      ", matriz[i][l]);
        }
        printf("\n");
    }
}

/* 4 9 2
   3 5 7
   8 1 6 
*/