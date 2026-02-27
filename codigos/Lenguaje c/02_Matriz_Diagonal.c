#include <stdio.h>
#define fil 3

int main(){
    int fila,col;
    int matriz [fil] [fil]={{1,2,3},{4,5,6},{7,8,9}};
    for(int i = 0; i < fil; i++){
        for(int j=0; j < fil; j++){
            if((i+j) == fil - 1){
                
                printf("%d ", matriz[i][j]);
            }
        }
    }
   /*printf("Hola mundo: ");
   scanf("%d %d", &fila, &col);
   printf("%d,%d", fila,col);*/
    return 0;
}