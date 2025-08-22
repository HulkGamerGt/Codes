/* Autor: Diego M. Solis Rojas
   Fecha: 21/ 08 / 2025
   Descripcion: Programa que realiza el cálculo del producto cruz
*/

#include <stdio.h>

int vector_u(int *);
int vector_v(int *);
int proceso(int *, int *, int *);

int main(){
    int u[3], v[3], w[3];

    vector_u(u);
    vector_v(v);
    proceso( u, v, w);

    printf("El vector resultante W( %d , %d , %d )\n",w[0],w[1],w[2]);

    return 0;
}

int vector_u(int *u){
    int i;

    for(i = 0 ;i < 3 ; i++)
    {
        printf("Ingrese el valor del vector U.%d : ",i+1);
        scanf("%d",&u[i]);
    }
    return *u;
}

int vector_v(int *v){
    int i;

    for(i = 0 ;i < 3 ; i++)
    {
        printf("Ingrese el valor del vector V.%d : ",i+1);
        scanf("%d",&v[i]);
    }
    return *v;
}

int proceso(int *u, int *v, int *w){
    int h = 0;

    while(h < 3){

        if(h == 0){
            w[h] = (u[1] * v[2]) - (u[2] * v[1]);
        }

        if(h == 1){
            w[h] = (u[2] * v[0]) - (u[0] * v[2]);
        }

        if(h == 2){
            w[h] = (u[0] * v[1]) - (u[1] * v[0]);
        }
        h++;
    }
    return *w;

}