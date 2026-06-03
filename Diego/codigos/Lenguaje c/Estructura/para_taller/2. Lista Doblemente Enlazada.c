#include <stdio.h>      // printf, scanf
#include <stdlib.h>     // malloc, free, NULL

typedef struct NodoDoble {
    int dato;                        // valor que guarda el nodo
    struct NodoDoble* anterior;      // puntero al nodo anterior
    struct NodoDoble* siguiente;     // puntero al nodo siguiente
} NodoDoble;

typedef struct {
    NodoDoble* cabeza;   // primer nodo
    NodoDoble* cola;     // último nodo
    int tam;             // cantidad de nodos
} ListaDoble;

void inicializarListaDoble(ListaDoble* l) {
    l->cabeza = l->cola = NULL;   // lista vacía
    l->tam = 0;                   // sin elementos
}

NodoDoble* crearNodoDoble(int dato) {
    NodoDoble* n = (NodoDoble*)malloc(sizeof(NodoDoble)); // pedir memoria
    if (!n) {                                           // si falla malloc
        printf("Error: memoria insuficiente para nodo doble.\n");
        return NULL;                                    // devolver NULL
    }
    n->dato = dato;                  // asignar valor
    n->anterior = n->siguiente = NULL; // sin enlaces todavía
    return n;                        // retornar nuevo nodo
}

int insertarInicioDoble(ListaDoble* l, int dato) {
    NodoDoble* n = crearNodoDoble(dato); // crear nodo
    if (!n) return 0;                    // fallo de memoria
    n->siguiente = l->cabeza;            // enlazar con la antigua cabeza
    if (l->cabeza)                       // si había cabeza
        l->cabeza->anterior = n;         // su anterior es n
    else                                 // lista vacía
        l->cola = n;                     // n también es la cola
    l->cabeza = n;                       // n es la nueva cabeza
    l->tam++;                            // incrementar tamaño
    return 1;                            // éxito
}

int insertarFinalDoble(ListaDoble* l, int dato) {
    NodoDoble* n = crearNodoDoble(dato); // crear nodo
    if (!n) return 0;                    // sin memoria
    if (!l->cola) {                      // lista vacía?
        l->cabeza = l->cola = n;         // cabeza y cola apuntan a n
    } else {
        l->cola->siguiente = n;          // enganchar al final
        n->anterior = l->cola;           // enlace hacia atrás
        l->cola = n;                     // actualizar cola
    }
    l->tam++;                            // un nodo más
    return 1;
}

int insertarOrdenadoDoble(ListaDoble* l, int dato) {
    NodoDoble* n = crearNodoDoble(dato); // crear nodo
    if (!n) return 0;
    if (!l->cabeza || l->cabeza->dato >= dato) { // vacía o menor que cabeza
        n->siguiente = l->cabeza;
        if (l->cabeza) l->cabeza->anterior = n; // ajustar anterior de cabeza
        else l->cola = n;                       // era vacía, cola también n
        l->cabeza = n;                          // nueva cabeza
    } else {
        NodoDoble* act = l->cabeza;              // buscar posición
        while (act->siguiente && act->siguiente->dato < dato)
            act = act->siguiente;               // avanzar mientras sea menor
        n->siguiente = act->siguiente;           // enlazar con siguiente
        n->anterior = act;                       // enlazar con anterior
        if (act->siguiente) act->siguiente->anterior = n; // ajustar anterior del siguiente
        else l->cola = n;                        // si se inserta al final, actualizar cola
        act->siguiente = n;                      // colocar n después de act
    }
    l->tam++;
    return 1;
}

int insertarPosicionDoble(ListaDoble* l, int dato, int pos) {
    if (pos < 0 || pos > l->tam) return 0;       // posición inválida
    if (pos == 0) return insertarInicioDoble(l, dato);   // delegar
    if (pos == l->tam) return insertarFinalDoble(l, dato); // delegar
    NodoDoble* act = l->cabeza;
    for (int i = 0; i < pos; i++) act = act->siguiente; // llegar al nodo en pos
    NodoDoble* n = crearNodoDoble(dato);
    if (!n) return 0;
    n->siguiente = act;                     // n va antes de act
    n->anterior = act->anterior;            // enlace hacia atrás
    act->anterior->siguiente = n;           // el anterior de act apunta a n
    act->anterior = n;                      // ajustar anterior de act
    l->tam++;
    return 1;
}

int eliminarDatoDoble(ListaDoble* l, int dato) {
    NodoDoble* act = l->cabeza;
    while (act) {
        if (act->dato == dato) {                 // encontrado
            if (act->anterior)                    // no es la cabeza
                act->anterior->siguiente = act->siguiente;
            else                                  // es la cabeza
                l->cabeza = act->siguiente;
            if (act->siguiente)                   // no es la cola
                act->siguiente->anterior = act->anterior;
            else                                  // es la cola
                l->cola = act->anterior;
            free(act);                            // liberar nodo
            l->tam--;
            return 1;
        }
        act = act->siguiente;                     // siguiente nodo
    }
    return 0;                                     // no encontrado
}

