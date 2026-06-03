#include <stdio.h>      // printf, scanf
#include <stdlib.h>     // malloc, free, NULL

typedef struct NodoPila {
    int dato;                      // valor del nodo
    struct NodoPila* siguiente;    // puntero al nodo de abajo
} NodoPila;

typedef struct {
    NodoPila* tope;   // nodo superior de la pila
    int tam;          // cantidad de elementos
} Pila;

void inicializarPila(Pila* p) {
    p->tope = NULL;   // pila vacía
    p->tam = 0;       // sin elementos
}

int pilaVacia(const Pila* p) {
    return p->tope == NULL;   // si no hay tope, está vacía
}

int apilar(Pila* p, int dato) {
    NodoPila* n = (NodoPila*)malloc(sizeof(NodoPila)); // pedir memoria
    if (!n) {                                         // fallo de malloc
        printf("Error: memoria insuficiente para apilar.\n");
        return 0;
    }
    n->dato = dato;           // guardar valor
    n->siguiente = p->tope;   // enlazar debajo del tope actual
    p->tope = n;              // nuevo tope
    p->tam++;                 // incrementar tamaño
    return 1;
}

int desapilar(Pila* p, int* dato) {
    if (pilaVacia(p)) {                       // no hay elementos
        printf("Error: pila vacía.\n");
        return 0;
    }
    NodoPila* tmp = p->tope;                 // nodo a eliminar
    *dato = tmp->dato;                       // devolver valor
    p->tope = tmp->siguiente;                // bajar el tope
    free(tmp);                               // liberar memoria
    p->tam--;                                // decrementar tamaño
    return 1;
}

int verTope(const Pila* p, int* dato) {
    if (pilaVacia(p)) return 0;              // vacía, no hay tope
    *dato = p->tope->dato;                   // copiar valor del tope
    return 1;
}

int tamanioPila(const Pila* p) {
    return p->tam;                           // tamaño almacenado O(1)
}

void mostrarPila(const Pila* p) {
    const NodoPila* aux = p->tope;           // empezar desde el tope
    printf("Tope -> ");
    while (aux) {
        printf("%d ", aux->dato);            // imprimir dato
        aux = aux->siguiente;                // bajar al siguiente
    }
    printf("(tam=%d)\n", p->tam);
}

int copiarPila(const Pila* origen, Pila* destino) {
    inicializarPila(destino);                // destino vacío
    if (pilaVacia(origen)) return 1;         // nada que copiar
    Pila aux;
    inicializarPila(&aux);                   // pila auxiliar para invertir
    const NodoPila* cur = origen->tope;
    while (cur) {
        apilar(&aux, cur->dato);             // volcar origen en aux (invertido)
        cur = cur->siguiente;
    }
    while (!pilaVacia(&aux)) {
        int val;
        desapilar(&aux, &val);               // sacar de aux
        apilar(destino, val);                // apilar en destino (recupera orden)
    }
    return 1;
}

void invertirPilaReal(Pila* p) {
    if (pilaVacia(p)) return;                // vacía, no hace nada
    NodoPila *ant = NULL, *act = p->tope, *sig;
    while (act) {
        sig = act->siguiente;                // guardar siguiente
        act->siguiente = ant;                // invertir enlace
        ant = act;                           // avanzar anterior
        act = sig;                           // avanzar actual
    }
    p->tope = ant;                           // nuevo tope
}

void invertirPila(Pila* p) {
    invertirPilaReal(p);                     // alias directo
}

void ordenarPila(Pila* p) {
    Pila aux;
    inicializarPila(&aux);                   // pila auxiliar para ordenar
    while (!pilaVacia(p)) {
        int tmp;
        desapilar(p, &tmp);                  // sacar elemento de p
        while (!pilaVacia(&aux)) {
            int topAux;
            verTope(&aux, &topAux);
            if (topAux < tmp) break;         // mantener orden ascendente (menor arriba)
            desapilar(&aux, &topAux);
            apilar(p, topAux);               // devolver a p los mayores
        }
        apilar(&aux, tmp);                   // insertar en aux en orden
    }
    p->tope = aux.tope;                      // transferir nodos ordenados
    p->tam = aux.tam;
    aux.tope = NULL;                         // evitar que aux libere los nodos
    aux.tam = 0;
}

