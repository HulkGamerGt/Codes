#include "arbol.h"

/* ===================================================================
 *                      FUNCIONES BÁSICAS
 * =================================================================== */

/*
 * Crea un nuevo nodo.
 * Reserva memoria con malloc, asigna el valor y pone los punteros a NULL.
 */
Nodo* crearNodo(int valor) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    if (nuevo != NULL) {
        nuevo->dato = valor;
        nuevo->izquierda = NULL;
        nuevo->derecha = NULL;
    }
    return nuevo;
}

/*
 * Inserción en un BST.
 * Si la raíz es NULL, se crea un nuevo nodo.
 * Si el valor es menor, se inserta recursivamente en el subárbol izquierdo.
 * Si es mayor, en el subárbol derecho.
 * Si es igual, no se hace nada (no duplicados).
 */
Nodo* insertar(Nodo* raiz, int valor) {
    if (raiz == NULL) {
        return crearNodo(valor);   /* caso base: árbol vacío */
    }
    if (valor < raiz->dato) {
        raiz->izquierda = insertar(raiz->izquierda, valor);
    } else if (valor > raiz->dato) {
        raiz->derecha = insertar(raiz->derecha, valor);
    }
    /* si valor == raiz->dato no se inserta (se ignora) */
    return raiz;
}

/*
 * Búsqueda recursiva en BST.
 * Se compara el valor con el nodo actual:
 *   - Si es igual, se retorna el nodo.
 *   - Si es menor, se busca en la izquierda.
 *   - Si es mayor, en la derecha.
 * Si se llega a NULL, el valor no está.
 */
Nodo* buscar(Nodo* raiz, int valor) {
    if (raiz == NULL || raiz->dato == valor) {
        return raiz;
    }
    if (valor < raiz->dato) {
        return buscar(raiz->izquierda, valor);
    }
    return buscar(raiz->derecha, valor);
}

/*
 * Encuentra el mínimo de un subárbol.
 * Avanza por la izquierda mientras exista nodo.
 */
Nodo* minimo(Nodo* nodo) {
    Nodo* actual = nodo;
    while (actual != NULL && actual->izquierda != NULL) {
        actual = actual->izquierda;
    }
    return actual;
}

/*
 * Eliminación de un nodo en BST.
 * Se busca el nodo recursivamente.
 * Al encontrarlo:
 *   1) Si no tiene hijo izquierdo, se reemplaza por el derecho (puede ser NULL).
 *   2) Si no tiene hijo derecho, se reemplaza por el izquierdo.
 *   3) Si tiene ambos, se reemplaza por el sucesor inorden (mínimo del subárbol derecho),
 *      se copia su valor y se elimina ese sucesor.
 */
Nodo* eliminar(Nodo* raiz, int valor) {
    if (raiz == NULL) return raiz;

    if (valor < raiz->dato) {
        raiz->izquierda = eliminar(raiz->izquierda, valor);
    } else if (valor > raiz->dato) {
        raiz->derecha = eliminar(raiz->derecha, valor);
    } else {
        /* Nodo encontrado */
        /* Caso 1: sin hijo izquierdo */
        if (raiz->izquierda == NULL) {
            Nodo* temp = raiz->derecha;
            free(raiz);
            return temp;
        }
        /* Caso 2: sin hijo derecho */
        else if (raiz->derecha == NULL) {
            Nodo* temp = raiz->izquierda;
            free(raiz);
            return temp;
        }
        /* Caso 3: dos hijos */
        Nodo* temp = minimo(raiz->derecha);          /* sucesor inorden */
        raiz->dato = temp->dato;                     /* copiamos el valor */
        raiz->derecha = eliminar(raiz->derecha, temp->dato); /* eliminamos el sucesor */
    }
    return raiz;
}

/*
 * Recorrido inorden: izquierda → raíz → derecha.
 * Visita los nodos en orden ascendente.
 */
void inorden(Nodo* raiz) {
    if (raiz != NULL) {
        inorden(raiz->izquierda);
        printf("%d ", raiz->dato);
        inorden(raiz->derecha);
    }
}

/*
 * Recorrido preorden: raíz → izquierda → derecha.
 */
void preorden(Nodo* raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->dato);
        preorden(raiz->izquierda);
        preorden(raiz->derecha);
    }
}

/*
 * Recorrido postorden: izquierda → derecha → raíz.
 */