int eliminarPosicionDoble(ListaDoble* l, int pos) {
    if (pos < 0 || pos >= l->tam) return 0;       // posición inválida
    NodoDoble* act = l->cabeza;
    for (int i = 0; i < pos; i++) act = act->siguiente; // nodo a eliminar
    if (act->anterior)                            // ajustar anterior
        act->anterior->siguiente = act->siguiente;
    else                                          // era cabeza
        l->cabeza = act->siguiente;
    if (act->siguiente)                           // ajustar siguiente
        act->siguiente->anterior = act->anterior;
    else                                          // era cola
        l->cola = act->anterior;
    free(act);
    l->tam--;
    return 1;
}

int buscarDoble(ListaDoble* l, int dato) {
    NodoDoble* p = l->cabeza;
    while (p) {
        if (p->dato == dato) return 1;             // encontrado
        p = p->siguiente;
    }
    return 0;                                      // no está
}

int longitudDoble(ListaDoble* l) {
    return l->tam;                                 // tamaño almacenado O(1)
}

void mostrarAdelante(ListaDoble* l) {
    NodoDoble* p = l->cabeza;
    while (p) {
        printf("%d <-> ", p->dato);                // imprimir dato
        p = p->siguiente;
    }
    printf("NULL (tam=%d)\n", l->tam);             // fin y tamaño
}

void mostrarAtras(ListaDoble* l) {
    NodoDoble* p = l->cola;
    while (p) {
        printf("%d <-> ", p->dato);                // imprimir dato
        p = p->anterior;                           // retroceder
    }
    printf("NULL (tam=%d)\n", l->tam);
}

int copiarListaDoble(ListaDoble* origen, ListaDoble* destino) {
    inicializarListaDoble(destino);                // preparar destino
    NodoDoble* p = origen->cabeza;
    while (p) {
        if (!insertarFinalDoble(destino, p->dato)) { // copiar cada dato
            liberarListaDoble(destino);            // si falla, liberar todo
            return 0;
        }
        p = p->siguiente;
    }
    return 1;
}

void invertirDoble(ListaDoble* l) {
    NodoDoble* act = l->cabeza;
    l->cola = l->cabeza;                    // la nueva cola será la antigua cabeza
    while (act) {
        NodoDoble* temp = act->siguiente;   // guardar siguiente
        act->siguiente = act->anterior;     // invertir enlace siguiente
        act->anterior = temp;               // invertir enlace anterior
        act = temp;                         // avanzar al que era siguiente
    }
    if (l->cola) {                          // si la lista no estaba vacía
        l->cabeza = l->cola;                // la cabeza es la antigua cola
        while (l->cabeza->anterior)          // moverse hasta el nuevo primer nodo
            l->cabeza = l->cabeza->anterior;
    }
}

void liberarListaDoble(ListaDoble* l) {
    NodoDoble* act = l->cabeza;
    while (act) {
        NodoDoble* temp = act;              // nodo a liberar
        act = act->siguiente;               // avanzar al siguiente
        free(temp);                         // liberar
    }
    l->cabeza = l->cola = NULL;
    l->tam = 0;
}

void concatenarDoble(ListaDoble* l1, ListaDoble* l2) {
    if (!l2->cabeza) return;                     // l2 vacía, nada que hacer
    if (!l1->cabeza) {                           // l1 vacía, copiar punteros
        l1->cabeza = l2->cabeza;
        l1->cola = l2->cola;
    } else {
        l1->cola->siguiente = l2->cabeza;        // enlazar final de l1 con inicio de l2
        l2->cabeza->anterior = l1->cola;         // enlace inverso
        l1->cola = l2->cola;                     // nueva cola
    }
    l1->tam += l2->tam;                          // sumar tamaños
    l2->cabeza = l2->cola = NULL;                // l2 queda vacía
    l2->tam = 0;
}

// --- MergeSort para lista doble ---
NodoDoble* dividirDoble(NodoDoble* cabeza) {
    NodoDoble* rapido = cabeza->siguiente;       // avanza de a dos
    NodoDoble* lento = cabeza;                   // avanza de a uno
    while (rapido) {
        rapido = rapido->siguiente;
        if (rapido) {                            // si puede dar otro paso
            lento = lento->siguiente;
            rapido = rapido->siguiente;
        }
    }
    NodoDoble* mitad = lento->siguiente;         // segunda mitad
    if (mitad) mitad->anterior = NULL;           // cortar enlace anterior
    lento->siguiente = NULL;                     // cortar la lista
    return mitad;
}

