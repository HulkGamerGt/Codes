#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

struct Nodo {
    int info;
    struct Nodo * sig;
};

typedef struct Nodo * TipoLista;

extern TipoLista lista_vacia(void);
extern int es_lista_vacia(TipoLista lista);
extern TipoLista inserta_por_cabeza(TipoLista lista, int valor );
extern TipoLista inserta_por_cola(TipoLista lista, int valor );
extern TipoLista borra_cabeza(TipoLista lista);
extern TipoLista borra_cola(TipoLista lista);
extern int longitud_lista(TipoLista lista);
extern void muestra_lista(TipoLista lista);
extern int pertenece(TipoLista lista, int valor );
extern TipoLista borra_primera_ocurrencia(TipoLista lista, int valor );
extern TipoLista borra_valor (TipoLista lista, int valor );
extern TipoLista inserta_en_posicion(TipoLista lista, int pos, int valor );
extern TipoLista inserta_en_orden(TipoLista lista, int valor );
extern TipoLista concatena_listas(TipoLista a, TipoLista b);
extern TipoLista libera_lista(TipoLista lista);


//objetivo:
// El objetivo es extender una estructura de datos tipo Lista incorporando funcionalidades no triviales.
// A partir de la estructura de datos tipo Lista (entregado en clases), implemente las siguientes funciones adicionales:

void EliminarRepetidos(lista);/*Elimina los caracteres repetidos de una cadena solo la primera vez que aparece ej:[3,5,4,7,5] -> [3,5,4,7]*/
void InvertirString(lista,inicio,fin);/*invierte los elementos de una cadena ej:[1,2,3,4,5] inicio=1 fin=5 -> [1,4,3,2,5]*/
void MoverMaxALFinal(lista);//Encuentra el valor maximo y lo mueve al final del arreglo ej:[3,5,4,7,5] -> [3,4,5,5,7]*/
void EsPalindromo(lista);//Retorna 1 si la cadena es un palindromo y 0 si no lo es ej:[1,2,3,2,1] -> 1 [1,2,3,4,5] -> 0*/

//Elimina los caracteres repetidos de una cadena solo la primera vez que aparece
void

//invierte los elementos de una cadena entre el inicio y el fin
void InvertirString(lista,inicio,fin){
    printf("Ingrese una cadena: ");
    fgets(lista,100,stdin);
    int i,j;
    char temp;
    for(i=inicio,j=fin;i<j;i++,j--){
        temp=lista[i];
        lista[i]=lista[j];
        lista[j]=temp;
    }
}

// mueve el valor maximo al final del arreglo
void MoverMaxALFinal(lista){
    printf("Ingrese una cadena: ");
    fgets(lista,100,stdin);
    char temp;
    int i,j;
    for(i=0;i<strlen(lista);i++){
        for(j=i+1;j<strlen(lista);j++){
            if(lista[i]>lista[j]){
                temp=lista[i];
                lista[i]=lista[j];
                lista[j]=temp;
            }
        }
    }
}
//Verifica si una cadena es un palindromo
void EsPalindromo(lista){
    int i,j;
    for(i=0,j=strlen(lista)-1;i<strlen(lista)/2;i++,j--){
        if(lista[i]!=lista[j]){
            printf("0");
            return;
        }
    }
    printf("1");
}