void postorden(Nodo* raiz) {
    if (raiz != NULL) {
        postorden(raiz->izquierda);
        postorden(raiz->derecha);
        printf("%d ", raiz->dato);
    }
}

/* ===================================================================
 *                      FUNCIONES AVANZADAS
 * =================================================================== */

/*
 * Altura del árbol.
 * Se calcula recursivamente: 1 + máximo(altura(izq), altura(der)).
 * Árbol vacío tiene altura 0.
 */
int altura(Nodo* raiz) {
    if (raiz == NULL) return 0;
    int altIzq = altura(raiz->izquierda);
    int altDer = altura(raiz->derecha);
    return 1 + (altIzq > altDer ? altIzq : altDer);
}

/*
 * Contar nodos: 1 (raíz) + nodos izquierda + nodos derecha.
 */
int contarNodos(Nodo* raiz) {
    if (raiz == NULL) return 0;
    return 1 + contarNodos(raiz->izquierda) + contarNodos(raiz->derecha);
}

/*
 * Contar hojas: si el nodo no tiene hijos, es hoja (retorna 1).
 * Si no, suma las hojas de ambos subárboles.
 */
int contarHojas(Nodo* raiz) {
    if (raiz == NULL) return 0;
    if (raiz->izquierda == NULL && raiz->derecha == NULL)
        return 1;
    return contarHojas(raiz->izquierda) + contarHojas(raiz->derecha);
}

/*
 * Espejo del árbol.
 * Intercambia los punteros izquierdo y derecho y se llama recursivamente.
 */
void espejo(Nodo* raiz) {
    if (raiz == NULL) return;
    Nodo* temp = raiz->izquierda;
    raiz->izquierda = raiz->derecha;
    raiz->derecha = temp;
    espejo(raiz->izquierda);
    espejo(raiz->derecha);
}

/*
 * Recorrido por niveles (BFS) con una cola estática.
 * Se encola la raíz y mientras la cola no esté vacía:
 *   - se desencola y se imprime,
 *   - se encolan sus hijos (si existen).
 */
#define MAX_COLA_LOCAL 1000

static void encolarLocal(Nodo* cola[], int* final, Nodo* nodo) {
    if (*final < MAX_COLA_LOCAL)
        cola[(*final)++] = nodo;
}

static Nodo* desencolarLocal(Nodo* cola[], int* frente) {
    if (*frente < *final)
        return cola[(*frente)++];
    return NULL;
}

void nivelOrden(Nodo* raiz) {
    if (raiz == NULL) return;
    Nodo* cola[MAX_COLA_LOCAL];
    int frente = 0, final = 0;
    encolarLocal(cola, &final, raiz);
    while (frente < final) {
        Nodo* actual = desencolarLocal(cola, &frente);
        printf("%d ", actual->dato);
        if (actual->izquierda) encolarLocal(cola, &final, actual->izquierda);
        if (actual->derecha) encolarLocal(cola, &final, actual->derecha);
    }
}

/*
 * Ancestro común más bajo (LCA) en BST.
 * Aprovecha la propiedad de orden:
 *   - Si ambos valores son menores, el LCA está en la izquierda.
 *   - Si ambos son mayores, está en la derecha.
 *   - Si uno es menor y otro mayor (o iguales), el nodo actual es el LCA.
 */
Nodo* ancestroComun(Nodo* raiz, int v1, int v2) {
    if (raiz == NULL) return NULL;
    if (v1 < raiz->dato && v2 < raiz->dato)
        return ancestroComun(raiz->izquierda, v1, v2);
    if (v1 > raiz->dato && v2 > raiz->dato)
        return ancestroComun(raiz->derecha, v1, v2);
    return raiz;
}

/*
 * Función auxiliar para k-ésimo menor.
 * Realiza un recorrido inorden, llevando un contador.
 * Cuando el contador alcanza k, guarda el resultado.
 */
static void kEsimoMenorUtil(Nodo* raiz, int k, int* contador, int* resultado) {
    if (raiz == NULL || *contador >= k) return;
    kEsimoMenorUtil(raiz->izquierda, k, contador, resultado);
    (*contador)++;
    if (*contador == k) {
        *resultado = raiz->dato;
        return;
    }
    kEsimoMenorUtil(raiz->derecha, k, contador, resultado);
}

int kEsimoMenor(Nodo* raiz, int k) {
    int contador = 0;
    int resultado = -1;
    kEsimoMenorUtil(raiz, k, &contador, &resultado);
    return resultado;
}

