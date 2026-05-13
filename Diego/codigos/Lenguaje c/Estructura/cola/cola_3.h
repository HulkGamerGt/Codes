#ifndef COLA_3_H
#define COLA_3_H

typedef enum { NORMAL, URGENTE } Prioridad;

typedef struct Documento {
    char nombre[50];
    char usuario[50];
    int paginas;
    Prioridad prioridad;
    struct Documento *sig;
} Documento;

typedef Documento *ColaImpresion;
typedef Documento *PilaHistorial;

// Cola de impresión
ColaImpresion cola_impresion_vacia(void);
int cola_vacia(ColaImpresion c);
ColaImpresion encolar(ColaImpresion c, Documento doc);
ColaImpresion desencolar(ColaImpresion c, Documento *atendido);
void mostrar_cola(ColaImpresion c);
int buscar_en_cola(ColaImpresion c, const char *nombre_doc);

// Pila de historial
PilaHistorial pila_historial_vacia(void);
int pila_vacia(PilaHistorial p);
PilaHistorial push_historial(PilaHistorial p, Documento doc);
void mostrar_historial(PilaHistorial p);
int total_paginas_impresas(PilaHistorial p);

// Liberación
void liberar_cola(ColaImpresion c);
void liberar_pila(PilaHistorial p);

#endif