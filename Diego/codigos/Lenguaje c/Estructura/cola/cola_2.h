#ifndef COLA_2_H
#define COLA_2_H

typedef struct Persona {
    char nombre[50];
    int num_atencion;
    struct Persona *sig;
} Persona;

typedef Persona *Cola;

extern Cola cola_vacia(void);
extern int es_cola_vacia(Cola c);
extern Cola encolar(Cola c, char *nombre, int num);
extern Cola desencolar(Cola c);          // atiende al primero
extern void mostrar_proximo(Cola c);
extern void mostrar_cola(Cola c);
extern void liberar_cola(Cola c);

#endif
