#include <stdio.h>
/*ordena la forma visual de la matriz poniendo la posicion de la fila y columna, sucesivamente dejarlo abajo el valor de la posicion*/

int main(){
    int matriz[3][3] = {
        {4, 9, 2},
        {3, 5, 7},
        {8, 1, 6}
    };
    int i,j,k,l,n;

    for(i=0;i < 3;i++){
        for(j=0;j < 3;j++){
            printf("Matriz[%d][%d] ", i, j);
        }
        printf("\n");
        for(l=0;l < 3;l++){
            printf("      %d      ", matriz[i][l]);
        }
        printf("\n");
    }
}