//
// Created by Nicolás Reyes on 03-05-26.
//

#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>

struct Nodo {
    int info;
    struct Nodo * sig;
};

typedef struct Nodo * TipoLista;

TipoLista lista_vacia(void);
int es_lista_vacia(TipoLista lista);
TipoLista inserta_por_cabeza(TipoLista lista, int valor );
TipoLista inserta_por_cola(TipoLista lista, int valor );
TipoLista borra_cabeza(TipoLista lista);
TipoLista borra_cola(TipoLista lista);
int longitud_lista(TipoLista lista);
void muestra_lista(TipoLista lista);
int pertenece(TipoLista lista, int valor );
TipoLista borra_primera_ocurrencia(TipoLista lista, int valor );
TipoLista borra_valor (TipoLista lista, int valor );
TipoLista inserta_en_posicion(TipoLista lista, int pos, int valor );
TipoLista inserta_en_orden(TipoLista lista, int valor );
TipoLista concatena_listas(TipoLista a, TipoLista b);
TipoLista libera_lista(TipoLista lista);

#endif