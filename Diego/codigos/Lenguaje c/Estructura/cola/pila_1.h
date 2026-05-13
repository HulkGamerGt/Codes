#ifndef PILA_1_H
#define PILA_1_H

struct Nodo {
    int info;
    struct Nodo *sig;
};

typedef struct Nodo *Pila;

extern Pila pila_vacia(void);
extern int es_pila_vacia(Pila p);
extern Pila push(Pila p, int valor);
extern Pila pop(Pila p);
extern int cima(Pila p);              // devuelve el valor sin borrar
extern void mostrar_pila(Pila p);
extern void liberar_pila(Pila p);

#endif