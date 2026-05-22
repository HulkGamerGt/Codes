#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

typedef struct Estudiante {
    char rut[15];
    char nombre[50];
    float nota;
    struct Estudiante *sig;   // puntero al siguiente
} Estudiante;

// Prototipos
Estudiante* insertar_lista(Estudiante *lista, char rut[], char nombre[], float nota);
Estudiante* leer_archivo(Estudiante *lista);
void mostrar_lista(Estudiante *lista);
void calcular_promedio(Estudiante *lista);
void guardar_aprobados(Estudiante *lista);
void liberar_lista(Estudiante *lista);

#endif
