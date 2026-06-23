/*
    Nombres : Ruben Sanchez, Diego Solis, Benjamin Vasquez, Joaquin Vasquez.
    Docente : Nicolas Reyes Reyes.
    Tema : Informe Estructuras de Datos - Serviexpress
    Descripcion: En este apartado se definen las estructuras de datos y funciones del serviexpress.c
    necesarias para la gestion de clientes en la oficina de atencion al cliente "Serviexpress".
    Se implementan una lista enlazada para los clientes agendados, una cola para los clientes en espera,
    y una pila para el historial de atenciones. Ademas, se incluyen funciones para cargar los
    datos iniciales desde archivos, procesar operaciones y generar reportes finales.
*/

#ifndef SERVIEXPRESS_H
#define SERVIEXPRESS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Constantes para tipo de solicitud */
#define TIPO_CONSULTA   0
#define TIPO_PAGO       1
#define TIPO_RECLAMO    2
#define TIPO_TRAMITE    3

/* Constantes para estado del cliente */
#define ESTADO_AGENDADO  0
#define ESTADO_EN_ESPERA 1
#define ESTADO_ATENDIDO  2
#define ESTADO_CANCELADO 3
#define ESTADO_ANULADO   4

/* Tamaños máximos de campos */
#define MAX_RUT    12
#define MAX_NOMBRE 50
#define MAX_HORA   6

/* Estructura que representa un cliente */
typedef struct {
    char rut[MAX_RUT];
    char nombre[MAX_NOMBRE];
    int tipo;           /* TIPO_CONSULTA, TIPO_PAGO, ... */
    char hora[MAX_HORA];
    int prioridad;      /* 1..3 */
    int estado;         /* ESTADO_AGENDADO, ESTADO_EN_ESPERA, ... */
} Cliente;

/* Nodo para lista simplemente enlazada de agendados */
typedef struct NodoLista {
    Cliente dato;
    struct NodoLista *sig;
} NodoLista;

/* Lista simplemente enlazada con punteros a cabeza y cola */
typedef struct {
    NodoLista *cabeza;
    NodoLista *cola;
} ListaEnlazada;

/* Nodo para cola FIFO */
typedef struct NodoCola {
    Cliente dato;
    struct NodoCola *sig;
} NodoCola;

/* Cola con punteros a frente y final */
typedef struct {
    NodoCola *frente;
    NodoCola *final;
} Cola;

/* Nodo para pila LIFO */
typedef struct NodoPila {
    Cliente dato;
    struct NodoPila *sig;
} NodoPila;

/* Pila con puntero al tope */
typedef struct {
    NodoPila *tope;
} Pila;

/* Variables globales para estadísticas */
extern int total_cargados_inicial;
extern int total_agendados_acum;
extern int total_cola_acum;
extern int total_cancelados;
extern int total_anulados;

/* Inicialización de estructuras */
void inicializarLista(ListaEnlazada *l);
void inicializarCola(Cola *c);
void inicializarPila(Pila *p);

/* Liberación de memoria */
void liberarLista(ListaEnlazada *l);
void liberarCola(Cola *c);
void liberarPila(Pila *p);

/* Operaciones sobre lista enlazada */
void insertarFinalLista(ListaEnlazada *l, Cliente c);
NodoLista* buscarEnLista(ListaEnlazada *l, const char *rut, NodoLista **anterior);
int eliminarNodoLista(ListaEnlazada *l, NodoLista *nodo, NodoLista *anterior);
int existeEnLista(ListaEnlazada *l, const char *rut);

/* Operaciones sobre cola */
void encolar(Cola *c, Cliente cl);
int desencolar(Cola *c, Cliente *salida);
NodoCola* buscarEnCola(Cola *c, const char *rut, NodoCola **anterior);
int eliminarNodoCola(Cola *c, NodoCola *nodo, NodoCola *anterior);
int existeEnCola(Cola *c, const char *rut);

/* Operaciones sobre pila */
void apilar(Pila *p, Cliente c);
int desapilar(Pila *p, Cliente *salida);
int existeEnPila(Pila *p, const char *rut);

/* Verificación global de RUT duplicado */
int existeRutGlobal(ListaEnlazada *lista, Cola *cola, Pila *historial, const char *rut);

/* Atención de clientes */
int atenderCliente(ListaEnlazada *lista, Cola *cola, Pila *historial, Cliente *atendido);
int atenderConPrioridad(ListaEnlazada *lista, Cola *cola, Pila *historial, Cliente *atendido);
int deshacerAtencion(Pila *historial, Pila *anulados, FILE *logFile);

/* Carga de archivos iniciales */
int cargarClientesAgendados(const char *nombre, ListaEnlazada *lista, Cola *cola, Pila *historial, FILE *logFile);
int cargarClientesLlegada(const char *nombre, Cola *cola, ListaEnlazada *lista, Pila *historial, FILE *logFile);

/* Procesamiento del archivo de operaciones */
void procesarOperaciones(const char *nombre, ListaEnlazada *lista, Cola *cola,
                         Pila *historial, Pila *anulados, FILE *logFile);

/* Generación de reportes finales */
void generarReporteFinal(const char *nombre, ListaEnlazada *lista, Cola *cola,
                         Pila *historial, Pila *anulados);
void generarEstadisticas(const char *nombre, ListaEnlazada *lista, Cola *cola,
                         Pila *historial, int totalInicial,
                         int totalAgendadosAcum, int totalColaAcum);

#endif