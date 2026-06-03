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

/* Constantes para tipo de solicitud y estado */

#define TIPO_CONSULTA   0
#define TIPO_PAGO       1
#define TIPO_RECLAMO    2
#define TIPO_TRAMITE    3

#define ESTADO_AGENDADO  0
#define ESTADO_EN_ESPERA 1
#define ESTADO_ATENDIDO  2
#define ESTADO_CANCELADO 3
#define ESTADO_ANULADO   4

#define MAX_RUT    12
#define MAX_NOMBRE 50
#define MAX_HORA   6

/* Estructura Cliente*/
typedef struct{
    char rut[MAX_RUT];
    char nombre[MAX_NOMBRE];
    int tipo;           /* TIPO_CONSULTA, TIPO_PAGO, ... */
    char hora[MAX_HORA];
    int prioridad;      /* 1..3 */
    int estado;         /* ESTADO_AGENDADO, ESTADO_EN_ESPERA, ... */
} Cliente;

/* Nodos para cada estructura */
typedef struct NodoLista{
    Cliente dato;
    struct NodoLista *sig;
} NodoLista;

typedef struct{
    NodoLista *cabeza;
    NodoLista *cola;
} ListaEnlazada;

typedef struct NodoCola{
    Cliente dato;
    struct NodoCola *sig;
} NodoCola;

typedef struct{
    NodoCola *frente;
    NodoCola *final;
} Cola;

typedef struct NodoPila{
    Cliente dato;
    struct NodoPila *sig;
} NodoPila;

typedef struct{
    NodoPila *tope;
} Pila;

/* Variables globales para estadisticas */
extern int total_cargados_inicial;
extern int total_cancelados;


/* Funciones del main*/

/* Inicializacion y liberacion */
void inicializarLista(ListaEnlazada *l);
void inicializarCola(Cola *c);
void inicializarPila(Pila *p);
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

/* Verificacion global de duplicados */
int existeRutGlobal(ListaEnlazada *lista, Cola *cola, Pila *pila, const char *rut);

/* Atencion */
int atenderCliente(ListaEnlazada *lista, Cola *cola, Pila *historial, Cliente *atendido);
int atenderConPrioridad(ListaEnlazada *lista, Cola *cola, Pila *historial, Cliente *atendido);
int deshacerAtencion(Pila *historial);

/* Carga de archivos iniciales */
int cargarClientesAgendados(const char *nombre, ListaEnlazada *lista, Cola *cola, Pila *pila);
int cargarClientesLlegada(const char *nombre, Cola *cola, ListaEnlazada *lista, Pila *pila);

/* Procesamiento de operaciones */
void procesarOperaciones(const char *nombre, ListaEnlazada *lista, Cola *cola, Pila *historial, FILE *logFile);

/* Generacion de reportes */
void generarReporteFinal(const char *nombre, ListaEnlazada *lista, Cola *cola, Pila *historial);
void generarEstadisticas(const char *nombre, ListaEnlazada *lista, Cola *cola, Pila *historial, int totalInicial);

#endif /* SERVIEXPRESS_H */