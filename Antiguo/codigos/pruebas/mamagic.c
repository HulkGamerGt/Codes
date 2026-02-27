#include <stdio.h>
#include <string.h>

#define N 3

void pedir_matriz(int [N][N]);
void mostrar_matriz(int [N][N]);
void magic(int [N][N]);
int sum_col(int [N][N]);
int sum_fil(int [N][N]);
int sum_dia(int [N][N]);


int main(){
    int matriz[N][N];

    pedir_matriz(matriz);
    magic(matriz);
    mostrar_matriz(matriz);
    
    return 0;
}

void pedir_matriz(int matriz[N][N]){
    int i, j;
    for(i = 0;i < N ;i++){
        for(j = 0 ; j < N ; j++ ){
            printf("Ingrese valor de la coordenada de la matriz[%d][%d]: ",i,j);
            scanf("%d", &matriz[i][j]);
        }
    }
}

void magic(int matriz[N][N]){
    int sum_c, sum_f, sum_d;

    sum_f = sum_fil(matriz);
    sum_c = sum_col(matriz);
    sum_d = sum_dia(matriz);

    if(sum_c == sum_f && sum_c == sum_d && sum_f == sum_d){
       printf("La matriz es magica.\n");
    }else{
        printf("La matriz no es magica.\n");
    }

}
int sum_fil(int matriz[N][N]){
    int j;
    int sum_f=0, sum_f1=0, sum_f2=0, sum_f3=0;
    for(j=0; j < N;j++ ){
        sum_f1 += matriz[0][j];
        sum_f2 += matriz[1][j];
        sum_f3 += matriz[2][j];
    }
    if(sum_f1 == sum_f2 && sum_f2 == sum_f3 && sum_f1 == sum_f3){
        sum_f = sum_f1 + sum_f2;
    }
    return sum_f;
}

int sum_col(int matriz[N][N]){
    int i;
    int sum_c=0, sum_c1=0, sum_c2=0, sum_c3=0;
    for(i=0; i < N; i++){
        sum_c1 += matriz[i][0];
        sum_c2 += matriz[i][1];
        sum_c3 += matriz[i][2];
    }
    if(sum_c1 == sum_c2 && sum_c2 == sum_c3 && sum_c1 == sum_c3){
        sum_c = sum_c1 + sum_c2 ;
    }
    return sum_c;

}

int sum_dia(int matriz[N][N]){
    int i;
    int sum_d=0, sum_d1=0, sum_d2=0;
    for(i=0; i < N; i++){
        sum_d1 += matriz[i][i];
        sum_d2 += matriz[i][N-i-1];
        if(sum_d1 == sum_d2){
            sum_d = sum_d1 + sum_d2;
        }
    }
    return sum_d;
}

void mostrar_matriz(int matriz[N][N]){
    int i, j;
    printf("Matriz conformada");
    printf("\n");
    for(i = 0;i < N ;i++){
        for(j = 0 ; j < N ; j++ ){
            printf("%d    ", matriz[i][j]);
        }
        printf("\n"); 
    }
}
/* 4 9 2
   3 5 7
   8 1 6 
*/