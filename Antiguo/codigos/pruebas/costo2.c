#include <stdio.h>

int main(){

    int costo,cliente, vuelto;

    printf("Ingrese el valor del producto : ");
    scanf("%d",&costo);
    printf("Ingrese el dinero que entrega el cliente : ");
    scanf("%d",&cliente);

    if(cliente < costo){
        printf("El cliente debe de proporcionarle mas dinero por el articulo");
    }else{
        vuelto = cliente - costo;
        printf("El vuelto que debe de recibir el cliente es de: %d\n",vuelto);
    }
    return 0;
}