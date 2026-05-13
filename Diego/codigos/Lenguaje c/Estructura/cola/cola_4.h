#ifndef COLA_4_H
#define COLA_4_H

typedef struct Cliente {
    char nombre[50];
    int cant_productos;
    int caja;           // 1, 2 o 3
    float monto_total;
    struct Cliente *sig;
} Cliente;

typedef Cliente *ColaCaja;
typedef Cliente *PilaHistorial;

// Operaciones para colas de caja
ColaCaja cola_vacia(void);                // crea cola vacía
int es_cola_vacia(ColaCaja c);            // verifica si está vacía
ColaCaja encolar_cliente(ColaCaja c, Cliente cl);
ColaCaja desencolar_cliente(ColaCaja c, Cliente *atendido);
void mostrar_cola_caja(ColaCaja c, int num_caja);
int clientes_en_espera(ColaCaja c);

// Operaciones para pila de historial
PilaHistorial pila_vacia(void);           // crea pila vacía
int es_pila_vacia(PilaHistorial p);       // verifica si está vacía
PilaHistorial push_historial(PilaHistorial p, Cliente cl);
void mostrar_historial(PilaHistorial p);
float total_vendido_caja(PilaHistorial p, int caja);

// Liberación
void liberar_cola(ColaCaja c);
void liberar_pila(PilaHistorial p);

#endif