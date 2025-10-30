#include <stdio.h>


#define Filas 3
#define Columnas 3

void leer_datos_puzzle(int [Filas][Columnas]);
void resolver_puzzle(int [Filas][Columnas], int [Filas][Columnas]);
void intercambiar(int *, int *);
void prueba_matriz(int [Filas][Columnas]);
int buscar_0_yNum(int , int [Filas][Columnas]);

int main(){
    int puzzle[Filas][Columnas];
    int puzzle_resuelto[Filas][Columnas]={
        {1,2,3},
        {4,5,6},
        {7,8,0}
    };
    leer_datos_puzzle(puzzle);
    prueba_matriz(puzzle);
    resolver_puzzle(puzzle, puzzle_resuelto);
    prueba_matriz(puzzle);

    return 0;
}

void leer_datos_puzzle(int puzzle[Filas][Columnas]){
    scanf("%d-%d-%d-%d-%d-%d-%d-%d-%d", &puzzle[0][0], &puzzle[0][1], &puzzle[0][2], &puzzle[1][0], &puzzle[1][1], &puzzle[1][2], &puzzle[2][0], &puzzle[2][1],&puzzle[2][2]);
}

void prueba_matriz(int puzzle[3][3]){
    int i,j;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            printf("%d ", puzzle[i][j]);
        }
        printf("\n");
    }
}

void resolver_puzzle(int puzzle[Filas][Columnas], int puzzle_resuelto[Filas][Columnas]){
    int i,j,k,l,posicion[Filas][Columnas];
    for(i=0;i<Filas;i++){
        for(j=0;j<Columnas;j++){
            if(puzzle[i][j] != puzzle_resuelto[i][j]){
                posicion[i][j] = buscar_0_yNum(puzzle[i][j], puzzle_resuelto);
            }

        }

    }
}

int buscar_0_yNum(int posicion, int puzzle_resuelto[Filas][Columnas]){}

void intercambiar(int *a, int *b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

/*
    for(i=0;i<Filas;i++){
        for(j=0;j<Columnas;j++){
            if(puzzle[i][j] != puzzle_resuelto[i][j]){
                //Buscar la posicion del valor correcto
                for(k=0;k<Filas;k++){
                    for(l=0;l<Columnas;l++){
                        if(puzzle[k][l] == puzzle_resuelto[i][j]){
                            //Intercambiar valores
                            intercambiar(&puzzle[i][j], &puzzle[k][l]);
                            printf("La posicion que hay que camiar es :(%d,%d) por (%d,%d)\n",k+1,l+1,i+1,j+1);
                        }
                    }
                }
            }
        }
    }*/