#include <stdio.h>

int main(){
    int Q=1,W=1,E=1,R=1;
    printf("Mencione el tamano de la fila del 1er arreglo: ");
    scanf("%d",&Q);
    printf("Mencione el tamano de la fila del 1er arreglo: ");
    scanf("%d",&W);
    printf("Mencione el tamano de la fila del 1er arreglo: ");
    scanf("%d",&E);
    printf("Mencione el tamano de la fila del 1er arreglo: ");
    scanf("%d",&Q);

    if(W!=E){
        return 0;
    }

    int A[Q][W];
    int B[E][R];
    int C[W][E];
    int i,j,m;

    for(int n=0; n<Q; n++){
        for(int l=0; l < W; l++){
            printf("ingrese valor de la 1era matriz en [%d][%d]",n,l);
            scanf("%d",A[n][l]);
        }
    }

    for(int n=0; n<E; n++){
        for(int l=0; l < Q; l++){
            printf("ingrese valor de la 2da matriz en[%d][%d]",n,l);
            scanf("%d",B[n][l]);
        }
    }

    for(i=0;i<W ; i++){
        for(j=0 ; j<E ;j++){
            for(m=0; m<W ; m++){
                C[i][j]=C[i][j] + A[m][i] * B[i][m];
            }
        }
    }

    for(j=0 ; j<W ;j++){
            for(m=0; m<E ; m++){
                printf("%d",C[W][E]);
            }
        }

    return 0;
}