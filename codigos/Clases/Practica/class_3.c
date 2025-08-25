#include <stdio.h>
#define N 3

void lectura_matriz(int [][N], int);
void imprime_matriz(int [][N], int);
void imprime_matriz_2(int [][N], int);
void proceso(int [][N], int, int *);
void resultado(int [][N], int, int);
int suma_filas(int [][N], int);
int suma_columnas(int [][N], int);
int suma_diagonales(int [][N], int);

int main(){
    int matriz[N][N];
    int status; // 0 es Falso y 1 Es Verdadero
    lectura_matriz(matriz, N);
    imprime_matriz(matriz, N);
    imprime_matriz_2(matriz, N);
    proceso(matriz, N, &status);
    resultado(matriz, N, status);
    return 0;
}

void lectura_matriz(int matriz[][N], int n){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            printf("Numero [%d][%d]: ", i, j);
            scanf("%d", &matriz[i][j]);
        }
    }
}

void imprime_matriz(int matriz[][N], int n){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            printf("Matriz[%d][%d]: %d\n", i, j, matriz[i][j]);
        }
    }
}

void imprime_matriz_2(int matriz[][N], int n){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            printf("%3d ",matriz[i][j]);
        }
        printf("\n");
    }
}

void proceso(int matriz[][N], int n, int *status){
    int st1, st2, st3;
    st1 = suma_filas(matriz, n); // devuelve 0 falso 1 verdadero
    st2 = suma_columnas(matriz, n); // devuelve 0 falso 1 verdadero
    st3 = suma_diagonales(matriz, n); // devuelve 0 falso 1 verdadero
    if ((st1 + st2 + st3)!=3){
        *status = 0;
    }
    else{
        *status = 1;
    }
}

int suma_filas(int matriz[][N], int n){
    int suma;
    for (int i = 0; i < n; i++){
        suma = 0;
        for (int j = 0; j < n; j++){
            suma += matriz[i][j];
        }
        if (suma != 15){
            return 0;
        }
    }
    return 1;
}

int suma_columnas(int matriz[][N], int n){
    int suma;
    for (int j = 0; j < n; j++){
        suma = 0;
        for (int i = 0; i < n; i++){
            suma += matriz[i][j];
        }
        if (suma != 15){
            return 0;
        }
    }
    return 1;
}

int suma_diagonales(int matriz[][N], int n){
    int suma1 = 0, suma2 = 0, i;
    for (i = 0; i < n; i++){
        suma1 += matriz[i][i];
        suma2 += matriz[i][n-i-1];
    }
    if (suma1 != 15 || suma2 != 15){
        return 0;
    }
    return 1;
}

/* 4 9 2
   3 5 7
   8 1 6 
*/