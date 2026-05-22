/*¿Cómo escribirías en C la definición completa de un struct llamado Nodo que contenga un número entero 
(llamémoslo dato) y el puntero necesario para conectarse al siguiente eslabón?*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo{
    int dato;
    struct Nodo *sig;
}Nodo;


/*¿Cómo escribirías la línea de código dentro de esta función 
para crear un puntero llamado nuevo y asignarle memoria dinámica usando 
malloc con el tamaño correcto de nuestro struct Nodo?*/

void insertarInicio(struct Nodo **cabeza, int valor) {
    // 1. Pedir memoria en el Heap para el nuevo nodo
    Nodo *aux;
    Nodo *nuevo = (Nodo*)malloc(sizeof(Nodo));
        
    // 2. Asignar el valor al nuevo nodo
    
    if (nuevo == NULL) {
        printf("Error al reservar memoria.\n");
        return; // Sale de la función void
    }
    nuevo->dato = valor;

    // 3. Conectar el nuevo nodo a la lista existente

    nuevo->sig = *cabeza;
    *cabeza = nuevo;

    // 4. Actualizar la cabeza de la lista

    return *cabeza;
}

void imprimirLista(struct Nodo *cabeza) {
    struct Nodo *actual = cabeza; // Empezamos en el inicio
    
    // Mientras no lleguemos al final de la lista...
    while (actual != NULL) {
        // 1. Imprimir el dato del nodo actual
        
        printf("%d\n",actual->dato);

        // 2. Avanzar al siguiente nodo
        actual= actual->sig;
    }
    printf("NULL\n"); // Para indicar el fin de la lista
}

void liberarLista(struct Nodo *cabeza) {
    struct Nodo *temporal;
    
    while (cabeza != NULL) {
        temporal = cabeza->sig; // 1. Guarda el siguiente nodo
        free(cabeza);           // 2. Libera el nodo actual
        cabeza = temporal;      // 3. Avanza al nodo guardado
    }
}


int main() {
    // Creamos la lista vacía
    struct Nodo *miLista = NULL;

    // Insertamos tres elementos
    insertarInicio(&miLista, 10);
    insertarInicio(&miLista, 20);
    insertarInicio(&miLista, 30);

    // Mostramos el resultado
    printf("Contenido de la lista: ");
    imprimirLista(miLista);

    return 0;
}
