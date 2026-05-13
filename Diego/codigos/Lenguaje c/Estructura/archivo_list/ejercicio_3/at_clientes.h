#ifndef AT_CLIENTES_H
#define AT_CLIENTES_H

// Definición de la estructura para la lista enlazada
typedef struct{
    int numero;
    char nombre[50];
    char accion[50];
    struct CLIENTE *sig;
} CLIENTE;

// Prototipos de funciones de lógica
CLIENTE* insertar_lista(CLIENTE *lista,int numero, char nombre[], char accion[]);
CLIENTE* leer_archivo(CLIENTE *lista);
void mostrar_lista(CLIENTE *lista);
void calcular_promedio(CLIENTE *lista);
void guardar_aprobados(CLIENTE *lista);
void liberar_lista(CLIENTE *lista);

#endif