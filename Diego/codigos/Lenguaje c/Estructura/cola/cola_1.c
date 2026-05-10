
// codigo donde se implementan las funciones /operaciones asociadas a una cola

#include <stdio.h>
#include <stdlib.h>
#include "cola_1.h"

TipoCola cola_vacia(void){

    return NULL;
}

int es_cola_vacia(TipoCola cola){
    
    return cola == NULL;
}

TipoCola inserta_por_cabeza(TipoCola cola, int valor ){
    
    struct Nodo * nuevo = malloc(sizeof (struct Nodo));
    nuevo->info = valor ;
    nuevo->sig = cola;
    cola = nuevo;
    return cola;
}

TipoCola inserta_por_cola(TipoCola cola, int valor ){
    
    struct Nodo * aux , * nuevo;
    nuevo = malloc(sizeof (struct Nodo));
    nuevo->info= valor ;
    nuevo->sig = NULL;
    
    if (cola == NULL){
        cola = nuevo;
    }
    else {
        for (aux = cola; aux ->sig != NULL; aux = aux ->sig) ;
        aux ->sig = nuevo;
    }
    
    return cola;
}

TipoCola borra_cabeza(TipoCola cola){
    
    struct Nodo * aux ;
    
    if (cola != NULL) {
        aux = cola->sig;
        free(cola);
        cola= aux ;
    }
    
    return cola;
}

TipoCola borra_cola(TipoCola cola){
    
    struct Nodo * aux , * atras;
    if (cola != NULL) {
        for (atras = NULL, aux = cola; aux ->sig != NULL; atras= aux , aux = aux ->sig) ;
        free(aux );
        if (atras == NULL){
            cola = NULL;
        }
        else{
            atras->sig = NULL;
        }
    }
    
    return cola;
}

int longitud_cola(TipoCola cola){
    
    struct Nodo * aux ;
    int contador= 0;
    
    for (aux = cola; aux != NULL; aux = aux ->sig)
        contador ++;
        
    return contador ;
}

void muestra_cola(TipoCola cola){ 
    
    struct Nodo * aux ;
    printf ("->");
    for (aux = cola; aux != NULL; aux = aux ->sig)
        printf ("[%d]->", aux ->info);
    printf ("|\n");
}

int pertenece(TipoCola cola, int valor ){
    
    struct Nodo * aux ;
    for (aux =cola; aux != NULL; aux = aux ->sig)
        if (aux ->info== valor )
            return 1;
            
    return 0;
}

TipoCola borra_primera_ocurrencia(TipoCola cola, int valor ){
    
    struct Nodo * aux , * atras;
    
    for (atras = NULL, aux =cola; aux != NULL; atras= aux , aux = aux ->sig){
        if (aux ->info== valor ) {
            if (atras == NULL){
                cola= aux ->sig;
            }
            else{            
                atras->sig= aux ->sig;
            }
            free(aux );
            return cola;
        }
    }
    return cola;
}

TipoCola borra_valor (TipoCola cola, int valor ){
    
    struct Nodo * aux , * atras;
    atras = NULL;
    aux = cola;
    
    while (aux != NULL) {
        if (aux ->info== valor ) {
            if (atras == NULL){
                cola= aux ->sig;
            }
            else{
                atras->sig= aux ->sig;
            }
            free(aux );
            if (atras == NULL){
                aux = cola;
            }
            else{
                aux = atras->sig;
            }
        }
        else {
            atras= aux ;
            aux = aux ->sig;
        }
    }
    
    return cola;
}

TipoCola inserta_en_posicion(TipoCola cola, int pos, int valor ){
    
    struct Nodo * aux , * atras, * nuevo;
    int i;
    
    nuevo = malloc(sizeof (struct Nodo));
    nuevo->info= valor ;
    
    for (i=0, atras=NULL, aux =cola; i < pos && aux != NULL; i++, atras= aux , aux = aux ->sig) ;
    nuevo->sig= aux ;
    
    if (atras == NULL){
        cola= nuevo;
    }
    else{
        atras->sig= nuevo;
    }
    
    return cola;
}

TipoCola inserta_en_orden(TipoCola cola, int valor ){
    
    struct Nodo * aux , * atras, * nuevo;
    nuevo = malloc(sizeof (struct Nodo));
    nuevo->info= valor ;
    for (atras = NULL, aux = cola; aux != NULL; atras= aux , aux = aux ->sig)
    if (valor <= aux ->info) {
        /* Aquı insertamos el nodo entre atras y aux. */
        nuevo->sig= aux ;
        if (atras == NULL){
            cola= nuevo;
        }
        else{
            atras->sig= nuevo;
        }
        return cola;
    }
    
    nuevo->sig = NULL;
    if (atras == NULL){
        cola= nuevo;
    }
    else{
        atras->sig= nuevo;
    }
    
    return cola;
}

TipoCola concatena_colas(TipoCola a, TipoCola b){
    
    TipoCola c = NULL;
    struct Nodo * aux , * nuevo, * anterior = NULL;
    
    for (aux = a; aux != NULL; aux = aux ->sig) {
        nuevo = malloc( sizeof (struct Nodo) );
        nuevo->info= aux ->info;
        if (anterior != NULL){
            anterior ->sig= nuevo;
        }
        else{
            c = nuevo;
        }
        anterior= nuevo;
    }
    
    for (aux = b; aux != NULL; aux = aux ->sig) {
        nuevo = malloc( sizeof (struct Nodo) );
        nuevo->info= aux ->info;
        if (anterior != NULL){
            anterior ->sig= nuevo;
        }
        else{
            c = nuevo;
        }
        anterior= nuevo;
    }
    
    if (anterior != NULL){
        anterior ->sig = NULL;
    }
    
    return c;
}

TipoCola libera_cola(TipoCola cola){
    
    struct Nodo *aux , *otroaux ;
    aux = cola;
    
    while (aux != NULL) {
        otroaux= aux ->sig;
        free(aux );
        aux = otroaux ;
    }
    
    return NULL;
}

