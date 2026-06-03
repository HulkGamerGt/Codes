#ifndef COLA_H
#define COLA_H

typedef struct NodoDeque {
    int m_normal;
    int m_urgente;
    int recompensa;                // valor del nodo
    struct NodoDeque* anterior;    // puntero al nodo anterior
    struct NodoDeque* siguiente;   // puntero al nodo siguiente
} NodoDeque;

typedef struct {
    NodoDeque* frente;   // primer nodo
    NodoDeque* final;    // último nodo
    int tam;             // cantidad de elementos
} Deque;

extern void inicializarDeque(Deque* d);

extern int dequeVacio(const Deque* d);

extern int encolarFrente(Deque* d, int m_normal);

extern int encolarFinal(Deque* d, int m_normal);

extern int desencolarFrente(Deque* d, int* m_normal);

extern int desencolarFinal(Deque* d, int* m_normal);

extern int verFrente(const Deque* d, int* m_normal);

extern int verFinal(const Deque* d, int* m_normal);

extern int tamanioDeque(const Deque* d);

extern void mostrarDeque(const Deque* d);

extern int buscarEnDeque(const Deque* d, int m_normal);

extern int copiarDeque(const Deque* origen, Deque* destino);

extern void invertirDeque(Deque* d);

extern void rotarDeque(Deque* d, int n);

extern void ordenarDeque(Deque* d);

extern void liberarDeque(Deque* d);

#endif // COLA_H