NodoDoble* fusionarDoble(NodoDoble* a, NodoDoble* b) {
    if (!a) return b;
    if (!b) return a;
    if (a->dato <= b->dato) {                    // elegir el menor
        a->siguiente = fusionarDoble(a->siguiente, b);
        if (a->siguiente) a->siguiente->anterior = a; // ajustar enlace inverso
        a->anterior = NULL;                      // cabeza no tiene anterior
        return a;
    } else {
        b->siguiente = fusionarDoble(a, b->siguiente);
        if (b->siguiente) b->siguiente->anterior = b;
        b->anterior = NULL;
        return b;
    }
}

void mergeSortDobleRec(NodoDoble** cabezaRef) {
    NodoDoble* cabeza = *cabezaRef;
    if (!cabeza || !cabeza->siguiente) return;   // 0 o 1 elemento -> ya ordenado
    NodoDoble* mitad = dividirDoble(cabeza);     // dividir
    mergeSortDobleRec(&cabeza);                  // ordenar primera mitad
    mergeSortDobleRec(&mitad);                   // ordenar segunda mitad
    *cabezaRef = fusionarDoble(cabeza, mitad);   // fusionar
}

void mergeSortDoble(ListaDoble* l) {
    mergeSortDobleRec(&(l->cabeza));             // ordenar recursivamente
    if (!l->cabeza) {
        l->cola = NULL;
        return;
    }
    l->cola = l->cabeza;                         // reconstruir cola
    while (l->cola->siguiente) l->cola = l->cola->siguiente;
}

void eliminarDuplicadosDoble(ListaDoble* l) {
    NodoDoble* act = l->cabeza;
    while (act && act->siguiente) {
        if (act->dato == act->siguiente->dato) {   // duplicado
            NodoDoble* tmp = act->siguiente;        // nodo a eliminar
            act->siguiente = tmp->siguiente;        // puentear
            if (tmp->siguiente) tmp->siguiente->anterior = act; // ajustar anterior
            else l->cola = act;                     // si era el último, actualizar cola
            free(tmp);
            l->tam--;
        } else {
            act = act->siguiente;                   // avanzar
        }
    }
}

int reemplazarDoble(ListaDoble* l, int pos, int nuevoDato) {
    if (pos < 0 || pos >= l->tam) return 0;        // posición inválida
    NodoDoble* act = l->cabeza;
    for (int i = 0; i < pos; i++) act = act->siguiente; // nodo en pos
    act->dato = nuevoDato;                          // cambiar valor
    return 1;
}

int moverNodo(ListaDoble* l, int posOrigen, int posDestino) {
    if (posOrigen < 0 || posOrigen >= l->tam ||
        posDestino < 0 || posDestino > l->tam) return 0; // rangos inválidos
    if (posOrigen == posDestino) return 1;          // nada que hacer

    // Extraer nodo en posOrigen
    NodoDoble* nodo = l->cabeza;
    for (int i = 0; i < posOrigen; i++) nodo = nodo->siguiente;
    if (nodo->anterior) nodo->anterior->siguiente = nodo->siguiente;
    else l->cabeza = nodo->siguiente;               // era cabeza
    if (nodo->siguiente) nodo->siguiente->anterior = nodo->anterior;
    else l->cola = nodo->anterior;                  // era cola

    // Insertar nodo en posDestino
    if (posDestino == 0) {                          // al inicio
        nodo->siguiente = l->cabeza;
        nodo->anterior = NULL;
        if (l->cabeza) l->cabeza->anterior = nodo;
        else l->cola = nodo;
        l->cabeza = nodo;
    } else if (posDestino == l->tam - 1) {          // al final (tam ya reducido en 1)
        nodo->siguiente = NULL;
        nodo->anterior = l->cola;
        l->cola->siguiente = nodo;
        l->cola = nodo;
    } else {                                        // en medio
        NodoDoble* ref = l->cabeza;
        for (int i = 0; i < posDestino; i++) ref = ref->siguiente;
        nodo->siguiente = ref;
        nodo->anterior = ref->anterior;
        ref->anterior->siguiente = nodo;
        ref->anterior = nodo;
    }
    return 1;
}

void hacerCircularDoble(ListaDoble* l) {
    if (!l->cabeza) return;                         // vacía, no hace nada
    l->cola->siguiente = l->cabeza;                 // enlazar cola con cabeza
    l->cabeza->anterior = l->cola;                  // enlace inverso
    l->cola = NULL;                                 // ahora es circular, cola no definida
}

