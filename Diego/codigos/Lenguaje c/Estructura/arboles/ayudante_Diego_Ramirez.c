#include <stdio.h>
#include <stdlib.h>

// 1. Estructura base del Nodo
typedef struct nodo {
    int dato;           // Valor almacenado en el nodo
    struct nodo* izq;   // Puntero al subárbol izquierdo
    struct nodo* der;   // Puntero al subárbol derecho
} Nodo;

// 2. Creación e inicialización de un nuevo nodo
Nodo* nuevoNodo(int valor) {
    Nodo* nodo = (Nodo*)malloc(sizeof(Nodo));
    nodo->dato = valor;                 
    nodo->izq = nodo->der = NULL;         
    return nodo;                            
}

// 3. Inserción recursiva manteniendo la propiedad del ABB
Nodo* insertar(Nodo* raiz, int valor) {
    if (raiz == NULL) return nuevoNodo(valor); // Caso base: lugar vacío encontrado
    
    if (valor < raiz->dato)                    // Si es menor, insertar en subárbol izquierdo
        raiz->izq = insertar(raiz->izq, valor);
    else if (valor > raiz->dato)               // Si es mayor, insertar en subárbol derecho
        raiz->der = insertar(raiz->der, valor); 
        
    return raiz;                     
}

// 4. Búsqueda de un elemento
Nodo* buscar(Nodo* raiz, int valor) {
    // Retorna la raíz si es NULL o si el nodo actual contiene el valor buscado
    if (raiz == NULL || raiz->dato == valor) return raiz; 
    
    if (valor < raiz->dato)                           
        return buscar(raiz->izq, valor);                  // Buscar en el izquierdo
    else
        return buscar(raiz->der, valor);                  // Buscar en el derecho
}

// 5. Función auxiliar: Sucesor Inorden (Menor nodo del subárbol derecho)
Nodo* minimo(Nodo* nodo) {
    // Desciende completamente hacia la izquierda para encontrar el valor mínimo
    while (nodo->izq) nodo = nodo->izq; 
    return nodo;                      
}

// 6. Eliminación de un nodo manejando los 3 casos estructurales
Nodo* eliminar(Nodo* raiz, int valor) {
    if (raiz == NULL) return raiz;                          
    
    // Proceso de búsqueda del nodo a eliminar
    if (valor < raiz->dato)                                 
        raiz->izq = eliminar(raiz->izq, valor);             
    else if (valor > raiz->dato)                            
        raiz->der = eliminar(raiz->der, valor);               
    else {                                                
        // Caso 1 y Caso 2: Nodo hoja (0 hijos) o con 1 único hijo 
        if (!raiz->izq) return raiz->der;                
        else if (!raiz->der) return raiz->izq;             
        
        // Caso 3: Nodo con 2 hijos. Reemplazo por el sucesor inorden 
        Nodo* temp = minimo(raiz->der);                       // Se obtiene la menor clave del subárbol derecho
        raiz->dato = temp->dato;                              // Se copia la información al nodo actual
        raiz->der = eliminar(raiz->der, temp->dato);          // Se elimina el nodo duplicado en la hoja
    }
    return raiz;                                             
}

// 7. Recorridos en Profundidad (DFS)
void inorden(Nodo* raiz) {
    if (raiz) {                      
        inorden(raiz->izq);         
        printf("%d ", raiz->dato);  
        inorden(raiz->der);         
    }
}

void preorden(Nodo* raiz) {
    if (raiz) {                      
        printf("%d ", raiz->dato);   
        preorden(raiz->izq);         
        preorden(raiz->der);         
    }
}

void postorden(Nodo* raiz) {
    if (raiz) {                      
        postorden(raiz->izq);        
        postorden(raiz->der);       
        printf("%d ", raiz->dato);   
    }
}

// 8. Recorrido en Amplitud o Niveles (BFS) usando una cola estática
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

// 9. Funciones Analíticas y Topológicas
int contar_nodos(Nodo* r) {
    if (!r) return 0;                                         
    return 1 + contar_nodos(r->izq) + contar_nodos(r->der);   
}

int altura(Nodo* r) {
    if (!r) return 0;                         
    int ai = altura(r->izq);                  // Altura subárbol izquierdo
    int ad = altura(r->der);                  // Altura subárbol derecho 
    return (ai > ad ? ai : ad) + 1;           // Se retorna el camino más largo más la raíz 
}

void imprimir_hojas(Nodo* r) {
    if (r) {                                
        if (!r->izq && !r->der) {                 // Condición estricta de nodo hoja 
            printf("%d ", r->dato);               
        }
        imprimir_hojas(r->izq);                  
        imprimir_hojas(r->der);                  
    }
}

// 10. Gestión de Memoria (Limpieza post-ejecución)
void liberar(Nodo* raiz) {
    // Se debe liberar utilizando postorden para evitar pérdida de enlaces
    if (raiz) {                   
        liberar(raiz->izq);         
        liberar(raiz->der);       
        free(raiz);                 // Liberar el nodo actual solo después de sus hijos 
    }
}