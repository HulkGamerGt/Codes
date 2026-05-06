#include <stdio.h>
#include "include/lista.h"


int main(){

    TipoLista l, l2, l3;

    printf(" Creacion de lista ... \n");
    l = lista_vacia();
    muestra_lista(l);

    printf(" Es lista vacia? : %d\n", es_lista_vacia(l));

    printf(" Insercion por cabeza de 2, 8, 3\n");
    l = inserta_por_cabeza(l, 2);
    l = inserta_por_cabeza(l, 8);
    l = inserta_por_cabeza(l, 3);
    muestra_lista(l);

    printf(" Longitud de la lista: %d\n", longitud_lista(l));

    printf(" Insercion por cola de 1, 5, 10\n");
    l= inserta_por_cola(l, 1);
    l= inserta_por_cola(l, 5);
    l= inserta_por_cola(l, 10);
    muestra_lista(l);

    printf(" Borrado de cabeza\n");
    l= borra_cabeza(l);
    muestra_lista(l);

    printf(" Borrado de cola\n");
    l = borra_cola(l);
    muestra_lista(l);

    printf(" Pertenece 5 a la lista: %d\n", pertenece(l, 5));
    printf(" Pertenece 7 a la lista: %d\n", pertenece(l, 7));

    printf (" Insercion por cola de 1\n");
    l= inserta_por_cola(l, 1);
    muestra_lista(l);

    printf (" Borrado de primera ocurrencia de 1\n");
    l = borra_primera_ocurrencia(l, 1);
    muestra_lista(l);

    printf(" Nuevo borrado de primera ocurrencia de 1\n");
    l = borra_primera_ocurrencia(l, 1);
    muestra_lista(l);

    printf(" Nuevo borrado de primera ocurrencia de 1 (que no esta)\n");
    l = borra_primera_ocurrencia(l, 1);
    muestra_lista(l);

    printf(" Insercion por cola y por cabeza de 2\n");
    l= inserta_por_cola(l, 2);
    l= inserta_por_cabeza(l, 2);
    muestra_lista(l);

    printf(" Borrado de todas las ocurrencias de 2\n");
    l = borra_valor (l, 2);
    muestra_lista(l);

    printf(" Borrado de todas las ocurrencias de 8\n");
    l = borra_valor (l, 8);
    muestra_lista(l);

    printf(" Insercion de 1 en posicion 0\n");
    l= inserta_en_posicion(l, 0, 1);
    muestra_lista(l);

    printf(" Insercion de 10 en posicion 2\n");
    l= inserta_en_posicion(l, 2, 10);
    muestra_lista(l);

    printf(" Insercion de 3 en posicion 1\n");
    l= inserta_en_posicion(l, 1, 3);
    muestra_lista(l);

    printf(" Insercion de 4, 0, 20 y 5 en orden\n");
    l= inserta_en_orden(l, 4);
    l= inserta_en_orden(l, 0);
    l= inserta_en_orden(l, 20);
    l= inserta_en_orden(l, 5);
    muestra_lista(l);

    printf(" Creacion de una nueva lista con los elementos 30, 40, 50\n");
    l2 = lista_vacia();
    l2 = inserta_por_cola(l2, 30);
    l2 = inserta_por_cola(l2, 40);
    l2 = inserta_por_cola(l2, 50);
    muestra_lista(l2);

    printf(" Concatenacion de las dos listas para formar una nueva\n");
    l3= concatena_listas(l, l2);
    muestra_lista(l3);

    printf(" Liberacion de las tres listas\n");
    l = libera_lista(l);
    l2 = libera_lista(l2);
    l3 = libera_lista(l3);
    muestra_lista(l);
    muestra_lista(l2);
    muestra_lista(l3);

    return 0;
}