void deshacerCircularDoble(ListaDoble* l) {
    if (!l->cabeza) return;
    NodoDoble* ultimo = l->cabeza;
    while (ultimo->siguiente && ultimo->siguiente != l->cabeza)
        ultimo = ultimo->siguiente;                 // buscar último nodo
    if (ultimo->siguiente == l->cabeza) {           // si era circular
        ultimo->siguiente = NULL;                   // romper enlace
        l->cabeza->anterior = NULL;                 // romper enlace inverso
        l->cola = ultimo;                           // restaurar cola lineal
    }
}

// ---------- MAIN DE PRUEBA ----------
int main() {
    ListaDoble lista;
    inicializarListaDoble(&lista);                  // lista vacía
    int opcion, valor, pos;

    do {
        printf("\n--- MENU LISTA DOBLE ---\n");
        printf("1. Insertar al inicio\n");
        printf("2. Insertar al final\n");
        printf("3. Insertar ordenado\n");
        printf("4. Insertar en posicion\n");
        printf("5. Eliminar por valor\n");
        printf("6. Eliminar por posicion\n");
        printf("7. Buscar\n");
        printf("8. Mostrar adelante\n");
        printf("9. Mostrar atras\n");
        printf("10. Invertir\n");
        printf("11. Ordenar (MergeSort)\n");
        printf("12. Copiar a otra lista\n");
        printf("13. Concatenar con lista auxiliar\n");
        printf("14. Reemplazar dato en posicion\n");
        printf("15. Mover nodo\n");
        printf("16. Hacer circular\n");
        printf("17. Deshacer circular\n");
        printf("0. Salir\n");
        printf("Elija: ");
        scanf("%d", &opcion);                       // leer opción

        switch(opcion) {
            case 1:
                printf("Valor: "); scanf("%d", &valor);
                insertarInicioDoble(&lista, valor);
                break;
            case 2:
                printf("Valor: "); scanf("%d", &valor);
                insertarFinalDoble(&lista, valor);
                break;
            case 3:
                printf("Valor: "); scanf("%d", &valor);
                insertarOrdenadoDoble(&lista, valor);
                break;
            case 4:
                printf("Valor y posicion: "); scanf("%d %d", &valor, &pos);
                if (!insertarPosicionDoble(&lista, valor, pos))
                    printf("Posicion invalida\n");
                break;
            case 5:
                printf("Valor a eliminar: "); scanf("%d", &valor);
                if (eliminarDatoDoble(&lista, valor))
                    printf("Eliminado\n");
                else
                    printf("No encontrado\n");
                break;
            case 6:
                printf("Posicion a eliminar: "); scanf("%d", &pos);
                if (!eliminarPosicionDoble(&lista, pos))
                    printf("Posicion invalida\n");
                break;
            case 7:
                printf("Valor a buscar: "); scanf("%d", &valor);
                printf(buscarDoble(&lista, valor) ? "Encontrado\n" : "No encontrado\n");
                break;
            case 8:
                mostrarAdelante(&lista);            // recorrido de cabeza a cola
                break;
            case 9:
                mostrarAtras(&lista);               // recorrido de cola a cabeza
                break;
            case 10:
                invertirDoble(&lista);
                printf("Lista invertida.\n");
                break;
            case 11:
                mergeSortDoble(&lista);
                printf("Ordenada con MergeSort.\n");
                break;
            case 12: {
                ListaDoble copia;
                if (copiarListaDoble(&lista, &copia)) {
                    printf("Copia: ");
                    mostrarAdelante(&copia);
                    liberarListaDoble(&copia);
                }
                break;
            }
            case 13: {
                ListaDoble aux;
                inicializarListaDoble(&aux);
                int n;
                printf("Cuantos elementos en lista auxiliar? ");
                scanf("%d", &n);
                for (int i = 0; i < n; i++) {
                    printf("Elemento %d: ", i+1);
                    scanf("%d", &valor);
                    insertarFinalDoble(&aux, valor);
                }
                concatenarDoble(&lista, &aux);
                printf("Listas concatenadas.\n");
                break;
            }
            case 14:
                printf("Posicion y nuevo valor: "); scanf("%d %d", &pos, &valor);
                if (!reemplazarDoble(&lista, pos, valor))
                    printf("Posicion invalida\n");
                break;
            case 15: {
                int orig, dest;
                printf("Posicion origen y destino: "); scanf("%d %d", &orig, &dest);
                if (!moverNodo(&lista, orig, dest))
                    printf("Error al mover\n");
                break;
            }
            case 16:
                hacerCircularDoble(&lista);
                printf("Lista vuelta circular (no usar mostrar normal).\n");
                break;
            case 17:
                deshacerCircularDoble(&lista);
                printf("Circularidad deshecha.\n");
                break;
            case 0:
                break;                              // salir del bucle
            default:
                printf("Opcion invalida\n");
        }
    } while (opcion != 0);

    liberarListaDoble(&lista);                      // liberar toda la memoria
    return 0;
}