/*
 * Verifica si el árbol está balanceado.
 * Calcula la altura de ambos lados, verifica que la diferencia sea ≤ 1
 * y que ambos subárboles también estén balanceados.
 */
int esBalanceado(Nodo* raiz) {
    if (raiz == NULL) return 1;
    int altIzq = altura(raiz->izquierda);
    int altDer = altura(raiz->derecha);
    if (abs(altIzq - altDer) <= 1 &&
        esBalanceado(raiz->izquierda) &&
        esBalanceado(raiz->derecha))
        return 1;
    return 0;
}

/*
 * Función auxiliar para verificar si es BST.
 * Comprueba que el dato del nodo esté dentro del rango [min, max].
 * Inicialmente el rango es el mínimo y máximo entero posible.
 */
static int esBSTUtil(Nodo* raiz, int min, int max) {
    if (raiz == NULL) return 1;
    if (raiz->dato < min || raiz->dato > max) return 0;
    return esBSTUtil(raiz->izquierda, min, raiz->dato - 1) &&
           esBSTUtil(raiz->derecha, raiz->dato + 1, max);
}

int esBST(Nodo* raiz) {
    return esBSTUtil(raiz, -2147483648, 2147483647);
}

/*
 * Impresión visual del árbol (rotado 90° antihorario).
 * Se imprime primero el subárbol derecho (aparece arriba),
 * luego la raíz con sangría, luego el subárbol izquierdo.
 * La sangría aumenta en cada nivel.
 */
void imprimirArbol(Nodo* raiz, int espacio) {
    if (raiz == NULL) return;
    espacio += 5;
    imprimirArbol(raiz->derecha, espacio);   /* imprime parte derecha */
    printf("\n");
    for (int i = 5; i < espacio; i++)
        printf(" ");
    printf("%d\n", raiz->dato);
    imprimirArbol(raiz->izquierda, espacio); /* imprime parte izquierda */
}

/*
 * Libera recursivamente la memoria del árbol.
 * Se utiliza un recorrido postorden: primero los hijos, luego el padre.
 */
void liberarArbol(Nodo* raiz) {
    if (raiz == NULL) return;
    liberarArbol(raiz->izquierda);
    liberarArbol(raiz->derecha);
    free(raiz);
}

/*
 * Máximo del BST: se recorre siempre a la derecha.
 */
Nodo* maximo(Nodo* raiz) {
    if (raiz == NULL) return NULL;
    Nodo* actual = raiz;
    while (actual->derecha != NULL) {
        actual = actual->derecha;
    }
    return actual;
}

/*
 * Sucesor y predecesor inorden de un valor.
 * Se busca el nodo con el valor dado, registrando los posibles
 * predecesor y sucesor durante la bajada.
 * Luego, si el nodo tiene subárboles, se obtiene:
 *   - predecesor: máximo del subárbol izquierdo (o el último giro a la derecha)
 *   - sucesor   : mínimo del subárbol derecho (o el último giro a la izquierda)
 */
void sucesorPredecesor(Nodo* raiz, int valor, int* predecesor, int* sucesor) {
    *predecesor = -1;
    *sucesor = -1;
    if (raiz == NULL) return;

    Nodo* actual = raiz;
    Nodo* pred = NULL;  /* posible predecesor */
    Nodo* suc = NULL;   /* posible sucesor */

    /* Descenso hasta encontrar el nodo */
    while (actual != NULL) {
        if (valor < actual->dato) {
            suc = actual;               /* actual podría ser sucesor */
            actual = actual->izquierda;
        } else if (valor > actual->dato) {
            pred = actual;              /* actual podría ser predecesor */
            actual = actual->derecha;
        } else {
            break;                      /* nodo encontrado */
        }
    }

    if (actual == NULL) return;          /* el valor no está en el árbol */

    /* Predecesor: máximo del subárbol izquierdo, si existe */
    if (actual->izquierda != NULL) {
        Nodo* temp = actual->izquierda;
        while (temp->derecha != NULL)
            temp = temp->derecha;
        *predecesor = temp->dato;
    } else {
        *predecesor = (pred != NULL) ? pred->dato : -1;
    }

    /* Sucesor: mínimo del subárbol derecho, si existe */
    if (actual->derecha != NULL) {
        Nodo* temp = actual->derecha;
        while (temp->izquierda != NULL)
            temp = temp->izquierda;
        *sucesor = temp->dato;
    } else {
        *sucesor = (suc != NULL) ? suc->dato : -1;
    }
}