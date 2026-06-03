
#include <stdio.h>
#include <stdlib.h>

/* =========================
   ESTRUCTURA NODO
========================= */

typedef struct Nodo{
    int dato;
    struct Nodo* sig;
}Nodo;

/* =========================
   COLA (Misiones normales)
========================= */

typedef struct{
    Nodo* frente;
    Nodo* final;
}Cola;

void inicializarCola(Cola* c){
    c->frente = NULL;
    c->final = NULL;
}

int colaVacia(Cola* c){
    return c->frente == NULL;
}

void encolar(Cola* c, int dato){
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));

    nuevo->dato = dato;
    nuevo->sig = NULL;

    if(colaVacia(c)){
        c->frente = nuevo;
        c->final = nuevo;
    }else{
        c->final->sig = nuevo;
        c->final = nuevo;
    }

    printf("Mision normal %d agregada.\n", dato);
}

int desencolar(Cola* c){
    if(colaVacia(c)){
        return -1;
    }

    Nodo* aux = c->frente;
    int dato = aux->dato;

    c->frente = aux->sig;

    if(c->frente == NULL){
        c->final = NULL;
    }

    free(aux);

    return dato;
}

void mostrarCola(Cola* c){
    Nodo* aux = c->frente;

    if(aux == NULL){
        printf("No hay misiones normales.\n");
        return;
    }

    printf("Cola de misiones normales:\n");

    while(aux != NULL){
        printf("%d -> ", aux->dato);
        aux = aux->sig;
    }

    printf("NULL\n");
}

/* =========================
   PILA (Misiones urgentes)
========================= */

typedef struct{
    Nodo* tope;
}Pila;

void inicializarPila(Pila* p){
    p->tope = NULL;
}

int pilaVacia(Pila* p){
    return p->tope == NULL;
}

void apilar(Pila* p, int dato){
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));

    nuevo->dato = dato;
    nuevo->sig = p->tope;

    p->tope = nuevo;

    printf("Mision urgente %d agregada.\n", dato);
}

int desapilar(Pila* p){
    if(pilaVacia(p)){
        return -1;
    }

    Nodo* aux = p->tope;
    int dato = aux->dato;

    p->tope = aux->sig;

    free(aux);

    return dato;
}

void mostrarPila(Pila* p){
    Nodo* aux = p->tope;

    if(aux == NULL){
        printf("No hay misiones urgentes.\n");
        return;
    }

    printf("Pila de misiones urgentes:\n");

    while(aux != NULL){
        printf("%d -> ", aux->dato);
        aux = aux->sig;
    }

    printf("NULL\n");
}


/* =========================
   MENU
========================= */

void menu(){
    printf("\n========== SISTEMA DE MISIONES ==========\n");
    printf("1. Agregar Mision Normal (MN)\n");
    printf("2. Agregar Mision Urgente (MU)\n");
    printf("3. Resolver Mision (RM)\n");
    printf("4. Invertir Recompensas (IR)\n");
    printf("5. Mostrar Misiones Normales\n");
    printf("6. Mostrar Misiones Urgentes\n");
    printf("7. Mostrar Recompensas\n");
    printf("8. Borrar Recompensa (BR)\n");
    printf("0. Salir\n");
    printf("Seleccione una opcion: ");
}

/* =========================
   MAIN
========================= */


```
