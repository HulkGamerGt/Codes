#include <stdio.h>

int main(){
    int i, moneda =0, cant,par=0,impar=0;
    int cofre[50];
    printf("ingrese la cantidad de monedas");
    scanf("%d", &cant);
    printf("Introduce 50 números (0 o 1) separados por espacios:\n");
    for(i = 0; i < 50; i++){
        if (scanf("%d", &cofre[i]) != 1) {
            printf("Error: Entrada incorrecta o insuficiente. Se esperaban 50 enteros.\n");
            return 1;
        }
    }

    for(int j=0; j<50; j++){
        if(cofre[j] == 1){
            moneda++;
            if(moneda == cant + 1){
                printf("Mas monedas de las esperadas");
                return 0;
            }
        }
    }

    for(i = 0; i < 50; i++){
        if(cofre[i] == 1){
            if(i % 2 == 0){ 
                printf("Primer par: %d\n", i);
                break;
            }
        }
    }
    
    for(i = 49; i >= 0; i--){
        if(cofre[i] == 1){
            if(i % 3 == 0){ 
                printf("Ultimo impar: %d\n", i);
                break;
            }
        }
    }
    
    return 0;
}