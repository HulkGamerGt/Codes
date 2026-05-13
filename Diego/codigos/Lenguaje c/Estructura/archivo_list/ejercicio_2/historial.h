#ifndef HISTORILA_H
#define HISTORILA_H

// Definición de la estructura para la lista enlazada
typedef struct{
    char rut[15];
    char nombre[50];
    float nota;
    struct Estudiante *sig;
} Estudiante;

// Prototipos de funciones de lógica
Estudiante* insertar_lista(Estudiante *lista, char rut[], char nombre[], float nota);
Estudiante* leer_archivo(Estudiante *lista);
void mostrar_lista(Estudiante *lista);
void calcular_promedio(Estudiante *lista);
void guardar_aprobados(Estudiante *lista);
void liberar_lista(Estudiante *lista);

#endif