int pilasIguales(const Pila* a, const Pila* b) {
    if (a->tam != b->tam) return 0;          // distinto tamaño -> diferentes
    const NodoPila *pa = a->tope, *pb = b->tope;
    while (pa && pb) {
        if (pa->dato != pb->dato) return 0;  // diferencia encontrada
        pa = pa->siguiente;
        pb = pb->siguiente;
    }
    return 1;                                // todos iguales
}

void duplicarTope(Pila* p) {
    if (pilaVacia(p)) return;                // sin tope, no se puede
    int val;
    verTope(p, &val);                        // leer tope
    apilar(p, val);                          // apilar el mismo valor
}

void intercambiarTopes(Pila* p) {
    if (tamanioPila(p) < 2) return;          // mínimo 2 elementos
    int a, b;
    desapilar(p, &a);                        // sacar primero
    desapilar(p, &b);                        // sacar segundo
    apilar(p, a);                            // meter primero (era segundo)
    apilar(p, b);                            // meter segundo (era primero)
}

void vaciarPila(Pila* p) {
    while (!pilaVacia(p)) {
        int tmp;
        desapilar(p, &tmp);                  // eliminar uno a uno
    }
}

void liberarPila(Pila* p) {
    vaciarPila(p);                           // vaciar = liberar todo
}

int main() {
    Pila p;
    inicializarPila(&p);                     // pila vacía
    int opcion, valor;

    do {
        printf("\n--- MENU PILA ---\n");
        printf("1. Apilar\n");
        printf("2. Desapilar\n");
        printf("3. Ver tope\n");
        printf("4. Mostrar pila\n");
        printf("5. Tamaño\n");
        printf("6. Invertir\n");
        printf("7. Ordenar\n");
        printf("8. Duplicar tope\n");
        printf("9. Intercambiar topes\n");
        printf("10. Copiar y mostrar copia\n");
        printf("11. Comparar con otra pila\n");
        printf("12. Vaciar\n");
        printf("0. Salir\n");
        printf("Elija: ");
        scanf("%d", &opcion);                // leer opción

        switch(opcion) {
            case 1:
                printf("Valor: "); scanf("%d", &valor);
                apilar(&p, valor);           // push
                break;
            case 2:
                if (desapilar(&p, &valor))   // pop
                    printf("Desapilado: %d\n", valor);
                break;
            case 3:
                if (verTope(&p, &valor))     // peek
                    printf("Tope: %d\n", valor);
                break;
            case 4:
                mostrarPila(&p);             // imprimir pila
                break;
            case 5:
                printf("Tamaño: %d\n", tamanioPila(&p));
                break;
            case 6:
                invertirPila(&p);            // invertir enlaces
                printf("Pila invertida.\n");
                break;
            case 7:
                ordenarPila(&p);             // ordenar con pila auxiliar
                printf("Pila ordenada (menor en tope).\n");
                break;
            case 8:
                duplicarTope(&p);            // duplicar el tope
                printf("Tope duplicado.\n");
                break;
            case 9:
                if (tamanioPila(&p) >= 2) {
                    intercambiarTopes(&p);   // intercambiar los dos superiores
                    printf("Topes intercambiados.\n");
                } else {
                    printf("Se necesitan al menos dos elementos.\n");
                }
                break;
            case 10: {
                Pila copia;
                copiarPila(&p, &copia);      // copia profunda
                printf("Copia: ");
                mostrarPila(&copia);
                liberarPila(&copia);         // liberar copia
                break;
            }
            case 11: {
                Pila otra;
                inicializarPila(&otra);
                int n;
                printf("Cuantos elementos en la otra pila? ");
                scanf("%d", &n);
                for (int i=0; i<n; i++) {
                    printf("Elemento %d: ", i+1);
                    scanf("%d", &valor);
                    apilar(&otra, valor);    // llenar segunda pila
                }
                printf("Las pilas son %s\n", pilasIguales(&p, &otra) ? "iguales" : "diferentes");
                liberarPila(&otra);
                break;
            }
            case 12:
                vaciarPila(&p);              // vaciar completamente
                printf("Pila vaciada.\n");
                break;
            case 0:
                break;                       // salir
            default:
                printf("Opcion invalida\n");
        }
    } while (opcion != 0);

    liberarPila(&p);                         // liberar memoria final
    return 0;
}