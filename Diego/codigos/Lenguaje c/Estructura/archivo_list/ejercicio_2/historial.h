#ifndef HISTORIAL_H
#define HISTORIAL_H

// Nodo para la pila (cada acción)
typedef struct PilaNode {
    char accion[100];
    struct PilaNode *sig;
} PilaNode;

// Funciones de pila
PilaNode* push(PilaNode *pila, const char *accion);
PilaNode* pop(PilaNode *pila, char *accion_salida);
void mostrar_pila(PilaNode *pila);
void guardar_pila_en_archivo(PilaNode *pila, const char *nombre_archivo);
void liberar_pila(PilaNode *pila);

// Lectura desde archivo (devuelve una lista simple de acciones)
PilaNode* cargar_acciones_a_pila(PilaNode *pila, const char *nombre_archivo);

#endif
