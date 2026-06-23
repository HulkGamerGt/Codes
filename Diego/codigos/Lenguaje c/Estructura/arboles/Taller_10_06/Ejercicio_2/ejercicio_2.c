/*
    Nombres : Ruben Sanchez, Diego Solis, Benjamin Vasquez, Joaquin Vasquez.
    Docente : Nicolas Reyes Reyes.
    Tema : Arboles - Taller 10/06
    Fecha : 10/06/2026
    Descripcion: En este programa se implementas las operaciones requeridas para 
                 el manejo de un árbol binario de búsqueda. 
*/


#include "ejercicio_2.h"

// 1. Creación e inicialización de un nuevo nodo
Nodo* nuevoNodo(int valor) {
    Nodo* nodo = (Nodo*)malloc(sizeof(Nodo));
    nodo->dato = valor;                 
    nodo->izq = NULL;
    nodo->der = NULL;         
    return nodo;                            
}

// 2. Inserción recursiva manteniendo la propiedad del ABB
Nodo* insertar(Nodo* raiz, int valor) {
    if (raiz == NULL) return nuevoNodo(valor); // Caso base: lugar vacío encontrado
    
    if (valor < raiz->dato)                    // Si es menor, insertar en subárbol izquierdo
        raiz->izq = insertar(raiz->izq, valor);
    else if (valor > raiz->dato)               // Si es mayor, insertar en subárbol derecho
        raiz->der = insertar(raiz->der, valor); 
        
    return raiz;                     
}



// 3. Recorridos en Profundidad (DFS)
void inorden(Nodo* raiz) {
    if (raiz) {                 /* Si el nodo no tiene hijos */      
        inorden(raiz->izq);         
        printf("%d ", raiz->dato);  
        inorden(raiz->der);         
    }
}

// 4. Recorrido de nodo raiz a sub-arbol izquierda a sub-arbol derecha (Preorden)
void preorden(Nodo* raiz) {
    if (raiz) {                         /* Si el nodo no tiene hijos */
        printf("%d ", raiz->dato);   
        preorden(raiz->izq);         
        preorden(raiz->der);         
    }
}

// 5. Recorrido de sub-arbol izquierda a sub-arbol derecha a nodoraiz (Postorden)
void postorden(Nodo* raiz) {
    if (raiz) {                      /* Si el nodo no tiene hijos, se visita de forma postorden */
        postorden(raiz->izq);        
        postorden(raiz->der);       
        printf("%d ", raiz->dato);   
    }
}

// 6. Recorrido en Amplitud o Niveles (BFS) usando una cola estática
void recorrido_niveles(Nodo* raiz) {
    if (!raiz) return;                          
    
    Nodo* cola[100];                             // Arreglo como cola auxiliar 
    int frente = 0, final = 0;                  
    
    cola[final++] = raiz;                        // Encolar la raíz
    
    while (frente < final) {                    
        Nodo* actual = cola[frente++];           // Desencolar y visitar
        printf("%d ", actual->dato);        
        
        // Encolar hijos de izquierda a derecha
        if (actual->izq) cola[final++] = actual->izq; 
        if (actual->der) cola[final++] = actual->der; 
    }
}


// 7. Gestión de Memoria (Limpieza post-ejecución)
Nodo* liberarArbol(Nodo* raiz) {
    // Se debe liberar utilizando postorden para evitar pérdida de enlaces
    if (raiz) {                   
        liberarArbol(raiz->izq);         
        liberarArbol(raiz->der);       
        free(raiz);                 // Liberar el nodo actual solo después de sus hijos 
    }
    return NULL;
}

/* ----- Función para cargar la secuencia de validación ----- */
/* ---- Se incertan valores predefinidos por la pauta ---- */
void cargarSecuenciaValidacion(Nodo **raiz) {
    int valores[] = {4, 2, 3, 6, 8, 9, 12, 14, 11, -2, -56, 92, 
                     45, -1, 104, 345, -25, -67, 17, 29};

    int n = sizeof(valores) / sizeof(valores[0]);
    for (int i = 0; i < n; i++) {
        *raiz = insertar(*raiz, valores[i]);
    }
    printf("Secuencia de validación cargada.\n");
}


/* ----- Menú interactivo ----- */
void mostrarMenu() {
    printf("\n===== MENU ARBOL BINARIO =====\n");
    printf("1. Insertar un valor\n");
    printf("2. Recorrido Preorden\n");
    printf("3. Recorrido Inorden\n");
    printf("4. Recorrido Postorden\n");
    printf("5. Recorrido por Niveles\n");
    printf("0. Salir\n");
    printf("Seleccione una opcion: ");
}