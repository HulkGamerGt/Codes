#ifndef AT_CLIENTES_H
#define AT_CLIENTES_H

typedef struct Cliente {
    int numero;
    char nombre[50];
    char tramite[50];
    struct Cliente *sig;
} CLIENTE;

// Operaciones de cola
CLIENTE* encolar(CLIENTE *cola, int numero, const char *nombre, const char *tramite);
CLIENTE* desencolar(CLIENTE *cola, int *num, char nombre[], char tramite[]);
void mostrar_cola(CLIENTE *cola);
void guardar_pendientes(CLIENTE *cola, const char *archivo);
void liberar_cola(CLIENTE *cola);
CLIENTE* cargar_clientes_desde_archivo(CLIENTE *cola, const char *archivo);

#endif
