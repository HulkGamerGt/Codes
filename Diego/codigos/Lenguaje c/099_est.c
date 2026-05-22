#include <stdio.h>
#include <stdlib.h>
#include <string.h>

registrar_accion(AccionSistema* s, char* descripcion);
deshacer(AccionSistema* s);
rehacer(AccionSistema* s);

// Nodo para almacenar cada acción
typedef struct NodoAccion {
    char descripcion[100];
    struct NodoAccion* sig;
} NodoAccion;

// Contenedor principal del sistema
typedef struct {
    NodoAccion* historial_deshacer; // Pila para deshacer (Undo)
    NodoAccion* historial_rehacer;  // Pila para rehacer (Redo)
} AccionSistema;

// Inicializa el sistema
void inicializar_sistema(AccionSistema* s) {
    s->historial_deshacer = NULL;
    s->historial_rehacer = NULL;
}



int main() {
    AccionSistema sistema;
    inicializar_sistema(&sistema);

    printf("--- Simulando Acciones ---\n");
    // Código para probar tu implementación...
    
    return 0;
}

/*
Selección de Estructuras: Determina qué estructura de las vistas en 
la guía (¿Lista simple, Lista doble, Pila o Cola?) es la óptima para
modelar el comportamiento del historial de "Deshacer" y cuál para el de 
"Rehacer". Pista: Piensa en el principio de flujo (LIFO o FIFO) que requiere 
el botón Ctrl+Z.  

Definición de Estructuras en C: Define la estructura del Nodo y 
la estructura contenedora AccionSistema.

Implementación: Escribe el código en C de las tres funciones 
principales, asegurándote de gestionar correctamente la memoria 
dinámica (malloc y free) para evitar fugas, tal como se muestra en 
los ejemplos del documento.
*/

registrar_accion(AccionSistema* s, char* descripcion);

deshacer(AccionSistema* s);

rehacer(AccionSistema* s);